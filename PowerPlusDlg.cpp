
// PowerPlusDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Global.h"
#include "Help.h"
#include "PowerPlus.h"
#include "PowerPlusDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "afxwin.h"
#include "afxdtctl.h"
#include "afxcmn.h"

//#include "Help_ENG.txt"
//#include "Help_VIE.txt"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Macros definition
#define LANG_VIE	LANGUAGE_VIET
#define LANG_ENG	LANGUAGE_ENG
#define LEFTMOUSE	0x00010
#define RIGHTMOUSE	0x00011
#define ACTSCHEDULE 0x00100
#define DIR_HORZ	0x00101
#define DIR_VERT	0x00110
#define WM_TRAYICON WM_USER+100
#define STARTUP_REG_VALUENAME L"PowerPlus2"
#define TIMER_STANDARD_BY_SECOND 1


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// CHelpDlg dialog used for App Help

class CHelpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHelpDlg)

public:
	CHelpDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CHelpDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HELP_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	UINT nLanguage;

public:
	void LoadLanguage();
	void SetupEditbox(CEdit&);
	BOOL LoadHelpFile();
	CString m_strHelpInfo;
	virtual BOOL OnInitDialog();
	CEdit m_pEdit;
};

IMPLEMENT_DYNAMIC(CHelpDlg, CDialogEx)

CHelpDlg::CHelpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HELP_DIALOG, pParent)
	, m_strHelpInfo(_T(""))
{
	
}

CHelpDlg::~CHelpDlg()
{
}

void CHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_HELPINFO, m_strHelpInfo);
	DDX_Control(pDX, IDC_HELPINFO, m_pEdit);
}


BEGIN_MESSAGE_MAP(CHelpDlg, CDialogEx)
END_MESSAGE_MAP()


// CHelpDlg message handlers

void CHelpDlg::LoadLanguage()
{
	nLanguage = stConfig.nLanguage;
	if (nLanguage == LANGUAGE_ENG)
	{
		English language;
		GetDlgItem(IDOK)->SetWindowTextW(language.szOKButton);
		SetWindowTextW(language.szHelp);
	}
	else
	{
		Vietnamese language;
		GetDlgItem(IDOK)->SetWindowTextW(language.szOKButton);
		SetWindowTextW(language.szHelp);
	}
}

void CHelpDlg::SetupEditbox(CEdit &m_pEdit)
{
	SetWindowLong(m_pEdit.m_hWnd, IDC_HELPINFO, ES_UPPERCASE);
	m_pEdit.UpdateWindow();
}

BOOL CHelpDlg::LoadHelpFile()
{
	CString strTemp;
	if (nLanguage == LANGUAGE_ENG)
	{
		for (int pos = 0; pos < 38; pos++)
		{
			strTemp.Format(L"%s", strHelpENG[pos]);
			m_strHelpInfo += strTemp;
			m_strHelpInfo += "\r\n";
			pos++;
		}
	}
	else if (nLanguage == LANGUAGE_VIET)
	{
		for (int pos = 0; pos < 38; pos++)
		{
			strTemp.Format(L"%s", strHelpVIE[pos]);
			m_strHelpInfo += strTemp;
			m_strHelpInfo += "\r\n";
			pos++;
		}
	}
	UpdateData(FALSE);
	return TRUE;
}

BOOL CHelpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	LoadLanguage();
	SetupEditbox(m_pEdit);
	BOOL isHelpInfo = LoadHelpFile();
	if (!isHelpInfo)
	{
		PostMessage(WM_DESTROY, 0, 0);
		return FALSE;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()

public:
	void SetupControls();
	virtual BOOL OnInitDialog();
	afx_msg void OnClickDevFacebookLink(NMHDR *pNMHDR, LRESULT *pResult);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_DEVFACEBOOK_LINK, &CAboutDlg::OnClickDevFacebookLink)
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetupControls();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CAboutDlg::SetupControls()
{
	if (stConfig.nLanguage == LANG_ENG)
	{
		English language;

		this->SetWindowText(language.szAbout);
		GetDlgItem(IDC_COPYRIGHT_LABEL)->SetWindowText(language.szCopyright);
		GetDlgItem(IDC_AUTH_LABEL)->SetWindowText(language.szAboutDev);
		GetDlgItem(IDC_DEVFACEBOOK_LINK)->SetWindowText(language.szFacebookLink);
		CString strAppInfo;
		strAppInfo.Format(L"%s%s%s", language.szAppInfo1, language.szAppInfo2, language.szAppInfo3);
		GetDlgItem(IDC_APPINFO_LABEL)->SetWindowText(strAppInfo);
		GetDlgItem(IDOK)->SetWindowText(language.szOKButton);
	}
	else if (stConfig.nLanguage == LANG_VIE)
	{
		Vietnamese language;

		this->SetWindowText(language.szAbout);
		GetDlgItem(IDC_COPYRIGHT_LABEL)->SetWindowText(language.szCopyright);
		GetDlgItem(IDC_AUTH_LABEL)->SetWindowText(language.szAboutDev);
		GetDlgItem(IDC_DEVFACEBOOK_LINK)->SetWindowText(language.szFacebookLink);
		CString strAppInfo;
		strAppInfo.Format(L"%s%s%s", language.szAppInfo1, language.szAppInfo2, language.szAppInfo3);
		GetDlgItem(IDC_APPINFO_LABEL)->SetWindowText(strAppInfo);
		GetDlgItem(IDOK)->SetWindowText(language.szOKButton);
	}
	
	UpdateData(FALSE);
}

void CAboutDlg::OnClickDevFacebookLink(NMHDR *pNMHDR, LRESULT *pResult)
{
	ShellExecute(0, 0, L"https://facebook.com/starklee.developer", NULL, NULL, SW_NORMAL);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// CScheduleDlg dialog used for App Schedule

class CScheduleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CScheduleDlg)

public:
	CScheduleDlg();   // standard constructor
	virtual ~CScheduleDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCHEDULEDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	CComboBox m_listAction;
	CDateTimeCtrl m_ctrlDate;
	CSpinButtonCtrl m_ctrlHourSpin;
	CSpinButtonCtrl m_ctrlMinuteSpin;
	CSpinButtonCtrl m_ctrlSecondSpin;

	BOOL m_bIsEnable;
	BOOL m_bDoEveryday;
	UINT m_nHour;
	UINT m_nMinute;
	UINT m_nSecond;
	int nAction;
	SYSTEMTIME m_timeSchedule;

	BOOL isEnable, isDoEveryday;
	BOOL isEnableChanged = FALSE, isActionChanged = FALSE, isDoEvrdChanged = FALSE;
	BOOL isHourChanged = FALSE, isMinuteChanged = FALSE, isSecondChanged = FALSE, isDateChanged = FALSE;

	LPCTSTR szMessage, szMsgCaption;

public:
	virtual BOOL OnInitDialog();
	void LoadLanguage();
	void LoadSchedule();
	BOOL SaveSchedule();
	void SetupControls();
	void EnableSaveButton();

	afx_msg void OnSaveAndApply();
	afx_msg void OnCloseAndExit();
	afx_msg void OnEnableSchedule();
	afx_msg void OnChangeAction();
	afx_msg void OnChangeDate(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDoEveryday();
	afx_msg void OnChangeHourSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnChangeMinuteSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnChangeSecondSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnChangeHourEdit();
	afx_msg void OnChangeMinuteEdit();
	afx_msg void OnChangeSecondEdit();
};

IMPLEMENT_DYNAMIC(CScheduleDlg, CDialogEx)

CScheduleDlg::CScheduleDlg() : CDialogEx(IDD_SCHEDULEDLG)
, m_bDoEveryday(FALSE)
, m_bIsEnable(FALSE)
, m_nHour(0)
, m_nMinute(0)
, m_nSecond(0)
{
}

CScheduleDlg::~CScheduleDlg()
{
}

void CScheduleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ACTION_LIST, m_listAction);
	DDX_Control(pDX, IDC_DATEOPT, m_ctrlDate);
	DDX_Check(pDX, IDC_EVERYDAYOPT, m_bDoEveryday);
	DDX_Check(pDX, IDC_ENABLESCHEDULE, m_bIsEnable);
	DDX_Text(pDX, IDC_HOUR_EDIT, m_nHour);
	DDX_Text(pDX, IDC_MINUTE_EDIT, m_nMinute);
	DDX_Text(pDX, IDC_SECOND_EDIT, m_nSecond);
	DDX_Control(pDX, IDC_HOUR_SPIN, m_ctrlHourSpin);
	DDX_Control(pDX, IDC_MINUTE_SPIN, m_ctrlMinuteSpin);
	DDX_Control(pDX, IDC_SECOND_SPIN, m_ctrlSecondSpin);
}


BEGIN_MESSAGE_MAP(CScheduleDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CScheduleDlg::OnSaveAndApply)
	ON_BN_CLICKED(IDCANCEL, &CScheduleDlg::OnCloseAndExit)
	ON_BN_CLICKED(IDC_ENABLESCHEDULE, &CScheduleDlg::OnEnableSchedule)
	ON_CBN_SELCHANGE(IDC_ACTION_LIST, &CScheduleDlg::OnChangeAction)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATEOPT, &CScheduleDlg::OnChangeDate)
	ON_BN_CLICKED(IDC_EVERYDAYOPT, &CScheduleDlg::OnDoEveryday)
	ON_NOTIFY(UDN_DELTAPOS, IDC_HOUR_SPIN, &CScheduleDlg::OnChangeHourSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_MINUTE_SPIN, &CScheduleDlg::OnChangeMinuteSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SECOND_SPIN, &CScheduleDlg::OnChangeSecondSpin)
	ON_EN_CHANGE(IDC_HOUR_EDIT, &CScheduleDlg::OnChangeHourEdit)
	ON_EN_CHANGE(IDC_MINUTE_EDIT, &CScheduleDlg::OnChangeMinuteEdit)
	ON_EN_CHANGE(IDC_SECOND_EDIT, &CScheduleDlg::OnChangeSecondEdit)
END_MESSAGE_MAP()


// CScheduleDlg message handlers

