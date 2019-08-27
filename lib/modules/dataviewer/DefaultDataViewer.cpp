#include "DefaultDataViewer.hpp"

#include "http/HttpClientFactory.hpp"
#include "public/DebugEvents.hpp"
#include "pal/PAL.hpp"

#include <algorithm>
#include <chrono>

namespace ARIASDK_NS_BEGIN
{

    DefaultDataViewer::DefaultDataViewer(const std::shared_ptr<IHttpClient>& httpClient, const char* machineFriendlyIdentifier) :
        m_httpClient(httpClient),
        m_isTransmissionEnabled(false), 
        m_enabledRemoteViewerNotifyCalled(false),
        m_endpoint(""),
        m_machineFriendlyIdentifier(machineFriendlyIdentifier)
    {
        if (m_httpClient == nullptr)
        {
    #ifdef HAVE_MAT_DEFAULT_HTTP_CLIENT
            m_httpClient = std::shared_ptr<IHttpClient>(HttpClientFactory::Create());
    #else
            throw std::invalid_argument("httpClient");
    #endif
        }

        if (IsNullOrEmpty(m_machineFriendlyIdentifier))
        {
            throw std::invalid_argument("machineFriendlyIdentifier");
        }
    }

    bool DefaultDataViewer::IsNullOrEmpty(const char* toCheck) noexcept
    {
        if (!toCheck || strlen(toCheck) == 0)
            return true;

        return std::all_of(toCheck, strlen(toCheck) + toCheck, [](char c)
            {
                return isspace(c);
            });
    }

    void DefaultDataViewer::ReceiveData(const std::vector<std::uint8_t>& packetData) noexcept
    {
        ProcessReceivedPacket(packetData);
    }

    bool DefaultDataViewer::EnableLocalViewer()
    {
        throw std::logic_error("Function not implemented");
    }

    bool DefaultDataViewer::EnableLocalViewer(const std::string& /*AppId*/, const std::string& /*AppPackage*/)
    {
        throw std::logic_error("Function not implemented");
    }

    void DefaultDataViewer::ProcessReceivedPacket(const std::vector<std::uint8_t>& packetData)
    {
        std::lock_guard<std::mutex> transmissionLock(m_transmissionGuard);
        if (!IsTransmissionEnabled())
            return;
        SendPacket(packetData);
    }

    void DefaultDataViewer::SendPacket(const std::vector<std::uint8_t>& packetData)
    {
        auto request = m_httpClient->CreateRequest();
        request->SetMethod("POST");

        auto localPacketData = std::vector<std::uint8_t> { packetData };
        request->SetBody(localPacketData);

        auto& header = request->GetHeaders();
        header.add("Machine-Identifier", m_machineFriendlyIdentifier);
        header.add("App-Name", PAL::GetSystemInformation()->GetAppId());
        header.add("App-Platform", PAL::GetSystemInformation()->GetDeviceClass());
        header.add("Content-Type", "Application/bond-compact-binary");

        request->SetUrl(m_endpoint);
        m_httpClient->SendRequestAsync(request, this);
    }

    void DefaultDataViewer::OnHttpResponse(IHttpResponse* response)
    {
        if (response == nullptr || response->GetStatusCode() != 200)
        {
            m_isTransmissionEnabled.exchange(false);
            m_httpClient->CancelAllRequests();
        }
        else if (!IsTransmissionEnabled())
        {
            m_isTransmissionEnabled.exchange(true);
        }

        if (!m_enabledRemoteViewerNotifyCalled)
        {
            m_enabledRemoteViewerNotifyCalled.exchange(true);
            m_initializationEvent.notify_all();
        }
    }

    bool DefaultDataViewer::EnableRemoteViewer(const char* endpoint)
    {
        std::unique_lock<std::mutex> transmissionLock(m_transmissionGuard);
        if (IsNullOrEmpty(endpoint))
        {
            throw std::invalid_argument("endpoint is null or empty");
        }

        m_endpoint = endpoint;

        m_enabledRemoteViewerNotifyCalled.exchange(false);
        SendPacket(std::vector<std::uint8_t>{});

        if (!m_enabledRemoteViewerNotifyCalled && !m_initializationEvent.wait_for(transmissionLock, std::chrono::seconds(30), []() noexcept
            {
                return false;
            }))
        {
            m_endpoint = "";
            m_isTransmissionEnabled.exchange(false);
        }
        return m_isTransmissionEnabled;
    }

    bool DefaultDataViewer::DisableViewer() noexcept
    {
        m_isTransmissionEnabled.exchange(false);
        
        {
            std::lock_guard<std::mutex> onDisableNotificationLock(m_onDisableNotificationGuard);
            for (const auto& notification : m_onDisabledNotification)
            {
                notification();
            }
        }

        return true;
    }

    void DefaultDataViewer::RegisterOnDisableNotification(const std::function<void()>& onDisabled) noexcept
    {
        std::lock_guard<std::mutex> transmissionLock(m_onDisableNotificationGuard);
        m_onDisabledNotification.push_back(onDisabled);
    }

} ARIASDK_NS_END
