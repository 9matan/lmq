#pragma once

#ifdef ARDUINO

#define lmq_LOG_DEBUG(msg) lmqLogDebug(msg);
#define lmq_LOG_INFO(msg) lmqLogInfo(msg);
#define lmq_LOG_WARNING(msg) lmqLogWarning(msg);
#define lmq_LOG_ERROR(msg) lmqLogError(msg);

class __FlashStringHelper;

void lmqLogDebug(const __FlashStringHelper* ifsh);
void lmqLogInfo(const __FlashStringHelper* ifsh);
void lmqLogWarning(const __FlashStringHelper* ifsh);
void lmqLogError(const __FlashStringHelper* ifsh);

void lmqLogDebug(const char* str);
void lmqLogInfo(const char* str);
void lmqLogWarning(const char* str);
void lmqLogError(const char* str);

#else // ARDUINO

#define lmq_LOG_DEBUG(msg)
#define lmq_LOG_INFO(msg);
#define lmq_LOG_WARNING(msg)
#define lmq_LOG_ERROR(msg)

#endif