BOOL CScheduleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_ctrlHourSpin.SetRange(0, 23);
	m_ctrlHourSpin.SetPos(0);
	m_ctrlHourSpin.SetBuddy(GetDlgItem(IDC_HOUR_EDIT));
	m_ctrlMinuteSpin.SetRange(0, 59);
	m_ctrlMinuteSpin.SetPos(0);
	m_ctrlMinuteSpin.SetBuddy(GetDlgItem(IDC_MINUTE_EDIT));
	m_ctrlSecondSpin.SetRange(0, 59);
	m_ctrlSecondSpin.SetPos(0);
	m_ctrlSecondSpin.SetBuddy(GetDlgItem(IDC_SECOND_EDIT));

	LoadSchedule();
	LoadLanguage();
	SetupControls();
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CScheduleDlg::LoadLanguage()
{
	if (stConfig.nLanguage == LANG_ENG)
	{
		English lang;

		// Set controls text
		this->SetWindowTextW(lang.szCaption);
		GetDlgItem(IDC_ENABLESCHEDULE)->SetWindowText(lang.szActive);
		GetDlgItem(IDC_ACTION_LABEL)->SetWindowText(lang.szActionLabel);
		GetDlgItem(IDC_TIMESET_LABEL)->SetWindowText(lang.szTimeSetting);
		GetDlgItem(IDC_TIME)->SetWindowText(lang.szTimeLabel);
		GetDlgItem(IDC_DATE_LABEL)->SetWindowText(lang.szDateLabel);
		GetDlgItem(IDC_EVERYDAYOPT)->SetWindowText(lang.szEveryday);
		GetDlgItem(IDOK)->SetWindowText(lang.szScdOK);
		GetDlgItem(IDCANCEL)->SetWindowText(lang.szScdCancel);

		// Set combo selections text
		m_listAction.ResetContent();
		m_listAction.AddString(lang.szScreenOff);
		m_listAction.AddString(lang.szSleep);
		m_listAction.AddString(lang.szShutdown);
		m_listAction.AddString(lang.szRestart);
		m_listAction.AddString(lang.szLogOff);
		m_listAction.AddString(lang.szHibernate);
		m_listAction.SetCurSel(0);

		szMessage = lang.szScdMsg;
		szMsgCaption = lang.szScdMsgCpt;

		UpdateData(FALSE);
	}
	else if (stConfig.nLanguage == LANG_VIE)
	{
		Vietnamese lang;

		// Set controls text
		this->SetWindowTextW(lang.szCaption);
		GetDlgItem(IDC_ENABLESCHEDULE)->SetWindowText(lang.szActive);
		GetDlgItem(IDC_ACTION_LABEL)->SetWindowText(lang.szActionLabel);
		GetDlgItem(IDC_TIMESET_LABEL)->SetWindowText(lang.szTimeSetting);
		GetDlgItem(IDC_TIME)->SetWindowText(lang.szTimeLabel);
		GetDlgItem(IDC_DATE_LABEL)->SetWindowText(lang.szDateLabel);
		GetDlgItem(IDC_EVERYDAYOPT)->SetWindowText(lang.szEveryday);
		GetDlgItem(IDOK)->SetWindowText(lang.szScdOK);
		GetDlgItem(IDCANCEL)->SetWindowText(lang.szScdCancel);

		// Set combo selections text
		m_listAction.ResetContent();
		m_listAction.AddString(lang.szScreenOff);
		m_listAction.AddString(lang.szSleep);
		m_listAction.AddString(lang.szShutdown);
		m_listAction.AddString(lang.szRestart);
		m_listAction.AddString(lang.szLogOff);
		m_listAction.AddString(lang.szHibernate);
		m_listAction.SetCurSel(0);

		szMessage = lang.szScdMsg;
		szMsgCaption = lang.szScdMsgCpt;

		UpdateData(FALSE);
	}
}

void CScheduleDlg::LoadSchedule()
{
	isEnable = stConfig.stSchedule.isScheduleOn;
	isDoEveryday = stConfig.stSchedule.isDoEveryday;
	nAction = stConfig.stSchedule.nAction - ACTION_NOTHING - 1;
	
	m_timeSchedule.wHour = stConfig.stSchedule.nHour;
	m_timeSchedule.wMinute = stConfig.stSchedule.nMinute;
	m_timeSchedule.wSecond = stConfig.stSchedule.nSecond;
	m_timeSchedule.wDay = stConfig.stSchedule.nDay;
	m_timeSchedule.wMonth = stConfig.stSchedule.nMonth;
	m_timeSchedule.wYear = stConfig.stSchedule.nYear;
}

BOOL CScheduleDlg::SaveSchedule()
{
	UpdateData(TRUE);
	nAction = m_listAction.GetCurSel();
	m_timeSchedule.wHour = m_nHour; m_timeSchedule.wMinute = m_nMinute; m_timeSchedule.wSecond = m_nSecond;
	SYSTEMTIME m_timeTemp;
	m_ctrlDate.GetTime(&m_timeTemp);
	m_timeSchedule.wDay = m_timeTemp.wDay; m_timeSchedule.wMonth = m_timeTemp.wMonth; m_timeSchedule.wYear = m_timeTemp.wYear;

	// Save schedule info
	stConfig.stSchedule.isScheduleOn = m_bIsEnable;
	stConfig.stSchedule.nAction = ACTION_NOTHING + nAction + 1;
	stConfig.stSchedule.nHour = m_timeSchedule.wHour;
	stConfig.stSchedule.nMinute = m_timeSchedule.wMinute;
	stConfig.stSchedule.nSecond = m_timeSchedule.wSecond;
	stConfig.stSchedule.nDay = m_timeSchedule.wDay;
	stConfig.stSchedule.nMonth = m_timeSchedule.wMonth;
	stConfig.stSchedule.nYear = m_timeSchedule.wYear;
	stConfig.stSchedule.isDoEveryday = m_bDoEveryday;
	stSavedConfig = stConfig;

	// Save to registry
	AfxGetApp()->WriteProfileInt(L"Schedule", L"isEnable", stSavedConfig.stSchedule.isScheduleOn);
	AfxGetApp()->WriteProfileInt(L"Schedule", L"hour", stSavedConfig.stSchedule.nHour);
	AfxGetApp()->WriteProfileInt(L"Schedule", L"minute", stSavedConfig.stSchedule.nMinute);
	AfxGetApp()->WriteProfileInt(L"Schedule", L"second", stSavedConfig.stSchedule.nSecond);
	AfxGetApp()->WriteProfileInt(L"Schedule", L"day", stSavedConfig.stSchedule.nDay);
	AfxGetApp()->WriteProfileInt(L"Schedule", L"month", stSavedConfig.stSchedule.nMonth);
	AfxGetApp()->WriteProfileInt(L"Schedule", L"year", stSavedConfig.stSchedule.nYear);
	AfxGetApp()->WriteProfileInt(L"Schedule", L"action", stSavedConfig.stSchedule.nAction);
	AfxGetApp()->WriteProfileInt(L"Schedule", L"isDoEveryday", stSavedConfig.stSchedule.isDoEveryday);

	return TRUE;
}

void CScheduleDlg::SetupControls()
{
	m_listAction.SetCurSel(nAction);
	m_nHour = m_timeSchedule.wHour;
	m_nMinute = m_timeSchedule.wMinute;
	m_nSecond = m_timeSchedule.wSecond;
	CTime timeTemp = CTime(m_timeSchedule);
	m_ctrlDate.SetTime(&timeTemp);
	UpdateData(FALSE);

	m_bIsEnable = isEnable;
	m_listAction.EnableWindow(m_bIsEnable);
	
	GetDlgItem(IDC_HOUR_EDIT)->EnableWindow(m_bIsEnable);
	GetDlgItem(IDC_MINUTE_EDIT)->EnableWindow(m_bIsEnable);
	GetDlgItem(IDC_SECOND_EDIT)->EnableWindow(m_bIsEnable);
	GetDlgItem(IDC_HOUR_SPIN)->EnableWindow(m_bIsEnable);
	GetDlgItem(IDC_HOUR_SPIN)->EnableWindow(m_bIsEnable);
	GetDlgItem(IDC_HOUR_SPIN)->EnableWindow(m_bIsEnable);

	m_ctrlDate.EnableWindow(m_bIsEnable);

	GetDlgItem(IDC_EVERYDAYOPT)->EnableWindow(m_bIsEnable);
	m_bDoEveryday = isDoEveryday;
	if (m_bDoEveryday == TRUE)
		m_ctrlDate.EnableWindow(FALSE);
	UpdateData(FALSE);
}

void CScheduleDlg::OnSaveAndApply()
{
	// TODO: Add your control notification handler code here
	SaveSchedule();
	CDialogEx::OnOK();
}

void CScheduleDlg::OnCloseAndExit()
{
	// TODO: Add your control notification handler code here
	if (isEnableChanged || isActionChanged || isHourChanged || isMinuteChanged || isSecondChanged || isDateChanged || isDoEvrdChanged)
	{
		BOOL bConfirm = MessageBox(szMessage, szMsgCaption, MB_YESNO | MB_ICONQUESTION);
		if (bConfirm == IDYES)
			SaveSchedule();
	}
	CDialogEx::OnCancel();
}

void CScheduleDlg::OnEnableSchedule()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_bIsEnable == TRUE)
	{
		if (m_bDoEveryday == FALSE)
			m_ctrlDate.EnableWindow(TRUE);
	}
	m_listAction.EnableWindow(m_bIsEnable);

	GetDlgItem(IDC_HOUR_EDIT)->EnableWindow(m_bIsEnable);
	GetDlgItem(IDC_MINUTE_EDIT)->EnableWindow(m_bIsEnable);
	GetDlgItem(IDC_SECOND_EDIT)->EnableWindow(m_bIsEnable);
	GetDlgItem(IDC_HOUR_SPIN)->EnableWindow(m_bIsEnable);
	GetDlgItem(IDC_HOUR_SPIN)->EnableWindow(m_bIsEnable);
	GetDlgItem(IDC_HOUR_SPIN)->EnableWindow(m_bIsEnable);

	m_ctrlDate.EnableWindow(m_bIsEnable);
	GetDlgItem(IDC_EVERYDAYOPT)->EnableWindow(m_bIsEnable);
	
	isEnableChanged = (m_bIsEnable != stConfig.stSchedule.isScheduleOn);
	EnableSaveButton();
}

void CScheduleDlg::OnChangeAction()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int nCurSel = m_listAction.GetCurSel();
	nCurSel += ACTION_NOTHING + 1;

	isActionChanged = (nCurSel != stConfig.stSchedule.nAction);
	EnableSaveButton();
}

