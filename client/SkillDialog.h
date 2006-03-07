#if !defined(AFX_SKILLDIALOG_H__5D63803A_F901_469C_90F3_B37E28F0C20D__INCLUDED_)
#define AFX_SKILLDIALOG_H__5D63803A_F901_469C_90F3_B37E28F0C20D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SkillDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSkillDialog dialog

class CSkillDialog : public CDialog
{
// Construction
public:
	CSkillDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSkillDialog)
	enum { IDD = IDD_SKILLDIALOG };
	CStatic	m_cInputMsg;
	CEdit	m_cInputEdit;
	CRect m_cRect;
	//}}AFX_DATA

	CString m_csMsg;
	CString m_csValue;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkillDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSkillDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKILLDIALOG_H__5D63803A_F901_469C_90F3_B37E28F0C20D__INCLUDED_)
