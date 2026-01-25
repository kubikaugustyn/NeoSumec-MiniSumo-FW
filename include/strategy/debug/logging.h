//
// Created by Jakub Augustýn on 25.01.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#pragma once
#include <Arduino.h> // To include Serial

#define LOGGING_DISABLED 0
#define LOG_ERROR 1
#define LOG_INFO 2
#define LOG_DEBUG 3

// Helper: adds a newline to the string
#define LOG_EOL(fmt) fmt "\n"

// Separate macros, removes unnecessary logs at compile time
#if LOG_LEVEL >= LOG_DEBUG
#define LOG_DEBUG_PRINTF(fmt, ...) Serial.printf(LOG_EOL(fmt), ##__VA_ARGS__)
#else
#define LOG_DEBUG_PRINTF(fmt, ...)
#endif

#if LOG_LEVEL >= LOG_INFO
#define LOG_INFO_PRINTF(fmt, ...) Serial.printf(LOG_EOL(fmt), ##__VA_ARGS__)
#else
#define LOG_INFO_PRINTF(fmt, ...)
#endif

#if LOG_LEVEL >= LOG_ERROR
#define LOG_ERROR_PRINTF(fmt, ...) Serial.printf(LOG_EOL(fmt), ##__VA_ARGS__)
#else
#define LOG_ERROR_PRINTF(fmt, ...)
#endif
