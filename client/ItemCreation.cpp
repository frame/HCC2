// ItemCreation.cpp : implementation file
//

#include "stdafx.h"
#include "HCC.h"
#include "ItemCreation.h"
#include "AppData.h"
#include "FormulaTier.h"
#include "Formula.h"
#include "FormulaSet.h"
#include "InputDialog.h"
#include "InputListDialog.h"
#include "Scheme.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define cInfoGridIndent 1150

/////////////////////////////////////////////////////////////////////////////
// CItemCreation dialog


CItemCreation::CItemCreation(CWnd* pParent /*=NULL*/)
	: CDialog(CItemCreation::IDD, pParent)
{
	//{{AFX_DATA_INIT(CItemCreation)
	//}}AFX_DATA_INIT
	RedrawCount = 0;
}


void CItemCreation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CItemCreation)
	DDX_Control(pDX, IDC_ITEMTEXT, m_cItemText);
	DDX_Control(pDX, IDC_ITEMSELECTER, m_cItemSelecter);
	DDX_Control(pDX, IDC_SKILLEDIT, m_cSkillEdit);
	DDX_Control(pDX, IDC_EXPAND, m_cExpandButton);
	DDX_Control(pDX, IDC_FILTERLIST, m_cFilterList);
	DDX_Control(pDX, IDC_FORMULASTEXT, m_cFormulasText);
	DDX_Control(pDX, IDC_CATEGORIESTEXT, m_cCategoriesText);
	DDX_Control(pDX, IDC_COLLAPSE, m_cCollapseButton);
	DDX_Control(pDX, IDC_PROFILETEXT, m_cProfileText);
	DDX_Control(pDX, IDC_PROFILESELECTER, m_cProfileSelecter);
	DDX_Control(pDX, IDC_SHOWLEVELS, m_cShowLevels);
	DDX_Control(pDX, IDC_SIZINGTITLEBOX, m_cSizingTitleBox);
	DDX_Control(pDX, IDC_SIZINGBOX, m_cSizingBox);
	DDX_Control(pDX, IDC_REMOVETECH, m_cRemoveTechButton);
	DDX_Control(pDX, IDC_ADDITEM, m_cAddItemButton);
	DDX_Control(pDX, IDC_FORMULATREE, m_cFormulaTree);
	DDX_Control(pDX, IDC_ITEMINFOGRID, m_cItemInfoGrid);
	DDX_Control(pDX, IDC_RESOURCEGRID, m_cResourceGrid);
	DDX_Control(pDX, IDC_TECHGRID, m_cTechGrid);
	DDX_Control(pDX, IDC_TIERGRID, m_cTierGrid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CItemCreation, CDialog)
	//{{AFX_MSG_MAP(CItemCreation)
	ON_WM_WINDOWPOSCHANGING ()
	ON_WM_GETMINMAXINFO()
	ON_WM_CLOSE()
	ON_NOTIFY(TVN_SELCHANGED, IDC_FORMULATREE, OnSelchangedFormulatree)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_ADDITEM, OnAdditem)
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_FORMULATREE, OnItemexpandingFormulatree)
	ON_BN_CLICKED(IDC_REMOVETECH, OnRemovetech)
	ON_COMMAND(ID_OPTIONS_SNAPSHOTWINDOW, OnOptionsSnapshotwindow)
	ON_COMMAND(ID_OPTIONS_RESTOREWINDOW, OnOptionsRestorewindow)
	ON_BN_CLICKED(IDC_SHOWLEVELS, OnShowlevels)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_PROFILESELECTER, OnSelchangeProfileselecter)
	ON_COMMAND(ID_OPTIONS_RESOURCEBREAKDOWN_SHOWFORMULARESOURCE, OnOptionsResourcebreakdownShowformularesource)
	ON_COMMAND(ID_OPTIONS_SHOWSUBCOMPONENTS, OnOptionsShowsubcomponents)
	ON_COMMAND(ID_OPTIONS_SHOWBASERESOURCE, OnOptionsShowbaseresource)
	ON_COMMAND(ID_OPTIONS_AUTOEXPAND_OFF, OnOptionsAutoexpandOff)
	ON_COMMAND(ID_OPTIONS_AUTOEXPAND_CURRENTCATEGORY, OnOptionsAutoexpandCurrentcategory)
	ON_COMMAND(ID_OPTIONS_AUTOEXPAND_ALLCATEGORIES, OnOptionsAutoexpandAllcategories)
	ON_BN_CLICKED(IDC_COLLAPSE, OnCollapse)
	ON_NOTIFY(NM_CLICK, IDC_FILTERLIST, OnClickFilterlist)
	ON_NOTIFY(LVN_KEYDOWN, IDC_FILTERLIST, OnKeydownFilterlist)
	ON_COMMAND(ID_HELP_HELP, OnHelpHelp)
	ON_BN_CLICKED(IDC_EXPAND, OnExpand)
	ON_EN_KILLFOCUS(IDC_SKILLEDIT, OnKillfocusSkilledit)
	ON_WM_MOVE()
	ON_CBN_SELCHANGE(IDC_ITEMSELECTER, OnSelchangeItemselecter)
	ON_COMMAND(ID_WINDOW_ALWAYSONTOP, OnWindowAlwaysontop)
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_OPTIONS_RESOURCEGRID_LIMITTO4ROWS, OnOptionsResourcegridLimitto4rows)
	ON_COMMAND(ID_OPTIONS_RESOURCEGRID_LIMITTO8ROWS, OnOptionsResourcegridLimitto8rows)
	ON_COMMAND(ID_OPTIONS_RESOURCEGRID_LIMITTO12ROWS, OnOptionsResourcegridLimitto12rows)
	ON_COMMAND(ID_OPTIONS_RESOURCEGRID_UNLIMITED, OnOptionsResourcegridUnlimited)
	ON_COMMAND(ID_SEARCH_BYNAME, OnSearchByname)
	ON_COMMAND(ID_SEARCH_BYFORMNAME, OnSearchByFormname)
	ON_COMMAND(ID_SEARCH_BYCLASS, OnSearchByclass)
	ON_WM_HELPINFO()
	ON_COMMAND(ID_OPTIONS_RESOURCEGRID_AUTOSHRINK, OnOptionsResourcegridAutoshrink)
	ON_WM_KEYUP()
	ON_WM_CHAR()
	ON_NOTIFY(NM_CLICK, IDC_FORMULATREE, OnClickFormulatree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CItemCreation, CDialog)
    //{{AFX_EVENTSINK_MAP(CItemCreation)
	ON_EVENT(CItemCreation, IDC_TIERGRID, 70 /* RowColChange */, OnRowColChangeTiergrid, VTS_NONE)
	ON_EVENT(CItemCreation, IDC_TIERGRID, -600 /* Click */, OnClickTiergrid, VTS_NONE)
	ON_EVENT(CItemCreation, IDC_RESOURCEGRID, -601 /* DblClick */, OnDblClickResourcegrid, VTS_NONE)
	ON_EVENT(CItemCreation, IDC_RESOURCEGRID, 73 /* Scroll */, OnScrollResourcegrid, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


/////////////////////////////////////////////////////////////////////////////
// CItemCreation message handlers

BOOL CItemCreation::OnInitDialog()
{
	CDialog::OnInitDialog();

   //remove some options from the system menu
   CMenu* pSysMenu = GetSystemMenu(FALSE);
   pSysMenu->RemoveMenu(SC_RESTORE,MF_BYCOMMAND);
   pSysMenu->RemoveMenu(SC_MINIMIZE,MF_BYCOMMAND);
   pSysMenu->RemoveMenu(SC_MAXIMIZE,MF_BYCOMMAND);
   pSysMenu->RemoveMenu(SC_TASKLIST ,MF_BYCOMMAND);

	m_bResize = false;
	m_iResourceListDelta = 0;
	m_cOS_CategoriesText.InitState	(m_cCategoriesText,		*this, NULL,						NULL,						1.0f, 0.0f, NULL);
	m_cOS_FormulaFilter.InitState		(m_cFilterList,			*this, NULL,						NULL,						1.0f, 0.0f, NULL);
	m_cOS_FormulasText.InitState		(m_cFormulasText,			*this, NULL,						NULL,						0.4f, 0.0f, NULL);
	m_cOS_FormulaExpand.InitState		(m_cExpandButton,			*this, &m_cOS_FormulasText,	NULL,						0.0f, 0.0f, NULL);
	m_cOS_FormulaCollapse.InitState	(m_cCollapseButton,		*this, NULL,						NULL,						0.0f, 0.0f, NULL);
	m_cOS_FormulaTree.InitState		(m_cFormulaTree,			*this, NULL,						NULL,						0.4f, 1.0f, &m_iResourceListDelta);
	m_cOS_InfoGrid.InitState			(m_cItemInfoGrid,			*this, &m_cOS_FormulaTree,		NULL,						0.6f, 1.0f, &m_iCombinedDelta);
	m_cOS_TierGrid.InitState			(m_cTierGrid,				*this, &m_cOS_FormulaTree,		&m_cOS_InfoGrid,		0.0f, 0.0f, &m_iTierListDeltaReverse);
	m_cOS_TechGrid.InitState			(m_cTechGrid,				*this, &m_cOS_TierGrid,			&m_cOS_InfoGrid,		0.6f, 0.0f, &m_iTierListDeltaReverse);
	m_cOS_RemoveTechButton.InitState (m_cRemoveTechButton,	*this, &m_cOS_TierGrid,			&m_cOS_TechGrid,		0.6f, 0.0f, &m_iTierListDeltaZero);
	m_cOS_ResourceGrid.InitState		(m_cResourceGrid,			*this, NULL,						&m_cOS_FormulaTree,	1.0f, 0.0f, &m_iResourceListDeltaReverse);
	m_cOS_AddItemButton.InitState		(m_cAddItemButton,		*this, &m_cOS_RemoveTechButton,	&m_cOS_ResourceGrid,	0.0f, 0.0f, &m_iResourceListDeltaZero);
	m_cOS_ShowLevels.InitState			(m_cShowLevels,			*this, NULL,						&m_cOS_ResourceGrid,	0.0f, 0.0f, &m_iResourceListDeltaZero);
	m_cOS_ItemSelecter.InitState	(m_cItemSelecter,		*this, NULL,						&m_cOS_FormulaTree,	0.4f, 0.0f, &m_iResourceListDeltaZero);
	m_cOS_ItemText.InitState		(m_cItemText,			*this, NULL,						&m_cOS_FormulaTree,	0.0f, 0.0f, &m_iResourceListDeltaZero);
	m_cOS_ProfileSelecter.InitState		(m_cProfileSelecter,			*this, &m_cOS_TierGrid,			&m_cOS_FormulaTree,	0.6f, 0.0f, &m_iResourceListDeltaZero);
	m_cOS_ProfileText.InitState			(m_cProfileText,				*this, &m_cOS_TierGrid,			&m_cOS_FormulaTree,	0.0f, 0.0f, &m_iResourceListDeltaZero);
	m_cOS_SizingBox.InitState			(m_cSizingBox,				*this, &m_cOS_FormulaTree,		NULL,						0.6f, 0.0f, NULL);
	m_cOS_SizingTitleBox.InitState	(m_cSizingTitleBox,		*this, &m_cOS_FormulaTree,		NULL,						0.6f, 0.0f, NULL);
	Initialise ();

	CMenu *l_pMenu;
	l_pMenu = GetMenu ();
	if (l_pMenu)
	{
		CAppData::SetMenuItem(l_pMenu, ID_WINDOW_ALWAYSONTOP, m_cWindowState.m_bOnTop);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CItemCreation::OnSize(UINT nType, int cx, int cy)
{
	RedrawOff ();

	CDialog::OnSize(nType, cx, cy);

	ResizeGrids ();

	RedrawOn ();

}

void CItemCreation::OnGetMinMaxInfo (MINMAXINFO FAR* lpMMI)
{
	CDialog::OnGetMinMaxInfo (lpMMI);

	lpMMI->ptMinTrackSize.x = 400;
	lpMMI->ptMinTrackSize.y = 550;
	lpMMI->ptMaxTrackSize.x = 800;
	lpMMI->ptMaxTrackSize.y = 1280;

}

CItemCreation::ResizeGrids()
{
	float l_fWidth;
	int l_iAdjust = 0;

	ResizeResourceGrid();
	m_cOS_CategoriesText.Resize ();
	m_cOS_FormulaFilter.Resize ();
	m_cOS_FormulaCollapse.Resize ();
	m_cOS_FormulasText.Resize ();
	m_cOS_FormulaExpand.Resize ();
	m_cOS_FormulaTree.Resize ();
	m_cOS_InfoGrid.Resize ();
	m_cOS_TierGrid.Resize ();
	m_cOS_TechGrid.Resize ();
	m_cOS_RemoveTechButton.Resize ();
	m_cOS_ProfileSelecter.Resize ();
	m_cOS_ProfileText.Resize ();
	m_cOS_ItemSelecter.Resize ();
	m_cOS_ItemText.Resize ();
	m_cOS_ItemSelecter.Resize ();
	m_cOS_ItemText.Resize ();
	m_cOS_ResourceGrid.Resize ();
	m_cOS_AddItemButton.Resize ();
	m_cOS_ShowLevels.Resize ();
	m_cOS_SizingBox.Resize ();
	m_cOS_SizingTitleBox.Resize ();

	if (m_cWindowState.m_bLoaded)
	{
		CRect l_cRect;
		m_cItemInfoGrid.GetClientRect (l_cRect);

		m_cItemInfoGrid.SetColWidth (0, cInfoGridIndent);
		m_cItemInfoGrid.SetColWidth (1, CAppData::ConvertScreenWidthToGrid (l_cRect.Width()) - cInfoGridIndent);
		m_cTechGrid.SetColWidth (0, CAppData::ConvertScreenWidthToGrid (m_cOS_TechGrid.m_iCurWidth));

		CRect l_cResourceRect;
		m_cResourceGrid.GetClientRect (l_cResourceRect);
		l_fWidth = (float) CAppData::ConvertScreenWidthToGrid (l_cResourceRect.Width()) - 1500 - 700 - 820 - 500 - 500 - 500 - 700 - l_iAdjust;
		m_cResourceGrid.SetColWidth (0, 1500 + (long) (l_fWidth * 0.5f));
		m_cResourceGrid.SetColWidth (1, 700);
		m_cResourceGrid.SetColWidth (2, 820);
		m_cResourceGrid.SetColWidth (3, 500 + (long) (l_fWidth * 0.5f));
		m_cResourceGrid.SetColWidth (4, 500);
		m_cResourceGrid.SetColWidth (5, 500);
		m_cResourceGrid.SetColWidth (6, 700);
		m_cResourceGrid.SetColWidth (7, l_iAdjust);

		OnRowColChangeTiergrid();

		if (m_cItemInfoGrid.GetRows () > 0)
		{
			CRect l_cSizingRect;
			CRect l_cSizingTitleRect;

			m_cSizingBox.GetClientRect (l_cSizingRect);
			m_cSizingTitleBox.GetClientRect (l_cSizingTitleRect);
			m_cSizingTitleBox.SetWindowPos (NULL, 0, 0, l_cRect.Width(), 20, SWP_NOMOVE);
			m_cSizingBox.SetWindowPos (NULL, 0, 0, l_cRect.Width() - CAppData::ConvertGridWidthToScreen (cInfoGridIndent), 20, SWP_NOMOVE);
		}
	}
}

CItemCreation::StartUp()
{

	this->Create (IDD_ITEMDIALOG, CWnd::GetDesktopWindow ());
	m_cWindowState.m_bLoaded = true;

}

CItemCreation::DrawCategoryList()
{
	POSITION l_Pos;
	int l_iPos = 0;

	m_cFilterList.SetBkColor (CScheme::GetColour ("TREE_BACKCOLOUR"));
	m_cFilterList.SetTextBkColor (CScheme::GetColour ("TREE_BACKCOLOUR"));
	m_cFilterList.DeleteAllItems();
	m_cFilterList.InsertItem  (l_iPos, cNo_Filter);
	m_cFilterList.SetItemData (l_iPos++, 5);
	m_cFilterList.InsertItem (l_iPos, cCustom_Filter);
	m_cFilterList.SetItemData (l_iPos++, 5);

	l_Pos = CAppData::m_clFormulaCategoryList.GetHeadPosition ();
	while (l_Pos)
	{
		m_cFilterList.InsertItem (l_iPos, CAppData::m_clFormulaCategoryList.GetNext (l_Pos));
		m_cFilterList.SetItemData (l_iPos++, 5);
	}
	m_cFilterList.SetColumnWidth (0, 75);

	SelectCategory (CAppData::m_csLastFormulaCategory);
	CAppData::m_csLastFormulaCategory = GetCategory ();
}

CItemCreation::Initialise()
{
	m_PrevFormulaTree = NULL;
	m_csPrevFormulaTierName = "";
	m_csPrevFormulaName.Empty ();
	m_bFormulaTreeExpand = false;
	m_bDisplayFormula = false;

	if (CAppData::m_bEnableIcons)
	{
		m_cFormulaTree.SetImageList (&CAppData::m_cpIconImages->m_cImageList, TVSIL_NORMAL);
	}
	else
	{
		m_cFormulaTree.SetImageList (NULL, TVSIL_NORMAL);
	}
	m_cFormulaTree.SetBkColor (CScheme::GetColour ("TREE_BACKCOLOUR"));

	DrawFormulaList ();
	DrawCategoryList();

	m_cItemInfoGrid.SetRows (0);
	m_cItemInfoGrid.SetFormatString (">Col1|<Col2");
	m_cItemInfoGrid.SetColWidth (0, cInfoGridIndent);
	m_cItemInfoGrid.SetColWidth (1, 2700);
	m_cItemInfoGrid.SetColAlignment (0, 7);
	m_cItemInfoGrid.SetColAlignment (1, 1);
	m_cItemInfoGrid.SetBackColor (CScheme::GetColour ("GRID_INFOBACKCOLOUR"));
	m_cItemInfoGrid.SetBackColorBkg (CScheme::GetColour ("GRID_INFOBACKCOLOUR"));
	m_cItemInfoGrid.SetGridColorFixed (CScheme::GetColour ("GRID_INFOBACKCOLOUR"));
	m_cItemInfoGrid.SetForeColorSel (CScheme::GetColour ("SELECTCOLOUR_FG"));
	m_cItemInfoGrid.SetBackColorSel (CScheme::GetColour ("SELECTCOLOUR_BG"));

	m_cResourceGrid.SetRows (1);
	m_cResourceGrid.SetFormatString ("<Resource|^Effiency|^Need|^Skill Used|^Min|^Opt|^Cur Skill|");
	m_cResourceGrid.SetColWidth (0, 1870);
	m_cResourceGrid.SetColWidth (1, 1000);
	m_cResourceGrid.SetColWidth (2, 700);
	m_cResourceGrid.SetColWidth (3, 1400);
	m_cResourceGrid.SetColWidth (4, 700);
	m_cResourceGrid.SetColWidth (5, 700);
	m_cResourceGrid.SetColWidth (6, 700);
	m_cResourceGrid.SetColWidth (7, 0);
	m_cResourceGrid.SetBackColor (CScheme::GetColour ("GRID_BACKCOLOUR"));
	m_cResourceGrid.SetBackColorBkg (CScheme::GetColour ("GRID_BACKCOLOUR"));
	m_cResourceGrid.SetGridColor (CScheme::GetColour ("GRID_LINECOLOUR_LIGHT"));
	m_cResourceGrid.SetGridColorFixed (CScheme::GetColour ("GRID_LINECOLOUR_DARK"));
	m_cResourceGrid.SetForeColorSel (CScheme::GetColour ("SELECTCOLOUR_FG"));
	m_cResourceGrid.SetBackColorSel (CScheme::GetColour ("SELECTCOLOUR_BG"));
	m_cTierGrid.SetRows (1);
	m_cTierGrid.SetFormatString ("^Tiers / Variants");
	//m_cTierGrid.SetColWidth (0, 1700);
	m_cTierGrid.SetColWidth (0, 2400);
	m_cTierGrid.SetBackColor (CScheme::GetColour ("GRID_LISTBACKCOLOUR"));
	m_cTierGrid.SetBackColorBkg (CScheme::GetColour ("GRID_LISTBACKCOLOUR"));
	m_cTierGrid.SetGridColorFixed (CScheme::GetColour ("GRID_LISTBACKCOLOUR"));
	m_cTierGrid.SetForeColorSel (CScheme::GetColour ("SELECTCOLOUR_FG"));
	m_cTierGrid.SetBackColorSel (CScheme::GetColour ("SELECTCOLOUR_BG"));

	m_cTechGrid.SetRows (1);
	m_cTechGrid.SetFormatString ("^Techniques");
	m_cTechGrid.SetColWidth (0, 2420);
	m_cTechGrid.SetBackColor (CScheme::GetColour ("GRID_LISTBACKCOLOUR"));
	m_cTechGrid.SetBackColorBkg (CScheme::GetColour ("GRID_LISTBACKCOLOUR"));
	m_cTechGrid.SetGridColorFixed (CScheme::GetColour ("GRID_LISTBACKCOLOUR"));
	m_cTechGrid.SetForeColorSel (CScheme::GetColour ("SELECTCOLOUR_FG"));
	m_cTechGrid.SetBackColorSel (CScheme::GetColour ("SELECTCOLOUR_BG"));

	DisableScreen();

	ResizeResourceGrid ();

	DisplayProfiles ();
	DisplayItems ();

	UpdateResourceBreakdownMenu();
	UpdateAutoExpandMenu();
	UpdateResourceGridMenu();
}

void CItemCreation::OnClose()
{
	CAppData::SetItemWindow (false);
	CDialog::OnClose();
}

void CItemCreation::OnCancel()
{
	EndEditCell (false);
}


/******************************************************************************************/

CItemCreation::FilterEffectList(CTypedPtrList<CPtrList, CEffect*> &a_clEffectsList,
										  int &a_iClassPermitted,
										  int &a_iSchoolPermitted,
										  int &a_iRacePermitted)
{
	POSITION l_Pos;
	CEffect     *l_cpEffect;

	l_Pos = a_clEffectsList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpEffect = a_clEffectsList.GetNext (l_Pos);
		if (l_cpEffect->m_csType == cXMLAttribute_ReqClass)
		{
			if (l_cpEffect->m_csDescription.Find (CAppData::m_cFormClassFilter) >= 0)
			{
				a_iClassPermitted = 1;
			}
			else
			{
				a_iClassPermitted = -1;
			}
		}
		else if (l_cpEffect->m_csType == cXMLAttribute_ReqLevel)
		{
			if (l_cpEffect->m_csDescription.Left (20) == "Current School Level")
			{
				a_iSchoolPermitted = -1;
			}
		}
		else if (l_cpEffect->m_csType == cXMLAttribute_ReqRace)
		{
			if (l_cpEffect->m_csDescription.Find (CAppData::m_cFormClassFilterType) >= 0)
			{
				a_iRacePermitted = 1;
			}
			else
			{
				a_iRacePermitted = -1;
			}
		}
	}
}

CItemCreation::DrawFormulaList()
{
	CFormulaSet *l_cpFormulaSet;
	CFormula		*l_cpFormula;
	CFormulaTier *l_cpFormulaTier;
	POSITION l_FormulaSetPos;
	POSITION l_FormulaPos;
	POSITION l_Pos;

	HTREEITEM l_hTypeItem;
	HTREEITEM l_hTreeItem;
	HTREEITEM l_hSelectedTreeItem = NULL;

	int l_iFormulaCount = 0;
	int l_iOffset = 0;
	bool l_bShowFormula;
	int  l_iClassPermitted;
	int  l_iSchoolPermitted;
	int  l_iRacePermitted;

	unsigned long l_iFormulaSetOffset = 0;
	CString l_csCategoryText;
	int l_iStartOffset;
	int l_iEndOffset;
	int l_iCatShow;
	int l_iCatTotal;
	CString l_csFormulaName;
	CString l_csFilterName;
	CString l_csFormulaTierName;

	m_bFormulaTreeExpand = true;
	this->LockWindowUpdate ();
	m_cFormulaTree.DeleteAllItems ();
	l_csFilterName = CAppData::m_cFormFilter;
	l_csFilterName.MakeLower ();

	l_FormulaSetPos = CAppData::m_clFormulaSetList.GetHeadPosition ();
	while (l_FormulaSetPos)
	{
		l_cpFormulaSet = CAppData::m_clFormulaSetList.GetNext (l_FormulaSetPos);

		if ((l_cpFormulaSet->m_csCategory == CAppData::m_csLastFormulaCategory) ||
			(CAppData::m_csLastFormulaCategory == cNo_Filter) ||
			(CAppData::m_csLastFormulaCategory == cCustom_Filter))
		{
			l_hTypeItem = m_cFormulaTree.FindTreeItem (l_cpFormulaSet->m_csName, 0);

			if (l_hTypeItem == NULL)
			{
				l_csCategoryText.Format ("%s (0/0)", l_cpFormulaSet->m_csName);
				l_hTypeItem = m_cFormulaTree.InsertItem (l_csCategoryText, l_cpFormulaSet->m_iIcon, l_cpFormulaSet->m_iIcon, TVI_ROOT, TVI_LAST);
				m_cFormulaTree.SetItemData (l_hTypeItem, -1);
			}

			l_csCategoryText = m_cFormulaTree.GetItemText (l_hTypeItem);
			l_iStartOffset = l_csCategoryText.Find ('(') + 1;
			l_iEndOffset = l_csCategoryText.Find ('/', l_iStartOffset);
			l_iCatShow = atoi (l_csCategoryText.Mid (l_iStartOffset, (l_iEndOffset - l_iStartOffset)));
			l_iStartOffset = l_iEndOffset + 1;
			l_iEndOffset =  l_csCategoryText.Find (')', l_iStartOffset);
			l_iCatTotal = atoi (l_csCategoryText.Mid (l_iStartOffset, (l_iEndOffset - l_iStartOffset)));

			l_FormulaPos = l_cpFormulaSet->m_clFormulaList.GetHeadPosition ();

			while (l_FormulaPos)
			{
				l_cpFormula = l_cpFormulaSet->m_clFormulaList.GetNext (l_FormulaPos);
				l_iCatTotal++;

				if (CAppData::m_csLastFormulaCategory == cCustom_Filter)
				{
					l_bShowFormula = false;
					if (CAppData::m_cpFormFilterTech)
					{
						l_bShowFormula = CAppData::m_cpFormFilterTech->CheckFormula (l_cpFormula, NULL);
					}

					if (!l_csFilterName.IsEmpty ())
					{
						l_csFormulaName = l_cpFormula->m_csName;
						l_csFormulaName.MakeLower ();
						l_bShowFormula = l_csFormulaName.Find (l_csFilterName) >= 0;

						if (!CAppData::m_bFormSearchMode && l_bShowFormula == false)
						{
                            l_Pos = l_cpFormula->m_clFormulaTierList.GetHeadPosition ();
                            while (l_Pos)
                            {
                                l_cpFormulaTier = l_cpFormula->m_clFormulaTierList.GetNext (l_Pos);
                                l_csFormulaTierName = l_cpFormulaTier->m_csName;
                                l_csFormulaTierName.MakeLower ();

                                if (l_csFormulaTierName.Find (l_csFilterName) != -1)
                                {
                                    if (!l_bShowFormula)
                                    {
                                        CAppData::m_csPreferedFormulaTierName = l_cpFormulaTier->m_csTierName;
                                        CAppData::m_csPreferedFormulaTier = l_cpFormulaTier->m_iTierLevel;

                                        //AfxMessageBox (l_cpFormulaTier->m_csTierName, MB_ICONEXCLAMATION );
                                    }

                                    l_bShowFormula = true;
                                    break;
                                }
                            }
						}


					}

					if (!CAppData::m_cFormClassFilter.IsEmpty ())
					{
						l_iClassPermitted = 0;
						l_iSchoolPermitted = 0;
						l_iRacePermitted = 0;

						FilterEffectList (l_cpFormula->m_clEffectsList, l_iClassPermitted, l_iSchoolPermitted, l_iRacePermitted);

						l_Pos = l_cpFormula->m_clFormulaTierList.GetHeadPosition ();
						while (l_Pos)
						{
							l_cpFormulaTier = l_cpFormula->m_clFormulaTierList.GetNext (l_Pos);
							FilterEffectList (l_cpFormulaTier->m_clEffectsList, l_iClassPermitted, l_iSchoolPermitted, l_iRacePermitted);
						}

						if (l_iClassPermitted > 0)
						{
							l_bShowFormula = true;
						}
						else if ((l_iClassPermitted == 0) && (l_iRacePermitted >= 0))
						{
							l_bShowFormula = (l_iSchoolPermitted > 0) || (l_iRacePermitted > 0);
						}
					}
				}
				else
				{
					l_bShowFormula = true;
				}

				if (l_bShowFormula)
				{
					l_iCatShow++;
					l_hTreeItem = m_cFormulaTree.InsertItem (l_cpFormula->m_csName, l_cpFormula->m_iIcon, l_cpFormula->m_iIcon, l_hTypeItem, TVI_LAST);
					m_cFormulaTree.SetItemData (l_hTreeItem, l_iFormulaSetOffset);
					l_iFormulaCount++;

					if (CAppData::m_cpCurrentFormula)
					{
						if ((CAppData::m_cpCurrentFormula->m_csCategory == l_cpFormula->m_csCategory) &&
							 (CAppData::m_cpCurrentFormula->m_csName == l_cpFormula->m_csName))
						{
							l_hSelectedTreeItem = l_hTreeItem;
						}
					}
				}
			}

			l_csCategoryText.Format ("%s (%d/%d)", l_cpFormulaSet->m_csName, l_iCatShow, l_iCatTotal);
			m_cFormulaTree.SetItemText (l_hTypeItem, l_csCategoryText);

			if (m_cFormulaTree.GetChildItem (l_hTypeItem))
			{
				if (CAppData::m_iExpandFormulaMode > 1)
				{
					m_cFormulaTree.Expand (l_hTypeItem, TVE_EXPAND);
				}

				m_cFormulaTree.SortChildren (l_hTypeItem);
			}
			else
			{
				m_cFormulaTree.DeleteItem (l_hTypeItem);
			}
		}

		l_iFormulaSetOffset++;
	}
	m_cFormulaTree.SortChildren (TVI_ROOT);


	if (l_hSelectedTreeItem)
	{
		if (CAppData::m_iExpandFormulaMode > 0)
		{
			m_cFormulaTree.SelectItem (l_hSelectedTreeItem);
			m_cFormulaTree.EnsureVisible (l_hSelectedTreeItem);
		}

		EnableScreen ();
	}
	else
	{
		l_hTypeItem = m_cFormulaTree.GetRootItem ();
		if (l_hTypeItem)
		{
			m_cFormulaTree.SelectItem (l_hTypeItem);
			if (CAppData::m_iExpandFormulaMode > 0)
			{
				m_cFormulaTree.Expand (l_hTypeItem, TVE_EXPAND);
			}
			CAppData::m_cpCurrentFormula = NULL;
			DisableScreen ();
			CAppData::m_cTechSelectionWnd.DrawTechList ();
		}
	}

	this->UnlockWindowUpdate ();
	m_bFormulaTreeExpand = false;

	CString l_csMsg;
	l_csMsg.Format ("%d Formulae", l_iFormulaCount);
	if (CAppData::m_csLastFormulaCategory == cCustom_Filter)
	{
		if (!CAppData::m_cFormClassFilter.IsEmpty ())
		{
			l_csMsg += " (" + CAppData::m_cFormClassFilter + ")";
		}
		else
		{
			l_csMsg += " (Filtered)";
		}
	}
	m_cFormulasText.SetWindowText (l_csMsg);

}


CItemCreation::SelectCategory(CString a_csCategory)
{
	int l_iPos = 0;

	while (l_iPos < m_cFilterList.GetItemCount ())
	{
		if (m_cFilterList.GetItemText (l_iPos, 0) == a_csCategory)
		{
			m_cFilterList.SetSelectionMark (l_iPos);
			m_cFilterList.SetItemState(l_iPos, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
			l_iPos = m_cFilterList.GetItemCount ();
		}
		else
		{
			l_iPos++;
		}
	}
}

void CItemCreation::OnSelchangedFormulatree(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	SelectCurrentFormula (m_cFormulaTree.GetSelectedItem ());
	*pResult = 0;
}

CItemCreation::DisplayFormula(bool a_bUpdateTechList)
{
	POSITION l_Pos;
	CFormulaTier *l_cpFormulaTier;
	CItemResource *l_cpItemResource;
	CString l_csSlot;
	CString l_csTierStr;
	CString l_csResourceStr = "";
	CString l_csBonusStr = "";
	CString l_csPrevInfoName = "";
	CString l_csDelayText;
	CString l_csEquipSlot = "";
	CItemTech l_cItemTech;
	CTechTier	*l_cpTechTier = NULL;
	int l_iSkillAdjust = 0;
	int l_iUsageAdjust = 0;
	bool l_bHeader;

	if (!m_bFormulaTreeExpand)
	{
		m_bDisplayFormula = true;
		l_iUsageAdjust = CAppData::DetermineCurrentItemUsageOffset ();

		if (CAppData::m_cpCurrentFormula)
		{
			RedrawOff ();
			this->LockWindowUpdate ();

			if (CAppData::m_cpCurrentFormula->FindFormulaTier (CAppData::m_csCurrentFormulaTierName, &l_cpFormulaTier))
			{

				m_cItemInfoGrid.SetRows (0);
				m_cResourceGrid.SetRows (1);

				AddTitleLine (l_cpFormulaTier->m_csName, GRID_TITLE);

				if (l_cpFormulaTier->m_csDescription.IsEmpty () == false)
				{
					AddTitleLine (l_cpFormulaTier->m_csDescription, GRID_DESCRIPTION);
				}

				AddSummaryLine ("|", GRID_EFFECT);

				l_Pos = CAppData::m_cCurrentOrderItem.m_clTechList.GetHeadPosition ();
				while (l_Pos)
				{
					l_cItemTech = CAppData::m_cCurrentOrderItem.m_clTechList.GetNext (l_Pos);

					if (CAppData::FindTechTier (l_cItemTech.m_csCategory, l_cItemTech.m_csTechName, l_cItemTech.m_csTierName, &l_cpTechTier))
					{
						l_iSkillAdjust += l_cpTechTier->m_iSkillAdjust;

					}
				}

				l_Pos = CAppData::m_cCurrentOrderItem.m_clTechList.GetHeadPosition ();
				while (l_Pos)
				{
					l_cItemTech = CAppData::m_cCurrentOrderItem.m_clTechList.GetNext (l_Pos);

					if (CAppData::FindTechTier (l_cItemTech.m_csCategory, l_cItemTech.m_csTechName, l_cItemTech.m_csTierName, &l_cpTechTier))
					{
					}
				}

				if (CAppData::m_cpCurrentFormula->m_iBatchQty > 1)
				{
					l_csResourceStr.Format ("%d", CAppData::m_cpCurrentFormula->m_iBatchQty);
					AddSummaryLine ("Qty Produced|" + l_csResourceStr, GRID_EFFECT);
				}

				// Normal Formulas
				// Equip Slot
				if (!CAppData::FindEffectType (CAppData::m_cpCurrentFormula->m_clEffectsList, cXMLAttribute_EquipSlot, l_csEquipSlot))
				{
					if (!CAppData::FindEffectType (l_cpFormulaTier->m_clEffectsList, cXMLAttribute_EquipSlot, l_csEquipSlot))
					{
						l_csEquipSlot = cXMLEquipSlot_Unknown;
					}
				}

				if (l_csEquipSlot != cXMLEquipSlot_Unknown)
				{
				}

				if (l_csEquipSlot == cXMLEquipSlot_Spellbook)
				{
					l_csDelayText = "Casting Delay";
				}
				else if ((l_csEquipSlot != cXMLEquipSlot_Unknown) &&
					      (l_csEquipSlot != cXMLEquipSlot_All))
				{
					l_csDelayText = "Delay";
					AddSummaryLine ("Equip Slot|" + l_csEquipSlot, GRID_EFFECT);

				}
				else
				{
					l_csDelayText = "Delay";
				}


				// Heal Amount
				l_bHeader = false;
				CAppData::AddEffectType (CAppData::m_cpCurrentFormula->m_clEffectsList, cXMLAttribute_HealAmount,
												 "Heals", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);
				CAppData::AddEffectType (l_cpFormulaTier->m_clEffectsList, cXMLAttribute_HealAmount,
												 "Heals", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);

				// Attack Damage
				l_bHeader = false;
				CAppData::AddEffectType (CAppData::m_cpCurrentFormula->m_clEffectsList, cXMLAttribute_Damage,
												 "Damage", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);
				CAppData::AddEffectType (l_cpFormulaTier->m_clEffectsList, cXMLAttribute_Damage,
												 "Damage", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);

				// Attack Type
				l_bHeader = false;
				CAppData::AddEffectType (CAppData::m_cpCurrentFormula->m_clEffectsList, cXMLAttribute_Type,
												 "Attack Type", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);
				CAppData::AddEffectType (l_cpFormulaTier->m_clEffectsList, cXMLAttribute_Type,
												 "Attack Type", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);

				// Attack Delay
				l_bHeader = false;
				CAppData::AddEffectType (CAppData::m_cpCurrentFormula->m_clEffectsList, cXMLAttribute_Delay,
												 l_csDelayText, m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);
				CAppData::AddEffectType (l_cpFormulaTier->m_clEffectsList, cXMLAttribute_Delay,
												 l_csDelayText, m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);

				// Attack Recycle
				l_bHeader = false;
				CAppData::AddEffectType (CAppData::m_cpCurrentFormula->m_clEffectsList, cXMLAttribute_Recycle,
												 "Recycle", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);
				CAppData::AddEffectType (l_cpFormulaTier->m_clEffectsList, cXMLAttribute_Recycle,
												 "Recycle", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);

				// Attack Range
				l_bHeader = false;
				CAppData::AddEffectType (CAppData::m_cpCurrentFormula->m_clEffectsList, cXMLAttribute_Range,
												 "Range", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);
				CAppData::AddEffectType (l_cpFormulaTier->m_clEffectsList, cXMLAttribute_Range,
												 "Range", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);

				// Attack Skill
				l_bHeader = false;
				CAppData::AddEffectType (CAppData::m_cpCurrentFormula->m_clEffectsList, cXMLAttribute_Skill,
												 "Skill", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);
				CAppData::AddEffectType (l_cpFormulaTier->m_clEffectsList, cXMLAttribute_Skill,
												 "Skill", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);

				// Area
				l_bHeader = false;
				CAppData::AddEffectType (CAppData::m_cpCurrentFormula->m_clEffectsList, cXMLAttribute_Area,
												 "Area", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);
				CAppData::AddEffectType (l_cpFormulaTier->m_clEffectsList, cXMLAttribute_Area,
												 "Area", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);

				// Extra Damage
				l_bHeader = false;
				CAppData::AddEffectType (CAppData::m_cpCurrentFormula->m_clEffectsList, cXMLAttribute_ExtraDamage,
												 "Extra Damage", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);
				CAppData::AddEffectType (l_cpFormulaTier->m_clEffectsList, cXMLAttribute_ExtraDamage,

												 "Extra Damage", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);
                /*
                // Race Requirements
                l_bHeader = false;
				CAppData::AddEffectType (CAppData::m_cpCurrentFormula->m_clEffectsList, cXMLAttribute_ReqRace,
												 "Requirements", m_cItemInfoGrid, GRID_REQUIREMENT, &m_cSizingBox, "", l_bHeader);
				CAppData::AddEffectType (l_cpFormulaTier->m_clEffectsList, cXMLAttribute_ReqRace,
												 "Requirements", m_cItemInfoGrid, GRID_REQUIREMENT, &m_cSizingBox, "", l_bHeader);
                */
				// Duration
				l_bHeader = false;
				CAppData::AddEffectType (CAppData::m_cpCurrentFormula->m_clEffectsList, cXMLAttribute_Duration,
												 "Duration", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);
				CAppData::AddEffectType (l_cpFormulaTier->m_clEffectsList, cXMLAttribute_Duration,
												 "Duration", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);

				// Frequency
				l_bHeader = false;
				CAppData::AddEffectType (CAppData::m_cpCurrentFormula->m_clEffectsList, cXMLAttribute_Frequency,
												 "Frequency", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);
				CAppData::AddEffectType (l_cpFormulaTier->m_clEffectsList, cXMLAttribute_Frequency,
												 "Frequency", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);

				// Hoard Cost
				l_bHeader = false;
				CAppData::AddEffectType (CAppData::m_cpCurrentFormula->m_clEffectsList, cXMLAttribute_HoardCost,
												 "Hoard Cost", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);
				CAppData::AddEffectType (l_cpFormulaTier->m_clEffectsList, cXMLAttribute_HoardCost,
												 "Hoard Cost", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);

				// Capacity
				l_bHeader = false;
				CAppData::AddEffectType (CAppData::m_cpCurrentFormula->m_clEffectsList, cXMLAttribute_Capacity,
												 "Capacity", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);
				CAppData::AddEffectType (l_cpFormulaTier->m_clEffectsList, cXMLAttribute_Capacity,
												 "Capacity", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);


				// Stat Bonuses, Stat Caps, ShieldOn, Prevent Teleport, Equip Effects
				l_bHeader = false;
				CAppData::AddEffectType (CAppData::m_cpCurrentFormula->m_clEffectsList, CAppData::m_csEffectList_Bonuses,
												 "", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);
				CAppData::AddEffectType (l_cpFormulaTier->m_clEffectsList, CAppData::m_csEffectList_Bonuses,
												 "", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);

				// New Timer
				l_bHeader = false;
				CAppData::AddEffectType (CAppData::m_cpCurrentFormula->m_clEffectsList, cXMLAttribute_Timer,
												 "", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);
				CAppData::AddEffectType (l_cpFormulaTier->m_clEffectsList, cXMLAttribute_Timer,
												 "", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);

				DisplayTechBonuses ();

				// Construction Formulas
				l_bHeader = false;
				CAppData::AddEffectType (l_cpFormulaTier->m_clEffectsList, cXMLAttribute_StructureStacks,
												 "Max Stacks", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);

				l_bHeader = false;
				CAppData::AddEffectType (l_cpFormulaTier->m_clEffectsList, cXMLAttribute_StructureBulk,
												 "Max Bulk", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);

				l_bHeader = false;
				CAppData::AddEffectType (l_cpFormulaTier->m_clEffectsList, cXMLAttribute_StructureNPC,
												 "Spawns", m_cItemInfoGrid, GRID_REQUIREMENT, &m_cSizingBox, "", l_bHeader);

				l_bHeader = false;
				CAppData::AddEffectType (l_cpFormulaTier->m_clEffectsList, cXMLAttribute_StructureMachine,
												 "Machines", m_cItemInfoGrid, GRID_REQUIREMENT, &m_cSizingBox, "", l_bHeader);

				l_bHeader = false;
				CAppData::AddEffectType (l_cpFormulaTier->m_clEffectsList, cXMLAttribute_StructureBind,
												 "", m_cItemInfoGrid, GRID_BONUS, &m_cSizingBox, "", l_bHeader);

				AddSummaryLine ("|", GRID_EFFECT);
				// Usable By
				l_bHeader = false;
				CAppData::AddEffectType (CAppData::m_cpCurrentFormula->m_clEffectsList, cXMLAttribute_ReqClass,
												 "Usable By", m_cItemInfoGrid, GRID_REQUIREMENT, &m_cSizingBox, "- ", l_bHeader);

				// Requirements
				l_bHeader = false;
				CAppData::AddEffectType (CAppData::m_cpCurrentFormula->m_clEffectsList, CAppData::m_csEffectList_Requirements,
												 "Requirements", m_cItemInfoGrid, GRID_REQUIREMENT, &m_cSizingBox, "- ", l_bHeader);
				CAppData::AddEffectType (l_cpFormulaTier->m_clEffectsList, CAppData::m_csEffectList_Requirements,
												 "Requirements", m_cItemInfoGrid, GRID_REQUIREMENT, &m_cSizingBox, "- ", l_bHeader);

				// Bulk
				l_bHeader = false;
				CAppData::AddEffectType (CAppData::m_cpCurrentFormula->m_clEffectsList, cXMLAttribute_Bulk,
												 "Bulk", m_cItemInfoGrid, GRID_REQUIREMENT, &m_cSizingBox, "", l_bHeader);
				CAppData::AddEffectType (l_cpFormulaTier->m_clEffectsList, cXMLAttribute_Bulk,
												 "Bulk", m_cItemInfoGrid, GRID_REQUIREMENT, &m_cSizingBox, "", l_bHeader);

				// Hoard Value
				l_bHeader = false;
				CAppData::AddEffectType (CAppData::m_cpCurrentFormula->m_clEffectsList, cXMLAttribute_HoardValue,
												 "Hoard Value", m_cItemInfoGrid, GRID_REQUIREMENT, &m_cSizingBox, "", l_bHeader);
				CAppData::AddEffectType (l_cpFormulaTier->m_clEffectsList, cXMLAttribute_HoardValue,
												 "Hoard Value", m_cItemInfoGrid, GRID_REQUIREMENT, &m_cSizingBox, "", l_bHeader);

                //AfxMessageBox (cXMLAttribute_DamageModifier, MB_ICONEXCLAMATION );

                AddSummaryLine ("|", GRID_EFFECT);
                l_bHeader = false;
				CAppData::AddEffectType (CAppData::m_cpCurrentFormula->m_clEffectsList, cXMLAttribute_DamageModifier,
												 "", m_cItemInfoGrid, GRID_EFFECTDESCRIPTION, &m_cSizingBox, "", l_bHeader);
				CAppData::AddEffectType (l_cpFormulaTier->m_clEffectsList, cXMLAttribute_DamageModifier,
												 "", m_cItemInfoGrid, GRID_EFFECTDESCRIPTION, &m_cSizingBox, "", l_bHeader);

				// Effect
                AddSummaryLine ("|", GRID_EFFECT);
				l_bHeader = false;
				CAppData::AddEffectType (CAppData::m_cpCurrentFormula->m_clEffectsList, cXMLAttribute_TargetName,
												 "Effect", m_cItemInfoGrid, GRID_EFFECTTITLE, &m_cSizingBox, "", l_bHeader);
				CAppData::AddEffectType (l_cpFormulaTier->m_clEffectsList, cXMLAttribute_TargetName,
												 "Effect", m_cItemInfoGrid, GRID_EFFECTTITLE, &m_cSizingBox, "", l_bHeader);

				l_bHeader = false;
				CAppData::AddEffectType (CAppData::m_cpCurrentFormula->m_clEffectsList, cXMLAttribute_TargetDescription,
												 "Description", m_cItemInfoGrid, GRID_EFFECTDESCRIPTION, &m_cSizingBox, "", l_bHeader);
				CAppData::AddEffectType (l_cpFormulaTier->m_clEffectsList, cXMLAttribute_TargetDescription,
												 "Description", m_cItemInfoGrid, GRID_EFFECTDESCRIPTION, &m_cSizingBox, "", l_bHeader);

				AddSummaryLine ("|", GRID_EFFECT);
				l_bHeader = false;

				CAppData::AddEffectType (CAppData::m_cpCurrentFormula->m_clEffectsList, cXMLAttribute_EffectChance,
												 "Chance", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);
				CAppData::AddEffectType (l_cpFormulaTier->m_clEffectsList, cXMLAttribute_EffectChance,
												 "Chance", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);
                l_bHeader = false;
				CAppData::AddEffectType (CAppData::m_cpCurrentFormula->m_clEffectsList, cXMLAttribute_TargetDuration,
												 "Duration", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);
				CAppData::AddEffectType (l_cpFormulaTier->m_clEffectsList, cXMLAttribute_TargetDuration,
												 "Duration", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);

				l_bHeader = false;
				CAppData::AddEffectType (CAppData::m_cpCurrentFormula->m_clEffectsList, cXMLAttribute_TargetFrequency,
												 "Frequency", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);
				CAppData::AddEffectType (l_cpFormulaTier->m_clEffectsList, cXMLAttribute_TargetFrequency,
												 "Frequency", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);

				l_bHeader = false;
				CAppData::AddEffectType (CAppData::m_cpCurrentFormula->m_clEffectsList, cXMLAttribute_TargetEffect,
												 "", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);
				CAppData::AddEffectType (l_cpFormulaTier->m_clEffectsList, cXMLAttribute_TargetEffect,
												 "", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);

				DisplayTechEffects ();

				AdjustTechUsage ();

				if (l_bHeader)
				{
					AddSummaryLine ("|", GRID_EFFECT);
				}

				l_Pos = l_cpFormulaTier->m_clResourceList.GetHeadPosition ();
				while (l_Pos)
				{
					l_cpItemResource = l_cpFormulaTier->m_clResourceList.GetNext (l_Pos);

					if (CAppData::m_iShowResourceMode == 2)
					{
						AddBaseResources (l_cpItemResource, GRID_RESOURCE, 1, l_iSkillAdjust);
					}
					else
					{
						AddToResources (l_cpItemResource, GRID_RESOURCE, 1, l_iSkillAdjust);
					}
				}

				AddTechResources ();

				m_cResourceGrid.SelectRow (1, false);

				DisplayFormulaTechs ();

				if (CAppData::m_iShowResourceMode == 1)
				{
					AddTemporaryFormulas ();
				}

				if (a_bUpdateTechList)
				{
					CAppData::m_cTechSelectionWnd.DrawTechList ();
 				}

			}

			this->UnlockWindowUpdate ();
			RedrawOn ();
			ResizeGrids ();


		}

		m_bDisplayFormula = false;
	}
}

void CItemCreation::ModifyLine (CString a_csLineName, CString a_csAttributeType, CString a_csModifier)
{
	int l_iOffset;
	CString l_csLine;
	CString l_csLineValue;
	int l_iValue1;
	int l_iValue2;
	int l_iValue3;
	int l_iValue4;

	l_iOffset = 1;
	while (l_iOffset < m_cItemInfoGrid.GetRows ())
	{
		l_csLine = m_cItemInfoGrid.GetTextMatrix (l_iOffset, 0);
		if (l_csLine == a_csLineName)
		{
			l_csLineValue = m_cItemInfoGrid.GetTextMatrix (l_iOffset, 1);

			if (a_csAttributeType == cXMLAttribute_RangeModifier)
			{
				sscanf (a_csModifier, "%d range", &l_iValue1);
				l_iValue1 += atoi (l_csLineValue);
				l_csLineValue.Format ("%d", l_iValue1);
			}
			else if (a_csAttributeType == cXMLAttribute_RecycleModifier)
			{
				if (l_csLineValue != "Repeating")
				{
					sscanf (l_csLineValue, "%d:%d", &l_iValue1, &l_iValue2);
					sscanf (a_csModifier, "%d:%d", &l_iValue3, &l_iValue4);

					if (a_csModifier[0] == '-')
					{
						l_iValue3 = 0 - l_iValue3;
						l_iValue4 = 0 - l_iValue4;
					}

					l_iValue1 += l_iValue3;
					l_iValue2 += l_iValue4;

					if (l_iValue2 >= 60)
					{
						l_iValue2 -= 60;
						l_iValue1++;
					}
					else if (l_iValue2 < 0)
					{
						l_iValue2 += 60;
						l_iValue1--;
					}


					l_csLineValue.Format ("%d:%02d", l_iValue1, l_iValue2);
				}
			}
			else if (a_csAttributeType == cXMLAttribute_AttackModifier)
			{
				sscanf (l_csLineValue, "%d-%d", &l_iValue1, &l_iValue2);
				sscanf (a_csModifier, "%d maximum damage", &l_iValue3);
				l_iValue4 = (l_iValue3 * 9) / 2;
				l_iValue1 += (l_iValue4 / 2);
				l_iValue2 += (l_iValue4);


				l_csLineValue.Format ("%d-%d", l_iValue1, l_iValue2);
			}
			else if (a_csAttributeType == cXMLAttribute_HealModifier)
			{
				sscanf (l_csLineValue, "%d-%d", &l_iValue1, &l_iValue2);
				sscanf (a_csModifier, "%d-%d points", &l_iValue3, &l_iValue4);
				l_iValue1 += (l_iValue3);
				l_iValue2 += (l_iValue4);


				l_csLineValue.Format ("%d-%d", l_iValue1, l_iValue2);
			}

			m_cItemInfoGrid.SetTextMatrix (l_iOffset, 1, l_csLineValue);
			l_iOffset = m_cItemInfoGrid.GetRows ();
		}
		l_iOffset++;
	}
}

void CItemCreation::DisplayTechBonuses ()
{
	POSITION l_Pos;
	POSITION l_EffectPos;
	CEffect *l_cpEffect;
	CItemTech l_cItemTech;
	CTechTier	*l_cpTechTier = NULL;
	bool l_bHeader;
	CString l_csValue;
	int l_iOffset;

	m_cTechGrid.SetRows (1);

	l_Pos = CAppData::m_cCurrentOrderItem.m_clTechList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cItemTech = CAppData::m_cCurrentOrderItem.m_clTechList.GetNext (l_Pos);

		if (CAppData::FindTechTier (l_cItemTech.m_csCategory, l_cItemTech.m_csTechName, l_cItemTech.m_csTierName, &l_cpTechTier))
		{
			l_bHeader = false;
			CAppData::AddEffectType (l_cpTechTier->m_clEffectList, cXMLAttribute_Bonus,
											 "", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);
			l_bHeader = false;
			CAppData::AddEffectType (l_cpTechTier->m_clEffectList, cXMLAttribute_ExtraDamage,
											 "Extra Damage", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);
			l_bHeader = false;
			CAppData::AddEffectType (l_cpTechTier->m_clEffectList, cXMLAttribute_ReqRace,
											 "Requirements", m_cItemInfoGrid, GRID_REQUIREMENT, &m_cSizingBox, "- ", l_bHeader);
			l_bHeader = false;
			CAppData::AddEffectType (l_cpTechTier->m_clEffectList, cXMLAttribute_Effect,
											 "", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);

			l_EffectPos = l_cpTechTier->m_clEffectList.GetHeadPosition ();
			while (l_EffectPos)
			{
				l_cpEffect = l_cpTechTier->m_clEffectList.GetNext (l_EffectPos);
				if (l_cpEffect->m_csType == cXMLAttribute_RangeModifier)
				{
					ModifyLine ("Range", cXMLAttribute_RangeModifier, l_cpEffect->m_csDescription);
				}
				else if (l_cpEffect->m_csType == cXMLAttribute_RecycleModifier)
				{
					ModifyLine ("Recycle", cXMLAttribute_RecycleModifier, l_cpEffect->m_csDescription);
				}
				else if (l_cpEffect->m_csType == cXMLAttribute_AttackModifier)
				{
					ModifyLine ("Damage", cXMLAttribute_AttackModifier, l_cpEffect->m_csDescription);
				}
				else if (l_cpEffect->m_csType == cXMLAttribute_HealModifier)
				{
					ModifyLine ("Heals", cXMLAttribute_HealModifier, l_cpEffect->m_csDescription);
				}

			}
		}

	}

	l_bHeader = true;
	l_Pos = CAppData::m_cCurrentOrderItem.m_clTechList.GetHeadPosition ();

	if (l_Pos)
	{
		AddSummaryLine ("|", GRID_EFFECT);
	}

	while (l_Pos)
	{
		l_cItemTech = CAppData::m_cCurrentOrderItem.m_clTechList.GetNext (l_Pos);

		if (CAppData::FindTechTier (l_cItemTech.m_csCategory, l_cItemTech.m_csTechName, l_cItemTech.m_csTierName, &l_cpTechTier))
		{
			if (l_bHeader)
			{
				l_bHeader = false;
				AddSummaryLine ("Technique(s)|" + l_cpTechTier->m_csName, GRID_EFFECT);
			}
			else
			{
				AddSummaryLine ("|" + l_cpTechTier->m_csName, GRID_EFFECT);
			}
		}
	}
}

void CItemCreation::DisplayTechEffects ()
{
	POSITION l_Pos;
	CItemTech l_cItemTech;
	CTechTier	*l_cpTechTier = NULL;
	bool l_bHeader;

	l_Pos = CAppData::m_cCurrentOrderItem.m_clTechList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cItemTech = CAppData::m_cCurrentOrderItem.m_clTechList.GetNext (l_Pos);

		if (CAppData::FindTechTier (l_cItemTech.m_csCategory, l_cItemTech.m_csTechName, l_cItemTech.m_csTierName, &l_cpTechTier))
		{
			l_bHeader = false;
			CAppData::AddEffectType (l_cpTechTier->m_clEffectList, cXMLAttribute_TargetEffect,
											 "", m_cItemInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);

		}
	}
}

void CItemCreation::AdjustTechUsage ()
{
	POSITION l_Pos;
	CItemTech l_cItemTech;
	CTechTier	*l_cpTechTier = NULL;
	CString l_csValue;
	int l_iOffset;
	CString l_csLine;
	CString l_csNewLine;
	CString l_csLineValue;
	int l_iValue1;
	int l_iValue2;
	int l_iValue3;
	int l_iValue4;
	bool l_bSearch = false;
	bool l_bChanged = false;



	l_Pos = CAppData::m_cCurrentOrderItem.m_clTechList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cItemTech = CAppData::m_cCurrentOrderItem.m_clTechList.GetNext (l_Pos);
		l_bSearch = false;

		if (CAppData::FindTechTier (l_cItemTech.m_csCategory, l_cItemTech.m_csTechName, l_cItemTech.m_csTierName, &l_cpTechTier))
		{
		    /*
		    l_iOffset = 1;
		    do
            {
                if (m_cItemInfoGrid.GetTextMatrix (l_iOffset, 0) == "Usable By")
                {
                    if (l_cItemTech.m_csTechName == "Invisible")
                    {
                        l_csLine = m_cItemInfoGrid.GetTextMatrix (l_iOffset, 1);
                        AfxMessageBox ("l_csLine", MB_ICONEXCLAMATION );
                        m_cItemInfoGrid.SetTextMatrix (l_iOffset, 1, "Saris, Sslik, Satyr and Dryad");
                    }
                }
                l_iOffset++;
            } while (l_iOffset < m_cItemInfoGrid.GetRows ());
            */
			if (l_cpTechTier->m_iUsageAdjust > 0)
			{

				l_iOffset = 1;
				l_csNewLine.Empty ();

				do
				{
				    if ((l_bSearch) || (m_cItemInfoGrid.GetTextMatrix (l_iOffset, 0) == "Requirements"))
					{
						l_bSearch= true;
						l_csLine = m_cItemInfoGrid.GetTextMatrix (l_iOffset, 1);

						if (l_csLine[0] == '-')
						{
							if (l_csLine.Find ("Level") < 0)
							{
								l_bChanged = false;
								l_iValue1 = 0;
								while (l_iValue1 < l_csLine.GetLength ())
								{
									l_iValue2 = l_csLine.Find ('(', l_iValue1);
									if (l_iValue2 >= 0)
									{
										l_iValue3 = l_csLine.Find (')', l_iValue2);
										if (l_iValue3 >= 0)
										{
											l_csLineValue = l_csLine.Mid (l_iValue2 + 1, (l_iValue3 - l_iValue2) - 1);
											l_iValue4 = atoi (l_csLineValue);
											l_iValue4 += l_cpTechTier->m_iUsageAdjust;

											l_csNewLine += l_csLine.Mid (l_iValue1, (l_iValue2 - l_iValue1));
											l_csLineValue.Format ("(%d)", l_iValue4);
											l_csNewLine += l_csLineValue;
											l_iValue1 = l_iValue3 + 1;
											l_bChanged = true;
										}
										else
										{
											l_iValue1 = l_csLine.GetLength ();
										}
									}
									else
									{
										l_iValue1 = l_csLine.GetLength ();
									}
								}

								if (l_bChanged)
								{
									m_cItemInfoGrid.SetTextMatrix (l_iOffset, 1, l_csNewLine);
								}
							}
						}
					}

					l_iOffset++;

				} while (l_iOffset < m_cItemInfoGrid.GetRows ());
			}
		}
	}
}

