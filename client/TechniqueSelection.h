//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_TECHNIQUESELECTION_H__1613002E_7803_4D10_9FB7_73C15C864AE1__INCLUDED_)
#define AFX_TECHNIQUESELECTION_H__1613002E_7803_4D10_9FB7_73C15C864AE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TechniqueSelection.h : header file
//
#include "WindowState.h"
#include "ObjectSpace.h"
#include "Tech.h"
#include "TreeCtrlX.h"

/////////////////////////////////////////////////////////////////////////////
// CTechniqueSelection dialog

class CTechniqueSelection : public CDialog
{
// Construction
public:
	DrawCategoryList();
	ResizeResourceGrid();
	CString GetCategory();
	UpdateAutoExpandMenu();
	HTREEITEM SelectTech (CString &a_csTechName);
	DisplayTechTiers (CTech *a_cpTech);
	AddTitleLine(CString a_csName, int a_iStyle);
	AddSummaryLine(CString a_csName, int a_iStyle = 1);
	AddToResources(CItemResource *a_cpResource, int a_iStyle);

	DisableScreen();
	EnableScreen();

	DisplayTech(CTech *a_cpTech, CString &a_csTierName);
	DrawTechList();
	SelectCategory(CString a_csCategory);
	Initialise();
	StartUp();
	ResizeGrids();
	CTechniqueSelection(CWnd* pParent = NULL);   // standard constructor

	CWindowState m_cWindowState;
	CString m_csPreferedCategory;
	CString m_csPreferedTech;

	CObjectSpace m_cOS_TechFilter;
	CObjectSpace m_cOS_CategoriesText;
	CObjectSpace m_cOS_TechsText;
	CObjectSpace m_cOS_TechExpand;
	CObjectSpace m_cOS_TechCollapse;
	CObjectSpace m_cOS_AddTechButton;
	CObjectSpace m_cOS_TechComponentGrid;
	CObjectSpace m_cOS_TechGrid;
	CObjectSpace m_cOS_TechInfoGrid;
	CObjectSpace m_cOS_TechTierGrid;
	CObjectSpace m_cOS_FilterFormulas;
	CObjectSpace m_cOS_ShowUsable;
	CObjectSpace m_cOS_SizingBox;
	CObjectSpace m_cOS_SizingTitleBox;

	int m_iResourceListDelta;
	int m_iResourceListDeltaReverse;
	int m_iResourceListDeltaZero;

	int m_iTierListDelta;
	int m_iTierListDeltaReverse;
	int m_iTierListDeltaZero;

	int m_iCombinedDelta;

	bool m_bUpdating;
	bool m_bTechTreeExpand;
// Dialog Data
	//{{AFX_DATA(CTechniqueSelection)
	enum { IDD = IDD_TECHDIALOG };
	CStatic	m_cTechsText;
	CListCtrl	m_cFilterList;
	CButton	m_cExpandButton;
	CStatic	m_cCategoriesText;
	CButton	m_cCollapseButton;
	CButton	m_cFilterFormulas;
	CTreeCtrlX	m_cTechTree;
	CStatic	m_cTest;
	CButton	m_cShowUsable;
	CEdit	m_cSizingBox;
	CEdit	m_cSizingTitleBox;
	CButton	m_cAddTechButton;
	CMSFlexGrid	m_cTechComponentGrid;
	CMSFlexGrid	m_cTechInfoGrid;
	CMSFlexGrid	m_cTechTierGrid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTechniqueSelection)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTechniqueSelection)
	afx_msg void OnWindowPosChanging( WINDOWPOS* lpwndpos );
	afx_msg void OnGetMinMaxInfo (MINMAXINFO* lpMMI) ;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClickTechtiergrid();
	afx_msg void OnSelchangeTechfilter();
	afx_msg void OnShowusable();
	afx_msg void OnSelchangedTechtree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAddtech();
	afx_msg void OnFilterforms();
	afx_msg void OnItemexpandingTechtree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOptionsSnapshotwindow();
	afx_msg void OnOptionsRestorewindow();
	afx_msg void OnOptionsAutoexpandOff();
	afx_msg void OnOptionsAutoexpandCurrentcategory();
	afx_msg void OnOptionsAutoexpandAllcategories();
	afx_msg void OnCollapse();
	afx_msg void OnHelpIndex();
	afx_msg void OnClickFilterlist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownFilterlist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnExpand();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnWindowAlwaysontop();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TECHNIQUESELECTION_H__1613002E_7803_4D10_9FB7_73C15C864AE1__INCLUDED_)
