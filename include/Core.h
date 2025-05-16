#pragma once

// Include stdafx.h
#include "stdafx.h"

// Check if WINDOWS.H be included
#ifndef WINDOWS_H_INCLUDED
#define WINDOWS_H_INCLUDED
#include "windows.h"
#include "PowrProf.h"
#pragma comment (lib, "PowrProf")
#endif

// Include all necessary header file here
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <string>
#include "mmsystem.h"
using namespace std;

// Define actions
#define ACTION_NOTHING			0x010000			// 65536
#define ACTION_SCREENOFF		ACTION_NOTHING + 1	// 65537
#define ACTION_SLEEP			ACTION_NOTHING + 2	// 65538
#define ACTION_SHUTDOWN			ACTION_NOTHING + 3	// 65539
#define ACTION_RESTART			ACTION_NOTHING + 4	// 65540
#define ACTION_LOGOFF			ACTION_NOTHING + 5	// 65541
#define ACTION_HIBERNATE		ACTION_NOTHING + 6	// 65542
#define ACTION_SHOWMENU			ACTION_NOTHING + 7	// 65543

// Define message
#define EWX_SCREENOFF			SC_MONITORPOWER
#define EWX_SLEEP				0x011010			// 69648
#define EWX_HIBERNATE			0x011011			// 69649

// Define type of action constant here
#define PW_SCREEN_ACTION		0x10100				// 65792
#define PW_POWER_ACTION			0x10101				// 65793

// Define error code right here
#define SUCCESS_NO_ERROR		0x11001				// 69633
#define FAILED_AND_ERROR		0x11002				// 69634

// Define menu item type
#define SELECTION_ITEM			0x20000				// 131072
#define SEPERATOR_ITEM			0x20001				// 131073
#define	POPUP_CHILDMENU			0x20002				// 131074

// Define menu actions
#define ACTION_HELP				0x30000				// 196608
#define ACTION_ABOUT			0x30001				// 196609
#define ACTION_MAINDLG			0x30002				// 196610
#define ACTION_EXIT				0x30003				// 196611
#define ACTION_SELVIETNAMESE	0x30004				// 196612
#define ACTION_SELENGLISH		0x30005				// 196613
#define ACTION_VIEWLOG			0x30006				// 196614
#define ACTION_DEFAULT			0x30007				// 196615
#define ACTION_ADJUSTMENU		0x30008				// 196616
#define ACTION_SHOWWHENSTART	0x30009				// 196617
#define ACTION_STARTUP			0x30010				// 196624
#define ACTION_ASKBEFORE		0x30011				// 196625
#define ACTION_SAVELOGS			0x30012				// 196626
#define ACTION_SHOWERRORMSG		0x30013				// 196627

// Define language
#define LANGUAGE_VIETNAMESE		0x40000				// 262144
#define LANGUAGE_ENGLISH		0x40001				// 262145

// Define registry informations
#define REG_HKEY_CURRENT_USER	HKEY_CURRENT_USER
#define REG_HKEY_LOCAL_MACHINE	HKEY_LOCAL_MACHINE
#define VALUE_STRING			0x50000				// 327680
#define VALUE_DWORDVALUE		0x50001				// 327681

// Define types of sound
#define SOUND_ERROR				0x60000				// 393216
#define SOUND_SUCCESS			0x60001				// 393217

// Define necessary structs here
struct USERMENUITEM
{
	UINT nItemID;
	UINT nTypeOfItem;
	UINT nAction;
	LPCSTR szItemTitle;
};

struct USERMENU
{
	unsigned int countElement;
	USERMENUITEM *pMenu = NULL;
};

struct SCHEDULE
{
	BOOL isScheduleOn, isDoEveryday;
	int nHour, nMinute, nSecond;
	int nDay, nMonth, nYear;
	UINT nAction;
};

struct CONFIGURATION
{
	// Main settings
	UINT actionLeftMouse;
	UINT actionRightMouse;
	BOOL isActionRightMouse;

	// Display setting
	UINT nLanguage;

	// System settings
	BOOL isShowWhenStart;
	BOOL isStartupEnabled;
	BOOL isAskBefore;
	BOOL isLogsEnabled;
	BOOL isShowErrorMsg;
	BOOL isScheduleTip;

	SCHEDULE stSchedule;
};

struct ACTION
{
	UINT nTypeOfAction;
	SYSTEMTIME atlTimeOfAction;
	LPCSTR szActionName;
	BOOL isActionSucceed;
	UINT nErrorCode;
};

struct REGISTRY_KEY
{
	HKEY szTagName;
	LPCTSTR szKeyName;
	UINT nTypeOfValue;
	LPCSTR szValue;
	DWORD dwValue;
};

////////////////////////////////////////////////////////
/////                                              /////
//////////                                    //////////
////////////// SET UP ACTION RIGHT-HERE/////////////////
//////////                                    //////////
/////                                              /////
////////////////////////////////////////////////////////

