// Copyright (c) Microsoft. All rights reserved.
#ifndef ITELEMETRYSYSTEM_HPP
#define ITELEMETRYSYSTEM_HPP

#include "pal/PAL.hpp"

#include "bond/BondSerializer.hpp"

#include "ILogManager.hpp"

#include "api/IRuntimeConfig.hpp"

namespace ARIASDK_NS_BEGIN {

    class DebugEventDispatcher;
    
    /// <summary>
    /// Common interface of a telemetry system
    /// </summary>
    /// <seealso cref="DebugEventDispatcher" />
    class ITelemetrySystem : public DebugEventDispatcher
    {
    public:
        virtual ~ITelemetrySystem() {};

        // Transmission control
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual void pause() = 0;
        virtual void resume() = 0;
        virtual bool upload() = 0;

        // Access to common core components
        virtual ILogManager& getLogManager() = 0;
        virtual IRuntimeConfig& getConfig() = 0;
        virtual ISemanticContext& getContext() = 0;

        // Debug functionality
        virtual bool DispatchEvent(DebugEvent evt) override = 0;

        // Core sendEvent
        virtual void sendEvent(IncomingEventContextPtr const& event) = 0;

    protected:
        virtual void handleFlushWorkerThread() = 0;
        virtual void signalDone() = 0;
        virtual void handleIncomingEventPrepared(IncomingEventContextPtr const& event) = 0;
        virtual void preparedIncomingEventAsync(IncomingEventContextPtr const& event) = 0;

    };
    
} ARIASDK_NS_END

#endif