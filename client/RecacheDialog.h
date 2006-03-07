#if !defined(AFX_RECACHEDIALOG_H__A2945FF1_D052_4125_992C_31030D156673__INCLUDED_)
#define AFX_RECACHEDIALOG_H__A2945FF1_D052_4125_992C_31030D156673__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RecacheDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRecacheDialog dialog

class CRecacheDialog : public CDialog
{
// Construction
public:
	int CalculateFilesToCache(CString &a_csPath);
	Recache(bool a_bQuiet);
	CRecacheDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRecacheDialog)
	enum { IDD = IDD_CACHEDIALOG };
	CProgressCtrl	m_cStatusProgress;
	//}}AFX_DATA

	bool m_bInProgress;
	int m_iTimerId;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecacheDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRecacheDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECACHEDIALOG_H__A2945FF1_D052_4125_992C_31030D156673__INCLUDED_)