// Main power function
BOOL DoPowerAction(UINT nTypeOfAction, UINT nMessage)
{
	// Action here
	if (nTypeOfAction == PW_SCREEN_ACTION)
	{
		PostMessage(HWND_BROADCAST, WM_SYSCOMMAND, (WPARAM)nMessage, (LPARAM)2);
		return TRUE;
	}
	else if (nTypeOfAction == PW_POWER_ACTION && (nMessage != EWX_SLEEP && nMessage != EWX_HIBERNATE))
	{
		UINT nActions = nMessage;
		nActions |= EWX_FORCE;
		
		HANDLE hToken;
		TOKEN_PRIVILEGES tkp;
		if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		{
			return FALSE;
		}
		LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
		tkp.PrivilegeCount = 1;
		tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
		if (GetLastError() != ERROR_SUCCESS)
		{
			return FALSE;
		}
		if (!ExitWindowsEx(nActions, 0))
		{
			return FALSE;
		}
		return TRUE;
	}
	else if (nTypeOfAction == PW_POWER_ACTION && (nMessage == EWX_SLEEP || nMessage == EWX_HIBERNATE))
	{
		switch (nMessage)
		{
		case EWX_SLEEP: 
			if (SetSuspendState(false, false, false))	// stand by (sleep)
				return TRUE;
			else
				return FALSE;
			break;
		case EWX_HIBERNATE:
			if (SetSuspendState(true, false, false))	// hibernate
				return TRUE;
			else
				return FALSE;
			break;
		}
		return TRUE;
	}
	else
	{
		//DO DEFAULT ACTION
		MessageBox(AfxGetMainWnd()->GetSafeHwnd(), L"Function \"DoPowerAction(UINT nTypeofAction, UINT nMessage)\" ran into an unknown error.", L"Error", MB_OK | MB_ICONERROR);
		return TRUE;
	}
}

// Check if log file is empty or not exist
BOOL isEmpty(const char* filename)
{
	ifstream logfile(filename);
	return (logfile.peek() == ifstream::traits_type::eof());
}

// Save actions log
void SaveLogs(BOOL isEnabled, ACTION stActionInfo)
{
	// Action here
	if (isEnabled)
	{
		ofstream logFile("PowerPlus_Log.log", ios::app);
		if (isEmpty("PowerPlus_Log.log"))
		{
			logFile << "// This is the action-log of Power++ 2.0 STL Application" << endl;
			logFile << "// Do not edit this file by any way!" << endl;
			logFile << "#################################################" << endl;
			logFile << "#                                               #" << endl;
			logFile << "#               Power++ 2.0 STL                 #" << endl;
			logFile << "#                                               #" << endl;
			logFile << "#################################################" << endl << endl;
		}
		GetLocalTime(&stActionInfo.atlTimeOfAction);
		logFile << stActionInfo.atlTimeOfAction.wHour << ":" << stActionInfo.atlTimeOfAction.wMinute << ":" << stActionInfo.atlTimeOfAction.wSecond << " ";
		logFile << stActionInfo.atlTimeOfAction.wDay << "/" << stActionInfo.atlTimeOfAction.wMonth << "/" << stActionInfo.atlTimeOfAction.wYear << " ";
		logFile << endl;
		logFile << stActionInfo.szActionName;
		if (stActionInfo.nErrorCode == SUCCESS_NO_ERROR)
			logFile << "successfully without any error." << endl;
		else if (stActionInfo.nErrorCode == FAILED_AND_ERROR)
			logFile << "unsuccessfully because of an error." << endl;
		logFile << endl;
		logFile.close();
	}
}

// Add new key into registry
BOOL AddRegistryKey(REGISTRY_KEY regKeyInfo)
{
	// Action here
	CRegKey regKey;
	LONG result = regKey.Open(regKeyInfo.szTagName, regKeyInfo.szKeyName, KEY_ALL_ACCESS);
	if (result != ERROR_SUCCESS)
	{
		if (result == ERROR_NOT_FOUND)
		{
			//regKey.Create(regKeyInfo.szTagName, regKeyInfo.szKeyName, REG_NONE, );
		}
	}
	return TRUE;
}

// Play sound "BEEP" when sound enabled
void PlaySounds(BOOL isSoundEnabled, UINT nTypeOfSound)
{
	if (isSoundEnabled)
	{
		// Play sound here
		switch (nTypeOfSound)
		{
		case SOUND_ERROR: PlaySound(TEXT("SystemExclamination"), NULL, SND_ASYNC); break;
		case SOUND_SUCCESS: PlaySound(TEXT("SystemExit"), NULL, SND_ASYNC); break;
		}
	}
}

// Backup registry and all configurations to INI file
BOOL RegistryBackup(void)
{
	return TRUE;
}

