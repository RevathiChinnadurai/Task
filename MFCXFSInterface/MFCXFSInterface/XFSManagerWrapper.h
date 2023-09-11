#pragma once
#include "XFSAPI.H"
#include "Definitions.h"
#include "messagewnd.h"

/******* Value of hKey *******************************************************/
#define     WFS_CFG_HKEY_XFS_ROOT               ((HKEY)1)
// these 2 values have been switched now
#define		WFS_CFG_USER_DEFAULT_XFS_ROOT       ((HKEY)3)
#define		WFS_CFG_MACHINE_XFS_ROOT            ((HKEY)2)
#define		WFS_CFG_CURRENT_USER_XFS_ROOT		((HKEY)4)

/******* Values of lpdwDisposition *******************************************/
#define     WFS_CFG_CREATED_NEW_KEY             (0)
#define     WFS_CFG_OPENED_EXISTING_KEY         (1)


#define		WFS_ERR_XFSMANAGER_ERROR            (-80)


class XFSManagerWrapper
{
	
	static XFSManagerWrapper* singleObj;
	static int m_nCounter;

	HMODULE m_hXFSMLib;
	HMODULE m_hConfigLib;
	HMODULE m_hSupportLib;

	bool m_bIsXFSMloaded;
	bool m_bIsConfigLoaded;
	bool m_bIsSupportLoaded;

	XFSManagerWrapper()
	{
	
		SetModuleName("MFCXFSInterface");
		//m_pWnd = 0;
		m_hXFSMLib = NULL;
		m_hConfigLib = NULL;
		m_hSupportLib = NULL;
		m_bIsXFSMloaded = m_bIsConfigLoaded = m_bIsSupportLoaded = false;
	}

	CStringA FindXFSManagerPath();
	CStringA FindConfigDLLPath();
	CStringA FindSupportDLLPath();

	bool LoadXFSManager(CStringA strPath);
	void ReleaseXFSManager();
	bool LoadConfigFunctions(CString strPath);
	void ReleaseConfigFunctions();
	bool LoadSupportFunctions(CString strPath);
	void ReleaseSupportFunctions();

	bool Initialise();
	void Release();

public:
	static XFSManagerWrapper* GetInstance();

	~XFSManagerWrapper(void);

	HRESULT WFSCancelAsyncRequest(HSERVICE hService, REQUESTID RequestID);
	HRESULT WFSCancelBlockingCall(DWORD dwThreadID);
	HRESULT WFSCleanUp();
	HRESULT WFSClose(HSERVICE hService);
	HRESULT WFSAsyncClose(HSERVICE hService, HWND hWnd, LPREQUESTID lpRequestID);
	HRESULT WFSCreateAppHandle(LPHAPP lphApp);
	HRESULT WFSDeregister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg);
	HRESULT WFSAsyncDeregister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg, HWND hWnd, LPREQUESTID lpRequestID);
	HRESULT WFSDestroyAppHandle(HAPP hApp);
	HRESULT WFSExecute(HSERVICE hService, DWORD dwCommand, LPVOID lpCmdData, DWORD dwTimeOut, LPWFSRESULT* lppResult);
	HRESULT WFSAsyncExecute(HSERVICE hService, DWORD dwCommand, LPVOID lpCmdData, DWORD dwTimeOut, HWND hWnd, LPREQUESTID lpRequestID);
	HRESULT WFSFreeResult(LPWFSRESULT lpResult);
	HRESULT WFSGetInfo(HSERVICE hService, DWORD dwCategory, LPVOID lpQueryDetails, DWORD dwTimeOut, LPWFSRESULT* lppResult);
	HRESULT WFSAsyncGetInfo(HSERVICE hService, DWORD dwCategory, LPVOID lpQueryDetails, DWORD dwTimeOut, HWND hWnd, LPREQUESTID lpRequestID);
	HRESULT WFSIsBlocking();
	HRESULT WFSLock(HSERVICE hService, DWORD dwTimeOut, LPWFSRESULT* lppResult);
	HRESULT WFSAsyncLock(HSERVICE hService, DWORD dwTimeOut, HWND hWnd, LPREQUESTID lpRequestID);
	HRESULT WFSOpen(LPSTR lpszLogicalName, HAPP hApp, LPSTR lpszAppID, DWORD dwTraceLevel, DWORD dwTimeOut, DWORD dwSrvcVersionsRequired, LPWFSVERSION lpSrvcVersion, LPWFSVERSION lpSPIVersion, LPHSERVICE lphService);
	HRESULT WFSAsyncOpen(LPSTR lpszLogicalName, HAPP hApp, LPSTR lpszAppID, DWORD dwTraceLevel, DWORD dwTimeOut, LPHSERVICE lphService, HWND hWnd, DWORD dwSrvcVersionsRequired, LPWFSVERSION lpSrvcVersion, LPWFSVERSION lpSPIVersion, LPREQUESTID lpRequestID);
	HRESULT WFSRegister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg);
	HRESULT WFSAsyncRegister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg, HWND hWnd, LPREQUESTID lpRequestID);
	HRESULT WFSSetBlockingHook(XFSBLOCKINGHOOK lpBlockFunc, LPXFSBLOCKINGHOOK lppPrevFunc);
	HRESULT WFSStartUp(DWORD dwVersionsRequired, LPWFSVERSION lpWFSVersion);
	HRESULT WFSUnhookBlockingHook();
	HRESULT WFSUnlock(HSERVICE hService);
	HRESULT WFSAsyncUnlock(HSERVICE hService, HWND hWnd, LPREQUESTID lpRequestID);
	HRESULT WFMSetTraceLevel(HSERVICE hService, DWORD dwTraceLevel);

	HRESULT WFMAllocateBuffer(ULONG ulSize, ULONG ulFlags, LPVOID* lppvData);
	HRESULT WFMAllocateMore(ULONG ulSize, LPVOID lpvOriginal, LPVOID* lppvData);
	HRESULT WFMFreeBuffer(LPVOID lpvData);
	HRESULT WFMGetTraceLevel(HSERVICE hService, LPDWORD lpdwTraceLevel);
	HRESULT WFMKillTimer(WORD wTimerID);
	HRESULT WFMOutputTraceData(LPSTR lpszData);
	HRESULT WFMReleaseDLL(HPROVIDER hProvider);
	HRESULT WFMSetTimer(HWND hWnd, LPVOID lpContext, DWORD dwTimeVal, LPWORD lpwTimerID);

	HRESULT WFMCloseKey(HKEY hKey);
	HRESULT	WFMCreateKey(HKEY hKey, LPSTR lpszSubKey, PHKEY phkResult, LPDWORD lpdwDisposition);
	HRESULT WFMDeleteKey(HKEY hKey, LPSTR lpszSubKey);
	HRESULT WFMDeleteValue(HKEY hKey, LPSTR lpszValue);
	HRESULT WFMEnumKey(HKEY hKey, DWORD iSubKey, LPSTR lpszName, LPDWORD lpcchName, PFILETIME lpftLastWrite);
	HRESULT WFMEnumValue(HKEY hKey, DWORD iValue, LPSTR lpszValue, LPDWORD lpcchValue, LPSTR lpszData, LPDWORD lpcchData);
	HRESULT WFMOpenKey(HKEY hKey, LPSTR lpszSubKey, PHKEY phkResult);
	HRESULT WFMQueryValue(HKEY hKey, LPSTR lpszValueName, LPSTR lpszData, LPDWORD lpcchData);
	HRESULT WFMSetValue(HKEY hKey, LPSTR lpszValueName, LPSTR lpszData, DWORD cchData);

};