void CScheduleDlg::OnChangeDate(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	SYSTEMTIME timeTemp;
	m_ctrlDate.GetTime(&timeTemp);
	isDateChanged = (timeTemp.wDay != m_timeSchedule.wDay || timeTemp.wMonth != m_timeSchedule.wMonth || timeTemp.wYear != m_timeSchedule.wYear);
	EnableSaveButton();
	*pResult = 0;
}

void CScheduleDlg::OnDoEveryday()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_bDoEveryday == FALSE)
	{
		if (m_bIsEnable == TRUE)
			m_ctrlDate.EnableWindow(TRUE);
	}
	else
		m_ctrlDate.EnableWindow(FALSE);

	isDoEvrdChanged = (m_bDoEveryday != stConfig.stSchedule.isDoEveryday);
	EnableSaveButton();
}

void CScheduleDlg::EnableSaveButton()
{
	GetDlgItem(IDOK)->EnableWindow(isEnableChanged || isActionChanged || isHourChanged || isMinuteChanged || isSecondChanged || isDateChanged || isDoEvrdChanged);
}

void CScheduleDlg::OnChangeHourSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	UINT m_nTemp = m_nHour + pNMUpDown->iDelta;
	if (m_nTemp >= 0 && m_nTemp <= 23)
		m_nHour = m_nTemp;
	isHourChanged = (m_nHour != m_timeSchedule.wHour);
	EnableSaveButton();
	UpdateData(FALSE);

	*pResult = 0;
}

void CScheduleDlg::OnChangeMinuteSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	UINT m_nTemp = m_nMinute + pNMUpDown->iDelta;
	if (m_nTemp >= 0 && m_nTemp <= 59)
		m_nMinute = m_nTemp;
	isMinuteChanged = (m_nMinute != m_timeSchedule.wMinute);
	EnableSaveButton();
	UpdateData(FALSE);

	*pResult = 0;
}

void CScheduleDlg::OnChangeSecondSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	UINT m_nTemp = m_nSecond + pNMUpDown->iDelta;
	if (m_nTemp >= 0 && m_nTemp <= 59)
		m_nSecond = m_nTemp;
	isSecondChanged = (m_nSecond != m_timeSchedule.wSecond);
	EnableSaveButton();
	UpdateData(FALSE);

	*pResult = 0;
}

void CScheduleDlg::OnChangeHourEdit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);
	if (m_nHour < 0 || m_nHour > 59)
	{
		MessageBox(L"Error: Invalid value! Please re-enter.", L"Error", MB_OK | MB_ICONERROR);
		m_nHour = m_timeSchedule.wHour;
	}
	isHourChanged = (m_nHour != m_timeSchedule.wHour);
	EnableSaveButton();
	UpdateData(FALSE);
}

void CScheduleDlg::OnChangeMinuteEdit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);
	if (m_nMinute < 0 || m_nMinute > 59)
	{
		MessageBox(L"Error: Invalid value! Please re-enter.", L"Error", MB_OK | MB_ICONERROR);
		m_nMinute = m_timeSchedule.wMinute;
	}
	isMinuteChanged = (m_nMinute != m_timeSchedule.wMinute);
	EnableSaveButton();
	UpdateData(FALSE);
}

void CScheduleDlg::OnChangeSecondEdit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);
	if (m_nHour < 0 || m_nHour > 59)
	{
		MessageBox(L"Error: Invalid value! Please re-enter.", L"Error", MB_OK | MB_ICONERROR);
		m_nSecond = m_timeSchedule.wSecond;
	}
	isSecondChanged = (m_nSecond != m_timeSchedule.wSecond);
	EnableSaveButton();
	UpdateData(FALSE);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// CPowerPlusDlg dialog used for Main Window

CPowerPlusDlg::CPowerPlusDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_POWERPLUS_DIALOG, pParent)
	, m_bShowAtStartup(FALSE)
	, m_bStartup(FALSE)
	, m_bAskBefore(FALSE)
	, m_bSaveLog(FALSE)
	, m_bShowError(FALSE)
	, m_bENBRightMouse(FALSE)
	, m_bShowTipBefore(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	isNotifyIconShowed = FALSE;
	
	// Loading configurations right-here
	memset(&stConfig, 0, sizeof(CONFIGURATION));
	memset(&stSavedConfig, 0, sizeof(CONFIGURATION));
	LoadConfiguration();

	m_bIsExpanded = TRUE;
	m_pSize = NULL;
}

CPowerPlusDlg::~CPowerPlusDlg()
{
	delete m_pSize;
}

void CPowerPlusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAINACTION_LIST, m_listMainAction);
	DDX_Control(pDX, IDC_SECONDARYACTION_LIST, m_listSecondaryAction);
	DDX_Control(pDX, IDC_LANGUAGE_LIST, m_listLanguage);
	DDX_Check(pDX, IDC_DISPLAYDLG, m_bShowAtStartup);
	DDX_Check(pDX, IDC_STARTUP, m_bStartup);
	DDX_Check(pDX, IDC_ASKBEFORE, m_bAskBefore);
	DDX_Check(pDX, IDC_SAVELOGS, m_bSaveLog);
	DDX_Check(pDX, IDC_SHOWERRORS, m_bShowError);
	DDX_Check(pDX, IDC_SELECTRIGHTMOUSE, m_bENBRightMouse);
	DDX_Check(pDX, IDC_SHOWTIPBEFORE, m_bShowTipBefore);
	//  DDX_Control(pDX, IDC_FRAMEWND, nFrameWnd);
}

BEGIN_MESSAGE_MAP(CPowerPlusDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CPowerPlusDlg::OnApplyAndClose)
	ON_BN_CLICKED(IDC_ABOUT_BTN, &CPowerPlusDlg::OnBnClickedAboutBtn)
	ON_BN_CLICKED(IDC_HELP_BTN, &CPowerPlusDlg::OnBnClickedHelpBtn)
	ON_BN_CLICKED(IDC_EXPAND, &CPowerPlusDlg::OnExpand)
	ON_BN_CLICKED(IDC_CONFIG_BACKUP, &CPowerPlusDlg::OnBackupConfiguration)
	ON_BN_CLICKED(IDC_DEFAULT_BTN, &CPowerPlusDlg::OnDefaultOptions)
	ON_BN_CLICKED(IDC_ACTIONSCHEDULE, &CPowerPlusDlg::OnSchedule)
	ON_CBN_SELCHANGE(IDC_LANGUAGE_LIST, &CPowerPlusDlg::OnChangeLanguage)
	ON_CBN_SELCHANGE(IDC_MAINACTION_LIST, &CPowerPlusDlg::OnChangeMainAction)
	ON_CBN_SELCHANGE(IDC_SECONDARYACTION_LIST, &CPowerPlusDlg::OnChangeSecondaryAction)
	ON_BN_CLICKED(IDC_SELECTRIGHTMOUSE, &CPowerPlusDlg::OnEnableRightMouse)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_VIEWLOG_BTN, &CPowerPlusDlg::OnViewActionLog)
END_MESSAGE_MAP()

// CPowerPlusDlg message handlers

BOOL CPowerPlusDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	SetNotifyIcon();
	SetTimer(TIMER_STANDARD_BY_SECOND, 1000, NULL);

	// TODO: Add extra initialization here
	SetControlsText(stConfig.nLanguage);
	SetupControls();
	OnExpand();
	ExpandDialog(FALSE); // Collapse the dialog

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPowerPlusDlg::SetWindowPosition()
{
	// this function basically do nothing
	// everything was set automatically when dialog had initialized
	// so this is just an 'void virtual' function
}

void CPowerPlusDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPowerPlusDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	//SetupButtons();
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.

HCURSOR CPowerPlusDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CPowerPlusDlg::DoAction(UINT nType)
{
	UINT nAction = 0, nActionID = 0, nMsg = 0;
	switch (nType)
	{
	case LEFTMOUSE:
	case ACTSCHEDULE:
		nActionID = stConfig.actionLeftMouse;
		switch (nActionID)
		{
		case ACTION_SCREENOFF: 
			nAction = PW_SCREEN_ACTION; 
			nMsg = EWX_SCREENOFF; 
			stAction.szActionName = "Turn off screen ";
			break;
		case ACTION_SLEEP: 
			nAction = PW_POWER_ACTION; 
			nMsg = EWX_SLEEP; 
			stAction.szActionName = "Turn computer to sleep mode  "; 
			break;
		case ACTION_SHUTDOWN: 
			nAction = PW_POWER_ACTION; 
			nMsg = EWX_SHUTDOWN | EWX_HYBRID_SHUTDOWN; 
			stAction.szActionName = "Shut down computer ";
			break;
		case ACTION_RESTART: 
			nAction = PW_POWER_ACTION; 
			nMsg = EWX_REBOOT; 
			stAction.szActionName = "Restart computer ";
			break;
		case ACTION_LOGOFF:
			nAction = PW_POWER_ACTION; 
			nMsg = EWX_LOGOFF; 
			stAction.szActionName = "Log off ";
			break;
		case ACTION_HIBERNATE:
			nAction = PW_POWER_ACTION; 
			nMsg = EWX_HIBERNATE; 
			stAction.szActionName = "Turn computer to hibernate mode ";
			break;
		}
		break;
	case RIGHTMOUSE:
		nActionID = stConfig.actionRightMouse;
		if (stConfig.isActionRightMouse == TRUE)
			return ShowNotifyMenu();
		else switch (nActionID)
		{
		case ACTION_SCREENOFF: 
			nAction = PW_SCREEN_ACTION;
			nMsg = EWX_SCREENOFF;
			stAction.szActionName = "Turn off screen ";
			break;
		case ACTION_SLEEP:
			nAction = PW_POWER_ACTION;
			nMsg = EWX_SLEEP; 
			stAction.szActionName = "Turn computer to sleep mode  ";
			break;
		case ACTION_SHUTDOWN: 
			nAction = PW_POWER_ACTION;
			nMsg = EWX_SHUTDOWN | EWX_HYBRID_SHUTDOWN;
			stAction.szActionName = "Shut down computer "; 
			break;
		case ACTION_RESTART: 
			nAction = PW_POWER_ACTION; 
			nMsg = EWX_REBOOT;
			stAction.szActionName = "Restart computer ";
			break;
		case ACTION_LOGOFF: 
			nAction = PW_POWER_ACTION; 
			nMsg = EWX_LOGOFF;
			stAction.szActionName = "Log off ";
			break;
		case ACTION_HIBERNATE:
			nAction = PW_POWER_ACTION;
			nMsg = EWX_HIBERNATE; 
			stAction.szActionName = "Turn computer to hibernate mode "; 
			break;
		} break;
	}
	stAction.nTypeOfAction = nMsg;
	if (nActionID == ACTION_SCREENOFF || AskBefore(nActionID, stConfig.nLanguage) == IDYES)
	{
		BOOL bResult = DoPowerAction(nAction, nMsg);
		stAction.isActionSucceed = bResult;
		if (bResult == TRUE)
			stAction.nErrorCode = SUCCESS_NO_ERROR;
		else
			stAction.nErrorCode = FAILED_AND_ERROR;
		SaveLogs(stConfig.isLogsEnabled, stAction);
		return bResult;
	}
	else
		return TRUE;
}