CString CItemCreation::GetSummaryData(CString a_csType, CString a_csLine, int a_iOffset)
{
	CString l_csReturnStr = a_csLine;
	int l_iLastPos = 0;
	int l_iBracketStart;
	int l_iBracketEnd;
	int l_iValue;

	if (a_csType == "Requirements")
	{
		if (a_csLine.Left (7) != "Current")
		{
			while (l_iLastPos >= 0)
			{
				l_iBracketStart = l_csReturnStr.Find ("(", l_iLastPos);
				l_iBracketEnd = l_csReturnStr.Find (")", l_iLastPos);

				if ((l_iBracketStart >= 0) &&
					 (l_iBracketEnd >= 0) &&
					 (l_iBracketStart < l_iBracketEnd))
				{
					l_iValue = atoi (l_csReturnStr.Mid (l_iBracketStart + 1, (l_iBracketEnd - l_iBracketStart - 1)));
					l_iValue += a_iOffset;
					l_csReturnStr.Format ("%s%d%s", l_csReturnStr.Left (l_iBracketStart + 1), l_iValue, l_csReturnStr.Mid (l_iBracketEnd));
					l_iLastPos = l_iBracketEnd + 1;
				}
				else
				{
					l_iLastPos = -1;
				}

			}
		}
	}
	return (l_csReturnStr);
}

