
// MyMFC.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "MyMFC.h"
#include "MyMFCDlg.h"
#include<Dbt.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMyMFCApp
DEV_BROADCAST_DEVICEINTERFACE   broadcastInterface;
GUID usbDevice = { 0xA5DCBF10L, 0x6530, 0x11D2, 0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED };
HANDLE hnotifydev;


BEGIN_MESSAGE_MAP(CMyMFCApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

// CMyMFCApp construction
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_DEVICECHANGE)
	{
		if (DBT_DEVICEARRIVAL == wParam)
		{
			MessageBox(NULL, TEXT("WM_DEVICECHANGE - Device Arrived"), TEXT("WndProc Message"), MB_OK);
		}

		if (DBT_DEVICEREMOVECOMPLETE == wParam)
		{
			MessageBox(NULL, TEXT("WM_DEVICECHANGE - Device removed"), TEXT("WndProc Message"), MB_OK);
		}
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

DWORD WINAPI CreateHiddenWindowAndRegisterForUSBEvents(LPVOID lpThreadParameter)
{
	HINSTANCE hInstance = reinterpret_cast<HINSTANCE>(GetModuleHandle(NULL));
	WNDCLASSEX  windowClass = { 0 };		//window class
	HWND		hwnd;				//window handle
	MSG			msg;



	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WndProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = 0;
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = L"USBtestclass";
	windowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);



	if (!RegisterClassEx(&windowClass))
	{
		MessageBox(NULL, TEXT("register class failed"), TEXT("WndProc"), MB_OK);
		return 0;
	}
	else
	{
		//MessageBox(NULL, TEXT("register class success"), TEXT("WndProc"), MB_OK);
	}
	hwnd = CreateWindowEx(NULL,		//extended style
		L"USBtestclass",			//class name
		L"USBtestclassApp",		//app name
		WS_OVERLAPPEDWINDOW |		//window style
		//WS_VISIBLE |
		WS_SYSMENU,
		0, 0,			//x/y coords
		0, 0,			//width,height
		NULL,			//handle to parent
		NULL,			//handle to menu
		0,				//application instance
		NULL);			//no extra parameter's

	if (hwnd == NULL)
	{
		MessageBox(NULL, TEXT("create window failed"), TEXT("WndProc"), MB_OK);

	}
	else
	{
	//	MessageBox(NULL, TEXT("create window success"), TEXT("WndProc"), MB_OK);
	}
	broadcastInterface.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
	broadcastInterface.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;

	broadcastInterface.dbcc_classguid = usbDevice;

	//Th->m_hWnd = hwnd;

	hnotifydev = RegisterDeviceNotification(hwnd, &broadcastInterface, DEVICE_NOTIFY_WINDOW_HANDLE);
	if (hnotifydev == NULL)
	{
		MessageBox(NULL, TEXT("register notify failed"), TEXT("WndProc"), MB_OK);
	}
	else
	{
		//MessageBox(NULL, TEXT("register notify success"), TEXT("WndProc"), MB_OK);
		while (GetMessage(&msg, NULL, 0, 0) > 0)
		{
			
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.message;
}


CMyMFCApp::CMyMFCApp()
{

	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
	HSERVICE hService= 1;
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMyMFCApp object

CMyMFCApp theApp;


// CMyMFCApp initialization

BOOL CMyMFCApp::InitInstance()
{
	LPVOID lpThreadParameter = NULL;
	


	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
	
	/*HANDLE hmutex = CreateMutex(NULL, FALSE, L"MYMFC");
	if (hmutex == NULL)
	{
		return FALSE;
	}
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		MessageBox(NULL, L"Program already Running", L"HELLO", MB_ICONINFORMATION);
		return FALSE;
	}*/
	
	AfxEnableControlContainer();
	AfxInitRichEdit2();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	CMyMFCDlg dlg;
	m_pMainWnd = &dlg;
	


	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}
	
	

	// Delete the shell manager created above.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}
	
#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
	
}

