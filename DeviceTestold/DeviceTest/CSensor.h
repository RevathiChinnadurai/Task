#pragma once
#include "afxdialogex.h"
#include "XFSLib/XFSManagerWrapper.h"

// CSensor dialog

class CSensor : public CDialogEx
{
	DECLARE_DYNAMIC(CSensor)

public:
	CSensor(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CSensor();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SIUnitdlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


	HICON m_hIcon;
	XFSManagerWrapper* m_pXFSManager;
	REQUESTID m_requestId;
	WFSVERSION m_wfsXFSManagerVersion;
	WFSVERSION m_wfsServiceVersion;
	WFSVERSION m_wfsSPIVersion;
	HSERVICE m_hService;
	WFSRESULT* pwfsRes;
	void AppendStatus(CString strTxt);
	void Lock();
	void UnLock();
	void AsyncLock();
	void AsyncUnLock();
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



	DECLARE_MESSAGE_MAP()
public:
	CRichEditCtrl m_stStatus;
	BOOL m_AsyncCheckVal;
	afx_msg void OnBnClickedStartup();
	afx_msg void OnBnClickedOpen();
	CButton m_btnStartup;
	CButton m_btnOpen;
	CButton m_btnClose;
	CButton m_btnGuideLight;
	CButton m_btnOpenShutter;
	CButton m_btnCloseShutter;
	CComboBox m_cmbGLight;
	CComboBox m_cmbCommand;
	afx_msg void OnBnClickedSetguide();
	afx_msg void OnBnClickedOpenshutter();
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedCloseshutter();
	afx_msg void OnBnClickedExit();
	CButton m_btnExit;
};
