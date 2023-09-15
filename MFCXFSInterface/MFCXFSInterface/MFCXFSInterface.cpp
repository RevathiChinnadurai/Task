// MFCXFSInterface.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "framework.h"
#include "MFCXFSInterface.h"
#include "Helper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CMFCXFSInterfaceApp

BEGIN_MESSAGE_MAP(CMFCXFSInterfaceApp, CWinApp)
	//ON_THREAD_MESSAGE(XFS_MSG_WFS_SYSTEMEVENT,OnSystemEventmessage)

END_MESSAGE_MAP()


// CMFCXFSInterfaceApp construction
XFSManagerWrapper* m_pXFSManagerwrapper;


void CMFCXFSInterfaceApp::OnSystemEventmessage(WPARAM wParam, LPARAM lParam)
{
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	//devicename = (LPWFSDEVSTATUS)pWESResult->lpBuffer;
	LOG_DATA(LOG_DEBUG, "thread messgae Called");

}


CMFCXFSInterfaceApp::CMFCXFSInterfaceApp()
{
	SetModuleName("MFCXFSInterface");

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CMFCXFSInterfaceApp object

CMFCXFSInterfaceApp theApp;


// CMFCXFSInterfaceApp initialization

BOOL CMFCXFSInterfaceApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
//BOOL CMFCXFSInterfaceApp::ExitInstance()
//{
//	PostThreadMessage(WM_QUIT,0,0);
	//return CWinApp::ExitInstance();
//}

messagewnd* m_pWnd;
WFSVERSION m_wfsServiceVersion;
WFSVERSION m_wfsSPIVersion;
HSERVICE m_hService;
HWND m_hWnd=0;
int deviceid;
WFSVERSION  m_wfsXFSManagerVersion;
bool camstatus;
bool ptrstatus;
bool pinstatus;
CCriticalSection g_Critical;
CEvent m_eventsystem;
BOOL g_isBlocking;

CAutoLock AutoLock(&g_Critical);


BEGIN_MESSAGE_MAP(messagewnd, CWnd)
	ON_MESSAGE(WFS_SYSTEM_EVENT, OnSystemEvent)
END_MESSAGE_MAP()
LPWFSDEVSTATUS pDevStatus;
LRESULT  messagewnd::OnSystemEvent(WPARAM wParam, LPARAM lParam)
{
	CWinApp* pApp = AfxGetApp();
	LOG_DATA(LOG_DEBUG, "Onsystem Event Invoked invoked....");
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	LPWFSDEVSTATUS devicename = (LPWFSDEVSTATUS)pWESResult->lpBuffer;

	if (strcmp(devicename->lpszPhysicalName, "ITASCamera") == 0)
	{

		switch (pWESResult->u.dwEventID)
		{
		case WFS_SYSE_UNDELIVERABLE_MSG:
		{
			LPWFSUNDEVMSG pUnDelivMsg = (LPWFSUNDEVMSG)pWESResult->lpBuffer;
		}
		break;
		case WFS_SYSE_DEVICE_STATUS:
		{
			CString strTxt;
	        pDevStatus = (LPWFSDEVSTATUS)pWESResult->lpBuffer;
			if (pDevStatus->dwState == WFS_STAT_DEVONLINE)
			{
				camstatus = true;
				strTxt.Format(L"Online");
				CString strTxt = L"Online";
				LOG_DATA(LOG_DEBUG, (CStringA)strTxt);
				//SendMessage((UINT)pDevStatus, wParam, lParam);
				//MessageBox(L"Camera Online", 0, 0);
				
			}
			else
			{
				camstatus = false;
				strTxt.Format(L"Camera offline");
				LOG_DATA(LOG_DEBUG, (CStringA)strTxt);
				//MessageBox(L"Camera Offline", 0, 0);
				//AppendStatus(strTxt);
			}
		}
		break;
		case WFS_SYSE_APP_DISCONNECT:
		{
			LPWFSAPPDISC pAppDisconnect = (LPWFSAPPDISC)pWESResult->lpBuffer;
		}
		break;
		case WFS_SYSE_HARDWARE_ERROR:
		{
			LPWFSHWERROR pError = (LPWFSHWERROR)pWESResult->lpBuffer;
		}
		break;
		case WFS_SYSE_SOFTWARE_ERROR:
		{
			LPWFSHWERROR pError = (LPWFSHWERROR)pWESResult->lpBuffer;
		}
		break;
		case WFS_SYSE_USER_ERROR:
		{
			LPWFSHWERROR pError = (LPWFSHWERROR)pWESResult->lpBuffer;
		}
		break;
		case WFS_SYSE_FRAUD_ATTEMPT:
		{
			LPWFSHWERROR pError = (LPWFSHWERROR)pWESResult->lpBuffer;
		}
		break;
		case WFS_SYSE_VERSION_ERROR:
		{
			LPWFSVRSNERROR pError = (LPWFSVRSNERROR)pWESResult->lpBuffer;
		}
		break;
		case WFS_SYSE_LOCK_REQUESTED:
		{
		}
		break;
		}
	}
	else if (strcmp(devicename->lpszPhysicalName, "ITASPrinter") == 0)
	{
		switch (pWESResult->u.dwEventID)
		{
		case WFS_SYSE_UNDELIVERABLE_MSG:
		{
			LPWFSUNDEVMSG pUnDelivMsg = (LPWFSUNDEVMSG)pWESResult->lpBuffer;
		}
		break;
		case WFS_SYSE_DEVICE_STATUS:
		{
			CString strTxt;
			 pDevStatus = (LPWFSDEVSTATUS)pWESResult->lpBuffer;
			if (pDevStatus->dwState == WFS_STAT_DEVONLINE)
			{
				ptrstatus = true;
				strTxt.Format(L"Printer online");
				LOG_DATA(LOG_DEBUG, (CStringA)strTxt);
				//MessageBox(L"Printer Online", 0, 0);
				
			}
			else
			{
				ptrstatus = false;
				strTxt.Format(L"Printer offline");
				LOG_DATA(LOG_DEBUG, (CStringA)strTxt);
				//MessageBox(L"Printer Offline", 0, 0);
				//AppendStatus(strTxt);
			}
		}
		break;
		case WFS_SYSE_APP_DISCONNECT:
		{
			LPWFSAPPDISC pAppDisconnect = (LPWFSAPPDISC)pWESResult->lpBuffer;
		}
		break;
		case WFS_SYSE_HARDWARE_ERROR:
		{
			LPWFSHWERROR pError = (LPWFSHWERROR)pWESResult->lpBuffer;
		}
		break;
		case WFS_SYSE_SOFTWARE_ERROR:
		{
			LPWFSHWERROR pError = (LPWFSHWERROR)pWESResult->lpBuffer;
		}
		break;
		case WFS_SYSE_USER_ERROR:
		{
			LPWFSHWERROR pError = (LPWFSHWERROR)pWESResult->lpBuffer;
		}
		break;
		case WFS_SYSE_FRAUD_ATTEMPT:
		{
			LPWFSHWERROR pError = (LPWFSHWERROR)pWESResult->lpBuffer;
		}
		break;
		case WFS_SYSE_VERSION_ERROR:
		{
			LPWFSVRSNERROR pError = (LPWFSVRSNERROR)pWESResult->lpBuffer;
		}
		break;
		case WFS_SYSE_LOCK_REQUESTED:
		{
		}
		break;
		}

	}
	else if (strcmp(devicename->lpszPhysicalName, "ITASPinpad") == 0)
	{
		switch (pWESResult->u.dwEventID)
		{
		case WFS_SYSE_UNDELIVERABLE_MSG:
		{
			LPWFSUNDEVMSG pUnDelivMsg = (LPWFSUNDEVMSG)pWESResult->lpBuffer;
		}
		break;
		case WFS_SYSE_DEVICE_STATUS:
		{
			CString strTxt;
			LPWFSDEVSTATUS pDevStatus = (LPWFSDEVSTATUS)pWESResult->lpBuffer;
			if (pDevStatus->dwState == WFS_STAT_DEVONLINE)
			{
				pinstatus = true;
				strTxt.Format(L"Pinpad online");
				LOG_DATA(LOG_DEBUG, (CStringA)strTxt);
				//MessageBox(L"PinPad Online", 0, 0);
			}
			else
			{
				pinstatus = false;
				strTxt.Format(L"PinPad offline");
				LOG_DATA(LOG_DEBUG, (CStringA)strTxt);
			//	MessageBox(L"PinPad Offline", L"Device Status", 0);
				//AppendStatus(strTxt);
			}
		}
		break;
		case WFS_SYSE_APP_DISCONNECT:
		{
			LPWFSAPPDISC pAppDisconnect = (LPWFSAPPDISC)pWESResult->lpBuffer;
		}
		break;
		case WFS_SYSE_HARDWARE_ERROR:
		{
			LPWFSHWERROR pError = (LPWFSHWERROR)pWESResult->lpBuffer;
		}
		break;
		case WFS_SYSE_SOFTWARE_ERROR:
		{
			LPWFSHWERROR pError = (LPWFSHWERROR)pWESResult->lpBuffer;
		}
		break;
		case WFS_SYSE_USER_ERROR:
		{
			LPWFSHWERROR pError = (LPWFSHWERROR)pWESResult->lpBuffer;
		}
		break;
		case WFS_SYSE_FRAUD_ATTEMPT:
		{
			LPWFSHWERROR pError = (LPWFSHWERROR)pWESResult->lpBuffer;
		}
		break;
		case WFS_SYSE_VERSION_ERROR:
		{
			LPWFSVRSNERROR pError = (LPWFSVRSNERROR)pWESResult->lpBuffer;
		}
		break;
		case WFS_SYSE_LOCK_REQUESTED:
		{
		}
		break;
		}
	}
	return nRes;
}



DLLAPI_API HRESULT LoadXFS()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	m_pXFSManagerwrapper = XFSManagerWrapper::GetInstance();
	DWORD dwVersionsRequired = 0x1403;
	LPWFSVERSION lpWFSVersion = &m_wfsXFSManagerVersion;
	m_pXFSManagerwrapper->WFSStartUp(dwVersionsRequired, lpWFSVersion);
	if (m_pXFSManagerwrapper == WFS_SUCCESS)
	{
		return WFS_SUCCESS;
	}
	else
	{
		return WFS_ERR_XFSMANAGER_ERROR;
	}
}