CItemCreation::DisableScreen()
{
	VARIANT l_cSVariant;
	l_cSVariant.vt = VT_I4;

	m_cItemInfoGrid.SetEnabled (false);
	m_cResourceGrid.SetEnabled (false);
	m_cTechGrid.SetEnabled (false);
	m_cTierGrid.SetEnabled (false);

	CAppData::m_bEditMode = false;
	m_cAddItemButton.EnableWindow (false);
	m_cAddItemButton.SetWindowText ("Add Item");
	m_cRemoveTechButton.EnableWindow (false);
	m_cShowLevels.EnableWindow (false);

	m_cItemInfoGrid.SetRows (0);

	l_cSVariant.intVal = 1;
	m_cResourceGrid.SetRows (1);
	//m_cResourceGrid.SetCols (6);
	m_cResourceGrid.SetFormatString ("<Resource|^Effiency|^Need|^Skill Used|^Min|^Opt|^Cur Skill|");
	m_cResourceGrid.AddRow ("None", GRID_RESOURCE);
	m_cResourceGrid.SelectRow (1);

	l_cSVariant.intVal = 1;
	m_cTierGrid.SetRows (1);
	m_cTierGrid.AddRow ("N/A", GRID_TIERNOTAVAIL);

	l_cSVariant.intVal = 1;
	m_cTechGrid.SetRows (1);
	m_cTechGrid.AddRow ("None", GRID_TECH);

	if (CAppData::m_cTechSelectionWnd.m_cWindowState.m_bLoaded)
	{
		CAppData::m_cTechSelectionWnd.m_cShowUsable.EnableWindow (false);
	}
}

