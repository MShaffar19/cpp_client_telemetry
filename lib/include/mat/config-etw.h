#define EVTSDK_VERSION_PREFIX "EVT"
#if defined(_WIN32) /* && defined(HAVE_PRIVATE_MODULES) */
#define HAVE_MAT_UTC
#define HAVE_MAT_ETW
#endif
#if defined(HAVE_PRIVATE_MODULES)
#define HAVE_MAT_EXP
#define HAVE_MAT_FIFOSTORAGE
//#define HAVE_MAT_DEFAULTDATAVIEWER
#endif
#define HAVE_MAT_JSONHPP
#ifndef ANDROID
#define HAVE_MAT_ZLIB
#endif
#define HAVE_MAT_LOGGING
#define HAVE_MAT_STORAGE
#define HAVE_MAT_DEFAULT_HTTP_CLIENT
//#define HAVE_MAT_DEFAULT_FILTER
#if defined(_WIN32) && !defined(_WINRT_DLL)
#define HAVE_MAT_NETDETECT
#endif