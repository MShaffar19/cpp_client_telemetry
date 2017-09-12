// Copyright (c) Microsoft. All rights reserved.

#pragma once
#include "Version.hpp"
#include "Enums.hpp"
#include "ILogger.hpp"
#include "ISemanticContext.hpp"
#include "api/LogConfiguration.hpp"
#include <string>

// *INDENT-OFF*
namespace Microsoft { namespace Applications { namespace Telemetry {
// *INDENT-ON*


/// <summary>
/// This class is used to manage the Telemetry logging system
/// </summary>
class ILogManager
{
  public:
    /// <summary>
    /// Initialize the telemetry logging system.
    /// </summary>
    /// <param name="configuration">Configuration settings to apply to the telemetry logging system</param>
    /// <returns>A telemetry logging system instance created with the specified configuration</returns>
    static ILogManager* Create(LogConfiguration& configuration, IRuntimeConfig* runtimeConfig);

    /// <summary>
    /// Destroy the telemetry logging system instance. Calls `FlushAndTeardown()` implicitly.
    /// </summary>
    virtual ~ILogManager() {}

    /// <summary>
    /// Flush any pending telemetry events in memory to disk and tear down the telemetry logging system.
    /// </summary>
    virtual void FlushAndTeardown() = 0;

    /// <summary>
    /// Flush any pending telemetry events in memory to disk to reduce possible data loss as seen necessary.
    /// This function can be very expensive so should be used sparingly. OS will block the calling thread
    /// and might flush the global file buffers, i.e. all buffered filesystem data, to disk, which could be
    /// time consuming.
    /// </summary>
    virtual void Flush() = 0;

	/// <summary>
	/// Try to send any pending telemetry events in memory or on disk.
	/// </summary>
	virtual void UploadNow() = 0;

    /// <summary>
    /// Pauses the transmission of events to data collector.
    /// While pasued events will continue to be queued up on client side in cache (either in memory or on disk file).
    /// </summary>
    virtual void PauseTransmission() = 0;

    /// <summary>
    /// Resumes the transmission of events to data collector.
    /// </summary>
    virtual void ResumeTransmission() = 0;

	/// <summary>
	/// Sets transmit profile for event transmission to one of the built-in profiles.
	/// A transmit profile is a collection of hardware and system settings (like network connectivity, power state)
	/// based on which to determine how events are to be transmitted. 
	/// </summary>
	/// <param name="profile">Transmit profile</param>
	/// <returns>This function doesn't return any value because it always succeeds.</returns>
	virtual void  SetTransmitProfile(TransmitProfile profile) = 0;

  	/// <summary>
	/// Sets transmit profile for event transmission.
	/// A transmit profile is a collection of hardware and system settings (like network connectivity, power state)
	/// based on which to determine how events are to be transmitted. 
	/// </summary>
	/// <param name="profile">Transmit profile</param>
	/// <returns>true if profile is successfully applied, false otherwise</returns>
	virtual bool  SetTransmitProfile(const std::string& profile)  = 0;

	/// <summary>
	/// Load transmit profiles from JSON config
	/// </summary>
	/// <param name="profiles_json">JSON config (see example above)</param>
	/// <returns>true on successful profiles load, false if config is invalid</returns>
	virtual bool  LoadTransmitProfiles(std::string profiles_json)  = 0;

	/// <summary>
	/// Reset transmission profiles to default settings
	/// </summary>
	virtual void  ResetTransmitProfiles() = 0;

	/// <summary>
	/// Reset transmission profiles to default settings
	/// </summary>
	virtual const std::string& GetTransmitProfileName() = 0;

    /// <summary>
    /// Retrieve an ISemanticContext interface through which to specify context information
    /// such as device, system, hardware and user information.
    /// Context information set via this API will apply to all logger instance unless they
    /// are overwritten by individual logger instance.
    /// </summary>
    /// <returns>ISemanticContext interface pointer</returns>
    virtual ISemanticContext& GetSemanticContext() = 0;

    /// <summary>
    /// Adds or  = 0s a property of the custom context for the telemetry logging system.
    /// Context information set here applies to events generated by all ILogger instances
    /// unless it is overwritten on a particular ILogger instance.
    /// </summary>
    /// <param name="name">Name of the context property</param>
    /// <param name="value">String value of the context property</param>
    /// <param name='piiKind'>PIIKind of the context with PiiKind_None as the default</param>
    virtual void SetContext(std::string const& name, std::string const& value, PiiKind piiKind = PiiKind_None) = 0;

	/// <summary>
	/// Adds or  = 0s a property of the custom context for the telemetry logging system.
	/// Context information set here applies to events generated by all ILogger instances 
	/// unless it is overwritten on a particular ILogger instance.
	/// </summary>
	/// <param name="name">Name of the context property</param>
	/// <param name="value">Value of the context property</param>
	/// <param name='piiKind'>PIIKind of the context with PiiKind_None as the default</param>
	virtual void SetContext(const std::string& name, const char *value, PiiKind piiKind = PiiKind_None) = 0;

    /// <summary>
    /// Adds or overrides a property of the custom context for the telemetry logging system.
    /// Context information set here applies to events generated by all ILogger instances
    /// unless it is overwritten on a particular ILogger instance.
    /// </summary>
    /// <param name="name">Name of the context property</param>
    /// <param name="value">Value of the context property</param>
    /// <param name='ccKind'>Customer content kind</param>
    virtual void SetContext(const std::string& name, const std::string& value, CustomerContentKind ccKind) = 0;