CItemCreation::EnableScreen()
{
	m_cItemInfoGrid.SetEnabled (true);
	m_cResourceGrid.SetEnabled (true);
	m_cTechGrid.SetEnabled (true);
	m_cTierGrid.SetEnabled (true);
	m_cShowLevels.EnableWindow (true);
	m_cAddItemButton.EnableWindow (true);

	if (CAppData::m_bEditMode)
	{
		m_cAddItemButton.SetWindowText ("Increase Qty");
	}
	else
	{
		m_cAddItemButton.SetWindowText ("Add Item");
	}

	if (CAppData::m_cTechSelectionWnd.m_cWindowState.m_bLoaded)
	{
		CAppData::m_cTechSelectionWnd.m_cShowUsable.EnableWindow (true);
	}
	//m_cRemoveTechButton.EnableWindow (true);
}

CItemCreation::AddTitleLine(CString a_csName, int a_iStyle)
{
	m_cItemInfoGrid.AddTitleRow (a_csName, a_iStyle, &m_cSizingTitleBox);
}

CItemCreation::AddSummaryLine(CString a_csName, int a_iStyle)
{
	m_cItemInfoGrid.AddRow (a_csName, a_iStyle, &m_cSizingBox);
}

void CItemCreation::OnRowColChangeTiergrid()
{

}

