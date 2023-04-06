// Cprinter.cpp : implementation file
//

#include "pch.h"
#include "DeviceTest.h"
#include "afxdialogex.h"
#include "Cprinter.h"
#include "XFSPTR.H"
#include "XFSADMIN.H"

HMODULE hdllp;
HSERVICE hServicep;


// Cprinter dialog

IMPLEMENT_DYNAMIC(Cprinter, CDialogEx)

Cprinter::Cprinter(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Printerdlg, pParent)
{

}

Cprinter::~Cprinter()
{
}

void Cprinter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT21, m_richprint);
	DDX_Control(pDX, IDC_EDIT_PrintData, m_editprintdata);
	DDX_Control(pDX, IDC_EDIT1, m_edtFileName);
}


BEGIN_MESSAGE_MAP(Cprinter, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Cprinter::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_BUTTON2, &Cprinter::OnBnClickedStartUp)
	ON_BN_CLICKED(IDC_BUTTON3, &Cprinter::OnBnClickedAsyncOPen)
	ON_BN_CLICKED(IDC_BUTTON6, &Cprinter::OnBnClickedSelectFile)



	ON_MESSAGE(WFS_OPEN_COMPLETE, &Cprinter::OnOpenComplete)
	ON_MESSAGE(WFS_CLOSE_COMPLETE, &Cprinter::OnCloseComplete)
	ON_MESSAGE(WFS_LOCK_COMPLETE, &Cprinter::OnLockComplete)
	ON_MESSAGE(WFS_UNLOCK_COMPLETE, &Cprinter::OnUnlockComplete)
	ON_MESSAGE(WFS_REGISTER_COMPLETE, &Cprinter::OnRegisterComplete)
	ON_MESSAGE(WFS_DEREGISTER_COMPLETE, &Cprinter::OnDeregisterComplete)
	ON_MESSAGE(WFS_GETINFO_COMPLETE, &Cprinter::OnGetInfoComplete)
	ON_MESSAGE(WFS_EXECUTE_COMPLETE, &Cprinter::OnExecuteComplete)

	ON_MESSAGE(WFS_TIMER_EVENT, &Cprinter::OnTimerEvent)
	ON_MESSAGE(WFS_EXECUTE_EVENT, &Cprinter::OnExecuteEvent)
	ON_MESSAGE(WFS_USER_EVENT, &Cprinter::OnUserEvent)
	ON_MESSAGE(WFS_SYSTEM_EVENT, &Cprinter::OnSystemEvent)
	ON_MESSAGE(WFS_SERVICE_EVENT, &Cprinter::OnServiceEvent)


	ON_EN_CHANGE(IDC_RICHEDIT21, &Cprinter::OnEnChangeRichedit21)
	ON_EN_CHANGE(IDC_EDIT_PrintData, &Cprinter::OnEnChangeEditPrintdata)
	
	ON_BN_CLICKED(IDC_PrintFile, &Cprinter::OnBnClickedPrintfile)
	ON_BN_CLICKED(IDC_PrintData, &Cprinter::OnBnClickedPrintdata)
	ON_BN_CLICKED(IDC_Reset, &Cprinter::OnBnClickedReset)
	ON_BN_CLICKED(IDC_Dispensepaper, &Cprinter::OnBnClickedDispensepaper)
	ON_BN_CLICKED(IDC_Cutpaper, &Cprinter::OnBnClickedCutpaper)
	ON_BN_CLICKED(IDC_Printform, &Cprinter::OnBnClickedPrintform)
	ON_BN_CLICKED(IDC_Async_Print_File, &Cprinter::OnBnClickedAsyncPrintFile)
	ON_BN_CLICKED(IDC_AsyncPrintData, &Cprinter::OnBnClickedAsyncprintdata)
	ON_BN_CLICKED(IDC_Async_Dispense_Paper, &Cprinter::OnBnClickedAsyncDispensePaper)
	ON_BN_CLICKED(IDC_AsyncReset, &Cprinter::OnBnClickedAsyncreset)
	ON_BN_CLICKED(IDC_Async_CutPaper, &Cprinter::OnBnClickedAsyncCutpaper)
	ON_BN_CLICKED(IDC_Async_PrintForm, &Cprinter::OnBnClickedAsyncPrintform)
	ON_BN_CLICKED(IDC_CleanUp, &Cprinter::OnBnClickedCleanup)
	ON_BN_CLICKED(IDC_Close, &Cprinter::OnBnClickedClose)
	ON_BN_CLICKED(IDC_AsyncClose, &Cprinter::OnBnClickedAsyncclose)
