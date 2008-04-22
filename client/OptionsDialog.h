#if !defined(AFX_OPTIONSDIALOG_H__3B362DBC_DA67_4690_8730_B4AE1633BBDD__INCLUDED_)
#define AFX_OPTIONSDIALOG_H__3B362DBC_DA67_4690_8730_B4AE1633BBDD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptionsDialog dialog

class COptionsDialog : public CDialog
{
// Construction
public:
	Initialise();
	COptionsDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COptionsDialog)
	enum { IDD = IDD_OPTIONS };
	CButton	m_cPriorityCheck;
	CButton	m_cAutoUpdateCheck;
	CComboBox	m_cThemeCombo;
	CButton	m_cToolbarCheck;
	CComboBox	m_cDockingCombo;
	CButton	m_cHotKeyCheck;
	CComboBox	m_cIconSizeCombo;
	CButton	m_cIconCheck;
	CEdit	m_cGameDir;
	CButton	m_cCacheCheck;
	CButton	m_cBrowseButton;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptionsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBrowsebutton();
	afx_msg void OnHelpIndex();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSDIALOG_H__3B362DBC_DA67_4690_8730_B4AE1633BBDD__INCLUDED_)
