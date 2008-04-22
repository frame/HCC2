// ReportDialog.cpp : implementation file
//

#include "stdafx.h"
#include "HCC.h"
#include "ReportDialog.h"
#include "OrderItem.h"
#include "AppData.h"
#include "Scheme.h"
#include "Regexp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define REPORT_SORTBYNAME 0
#define REPORT_SORTBYQTY 1

#define REPORT_ORDERCOMPS 0
#define REPORT_ORDER 1
#define REPORT_COMPS 2
#define REPORT_BONUS 3

#define SpinSpeeds 4
UDACCEL CellSpinSpeeds [SpinSpeeds] =	{
													{0,1},
													{1,2},
													{2,4},
													{4,8},
													};

/////////////////////////////////////////////////////////////////////////////
// CReportDialog dialog


CReportDialog::CReportDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CReportDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReportDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CReportDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportDialog)
	DDX_Control(pDX, IDC_QTYSPIN, m_cQtySpin);
	DDX_Control(pDX, IDC_REPORTTYPE, m_cReportType);
	DDX_Control(pDX, IDC_REPORTFORMAT, m_cReportFormat);
	DDX_Control(pDX, IDC_GENERATEBUTTON, m_cGenerateButton);
	DDX_Control(pDX, IDC_REPORTGRID, m_cReportGrid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReportDialog, CDialog)
	//{{AFX_MSG_MAP(CReportDialog)
	ON_WM_WINDOWPOSCHANGING ()
	ON_BN_CLICKED(IDC_GENERATEBUTTON, OnGeneratebutton)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_CLOSE()
	ON_COMMAND(ID_OPTIONS_SNAPSHOTWINDOW, OnOptionsSnapshotwindow)
	ON_COMMAND(ID_OPTIONS_RESTOREWINDOW, OnOptionsRestorewindow)
	ON_COMMAND(ID_OPTIONS_ORDERBY_RESOURCETYPE, OnOptionsOrderbyResourcetype)
	ON_COMMAND(ID_OPTIONS_ORDERBY_QUANTITY, OnOptionsOrderbyQuantity)
	ON_COMMAND(ID_HELP_INDEX, OnHelpIndex)
	ON_COMMAND(ID_OPTIONS_RESOURCEBREAKDOWN_SHOWFORMULARESOURCE, OnOptionsResourcebreakdownShowformularesource)
	ON_COMMAND(ID_OPTIONS_SHOWSUBCOMPONENTS, OnOptionsShowsubcomponents)
	ON_COMMAND(ID_OPTIONS_SHOWBASERESOURCE, OnOptionsShowbaseresource)
	ON_NOTIFY(UDN_DELTAPOS, IDC_QTYSPIN, OnDeltaposQtyspin)
	ON_WM_MOVE()
	ON_COMMAND(ID_WINDOW_ALWAYSONTOP, OnWindowAlwaysontop)
	ON_WM_MOUSEWHEEL()
	ON_WM_HELPINFO()
	ON_CBN_SELCHANGE(IDC_REPORTTYPE, OnSelchangeReporttype)
	ON_COMMAND(ID_OPTIONS_BONUSES_DIRECTONLY, OnOptionsBonusesDirectonly)
	ON_COMMAND(ID_OPTIONS_BONUSES_ALL, OnOptionsBonusesAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportDialog message handlers

CReportDialog::StartUp()
{
	this->Create (IDD_REPORTDIALOG, CWnd::GetDesktopWindow ());
	m_cWindowState.m_bLoaded = true;
}


void CReportDialog::OnGeneratebutton()
{
	if (m_cReportFormat.GetCurSel() == 0)
	{
		GenerateDirectReport ();
	}
	else if (m_cReportFormat.GetCurSel() == 1)
	{
		GenerateDirectReport ();
		ExportToHTML (CAppData::m_csTmpDir + cFile_App_ReportHTML);
	}
	else
	{
		GenerateDirectReport ();
		ExportToClipboard ();
	}
}

CReportDialog::GenerateOrderList()
{
	POSITION l_OrderPos;
	POSITION l_ItemPos;
	COrderItem l_cOrderItem;
	CItemTech l_cItemTech;
	CString l_csStr;
	CTech *l_cpTech = NULL;
	CTechTier *l_cpTechTier = NULL;
	bool	l_bFirstRow;
	int l_iRowHighlight = GRID_REPORT1;
	int l_iSelected = ReportSelection();
	bool l_bReport = false;
	bool l_bReportSelection = l_iSelected > 0;
	bool l_bReportSubTree = false;

	if (l_bReportSelection)
	{
		l_csStr.Format ("Reports - %d of %d Selected", l_iSelected, CAppData::m_clOrderList.GetCount ());
	}
	else
	{
		l_csStr.Format ("Reports - %d of %d Selected", CAppData::m_clOrderList.GetCount (), CAppData::m_clOrderList.GetCount ());
	}

	this->SetWindowText (l_csStr);

	m_cReportGrid.AddRow ("Craft Item|Batches|Techniques", GRID_REPORTTITLE);

	if (CAppData::m_cOrderWnd.m_cWindowState.m_bLoaded)
	{
		HTREEITEM l_ParentTreeItem = CAppData::m_cOrderWnd.m_cItemTree.GetRootItem ();
		HTREEITEM l_ChildTreeItem;

		while (l_ParentTreeItem)
		{
			l_bReportSubTree = CAppData::m_cOrderWnd.m_cItemTree.GetCheck (l_ParentTreeItem) != FALSE;
			l_ChildTreeItem = CAppData::m_cOrderWnd.m_cItemTree.GetChildItem (l_ParentTreeItem);
			while (l_ChildTreeItem)
			{
				if ((!l_bReportSelection) || (l_bReportSubTree) || (CAppData::m_cOrderWnd.m_cItemTree.GetCheck (l_ChildTreeItem)))
				{
					if (CAppData::FindOrderItem (CAppData::m_cOrderWnd.m_cItemTree.GetItemData (l_ChildTreeItem), l_cOrderItem))
					{
						l_bReport = true;
						l_bFirstRow= true;

						l_ItemPos = l_cOrderItem.m_clTechList.GetHeadPosition ();
						while (l_ItemPos)
						{
							l_cItemTech = l_cOrderItem.m_clTechList.GetNext (l_ItemPos);

							if (CAppData::FindTech (l_cItemTech.m_csCategory, l_cItemTech.m_csTechName, &l_cpTech))
							{

								if (l_cpTech->FindTechTier (l_cItemTech.m_csTierName, &l_cpTechTier))
								{
									if (l_bFirstRow)
									{
										l_bFirstRow = false;
										l_csStr.Format ("%s|%d|%s", l_cOrderItem.m_csItemName, l_cOrderItem.m_iQty, l_cpTechTier->m_csName);
									}
									else
									{
										l_csStr.Format ("||%s", l_cpTechTier->m_csName);
									}

									m_cReportGrid.AddRow (l_csStr, l_iRowHighlight);
								}
							}
						}

						if (l_bFirstRow)
						{
							l_csStr.Format ("%s|%d|(none)", l_cOrderItem.m_csItemName, l_cOrderItem.m_iQty);
							m_cReportGrid.AddRow (l_csStr, l_iRowHighlight);
						}

						m_cReportGrid.AddRow ("|", l_iRowHighlight);

						if (l_iRowHighlight == GRID_REPORT1)
						{
							l_iRowHighlight = GRID_REPORT2;
						}
						else
						{
							l_iRowHighlight = GRID_REPORT1;
						}
					}
				}

				l_ChildTreeItem = CAppData::m_cOrderWnd.m_cItemTree.GetNextSiblingItem (l_ChildTreeItem);
			}

			l_ParentTreeItem = CAppData::m_cOrderWnd.m_cItemTree.GetNextSiblingItem (l_ParentTreeItem);
		}
	}
	else
	{
		l_OrderPos = CAppData::m_clOrderList.GetHeadPosition ();
		while (l_OrderPos)
		{
			l_cOrderItem = CAppData::m_clOrderList.GetNext (l_OrderPos);
			l_bReport = true;
			l_bFirstRow= true;

			l_ItemPos = l_cOrderItem.m_clTechList.GetHeadPosition ();
			while (l_ItemPos)
			{
				l_cItemTech = l_cOrderItem.m_clTechList.GetNext (l_ItemPos);

				if (CAppData::FindTech (l_cItemTech.m_csCategory, l_cItemTech.m_csTechName, &l_cpTech))
				{

					if (l_cpTech->FindTechTier (l_cItemTech.m_csTierName, &l_cpTechTier))
					{
						if (l_bFirstRow)
						{
							l_bFirstRow = false;
							l_csStr.Format ("%s|%d|%s", l_cOrderItem.m_csItemName, l_cOrderItem.m_iQty, l_cpTechTier->m_csName);
						}
						else
						{
							l_csStr.Format ("||%s", l_cpTechTier->m_csName);
						}

						m_cReportGrid.AddRow (l_csStr, l_iRowHighlight);
					}
				}
			}

			if (l_bFirstRow)
			{
				l_csStr.Format ("%s|%d|(none)", l_cOrderItem.m_csItemName, l_cOrderItem.m_iQty);
				m_cReportGrid.AddRow (l_csStr, l_iRowHighlight);
			}

			m_cReportGrid.AddRow ("|", l_iRowHighlight);

			if (l_iRowHighlight == GRID_REPORT1)
			{
				l_iRowHighlight = GRID_REPORT2;
			}
			else
			{
				l_iRowHighlight = GRID_REPORT1;
			}
		}
	}

	if (!l_bReport)
	{
		m_cReportGrid.AddRow ("None|", l_iRowHighlight);
	}

}

CReportDialog::GenerateResourceList()
{
	POSITION l_OrderPos;
	POSITION l_Pos;
	POSITION l_ListPos;
	POSITION l_ListPrevPos;
	COrderItem l_cOrderItem;
	CItemTech l_cItemTech;
	CTechTier	*l_cpTechTier = NULL;
	POSITION l_ResourcePos;
	CItemResource *l_cpTechResource;
	CItemResource *l_cpItemResource;
	CItemResource *l_cpReportItemResource;
	CItemResource *l_cpListItemResource;
	CFormulaTier *l_cpFormulaTier;
	CTypedPtrList<CPtrList,  CItemResource*> l_clResourceList;
	bool l_bFound;
	int l_iRowHighlight = GRID_REPORT1;
	CString l_csStr;
	int l_iResourceStartRow = m_cReportGrid.GetRows () + 1;
	int l_iSkillAdjust = 0;
	bool l_bReport = false;
	bool l_bReportSelection = ReportSelection() > 0;
	bool l_bReportSubTree = false;

	m_cReportGrid.AddRow ("Component Name||Quantity", GRID_REPORTTITLE);

	if (CAppData::m_cOrderWnd.m_cWindowState.m_bLoaded)
	{
		HTREEITEM l_ParentTreeItem = CAppData::m_cOrderWnd.m_cItemTree.GetRootItem ();
		HTREEITEM l_ChildTreeItem;

		while (l_ParentTreeItem)
		{
			l_bReportSubTree = CAppData::m_cOrderWnd.m_cItemTree.GetCheck (l_ParentTreeItem) != FALSE;
			l_ChildTreeItem = CAppData::m_cOrderWnd.m_cItemTree.GetChildItem (l_ParentTreeItem);
			while (l_ChildTreeItem)
			{
				if ((!l_bReportSelection) || (l_bReportSubTree) || (CAppData::m_cOrderWnd.m_cItemTree.GetCheck (l_ChildTreeItem)))
				{
					if (CAppData::FindOrderItem (CAppData::m_cOrderWnd.m_cItemTree.GetItemData (l_ChildTreeItem), l_cOrderItem))
					{
						l_bReport = true;
						l_iSkillAdjust = 0;

						l_Pos = l_cOrderItem.m_clTechList.GetHeadPosition ();
						while (l_Pos)
						{
							l_cItemTech = l_cOrderItem.m_clTechList.GetNext (l_Pos);

							if (CAppData::FindTechTier (l_cItemTech.m_csCategory, l_cItemTech.m_csTechName, l_cItemTech.m_csTierName, &l_cpTechTier))
							{
								l_iSkillAdjust += l_cpTechTier->m_iSkillAdjust;

								l_ResourcePos = l_cpTechTier->m_clResourceList.GetHeadPosition ();
								while (l_ResourcePos)
								{
									l_cpTechResource = l_cpTechTier->m_clResourceList.GetNext (l_ResourcePos);
									l_bFound = false;

									l_ListPos = l_clResourceList.GetHeadPosition ();
									while (l_ListPos)
									{
										l_ListPrevPos = l_ListPos;
										l_cpListItemResource = l_clResourceList.GetNext (l_ListPos);
										if (l_cpListItemResource->m_csName == l_cpTechResource->m_csName)
										{
											l_cpListItemResource->m_iMinAmt += (l_cpTechResource->m_iMinAmt * l_cOrderItem.m_iQty);
											l_ListPos = NULL;
											l_bFound = true;
										}
									}

									if (!l_bFound)
									{
										l_cpListItemResource = new CItemResource;
										l_cpListItemResource->m_csName = l_cpTechResource->m_csName;
										l_cpListItemResource->m_csSkill = l_cpTechResource->m_csSkill;
										l_cpListItemResource->m_iMinAmt = l_cpTechResource->m_iMinAmt * l_cOrderItem.m_iQty;
										l_cpListItemResource->m_iMinLvl = 0;
										l_cpListItemResource->m_iOptLvl = 0;
										l_clResourceList.AddTail (l_cpListItemResource);
									}
								}
							}
						}

						if (CAppData::FindFormulaTier (l_cOrderItem.m_csCategory, l_cOrderItem.m_csFormulaName, l_cOrderItem.m_csTierName, &l_cpFormulaTier))
						{
							l_ResourcePos = l_cpFormulaTier->m_clResourceList.GetHeadPosition ();
							while (l_ResourcePos)
							{
								l_cpItemResource = l_cpFormulaTier->m_clResourceList.GetNext (l_ResourcePos);
								l_cpReportItemResource = new CItemResource;
								*l_cpReportItemResource = *l_cpItemResource;
								l_cpReportItemResource->m_iMinAmt = CAppData::CalculateEfficiency (l_cpItemResource, CAppData::m_cpCurrentProfile, l_iSkillAdjust) * l_cOrderItem.m_iQty;
								l_cpReportItemResource->m_iMinLvl = CAppData::CalculateEfficiencyPercentage (l_cpItemResource, CAppData::m_cpCurrentProfile, l_iSkillAdjust) * l_cOrderItem.m_iQty;
								l_cpReportItemResource->m_iOptLvl = l_cOrderItem.m_iQty;

								if (l_cpReportItemResource->m_iMinLvl < 0)
								{
									l_cpReportItemResource->m_iMinLvl = 0;
								}

								l_bFound = false;

								l_ListPos = l_clResourceList.GetHeadPosition ();
								while (l_ListPos)
								{
									l_ListPrevPos = l_ListPos;
									l_cpListItemResource = l_clResourceList.GetNext (l_ListPos);
									if (l_cpListItemResource->m_csName == l_cpReportItemResource->m_csName)
									{
										l_cpListItemResource->m_iMinAmt += l_cpReportItemResource->m_iMinAmt;
										l_cpListItemResource->m_iMinLvl += l_cpReportItemResource->m_iMinLvl;
										l_cpListItemResource->m_iOptLvl += l_cpReportItemResource->m_iOptLvl;
										l_ListPos = NULL;
										l_bFound = true;

										delete (l_cpReportItemResource);
										l_cpReportItemResource = NULL;
									}
								}

								if (!l_bFound)
								{
									l_clResourceList.AddTail (l_cpReportItemResource);
								}
							}
						}
					}
				}

				l_ChildTreeItem = CAppData::m_cOrderWnd.m_cItemTree.GetNextSiblingItem (l_ChildTreeItem);
			}

			l_ParentTreeItem = CAppData::m_cOrderWnd.m_cItemTree.GetNextSiblingItem (l_ParentTreeItem);
		}
	}
	else
	{
		l_OrderPos = CAppData::m_clOrderList.GetHeadPosition ();
		while (l_OrderPos)
		{
			l_cOrderItem = CAppData::m_clOrderList.GetNext (l_OrderPos);
			l_bReport = true;
			l_iSkillAdjust = 0;

			l_Pos = l_cOrderItem.m_clTechList.GetHeadPosition ();
			while (l_Pos)
			{
				l_cItemTech = l_cOrderItem.m_clTechList.GetNext (l_Pos);

				if (CAppData::FindTechTier (l_cItemTech.m_csCategory, l_cItemTech.m_csTechName, l_cItemTech.m_csTierName, &l_cpTechTier))
				{
					l_iSkillAdjust += l_cpTechTier->m_iSkillAdjust;

					l_ResourcePos = l_cpTechTier->m_clResourceList.GetHeadPosition ();
					while (l_ResourcePos)
					{
						l_cpTechResource = l_cpTechTier->m_clResourceList.GetNext (l_ResourcePos);
						l_bFound = false;

						l_ListPos = l_clResourceList.GetHeadPosition ();
						while (l_ListPos)
						{
							l_ListPrevPos = l_ListPos;
							l_cpListItemResource = l_clResourceList.GetNext (l_ListPos);
							if (l_cpListItemResource->m_csName == l_cpTechResource->m_csName)
							{
								l_cpListItemResource->m_iMinAmt += (l_cpTechResource->m_iMinAmt * l_cOrderItem.m_iQty);
								l_ListPos = NULL;
								l_bFound = true;
							}
						}

						if (!l_bFound)
						{
							l_cpListItemResource = new CItemResource;
							l_cpListItemResource->m_csName = l_cpTechResource->m_csName;
							l_cpListItemResource->m_csSkill = l_cpTechResource->m_csSkill;
							l_cpListItemResource->m_iMinAmt = l_cpTechResource->m_iMinAmt * l_cOrderItem.m_iQty;
							l_cpListItemResource->m_iMinLvl = 0;
							l_cpListItemResource->m_iOptLvl = 0;
							l_clResourceList.AddTail (l_cpListItemResource);
						}
					}
				}
			}

			if (CAppData::FindFormulaTier (l_cOrderItem.m_csCategory, l_cOrderItem.m_csFormulaName, l_cOrderItem.m_csTierName, &l_cpFormulaTier))
			{
				l_ResourcePos = l_cpFormulaTier->m_clResourceList.GetHeadPosition ();
				while (l_ResourcePos)
				{
					l_cpItemResource = l_cpFormulaTier->m_clResourceList.GetNext (l_ResourcePos);
					l_cpReportItemResource = new CItemResource;
					*l_cpReportItemResource = *l_cpItemResource;
					l_cpReportItemResource->m_iMinAmt = CAppData::CalculateEfficiency (l_cpItemResource, CAppData::m_cpCurrentProfile, l_iSkillAdjust) * l_cOrderItem.m_iQty;
					l_cpReportItemResource->m_iMinLvl = CAppData::CalculateEfficiencyPercentage (l_cpItemResource, CAppData::m_cpCurrentProfile, l_iSkillAdjust) * l_cOrderItem.m_iQty;
					l_cpReportItemResource->m_iOptLvl = l_cOrderItem.m_iQty;

					if (l_cpReportItemResource->m_iMinLvl < 0)
					{
						l_cpReportItemResource->m_iMinLvl = 0;
					}

					l_bFound = false;

					l_ListPos = l_clResourceList.GetHeadPosition ();
					while (l_ListPos)
					{
						l_ListPrevPos = l_ListPos;
						l_cpListItemResource = l_clResourceList.GetNext (l_ListPos);
						if (l_cpListItemResource->m_csName == l_cpReportItemResource->m_csName)
						{
							l_cpListItemResource->m_iMinAmt += l_cpReportItemResource->m_iMinAmt;
							l_cpListItemResource->m_iMinLvl += l_cpReportItemResource->m_iMinLvl;
							l_cpListItemResource->m_iOptLvl += l_cpReportItemResource->m_iOptLvl;
							l_ListPos = NULL;
							l_bFound = true;

							delete (l_cpReportItemResource);
							l_cpReportItemResource = NULL;
						}
					}

					if (!l_bFound)
					{
						l_clResourceList.AddTail (l_cpReportItemResource);
					}
				}
			}
		}
	}

	if (CAppData::m_iShowReportResourceMode == 2)
	{
		ConvertToBaseResources (l_clResourceList);
	}

	SortResources (l_clResourceList, CAppData::m_iShowReportMode);

	l_ListPos = l_clResourceList.GetHeadPosition ();
	while (l_ListPos)
	{
		l_cpListItemResource = l_clResourceList.GetNext (l_ListPos);
		l_csStr.Format ("%s||0/%d", l_cpListItemResource->m_csName, l_cpListItemResource->m_iMinAmt);
		m_cReportGrid.AddRow (l_csStr, l_iRowHighlight);

		if (CAppData::m_iShowReportResourceMode == 1)
		{
			AddToResources (l_cpListItemResource, GRID_SUBRESOURCE, l_cpListItemResource->m_iMinAmt);
		}

		if (l_iRowHighlight == GRID_REPORT1)
		{
			l_iRowHighlight = GRID_REPORT2;
		}
		else
		{
			l_iRowHighlight = GRID_REPORT1;
		}
	}

	if (!l_bReport)
	{
		m_cReportGrid.AddRow ("None|", l_iRowHighlight);
	}

	// Clear out resource list
	l_ListPos = l_clResourceList.GetHeadPosition ();
	while (l_ListPos)
	{
		l_cpListItemResource = l_clResourceList.GetNext (l_ListPos);
		delete (l_cpListItemResource);
	}
}

CReportDialog::DetermineIndirectBonus(CString a_csBonusName, int a_iAmount, CTypedPtrList<CPtrList,  CItemResource*> &a_clResourceList)
{
	CTech *l_cpTech;
	CTechSet *l_cpTechSet;
	CItemResource *l_cpListItemResource;
	int l_iBonus = 0;
	POSITION l_SetPos;
	POSITION l_Pos;
	POSITION l_TechPos;
	POSITION l_ListPos;
	CEffect *l_cpEffect;
	char l_cBonusName[256];
	CString l_csBonusName;
	int l_iBonusAmount;
	bool l_bFound;

	l_SetPos = CAppData::m_clTechSetList.GetHeadPosition ();

	while (l_SetPos)
	{
		l_cpTechSet = CAppData::m_clTechSetList.GetNext (l_SetPos);
		//if (l_cpTechSet->m_csCategory == "Craft")
		{
			l_TechPos = l_cpTechSet->m_clTechList.GetHeadPosition ();

			while (l_TechPos)
			{
				l_cpTech = l_cpTechSet->m_clTechList.GetNext (l_TechPos);

				l_Pos = l_cpTech->m_clEffectsList.GetHeadPosition ();
				while (l_Pos)
				{
					l_cpEffect = l_cpTech->m_clEffectsList.GetNext (l_Pos);
					if (l_cpEffect->m_csType == cXMLAttribute_StatBonus)
					{
						sscanf (l_cpEffect->m_csDescription, "%d%% %s", &l_iBonusAmount, l_cBonusName);
						l_csBonusName.Format ("%s", l_cBonusName);
						l_iBonusAmount = ((a_iAmount * l_iBonusAmount) / 1000);
						l_bFound = false;

						if ((a_csBonusName == l_csBonusName) && (l_iBonusAmount > 0))
						{
							l_ListPos = a_clResourceList.GetHeadPosition ();
							while (l_ListPos)
							{
								l_cpListItemResource = a_clResourceList.GetNext (l_ListPos);
								if (l_cpListItemResource->m_csName == l_cpTech->m_csName)
								{
									l_cpListItemResource->m_csSkill = "Both";
									l_cpListItemResource->m_iMinAmt += l_iBonusAmount;
									l_ListPos = NULL;
									l_bFound = true;
								}
							}

							if (!l_bFound)
							{
								l_cpListItemResource = new CItemResource;
								l_cpListItemResource->m_csName = l_cpTech->m_csName;
								l_cpListItemResource->m_csSkill = "Indirect";
								l_cpListItemResource->m_iMinAmt = l_iBonusAmount;
								l_cpListItemResource->m_iMinLvl = 0;
								l_cpListItemResource->m_iOptLvl = 0;
								a_clResourceList.AddTail (l_cpListItemResource);
							}
						}
					}
				}
			}
		}
	}

}

CReportDialog::GenerateBonusFromList(int a_iQty, CTypedPtrList<CPtrList, CEffect*>	&a_clEffectsList, CTypedPtrList<CPtrList,  CItemResource*> &a_clResourceList)
{
	CEffect *l_cpEffect;
	CItemResource *l_cpListItemResource;
	POSITION l_ListPos;
	CString l_csBonusName, l_iBonusValue_tmp;
	int l_iBonusAmount;
	POSITION l_EffectPos;
	bool l_bFound;
	int l_iOffset, l_iOffset_tmp;

	l_EffectPos = a_clEffectsList.GetHeadPosition ();
	while (l_EffectPos)
	{
		l_cpEffect = a_clEffectsList.GetNext (l_EffectPos);

		if (l_cpEffect->m_csType == cXMLAttribute_Bonus)
		{
			l_iOffset = l_cpEffect->m_csDescription.Find (' ');
			l_iBonusAmount = atoi (l_cpEffect->m_csDescription.Left (l_iOffset));
			l_csBonusName = l_cpEffect->m_csDescription.Mid (l_iOffset + 1);
			l_bFound = false;

			l_ListPos = a_clResourceList.GetHeadPosition ();
			while (l_ListPos)
			{
				l_cpListItemResource = a_clResourceList.GetNext (l_ListPos);
				if (l_cpListItemResource->m_csName == l_csBonusName)
				{
					l_cpListItemResource->m_iMinAmt += (l_iBonusAmount * a_iQty);
					l_ListPos = NULL;
					l_bFound = true;
				}
			}

			if (!l_bFound)
			{
				l_cpListItemResource = new CItemResource;
				l_cpListItemResource->m_csName = l_csBonusName;
				l_cpListItemResource->m_csSkill = "Direct";
				l_cpListItemResource->m_iMinAmt = (l_iBonusAmount * a_iQty);
				l_cpListItemResource->m_iMinLvl = 0;
				l_cpListItemResource->m_iOptLvl = 0;
				a_clResourceList.AddTail (l_cpListItemResource);
			}
		}
		else if (l_cpEffect->m_csType == cXMLAttribute_Timer)
		{
			//RESUMEWORKHERE

			l_iOffset = l_cpEffect->m_csDescription.ReverseFind(' ');
			CString ;
			l_iBonusValue_tmp = l_cpEffect->m_csDescription.Mid (l_iOffset);

			//int i_minutes;

			Regexp re("(.*)[\t ]*([0-9]*):([0-9]*):([0-9]*)");
			if ( re.Match( l_iBonusValue_tmp ) )
			{
				l_iBonusAmount = (atoi(re[1]) * 60) + atoi(re[3]);

//				AfxMessageBox (re[3] + " Minutes", MB_ICONINFORMATION); // min
//				AfxMessageBox (re[1] + " Hours", MB_ICONINFORMATION);
			}
			else
			{

				Regexp re2("(.*)[\t ]*([0-9]*):([0-9]*)");
				if ( re2.Match( l_iBonusValue_tmp ) )
				{
					l_iBonusAmount = (atoi(re2[1]));
//					AfxMessageBox (re2[1] + "Minutes", MB_ICONINFORMATION);
				}
			}

			if (l_cpEffect->m_csDescription.Find("Death Points"))
			{
				//AfxMessageBox ("YESDP", MB_ICONINFORMATION);
				l_csBonusName = "Death Point time reduction";
			}
			else
			{
				//AfxMessageBox ("NODP", MB_ICONINFORMATION);
				l_csBonusName = l_cpEffect->m_csDescription.Left (l_iOffset);
			}


			l_bFound = false;

			l_ListPos = a_clResourceList.GetHeadPosition ();
			while (l_ListPos)
			{
				l_cpListItemResource = a_clResourceList.GetNext (l_ListPos);
				if (l_cpListItemResource->m_csName == l_csBonusName)
				{
					l_cpListItemResource->m_iMinAmt += (l_iBonusAmount * a_iQty);
					l_ListPos = NULL;
					l_bFound = true;
				}
			}

			if (!l_bFound)
			{
				l_cpListItemResource = new CItemResource;
				l_cpListItemResource->m_csName = l_csBonusName;
				l_cpListItemResource->m_csSkill = "Direct";
				l_cpListItemResource->m_iMinAmt = (l_iBonusAmount * a_iQty);
				l_cpListItemResource->m_iMinLvl = 0;
				l_cpListItemResource->m_iOptLvl = 0;
				a_clResourceList.AddTail (l_cpListItemResource);
			}
		}
	}
}

CReportDialog::GenerateBonusList()
{
	POSITION l_OrderPos;
	POSITION l_Pos;
	POSITION l_ListPos;
	COrderItem l_cOrderItem;
	CItemTech l_cItemTech;
	CTechTier	*l_cpTechTier = NULL;
	CItemResource *l_cpListItemResource;
	CFormula *l_cpFormula;
	CFormulaTier *l_cpFormulaTier;
	CTypedPtrList<CPtrList,  CItemResource*> l_clResourceList;
	int l_iRowHighlight = GRID_REPORT1;
	CString l_csStr;
	int l_iResourceStartRow = m_cReportGrid.GetRows () + 1;
	bool l_bReport = false;
	bool l_bReportSelection = ReportSelection() > 0;
	bool l_bReportSubTree = false;

	m_cReportGrid.AddRow ("Bonus|Type|Amount", GRID_REPORTTITLE);

	if (CAppData::m_cOrderWnd.m_cWindowState.m_bLoaded)
	{
		HTREEITEM l_ParentTreeItem = CAppData::m_cOrderWnd.m_cItemTree.GetRootItem ();
		HTREEITEM l_ChildTreeItem;

		while (l_ParentTreeItem)
		{
			l_bReportSubTree = CAppData::m_cOrderWnd.m_cItemTree.GetCheck (l_ParentTreeItem) != FALSE;
			l_ChildTreeItem = CAppData::m_cOrderWnd.m_cItemTree.GetChildItem (l_ParentTreeItem);
			while (l_ChildTreeItem)
			{
				if ((!l_bReportSelection) || (l_bReportSubTree) || (CAppData::m_cOrderWnd.m_cItemTree.GetCheck (l_ChildTreeItem)))
				{
					if (CAppData::FindOrderItem (CAppData::m_cOrderWnd.m_cItemTree.GetItemData (l_ChildTreeItem), l_cOrderItem))
					{
						l_bReport = true;

						l_Pos = l_cOrderItem.m_clTechList.GetHeadPosition ();
						while (l_Pos)
						{
							l_cItemTech = l_cOrderItem.m_clTechList.GetNext (l_Pos);

							if (CAppData::FindTechTier (l_cItemTech.m_csCategory, l_cItemTech.m_csTechName, l_cItemTech.m_csTierName, &l_cpTechTier))
							{
								GenerateBonusFromList (l_cOrderItem.m_iQty, l_cpTechTier->m_clEffectList, l_clResourceList);
							}
						}

						if (CAppData::FindFormula (l_cOrderItem.m_csCategory, l_cOrderItem.m_csFormulaName, &l_cpFormula))
						{
							GenerateBonusFromList (l_cOrderItem.m_iQty, l_cpFormula->m_clEffectsList, l_clResourceList);
						}

						if (CAppData::FindFormulaTier (l_cOrderItem.m_csCategory, l_cOrderItem.m_csFormulaName, l_cOrderItem.m_csTierName, &l_cpFormulaTier))
						{
							GenerateBonusFromList (l_cOrderItem.m_iQty, l_cpFormulaTier->m_clEffectsList, l_clResourceList);
						}
					}
				}

				l_ChildTreeItem = CAppData::m_cOrderWnd.m_cItemTree.GetNextSiblingItem (l_ChildTreeItem);
			}

			l_ParentTreeItem = CAppData::m_cOrderWnd.m_cItemTree.GetNextSiblingItem (l_ParentTreeItem);
		}
	}
	else
	{
		l_OrderPos = CAppData::m_clOrderList.GetHeadPosition ();
		while (l_OrderPos)
		{
			l_cOrderItem = CAppData::m_clOrderList.GetNext (l_OrderPos);
			l_bReport = true;

			l_Pos = l_cOrderItem.m_clTechList.GetHeadPosition ();
			while (l_Pos)
			{
				l_cItemTech = l_cOrderItem.m_clTechList.GetNext (l_Pos);

				if (CAppData::FindTechTier (l_cItemTech.m_csCategory, l_cItemTech.m_csTechName, l_cItemTech.m_csTierName, &l_cpTechTier))
				{
					GenerateBonusFromList (l_cOrderItem.m_iQty, l_cpTechTier->m_clEffectList, l_clResourceList);
				}
			}

			if (CAppData::FindFormula (l_cOrderItem.m_csCategory, l_cOrderItem.m_csFormulaName, &l_cpFormula))
			{
				GenerateBonusFromList (l_cOrderItem.m_iQty, l_cpFormula->m_clEffectsList, l_clResourceList);
			}

			if (CAppData::FindFormulaTier (l_cOrderItem.m_csCategory, l_cOrderItem.m_csFormulaName, l_cOrderItem.m_csTierName, &l_cpFormulaTier))
			{
				GenerateBonusFromList (l_cOrderItem.m_iQty, l_cpFormulaTier->m_clEffectsList, l_clResourceList);
			}
		}
	}

	if (CAppData::m_iShowReportBonusMode == 1)
	{
		CItemResource *l_cpStrength = NULL;
		CItemResource *l_cpPower = NULL;
		CItemResource *l_cpFocus = NULL;
		CItemResource *l_cpDexterity = NULL;

		l_ListPos = l_clResourceList.GetHeadPosition ();
		while (l_ListPos)
		{
			l_cpListItemResource = l_clResourceList.GetNext (l_ListPos);
			if (l_cpListItemResource->m_csName == "Strength")
			{
				l_cpStrength = l_cpListItemResource;
			}
			else if (l_cpListItemResource->m_csName == "Power")
			{
				l_cpPower = l_cpListItemResource;
			}
			else if (l_cpListItemResource->m_csName == "Focus")
			{
				l_cpFocus = l_cpListItemResource;
			}
			else if (l_cpListItemResource->m_csName == "Dexterity")
			{
				l_cpDexterity = l_cpListItemResource;
			}
		}

		if (l_cpStrength)
		{
			DetermineIndirectBonus (l_cpStrength->m_csName, l_cpStrength->m_iMinAmt, l_clResourceList);
		}

		if (l_cpPower)
		{
			DetermineIndirectBonus (l_cpPower->m_csName, l_cpPower->m_iMinAmt, l_clResourceList);
		}

		if (l_cpFocus)
		{
			DetermineIndirectBonus (l_cpFocus->m_csName, l_cpFocus->m_iMinAmt, l_clResourceList);
		}

		if (l_cpDexterity)
		{
			DetermineIndirectBonus (l_cpDexterity->m_csName, l_cpDexterity->m_iMinAmt, l_clResourceList);
		}
	}

	SortResources (l_clResourceList, CAppData::m_iShowReportMode);

	l_ListPos = l_clResourceList.GetHeadPosition ();

	int tmp_hours, tmp_minutes;
	CString tmp_time, c_hours, c_minutes;
	CString final_time;

	while (l_ListPos)
	{
		l_cpListItemResource = l_clResourceList.GetNext (l_ListPos);



		if (l_cpListItemResource->m_csName.Find("Death Point") != -1)
		{
			tmp_hours = (l_cpListItemResource->m_iMinAmt / 60);
			tmp_minutes = (l_cpListItemResource->m_iMinAmt % 60);

			c_hours.Format("%d", tmp_hours);
			if (tmp_hours < 10)
			{
				c_hours.Format("0%d", tmp_hours);
			}
			c_minutes.Format("%d", tmp_minutes);
			if (tmp_minutes < 10)
			{
				c_minutes.Format("0%d", tmp_minutes);
			}
			l_csStr.Format ("%s|%s|%s", l_cpListItemResource->m_csName, l_cpListItemResource->m_csSkill, c_hours + ":" + c_minutes + ":00");
		}
		else
		{
			l_csStr.Format ("%s|%s|%d", l_cpListItemResource->m_csName, l_cpListItemResource->m_csSkill, l_cpListItemResource->m_iMinAmt);
		}


		m_cReportGrid.AddRow (l_csStr, l_iRowHighlight);

		if (l_iRowHighlight == GRID_REPORT1)
		{
			l_iRowHighlight = GRID_REPORT2;
		}
		else
		{
			l_iRowHighlight = GRID_REPORT1;
		}
	}

	if (!l_bReport)
	{
		m_cReportGrid.AddRow ("None|", l_iRowHighlight);
	}

	// Clear out resource list
	l_ListPos = l_clResourceList.GetHeadPosition ();
	while (l_ListPos)
	{
		l_cpListItemResource = l_clResourceList.GetNext (l_ListPos);
		delete (l_cpListItemResource);
	}
}

CReportDialog::AddToResources(CItemResource *a_cpResource, int a_iStyle, int a_iBaseQty, int a_iIndent, int a_iSkillAdjust)
{
	CString l_csStr;
	int l_iLevel;
	CString l_csResourceName;
	CFormula *l_cpResourceFormula;
	CFormulaTier *l_cpResourceFormulaTier;
	POSITION l_Pos;
	CItemResource *l_cpItemResource;
	int l_iBaseQty;
	int l_iProfileQty;

	if (CAppData::FindResourceFormulaTier (a_cpResource->m_csName, &l_cpResourceFormula, &l_cpResourceFormulaTier))
	{

		l_Pos = l_cpResourceFormulaTier->m_clResourceList.GetHeadPosition ();
		while (l_Pos)
		{
			l_cpItemResource = l_cpResourceFormulaTier->m_clResourceList.GetNext (l_Pos);

			l_iProfileQty = CAppData::CalculateEfficiency (l_cpItemResource, CAppData::m_cpCurrentProfile, a_iSkillAdjust);

			if ((a_iBaseQty % l_cpResourceFormula->m_iBatchQty) == 0)
			{
				l_iBaseQty = (a_iBaseQty / l_cpResourceFormula->m_iBatchQty);
			}
			else
			{
				l_iBaseQty = (a_iBaseQty / l_cpResourceFormula->m_iBatchQty) + 1;
			}

			l_iBaseQty *= l_iProfileQty;
			l_csStr.Format ("-->%s||(0/%d)", l_cpItemResource->m_csName, l_iBaseQty);
			for (l_iLevel=0; l_iLevel<a_iIndent; l_iLevel++)
			{
				l_csStr = "--" + l_csStr;
			}

			m_cReportGrid.AddRow (l_csStr, a_iStyle);

			AddToResources (l_cpItemResource, a_iStyle, l_iBaseQty, a_iIndent + 1);
		}
	}
}

CReportDialog::GenerateDirectReport()
{
	this->LockWindowUpdate ();

	m_cReportGrid.SetRows (0);

	if (m_cReportType.GetCurSel() == REPORT_ORDERCOMPS)
	{
		GenerateOrderList ();
		m_cReportGrid.AddRow ("|", GRID_BLANK);
		GenerateResourceList ();
		UpdateComponentCounts ();
	}
	else if (m_cReportType.GetCurSel() == REPORT_ORDER)
	{
		GenerateOrderList ();
		m_cReportGrid.AddRow ("|", GRID_BLANK);
	}
	else if (m_cReportType.GetCurSel() == REPORT_COMPS)
	{
		GenerateResourceList ();
		UpdateComponentCounts ();
	}
	else if (m_cReportType.GetCurSel() == REPORT_BONUS)
	{
		GenerateBonusList ();
	}
	else
	{
		m_cReportGrid.AddRow ("None||", REPORT_ORDER);
	}

	Resize();
	this->UnlockWindowUpdate ();
}

BOOL CReportDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

   //remove some options from the system menu
   CMenu* pSysMenu = GetSystemMenu(FALSE);
   pSysMenu->RemoveMenu(SC_RESTORE,MF_BYCOMMAND);
   pSysMenu->RemoveMenu(SC_MINIMIZE,MF_BYCOMMAND);
   pSysMenu->RemoveMenu(SC_MAXIMIZE,MF_BYCOMMAND);
   pSysMenu->RemoveMenu(SC_TASKLIST ,MF_BYCOMMAND);

	m_cReportGrid.SetRows (0);
	m_cReportGrid.SetFormatString ("Item Name|^Batches|^Tech");
	m_cReportGrid.SetColWidth (0, 4500);
	m_cReportGrid.SetColWidth (1, 800);
	m_cReportGrid.SetColWidth (2, 1700);
	m_cReportGrid.SetBackColor (CScheme::GetColour ("GRID_REPORTBACKCOLOUR"));
	m_cReportGrid.SetBackColorBkg (CScheme::GetColour ("GRID_REPORTBACKCOLOUR"));
	m_cReportGrid.SetGridColor (CScheme::GetColour ("GRID_REPORTLINECOLOUR_LIGHT"));
	m_cReportGrid.SetGridColorFixed (CScheme::GetColour ("GRID_REPORTLINECOLOUR_DARK"));
	m_cReportGrid.SetForeColorSel (CScheme::GetColour ("SELECTCOLOUR_FG"));
	m_cReportGrid.SetBackColorSel (CScheme::GetColour ("SELECTCOLOUR_BG"));

	m_cOS_ReportGrid.InitState		(m_cReportGrid,	 *this, NULL,	NULL,	1.0f, 1.0f);
	m_cOS_GenerateButton.InitState	(m_cGenerateButton,	*this,  &m_cOS_ReportGrid,	NULL,	0.0f, 0.0f);

	m_cReportType.SetCurSel (CAppData::m_iReportType);
	m_cReportFormat.SetCurSel (0);
	UpdateOrderMenu();
	GenerateDirectReport ();

	m_cQtySpin.SetAccel (SpinSpeeds, CellSpinSpeeds);

	Resize();

	CMenu *l_pMenu;
	l_pMenu = GetMenu ();
	if (l_pMenu)
	{
		CAppData::SetMenuItem(l_pMenu, ID_WINDOW_ALWAYSONTOP, m_cWindowState.m_bOnTop);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CReportDialog::Resize()
{
	float l_fWidth;
	int l_iRows;
	int l_iHeightRows;
	int l_iTotalHeight;
	int l_iWndHeight;
	CRect l_cRect;
	int l_iAdjust = 0;

	m_cOS_ReportGrid.Resize ();
	m_cOS_GenerateButton.Resize ();

	l_iRows = m_cReportGrid.GetRows ();
	l_iHeightRows = m_cReportGrid.GetRowHeight (0);
	l_iTotalHeight = l_iRows * l_iHeightRows;
	m_cReportGrid.GetClientRect (&l_cRect);
	l_iWndHeight = CAppData::ConvertScreenWidthToGrid (l_cRect.Height());

	if (l_iWndHeight < l_iTotalHeight)
	{
		l_iAdjust = 300;
	}

	l_fWidth = (float) CAppData::ConvertScreenWidthToGrid (m_cOS_ReportGrid.m_iCurWidth) - 800 - 1700 - l_iAdjust;
	m_cReportGrid.SetColWidth (0, (long) (l_fWidth * 1.00f));
	m_cReportGrid.SetColWidth (1, 800);
	m_cReportGrid.SetColWidth (2, 1700);
}


void CReportDialog::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (m_cWindowState.m_bLoaded)
	{
		Resize ();
	}

}

void CReportDialog::OnGetMinMaxInfo (MINMAXINFO FAR* lpMMI)
{
	CDialog::OnGetMinMaxInfo (lpMMI);

	lpMMI->ptMinTrackSize.x = 330;
	lpMMI->ptMinTrackSize.y = 240;
	lpMMI->ptMaxTrackSize.x = 800;
	lpMMI->ptMaxTrackSize.y = 1280;

}


void CReportDialog::OnClose()
{
	CAppData::SetReportWindow (false);
	CDialog::OnClose();
}

void CReportDialog::OnOK()
{
}

void CReportDialog::OnOptionsSnapshotwindow()
{
	CAppData::SetReportWindowState ();
}

void CReportDialog::OnOptionsRestorewindow()
{
	CAppData::GetReportWindowState ();
}

void CReportDialog::OnOptionsOrderbyResourcetype()
{
	CAppData::m_iShowReportMode = 0;
	UpdateOrderMenu();

	GenerateDirectReport ();
}

void CReportDialog::OnOptionsOrderbyQuantity()
{
	CAppData::m_iShowReportMode = 1;
	UpdateOrderMenu();

	GenerateDirectReport ();
}

CReportDialog::UpdateOrderMenu()
{
	CMenu *l_pMenu;
	l_pMenu = GetMenu ();
	if (l_pMenu)
	{
		CAppData::SetMenuItem(l_pMenu, ID_OPTIONS_ORDERBY_RESOURCETYPE, CAppData::m_iShowReportMode == 0);
		CAppData::SetMenuItem(l_pMenu, ID_OPTIONS_ORDERBY_QUANTITY, CAppData::m_iShowReportMode == 1);
		CAppData::SetMenuItem(l_pMenu, ID_OPTIONS_RESOURCEBREAKDOWN_SHOWFORMULARESOURCE, CAppData::m_iShowReportResourceMode == 0);
		CAppData::SetMenuItem(l_pMenu, ID_OPTIONS_SHOWSUBCOMPONENTS, CAppData::m_iShowReportResourceMode == 1);
		CAppData::SetMenuItem(l_pMenu, ID_OPTIONS_SHOWBASERESOURCE, CAppData::m_iShowReportResourceMode == 2);
		CAppData::SetMenuItem(l_pMenu, ID_OPTIONS_BONUSES_DIRECTONLY, CAppData::m_iShowReportBonusMode == 0);
		CAppData::SetMenuItem(l_pMenu, ID_OPTIONS_BONUSES_ALL, CAppData::m_iShowReportBonusMode == 1);
	}
}

CReportDialog::ExportToClipboard()
{
	int i = 1;
	bool m_bPreviousLineBlank = false;
	bool m_bEndSection = false;
	CString l_csItem;
	CString l_csType;
	CString l_csBatches;
	CString l_csTech;
	CString l_csComp;
	CString l_csQty;
	bool	l_bQuantitiesFull = true;
	bool	l_bQuantitiesEmpty = true;
	int l_iCurQty;
	int l_iTotalQty;

	CString l_csOutput = "";

	i=1;
	while (i<m_cReportGrid.GetRows ())
	{
		l_csQty = m_cReportGrid.GetTextMatrix (i, 2);
		if (l_csQty.Find ('/') > 0)
		{
			sscanf (l_csQty, "%d/%d", &l_iCurQty, &l_iTotalQty);


			if (l_iCurQty != l_iTotalQty)
			{
				l_bQuantitiesFull = false;
			}

			if (l_iCurQty != 0)
			{
				l_bQuantitiesEmpty = false;
			}
		}

		i++;
	}

	if ((m_cReportType.GetCurSel() == REPORT_ORDERCOMPS) ||
		 (m_cReportType.GetCurSel() == REPORT_ORDER))
	{

		i=1;
		while ((i<m_cReportGrid.GetRows ()) && (!m_bEndSection))
		{
			if (m_cReportGrid.GetTextMatrix (i, 2) == "")
			{
				if (m_bPreviousLineBlank)
				{
					m_bEndSection = true;
				}
				else
				{
					m_bPreviousLineBlank = true;
				}
			}
			else
			{
				m_bPreviousLineBlank = false;
			}

			if (!m_bEndSection)
			{
				l_csItem = m_cReportGrid.GetTextMatrix (i, 0);
				l_csBatches = m_cReportGrid.GetTextMatrix (i, 1);
				l_csTech = m_cReportGrid.GetTextMatrix (i, 2);

				if (l_csItem != "None")
				{
					if (!l_csItem.IsEmpty ())
					{
						if (l_csTech != "(none)")
						{
							if (l_csBatches != "1")
							{
								l_csOutput += l_csBatches + " x " + l_csItem + " (" + l_csTech;
							}
							else
							{
								l_csOutput += l_csItem + " (" + l_csTech;
							}
						}
						else
						{
							if (l_csBatches != "1")
							{
								l_csOutput += l_csBatches + " x " + l_csItem + " (";
							}
							else
							{
								l_csOutput += l_csItem + " (";
							}
						}
					}
					else
					{
						if (l_csTech.IsEmpty ())
						{
							l_csOutput += "), \r\n";
						}
						else
						{
							l_csOutput += ", " + l_csTech;
						}
					}
				}
				else
				{
					m_bEndSection = true;
				}
			}

			i++;

		}

		i++;
	}

	if ((m_cReportType.GetCurSel() == REPORT_ORDERCOMPS) ||
		 (m_cReportType.GetCurSel() == REPORT_COMPS))
	{
		i=1;
		while (i<m_cReportGrid.GetRows ())
		{
			l_csComp = m_cReportGrid.GetTextMatrix (i, 0);
			l_csQty = m_cReportGrid.GetTextMatrix (i, 2);
			if (l_csQty.Find ('/') > 0)
			{
				l_csQty.Replace ("(", "");
				l_csQty.Replace (")", "");
				sscanf (l_csQty, "%d/%d", &l_iCurQty, &l_iTotalQty);

				if ((l_bQuantitiesFull) || (l_bQuantitiesEmpty))
				{
					l_csQty.Format ("%d", l_iTotalQty);
					l_csOutput += l_csQty + " " + l_csComp + ", \r\n";
				}
				else
				{
					l_csOutput += l_csQty + " " + l_csComp + ", \r\n";
				}
			}

			i++;

		}
	}

	if (m_cReportType.GetCurSel() == REPORT_BONUS)
	{

		while (i<m_cReportGrid.GetRows ())
		{
			l_csItem = m_cReportGrid.GetTextMatrix (i, 0);
			l_csType = m_cReportGrid.GetTextMatrix (i, 1);
			l_csQty = m_cReportGrid.GetTextMatrix (i, 2);

			l_csOutput += l_csItem + " (" + l_csType + ") = " + l_csQty + "\r\n";

			i++;

		}

	}

	l_csOutput.Replace (" ()", "");
	if (l_csOutput.Right (4) == ", \r\n")
	{
		l_csOutput.Delete (l_csOutput.GetLength () -4, 4);
	}

	CAppData::CopyToClipboard (l_csOutput);
}

CReportDialog::ExportToHTML(CString a_csFilename)
{
	int i;
	FILE *l_cFilePtr;
	CString m_csItemName = "";
	CString m_csQty;
	CString m_csBaseCost;
	CString m_csFinalCost;
	CString m_csTechList;
	CString m_csTech;
	CString m_csEff;
	CString m_csCmd;
	bool m_bEven = false;
	bool m_bPreviousLineBlank = false;
	bool m_bEndSection = false;

	l_cFilePtr = fopen (a_csFilename, "w");

	if (l_cFilePtr)
	{
		ExportHTMLHeader (l_cFilePtr, "Craft Order HTML Export");
		i=1;

		if ((m_cReportType.GetCurSel() == REPORT_ORDERCOMPS) ||
		 	 (m_cReportType.GetCurSel() == REPORT_ORDER))
		{
			ExportHTMLOrderHeader(l_cFilePtr);
			while ((i<m_cReportGrid.GetRows ()) && (!m_bEndSection))
			{
				ExportHTMLItemLine (l_cFilePtr, m_cReportGrid.GetTextMatrix (i, 0), m_cReportGrid.GetTextMatrix (i, 1), m_cReportGrid.GetTextMatrix (i, 2),  m_bEven);

				if (m_cReportGrid.GetTextMatrix (i, 2) == "")
				{
					if (m_bPreviousLineBlank)
					{
						m_bEndSection = true;
					}
					else
					{
						m_bPreviousLineBlank = true;
					}
				}
				else
				{
					m_bPreviousLineBlank = false;
				}

				i++;

			}

			ExportHTMLLineFooter (l_cFilePtr);

			i++;
		}

		if ((m_cReportType.GetCurSel() == REPORT_ORDERCOMPS) ||
		 	 (m_cReportType.GetCurSel() == REPORT_COMPS))
		{
			ExportHTMLResourceHeader (l_cFilePtr);

			while (i<m_cReportGrid.GetRows ())
			{
				ExportHTMLResourceLine (l_cFilePtr, m_cReportGrid.GetTextMatrix (i, 0), m_cReportGrid.GetTextMatrix (i, 1), m_cReportGrid.GetTextMatrix (i, 2), m_bEven);

				i++;

			}

			ExportHTMLResourceFooter (l_cFilePtr);
		}

		if (m_cReportType.GetCurSel() == REPORT_BONUS)
		{
			ExportHTMLBonusHeader (l_cFilePtr);

			while (i<m_cReportGrid.GetRows ())
			{
				ExportHTMLResourceLine (l_cFilePtr, m_cReportGrid.GetTextMatrix (i, 0), m_cReportGrid.GetTextMatrix (i, 1), m_cReportGrid.GetTextMatrix (i, 2), m_bEven);

				i++;

			}

			ExportHTMLBonusFooter (l_cFilePtr);
		}

		fclose (l_cFilePtr);
	}

	m_csCmd.Format ("%s", a_csFilename);
	ShellExecute (this->m_hWnd, "open", m_csCmd, NULL, NULL, SW_SHOWNORMAL );
}

CReportDialog::ExportHTMLItemLine(FILE *a_cFilePtr, CString &a_csItemName, CString &a_csQty, CString &a_csTech, bool &a_bEven)
{
	if (a_bEven)
	{
		fprintf (a_cFilePtr, "<tr class=\"even\">\n");
	}
	else
	{
		fprintf (a_cFilePtr, "<tr class=\"odd\">\n");
	}

	a_bEven = !a_bEven;

	fprintf (a_cFilePtr, "<td class=\"left\">%s</td>\n",a_csItemName);
	fprintf (a_cFilePtr, "<td class=\"center\">%s</td>\n",a_csQty);
	fprintf (a_cFilePtr, "<td class=\"center\">%s</td>\n",a_csTech);
	fprintf (a_cFilePtr, "</tr>\n");
}

CReportDialog::ExportHTMLHeader(FILE *a_cFilePtr, CString a_csTitle)
{
	fprintf (a_cFilePtr, "<head> <title>%s</title></head>\n", a_csTitle);
	fprintf (a_cFilePtr, "<body>\n");
	fprintf (a_cFilePtr, "<style type=\"text/css\">\n");
	fprintf (a_cFilePtr, "body { background-color: #FFFFFF; font-family: Geneva,Helvetica,Arial,sans-serif; color: #000000; margin-top: 5px; margin-right: 5px; margin-bottom: 5px; margin-left: 5px }\n");
	fprintf (a_cFilePtr, "td { font-size: 9pt; font-family: Geneva,Helvetica,Arial,sans-serif; vertical-align: text-top; border-style:solid; border-width:0.05em; border-spacing:0; border-color: #404040, #808080;}\n");
	fprintf (a_cFilePtr, ".headerClass { width: 100%; padding:0; border-style:solid; border-width:0.05em; border-spacing:0; }\n");
	fprintf (a_cFilePtr, ".tableClass { width: 500; margin-left: 5%%; padding:0; border-style:solid; border-width:0.05em; border-spacing:0; }\n");
	fprintf (a_cFilePtr, ".subtableClass { width: 450; margin-left: 5%%; padding:0; border-style:solid; border-width:0.05em; border-spacing:0; }\n");
	fprintf (a_cFilePtr, ".formStyle { margin:0px;}\n");
	fprintf (a_cFilePtr, ".odd { background-color: #FFFFFF; padding:0; border-style:dashed; border-width:0.05em; border-spacing:0; }\n");
	fprintf (a_cFilePtr, ".even { background-color: #ECE9D8; padding:0; border-style:dashed; border-width:0.05em; border-spacing:0;}\n");
	fprintf (a_cFilePtr, ".tableHeader { font-size: 10pt; color: #efefef; background-color: #525252; padding:0; border-style:solid; border-width:0.05em; border-spacing:0;}\n");
	fprintf (a_cFilePtr, ".left { text-align:left; }\n");
	fprintf (a_cFilePtr, ".right { text-align:right; }\n");
	fprintf (a_cFilePtr, ".center { text-align:center; }\n");
	fprintf (a_cFilePtr, "</style>\n");

}

CReportDialog::ExportHTMLOrderHeader(FILE *a_cFilePtr)
{
	fprintf (a_cFilePtr, "<H3>Items To Craft</H3>\n");
	fprintf (a_cFilePtr, "<table class=\"tableClass\">\n");
	fprintf (a_cFilePtr, "<thead>\n");
	fprintf (a_cFilePtr, "<tr>\n");
	fprintf (a_cFilePtr, "<th class=\"tableHeader\">Craft Item</th>\n");
	fprintf (a_cFilePtr, "<th class=\"tableHeader\">Batches<span align=right><span></th>\n");
	fprintf (a_cFilePtr, "<th class=\"tableHeader\">Techniques<span align=right><span></th>\n");
	fprintf (a_cFilePtr, "<tbody>\n");

}

CReportDialog::ExportHTMLLineFooter(FILE *a_cFilePtr)
{
	fprintf (a_cFilePtr, "</tbody></table width=\"100%%\">\n");
	fprintf (a_cFilePtr, "</table>\n");
}

CReportDialog::ExportHTMLResourceHeader(FILE *a_cFilePtr)
{
	fprintf (a_cFilePtr, "<H3>Components Required</H3>\n");
	fprintf (a_cFilePtr, "<table class=\"subtableClass\">\n");
	fprintf (a_cFilePtr, "<thead>\n");
	fprintf (a_cFilePtr, "<tr>\n");
	fprintf (a_cFilePtr, "<th class=\"tableHeader\">Component Name</th>\n");
	fprintf (a_cFilePtr, "<th class=\"tableHeader\">Acquired<span align=right><span></th>\n");
	fprintf (a_cFilePtr, "<th class=\"tableHeader\">Quantity<span align=right><span></th>\n");
	fprintf (a_cFilePtr, "<tbody>\n");
}

CReportDialog::ExportHTMLResourceFooter(FILE *a_cFilePtr)
{
	fprintf (a_cFilePtr, "</tbody></table width=\"100%%\">\n");
	fprintf (a_cFilePtr, "</table>\n");
	fprintf (a_cFilePtr, "</body>\n");
}

CReportDialog::ExportHTMLBonusHeader(FILE *a_cFilePtr)
{
	fprintf (a_cFilePtr, "<H3>Bonuses</H3>\n");
	fprintf (a_cFilePtr, "<table class=\"subtableClass\">\n");
	fprintf (a_cFilePtr, "<thead>\n");
	fprintf (a_cFilePtr, "<tr>\n");
	fprintf (a_cFilePtr, "<th class=\"tableHeader\">Bonus</th>\n");
	fprintf (a_cFilePtr, "<th class=\"tableHeader\">Type<span align=right><span></th>\n");
	fprintf (a_cFilePtr, "<th class=\"tableHeader\">Amount<span align=right><span></th>\n");
	fprintf (a_cFilePtr, "<tbody>\n");
}

CReportDialog::ExportHTMLBonusFooter(FILE *a_cFilePtr)
{
	fprintf (a_cFilePtr, "</tbody></table width=\"100%%\">\n");
	fprintf (a_cFilePtr, "</table>\n");
	fprintf (a_cFilePtr, "</body>\n");
}

CReportDialog::ExportHTMLResourceLine(FILE *a_cFilePtr, CString &m_csResourceName, CString &a_csQty, CString &a_csEff, bool &a_bEven)
{
	if (a_bEven)
	{
		fprintf (a_cFilePtr, "<tr class=\"even\">\n");
	}
	else
	{
		fprintf (a_cFilePtr, "<tr class=\"odd\">\n");
	}

	a_bEven = !a_bEven;

	fprintf (a_cFilePtr, "<td class=\"left\">%s</td>\n",m_csResourceName);

	if (a_csQty.IsEmpty ())
	{
		fprintf (a_cFilePtr, "<td class=\"center\">&nbsp;</td>\n");
	}
	else
	{
		fprintf (a_cFilePtr, "<td class=\"center\">%s</td>\n",a_csQty);
	}

	fprintf (a_cFilePtr, "<td class=\"center\">%s</td>\n",a_csEff);
	fprintf (a_cFilePtr, "</tr>\n");
}


int CReportDialog::ReportSelection()
{
	HTREEITEM l_ParentTreeItem = CAppData::m_cOrderWnd.m_cItemTree.GetRootItem ();
	HTREEITEM l_ChildTreeItem;
	int l_iSelected = 0;
	bool l_bSelectGroup = false;

	if (CAppData::m_cOrderWnd.m_cWindowState.m_bLoaded)
	{
		while (l_ParentTreeItem)
		{
			l_bSelectGroup = ((CAppData::m_cOrderWnd.m_cItemTree.GetCheck (l_ParentTreeItem)) != 0);
			l_ChildTreeItem = CAppData::m_cOrderWnd.m_cItemTree.GetChildItem (l_ParentTreeItem);
			while (l_ChildTreeItem)
			{
				if ((l_bSelectGroup) || (CAppData::m_cOrderWnd.m_cItemTree.GetCheck (l_ChildTreeItem)) )
				{
					l_iSelected++;
				}

				l_ChildTreeItem = CAppData::m_cOrderWnd.m_cItemTree.GetNextSiblingItem (l_ChildTreeItem);
			}

			l_ParentTreeItem = CAppData::m_cOrderWnd.m_cItemTree.GetNextSiblingItem (l_ParentTreeItem);
		}
	}

	return (l_iSelected);
}

void CReportDialog::OnHelpIndex()
{
	CAppData::LaunchWebLink ((CString) "reportwindow");
}

void CReportDialog::OnOptionsResourcebreakdownShowformularesource()
{
	CAppData::m_iShowReportResourceMode = 0;
	UpdateOrderMenu();

	GenerateDirectReport ();
}

void CReportDialog::OnOptionsShowsubcomponents()
{
	CAppData::m_iShowReportResourceMode = 1;
	UpdateOrderMenu();

	GenerateDirectReport ();
}

void CReportDialog::OnOptionsShowbaseresource()
{
	CAppData::m_iShowReportResourceMode = 2;
	UpdateOrderMenu();

	GenerateDirectReport ();
}

CReportDialog::SortResources(CTypedPtrList<CPtrList,  CItemResource*> &l_clResourceList, int a_iMode)
{
	int i;
	int j;
	int l_iSize = l_clResourceList.GetCount ();
	CItemResource *l_cpItemA;
	CItemResource *l_cpItemB;
	CItemResource l_cItem;
	POSITION l_Pos;
	bool l_bSwap;

	for (j=1; j<l_iSize; j++)
	{
		l_Pos = l_clResourceList.GetHeadPosition ();
		l_cpItemA = l_clResourceList.GetNext (l_Pos);

		for (i=0; i<l_iSize - j; i++)
		{
			l_cpItemB = l_clResourceList.GetNext (l_Pos);

			switch (a_iMode)
			{
				case (REPORT_SORTBYNAME) :
				{
					l_bSwap = (l_cpItemA->m_csName > l_cpItemB->m_csName);
					break;
				}
				case (REPORT_SORTBYQTY) :
				{
					l_bSwap = (l_cpItemA->m_iMinAmt < l_cpItemB->m_iMinAmt);
					break;
				}
				default :
				{
					l_bSwap = false;
				}
			}


			if (l_bSwap)
			{
				l_cItem = *l_cpItemA;

				// Copy Item B to Item A
				*l_cpItemA = *l_cpItemB;

				// Copy buffer to Item B
				*l_cpItemB = l_cItem;
			}

			l_cpItemA = l_cpItemB;
		}
	}
}

CReportDialog::ConvertToBaseResources (CTypedPtrList<CPtrList,  CItemResource*> &l_clResourceList)
{
	CItemResource *l_cpItem;
	POSITION l_Pos;
	CTypedPtrList<CPtrList,  CItemResource*> l_clBaseResourceList;

	l_Pos = l_clResourceList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpItem = l_clResourceList.GetNext (l_Pos);
		AddToBaseResources (l_cpItem, l_cpItem->m_iMinAmt, l_clBaseResourceList, 0);
	}

	l_Pos = l_clResourceList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpItem = l_clResourceList.GetNext (l_Pos);
		delete (l_cpItem);
	}
	l_clResourceList.RemoveAll ();

	l_Pos = l_clBaseResourceList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpItem = l_clBaseResourceList.GetNext (l_Pos);
		l_clResourceList.AddTail (l_cpItem);
	}
	l_clBaseResourceList.RemoveAll ();
}

