#pragma once
#include "stdafx.h"
#include "messagewnd.h"
#include "XFSManagerWrapper.h"
#include "XFSCAM.H"
#include "XFSPTR.H"
#include "XFSPIN.H"



#ifdef DLLAPI_EXPORTS
#define DLLAPI_API __declspec(dllexport)
#else
#define DLLAPI_API __declspec(dllimport)
#endif // DLLAPI_API __declspec(dllexport)

//#define XFS_MSG_WFS_SYSTEMEVENT (WM_USER+1901)


class CMFCXFSInterfaceApp : public CWinApp
{
public:
	class messagewnd;
	CMFCXFSInterfaceApp();
	// Overrides
public:
	
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSystemEventmessage(WPARAM wParam, LPARAM lParam);
};

DLLAPI_API HRESULT LoadXFS();
DLLAPI_API HRESULT CleanXFS();
DLLAPI_API HRESULT GetDeviceStatus(LPSTR devicetype);
void Blocking(HANDLE hHandle, DWORD dwTimeOut);

