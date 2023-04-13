
// DeviceTestDlg.h : header file
//
#include "Ccamera.h"
#include "Cprinter.h"
#include "CPinpad.h"
#include "CSensor.h"
#pragma once


// CDeviceTestDlg dialog
class CDeviceTestDlg : public CDialogEx
{
// Construction
public:
	CDeviceTestDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEVICETEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;


	



	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tab;
	Ccamera m_cam;
	Cprinter m_print;
	CWnd* m_pwndShow;
	CPinpad m_pinpad;
	afx_msg void OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	
	CSensor m_sensor;
};
