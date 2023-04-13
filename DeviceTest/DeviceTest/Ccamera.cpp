// Ccamera.cpp : implementation file
//

#include "pch.h"
#include "DeviceTest.h"
#include "afxdialogex.h"
#include "Ccamera.h"

#include "CAMSPI/CAMSPI.h"

HMODULE hdll;
HSERVICE hService;
HWND m_hWnd;
// Ccamera dialog

IMPLEMENT_DYNAMIC(Ccamera, CDialogEx)

Ccamera::Ccamera(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Camdlg, pParent)
	, m_AsyncCheckVal(FALSE)
{
	m_pXFSManager = XFSManagerWrapper::GetInstance();
}
Ccamera::~Ccamera()
{
}

void Ccamera::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT21, m_RichText);
	DDX_Control(pDX, IDC_CHECK1, m_AsyncCheck);
	DDX_Check(pDX, IDC_CHECK1, m_AsyncCheckVal);
	DDX_Control(pDX, IDC_BUTTON2, m_btnStartup);
	DDX_Control(pDX, IDC_BUTTON1, m_btnOpen);
	DDX_Control(pDX, IDC_BUTTON6, m_btnTakepic);
	DDX_Control(pDX, IDC_TakePicture_Ex, m_btnTakepicEx);
	DDX_Control(pDX, IDC_Reset, m_btnReset);
	DDX_Control(pDX, IDC_BUTTON5, m_btnClose);
}


BEGIN_MESSAGE_MAP(Ccamera, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Ccamera::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_BUTTON2, &Ccamera::OnBnClickedStartup)
	//ON_BN_CLICKED(IDC_BUTTON3, &Ccamera::OnBnClickedAsyncOpen)

	ON_MESSAGE(WFS_OPEN_COMPLETE, &Ccamera::OnOpenComplete)
	ON_MESSAGE(WFS_CLOSE_COMPLETE, &Ccamera::OnCloseComplete)
	ON_MESSAGE(WFS_LOCK_COMPLETE, &Ccamera::OnLockComplete)
	ON_MESSAGE(WFS_UNLOCK_COMPLETE, &Ccamera::OnUnlockComplete)
	ON_MESSAGE(WFS_REGISTER_COMPLETE, &Ccamera::OnRegisterComplete)
	ON_MESSAGE(WFS_DEREGISTER_COMPLETE, &Ccamera::OnDeregisterComplete)
	ON_MESSAGE(WFS_GETINFO_COMPLETE, &Ccamera::OnGetInfoComplete)
	ON_MESSAGE(WFS_EXECUTE_COMPLETE, &Ccamera::OnExecuteComplete)

	ON_MESSAGE(WFS_TIMER_EVENT, &Ccamera::OnTimerEvent)
	ON_MESSAGE(WFS_EXECUTE_EVENT, &Ccamera::OnExecuteEvent)
	ON_MESSAGE(WFS_USER_EVENT, &Ccamera::OnUserEvent)
	ON_MESSAGE(WFS_SYSTEM_EVENT, &Ccamera::OnSystemEvent)
	ON_MESSAGE(WFS_SERVICE_EVENT, &Ccamera::OnServiceEvent)
	ON_MESSAGE(WFS_OPEN_COMPLETE, &Ccamera::OnOpenComplete)


	ON_BN_CLICKED(IDC_BUTTON4, &Ccamera::OnBnClickedCleanUp)
	ON_BN_CLICKED(IDC_BUTTON5, &Ccamera::OnBnClickedClose)
	ON_BN_CLICKED(IDC_BUTTON6, &Ccamera::OnBnClickedTakePicture)
	//ON_BN_CLICKED(IDC_BUTTON7, &Ccamera::OnBnClickedAsyncTakepictureex)
	//ON_BN_CLICKED(IDC_AsyncClose, &Ccamera::OnBnClickedAsyncclose)
	ON_BN_CLICKED(IDC_TakePicture_Ex, &Ccamera::OnBnClickedTakepictureEx)
	//ON_BN_CLICKED(IDC_AsyncTakepicture, &Ccamera::OnBnClickedAsynctakepicture)
	ON_BN_CLICKED(IDC_Reset, &Ccamera::OnBnClickedReset)
	//ON_BN_CLICKED(IDC_Async_Reset, &Ccamera::OnBnClickedAsyncReset)
