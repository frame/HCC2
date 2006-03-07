// ComponentDialog.cpp : implementation file
//

#include "stdafx.h"
#include "HCC.h"
#include "ComponentDialog.h"
#include "AppData.h"
#include "Scheme.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define cInfoGridIndent 1150

/////////////////////////////////////////////////////////////////////////////
// CComponentDialog dialog


CComponentDialog::CComponentDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CComponentDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CComponentDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CComponentDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CComponentDialog)
	DDX_Control(pDX, IDC_TIERFILTER, m_cTierFilter);
	DDX_Control(pDX, IDC_SIZINGTITLEBOX, m_cSizingTitleBox);
	DDX_Control(pDX, IDC_SIZINGBOX, m_cSizingBox);
	DDX_Control(pDX, IDC_COMPTREE, m_cCompTree);
	DDX_Control(pDX, IDC_COMPFILTER, m_cCompFilter);
	DDX_Control(pDX, IDC_RESOURCEGRID, m_cResourceGrid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CComponentDialog, CDialog)
	//{{AFX_MSG_MAP(CComponentDialog)
	ON_WM_WINDOWPOSCHANGING ()
	ON_WM_GETMINMAXINFO()
	ON_CBN_SELCHANGE(IDC_COMPFILTER, OnSelchangeCompfilter)
	ON_NOTIFY(TVN_SELCHANGED, IDC_COMPTREE, OnSelchangedComptree)
	ON_COMMAND(ID_OPTIONS_SNAPSHOTWINDOW, OnOptionsSnapshotwindow)
	ON_COMMAND(ID_OPTIONS_RESTOREWINDOW, OnOptionsRestorewindow)
	ON_WM_SIZE()
	ON_COMMAND(ID_HELP_INDEX, OnHelpIndex)
	ON_WM_MOVE()
	ON_COMMAND(ID_WINDOW_ALWAYSONTOP, OnWindowAlwaysontop)
	ON_CBN_SELCHANGE(IDC_TIERFILTER, OnSelchangeTierfilter)
	ON_WM_CLOSE()
	ON_WM_CANCELMODE()
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComponentDialog message handlers

CComponentDialog::StartUp()
{
	this->Create (IDD_COMPONENTDIALOG, CWnd::GetDesktopWindow ());
	m_cWindowState.m_bLoaded = true;
}

CComponentDialog::Initialise()
{
	//m_cTechTree.SetImageList (&CAppData::m_cTechImages.m_cImageList, TVSIL_NORMAL);
	l_bUpdating = false;
	m_cCompTree.SetBkColor (CScheme::GetColour ("TREE_BACKCOLOUR"));
	DisplayComponentTypes ();
	DrawCompTree ();

	m_cResourceGrid.SetRows (0);
	m_cResourceGrid.SetFormatString (">Col1|<Col2");
	m_cResourceGrid.SetColWidth (0, cInfoGridIndent);
	m_cResourceGrid.SetColWidth (1, 2700);
	m_cResourceGrid.SetColAlignment (0, 7);
	m_cResourceGrid.SetColAlignment (1, 1);
	m_cResourceGrid.SetBackColor (CScheme::GetColour ("GRID_INFOBACKCOLOUR"));
	m_cResourceGrid.SetBackColorBkg (CScheme::GetColour ("GRID_INFOBACKCOLOUR"));
	m_cResourceGrid.SetGridColorFixed (CScheme::GetColour ("GRID_INFOBACKCOLOUR"));
	m_cResourceGrid.SetForeColorSel (CScheme::GetColour ("SELECTCOLOUR_FG"));
	m_cResourceGrid.SetBackColorSel (CScheme::GetColour ("SELECTCOLOUR_BG"));

}

void CComponentDialog::OnClose() 
{
	CAppData::SetComponentWindow (false);
	
	CDialog::OnClose();
}

void CComponentDialog::OnOK() 
{
}

BOOL CComponentDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
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
					return false;

			}
		}
		break;
	}

	return CDialog::OnNotify(wParam, lParam, pResult);
}