void CPowerPlusDlg::OnViewActionLog()
{
	// TODO: Add your control notification handler code here
	//ShellExecute(this->GetSafeHwnd(), L"open", L"C:\\Windows\\notepad.exe", L"PowerPlus_Log.log", NULL, SW_SHOW);
	ViewActionLog(this->GetSafeHwnd());
}

void CPowerPlusDlg::ViewConfiguration()
{
	ShellExecute(this->GetSafeHwnd(), L"open", L"C:\\Windows\\notepad.exe", L"PowerPlus_Config.ini", NULL, SW_SHOW);
}

BOOL CPowerPlusDlg::LoadConfiguration()
{
	/// Load configuration info
	stSavedConfig.actionLeftMouse = AfxGetApp()->GetProfileIntW(L"Configuration", L"actionLMB", ACTION_SCREENOFF);
	stSavedConfig.actionRightMouse = AfxGetApp()->GetProfileIntW(L"Configuration", L"actionRMB", ACTION_SCREENOFF);
	stSavedConfig.isActionRightMouse = AfxGetApp()->GetProfileIntW(L"Configuration", L"isRMShowMenu", TRUE);
	stSavedConfig.isShowWhenStart = AfxGetApp()->GetProfileIntW(L"Configuration", L"isShowAtStartup", TRUE);
	stSavedConfig.isStartupEnabled = AfxGetApp()->GetProfileIntW(L"Configuration", L"isStartupEnabled", TRUE);
	stSavedConfig.isAskBefore = AfxGetApp()->GetProfileIntW(L"Configuration", L"isAskBefore", FALSE);
	stSavedConfig.isLogsEnabled = AfxGetApp()->GetProfileIntW(L"Configuration", L"isSaveLogs", TRUE);
	stSavedConfig.isShowErrorMsg = AfxGetApp()->GetProfileIntW(L"Configuration", L"isShowError", FALSE);
	stSavedConfig.isScheduleTip = AfxGetApp()->GetProfileIntW(L"Configuration", L"isScheduleTip", FALSE);
	stSavedConfig.nLanguage = AfxGetApp()->GetProfileIntW(L"Configuration", L"languageID", LANG_VIE);

	// Load schedule info

	stSavedConfig.stSchedule.isScheduleOn = AfxGetApp()->GetProfileIntW(L"Schedule", L"isEnable", FALSE);
	stSavedConfig.stSchedule.nHour = AfxGetApp()->GetProfileIntW(L"Schedule", L"hour", 0);
	stSavedConfig.stSchedule.nMinute = AfxGetApp()->GetProfileIntW(L"Schedule", L"minute", 0);
	stSavedConfig.stSchedule.nSecond = AfxGetApp()->GetProfileIntW(L"Schedule", L"second", 0);
	stSavedConfig.stSchedule.nDay = AfxGetApp()->GetProfileIntW(L"Schedule", L"day", 0);
	stSavedConfig.stSchedule.nMonth = AfxGetApp()->GetProfileIntW(L"Schedule", L"month", 0);
	stSavedConfig.stSchedule.nYear = AfxGetApp()->GetProfileIntW(L"Schedule", L"year", 0);
	stSavedConfig.stSchedule.nAction = AfxGetApp()->GetProfileIntW(L"Schedule", L"action", ACTION_NOTHING);
	stSavedConfig.stSchedule.isDoEveryday = AfxGetApp()->GetProfileIntW(L"Schedule", L"isDoEveryday", FALSE);

	// Prepare configuration for using
	stConfig = stSavedConfig;
	return TRUE;
}

BOOL CPowerPlusDlg::SaveConfiguration()
{
	BOOL bIsSuccess = TRUE;

	// Save configurations info
	bIsSuccess |= AfxGetApp()->WriteProfileInt(L"Configuration", L"actionLMB", stSavedConfig.actionLeftMouse);
	bIsSuccess |= AfxGetApp()->WriteProfileInt(L"Configuration", L"actionRMB", stSavedConfig.actionRightMouse);
	bIsSuccess |= AfxGetApp()->WriteProfileInt(L"Configuration", L"isRMShowMenu", stSavedConfig.isActionRightMouse);
	bIsSuccess |= AfxGetApp()->WriteProfileInt(L"Configuration", L"isShowAtStartup", stSavedConfig.isShowWhenStart);
	bIsSuccess |= AfxGetApp()->WriteProfileInt(L"Configuration", L"isStartupEnabled", stSavedConfig.isStartupEnabled);
	bIsSuccess |= AfxGetApp()->WriteProfileInt(L"Configuration", L"isAskBefore", stSavedConfig.isAskBefore);
	bIsSuccess |= AfxGetApp()->WriteProfileInt(L"Configuration", L"isSaveLogs", stSavedConfig.isLogsEnabled);
	bIsSuccess |= AfxGetApp()->WriteProfileInt(L"Configuration", L"isShowError", stSavedConfig.isShowErrorMsg);
	bIsSuccess |= AfxGetApp()->WriteProfileInt(L"Configuration", L"isScheduleTip", stSavedConfig.isScheduleTip);
	bIsSuccess |= AfxGetApp()->WriteProfileInt(L"Configuration", L"languageID", stSavedConfig.nLanguage);

	// Save schedule info
	bIsSuccess |= AfxGetApp()->WriteProfileInt(L"Schedule", L"isEnable", stSavedConfig.stSchedule.isScheduleOn);
	bIsSuccess |= AfxGetApp()->WriteProfileInt(L"Schedule", L"hour", stSavedConfig.stSchedule.nHour);
	bIsSuccess |= AfxGetApp()->WriteProfileInt(L"Schedule", L"minute", stSavedConfig.stSchedule.nMinute);
	bIsSuccess |= AfxGetApp()->WriteProfileInt(L"Schedule", L"second", stSavedConfig.stSchedule.nSecond);
	bIsSuccess |= AfxGetApp()->WriteProfileInt(L"Schedule", L"day", stSavedConfig.stSchedule.nDay);
	bIsSuccess |= AfxGetApp()->WriteProfileInt(L"Schedule", L"month", stSavedConfig.stSchedule.nMonth);
	bIsSuccess |= AfxGetApp()->WriteProfileInt(L"Schedule", L"year", stSavedConfig.stSchedule.nYear);
	bIsSuccess |= AfxGetApp()->WriteProfileInt(L"Schedule", L"action", stSavedConfig.stSchedule.nAction);
	bIsSuccess |= AfxGetApp()->WriteProfileInt(L"Schedule", L"isDoEveryday", stSavedConfig.stSchedule.isDoEveryday);

	int isEASOk = EnableAutoStart(stSavedConfig.isStartupEnabled);
	bIsSuccess |= isEASOk ? TRUE : FALSE;

	return bIsSuccess;
}

void CPowerPlusDlg::PreparePrivateProfileFile(std::ofstream* &ofProfileName)
{
	ofProfileName = new ofstream("ConfigBackup.reg");
	*ofProfileName << "Windows Registry Editor Version 5.00\n\n; Power++ 2.0 STL registry\n; Generate by Stark Lee\n\n";
	*ofProfileName << "[HKEY_CURRENT_USER\\SOFTWARE\\Stark Industries\\PowerPlus]\n\n";
}

void CPowerPlusDlg::WritePrivateProfileInt(std::ofstream* ofProfileName, std::string lpKeyName, UINT uiValue)
{
	*ofProfileName << "\"" << lpKeyName << "\"=dword:";
	(*ofProfileName).width(8);
	(*ofProfileName).fill('0');
	*ofProfileName << std::right << std::hex << uiValue << endl;
}

void CPowerPlusDlg::ClosePrivateProfileFile(std::ofstream* ofProfileName)
{
	ofProfileName->close();
}

BOOL CPowerPlusDlg::BackupConfiguration()
{
	if (!LoadConfiguration())
		return FALSE;

	std::ofstream *ofProfileName;
	PreparePrivateProfileFile(ofProfileName);

	*ofProfileName << "[HKEY_CURRENT_USER\\SOFTWARE\\Stark Industries\\PowerPlus\\Configuration]\n";

	WritePrivateProfileInt(ofProfileName, "actionLMB", stSavedConfig.actionLeftMouse);
	WritePrivateProfileInt(ofProfileName, "actionRMB", stSavedConfig.actionRightMouse);
	WritePrivateProfileInt(ofProfileName, "isRMShowMenu", stSavedConfig.isActionRightMouse);
	WritePrivateProfileInt(ofProfileName, "isShowAtStartup", stSavedConfig.isShowWhenStart);
	WritePrivateProfileInt(ofProfileName, "isStartupEnabled", stSavedConfig.isStartupEnabled);
	WritePrivateProfileInt(ofProfileName, "isAskBefore", stSavedConfig.isAskBefore);
	WritePrivateProfileInt(ofProfileName, "isSaveLogs", stSavedConfig.isLogsEnabled);
	WritePrivateProfileInt(ofProfileName, "isShowError", stSavedConfig.isShowErrorMsg);
	WritePrivateProfileInt(ofProfileName, "isScheduleTip", stSavedConfig.isScheduleTip);
	WritePrivateProfileInt(ofProfileName, "languageID", stSavedConfig.nLanguage);

	*ofProfileName << "\n[HKEY_CURRENT_USER\\SOFTWARE\\Stark Industries\\PowerPlus\\Schedule]\n";
	
	WritePrivateProfileInt(ofProfileName, "isEnable", stSavedConfig.stSchedule.isScheduleOn);
	WritePrivateProfileInt(ofProfileName, "hour", stSavedConfig.stSchedule.nHour);
	WritePrivateProfileInt(ofProfileName, "minute", stSavedConfig.stSchedule.nMinute);
	WritePrivateProfileInt(ofProfileName, "second", stSavedConfig.stSchedule.nSecond);
	WritePrivateProfileInt(ofProfileName, "day", stSavedConfig.stSchedule.nDay);
	WritePrivateProfileInt(ofProfileName, "month", stSavedConfig.stSchedule.nMonth);
	WritePrivateProfileInt(ofProfileName, "year", stSavedConfig.stSchedule.nYear);
	WritePrivateProfileInt(ofProfileName, "action", stSavedConfig.stSchedule.nAction);
	WritePrivateProfileInt(ofProfileName, "isDoEveryday", stSavedConfig.stSchedule.isDoEveryday);

	ClosePrivateProfileFile(ofProfileName);

	return TRUE;
}

