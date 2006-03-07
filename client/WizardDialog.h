#if !defined(AFX_WIZARDDIALOG_H__393BD226_9396_4BAA_8611_439A107612D1__INCLUDED_)
#define AFX_WIZARDDIALOG_H__393BD226_9396_4BAA_8611_439A107612D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WizardDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWizardDialog

class CWizardDialog : public CPropertySheet
{
	DECLARE_DYNAMIC(CWizardDialog)

// Construction
public:
	CWizardDialog(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CWizardDialog(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWizardDialog)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWizardDialog();

	// Generated message map functions
protected:
	//{{AFX_MSG(CWizardDialog)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZARDDIALOG_H__393BD226_9396_4BAA_8611_439A107612D1__INCLUDED_)
