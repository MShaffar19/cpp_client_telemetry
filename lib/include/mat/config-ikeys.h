/*
 * Copyright 2019 (c) Microsoft. All rights reserved.
 *
 * Default ingestion keys for anonymous SDK usage statistics.
 */
#ifndef CONFIG_IKEYS_H
#define CONFIG_IKEYS_H
#if defined(__linux__) || defined(__gnu_linux__)
#define STATS_TOKEN_PROD "99999999999999999999999999999999-99999999-9999-9999-9999-999999999999-9999"
#else
#define STATS_TOKEN_PROD "99999999999999999999999999999999-99999999-9999-9999-9999-999999999999-9999"
#endif
#define STATS_TOKEN_INT  "99999999999999999999999999999999-99999999-9999-9999-9999-999999999999-9999"
#endif