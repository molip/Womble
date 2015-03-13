
// Womble.h : main header file for the Womble application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CWombleApp:
// See Womble.cpp for the implementation of this class
//

class CWombleApp : public CWinApp
{
public:
	CWombleApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL OnIdle(LONG lCount) override;

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CWombleApp theApp;
