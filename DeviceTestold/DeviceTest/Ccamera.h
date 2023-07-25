#pragma once
#include "afxdialogex.h"
#include "XFSAPI.H"
#include "XFSLib/XFSManagerWrapper.h"
//typedef HRESULT(WINAPI* pfnWFPOpen) (HSERVICE hService, LPSTR lpszLogicalName, HAPP hApp, LPSTR lpszAppID, DWORD dwTraceLevel, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID, HPROVIDER hProvider, DWORD dwSPIVersionsRequired, LPWFSVERSION lpSPIVersion, DWORD dwSrvcVersionsRequired, LPWFSVERSION lpSrvcVersion);

// Ccamera dialog

class Ccamera : public CDialogEx
{
	DECLARE_DYNAMIC(Ccamera)

public:
	Ccamera(CWnd* pParent = nullptr);   // standard constructor
	virtual ~Ccamera();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Camdlg };
#endif

protected:

	XFSManagerWrapper* m_pXFSManager;

	WFSVERSION m_wfsXFSManagerVersion;
	WFSVERSION m_wfsSPIVersion;
	WFSVERSION m_wfsServiceVersion;

	HSERVICE m_hService;
	WFSCAMTAKEPICT ipData;
	WFSCAMTAKEPICTEX data;
	REQUESTID m_requestId;
	WFSRESULT *pwfsres;
	//WFSRESULT* pwfsRes;
	void AppendStatus(CString strTxt);


	LRESULT OnOpenComplete(WPARAM wParam, LPARAM lParam);
	LRESULT OnCloseComplete(WPARAM wParam, LPARAM lParam);
	LRESULT OnLockComplete(WPARAM wParam, LPARAM lParam);
	LRESULT OnUnlockComplete(WPARAM wParam, LPARAM lParam);
	LRESULT OnRegisterComplete(WPARAM wParam, LPARAM lParam);
	LRESULT OnDeregisterComplete(WPARAM wParam, LPARAM lParam);
	LRESULT OnGetInfoComplete(WPARAM wParam, LPARAM lParam);
	LRESULT OnExecuteComplete(WPARAM wParam, LPARAM lParam);

	LRESULT OnTimerEvent(WPARAM wParam, LPARAM lParam);
	LRESULT OnExecuteEvent(WPARAM wParam, LPARAM lParam);
	LRESULT OnServiceEvent(WPARAM wParam, LPARAM lParam);
	LRESULT OnUserEvent(WPARAM wParam, LPARAM lParam);
	LRESULT OnSystemEvent(WPARAM wParam, LPARAM lParam);


	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

	void Lock();
	void UnLock();

	void AsyncLock();
	void AsyncUnLock();


	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedStartup();
	//afx_msg void OnBnClickedAsyncOpen();
	CRichEditCtrl m_RichText;
	afx_msg void OnBnClickedCleanUp();
	afx_msg void OnBnClickedClose();
	
	afx_msg void OnBnClickedTakePicture();
	//afx_msg void OnBnClickedAsyncTakepictureex();
	//afx_msg void OnBnClickedAsyncclose();
	afx_msg void OnBnClickedTakepictureEx();
	//afx_msg void OnBnClickedAsynctakepicture();
	afx_msg void OnBnClickedReset();
	//afx_msg void OnBnClickedAsyncReset();
	CButton m_AsyncCheck;
	BOOL m_AsyncCheckVal;
	CButton m_btnStartup;
	CButton m_btnOpen;
	CButton m_btnTakepic;
	CButton m_btnTakepicEx;
	CButton m_btnReset;
	CButton m_btnClose;
};
