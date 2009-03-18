// TechniqueSelection.cpp : implementation file
//

#include "stdafx.h"
#include <afxctl.h>
#include "HCC.h"
#include "TechniqueSelection.h"
#include "AppData.h"
#include "Scheme.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define cInfoGridIndent 750

/////////////////////////////////////////////////////////////////////////////
// CTechniqueSelection dialog


CTechniqueSelection::CTechniqueSelection(CWnd* pParent /*=NULL*/)
	: CDialog(CTechniqueSelection::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTechniqueSelection)
	//}}AFX_DATA_INIT
}


void CTechniqueSelection::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTechniqueSelection)
	DDX_Control(pDX, IDC_TECHSTEXT, m_cTechsText);
	DDX_Control(pDX, IDC_FILTERLIST, m_cFilterList);
	DDX_Control(pDX, IDC_EXPAND, m_cExpandButton);
	DDX_Control(pDX, IDC_CATEGORIESTEXT, m_cCategoriesText);
	DDX_Control(pDX, IDC_COLLAPSE, m_cCollapseButton);
	DDX_Control(pDX, IDC_FILTERFORMS, m_cFilterFormulas);
	DDX_Control(pDX, IDC_TECHTREE, m_cTechTree);
	DDX_Control(pDX, IDC_SHOWUSABLE, m_cShowUsable);
	DDX_Control(pDX, IDC_SIZINGBOX, m_cSizingBox);
	DDX_Control(pDX, IDC_SIZINGTITLEBOX, m_cSizingTitleBox);
	DDX_Control(pDX, IDC_ADDTECH, m_cAddTechButton);
	DDX_Control(pDX, IDC_TECHCOMPONENTGRID, m_cTechComponentGrid);
	DDX_Control(pDX, IDC_TECHINFOGRID, m_cTechInfoGrid);
	DDX_Control(pDX, IDC_TECHTIERGRID, m_cTechTierGrid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTechniqueSelection, CDialog)
	//{{AFX_MSG_MAP(CTechniqueSelection)
	ON_WM_WINDOWPOSCHANGING ()
	ON_WM_GETMINMAXINFO()
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_TECHFILTER, OnSelchangeTechfilter)
	ON_BN_CLICKED(IDC_SHOWUSABLE, OnShowusable)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TECHTREE, OnSelchangedTechtree)
	ON_BN_CLICKED(IDC_ADDTECH, OnAddtech)
	ON_BN_CLICKED(IDC_FILTERFORMS, OnFilterforms)
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_TECHTREE, OnItemexpandingTechtree)
	ON_COMMAND(ID_OPTIONS_SNAPSHOTWINDOW, OnOptionsSnapshotwindow)
	ON_COMMAND(ID_OPTIONS_RESTOREWINDOW, OnOptionsRestorewindow)
	ON_COMMAND(ID_OPTIONS_AUTOEXPAND_OFF, OnOptionsAutoexpandOff)
	ON_COMMAND(ID_OPTIONS_AUTOEXPAND_CURRENTCATEGORY, OnOptionsAutoexpandCurrentcategory)
	ON_COMMAND(ID_OPTIONS_AUTOEXPAND_ALLCATEGORIES, OnOptionsAutoexpandAllcategories)
	ON_BN_CLICKED(IDC_COLLAPSE, OnCollapse)
	ON_COMMAND(ID_HELP_INDEX, OnHelpIndex)
	ON_NOTIFY(NM_CLICK, IDC_FILTERLIST, OnClickFilterlist)
	ON_NOTIFY(LVN_KEYDOWN, IDC_FILTERLIST, OnKeydownFilterlist)
	ON_BN_CLICKED(IDC_EXPAND, OnExpand)
	ON_WM_MOVE()
	ON_COMMAND(ID_WINDOW_ALWAYSONTOP, OnWindowAlwaysontop)
	ON_WM_MOUSEWHEEL()
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CTechniqueSelection, CDialog)
    //{{AFX_EVENTSINK_MAP(CTechniqueSelection)
	ON_EVENT(CTechniqueSelection, IDC_TECHTIERGRID, -600 /* Click */, OnClickTechtiergrid, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTechniqueSelection message handlers

BOOL CTechniqueSelection::OnInitDialog()
{
	CDialog::OnInitDialog();

   //remove some options from the system menu
   CMenu* pSysMenu = GetSystemMenu(FALSE);
   pSysMenu->RemoveMenu(SC_RESTORE,MF_BYCOMMAND);
   pSysMenu->RemoveMenu(SC_MINIMIZE,MF_BYCOMMAND);
   pSysMenu->RemoveMenu(SC_MAXIMIZE,MF_BYCOMMAND);
   pSysMenu->RemoveMenu(SC_TASKLIST ,MF_BYCOMMAND);

	m_cOS_CategoriesText.InitState	(m_cCategoriesText,		*this, NULL,						NULL,						1.0f, 0.0f, NULL);
	m_cOS_TechFilter.InitState			(m_cFilterList,			*this, NULL,						NULL,						1.0f, 0.0f, NULL);
	m_cOS_TechsText.InitState			(m_cTechsText,				*this, NULL,						NULL,						0.2f, 0.0f, NULL);
	m_cOS_TechExpand.InitState			(m_cExpandButton,			*this, &m_cOS_TechsText,		NULL,						0.0f, 0.0f, NULL);
	m_cOS_TechCollapse.InitState		(m_cCollapseButton,		*this, NULL,						NULL,						0.0f, 0.0f, NULL);
	m_cOS_TechGrid.InitState			(m_cTechTree,				*this, NULL,						NULL,						0.2f, 1.0f);
	m_cOS_TechInfoGrid.InitState		(m_cTechInfoGrid,			*this, &m_cOS_TechGrid,			NULL,						0.8f, 1.0f, &m_iCombinedDelta);
	m_cOS_TechTierGrid.InitState		(m_cTechTierGrid,			*this, &m_cOS_TechGrid,			&m_cOS_TechInfoGrid,	0.8f, 0.0f, &m_iTierListDeltaReverse);
	m_cOS_TechComponentGrid.InitState(m_cTechComponentGrid,	*this, &m_cOS_TechGrid,			&m_cOS_TechTierGrid,	0.8f, 0.0f, &m_iResourceListDeltaReverse);
	m_cOS_AddTechButton.InitState		(m_cAddTechButton,		*this, &m_cOS_TechGrid,			&m_cOS_TechGrid,		0.8f, 0.0f, &m_iResourceListDeltaZero);
	m_cOS_FilterFormulas.InitState	(m_cFilterFormulas,		*this, NULL,						&m_cOS_TechGrid,		0.2f, 0.0f, &m_iResourceListDeltaZero);
	m_cOS_ShowUsable.InitState			(m_cShowUsable,			*this, NULL,						&m_cOS_TechGrid,		0.0f, 0.0f, &m_iResourceListDeltaZero);
	m_cOS_SizingBox.InitState			(m_cSizingBox,				*this, &m_cOS_TechGrid,			NULL,						0.8f, 0.0f);
	m_cOS_SizingTitleBox.InitState	(m_cSizingTitleBox,		*this, &m_cOS_TechGrid,			NULL,						0.8f, 0.0f);
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

void CTechniqueSelection::OnGetMinMaxInfo (MINMAXINFO FAR* lpMMI)
{
	CDialog::OnGetMinMaxInfo (lpMMI);

	lpMMI->ptMinTrackSize.x = 400;
	lpMMI->ptMinTrackSize.y = 350;
	lpMMI->ptMaxTrackSize.x = 600;
	lpMMI->ptMaxTrackSize.y = 1280;

}

CTechniqueSelection::StartUp()
{
	this->Create (IDD_TECHDIALOG, CWnd::GetDesktopWindow ());
	m_cWindowState.m_bLoaded = true;
	m_bUpdating = false;
}

CTechniqueSelection::DrawCategoryList()
{
	POSITION l_Pos;
	int l_iPos = 0;

	m_cFilterList.SetBkColor (CScheme::GetColour ("TREE_BACKCOLOUR"));
	m_cFilterList.SetTextBkColor (CScheme::GetColour ("TREE_BACKCOLOUR"));
	m_cFilterList.DeleteAllItems();
	l_Pos = CAppData::m_clTechCategoryList.GetHeadPosition ();
	m_cFilterList.InsertItem  (l_iPos, cNo_Filter);
	m_cFilterList.SetItemData (l_iPos++, 5);
	while (l_Pos)
	{
		m_cFilterList.InsertItem (l_iPos, CAppData::m_clTechCategoryList.GetNext (l_Pos));
		m_cFilterList.SetItemData (l_iPos++, 5);
	}
	m_cFilterList.SetColumnWidth (0, 75);

	SelectCategory (CAppData::m_csLastTechCategory);
	CAppData::m_csLastTechCategory = GetCategory ();
}

CTechniqueSelection::Initialise()
{
	m_bTechTreeExpand = false;

	m_cTechInfoGrid.SetRows (0);
	m_cTechInfoGrid.SetFormatString (">Col1|<Col2");
	m_cTechInfoGrid.SetColWidth (0, 700);
	m_cTechInfoGrid.SetColWidth (1, 3100);
	m_cTechInfoGrid.SetColAlignment (0, 7);
	m_cTechInfoGrid.SetColAlignment (1, 1);
	m_cTechInfoGrid.SetBackColor (CScheme::GetColour ("GRID_INFOBACKCOLOUR"));
	m_cTechInfoGrid.SetBackColorBkg (CScheme::GetColour ("GRID_INFOBACKCOLOUR"));
	m_cTechInfoGrid.SetGridColorFixed (CScheme::GetColour ("GRID_INFOBACKCOLOUR"));
	m_cTechInfoGrid.SetForeColorSel (CScheme::GetColour ("SELECTCOLOUR_FG"));
	m_cTechInfoGrid.SetBackColorSel (CScheme::GetColour ("SELECTCOLOUR_BG"));

	m_cTechComponentGrid.SetRows (1);
	m_cTechComponentGrid.SetFormatString ("<Component|^Need|^Source");
	m_cTechComponentGrid.SetColWidth (0, 2500);
	m_cTechComponentGrid.SetColWidth (1, 1000);
	m_cTechComponentGrid.SetColWidth (2, 700);
	m_cTechComponentGrid.SetBackColor (CScheme::GetColour ("GRID_BACKCOLOUR"));
	m_cTechComponentGrid.SetBackColorBkg (CScheme::GetColour ("GRID_BACKCOLOUR"));
	m_cTechComponentGrid.SetGridColor (CScheme::GetColour ("GRID_LINECOLOUR_LIGHT"));
	m_cTechComponentGrid.SetGridColorFixed (CScheme::GetColour ("GRID_LINECOLOUR_DARK"));
	m_cTechComponentGrid.SetForeColorSel (CScheme::GetColour ("SELECTCOLOUR_FG"));
	m_cTechComponentGrid.SetBackColorSel (CScheme::GetColour ("SELECTCOLOUR_BG"));

	m_cTechTierGrid.SetRows (1);
	m_cTechTierGrid.SetFormatString ("^Tiers");
	m_cTechTierGrid.SetColWidth (0, 820);
	m_cTechTierGrid.SetBackColor (CScheme::GetColour ("GRID_LISTBACKCOLOUR"));
	m_cTechTierGrid.SetBackColorBkg (CScheme::GetColour ("GRID_LISTBACKCOLOUR"));
	m_cTechTierGrid.SetGridColorFixed (CScheme::GetColour ("GRID_LISTBACKCOLOUR"));
	m_cTechTierGrid.SetForeColorSel (CScheme::GetColour ("SELECTCOLOUR_FG"));
	m_cTechTierGrid.SetBackColorSel (CScheme::GetColour ("SELECTCOLOUR_BG"));

	if (CAppData::m_bEnableIcons)
	{
		m_cTechTree.SetImageList (&CAppData::m_cpIconImages->m_cImageList, TVSIL_NORMAL);
	}
	else
	{
		m_cTechTree.SetImageList (NULL, TVSIL_NORMAL);
	}
	m_cTechTree.SetBkColor (CScheme::GetColour ("TREE_BACKCOLOUR"));

	DrawCategoryList();

	m_cShowUsable.SetCheck (CAppData::m_bShowUsableTechs);
	if (CAppData::m_cItemCreationWnd.m_cWindowState.m_bLoaded)
	{
		m_cShowUsable.EnableWindow (CAppData::m_cItemCreationWnd.m_cAddItemButton.IsWindowEnabled ());
	}

	m_cWindowState.m_bLoaded = true;
	DrawTechList ();

	ResizeGrids();
	if (CAppData::m_cpCurrentTech)
	{
		DisplayTech (CAppData::m_cpCurrentTech, CAppData::m_csCurrentTechTierName);
		ResizeResourceGrid ();
	}
	else
	{
		DisableScreen();
	}

	UpdateAutoExpandMenu();


}

CTechniqueSelection::SelectCategory(CString a_csCategory)
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

void CTechniqueSelection::OnClose()
{
	CAppData::SetTechWindow(false);

	CDialog::OnClose();
}

void CTechniqueSelection::OnOK()
{
}

void CTechniqueSelection::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (m_cWindowState.m_bLoaded)
	{
		ResizeGrids ();
	}

}

CTechniqueSelection::ResizeGrids()
{
//	m_cTechInfoGrid.SetColWidth (1, CAppData::ConvertScreenWidthToGrid (m_cOS_SizingBox.m_iCurWidth) + 300);
	CRect l_cRect;

	float l_fWidth;

	ResizeResourceGrid();
	m_cOS_CategoriesText.Resize ();
	m_cOS_TechFilter.Resize ();
	m_cOS_TechCollapse.Resize ();
	m_cOS_TechsText.Resize ();
	m_cOS_TechExpand.Resize ();
	m_cOS_TechGrid.Resize ();
	m_cOS_TechInfoGrid.Resize ();
	m_cOS_TechTierGrid.Resize ();
	m_cOS_AddTechButton.Resize ();
	m_cOS_TechComponentGrid.Resize ();
	m_cOS_ShowUsable.Resize ();
	m_cOS_FilterFormulas.Resize ();
	m_cOS_SizingBox.Resize ();
	m_cOS_SizingTitleBox.Resize ();

	//m_cTechTierGrid.SetColWidth (0, CAppData::ConvertScreenWidthToGrid (m_cOS_TechTierGrid.m_iCurWidth));

	m_cTechInfoGrid.GetClientRect (l_cRect);

	m_cTechInfoGrid.SetColWidth (0, cInfoGridIndent);
	m_cTechInfoGrid.SetColWidth (1, CAppData::ConvertScreenWidthToGrid (l_cRect.Width()) - cInfoGridIndent);

	m_cTechInfoGrid.GetWindowRect (l_cRect);
	m_cOS_TechTierGrid.m_iCurWidth = (l_cRect.Width ());
	m_cTechTierGrid.SetColWidth (0, CAppData::ConvertScreenWidthToGrid (l_cRect.Width ()));

	l_fWidth = (float) CAppData::ConvertScreenWidthToGrid (m_cOS_TechComponentGrid.m_iCurWidth) - 2000- 300;
	m_cTechComponentGrid.SetColWidth (0, (long) (l_fWidth * 1.00f) + 1700);
	m_cTechComponentGrid.SetColWidth (1, 600);
}

CTechniqueSelection::DrawTechList()
{
	CTechSet *l_cpTechSet;
	CTech		*l_cpTech;
	CFormulaTier *l_cpFormulaTier = NULL;
	POSITION l_TechSetPos;
	POSITION l_TechPos;
	bool l_bTechAdded;
   HTREEITEM l_TreeItem;
   HTREEITEM l_hTypeItem;
	CTech *l_cpTechCheck[10];
	CTechTier *l_cpTechTierCheck[10];
	int   l_iTechCount;
	int   l_iTechSlotCount;
	int   l_iTechOffset;
	CItemTech l_cItemTech;
	CString l_csCategoryText;
	int l_iStartOffset;
	int l_iEndOffset;
	int l_iCatShow;
	int l_iCatTotal;
	HTREEITEM l_SelectedTech = NULL;
	bool l_bPickedSelected = false;
	int l_iDisplayedTechCount = 0;
	bool l_bShowUsable = false;

	if (m_cShowUsable)
	{
		l_bShowUsable = (m_cShowUsable.GetCheck () > 0) && (m_cShowUsable.IsWindowEnabled ());
	}

	if (m_cWindowState.m_bLoaded)
	{
		if (CAppData::m_cpCurrentFormula)
		{
			CAppData::FindFormulaTier (CAppData::m_csLastFormulaCategory, CAppData::m_cpCurrentFormula->m_csName, CAppData::m_csCurrentFormulaTierName, &l_cpFormulaTier);
		}

		this->LockWindowUpdate ();
		m_bTechTreeExpand = true;
		m_bUpdating = true;
		m_cTechTree.DeleteAllItems ();
		m_bUpdating = false;

		l_iTechCount = 0;
		l_iTechSlotCount = 0;
		l_TechPos = CAppData::m_cCurrentOrderItem.m_clTechList.GetHeadPosition ();
		while (l_TechPos)
		{
			l_cItemTech = CAppData::m_cCurrentOrderItem.m_clTechList.GetNext (l_TechPos);
			if (CAppData::FindTech (l_cItemTech.m_csCategory, l_cItemTech.m_csTechName, &l_cpTechCheck[l_iTechCount]))
			{
				if (CAppData::FindTechTier (l_cItemTech.m_csCategory, l_cItemTech.m_csTechName, l_cItemTech.m_csTierName, &l_cpTechTierCheck[l_iTechCount]))
				{
					l_iTechSlotCount += l_cpTechTierCheck[l_iTechCount]->m_iSize;
					l_iTechCount++;

				}
			}
		}

		l_TechSetPos = CAppData::m_clTechSetList.GetHeadPosition ();
		while (l_TechSetPos)
		{
			l_cpTechSet = CAppData::m_clTechSetList.GetNext (l_TechSetPos);

			if ((l_cpTechSet->m_csCategory == CAppData::m_csLastTechCategory) ||
				 (CAppData::m_csLastTechCategory == cNo_Filter))
			{
				l_hTypeItem = m_cTechTree.FindTreeItem (l_cpTechSet->m_csCategory, 0);

				if (l_hTypeItem == NULL)
				{
					l_csCategoryText.Format ("%s (0/0)", l_cpTechSet->m_csCategory);
					l_hTypeItem = m_cTechTree.InsertItem (l_csCategoryText, l_cpTechSet->m_iIcon, l_cpTechSet->m_iIcon, TVI_ROOT, TVI_LAST);
					m_cTechTree.SetItemData (l_hTypeItem, 2);

					if (l_cpTechSet->m_csCategory == CAppData::m_csLastTechCategory)
					{
						m_cTechTree.Expand (l_hTypeItem, TVE_EXPAND);
					}

				}

				l_csCategoryText = m_cTechTree.GetItemText (l_hTypeItem);
				l_iStartOffset = l_csCategoryText.Find ('(') + 1;
				l_iEndOffset = l_csCategoryText.Find ('/', l_iStartOffset);
				l_iCatShow = atoi (l_csCategoryText.Mid (l_iStartOffset, (l_iEndOffset - l_iStartOffset)));
				l_iStartOffset = l_iEndOffset + 1;
				l_iEndOffset =  l_csCategoryText.Find (')', l_iStartOffset);
				l_iCatTotal = atoi (l_csCategoryText.Mid (l_iStartOffset, (l_iEndOffset - l_iStartOffset)));

				l_TechPos = l_cpTechSet->m_clTechList.GetHeadPosition ();

				while (l_TechPos)
				{
					l_cpTech = l_cpTechSet->m_clTechList.GetNext (l_TechPos);
					l_bTechAdded = false;
					l_iCatTotal++;

					if (l_cpFormulaTier)
					{
						if ((l_cpFormulaTier->m_iAllowedTechniques > 0) &&
							 ((l_iTechSlotCount < l_cpFormulaTier->m_iAllowedTechniques) || (l_cpTechSet->m_csCategory == "Armor Dye")))
						{
							if (l_cpTech->CheckFormula (CAppData::m_cpCurrentFormula, l_cpFormulaTier))
							{
								l_bTechAdded = true;

								l_iTechOffset =0 ;

								while (l_iTechOffset < l_iTechCount)
								{
									if (!l_cpTechCheck[l_iTechOffset]->CheckTech (l_cpTech))
									{
										l_bTechAdded = false;
										l_iTechOffset = l_iTechCount;
									}

									l_iTechOffset++;
								}

								if (l_bTechAdded)
								{
									l_TreeItem = m_cTechTree.InsertItem (l_cpTech->m_csName, l_cpTech->m_iIcon, l_cpTech->m_iIcon, l_hTypeItem, TVI_LAST);
									m_cTechTree.SetItemData (l_TreeItem, 1);
									l_iCatShow++;
								}
							}
						}
					}

					if (!l_bTechAdded)
					{
						if (!l_bShowUsable)
						{
							l_TreeItem = m_cTechTree.InsertItem (l_cpTech->m_csName, l_cpTech->m_iIcon, l_cpTech->m_iIcon, l_hTypeItem, TVI_LAST);
							m_cTechTree.SetItemData (l_TreeItem, 0);
							l_iCatShow++;
							l_bTechAdded = true;
						}
					}

					if (l_bTechAdded)
					{
						l_iDisplayedTechCount++;
						if (l_cpTechSet->m_csCategory == m_csPreferedCategory)
						{
							if (!l_bPickedSelected)
							{
								if ((m_csPreferedTech.IsEmpty ()) || (l_cpTech->m_csName < m_csPreferedTech))
								{
									l_SelectedTech = l_TreeItem;
								}
								else if (l_cpTech->m_csName >= m_csPreferedTech)
								{
									l_SelectedTech = l_TreeItem;
									l_bPickedSelected = true;
								}
							}
						}
					}

				}

				l_csCategoryText.Format ("%s (%d/%d)", l_cpTechSet->m_csCategory, l_iCatShow, l_iCatTotal);
				m_cTechTree.SetItemText (l_hTypeItem, l_csCategoryText);

			}

		}

		l_hTypeItem = m_cTechTree.GetRootItem ();
		while (l_hTypeItem)
		{
			if (m_cTechTree.GetChildItem (l_hTypeItem))
			{
				if (CAppData::m_iExpandTechMode > 1)
				{
					m_cTechTree.Expand (l_hTypeItem, TVE_EXPAND);
				}

				m_cTechTree.SortChildren (l_hTypeItem);
				l_hTypeItem = m_cTechTree.GetNextSiblingItem (l_hTypeItem);
			}
			else
			{
				m_cTechTree.SetItemData (l_hTypeItem, 3);
				l_TreeItem = l_hTypeItem;
				l_hTypeItem = m_cTechTree.GetNextSiblingItem (l_hTypeItem);
				//m_cTechTree.DeleteItem (l_TreeItem);
			}

		}

		//if (CAppData::m_cpCurrentTech)
		//{
		//	l_TreeItem = SelectTech (CAppData::m_cpCurrentTech->m_csName);
		//}
		//else
		//{
			if (l_SelectedTech)
			{
				m_cTechTree.SelectItem (l_SelectedTech);
				l_TreeItem = l_SelectedTech;
			}
			else
			{
				l_TreeItem = NULL;
				DisableScreen ();
			}
		//}

		if (l_TreeItem)
		{
			if (CAppData::m_iExpandTechMode > 0)
			{
				m_cTechTree.SelectItem (l_TreeItem);
				m_cTechTree.EnsureVisible (l_TreeItem);
			}
		}
		else if (m_cTechTree.GetCount () > 0)
		{
			CString l_csTechName;
			CString l_csCategory;

			l_TreeItem = m_cTechTree.GetRootItem ();
			while (l_TreeItem)
			{
				if (m_cTechTree.GetChildItem (l_TreeItem))
				{
					l_TreeItem = m_cTechTree.GetChildItem (l_TreeItem);

					if (CAppData::m_iExpandTechMode > 0)
					{
						m_cTechTree.SelectItem (l_TreeItem);
					}

					l_csTechName = m_cTechTree.GetItemText (l_TreeItem);
					l_csCategory = GetCategory ();

					if (CAppData::FindTech (l_csCategory, l_csTechName,  &CAppData::m_cpCurrentTech))
					{
						DisplayTechTiers (CAppData::m_cpCurrentTech);
						DisplayTech (CAppData::m_cpCurrentTech, CAppData::m_csCurrentTechTierName);
						EnableScreen ();

					}
					else
					{
						DisableScreen ();
					}
				}
				else
				{
					l_TreeItem = m_cTechTree.GetNextSiblingItem (l_TreeItem);
				}
			}
		}
		else
		{
			l_TreeItem = m_cTechTree.InsertItem ("None", 0, 0, TVI_ROOT, TVI_LAST);
			m_cTechTree.SetItemData (l_TreeItem, 0);
			m_cTechTree.SelectItem (l_TreeItem);
			DisableScreen ();
			m_cTechInfoGrid.SetRows (0);
			m_cTechComponentGrid.SetRows (1);
		}

		CString l_csMsg;
		l_csMsg.Format ("%d Techniques", l_iDisplayedTechCount);
		if (CAppData::m_bShowUsableTechs)
		{
			l_csMsg += " (Usable)";
		}
		m_cTechsText.SetWindowText (l_csMsg);

		m_bTechTreeExpand = false;
		this->UnlockWindowUpdate ();

		if (CAppData::m_cpCurrentTech)
		{
			DisplayTechTiers (CAppData::m_cpCurrentTech);
			DisplayTech (CAppData::m_cpCurrentTech, CAppData::m_csCurrentTechTierName);
		}
	}
}

CTechniqueSelection::DisplayTech(CTech *a_cpTech, CString &a_csTierName)
{
	POSITION l_Pos;
	CTechTier *l_cpTechTier = NULL;
	CItemResource *l_cpItemResource;
	CString l_csSlot;
	CString l_csTierStr;
	CString l_csResourceStr = "";
	CString l_csBonusStr = "";
	CString l_csPrevInfoName = "";
	CString l_csStr = "";
	int l_iAdjust;
   bool l_bFoundMeleeDefend = false;
   bool l_bFoundSpellsDefend = false;
   bool l_bFoundResistance = false;
   bool l_bFoundEffective = false;
	CString l_csDescription = "";
	l_iAdjust = 0;
	bool l_bHeader;

	this->LockWindowUpdate ();
	m_cTechInfoGrid.EnableWindow (false);

	if (a_cpTech->FindTechTier (a_csTierName, &l_cpTechTier))
	{
		m_cTechInfoGrid.SetRows (0);
		m_cTechComponentGrid.SetRows (1);

		AddTitleLine (l_cpTechTier->m_csName, GRID_TITLE);

		if (a_cpTech->m_csSubDescription.IsEmpty () == false)
		{
			l_csDescription = a_cpTech->m_csSubDescription;
		}

		if (l_cpTechTier->m_csDescription.IsEmpty () == false)
		{
			l_csDescription += " " + l_cpTechTier->m_csDescription;
		}
		else if (a_cpTech->m_csDescription.IsEmpty () == false)
		{
			l_csDescription += " " + a_cpTech->m_csDescription;
		}

		if (!l_csDescription.IsEmpty ())
		{
			AddTitleLine (l_csDescription, GRID_DESCRIPTION);
		}

		AddSummaryLine (" |", GRID_BONUS);

		l_bHeader = false;
		CAppData::AddEffectType (l_cpTechTier->m_clEffectList, cXMLAttribute_RangeModifier,
										 "", m_cTechInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);

		CAppData::AddEffectType (l_cpTechTier->m_clEffectList, cXMLAttribute_ExtraDamage,
										 "", m_cTechInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);

		CAppData::AddEffectType (l_cpTechTier->m_clEffectList, cXMLAttribute_AttackModifier,
										 "", m_cTechInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);

		CAppData::AddEffectType (l_cpTechTier->m_clEffectList, cXMLAttribute_Effect,
										 "", m_cTechInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);

		CAppData::AddEffectType (l_cpTechTier->m_clEffectList, cXMLAttribute_TargetEffect,
										 "", m_cTechInfoGrid, GRID_EFFECT, &m_cSizingBox, "", l_bHeader);

		CAppData::AddEffectType (l_cpTechTier->m_clEffectList, cXMLAttribute_HealModifier,
										 "", m_cTechInfoGrid, GRID_EFFECT, &m_cSizingBox, "Heals additional ", l_bHeader);

		CAppData::AddEffectType (l_cpTechTier->m_clEffectList,
										 cXMLAttribute_Bonus,
										 "",
										 m_cTechInfoGrid,
										 GRID_EFFECT,
										 &m_cSizingBox, "", l_bHeader);

		if (l_bHeader)
		{
			AddSummaryLine (" |", GRID_BONUS);
		}

		// Stat Bonuses, Stat Caps, ShieldOn, Prevent Teleport, Equip Effects

		CAppData::AddTitledEffectType (a_cpTech->m_clEffectsList,
										 cXMLAttribute_StatBonus,
										 "Skill Gain From Statistics",
										 m_cTechInfoGrid,
										 GRID_TECH,
										 &m_cSizingBox);

		CAppData::AddTitledEffectType (a_cpTech->m_clEffectsList,
										 cXMLAttribute_SchoolBonus,
										 "Skill Gain From School",
										 m_cTechInfoGrid,
										 GRID_TECH,
										 &m_cSizingBox);

		CAppData::AddTitledEffectType (a_cpTech->m_clEffectsList,
										 cXMLAttribute_SpellDefense,
										 "Protects Against Spells",
										 m_cTechInfoGrid,
										 GRID_TECH,
										 &m_cSizingBox);

		CAppData::AddTitledEffectType (a_cpTech->m_clEffectsList,
										 cXMLAttribute_MeleeDefense,
										 "Protects Against Melee",
										 m_cTechInfoGrid,
										 GRID_TECH,
										 &m_cSizingBox);

		CAppData::AddTitledEffectType (a_cpTech->m_clEffectsList,
										 cXMLAttribute_MeleeOffense,
										 "Offense",
										 m_cTechInfoGrid,
										 GRID_TECH,
										 &m_cSizingBox);

		CAppData::AddTitledEffectType (a_cpTech->m_clEffectsList,
										 cXMLAttribute_LowResist,
										 "Vulnerable Creatures",
										 m_cTechInfoGrid,
										 GRID_TECH,
										 &m_cSizingBox);

		CAppData::AddTitledEffectType (a_cpTech->m_clEffectsList,
										 cXMLAttribute_HighResist,
										 "Resistant Creatures",
										 m_cTechInfoGrid,
										 GRID_TECH,
										 &m_cSizingBox);

		l_Pos = l_cpTechTier->m_clResourceList.GetHeadPosition ();
		while (l_Pos)
		{
			l_cpItemResource = l_cpTechTier->m_clResourceList.GetNext (l_Pos);
			AddToResources (l_cpItemResource, GRID_COMPONENT);
		}

		m_cTechComponentGrid.SelectRow (1, false);
		EnableScreen ();

	}
	else
	{
		DisableScreen ();
	}

	m_cTechInfoGrid.EnableWindow (true);
	this->UnlockWindowUpdate ();
}

CTechniqueSelection::AddTitleLine(CString a_csName, int a_iStyle)
{
	m_cTechInfoGrid.AddTitleRow (a_csName, a_iStyle, &m_cSizingTitleBox);
}

CTechniqueSelection::AddSummaryLine(CString a_csName, int a_iStyle)
{
	m_cTechInfoGrid.AddRow (a_csName, a_iStyle, &m_cSizingBox);
}

CTechniqueSelection::AddToResources(CItemResource *a_cpResource, int a_iStyle)
{
	CString l_csStr;

	l_csStr.Format ("%s|%d|-", a_cpResource->m_csName, a_cpResource->m_iMinAmt);
	m_cTechComponentGrid.AddRow (l_csStr, a_iStyle);
}

CTechniqueSelection::DisableScreen()
{
	VARIANT l_cSVariant;
	l_cSVariant.vt = VT_I4;

	m_cTechInfoGrid.SetEnabled (false);
	m_cTechComponentGrid.SetEnabled (false);
	m_cTechTierGrid.SetEnabled (false);

	m_cAddTechButton.EnableWindow (false);
	m_cFilterFormulas.EnableWindow (false);

	m_cTechInfoGrid.SetRows (0);

	l_cSVariant.intVal = 1;
	m_cTechComponentGrid.SetRows (1);
	m_cTechComponentGrid.AddRow ("None", GRID_COMPONENT);

	l_cSVariant.intVal = 1;
	m_cTechTierGrid.SetRows (1);
	m_cTechTierGrid.AddItem ("N/A", l_cSVariant);

	CAppData::m_cpCurrentTech = NULL;

}

CTechniqueSelection::EnableScreen()
{
	HTREEITEM l_cTreeItem;

	m_cTechInfoGrid.SetEnabled (true);
	m_cTechComponentGrid.SetEnabled (true);
	m_cTechTierGrid.SetEnabled (true);

	m_cAddTechButton.EnableWindow (true);
	m_cFilterFormulas.EnableWindow (true);
	l_cTreeItem = m_cTechTree.GetSelectedItem ();

	if (!l_cTreeItem)
	{
		m_cAddTechButton.EnableWindow (false);
	}
	else
	{
		if (m_cTechTree.GetItemData (l_cTreeItem) == 0)
		{
			m_cAddTechButton.EnableWindow (false);
		}
	}

	if (!m_cTechTierGrid.IsRowEnabled (m_cTechTierGrid.GetRowSel ()))
	{
		m_cAddTechButton.EnableWindow (false);
	}

}


void CTechniqueSelection::OnClickTechtiergrid()
{

	int l_irow =  m_cTechTierGrid.GetRowSel ();
	CString l_csTierName;

	if ((l_irow > 0) && (CAppData::m_cpCurrentTech))
	{
		l_csTierName = m_cTechTierGrid.GetTextMatrix (l_irow, 0);
		CAppData::m_csCurrentTechTierName = l_csTierName;
		CAppData::m_csPreferedTechTierName = l_csTierName;
		DisplayTech (CAppData::m_cpCurrentTech, CAppData::m_csCurrentTechTierName);

		ResizeGrids ();
	}

}

void CTechniqueSelection::OnSelchangeTechfilter()
{
}

void CTechniqueSelection::OnShowusable()
{
	CAppData::m_bShowUsableTechs = !CAppData::m_bShowUsableTechs;
	DrawTechList ();
}

CTechniqueSelection::DisplayTechTiers(CTech *a_cpTech)
{
	CTechTier *l_cpTechTier;
	CFormulaTier *l_cpFormulaTier;
	POSITION l_Pos;
	bool l_bCurrentTierFound = false;
	bool l_bTierDisplayed;
	int l_iCurrentTierRow = 1;
	CString l_csLastTierName;
	CString l_csTierName;
	int l_iMaxTier = 0;
	bool l_bShowUsable = (m_cShowUsable.GetCheck () > 0) && (m_cShowUsable.IsWindowEnabled ());

	m_cTechTierGrid.SetRows (1);
	m_cTechTierGrid.SetFormatString ("^Tiers");
	m_cTechTierGrid.SetColWidth (0, CAppData::ConvertScreenWidthToGrid (m_cOS_TechTierGrid.m_iCurWidth));

	if (CAppData::m_cpCurrentFormula)
	{
		if (CAppData::m_cpCurrentFormula->FindFormulaTier (CAppData::m_csCurrentFormulaTierName, &l_cpFormulaTier))
		{
			l_iMaxTier = l_cpFormulaTier->m_iTierLevel;
		}
	}

	l_Pos =  a_cpTech->m_clTechTierList.GetHeadPosition ();

	while (l_Pos)
	{
		l_cpTechTier = a_cpTech->m_clTechTierList.GetNext (l_Pos);
		l_bTierDisplayed = false;

		l_csTierName = l_cpTechTier->m_csTierName;

		if (l_cpTechTier->m_iTierLevel <= l_iMaxTier)
		{
			if (l_cpTechTier->CheckFormula (CAppData::m_cpCurrentFormula, l_cpFormulaTier))
			{
				m_cTechTierGrid.AddRow (l_csTierName, GRID_TIERAVAIL);
				l_bTierDisplayed = true;
			}
		}


		if ((!l_bShowUsable) && (!l_bTierDisplayed))
		{
			m_cTechTierGrid.AddRow (l_csTierName, GRID_TIERNOTAVAIL);
			l_bTierDisplayed = true;
		}

		if (l_bTierDisplayed)
		{
			l_csLastTierName = l_cpTechTier->m_csTierName;

			if (l_cpTechTier->m_csTierName == CAppData::m_csPreferedTechTierName)
			{
				l_bCurrentTierFound = true;
				l_iCurrentTierRow = m_cTechTierGrid.GetRows () - 1;
			}
		}
	}

	if (!l_bCurrentTierFound)
	{
		CAppData::m_csCurrentTechTierName = l_csLastTierName;
		l_iCurrentTierRow = m_cTechTierGrid.GetRows () - 1;
	}

	if (m_cTechTierGrid.GetRows () == 1)
	{
		CAppData::m_csCurrentTechTierName = CAppData::m_csPreferedTechTierName;
		m_cTechTierGrid.AddRow ("None", GRID_TIERNOTAVAIL);
	}

	m_cTechTierGrid.SelectRow (l_iCurrentTierRow);
	this->UnlockWindowUpdate ();
}

BOOL CTechniqueSelection::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	LPNMHDR pNmhdr = (LPNMHDR)lParam;

	switch (pNmhdr->code)
	{
		case NM_CUSTOMDRAW:
		{
			LPNMTVCUSTOMDRAW pCustomDraw = (LPNMTVCUSTOMDRAW)lParam;
			switch (pCustomDraw->nmcd.dwDrawStage)
			{
				case CDDS_PREPAINT:
					// Need to process this case and set pResult to CDRF_NOTIFYITEMDRAW,
					// otherwise parent will never receive CDDS_ITEMPREPAINT notification. (GGH)
					*pResult = CDRF_NOTIFYITEMDRAW;
					return true;

				case CDDS_ITEMPREPAINT:
					switch (pCustomDraw->nmcd.lItemlParam)
					{
						// painting all 0-level items blue,
						// and all 1-level items red (GGH)
						case 0:
							if (pCustomDraw->nmcd.uItemState & (CDIS_SELECTED))
							{
								pCustomDraw->clrText = CScheme::GetColour ("TREE_DISABLED_SELECTED_FG");
								pCustomDraw->clrTextBk = CScheme::GetColour ("TREE_DISABLED_SELECTED_BG");
							}
							else if (pCustomDraw->nmcd.uItemState & CDIS_HOT )
							{
								pCustomDraw->clrText = CScheme::GetColour ("TREE_DISABLED_HIGHLIGHT_FG");
								pCustomDraw->clrTextBk = CScheme::GetColour ("TREE_DISABLED_HIGHLIGHT_BG");
							}
							else
							{
								pCustomDraw->clrText = CScheme::GetColour ("TREE_DISABLED_NORMAL_FG");
							}
							*pResult = CDRF_SKIPDEFAULT;
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
							*pResult = CDRF_SKIPDEFAULT;
							break;
						}
						case 2:
						{
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
							break;
						}
						case 3:
						{
							SelectObject (pCustomDraw->nmcd.hdc, CAppData::m_cTitleFont);
							if (pCustomDraw->nmcd.uItemState & (CDIS_SELECTED))
							{
								pCustomDraw->clrText = CScheme::GetColour ("TREE_EMPTY_SELECTED_FG");
								pCustomDraw->clrTextBk = CScheme::GetColour ("TREE_EMPTY_SELECTED_BG");
							}
							else if (pCustomDraw->nmcd.uItemState & CDIS_HOT )
							{
								pCustomDraw->clrText = CScheme::GetColour ("TREE_EMPTY_HIGHLIGHT_FG");
								pCustomDraw->clrTextBk = CScheme::GetColour ("TREE_EMPTY_HIGHLIGHT_BG");
							}
							else
							{
								pCustomDraw->clrText = CScheme::GetColour ("TREE_EMPTY_NORMAL_FG");
							}
							*pResult = CDRF_NEWFONT;
							break;
						}
					}

					return false;

			}
		}
		break;
	}

	return CDialog::OnNotify(wParam, lParam, pResult);
}

