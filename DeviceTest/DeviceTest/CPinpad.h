#pragma once
#include "afxdialogex.h"


// CPinpad dialog

class CPinpad : public CDialogEx
{
	DECLARE_DYNAMIC(CPinpad)

public:
	CPinpad(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPinpad();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