void CPowerPlusDlg::OnApplyAndClose()
{
	// TODO: Add your control notification handler code here
	CString strInfo;
	UpdateData(TRUE);

	// Get left mouse button action
	int nActionLMPos = m_listMainAction.GetCurSel();
	stConfig.actionLeftMouse = ACTION_NOTHING + nActionLMPos + 1;

	// Get right mouse button action
	int nActionRMPos = m_listSecondaryAction.GetCurSel();
	stConfig.actionRightMouse = ACTION_NOTHING + nActionRMPos + 1;
	stConfig.isActionRightMouse = m_bENBRightMouse;
	if (m_bENBRightMouse == TRUE)
		stConfig.actionRightMouse = ACTION_SHOWMENU;

	// Get avanced options
	stConfig.isShowWhenStart = m_bShowAtStartup;
	stConfig.isStartupEnabled = m_bStartup;
	stConfig.isAskBefore = m_bAskBefore;
	stConfig.isLogsEnabled = m_bSaveLog;
	stConfig.isShowErrorMsg = m_bShowError;
	stConfig.isScheduleTip = m_bShowTipBefore;

	// Get language option
	int nLangPos = m_listLanguage.GetCurSel();
	stConfig.nLanguage = nLangPos;

	// Copy configurations and save
	stSavedConfig = stConfig;
	SaveConfiguration();
	UpdateNotifyIcon();

	ShowWindow(FALSE);
}

void CPowerPlusDlg::OnBnClickedAboutBtn()
{
	// TODO: Add your control notification handler code here
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CPowerPlusDlg::SetNotifyIcon()
{
	if (isNotifyIconShowed)
		return;
	memset(&stNotifyIcon, 0, sizeof(NOTIFYICONDATA));
	stNotifyIcon.hWnd = this->GetSafeHwnd();
	stNotifyIcon.cbSize = sizeof(NOTIFYICONDATA);
	stNotifyIcon.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetNotifyTipText(&stNotifyIcon, stConfig.nLanguage);
	stNotifyIcon.uCallbackMessage = WM_TRAYICON;
	stNotifyIcon.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	stNotifyIcon.uID = 500;
	Shell_NotifyIcon(NIM_ADD, &stNotifyIcon);
	isNotifyIconShowed = TRUE;
}

BOOL CPowerPlusDlg::ShowNotifyMenu()
{
	CMenu menuNotify, *pMenu;
	menuNotify.LoadMenu(IDR_MENU1);
	pMenu = menuNotify.GetSubMenu(0);
	this->SetForegroundWindow();
	POINT ptCursor;
	GetCursorPos(&ptCursor);
	SetMenuItemsText(pMenu, stConfig.nLanguage);
	SetMenuDefaultItem(pMenu->m_hMenu, IDM_SHOWWINDOW, NULL);
	BOOL bResult = pMenu->TrackPopupMenu(TPM_RIGHTALIGN | TPM_BOTTOMALIGN, ptCursor.x, ptCursor.y, (CWnd*) this, NULL);
	return bResult;
}

void CPowerPlusDlg::UpdateNotifyIcon()
{
	SetNotifyTipText(&stNotifyIcon, stConfig.nLanguage);
	Shell_NotifyIcon(NIM_MODIFY, &stNotifyIcon);
}

void CPowerPlusDlg::RemoveNotifyIcon()
{
	if (!isNotifyIconShowed)
		return;
	stNotifyIcon.hIcon = NULL;
	Shell_NotifyIcon(NIM_DELETE, &stNotifyIcon);
	isNotifyIconShowed = FALSE;
}

LRESULT CPowerPlusDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	switch (message)
	{
	case WM_TRAYICON:
		switch (lParam)
		{
		case WM_LBUTTONDOWN:
			DoAction(LEFTMOUSE);
			break;
		case WM_RBUTTONUP:
			DoAction(RIGHTMOUSE);
			break;
		case WM_MBUTTONDOWN:
			PostMessage(WM_COMMAND, (WPARAM)IDM_SHOWWINDOW, (LPARAM)0);
			break;
		//case WM_LBUTTONDBLCLK:
		//	UINT uiID = GetMenuDefaultItem(pMenu->m_hMenu, FALSE, 0);
		//	if (uiID != -1)
		//	{
		//		// SwitchMode();
		//		PostMessage(WM_COMMAND, uiID, 0);
		//	}
		//	break;
		}
		return 0;
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		// BEGIN: Code for action items
		case IDM_SCREENOFF:
			DoPowerAction(PW_SCREEN_ACTION, SC_MONITORPOWER);
			break;
		case IDM_STANDBY:
			DoPowerAction(PW_POWER_ACTION, EWX_SLEEP);
			break;
		case IDM_SHUTDOWN:
			DoPowerAction(PW_POWER_ACTION, EWX_POWEROFF);
			break;
		case IDM_RESTART:
			DoPowerAction(PW_POWER_ACTION, EWX_REBOOT);
			break;
		case IDM_LOGOFF:
			DoPowerAction(PW_POWER_ACTION, EWX_LOGOFF);
			break;
		case IDM_HIBERNATE:
			DoPowerAction(PW_POWER_ACTION, EWX_HIBERNATE);
			break;
		case IDM_ACTIONSCHEDULE:
			OnSchedule();
			break;
		// END
		// BEGIN: Code for another items
		case IDM_ABOUT:
			OnBnClickedAboutBtn();
			break;
		case IDM_HELP:
			OnBnClickedHelpBtn();
			break;
		case IDM_VIEWLOG:
			ViewActionLog(this->GetSafeHwnd());
			break;
		case IDM_CONFIGBACKUP:
			BackupConfiguration();
			break;
		case IDM_SHOWWINDOW:
			ExpandDialog(FALSE);
			OnPanel();
			break;
		// END
		}
		return CDialogEx::WindowProc(message, wParam, lParam);
		break;
	case WM_DESTROY:
		OnDestroy();
		break;
	case WM_QUERYENDSESSION:
		OnApplyAndClose();
		break;
	}
	return CDialogEx::WindowProc(message, wParam, lParam);
}

void CPowerPlusDlg::OnBnClickedHelpBtn()
{
	// TODO: Add your control notification handler code here
	CHelpDlg dlgHelp;
	dlgHelp.DoModal();
}