void CTechniqueSelection::OnSelchangedTechtree(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	if (!m_bUpdating)
	{
		HTREEITEM l_TreeItem = m_cTechTree.GetSelectedItem ();
		HTREEITEM l_ParentTreeItem = m_cTechTree.GetParentItem (l_TreeItem);
		CString l_csTechName;
		CString l_csCategory;
		int l_iOffset;

		if (l_ParentTreeItem)
		{
			l_csTechName = m_cTechTree.GetItemText (l_TreeItem);
			l_csCategory = m_cTechTree.GetItemText (l_ParentTreeItem);
			l_iOffset = l_csCategory.Find (" (");

			if (l_iOffset > 0)
			{
				l_csCategory = l_csCategory.Left (l_iOffset);
			}
			else
			{
				l_csCategory = GetCategory ();
			}
			m_csPreferedCategory = l_csCategory;
			m_csPreferedTech = l_csTechName;

			if (CAppData::FindTech (l_csCategory, l_csTechName, &CAppData::m_cpCurrentTech))
			{
				CAppData::m_csCurrentTechTierName = CAppData::m_csPreferedTechTierName;
				//CAppData::m_csCurrentTechTierName = CAppData::m_csCurrentFormulaTierName;
				DisplayTechTiers (CAppData::m_cpCurrentTech);
				DisplayTech (CAppData::m_cpCurrentTech, CAppData::m_csCurrentTechTierName);
				EnableScreen ();

			}
			else
			{
				DisableScreen ();
			}
		}
		else
		{
			DisableScreen ();
			m_cTechTree.Expand (l_TreeItem, TVE_EXPAND);

			if (CAppData::m_iExpandTechMode == 1)
			{
				l_ParentTreeItem = m_cTechTree.GetRootItem ();
				while (l_ParentTreeItem)
				{
					if (l_ParentTreeItem != l_TreeItem)
					{
						m_cTechTree.Expand (l_ParentTreeItem, TVE_COLLAPSE);
					}

					l_ParentTreeItem = m_cTechTree.GetNextSiblingItem (l_ParentTreeItem);
				}
			}
		}

		ResizeGrids ();
	}

	*pResult = 0;
}

