// CSensor.cpp : implementation file
//

#include "pch.h"
#include "DeviceTest.h"
#include "afxdialogex.h"
#include "CSensor.h"
#include "XFSLib/XFSManagerWrapper.h"
#include "XFSADMIN.H"
#include "XFSSIU.H"

// CSensor dialog

IMPLEMENT_DYNAMIC(CSensor, CDialogEx)

CSensor::CSensor(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SIUnitdlg, pParent)
	, m_AsyncCheckVal(FALSE)
{
	m_pXFSManager = XFSManagerWrapper::GetInstance();
}

CSensor::~CSensor()
{
}

void CSensor::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT21, m_stStatus);
	DDX_Check(pDX, IDC_AsyncCheck, m_AsyncCheckVal);
	DDX_Control(pDX, IDC_StartUp, m_btnStartup);
	DDX_Control(pDX, IDC_Open, m_btnOpen);
	DDX_Control(pDX, IDC_Close, m_btnClose);
	DDX_Control(pDX, IDC_SETGUIDE, m_btnGuideLight);
	DDX_Control(pDX, IDC_OPENSHUTTER, m_btnOpenShutter);
	DDX_Control(pDX, IDC_CLOSESHUTTER, m_btnCloseShutter);
	DDX_Control(pDX, IDC_CMDGUIDLIGHT, m_cmbGLight);
	DDX_Control(pDX, IDC_CMB_COMMAND, m_cmbCommand);
	DDX_Control(pDX, IDC_Exit, m_btnExit);
}


BEGIN_MESSAGE_MAP(CSensor, CDialogEx)
	ON_BN_CLICKED(IDC_StartUp, &CSensor::OnBnClickedStartup)
	ON_BN_CLICKED(IDC_Open, &CSensor::OnBnClickedOpen)


	ON_MESSAGE(WFS_OPEN_COMPLETE, &CSensor::OnOpenComplete)
	ON_MESSAGE(WFS_CLOSE_COMPLETE, &CSensor::OnCloseComplete)
	ON_MESSAGE(WFS_LOCK_COMPLETE, &CSensor::OnLockComplete)
	ON_MESSAGE(WFS_UNLOCK_COMPLETE, &CSensor::OnUnlockComplete)
	ON_MESSAGE(WFS_REGISTER_COMPLETE, &CSensor::OnRegisterComplete)
	ON_MESSAGE(WFS_DEREGISTER_COMPLETE, &CSensor::OnDeregisterComplete)
	ON_MESSAGE(WFS_GETINFO_COMPLETE, &CSensor::OnGetInfoComplete)
	ON_MESSAGE(WFS_EXECUTE_COMPLETE, &CSensor::OnExecuteComplete)

	ON_MESSAGE(WFS_TIMER_EVENT, &CSensor::OnTimerEvent)
	ON_MESSAGE(WFS_EXECUTE_EVENT, &CSensor::OnExecuteEvent)
	ON_MESSAGE(WFS_USER_EVENT, &CSensor::OnUserEvent)
	ON_MESSAGE(WFS_SYSTEM_EVENT, &CSensor::OnSystemEvent)
	ON_MESSAGE(WFS_SERVICE_EVENT, &CSensor::OnServiceEvent)


	ON_BN_CLICKED(IDC_SETGUIDE, &CSensor::OnBnClickedSetguide)
	ON_BN_CLICKED(IDC_OPENSHUTTER, &CSensor::OnBnClickedOpenshutter)
	ON_BN_CLICKED(IDC_Close, &CSensor::OnBnClickedClose)
	ON_BN_CLICKED(IDC_CLOSESHUTTER, &CSensor::OnBnClickedCloseshutter)
	ON_BN_CLICKED(IDC_Exit, &CSensor::OnBnClickedExit)
END_MESSAGE_MAP()


