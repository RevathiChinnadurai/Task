#include "stdafx.h"
#include "XFSManagerWrapper.h"
#include "Definitions.h"
#include "Helper.h"
#include "XFSCONF.H"

pfnWFMAllocateBuffer		fnWFMAllocateBuffer = NULL;
pfnWFMAllocateMore			fnWFMAllocateMore = NULL;
pfnWFMFreeBuffer			fnWFMFreeBuffer = NULL;
pfnWFMGetTraceLevel			fnWFMGetTraceLevel = NULL;
pfnWFMKillTimer				fnWFMKillTimer = NULL;
//WFMMakeResult
pfnWFMOutputTraceData		fnWFMOutputTraceData = NULL;
pfnWFMReleaseDLL			fnWFMReleaseDLL = NULL;
pfnWFMSetTimer				fnWFMSetTimer = NULL;
pfnWFMSetTraceLevel			fnWFMSetTraceLevel = NULL;

pfnWFSAsyncClose			fnWFSAsyncClose = NULL;
pfnWFSAsyncDeregister		fnWFSAsyncDeregister = NULL;
pfnWFSAsyncExecute			fnWFSAsyncExecute = NULL;
pfnWFSAsyncGetInfo			fnWFSAsyncGetInfo = NULL;
pfnWFSAsyncLock				fnWFSAsyncLock = NULL;
pfnWFSAsyncOpen				fnWFSAsyncOpen = NULL;
pfnWFSAsyncRegister			fnWFSAsyncRegister = NULL;
pfnWFSAsyncUnlock			fnWFSAsyncUnlock = NULL;
pfnWFSCancelAsyncRequest	fnWFSCancelAsyncRequest = NULL;
pfnWFSCancelBlockingCall	fnWFSCancelBlockingCall = NULL;
pfnWFSCleanUp				fnWFSCleanUp = NULL;
pfnWFSClose					fnWFSClose = NULL;
pfnWFSCreateAppHandle		fnWFSCreateAppHandle = NULL;
pfnWFSDeregister			fnWFSDeregister = NULL;
pfnWFSDestroyAppHandle		fnWFSDestroyAppHandle = NULL;
pfnWFSExecute				fnWFSExecute = NULL;
pfnWFSFreeResult			fnWFSFreeResult = NULL;
pfnWFSGetInfo				fnWFSGetInfo = NULL;
//WFSGetSCode
pfnWFSIsBlocking			fnWFSIsBlocking = NULL;
pfnWFSLock					fnWFSLock = NULL;
pfnWFSOpen					fnWFSOpen = NULL;
pfnWFSRegister				fnWFSRegister = NULL;
pfnWFSSetBlockingHook		fnWFSSetBlockingHook = NULL;
pfnWFSStartUp				fnWFSStartUp = NULL;
pfnWFSUnhookBlockingHook	fnWFSUnhookBlockingHook = NULL;
pfnWFSUnlock				fnWFSUnlock = NULL;


pfnWFMCloseKey				fnWFMCloseKey = NULL;
pfnWFMCreateKey				fnWFMCreateKey = NULL;
pfnWFMDeleteKey				fnWFMDeleteKey = NULL;
pfnWFMDeleteValue			fnWFMDeleteValue = NULL;
pfnWFMEnumKey				fnWFMEnumKey = NULL;
pfnWFMEnumValue				fnWFMEnumValue = NULL;
pfnWFMOpenKey				fnWFMOpenKey = NULL;
pfnWFMQueryValue			fnWFMQueryValue = NULL;
pfnWFMSetValue				fnWFMSetValue = NULL;





XFSManagerWrapper* XFSManagerWrapper::singleObj = NULL;
int XFSManagerWrapper::m_nCounter = 0;

CCriticalSection g_CriticalSection;


XFSManagerWrapper* XFSManagerWrapper::GetInstance()
{
	{
		CAutoLock lock(&g_CriticalSection);
		if (singleObj == NULL)
		{
			singleObj = new XFSManagerWrapper();
			if (!singleObj->Initialise())
			{
				singleObj->Release();
				singleObj = NULL;
			}
		}
	}
	++m_nCounter;
	return singleObj;
}

CStringA XFSManagerWrapper::FindXFSManagerPath()
{
	DWORD dwResult = 0;

#ifdef _V2_
	HKEY hKeyXFS_ROOT;
	HRESULT hr = WFMOpenKey(HKEY_CLASSES_ROOT, //WOSA/XFS_ROOT/LOGICAL_SERVICES,
		"WOSA/XFS_ROOT", //lpszSubKey, 
		&hKeyXFS_ROOT); //phkResult, lpdwDisposition )
	if (hr != WFS_SUCCESS) return -1;

	HKEY hKeyXFSManager;
	hr = WFMOpenKey(hKeyXFS_ROOT, //WOSA/XFS_ROOT/LOGICAL_SERVICES,
		"XFS_MANAGER", //lpszSubKey, 
		&hKeyXFSManager); //phkResult, lpdwDisposition )
	if (hr != WFS_SUCCESS) return -1;
#else
	HKEY hKeyXFSManager;

	char buf[2048];
	DWORD len = 2048;
	CStringA strOut;
	DWORD err;

	if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\XFS\\XFS_MANAGER", 0, KEY_READ, &hKeyXFSManager) == ERROR_SUCCESS)
	{
		if (RegQueryValueExA(hKeyXFSManager, "dllname", 0, 0, (BYTE*)buf, &len) == ERROR_SUCCESS)
		{
			buf[len - 1] = 0;
			strOut = (CStringA)buf;
		}
		else
		{
			err = GetLastError();
			SetLastError(NULL);

		}
	}
	else
	{
		err = GetLastError();
		SetLastError(NULL);
	}
#endif
#ifdef _V2_
	WFMCloseKey(hKeyXFS_ROOT);
	WFMCloseKey(hKeyXFSManager);
#else
	RegCloseKey(hKeyXFSManager);
#endif

	return strOut;
}