HTREEITEM CTechniqueSelection::SelectTech(CString &a_csTechName)
{
	HTREEITEM l_cParentItem;
	HTREEITEM l_cTreeItem;
	CString l_csTechName;

	AfxMessageBox ("Selecting " + a_csTechName);
	l_cParentItem = m_cTechTree.GetRootItem ();
	while (l_cParentItem)
	{
		l_cTreeItem = m_cTechTree.GetChildItem (l_cParentItem);
		while (l_cTreeItem)
		{
			l_csTechName = m_cTechTree.GetItemText (l_cTreeItem);
			if (l_csTechName == a_csTechName)
			{
				return (l_cTreeItem);
			}

			l_cTreeItem = m_cTechTree.GetNextSiblingItem (l_cTreeItem);
		}

		l_cParentItem = m_cTechTree.GetNextSiblingItem (l_cParentItem);
	}

	return (NULL);
}

void CTechniqueSelection::OnAddtech()
{
	CItemTech l_cItemTech;

	if (CAppData::m_cpCurrentTech)
	{
		l_cItemTech.m_csCategory = CAppData::m_csLastTechCategory;
		l_cItemTech.m_csTechName = CAppData::m_cpCurrentTech->m_csName;
		l_cItemTech.m_csTierName = CAppData::m_csCurrentTechTierName;
		CAppData::m_cCurrentOrderItem.m_clTechList.AddTail (l_cItemTech);

		CAppData::m_cpCurrentTech = NULL;
		CAppData::m_csCurrentTechTierName = CAppData::m_csCurrentFormulaTierName;
		CAppData::m_cItemCreationWnd.DisplayFormula (true);

		if (CAppData::m_bEditMode)
		{
			CAppData::UpdateOrderItem (CAppData::m_cCurrentOrderItem);
			CAppData::m_cOrderWnd.DisplayOrderItem (CAppData::m_cCurrentOrderItem.m_iId);
		}

	}
}