// CSensor message handlers
LRESULT CSensor::OnOpenComplete(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT CSensor::OnCloseComplete(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT CSensor::OnLockComplete(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT CSensor::OnUnlockComplete(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT CSensor::OnRegisterComplete(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT CSensor::OnDeregisterComplete(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT CSensor::OnGetInfoComplete(WPARAM wParam, LPARAM lParam)
{
	pwfsRes = (WFSRESULT*)lParam;
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	pwfsRes->lpBuffer = pWESResult;
	return nRes;
}

LRESULT CSensor::OnExecuteComplete(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT CSensor::OnTimerEvent(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT CSensor::OnExecuteEvent(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT CSensor::OnServiceEvent(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	if (pWESResult->u.dwEventID == WFS_SRVE_SIU_PORT_STATUS)
	{
		CString strTxt;
		LPWFSSIUPORTEVENT pPortEvt = (LPWFSSIUPORTEVENT)pWESResult->lpBuffer;
		if (pPortEvt->wPortStatus == WFS_SIU_RUN)
			strTxt.Format(L"Terminal in Run Mode");
		else if (pPortEvt->wPortStatus == WFS_SIU_SUPERVISOR)
			strTxt.Format(L"Terminal in Supervisor Mode");
		else
			strTxt.Format(L"SIU Not available");

		AppendStatus(strTxt);
	}
	return nRes;
}

LRESULT CSensor::OnUserEvent(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT CSensor::OnSystemEvent(WPARAM wParam, LPARAM lParam)
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
			strTxt.Format(L"SIU online");
		else
			strTxt.Format(L"SIU offline");
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

void CSensor::AppendStatus(CString strTxt)
{
	CString txt;
	m_stStatus.GetWindowText(txt);
	txt.Append(_T("\r\n"));
	txt += strTxt;
	m_stStatus.SetWindowText(txt);
}

void CSensor::Lock()
{
	HRESULT hRes;
	CString strTxt;
	WFSRESULT* pwfsRes;
	if ((hRes = m_pXFSManager->WFSLock(m_hService, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSOpen HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"WFSLock completed");
	}
	AppendStatus(strTxt);
}

void CSensor::UnLock()
{
	HRESULT hRes;
	CString strTxt;
	if ((hRes = m_pXFSManager->WFSUnlock(m_hService)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSOpen HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"WFSUnlock completed");
	}
	AppendStatus(strTxt);
}

void CSensor::AsyncLock()
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

void CSensor::AsyncUnLock()
{
	HRESULT hRes;
	CString strTxt;
	if ((hRes = m_pXFSManager->WFSAsyncUnlock(m_hService,m_hWnd,&m_requestId)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSAsyncUnlock HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"WFSAsyncUnlock completed");
	}
	AppendStatus(strTxt);
}

void CSensor::OnBnClickedStartup()
{

	HRESULT hRes;
	CString strTxt;
	if ((hRes = m_pXFSManager->WFSStartUp(0x0001403, &m_wfsXFSManagerVersion)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSStartUp HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"Startup completed");

		m_btnStartup.EnableWindow(FALSE);
		m_btnOpen.EnableWindow(TRUE);
	}
	AppendStatus(strTxt);
}


void CSensor::OnBnClickedOpen()
{
	HRESULT hRes;
	CString strTxt;

	UpdateData(TRUE);
	if (m_AsyncCheckVal == FALSE)
	{
		if ((hRes = m_pXFSManager->WFSOpen("ITASSensorUnit", WFS_DEFAULT_HAPP, "SIUSPTest", WFS_TRACE_ALL_SPI,
			WFS_INDEFINITE_WAIT, 0x00001403, &m_wfsServiceVersion, &m_wfsSPIVersion, &m_hService)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSOpen HRESULT = %d", hRes);
		}
		else
		{
			strTxt.Format(L"WFSOpen completed");
			m_btnOpen.EnableWindow(FALSE);
			m_btnClose.EnableWindow(TRUE);
			m_btnGuideLight.EnableWindow(TRUE);
			m_btnOpenShutter.EnableWindow(TRUE);
			m_btnCloseShutter.EnableWindow(TRUE);
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
		LPWFSSIUCAPS lpCaps;
		if ((hRes = m_pXFSManager->WFSGetInfo(m_hService, WFS_INF_SIU_CAPABILITIES, NULL, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSRegister HRESULT = %d", hRes);
		}
		else
		{
			lpCaps = (LPWFSSIUCAPS)pwfsRes->lpBuffer;
			strTxt.Format(L"WFSGetInfo - WFS_INF_SIU_CAPABILITIES completed\r\n");
		}
		AppendStatus(strTxt);
		//m_pXFSManager->WFMFreeBuffer(pwfsRes);

		pwfsRes = NULL;
		LPWFSSIUSTATUS lpStatus;
		if ((hRes = m_pXFSManager->WFSGetInfo(m_hService, WFS_INF_SIU_STATUS, NULL, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSRegister HRESULT = %d", hRes);
		}
		else
		{
			lpStatus = (LPWFSSIUSTATUS)pwfsRes->lpBuffer;
			strTxt.Format(L"WFSGetInfo - WFS_INF_SIU_STATUS completed\r\n");
		}
		AppendStatus(strTxt);
		//m_pXFSManager->WFMFreeBuffer(pwfsRes);

		UnLock();
	}
	else
	{
		if ((hRes = m_pXFSManager->WFSAsyncOpen("ITASSensorUnit", WFS_DEFAULT_HAPP, "SIUSPTest", WFS_TRACE_ALL_SPI,
			WFS_INDEFINITE_WAIT,&m_hService,m_hWnd, 0x00001403, &m_wfsServiceVersion, &m_wfsSPIVersion, &m_requestId)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSAsyncOpen HRESULT = %d", hRes);
		}
		else
		{
			strTxt.Format(L"WFSOAsyncpen completed");
			m_btnClose.EnableWindow(TRUE);
			m_btnGuideLight.EnableWindow(TRUE);
			m_btnOpenShutter.EnableWindow(TRUE);
			m_btnCloseShutter.EnableWindow(TRUE);
		}
		AppendStatus(strTxt);

		if ((hRes = m_pXFSManager->WFSAsyncRegister(m_hService, WFS_EXECUTE_EVENT | WFS_USER_EVENT | WFS_SYSTEM_EVENT, m_hWnd,m_hWnd,&m_requestId)) != WFS_SUCCESS)
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
		LPWFSSIUCAPS lpCaps;
		if ((hRes = m_pXFSManager->WFSAsyncGetInfo(m_hService, WFS_INF_SIU_CAPABILITIES, NULL, WFS_INDEFINITE_WAIT,m_hWnd,&m_requestId)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSAsyncGetInfo HRESULT = %d", hRes);
		}
		else
		{
			lpCaps = (LPWFSSIUCAPS)pwfsRes->lpBuffer;
			strTxt.Format(L"WFSAsyncGetInfo - WFS_INF_SIU_CAPABILITIES completed\r\n");
		}
		AppendStatus(strTxt);
		//m_pXFSManager->WFMFreeBuffer(pwfsRes);

		pwfsRes = NULL;
		LPWFSSIUSTATUS lpStatus;
		if ((hRes = m_pXFSManager->WFSAsyncGetInfo(m_hService, WFS_INF_SIU_STATUS, NULL, WFS_INDEFINITE_WAIT,m_hWnd,&m_requestId)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSAsyncGetInfo HRESULT = %d", hRes);
		}
		else
		{
			lpStatus = (LPWFSSIUSTATUS)pwfsRes->lpBuffer;
			strTxt.Format(L"WFSAsyncGetInfo - WFS_INF_SIU_STATUS completed\r\n");
		}
		AppendStatus(strTxt);
		//m_pXFSManager->WFMFreeBuffer(pwfsRes);

		AsyncUnLock();
	}
}


void CSensor::OnBnClickedSetguide()
{
	HRESULT hRes;
	CString strTxt;
	WFSSIUSETGUIDLIGHT ipData;

	int gLight = m_cmbGLight.GetCurSel();
	int gCommand = m_cmbCommand.GetCurSel();

	if (gLight == -1)
	{
		MessageBox(L"Select a valid Guide Light");

		m_cmbGLight.SetFocus();
		return;
	}
	if (gCommand == -1)
	{
		MessageBox(L"Select a valid Command");

		m_cmbCommand.SetFocus();
		return;
	}

	if (gLight == 0)
		ipData.wGuidLight = WFS_SIU_NOTESDISPENSER;
	else
		ipData.wGuidLight = WFS_SIU_RECEIPTPRINTER;

	switch (gCommand)
	{
	case 0:
		ipData.fwCommand = WFS_SIU_OFF;
		break;
	case 1:
		ipData.fwCommand = WFS_SIU_ON;
		break;
	case 2:
		ipData.fwCommand = WFS_SIU_SLOW_FLASH;
		break;
	case 3:
		ipData.fwCommand = WFS_SIU_MEDIUM_FLASH;
		break;
	case 4:
		ipData.fwCommand = WFS_SIU_QUICK_FLASH;
		break;
	case 5:
		ipData.fwCommand = WFS_SIU_CONTINUOUS;
		break;
	}
	UpdateData(TRUE);
	if (m_AsyncCheckVal == FALSE)
	{
		Lock();

		WFSRESULT* pwfsRes;
		if ((hRes = m_pXFSManager->WFSExecute(m_hService, WFS_CMD_SIU_SET_GUIDLIGHT, &ipData, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSExecute - WFS_CMD_SIU_SET_GUIDLIGHT HRESULT = %d", hRes);
		}
		else
		{
			strTxt.Format(L"WFSExecute - WFS_CMD_SIU_SET_GUIDLIGHT completed");
		}
		AppendStatus(strTxt);

		UnLock();
	}
	else
	{
		AsyncLock();

		WFSRESULT* pwfsRes;
		if ((hRes = m_pXFSManager->WFSAsyncExecute(m_hService, WFS_CMD_SIU_SET_GUIDLIGHT, &ipData, WFS_INDEFINITE_WAIT,m_hWnd,&m_requestId)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSAsyncExecute - WFS_CMD_SIU_SET_GUIDLIGHT HRESULT = %d", hRes);
		}
		else
		{
			strTxt.Format(L"WFSAsyncExecute - WFS_CMD_SIU_SET_GUIDLIGHT completed");
		}
		AppendStatus(strTxt);

		AsyncUnLock();
	}
}


void CSensor::OnBnClickedOpenshutter()
{

	HRESULT hRes;
	CString strTxt;
	WFSSIUSETPORTS ports = { 0 };
	ports.fwIndicators[WFS_SIU_GENERALOUTPUTPORT] = 0b00000001;
	UpdateData(TRUE);
	if (m_AsyncCheckVal == FALSE)
	{
		Lock();

		WFSRESULT* pwfsRes;
		if ((hRes = m_pXFSManager->WFSExecute(m_hService, WFS_CMD_SIU_SET_PORTS, &ports, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSExecute - WFS_CMD_SIU_SET_PORTS HRESULT = %d", hRes);
		}
		else
		{
			strTxt.Format(L"WFSExecute - WFS_CMD_SIU_SET_PORTS completed");
		}
		AppendStatus(strTxt);

		UnLock();
	}
	else
	{
		AsyncLock();

		WFSRESULT* pwfsRes;
		if ((hRes = m_pXFSManager->WFSAsyncExecute(m_hService, WFS_CMD_SIU_SET_PORTS, &ports, WFS_INDEFINITE_WAIT,m_hWnd,&m_requestId)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSAsyncExecute - WFS_CMD_SIU_SET_PORTS HRESULT = %d", hRes);
		}
		else
		{
			strTxt.Format(L"WFSAsyncExecute - WFS_CMD_SIU_SET_PORTS completed");
		}
		AppendStatus(strTxt);

		AsyncUnLock();
	}
}


void CSensor::OnBnClickedClose()
{
	HRESULT hRes;
	CString strTxt;
	UpdateData(TRUE);
	if (m_AsyncCheckVal == FALSE)
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
			m_btnGuideLight.EnableWindow(FALSE);
			m_btnOpenShutter.EnableWindow(FALSE);
			m_btnCloseShutter.EnableWindow(FALSE);
		}
		AppendStatus(strTxt);
	}
	else
	{
		if ((hRes = m_pXFSManager->WFSAsyncDeregister(m_hService, WFS_EXECUTE_EVENT | WFS_USER_EVENT | WFS_SYSTEM_EVENT, m_hWnd,m_hWnd,&m_requestId)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSAsyncDeregister HRESULT = %d", hRes);
		}
		else
		{
			strTxt.Format(L"WFSAsyncDeregister completed");
		}
		AppendStatus(strTxt);

		if ((hRes = m_pXFSManager->WFSAsyncClose(m_hService,m_hWnd,&m_requestId)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSAsyncClose HRESULT = %d", hRes);
		}
		else
		{
			strTxt.Format(L"WFSAsyncClose completed");
			m_btnOpen.EnableWindow(TRUE);
			m_btnClose.EnableWindow(FALSE);
			m_btnGuideLight.EnableWindow(FALSE);
			m_btnOpenShutter.EnableWindow(FALSE);
			m_btnCloseShutter.EnableWindow(FALSE);
		}
		AppendStatus(strTxt);
	}
}


void CSensor::OnBnClickedCloseshutter()
{
	HRESULT hRes;
	CString strTxt;
	WFSSIUSETPORTS ports = { 0 };
	ports.fwIndicators[WFS_SIU_GENERALOUTPUTPORT] = 0b00000000;
	UpdateData(TRUE);
	if (m_AsyncCheckVal == FALSE)
	{
		Lock();

		WFSRESULT* pwfsRes;
		if ((hRes = m_pXFSManager->WFSExecute(m_hService, WFS_CMD_SIU_SET_PORTS, &ports, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSExecute - WFS_CMD_SIU_SET_PORTS HRESULT = %d", hRes);
		}
		else
		{
			strTxt.Format(L"WFSExecute - WFS_CMD_SIU_SET_PORTS completed");
		}
		AppendStatus(strTxt);

		UnLock();
	}
	else
	{
		AsyncLock();
		WFSRESULT* pwfsRes;
		if ((hRes = m_pXFSManager->WFSAsyncExecute(m_hService, WFS_CMD_SIU_SET_PORTS, &ports, WFS_INDEFINITE_WAIT,m_hWnd,&m_requestId)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSAsyncExecute - WFS_CMD_SIU_SET_PORTS HRESULT = %d", hRes);
		}
		else
		{
			strTxt.Format(L"WFSAsyncExecute - WFS_CMD_SIU_SET_PORTS completed");
		}
		AppendStatus(strTxt);

		AsyncUnLock();
	}
}


void CSensor::OnBnClickedExit()
{
	HRESULT hRes;
	CString strTxt;

	if (GetDlgItem(IDC_Close)->IsWindowEnabled())
	{
		OnClose();
	}
	if (!GetDlgItem(IDC_StartUp)->IsWindowEnabled())
	{
		if ((hRes = m_pXFSManager->WFSCleanUp()) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSCleanUp HRESULT = %d", hRes);
		}
		else
		{
			strTxt.Format(L"WFSCleanUp completed");
		}
		AppendStatus(strTxt);
	}
	OnOK();
}
