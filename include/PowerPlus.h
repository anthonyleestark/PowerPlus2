
// PowerPlus.h : main header file for the PROJECT_NAME application
//

#pragma once

#include "stdafx.h"
#include "resource.h"		// main symbols

// CPowerPlusApp:
// See PowerPlus.cpp for the implementation of this class
//

class CPowerPlusApp : public CWinApp
{
public:
	CPowerPlusApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CPowerPlusApp theApp;