DLLAPI_API HRESULT CleanXFS()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	m_pXFSManagerwrapper->WFSCleanUp();
	if (m_pXFSManagerwrapper == WFS_SUCCESS)
	{
		return WFS_SUCCESS;
	}
	else
	{
		return WFS_ERR_XFSMANAGER_ERROR;
	}
}

DLLAPI_API HRESULT GetDeviceStatus(LPSTR devicetype)
{
	if (m_hWnd == 0)
	{
		static CString className = AfxRegisterWndClass(0);
		CRect rc(2, 2, 2, 2);
		m_pWnd = new messagewnd();
		BOOL b = m_pWnd->CreateEx(NULL, className, L"Message", WS_POPUP, rc, NULL, 0, NULL);
		if (b == FALSE)
		{
			LOG_DATA(LOG_DEBUG, CStringA("Window Creation failed in MFCXFSInterface\r\n"));

		}
		else {
			LOG_DATA(LOG_DEBUG, CStringA("Window Creation success  in MFCXFSInterface\r\n"));
		}
	}
	m_hWnd = m_pWnd->GetSafeHwnd();
	

	LOG_DATA(LOG_DEBUG, "GetDeviceStatus Called");

	LOG_DATA(LOG_DEBUG, (LPSTR)devicetype);
	if (strcmp(devicetype,"Camera") ==0) { deviceid = 1; }
	else if (strcmp(devicetype, "Printer") == 0) { deviceid = 2; }
	else if (strcmp(devicetype, "Pinpad") == 0) { deviceid = 3; }

	switch (deviceid)
	{
	case 1:
	{
		HRESULT hres;
		HRESULT hReg;
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		hres = m_pXFSManagerwrapper->WFSOpen("ITASCamera", WFS_DEFAULT_HAPP, "CAMSPTest", WFS_TRACE_ALL_SPI,
			WFS_INDEFINITE_WAIT, 0x00001403, &m_wfsServiceVersion, &m_wfsSPIVersion, &m_hService);
		if (hres == WFS_SUCCESS)
		{
			LOG_DATA(LOG_DEBUG, "WFSOpen Completed");	
			AFX_MANAGE_STATE(AfxGetStaticModuleState());
			m_eventsystem.ResetEvent();
			hres = m_pXFSManagerwrapper->WFSRegister(m_hService, WFS_EXECUTE_EVENT | WFS_USER_EVENT | WFS_SYSTEM_EVENT, m_hWnd);
			LOG_DATA(LOG_DEBUG, "WFSRegister Completed");
			
			//AutoLock.~CAutoLock();
			//Blocking(m_eventsystem.m_hObject, WFS_INDEFINITE_WAIT);
			
			CString strTxt;
			WFSRESULT* pwfsRes;
			LPWFSCAMSTATUS lpStatus = NULL;
			hres = m_pXFSManagerwrapper->WFSGetInfo(m_hService, WFS_INF_CAM_STATUS, NULL, WFS_INDEFINITE_WAIT, &pwfsRes);
			lpStatus = (LPWFSCAMSTATUS)pwfsRes->lpBuffer;
			if (lpStatus != NULL)
			{
				strTxt.Format(L"WFSCAMSTATUS::fwCameras = %d  \n \
								WFSCAMSTATUS::fwDevice = %d  \n \
								WFSCAMSTATUS::fwMedia = %d \n  \
								WFSCAMSTATUS::lpszExtra = %s \n  \
								WFSCAMSTATUS::usPictures= %d \n \
								WFSCAMSTATUS::wAntiFraudModule = %d \n", lpStatus->fwCameras[0], lpStatus->fwDevice, lpStatus->fwMedia[0], lpStatus->lpszExtra, lpStatus->usPictures[0], lpStatus->wAntiFraudModule);
				
				LOG_DATA(LOG_DEBUG,(CStringA)strTxt);
			}
			if (camstatus == true)
			{
				LOG_DATA(LOG_DEBUG, "Device is online ");
				return 0;
			}
			else
			{
				return 1;
			}
		}
		else
		{
			return WFS_ERR_XFSMANAGER_ERROR;
		}

	
	}
	break;
	case 2:
	{
		HRESULT hRes;
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
	hRes =	m_pXFSManagerwrapper->WFSOpen("ITASPrinter", WFS_DEFAULT_HAPP, "PTRSPTest", WFS_TRACE_ALL_SPI,
			WFS_INDEFINITE_WAIT, 0x00001403, &m_wfsServiceVersion, &m_wfsSPIVersion, &m_hService);
		if (hRes == WFS_SUCCESS)
		{
			LOG_DATA(LOG_DEBUG, "WFSOpen Completed");
			AFX_MANAGE_STATE(AfxGetStaticModuleState());
			hRes = m_pXFSManagerwrapper->WFSRegister(m_hService, WFS_EXECUTE_EVENT | WFS_USER_EVENT | WFS_SYSTEM_EVENT, m_hWnd);
			LOG_DATA(LOG_DEBUG, "WFSRegister Completed");
			//AutoLock.~CAutoLock();
			//Blocking(m_eventsystem.m_hObject, WFS_INDEFINITE_WAIT);
			if (ptrstatus == true)
			{
				LOG_DATA(LOG_DEBUG, "Device is online ");
				return 0;
			}
			else
			{
				return 1;
			}
				
			//return WFS_SUCCESS;
		}
		else
		{
			return WFS_ERR_XFSMANAGER_ERROR;
		}
		
	}break;
	case 3:
	{
		HRESULT hRes;
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		hRes = m_pXFSManagerwrapper->WFSOpen("ITASPinpad", WFS_DEFAULT_HAPP, "PINSPTest", WFS_TRACE_ALL_SPI,
			WFS_INDEFINITE_WAIT, 0x00001403, &m_wfsServiceVersion, &m_wfsSPIVersion, &m_hService);
		if (hRes == WFS_SUCCESS)
		{
			hRes = m_pXFSManagerwrapper->WFSRegister(m_hService, WFS_EXECUTE_EVENT | WFS_USER_EVENT | WFS_SYSTEM_EVENT, m_hWnd);
			LOG_DATA(LOG_DEBUG, "WFSRegister Completed");
		   // AutoLock.~CAutoLock();
		  //Blocking(m_eventsystem.m_hObject, WFS_INDEFINITE_WAIT);
			if (pinstatus == true)
			{
				LOG_DATA(LOG_DEBUG, "Device is online ");
				return 0;
			}
			else
			{
				return 1;
			}

			
		}
		else
		{
			return WFS_ERR_XFSMANAGER_ERROR;
		}
		
	}break;
	default:
		MessageBox(0, L"Enter Valid Device Type", L"Warning", MB_OK);
		break;
	}
}


void Blocking(HANDLE hHandle, DWORD dwTimeOut)
{
	DWORD dwMilliseconds = dwTimeOut;
	if (dwTimeOut == WFS_INDEFINITE_WAIT) dwMilliseconds = INFINITE;

	HANDLE handles[1];
	handles[0] = hHandle;

	g_isBlocking = TRUE;

	switch (MsgWaitForMultipleObjects(1, &handles[0], FALSE, dwMilliseconds, QS_ALLINPUT | QS_ALLPOSTMESSAGE | QS_ALLEVENTS)) {
	case WAIT_OBJECT_0: // event has been signalled
		break;
	case WAIT_OBJECT_0 + 1: // we have a message - peek and dispatch it
		MSG msg;

		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	case WAIT_TIMEOUT: // Timeout failure
		break;
	default: // unexpected failure
		break;
	}

	g_isBlocking = FALSE;
	//g_BlockedHandle = 0;

}