#pragma once

#include "stdafx.h"
#include "LogMan.h"

#define TIMEOUT 1000

#define LOGMAN_PIPE 	"\\\\.\\pipe\\ITAS_Logger"
#define LOGMAN_REG_KEY	"SOFTWARE\\XFS\\LogManager"

#define LOGBUFFER_SIZE			1024
#define MODULE_NAME_SIZE		64
#define PIPE_MAX_SIZE			LOGBUFFER_SIZE
#define PIPE_OUT_BUFFER_SIZE    PIPE_MAX_SIZE
#define PIPE_IN_BUFFER_SIZE     PIPE_MAX_SIZE
#define PIPE_DEFAULT_TIMEOUT    10000
#define PIPE_BUFFER_SIZE        PIPE_MAX_SIZE
#define PIPE_NAME_SIZE          256

HANDLE	g_hLogManPipe = INVALID_HANDLE_VALUE;

TCHAR	g_chModule[MODULE_NAME_SIZE] = { 0 };
LogLevel_t	g_dwLogLevel = LogLevel_t::LOG_NONE;


DWORD LOG(LogLevel_t iLevel, const char *buff, int iLineNo, const char* pchSrc)
{
	TCHAR chTrcBuffer[LOGBUFFER_SIZE] = { 0 };
	TCHAR chTime[64] = { 0 };
	DWORD dwErr = 0;
	SYSTEMTIME SysTime;
	GetLocalTime(&SysTime);
	sprintf_s(chTime, "%0.2d-%0.2d-%0.4d %0.2d:%0.2d:%0.2d:%0.3d", SysTime.wDay, SysTime.wMonth, SysTime.wYear, SysTime.wHour, SysTime.wMinute, SysTime.wSecond, SysTime.wMilliseconds);
	
	if (buff && pchSrc)
	{
		// Skip full path - Only print the file name with containing folder name
		const char* pchCurr = strstr(pchSrc, "\\");
		const char* pchPrev = NULL;
		while (pchCurr != NULL)
		{
			pchPrev = pchCurr + 1;
			pchCurr = strstr(pchPrev, "\\");
			if(pchCurr != NULL)
				pchCurr = strstr((pchCurr + 1), "\\");
		}
	
		sprintf_s(chTrcBuffer, "%s %s %s %d # %s", chTime, g_chModule, pchPrev, iLineNo, buff);
		DWORD dwBytesWritten = 0;
		BOOL bWriteResult = FALSE;

		if (g_hLogManPipe == INVALID_HANDLE_VALUE)
		{
			SECURITY_DESCRIPTOR sdSecDesc;
			SECURITY_ATTRIBUTES saSecuAttrib;

			if (InitializeSecurityDescriptor(&sdSecDesc, SECURITY_DESCRIPTOR_REVISION))
				SetSecurityDescriptorDacl(&sdSecDesc, TRUE, (PACL)NULL, FALSE);

			saSecuAttrib.nLength = sizeof(SECURITY_ATTRIBUTES);
			saSecuAttrib.bInheritHandle = TRUE;
			saSecuAttrib.lpSecurityDescriptor = &sdSecDesc;

			g_hLogManPipe = CreateFileA(LOGMAN_PIPE, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);

			dwErr = GetLastError();
			SetLastError(NULL);
		}
		if (g_hLogManPipe != INVALID_HANDLE_VALUE)
		{
			if (iLevel <= g_dwLogLevel && g_dwLogLevel != LOG_NONE)
			{
				bWriteResult = WriteFile(g_hLogManPipe, chTrcBuffer, sizeof(chTrcBuffer), &dwBytesWritten, NULL);
				dwErr = GetLastError();
				SetLastError(NULL);
			}
		}
		if (dwErr == ERROR_BROKEN_PIPE)
		{
			CloseHandle(g_hLogManPipe);
			g_hLogManPipe = INVALID_HANDLE_VALUE;
		}
	}
	return ERROR_SUCCESS;
}

DWORD SetModuleName(const char *pchModuleName)
{
	if (strlen(g_chModule) == 0)
	{
		strcpy_s(g_chModule, strlen(pchModuleName)+1, pchModuleName);
		g_dwLogLevel = GetLogLevel(pchModuleName);
	}
	return ERROR_SUCCESS;
}

LogLevel_t GetLogLevel(const char *pchModuleName)
{
	HKEY hTrcKey = NULL;
	HKEY hSubKey = NULL;
	CHAR chData[512] = { 0 };
	DWORD dwNumOfBytesRead = sizeof(chData);
	LogLevel_t iLvl = LOG_NONE;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, LOGMAN_REG_KEY, 0, KEY_READ, &hTrcKey) == ERROR_SUCCESS)
	{
		if (RegQueryValueEx(hTrcKey, pchModuleName, 0, 0, (BYTE*)chData, &dwNumOfBytesRead) == ERROR_SUCCESS)
		{
			iLvl = (LogLevel_t) atoi(chData);
		}
	}
	return iLvl;
}

DWORD SetLogLevel(const char* pchModuleName, LogLevel_t level)
{
	HKEY hTrcKey = NULL;
	HKEY hSubKey = NULL;
	CHAR chData[32] = { 0 };

	g_dwLogLevel = level;
	sprintf_s(chData, 32, "%d", g_dwLogLevel);
	DWORD dwNumOfBytesWrite = strnlen(chData, 32);

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, LOGMAN_REG_KEY, 0, KEY_READ, &hTrcKey) == ERROR_SUCCESS)
	{
		if (RegSetValueEx(hTrcKey, pchModuleName, 0, 0, (BYTE*)chData, dwNumOfBytesWrite) != ERROR_SUCCESS)
		{
			return GetLastError();
		}
	}
	return ERROR_SUCCESS;
}