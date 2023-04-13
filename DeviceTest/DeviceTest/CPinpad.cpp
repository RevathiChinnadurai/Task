// CPinpad.cpp : implementation file
//

#include "pch.h"
#include "DeviceTest.h"
#include "afxdialogex.h"
#include "CPinpad.h"
#include "XFSPIN.H"
#include "XFSADMIN.H"

// CPinpad dialog

IMPLEMENT_DYNAMIC(CPinpad, CDialogEx)

CPinpad::CPinpad(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Pinpaddlg, pParent)
	, m_AsyncCheckVal(FALSE)
{

}

CPinpad::~CPinpad()
{
}

void CPinpad::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDT_INFOCMD_INPUT, m_edtInfoInput);
	DDX_Control(pDX, IDC_EDT_INPUT, m_edtKeyInput);
	DDX_Control(pDX, IDC_EDT_KEYNAME, m_edtkeyName);
	DDX_Control(pDX, IDC_RICHEDIT22, m_stStatus);
	DDX_Check(pDX, IDC_CHECK1, m_AsyncCheckVal);
	DDX_Text(pDX, IDC_EDT_INFOCMD_INPUT, m_edtInfoInput1);
	DDX_Control(pDX, IDC_StartUp, m_btnStartup);
	DDX_Control(pDX, IDC_Open, m_btnopen);
	DDX_Control(pDX, IDC_Close, m_btnclose);
	DDX_Control(pDX, IDC_GET_STATUS, m_btngetstatus);
	DDX_Control(pDX, IDC_GET_CAPS, m_btngetcaps);
	DDX_Control(pDX, IDC_GET_KEY_DETAILS, m_btnkeydetails);
	DDX_Control(pDX, IDC_GET_KEY_DETAILS_EX, m_btnkeydetailsex);
	DDX_Control(pDX, IDC_GET_FUNC_KEY, m_btnfunkey);
	DDX_Control(pDX, IDC_GET_HSM, m_btnhsm);
	DDX_Control(pDX, IDC_GET_SEC_KEY, m_btnsecurekey);
	DDX_Control(pDX, IDC_GET_DEV_ID, m_btndeviceid);
	DDX_Control(pDX, IDC_LOADKEY, m_btnloadkey);
	DDX_Control(pDX, IDC_DELETEKEY, m_btndeletekey);
	DDX_Control(pDX, IDC_GETPIN, m_btnGetpin);
	DDX_Control(pDX, IDC_CRYPTDATA, m_btnCryptdata);
}


BEGIN_MESSAGE_MAP(CPinpad, CDialogEx)
	ON_BN_CLICKED(IDC_StartUp, &CPinpad::OnBnClickedStartup)
	ON_BN_CLICKED(IDC_Open, &CPinpad::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_Close, &CPinpad::OnBnClickedClose)
	ON_BN_CLICKED(IDC_Exit, &CPinpad::OnBnClickedExit)
	ON_BN_CLICKED(IDC_GET_STATUS, &CPinpad::OnBnClickedGetStatus)
	ON_BN_CLICKED(IDC_Clear, &CPinpad::OnBnClickedClear)
	ON_BN_CLICKED(IDC_GET_CAPS, &CPinpad::OnBnClickedGetCaps)
	ON_BN_CLICKED(IDC_GET_KEY_DETAILS, &CPinpad::OnBnClickedGetKeyDetails)
	ON_BN_CLICKED(IDC_GET_KEY_DETAILS_EX, &CPinpad::OnBnClickedGetKeyDetailsEx)
	ON_BN_CLICKED(IDC_GET_FUNC_KEY, &CPinpad::OnBnClickedGetFuncKey)
	ON_BN_CLICKED(IDC_GET_HSM, &CPinpad::OnBnClickedGetHsm)
	ON_BN_CLICKED(IDC_GET_SEC_KEY, &CPinpad::OnBnClickedGetSecKey)
	ON_BN_CLICKED(IDC_GET_DEV_ID, &CPinpad::OnBnClickedGetDevId)
	ON_BN_CLICKED(IDC_LOADKEY, &CPinpad::OnBnClickedLoadkey)
	ON_BN_CLICKED(IDC_DELETEKEY, &CPinpad::OnBnClickedDeletekey)
	ON_BN_CLICKED(IDC_GETPIN, &CPinpad::OnBnClickedGetpin)
	ON_BN_CLICKED(IDC_CRYPTDATA, &CPinpad::OnBnClickedCryptdata)

	ON_MESSAGE(WFS_OPEN_COMPLETE, &CPinpad::OnOpenComplete)
	ON_MESSAGE(WFS_CLOSE_COMPLETE, &CPinpad::OnCloseComplete)
	ON_MESSAGE(WFS_LOCK_COMPLETE, &CPinpad::OnLockComplete)
	ON_MESSAGE(WFS_UNLOCK_COMPLETE, &CPinpad::OnUnlockComplete)
	ON_MESSAGE(WFS_REGISTER_COMPLETE, &CPinpad::OnRegisterComplete)
	ON_MESSAGE(WFS_DEREGISTER_COMPLETE, &CPinpad::OnDeregisterComplete)
	ON_MESSAGE(WFS_GETINFO_COMPLETE, &CPinpad::OnGetInfoComplete)
	ON_MESSAGE(WFS_EXECUTE_COMPLETE, &CPinpad::OnExecuteComplete)

	ON_MESSAGE(WFS_TIMER_EVENT, &CPinpad::OnTimerEvent)
	ON_MESSAGE(WFS_EXECUTE_EVENT, &CPinpad::OnExecuteEvent)
	ON_MESSAGE(WFS_USER_EVENT, &CPinpad::OnUserEvent)
	ON_MESSAGE(WFS_SYSTEM_EVENT, &CPinpad::OnSystemEvent)
	ON_MESSAGE(WFS_SERVICE_EVENT, &CPinpad::OnServiceEvent)

END_MESSAGE_MAP()