CStringA XFSManagerWrapper::FindConfigDLLPath()
{
	DWORD dwResult = 0;

#ifdef _V2_
	HKEY hKeyXFS_ROOT;
	HRESULT hr = WFMOpenKey(HKEY_CLASSES_ROOT, //WOSA/XFS_ROOT/LOGICAL_SERVICES,
		"WOSA/XFS_ROOT", //lpszSubKey, 
		&hKeyXFS_ROOT); //phkResult, lpdwDisposition )
	if (hr != WFS_SUCCESS) return -1;

	HKEY hKeyXFSManager;
	hr = WFMOpenKey(hKeyXFS_ROOT, //WOSA/XFS_ROOT/LOGICAL_SERVICES,
		"XFS_MANAGER", //lpszSubKey, 
		&hKeyXFSManager); //phkResult, lpdwDisposition )
	if (hr != WFS_SUCCESS) return -1;
#else
	HKEY hKeyXFSManager;

	char buf[2048];
	DWORD len = 2048;
	CStringA strOut;
	DWORD err;

	if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\XFS\\XFS_MANAGER", 0, KEY_READ, &hKeyXFSManager) == ERROR_SUCCESS)
	{
		if (RegQueryValueExA(hKeyXFSManager, "confdllname", 0, 0, (BYTE*)buf, &len) == ERROR_SUCCESS)
		{
			buf[len - 1] = 0;
			strOut = (CStringA)buf;
		}
		else
		{
			err = GetLastError();
			SetLastError(NULL);

		}
	}
	else
	{
		err = GetLastError();
		SetLastError(NULL);
	}
#endif
#ifdef _V2_
	WFMCloseKey(hKeyXFS_ROOT);
	WFMCloseKey(hKeyXFSManager);
#else
	RegCloseKey(hKeyXFSManager);
#endif
	return strOut;
}

CStringA XFSManagerWrapper::FindSupportDLLPath()
{
	DWORD dwResult = 0;

#ifdef _V2_
	HKEY hKeyXFS_ROOT;
	HRESULT hr = WFMOpenKey(HKEY_CLASSES_ROOT, //WOSA/XFS_ROOT/LOGICAL_SERVICES,
		"WOSA/XFS_ROOT", //lpszSubKey, 
		&hKeyXFS_ROOT); //phkResult, lpdwDisposition )
	if (hr != WFS_SUCCESS) return -1;

	HKEY hKeyXFSManager;
	hr = WFMOpenKey(hKeyXFS_ROOT, //WOSA/XFS_ROOT/LOGICAL_SERVICES,
		"XFS_MANAGER", //lpszSubKey, 
		&hKeyXFSManager); //phkResult, lpdwDisposition )
	if (hr != WFS_SUCCESS) return -1;
#else
	HKEY hKeyXFSManager;

	char buf[2048];
	DWORD len = 2048;
	CStringA strOut;
	DWORD err;

	if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\XFS\\XFS_MANAGER", 0, KEY_READ, &hKeyXFSManager) == ERROR_SUCCESS)
	{
		if (RegQueryValueExA(hKeyXFSManager, "suppdllname", 0, 0, (BYTE*)buf, &len) == ERROR_SUCCESS)
		{
			buf[len - 1] = 0;
			strOut = (CStringA)buf;
		}
		else
		{
			err = GetLastError();
			SetLastError(NULL);

		}
	}
	else
	{
		err = GetLastError();
		SetLastError(NULL);
	}
#endif
#ifdef _V2_
	WFMCloseKey(hKeyXFS_ROOT);
	WFMCloseKey(hKeyXFSManager);
#else
	RegCloseKey(hKeyXFSManager);
#endif
	return strOut;
}