void CTechniqueSelection::OnFilterforms()
{
	if (CAppData::m_cpCurrentTech)
	{
		CAppData::m_cFormFilter = "";
		CAppData::m_cFormClassFilter = "";
		CAppData::m_cpFormFilterTech = CAppData::m_cpCurrentTech;
		CAppData::m_csLastFormulaCategory = cCustom_Filter;
		CAppData::m_cpCurrentFormula = NULL;
		CAppData::m_bEditMode = false;
		CAppData::m_cItemCreationWnd.SelectCategory (cCustom_Filter);
		CAppData::m_cItemCreationWnd.DrawFormulaList ();
		CAppData::SetItemWindow(true);
		CAppData::m_cItemCreationWnd.SetFocus ();
		CAppData::m_cItemCreationWnd.m_cItemSelecter.SetCurSel (0);
		CAppData::m_cItemCreationWnd.SetFocus ();
	}
}

void CTechniqueSelection::OnItemexpandingTechtree(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	//if (m_bTechTreeExpand)
	{
		*pResult = 0;
	}
	//else
	//{
	//	*pResult = 1;
	//}
}

void CTechniqueSelection::OnOptionsSnapshotwindow()
{
	CAppData::SetTechWindowState ();
}

void CTechniqueSelection::OnOptionsRestorewindow()
{
	CAppData::GetTechWindowState ();
}

