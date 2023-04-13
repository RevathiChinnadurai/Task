#pragma once
#include "afxdialogex.h"
#include "XFSLib/XFSManagerWrapper.h"

//typedef HRESULT(WINAPI* pfnWFPOpen) (HSERVICE hService, LPSTR lpszLogicalName, HAPP hApp, LPSTR lpszAppID, DWORD dwTraceLevel, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID, HPROVIDER hProvider, DWORD dwSPIVersionsRequired, LPWFSVERSION lpSPIVersion, DWORD dwSrvcVersionsRequired, LPWFSVERSION lpSrvcVersion);


// Cprinter dialog

class Cprinter : public CDialogEx
{
	DECLARE_DYNAMIC(Cprinter)

public:
	Cprinter(CWnd* pParent = nullptr);   // standard constructor
	virtual ~Cprinter();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Printerdlg };
#endif

protected:


	XFSManagerWrapper* m_pXFSManager;

	WFSVERSION m_wfsXFSManagerVersion;
	WFSVERSION m_wfsSPIVersion;
	WFSVERSION m_wfsServiceVersion;
	HSERVICE m_hService;
	WFSRESULT* pwfsRes;
	REQUESTID m_requestId;
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

	void AppendStatus(CString strTxt);

	void Lock();
	void UnLock();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editprintdata;
	CEdit m_edtFileName;
	CRichEditCtrl m_richprint;
	void AsyncLock();
	void AsyncUnLock();
	afx_msg void OnBnClickedOpen();
	//afx_msg void OnBnClickedStartUp();
	
	afx_msg void OnEnChangeRichedit21();
	afx_msg void OnEnChangeEditPrintdata();
	afx_msg void OnBnClickedSelectFile();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedPrintfile();
	afx_msg void OnBnClickedPrintdata();
	afx_msg void OnBnClickedReset();
	afx_msg void OnBnClickedDispensepaper();
	afx_msg void OnBnClickedCutpaper();
	afx_msg void OnBnClickedPrintform();
	//afx_msg void OnBnClickedAsyncPrintFile();
	//afx_msg void OnBnClickedAsyncprintdata();
	//afx_msg void OnBnClickedAsyncDispensePaper();
	//afx_msg void OnBnClickedAsyncreset();
	//afx_msg void OnBnClickedAsyncCutpaper();
	//afx_msg void OnBnClickedAsyncPrintform();
	//afx_msg void OnBnClickedAsyncOPen();
	//afx_msg void OnBnClickedAsyncclose();
	afx_msg void OnBnClickedCleanup();
	afx_msg void OnBnClickedClose();
	BOOL m_AsyncCheckVal;
	CButton m_btnStartup;
	CButton m_btnOpen;
	CButton m_btnSelectFile;
	CButton m_PrintFile;
	CButton m_PrintData;
	CButton m_btnReset;
	CButton m_Dispense;
	CButton m_btnCutPaper;
	CButton m_btnPrintForm;
	CButton m_btnClose;
	afx_msg void OnBnClickedStartup();
};