void CComponentDialog::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	m_cOS_ComponentTree.Resize ();
	m_cOS_ComponentGrid.Resize ();
	m_cOS_SizingBox.Resize ();
	m_cOS_SizingTitleBox.Resize ();

	if (m_cWindowState.m_bLoaded)
	{
		CRect l_cRect;
		m_cResourceGrid.GetClientRect (l_cRect);

		m_cResourceGrid.SetColWidth (0, cInfoGridIndent);
		m_cResourceGrid.SetColWidth (1, CAppData::ConvertScreenWidthToGrid (l_cRect.Width()) - cInfoGridIndent);
	}
}

void CComponentDialog::OnGetMinMaxInfo (MINMAXINFO FAR* lpMMI) 
{
	CDialog::OnGetMinMaxInfo (lpMMI);

	lpMMI->ptMinTrackSize.x = 380;
	lpMMI->ptMinTrackSize.y = 200;
	lpMMI->ptMaxTrackSize.x = 600;
	lpMMI->ptMaxTrackSize.y = 1280;

}

BOOL CComponentDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
   //remove some options from the system menu 
   CMenu* pSysMenu = GetSystemMenu(FALSE); 
   pSysMenu->RemoveMenu(SC_RESTORE,MF_BYCOMMAND); 
   pSysMenu->RemoveMenu(SC_MINIMIZE,MF_BYCOMMAND); 
   pSysMenu->RemoveMenu(SC_MAXIMIZE,MF_BYCOMMAND); 
   pSysMenu->RemoveMenu(SC_TASKLIST ,MF_BYCOMMAND); 

	m_cOS_ComponentTree.InitState		(m_cCompTree,				*this, NULL,						NULL,	0.4f, 1.0f);
	m_cOS_ComponentGrid.InitState		(m_cResourceGrid,			*this, &m_cOS_ComponentTree,	NULL,	0.6f, 1.0f);
	m_cOS_SizingBox.InitState			(m_cSizingBox,				*this, &m_cOS_ComponentTree,	NULL,	0.6f, 0.0f, NULL);
	m_cOS_SizingTitleBox.InitState	(m_cSizingTitleBox,		*this, &m_cOS_ComponentTree,	NULL,	0.6f, 0.0f, NULL);

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

CComponentDialog::DrawCompTree()
{
	CComponent l_cComponent;
	POSITION l_Pos;
	CString l_csType;
	CString l_csTier;
	int l_iTier;

	this->LockWindowUpdate ();
	l_bUpdating = true;
	m_cCompTree.DeleteAllItems ();
	m_cCompFilter.GetWindowText (l_csType);
	m_cTierFilter.GetWindowText (l_csTier);
	l_iTier = CAppData::GetTierLevel (l_csTier);

	l_Pos = CAppData::m_clComponentList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cComponent = CAppData::m_clComponentList.GetNext (l_Pos);
		if (((l_cComponent.m_csType == l_csType) || (l_csType == "All Types")) &&
			 ((l_cComponent.m_iTier == l_iTier) || (l_iTier == 0)))
		{
			m_cCompTree.InsertItem (l_cComponent.m_csComponentName, 0, 0, TVI_ROOT, TVI_LAST);
		}
	}

	m_cCompTree.SortChildren (TVI_ROOT);
	l_bUpdating = false;
	this->UnlockWindowUpdate ();
}

CComponentDialog::DisplayComponentTypes()
{
	CComponent l_cComponent;
	POSITION l_Pos;

	CAppData::ClearComboBox (m_cCompFilter);
	m_cCompFilter.InsertString (-1, "All Types");

	l_Pos = CAppData::m_clComponentList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cComponent = CAppData::m_clComponentList.GetNext (l_Pos);
		if (m_cCompFilter.FindStringExact (0, l_cComponent.m_csType) == CB_ERR)
		{
			m_cCompFilter.InsertString (-1, l_cComponent.m_csType);
		}
	}

	m_cCompFilter.SetCurSel (0);
	m_cTierFilter.SetCurSel (0);

}