void CTechniqueSelection::OnOptionsAutoexpandOff()
{
	CAppData::m_iExpandTechMode = 0;
	UpdateAutoExpandMenu();
}

void CTechniqueSelection::OnOptionsAutoexpandCurrentcategory()
{
	CAppData::m_iExpandTechMode = 1;
	UpdateAutoExpandMenu();
}

void CTechniqueSelection::OnOptionsAutoexpandAllcategories()
{
	CAppData::m_iExpandTechMode = 2;
	UpdateAutoExpandMenu();
}

void CTechniqueSelection::OnCollapse()
{
	HTREEITEM l_TreeItem;

	l_TreeItem = m_cTechTree.GetRootItem ();
	while (l_TreeItem)
	{
		m_cTechTree.Expand (l_TreeItem, TVE_COLLAPSE);
		l_TreeItem = m_cTechTree.GetNextSiblingItem (l_TreeItem);
	}
}

CTechniqueSelection::UpdateAutoExpandMenu()
{
	CMenu *l_pMenu;
	l_pMenu = GetMenu ();
	if (l_pMenu)
	{
		CAppData::SetMenuItem(l_pMenu, ID_OPTIONS_AUTOEXPAND_OFF, CAppData::m_iExpandTechMode == 0);
		CAppData::SetMenuItem(l_pMenu, ID_OPTIONS_AUTOEXPAND_CURRENTCATEGORY, CAppData::m_iExpandTechMode == 1);
		CAppData::SetMenuItem(l_pMenu, ID_OPTIONS_AUTOEXPAND_ALLCATEGORIES, CAppData::m_iExpandTechMode == 2);
	}
}