void CPowerPlusDlg::SetControlsText(UINT nCurLanguage)
{
	UpdateData(TRUE);
	// Language settings
	if (nCurLanguage == LANG_ENG)
	{
		English language;
		// Items language
		this->GetDlgItem(IDC_MAIN_TITLE)->SetWindowTextW(language.szMainSettings);
		this->GetDlgItem(IDC_LEFTMOUSE_TITLE)->SetWindowTextW(language.szLMButton);
		this->GetDlgItem(IDC_RIGHTMOUSE_TITLE)->SetWindowTextW(language.szRMButton);
		this->GetDlgItem(IDC_SELECTRIGHTMOUSE)->SetWindowTextW(language.szENBRightMouse);
		this->GetDlgItem(IDOK)->SetWindowTextW(language.szApply);
		this->GetDlgItem(IDCANCEL)->SetWindowTextW(language.szExit);
		this->GetDlgItem(IDC_EXPAND)->SetWindowTextW(m_bIsExpanded ? language.szCollapse : language.szExpand);
		this->GetDlgItem(IDC_HELP_BTN)->SetWindowTextW(language.szHelp);
		this->GetDlgItem(IDC_ABOUT_BTN)->SetWindowTextW(language.szAbout);
		this->GetDlgItem(IDC_DEFAULT_BTN)->SetWindowTextW(language.szDefault);
		this->GetDlgItem(IDC_SYSTEM_TITLE)->SetWindowTextW(language.szAdvOpts);
		this->GetDlgItem(IDC_DISPLAYDLG)->SetWindowTextW(language.szShowAtStartup);
		this->GetDlgItem(IDC_STARTUP)->SetWindowTextW(language.szStartup);
		this->GetDlgItem(IDC_ASKBEFORE)->SetWindowTextW(language.szAskBefore);
		this->GetDlgItem(IDC_SAVELOGS)->SetWindowTextW(language.szSaveLog);
		this->GetDlgItem(IDC_SHOWERRORS)->SetWindowTextW(language.szShowError);
		this->GetDlgItem(IDC_SHOWTIPBEFORE)->SetWindowTextW(language.szRemindAction);
		this->GetDlgItem(IDC_LANGUAGE_TITLE)->SetWindowTextW(language.szLanguage);
		this->GetDlgItem(IDC_VIEWLOG_BTN)->SetWindowTextW(language.szViewLog);
		this->GetDlgItem(IDC_CONFIG_BACKUP)->SetWindowTextW(language.szBackup);
		this->GetDlgItem(IDC_ACTIONSCHEDULE)->SetWindowTextW(language.szSchedule);

		// Combobox language
		m_listMainAction.ResetContent();
		m_listMainAction.AddString(language.szScreenOff);
		m_listMainAction.AddString(language.szSleep);
		m_listMainAction.AddString(language.szShutdown);
		m_listMainAction.AddString(language.szRestart);
		m_listMainAction.AddString(language.szLogOff);
		m_listMainAction.AddString(language.szHibernate);
		m_listMainAction.SetCurSel(stConfig.actionLeftMouse - ACTION_NOTHING - 1);
		
		m_listSecondaryAction.ResetContent();
		m_listSecondaryAction.AddString(language.szScreenOff);
		m_listSecondaryAction.AddString(language.szSleep);
		m_listSecondaryAction.AddString(language.szShutdown);
		m_listSecondaryAction.AddString(language.szRestart);
		m_listSecondaryAction.AddString(language.szLogOff);
		m_listSecondaryAction.AddString(language.szHibernate);
		m_listSecondaryAction.AddString(language.szJustMenu);
		m_listSecondaryAction.SetCurSel(stConfig.actionRightMouse - ACTION_NOTHING - 1);

		m_listLanguage.ResetContent();
		m_listLanguage.AddString(language.szVietnamese);
		m_listLanguage.AddString(language.szEnglish);
		m_listLanguage.SetCurSel(stConfig.nLanguage);

		m_strCollapse = language.szCollapse;
		m_strExpand = language.szExpand;
	}
	else if (nCurLanguage == LANG_VIE)
	{
		Vietnamese language;
		// Items language
		this->GetDlgItem(IDC_MAIN_TITLE)->SetWindowTextW(language.szMainSettings);
		this->GetDlgItem(IDC_LEFTMOUSE_TITLE)->SetWindowTextW(language.szLMButton);
		this->GetDlgItem(IDC_RIGHTMOUSE_TITLE)->SetWindowTextW(language.szRMButton);
		this->GetDlgItem(IDC_SELECTRIGHTMOUSE)->SetWindowTextW(language.szENBRightMouse);
		this->GetDlgItem(IDOK)->SetWindowTextW(language.szApply);
		this->GetDlgItem(IDCANCEL)->SetWindowTextW(language.szExit);
		this->GetDlgItem(IDC_EXPAND)->SetWindowTextW(m_bIsExpanded ? language.szCollapse : language.szExpand);
		this->GetDlgItem(IDC_HELP_BTN)->SetWindowTextW(language.szHelp);
		this->GetDlgItem(IDC_ABOUT_BTN)->SetWindowTextW(language.szAbout);
		this->GetDlgItem(IDC_DEFAULT_BTN)->SetWindowTextW(language.szDefault);
		this->GetDlgItem(IDC_SYSTEM_TITLE)->SetWindowTextW(language.szAdvOpts);
		this->GetDlgItem(IDC_DISPLAYDLG)->SetWindowTextW(language.szShowAtStartup);
		this->GetDlgItem(IDC_STARTUP)->SetWindowTextW(language.szStartup);
		this->GetDlgItem(IDC_ASKBEFORE)->SetWindowTextW(language.szAskBefore);
		this->GetDlgItem(IDC_SAVELOGS)->SetWindowTextW(language.szSaveLog);
		this->GetDlgItem(IDC_SHOWERRORS)->SetWindowTextW(language.szShowError);
		this->GetDlgItem(IDC_SHOWTIPBEFORE)->SetWindowTextW(language.szRemindAction);
		this->GetDlgItem(IDC_LANGUAGE_TITLE)->SetWindowTextW(language.szLanguage);
		this->GetDlgItem(IDC_VIEWLOG_BTN)->SetWindowTextW(language.szViewLog);
		this->GetDlgItem(IDC_CONFIG_BACKUP)->SetWindowTextW(language.szBackup);
		this->GetDlgItem(IDC_ACTIONSCHEDULE)->SetWindowTextW(language.szSchedule);

		// Combobox language
		m_listMainAction.ResetContent();
		m_listMainAction.AddString(language.szScreenOff);
		m_listMainAction.AddString(language.szSleep);
		m_listMainAction.AddString(language.szShutdown);
		m_listMainAction.AddString(language.szRestart);
		m_listMainAction.AddString(language.szLogOff);
		m_listMainAction.AddString(language.szHibernate);
		m_listMainAction.SetCurSel(stConfig.actionLeftMouse - ACTION_NOTHING - 1);

		m_listSecondaryAction.ResetContent();
		m_listSecondaryAction.AddString(language.szScreenOff);
		m_listSecondaryAction.AddString(language.szSleep);
		m_listSecondaryAction.AddString(language.szShutdown);
		m_listSecondaryAction.AddString(language.szRestart);
		m_listSecondaryAction.AddString(language.szLogOff);
		m_listSecondaryAction.AddString(language.szHibernate);
		m_listSecondaryAction.AddString(language.szJustMenu);
		m_listSecondaryAction.SetCurSel(stConfig.actionRightMouse - ACTION_NOTHING - 1);

		m_listLanguage.ResetContent();
		m_listLanguage.AddString(language.szVietnamese);
		m_listLanguage.AddString(language.szEnglish);
		m_listLanguage.SetCurSel(stConfig.nLanguage);

		m_strCollapse = language.szCollapse;
		m_strExpand = language.szExpand;
	}
	else // nCurLanguage >= 2
		MessageBox(L"The language is now unavailble. Coming soon.", L"Unavailble Language", MB_OK | MB_ICONERROR);

	UpdateData(FALSE);
}

void CPowerPlusDlg::SetMenuItemsText(CMenu* pMenu, UINT nCurLanguage)
{
	// Language settings
	if (nCurLanguage == LANG_ENG)
	{
		English language;
		pMenu->ModifyMenu(IDM_ABOUT, MF_BYCOMMAND | MF_STRING, IDM_ABOUT, language.szAbout);
		pMenu->ModifyMenu(IDM_HELP, MF_BYCOMMAND | MF_STRING, IDM_HELP, language.szHelp);
		pMenu->ModifyMenu(IDM_VIEWLOG, MF_BYCOMMAND | MF_STRING, IDM_VIEWLOG, language.szViewLog);
		pMenu->ModifyMenu(IDM_CONFIGBACKUP, MF_BYCOMMAND | MF_STRING, IDM_CONFIGBACKUP, language.szBackup);
		pMenu->ModifyMenu(IDM_SHOWWINDOW, MF_BYCOMMAND | MF_STRING, IDM_SHOWWINDOW, language.szMainWnd);
		pMenu->ModifyMenu(IDCANCEL, MF_BYCOMMAND | MF_STRING, IDCANCEL, language.szExit);
		pMenu->ModifyMenu(6, MF_BYPOSITION| MF_STRING, NULL, language.szActionTitle);
		pMenu->ModifyMenu(IDM_SCREENOFF, MF_BYCOMMAND | MF_STRING, IDM_SCREENOFF, language.szScreenOff);
		pMenu->ModifyMenu(IDM_STANDBY, MF_BYCOMMAND | MF_STRING, IDM_STANDBY, language.szSleep);
		pMenu->ModifyMenu(IDM_SHUTDOWN, MF_BYCOMMAND | MF_STRING, IDM_SHUTDOWN, language.szShutdown);
		pMenu->ModifyMenu(IDM_RESTART, MF_BYCOMMAND | MF_STRING, IDM_RESTART, language.szRestart);
		pMenu->ModifyMenu(IDM_LOGOFF, MF_BYCOMMAND | MF_STRING, IDM_LOGOFF, language.szLogOff);
		pMenu->ModifyMenu(IDM_HIBERNATE, MF_BYCOMMAND | MF_STRING, IDM_HIBERNATE, language.szHibernate);
		pMenu->ModifyMenu(IDM_ACTIONSCHEDULE, MF_BYCOMMAND | MF_STRING, IDM_ACTIONSCHEDULE, language.szSchedule);
	}
	else if (nCurLanguage == LANG_VIE)
	{
		Vietnamese language;
		pMenu->ModifyMenu(IDM_ABOUT, MF_BYCOMMAND | MF_STRING, IDM_ABOUT, language.szAbout);
		pMenu->ModifyMenu(IDM_HELP, MF_BYCOMMAND | MF_STRING, IDM_HELP, language.szHelp);
		pMenu->ModifyMenu(IDM_VIEWLOG, MF_BYCOMMAND | MF_STRING, IDM_VIEWLOG, language.szViewLog);
		pMenu->ModifyMenu(IDM_CONFIGBACKUP, MF_BYCOMMAND | MF_STRING, IDM_CONFIGBACKUP, language.szBackup);
		pMenu->ModifyMenu(IDM_SHOWWINDOW, MF_BYCOMMAND | MF_STRING, IDM_SHOWWINDOW, language.szMainWnd);
		pMenu->ModifyMenu(IDCANCEL, MF_BYCOMMAND | MF_STRING, IDCANCEL, language.szExit);
		pMenu->ModifyMenu(6, MF_BYPOSITION | MF_STRING, NULL, language.szActionTitle);
		pMenu->ModifyMenu(IDM_SCREENOFF, MF_BYCOMMAND | MF_STRING, IDM_SCREENOFF, language.szScreenOff);
		pMenu->ModifyMenu(IDM_STANDBY, MF_BYCOMMAND | MF_STRING, IDM_STANDBY, language.szSleep);
		pMenu->ModifyMenu(IDM_SHUTDOWN, MF_BYCOMMAND | MF_STRING, IDM_SHUTDOWN, language.szShutdown);
		pMenu->ModifyMenu(IDM_RESTART, MF_BYCOMMAND | MF_STRING, IDM_RESTART, language.szRestart);
		pMenu->ModifyMenu(IDM_LOGOFF, MF_BYCOMMAND | MF_STRING, IDM_LOGOFF, language.szLogOff);
		pMenu->ModifyMenu(IDM_HIBERNATE, MF_BYCOMMAND | MF_STRING, IDM_HIBERNATE, language.szHibernate);
		pMenu->ModifyMenu(IDM_ACTIONSCHEDULE, MF_BYCOMMAND | MF_STRING, IDM_ACTIONSCHEDULE, language.szSchedule);
	}
	else // nCurLanguage >= 2
		MessageBox(L"The language is now unavailble. Coming soon.", L"Unavailble Language", MB_OK | MB_ICONERROR);
}