bool XFSManagerWrapper::LoadXFSManager(CStringA strPath)
{
	CString strResult = _T("");
	m_bIsXFSMloaded = false;

	m_hXFSMLib = LoadLibraryA(strPath);
	if (m_hXFSMLib == NULL)
	{
		LOG_DATA(LOG_ERROR, CStringA("Load XFS Manager failed").GetBuffer());
		return m_bIsXFSMloaded;
	}
	else
	{
		m_bIsXFSMloaded = true;
		LOG_DATA(LOG_ERROR, CStringA("Load XFS Manager succeeded").GetBuffer());
	}

	fnWFSCancelBlockingCall = (pfnWFSCancelBlockingCall)GetProcAddress(m_hXFSMLib, "WFSCancelBlockingCall");
	if (fnWFSCancelBlockingCall == NULL)
	{
		strResult += _T("WFSCancelBlockingCall missing.\r\n");
	}
	fnWFSCleanUp = (pfnWFSCleanUp)GetProcAddress(m_hXFSMLib, "WFSCleanUp");
	if (fnWFSCleanUp == NULL)
	{
		strResult += _T("WFSCleanUp missing.\r\n");
	}
	fnWFSClose = (pfnWFSClose)GetProcAddress(m_hXFSMLib, "WFSClose");
	if (fnWFSClose == NULL)
	{
		strResult += _T("WFSClose missing.\r\n");
	}
	fnWFSAsyncClose = (pfnWFSAsyncClose)GetProcAddress(m_hXFSMLib, "WFSAsyncClose");
	if (fnWFSAsyncClose == NULL)
	{
		strResult += _T("WFSAsyncClose missing.\r\n");
	}
	fnWFSCreateAppHandle = (pfnWFSCreateAppHandle)GetProcAddress(m_hXFSMLib, "WFSCreateAppHandle");
	if (fnWFSCreateAppHandle == NULL)
	{
		strResult += _T("WFSCreateAppHandle missing.\r\n");
	}
	fnWFSDeregister = (pfnWFSDeregister)GetProcAddress(m_hXFSMLib, "WFSDeregister");
	if (fnWFSDeregister == NULL)
	{
		strResult += _T("WFSDeregister missing.\r\n");
	}
	fnWFSAsyncDeregister = (pfnWFSAsyncDeregister)GetProcAddress(m_hXFSMLib, "WFSAsyncDeregister");
	if (fnWFSAsyncDeregister == NULL)
	{
		strResult += _T("WFSAsyncDeregister missing.\r\n");
	}
	fnWFSDestroyAppHandle = (pfnWFSDestroyAppHandle)GetProcAddress(m_hXFSMLib, "WFSDestroyAppHandle");
	if (fnWFSDestroyAppHandle == NULL)
	{
		strResult += _T("WFSDestroyAppHandle missing.\r\n");
	}
	fnWFSExecute = (pfnWFSExecute)GetProcAddress(m_hXFSMLib, "WFSExecute");
	if (fnWFSExecute == NULL)
	{
		strResult += _T("WFSExecute missing.\r\n");
	}
	fnWFSAsyncExecute = (pfnWFSAsyncExecute)GetProcAddress(m_hXFSMLib, "WFSAsyncExecute");
	if (fnWFSAsyncExecute == NULL)
	{
		strResult += _T("WFSAsyncExecute missing.\r\n");
	}
	fnWFSFreeResult = (pfnWFSFreeResult)GetProcAddress(m_hXFSMLib, "WFSFreeResult");
	if (fnWFSFreeResult == NULL)
	{
		strResult += _T("WFSFreeResult missing.\r\n");
	}
	fnWFSGetInfo = (pfnWFSGetInfo)GetProcAddress(m_hXFSMLib, "WFSGetInfo");
	if (fnWFSGetInfo == NULL)
	{
		strResult += _T("WFSGetInfo missing.\r\n");
	}

	fnWFSAsyncGetInfo = (pfnWFSAsyncGetInfo)GetProcAddress(m_hXFSMLib, "WFSAsyncGetInfo");
	if (fnWFSAsyncGetInfo == NULL)
	{
		strResult += _T("WFSAsyncGetInfo missing.\r\n");
	}
	fnWFSIsBlocking = (pfnWFSIsBlocking)GetProcAddress(m_hXFSMLib, "WFSIsBlocking");
	if (fnWFSIsBlocking == NULL)
	{
		strResult += _T("WFSIsBlocking missing.\r\n");
	}
	fnWFSLock = (pfnWFSLock)GetProcAddress(m_hXFSMLib, "WFSLock");
	if (fnWFSLock == NULL)
	{
		strResult += _T("WFSLock missing.\r\n");
	}
	fnWFSAsyncLock = (pfnWFSAsyncLock)GetProcAddress(m_hXFSMLib, "WFSAsyncLock");
	if (fnWFSAsyncLock == NULL)
	{
		strResult += _T("WFSAsyncLock missing.\r\n");
	}
	fnWFSOpen = (pfnWFSOpen)GetProcAddress(m_hXFSMLib, "WFSOpen");
	if (fnWFSOpen == NULL)
	{
		strResult += _T("WFSOpen missing.\r\n");
	}
	fnWFSAsyncOpen = (pfnWFSAsyncOpen)GetProcAddress(m_hXFSMLib, "WFSAsyncOpen");
	if (fnWFSAsyncOpen == NULL)
	{
		strResult += _T("WFSAsyncOpen missing.\r\n");
	}
	fnWFSRegister = (pfnWFSRegister)GetProcAddress(m_hXFSMLib, "WFSRegister");
	if (fnWFSRegister == NULL)
	{
		strResult += _T("WFSRegister missing.\r\n");
	}
	fnWFSAsyncRegister = (pfnWFSAsyncRegister)GetProcAddress(m_hXFSMLib, "WFSAsyncRegister");
	if (fnWFSAsyncRegister == NULL)
	{
		strResult += _T("WFSAsyncRegister missing.\r\n");
	}
	fnWFSSetBlockingHook = (pfnWFSSetBlockingHook)GetProcAddress(m_hXFSMLib, "WFSSetBlockingHook");
	if (fnWFSSetBlockingHook == NULL)
	{
		strResult += _T("WFSSetBlockingHook missing.\r\n");
	}
	fnWFSStartUp = (pfnWFSStartUp)GetProcAddress(m_hXFSMLib, "WFSStartUp");
	if (fnWFSStartUp == NULL)
	{
		strResult += _T("WFSStartUp missing.\r\n");
	}
	fnWFSUnhookBlockingHook = (pfnWFSUnhookBlockingHook)GetProcAddress(m_hXFSMLib, "WFSUnhookBlockingHook");
	if (fnWFSUnhookBlockingHook == NULL)
	{
		strResult += _T("WFSUnhookBlockingHook missing.\r\n");
	}
	fnWFSUnlock = (pfnWFSUnlock)GetProcAddress(m_hXFSMLib, "WFSUnlock");
	if (fnWFSUnlock == NULL)
	{
		strResult += _T("WFSUnlock missing.\r\n");
	}
	fnWFSAsyncUnlock = (pfnWFSAsyncUnlock)GetProcAddress(m_hXFSMLib, "WFSAsyncUnlock");
	if (fnWFSAsyncUnlock == NULL)
	{
		strResult += _T("WFSAsyncUnlock missing.\r\n");
	}
	fnWFMSetTraceLevel = (pfnWFMSetTraceLevel)GetProcAddress(m_hXFSMLib, "WFMSetTraceLevel");
	if (fnWFMSetTraceLevel == NULL)
	{
		strResult += _T("WFMSetTraceLevel missing.\r\n");
	}

	fnWFMAllocateBuffer = (pfnWFMAllocateBuffer)GetProcAddress(m_hXFSMLib, "WFMAllocateBuffer");
	if (fnWFMAllocateBuffer == NULL)
	{
		strResult += _T("WFMAllocateBuffer missing.\r\n");
	}
	fnWFMAllocateMore = (pfnWFMAllocateMore)GetProcAddress(m_hXFSMLib, "WFMAllocateMore");
	if (fnWFMAllocateMore == NULL)
	{
		strResult += _T("WFMAllocateMore missing.\r\n");
	}
	fnWFMFreeBuffer = (pfnWFMFreeBuffer)GetProcAddress(m_hXFSMLib, "WFMFreeBuffer");
	if (fnWFMFreeBuffer == NULL)
	{
		strResult += _T("WFMFreeBuffer missing.\r\n");
	}
	fnWFMGetTraceLevel = (pfnWFMGetTraceLevel)GetProcAddress(m_hXFSMLib, "WFMGetTraceLevel");
	if (fnWFMGetTraceLevel == NULL)
	{
		strResult += _T("WFMGetTraceLevel missing.\r\n");
	}
	fnWFMKillTimer = (pfnWFMKillTimer)GetProcAddress(m_hXFSMLib, "WFMGetTraceLevel");
	if (fnWFMKillTimer == NULL)
	{
		strResult += _T("WFMGetTraceLevel missing.\r\n");
	}
	fnWFMOutputTraceData = (pfnWFMOutputTraceData)GetProcAddress(m_hXFSMLib, "WFMOutputTraceData");
	if (fnWFMOutputTraceData == NULL)
	{
		strResult += _T("WFMOutputTraceData missing.\r\n");
	}
	fnWFMReleaseDLL = (pfnWFMReleaseDLL)GetProcAddress(m_hXFSMLib, "WFMReleaseDLL");
	if (fnWFMReleaseDLL == NULL)
	{
		strResult += _T("WFMReleaseDLL missing.\r\n");
	}
	fnWFMSetTimer = (pfnWFMSetTimer)GetProcAddress(m_hXFSMLib, "WFMSetTimer");
	if (fnWFMSetTimer == NULL)
	{
		strResult += _T("WFMSetTimer missing.\r\n");
	}

	strResult.Trim();
	if (strResult.GetLength() != 0)
	{
		LOG_DATA(LOG_ERROR, CStringA(strResult).GetBuffer());
		ReleaseXFSManager();
	}

	return m_bIsXFSMloaded;
}