void CTechniqueSelection::OnHelpIndex()
{
	CAppData::LaunchWebLink ((CString) "techniquewindow");
}

void CTechniqueSelection::OnClickFilterlist(NMHDR* pNMHDR, LRESULT* pResult)
{
	CAppData::m_csLastTechCategory = GetCategory ();
	DrawTechList ();


	*pResult = 0;
}

void CTechniqueSelection::OnKeydownFilterlist(NMHDR* pNMHDR, LRESULT* pResult)
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;

	*pResult = 1;
}

CString CTechniqueSelection::GetCategory()
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

CTechniqueSelection::ResizeResourceGrid()
{
	if (m_cWindowState.m_bLoaded)
	{
		int l_iResize = CAppData::ConvertGridWidthToScreen (m_cTechComponentGrid.GetGridMinHeight (-2, 10, 4));

		m_iResourceListDelta = l_iResize;
		m_iResourceListDeltaZero = 0;
		m_iResourceListDeltaReverse = 0 - l_iResize;

		int l_iTResize = CAppData::ConvertGridWidthToScreen (m_cTechTierGrid.GetGridMinHeight (-1, 9, 6));

		m_iTierListDelta = l_iTResize;
		m_iTierListDeltaZero = 0;
		m_iTierListDeltaReverse = 0 - l_iTResize;

		m_iCombinedDelta = m_iResourceListDelta + m_iTierListDelta;
	}
}