void CPowerPlusDlg::SetNotifyTipText(PNOTIFYICONDATA pNotifyIcon, UINT nCurLanguage)
{
	// Language settings
	CString strTipText = L"";
	LPWSTR lpszFormat = L"";
	LPWSTR lpszLeftText = L"", lpszRightText = L"";
	if (nCurLanguage == LANG_ENG)
	{
		English language;
		lpszFormat = (LPWSTR)language.szNotifyTip;

		switch (stConfig.actionLeftMouse)
		{
		case ACTION_SCREENOFF:
			lpszLeftText = (LPWSTR)language.szTipScreenOff;
			break;
		case ACTION_SLEEP:
			lpszLeftText = (LPWSTR)language.szTipSleep;
			break;
		case ACTION_SHUTDOWN:
			lpszLeftText = (LPWSTR)language.szTipShutdown;
			break;
		case ACTION_RESTART:
			lpszLeftText = (LPWSTR)language.szTipRestart;
			break;
		case ACTION_LOGOFF:
			lpszLeftText = (LPWSTR)language.szTipLogOff;
			break;
		case ACTION_HIBERNATE:
			lpszLeftText = (LPWSTR)language.szTipHibernate;
			break;
		}

		switch (stConfig.actionRightMouse)
		{
		case ACTION_SCREENOFF:
			lpszRightText = (LPWSTR)language.szTipScreenOff;
			break;
		case ACTION_SLEEP:
			lpszRightText = (LPWSTR)language.szTipSleep;
			break;
		case ACTION_SHUTDOWN:
			lpszRightText = (LPWSTR)language.szTipShutdown;
			break;
		case ACTION_RESTART:
			lpszRightText = (LPWSTR)language.szTipRestart;
			break;
		case ACTION_LOGOFF:
			lpszRightText = (LPWSTR)language.szTipLogOff;
			break;
		case ACTION_HIBERNATE:
			lpszRightText = (LPWSTR)language.szTipHibernate;
			break;
		case ACTION_SHOWMENU:
			lpszRightText = (LPWSTR)language.szTipMenu;
			break;
		}
	}
	else if (nCurLanguage == LANG_VIE)
	{
		Vietnamese language;
		lpszFormat = (LPWSTR)language.szNotifyTip;

		switch (stConfig.actionLeftMouse)
		{
		case ACTION_SCREENOFF:
			lpszLeftText = (LPWSTR)language.szTipScreenOff;
			break;
		case ACTION_SLEEP:
			lpszLeftText = (LPWSTR)language.szTipSleep;
			break;
		case ACTION_SHUTDOWN:
			lpszLeftText = (LPWSTR)language.szTipShutdown;
			break;
		case ACTION_RESTART:
			lpszLeftText = (LPWSTR)language.szTipRestart;
			break;
		case ACTION_LOGOFF:
			lpszLeftText = (LPWSTR)language.szTipLogOff;
			break;
		case ACTION_HIBERNATE:
			lpszLeftText = (LPWSTR)language.szTipHibernate;
			break;
		}

		switch (stConfig.actionRightMouse)
		{
		case ACTION_SCREENOFF:
			lpszRightText = (LPWSTR)language.szTipScreenOff;
			break;
		case ACTION_SLEEP:
			lpszRightText = (LPWSTR)language.szTipSleep;
			break;
		case ACTION_SHUTDOWN:
			lpszRightText = (LPWSTR)language.szTipShutdown;
			break;
		case ACTION_RESTART:
			lpszRightText = (LPWSTR)language.szTipRestart;
			break;
		case ACTION_LOGOFF:
			lpszRightText = (LPWSTR)language.szTipLogOff;
			break;
		case ACTION_HIBERNATE:
			lpszRightText = (LPWSTR)language.szTipHibernate;
			break;
		case ACTION_SHOWMENU:
			lpszRightText = (LPWSTR)language.szTipMenu;
			break;
		}
	}
	else // nCurLanguage >= 2
	{
		MessageBox(L"The language is now unavailble. Coming soon.", L"Unavailble Language", MB_OK | MB_ICONERROR);
		return;
	}

	strTipText.Format(lpszFormat, lpszLeftText, lpszRightText);
	StrCpyW(pNotifyIcon->szTip, strTipText.GetString());
}

LPCTSTR CPowerPlusDlg::GetNotifyTipText(PNOTIFYICONDATA pNotifyIcon)
{
	return pNotifyIcon->szTip;
}

void CPowerPlusDlg::OnChangeLanguage()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int nCurSel = m_listLanguage.GetCurSel();
	stConfig.nLanguage = nCurSel;
	SetControlsText(stConfig.nLanguage);
	UpdateNotifyIcon();
}

void CPowerPlusDlg::OnChangeMainAction()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int nCurSel = m_listMainAction.GetCurSel();
	stConfig.actionLeftMouse = ACTION_NOTHING + nCurSel + 1;
	UpdateNotifyIcon();
}

void CPowerPlusDlg::OnChangeSecondaryAction()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int nCurSel = m_listSecondaryAction.GetCurSel();
	if (nCurSel == ACTION_SHOWMENU - ACTION_NOTHING - 1)
		m_bENBRightMouse = TRUE;
	else
		m_bENBRightMouse = FALSE;
	m_listSecondaryAction.EnableWindow(!m_bENBRightMouse);
	UpdateData(FALSE);
}

void CPowerPlusDlg::OnEnableRightMouse()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_listSecondaryAction.SetCurSel(((m_bENBRightMouse == TRUE) ? ACTION_SHOWMENU : stConfig.actionRightMouse) - ACTION_NOTHING - 1);
	this->GetDlgItem(IDC_SECONDARYACTION_LIST)->EnableWindow(!m_bENBRightMouse);
	UpdateData(FALSE);
}

void CPowerPlusDlg::SetupControls()
{
	m_listMainAction.SetCurSel(stConfig.actionLeftMouse - ACTION_NOTHING - 1);
	m_bENBRightMouse = stConfig.isActionRightMouse;

	if (m_bENBRightMouse)
		m_listSecondaryAction.SetCurSel(ACTION_SHOWMENU - ACTION_NOTHING - 1);
	else
		m_listSecondaryAction.SetCurSel(stConfig.actionRightMouse - ACTION_NOTHING - 1);
	m_listSecondaryAction.EnableWindow(!m_bENBRightMouse);

	m_bShowAtStartup = stConfig.isShowWhenStart;
	m_bStartup = stConfig.isStartupEnabled;
	m_bAskBefore = stConfig.isAskBefore;
	m_bSaveLog = stConfig.isLogsEnabled;
	m_bShowError = stConfig.isShowErrorMsg;
	m_bShowTipBefore = stConfig.isScheduleTip;
	m_listLanguage.SetCurSel(stConfig.nLanguage);

	UpdateData(FALSE);
}

void CPowerPlusDlg::SetupButtons()
{
	//CButton* pButton = (CButton*)GetDlgItem(IDC_HELP_BTN);
	//DrawButton(IDR_HELP, NULL, pButton);
	//pButton = (CButton*)GetDlgItem(IDC_ABOUT_BTN);
	//DrawButton(IDR_ABOUT, NULL, pButton);
	//pButton = (CButton*)GetDlgItem(IDOK);
	//DrawButton(IDR_ICONOK, NULL, pButton);
	//pButton = (CButton*)GetDlgItem(IDCANCEL);
	//DrawButton(IDR_ICONCANCEL, NULL, pButton);
	//pButton = (CButton*)GetDlgItem(IDC_EXPAND);
	//if (m_bIsExpanded)
	//	DrawButton(IDR_ICONCOLLAPSE, NULL, pButton);
	//else
	//	DrawButton(IDR_ICONEXPAND, NULL, pButton);
}

void CPowerPlusDlg::OnDestroy()
{
	// TODO: Add your message handler code here
	OnApplyAndClose();
	RemoveNotifyIcon();
	KillTimer(TIMER_STANDARD_BY_SECOND);
	CDialogEx::OnDestroy();
}

int CPowerPlusDlg::AskBefore(UINT nAction, UINT nLanguage)
{
	if (stConfig.isAskBefore == FALSE)
		return IDYES;
	UINT nStringID = nAction - ACTION_NOTHING + 10*(nLanguage + 1) - 1;
	CString strMsg; 
	strMsg.LoadStringW(nStringID);
	int nResult = MessageBox(strMsg, AfxGetAppName(), MB_YESNO | MB_ICONQUESTION);
	return nResult;
}

void CPowerPlusDlg::ExpandDialog(BOOL fExpand)
{
	if (fExpand == m_bIsExpanded)
		return;

	CRect rcWnd, rcFrameWnd, rcChild, rcIntersection;
	CWnd *pWndChild = NULL;
	CWnd *pWndFrame = NULL;
	
	CWnd *pButton = GetDlgItem(IDC_EXPAND);
	if (pButton == NULL)
		return;

	pWndFrame = GetDlgItem(IDC_FRAMEWND);
	if (pWndFrame == NULL)
		return;

	pWndFrame->GetWindowRect(&rcFrameWnd);
	
	for (pWndChild = GetTopWindow(); pWndChild != NULL; pWndChild = pWndChild->GetWindow(GW_HWNDNEXT))
	{
		pWndChild->GetWindowRect(&rcChild);
		if (rcChild.bottom > rcFrameWnd.top)
		{
			switch (pWndChild->GetDlgCtrlID())
			{
			case IDC_SYSTEM_TITLE:
			case IDC_DISPLAYDLG:
			case IDC_LANGUAGE_TITLE:
			case IDC_LANGUAGE_LIST:
				pWndChild->ShowWindow(fExpand); break;
			case IDC_HELP_BTN:
			case IDC_ABOUT_BTN:
			case IDC_DEFAULT_BTN:
			{
				CRect rcChildNew, rcChildOld;
				this->GetDlgItem(pWndChild->GetDlgCtrlID())->GetWindowRect(&rcChildOld);
				this->ScreenToClient(&rcChildOld);
				if (!fExpand)
				{
					CRect rcCollapseBtn;
					GetDlgItem(IDC_COLLAPSE_BTNPOS)->GetWindowRect(&rcCollapseBtn);
					this->ScreenToClient(&rcCollapseBtn);
					rcChildNew = rcChildOld;
					rcChildNew.top = rcCollapseBtn.top;
					rcChildNew.bottom = rcCollapseBtn.bottom;
				}
				else
				{
					CRect rcExpandBtn;
					GetDlgItem(IDC_EXPAND_BTNPOS)->GetWindowRect(&rcExpandBtn);
					this->ScreenToClient(&rcExpandBtn);
					rcChildNew = rcChildOld;
					rcChildNew.top = rcExpandBtn.top;
					rcChildNew.bottom = rcExpandBtn.bottom;
				}
				pWndChild->MoveWindow(&rcChildNew);
			}
				break;
			default:
				pWndChild->EnableWindow(fExpand);
				break;
			}
		}
	}

	if (!fExpand)
	{
		GetWindowRect(&rcWnd);
		if (m_pSize == NULL)
		{
			m_pSize = new CSize;
			m_pSize->cx = rcWnd.right - rcWnd.left;
			m_pSize->cy = rcWnd.bottom - rcWnd.top;
		}

		SetWindowPos(NULL, 0, 0, rcWnd.right - rcWnd.left, rcFrameWnd.bottom - rcWnd.top, SWP_NOMOVE | SWP_NOZORDER);
		pButton->SetWindowTextW(m_strExpand);
	}
	else
	{
		SetWindowPos(NULL, 0, 0, m_pSize->cx, m_pSize->cy, SWP_NOMOVE | SWP_NOZORDER);

		// make sure that the entire dialog box is visible on the user's
		// screen.
		SendMessage(DM_REPOSITION, 0, 0);

		pButton->SetWindowTextW(m_strCollapse);
	}
	
	m_bIsExpanded = !m_bIsExpanded;
}

