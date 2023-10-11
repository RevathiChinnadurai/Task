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



// CMFCXFSInterfaceApp construction
XFSManagerWrapper* m_pXFSManagerwrapper;




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

struct camerastatus
{
	CString camname, camstate, cammedia, camfraudmodule, camstatus;
}camera;

struct ptrstatus
{
	CString ptrname, ptrstate, ptrmedia, ptrpprstate, ptrpprtype;
}printer;

messagewnd* m_pWnd;
WFSVERSION m_wfsServiceVersion;
WFSVERSION m_wfsSPIVersion;
HSERVICE m_hService;
HWND m_hWnd=0;
int deviceid;
WFSVERSION  m_wfsXFSManagerVersion;
bool bcamstatus, bptrstatus, bpinstatus,bsuistatus;
CCriticalSection g_Critical;
BOOL g_isBlocking;
int camservice, ptrservice, pinservice,suiservice;
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
		camera.camname = (CString)devicename->lpszPhysicalName;
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
				bcamstatus = true;
				strTxt.Format(L"Online");
				CString strTxt = L"Online";
				LOG_DATA(LOG_DEBUG, (CStringA)strTxt);
			}
			else
			{
				bcamstatus = false;
				strTxt.Format(L"Camera offline");
				LOG_DATA(LOG_DEBUG, (CStringA)strTxt);
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
			printer.ptrname =(CString) devicename->lpszPhysicalName;
			CString strTxt;
			pDevStatus = (LPWFSDEVSTATUS)pWESResult->lpBuffer;
			if (pDevStatus->dwState == WFS_STAT_DEVONLINE)
			{
				bptrstatus = true;
				strTxt.Format(L"Printer online");
				LOG_DATA(LOG_DEBUG, (CStringA)strTxt);
				//MessageBox(L"Printer Online", 0, 0);

			}
			else
			{
				bptrstatus = false;
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
				bpinstatus = true;
				strTxt.Format(L"Pinpad online");
				LOG_DATA(LOG_DEBUG, (CStringA)strTxt);
				//MessageBox(L"PinPad Online", 0, 0);
			}
			else
			{
				bpinstatus = false;
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
	else if (strcmp(devicename->lpszPhysicalName, "ITASSensorUnit") == 0)
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
				bsuistatus = true;
				strTxt.Format(L"SIU online");
				LOG_DATA(LOG_DEBUG, (CStringA)strTxt);
			}
			else
			{
				bsuistatus = false;
				strTxt.Format(L"SIU offline");
				LOG_DATA(LOG_DEBUG, (CStringA)strTxt);
				
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
		return nRes;
	}
}


