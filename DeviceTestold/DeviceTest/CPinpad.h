#pragma once
#include "afxdialogex.h"
#include "XFSLib/XFSManagerWrapper.h"

// CPinpad dialog

class CPinpad : public CDialogEx
{
	DECLARE_DYNAMIC(CPinpad)

public:
	CPinpad(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPinpad();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Pinpaddlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);// DDX/DDV support

	HICON m_hIcon;
	XFSManagerWrapper* m_pXFSManager;
	REQUESTID m_requestId;
	WFSVERSION m_wfsXFSManagerVersion;
	WFSVERSION m_wfsServiceVersion;
	WFSVERSION m_wfsSPIVersion;
	HSERVICE m_hService;
	WFSRESULT* pwfsRes;
	void AppendStatus(CString strTxt);
	DECLARE_MESSAGE_MAP()
	void AppendPIN(CString strTxt);
	void Lock();
	void UnLock();
	void AsyncLock();
	void AsyncUnLock();
	friend UINT GetPINThread(LPVOID wParam);
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


public:
	afx_msg void OnBnClickedStartup();
	CEdit m_edtKeyInput;
	CEdit m_edtInfoInput;
	CEdit m_edtkeyName;
	CRichEditCtrl m_stStatus;
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedClose();
	BOOL m_AsyncCheckVal;
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedGetStatus();
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedGetCaps();
	afx_msg void OnBnClickedGetKeyDetails();
	afx_msg void OnBnClickedGetKeyDetailsEx();
	afx_msg void OnBnClickedGetFuncKey();
	afx_msg void OnBnClickedGetHsm();
	afx_msg void OnBnClickedGetSecKey();
	afx_msg void OnBnClickedGetDevId();
	afx_msg void OnBnClickedLoadkey();
	afx_msg void OnBnClickedDeletekey();
	afx_msg void OnBnClickedGetpin();
	afx_msg void OnBnClickedCryptdata();
	CString m_edtInfoInput1;
	CButton m_btnStartup;
	CButton m_btnopen;
	CButton m_btnclose;
	CButton m_btngetstatus;
	CButton m_btngetcaps;
	CButton m_btnkeydetails;
	CButton m_btnkeydetailsex;
	CButton m_btnfunkey;
	CButton m_btnhsm;
	CButton m_btnsecurekey;
	CButton m_btndeviceid;
	CButton m_btnloadkey;
	CButton m_btndeletekey;
	CButton m_btnGetpin;
	CButton m_btnCryptdata;
};
