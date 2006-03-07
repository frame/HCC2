//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_PROFILEPAGE1_H__DF25E221_7C6D_4520_BF0B_8241A1ECD09D__INCLUDED_)
#define AFX_PROFILEPAGE1_H__DF25E221_7C6D_4520_BF0B_8241A1ECD09D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProfilePage1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProfilePage1 dialog

class CProfilePage1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CProfilePage1)

// Construction
public:
	CProfilePage1();
	~CProfilePage1();

// Dialog Data
	//{{AFX_DATA(CProfilePage1)
	enum { IDD = IDD_PROFILE1DIALOG };
	CListCtrl	m_cStatistcsList;
	CComboBox	m_cProfileServerCombo;
	CEdit	m_cProfileEmail;
	CEdit	m_cProfileName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CProfilePage1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CProfilePage1)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkStatisticslist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeName();
	afx_msg void OnSelchangeServercombo();
	afx_msg void OnChangeEmail();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROFILEPAGE1_H__DF25E221_7C6D_4520_BF0B_8241A1ECD09D__INCLUDED_)