void Appendstatus(CString strTxt)
{
	CString txt;
	txt = strTxt;
	txt.Append(_T("\r\n"));
	txt += strTxt;
	strTxt = txt;
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
	else if (strcmp(devicetype, "Sensor") == 0) { deviceid = 4; }

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
			CStringA str;
			str.Format("Hservice = %d", m_hService);
			camservice = m_hService;
			LOG_DATA(LOG_ERROR, str.GetBuffer());
			LOG_DATA(LOG_DEBUG, "WFSOpen Completed");	
			AFX_MANAGE_STATE(AfxGetStaticModuleState());
			hres = m_pXFSManagerwrapper->WFSRegister(m_hService, WFS_EXECUTE_EVENT | WFS_USER_EVENT | WFS_SYSTEM_EVENT, m_hWnd);
			LOG_DATA(LOG_DEBUG, "WFSRegister Completed");
			
			if (bcamstatus == true)
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
			CStringA str;
			str.Format("Hservice = %d", m_hService);
			LOG_DATA(LOG_ERROR, str.GetBuffer());
			ptrservice = m_hService;
			LOG_DATA(LOG_DEBUG, "WFSOpen Completed");
			AFX_MANAGE_STATE(AfxGetStaticModuleState());
			hRes = m_pXFSManagerwrapper->WFSRegister(m_hService, WFS_EXECUTE_EVENT | WFS_USER_EVENT | WFS_SYSTEM_EVENT, m_hWnd);
			LOG_DATA(LOG_DEBUG, "WFSRegister Completed");
			//AutoLock.~CAutoLock();
			//Blocking(m_eventsystem.m_hObject, WFS_INDEFINITE_WAIT);
			if (bptrstatus == true)
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
			pinservice = m_hService;
			hRes = m_pXFSManagerwrapper->WFSRegister(m_hService, WFS_EXECUTE_EVENT | WFS_USER_EVENT | WFS_SYSTEM_EVENT, m_hWnd);
			LOG_DATA(LOG_DEBUG, "WFSRegister Completed");
		   // AutoLock.~CAutoLock();
		  //Blocking(m_eventsystem.m_hObject, WFS_INDEFINITE_WAIT);
			if (bpinstatus == true)
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
	case 4:
	{
		HRESULT hRes;
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		hRes = m_pXFSManagerwrapper->WFSOpen("ITASSensorUnit", WFS_DEFAULT_HAPP, "SIUSPTest", WFS_TRACE_ALL_SPI,
			WFS_INDEFINITE_WAIT, 0x00001403, &m_wfsServiceVersion, &m_wfsSPIVersion, &m_hService);
		if (hRes == WFS_SUCCESS)
		{
			suiservice = m_hService;
			hRes = m_pXFSManagerwrapper->WFSRegister(m_hService, WFS_EXECUTE_EVENT | WFS_USER_EVENT | WFS_SYSTEM_EVENT, m_hWnd);
			LOG_DATA(LOG_DEBUG, "WFSRegister Completed");
			// AutoLock.~CAutoLock();
		   //Blocking(m_eventsystem.m_hObject, WFS_INDEFINITE_WAIT);
			if (bsuistatus == true)
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
DLLAPI_API HRESULT DeviceInformation(LPSTR devicename)
{
	if (strcmp(devicename, "Camera") == 0) { deviceid = 1; }
	else if (strcmp(devicename, "Printer") == 0) { deviceid = 2; }
	else if (strcmp(devicename, "Pinpad") == 0) { deviceid = 3; }
	else if (strcmp(devicename, "Sensor") == 0) { deviceid = 4; }

	switch (deviceid)
	{
	case 1:
	{
		HRESULT hres;
		CString strTxt;
		WFSRESULT* pwfsRes;
		LPWFSCAMSTATUS lpStatus = NULL;
		hres = m_pXFSManagerwrapper->WFSGetInfo(camservice, WFS_INF_CAM_STATUS, NULL, WFS_INDEFINITE_WAIT, &pwfsRes);
		lpStatus = (LPWFSCAMSTATUS)pwfsRes->lpBuffer;
		if (lpStatus != NULL)
		{
			if (lpStatus->fwCameras[2] = 1) camera.camstate = "Good";
			else camera.camstate = "Not Good";

			if (bcamstatus == true) camera.camstatus = "Active";
			else camera.camstatus = "Inactive";

			if (lpStatus->fwMedia[2] == 0) camera.cammedia = "Good";
			else camera.cammedia = "Not Good";
			if (lpStatus->wAntiFraudModule == 0) camera.camfraudmodule = "Not Supported";
		}
		strTxt.Format(L" Device Name : %s\n\Camera Status : %s\n \Camera State  : %s\n \Media State   : %s\n \Pictures Count : %d\n \AntiFraudModule: %s", camera.camname, camera.camstatus, camera.camstate, camera.cammedia, lpStatus->usPictures[1], camera.camfraudmodule);
			MessageBox(NULL, (LPCWSTR)strTxt.GetBuffer(), L"Camera Info", 0);
			return 0;
		}

	case 2:
	{
		HRESULT hRes;
		CString strTxt;
		WFSRESULT* pwfsRes;
		LPWFSPTRSTATUS lpStatus;
		if ((hRes = m_pXFSManagerwrapper->WFSGetInfo(ptrservice, WFS_INF_PTR_STATUS, NULL, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSGetInfo - WFS_INF_PTR_STATUS HRESULT = %d", hRes);
		}
		else
		{
			lpStatus = (LPWFSPTRSTATUS)pwfsRes->lpBuffer;
			if (lpStatus != NULL)
			{
				if (lpStatus->fwMedia == 0) printer.ptrmedia = "GOOD";
				else printer.ptrmedia = "Not Good";
				if (lpStatus->fwPaper[0] == 0) printer.ptrpprstate = "Good";
				else printer.ptrpprstate = "Not Good";
				if (bptrstatus == true) printer.ptrstate = "Active";
				else printer.ptrstate = "Inactive";
				if (lpStatus->wPaperType[0] == 0) printer.ptrpprtype = "Single sided";
			}
			strTxt.Format(L"Device Name   :  %s\n \Printer Status  :   %s\n \Media State     :   Good\n \Paper State     :   Paper Full\n \Paper Type      :   %s\n \ ", printer.ptrname, printer.ptrstate, printer.ptrpprtype);
			MessageBox(NULL, (LPCWSTR)strTxt.GetBuffer(), L"Printer Info", 0);
			return 0;
		}break;

	}
	case 3:
	{
		HRESULT hRes;
		CString strTxt;
		WFSRESULT* pwfsRes = NULL;
		LPWFSPINSTATUS lpStatus = NULL;
		if ((hRes = m_pXFSManagerwrapper->WFSGetInfo(pinservice, WFS_INF_PIN_STATUS, NULL, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSGetInfo WFS_INF_PIN_STATUS HRESULT = %d", hRes);
		}
		else
		{
			lpStatus = (LPWFSPINSTATUS)pwfsRes->lpBuffer;
			strTxt.Format(L"WFSGetInfo - WFS_INF_PIN_STATUS completed\r\n");
		}
		if (lpStatus != NULL)
		{
			strTxt.FormatMessage(L"WFSPINSTATUS::fwDevice = %d \n \
		WFSPINSTATUS::fwEncStat = %d \n \
		WFSPINSTATUS::lpszExtra = %s \n \
		WFSPINSTATUS::fwAutoBeepMode = %d \n \
		WFSPINSTATUS::dwCertificateState = %d \n \
		WFSPINSTATUS::wDevicePosition = %d \n \
		WFSPINSTATUS::usPowerSaveRecoveryTime = %d \n \
		WFSPINSTATUS::wAntiFraudModule = %d \n ",
				lpStatus->fwDevice, lpStatus->fwEncStat, lpStatus->lpszExtra, lpStatus->fwAutoBeepMode, lpStatus->dwCertificateState,
				lpStatus->wDevicePosition, lpStatus->usPowerSaveRecoveryTime, lpStatus->wAntiFraudModule);
		}
		MessageBox(NULL, (LPCWSTR)strTxt.GetBuffer(), L"INFO", 0);
		return 0;
	}

	}

}