void CItemCreation::OnClickTiergrid()
{
	int l_irow = m_cTierGrid.GetRowSel ();
	CString l_csTierName = "";
	int m_iTierLevel = 1;
	CFormulaTier *l_cpFormulaTier;
	CTechTier *l_cpTechTier;
	POSITION l_Pos;
	CItemTech l_cItemTech;
	CString l_csErrorMsg;
	bool l_bInvalid = false;

	if ((l_irow > 0) && (CAppData::m_cpCurrentFormula))
	{
		l_csTierName = m_cTierGrid.GetTextMatrix (l_irow, 0);

		if (CAppData::m_cpCurrentFormula->FindFormulaTier (l_csTierName, &l_cpFormulaTier))
		{

			if ((CAppData::m_cCurrentOrderItem.m_clTechList.GetCount ()) <= l_cpFormulaTier->m_iAllowedTechniques)
			{
				l_Pos = CAppData::m_cCurrentOrderItem.m_clTechList.GetHeadPosition ();
				while (l_Pos)
				{
					l_cItemTech = CAppData::m_cCurrentOrderItem.m_clTechList.GetNext (l_Pos);
					if (!CAppData::FindTechTier (l_cItemTech.m_csCategory, l_cItemTech.m_csTechName, l_cItemTech.m_csTierName, &l_cpTechTier))
					{
						l_csErrorMsg.Format ("Error - Cannot find the tier '%s' for the technique '%s'",  l_cItemTech.m_csTierName, l_cItemTech.m_csTechName);
						l_bInvalid = true;
					}
					else
					{
						if (l_cpTechTier->m_iTierLevel > l_cpFormulaTier->m_iTierLevel)
						{
							l_csErrorMsg.Format ("This tier of the Formula '%s' cannot take '%s'.\nPlease remove it and try again", l_cpFormulaTier->m_csName, l_cpTechTier->m_csName);
							l_bInvalid = true;
						}
					}
				}

				if (l_bInvalid == false)
				{
					CAppData::m_csCurrentFormulaTierName = l_csTierName;
					CAppData::m_cCurrentOrderItem.m_csTierName = l_csTierName;
					CAppData::m_csCurrentTechTierName = CAppData::m_csCurrentFormulaTierName;
					CAppData::m_csPreferedFormulaTierName = l_csTierName;
					CAppData::m_csPreferedFormulaTier = m_iTierLevel;

					//AfxMessageBox (l_csTierName, MB_ICONEXCLAMATION );
					DisplayFormulaTiers ();
					DisplayFormula (true);

					CAppData::m_cCurrentOrderItem.m_csItemName = l_cpFormulaTier->m_csName;

					if (CAppData::m_cSkillLevelWnd.m_cWindowState.m_bVisible)
					{
						CAppData::m_cSkillLevelWnd.DisplaySkillLevels();
					}

					if (CAppData::m_bEditMode)
					{
						if (GetKeyState(VK_SHIFT)<0)
						{
							CAppData::UpdateOrderItem (CAppData::m_cCurrentOrderItem);
							CAppData::m_cOrderWnd.DisplayOrder ();
							CAppData::m_cOrderWnd.DisplayOrderItem (CAppData::m_cCurrentOrderItem.m_iId);
							CAppData::ChangeOrderState (true);
						}
						else
						{
							//CAppData::m_cOrderWnd.DisplayOrder ();
							//CAppData::m_cOrderWnd.DisplayOrderItem (0);

							//CAppData::m_cItemCreationWnd.DisplayItems();
							CAppData::m_cItemCreationWnd.ResetItemEdit();
						}
					}
				}
			}
			else
			{
				l_csErrorMsg.Format ("This tier of the Formula '%s' can only take %d techniques.\nPlease remove any excess techniques and try again", l_cpFormulaTier->m_csName, l_cpFormulaTier->m_iAllowedTechniques);
				l_bInvalid = true;
			}

			if (l_bInvalid)
			{
				AfxMessageBox (l_csErrorMsg, MB_ICONEXCLAMATION );
				DisplayFormulaTiers ();
			}
		}
	}
}

CItemCreation::DisplayFormulaTiers()
{
	CFormulaTier *l_cpFormulaTier;
	POSITION l_Pos;
	bool l_bCurrentTierFound = false;
	int l_iCurrentTierRow = 1;
	CString l_csFormulaTierName;

    CString l_csFormulaTierName_error = "";
	CString l_csFormulaTierName_first_match = "";
	int l_csFormulaTierName_first_match_cnt = 1;
	int l_csFormulaTierName_cur_pos = 1;

	CString l_csFilterName;
    CString l_csFilterNameMode;

	l_csFilterName = CAppData::m_cFormFilter;
	l_csFilterName.MakeLower ();

	m_cTierGrid.SetRows (1);
	m_cTierGrid.SetFormatString ("^Tiers / Variants");
	//m_cTierGrid.SetColWidth (0, 1600);
	m_cTierGrid.SetColWidth (0, 2400);

	if (CAppData::m_cpCurrentFormula)
	{
		l_Pos = CAppData::m_cpCurrentFormula->m_clFormulaTierList.GetHeadPosition ();

		while (l_Pos)
		{
		    l_csFormulaTierName_cur_pos++;
			l_cpFormulaTier = CAppData::m_cpCurrentFormula->m_clFormulaTierList.GetNext (l_Pos);
            l_csFormulaTierName = l_cpFormulaTier->m_csName;
            l_csFormulaTierName.MakeLower ();

            if (CAppData::m_bFormSearchMode || CAppData::m_csLastFormulaCategory != cCustom_Filter || l_csFilterName.IsEmpty() || l_csFormulaTierName.Find (l_csFilterName) != -1)
            {
                //AfxMessageBox (CAppData::m_csPreferedFormulaTierName, MB_ICONEXCLAMATION );
                //if (CAppData::m_csPreferedFormulaTierName == l_cpFormulaTier->m_csTierName)
                //{
                 //   l_csFormulaTierName_first_match_cnt = l_csFormulaTierName_cur_pos;
                 //   l_csFormulaTierName_first_match = l_cpFormulaTier->m_csTierName;
               // }
                //else
                if (l_csFormulaTierName_first_match == "")
                {
                    //AfxMessageBox (CAppData::m_csPreferedFormulaTierName + " x " + l_csFormulaTierName_first_match, MB_ICONEXCLAMATION );
                    //CAppData::m_csPreferedFormulaTierName = l_cpFormulaTier->m_csTierName;
                    l_csFormulaTierName_first_match_cnt = l_csFormulaTierName_cur_pos;
                    l_csFormulaTierName_first_match = l_cpFormulaTier->m_csTierName;

                    //l_csFormulaTierName_error.Format ("%d", l_csFormulaTierName_cur_pos);
                    //AfxMessageBox (l_csFormulaTierName_error, MB_ICONEXCLAMATION );
                    //AfxMessageBox (l_csFilterName, MB_ICONEXCLAMATION );

                }
                //AfxMessageBox (l_cpFormulaTier->m_csTierName, MB_ICONEXCLAMATION );

                m_cTierGrid.AddRow (l_cpFormulaTier->m_csTierName, GRID_TIERAVAIL, 1);
            }
            else
            {
                m_cTierGrid.AddRow (l_cpFormulaTier->m_csTierName, GRID_TIERNOTAVAIL, 1);
            }

			if (!CAppData::m_bEditMode)
			{
                //AfxMessageBox (CAppData::m_csPreferedFormulaTierName + " x " + l_cpFormulaTier->m_csTierName, MB_ICONEXCLAMATION );
			    if (l_cpFormulaTier->m_csTierName == CAppData::m_csPreferedFormulaTierName)
				{
					CAppData::m_csCurrentFormulaTierName = CAppData::m_csPreferedFormulaTierName;
					l_bCurrentTierFound = true;
					l_iCurrentTierRow = m_cTierGrid.GetRows () - 1;
					//AfxMessageBox ("Norm: " + CAppData::m_csPreferedFormulaTierName, MB_ICONEXCLAMATION );
				}
				else if (!CAppData::m_bFormSearchMode && !CAppData::m_cpFormFilterTech && CAppData::m_csLastFormulaCategory == cCustom_Filter && l_csFormulaTierName_first_match_cnt > 1 && l_cpFormulaTier->m_iTierLevel == CAppData::m_csPreferedFormulaTier && !l_bCurrentTierFound)
				{
                    //AfxMessageBox (l_cpFormulaTier->m_iTierLevel, MB_ICONEXCLAMATION );

/*
Problem ist dass dieser Code ausgefuehrt wird, auch wenn ein perfect match dabei ist.
*/

					CAppData::m_csCurrentFormulaTierName = l_csFormulaTierName_first_match;
					//CAppData::m_csPreferedFormulaTierName = l_csFormulaTierName_first_match;
					l_bCurrentTierFound = true;
					l_iCurrentTierRow = l_csFormulaTierName_first_match_cnt -1;


					//AfxMessageBox ("AB", MB_ICONEXCLAMATION );
				}

			}
			else
			{
				if (l_cpFormulaTier->m_csTierName == CAppData::m_csCurrentFormulaTierName)
				{
					l_bCurrentTierFound = true;
					l_iCurrentTierRow = m_cTierGrid.GetRows () - 1;
				}

			}

		}

		if (!l_bCurrentTierFound)
		{
			CAppData::m_csCurrentFormulaTierName = l_cpFormulaTier->m_csTierName;
			l_iCurrentTierRow = m_cTierGrid.GetRows () - 1;
		}
	}

	if (m_cTierGrid.GetRows () == 1)
	{
		m_cTierGrid.AddRow ("None", GRID_TIERNOTAVAIL);
	}

	m_cTierGrid.SelectRow (l_iCurrentTierRow);
}


void CItemCreation::OnAdditem()
{
	if (CAppData::m_bEditMode)
	{
		CAppData::m_cCurrentOrderItem.m_iQty++;
		CAppData::UpdateOrderItem (CAppData::m_cCurrentOrderItem);
		CAppData::m_cOrderWnd.DisplayOrder();
		CAppData::m_cOrderWnd.DisplayOrderItem (CAppData::m_cCurrentOrderItem.m_iId);
	}
	else
	{
		CAppData::m_cCurrentOrderItem.AssignId ();
		CAppData::m_clOrderList.AddTail (CAppData::m_cCurrentOrderItem);
		CAppData::m_iCurrentOrderId = CAppData::m_cCurrentOrderItem.m_iId;
		CAppData::m_bEditMode = true;

		CAppData::m_cCurrentOrderItem.m_iQty = 1;
		//CAppData::m_cOrderWnd.m_iQty = 1;
		CAppData::m_cOrderWnd.m_cItemQty.SetWindowText ("1");

		m_cAddItemButton.EnableWindow (true);
		m_cAddItemButton.SetWindowText ("Increase Qty");
		CAppData::m_cOrderWnd.DisplayOrder();
		CAppData::m_cOrderWnd.DisplayOrderItem (CAppData::m_cCurrentOrderItem.m_iId);
		CAppData::m_cOrderWnd.m_cDeleteButton.EnableWindow (false);
	}

	CAppData::ChangeOrderState (true);
}

void CItemCreation::OnItemexpandingFormulatree(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	//if (m_bFormulaTreeExpand)
	{
		*pResult = 0;
	}
	//else
	//{
	//	*pResult = 1;
	//}
}

BOOL CItemCreation::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	LPNMHDR pNmhdr = (LPNMHDR)lParam;
	static HBRUSH l_hFillBrush1 = CreateSolidBrush (0x00000000);
	static HBRUSH l_hFillBrush2 = CreateSolidBrush (0x00FFFFFF);

	switch (pNmhdr->code)
	{
		case NM_CUSTOMDRAW:
		{
			LPNMTVCUSTOMDRAW pCustomDraw = (LPNMTVCUSTOMDRAW)lParam;
			switch (pCustomDraw->nmcd.dwDrawStage)
			{
				case CDDS_PREPAINT:
				{
					// Need to process this case and set pResult to CDRF_NOTIFYITEMDRAW,
					// otherwise parent will never receive CDDS_ITEMPREPAINT notification. (GGH)
					*pResult = CDRF_NOTIFYITEMDRAW;
					return true;
				}

				case CDDS_ITEMPREPAINT:
				{
					switch (pCustomDraw->iLevel)
					{
						// painting all 0-level items blue,
						// and all 1-level items red (GGH)
						case 0:
							if (pCustomDraw->nmcd.lItemlParam != 5)
							{
								SelectObject (pCustomDraw->nmcd.hdc, CAppData::m_cTitleFont);
								if (pCustomDraw->nmcd.uItemState & (CDIS_SELECTED))
								{
									SelectObject (pCustomDraw->nmcd.hdc, CAppData::m_cTitleFont);
									pCustomDraw->clrText = CScheme::GetColour ("TREE_LVL1_SELECTED_FG");
									pCustomDraw->clrTextBk = CScheme::GetColour ("TREE_LVL1_SELECTED_BG");
								}
								else if (pCustomDraw->nmcd.uItemState & CDIS_HOT )
								{
									SelectObject (pCustomDraw->nmcd.hdc, CAppData::m_cTitleSelFont);
									pCustomDraw->clrText = CScheme::GetColour ("TREE_LVL1_HIGHLIGHT_FG");
									pCustomDraw->clrTextBk = CScheme::GetColour ("TREE_LVL1_HIGHLIGHT_BG");
								}
								else
								{
									SelectObject (pCustomDraw->nmcd.hdc, CAppData::m_cTitleFont);
									pCustomDraw->clrText = CScheme::GetColour ("TREE_LVL1_NORMAL_FG");
								}
								*pResult = CDRF_NEWFONT;
								return false;
							}
							break;
						case 1:
						{
							if (pCustomDraw->nmcd.uItemState & (CDIS_SELECTED))
							{
								pCustomDraw->clrText = CScheme::GetColour ("TREE_LVL2_SELECTED_FG");
								pCustomDraw->clrTextBk = CScheme::GetColour ("TREE_LVL2_SELECTED_BG");
							}
							else if (pCustomDraw->nmcd.uItemState & CDIS_HOT )
							{
								pCustomDraw->clrText = CScheme::GetColour ("TREE_LVL2_HIGHLIGHT_FG");
								pCustomDraw->clrTextBk = CScheme::GetColour ("TREE_LVL2_HIGHLIGHT_BG");
							}
							else
							{
								pCustomDraw->clrText = CScheme::GetColour ("TREE_LVL2_NORMAL_FG");
							}
							break;
						}
						case 2:
						case 3:
							if (pCustomDraw->nmcd.uItemState & (CDIS_SELECTED))
							{
								pCustomDraw->clrText = CScheme::GetColour ("TREE_LVL3_SELECTED_FG");
								pCustomDraw->clrTextBk = CScheme::GetColour ("TREE_LVL3_SELECTED_BG");
							}
							else if (pCustomDraw->nmcd.uItemState & CDIS_HOT )
							{
								pCustomDraw->clrText = CScheme::GetColour ("TREE_LVL3_HIGHLIGHT_FG");
								pCustomDraw->clrTextBk = CScheme::GetColour ("TREE_LVL3_HIGHLIGHT_BG");
							}
							else
							{
								pCustomDraw->clrText = CScheme::GetColour ("TREE_LVL3_NORMAL_FG");
							}
							break;
					}
					*pResult = CDRF_SKIPDEFAULT;
					return false;
				}


			}
		}
		break;
	}

	return CDialog::OnNotify(wParam, lParam, pResult);
}