CReportDialog::AddToBaseResources (CItemResource *a_cpItemResource, int a_iBaseQty, CTypedPtrList<CPtrList,  CItemResource*> &l_clBaseResourceList, int a_iSkillAdjust)
{
	CItemResource *l_cpItemResource;
	CFormula *l_cpResourceFormula;
	CFormulaTier *l_cpResourceFormulaTier;
	POSITION l_Pos;
	int l_iBaseQty;
	int l_iProfileQty;

	if (a_cpItemResource)
	{
		if (CAppData::FindResourceFormulaTier (a_cpItemResource->m_csName, &l_cpResourceFormula, &l_cpResourceFormulaTier))
		{
			l_Pos = l_cpResourceFormulaTier->m_clResourceList.GetHeadPosition ();
			while (l_Pos)
			{
				l_cpItemResource = l_cpResourceFormulaTier->m_clResourceList.GetNext (l_Pos);

				l_iProfileQty = CAppData::CalculateEfficiency (l_cpItemResource, CAppData::m_cpCurrentProfile, a_iSkillAdjust);
				if ((a_iBaseQty % l_cpResourceFormula->m_iBatchQty) == 0)
				{
					l_iBaseQty = (a_iBaseQty / l_cpResourceFormula->m_iBatchQty);
				}
				else
				{
					l_iBaseQty = (a_iBaseQty / l_cpResourceFormula->m_iBatchQty) + 1;
				}

				l_iBaseQty *= l_iProfileQty;
				AddToBaseResources (l_cpItemResource, l_iBaseQty, l_clBaseResourceList, a_iSkillAdjust );
			}
		}
		else
		{
			// Base Resource, search list
			bool l_bAdded = false;

			l_Pos = l_clBaseResourceList.GetHeadPosition ();
			while (l_Pos)
			{
				l_cpItemResource = l_clBaseResourceList.GetNext (l_Pos);
				if (l_cpItemResource->m_csName == a_cpItemResource->m_csName)
				{
					l_cpItemResource->m_iMinAmt += a_iBaseQty;
					l_cpItemResource->m_iOptLvl = -1;
					l_bAdded = true;
				}
			}

			if (!l_bAdded)
			{
				l_cpItemResource = new CItemResource ();
				*l_cpItemResource = *a_cpItemResource;
				l_cpItemResource->m_iMinAmt = a_iBaseQty;
				l_cpItemResource->m_iOptLvl = -1;
				l_clBaseResourceList.AddTail (l_cpItemResource);
			}
		}
	}
}

