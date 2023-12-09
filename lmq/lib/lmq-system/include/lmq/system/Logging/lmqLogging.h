#pragma once

enum class ELogLevel
{
    Error = 0,
    Warning,
    Info,
    Debug
};

#define lmq_LOGGING_BUFFER_SIZE 256

#ifdef ARDUINO

#define lmq_PLATFORM_SUPPORT_LOGGING 1

class __FlashStringHelper;

void lmqLog(const ELogLevel logLevel, const __FlashStringHelper* ifsh);
void lmqLog(const ELogLevel logLevel, const char* str);
void lmqLogf(const ELogLevel logLevel, const char* format, ...);

#endif // ARDUINO

#ifdef lmq_PLATFORM_SUPPORT_LOGGING

#define lmq_LOG(logLvl, msg) lmqLog(logLvl, msg)
#define lmq_LOGF(logLvl, fmt, ...) lmqLogf(logLvl, fmt, __VA_ARGS__)

#else // lmq_PLATFORM_SUPPORT_LOGGING

#warning ("Warning: the platform does not support logging")

#define lmq_LOG(logLvl, msg)
#define lmq_LOGF(logLvl, fmt, ...)

#endif // !lmq_PLATFORM_SUPPORT_LOGGING

#define lmq_LOG_DEBUG(msg) lmq_LOG(ELogLevel::Debug, msg)
#define lmq_LOG_INFO(msg) lmq_LOG(ELogLevel::Info, msg)
#define lmq_LOG_WARNING(msg) lmq_LOG(ELogLevel::Warning, msg)
#define lmq_LOG_ERROR(msg) lmq_LOG(ELogLevel::Error, msg)

#define lmq_LOGF_DEBUG(fmt, ...) lmq_LOGF(ELogLevel::Debug, fmt, __VA_ARGS__)
#define lmq_LOGF_INFO(fmt, ...) lmq_LOGF(ELogLevel::Info, fmt, __VA_ARGS__)
#define lmq_LOGF_WARNING(fmt, ...) lmq_LOGF(ELogLevel::Warning, fmt, __VA_ARGS__)
#define lmq_LOGF_ERROR(fmt, ...) lmq_LOGF(ELogLevel::Error, fmt, __VA_ARGS__)