void CComponentDialog::OnSelchangeCompfilter() 
{
	DrawCompTree ();	
}

CComponentDialog::DisplayComponent()
{
	HTREEITEM l_TreeItem = m_cCompTree.GetSelectedItem ();
	CComponent *l_cpComponent;
	CCompGatherInfo *l_cpCompGatherInfo;
	CCompBonusInfo *l_cpCompBonusInfo;
	CString l_csCurComponent;
	CTechSet *l_cpTechSet;
	CTech		*l_cpTech;
	CTechTier *l_cpTechTier;
	CItemResource *l_cpItemResource;
	POSITION l_TechSetPos;
	POSITION l_TechPos;
	POSITION l_TechTierPos;
	POSITION l_Pos;
	POSITION l_BonusPos;
	bool l_bFirstLoc = true;
	bool l_bFirstTech = true;
	CString l_csValue;
	CString l_csKey;

	this->LockWindowUpdate ();

	l_csCurComponent = m_cCompTree.GetItemText (l_TreeItem);

	m_cResourceGrid.SetRows (0);

	if (CAppData::FindComponent (l_csCurComponent, &l_cpComponent))
	{
		AddTitleLine (l_cpComponent->m_csComponentName, GRID_TITLE);
		if (!l_cpComponent->m_csDescription.IsEmpty ())
		{
			AddTitleLine (l_cpComponent->m_csDescription, GRID_DESCRIPTION);
		}
		AddSummaryLine ("|", GRID_EFFECT);

		AddSummaryLine ("Type|" + l_cpComponent->m_csType + " (" + CAppData::GetTierName (l_cpComponent->m_iTier) + ")", GRID_EFFECT);
		l_csValue.Format ("%d", l_cpComponent->m_iBulk);
		AddSummaryLine ("Bulk|" + l_csValue, GRID_EFFECT);
		AddSummaryLine ("|", GRID_EFFECT);
		AddSummaryLine ("Sell Value|" + l_cpComponent->m_csPawnBuyPrice, GRID_REQUIREMENT);
		AddSummaryLine ("Buy Value|" + l_cpComponent->m_csPawnSellPrice, GRID_REQUIREMENT);

		if (!l_cpComponent->m_csVieloSellPrice.IsEmpty())
		{
			AddSummaryLine ("Vielo Cost|" + l_cpComponent->m_csVieloSellPrice, GRID_REQUIREMENT);
		}
		AddSummaryLine ("|", GRID_EFFECT);

		l_Pos = l_cpComponent->m_clCompGatherInfoList.GetHeadPosition ();
		while (l_Pos)
		{
			l_cpCompGatherInfo = l_cpComponent->m_clCompGatherInfoList.GetNext (l_Pos);
			AddSummaryLine ("Harvest With|" + l_cpCompGatherInfo->m_csTool, GRID_REQUIREMENT);
			AddSummaryLine ("Gather Rate|" + l_cpCompGatherInfo->m_csRate, GRID_EFFECT);
			l_csValue.Format ("%s to %s", l_cpCompGatherInfo->m_csMinLvl, l_cpCompGatherInfo->m_csOptLvl);
			AddSummaryLine ("Skill Needed|" + l_csValue + " " + l_cpCompGatherInfo->m_csSkill, GRID_EFFECT);

			l_csKey = "Bonuses";
			l_BonusPos = l_cpCompGatherInfo->m_clCompBonusInfoList.GetHeadPosition ();
			while (l_BonusPos)
			{
				l_cpCompBonusInfo = l_cpCompGatherInfo->m_clCompBonusInfoList.GetNext (l_BonusPos);
				l_csValue.Format ("%01.1f%% chance of %s x %s", atof(l_cpCompBonusInfo->m_csChance),
						                                      l_cpCompBonusInfo->m_csAmount,
																		  l_cpCompBonusInfo->m_csName);
				AddSummaryLine (l_csKey + "|" + l_csValue, GRID_BONUS);
				l_csKey.Empty ();
			}

			AddSummaryLine ("|", GRID_EFFECT);
		}

		l_TechSetPos = CAppData::m_clTechSetList.GetHeadPosition ();
		while (l_TechSetPos)
		{
			l_cpTechSet = CAppData::m_clTechSetList.GetNext (l_TechSetPos);

			l_TechPos = l_cpTechSet->m_clTechList.GetHeadPosition ();
			while (l_TechPos)
			{
				l_cpTech = l_cpTechSet->m_clTechList.GetNext (l_TechPos);
				l_TechTierPos = l_cpTech->m_clTechTierList.GetHeadPosition ();
				while (l_TechTierPos)
				{
					l_cpTechTier = l_cpTech->m_clTechTierList.GetNext (l_TechTierPos);
					
					if (l_cpTechTier->m_csTierName == CAppData::GetTierName (l_cpComponent->m_iTier))
					{
						l_Pos = l_cpTechTier->m_clResourceList.GetHeadPosition ();
						while (l_Pos)
						{
							l_cpItemResource = l_cpTechTier->m_clResourceList.GetNext (l_Pos);
							if (l_cpItemResource->m_csName == l_cpComponent->m_csComponentName)
							{
								if (l_bFirstTech)
								{
									l_bFirstTech = false;
									AddSummaryLine ("Used By|" + l_cpTechTier->m_csName, GRID_TECHLIST);
								}
								else
								{
									AddSummaryLine ("|" + l_cpTechTier->m_csName, GRID_TECHLIST);
								}
							}
						}
					}
				}
			}
		}


		AddSummaryLine (" ");

		if (l_cpComponent->m_csLocations.GetCount () > 0)
		{
			l_Pos = l_cpComponent->m_csLocations.GetHeadPosition ();
			while (l_Pos)
			{
				if (l_bFirstLoc)
				{
					l_bFirstLoc = false;
					AddSummaryLine ("Location|" + l_cpComponent->m_csLocations.GetNext (l_Pos), GRID_BONUS);
				}
				else
				{
					AddSummaryLine ("|" + l_cpComponent->m_csLocations.GetNext (l_Pos), GRID_BONUS);
				}
			}
			AddSummaryLine (" ");
		}

	}
	
	this->UnlockWindowUpdate ();

}