BEGIN_EVENTSINK_MAP(CReportDialog, CDialog)
    //{{AFX_EVENTSINK_MAP(CReportDialog)
	ON_EVENT(CReportDialog, IDC_REPORTGRID, 71 /* EnterCell */, OnEnterCellReportgrid, VTS_NONE)
	ON_EVENT(CReportDialog, IDC_REPORTGRID, 72 /* LeaveCell */, OnLeaveCellReportgrid, VTS_NONE)
	ON_EVENT(CReportDialog, IDC_REPORTGRID, -606 /* MouseMove */, OnMouseMoveReportgrid, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
	ON_EVENT(CReportDialog, IDC_REPORTGRID, 73 /* Scroll */, OnScrollReportgrid, VTS_NONE)
	ON_EVENT(CReportDialog, IDC_REPORTGRID, -600 /* Click */, OnClickReportgrid, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CReportDialog::OnEnterCellReportgrid()
{
}

void CReportDialog::OnLeaveCellReportgrid()
{
	EndEditCell();
}

CReportDialog::StartEditCell()
{
	CRect l_cQtyRect;
	CRect l_cRect;
	CString l_csCell;

	if (!m_cQtySpin.IsWindowVisible ())
	{
		m_iReportGridEditRow = m_cReportGrid.GetMouseRow ();
		m_iReportGridEditCol = 2;

		if ((m_iReportGridEditRow > 0) && (m_iReportGridEditCol == 2))
		{
			m_cQtySpin.GetClientRect (l_cQtyRect);
			l_csCell = m_cReportGrid.GetTextMatrix (m_iReportGridEditRow, m_iReportGridEditCol);
			if (l_csCell.Find ('/') >= 0)
			{
				l_cRect = m_cReportGrid.GetCellRect (m_iReportGridEditRow, m_iReportGridEditCol);
				m_cQtySpin.SetWindowPos  (NULL, l_cRect.right - l_cQtyRect.Width (), l_cRect.top, l_cRect.Width(), l_cRect.Height(), SWP_NOSIZE);
				m_cQtySpin.ShowWindow (true);
				m_cQtySpin.SetFocus();
			}
			else
			{
				EndEditCell ();
			}
		}
		else
		{
			EndEditCell();
		}
	}
}

CReportDialog::EndEditCell()
{
	if (m_cQtySpin.IsWindowVisible ())
	{
		m_cQtySpin.ShowWindow (false);
	}
}

void CReportDialog::OnMouseMoveReportgrid(short Button, short Shift, long x, long y)
{
}

void CReportDialog::OnScrollReportgrid()
{
	EndEditCell();

}

void CReportDialog::OnDeltaposQtyspin(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	CString l_csComponentName;
	int l_iMin;
	int l_iMax;
	bool l_bSubComp;

	//RESUME
	if (GetKeyState(VK_CONTROL)<0 && GetKeyState(VK_SHIFT)<0)
	{
		pNMUpDown->iDelta = pNMUpDown->iDelta * 1000;
	}
	else if (GetKeyState(VK_CONTROL)<0)
	{
		pNMUpDown->iDelta = pNMUpDown->iDelta * 100;
	}
	else if (GetKeyState(VK_SHIFT)<0)
	{
		pNMUpDown->iDelta = pNMUpDown->iDelta * 10;
	}

	if ((m_iReportGridEditRow > 0) && (m_iReportGridEditCol == 2))
	{
		if (IsComponent (m_iReportGridEditRow, l_csComponentName, l_iMin, l_iMax, l_bSubComp))
		{
			CAppData::GetStoredComponent (l_csComponentName, l_iMin);

			l_iMin -= pNMUpDown->iDelta;

			if (l_iMin < 0)
			{
				l_iMin = 0;
			}
			else if (l_iMin > l_iMax)
			{
				l_iMin = l_iMax;
			}

			CAppData::SetStoredComponent (l_csComponentName, l_iMin);
			UpdateComponentCounts ();
		}
	}

	*pResult = 0;
}

void CReportDialog::OnClickReportgrid()
{
	StartEditCell ();
}

CReportDialog::UpdateComponentCounts()
{
	int l_iRow = 1;
	CString l_csComponentName;
	CString l_csStr;
	int l_iMin;
	int l_iMax;
	bool l_bSubComp;
	bool l_bCompleteAllSubComps = false;

	while (l_iRow < m_cReportGrid.GetRows ())
	{
		if (IsComponent (l_iRow, l_csComponentName, l_iMin, l_iMax, l_bSubComp))
		{
			if (!CAppData::GetStoredComponent (l_csComponentName, l_iMin))
			{
				l_iMin = 0;
			}

			if (l_iMin > l_iMax)
			{
				l_iMin = l_iMax;
			}

			if (l_bSubComp)
			{
				l_csStr.Format ("(%d/%d)", l_iMin, l_iMax);
			}
			else
			{
				l_csStr.Format ("%d/%d", l_iMin, l_iMax);
				l_bCompleteAllSubComps = (l_iMin >= l_iMax);
			}

			m_cReportGrid.SetTextMatrix (l_iRow, 2, l_csStr);
			if (l_bCompleteAllSubComps)
			{
				m_cReportGrid.SetTextMatrix (l_iRow, 1, "Done");
			}
			else
			{
				m_cReportGrid.SetTextMatrix (l_iRow, 1, "");
			}
		}

		l_iRow++;
	}
}

bool CReportDialog::IsComponent(int a_iRow, CString &a_csName, int &a_Min, int &a_iMax, bool &a_bSubComp)
{
	CString l_csCell = m_cReportGrid.GetTextMatrix (a_iRow, 2);
	int l_iOffset;

	a_csName = m_cReportGrid.GetTextMatrix (a_iRow, 0);
	a_bSubComp = a_csName.Find("-->") >= 0;
	l_csCell.Replace ("(", "");
	l_csCell.Replace (")", "");
	l_iOffset = l_csCell.Find ('/');

	if (l_iOffset >= 0)
	{
		a_Min = atoi (l_csCell.Left (l_iOffset));
		a_iMax = atoi (l_csCell.Mid (l_iOffset + 1));

		if (a_bSubComp)
		{
			a_csName = a_csName.Mid (a_csName.Find("-->") + 3);
		}

		return (true);
	}

	return (false);
}

void CReportDialog::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);
}