bool XFSManagerWrapper::LoadConfigFunctions(CString strPath)
{
	CString strResult = _T("");
	m_bIsConfigLoaded = false;
	m_hConfigLib = LoadLibrary(strPath);
	if (m_hConfigLib == NULL)
	{
		LOG_DATA(LOG_ERROR, CStringA("Load XFS Config load failed.\r\n").GetBuffer());
		return m_bIsConfigLoaded;
	}
	else
	{
		m_bIsConfigLoaded = true;
		LOG_DATA(LOG_ERROR, CStringA("Load XFS Config load succeeded.\r\n").GetBuffer());
	}

	fnWFMCloseKey = (pfnWFMCloseKey)GetProcAddress(m_hConfigLib, "WFMCloseKey");
	if (fnWFMCloseKey == NULL)
	{
		strResult += _T("WFMCloseKey missing.\r\n");
	}
	fnWFMCreateKey = (pfnWFMCreateKey)GetProcAddress(m_hConfigLib, "WFMCreateKey");
	if (fnWFMCreateKey == NULL)
	{
		strResult += _T("WFMCreateKey missing.\r\n");
	}
	fnWFMDeleteKey = (pfnWFMDeleteKey)GetProcAddress(m_hConfigLib, "WFMDeleteKey");
	if (fnWFMDeleteKey == NULL)
	{
		strResult += _T("WFMDeleteKey missing.\r\n");
	}
	fnWFMDeleteValue = (pfnWFMDeleteValue)GetProcAddress(m_hConfigLib, "WFMDeleteValue");
	if (fnWFMDeleteValue == NULL)
	{
		strResult += _T("WFMDeleteValue missing.\r\n");
	}
	fnWFMEnumKey = (pfnWFMEnumKey)GetProcAddress(m_hConfigLib, "WFMEnumKey");
	if (fnWFMEnumKey == NULL)
	{
		strResult += _T("WFMEnumKey missing.\r\n");
	}
	fnWFMEnumValue = (pfnWFMEnumValue)GetProcAddress(m_hConfigLib, "WFMEnumValue");
	if (fnWFMEnumValue == NULL)
	{
		strResult += _T("WFMEnumValue missing.\r\n");
	}
	fnWFMOpenKey = (pfnWFMOpenKey)GetProcAddress(m_hConfigLib, "WFMOpenKey");
	if (fnWFMOpenKey == NULL)
	{
		strResult += _T("WFMOpenKey missing.\r\n");
	}
	fnWFMQueryValue = (pfnWFMQueryValue)GetProcAddress(m_hConfigLib, "WFMQueryValue");
	if (fnWFMQueryValue == NULL)
	{
		strResult += _T("WFMQueryValue missing.\r\n");
	}
	fnWFMSetValue = (pfnWFMSetValue)GetProcAddress(m_hConfigLib, "WFMSetValue");
	if (fnWFMSetValue == NULL)
	{
		strResult += _T("WFMSetValue missing.\r\n");
	}

	strResult.Trim();
	if (strResult.GetLength() > 0)
	{
		ReleaseConfigFunctions();
	}

	return m_bIsConfigLoaded;
}

