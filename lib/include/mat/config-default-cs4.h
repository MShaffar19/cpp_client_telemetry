//
// Copyright (c) 2015-2020 Microsoft Corporation and Contributors.
// SPDX-License-Identifier: Apache-2.0
//
#define EVTSDK_VERSION_PREFIX "EVT"
#if defined(_WIN32) /* && defined(HAVE_PRIVATE_MODULES) */
#define HAVE_MAT_UTC
#endif
#if defined(HAVE_PRIVATE_MODULES)
#define HAVE_MAT_EXP
#define HAVE_MAT_FIFOSTORAGE
//#define HAVE_MAT_DEFAULTDATAVIEWER
#endif
#define HAVE_MAT_JSONHPP
#define HAVE_MAT_ZLIB
#define HAVE_MAT_LOGGING
#define HAVE_MAT_STORAGE
#define HAVE_MAT_DEFAULT_HTTP_CLIENT
//#define HAVE_MAT_DEFAULT_FILTER
#if defined(_WIN32) && !defined(_WINRT_DLL)
#define HAVE_MAT_NETDETECT
#endif
//#define HAVE_CS3
#define HAVE_CS4
#define HAVE_CS4_FULL

