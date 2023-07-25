
// DeviceTest.h : main header file for the PROJECT_NAME application
//
#include "XFSCAM.H"
#include"XFSAPI.H"
#include "LogManLib/LogMan.h"
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols








// CDeviceTestApp:
// See DeviceTest.cpp for the implementation of this class
//

class CDeviceTestApp : public CWinApp
{
public:
	CDeviceTestApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CDeviceTestApp theApp;
