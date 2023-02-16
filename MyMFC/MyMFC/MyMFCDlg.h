
// MyMFCDlg.h : header file
//
#include "XFSAPI.H"
#include "XFSCAM.H"
#include "LogManLib/LogMan.h"
#include "CAMSPI.h"
#pragma once

typedef HRESULT (WINAPI* pfnWFPOpen) (HSERVICE hService, LPSTR lpszLogicalName, HAPP hApp, LPSTR lpszAppID, DWORD dwTraceLevel, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID, HPROVIDER hProvider, DWORD dwSPIVersionsRequired, LPWFSVERSION lpSPIVersion, DWORD dwSrvcVersionsRequired, LPWFSVERSION lpSrvcVersion);
typedef HRESULT (WINAPI* pfnWFPClose) (HSERVICE hService, HWND hWnd, REQUESTID ReqID);
typedef HRESULT (WINAPI* pfnWFPLock) (HSERVICE hService, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID);
typedef HRESULT (WINAPI* pfnWFPExecute) (HSERVICE hService, DWORD dwCommand, LPVOID lpCmdData, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID);
typedef HRESULT (WINAPI* pfnWFPRegister)(HSERVICE hService, DWORD dwEventClass, HWND hWndReg, HWND hWnd, REQUESTID ReqID);
typedef HRESULT (WINAPI* pfnWFPUnlock)(HSERVICE hService, HWND hWnd, REQUESTID ReqID);
typedef HRESULT (WINAPI* pfnWFPDeregister) (HSERVICE hService, DWORD dwEventClass, HWND hWndReg, HWND hWnd, REQUESTID ReqID);
typedef HRESULT(WINAPI* pfnWFPGetInfo)(HSERVICE hService, DWORD dwCategory, LPVOID lpQueryDetails, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID);
DWORD WINAPI CreateHiddenWindowAndRegisterForUSBEvents(LPVOID lpThreadParameter);
// CMyMFCDlg dialog
class CMyMFCDlg : public CDialogEx
{
// Construction
public:

	CMyMFCDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:

	HICON m_hIcon;
	WFSVERSION m_wfsServiceVersion;
	WFSVERSION m_wfsSPIVersion;
	WFSCAMTAKEPICT ipData;
	WFSCAMTAKEPICTEX data;
	void AppendStatus(CString strtext);


	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
		//void Appendstatus(CString strtext);
public:
	afx_msg void OnBnClickedBtopen();
	afx_msg void OnBnClickedBtstop();
	afx_msg void OnBnClickedBtstart();
	afx_msg void OnBnClickedBtlock();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBttakepic();
	afx_msg void OnBnClickedBtRegister();
	afx_msg void OnBnClickedBtDeregister();
	afx_msg void OnBnClickedBtUnlock();
	afx_msg void OnBnClickedBtGetinfocap();
	CRichEditCtrl m_cntrl;
	afx_msg void OnEnChangeRichedit22();
	afx_msg void OnBnClickedBtGetinfostatus();
	afx_msg void OnBnClickedBtreset();
	afx_msg void OnBnClickedBttakepicex();
};