CItemCreation::DisplayFormulaTechs()
{
	POSITION l_Pos;
	CItemTech l_cItemTech;
	CTechTier	*l_cpTechTier = NULL;

	m_cTechGrid.SetRows (1);

	l_Pos = CAppData::m_cCurrentOrderItem.m_clTechList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cItemTech = CAppData::m_cCurrentOrderItem.m_clTechList.GetNext (l_Pos);

		if (CAppData::FindTechTier (l_cItemTech.m_csCategory, l_cItemTech.m_csTechName, l_cItemTech.m_csTierName, &l_cpTechTier))
		{
			m_cTechGrid.AddRow (l_cpTechTier->m_csName, GRID_TECH);
		}
	}

	if (m_cTechGrid.GetRows () == 1)
	{
		m_cTechGrid.AddRow ("None", GRID_TIERNOTAVAIL);
		m_cRemoveTechButton.EnableWindow (false);
	}
	else
	{
		m_cRemoveTechButton.EnableWindow (true);
	}

}

CItemCreation::AddTechResources()
{
	POSITION l_Pos;
	POSITION l_ListPos;
	POSITION l_ListPrevPos;
	CItemTech l_cItemTech;
	CTechTier	*l_cpTechTier = NULL;
	POSITION l_ResourcePos;
	CItemResource *l_cpItemResource = NULL;
	CItemResource l_cListItemResource;
	CList <CItemResource, CItemResource&> l_clResourceList;
	bool l_bFound;

	m_cTechGrid.SetRows (1);

	l_Pos = CAppData::m_cCurrentOrderItem.m_clTechList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cItemTech = CAppData::m_cCurrentOrderItem.m_clTechList.GetNext (l_Pos);

		if (CAppData::FindTechTier (l_cItemTech.m_csCategory, l_cItemTech.m_csTechName, l_cItemTech.m_csTierName, &l_cpTechTier))
		{
			l_ResourcePos = l_cpTechTier->m_clResourceList.GetHeadPosition ();
			while (l_ResourcePos)
			{
				l_cpItemResource = l_cpTechTier->m_clResourceList.GetNext (l_ResourcePos);
				l_bFound = false;

				l_ListPos = l_clResourceList.GetHeadPosition ();
				while (l_ListPos)
				{
					l_ListPrevPos = l_ListPos;
					l_cListItemResource = l_clResourceList.GetNext (l_ListPos);
					if (l_cListItemResource.m_csName == l_cpItemResource->m_csName)
					{
						l_cListItemResource.m_iMinAmt += l_cpItemResource->m_iMinAmt;
						l_clResourceList.SetAt (l_ListPrevPos, l_cListItemResource);
						l_ListPos = NULL;
						l_bFound = true;
					}
				}

				if (!l_bFound)
				{
					l_clResourceList.AddTail (*l_cpItemResource);
				}
			}
		}
	}

	l_ListPos = l_clResourceList.GetHeadPosition ();
	while (l_ListPos)
	{
		l_cListItemResource = l_clResourceList.GetNext (l_ListPos);
		AddComponents (&l_cListItemResource , GRID_RESOURCE);
	}
}

void CItemCreation::OnRemovetech()
{
	POSITION l_Pos;
	int l_iOffset = m_cTechGrid.GetRowSel ();

	if (l_iOffset > 0)
	{
		if (m_cTechGrid.GetTextMatrix (l_iOffset, 0) != "None")
		{
			l_Pos = CAppData::m_cCurrentOrderItem.m_clTechList.GetHeadPosition ();
			while (l_iOffset-- != 1)
			{
				CAppData::m_cCurrentOrderItem.m_clTechList.GetNext (l_Pos);
			}

			if (l_Pos)
			{
				CAppData::m_cCurrentOrderItem.m_clTechList.RemoveAt (l_Pos);
			}

			DisplayFormula (false);
			DisplayFormulaTechs ();
			CAppData::m_cTechSelectionWnd.DrawTechList ();

			if (CAppData::m_bEditMode)
			{
				CAppData::UpdateOrderItem (CAppData::m_cCurrentOrderItem);
				CAppData::m_cOrderWnd.DisplayOrderItem (CAppData::m_cCurrentOrderItem.m_iId);
				CAppData::ChangeOrderState (true);
			}
		}
	}
}

CItemCreation::SelectFormula(COrderItem l_cOrderItem)
{
	if (CAppData::FindFormula (l_cOrderItem.m_csCategory, l_cOrderItem.m_csFormulaName, &CAppData::m_cpCurrentFormula))
	{
		CAppData::m_cCurrentOrderItem = l_cOrderItem;

		if (CAppData::m_csLastFormulaCategory != cCustom_Filter)
		{
			CAppData::m_csLastFormulaCategory = CAppData::m_cpCurrentFormula->m_csCategory;
			SelectCategory (CAppData::m_cpCurrentFormula->m_csCategory);
		}
		else
		{
			// Find in list
			if (!m_cFormulaTree.FindTreeItem (l_cOrderItem.m_csFormulaName, 0))
			{
				CAppData::m_csLastFormulaCategory = CAppData::m_cpCurrentFormula->m_csCategory;
			}
		}

		CAppData::m_csCurrentFormulaTierName = l_cOrderItem.m_csTierName;
		DrawFormulaList ();

		EnableScreen ();

		DisplayFormula (true);
		DisplayFormulaTiers ();

	}

}

void CItemCreation::OnOptionsSnapshotwindow()
{
	CAppData::SetFormulaWindowState ();
}

void CItemCreation::OnOptionsRestorewindow()
{
	CAppData::GetFormulaWindowState ();
}

CItemCreation::ResetCurrentFormula()
{
	CFormulaTier *l_cpFormulaTier;

	if (CAppData::m_cpCurrentFormula)
	{
		CAppData::m_csCurrentFormulaTierName = CAppData::FindBestMatchingTier (CAppData::m_cpCurrentFormula, (CString) "");

		CAppData::m_cCurrentOrderItem.m_csItemName = CAppData::m_cpCurrentFormula->m_csName;
		CAppData::m_cCurrentOrderItem.m_csCategory = CAppData::m_cpCurrentFormula->m_csCategory;
		CAppData::m_cCurrentOrderItem.m_csFormulaName = CAppData::m_cpCurrentFormula->m_csName;
		CAppData::m_cCurrentOrderItem.m_csOrderGroup = CAppData::m_cpCurrentFormula->m_csCategory;
		CAppData::m_cCurrentOrderItem.m_clTechList.RemoveAll ();
		CAppData::m_cCurrentOrderItem.m_iQty = 1;
		CAppData::m_csCurrentTechTierName = CAppData::m_csCurrentFormulaTierName;

		EnableScreen ();

		DisplayFormulaTiers ();
		CAppData::m_cCurrentOrderItem.m_csTierName = CAppData::m_csCurrentFormulaTierName;


		if (CAppData::m_cpCurrentFormula->FindFormulaTier (CAppData::m_csCurrentFormulaTierName, &l_cpFormulaTier))
		{
			CAppData::m_cCurrentOrderItem.m_csItemName = l_cpFormulaTier->m_csName;
		}

		DisplayFormula (true);

		if (CAppData::m_cSkillLevelWnd.m_cWindowState.m_bVisible)
		{
			CAppData::m_cSkillLevelWnd.DisplaySkillLevels();
		}
	}
}

void CItemCreation::OnShowlevels()
{
	CAppData::SetSkillLevelWindow (true);

	CAppData::m_cSkillLevelWnd.DisplaySkillLevels ();
}

CItemCreation::ResizeResourceGrid()
{
	if (m_cWindowState.m_bLoaded)
	{
		int l_iResize;

		if (!CAppData::m_bAutoShrink)
		{
			l_iResize = CAppData::ConvertGridWidthToScreen ((CAppData::m_iItemResourceSize - 4) * m_cResourceGrid.GetRowHeight (0));
		}
		else if (CAppData::m_iItemResourceSize == 0)
		{
			l_iResize = CAppData::ConvertGridWidthToScreen (m_cResourceGrid.GetGridMinHeight (-2, 20, 5));
		}
		else
		{
			l_iResize = CAppData::ConvertGridWidthToScreen (m_cResourceGrid.GetGridMinHeight (-2, CAppData::m_iItemResourceSize - 4, 5));
		}

		m_iResourceListDelta = l_iResize;
		m_iResourceListDeltaZero = 0;
		m_iResourceListDeltaReverse = 0 - l_iResize;

		int l_iTResize = CAppData::ConvertGridWidthToScreen (m_cTierGrid.GetGridMinHeight (-1, 9, 7));

		m_iTierListDelta = l_iTResize;
		m_iTierListDeltaZero = 0;
		m_iTierListDeltaReverse = 0 - l_iTResize;

		m_iCombinedDelta = m_iResourceListDelta + m_iTierListDelta;


	}
}

CItemCreation::AddTemporaryFormulas()
{
	HTREEITEM l_TreeItem = m_cFormulaTree.GetSelectedItem ();
	CFormulaTier *l_cpFormulaTier;

	if (CAppData::m_cpCurrentFormula)
	{
		if (CAppData::m_cpCurrentFormula->FindFormulaTier (CAppData::m_csCurrentFormulaTierName, &l_cpFormulaTier))
		{
			if (m_PrevFormulaTree)
			{
				if ((m_csPrevFormulaName != CAppData::m_cpCurrentFormula->m_csName) ||
					 (m_csPrevFormulaTierName != CAppData::m_csCurrentFormulaTierName))
				{
					while (m_cFormulaTree.GetItemLevel (l_TreeItem) >= 3)
					{
						l_TreeItem = m_cFormulaTree.GetParentItem (l_TreeItem);
					}

					while (m_cFormulaTree.GetChildItem (m_PrevFormulaTree))
					{
						m_cFormulaTree.DeleteItem (m_cFormulaTree.GetChildItem (m_PrevFormulaTree));
					}

					AddSubFormula (l_TreeItem, l_cpFormulaTier, CAppData::m_csCurrentFormulaTierName);
					m_PrevFormulaTree = l_TreeItem;
					m_csPrevFormulaTierName = CAppData::m_csCurrentFormulaTierName;
					m_csPrevFormulaName = CAppData::m_cpCurrentFormula->m_csName;
				}
			}
			else
			{
				AddSubFormula (l_TreeItem, l_cpFormulaTier, CAppData::m_csCurrentFormulaTierName);
				m_PrevFormulaTree = l_TreeItem;
				m_csPrevFormulaTierName = CAppData::m_csCurrentFormulaTierName;
				m_csPrevFormulaName = CAppData::m_cpCurrentFormula->m_csName;
			}
		}
	}

}

CItemCreation::AddSubFormula(HTREEITEM a_cTreeItem, CFormulaTier *a_cpParentFormulaTier, CString &a_csParentTierName)
{
	CItemResource *l_cpItemResource;
	CFormula *l_cpResourceFormula;
	CFormulaTier *l_cpResourceFormulaTier;
	POSITION l_Pos;
	HTREEITEM l_NewTreeItem;

	l_Pos = a_cpParentFormulaTier->m_clResourceList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpItemResource = a_cpParentFormulaTier->m_clResourceList.GetNext (l_Pos);

		if (CAppData::FindResourceFormulaTier (l_cpItemResource->m_csName, &l_cpResourceFormula, &l_cpResourceFormulaTier))
		{
			l_NewTreeItem = m_cFormulaTree.InsertItem (l_cpItemResource->m_csName, l_cpResourceFormula->m_iIcon, l_cpResourceFormula->m_iIcon, a_cTreeItem, TVI_LAST);
			AddSubFormula (l_NewTreeItem, l_cpResourceFormulaTier, l_cpResourceFormulaTier->m_csTierName);
		}
	}

	m_bFormulaTreeExpand = true;
	m_cFormulaTree.Expand (a_cTreeItem, TVE_EXPAND);
	m_bFormulaTreeExpand = false;
}

CItemCreation::AddToResources(CItemResource *a_cpResource, int a_iStyle, int a_iBaseQty, int a_iSkillAdjust)
{
	CString l_csStr;
	HTREEITEM l_TreeItem = m_cFormulaTree.GetSelectedItem ();
	int l_iLevel;
	CString l_csResourceName;
	bool l_bAddBase = true;
	CFormula *l_cpResourceFormula;
	CFormulaTier *l_cpResourceFormulaTier;
	POSITION l_Pos;
	CItemResource *l_cpItemResource;
	int l_iBaseQty;
	int l_iProfileSkill;
	int l_iProfileQty;
	int l_iProfileEffiency;

	l_iLevel = m_cFormulaTree.GetItemLevel (l_TreeItem);
	while ((l_iLevel > 2) && (l_bAddBase))
	{
		l_csResourceName = m_cFormulaTree.GetItemText (l_TreeItem);
		if (l_csResourceName == a_cpResource->m_csName)
		{
			l_bAddBase = false;
		}
		else
		{
			l_TreeItem = m_cFormulaTree.GetParentItem (l_TreeItem);
			l_iLevel--;
		}
	}

	if (l_bAddBase)
	{
		if (CAppData::m_cpCurrentProfile)
		{
			l_iProfileSkill = CAppData::m_cpCurrentProfile->FindCraftSkill (a_cpResource->m_csSkill);
			l_iProfileQty = CAppData::CalculateEfficiency (a_cpResource, CAppData::m_cpCurrentProfile, a_iSkillAdjust);
			l_iProfileEffiency = CAppData::CalculateEfficiencyPercentage (a_cpResource, CAppData::m_cpCurrentProfile, a_iSkillAdjust);

			if (l_iProfileEffiency > -1)
			{
				l_csStr.Format ("%s\t%d%%\t%d\t%s\t%d\t%d\t%d", a_cpResource->m_csName, l_iProfileEffiency, l_iProfileQty * a_iBaseQty, a_cpResource->m_csSkill, a_cpResource->m_iMinLvl + a_iSkillAdjust, a_cpResource->m_iOptLvl + a_iSkillAdjust, l_iProfileSkill);
			}
			else
			{
				if (a_cpResource->m_iUnits == 0)
				{
					l_csStr.Format ("%s\tToo Low\t%d->%d\t%s\t%d\t%d\t%d", a_cpResource->m_csName, (a_cpResource->m_iMinAmt * a_iBaseQty), (a_cpResource->m_iOptAmt * a_iBaseQty), a_cpResource->m_csSkill, a_cpResource->m_iMinLvl + a_iSkillAdjust, a_cpResource->m_iOptLvl + a_iSkillAdjust, l_iProfileSkill);
				}
				else
				{
					l_csStr.Format ("%s\tToo Low\t%d->%d\t%s\t%d\t%d\t%d", a_cpResource->m_csName, (a_cpResource->m_iMinAmt * a_iBaseQty * a_cpResource->m_iUnits), (a_cpResource->m_iOptAmt * a_iBaseQty * a_cpResource->m_iUnits), a_cpResource->m_csSkill, a_cpResource->m_iMinLvl + a_iSkillAdjust, a_cpResource->m_iOptLvl + a_iSkillAdjust, l_iProfileSkill);
				}
			}
			m_cResourceGrid.AddRow (l_csStr, a_iStyle);
		}
	}
	else
	{
		if (CAppData::FindResourceFormulaTier (a_cpResource->m_csName, &l_cpResourceFormula, &l_cpResourceFormulaTier))
		{
			l_iProfileQty = CAppData::CalculateEfficiency (a_cpResource, CAppData::m_cpCurrentProfile, a_iSkillAdjust);

			if ((l_iProfileQty % l_cpResourceFormula->m_iBatchQty) == 0)
			{
				l_iProfileQty = (l_iProfileQty / l_cpResourceFormula->m_iBatchQty);
			}
			else
			{
				l_iProfileQty = (l_iProfileQty / l_cpResourceFormula->m_iBatchQty) + 1;
			}

			l_iBaseQty = l_iProfileQty * a_iBaseQty;

			l_Pos = l_cpResourceFormulaTier->m_clResourceList.GetHeadPosition ();
			while (l_Pos)
			{
				l_cpItemResource = l_cpResourceFormulaTier->m_clResourceList.GetNext (l_Pos);

				if (l_iProfileQty == 0)
				{
					l_iProfileQty = a_cpResource->m_iMinAmt;
				}

				AddToResources (l_cpItemResource, a_iStyle, l_iProfileQty * a_iBaseQty);
			}
		}
	}


}

