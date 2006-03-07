#if !defined(AFX_PROFILEPAGE2_H__5E8CCFAA_B239_42C1_96A5_6D7C0AA8F779__INCLUDED_)
#define AFX_PROFILEPAGE2_H__5E8CCFAA_B239_42C1_96A5_6D7C0AA8F779__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProfilePage2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProfilePage2 dialog

class CProfilePage2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CProfilePage2)

// Construction
public:
	void DisplayProfile();
	DisplayCraftSkills();
	DisplayCraftSchools();
	CProfilePage2();
	~CProfilePage2();

// Dialog Data
	//{{AFX_DATA(CProfilePage2)
	enum { IDD = IDD_PROFILE2DIALOG };
	CButton	m_cOptSkills;
	CButton	m_cOptSchools;
	CListCtrl	m_cCraftList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CProfilePage2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CProfilePage2)
	afx_msg void OnOptschools();
	afx_msg void OnOptskills();
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkCraftlist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	bool m_bLoaded;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROFILEPAGE2_H__5E8CCFAA_B239_42C1_96A5_6D7C0AA8F779__INCLUDED_)
