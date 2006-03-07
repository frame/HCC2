#if !defined(AFX_PROFILEPAGE3_H__1A49024B_7DD1_4835_8150_4A5E1B3AC426__INCLUDED_)
#define AFX_PROFILEPAGE3_H__1A49024B_7DD1_4835_8150_4A5E1B3AC426__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProfilePage3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProfilePage3 dialog

class CProfilePage3 : public CPropertyPage
{
	DECLARE_DYNCREATE(CProfilePage3)

// Construction
public:
	void DisplayProfile();
	DisplayAdventureSkills();
	DisplayAdventureSchools();
	CProfilePage3();
	~CProfilePage3();

// Dialog Data
	//{{AFX_DATA(CProfilePage3)
	enum { IDD = IDD_PROFILE3DIALOG };
	CButton	m_cOptSkills;
	CButton	m_cOptSchools;
	CListCtrl	m_cAdventureList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CProfilePage3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CProfilePage3)
	afx_msg void OnOptschools();
	afx_msg void OnOptskills();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROFILEPAGE3_H__1A49024B_7DD1_4835_8150_4A5E1B3AC426__INCLUDED_)