void CTechniqueSelection::OnExpand()
{
	HTREEITEM l_TreeItem;

	l_TreeItem = m_cTechTree.GetRootItem ();
	while (l_TreeItem)
	{
		m_cTechTree.Expand (l_TreeItem, TVE_EXPAND);
		l_TreeItem = m_cTechTree.GetNextSiblingItem (l_TreeItem);
	}
}

void CTechniqueSelection::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);
}

void CTechniqueSelection::OnWindowPosChanging( WINDOWPOS* lpwndpos )
{
	CRect l_cRect;
	this->GetWindowRect (l_cRect);

	m_cWindowState.SnapToWnd (lpwndpos, &l_cRect, NULL, CAppData::m_iStickyStrength);
	m_cWindowState.SnapToWnd (lpwndpos, &l_cRect, CAppData::m_cpHCCDlg, CAppData::m_iStickyStrength);

	if (CAppData::m_cItemCreationWnd.m_cWindowState.m_bVisible)
	{
		m_cWindowState.SnapToWnd (lpwndpos, &l_cRect, &CAppData::m_cItemCreationWnd, CAppData::m_iStickyStrength);
	}

	if (CAppData::m_cOrderWnd.m_cWindowState.m_bVisible)
	{
		m_cWindowState.SnapToWnd (lpwndpos, &l_cRect, &CAppData::m_cOrderWnd, CAppData::m_iStickyStrength);
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

void CTechniqueSelection::OnWindowAlwaysontop()
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

BOOL CTechniqueSelection::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	int l_iTop = m_cTechInfoGrid.GetTopRow ();

	if ((zDelta > 0) && (l_iTop > 0))
	{
		l_iTop--;
	}
	else if (zDelta < 0)
	{
		l_iTop++;
	}

	if (l_iTop < m_cTechInfoGrid.GetRows ())
	{
		m_cTechInfoGrid.SetTopRow (l_iTop);
	}

	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

BOOL CTechniqueSelection::OnHelpInfo(HELPINFO* pHelpInfo)
{
	return (TRUE);
}