void CPowerPlusDlg::MoveControls(const int* arrControl, int nCount, int nDir, int nDistance)
{
	if (arrControl == NULL)
		return;

	RECT rcControl;
	CWnd *pControl = NULL;
	for (int nID = 0; nID < nCount; nID++)
	{
		pControl = GetDlgItem(arrControl[nID]);
		if (pControl == NULL)
			break;

		pControl->GetWindowRect(&rcControl);
		if (nDir == DIR_HORZ)
			pControl->SetWindowPos(NULL, rcControl.left + nDistance, rcControl.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		
		else if (nDir == DIR_VERT)
			pControl->SetWindowPos(NULL, rcControl.left, rcControl.top + nDistance, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	
	}
	delete pControl;
}

void CPowerPlusDlg::SetControlsPos(BOOL bExpandOrCollapse)
{
	return;
}

void CPowerPlusDlg::OnExpand()
{
	ExpandDialog(!m_bIsExpanded);
}

void CPowerPlusDlg::OnBackupConfiguration()
{
	// TODO: Add your control notification handler code here
	BackupConfiguration();
}

void CPowerPlusDlg::OnDefaultOptions()
{
	// TODO: Add your control notification handler code here
	m_listMainAction.SetCurSel(0);
	m_listSecondaryAction.SetCurSel(6);
	m_bENBRightMouse = TRUE;
	m_listSecondaryAction.EnableWindow(!m_bENBRightMouse);
	m_bShowAtStartup = TRUE;
	m_bStartup = TRUE;
	m_bAskBefore = FALSE;
	m_bSaveLog = TRUE;
	m_bShowError = FALSE;
	m_bShowTipBefore = FALSE;
	m_listLanguage.SetCurSel(0);
	UpdateData(FALSE);
}

void CPowerPlusDlg::OnSchedule()
{
	// TODO: Add your control notification handler code here
	CScheduleDlg dlgSchedule;
	dlgSchedule.DoModal();
}

//---------------------------------------------------------------
int CPowerPlusDlg::EnableAutoStart(BOOL isEnabled)
{
	long lRes;
	HKEY hKey, hRoot;
	DWORD dwState;
	TCHAR tcPath[_MAX_PATH];
	int isOk;
	OSVERSIONINFO oviOSVersion;
	oviOSVersion.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&oviOSVersion);
	if (oviOSVersion.dwPlatformId == VER_PLATFORM_WIN32_NT)
		hRoot = HKEY_CURRENT_USER;
	else
		hRoot = HKEY_LOCAL_MACHINE;

	lRes = RegCreateKeyEx(hRoot, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_QUERY_VALUE | KEY_SET_VALUE, NULL, &hKey, &dwState);

	if (lRes != ERROR_SUCCESS)
		return 0;

	if (isEnabled) {
		GetModuleFileName(NULL, tcPath, sizeof(tcPath) / sizeof(TCHAR));
		lRes = RegSetValueEx(hKey, STARTUP_REG_VALUENAME, 0, REG_SZ, (LPBYTE)tcPath, (_tcsclen(tcPath) + 1) * sizeof(TCHAR));
		isOk = (lRes == ERROR_SUCCESS);
	}
	else {
		RegDeleteValue(hKey, STARTUP_REG_VALUENAME);
		lRes = RegQueryValueEx(hKey, STARTUP_REG_VALUENAME, 0, NULL, NULL, NULL);
		isOk = (lRes != ERROR_SUCCESS);
	}
	RegCloseKey(hKey);
	return isOk;
}

int CPowerPlusDlg::IsAutoStartEnabled()
{
	long lRes;
	HKEY hKey, hRoot;
	OSVERSIONINFO oviOSVersion;
	oviOSVersion.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&oviOSVersion);
	if (oviOSVersion.dwPlatformId == VER_PLATFORM_WIN32_NT)
		hRoot = HKEY_CURRENT_USER;
	else
		hRoot = HKEY_LOCAL_MACHINE;
	lRes = RegOpenKeyEx(hRoot, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_SET_VALUE | KEY_QUERY_VALUE, &hKey);
	if (lRes != ERROR_SUCCESS)
		return 0;
	lRes = RegQueryValueEx(hKey, STARTUP_REG_VALUENAME, 0, NULL, NULL, NULL);
	RegCloseKey(hKey);
	return (lRes == ERROR_SUCCESS);
}

void CPowerPlusDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	SYSTEMTIME stCurrentTime;
	GetLocalTime(&stCurrentTime);

	if (nIDEvent == TIMER_STANDARD_BY_SECOND)
	{
		if (stConfig.stSchedule.isScheduleOn == TRUE)
		{
			SYSTEMTIME stTimeTemp;
			stTimeTemp.wHour = stConfig.stSchedule.nHour; 
			stTimeTemp.wMinute = stConfig.stSchedule.nMinute; 
			stTimeTemp.wSecond = stConfig.stSchedule.nSecond;
			if (stConfig.stSchedule.isDoEveryday == FALSE)
			{
				stTimeTemp.wDay = stConfig.stSchedule.nDay; 
				stTimeTemp.wMonth = stConfig.stSchedule.nMonth; 
				stTimeTemp.wYear = stConfig.stSchedule.nYear;
			}
			else
			{
				stTimeTemp.wDay = stCurrentTime.wDay; 
				stTimeTemp.wMonth = stCurrentTime.wMonth; 
				stTimeTemp.wYear = stCurrentTime.wYear;
			}

			if (isTimeMatch(stCurrentTime, stTimeTemp))
				DoAction(ACTSCHEDULE);

			else if (stConfig.isScheduleTip == TRUE)
			{
				if (stTimeTemp.wDay == stCurrentTime.wDay &&
					stTimeTemp.wMonth == stCurrentTime.wMonth &&
					stTimeTemp.wYear == stCurrentTime.wYear)
				{
					int nSecondLeft = MinusTwoTime(stCurrentTime, stTimeTemp);
					if (nSecondLeft == 30)
					{
						// Show balloon tip to notify schedule
						// stNotifyIcon.hBalloonIcon = AfxGetApp()->LoadIcon(IDB_PNG1);
						stNotifyIcon.uFlags = NIF_INFO;
						stNotifyIcon.dwInfoFlags = NIIF_INFO;
						stNotifyIcon.uTimeout = 300;
						CString strBalloonTip;
						LPCTSTR lpszBalloonText;
						switch (stConfig.stSchedule.nAction)
						{
						case ACTION_SCREENOFF:
							if (stConfig.nLanguage == LANG_ENG)
							{
								English lang;
								lpszBalloonText = lang.szBTipScreenOff;
							}
							else
							{
								Vietnamese lang;
								lpszBalloonText = lang.szBTipScreenOff;
							}
							break;
						case ACTION_SLEEP:
							if (stConfig.nLanguage == LANG_ENG)
							{
								English lang;
								lpszBalloonText = lang.szBTipSleep;
							}
							else
							{
								Vietnamese lang;
								lpszBalloonText = lang.szBTipSleep;
							}
							break;
						case ACTION_SHUTDOWN:
							if (stConfig.nLanguage == LANG_ENG)
							{
								English lang;
								lpszBalloonText = lang.szBTipShutdown;
							}
							else
							{
								Vietnamese lang;
								lpszBalloonText = lang.szBTipShutdown;
							}
							break;
						case ACTION_RESTART:
							if (stConfig.nLanguage == LANG_ENG)
							{
								English lang;
								lpszBalloonText = lang.szBTipRestart;
							}
							else
							{
								Vietnamese lang;
								lpszBalloonText = lang.szBTipRestart;
							}
							break;
						case ACTION_LOGOFF:
							if (stConfig.nLanguage == LANG_ENG)
							{
								English lang;
								lpszBalloonText = lang.szBTipLogoff;
							}
							else
							{
								Vietnamese lang;
								lpszBalloonText = lang.szBTipLogoff;
							}
							break;
						case ACTION_HIBERNATE:
							if (stConfig.nLanguage == LANG_ENG)
							{
								English lang;
								lpszBalloonText = lang.szBTipHibernate;
							}
							else
							{
								Vietnamese lang;
								lpszBalloonText = lang.szBTipHibernate;
							}
							break;
						}
						if (stConfig.nLanguage == LANG_ENG)
						{
							English lang;
							strBalloonTip.Format(lang.szBalloonTipText, lpszBalloonText, nSecondLeft);
							StrCpy(stNotifyIcon.szInfoTitle, (PWSTR)lang.szBalloonTipTitle);
						}
						else
						{
							Vietnamese lang;
							strBalloonTip.Format(lang.szBalloonTipText, lpszBalloonText, nSecondLeft);
							StrCpy(stNotifyIcon.szInfoTitle, (PWSTR)lang.szBalloonTipTitle);
						}
						StrCpy(stNotifyIcon.szInfo, (PWSTR) strBalloonTip.GetString());
						Shell_NotifyIcon(NIM_MODIFY, &stNotifyIcon);
					}
				}
			}
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CPowerPlusDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	OnApplyAndClose();
}

void CPowerPlusDlg::OnPanel()
{
	if (this->m_hWnd != NULL)
	{
		this->ShowWindow(SW_SHOW);
		this->BringWindowToTop();
	}
}
