#if !defined(AFX_CRAFTERSEARCHDIALOG_H__A6AE89A6_CD42_4728_86EE_D728E09027C7__INCLUDED_)
#define AFX_CRAFTERSEARCHDIALOG_H__A6AE89A6_CD42_4728_86EE_D728E09027C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CrafterSearchDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCrafterSearchDialog dialog

class CCrafterSearchDialog : public CDialog
{
// Construction
public:
	CCrafterSearchDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCrafterSearchDialog)
	enum { IDD = IDD_CRAFTERSEARCHDIALOG };
	CButton	m_cViewProfileButton;
	CButton	m_cSubmitRequestButton;
	CComboBox	m_cShardCombo;
	CListCtrl	m_cSearchList;
	CButton	m_cSearchFrame;
	CButton	m_cSearchButton;
	CComboBox	m_cNameCombo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCrafterSearchDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCrafterSearchDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRAFTERSEARCHDIALOG_H__A6AE89A6_CD42_4728_86EE_D728E09027C7__INCLUDED_)
