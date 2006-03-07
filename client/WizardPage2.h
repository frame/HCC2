#if !defined(AFX_WIZARDPAGE2_H__1A336654_8DE3_4A94_BE7A_E5920680CA17__INCLUDED_)
#define AFX_WIZARDPAGE2_H__1A336654_8DE3_4A94_BE7A_E5920680CA17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WizardPage2.h : header file
//

#include "WizardPage1.h"
#include "WizardDialog.h"
#include "treectrlx.h"

/////////////////////////////////////////////////////////////////////////////
// CWizardPage2 dialog

class CWizardPage2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CWizardPage2)

// Construction
public:
	CWizardPage2();
	~CWizardPage2();

// Dialog Data
	//{{AFX_DATA(CWizardPage2)
	enum { IDD = IDD_WIZARDPAGE2 };
	CStatic	m_cDesc;
	CStatic	m_cInfo;
	CTreeCtrlX	m_cCategoryTree;
	//}}AFX_DATA
	CWizardPage1 *m_cpWizardDialog1;
	CWizardDialog *m_cpWizardDialog;

	UpdateCategories();
// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CWizardPage2)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CWizardPage2)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangedCategorytree(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZARDPAGE2_H__1A336654_8DE3_4A94_BE7A_E5920680CA17__INCLUDED_)
