
// MyMFCDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MyMFC.h"
#include "MyMFCDlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif
HMODULE hdll;
HMODULE husb;
HWND m_hWnd;
HSERVICE hService;
// CAboutDlg dialog used for App About
LPVOID lpThreadParameter = NULL;
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
}; 
CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyMFCDlg dialog



CMyMFCDlg::CMyMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT22, m_cntrl);
}

BEGIN_MESSAGE_MAP(CMyMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMyMFCDlg::OnBnClickedBtopen)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyMFCDlg::OnBnClickedBtstop)
	ON_BN_CLICKED(IDC_BUTTON4, &CMyMFCDlg::OnBnClickedBtstart)
	ON_BN_CLICKED(IDC_BUTTON5, &CMyMFCDlg::OnBnClickedBtlock)
	ON_BN_CLICKED(IDCANCEL, &CMyMFCDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON6, &CMyMFCDlg::OnBnClickedBttakepic)
	ON_BN_CLICKED(IDC_BUTTON7, &CMyMFCDlg::OnBnClickedBtRegister)
	ON_BN_CLICKED(IDC_BUTTON9, &CMyMFCDlg::OnBnClickedBtDeregister)
	ON_BN_CLICKED(IDC_BUTTON10, &CMyMFCDlg::OnBnClickedBtUnlock)
	ON_BN_CLICKED(IDC_BUTTON11, &CMyMFCDlg::OnBnClickedBtGetinfocap)
	ON_EN_CHANGE(IDC_RICHEDIT22, &CMyMFCDlg::OnEnChangeRichedit22)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyMFCDlg::OnBnClickedBtGetinfostatus)
	ON_BN_CLICKED(IDC_BUTTON8, &CMyMFCDlg::OnBnClickedBtreset)
	ON_BN_CLICKED(IDC_BUTTON12, &CMyMFCDlg::OnBnClickedBttakepicex)
END_MESSAGE_MAP()
// CMyMFCDlg message handlers


BOOL CMyMFCDlg::OnInitDialog()
{
	
	CString strtext;
	CDialogEx::OnInitDialog();
	
	
	hdll = LoadLibraryA("C:\\Revathi\\Projects\\iTAS-XFS-dev\\xfs-spi\\Bin\\CAMSPI.dll");

	

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE  unless you set the focus to a control


}

void CMyMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CMyMFCDlg::AppendStatus(CString strtext)
{
	CString txt;
	m_cntrl.GetWindowText(txt);
	txt.Append(_T("\r\n"));
	txt += strtext;
	m_cntrl.SetWindowText(txt);
}


void CMyMFCDlg::OnBnClickedBtopen()
{
	
	CString strtext;
	pfnWFPOpen fnWFPOpen;

		fnWFPOpen = (pfnWFPOpen)GetProcAddress(hdll, "WFPOpen");
		if (NULL != fnWFPOpen)
		{
			
			if( fnWFPOpen(hService, "ITASCamera", 
				WFS_DEFAULT_HAPP, 
				"MyMFC", 
				WFS_TRACE_ALL_SPI, 
				WFS_INDEFINITE_WAIT,
				m_hWnd,
				0x00000001,
				hdll, 
				0x00001403,
				&m_wfsSPIVersion, 
				0x00001403, 
				&m_wfsServiceVersion)== WFS_SUCCESS)
			{
				strtext.Format(L"WFPOpen Success ");
			}
			else
			{
				strtext.Format(L"WFPOpen Call failed ");
				
			}
			//AppendStatus(strtext);
		}
		else
		{
			strtext.Format(L"Library load failed");
			GetDlgItem(IDC_STATIC)->SetWindowTextW(strtext);
		}
		AppendStatus(strtext);
}
	
	
	// TODO: Add your control notification handler code here

void CMyMFCDlg::OnBnClickedBtstop()
{
	CString strtext;
	pfnWFPClose fnWFPClose;

		fnWFPClose = (pfnWFPClose)GetProcAddress(hdll, "WFPClose");
		if (fnWFPClose != NULL)
		{
			if (fnWFPClose(hService, m_hWnd, 0x00000001) == WFS_SUCCESS)
			{
				strtext.Format(L"WFPClose success");
			}
			else
			{
				strtext.Format(L"WFPClose failed %d", GetLastError());
			}
		}
		else
		{
			strtext.Format(L"WFPClose load failed");
			GetDlgItem(IDC_STATIC)->SetWindowTextW(strtext);
		}
		AppendStatus(strtext);
}

