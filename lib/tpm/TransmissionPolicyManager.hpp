// Copyright (c) Microsoft. All rights reserved.
#ifndef TRANSMISSIONPOLICYMANAGER_HPP
#define TRANSMISSIONPOLICYMANAGER_HPP

#include "IBandwidthController.hpp"

#include "api/IRuntimeConfig.hpp"
#include "backoff/IBackoff.hpp"
#include "pal/PAL.hpp"

#include "system/Contexts.hpp"
#include "system/Route.hpp"
#include "system/ITelemetrySystem.hpp"

#include "DeviceStateHandler.hpp"
#include "pal/TaskDispatcher.hpp"

#include "TransmitProfiles.hpp"

#include <atomic>
#include <chrono>
#include <cstdint>
#include <limits>
#include <set>

namespace ARIASDK_NS_BEGIN {

// This macro allows to specify max upload task cancellation wait time at compile-time,
// addressing the case when a task that we are trying to cancel is currently running.
// Default value:   500ms       - sufficient for upload scheduler/batcher task to finish.
// Alternate value: UINT64_MAX  - for infinite wait until the task is completed.
#ifdef UPLOAD_TASK_CANCEL_TIME_MS
static_assert(std::numeric_limits<std::chrono::milliseconds::rep>::max() >= UPLOAD_TASK_CANCEL_TIME_MS, "std::numeric_limits<std::chrono::milliseconds::rep>::max() >= UPLOAD_TASK_CANCEL_TIME_MS");
static_assert(UPLOAD_TASK_CANCEL_TIME_MS >= 0, "UPLOAD_TASK_CANCEL_TIME_MS >= 0");
constexpr std::chrono::milliseconds DefaultTaskCancelTime { uint64_t { UPLOAD_TASK_CANCEL_TIME_MS } };
#else
constexpr std::chrono::milliseconds DefaultTaskCancelTime { 500 };
#endif

    class TransmissionPolicyManager
    {

    public:
        TransmissionPolicyManager(ITelemetrySystem& system, ITaskDispatcher& taskDispatcher, IBandwidthController* bandwidthController);
        virtual ~TransmissionPolicyManager();
        virtual void scheduleUpload(int delayInMs, EventLatency latency, bool force = false);

    protected:
        MATSDK_LOG_DECL_COMPONENT_CLASS();
        void checkBackoffConfigUpdate();
        void resetBackoff();
        int  increaseBackoff();

        void uploadAsync(EventLatency priority);
        void finishUpload(EventsUploadContextPtr const& ctx, int nextUploadInMs);
        bool updateTimersIfNecessary();

        bool handleStart();
        bool handlePause();
        bool handleStop();
        void handleFinishAllUploads();

        void handleEventArrived(IncomingEventContextPtr const& event);

        void handleNothingToUpload(EventsUploadContextPtr const& ctx);
        void handlePackagingFailed(EventsUploadContextPtr const& ctx);
        void handleEventsUploadSuccessful(EventsUploadContextPtr const& ctx);
        void handleEventsUploadRejected(EventsUploadContextPtr const& ctx);
        void handleEventsUploadFailed(EventsUploadContextPtr const& ctx);
        void handleEventsUploadAborted(EventsUploadContextPtr const& ctx);

        EventLatency calculateNewPriority();

        std::mutex                       m_lock;

        ITelemetrySystem&                m_system;
        ITaskDispatcher&                 m_taskDispatcher;
        IRuntimeConfig&                  m_config;
        IBandwidthController*            m_bandwidthController;

        std::recursive_mutex             m_backoffMutex;
        std::string                      m_backoffConfig;           // TODO: [MG] - move to config
        std::unique_ptr<IBackoff>        m_backoff;
        DeviceStateHandler               m_deviceStateHandler;

        std::atomic<bool>                m_isPaused;
        std::atomic<bool>                m_isUploadScheduled;
        uint64_t                         m_scheduledUploadTime;
        std::mutex                       m_scheduledUploadMutex;
        PAL::DeferredCallbackHandle      m_scheduledUpload;
        bool                             m_scheduledUploadAborted;

        std::mutex                       m_activeUploads_lock;
        std::set<EventsUploadContextPtr> m_activeUploads;
        
        /// <summary>
        /// Thread-safe method to add the upload to active uploads.
        /// </summary>
        /// <param name="ctx">The CTX.</param>
        void addUpload(EventsUploadContextPtr const& ctx);
        
        /// <summary>
        /// Thread-safe method to remove the upload from active uploads.
        /// </summary>
        /// <param name="ctx">The CTX.</param>
        /// <returns></returns>
        bool removeUpload(EventsUploadContextPtr const& ctx);
        
        /// <summary>
        /// Cancel pending upload task and stop scheduling further uploads.
        /// </summary>
        void pauseAllUploads();

        std::chrono::milliseconds getCancelWaitTime() noexcept;

        /// <summary>
        /// Cancels pending upload task.
        /// </summary>
        bool cancelUploadTask();
        
        /// <summary>
        /// Calculate the number of pending upload contexts.
        /// </summary>
        /// <returns></returns>
        size_t uploadCount();

        int                              m_timerdelay;
        EventLatency                     m_runningLatency;
        TimerArray                       m_timers;

    public:
        RoutePassThrough<TransmissionPolicyManager>                          start{ this, &TransmissionPolicyManager::handleStart };
        RoutePassThrough<TransmissionPolicyManager>                          pause{ this, &TransmissionPolicyManager::handlePause };
        RoutePassThrough<TransmissionPolicyManager>                          stop{ this, &TransmissionPolicyManager::handleStop };
        RouteSink<TransmissionPolicyManager>                                 finishAllUploads{ this, &TransmissionPolicyManager::handleFinishAllUploads };
        RouteSource<>                                                        allUploadsFinished;

        RouteSink<TransmissionPolicyManager, IncomingEventContextPtr const&> eventArrived{ this, &TransmissionPolicyManager::handleEventArrived };

        RouteSource<EventsUploadContextPtr const&>                           initiateUpload;
        RouteSink<TransmissionPolicyManager, EventsUploadContextPtr const&>  nothingToUpload{ this, &TransmissionPolicyManager::handleNothingToUpload };
        RouteSink<TransmissionPolicyManager, EventsUploadContextPtr const&>  packagingFailed{ this, &TransmissionPolicyManager::handlePackagingFailed };
        RouteSink<TransmissionPolicyManager, EventsUploadContextPtr const&>  eventsUploadSuccessful{ this, &TransmissionPolicyManager::handleEventsUploadSuccessful };
        RouteSink<TransmissionPolicyManager, EventsUploadContextPtr const&>  eventsUploadRejected{ this, &TransmissionPolicyManager::handleEventsUploadRejected };
        RouteSink<TransmissionPolicyManager, EventsUploadContextPtr const&>  eventsUploadFailed{ this, &TransmissionPolicyManager::handleEventsUploadFailed };
        RouteSink<TransmissionPolicyManager, EventsUploadContextPtr const&>  eventsUploadAborted{ this, &TransmissionPolicyManager::handleEventsUploadAborted };

        virtual bool isUploadInProgress();

        virtual bool isPaused();
    };


} ARIASDK_NS_END

#endif // TRANSMISSIONPOLICYMANAGER_HPP