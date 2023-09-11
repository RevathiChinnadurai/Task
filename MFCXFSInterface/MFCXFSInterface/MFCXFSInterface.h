#pragma once
#include "stdafx.h"
#include "XFSManagerWrapper.h"
#include "messagewnd.h"


#ifdef DLLAPI_EXPORTS
#define DLLAPI_API __declspec(dllexport)
#else
#define DLLAPI_API __declspec(dllimport)
#endif // DLLAPI_API __declspec(dllexport)

class CMFCXFSInterfaceApp : public CWinApp
{
public:
	
	CMFCXFSInterfaceApp();
	
	// Overrides
public:
	bool devstatus;
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()

};
class messagewnd;
DLLAPI_API HRESULT LoadXFS();
DLLAPI_API HRESULT CleanXFS();
DLLAPI_API HRESULT GetDeviceStatus(LPSTR devicetype);
//DLLAPI_API HRESULT GetDevcieInfo();
