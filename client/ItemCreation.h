//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_ITEMCREATION_H__680D3960_8175_4B78_BE1C_1BE5EA95BDF7__INCLUDED_)
#define AFX_ITEMCREATION_H__680D3960_8175_4B78_BE1C_1BE5EA95BDF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ItemCreation.h : header file
//
#include "WindowState.h"
#include "Formula.h"
#include "ObjectSpace.h"
#include "OrderItem.h"
#include "TreeCtrlX.h"

/////////////////////////////////////////////////////////////////////////////
// CItemCreation dialog

class CItemCreation : public CDialog
{
// Construction
public:
	DrawCategoryList();
	FilterEffectList(CTypedPtrList<CPtrList, CEffect*> &a_clEffectsList,
										  int &a_iClassPermitted,
										  int &a_iSchoolPermitted,
										  int &a_iRacePermitted);
	ResetItemEdit();
	void AdjustTechUsage ();
	void ModifyLine (CString a_csLineName, CString a_csAttributeType, CString a_csModifier);
	void DisplayTechBonuses ();
	void DisplayTechEffects ();
	EndEditCell (bool a_bSuccess);
	StartEditCell();
	SelectCurrentFormula (HTREEITEM l_TreeItem);
	CString GetCategory();
	UpdateAutoExpandMenu();
	UpdateResourceBreakdownMenu();
	UpdateResourceGridMenu();
	DisplayProfiles();
	DisplayItems();
	RedrawOff ();
	RedrawOn();
	AddSubFormula (HTREEITEM a_cTreeItem, CFormulaTier *a_cpParentFormulaTier, CString &a_csParentTierName);
	AddTemporaryFormulas ();
	ResizeResourceGrid ();
	ResetCurrentFormula ();
	SelectFormula (COrderItem l_cOrderItem);
	AddTechResources ();
	DisplayFormulaTechs ();
	DisplayFormulaTiers ();
	ResizeGrids();
	CString GetSummaryData(CString a_csType, CString a_csLine, int a_iOffset);

	AddComponents(CItemResource *a_cpResource, int a_iStyle);
	AddToResources(CItemResource *a_cpResource, int a_iStyle, int a_iBaseQty = 1, int a_iSkillAdjust = 0);
	AddBaseResources(CItemResource *a_cpResource, int a_iStyle, int a_iBaseQty = 1, int a_iSkillAdjust = 0);
	AddTitleLine(CString a_csName, int a_iStyle);
	AddSummaryLine(CString a_csName, int a_iStyle = 1);

	afx_msg void OnSearchByname();
	afx_msg void OnSearchByFormname();
	afx_msg void OnSearchByclass();

	EnableScreen ();
	DisableScreen ();
	DisplayFormula (bool a_bUpdateTechList);
	Initialise();
	SelectCategory (CString a_csCategory);
	StartUp();
	DrawFormulaList();
	CItemCreation(CWnd* pParent = NULL);   // standard constructor

	CWindowState m_cWindowState;

	CObjectSpace m_cOS_FormulaFilter;
	CObjectSpace m_cOS_CategoriesText;
	CObjectSpace m_cOS_FormulasText;
	CObjectSpace m_cOS_FormulaExpand;
	CObjectSpace m_cOS_FormulaCollapse;
	CObjectSpace m_cOS_InfoGrid;
	CObjectSpace m_cOS_FormulaTree;
	CObjectSpace m_cOS_TierGrid;
	CObjectSpace m_cOS_TechGrid;
	CObjectSpace m_cOS_AddItemButton;
	CObjectSpace m_cOS_RemoveTechButton;
	CObjectSpace m_cOS_ResourceGrid;
	CObjectSpace m_cOS_ShowLevels;
	CObjectSpace m_cOS_ProfileSelecter;
	CObjectSpace m_cOS_ProfileText;
	CObjectSpace m_cOS_ItemSelecter;
	CObjectSpace m_cOS_ItemText;
	CObjectSpace m_cOS_SizingBox;
	CObjectSpace m_cOS_SizingTitleBox;

	bool m_bFormulaTreeExpand;
	bool m_bDisplayFormula;
	int m_iResourceListDelta;
	int m_iResourceListDeltaReverse;
	int m_iResourceListDeltaZero;

	int m_iTierListDelta;
	int m_iTierListDeltaReverse;
	int m_iTierListDeltaZero;

	int m_iCombinedDelta;

	int m_iResourceGridEditRow;
	int m_iResourceGridEditCol;

	HTREEITEM m_PrevFormulaTree;
	CString	m_csPrevFormulaName;
	CString	m_csPrevFormulaTierName;

	int RedrawCount;

	bool m_bResize;
	// Dialog Data
	//{{AFX_DATA(CItemCreation)
	enum { IDD = IDD_ITEMDIALOG };
	CStatic	m_cItemText;
	CComboBox	m_cItemSelecter;
	CEdit	m_cSkillEdit;
	CButton	m_cExpandButton;
	CListCtrl	m_cFilterList;
	CStatic	m_cFormulasText;
	CStatic	m_cCategoriesText;
	CButton	m_cCollapseButton;
	CStatic	m_cProfileText;
	CComboBox	m_cProfileSelecter;
	CButton	m_cShowLevels;
	CEdit	m_cSizingTitleBox;
	CEdit	m_cSizingBox;
	CButton	m_cRemoveTechButton;
	CButton	m_cAddItemButton;
	CTreeCtrlX	m_cFormulaTree;
	CMSFlexGrid	m_cItemInfoGrid;
	CMSFlexGrid	m_cResourceGrid;
	CMSFlexGrid	m_cTechGrid;
	CMSFlexGrid	m_cTierGrid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CItemCreation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CItemCreation)
	afx_msg void OnWindowPosChanging( WINDOWPOS* lpwndpos );
	afx_msg void OnGetMinMaxInfo (MINMAXINFO* lpMMI) ;
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	virtual void OnCancel();
	afx_msg void OnSelchangedFormulatree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRowColChangeTiergrid();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClickTiergrid();
	afx_msg void OnAdditem();
	afx_msg void OnItemexpandingFormulatree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRemovetech();
	afx_msg void OnOptionsSnapshotwindow();
	afx_msg void OnOptionsRestorewindow();
	afx_msg void OnShowlevels();
	virtual void OnOK();
	afx_msg void OnPaint();
	afx_msg void OnSelchangeProfileselecter();
	afx_msg void OnOptionsResourcebreakdownShowformularesource();
	afx_msg void OnOptionsShowsubcomponents();
	afx_msg void OnOptionsShowbaseresource();
	afx_msg void OnOptionsAutoexpandOff();
	afx_msg void OnOptionsAutoexpandCurrentcategory();
	afx_msg void OnOptionsAutoexpandAllcategories();
	afx_msg void OnCollapse();
	afx_msg void OnClickFilterlist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownFilterlist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHelpHelp();
	afx_msg void OnExpand();
	afx_msg void OnDblClickResourcegrid();
	afx_msg void OnScrollResourcegrid();
	afx_msg void OnKillfocusSkilledit();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSelchangeItemselecter();
	afx_msg void OnWindowAlwaysontop();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnOptionsResourcegridLimitto4rows();
	afx_msg void OnOptionsResourcegridLimitto8rows();
	afx_msg void OnOptionsResourcegridLimitto12rows();
	afx_msg void OnOptionsResourcegridUnlimited();


	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnOptionsResourcegridAutoshrink();
	afx_msg void OnClickFormulatree(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ITEMCREATION_H__680D3960_8175_4B78_BE1C_1BE5EA95BDF7__INCLUDED_)