CItemCreation::AddBaseResources(CItemResource *a_cpResource, int a_iStyle, int a_iBaseQty, int a_iSkillAdjust)
{
	CString l_csStr;
	CString l_csResourceName;
	bool l_bAddBase = true;
	CFormula *l_cpResourceFormula;
	CFormulaTier *l_cpResourceFormulaTier;
	POSITION l_Pos;
	CItemResource *l_cpItemResource;
	int l_iBaseQty;
	int l_iProfileSkill;
	int l_iProfileQty;
	int l_iProfileEffiency;
	int l_iExistingRow;
	int l_iExistingQty;

	if (CAppData::FindResourceFormulaTier (a_cpResource->m_csName, &l_cpResourceFormula, &l_cpResourceFormulaTier))
	{
		l_iProfileQty = CAppData::CalculateEfficiency (a_cpResource, CAppData::m_cpCurrentProfile, a_iSkillAdjust);

		if ((l_iProfileQty % l_cpResourceFormula->m_iBatchQty) == 0)
		{
			l_iProfileQty = (l_iProfileQty / l_cpResourceFormula->m_iBatchQty);
		}
		else
		{
			l_iProfileQty = (l_iProfileQty / l_cpResourceFormula->m_iBatchQty) + 1;
		}

		l_iBaseQty = l_iProfileQty * a_iBaseQty;

		l_Pos = l_cpResourceFormulaTier->m_clResourceList.GetHeadPosition ();
		while (l_Pos)
		{
			l_cpItemResource = l_cpResourceFormulaTier->m_clResourceList.GetNext (l_Pos);

			if (l_iProfileQty == 0)
			{
				l_iProfileQty = a_cpResource->m_iMinAmt;
			}

			AddBaseResources (l_cpItemResource, a_iStyle, l_iProfileQty * a_iBaseQty);
		}
	}
	else
	{
		l_iProfileSkill = CAppData::m_cpCurrentProfile->FindCraftSkill (a_cpResource->m_csSkill);
		l_iProfileQty = CAppData::CalculateEfficiency (a_cpResource, CAppData::m_cpCurrentProfile, a_iSkillAdjust);
		l_iProfileEffiency = CAppData::CalculateEfficiencyPercentage (a_cpResource, CAppData::m_cpCurrentProfile, a_iSkillAdjust);

		if (l_iProfileEffiency > -1)
		{
			l_iProfileQty *= a_iBaseQty;
			l_csStr.Format ("%s\t%d%%\t%d\t%s\t%d\t%d\t%d", a_cpResource->m_csName, l_iProfileEffiency, l_iProfileQty, a_cpResource->m_csSkill, a_cpResource->m_iMinLvl + a_iSkillAdjust, a_cpResource->m_iOptLvl + a_iSkillAdjust, l_iProfileSkill);
		}
		else
		{
			l_iProfileQty = a_cpResource->m_iMinAmt * a_iBaseQty;
			l_csStr.Format ("%s\tToo Low\t%d->%d\t%s\t%d\t%d\t%d", a_cpResource->m_csName, l_iProfileQty, (a_cpResource->m_iOptAmt * a_iBaseQty), a_cpResource->m_csSkill, a_cpResource->m_iMinLvl + a_iSkillAdjust, a_cpResource->m_iOptLvl + a_iSkillAdjust, l_iProfileSkill);
		}

		l_iExistingRow = m_cResourceGrid.FindRow (a_cpResource->m_csName, 0);

		if (l_iExistingRow == -1)
		{
			m_cResourceGrid.AddRow (l_csStr, a_iStyle);
		}
		else
		{
			l_iExistingQty = atoi (m_cResourceGrid.GetTextMatrix (l_iExistingRow, 2));
			l_csStr.Format ("%d", l_iExistingQty + l_iProfileQty);
			m_cResourceGrid.SetTextMatrix (l_iExistingRow, 2, l_csStr);
		}
	}


}

CItemCreation::AddComponents(CItemResource *a_cpResource, int a_iStyle)
{
	CString l_csStr;

	l_csStr.Format ("%s\t-\t%d\t(technique)\t-\t-\t-", a_cpResource->m_csName, a_cpResource->m_iMinAmt);
	m_cResourceGrid.AddRow (l_csStr, a_iStyle);
}


CItemCreation::RedrawOn()
{
	RedrawCount++;
}

CItemCreation::RedrawOff()
{
	RedrawCount--;
}

void CItemCreation::OnPaint()
{
	if (RedrawCount<0) return;

	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here

	// Do not call CDialog::OnPaint() for painting messages
}

void CItemCreation::OnOK()
{
	EndEditCell (true);
}

CItemCreation::DisplayProfiles()
{
	CProfile *l_cpProfile;
	POSITION l_Pos;
	int l_iOffset = 0;

	CAppData::ClearComboBox (m_cProfileSelecter);

	l_Pos = CAppData::m_clProfileList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpProfile = CAppData::m_clProfileList.GetNext (l_Pos);
		if (l_cpProfile != CAppData::m_cpTemplateProfile)
		{
			m_cProfileSelecter.AddString (l_cpProfile->m_csProfileServer + ":" + l_cpProfile->m_csProfileName);

			if (l_cpProfile == CAppData::m_cpCurrentProfile)
			{
				l_iOffset = m_cProfileSelecter.GetCount () - 1;
			}
		}
	}

	m_cProfileSelecter.SetCurSel (l_iOffset);
	//CAppData::FindProfile (CAppData::m_csCurrentProfile, CAppData::m_csCurrentProfileType, &CAppData::m_cpCurrentProfile);
}

CItemCreation::DisplayItems()
{
	COrderItem l_cOrderItem;
	POSITION l_Pos;
	int l_iOffset = 0;

	CAppData::ClearComboBox (m_cItemSelecter);
	m_cItemSelecter.AddString ("None");

	l_Pos = CAppData::m_clOrderList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cOrderItem = CAppData::m_clOrderList.GetNext (l_Pos);
		m_cItemSelecter.AddString (l_cOrderItem.m_csItemName);

		if (l_cOrderItem.m_iId == CAppData::m_cCurrentOrderItem.m_iId)
		{
			l_iOffset = m_cItemSelecter.GetCount () - 1;
		}
	}

	m_cItemSelecter.SetCurSel (l_iOffset);
}

void CItemCreation::OnSelchangeProfileselecter()
{
	CString l_csCurProfile;
	CString l_csProfileName;
	CString l_csProfileServer;
	int l_iOffset;

	m_cProfileSelecter.GetWindowText (l_csCurProfile);
	CAppData::m_cProfileWnd.SelectProfile (l_csCurProfile);

	l_iOffset = l_csCurProfile.Find (':', 0);
	if (l_iOffset > 0)
	{
		l_csProfileServer = l_csCurProfile.Left (l_iOffset);
		l_csProfileName = l_csCurProfile.Mid (l_iOffset + 1);

		if (CAppData::FindProfile (l_csProfileName, l_csProfileServer, &CAppData::m_cpCurrentProfile))
		{

			CAppData::m_csCurrentProfile = CAppData::m_cpCurrentProfile->m_csProfileName;
			CAppData::m_csCurrentProfileType = CAppData::m_cpCurrentProfile->m_csProfileType;
			DisplayFormula (false);
		}
	}
}

void CItemCreation::OnOptionsResourcebreakdownShowformularesource()
{
	CAppData::m_iShowResourceMode = 0;
	DrawFormulaList();
	DisplayFormula (false);

	UpdateResourceBreakdownMenu();
}

void CItemCreation::OnOptionsShowsubcomponents()
{
	CAppData::m_iShowResourceMode = 1;
	DrawFormulaList();
	DisplayFormula (false);
	AddTemporaryFormulas ();

	UpdateResourceBreakdownMenu();
}

void CItemCreation::OnOptionsShowbaseresource()
{
	CAppData::m_iShowResourceMode = 2;
	DrawFormulaList();
	DisplayFormula (false);

	UpdateResourceBreakdownMenu();
}

void CItemCreation::OnOptionsAutoexpandOff()
{
	CAppData::m_iExpandFormulaMode = 0;
	UpdateAutoExpandMenu();
}

void CItemCreation::OnOptionsAutoexpandCurrentcategory()
{
	CAppData::m_iExpandFormulaMode = 1;
	UpdateAutoExpandMenu();
}

void CItemCreation::OnOptionsAutoexpandAllcategories()
{
	CAppData::m_iExpandFormulaMode = 2;
	UpdateAutoExpandMenu();
}

void CItemCreation::OnCollapse()
{
	HTREEITEM l_TreeItem;

	l_TreeItem = m_cFormulaTree.GetRootItem ();
	while (l_TreeItem)
	{
		m_cFormulaTree.Expand (l_TreeItem, TVE_COLLAPSE);
		l_TreeItem = m_cFormulaTree.GetNextSiblingItem (l_TreeItem);
	}
}

CItemCreation::UpdateResourceBreakdownMenu()
{
	CMenu *l_pMenu;
	l_pMenu = GetMenu ();
	if (l_pMenu)
	{
		CAppData::SetMenuItem(l_pMenu, ID_OPTIONS_RESOURCEBREAKDOWN_SHOWFORMULARESOURCE, CAppData::m_iShowResourceMode == 0);
		CAppData::SetMenuItem(l_pMenu, ID_OPTIONS_SHOWSUBCOMPONENTS, CAppData::m_iShowResourceMode == 1);
		CAppData::SetMenuItem(l_pMenu, ID_OPTIONS_SHOWBASERESOURCE, CAppData::m_iShowResourceMode == 2);
	}
}

CItemCreation::UpdateAutoExpandMenu()
{
	CMenu *l_pMenu;
	l_pMenu = GetMenu ();
	if (l_pMenu)
	{
		CAppData::SetMenuItem(l_pMenu, ID_OPTIONS_AUTOEXPAND_OFF, CAppData::m_iExpandFormulaMode == 0);
		CAppData::SetMenuItem(l_pMenu, ID_OPTIONS_AUTOEXPAND_CURRENTCATEGORY, CAppData::m_iExpandFormulaMode == 1);
		CAppData::SetMenuItem(l_pMenu, ID_OPTIONS_AUTOEXPAND_ALLCATEGORIES, CAppData::m_iExpandFormulaMode == 2);
	}
}

CItemCreation::UpdateResourceGridMenu()
{
	CMenu *l_pMenu;
	l_pMenu = GetMenu ();
	if (l_pMenu)
	{
		CAppData::SetMenuItem(l_pMenu, ID_OPTIONS_RESOURCEGRID_AUTOSHRINK, CAppData::m_bAutoShrink);
		CAppData::SetMenuItem(l_pMenu, ID_OPTIONS_RESOURCEGRID_LIMITTO4ROWS, CAppData::m_iItemResourceSize == 4);
		CAppData::SetMenuItem(l_pMenu, ID_OPTIONS_RESOURCEGRID_LIMITTO8ROWS, CAppData::m_iItemResourceSize == 8);
		CAppData::SetMenuItem(l_pMenu, ID_OPTIONS_RESOURCEGRID_LIMITTO12ROWS, CAppData::m_iItemResourceSize == 12);
		CAppData::SetMenuItem(l_pMenu, ID_OPTIONS_RESOURCEGRID_UNLIMITED, CAppData::m_iItemResourceSize == 16);
	}

	ResizeGrids ();
}

CString CItemCreation::GetCategory()
{
	int l_iPos = m_cFilterList.GetSelectionMark ();

	if (l_iPos >= 0)
	{
		return (m_cFilterList.GetItemText (l_iPos, 0));
	}
	else
	{
		return ("");
	}
}

void CItemCreation::OnClickFilterlist(NMHDR* pNMHDR, LRESULT* pResult)
{
	CAppData::m_csLastFormulaCategory = GetCategory ();

	CAppData::m_cpCurrentFormula = NULL;
	DrawFormulaList ();

	if (CAppData::m_cpCurrentFormula)
	{
		//DisplayFormula (false);
	}

	*pResult = 0;
}

void CItemCreation::OnKeydownFilterlist(NMHDR* pNMHDR, LRESULT* pResult)
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;

	*pResult = 1;
}

void CItemCreation::OnHelpHelp()
{
	CAppData::LaunchWebLink ((CString) "formulawindow");
}

void CItemCreation::OnExpand()
{
	HTREEITEM l_TreeItem;

	l_TreeItem = m_cFormulaTree.GetRootItem ();
	while (l_TreeItem)
	{
		m_cFormulaTree.Expand (l_TreeItem, TVE_EXPAND);
		l_TreeItem = m_cFormulaTree.GetNextSiblingItem (l_TreeItem);
	}
}

CItemCreation::SelectCurrentFormula(HTREEITEM l_TreeItem)
{
	HTREEITEM l_ParentTreeItem;
	CString l_csCategory;
	CString l_csFormula;
	int l_iLevel = 0;
	bool l_bFormulaMatch;

	if (m_bFormulaTreeExpand == false)
	{
		CAppData::m_bEditMode = false;
		l_iLevel = m_cFormulaTree.GetItemLevel (l_TreeItem);
		m_cItemSelecter.SetCurSel (0);

		if (l_iLevel == 1)
		{
			CAppData::m_cpCurrentFormula = NULL;
			DisableScreen ();
			CAppData::m_cTechSelectionWnd.DrawTechList ();
			CAppData::m_cTechSelectionWnd.DisableScreen ();

			m_cFormulaTree.Expand (l_TreeItem, TVE_EXPAND);

			if (CAppData::m_iExpandFormulaMode == 1)
			{

				l_ParentTreeItem = m_cFormulaTree.GetRootItem ();
				while (l_ParentTreeItem)
				{
					if (l_ParentTreeItem != l_TreeItem)
					{
						m_cFormulaTree.Expand (l_ParentTreeItem, TVE_COLLAPSE);
					}

					l_ParentTreeItem = m_cFormulaTree.GetNextSiblingItem (l_ParentTreeItem);
				}
			}
		}
		else
		{
			if (l_iLevel == 2)
			{
				l_csCategory = GetCategory ();
				l_csFormula = m_cFormulaTree.GetItemText (l_TreeItem);
				l_bFormulaMatch = false;

				if (CAppData::m_cpCurrentFormula)
				{
					l_bFormulaMatch = CAppData::m_cpCurrentFormula->m_csName == l_csFormula;
				}

				if (!l_bFormulaMatch)
				{
					if (CAppData::FindFormula (l_csCategory, l_csFormula, &CAppData::m_cpCurrentFormula))
					{
						ResetCurrentFormula ();
					}
					else
					{
						CAppData::m_cpCurrentFormula = NULL;
						DisableScreen ();
						CAppData::m_cTechSelectionWnd.DisableScreen ();
					}
				}
				else
				{
					DisplayFormula (false);
				}

			}
			else
			{
				if (l_iLevel >= 3)
				{
					if (CAppData::m_iShowResourceMode == 1)
					{
						AddTemporaryFormulas	();
					}

					DisplayFormula (false);
				}
				else
				{
					CAppData::m_cpCurrentFormula = NULL;
					DisableScreen ();
					CAppData::m_cTechSelectionWnd.DisableScreen ();
				}
			}
		}
	}

}

void CItemCreation::OnDblClickResourcegrid()
{
	StartEditCell();
}

void CItemCreation::OnScrollResourcegrid()
{
	EndEditCell (false);
}

