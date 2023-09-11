#include "stdafx.h"
#include "MFCXFSInterface.h"
#include "messagewnd.h"

messagewnd::messagewnd()
{
	SetModuleName("MFCXFSInterface");
}
messagewnd::~messagewnd()
{
}



BEGIN_MESSAGE_MAP(messagewnd, CWnd)
	ON_MESSAGE(WFS_SYSTEM_EVENT, OnSystemEvent)
END_MESSAGE_MAP()

LRESULT messagewnd::OnSystemEvent(WPARAM wParam, LPARAM lParam)
{
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
			LPWFSDEVSTATUS pDevStatus = (LPWFSDEVSTATUS)pWESResult->lpBuffer;
			if (pDevStatus->dwState == WFS_STAT_DEVONLINE)
			{
				strTxt.Format(L"Camera online");
				LOG_DATA(LOG_DEBUG, (CStringA)strTxt);
				MessageBox(L"Camera Online", 0, 0);
			}
			else
			{
				strTxt.Format(L"Camera offline");
				LOG_DATA(LOG_DEBUG, (CStringA)strTxt);
				MessageBox(L"Camera Offline", 0, 0);
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
			LPWFSDEVSTATUS pDevStatus = (LPWFSDEVSTATUS)pWESResult->lpBuffer;
			if (pDevStatus->dwState == WFS_STAT_DEVONLINE)
			{
				strTxt.Format(L"Printer online");
				LOG_DATA(LOG_DEBUG, (CStringA)strTxt);
				MessageBox(L"Printer Online", 0, 0);
			}
			else
			{
				strTxt.Format(L"Printer offline");
				LOG_DATA(LOG_DEBUG, (CStringA)strTxt);
				MessageBox(L"Printer Offline", 0, 0);
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
				strTxt.Format(L"Pinpad online");
				LOG_DATA(LOG_DEBUG, (CStringA)strTxt);
				MessageBox(L"PinPad Online", 0, 0);
			}
			else
			{
				strTxt.Format(L"PinPad offline");
				LOG_DATA(LOG_DEBUG, (CStringA)strTxt);
				MessageBox(L"PinPad Offline", 0, 0);
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

