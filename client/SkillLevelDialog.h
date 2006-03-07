//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_SKILLLEVELDIALOG_H__4FCDD736_418B_421B_B3CF_5F1F107B99D1__INCLUDED_)
#define AFX_SKILLLEVELDIALOG_H__4FCDD736_418B_421B_B3CF_5F1F107B99D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SkillLevelDialog.h : header file
//
#include "WindowState.h"
#include "ItemResource.h"

/////////////////////////////////////////////////////////////////////////////
// CSkillLevelDialog dialog

class CSkillLevelDialog : public CDialog
{
// Construction
public:
	DisplaySkillLevels ();
	CSkillLevelDialog(CWnd* pParent = NULL);   // standard constructor

	void OnClose();
	void OnCancel();
	StartUp();
	CWindowState m_cWindowState;
// Dialog Data
	//{{AFX_DATA(CSkillLevelDialog)
	enum { IDD = IDD_LEVELDIALOG };
	CEdit	m_cSkillName;
	CListBox	m_cResourceList;
	CMSFlexGrid	m_cSkillGrid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkillLevelDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSkillLevelDialog)
	afx_msg void OnSelchangeResourcelist();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKILLLEVELDIALOG_H__4FCDD736_418B_421B_B3CF_5F1F107B99D1__INCLUDED_)