UINT GetPINThread(LPVOID wParam)
{
	CPinpad* pHandler = (CPinpad*)wParam;

	HRESULT hRes;
	CString str, strTxt;
	pHandler->Lock();
	WFSRESULT* pwfsRes;
	WFSPINGETDATA in;
	LPWFSPINDATA lpPinData;
	in.bAutoEnd = true;
	in.usMaxLen = 4;
	in.ulTerminateFDKs = 0;
	in.ulTerminateKeys = 0;
	in.ulActiveFDKs = 0;
	in.ulActiveKeys = 0;

	REQUESTID reqID;
	if ((hRes = pHandler->m_pXFSManager->WFSAsyncExecute(pHandler->m_hService, WFS_CMD_PIN_GET_DATA, &in, INFINITE, pHandler->m_hWnd, &reqID)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSExecute WFS_CMD_PIN_GET_DATA HRESULT = %d", hRes);
	}
	else
	{
		//lpPinData = (LPWFSPINDATA)pwfsRes->lpBuffer;
		strTxt.Format(L"WFSExecute - WFS_CMD_PIN_GET_DATA completed\r\n");
	}
	pHandler->AppendStatus(strTxt);
	//	pHandler->m_pXFSManager->WFMFreeBuffer(pwfsRes);
	pHandler->UnLock();
	return 0;
}
// CPinpad message handlers

LRESULT CPinpad::OnOpenComplete(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT CPinpad::OnCloseComplete(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT CPinpad::OnLockComplete(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT CPinpad::OnUnlockComplete(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT CPinpad::OnRegisterComplete(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT CPinpad::OnDeregisterComplete(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT CPinpad::OnGetInfoComplete(WPARAM wParam, LPARAM lParam)
{
	pwfsRes = (WFSRESULT*)lParam;
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	pwfsRes->lpBuffer = pWESResult;
	//m_pXFSManager->WFSFreeResult(pWESResult);
	return nRes;
}

LRESULT CPinpad::OnExecuteComplete(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT CPinpad::OnTimerEvent(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT CPinpad::OnExecuteEvent(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	CString strKey;
	switch (pWESResult->u.dwEventID)
	{
	case WFS_EXEE_PIN_ENTERDATA:
	{
		AppendStatus(L"EPP ready for PIN Entry");
		m_edtkeyName.SetWindowText(L"");
	}
	break;
	case WFS_EXEE_PIN_KEY:
	{
		LPWFSPINKEY pKey = (LPWFSPINKEY)pWESResult->lpBuffer;
		if (pKey->wCompletion == WFS_PIN_COMPAUTO)
		{
			AppendStatus(L"Auto end");
		}
		else
		{
			switch (pKey->ulDigit)
			{
			case  WFS_PIN_FK_0:AppendPIN(L"0"); break;
			case  WFS_PIN_FK_1:AppendPIN(L"1"); break;
			case  WFS_PIN_FK_2:AppendPIN(L"2"); break;
			case  WFS_PIN_FK_3:AppendPIN(L"3"); break;
			case  WFS_PIN_FK_4:AppendPIN(L"4"); break;
			case  WFS_PIN_FK_5:AppendPIN(L"5"); break;
			case  WFS_PIN_FK_6:AppendPIN(L"6"); break;
			case  WFS_PIN_FK_7:AppendPIN(L"7"); break;
			case  WFS_PIN_FK_8:AppendPIN(L"8"); break;
			case  WFS_PIN_FK_9:AppendPIN(L"9"); break;
			case  WFS_PIN_FK_ENTER:AppendStatus(L"[ENTER] pressed"); break;
			case  WFS_PIN_FK_CANCEL:AppendStatus(L"[CANCEL] pressed"); break;
			case  WFS_PIN_FK_CLEAR:AppendStatus(L"[CLEAR] pressed"); break;
			case  WFS_PIN_FK_BACKSPACE:AppendStatus(L"[BACKSPACE] pressed"); break;
			}
		}
	}
	break;
	}

	return nRes;
}

LRESULT CPinpad::OnServiceEvent(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT CPinpad::OnUserEvent(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT CPinpad::OnSystemEvent(WPARAM wParam, LPARAM lParam)
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
			strTxt.Format(L"Pinpad online");
		else
			strTxt.Format(L"Pinpad offline");
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

void CPinpad::AppendStatus(CString strTxt)
{
	CString txt;
	m_stStatus.GetWindowText(txt);
	txt.Append(_T("\r\n"));
	txt += strTxt;
	m_stStatus.SetWindowText(txt);
	Invalidate(TRUE);
	//UpdateData();
}

void CPinpad::AppendPIN(CString strTxt)
{
	CString txt;
	m_edtkeyName.GetWindowText(txt);
	txt.Append(_T("\r\n"));
	txt += strTxt;
	m_edtkeyName.SetWindowText(txt);
}

void CPinpad::OnBnClickedStartup()
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
		m_btnopen.EnableWindow(TRUE);


	}
	AppendStatus(strTxt);
}

void CPinpad::UnLock()
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

void CPinpad::Lock()
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

void CPinpad::AsyncUnLock()
{
	HRESULT hRes;
	CString strTxt;
	if ((hRes = m_pXFSManager->WFSAsyncUnlock(m_hService,m_hWnd,&m_requestId)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSUnlock HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"WFSUnlock completed");
	}
	AppendStatus(strTxt);
}

void CPinpad::AsyncLock()
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
void CPinpad::OnBnClickedOpen()
{
	HRESULT hRes;
	CString strTxt;
	UpdateData(TRUE);
	if (m_AsyncCheckVal == FALSE)
	{

		if ((hRes = m_pXFSManager->WFSOpen("ITASPinpad", WFS_DEFAULT_HAPP, "PINSPTest", WFS_TRACE_ALL_SPI,
			WFS_INDEFINITE_WAIT, 0x00001403, &m_wfsServiceVersion, &m_wfsSPIVersion, &m_hService)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSOpen HRESULT = %d", hRes);
		}
		else
		{
			strTxt.Format(L"WFSOpen completed");
			m_btnStartup.EnableWindow(FALSE);
			m_btnclose.EnableWindow(TRUE);
			m_btnhsm.EnableWindow(TRUE);
			m_btndeletekey.EnableWindow(TRUE);
			m_btnCryptdata.EnableWindow(TRUE);
			m_btndeviceid.EnableWindow(TRUE);
			m_btnfunkey.EnableWindow(TRUE);
			m_btngetcaps.EnableWindow(TRUE);
			m_btnGetpin.EnableWindow(TRUE);
			m_btngetstatus.EnableWindow(TRUE);
			m_btnkeydetails.EnableWindow(TRUE);
			m_btnkeydetailsex.EnableWindow(TRUE);
			m_btnloadkey.EnableWindow(TRUE);
			m_btnsecurekey.EnableWindow(TRUE);

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
	}
	else
	{
		if ((hRes = m_pXFSManager->WFSAsyncOpen("ITASPinpad", WFS_DEFAULT_HAPP, "PINSPTest", WFS_TRACE_ALL_SPI,
			WFS_INDEFINITE_WAIT,&m_hService,m_hWnd, 0x00001403, &m_wfsServiceVersion, &m_wfsSPIVersion, &m_requestId)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSAsyncOpen HRESULT = %d", hRes);
		}
		else
		{
			strTxt.Format(L"WFSAsyncOpen completed");
			m_btnStartup.EnableWindow(FALSE);
			m_btnclose.EnableWindow(TRUE);
			m_btnhsm.EnableWindow(TRUE);
			m_btndeletekey.EnableWindow(TRUE);
			m_btnCryptdata.EnableWindow(TRUE);
			m_btndeviceid.EnableWindow(TRUE);
			m_btnfunkey.EnableWindow(TRUE);
			m_btngetcaps.EnableWindow(TRUE);
			m_btnGetpin.EnableWindow(TRUE);
			m_btngetstatus.EnableWindow(TRUE);
			m_btnkeydetails.EnableWindow(TRUE);
			m_btnkeydetailsex.EnableWindow(TRUE);
			m_btnloadkey.EnableWindow(TRUE);
			m_btnsecurekey.EnableWindow(TRUE);
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
	}
}


void CPinpad::OnBnClickedClose()
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
	
			m_btnStartup.EnableWindow(TRUE);
			m_btnopen.EnableWindow(TRUE);
			m_btnclose.EnableWindow(FALSE);
			m_btnhsm.EnableWindow(FALSE);
            m_btndeletekey.EnableWindow(FALSE);
            m_btnCryptdata.EnableWindow(FALSE);
			m_btndeviceid.EnableWindow(FALSE);
			m_btnfunkey.EnableWindow(FALSE);
			m_btngetcaps.EnableWindow(FALSE);
			m_btnGetpin.EnableWindow(FALSE);
	        m_btngetstatus.EnableWindow(FALSE);
			m_btnkeydetails.EnableWindow(FALSE);
		    m_btnkeydetailsex.EnableWindow(FALSE);
			m_btnloadkey.EnableWindow(FALSE);
			m_btnsecurekey.EnableWindow(FALSE);
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
			m_btnStartup.EnableWindow(TRUE);
			m_btnopen.EnableWindow(TRUE);
			m_btnclose.EnableWindow(FALSE);
			m_btnhsm.EnableWindow(FALSE);
			m_btndeletekey.EnableWindow(FALSE);
			m_btnCryptdata.EnableWindow(FALSE);
			m_btndeviceid.EnableWindow(FALSE);
			m_btnfunkey.EnableWindow(FALSE);
			m_btngetcaps.EnableWindow(FALSE);
			m_btnGetpin.EnableWindow(FALSE);
			m_btngetstatus.EnableWindow(FALSE);
			m_btnkeydetails.EnableWindow(FALSE);
			m_btnkeydetailsex.EnableWindow(FALSE);
			m_btnloadkey.EnableWindow(FALSE);
			m_btnsecurekey.EnableWindow(FALSE);
		}
		AppendStatus(strTxt);
	}

}


void CPinpad::OnBnClickedExit()
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
	}
	AppendStatus(strTxt);
	OnOK();
}


void CPinpad::OnBnClickedGetStatus()
{
	HRESULT hRes;
	CString strTxt;
	UpdateData(TRUE);
	if (m_AsyncCheckVal == FALSE)
	{
		Lock();
		LPWFSPINSTATUS lpStatus = NULL;
		if ((hRes = m_pXFSManager->WFSGetInfo(m_hService, WFS_INF_PIN_STATUS, NULL, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSGetInfo WFS_INF_PIN_STATUS HRESULT = %d", hRes);
		}
		else
		{
			lpStatus = (LPWFSPINSTATUS)pwfsRes->lpBuffer;
			strTxt.Format(L"WFSGetInfo - WFS_INF_PIN_STATUS completed\r\n");
		}
		AppendStatus(strTxt);
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
			AppendStatus(strTxt);
		}
		m_pXFSManager->WFMFreeBuffer(pwfsRes);

		UnLock();
	}
	else
	{
		AsyncLock();
		LPWFSPINSTATUS lpStatus = NULL;
		if ((hRes = m_pXFSManager->WFSAsyncGetInfo(m_hService, WFS_INF_PIN_STATUS, NULL, WFS_INDEFINITE_WAIT,m_hWnd, &m_requestId)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSAsyncGetInfo WFS_INF_PIN_STATUS HRESULT = %d", hRes);
		}
		else
		{
			lpStatus = (LPWFSPINSTATUS)pwfsRes->lpBuffer;
			strTxt.Format(L"WFSAsyncGetInfo - WFS_INF_PIN_STATUS completed\r\n");
		}
		AppendStatus(strTxt);
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
			AppendStatus(strTxt);
		}
		m_pXFSManager->WFSFreeResult(pwfsRes);

		AsyncUnLock();
	}
}


void CPinpad::OnBnClickedClear()
{
	m_stStatus.SetWindowText(L"");
}


void CPinpad::OnBnClickedGetCaps()
{
	HRESULT hRes;
	CString strTxt;
	//WFSRESULT* pwfsRes = NULL;
	UpdateData(TRUE);
	if (m_AsyncCheckVal == FALSE)
	{

		Lock();
		
		LPWFSPINCAPS lpCaps = NULL;
		if ((hRes = m_pXFSManager->WFSGetInfo(m_hService, WFS_INF_PIN_CAPABILITIES, NULL, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSGetInfo WFS_INF_PIN_CAPABILITIES HRESULT = %d", hRes);
		}
		else
		{
			lpCaps = (LPWFSPINCAPS)pwfsRes->lpBuffer;
			strTxt.Format(L"WFSGetInfo - WFS_INF_PIN_CAPABILITIES completed\r\n");
		}
		AppendStatus(strTxt);
		if (lpCaps != NULL)
		{
			strTxt.FormatMessage(L"WFSPINCAPS::wClass = %d \n \
		WFSPINCAPS::fwType = %d \n \
		WFSPINCAPS::bCompound = %d \n \
		WFSPINCAPS::usKeyNum = %d \n \
		WFSPINCAPS::fwAlgorithms = %d \n \
		WFSPINCAPS::fwPinFormats = %d \n \
		WFSPINCAPS::fwDerivationAlgorithms = %d \n \
		WFSPINCAPS::fwPresentationAlgorithms = %d \n \
		WFSPINCAPS::fwDisplay = %d \n \
		WFSPINCAPS::bIDConnect = %d \n \
		WFSPINCAPS::fwIDKey = %d \n \
		WFSPINCAPS::fwValidationAlgorithms = %d \n \
		WFSPINCAPS::fwKeyCheckModes = %d \n \
		WFSPINCAPS::lpszExtra = %s \n \
		WFSPINCAPS::bPINCanPersistAfterUse = %d \n \
		WFSPINCAPS::fwAutoBeep = %d \n \
		WFSPINCAPS::bHSMJournaling = %d \n \
		WFSPINCAPS::dwRSAAuthenticationScheme = %d \n \
		WFSPINCAPS::dwRSASignatureAlgorithm = %d \n \
		WFSPINCAPS::dwRSACryptAlgorithm = %d \n \
		WFSPINCAPS::dwRSAKeyCheckMode = % d \n \
		WFSPINCAPS::dwSignatureScheme = %d \n \
		WFSPINCAPS::fwEMVHashAlgorithm = %d \n \
		WFSPINCAPS::bKeyImportThroughParts = % d \n \
		WFSPINCAPS::fwENCIOProtocols = %d \n \
		WFSPINCAPS::bTypeCombined = %d \n \
		WFSPINCAPS::bSetPinblockDataRequired = %d \n \
		WFSPINCAPS::fwKeyBlockImportFormats = %d \n \
		WFSPINCAPS::bPowerSaveControl = %d \n \
		WFSPINCAPS::bAntiFraudModule = %d \n \
		WFSPINCAPS::lpsHSMVendor = % d \n	\
		WFSPINCAPS::lpwEMVImportSchemes = %d \n ",
				lpCaps->wClass, lpCaps->fwType, lpCaps->bCompound, lpCaps->usKeyNum, lpCaps->fwAlgorithms, lpCaps->fwPinFormats,
				lpCaps->fwDerivationAlgorithms, lpCaps->fwPresentationAlgorithms, lpCaps->fwDisplay, lpCaps->bIDConnect, lpCaps->fwIDKey,
				lpCaps->fwValidationAlgorithms, lpCaps->fwKeyCheckModes, lpCaps->lpszExtra, lpCaps->bPINCanPersistAfterUse, lpCaps->fwAutoBeep,
				lpCaps->bHSMJournaling, lpCaps->dwRSAAuthenticationScheme, lpCaps->dwRSASignatureAlgorithm, lpCaps->dwRSACryptAlgorithm,
				lpCaps->dwRSAKeyCheckMode, lpCaps->dwSignatureScheme, lpCaps->fwEMVHashAlgorithm, lpCaps->bKeyImportThroughParts,
				lpCaps->fwENCIOProtocols, lpCaps->bTypeCombined, lpCaps->bSetPinblockDataRequired, lpCaps->fwKeyBlockImportFormats,
				lpCaps->bPowerSaveControl, lpCaps->bAntiFraudModule, lpCaps->lpsHSMVendor, lpCaps->lpwEMVImportSchemes
			);

			AppendStatus(strTxt);
		}
		m_pXFSManager->WFMFreeBuffer(pwfsRes);

		UnLock();
	}
	else
	{
		AsyncLock();
		LPWFSPINCAPS lpCaps = NULL;
		if ((hRes = m_pXFSManager->WFSAsyncGetInfo(m_hService, WFS_INF_PIN_CAPABILITIES, NULL, WFS_INDEFINITE_WAIT,m_hWnd,&m_requestId)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSAsyncGetInfo WFS_INF_PIN_CAPABILITIES HRESULT = %d", hRes);
		}
		else
		{
			lpCaps = (LPWFSPINCAPS)pwfsRes->lpBuffer;
			strTxt.Format(L"WFSAsyncGetInfo - WFS_INF_PIN_CAPABILITIES completed\r\n");
		}
		AppendStatus(strTxt);
		if (lpCaps != NULL)
		{
			strTxt.FormatMessage(L"WFSPINCAPS::wClass = %d \n \
		WFSPINCAPS::fwType = %d \n \
		WFSPINCAPS::bCompound = %d \n \
		WFSPINCAPS::usKeyNum = %d \n \
		WFSPINCAPS::fwAlgorithms = %d \n \
		WFSPINCAPS::fwPinFormats = %d \n \
		WFSPINCAPS::fwDerivationAlgorithms = %d \n \
		WFSPINCAPS::fwPresentationAlgorithms = %d \n \
		WFSPINCAPS::fwDisplay = %d \n \
		WFSPINCAPS::bIDConnect = %d \n \
		WFSPINCAPS::fwIDKey = %d \n \
		WFSPINCAPS::fwValidationAlgorithms = %d \n \
		WFSPINCAPS::fwKeyCheckModes = %d \n \
		WFSPINCAPS::lpszExtra = %s \n \
		WFSPINCAPS::bPINCanPersistAfterUse = %d \n \
		WFSPINCAPS::fwAutoBeep = %d \n \
		WFSPINCAPS::bHSMJournaling = %d \n \
		WFSPINCAPS::dwRSAAuthenticationScheme = %d \n \
		WFSPINCAPS::dwRSASignatureAlgorithm = %d \n \
		WFSPINCAPS::dwRSACryptAlgorithm = %d \n \
		WFSPINCAPS::dwRSAKeyCheckMode = % d \n \
		WFSPINCAPS::dwSignatureScheme = %d \n \
		WFSPINCAPS::fwEMVHashAlgorithm = %d \n \
		WFSPINCAPS::bKeyImportThroughParts = % d \n \
		WFSPINCAPS::fwENCIOProtocols = %d \n \
		WFSPINCAPS::bTypeCombined = %d \n \
		WFSPINCAPS::bSetPinblockDataRequired = %d \n \
		WFSPINCAPS::fwKeyBlockImportFormats = %d \n \
		WFSPINCAPS::bPowerSaveControl = %d \n \
		WFSPINCAPS::bAntiFraudModule = %d \n \
		WFSPINCAPS::lpsHSMVendor = % d \n	\
		WFSPINCAPS::lpwEMVImportSchemes = %d \n ",
				lpCaps->wClass, lpCaps->fwType, lpCaps->bCompound, lpCaps->usKeyNum, lpCaps->fwAlgorithms, lpCaps->fwPinFormats,
				lpCaps->fwDerivationAlgorithms, lpCaps->fwPresentationAlgorithms, lpCaps->fwDisplay, lpCaps->bIDConnect, lpCaps->fwIDKey,
				lpCaps->fwValidationAlgorithms, lpCaps->fwKeyCheckModes, lpCaps->lpszExtra, lpCaps->bPINCanPersistAfterUse, lpCaps->fwAutoBeep,
				lpCaps->bHSMJournaling, lpCaps->dwRSAAuthenticationScheme, lpCaps->dwRSASignatureAlgorithm, lpCaps->dwRSACryptAlgorithm,
				lpCaps->dwRSAKeyCheckMode, lpCaps->dwSignatureScheme, lpCaps->fwEMVHashAlgorithm, lpCaps->bKeyImportThroughParts,
				lpCaps->fwENCIOProtocols, lpCaps->bTypeCombined, lpCaps->bSetPinblockDataRequired, lpCaps->fwKeyBlockImportFormats,
				lpCaps->bPowerSaveControl, lpCaps->bAntiFraudModule, lpCaps->lpsHSMVendor, lpCaps->lpwEMVImportSchemes
			);

			AppendStatus(strTxt);
		}
		m_pXFSManager->WFMFreeBuffer(pwfsRes);

		AsyncUnLock();
	}
}


void CPinpad::OnBnClickedGetKeyDetails()
{
	HRESULT hRes;
	CString strTxt;
	CString strInput;
	//m_edtInfoInput.SetFocus();
	
	GetDlgItemText(IDC_EDT_INFOCMD_INPUT,strInput);
	m_edtInfoInput.GetWindowText(strInput);
	UpdateData(TRUE);
	if (m_AsyncCheckVal == FALSE)
	{
		Lock();
		WFSRESULT* pwfsRes = NULL;
		LPWFSPINKEYDETAIL lpKeyDetails = NULL;
		if ((hRes = m_pXFSManager->WFSGetInfo(m_hService, WFS_INF_PIN_KEY_DETAIL, CStringA(strInput).GetBuffer(), WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSGetInfo WFS_INF_PIN_KEY_DETAIL HRESULT = %d", hRes);
		}
		else
		{
			lpKeyDetails = (LPWFSPINKEYDETAIL)pwfsRes->lpBuffer;
			strTxt.Format(L"WFSGetInfo - WFS_INF_PIN_KEY_DETAIL completed\r\n");
		}
		AppendStatus(strTxt);

		if (lpKeyDetails != NULL)
		{
			CString strData = L"";
			if (lpKeyDetails->lpxKeyBlockHeader != NULL && lpKeyDetails->lpxKeyBlockHeader->lpbData != NULL)
			{
				CString strTmp;
				for (USHORT i = 0; i < lpKeyDetails->lpxKeyBlockHeader->usLength; ++i)
				{
					strTmp.FormatMessage(L"%0.2x ", lpKeyDetails->lpxKeyBlockHeader->lpbData[i]);
					strData += strTmp;
				}
			}

			strTxt.FormatMessage(L"lpKeyDetails->lpsKeyName = %s \n lpKeyDetails->fwUse = % d \n \
		lpKeyDetails->bLoaded = %d \n lpKeyDetails->lpxKeyBlockHeader->lpbData = %s",
				lpKeyDetails->lpsKeyName, lpKeyDetails->fwUse, lpKeyDetails->bLoaded, strData);

			AppendStatus(strTxt);
		}
		m_pXFSManager->WFMFreeBuffer(pwfsRes);

		UnLock();
	}
	else
	{
		Lock();
		//WFSRESULT* pwfsRes = NULL;
		LPWFSPINKEYDETAIL lpKeyDetails = NULL;
		if ((hRes = m_pXFSManager->WFSAsyncGetInfo(m_hService, WFS_INF_PIN_KEY_DETAIL, CStringA(strInput).GetBuffer(), WFS_INDEFINITE_WAIT,m_hWnd,&m_requestId)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSAsyncGetInfo WFS_INF_PIN_KEY_DETAIL HRESULT = %d", hRes);
		}
		else
		{
			lpKeyDetails = (LPWFSPINKEYDETAIL)pwfsRes->lpBuffer;
			strTxt.Format(L"WFSAsyncGetInfo - WFS_INF_PIN_KEY_DETAIL completed\r\n");
		}
		AppendStatus(strTxt);

		if (lpKeyDetails != NULL)
		{
			CString strData = L"";
			if (lpKeyDetails->lpxKeyBlockHeader != NULL && lpKeyDetails->lpxKeyBlockHeader->lpbData != NULL)
			{
				CString strTmp;
				for (USHORT i = 0; i < lpKeyDetails->lpxKeyBlockHeader->usLength; ++i)
				{
					strTmp.FormatMessage(L"%0.2x ", lpKeyDetails->lpxKeyBlockHeader->lpbData[i]);
					strData += strTmp;
				}
			}

			strTxt.FormatMessage(L"lpKeyDetails->lpsKeyName = %s \n lpKeyDetails->fwUse = % d \n \
		lpKeyDetails->bLoaded = %d \n lpKeyDetails->lpxKeyBlockHeader->lpbData = %s",
				lpKeyDetails->lpsKeyName, lpKeyDetails->fwUse, lpKeyDetails->bLoaded, strData);

			AppendStatus(strTxt);
		}
		m_pXFSManager->WFMFreeBuffer(pwfsRes);
		AsyncUnLock();
	}
}


void CPinpad::OnBnClickedGetKeyDetailsEx()
{
	HRESULT hRes;
	CString strTxt;
	CString strInput;
	m_edtInfoInput.GetWindowText(strInput);
	UpdateData(TRUE);
	if (m_AsyncCheckVal == FALSE)
	{
		Lock();
		//WFSRESULT* pwfsRes = NULL;
		LPWFSPINKEYDETAILEX lpKeyDetailsEx = NULL;
		if ((hRes = m_pXFSManager->WFSGetInfo(m_hService, WFS_INF_PIN_KEY_DETAIL_EX, CStringA(strInput).GetBuffer(), WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSGetInfo WFS_INF_PIN_KEY_DETAIL_EX HRESULT = %d", hRes);
		}
		else
		{
			lpKeyDetailsEx = (LPWFSPINKEYDETAILEX)pwfsRes->lpBuffer;
			strTxt.Format(L"WFSGetInfo - WFS_INF_PIN_KEY_DETAIL_EX completed\r\n");
		}
		AppendStatus(strTxt);

		if (lpKeyDetailsEx != NULL)
		{
			CString strData = L"";
			if (lpKeyDetailsEx->lpxKeyBlockHeader != NULL && lpKeyDetailsEx->lpxKeyBlockHeader->lpbData != NULL)
			{
				CString strTmp;
				for (USHORT i = 0; i < lpKeyDetailsEx->lpxKeyBlockHeader->usLength; ++i)
				{
					strTmp.FormatMessage(L"%0.2x ", lpKeyDetailsEx->lpxKeyBlockHeader->lpbData[i]);
					strData += strTmp;
				}
			}

			strTxt.FormatMessage(L"lpKeyDetailsEx->lpsKeyName = %s \n \
		lpKeyDetailsEx->fwUse = % d \n \
		lpKeyDetailsEx->bLoaded = %d \n \
		lpKeyDetailsEx->lpxKeyBlockHeader->lpbData = %s \n \
		lpKeyDetailsEx->bGeneration = %d \n \
		lpKeyDetailsEx->bVersion = %d \n \
		lpKeyDetailsEx->bActivatingDate = %0.8x \n \
		lpKeyDetailsEx->bExpiryDate = %0.8x",
				lpKeyDetailsEx->lpsKeyName, lpKeyDetailsEx->dwUse, lpKeyDetailsEx->bLoaded, strData,
				lpKeyDetailsEx->bGeneration, lpKeyDetailsEx->bVersion, lpKeyDetailsEx->bActivatingDate, lpKeyDetailsEx->bExpiryDate);

			AppendStatus(strTxt);
		}

		m_pXFSManager->WFMFreeBuffer(pwfsRes);

		UnLock();
	}
	else
	{
		AsyncLock();
		//WFSRESULT* pwfsRes = NULL;
		LPWFSPINKEYDETAILEX lpKeyDetailsEx = NULL;
		if ((hRes = m_pXFSManager->WFSAsyncGetInfo(m_hService, WFS_INF_PIN_KEY_DETAIL_EX, CStringA(strInput).GetBuffer(), WFS_INDEFINITE_WAIT,m_hWnd,&m_requestId)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSAsyncGetInfo WFS_INF_PIN_KEY_DETAIL_EX HRESULT = %d", hRes);
		}
		else
		{
			lpKeyDetailsEx = (LPWFSPINKEYDETAILEX)pwfsRes->lpBuffer;
			strTxt.Format(L"WFSAsyncGetInfo - WFS_INF_PIN_KEY_DETAIL_EX completed\r\n");
		}
		AppendStatus(strTxt);

		if (lpKeyDetailsEx != NULL)
		{
			CString strData = L"";
			if (lpKeyDetailsEx->lpxKeyBlockHeader != NULL && lpKeyDetailsEx->lpxKeyBlockHeader->lpbData != NULL)
			{
				CString strTmp;
				for (USHORT i = 0; i < lpKeyDetailsEx->lpxKeyBlockHeader->usLength; ++i)
				{
					strTmp.FormatMessage(L"%0.2x ", lpKeyDetailsEx->lpxKeyBlockHeader->lpbData[i]);
					strData += strTmp;
				}
			}

			strTxt.FormatMessage(L"lpKeyDetailsEx->lpsKeyName = %s \n \
		lpKeyDetailsEx->fwUse = % d \n \
		lpKeyDetailsEx->bLoaded = %d \n \
		lpKeyDetailsEx->lpxKeyBlockHeader->lpbData = %s \n \
		lpKeyDetailsEx->bGeneration = %d \n \
		lpKeyDetailsEx->bVersion = %d \n \
		lpKeyDetailsEx->bActivatingDate = %0.8x \n \
		lpKeyDetailsEx->bExpiryDate = %0.8x",
				lpKeyDetailsEx->lpsKeyName, lpKeyDetailsEx->dwUse, lpKeyDetailsEx->bLoaded, strData,
				lpKeyDetailsEx->bGeneration, lpKeyDetailsEx->bVersion, lpKeyDetailsEx->bActivatingDate, lpKeyDetailsEx->bExpiryDate);

			AppendStatus(strTxt);
		}
		m_pXFSManager->WFMFreeBuffer(pwfsRes);
		AsyncUnLock();
	}
}


void CPinpad::OnBnClickedGetFuncKey()
{
	HRESULT hRes;
	CString strTxt;
	UpdateData(TRUE);
	if (m_AsyncCheckVal == FALSE)
	{
		Lock();
		//WFSRESULT* pwfsRes = NULL;
		LPWFSPINFUNCKEYDETAIL lpFunKeyDetails = NULL;
		if ((hRes = m_pXFSManager->WFSGetInfo(m_hService, WFS_INF_PIN_FUNCKEY_DETAIL, NULL, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSGetInfo WFS_INF_PIN_FUNCKEY_DETAIL HRESULT = %d", hRes);
		}
		else
		{
			lpFunKeyDetails = (LPWFSPINFUNCKEYDETAIL)pwfsRes->lpBuffer;
			strTxt.Format(L"WFSGetInfo - WFS_INF_PIN_FUNCKEY_DETAIL completed\r\n");
		}
		AppendStatus(strTxt);

		if (lpFunKeyDetails != NULL)
		{
			CString strData = L"";
			if (lpFunKeyDetails->lppFDKs != NULL)
			{
				CString strTmp;
				LPWFSPINFDK* lppFDKs = lpFunKeyDetails->lppFDKs;
				for (USHORT i = 0; i < lpFunKeyDetails->usNumberFDKs; ++i)
				{
					strTmp.FormatMessage(L"ulFDK[%d] = %d, usXPosition = %d, usYPosition = %d \n ",
						i, (*lppFDKs)->ulFDK, (*lppFDKs)->usXPosition, (*lppFDKs)->usYPosition);
					lppFDKs++;
					strData += strTmp;
				}
			}

			strTxt.Format(L"lpFunKeyDetails->ulFuncMask = %d \n  lpFunKeyDetails->usNumberFDKs  = %d \n lpFunKeyDetails->lppFDKs = %s",
				lpFunKeyDetails->ulFuncMask, lpFunKeyDetails->usNumberFDKs, strData);

			AppendStatus(strTxt);
		}
		m_pXFSManager->WFMFreeBuffer(pwfsRes);
		UnLock();
	}
	else
	{
		AsyncLock();
		//WFSRESULT* pwfsRes = NULL;
		LPWFSPINFUNCKEYDETAIL lpFunKeyDetails = NULL;
		if ((hRes = m_pXFSManager->WFSAsyncGetInfo(m_hService, WFS_INF_PIN_FUNCKEY_DETAIL, NULL, WFS_INDEFINITE_WAIT,m_hWnd,&m_requestId)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSAsyncGetInfo WFS_INF_PIN_FUNCKEY_DETAIL HRESULT = %d", hRes);
		}
		else
		{
			lpFunKeyDetails = (LPWFSPINFUNCKEYDETAIL)pwfsRes->lpBuffer;
			strTxt.Format(L"WFSAsyncGetInfo - WFS_INF_PIN_FUNCKEY_DETAIL completed\r\n");
		}
		AppendStatus(strTxt);
		if (lpFunKeyDetails != NULL)
		{
			CString strData = L"";
			if (lpFunKeyDetails->lppFDKs != NULL)
			{
				CString strTmp;
				LPWFSPINFDK* lppFDKs = lpFunKeyDetails->lppFDKs;
				for (USHORT i = 0; i < lpFunKeyDetails->usNumberFDKs; ++i)
				{
					strTmp.FormatMessage(L"ulFDK[%d] = %d, usXPosition = %d, usYPosition = %d \n ",
						i, (*lppFDKs)->ulFDK, (*lppFDKs)->usXPosition, (*lppFDKs)->usYPosition);
					lppFDKs++;
					strData += strTmp;
				}
			}
			strTxt.Format(L"lpFunKeyDetails->ulFuncMask = %d \n  lpFunKeyDetails->usNumberFDKs  = %d \n lpFunKeyDetails->lppFDKs = %s",
				lpFunKeyDetails->ulFuncMask, lpFunKeyDetails->usNumberFDKs, strData);

			AppendStatus(strTxt);
		}
		m_pXFSManager->WFMFreeBuffer(pwfsRes);
		AsyncUnLock();

	}
}


void CPinpad::OnBnClickedGetHsm()
{

	HRESULT hRes;
	CString strTxt;
	UpdateData(TRUE);
	if (m_AsyncCheckVal == FALSE)
	{
		Lock();
		//WFSRESULT* pwfsRes = NULL;
		LPWFSXDATA lpHSM = NULL;
		if ((hRes = m_pXFSManager->WFSGetInfo(m_hService, WFS_INF_PIN_HSM_TDATA, NULL, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSGetInfo WFS_INF_PIN_HSM_TDATA HRESULT = %d", hRes);
		}
		else
		{
			lpHSM = (LPWFSXDATA)pwfsRes->lpBuffer;
			strTxt.Format(L"WFSGetInfo - WFS_INF_PIN_HSM_TDATA completed\r\n");
		}
		AppendStatus(strTxt);

		if (lpHSM != NULL)
		{
			CString strData = L"";
			if (lpHSM->lpbData != NULL)
			{
				CString strTmp;
				for (USHORT i = 0; i < lpHSM->usLength; ++i)
				{
					strTmp.FormatMessage(L"%0.2x ", lpHSM->lpbData[i]);
					strData += strTmp;
				}
			}
			strTxt.FormatMessage(L"lpHSM->usLength = %d \n lpHSM->lpbData = %s",
				lpHSM->usLength, strData);

			AppendStatus(strTxt);
		}
		m_pXFSManager->WFMFreeBuffer(pwfsRes);
		UnLock();
	}
	else
	{
		AsyncLock();
		//WFSRESULT* pwfsRes = NULL;
		LPWFSXDATA lpHSM = NULL;
		if ((hRes = m_pXFSManager->WFSAsyncGetInfo(m_hService, WFS_INF_PIN_HSM_TDATA, NULL, WFS_INDEFINITE_WAIT,m_hWnd,&m_requestId)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSGetInfo WFS_INF_PIN_HSM_TDATA HRESULT = %d", hRes);
		}
		else
		{
			lpHSM = (LPWFSXDATA)pwfsRes->lpBuffer;
			strTxt.Format(L"WFSGetInfo - WFS_INF_PIN_HSM_TDATA completed\r\n");
		}
		AppendStatus(strTxt);

		if (lpHSM != NULL)
		{
			CString strData = L"";
			if (lpHSM->lpbData != NULL)
			{
				CString strTmp;
				for (USHORT i = 0; i < lpHSM->usLength; ++i)
				{
					strTmp.FormatMessage(L"%0.2x ", lpHSM->lpbData[i]);
					strData += strTmp;
				}
			}
			strTxt.FormatMessage(L"lpHSM->usLength = %d \n lpHSM->lpbData = %s",
				lpHSM->usLength, strData);

			AppendStatus(strTxt);
		}
		m_pXFSManager->WFMFreeBuffer(pwfsRes);
		AsyncUnLock();
	}
}


void CPinpad::OnBnClickedGetSecKey()
{
	HRESULT hRes;
	CString strTxt;

	UpdateData(TRUE);
	if (m_AsyncCheckVal == FALSE)
	{
		Lock();
		//WFSRESULT* pwfsRes = NULL;
		LPWFSPINSECUREKEYDETAIL lpSecKey = NULL;
		if ((hRes = m_pXFSManager->WFSGetInfo(m_hService, WFS_INF_PIN_SECUREKEY_DETAIL, NULL, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSGetInfo WFS_INF_PIN_SECUREKEY_DETAIL HRESULT = %d", hRes);
		}
		else
		{
			lpSecKey = (LPWFSPINSECUREKEYDETAIL)pwfsRes->lpBuffer;
			strTxt.Format(L"WFSGetInfo - WFS_INF_PIN_SECUREKEY_DETAIL completed\r\n");
		}
		AppendStatus(strTxt);

		if (lpSecKey != NULL)
		{
			CString strData = L"";
			if (lpSecKey->lppHexKeys != NULL)
			{
				CString strTmp;
				int nCount = lpSecKey->wColumns * lpSecKey->wRows;
				LPWFSPINHEXKEYS* lppHexKeys = lpSecKey->lppHexKeys;
				for (USHORT i = 0; i < nCount; ++i)
				{
					strTmp.FormatMessage(L"FDK[%d] = %d, usXPos = %d, usYPos = %d, usXSize = %d, usYSize = %d, ulFK = %d, ulShiftFK = %d \n ",
						i, (*lppHexKeys)->usXPos, (*lppHexKeys)->usYPos, (*lppHexKeys)->usXSize, (*lppHexKeys)->usYSize, (*lppHexKeys)->ulFK, (*lppHexKeys)->ulShiftFK);
					lppHexKeys++;
					strData += strTmp;
				}
			}
			CString strData1 = L"";
			if (lpSecKey->lpFuncKeyDetail != NULL && lpSecKey->lpFuncKeyDetail->lppFDKs != NULL)
			{
				CString strTmp;
				LPWFSPINFDK* lppFDKs = lpSecKey->lpFuncKeyDetail->lppFDKs;
				strData.FormatMessage(L"lpSecKey->lpFuncKeyDetail->usNumberFDKs = %d, lpSecKey->lpFuncKeyDetail->ulFuncMask = %d \n ",
					lpSecKey->lpFuncKeyDetail->usNumberFDKs, lpSecKey->lpFuncKeyDetail->ulFuncMask);
				for (USHORT i = 0; i < lpSecKey->lpFuncKeyDetail->usNumberFDKs; ++i)
				{
					strTmp.FormatMessage(L"ulFDK[%d] = %d, usXPosition = %d, usYPosition = %d \n ",
						i, (*lppFDKs)->ulFDK, (*lppFDKs)->usXPosition, (*lppFDKs)->usYPosition);
					lppFDKs++;
					strData += strTmp;
				}
			}
			strTxt.FormatMessage(L"	lpSecKey->fwKeyEntryMode = %d \n lpSecKey->ulClearFDK = %d \n lpSecKey->ulCancelFDK = %d \n \
		lpSecKey->ulBackspaceFDK = %d \n lpSecKey->ulEnterFDK = %d \n lpSecKey->wColumns = %d \n \
		lpSecKey->wRows = %d \n lpSecKey->lppHexKeys = %s \n  lpSecKey->lpFuncKeyDetail = %s",
				lpSecKey->fwKeyEntryMode, lpSecKey->ulClearFDK, lpSecKey->ulCancelFDK, lpSecKey->ulBackspaceFDK, lpSecKey->ulEnterFDK,
				lpSecKey->wColumns, lpSecKey->wRows, strData, strData1);

			AppendStatus(strTxt);
		}
		m_pXFSManager->WFMFreeBuffer(pwfsRes);
		UnLock();
	}
	else
	{
		AsyncLock();
		//WFSRESULT* pwfsRes = NULL;
		LPWFSPINSECUREKEYDETAIL lpSecKey = NULL;
		if ((hRes = m_pXFSManager->WFSAsyncGetInfo(m_hService, WFS_INF_PIN_SECUREKEY_DETAIL, NULL, WFS_INDEFINITE_WAIT,m_hWnd,&m_requestId)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSAsyncGetInfo WFS_INF_PIN_SECUREKEY_DETAIL HRESULT = %d", hRes);
		}
		else
		{
			lpSecKey = (LPWFSPINSECUREKEYDETAIL)pwfsRes->lpBuffer;
			strTxt.Format(L"WFSAsyncGetInfo - WFS_INF_PIN_SECUREKEY_DETAIL completed\r\n");
		}
		AppendStatus(strTxt);

		if (lpSecKey != NULL)
		{
			CString strData = L"";
			if (lpSecKey->lppHexKeys != NULL)
			{
				CString strTmp;
				int nCount = lpSecKey->wColumns * lpSecKey->wRows;
				LPWFSPINHEXKEYS* lppHexKeys = lpSecKey->lppHexKeys;
				for (USHORT i = 0; i < nCount; ++i)
				{
					strTmp.FormatMessage(L"FDK[%d] = %d, usXPos = %d, usYPos = %d, usXSize = %d, usYSize = %d, ulFK = %d, ulShiftFK = %d \n ",
						i, (*lppHexKeys)->usXPos, (*lppHexKeys)->usYPos, (*lppHexKeys)->usXSize, (*lppHexKeys)->usYSize, (*lppHexKeys)->ulFK, (*lppHexKeys)->ulShiftFK);
					lppHexKeys++;
					strData += strTmp;
				}
			}
			CString strData1 = L"";
			if (lpSecKey->lpFuncKeyDetail != NULL && lpSecKey->lpFuncKeyDetail->lppFDKs != NULL)
			{
				CString strTmp;
				LPWFSPINFDK* lppFDKs = lpSecKey->lpFuncKeyDetail->lppFDKs;
				strData.FormatMessage(L"lpSecKey->lpFuncKeyDetail->usNumberFDKs = %d, lpSecKey->lpFuncKeyDetail->ulFuncMask = %d \n ",
					lpSecKey->lpFuncKeyDetail->usNumberFDKs, lpSecKey->lpFuncKeyDetail->ulFuncMask);
				for (USHORT i = 0; i < lpSecKey->lpFuncKeyDetail->usNumberFDKs; ++i)
				{
					strTmp.FormatMessage(L"ulFDK[%d] = %d, usXPosition = %d, usYPosition = %d \n ",
						i, (*lppFDKs)->ulFDK, (*lppFDKs)->usXPosition, (*lppFDKs)->usYPosition);
					lppFDKs++;
					strData += strTmp;
				}
			}
			strTxt.FormatMessage(L"	lpSecKey->fwKeyEntryMode = %d \n lpSecKey->ulClearFDK = %d \n lpSecKey->ulCancelFDK = %d \n \
		lpSecKey->ulBackspaceFDK = %d \n lpSecKey->ulEnterFDK = %d \n lpSecKey->wColumns = %d \n \
		lpSecKey->wRows = %d \n lpSecKey->lppHexKeys = %s \n  lpSecKey->lpFuncKeyDetail = %s",
				lpSecKey->fwKeyEntryMode, lpSecKey->ulClearFDK, lpSecKey->ulCancelFDK, lpSecKey->ulBackspaceFDK, lpSecKey->ulEnterFDK,
				lpSecKey->wColumns, lpSecKey->wRows, strData, strData1);

			AppendStatus(strTxt);
		}
		m_pXFSManager->WFMFreeBuffer(pwfsRes);

		AsyncUnLock();
	}
}


void CPinpad::OnBnClickedGetDevId()
{
	HRESULT hRes;
	CString strTxt;
	UpdateData(TRUE);
	if (m_AsyncCheckVal == FALSE)
	{
		Lock();
		//WFSRESULT* pwfsRes = NULL;
		LPWFSPINPCIPTSDEVICEID lpDevID = NULL;
		if ((hRes = m_pXFSManager->WFSGetInfo(m_hService, WFS_INF_PIN_QUERY_PCIPTS_DEVICE_ID, NULL, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSGetInfo WFS_INF_PIN_QUERY_PCIPTS_DEVICE_ID HRESULT = %d", hRes);
		}
		else
		{
			lpDevID = (LPWFSPINPCIPTSDEVICEID)pwfsRes->lpBuffer;
			strTxt.Format(L"WFSGetInfo - WFS_INF_PIN_QUERY_PCIPTS_DEVICE_ID completed\r\n");
		}
		AppendStatus(strTxt);

		if (lpDevID != NULL)
		{
			strTxt.FormatMessage(L"lpDevID->lpszManufacturerIdentifier = %s \n lpDevID->lpszModelIdentifier = %s \n lpDevID->lpszHardwareIdentifier = %s \n\
		 lpDevID->lpszFirmwareIdentifier = %s \n  lpDevID->lpszApplicationIdentifier = %s", lpDevID->lpszManufacturerIdentifier,
				lpDevID->lpszModelIdentifier, lpDevID->lpszHardwareIdentifier, lpDevID->lpszFirmwareIdentifier, lpDevID->lpszApplicationIdentifier);

			AppendStatus(strTxt);
		}
		m_pXFSManager->WFMFreeBuffer(pwfsRes);
		UnLock();
	}
	else
	{
		AsyncLock();
		//WFSRESULT* pwfsRes = NULL;
		LPWFSPINPCIPTSDEVICEID lpDevID = NULL;
		if ((hRes = m_pXFSManager->WFSAsyncGetInfo(m_hService, WFS_INF_PIN_QUERY_PCIPTS_DEVICE_ID, NULL, WFS_INDEFINITE_WAIT,m_hWnd,&m_requestId)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSAsyncGetInfo WFS_INF_PIN_QUERY_PCIPTS_DEVICE_ID HRESULT = %d", hRes);
		}
		else
		{
			lpDevID = (LPWFSPINPCIPTSDEVICEID)pwfsRes->lpBuffer;
			strTxt.Format(L"WFSAsyncGetInfo - WFS_INF_PIN_QUERY_PCIPTS_DEVICE_ID completed\r\n");
		}
		AppendStatus(strTxt);

		if (lpDevID != NULL)
		{
			strTxt.FormatMessage(L"lpDevID->lpszManufacturerIdentifier = %s \n lpDevID->lpszModelIdentifier = %s \n lpDevID->lpszHardwareIdentifier = %s \n\
		 lpDevID->lpszFirmwareIdentifier = %s \n  lpDevID->lpszApplicationIdentifier = %s", lpDevID->lpszManufacturerIdentifier,
				lpDevID->lpszModelIdentifier, lpDevID->lpszHardwareIdentifier, lpDevID->lpszFirmwareIdentifier, lpDevID->lpszApplicationIdentifier);

			AppendStatus(strTxt);
		}
		m_pXFSManager->WFMFreeBuffer(pwfsRes);
		AsyncUnLock();
	}
}


void CPinpad::OnBnClickedLoadkey()
{
	HRESULT hRes;
	CString str, strTxt;
	WFSPINIMPORT importkey;
	m_edtkeyName.GetWindowText(str);
	if (str.Trim().GetLength() == 0)
	{
		MessageBox(L"Enter valid key name");
		m_edtkeyName.SetFocus();
		return;
	}

	importkey.lpsKey = ((CStringA)str).GetBuffer();
	importkey.fwUse = WFS_PIN_USECRYPT;

	m_edtKeyInput.GetWindowText(str);
	if (str.Trim().GetLength() == 0)
	{
		MessageBox(L"Enter valid key");
		m_edtKeyInput.SetFocus();
		return;
	}

	BYTE byteValue[128] = { 0 };
	USHORT byteIndex = 0;
	bool bMoveToNext = false;
	for (int nIndex = 0; nIndex < str.GetLength(); ++nIndex)
	{
		volatile char ch = str[nIndex];
		if (ch >= '0' && ch <= '9')
		{
			byteValue[byteIndex] |= ch - '0';
		}
		else if (ch >= 'A' && ch <= 'F')
		{
			byteValue[byteIndex] |= 0x0A + (ch - 'A');
		}
		else if (ch >= 'a' && ch <= 'f')
		{
			byteValue[byteIndex] |= 0x0A + (ch - 'a');
		}
		else
		{
			MessageBox(L"Enter valid key");
			m_edtKeyInput.SetFocus();
			return;
		}

		if (!bMoveToNext)
		{
			bMoveToNext = true;
			byteValue[byteIndex] <<= 4;
		}
		else
		{
			bMoveToNext = false;
			byteIndex++;
		}
	}

	WFSXDATA keyData;
	keyData.lpbData = byteValue;
	keyData.usLength = byteIndex;
	importkey.lpxValue = &keyData;
	UpdateData(TRUE);
	if (m_AsyncCheckVal == FALSE)
	{
		Lock();
		//WFSRESULT* pwfsRes;
		if ((hRes = m_pXFSManager->WFSExecute(m_hService, WFS_CMD_PIN_IMPORT_KEY, &importkey, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSExecute WFS_CMD_PIN_IMPORT_KEY HRESULT = %d", hRes);
		}
		else
		{
			strTxt.Format(L"WFSExecute WFS_CMD_PIN_IMPORT_KEY completed");
		}
		AppendStatus(strTxt);
		UnLock();
	}
	else
	{
		AsyncLock();
		//WFSRESULT* pwfsRes;
		if ((hRes = m_pXFSManager->WFSAsyncExecute(m_hService, WFS_CMD_PIN_IMPORT_KEY, &importkey, WFS_INDEFINITE_WAIT,m_hWnd,&m_requestId)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSAsyncExecute WFS_CMD_PIN_IMPORT_KEY HRESULT = %d", hRes);
		}
		else
		{
			strTxt.Format(L"WFSAsyncExecute WFS_CMD_PIN_IMPORT_KEY completed");
		}
		AppendStatus(strTxt);
		AsyncUnLock();
	}
}


void CPinpad::OnBnClickedDeletekey()
{
	HRESULT hRes;
	CString str, strTxt;
	m_edtkeyName.GetWindowText(str);
	if (str.Trim().GetLength() == 0)
	{
		MessageBox(L"Enter valid key name");
		m_edtkeyName.SetFocus();
		return;
	}
	WFSPINIMPORT importkey;
	importkey.lpsKey = ((CStringA)str).GetBuffer();
	importkey.fwUse = 0;
	UpdateData(TRUE);
	if (m_AsyncCheckVal == FALSE)
	{
		Lock();
		//WFSRESULT* pwfsRes;
		if ((hRes = m_pXFSManager->WFSExecute(m_hService, WFS_CMD_PIN_IMPORT_KEY, &importkey, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSExecute WFS_CMD_PIN_IMPORT_KEY HRESULT = %d", hRes);
		}
		else
		{
			strTxt.Format(L"WFSExecute WFS_CMD_PIN_IMPORT_KEY completed");
		}
		UnLock();
		AppendStatus(strTxt);
	}
	else
	{
		AsyncLock();
		//WFSRESULT* pwfsRes;
		if ((hRes = m_pXFSManager->WFSAsyncExecute(m_hService, WFS_CMD_PIN_IMPORT_KEY, &importkey, WFS_INDEFINITE_WAIT,m_hWnd,&m_requestId)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSAsyncExecute WFS_CMD_PIN_IMPORT_KEY HRESULT = %d", hRes);
		}
		else
		{
			strTxt.Format(L"WFSAsyncExecute WFS_CMD_PIN_IMPORT_KEY completed");
		}
		AsyncUnLock();
		AppendStatus(strTxt);
	}
}


void CPinpad::OnBnClickedGetpin()
{
	DWORD dwThreadID;
	AfxBeginThread(GetPINThread, (LPVOID)this);

	/*HANDLE hThreadArray = CreateThread(
		NULL,               // default security attributes
		0,                  // use default stack size
		GetPINThread,       // thread function name
		(LPVOID)this,		// argument to thread function
		0,                  // use default creation flags
		&dwThreadID);		// returns the thread identifier
	*/

	/*
	_beginthread(GetPINThread, 256, (LPVOID)this);
	*/
}


void CPinpad::OnBnClickedCryptdata()
{
	// TODO: Add your control notification handler code here
}
