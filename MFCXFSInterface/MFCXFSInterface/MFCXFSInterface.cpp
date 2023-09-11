// MFCXFSInterface.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "framework.h"
#include "MFCXFSInterface.h"

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
END_MESSAGE_MAP()


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
messagewnd* m_pWnd;
WFSVERSION m_wfsServiceVersion;
WFSVERSION m_wfsSPIVersion;
HSERVICE m_hService;
HWND m_hWnd=0;
int deviceid;
WFSVERSION  m_wfsXFSManagerVersion;




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
			hres = m_pXFSManagerwrapper->WFSRegister(m_hService, WFS_EXECUTE_EVENT | WFS_USER_EVENT | WFS_SYSTEM_EVENT, m_hWnd);
			LOG_DATA(LOG_DEBUG, "WFSRegister Completed");
			return hres;
		}
		else
		{
			return WFS_ERR_XFSMANAGER_ERROR;
		}
		break;
	}
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
			return hRes;
			//return WFS_SUCCESS;
		}
		else
		{
			return WFS_ERR_XFSMANAGER_ERROR;
		}
		break;
	}
	case 3:
	{
		HRESULT hRes;
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		hRes = m_pXFSManagerwrapper->WFSOpen("ITASPinpad", WFS_DEFAULT_HAPP, "PINSPTest", WFS_TRACE_ALL_SPI,
			WFS_INDEFINITE_WAIT, 0x00001403, &m_wfsServiceVersion, &m_wfsSPIVersion, &m_hService);
		if (hRes == WFS_SUCCESS)
		{
			WFSRESULT* pwfsres;
			hRes = m_pXFSManagerwrapper->WFSRegister(m_hService, WFS_EXECUTE_EVENT | WFS_USER_EVENT | WFS_SYSTEM_EVENT, m_hWnd);
			LOG_DATA(LOG_DEBUG, "WFSRegister Completed");
	//	LPWFSRESULT lpres;

			return hRes;
			
		}
		else
		{
			return WFS_ERR_XFSMANAGER_ERROR;
		}
		break;
	}
	default:
		MessageBox(0, L"Enter Valid Device Type", L"Warning", MB_OK);
		break;
	}
}
