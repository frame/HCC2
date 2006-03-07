#if !defined(AFX_INPUTDIALOG_H__2FB37703_0D32_4116_BB22_59E2BA95BEB2__INCLUDED_)
#define AFX_INPUTDIALOG_H__2FB37703_0D32_4116_BB22_59E2BA95BEB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInputDialog dialog

class CInputDialog : public CDialog
{
// Construction
public:
	CInputDialog(CWnd* pParent = NULL);   // standard constructor
	CString m_csInput;
	CString m_csInputMsg;
	CString m_csTitleMsg;

// Dialog Data
	//{{AFX_DATA(CInputDialog)
	enum { IDD = IDD_INPUTDIALOG };
	CStatic	m_cInputMsg;
	CEdit	m_cInputEdit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInputDialog)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInputDialog)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTDIALOG_H__2FB37703_0D32_4116_BB22_59E2BA95BEB2__INCLUDED_)