// Load string as language
LPCWSTR LoadStringAsLang(UINT nLanguage, UINT nID)
{
	CString strResult;
	if (nLanguage = LANGUAGE_ENGLISH)
		strResult.LoadString(nID);
	else if (nLanguage = LANGUAGE_VIETNAMESE)
		strResult.LoadString(nID + 100);
	return strResult.GetString();
}

// Return language
UINT GetLanguage(void)
{
	return 0;
}

// Open the action-log file to view with Notepad
BOOL ViewActionLog(HWND hWnd)
{
	if (!ShellExecute(hWnd, L"open", L"C:\\Windows\\notepad.exe", L"PowerPlus_Log.log", NULL, SW_SHOW))
		return FALSE;
	return TRUE;
}

// Minus two time and return the number of different second
int MinusTwoTime(SYSTEMTIME stFirstTime, SYSTEMTIME stSecondTime)
{
	int nFirstTimeToSecond = (stFirstTime.wHour * 3600) + (stFirstTime.wMinute * 60) + (stFirstTime.wSecond);
	int nSecondTimeToSecond = (stSecondTime.wHour * 3600) + (stSecondTime.wMinute * 60) + (stSecondTime.wSecond);
	return (nFirstTimeToSecond - nSecondTimeToSecond);
}

// Check if same time
BOOL isTimeMatch(SYSTEMTIME timeDest, SYSTEMTIME timePar)
{
	if ((timeDest.wHour == timePar.wHour) && 
		(timeDest.wMinute == timePar.wMinute) && 
		(timeDest.wSecond == timePar.wSecond) && 
		// (timeDest.wMilliseconds == timePar.wMilliseconds) &&
		(timeDest.wDay == timePar.wDay) && 
		// (timeDest.wDayOfWeek == timePar.wDayOfWeek) &&
		(timeDest.wMonth == timePar.wMonth) && 
		(timeDest.wYear == timePar.wYear))
		return TRUE;
	return FALSE;
}

/*
// A new version of isTimeMatch function above
BOOL isTimeMatchNew(SYSTEMTIME timeDest, SYSTEMTIME timePar, const char* strCompare)
{
	// This function will check each member of time depend on the KEYWORD in compare-string
	// "hh" for hour, "mm" for minute, "ss" for second, "ms" for milisecond
	// "DD" for day, "DW" for day of week, "MM"for month, "YY" for year
	// Insert code here
	return TRUE;
}

// Get app path
LPCTSTR GetAppPath()
{
	LPWSTR strBuffer = L"";
	GetCurrentDirectory(1000, strBuffer);
 	strBuffer = StrCpyW((PWSTR) (*strBuffer), (PWSTR)L"\\PowerPlus.exe");
	return static_cast<LPCTSTR> (strBuffer);
}

// Create process
BOOL CreateAProcess(LPCWSTR lpszAppPath, LPWSTR lpszCmdLine, UINT nStyle, DWORD &dwErrorCode)
{
	STARTUPINFO stStartupInfo;
	ZeroMemory(&stStartupInfo, sizeof(STARTUPINFO));
	stStartupInfo.cb = sizeof(STARTUPINFO);

	PROCESS_INFORMATION stProcessInfo;
	ZeroMemory(&stProcessInfo, sizeof(PROCESS_INFORMATION));

	BOOL bResult = CreateProcessW(lpszAppPath, lpszCmdLine, (LPSECURITY_ATTRIBUTES)NULL, (LPSECURITY_ATTRIBUTES)NULL, FALSE, (DWORD) nStyle, NULL, NULL, &stStartupInfo, &stProcessInfo);
	if (bResult)
	{
		WaitForSingleObject(stProcessInfo.hProcess, INFINITE);
		// Check whether our command succeeded?
		GetExitCodeProcess(stProcessInfo.hProcess, &dwErrorCode);
		// Avoid memory leak by closing process handle
		CloseHandle(stProcessInfo.hProcess);
	}
	else
		dwErrorCode = GetLastError();
	return bResult;
}

// Restart application itself
void ActionSchedule(SYSTEMTIME stScheduleTime, UINT nActionType, UINT nAction)
{
	SYSTEMTIME time;
	GetLocalTime(&time);
	if (!isTimeMatch(stScheduleTime, time))
		return;
	DoPowerAction(nActionType, nAction);
}

void DrawButton(UINT nIconID, LPCTSTR lpszButtonTitle, CButton*& pButton)
{
	HICON hButtonIcon = AfxGetApp()->LoadIcon(nIconID);
	if (hButtonIcon == NULL)
		return;
	if (pButton == NULL)
		return;

	CRect rcButtonRect;
	pButton->GetWindowRect(&rcButtonRect);
	if (rcButtonRect == NULL)
		return;

	CString strButtonTitle;
	strButtonTitle.SetString(lpszButtonTitle);
	if (strButtonTitle.IsEmpty())
		pButton->GetWindowText(strButtonTitle);

	pButton->SetButtonStyle(BS_ICON);
	pButton->SetIcon(hButtonIcon);
	pButton->UpdateWindow();
}
*/

