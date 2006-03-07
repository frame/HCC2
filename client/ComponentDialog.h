//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_COMPONENTDIALOG_H__1DDCC8DC_EE4F_44BD_9F6B_C6A6A32DFE5E__INCLUDED_)
#define AFX_COMPONENTDIALOG_H__1DDCC8DC_EE4F_44BD_9F6B_C6A6A32DFE5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComponentDialog.h : header file
//
#include "WindowState.h"
#include "ObjectSpace.h"
#include "TreeCtrlX.h"
#include "Component.h"

/////////////////////////////////////////////////////////////////////////////
// CComponentDialog dialog

class CComponentDialog : public CDialog
{
// Construction
public:
	DisplayComponent ();
	DisplayComponentTypes ();
	DrawCompTree ();
	CComponentDialog(CWnd* pParent = NULL);   // standard constructor
	AddTitleLine(CString a_csName, int a_iStyle);
	AddSummaryLine(CString a_csName, int a_iStyle = 1);


	CObjectSpace m_cOS_ComponentTree;
	CObjectSpace m_cOS_ComponentGrid;
	CObjectSpace m_cOS_SizingBox;
	CObjectSpace m_cOS_SizingTitleBox;
	CWindowState m_cWindowState;

	Initialise();
	StartUp();
	void OnClose();

	bool l_bUpdating;

// Dialog Data
	//{{AFX_DATA(CComponentDialog)
	enum { IDD = IDD_COMPONENTDIALOG };
	CComboBox	m_cTierFilter;
	CEdit	m_cSizingTitleBox;
	CEdit	m_cSizingBox;
	CTreeCtrlX	m_cCompTree;
	CComboBox	m_cCompFilter;
	CMSFlexGrid	m_cResourceGrid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComponentDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CComponentDialog)
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	afx_msg void OnWindowPosChanging( WINDOWPOS* lpwndpos );
	afx_msg void OnGetMinMaxInfo (MINMAXINFO* lpMMI) ;
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCompfilter();
	afx_msg void OnSelchangedComptree(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	afx_msg void OnOptionsSnapshotwindow();
	afx_msg void OnOptionsRestorewindow();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHelpIndex();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnWindowAlwaysontop();
	afx_msg void OnSelchangeTierfilter();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPONENTDIALOG_H__1DDCC8DC_EE4F_44BD_9F6B_C6A6A32DFE5E__INCLUDED_)
