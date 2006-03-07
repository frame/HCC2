#if !defined(AFX_NEWPROFILEDIALOG_H__1F4F0FB8_6085_43C9_932B_B908750D86E7__INCLUDED_)
#define AFX_NEWPROFILEDIALOG_H__1F4F0FB8_6085_43C9_932B_B908750D86E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewProfileDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewProfileDialog dialog

class CNewProfileDialog : public CDialog
{
// Construction
public:
	CNewProfileDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewProfileDialog)
	enum { IDD = IDD_NEWPROFILEDIALOG };
	CComboBox	m_cServerCombo;
	CEdit	m_cName;
	CRect m_cRect;
	//}}AFX_DATA

	CString m_csName;
	CString m_csServer;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewProfileDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewProfileDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWPROFILEDIALOG_H__1F4F0FB8_6085_43C9_932B_B908750D86E7__INCLUDED_)
