#if !defined(AFX_WIZARDPAGE3_H__8B1E5635_5FF3_4CE6_BB28_0985D12D4949__INCLUDED_)
#define AFX_WIZARDPAGE3_H__8B1E5635_5FF3_4CE6_BB28_0985D12D4949__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WizardPage3.h : header file
//

#include "WizardPage1.h"
#include "WizardDialog.h"
#include "treectrlx.h"

/////////////////////////////////////////////////////////////////////////////
// CWizardPage3 dialog

class CWizardPage3 : public CPropertyPage
{
	DECLARE_DYNCREATE(CWizardPage3)

// Construction
public:
	UpdateTechs();
	CWizardPage3();
	~CWizardPage3();

// Dialog Data
	//{{AFX_DATA(CWizardPage3)
	enum { IDD = IDD_WIZARDPAGE3 };
	CStatic	m_cDesc;
	CTreeCtrlX	m_cTechTree;
	CStatic	m_cInfo;
	//}}AFX_DATA

	CWizardPage1 *m_cpWizardDialog1;
	CWizardDialog *m_cpWizardDialog;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CWizardPage3)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CWizardPage3)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangedTechtree(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZARDPAGE3_H__8B1E5635_5FF3_4CE6_BB28_0985D12D4949__INCLUDED_)
