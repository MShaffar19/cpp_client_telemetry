// Copyright (c) Microsoft. All rights reserved.

#include "OfflineStorageHandler.hpp"
#include "offline/OfflineStorage_SQLite.hpp"
#include "LogManager.hpp"
#include <algorithm>
#include <numeric>
#include <set>

namespace ARIASDK_NS_BEGIN {


ARIASDK_LOG_INST_COMPONENT_CLASS(OfflineStorageHandler, "AriaSDK.StorageHandler", "Aria telemetry client - OfflineStorageHandler class");

OfflineStorageHandler::OfflineStorageHandler(LogConfiguration& configuration, IRuntimeConfig& runtimeConfig)
    : m_logConfiguration(configuration),
    m_runtimeConfig(runtimeConfig),
    m_offlineStorageMemory(nullptr),
    m_offlineStorageDisk(nullptr),
    m_readFromMemory(false),
    m_lastReadCount(0),
    m_shutdownStarted(false),
    m_memoryDbSize(0),
    m_queryDbSize(0),
    m_isStorageFullNotificationSend(false)
{
    bool error;
    int percentage = configuration.GetIntProperty(CFG_INT_CACHE_MEMORY_FULL_NOTIFICATION_PERCENTAGE, error);
    unsigned int cacheMemorySizeLimitInBytes = configuration.GetIntProperty(CFG_INT_RAM_QUEUE_SIZE, error);
    if (percentage > 0 && percentage <= 100)
    {
        m_memoryDbSizeNotificationLimit = (percentage * cacheMemorySizeLimitInBytes) /100;
    }
    else
    {// incase user has specified bad percentage, we stck to 75%
        m_memoryDbSizeNotificationLimit = (DB_FULL_NOTIFICATION_DEFAULT_PERCENTAGE * cacheMemorySizeLimitInBytes)/100;
    }
}

OfflineStorageHandler::~OfflineStorageHandler()
{
    if (nullptr != m_offlineStorageMemory)
    {
        m_offlineStorageMemory.reset();
    }	
    m_offlineStorageDisk.reset();
}

void OfflineStorageHandler::Initialize(IOfflineStorageObserver& observer)
{
    m_observer = &observer;
    bool error;
    unsigned int cacheMemorySizeLimitInBytes = m_logConfiguration.GetIntProperty(CFG_INT_RAM_QUEUE_SIZE, error);
    if (cacheMemorySizeLimitInBytes > 0)
    {
        LogConfiguration inMemoryConfig(m_logConfiguration);
        inMemoryConfig.SetProperty(CFG_STR_CACHE_FILE_PATH,":memory:");

        m_offlineStorageMemory.reset(new OfflineStorage_SQLite(inMemoryConfig, m_runtimeConfig));
        m_offlineStorageMemory->Initialize(*this);
    }

    m_offlineStorageDisk.reset(new OfflineStorage_SQLite(m_logConfiguration, m_runtimeConfig));
    m_offlineStorageDisk->Initialize(*this);
    m_shutdownStarted = false;

    ARIASDK_LOG_DETAIL("Initializing offline storage handler");
}

void OfflineStorageHandler::Shutdown()
{
    ARIASDK_LOG_DETAIL("Shutting down offline storage handler");
    m_shutdownStarted = true;
    if (nullptr != m_offlineStorageMemory)
    {  // transfer data from Memory DB to Disk DB before shutting down.
        std::vector<StorageRecord>* records = m_offlineStorageMemory->GetRecords(true, EventPriority_Low, 0);
        std::vector<StorageRecord>::const_iterator iter;
        for (iter = records->begin(); iter != records->end(); iter++)
        {
            m_offlineStorageDisk->StoreRecord(*iter);
        }		
        records->clear();
        delete records;        
    }
    m_offlineStorageDisk->Shutdown();	
    if (nullptr != m_offlineStorageMemory)
    {
        m_offlineStorageMemory->Shutdown();
    }
}

unsigned OfflineStorageHandler::GetSize() 
{
    return 0;
}

bool OfflineStorageHandler::StoreRecord(StorageRecord const& record)
{
    if (nullptr != m_offlineStorageMemory && !m_shutdownStarted)
    {     
        ++m_queryDbSize;
        //query DB size from DB only every 100 Events, use size calculation done before that
        if ( m_queryDbSize >= 100)
        {
            m_queryDbSize = 0;
            m_memoryDbSize = m_offlineStorageMemory->GetSize();
        }
      
        m_queryDbSize = m_queryDbSize + static_cast<unsigned>(/* empiric estimate */ 32 + 2 * record.id.size() + record.tenantToken.size() + record.blob.size());

        //check if Application needs to be notified
        if (m_memoryDbSize > m_memoryDbSizeNotificationLimit && !m_isStorageFullNotificationSend)
        {
            DebugEvent evt;
            evt.type = DebugEventType::EVT_STORAGE_FULL;
            evt.param1 = 1;
            LogManager::DispatchEvent(evt);
            m_isStorageFullNotificationSend = true;
        }
        bool error;
        unsigned int cacheMemorySizeLimitInBytes = m_logConfiguration.GetIntProperty(CFG_INT_RAM_QUEUE_SIZE, error);

        if (m_queryDbSize > cacheMemorySizeLimitInBytes)
        {
            // transfer data from Memory DB to Disk DB
            std::vector<StorageRecord>* records = m_offlineStorageMemory->GetRecords(false, EventPriority_Low, 500);
            std::vector<StorageRecord>::const_iterator iter;
            std::vector<StorageRecordId> recordIds;
            for (iter = records->begin(); iter != records->end(); iter++)
            {
                recordIds.push_back(iter->id);
                m_offlineStorageDisk->StoreRecord(*iter);
            }
            HttpHeaders temp;
            bool fromMemory;
            m_offlineStorageMemory->DeleteRecords(recordIds, temp, fromMemory);

            delete records;
            //Resize the memory DB after delete
            m_offlineStorageMemory->ResizeDb();
            m_queryDbSize = 100;
            m_isStorageFullNotificationSend = false;
        }
        m_offlineStorageMemory->StoreRecord(record);
    }
    else
    {
        m_offlineStorageDisk->StoreRecord(record);
    }

    return true;
}

bool OfflineStorageHandler::ResizeDb()
{
    if (nullptr != m_offlineStorageMemory )
    {
        m_offlineStorageMemory->ResizeDb();
    }

    m_offlineStorageDisk->ResizeDb();
    
    return true;
}

bool OfflineStorageHandler::GetAndReserveRecords(std::function<bool(StorageRecord&&)> const& consumer, unsigned leaseTimeMs, EventPriority minPriority, unsigned maxCount)
{
    bool returnValue = false;
    m_lastReadCount = 0;
    if (nullptr != m_offlineStorageMemory && m_offlineStorageMemory->GetAndReserveRecords(consumer, leaseTimeMs, minPriority, maxCount))
    {
        m_readFromMemory = true;
        returnValue =  true;
        m_lastReadCount = m_offlineStorageMemory->LastReadRecordCount();
    }

    if(nullptr == m_offlineStorageMemory || m_lastReadCount == 0)
    { //nothing in memory left to send. lets end from disk
        m_readFromMemory = false;
        returnValue =  m_offlineStorageDisk->GetAndReserveRecords(consumer, leaseTimeMs, minPriority, maxCount);
        m_lastReadCount = m_offlineStorageDisk->LastReadRecordCount();
    }

    return returnValue;
}

bool OfflineStorageHandler::IsLastReadFromMemory()
{
    return m_readFromMemory;
}
unsigned OfflineStorageHandler::LastReadRecordCount()
{
    return  m_lastReadCount;
}

std::vector<StorageRecord>* OfflineStorageHandler::GetRecords(bool shutdown, EventPriority minPriority, unsigned maxCount) 
{
    UNREFERENCED_PARAMETER(shutdown);
    UNREFERENCED_PARAMETER(minPriority);
    UNREFERENCED_PARAMETER(maxCount);
    std::vector<StorageRecord>* records = new std::vector<StorageRecord>();
    return records;
}

void OfflineStorageHandler::DeleteRecords(std::vector<StorageRecordId> const& ids, HttpHeaders headers, bool& fromMemory)
{    
    if (m_shutdownStarted)
    {
        return;
    }
    ARIASDK_LOG_DETAIL(" OfflineStorageHandler Deleting %u sent event(s) {%s%s}...",
        static_cast<unsigned>(ids.size()), ids.front().c_str(), (ids.size() > 1) ? ", ..." : "");
    if (fromMemory && nullptr != m_offlineStorageMemory)
    {
        m_offlineStorageMemory->DeleteRecords(ids, headers, fromMemory);
    }
    else
    {
        m_offlineStorageDisk->DeleteRecords(ids, headers, fromMemory);
    }
}

void OfflineStorageHandler::ReleaseRecords(std::vector<StorageRecordId> const& ids, bool incrementRetryCount, HttpHeaders headers, bool& fromMemory)
{
    if (m_shutdownStarted)
    {
        return;
    }
    if (fromMemory && nullptr != m_offlineStorageMemory)
    {
        m_offlineStorageMemory->ReleaseRecords(ids, incrementRetryCount, headers, fromMemory);
    }
    else
    {
        m_offlineStorageDisk->ReleaseRecords(ids, incrementRetryCount, headers, fromMemory);
    }
}

bool OfflineStorageHandler::StoreSetting(std::string const& name, std::string const& value)
{
    m_offlineStorageDisk->StoreSetting(name, value);
    return true;
}

std::string OfflineStorageHandler::GetSetting(std::string const& name)
{
    return m_offlineStorageDisk->GetSetting(name);
}


void OfflineStorageHandler::OnStorageOpened(std::string const& type)
{
    m_observer->OnStorageOpened(type);
}

void OfflineStorageHandler::OnStorageFailed(std::string const& reason)
{
    m_observer->OnStorageFailed(reason);
}

void OfflineStorageHandler::OnStorageTrimmed(unsigned numRecords)
{
    m_observer->OnStorageTrimmed(numRecords);
}

void OfflineStorageHandler::OnStorageRecordsDropped(unsigned numRecords)
{
    m_observer->OnStorageRecordsDropped(numRecords);
}

} ARIASDK_NS_END
