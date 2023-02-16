#pragma once
typedef enum _LogLevel
{
	LOG_ERROR = 0,
	LOG_INFO,
	LOG_WARN,
	LOG_DEBUG,
	LOG_NONE
}LogLevel_t;

#define LOG_DATA(iLvl, chLog); LOG(iLvl, chLog, __LINE__, __FILE__);

DWORD LOG(LogLevel_t iLevel, const char* buff, int iLineNo, const char* pchSrc);
DWORD SetModuleName(const char* pchModuleName);
LogLevel_t GetLogLevel(const char* pchModuleName); 
DWORD SetLogLevel(const char* pchModuleName, LogLevel_t level);