void CReportDialog::OnWindowPosChanging( WINDOWPOS* lpwndpos )
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

	if (CAppData::m_cComponentWnd.m_cWindowState.m_bVisible)
	{
		m_cWindowState.SnapToWnd (lpwndpos, &l_cRect, &CAppData::m_cComponentWnd, CAppData::m_iStickyStrength);
	}

	if (CAppData::m_cProfileWnd.m_cWindowState.m_bVisible)
	{
		m_cWindowState.SnapToWnd (lpwndpos, &l_cRect, &CAppData::m_cProfileWnd, CAppData::m_iStickyStrength);
	}

	CDialog::OnWindowPosChanging(lpwndpos);
}

void CReportDialog::OnWindowAlwaysontop()
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

BOOL CReportDialog::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	int l_iTop = m_cReportGrid.GetTopRow ();

	if ((zDelta > 0) && (l_iTop > 0))
	{
		l_iTop--;
	}
	else if (zDelta < 0)
	{
		l_iTop++;
	}

	if ((zDelta > 0) && (l_iTop > 0))
	{
		l_iTop--;
	}
	else if (zDelta < 0)
	{
		l_iTop++;
	}

	if (l_iTop < m_cReportGrid.GetRows ())
	{
		m_cReportGrid.SetTopRow (l_iTop);
	}

	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

BOOL CReportDialog::OnHelpInfo(HELPINFO* pHelpInfo)
{
	return (TRUE);
}

void CReportDialog::OnSelchangeReporttype()
{
	CAppData::m_iReportType = m_cReportType.GetCurSel ();
}

void CReportDialog::OnOptionsBonusesDirectonly()
{
	CAppData::m_iShowReportBonusMode = 0;
	UpdateOrderMenu();

	GenerateDirectReport ();
}

void CReportDialog::OnOptionsBonusesAll()
{
	CAppData::m_iShowReportBonusMode = 1;
	UpdateOrderMenu();

	GenerateDirectReport ();
}
