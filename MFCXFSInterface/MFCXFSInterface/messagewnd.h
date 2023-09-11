#pragma once
#include "stdafx.h"
#include "MFCXFSInterface.h"


class messagewnd :public CWnd
{
public:
	messagewnd();
	
public:
	virtual ~messagewnd();

protected:
	afx_msg LRESULT OnSystemEvent(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};