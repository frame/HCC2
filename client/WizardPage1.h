#if !defined(AFX_WIZARDPAGE1_H__13A038F7_D7F5_431F_A21A_F61E43391505__INCLUDED_)
#define AFX_WIZARDPAGE1_H__13A038F7_D7F5_431F_A21A_F61E43391505__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WizardPage1.h : header file
//
#include "Profile.h"
#include "WizardDialog.h"
#include "SchoolWizard.h"

/////////////////////////////////////////////////////////////////////////////
// CWizardPage1 dialog

class CWizardPage1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CWizardPage1)

// Construction
public:
	CWizardPage1();
	~CWizardPage1();

// Dialog Data
	//{{AFX_DATA(CWizardPage1)
	enum { IDD = IDD_WIZARDPAGE1 };
	CButton	m_cOptProfile;
	CButton	m_cOptManual;
	CComboBox	m_cSchoolTypeCombo;
	CComboBox	m_cSchoolNameCombo;
	CSpinButtonCtrl	m_cSchoolLevelSpin;
	CEdit	m_cSchoolLevel;
	CComboBox	m_cRaceCombo;
	CComboBox	m_cProfileSchoolCombo;
	CListCtrl	m_cProfileList;
	CStatic	m_cInfo;
	//}}AFX_DATA

	CString m_csRace;
	int m_iLevel;
	CProfile *m_cpProfile;
	CSchoolWizard *m_cpSchoolWizard;
	CWizardDialog *m_cpWizardDialog;

	UpdateWizard();
	UpdateClassTypes();
	UpdateClassChoices();
	UpdateProfileClassChoices();
	SetChosenWizard();

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CWizardPage1)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CWizardPage1)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeRacecombo();
	afx_msg void OnSelchangeSchooltypecombo();
	afx_msg void OnSelchangeSchoolnamecombo();
	afx_msg void OnClickProfilelist(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZARDPAGE1_H__13A038F7_D7F5_431F_A21A_F61E43391505__INCLUDED_)
