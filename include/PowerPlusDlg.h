
// PowerPlusDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CPowerPlusDlg dialog
class CPowerPlusDlg : public CDialogEx
{
// Construction
public:
	CPowerPlusDlg(CWnd* pParent = NULL);	// standard constructor
	~CPowerPlusDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_POWERPLUS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	// Message processing functions
	afx_msg void OnApplyAndClose();
	afx_msg void OnBnClickedAboutBtn();
	afx_msg void OnBnClickedHelpBtn();
	afx_msg void OnChangeLanguage();
	afx_msg void OnChangeMainAction();
	afx_msg void OnChangeSecondaryAction();
	afx_msg void OnEnableRightMouse();
	afx_msg void OnDestroy();
	afx_msg void OnExpand();
	afx_msg void OnBackupConfiguration();
	afx_msg void OnDefaultOptions();
	afx_msg void OnSchedule();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnViewActionLog();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

private:
	// Member using for resizing dialog:
	CString m_strExpand, m_strCollapse;
	BOOL m_bIsExpanded;
	CSize *m_pSize;

	void ExpandDialog(BOOL fExpand);
	void MoveControls(const int* arrControl, int nCount, int nDir, int nDistance);
	void SetControlsPos(BOOL);

	// Dialog control variables:
	CComboBox m_listMainAction;
	CComboBox m_listSecondaryAction;
	CComboBox m_listLanguage;

	BOOL m_bShowAtStartup;
	BOOL m_bStartup;
	BOOL m_bAskBefore;
	BOOL m_bSaveLog;
	BOOL m_bShowError;
	BOOL m_bENBRightMouse;
	BOOL m_bShowTipBefore;

	// Notify Icon Members:
	BOOL isNotifyIconShowed;

	void SetNotifyIcon();
	void UpdateNotifyIcon();
	void RemoveNotifyIcon();
	BOOL ShowNotifyMenu();

	// Setup dialog:
	void SetWindowPosition();
	void SetupControls();
	void SetupButtons();
	void SetControlsText(UINT = 0);
	void SetMenuItemsText(CMenu*, UINT = 0);
	void SetNotifyTipText(PNOTIFYICONDATA, UINT = 0);
	LPCTSTR GetNotifyTipText(PNOTIFYICONDATA);

	// Core functions:
	BOOL DoAction(UINT);
	void ViewConfiguration();
	BOOL LoadConfiguration();
	BOOL SaveConfiguration();
	void PreparePrivateProfileFile(std::ofstream*&);
	void WritePrivateProfileInt(std::ofstream*, std::string, UINT);
	void ClosePrivateProfileFile(std::ofstream*);
	BOOL BackupConfiguration();
	int AskBefore(UINT, UINT);
	int EnableAutoStart(BOOL);
	int IsAutoStartEnabled();
	void OnPanel();
};