    /// <summary>
    /// Adds or overrides a property of the custom context for the telemetry logging system.
    /// Context information set here applies to events generated by all ILogger instances
    /// unless it is overwritten on a particular ILogger instance.
    /// </summary>
    /// <param name="name">Name of the context property</param>
    /// <param name="value">Value of the context property</param>
    /// <param name='ccKind'>Customer content kind</param>
    virtual void SetContext(const std::string& name, const char *value, CustomerContentKind ccKind) = 0;

	/// <summary>
	/// Adds or  = 0s a property of the global context.
	/// </summary>
	/// <param name="name">Name of the property</param>
	/// <param name="value">Double value of the property</param>
	virtual void  SetContext(const std::string& name, double value, PiiKind piiKind = PiiKind_None)  = 0;

	/// <summary>
	/// Adds or  = 0s a property of the global context.
	/// </summary>
	/// <param name="name">Name of the property</param>
	/// <param name="value">64-bit Integer value of the property</param>
	virtual void  SetContext(const std::string& name, int64_t value, PiiKind piiKind = PiiKind_None) = 0;;

	/// <summary>
	/// Adds or  = 0s a property of the global context.<br>
	/// All integer types other than int64_t are currently being converted to int64_t
	/// </summary>
	/// <param name="name">Name of the property</param>
	/// <param name="value">8-bit Integer value of the property</param>
	virtual void SetContext(const std::string& name, int8_t  value, PiiKind piiKind = PiiKind_None) = 0;

	/// <summary>
	/// Adds or  = 0s a property of the global context.<br>
	/// All integer types other than int64_t are currently being converted to int64_t
	/// </summary>
	/// <param name="name">Name of the property</param>
	/// <param name="value">16-bit Integer value of the property</param>
	virtual void SetContext(const std::string& name, int16_t value, PiiKind piiKind = PiiKind_None) = 0;

	/// <summary>
	/// Adds or  = 0s a property of the global context.<br>
	/// All integer types other than int64_t are currently being converted to int64_t
	/// </summary>
	/// <param name="name">Name of the property</param>
	/// <param name="value">32-bit Integer value of the property</param>
	virtual  void SetContext(const std::string& name, int32_t value, PiiKind piiKind = PiiKind_None) = 0;

	/// <summary>
	/// Adds or  = 0s a property of the global context.<br>
	/// All integer types other than int64_t are currently being converted to int64_t
	/// </summary>
	/// <param name="name">Name of the property</param>
	/// <param name="value">8-bit unsigned integer value of the property</param>
	virtual  void SetContext(const std::string& name, uint8_t  value, PiiKind piiKind = PiiKind_None) = 0;

	/// <summary>
	/// Adds or  = 0s a property of the global context.<br>
	/// All integer types other than int64_t are currently being converted to int64_t
	/// </summary>
	/// <param name="name">Name of the property</param>
	/// <param name="value">16-bit unsigned integer value of the property</param>
	virtual  void SetContext(const std::string& name, uint16_t value, PiiKind piiKind = PiiKind_None) = 0;

	/// <summary>
	/// Adds or  = 0s a property of the global context.<br>
	/// All integer types other than int64_t are currently being converted to int64_t
	/// </summary>
	/// <param name="name">Name of the property</param>
	/// <param name="value">32-bit unsigned integer value of the property</param>
	virtual  void SetContext(const std::string& name, uint32_t value, PiiKind piiKind = PiiKind_None) = 0;

	/// <summary>
	/// Adds or  = 0s a property of the global context.<br>
	/// All integer types other than int64_t are currently being converted to int64_t
	/// </summary>
	/// <param name="name">Name of the property</param>
	/// <param name="value">64-bit unsigned integer value of the property</param>
	virtual  void SetContext(const std::string& name, uint64_t value, PiiKind piiKind = PiiKind_None) = 0;

	/// <summary>
	/// Adds or  = 0s a property of the global context.
	/// </summary>
	/// <param name="name">Name of the property</param>
	/// <param name="value">Boolean value of the property</param>
	virtual void  SetContext(const std::string& name, bool value, PiiKind piiKind = PiiKind_None) = 0;

	/// <summary>
	/// Adds or  = 0s a property of the global context.
	/// </summary>
	/// <param name="name">Name of the property</param>
	/// <param name="value">.NET time ticks</param>
	virtual void  SetContext(const std::string& name, time_ticks_t value, PiiKind piiKind = PiiKind_None) = 0;

	/// <summary>
	/// Adds or overrides a property of the global context.
	/// </summary>
	/// <param name="name">Name of the property</param>
	/// <param name="value">GUID</param>
	virtual void  SetContext(const std::string& name, GUID_t value, PiiKind piiKind = PiiKind_None) = 0;

    /// <summary>
    /// Retrieves the ILogger interface of a Logger instance through which to log telemetry events.
    /// Also associates it with the specified experimentation project (e.g. ECS) for retrieving configuration context info.
    /// </summary>
    /// <param name="tenantToken">Token of the tenant with which the application is associated for collecting telemetry</param>
    /// <param name="source">Source name of events sent by this logger instance</param>
    /// <param name="experimentationProject">Project name of experimentation configurations whose config IDs will be associated with all events sent by this ILogger</param>
    /// <returns>Pointer to the ILogger interface of the logger instance</returns>
    virtual ILogger* GetLogger(std::string const& tenantToken, std::string const& source = std::string(), std::string const& experimentationProject = std::string()) = 0;
};


}}} // namespace Microsoft::Applications::Telemetry