CItemCreation::StartEditCell()
{
	CRect l_cRect;

	if (!m_cSkillEdit.IsWindowVisible ())
	{
		if (CAppData::m_cpCurrentProfile)
		{
			if (CAppData::m_cpCurrentProfile->m_csProfileType != cAppData_Profile_Defaults)
			{
				m_iResourceGridEditRow = m_cResourceGrid.GetMouseRow ();
				m_iResourceGridEditCol = m_cResourceGrid.GetMouseCol ();

				if ((m_iResourceGridEditRow > 0) && (m_iResourceGridEditCol == 6))
				{
					l_cRect = m_cResourceGrid.GetCellRect (m_iResourceGridEditRow, m_iResourceGridEditCol);
					m_cSkillEdit.SetWindowText (m_cResourceGrid.GetTextMatrix (m_iResourceGridEditRow, m_iResourceGridEditCol));
					m_cSkillEdit.SetWindowPos  (NULL, l_cRect.left, l_cRect.top, l_cRect.Width(), l_cRect.Height(), NULL);
					m_cSkillEdit.ShowWindow (true);
					m_cSkillEdit.SetSel (0, -1);
					m_cSkillEdit.SetFocus();
				}
			}
		}
	}
}

CItemCreation::EndEditCell(bool a_bSuccess)
{
	CString l_csCell;
	CString l_csSkill;

	m_cSkillEdit.GetWindowText (l_csCell);
	if (m_cSkillEdit.IsWindowVisible ())
	{
		if (a_bSuccess)
		{
			if (CAppData::m_cpCurrentProfile)
			{
				if (CAppData::m_cpCurrentProfile->m_csProfileType != cAppData_Profile_Defaults)
				{
					l_csSkill = m_cResourceGrid.GetTextMatrix (m_iResourceGridEditRow, 3);
					if (CAppData::m_cpCurrentProfile->UpdateCraftSkill (l_csSkill, atoi (l_csCell)))
					{
						CAppData::SetProfilesChangeState (true);
						DisplayFormula (false);
						CAppData::m_cProfileWnd.DrawProfileTree ();
						m_cResourceGrid.SetTextMatrix (m_iResourceGridEditRow, m_iResourceGridEditCol, l_csCell);
					}
				}
			}
		}

		m_cSkillEdit.ShowWindow (false);
	}
}

void CItemCreation::OnKillfocusSkilledit()
{
	EndEditCell(false);
}


void CItemCreation::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);
}

void CItemCreation::OnWindowPosChanging( WINDOWPOS* lpwndpos )
{
	CRect l_cRect;
	this->GetWindowRect (l_cRect);

	m_cWindowState.SnapToWnd (lpwndpos, &l_cRect, NULL, CAppData::m_iStickyStrength);
	m_cWindowState.SnapToWnd (lpwndpos, &l_cRect, CAppData::m_cpHCCDlg, CAppData::m_iStickyStrength);

	if (CAppData::m_cOrderWnd.m_cWindowState.m_bVisible)
	{
		m_cWindowState.SnapToWnd (lpwndpos, &l_cRect, &CAppData::m_cOrderWnd, CAppData::m_iStickyStrength);
	}

	if (CAppData::m_cTechSelectionWnd.m_cWindowState.m_bVisible)
	{
		m_cWindowState.SnapToWnd (lpwndpos, &l_cRect, &CAppData::m_cTechSelectionWnd, CAppData::m_iStickyStrength);
	}

	if (CAppData::m_cComponentWnd.m_cWindowState.m_bVisible)
	{
		m_cWindowState.SnapToWnd (lpwndpos, &l_cRect, &CAppData::m_cComponentWnd, CAppData::m_iStickyStrength);
	}

	if (CAppData::m_cReportWnd.m_cWindowState.m_bVisible)
	{
		m_cWindowState.SnapToWnd (lpwndpos, &l_cRect, &CAppData::m_cReportWnd, CAppData::m_iStickyStrength);
	}

	if (CAppData::m_cProfileWnd.m_cWindowState.m_bVisible)
	{
		m_cWindowState.SnapToWnd (lpwndpos, &l_cRect, &CAppData::m_cProfileWnd, CAppData::m_iStickyStrength);
	}

	CDialog::OnWindowPosChanging(lpwndpos);
}

void CItemCreation::OnSelchangeItemselecter()
{
	COrderItem l_cOrderItem;
	int l_iOffset;
	POSITION l_Pos;

	l_iOffset = m_cItemSelecter.GetCurSel ();

	if (l_iOffset == CB_ERR)
	{
	}
	else if (l_iOffset == 0)
	{
		CAppData::m_bEditMode = false;
		m_cAddItemButton.EnableWindow (true);
		m_cAddItemButton.SetWindowText ("Add Item");
	}
	else
	{
		l_Pos = CAppData::m_clOrderList.GetHeadPosition ();
		while (l_iOffset--)
		{
			l_cOrderItem = CAppData::m_clOrderList.GetNext (l_Pos);
		}

		CAppData::m_cCurrentOrderItem = l_cOrderItem;
		CAppData::m_iCurrentOrderId = l_cOrderItem.m_iId;

		CAppData::m_bEditMode = true;
		m_cAddItemButton.EnableWindow (true);
		m_cAddItemButton.SetWindowText ("Increase Qty");

		CAppData::m_cOrderWnd.DisplayOrderItem (l_cOrderItem.m_iId);
		CAppData::m_cItemCreationWnd.SelectFormula (l_cOrderItem);

	}

	if (CAppData::m_cSkillLevelWnd.m_cWindowState.m_bVisible)
	{
		CAppData::m_cSkillLevelWnd.DisplaySkillLevels();
	}
}

void CItemCreation::OnWindowAlwaysontop()
{
	m_cWindowState.m_bOnTop = !m_cWindowState.m_bOnTop;

	CMenu *l_pMenu;
	l_pMenu = GetMenu ();
	if (l_pMenu)
	{
		CAppData::SetMenuItem(l_pMenu, ID_WINDOW_ALWAYSONTOP, m_cWindowState.m_bOnTop);
	}

	if (m_cWindowState.m_bOnTop)
	{
		this->SetWindowPos (&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
	}
	else
	{
		this->SetWindowPos (&CWnd::wndNoTopMost , 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
	}

}

BOOL CItemCreation::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	int l_iTop = m_cItemInfoGrid.GetTopRow ();

	if ((zDelta > 0) && (l_iTop > 0))
	{
		l_iTop--;
	}
	else if (zDelta < 0)
	{
		l_iTop++;
	}

	if (l_iTop < m_cItemInfoGrid.GetRows ())
	{
		m_cItemInfoGrid.SetTopRow (l_iTop);
	}

	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

void CItemCreation::OnOptionsResourcegridLimitto4rows()
{
	CAppData::m_iItemResourceSize	= 4;
	UpdateResourceGridMenu();
}

void CItemCreation::OnOptionsResourcegridLimitto8rows()
{
	CAppData::m_iItemResourceSize	= 8;
	UpdateResourceGridMenu();
}

void CItemCreation::OnOptionsResourcegridLimitto12rows()
{
	CAppData::m_iItemResourceSize	= 12;
	UpdateResourceGridMenu();
}

void CItemCreation::OnOptionsResourcegridUnlimited()
{
	CAppData::m_iItemResourceSize	= 16;
	UpdateResourceGridMenu();
}

void CItemCreation::OnOptionsResourcegridAutoshrink()
{
	CAppData::m_bAutoShrink	= !CAppData::m_bAutoShrink;
	UpdateResourceGridMenu();
}

void CItemCreation::OnSearchByname()
{
	CInputDialog l_cInputDialog (this);

	l_cInputDialog.m_csInputMsg = "Search for";
	l_cInputDialog.m_csTitleMsg = "Filter By Name";
	if (l_cInputDialog.DoModal () == IDOK)
	{
		CAppData::m_cFormFilter = l_cInputDialog.m_csInput;
		CAppData::m_cFormClassFilter = "";
		CAppData::m_cpFormFilterTech = NULL;
		CAppData::m_csLastFormulaCategory = cCustom_Filter;
		CAppData::m_cpCurrentFormula = NULL;
		CAppData::m_bEditMode = false;
		CAppData::m_bFormSearchMode = false;
		CAppData::m_cItemCreationWnd.SelectCategory (cCustom_Filter);
		CAppData::m_cItemCreationWnd.DrawFormulaList ();
		CAppData::SetItemWindow(true);
	}

}

void CItemCreation::OnSearchByFormname()
{
	CInputDialog l_cInputDialog (this);

	l_cInputDialog.m_csInputMsg = "Search for";
	l_cInputDialog.m_csTitleMsg = "Filter By Formula Name";
	if (l_cInputDialog.DoModal () == IDOK)
	{
		CAppData::m_cFormFilter = l_cInputDialog.m_csInput;
		CAppData::m_cFormClassFilter = "";
		CAppData::m_cpFormFilterTech = NULL;
		CAppData::m_csLastFormulaCategory = cCustom_Filter;
		CAppData::m_cpCurrentFormula = NULL;
		CAppData::m_bEditMode = false;
		CAppData::m_bFormSearchMode = true;
		CAppData::m_cItemCreationWnd.SelectCategory (cCustom_Filter);
		CAppData::m_cItemCreationWnd.DrawFormulaList ();
		CAppData::SetItemWindow(true);
	}

}

void CItemCreation::OnSearchByclass()
{
	CInputListDialog l_cInputDialog (this);

	l_cInputDialog.m_csInputMsg = "Class Name";
	l_cInputDialog.m_csTitleMsg = "Filter By Class";
	l_cInputDialog.m_csInputList.AddTail ("Adventure: Battle Mage (BTLM)");
	l_cInputDialog.m_csInputList.AddTail ("Adventure: Berserker (BERS)");
	l_cInputDialog.m_csInputList.AddTail ("Adventure: Blood Mage (BLDM)");
	l_cInputDialog.m_csInputList.AddTail ("Adventure: Chaos Warrior (CHSW)");
	l_cInputDialog.m_csInputList.AddTail ("Adventure: Cleric (CLRC)");
	l_cInputDialog.m_csInputList.AddTail ("Adventure: Conjurer (CONJ)");
	l_cInputDialog.m_csInputList.AddTail ("Adventure: Crossbowman (CRSB)");
	l_cInputDialog.m_csInputList.AddTail ("Adventure: Dragon (DRAG)");
	l_cInputDialog.m_csInputList.AddTail ("Adventure: Druid (DRU)");
	l_cInputDialog.m_csInputList.AddTail ("Adventure: Elemental Archer (ELAR)");
	l_cInputDialog.m_csInputList.AddTail ("Adventure: Flame Disciple (FLMD)");
	l_cInputDialog.m_csInputList.AddTail ("Adventure: Guardian (GRDN)");
	l_cInputDialog.m_csInputList.AddTail ("Adventure: Healer (HLR)");
	l_cInputDialog.m_csInputList.AddTail ("Adventure: Ice Disciple (ICED)");
	l_cInputDialog.m_csInputList.AddTail ("Adventure: Knight of Creation (KNOC)");
	l_cInputDialog.m_csInputList.AddTail ("Adventure: Mage (MAGE)");
	l_cInputDialog.m_csInputList.AddTail ("Adventure: Monk (MONK)");
	l_cInputDialog.m_csInputList.AddTail ("Adventure: Paladin (PLDN)");
	l_cInputDialog.m_csInputList.AddTail ("Adventure: Ranger (RNGR)");
	l_cInputDialog.m_csInputList.AddTail ("Adventure: Reaver (RVR)");
	l_cInputDialog.m_csInputList.AddTail ("Adventure: Scout (SCT)");
	l_cInputDialog.m_csInputList.AddTail ("Adventure: Shaman (SHMN)");
	l_cInputDialog.m_csInputList.AddTail ("Adventure: Sorcerer (SORC)");
	l_cInputDialog.m_csInputList.AddTail ("Adventure: Spearman (SPRM)");
	l_cInputDialog.m_csInputList.AddTail ("Adventure: Spiritist (SPRT)");
	l_cInputDialog.m_csInputList.AddTail ("Adventure: Storm Disciple (STMD)");
	l_cInputDialog.m_csInputList.AddTail ("Adventure: Warrior (WAR)");
	l_cInputDialog.m_csInputList.AddTail ("Adventure: Wizard (WIZ)");
	l_cInputDialog.m_csInputList.AddTail ("Craft: Alchemist (ALC)");
	l_cInputDialog.m_csInputList.AddTail ("Craft: Armorer (ARM)");
	l_cInputDialog.m_csInputList.AddTail ("Craft: Blacksmith (BLK)");
	l_cInputDialog.m_csInputList.AddTail ("Craft: Carpenter (CRP)");
	l_cInputDialog.m_csInputList.AddTail ("Craft: Confectioner (CNF)");
	l_cInputDialog.m_csInputList.AddTail ("Craft: Dragon Crafter (DCRA)");
	l_cInputDialog.m_csInputList.AddTail ("Craft: Dragon Lairshaper (DLSH)");
	l_cInputDialog.m_csInputList.AddTail ("Craft: Enchanter (ENC)");
	l_cInputDialog.m_csInputList.AddTail ("Craft: Fitter (FIT)");
	l_cInputDialog.m_csInputList.AddTail ("Craft: Fletcher (FLT)");
	l_cInputDialog.m_csInputList.AddTail ("Craft: Gatherer (GTH)");
	l_cInputDialog.m_csInputList.AddTail ("Craft: Jeweler (JWL)");
	l_cInputDialog.m_csInputList.AddTail ("Craft: Mason (MSN)");
	l_cInputDialog.m_csInputList.AddTail ("Craft: Miner (MIN)");
	l_cInputDialog.m_csInputList.AddTail ("Craft: Outfitter (OUT)");
	l_cInputDialog.m_csInputList.AddTail ("Craft: Scholar (SCH)");
	l_cInputDialog.m_csInputList.AddTail ("Craft: Spellcrafter (SPL)");
	l_cInputDialog.m_csInputList.AddTail ("Craft: Tailor (TLR)");
	l_cInputDialog.m_csInputList.AddTail ("Craft: Tinkerer (TNK)");
	l_cInputDialog.m_csInputList.AddTail ("Craft: Weaponsmith (WPN)");
	l_cInputDialog.m_csInputList.AddTail ("Craft: Weaver (WVR)");

	if (l_cInputDialog.DoModal () == IDOK)
	{
		int l_iStart = l_cInputDialog.m_csSelectedInput.Find ("(") + 1;
		int l_iEnd = l_cInputDialog.m_csSelectedInput.Find (")");
		CAppData::m_cFormClassFilter = l_cInputDialog.m_csSelectedInput.Mid (l_iStart, l_iEnd - l_iStart);

		if ((CAppData::m_cFormClassFilter  == "DRAG") ||
			 (CAppData::m_cFormClassFilter  == "DCRA") ||
			 (CAppData::m_cFormClassFilter  == "DLSH"))
		{
			CAppData::m_cFormClassFilterType = "Khutit";
		}
		else
		{
			CAppData::m_cFormClassFilterType = "Human";
		}

		CAppData::m_cFormFilter = "";
		CAppData::m_cpFormFilterTech = NULL;
		CAppData::m_csLastFormulaCategory = cCustom_Filter;
		CAppData::m_cpCurrentFormula = NULL;
		CAppData::m_bEditMode = false;
		CAppData::m_cItemCreationWnd.SelectCategory (cCustom_Filter);
		CAppData::m_cItemCreationWnd.DrawFormulaList ();
		CAppData::SetItemWindow(true);
	}

}

BOOL CItemCreation::OnHelpInfo(HELPINFO* pHelpInfo)
{
	return (TRUE);
}


CItemCreation::ResetItemEdit()
{
	CAppData::m_bEditMode = false;
	m_cAddItemButton.EnableWindow (true);
	m_cAddItemButton.SetWindowText ("Add Item");
	m_cItemSelecter.SetCurSel (0);
}

void CItemCreation::OnClickFormulatree(NMHDR* pNMHDR, LRESULT* pResult)
{

	*pResult = 0;
}