void CMyMFCDlg::OnBnClickedBtstart()
{
	
	CString strtext;
	if (hdll != NULL)
	{
		strtext.Format(L"Library load Success");
		GetDlgItem(IDC_STATIC)->SetWindowTextW(strtext);
	}
	else
	{
		strtext.Format(L"Library load Failed");
		GetDlgItem(IDC_STATIC)->SetWindowTextW(strtext);
	}
	//Appendstatus(strtext);
	CreateHiddenWindowAndRegisterForUSBEvents(lpThreadParameter);
}


void CMyMFCDlg::OnBnClickedBtlock()
{
	CString strtext;
	pfnWFPLock fnWFPLock;
	fnWFPLock = (pfnWFPLock)GetProcAddress(hdll, "WFPLock");
	if (fnWFPLock != NULL)
	{
		if (fnWFPLock(hService,WFS_INDEFINITE_WAIT, m_hWnd, 0x00000001) == WFS_SUCCESS)
		{
			strtext.Format(L"WFPLock success");
		}
		else
		{
			strtext.Format(L"WFPLock failed %d", GetLastError());
		}
		//AppendStatus(strtext);
	}
	else
	{
		strtext.Format(L"WFPLock load failed");
	}
	AppendStatus(strtext);
}


void CMyMFCDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
	exit(0);
}


void CMyMFCDlg::OnBnClickedBttakepic()
{
	CString strtext;
	pfnWFPExecute fnWFPExecute;
	ipData.wCamera = WFS_CAM_EXITSLOT;
	ipData.lpszCamData = "Test data from takepicture";
	ipData.lpszUNICODECamData = NULL;
	fnWFPExecute = (pfnWFPExecute)GetProcAddress(hdll, "WFPExecute");
	if (fnWFPExecute != NULL)
	{
		if (fnWFPExecute(hService, WFS_CMD_CAM_TAKE_PICTURE,&ipData,WFS_INDEFINITE_WAIT, m_hWnd, 0x00000001) == WFS_SUCCESS)
		{
			strtext.Format(L"WFPExecute  success");
		}
		else
		{
			strtext.Format(L"WFPExecute failed %d", GetLastError());
		}
	}
	else
	{
		strtext.Format(L"WFPLock load failed");
		GetDlgItem(IDC_STATIC)->SetWindowTextW(strtext);
	}
	AppendStatus(strtext);
}



void CMyMFCDlg::OnBnClickedBtRegister()
{
	CString strtext;
	pfnWFPRegister fnWFPRegister;
	fnWFPRegister = (pfnWFPRegister)GetProcAddress(hdll, "WFPRegister");
	if (fnWFPRegister != NULL)
	{
		if (fnWFPRegister(hService,WFS_EXECUTE_EVENT|WFS_USER_EVENT|WFS_SYSTEM_EVENT,m_hWnd,m_hWnd, 0x00000001) == WFS_SUCCESS)
		{
			strtext.Format(L"WFPRegister success");
		}
		else
		{
			strtext.Format(L"WFPRegister failed %d", GetLastError());
		}
		//AppendStatus(strtext);
	}
	else
	{
		strtext.Format(L"WFPRegister load failed");
	}
	AppendStatus(strtext);
}

void CMyMFCDlg::OnBnClickedBtDeregister()
{
	CString strtext;
	pfnWFPDeregister fnWFPDeregister;
	fnWFPDeregister = (pfnWFPDeregister)GetProcAddress(hdll, "WFPDeregister");
	if (fnWFPDeregister != NULL)
	{
		if (fnWFPDeregister(hService, WFS_EXECUTE_EVENT | WFS_USER_EVENT | WFS_SYSTEM_EVENT, m_hWnd, m_hWnd, 0x00000001) == WFS_SUCCESS)
		{
			strtext.Format(L"WFPDeregister success");
		}
		else
		{
			strtext.Format(L"WFPDeregister failed %d", GetLastError());
		}
	}
	else
	{
		strtext.Format(L"WFPDeregister load failed");
	}
	AppendStatus(strtext);
}