bool XFSManagerWrapper::LoadSupportFunctions(CString strPath)
{
	CString strResult = _T("");
	m_bIsSupportLoaded = false;
	m_hSupportLib = LoadLibrary(strPath);
	if (m_hSupportLib == NULL)
	{
		LOG_DATA(LOG_ERROR, CStringA("XFS Support Dll load failed").GetBuffer());
		return m_bIsSupportLoaded;
	}
	else
	{
		m_bIsSupportLoaded = true;
		LOG_DATA(LOG_ERROR, CStringA("XFS Support Dll load succeeded").GetBuffer());
	}

	fnWFMAllocateBuffer = (pfnWFMAllocateBuffer)GetProcAddress(m_hSupportLib, "WFMAllocateBuffer");
	if (fnWFMAllocateBuffer == NULL)
	{
		strResult += _T("WFMAllocateBuffer missing.\r\n");
	}

	fnWFMAllocateMore = (pfnWFMAllocateMore)GetProcAddress(m_hSupportLib, "WFMAllocateMore");
	if (fnWFMAllocateMore == NULL)
	{
		strResult += _T("WFMAllocateMore missing.\r\n");
	}

	fnWFMFreeBuffer = (pfnWFMFreeBuffer)GetProcAddress(m_hSupportLib, "WFMFreeBuffer");
	if (fnWFMFreeBuffer == NULL)
	{
		strResult += _T("WFMFreeBuffer missing.\r\n");
	}
	strResult.Trim();
	if (strResult.GetLength() > 0)
	{
		ReleaseSupportFunctions();
	}

	return m_bIsSupportLoaded;
}

bool XFSManagerWrapper::Initialise()
{
	bool bRet = true;
	CStringA strXMLManagerPath = FindXFSManagerPath();
	CStringA strConfigPath = FindConfigDLLPath();
	CStringA strSupportPath = FindSupportDLLPath();

	if (strXMLManagerPath.GetLength() > 0)
	{
		if ((bRet = LoadXFSManager(strXMLManagerPath)) != true)
		{
			return bRet;
		}
	}

	LoadConfigFunctions((CString)strConfigPath);

	return bRet;
}

void XFSManagerWrapper::Release()
{
	ReleaseXFSManager();
	ReleaseConfigFunctions();
	ReleaseSupportFunctions();
}

void XFSManagerWrapper::ReleaseXFSManager()
{
	fnWFSCancelAsyncRequest = NULL;
	fnWFSCancelBlockingCall = NULL;
	fnWFSCleanUp = NULL;
	fnWFSClose = NULL;
	fnWFSAsyncClose = NULL;
	fnWFSCreateAppHandle = NULL;
	fnWFSDeregister = NULL;
	fnWFSAsyncDeregister = NULL;
	fnWFSDestroyAppHandle = NULL;
	fnWFSExecute = NULL;
	fnWFSAsyncExecute = NULL;
	fnWFSFreeResult = NULL;
	fnWFSGetInfo = NULL;
	fnWFSAsyncGetInfo = NULL;
	fnWFSIsBlocking = NULL;
	fnWFSLock = NULL;
	fnWFSAsyncLock = NULL;
	fnWFSOpen = NULL;
	fnWFSAsyncOpen = NULL;
	fnWFSRegister = NULL;
	fnWFSAsyncRegister = NULL;
	fnWFSSetBlockingHook = NULL;
	fnWFSStartUp = NULL;
	fnWFSUnhookBlockingHook = NULL;
	fnWFSUnlock = NULL;
	fnWFSAsyncUnlock = NULL;
	fnWFMAllocateBuffer = NULL;
	fnWFMAllocateMore = NULL;
	fnWFMFreeBuffer = NULL;
	fnWFMGetTraceLevel = NULL;
	fnWFMKillTimer = NULL;
	fnWFMOutputTraceData = NULL;
	fnWFMReleaseDLL = NULL;
	fnWFMSetTimer = NULL;
	fnWFMSetTraceLevel = NULL;

	fnWFMCloseKey = NULL;
	fnWFMCreateKey = NULL;
	fnWFMDeleteKey = NULL;
	fnWFMDeleteValue = NULL;
	fnWFMEnumKey = NULL;
	fnWFMEnumValue = NULL;
	fnWFMOpenKey = NULL;
	fnWFMQueryValue = NULL;
	fnWFMSetValue = NULL;

	if (m_hXFSMLib != NULL || m_bIsXFSMloaded == true)
	{
		FreeLibrary(m_hXFSMLib);
		m_hXFSMLib = NULL;
		m_bIsXFSMloaded = false;
	}
}

void XFSManagerWrapper::ReleaseConfigFunctions()
{
	fnWFMCloseKey = NULL;
	fnWFMCreateKey = NULL;
	fnWFMDeleteKey = NULL;
	fnWFMDeleteValue = NULL;
	fnWFMEnumKey = NULL;
	fnWFMEnumValue = NULL;
	fnWFMOpenKey = NULL;
	fnWFMQueryValue = NULL;
	fnWFMSetValue = NULL;

	if (m_hConfigLib != NULL || m_bIsConfigLoaded == true)
	{
		FreeLibrary(m_hConfigLib);
		m_hConfigLib = NULL;
		m_bIsConfigLoaded = false;
	}
}