END_MESSAGE_MAP()



void Ccamera::AppendStatus(CString strTxt)
{
	CString txt;
	m_RichText.GetWindowText(txt);
	txt.Append(_T("\r\n"));
	txt += strTxt;
	m_RichText.SetWindowText(txt);
}

// Ccamera message handlers

LRESULT Ccamera::OnOpenComplete(WPARAM wParam, LPARAM lParam)
{
	CString strTxt;
	strTxt.Format(L"OnOpenComplete Event Received Camera");
	AppendStatus(strTxt);
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}
LRESULT Ccamera::OnCloseComplete(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT Ccamera::OnLockComplete(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT Ccamera::OnUnlockComplete(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT Ccamera::OnRegisterComplete(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT Ccamera::OnDeregisterComplete(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT Ccamera::OnGetInfoComplete(WPARAM wParam, LPARAM lParam)
{
	pwfsres = (WFSRESULT*)lParam;
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;

	pwfsres->lpBuffer = pWESResult;
	return nRes;
}

LRESULT Ccamera::OnExecuteComplete(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT Ccamera::OnTimerEvent(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT Ccamera::OnExecuteEvent(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT Ccamera::OnServiceEvent(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT Ccamera::OnUserEvent(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT Ccamera::OnSystemEvent(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
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
			strTxt.Format(L"Camera online");
		else
			strTxt.Format(L"Camera offline");
		AppendStatus(strTxt);
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


void Ccamera::Lock()
{
	HRESULT hRes;
	CString strTxt;
	WFSRESULT* pwfsRes;
	if ((hRes = m_pXFSManager->WFSLock(m_hService, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSLock HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"WFSLock completed");
	}
	AppendStatus(strTxt);
}


void Ccamera::AsyncLock()
{
	HRESULT hRes;
	CString strTxt;
	WFSRESULT* pwfsRes;
	if ((hRes = m_pXFSManager->WFSAsyncLock(m_hService, WFS_INDEFINITE_WAIT,m_hWnd,&m_requestId)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSAsyncLock HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"WFSAsyncLock completed");
	}
	AppendStatus(strTxt);
}

void Ccamera::UnLock()
{
	HRESULT hRes;
	CString strTxt;
	if ((hRes = m_pXFSManager->WFSUnlock(m_hService)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSUnlock HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"WFSUnlock completed");
	}
	AppendStatus(strTxt);
}


void Ccamera::AsyncUnLock()
{
	HRESULT hRes;
	CString strTxt;
	if ((hRes = m_pXFSManager->WFSAsyncUnlock(m_hService,m_hWnd,&m_requestId) )!= WFS_SUCCESS)
	{
		strTxt.Format(L"WFSAsyncUnlock HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"WFSAsyncUnlock completed");
	}
	AppendStatus(strTxt);
}

void Ccamera::OnBnClickedOpen()
{
	

	HRESULT hRes;
	CString strTxt;

	UpdateData(TRUE);
	if (m_AsyncCheckVal == FALSE)
	{
		if ((hRes = m_pXFSManager->WFSOpen("ITASCamera", WFS_DEFAULT_HAPP, "CAMSPTest", WFS_TRACE_ALL_SPI,
			WFS_INDEFINITE_WAIT, 0x00001403, &m_wfsServiceVersion, &m_wfsSPIVersion, &m_hService)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSOpen HRESULT = %d", hRes);
		}
		else
		{
			strTxt.Format(L"WFSOpen completed");
			m_btnOpen.EnableWindow(FALSE);
			m_btnClose.EnableWindow(TRUE);
			m_btnTakepic.EnableWindow(TRUE);
			m_btnTakepicEx.EnableWindow(TRUE);
			m_btnReset.EnableWindow(TRUE);
		}
		AppendStatus(strTxt);

		if ((hRes = m_pXFSManager->WFSRegister(m_hService, WFS_EXECUTE_EVENT | WFS_USER_EVENT | WFS_SYSTEM_EVENT, m_hWnd)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSRegister HRESULT = %d", hRes);
		}
		else
		{
			strTxt.Format(L"WFSRegister completed");
		}
		AppendStatus(strTxt);

		UnLock();
		Lock();
		WFSRESULT* pwfsRes;
		LPWFSCAMCAPS lpCaps;
		if ((hRes = m_pXFSManager->WFSGetInfo(m_hService, WFS_INF_CAM_CAPABILITIES, NULL, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSGetInfo WFS_INF_CAM_CAPABILITIES HRESULT = %d", hRes);
		}
		else
		{
			lpCaps = (LPWFSCAMCAPS)pwfsRes->lpBuffer;
			strTxt.Format(L"WFSGetInfo - WFS_INF_CAM_CAPABILITIES completed\r\n");
		}
		AppendStatus(strTxt);
		m_pXFSManager->WFMFreeBuffer(pwfsRes);

		pwfsRes = NULL;
		LPWFSCAMSTATUS lpStatus;
		if ((hRes = m_pXFSManager->WFSGetInfo(m_hService, WFS_INF_CAM_STATUS, NULL, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSGetInfo WFS_INF_CAM_STATUS HRESULT = %d", hRes);
		}
		else
		{
			lpStatus = (LPWFSCAMSTATUS)pwfsRes->lpBuffer;
			strTxt.Format(L"WFSGetInfo - WFS_INF_CAM_STATUS completed\r\n");
		}
		AppendStatus(strTxt);
		m_pXFSManager->WFMFreeBuffer(pwfsRes);

		UnLock();

	}
	else
	{
		HRESULT hRes;
		CString strTxt;
		if ((hRes = m_pXFSManager->WFSAsyncOpen("ITASCamera", WFS_DEFAULT_HAPP, "CAMSPTest", WFS_TRACE_ALL_SPI,
			WFS_INDEFINITE_WAIT, &m_hService, m_hWnd, 0x00001403, &m_wfsServiceVersion, &m_wfsSPIVersion, &m_requestId)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSAsyncOpen HRESULT = %d", hRes);
		}
		else
		{
			strTxt.Format(L"WFSAsyncOpen completed");
			m_btnOpen.EnableWindow(FALSE);
			m_btnClose.EnableWindow(TRUE);
			m_btnTakepic.EnableWindow(TRUE);
			m_btnTakepicEx.EnableWindow(TRUE);
			m_btnReset.EnableWindow(TRUE);
		}
		AppendStatus(strTxt);

		if ((hRes = m_pXFSManager->WFSAsyncRegister(m_hService, WFS_EXECUTE_EVENT | WFS_USER_EVENT | WFS_SYSTEM_EVENT, m_hWnd, m_hWnd, &m_requestId)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSAsyncRegister HRESULT = %d", hRes);
		}
		else
		{
			strTxt.Format(L"WFSAsyncRegister completed");
		}
		AppendStatus(strTxt);

		AsyncUnLock();
		AsyncLock();
		LPWFSCAMCAPS lpCaps;
		if ((hRes = m_pXFSManager->WFSAsyncGetInfo(m_hService, WFS_INF_CAM_CAPABILITIES, NULL, WFS_INDEFINITE_WAIT, m_hWnd, &m_requestId)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSAsyncGetInfo WFS_INF_CAM_CAPABILITIES HRESULT = %d", hRes);
		}
		else
		{
			lpCaps = (LPWFSCAMCAPS)pwfsres->lpBuffer;
			strTxt.Format(L"WFSAsyncGetInfo - WFS_INF_CAM_CAPABILITIES completed\r\n");
		}
		AppendStatus(strTxt);
		//m_pXFSManager->WFMFreeBuffer(pwfsRes);

		pwfsres = NULL;
		LPWFSCAMSTATUS lpStatus;
		if ((hRes = m_pXFSManager->WFSAsyncGetInfo(m_hService, WFS_INF_CAM_STATUS, NULL, WFS_INDEFINITE_WAIT, m_hWnd, &m_requestId)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSAsyncGetInfo WFS_INF_CAM_STATUS HRESULT = %d", hRes);
		}
		else
		{
			lpStatus = (LPWFSCAMSTATUS)pwfsres->lpBuffer;
			strTxt.Format(L"WFSAsyncGetInfo - WFS_INF_CAM_STATUS completed\r\n");
		}
		AppendStatus(strTxt);
		m_pXFSManager->WFMFreeBuffer(pwfsres);

		AsyncUnLock();

	}
}


void Ccamera::OnBnClickedStartup()
{
	HRESULT hRes;
	CString strTxt;
	if ((hRes = m_pXFSManager->WFSStartUp(0x1403, &m_wfsXFSManagerVersion)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSStartUp HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"Camera   Startup completed ");
		m_btnStartup.EnableWindow(FALSE);
		m_btnOpen.EnableWindow(TRUE);
	}
	AppendStatus(strTxt);
}


/*void Ccamera::OnBnClickedAsyncOpen()
{


	HRESULT hRes;
	CString strTxt;
	if ((hRes = m_pXFSManager->WFSAsyncOpen("ITASCamera", WFS_DEFAULT_HAPP, "CAMSPTest", WFS_TRACE_ALL_SPI,
		WFS_INDEFINITE_WAIT,&m_hService,m_hWnd, 0x00001403, &m_wfsServiceVersion, &m_wfsSPIVersion,&m_requestId)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSAsyncOpen HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"WFSAsyncOpen completed");
	}
	AppendStatus(strTxt);

	if ((hRes = m_pXFSManager->WFSAsyncRegister(m_hService, WFS_EXECUTE_EVENT | WFS_USER_EVENT | WFS_SYSTEM_EVENT,m_hWnd,m_hWnd,&m_requestId)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSAsyncRegister HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"WFSAsyncRegister completed");
	}
	AppendStatus(strTxt);

	AsyncUnLock();
	AsyncLock();
	LPWFSCAMCAPS lpCaps;
	if ((hRes = m_pXFSManager->WFSAsyncGetInfo(m_hService, WFS_INF_CAM_CAPABILITIES, NULL, WFS_INDEFINITE_WAIT,m_hWnd,&m_requestId)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSAsyncGetInfo WFS_INF_CAM_CAPABILITIES HRESULT = %d", hRes);
	}
	else
	{
		lpCaps = (LPWFSCAMCAPS)pwfsres->lpBuffer;
		strTxt.Format(L"WFSAsyncGetInfo - WFS_INF_CAM_CAPABILITIES completed\r\n");
	}
	AppendStatus(strTxt);
	//m_pXFSManager->WFMFreeBuffer(pwfsRes);

	pwfsres = NULL;
	LPWFSCAMSTATUS lpStatus;
	if ((hRes = m_pXFSManager->WFSAsyncGetInfo(m_hService, WFS_INF_CAM_STATUS, NULL, WFS_INDEFINITE_WAIT,m_hWnd,&m_requestId)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSAsyncGetInfo WFS_INF_CAM_STATUS HRESULT = %d", hRes);
	}
	else
	{
		lpStatus = (LPWFSCAMSTATUS)pwfsres->lpBuffer;
		strTxt.Format(L"WFSAsyncGetInfo - WFS_INF_CAM_STATUS completed\r\n");
	}
	AppendStatus(strTxt);
	//m_pXFSManager->WFMFreeBuffer(pwfsRes);

	AsyncUnLock();
}*/


void Ccamera::OnBnClickedCleanUp()
{
	HRESULT hRes;
	CString strTxt;
	if ((hRes = m_pXFSManager->WFSCleanUp()) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSCleanUp HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"WFSCleanUp completed");
		m_btnStartup.EnableWindow(TRUE);
		m_btnOpen.EnableWindow(FALSE);
	}
	AppendStatus(strTxt);
}
	


void Ccamera::OnBnClickedClose()
{	
	HRESULT hRes;
	CString strTxt;
	UpdateData(TRUE);
	if(m_AsyncCheckVal == FALSE)
	{
		if ((hRes = m_pXFSManager->WFSDeregister(m_hService, WFS_EXECUTE_EVENT | WFS_USER_EVENT | WFS_SYSTEM_EVENT, m_hWnd)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSDeregister HRESULT = %d", hRes);
		}
		else
		{
			strTxt.Format(L"WFSDeregister completed");
		}
		AppendStatus(strTxt);

		if ((hRes = m_pXFSManager->WFSClose(m_hService)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSClose HRESULT = %d", hRes);
		}
		else
		{
			strTxt.Format(L"WFSClose completed");
			m_btnOpen.EnableWindow(TRUE);
			m_btnClose.EnableWindow(FALSE);
			m_btnTakepic.EnableWindow(FALSE);
			m_btnTakepicEx.EnableWindow(FALSE);
			m_btnReset.EnableWindow(FALSE);
		}
		AppendStatus(strTxt);
	}
	else
	{
		HRESULT hRes;
		CString strTxt;

		if ((hRes = m_pXFSManager->WFSAsyncDeregister(m_hService, WFS_EXECUTE_EVENT | WFS_USER_EVENT | WFS_SYSTEM_EVENT, m_hWnd, m_hWnd, &m_requestId)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSAsyncDeregister HRESULT = %d", hRes);
		}
		else
		{
			strTxt.Format(L"WFSAsyncDeregister completed");
		}
		AppendStatus(strTxt);

		if ((hRes = m_pXFSManager->WFSAsyncClose(m_hService, m_hWnd, &m_requestId)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSAsyncClose HRESULT = %d", hRes);
		}
		else
		{
			strTxt.Format(L"WFSAsyncClose completed");
		}
		AppendStatus(strTxt);
	}
}



void Ccamera::OnBnClickedTakePicture()
{
	HRESULT hRes;
	CString strTxt;
	WFSCAMTAKEPICT ipData;
	ipData.wCamera = WFS_CAM_PERSON;
	ipData.lpszCamData = "Test Data from takepicture";
	ipData.lpszUNICODECamData = NULL;
	UpdateData(TRUE); // for checkbox enable and disable
	if (m_AsyncCheckVal == FALSE)
	{
		Lock();

		WFSRESULT* pwfsRes;
		if ((hRes = m_pXFSManager->WFSExecute(m_hService, WFS_CMD_CAM_TAKE_PICTURE, &ipData, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSExecute HRESULT = %d", hRes);
		}
		else
		{
			strTxt.Format(L"WFSExecute - WFS_CMD_CAM_TAKE_PICTURE completed");
		}
		AppendStatus(strTxt);

		UnLock();
	}
	else
	{
		HRESULT hRes;
		CString strTxt;
		WFSCAMTAKEPICT ipData;
		ipData.wCamera = WFS_CAM_PERSON;
		ipData.lpszCamData = "Test Data from Async_takepicture";
		ipData.lpszUNICODECamData = NULL;

		AsyncLock();

		WFSRESULT* pwfsRes;
		if ((hRes = m_pXFSManager->WFSAsyncExecute(m_hService, WFS_CMD_CAM_TAKE_PICTURE, &ipData, WFS_INDEFINITE_WAIT, m_hWnd, &m_requestId)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSAsyncExecute HRESULT = %d", hRes);
		}
		else
		{
			strTxt.Format(L"WFSAsyncExecute - WFS_CMD_CAM_TAKE_PICTURE completed");
		}
		AppendStatus(strTxt);

		AsyncUnLock();
	}
}


/*void Ccamera::OnBnClickedAsyncTakepictureex()
{
	HRESULT hRes;
	CString strTxt;
	WFSCAMTAKEPICTEX ipData;
	ipData.wCamera = WFS_CAM_PERSON;
	ipData.lpszCamData = "Test Data from Asynctakepictureex";
	ipData.lpszUNICODECamData = NULL;
	ipData.lpszPictureFile = NULL;

	AsyncLock();

	WFSRESULT* pwfsRes;
	if ((hRes = m_pXFSManager->WFSAsyncExecute(m_hService, WFS_CMD_CAM_TAKE_PICTURE_EX, &ipData, WFS_INDEFINITE_WAIT,m_hWnd,&m_requestId)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSAsyncExecute HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"WFSAsyncExecute - WFS_CMD_CAM_TAKE_PICTURE_EX completed");
	}
	AppendStatus(strTxt);

	AsyncUnLock();	
}*/

void Ccamera::OnBnClickedTakepictureEx()
{
	HRESULT hRes;
	CString strTxt;
	WFSCAMTAKEPICTEX ipData;
	ipData.wCamera = WFS_CAM_PERSON;
	ipData.lpszCamData = "Test Data from takepicture ex";
	ipData.lpszUNICODECamData = NULL;
	ipData.lpszPictureFile = NULL;
	UpdateData(TRUE);
	if (m_AsyncCheckVal == FALSE)
	{
		Lock();

		WFSRESULT* pwfsRes;
		if ((hRes = m_pXFSManager->WFSExecute(m_hService, WFS_CMD_CAM_TAKE_PICTURE_EX, &ipData, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSExecute HRESULT = %d", hRes);
		}
		else
		{
			strTxt.Format(L"WFSExecute - WFS_CMD_CAM_TAKE_PICTURE_EX completed");
		}
		AppendStatus(strTxt);

		UnLock();

	}
	else
	{

		AsyncLock();

		WFSRESULT* pwfsRes;
		if ((hRes = m_pXFSManager->WFSAsyncExecute(m_hService, WFS_CMD_CAM_TAKE_PICTURE_EX, &ipData, WFS_INDEFINITE_WAIT, m_hWnd, &m_requestId)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSAsyncExecute HRESULT = %d", hRes);
		}
		else
		{
			strTxt.Format(L"WFSAsyncExecute - WFS_CMD_CAM_TAKE_PICTURE_EX completed");
		}
		AppendStatus(strTxt);

		AsyncUnLock();

	}
}


/*void Ccamera::OnBnClickedAsynctakepicture()
{
	HRESULT hRes;
	CString strTxt;
	WFSCAMTAKEPICT ipData;
	ipData.wCamera = WFS_CAM_PERSON;
	ipData.lpszCamData = "Test Data from Async_takepicture";
	ipData.lpszUNICODECamData = NULL;

	AsyncLock();

	WFSRESULT* pwfsRes;
	if ((hRes = m_pXFSManager->WFSAsyncExecute(m_hService, WFS_CMD_CAM_TAKE_PICTURE, &ipData, WFS_INDEFINITE_WAIT, m_hWnd, &m_requestId)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSAsyncExecute HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"WFSAsyncExecute - WFS_CMD_CAM_TAKE_PICTURE completed");
	}
	AppendStatus(strTxt);

	AsyncUnLock();

}*/


void Ccamera::OnBnClickedReset()
{
	HRESULT hRes;
	CString strTxt;
	WFSCAMTAKEPICTEX ipData;
	UpdateData(TRUE);
	if (m_AsyncCheckVal == FALSE)
	{

		Lock();
		WFSRESULT* pwfsRes;
		if ((hRes = m_pXFSManager->WFSExecute(m_hService, WFS_CMD_CAM_RESET, &ipData, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSExecute_Reset HRESULT = %d", hRes);
		}
		else
		{
			strTxt.Format(L"WFSExecute_Reset -WFS_CMD_CAM_RESET completed");
		}
		AppendStatus(strTxt);

		UnLock();

	}
	else
	{
		HRESULT hRes;
		CString strTxt;
		WFSCAMTAKEPICTEX ipData;
		AsyncLock();

		WFSRESULT* pwfsRes;
		if ((hRes = m_pXFSManager->WFSAsyncExecute(m_hService, WFS_CMD_CAM_RESET, &ipData, WFS_INDEFINITE_WAIT, m_hWnd, &m_requestId)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSAsyncExecute_Reset HRESULT = %d", hRes);
		}
		else
		{
			strTxt.Format(L"WFSAsyncExecute_Reset -WFS_CMD_CAM_RESET completed");
		}
		AppendStatus(strTxt);

		AsyncUnLock();

	}

}


/*void Ccamera::OnBnClickedAsyncReset()
{
	HRESULT hRes;
	CString strTxt;
	WFSCAMTAKEPICTEX ipData;
	AsyncLock();

	WFSRESULT* pwfsRes;
	if ((hRes = m_pXFSManager->WFSAsyncExecute(m_hService, WFS_CMD_CAM_RESET, &ipData, WFS_INDEFINITE_WAIT,m_hWnd,&m_requestId)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSAsyncExecute_Reset HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"WFSAsyncExecute_Reset -WFS_CMD_CAM_RESET completed");
	}
	AppendStatus(strTxt);

	AsyncUnLock();

}*/

/*void Ccamera::OnBnClickedAsyncclose()
{
	HRESULT hRes;
	CString strTxt;

	if ((hRes = m_pXFSManager->WFSAsyncDeregister(m_hService, WFS_EXECUTE_EVENT | WFS_USER_EVENT | WFS_SYSTEM_EVENT, m_hWnd, m_hWnd, &m_requestId)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSAsyncDeregister HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"WFSAsyncDeregister completed");
	}
	AppendStatus(strTxt);

	if ((hRes = m_pXFSManager->WFSAsyncClose(m_hService, m_hWnd, &m_requestId)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSAsyncClose HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"WFSAsyncClose completed");
	}
	AppendStatus(strTxt);
}*/