void CMyMFCDlg::OnBnClickedBtUnlock()
{
	CString strtext;
	pfnWFPUnlock fnWFPUnlock;
	fnWFPUnlock = (pfnWFPUnlock)GetProcAddress(hdll, "WFPUnlock");
	if (fnWFPUnlock != NULL)
	{
		if (fnWFPUnlock(hService, m_hWnd, 0x00000001) == WFS_SUCCESS)
		{
			strtext.Format(L"WFPUnLock success");
		}
		else
		{
			strtext.Format(L"WFPUnLock failed %d", GetLastError());
		}
	}
	else
	{
		strtext.Format(L"WFPUnLock load failed");
	}
	AppendStatus(strtext);
}


void CMyMFCDlg::OnBnClickedBtGetinfocap()
{
	CString strtext;
	pfnWFPGetInfo fnWFPGetInfo;
	fnWFPGetInfo = (pfnWFPGetInfo)GetProcAddress(hdll, "WFPGetInfo");
	if (fnWFPGetInfo != NULL)
	{
	
		if (fnWFPGetInfo(hService,WFS_INF_CAM_CAPABILITIES , NULL, WFS_INDEFINITE_WAIT, m_hWnd, 0x00000001) == WFS_SUCCESS)
		{
			strtext.Format(L"WFPGetinfo WFS_INF_CAM_CAPABILITIES -  success");
		}
		else
		{
			strtext.Format(L"WFPGetinfo WFS_INF_CAM_CAPABILITIES-  failed %d", GetLastError());
		}
	}
	else
	{
		strtext.Format(L"WFPGetinfo - load failed");
	}
	AppendStatus(strtext);
}


void CMyMFCDlg::OnEnChangeRichedit22()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CMyMFCDlg::OnBnClickedBtGetinfostatus()
{

	CString strtext;
	pfnWFPGetInfo fnWFPGetInfo;
	fnWFPGetInfo = (pfnWFPGetInfo)GetProcAddress(hdll, "WFPGetInfo");
	if (fnWFPGetInfo != NULL)
	{
		if (fnWFPGetInfo(hService, WFS_INF_CAM_STATUS, NULL, WFS_INDEFINITE_WAIT, m_hWnd, 0x00000001) == WFS_SUCCESS)
		{
			strtext.Format(L"WFPGetinfo WFS_INF_CAM_STATUS -  success");
		}
		else
		{
			strtext.Format(L"WFPGetinfo WFS_INF_CAM_STATUS -  failed %d", GetLastError());
		}

		AppendStatus(strtext);
	}
}


void CMyMFCDlg::OnBnClickedBtreset()
{

	CString strtext;
	pfnWFPExecute fnWFPExecute;
	fnWFPExecute = (pfnWFPExecute)GetProcAddress(hdll, "WFPExecute");
	if (fnWFPExecute != NULL)
	{
		if (fnWFPExecute(hService, WFS_CMD_CAM_RESET, NULL, WFS_INDEFINITE_WAIT, m_hWnd, 0x00000001) == WFS_SUCCESS)
		{
			strtext.Format(L"WFPExecute Reset Success");
		}
		else
		{
			strtext.Format(L"WFPExecute Reset failed %d", GetLastError());
		}
	}
	else
	{
		strtext.Format(L"WFPExecute load failed");
		GetDlgItem(IDC_STATIC)->SetWindowTextW(strtext);
	}
	AppendStatus(strtext);
}


void CMyMFCDlg::OnBnClickedBttakepicex()
{
	CString strtext;
	pfnWFPExecute fnWFPExecute;
	data.wCamera = WFS_CAM_PERSON;
	data.lpszCamData = "Test data from takepictureex";
	data.lpszUNICODECamData = NULL;
	data.lpszPictureFile = NULL;
	fnWFPExecute = (pfnWFPExecute)GetProcAddress(hdll, "WFPExecute");
	if (fnWFPExecute != NULL)
	{
		if (fnWFPExecute(hService,WFS_CMD_CAM_TAKE_PICTURE_EX, &data, WFS_INDEFINITE_WAIT, m_hWnd, 0x00000001) == WFS_SUCCESS)
		{
			strtext.Format(L"WFPExecute TakepictureEx  success");
		}
		else
		{
			strtext.Format(L"WFPExecute  TakepictureEx failed %d", GetLastError());
		}
	}
	
	else
	{
		strtext.Format(L"WFPExecute load failed");
		GetDlgItem(IDC_STATIC)->SetWindowTextW(strtext);
	}
	AppendStatus(strtext);
}
