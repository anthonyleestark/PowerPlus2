
// PowerPlus.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PowerPlus.h"
#include "PowerPlusDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPowerPlusApp

BEGIN_MESSAGE_MAP(CPowerPlusApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CPowerPlusApp construction

CPowerPlusApp::CPowerPlusApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CPowerPlusApp object

CPowerPlusApp theApp;


// CPowerPlusApp initialization

BOOL CPowerPlusApp::InitInstance()
{
	// Check if any another instance is running
	if (HWND hPrevWnd = FindWindow(NULL, L"Power++ 2.0 STL"))
	{
		// ShowWindow(hPrevWnd, TRUE);
		PostMessage(hPrevWnd, WM_COMMAND, (WPARAM)IDM_SHOWWINDOW, (LPARAM)0);
		BringWindowToTop(hPrevWnd);
		SetForegroundWindow(hPrevWnd);
		return 0;
	}

	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Stark Industries"));

	CPowerPlusDlg dlg;
//	INT_PTR nRespond;

	BOOL isShowWhenStart = AfxGetApp()->GetProfileIntW(L"Configuration", L"isShowAtStartup", TRUE);
	if (isShowWhenStart == FALSE) // Hide dialog when start
	{
		dlg.Create(IDD_POWERPLUS_DIALOG, NULL);
		dlg.ShowWindow(SW_HIDE);
		m_pMainWnd = &dlg;
		MessageBeep(0xFFFFFFFF);
		dlg.RunModalLoop();
	}
	else
	{
		m_pMainWnd = &dlg;
		dlg.DoModal();
		PostMessage(dlg.m_hWnd, WM_COMMAND, (WPARAM)IDM_SHOWWINDOW, 0);
	}

	//if (nRespond == IDOK)
	//{
	//	// TODO: Place code here to handle when the dialog is
	//	//  dismissed with OK
	//}
	//else if (nRespond == IDCANCEL)
	//{
	//	// TODO: Place code here to handle when the dialog is
	//	//  dismissed with Cancel
	//	//PostMessage(dlg.m_hWnd, WM_DESTROY, 0, 0);
	//}
	//else if (nRespond == -1)
	//{
	//	TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
	//	TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	//}

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#ifndef _AFXDLL
	ControlBarCleanUp();
#endif

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