END_MESSAGE_MAP()

LRESULT Cprinter::OnOpenComplete(WPARAM wParam, LPARAM lParam)
{
	CString strTxt;
	strTxt.Format(L"OnOpenComplete Event Received prnter");
	AppendStatus(strTxt);
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT Cprinter::OnCloseComplete(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT Cprinter::OnLockComplete(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT Cprinter::OnUnlockComplete(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT Cprinter::OnRegisterComplete(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT Cprinter::OnDeregisterComplete(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT Cprinter::OnGetInfoComplete(WPARAM wParam, LPARAM lParam)
{
	pwfsRes = (WFSRESULT*) lParam;
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	pwfsRes->lpBuffer = pWESResult;
	return nRes;
	m_pXFSManager->WFSFreeResult(pWESResult);
}

LRESULT Cprinter::OnExecuteComplete(WPARAM wParam, LPARAM lParam)
{
	pwfsRes = (WFSRESULT*)lParam;
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	pwfsRes->lpBuffer = pWESResult;
	return pwfsRes->hResult;
}

LRESULT Cprinter::OnTimerEvent(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT Cprinter::OnExecuteEvent(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	switch (pWESResult->u.dwEventID)
	{
	case WFS_EXEE_PTR_NOMEDIA:
	{
		CString strTxt;
		strTxt.Format(L"Paper Empty");
		AppendStatus(strTxt);
	}
	break;
	case WFS_SRVE_PTR_MEDIAINSERTED:
	{
		CString strTxt;
		strTxt.Format(L"Paper Inserted");
		AppendStatus(strTxt);
	}
	break;
	}

	return nRes;
}

LRESULT Cprinter::OnServiceEvent(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT Cprinter::OnUserEvent(WPARAM wParam, LPARAM lParam)
{
	LRESULT nRes = WFS_SUCCESS;
	LPWFSRESULT pWESResult = (LPWFSRESULT)lParam;
	return nRes;
}

LRESULT Cprinter::OnSystemEvent(WPARAM wParam, LPARAM lParam)
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
			strTxt.Format(L"Printer online");
		else
			strTxt.Format(L"Printer offline");
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

// Cprinter message handlers

void Cprinter::AppendStatus(CString strTxt)
{
	CString txt;
	m_richprint.GetWindowText(txt);
	txt.Append(_T("\r\n"));
	txt += strTxt;
	m_richprint.SetWindowText(txt);
}
void Cprinter::Lock()
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



void Cprinter::AsyncLock()
{
	HRESULT hRes;
	CString strTxt;
	WFSRESULT* pwfsRes;
	if ((hRes = m_pXFSManager->WFSAsyncLock(m_hService, WFS_INDEFINITE_WAIT, m_hWnd, &m_requestId)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSAsyncLock HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"WFSAsyncLock completed");
	}
	AppendStatus(strTxt);
}

void Cprinter::AsyncUnLock()
{
	HRESULT hRes;
	CString strTxt;
	if ((hRes = m_pXFSManager->WFSAsyncUnlock(m_hService, m_hWnd, &m_requestId)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSAsyncUnlock HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"WFSAsyncUnlock completed");
	}
	AppendStatus(strTxt);
}



void Cprinter::UnLock()
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


void Cprinter::OnBnClickedOpen()
{

	HRESULT hRes;
	CString strTxt;
	if ((hRes = m_pXFSManager->WFSOpen("ITASPrinter", WFS_DEFAULT_HAPP, "PTRSPTest", WFS_TRACE_ALL_SPI,
		WFS_INDEFINITE_WAIT, 0x00001403, &m_wfsServiceVersion, &m_wfsSPIVersion, &m_hService)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSOpen HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"WFSOpen completed");
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
	LPWFSPTRCAPS lpCaps;
	if ((hRes = m_pXFSManager->WFSGetInfo(m_hService, WFS_INF_PTR_CAPABILITIES, NULL, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSGetInfo - WFS_INF_PTR_CAPABILITIES HRESULT = %d", hRes);
	}
	else
	{
		lpCaps = (LPWFSPTRCAPS)pwfsRes->lpBuffer;
		strTxt.Format(L"WFSGetInfo - WFS_INF_PTR_CAPABILITIES completed\r\n");
	}
	AppendStatus(strTxt);
	//m_pXFSManager->WFMFreeBuffer(pwfsRes);

	pwfsRes = NULL;
	LPWFSPTRSTATUS lpStatus;
	if ((hRes = m_pXFSManager->WFSGetInfo(m_hService, WFS_INF_PTR_STATUS, NULL, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSGetInfo - WFS_INF_PTR_STATUS HRESULT = %d", hRes);
	}
	else
	{
		lpStatus = (LPWFSPTRSTATUS)pwfsRes->lpBuffer;
		strTxt.Format(L"WFSGetInfo - WFS_INF_PTR_STATUS completed\r\n");
	}
	AppendStatus(strTxt);
	//m_pXFSManager->WFMFreeBuffer(pwfsRes);

	try
	{
		pwfsRes = NULL;
		if ((hRes = m_pXFSManager->WFSGetInfo(m_hService, WFS_INF_PTR_MEDIA_LIST, NULL, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSGetInfo - WFS_INF_PTR_MEDIA_LIST HRESULT = %d", hRes);
		}
		else
		{
			LPSTR lpMediaList = (LPSTR)pwfsRes->lpBuffer;
			strTxt.Format(L"WFSGetInfo - WFS_INF_PTR_MEDIA_LIST completed : %s\r\n", CString(lpMediaList));
		}
		AppendStatus(strTxt);
		//m_pXFSManager->WFMFreeBuffer(pwfsRes);

		pwfsRes = NULL;
		LPSTR lpFormList = NULL;
		if ((hRes = m_pXFSManager->WFSGetInfo(m_hService, WFS_INF_PTR_FORM_LIST, NULL, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSGetInfo - WFS_INF_PTR_FORM_LIST HRESULT = %d", hRes);
		}
		else
		{
			lpFormList = (LPSTR)pwfsRes->lpBuffer;
			strTxt.Format(L"WFSGetInfo - WFS_INF_PTR_FORM_LIST completed : %s\r\n", CString(lpFormList));
		}
		AppendStatus(strTxt);
		//m_pXFSManager->WFMFreeBuffer(pwfsRes);
/*		CStringA str(lpFormList);

		pwfsRes = NULL;
		if ((hRes = m_pXFSManager->WFSGetInfo(m_hService, WFS_INF_PTR_QUERY_FORM, str.GetBuffer(), WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSGetInfo - WFS_INF_PTR_QUERY_FORM HRESULT = %d", hRes);
		}
		else
		{
			LPWFSFRMHEADER lpForm = (LPWFSFRMHEADER)pwfsRes->lpBuffer;
			strTxt.Format(L"WFSGetInfo - WFS_INF_PTR_QUERY_FORM completed : %s\r\n", CString(lpForm->lpszFormName));
		}
		AppendStatus(strTxt);
		m_pXFSManager->WFMFreeBuffer(pwfsRes);

		pwfsRes = NULL;
		WFSPTRQUERYFIELD qField;
		CStringA field("Account Number");
		m_pXFSManager->WFMAllocateBuffer(64, WFS_MEM_SHARE | WFS_MEM_ZEROINIT, (LPVOID*)&qField.lpszFieldName);
		m_pXFSManager->WFMAllocateBuffer(64, WFS_MEM_SHARE | WFS_MEM_ZEROINIT, (LPVOID*)&qField.lpszFormName);

		strncpy_s(qField.lpszFormName, 64, str.GetBuffer(), str.GetLength());
		strncpy_s(qField.lpszFieldName, 64, field.GetBuffer(), field.GetLength());

		if ((hRes = m_pXFSManager->WFSGetInfo(m_hService, WFS_INF_PTR_QUERY_FIELD, &qField, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSGetInfo - WFS_INF_PTR_QUERY_FIELD HRESULT = %d", hRes);
		}
		else
		{
			LPWFSFRMFIELD* lpField = (LPWFSFRMFIELD*)pwfsRes->lpBuffer;
			strTxt.Format(L"WFSGetInfo - WFS_INF_PTR_QUERY_FIELD completed : %s\r\n", CString(lpField[0]->lpszFieldName));
		}
		AppendStatus(strTxt);
		m_pXFSManager->WFMFreeBuffer(pwfsRes);*/
	}
	catch (CException& e)
	{

	}
	UnLock();
}


void Cprinter::OnBnClickedStartUp()
{
	HRESULT hRes;
	CString strTxt;
	if ((hRes = m_pXFSManager->WFSStartUp(0x1403, &m_wfsXFSManagerVersion)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSStartUp HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"Printer   Startup completed ");
	}
	AppendStatus(strTxt);
}


void Cprinter::OnBnClickedAsyncOPen()
{
	HRESULT hRes;
	CString strTxt;
	if ((hRes = m_pXFSManager->WFSAsyncOpen("ITASPrinter", WFS_DEFAULT_HAPP, "PTRSPTest", WFS_TRACE_ALL_SPI,
		WFS_INDEFINITE_WAIT,&m_hService,m_hWnd, 0x00001403,&m_wfsServiceVersion,&m_wfsSPIVersion,&m_requestId)) != WFS_SUCCESS)
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
	LPWFSPTRCAPS lpCaps;
	if ((hRes = m_pXFSManager->WFSAsyncGetInfo(m_hService, WFS_INF_PTR_CAPABILITIES, NULL, WFS_INDEFINITE_WAIT,m_hWnd,&m_requestId)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSAsyncGetInfo - WFS_INF_PTR_CAPABILITIES HRESULT = %d", hRes);
	}
	else
	{
		lpCaps = (LPWFSPTRCAPS)pwfsRes->lpBuffer;
		strTxt.Format(L"WFSAsyncGetInfo - WFS_INF_PTR_CAPABILITIES completed\r\n");
	}
	AppendStatus(strTxt);
	//m_pXFSManager->WFMFreeBuffer(pwfsRes);

	pwfsRes = NULL;
	LPWFSPTRSTATUS lpStatus;
	if ((hRes = m_pXFSManager->WFSAsyncGetInfo(m_hService, WFS_INF_PTR_STATUS, NULL, WFS_INDEFINITE_WAIT, m_hWnd, &m_requestId)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSAsyncGetInfo - WFS_INF_PTR_STATUS HRESULT = %d", hRes);
	}
	else
	{
		lpStatus = (LPWFSPTRSTATUS)pwfsRes->lpBuffer;
		strTxt.Format(L"WFSAsyncGetInfo - WFS_INF_PTR_STATUS completed\r\n");
	}
	AppendStatus(strTxt);
	//m_pXFSManager->WFMFreeBuffer(pwfsRes);

	try
	{
		pwfsRes = NULL;
		if ((hRes = m_pXFSManager->WFSAsyncGetInfo(m_hService, WFS_INF_PTR_MEDIA_LIST, NULL, WFS_INDEFINITE_WAIT, m_hWnd, &m_requestId)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSAsyncGetInfo - WFS_INF_PTR_MEDIA_LIST HRESULT = %d", hRes);
		}
		else
		{
			LPSTR lpMediaList = (LPSTR)pwfsRes->lpBuffer;
			strTxt.Format(L"WFSAsyncGetInfo - WFS_INF_PTR_MEDIA_LIST completed : %s\r\n", CString(lpMediaList));
		}
		AppendStatus(strTxt);
		//m_pXFSManager->WFMFreeBuffer(pwfsRes);

		pwfsRes = NULL;
		LPSTR lpFormList = NULL;
		if ((hRes = m_pXFSManager->WFSAsyncGetInfo(m_hService, WFS_INF_PTR_MEDIA_LIST, NULL, WFS_INDEFINITE_WAIT, m_hWnd, &m_requestId)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSAsyncGetInfo - WFS_INF_PTR_FORM_LIST HRESULT = %d", hRes);
		}
		else
		{
			lpFormList = (LPSTR)pwfsRes->lpBuffer;
			strTxt.Format(L"WFSAsyncGetInfo - WFS_INF_PTR_FORM_LIST completed : %s\r\n", CString(lpFormList));
		}
		AppendStatus(strTxt);
		//m_pXFSManager->WFMFreeBuffer(pwfsRes);
/*		CStringA str(lpFormList);

		pwfsRes = NULL;
		if ((hRes = m_pXFSManager->WFSGetInfo(m_hService, WFS_INF_PTR_QUERY_FORM, str.GetBuffer(), WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSGetInfo - WFS_INF_PTR_QUERY_FORM HRESULT = %d", hRes);
		}
		else
		{
			LPWFSFRMHEADER lpForm = (LPWFSFRMHEADER)pwfsRes->lpBuffer;
			strTxt.Format(L"WFSGetInfo - WFS_INF_PTR_QUERY_FORM completed : %s\r\n", CString(lpForm->lpszFormName));
		}
		AppendStatus(strTxt);
		m_pXFSManager->WFMFreeBuffer(pwfsRes);

		pwfsRes = NULL;
		WFSPTRQUERYFIELD qField;
		CStringA field("Account Number");
		m_pXFSManager->WFMAllocateBuffer(64, WFS_MEM_SHARE | WFS_MEM_ZEROINIT, (LPVOID*)&qField.lpszFieldName);
		m_pXFSManager->WFMAllocateBuffer(64, WFS_MEM_SHARE | WFS_MEM_ZEROINIT, (LPVOID*)&qField.lpszFormName);

		strncpy_s(qField.lpszFormName, 64, str.GetBuffer(), str.GetLength());
		strncpy_s(qField.lpszFieldName, 64, field.GetBuffer(), field.GetLength());

		if ((hRes = m_pXFSManager->WFSGetInfo(m_hService, WFS_INF_PTR_QUERY_FIELD, &qField, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
		{
			strTxt.Format(L"WFSGetInfo - WFS_INF_PTR_QUERY_FIELD HRESULT = %d", hRes);
		}
		else
		{
			LPWFSFRMFIELD* lpField = (LPWFSFRMFIELD*)pwfsRes->lpBuffer;
			strTxt.Format(L"WFSGetInfo - WFS_INF_PTR_QUERY_FIELD completed : %s\r\n", CString(lpField[0]->lpszFieldName));
		}
		AppendStatus(strTxt);
		m_pXFSManager->WFMFreeBuffer(pwfsRes);*/
	}
	catch (CException& e)
	{

	}
	AsyncUnLock();
}


void Cprinter::OnEnChangeRichedit21()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void Cprinter::OnEnChangeEditPrintdata()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}





void Cprinter::OnBnClickedSelectFile()
{
	CFileDialog dlg(true);
	if (dlg.DoModal() == IDOK)
	{
		m_edtFileName.SetWindowText(dlg.GetPathName());
	}
}


void Cprinter::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void Cprinter::OnBnClickedPrintfile()
{
	HRESULT hRes;
	CString strTxt;
	m_edtFileName.GetWindowText(strTxt);
	CStringA strData(strTxt);

	WFSPTRPRINTRAWFILE ipData;
	m_pXFSManager->WFMAllocateBuffer(strData.GetLength() + 1, WFS_MEM_SHARE | WFS_MEM_ZEROINIT, (LPVOID*)&ipData.lpszFileName);
	memset(ipData.lpszFileName, 0, strData.GetLength() + 1);
	strcpy_s(ipData.lpszFileName, strData.GetLength() + 1, CStringA(strData).GetBuffer());
	ipData.dwMediaControl = 0;
	ipData.dwPaperSource = 1;
	Lock();

	WFSRESULT* pwfsRes;
	if ((hRes = m_pXFSManager->WFSExecute(m_hService, WFS_CMD_PTR_PRINT_RAW_FILE, &ipData, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSExecute HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"WFSExecute - WFS_CMD_PTR_PRINT_RAW_FILE completed");
	}
	AppendStatus(strTxt);

	UnLock();

}


void Cprinter::OnBnClickedPrintdata()
{
	HRESULT hRes;
	CString strTxt;
	m_editprintdata.GetWindowText(strTxt);
	CStringA strData(strTxt);
	WFSPTRRAWDATA ipData;
	m_pXFSManager->WFMAllocateBuffer(strData.GetLength() + 1, WFS_MEM_SHARE | WFS_MEM_ZEROINIT, (LPVOID*)&ipData.lpbData);
	memset(ipData.lpbData, 0, strData.GetLength() + 1);
	memcpy(ipData.lpbData, CStringA(strData).GetBuffer(), strData.GetLength() + 1);
	ipData.ulSize = strData.GetLength();
	ipData.wInputData = 1;

	Lock();

	WFSRESULT* pwfsRes;
	if ((hRes = m_pXFSManager->WFSExecute(m_hService, WFS_CMD_PTR_RAW_DATA, &ipData, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSExecute HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"WFSExecute - WFS_CMD_PTR_RAW_DATA completed");
	}
	AppendStatus(strTxt);

	UnLock();
}


void Cprinter::OnBnClickedReset()
{
	HRESULT hRes;
	CString strTxt;
	WFSPTRRESET reset;
	reset.dwMediaControl = WFS_PTR_CTRLEXPEL;
	reset.usRetractBinNumber = 0;
	Lock();

	WFSRESULT* pwfsRes;
	if ((hRes = m_pXFSManager->WFSExecute(m_hService, WFS_CMD_PTR_RESET, &reset, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSExecute HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"WFSExecute - WFS_PTR_RESET completed");
	}
	AppendStatus(strTxt);

	UnLock();
}


void Cprinter::OnBnClickedDispensepaper()
{
	HRESULT hRes;
	CString strTxt;
	LPWORD ipData;
	m_pXFSManager->WFMAllocateBuffer(sizeof(WORD), WFS_MEM_SHARE | WFS_MEM_ZEROINIT, (LPVOID*)&ipData);
	*ipData = WFS_PTR_PAPERANY;
	Lock();

	WFSRESULT* pwfsRes;
	if ((hRes = m_pXFSManager->WFSExecute(m_hService, WFS_CMD_PTR_DISPENSE_PAPER, ipData, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSExecute HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"WFSExecute - WFS_CMD_PTR_DISPENSE_PAPER completed");
	}
	AppendStatus(strTxt);

	UnLock();
	//m_pXFSManager->WFMFreeBuffer(ipData);
	//m_pXFSManager->WFMFreeBuffer(pwfsRes);
}


void Cprinter::OnBnClickedCutpaper()
{
	HRESULT hRes;
	CString strTxt;
	LPWORD ipData;
	m_pXFSManager->WFMAllocateBuffer(sizeof(WORD), WFS_MEM_SHARE | WFS_MEM_ZEROINIT, (LPVOID*)&ipData);
	*ipData = WFS_PTR_CTRLCUT;
	Lock();

	WFSRESULT* pwfsRes;
	if ((hRes = m_pXFSManager->WFSExecute(m_hService, WFS_CMD_PTR_CONTROL_MEDIA, ipData, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSExecute HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"WFSExecute - WFS_PTR_CTRLCUT completed");
	}
	AppendStatus(strTxt);

	UnLock();
	//m_pXFSManager->WFMFreeBuffer(ipData);
	//m_pXFSManager->WFMFreeBuffer(pwfsRes);
	
}


void Cprinter::OnBnClickedPrintform()
{
	HRESULT hRes;
	CString strTxt;
	WFSPTRPRINTFORM Form = { 0 };
	CStringA strForm = "DemoForm";
	CStringA strMedia = "Media";
	CStringArray strField;
	strField.Add(L"Name=MOHANKUMAR");
	strField.Add(L"Account Number=123456789");

	char buff[1024] = { 0 };
	int nLen = 0;
	for (int i = 0; i < strField.GetCount(); i++)
	{
		CStringA str = CStringA(strField.GetAt(i));
		memcpy(&buff[nLen], str.GetBuffer(), str.GetLength());
		nLen += str.GetLength() + 1;
	}
	nLen++;

	m_pXFSManager->WFMAllocateBuffer(strForm.GetLength() + 1, WFS_MEM_SHARE | WFS_MEM_ZEROINIT, (LPVOID*)&Form.lpszFormName);
	if (Form.lpszFormName)
		strcpy_s(Form.lpszFormName, strForm.GetLength() + 1, strForm.GetBuffer());
	m_pXFSManager->WFMAllocateBuffer(strMedia.GetLength() + 1, WFS_MEM_SHARE | WFS_MEM_ZEROINIT, (LPVOID*)&Form.lpszMediaName);
	if (Form.lpszMediaName)
		strcpy_s(Form.lpszMediaName, strMedia.GetLength() + 1, strMedia.GetBuffer());
	Form.wOffsetX = 0;
	Form.wOffsetY = 0;

	m_pXFSManager->WFMAllocateBuffer(nLen, WFS_MEM_SHARE | WFS_MEM_ZEROINIT, (LPVOID*)&Form.lpszFields);
	if (Form.lpszFields)
		memcpy_s(Form.lpszFields, nLen, buff, nLen);
	Form.wPaperSource = WFS_PTR_PAPERUPPER;
	Lock();

	WFSRESULT* pwfsRes;
	if ((hRes = m_pXFSManager->WFSExecute(m_hService, WFS_CMD_PTR_PRINT_FORM, &Form, WFS_INDEFINITE_WAIT, &pwfsRes)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSExecute HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"WFSExecute - WFS_CMD_PTR_DISPENSE_PAPER completed");
	}
	AppendStatus(strTxt);

	UnLock();
	//m_pXFSManager->WFMFreeBuffer(pwfsRes);
}


void Cprinter::OnBnClickedAsyncPrintFile()
{
	HRESULT hRes;
	CString strTxt;
	m_edtFileName.GetWindowText(strTxt);
	CStringA strData(strTxt);

	WFSPTRPRINTRAWFILE ipData;
	m_pXFSManager->WFMAllocateBuffer(strData.GetLength() + 1, WFS_MEM_SHARE | WFS_MEM_ZEROINIT, (LPVOID*)&ipData.lpszFileName);
	memset(ipData.lpszFileName, 0, strData.GetLength() + 1);
	strcpy_s(ipData.lpszFileName, strData.GetLength() + 1, CStringA(strData).GetBuffer());
	ipData.dwMediaControl = 0;
	ipData.dwPaperSource = 1;
	AsyncLock();

	WFSRESULT* pwfsRes;
	if ((hRes = m_pXFSManager->WFSAsyncExecute(m_hService, WFS_CMD_PTR_PRINT_RAW_FILE, &ipData, WFS_INDEFINITE_WAIT,m_hWnd,&m_requestId)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSAsyncExecute HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"WFSAsyncExecute - WFS_CMD_PTR_PRINT_RAW_FILE completed");
	}
	AppendStatus(strTxt);

	AsyncUnLock();

}


void Cprinter::OnBnClickedAsyncprintdata()
{
	HRESULT hRes;
	CString strTxt;
	m_editprintdata.GetWindowText(strTxt);
	CStringA strData(strTxt);
	WFSPTRRAWDATA ipData;
	m_pXFSManager->WFMAllocateBuffer(strData.GetLength() + 1, WFS_MEM_SHARE | WFS_MEM_ZEROINIT, (LPVOID*)&ipData.lpbData);
	memset(ipData.lpbData, 0, strData.GetLength() + 1);
	memcpy(ipData.lpbData, CStringA(strData).GetBuffer(), strData.GetLength() + 1);
	ipData.ulSize = strData.GetLength();
	ipData.wInputData = 1;

	AsyncLock();

	WFSRESULT* pwfsRes;
	if ((hRes = m_pXFSManager->WFSAsyncExecute(m_hService, WFS_CMD_PTR_RAW_DATA, &ipData, WFS_INDEFINITE_WAIT,m_hWnd,&m_requestId)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSAsyncExecute HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"WFSAsyncExecute - WFS_CMD_PTR_RAW_DATA completed");
	}
	AppendStatus(strTxt);

	AsyncUnLock();
}


void Cprinter::OnBnClickedAsyncDispensePaper()
{
	HRESULT hRes;
	CString strTxt;
	LPWORD ipData;
	m_pXFSManager->WFMAllocateBuffer(sizeof(WORD), WFS_MEM_SHARE | WFS_MEM_ZEROINIT, (LPVOID*)&ipData);
	*ipData = WFS_PTR_PAPERANY;
	AsyncLock();

	WFSRESULT* pwfsRes;
	if ((hRes = m_pXFSManager->WFSAsyncExecute(m_hService, WFS_CMD_PTR_DISPENSE_PAPER, ipData, WFS_INDEFINITE_WAIT,m_hWnd,&m_requestId) )!= WFS_SUCCESS)
	{
		strTxt.Format(L"WFSAsyncExecute HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"WFSAsyncExecute - WFS_CMD_PTR_DISPENSE_PAPER completed");
	}
	AppendStatus(strTxt);

	AsyncUnLock();
	//m_pXFSManager->WFMFreeBuffer(ipData);
	//m_pXFSManager->WFMFreeBuffer(pwfsRes);
}


void Cprinter::OnBnClickedAsyncreset()
{
	HRESULT hRes;
	CString strTxt;
	WFSPTRRESET reset;
	reset.dwMediaControl = WFS_PTR_CTRLEXPEL;
	reset.usRetractBinNumber = 0;
	AsyncLock();

	WFSRESULT* pwfsRes;
	if ((hRes = m_pXFSManager->WFSAsyncExecute(m_hService, WFS_CMD_PTR_RESET, &reset, WFS_INDEFINITE_WAIT,m_hWnd,&m_requestId)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSAsyncExecute HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"WFSAsyncExecute - WFS_PTR_RESET completed");
	}
	AppendStatus(strTxt);

	AsyncUnLock();
}


void Cprinter::OnBnClickedAsyncCutpaper()
{
	HRESULT hRes;
	CString strTxt;
	LPWORD ipData;
	m_pXFSManager->WFMAllocateBuffer(sizeof(WORD), WFS_MEM_SHARE | WFS_MEM_ZEROINIT, (LPVOID*)&ipData);
	*ipData = WFS_PTR_CTRLCUT;
	AsyncLock();

	WFSRESULT* pwfsRes;
	if ((hRes = m_pXFSManager->WFSAsyncExecute(m_hService, WFS_CMD_PTR_CONTROL_MEDIA, ipData, WFS_INDEFINITE_WAIT,m_hWnd,&m_requestId)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSAsyncExecute HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"WFSAsyncExecute - WFS_PTR_CTRLCUT completed");
	}
	AppendStatus(strTxt);

	AsyncUnLock();
	//m_pXFSManager->WFMFreeBuffer(ipData);
	//m_pXFSManager->WFMFreeBuffer(pwfsRes);
}


void Cprinter::OnBnClickedAsyncPrintform()
{
	HRESULT hRes;
	CString strTxt;
	WFSPTRPRINTFORM Form = { 0 };
	CStringA strForm = "DemoForm";
	CStringA strMedia = "Media";
	CStringArray strField;
	strField.Add(L"Name=MOHANKUMAR");
	strField.Add(L"Account Number=123456789");

	char buff[1024] = { 0 };
	int nLen = 0;
	for (int i = 0; i < strField.GetCount(); i++)
	{
		CStringA str = CStringA(strField.GetAt(i));
		memcpy(&buff[nLen], str.GetBuffer(), str.GetLength());
		nLen += str.GetLength() + 1;
	}
	nLen++;

	m_pXFSManager->WFMAllocateBuffer(strForm.GetLength() + 1, WFS_MEM_SHARE | WFS_MEM_ZEROINIT, (LPVOID*)&Form.lpszFormName);
	if (Form.lpszFormName)
		strcpy_s(Form.lpszFormName, strForm.GetLength() + 1, strForm.GetBuffer());
	m_pXFSManager->WFMAllocateBuffer(strMedia.GetLength() + 1, WFS_MEM_SHARE | WFS_MEM_ZEROINIT, (LPVOID*)&Form.lpszMediaName);
	if (Form.lpszMediaName)
		strcpy_s(Form.lpszMediaName, strMedia.GetLength() + 1, strMedia.GetBuffer());
	Form.wOffsetX = 0;
	Form.wOffsetY = 0;

	m_pXFSManager->WFMAllocateBuffer(nLen, WFS_MEM_SHARE | WFS_MEM_ZEROINIT, (LPVOID*)&Form.lpszFields);
	if (Form.lpszFields)
		memcpy_s(Form.lpszFields, nLen, buff, nLen);
	Form.wPaperSource = WFS_PTR_PAPERUPPER;
	AsyncLock();

	WFSRESULT* pwfsRes;
	if ((hRes = m_pXFSManager->WFSAsyncExecute(m_hService, WFS_CMD_PTR_PRINT_FORM, &Form, WFS_INDEFINITE_WAIT,m_hWnd,&m_requestId)) != WFS_SUCCESS)
	{
		strTxt.Format(L"WFSAsyncExecute HRESULT = %d", hRes);
	}
	else
	{
		strTxt.Format(L"WFSAsyncExecute - WFS_CMD_PTR_DISPENSE_PAPER completed");
	}
	AppendStatus(strTxt);

	AsyncUnLock();
	//m_pXFSManager->WFMFreeBuffer(pwfsRes);	
}


void Cprinter::OnBnClickedCleanup()
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
}


void Cprinter::OnBnClickedClose()
{
	HRESULT hRes;
	CString strTxt;

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
	}
	AppendStatus(strTxt);
}


void Cprinter::OnBnClickedAsyncclose()
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
