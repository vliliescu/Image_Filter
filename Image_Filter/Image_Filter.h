
// Image_Filter.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CImageFilterApp:
// See Image_Filter.cpp for the implementation of this class
//

class CImageFilterApp : public CWinApp
{
public:
	CImageFilterApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CImageFilterApp theApp;
