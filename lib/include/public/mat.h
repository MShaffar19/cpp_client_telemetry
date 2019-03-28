/* Copyright (c) Microsoft. All rights reserved. */
#ifndef TELEMETRY_EVENTS_H
#define TELEMETRY_EVENTS_H

/* API semver $MAJOR.$MINOR.$PATCH must be updated with every $MAJOR or $MINOR change.
 * For version handshake check there is no mandatory requirement to update the $PATCH level.
 * Ref. https://semver.org/ for Semantic Versioning documentation.
 */
#define TELEMETRY_EVENTS_VERSION	"3.1.0"

#include <ctmacros.hpp>

#ifdef _WIN32
#include <Windows.h>
#endif

#if (_MSC_VER == 1500) || (_MSC_VER == 1600)
/* Visual Studio 2010 */
typedef	__int64				int64_t;
typedef unsigned __int64	uint64_t;
typedef	__int32				int32_t;
typedef unsigned __int32	uint32_t;
typedef	__int16				int16_t;
typedef unsigned __int16	uint16_t;
typedef	__int8				int8_t;
typedef unsigned __int8	    uint8_t;
typedef int                 bool;
#define inline
#else
/* Other compilers with C11 support */
#include <inttypes.h>
#include <stdbool.h>
#endif

#ifndef EVT_ARRAY_SIZE
#define EVT_ARRAY_SIZE(a)                               \
  ((sizeof(a) / sizeof(*(a))) /                     \
  (unsigned)(!(sizeof(a) % sizeof(*(a)))))
#endif