void XFSManagerWrapper::ReleaseSupportFunctions()
{
	fnWFMAllocateBuffer = NULL;
	fnWFMAllocateMore = NULL;
	fnWFMFreeBuffer = NULL;
	if (m_hSupportLib != NULL || m_bIsSupportLoaded == true)
	{
		FreeLibrary(m_hSupportLib);
		m_hSupportLib = NULL;
		m_bIsSupportLoaded = false;
	}
}

XFSManagerWrapper::~XFSManagerWrapper(void)
{
	--m_nCounter;
	if (m_nCounter == 0)
	{
		Release();
		singleObj = NULL;
	}
}

HRESULT XFSManagerWrapper::WFSCancelAsyncRequest(HSERVICE hService, REQUESTID RequestID)
{
	if (fnWFSCancelAsyncRequest != NULL)
		return fnWFSCancelAsyncRequest(hService, RequestID);
	LOG_DATA(LOG_ERROR, "WFSCancelAsyncRequest Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFSCancelBlockingCall(DWORD dwThreadID)
{
	if (fnWFSCancelAsyncRequest != NULL)
		return fnWFSCancelBlockingCall(dwThreadID);
	LOG_DATA(LOG_ERROR, "WFSCancelBlockingCall Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFSCleanUp()
{
	if (fnWFSCleanUp != NULL)
		return fnWFSCleanUp();
	LOG_DATA(LOG_ERROR, "WFSCleanUp Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFSClose(HSERVICE hService)
{
	if (fnWFSClose != NULL)
		return fnWFSClose(hService);
	LOG_DATA(LOG_ERROR, "WFSClose Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFSAsyncClose(HSERVICE hService, HWND hWnd, LPREQUESTID lpRequestID)
{
	if (fnWFSAsyncClose != NULL)
		return fnWFSAsyncClose(hService, hWnd, lpRequestID);
	LOG_DATA(LOG_ERROR, "WFSAsyncClose Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFSCreateAppHandle(LPHAPP lphApp)
{
	if (fnWFSCreateAppHandle != NULL)
		return fnWFSCreateAppHandle(lphApp);
	LOG_DATA(LOG_ERROR, "WFSCreateAppHandle Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFSDeregister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg)
{
	if (fnWFSDeregister != NULL)
		return fnWFSDeregister(hService, dwEventClass, hWndReg);
	LOG_DATA(LOG_ERROR, "WFSDeregister Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFSAsyncDeregister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg, HWND hWnd, LPREQUESTID lpRequestID)
{
	if (fnWFSAsyncDeregister != NULL)
		return fnWFSAsyncDeregister(hService, dwEventClass, hWndReg, hWnd, lpRequestID);
	LOG_DATA(LOG_ERROR, "WFSAsyncDeregister Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFSDestroyAppHandle(HAPP hApp)
{
	if (fnWFSDestroyAppHandle != NULL)
		return fnWFSDestroyAppHandle(hApp);
	LOG_DATA(LOG_ERROR, "WFSDestroyAppHandle Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFSExecute(HSERVICE hService, DWORD dwCommand, LPVOID lpCmdData, DWORD dwTimeOut, LPWFSRESULT* lppResult)
{
	if (fnWFSExecute != NULL)
		return fnWFSExecute(hService, dwCommand, lpCmdData, dwTimeOut, lppResult);
	LOG_DATA(LOG_ERROR, "WFSExecute Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFSAsyncExecute(HSERVICE hService, DWORD dwCommand, LPVOID lpCmdData, DWORD dwTimeOut, HWND hWnd, LPREQUESTID lpRequestID)
{
	if (fnWFSAsyncExecute != NULL)
		return fnWFSAsyncExecute(hService, dwCommand, lpCmdData, dwTimeOut, hWnd, lpRequestID);
	LOG_DATA(LOG_ERROR, "WFSAsyncExecute Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFSFreeResult(LPWFSRESULT lpResult)
{
	if (fnWFSFreeResult != NULL)
		return fnWFSFreeResult(lpResult);
	LOG_DATA(LOG_ERROR, "WFSFreeResult Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFSGetInfo(HSERVICE hService, DWORD dwCategory, LPVOID lpQueryDetails, DWORD dwTimeOut, LPWFSRESULT* lppResult)
{
	if (fnWFSGetInfo != NULL)
		return fnWFSGetInfo(hService, dwCategory, lpQueryDetails, dwTimeOut, lppResult);
	LOG_DATA(LOG_ERROR, "WFSGetInfo Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFSAsyncGetInfo(HSERVICE hService, DWORD dwCategory, LPVOID lpQueryDetails, DWORD dwTimeOut, HWND hWnd, LPREQUESTID lpRequestID)
{
	HRESULT h;
	if (fnWFSAsyncGetInfo != NULL)
		h = fnWFSAsyncGetInfo(hService, dwCategory, lpQueryDetails, dwTimeOut, hWnd, lpRequestID);
	//Sleep(1000);
	return h;
	LOG_DATA(LOG_ERROR, "WFSAsyncGetInfo Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFSIsBlocking()
{
	if (fnWFSIsBlocking != NULL)
		return fnWFSIsBlocking();
	LOG_DATA(LOG_ERROR, "WFSIsBlocking Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFSLock(HSERVICE hService, DWORD dwTimeOut, LPWFSRESULT* lppResult)
{
	if (fnWFSLock != NULL)
		return fnWFSLock(hService, dwTimeOut, lppResult);
	LOG_DATA(LOG_ERROR, "WFSLock Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFSAsyncLock(HSERVICE hService, DWORD dwTimeOut, HWND hWnd, LPREQUESTID lpRequestID)
{
	if (fnWFSAsyncLock != NULL)
		return fnWFSAsyncLock(hService, dwTimeOut, hWnd, lpRequestID);
	LOG_DATA(LOG_ERROR, "WFSAsyncLock Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFSOpen(LPSTR lpszLogicalName, HAPP hApp, LPSTR lpszAppID, DWORD dwTraceLevel, DWORD dwTimeOut, DWORD dwSrvcVersionsRequired, LPWFSVERSION lpSrvcVersion, LPWFSVERSION lpSPIVersion, LPHSERVICE lphService)
{
	
	if (fnWFSOpen != NULL)
		return fnWFSOpen(lpszLogicalName, hApp, lpszAppID, dwTraceLevel, dwTimeOut, dwSrvcVersionsRequired, lpSrvcVersion, lpSPIVersion, lphService);
	LOG_DATA(LOG_ERROR, "WFSOpen Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFSAsyncOpen(LPSTR lpszLogicalName, HAPP hApp, LPSTR lpszAppID, DWORD dwTraceLevel, DWORD dwTimeOut, LPHSERVICE lphService, HWND hWnd, DWORD dwSrvcVersionsRequired, LPWFSVERSION lpSrvcVersion, LPWFSVERSION lpSPIVersion, LPREQUESTID lpRequestID)
{
	if (fnWFSAsyncOpen != NULL)
		return fnWFSAsyncOpen(lpszLogicalName, hApp, lpszAppID, dwTraceLevel, dwTimeOut, lphService, hWnd, dwSrvcVersionsRequired, lpSrvcVersion, lpSPIVersion, lpRequestID);
	LOG_DATA(LOG_ERROR, "WFSAsyncOpen Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFSRegister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg)
{
	
	if (fnWFSRegister != NULL)
		return fnWFSRegister(hService, dwEventClass, hWndReg);
	LOG_DATA(LOG_ERROR, "WFSRegister Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFSAsyncRegister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg, HWND hWnd, LPREQUESTID lpRequestID)
{
	if (fnWFSAsyncRegister != NULL)
		return fnWFSAsyncRegister(hService, dwEventClass, hWndReg, hWnd, lpRequestID);
	LOG_DATA(LOG_ERROR, "WFSAsyncRegister Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFSSetBlockingHook(XFSBLOCKINGHOOK lpBlockFunc, LPXFSBLOCKINGHOOK lppPrevFunc)
{
	if (fnWFSSetBlockingHook != NULL)
		return fnWFSSetBlockingHook(lpBlockFunc, lppPrevFunc);
	LOG_DATA(LOG_ERROR, "WFSSetBlockingHook Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFSStartUp(DWORD dwVersionsRequired, LPWFSVERSION lpWFSVersion)
{
	LOG_DATA(LOG_ERROR, "WFSStartUp Called");
	if (fnWFSStartUp != NULL)
		return fnWFSStartUp(dwVersionsRequired, lpWFSVersion);
	LOG_DATA(LOG_ERROR, "WFSStartUp Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFSUnhookBlockingHook()
{
	if (fnWFSUnhookBlockingHook != NULL)
		return fnWFSUnhookBlockingHook();
	LOG_DATA(LOG_ERROR, "WFSUnhookBlockingHook Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFSUnlock(HSERVICE hService)
{
	if (fnWFSUnlock != NULL)
		return fnWFSUnlock(hService);
	LOG_DATA(LOG_ERROR, "WFSUnlock Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFSAsyncUnlock(HSERVICE hService, HWND hWnd, LPREQUESTID lpRequestID)
{
	if (fnWFSAsyncUnlock != NULL)
		return fnWFSAsyncUnlock(hService, hWnd, lpRequestID);
	LOG_DATA(LOG_ERROR, "WFSAsyncUnlock Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFMSetTraceLevel(HSERVICE hService, DWORD dwTraceLevel)
{
	if (fnWFMSetTraceLevel != NULL)
		return fnWFMSetTraceLevel(hService, dwTraceLevel);
	LOG_DATA(LOG_ERROR, "WFMSetTraceLevel Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFMAllocateBuffer(ULONG ulSize, ULONG ulFlags, LPVOID* lppvData)
{
	if (fnWFMAllocateBuffer != NULL)
		return fnWFMAllocateBuffer(ulSize, ulFlags, lppvData);
	LOG_DATA(LOG_ERROR, "WFMAllocateBuffer Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFMAllocateMore(ULONG ulSize, LPVOID lpvOriginal, LPVOID* lppvData)
{
	if (fnWFMAllocateMore != NULL)
		return fnWFMAllocateMore(ulSize, lpvOriginal, lppvData);
	LOG_DATA(LOG_ERROR, "WFMAllocateMore Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFMFreeBuffer(LPVOID lpvData)
{
	if (fnWFMFreeBuffer != NULL)
		return fnWFMFreeBuffer(lpvData);
	LOG_DATA(LOG_ERROR, "WFMFreeBuffer Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFMGetTraceLevel(HSERVICE hService, LPDWORD lpdwTraceLevel)
{
	if (fnWFMGetTraceLevel != NULL)
		return fnWFMGetTraceLevel(hService, lpdwTraceLevel);
	LOG_DATA(LOG_ERROR, "WFMGetTraceLevel Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFMKillTimer(WORD wTimerID)
{
	if (fnWFMKillTimer != NULL)
		return fnWFMKillTimer(wTimerID);
	LOG_DATA(LOG_ERROR, "WFMKillTimer Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFMOutputTraceData(LPSTR lpszData)
{
	if (fnWFMOutputTraceData != NULL)
		return fnWFMOutputTraceData(lpszData);
	LOG_DATA(LOG_ERROR, "WFMOutputTraceData Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFMReleaseDLL(HPROVIDER hProvider)
{
	if (fnWFMReleaseDLL != NULL)
		return fnWFMReleaseDLL(hProvider);
	LOG_DATA(LOG_ERROR, "WFMReleaseDLL Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFMSetTimer(HWND hWnd, LPVOID lpContext, DWORD dwTimeVal, LPWORD lpwTimerID)
{
	if (fnWFMSetTimer != NULL)
		return fnWFMSetTimer(hWnd, lpContext, dwTimeVal, lpwTimerID);
	LOG_DATA(LOG_ERROR, "WFMSetTimer Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFMCloseKey(HKEY hKey)
{
	if (fnWFMCloseKey != NULL)
	{
		return fnWFMCloseKey(hKey);
	}
	else
	{
		return RegCloseKey(hKey);
	}
	LOG_DATA(LOG_ERROR, "WFMCloseKey Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT	XFSManagerWrapper::WFMCreateKey(HKEY hKey, LPSTR lpszSubKey, PHKEY phkResult, LPDWORD lpdwDisposition)
{
	if (fnWFMCreateKey != NULL)
	{
		return fnWFMCreateKey(hKey, lpszSubKey, phkResult, lpdwDisposition);
	}
	else
	{
		if (lpszSubKey != NULL)
		{
			SECURITY_DESCRIPTOR dsec;
			InitializeSecurityDescriptor(&dsec, SECURITY_DESCRIPTOR_REVISION);
			SECURITY_ATTRIBUTES sec;
			sec.bInheritHandle = TRUE;
			sec.lpSecurityDescriptor = &dsec;
			sec.nLength = sizeof(SECURITY_ATTRIBUTES);

			CString subKey = CString(lpszSubKey);
			return RegCreateKeyEx(hKey, subKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_CREATE_SUB_KEY, &sec, phkResult, NULL);
		}
	}
	LOG_DATA(LOG_ERROR, "WFMCreateKey Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFMDeleteKey(HKEY hKey, LPSTR lpszSubKey)
{
	if (fnWFMDeleteKey != NULL)
	{
		return fnWFMDeleteKey(hKey, lpszSubKey);
	}
	else
	{
		CString subKey = CString(lpszSubKey);
		return RegDeleteKeyEx(hKey, subKey, KEY_ALL_ACCESS, NULL);
	}
	LOG_DATA(LOG_ERROR, "WFMDeleteKey Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFMDeleteValue(HKEY hKey, LPSTR lpszValue)
{
	if (fnWFMDeleteValue != NULL)
	{
		return fnWFMDeleteValue(hKey, lpszValue);
	}
	else
	{
		CString value = CString(lpszValue);
		return RegDeleteValue(hKey, value);
	}
	LOG_DATA(LOG_ERROR, "WFMDeleteValue Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFMEnumKey(HKEY hKey, DWORD iSubKey, LPSTR lpszName, LPDWORD lpcchName, PFILETIME lpftLastWrite)
{
	if (fnWFMEnumKey != NULL)
	{
		return fnWFMEnumKey(hKey, iSubKey, lpszName, lpcchName, lpftLastWrite);
	}
	else
	{
		CString name = CString(lpszName);
		return RegEnumKeyEx(hKey, iSubKey, name.GetBuffer(), lpcchName, 0, NULL, NULL, lpftLastWrite);
	}
	LOG_DATA(LOG_ERROR, "WFMEnumKey Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT  XFSManagerWrapper::WFMEnumValue(HKEY hKey, DWORD iValue, LPSTR lpszValue, LPDWORD lpcchValue, LPSTR lpszData, LPDWORD lpcchData)
{
	if (fnWFMEnumValue != NULL)
	{
		return fnWFMEnumValue(hKey, iValue, lpszValue, lpcchValue, lpszData, lpcchData);
	}
	else
	{
		CString value = CString(lpszValue);
		return RegEnumValue(hKey, iValue, value.GetBuffer(), lpcchValue, 0, NULL, (LPBYTE)lpszData, lpcchData);
	}
	LOG_DATA(LOG_ERROR, "WFMEnumValue Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFMOpenKey(HKEY hKey, LPSTR lpszSubKey, PHKEY phkResult)
{
	if (fnWFMOpenKey != NULL)
	{
		return fnWFMOpenKey(hKey, lpszSubKey, phkResult);
	}
	else
	{
		CString subKey = CString(lpszSubKey);
		return RegOpenKeyEx(hKey, subKey, 0, KEY_ALL_ACCESS | KEY_WOW64_32KEY, phkResult);
	}
	LOG_DATA(LOG_ERROR, "WFMOpenKey Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFMQueryValue(HKEY hKey, LPSTR lpszValueName, LPSTR lpszData, LPDWORD lpcchData)
{
	if (fnWFMQueryValue != NULL)
	{
		return fnWFMQueryValue(hKey, lpszValueName, lpszData, lpcchData);
	}
	else
	{
		CString value = CString(lpszValueName);
		return RegQueryValueEx(hKey, value, 0, NULL, (LPBYTE)lpszData, lpcchData);
	}
	LOG_DATA(LOG_ERROR, "WFMQueryValue Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}

HRESULT XFSManagerWrapper::WFMSetValue(HKEY hKey, LPSTR lpszValueName, LPSTR lpszData, DWORD cchData)
{
	if (fnWFMSetValue != NULL)
	{
		return fnWFMSetValue(hKey, lpszValueName, lpszData, cchData);
	}
	else
	{
		CString value = CString(lpszValueName);
		CString data = CString(lpszData);
		return RegSetValue(hKey, value, REG_SZ, data, cchData);
	}
	LOG_DATA(LOG_ERROR, "WFMSetValue Not found");
	return WFS_ERR_XFSMANAGER_ERROR;
}