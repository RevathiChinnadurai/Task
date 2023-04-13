
// DeviceTestDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "DeviceTest.h"
#include "DeviceTestDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

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


// CDeviceTestDlg dialog



CDeviceTestDlg::CDeviceTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DEVICETEST_DIALOG, pParent),m_pwndShow(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	
}

void CDeviceTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
}

BEGIN_MESSAGE_MAP(CDeviceTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CDeviceTestDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CDeviceTestDlg message handlers

BOOL CDeviceTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	CString str;

	int i[10] = { 0 };
	str.Format(L"SENSOR UNIT");
	m_tab.InsertItem(i[0], str);

	str.Format(L"PINPAD");
	m_tab.InsertItem(i[1], str);

	str.Format(L"PRINTER");
	m_tab.InsertItem(i[2], str);
	
	str.Format(L"CAMERA");
	m_tab.InsertItem(i[3], str);



	CRect rect;
	m_tab.GetClientRect(&rect);
	m_cam.Create(IDD_Camdlg, &m_tab);
	m_cam.SetWindowPos(NULL, 5, 25, rect.Width() , rect.Height() , SWP_SHOWWINDOW | SWP_NOZORDER);
	m_cam.m_btnOpen.EnableWindow(FALSE);
	m_cam.m_btnClose.EnableWindow(FALSE);
	m_cam.m_btnTakepic.EnableWindow(FALSE);
	m_cam.m_btnTakepicEx.EnableWindow(FALSE);
	m_cam.m_btnReset.EnableWindow(FALSE);
	m_pwndShow = &m_cam;

	m_print.Create(IDD_Printerdlg, &m_tab);
	m_print.SetWindowPos(NULL, 5, 25, rect.Width() , rect.Height() , SWP_NOSIZE | SWP_NOZORDER);
	m_print.m_btnOpen.EnableWindow(FALSE);
	m_print.m_btnClose.EnableWindow(FALSE);
	m_print.m_btnCutPaper.EnableWindow(FALSE);
	m_print.m_btnPrintForm.EnableWindow(FALSE);
	m_print.m_btnReset.EnableWindow(FALSE);
	m_print.m_btnSelectFile.EnableWindow(FALSE);
	m_print.m_Dispense.EnableWindow(FALSE);
	m_print.m_PrintData.EnableWindow(FALSE);
	m_print.m_PrintFile.EnableWindow(FALSE);
	m_print.m_editprintdata.EnableWindow(TRUE);
	m_pwndShow = &m_print;

	m_pinpad.Create(IDD_Pinpaddlg, &m_tab);
	m_pinpad.SetWindowPos(NULL, 5, 25, rect.Width(), rect.Height(), SWP_SHOWWINDOW | SWP_NOZORDER);
	m_pinpad.m_btnStartup.EnableWindow(TRUE);
	m_pinpad.m_btnopen.EnableWindow(FALSE);
	m_pinpad.m_btnclose.EnableWindow(FALSE);
	m_pinpad.m_btnhsm.EnableWindow(FALSE);
	m_pinpad.m_btndeletekey.EnableWindow(FALSE);
	m_pinpad.m_btnCryptdata.EnableWindow(FALSE);
	m_pinpad.m_btndeviceid.EnableWindow(FALSE);
	m_pinpad.m_btnfunkey.EnableWindow(FALSE);
	m_pinpad.m_btngetcaps.EnableWindow(FALSE);
	m_pinpad.m_btnGetpin.EnableWindow(FALSE);
	m_pinpad.m_btngetstatus.EnableWindow(FALSE);
	m_pinpad.m_btnkeydetails.EnableWindow(FALSE);
	m_pinpad.m_btnkeydetailsex.EnableWindow(FALSE);
	m_pinpad.m_btnloadkey.EnableWindow(FALSE);
	m_pinpad.m_btnsecurekey.EnableWindow(FALSE);
	m_pwndShow = &m_pinpad;

	m_sensor.Create(IDD_SIUnitdlg, &m_tab);
	m_sensor.SetWindowPos(NULL, 5, 25, rect.Width(), rect.Height(), SWP_SHOWWINDOW | SWP_NOZORDER);
	m_sensor.m_btnClose.EnableWindow(FALSE);
	m_sensor.m_btnOpen.EnableWindow(FALSE);
	m_sensor.m_btnCloseShutter.EnableWindow(FALSE);
	m_sensor.m_btnOpenShutter.EnableWindow(FALSE);
	m_sensor.m_btnGuideLight.EnableWindow(FALSE);
	m_pwndShow = &m_sensor;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDeviceTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDeviceTestDlg::OnPaint()
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
HCURSOR CDeviceTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDeviceTestDlg::OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (m_pwndShow != NULL)
	{
		m_pwndShow->ShowWindow(SW_HIDE);
		m_pwndShow = NULL;
	}
	int index = m_tab.GetCurSel();
	switch (index)
	{
	case 0:
		m_cam.ShowWindow(SW_SHOW);
		m_pwndShow = &m_cam;
		break;


	case 1:
		m_print.ShowWindow(SW_SHOW);
		m_pwndShow = &m_print;
		break;


	case 2:
		m_pinpad.ShowWindow(SW_SHOWNORMAL);
		m_pwndShow = &m_pinpad;
		break;

	case 3:
		m_sensor.ShowWindow(SW_SHOW);
		m_pwndShow = &m_sensor;
		break;
	}

	*pResult = 0;
}