#ifdef __cplusplus
extern "C" {
#endif

    typedef enum
    {
        EVT_OP_LOAD = 0x00000001,
        EVT_OP_UNLOAD = 0x00000002,
        EVT_OP_OPEN = 0x00000003,
        EVT_OP_CLOSE = 0x00000004,
        EVT_OP_CONFIG = 0x00000005,
        EVT_OP_LOG = 0x00000006,
        EVT_OP_PAUSE = 0x00000007,
        EVT_OP_RESUME = 0x00000008,
        EVT_OP_UPLOAD = 0x00000009,
        EVT_OP_FLUSH = 0x0000000A,
        EVT_OP_VERSION = 0x0000000B,
        EVT_OP_MAX = EVT_OP_VERSION + 1
    } evt_call_t;

    typedef enum
    {
        /* Basic types */
        TYPE_STRING,
        TYPE_INT64,
        TYPE_DOUBLE,
        TYPE_TIME,
        TYPE_BOOLEAN,
        TYPE_GUID,
        /* Arrays of basic types */
        TYPE_STRING_ARRAY,
        TYPE_INT64_ARRAY,
        TYPE_DOUBLE_ARRAY,
        TYPE_TIME_ARRAY,
        TYPE_BOOL_ARRAY,
        TYPE_GUID_ARRAY,
        /* NULL-type */
        TYPE_NULL
    } evt_prop_t;

    typedef struct
    {
        /**
         * <summary>
         * Specifies the first eight hexadecimal digits of the GUID.
         * </summary>
         */
        uint32_t Data1;

        /* <summary>
         * Specifies the first group of four hexadecimal digits.
         * </summary>
         */
        uint16_t Data2;

        /**
         * <summary>
         * Specifies the second group of four hexadecimal digits.
         * </summary>
         */
        uint16_t Data3;

        /** <summary>
         * An array of eight bytes.
         * The first two bytes contain the third group of four hexadecimal digits.
         * The remaining six bytes contain the final 12 hexadecimal digits.
         * </summary>
         */
        uint8_t  Data4[8];
    } evt_guid_t;

    typedef int64_t  evt_handle_t;
    typedef int32_t  evt_status_t;
    typedef struct   evt_event evt_event;

    typedef struct
    {
        evt_call_t      call;       /* In       */
        evt_handle_t    handle;     /* In / Out */
        void*           data;       /* In / Out */
        evt_status_t    result;     /* Out      */
        uint32_t        size;       /* In / Out */
    } evt_context_t;

    typedef struct
    {
        const char*             name;
        evt_prop_t              type;
        union
        {
            /* Basic types */
            const char*         as_string;
            int64_t             as_int64;
            double              as_double;
            bool                as_bool;
            evt_guid_t*         as_guid;
            uint64_t            as_time;
            /* Array types are nullptr-terminated array of pointers */
            char**              as_arr_string;
            int64_t**           as_arr_int64;
            bool**              as_arr_bool;
            double**            as_arr_double;
            evt_guid_t**        as_arr_guid;
            uint64_t**          as_arr_time;
        } value;
        uint32_t                piiKind;
    } evt_prop;

#if (_MSC_VER == 1500) || (_MSC_VER == 1600)
    /* Code to support C89 compiler, including VS2010 */
#define TELEMETRY_EVENT(...)    { __VA_ARGS__ , { NULL, TYPE_NULL } }
/* With C89-style initializers, structure members must be initialized in the order declared.
   ...and (!) - only the first member of a union can be initialized.
   Which means that we have to do the hack of C-style casting from value to char* ...
 */
#define _STR(key, val)           { key, TYPE_STRING,    { (char *)val } }
#define _INT(key, val)           { key, TYPE_INT64,     { (char *)val } }
#define _DBL(key, val)           { key, TYPE_DOUBLE,    { (char *)val } }
#define _BOOL(key, val)          { key, TYPE_BOOLEAN,   { (char *)val } }
#define _GUID(key, val)          { key, TYPE_GUID,      { (char *)val } }
#define _TIME(key, val)          { key, TYPE_TIME,      { (char *)val } }

#define PII_STR(key, val, kind)  { key, TYPE_STRING,    { (char *)val }, kind }
#define PII_INT(key, val, kind)  { key, TYPE_INT64,     { (char *)val }, kind }
#define PII_DBL(key, val, kind)  { key, TYPE_DOUBLE,    { (char *)val }, kind }
#define PII_BOOL(key, val, kind) { key, TYPE_BOOLEAN,   { (char *)val }, kind }
#define PII_GUID(key, val, kind) { key, TYPE_GUID,      { (char *)val }, kind }
#define PII_TIME(key, val, kind) { key, TYPE_TIME,      { (char *)val }, kind }

#else
    /* Code to support any modern C99 compiler */
#define TELEMETRY_EVENT(...)    { __VA_ARGS__ , { .name = NULL, .type = TYPE_NULL } }

#define _STR(key, val)           { .name = key, .type = TYPE_STRING,  .value = { .as_string = val }, .piiKind = 0 }
#define _INT(key, val)           { .name = key, .type = TYPE_INT64,   .value = { .as_int64  = val }, .piiKind = 0 }
#define _DBL(key, val)           { .name = key, .type = TYPE_DOUBLE,  .value = { .as_double = val }, .piiKind = 0 }
#define _BOOL(key, val)          { .name = key, .type = TYPE_BOOLEAN, .value = { .as_bool   = val }, .piiKind = 0 }
#define _GUID(key, val)          { .name = key, .type = TYPE_GUID,    .value = { .as_guid   = val }, .piiKind = 0 }
#define _TIME(key, val)          { .name = key, .type = TYPE_TIME,    .value = { .as_time   = val }, .piiKind = 0 }

#define PII_STR(key,  val, kind) { .name = key, .type = TYPE_STRING,  .value = { .as_string = val }, .piiKind = kind }
#define PII_INT(key,  val, kind) { .name = key, .type = TYPE_INT64,   .value = { .as_int64  = val }, .piiKind = kind }
#define PII_DBL(key,  val, kind) { .name = key, .type = TYPE_DOUBLE,  .value = { .as_double = val }, .piiKind = kind }
#define PII_BOOL(key, val, kind) { .name = key, .type = TYPE_BOOLEAN, .value = { .as_bool   = val }, .piiKind = kind }
#define PII_GUID(key, val, kind) { .name = key, .type = TYPE_GUID,    .value = { .as_guid   = val }, .piiKind = kind }
#define PII_TIME(key, val, kind) { .name = key, .type = TYPE_TIME,    .value = { .as_time   = val }, .piiKind = kind }

#endif

    typedef evt_status_t(EVTSDK_LIBABI_CDECL *evt_app_call_t)(evt_context_t *);

    EVTSDK_LIBABI evt_status_t EVTSDK_LIBABI_CDECL evt_api_call_default(evt_context_t *ctx);

#ifdef _MSC_VER
    /* User of the library may delay-load the invocation of __impl_evt_api_call to assign their own implementation */
    __declspec(selectany) evt_app_call_t evt_api_call = evt_api_call_default;
#else
    /* Implementation of evt_api_call can be provided by the executable module that includes this header */
    __attribute__((weak)) evt_app_call_t evt_api_call = evt_api_call_default;
#endif

    /**
     * <summary>
     * Load alternate implementation of SDK Client Telemetry library at runtime.
     * </summary>
     * <param name="handle">Library handle.</param>
     * <returns>Status code.</returns>
     */
    static inline evt_status_t evt_load(evt_handle_t handle)
    {
#ifdef _WIN32
        /* This code accepts a handle of a library loaded in customer's code */
        evt_app_call_t impl = (evt_app_call_t)GetProcAddress((HMODULE)handle, "evt_api_call_default");
        if (impl != NULL)
        {
            evt_api_call = impl;
            return 0;
        }
        // Unable to load alternate implementation
        return -1;
#else
        /* TODO:
         * - provide implementation for Linux and Mac
         * - consider accepting a library path rather than a library handle for dlopen
         */
        evt_context_t ctx;
        ctx.call = EVT_OP_LOAD;
        ctx.handle = handle;
        return evt_api_call(&ctx);
#endif
    }
    
    /**
     * <summary>
     * Unloads SDK instance loaded with evt_load
     * </summary>
     * <param name="handle">SDK instance handle.</param>
     * <returns>
     * Status code.
     * </returns>
     */
    static inline evt_status_t evt_unload(evt_handle_t handle)
    {
        evt_context_t ctx;
        ctx.call = EVT_OP_UNLOAD;
        ctx.handle = handle;
        return evt_api_call(&ctx);
    }
        
    /**
     * <summary>
     * Create or open existing SDK instance.
     * </summary>
     * <param name="config">SDK configuration.</param>
     * <returns>SDK instance handle.</returns>
     */
    static inline evt_handle_t evt_open(const char* config)
    {
        evt_context_t ctx;
        ctx.call = EVT_OP_OPEN;
        ctx.data = (void *)config;
        evt_api_call(&ctx);
        return ctx.handle;
    }
    
    /**
     * <summary>
     * Destroy or close SDK instance by handle
     * </summary>
     * <param name="handle">SDK instance handle.</param>
     * <returns>Status code.</returns>
     */
    static inline evt_status_t evt_close(evt_handle_t handle)
    {
        evt_context_t ctx;
        ctx.call = EVT_OP_CLOSE;
        ctx.handle = handle;
        return evt_api_call(&ctx);
    }
    
    /**
     * <summary>
     * Configure SDK instance using configuration provided.
     * </summary>
     * <param name="handle">SDK handle.</param>
     * <param name="config">The configuration.</param>
     * <returns></returns>
     */
    static inline evt_status_t evt_configure(evt_handle_t handle, const char* config)
    {
        evt_context_t ctx;
        ctx.call = EVT_OP_CONFIG;
        ctx.handle = handle;
        ctx.data = (void *)config;
        return evt_api_call(&ctx);
    }
    
    /** 
     * <summary>
     * Logs a telemetry event (security-enhanced _s function)
     * </summary>
     * <param name="handle">SDK handle.</param>
     * <param name="size">Number of event properties in array.</param>
     * <param name="evt">Event properties array.</param>
     * <returns></returns>
     */
    static inline evt_status_t evt_log_s(evt_handle_t handle, uint32_t size, evt_prop* evt)
    {
        evt_context_t ctx;
        ctx.call = EVT_OP_LOG;
        ctx.handle = handle;
        ctx.data = (void *)evt;
        ctx.size = size;
        return evt_api_call(&ctx);
    }

    /**
     * <summary>
     * Logs a telemetry event.
     * Last item in evt_prop array must be { .name = NULL, .type = TYPE_NULL }
     * </summary>
     * <param name="handle">SDK handle.</param>
     * <param name="size">Number of event properties in array.</param>
     * <param name="evt">Event properties array.</param>
     * <returns></returns>
     */
    static inline evt_status_t evt_log(evt_handle_t handle, evt_prop* evt)
    {
        evt_context_t ctx;
        ctx.call = EVT_OP_LOG;
        ctx.handle = handle;
        ctx.data = (void *)evt;
        ctx.size = 0;
        return evt_api_call(&ctx);
    }

    /* This macro automagically calculates the array size and passes it down to evt_log_s.
     * Developers don't have to calculate the number of event properties passed down to
     *'Log Event' API call utilizing the concept of Secure Template Overloads:
     * https://docs.microsoft.com/en-us/cpp/c-runtime-library/secure-template-overloads
     */
#if defined(_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES) || defined(_CRT_SECURE_LOG_S)
#if _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES || defined(_CRT_SECURE_LOG_S)
#define evt_log(handle, evt) evt_log_s(handle, EVT_ARRAY_SIZE(evt), evt)
#endif
#endif
    
    /**
     * <summary>
     * Pauses transmission. In that mode events stay in ram or saved to disk, not sent.
     * </summary>
     * <param name="handle">SDK handle.</param>
     * <returns>Status code.</returns>
     */
    static inline evt_status_t evt_pause(evt_handle_t handle)
    {
        evt_context_t ctx;
        ctx.call = EVT_OP_PAUSE;
        ctx.handle = handle;
        return evt_api_call(&ctx);
    }
    
    /**
     * <summary>
     * Resumes transmission. Pending telemetry events should be attempted to be sent.
     * </summary>
     * <param name="handle">SDK handle.</param>
     * <returns>Status code.</returns>
     */
    static inline evt_status_t evt_resume(evt_handle_t handle)
    {
        evt_context_t ctx;
        ctx.call = EVT_OP_RESUME;
        ctx.handle = handle;
        return evt_api_call(&ctx);
    }
    
    /** <summary>
     * Provide a hint to telemetry system to attempt force-upload of events
     * without waiting for the next batch timer interval. This API does not
     * guarantee the upload.
     * </summary>
     * <param name="handle">SDK handle.</param>
     * <returns>Status code.</returns>
     */
    static inline evt_status_t evt_upload(evt_handle_t handle)
    {
        evt_context_t ctx;
        ctx.call = EVT_OP_UPLOAD;
        ctx.handle = handle;
        return evt_api_call(&ctx);
    }
    
    /** <summary>
     * Save pending telemetry events to offline storage on disk.
     * </summary>
     * <param name="handle">SDK handle.</param>
     * <returns>Status code.</returns>
     */
    static inline evt_status_t evt_flush(evt_handle_t handle)
    {
        evt_context_t ctx;
        ctx.call = EVT_OP_FLUSH;
        ctx.handle = handle;
        return evt_api_call(&ctx);
    }
    
    /** <summary>
     * Pass down SDK header version to SDK library. Needed for late binding version checking.
     * This method provides means of a handshake between library header and a library impl.
     * It is up to app dev to verify the value returned, making a decision whether some SDK
     * features are implemented/supported by particular SDK version or not.
     * </summary>
     * <param name="libSemver">SDK header semver.</param>
     * <returns>SDK library semver</returns>
     */
    static inline const char * evt_version()
    {
        static const char * libSemver = TELEMETRY_EVENTS_VERSION;
        evt_context_t ctx;
        ctx.call = EVT_OP_VERSION;
        ctx.data = (void*)libSemver;
        evt_api_call(&ctx);
        return (const char *)(ctx.data);
    }

    /* New API calls to be added using evt_api_call(&ctx) for backwards-forward / ABI compat */

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include "CAPIClient.hpp"
#endif

#endif
