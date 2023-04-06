// CPinpad.cpp : implementation file
//

#include "pch.h"
#include "DeviceTest.h"
#include "afxdialogex.h"
#include "CPinpad.h"


// CPinpad dialog

IMPLEMENT_DYNAMIC(CPinpad, CDialogEx)

CPinpad::CPinpad(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CPinpad::~CPinpad()
{
}

void CPinpad::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPinpad, CDialogEx)
END_MESSAGE_MAP()


// CPinpad message handlers