void CComponentDialog::OnSelchangedComptree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	if (!l_bUpdating)
	{
		DisplayComponent ();
	}

	*pResult = 0;
}

CComponentDialog::AddTitleLine(CString a_csName, int a_iStyle)
{
	m_cResourceGrid.AddTitleRow (a_csName, a_iStyle, &m_cSizingTitleBox);
}

CComponentDialog::AddSummaryLine(CString a_csName, int a_iStyle)
{
	m_cResourceGrid.AddRow (a_csName, a_iStyle, &m_cSizingBox);
}


void CComponentDialog::OnOptionsSnapshotwindow() 
{
	CAppData::SetCompWindowState ();
}

void CComponentDialog::OnOptionsRestorewindow() 
{
	CAppData::GetCompWindowState ();
}


void CComponentDialog::OnHelpIndex() 
{
	CAppData::LaunchWebLink ((CString) "componentwindow");	
}

void CComponentDialog::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
	
}

void CComponentDialog::OnWindowPosChanging( WINDOWPOS* lpwndpos )
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

	if (CAppData::m_cTechSelectionWnd.m_cWindowState.m_bVisible)
	{
		m_cWindowState.SnapToWnd (lpwndpos, &l_cRect, &CAppData::m_cTechSelectionWnd, CAppData::m_iStickyStrength);
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

void CComponentDialog::OnWindowAlwaysontop() 
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

void CComponentDialog::OnSelchangeTierfilter() 
{
	DrawCompTree ();		
}

BOOL CComponentDialog::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	return (TRUE);
}
