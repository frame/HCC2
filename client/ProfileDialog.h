#if !defined(AFX_PROFILEDIALOG_H__2F7F46D5_3AB1_47E1_81FA_ACCDD46669FD__INCLUDED_)
#define AFX_PROFILEDIALOG_H__2F7F46D5_3AB1_47E1_81FA_ACCDD46669FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProfileDialog.h : header file
//
#include "WindowState.h"
#include "ObjectSpace.h"
#include "TreeCtrlX.h"
#include "ProfilePage1.h"
#include "ProfilePage2.h"
#include "ProfilePage3.h"

/////////////////////////////////////////////////////////////////////////////
// CProfileDialog dialog

class CProfileDialog : public CDialog
{
// Construction
public:
	CString GetProfileName (CString &a_csProfileText);
	SelectProfile (CString &a_csProfileName);
	DisplayProfile();
	CProfileDialog(CWnd* pParent = NULL);   // standard constructor

	CObjectSpace m_cOS_ProfileTree;
	CObjectSpace m_cOS_ProfileTab;
	CWindowState m_cWindowState;

	DrawProfileTree();
	Initialise();
	StartUp();
	ResizeGrids();
// Dialog Data
	//{{AFX_DATA(CProfileDialog)
	enum { IDD = IDD_PROFILEDIALOG };
	CButton	m_cCopyButton;
	CButton	m_cNewButton;
	CButton	m_cDeleteButton;
	CButton	m_cUpdateButton;
	CTreeCtrlX	m_cProfileTree;
	CProfilePage1	m_cProfilePage1;
	CProfilePage2	m_cProfilePage2;
	CProfilePage3	m_cProfilePage3;
	CPropertySheet m_ProfileSheet;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProfileDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProfileDialog)
	afx_msg void OnWindowPosChanging( WINDOWPOS* lpwndpos );
	afx_msg void OnGetMinMaxInfo (MINMAXINFO* lpMMI) ;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangedProfiletree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClose();
	virtual void OnOK();
	afx_msg void OnWindowSnapshotwindow();
	afx_msg void OnWindowRestorewindow();
	afx_msg void OnHelpIndex();
	afx_msg void OnUpdate();
	afx_msg void OnNewbutton();
	afx_msg void OnCopybutton();
	afx_msg void OnDeletebutton();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnWindowAlwaysontop();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROFILEDIALOG_H__2F7F46D5_3AB1_47E1_81FA_ACCDD46669FD__INCLUDED_)
