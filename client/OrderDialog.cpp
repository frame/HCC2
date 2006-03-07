// OrderDialog.cpp : implementation file
//

#include "stdafx.h"
#include "HCC.h"
#include "OrderDialog.h"
#include "AppData.h"
#include "InputDialog.h"
#include <windowsx.h>
#include <windows.h>
#include <winuser.h>
#include "Scheme.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define UM_CHECKSTATECHANGE (WM_USER + 100)

/////////////////////////////////////////////////////////////////////////////
// COrderDialog dialog


COrderDialog::COrderDialog(CWnd* pParent /*=NULL*/)
	: CDialog(COrderDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(COrderDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void COrderDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COrderDialog)
	DDX_Control(pDX, IDC_ALIGNTIERS, m_cAlignTiers);
	DDX_Control(pDX, IDC_TECHLIST, m_cTechList);
	DDX_Control(pDX, IDC_QTYSPIN, m_cQtySpin);
	DDX_Control(pDX, IDC_ORDERFRAME, m_cOrderFrame);
	DDX_Control(pDX, IDC_NEWGROUPBUTTON, m_cNewGroupButton);
	DDX_Control(pDX, IDC_ITEMTREE, m_cItemTree);
	DDX_Control(pDX, IDC_ITEMTOTALQTY, m_cItemTotalQty);
	DDX_Control(pDX, IDC_ITEMQTY, m_cItemQty);
	DDX_Control(pDX, IDC_ITEMNAME, m_cItemName);
	DDX_Control(pDX, IDC_DELETEBUTTON, m_cDeleteButton);
	DDX_Control(pDX, IDC_COPYTOCLIPBOARD, m_cCopyToClipboardButton);
	DDX_Control(pDX, IDC_COPYITEM, m_cCopyItemButton);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COrderDialog, CDialog)
	//{{AFX_MSG_MAP(COrderDialog)
	ON_WM_WINDOWPOSCHANGING ()
	ON_WM_MOVING()
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVEAS, OnFileSaveas)
	ON_COMMAND(ID_SELECTION_SELECTNONE, OnSelectionSelectnone)
	ON_COMMAND(ID_SELECTION_SELECTALL, OnSelectionSelectall)
	ON_COMMAND(ID_SELECTION_INVERTSELECTION, OnSelectionInvertselection)
	ON_COMMAND(ID_SELECTION_COPYTOCLIPBOARD, OnSelectionCopytoclipboard)
	ON_WM_SIZE()
	ON_EN_CHANGE(IDC_ITEMQTY, OnChangeItemqty)
	ON_BN_CLICKED(IDC_DELETEBUTTON, OnDeletebutton)
	ON_BN_CLICKED(IDC_NEWGROUPBUTTON, OnNewgroupbutton)
	ON_NOTIFY(UDN_DELTAPOS, IDC_QTYSPIN, OnDeltaposQtyspin)
	ON_BN_CLICKED(IDC_COPYTOCLIPBOARD, OnCopytoclipboard)
	ON_BN_CLICKED(IDC_COPYITEM, OnCopyitem)
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_ITEMTREE, OnItemexpandingItemtree)
	ON_NOTIFY(TVN_SELCHANGED, IDC_ITEMTREE, OnSelchangedItemtree)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_ITEMTREE, OnEndlabeleditItemtree)
	ON_WM_CLOSE()
	ON_COMMAND(ID_OPTIONS_SNAPSHOTWINDOW, OnOptionsSnapshotwindow)
	ON_COMMAND(ID_OPTIONS_RESTOREWINDOW, OnOptionsRestorewindow)
	ON_COMMAND(ID_HELP_INDEX, OnHelpIndex)
	ON_WM_MOVE()
	ON_COMMAND(ID_WINDOW_ALWAYSONTOP, OnWindowAlwaysontop)
	ON_NOTIFY(NM_CLICK, IDC_ITEMTREE, OnClickItemtree)
	ON_NOTIFY(TVN_SELCHANGING, IDC_ITEMTREE, OnSelchangingItemtree)
	ON_WM_HELPINFO()
	ON_WM_QUERYDRAGICON()
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_ALIGNTIERS, OnAligntiers)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COrderDialog message handlers

void COrderDialog::OnFileNew() 
{
}

void COrderDialog::OnFileOpen() 
{
}

void COrderDialog::OnFileSave() 
{
}

void COrderDialog::OnFileSaveas() 
{
}

void COrderDialog::OnSelectionSelectnone() 
{
	HTREEITEM l_cGroupTreeItem;
	HTREEITEM l_cItemTreeItem;
	
	l_cGroupTreeItem = m_cItemTree.GetRootItem ();
	while (l_cGroupTreeItem)
	{
		m_cItemTree.SetCheck (l_cGroupTreeItem, false);

		l_cItemTreeItem = m_cItemTree.GetChildItem (l_cGroupTreeItem);
		while (l_cItemTreeItem)
		{
			m_cItemTree.SetCheck (l_cItemTreeItem, false);
			l_cItemTreeItem = m_cItemTree.GetNextSiblingItem (l_cItemTreeItem);
		}

		l_cGroupTreeItem = m_cItemTree.GetNextSiblingItem (l_cGroupTreeItem);
	}
	m_cDeleteButton.EnableWindow (false);
}

void COrderDialog::OnSelectionSelectall() 
{
	HTREEITEM l_cGroupTreeItem;
	HTREEITEM l_cItemTreeItem;
	
	l_cGroupTreeItem = m_cItemTree.GetRootItem ();
	while (l_cGroupTreeItem)
	{
		m_cItemTree.SetCheck (l_cGroupTreeItem, true);

		l_cItemTreeItem = m_cItemTree.GetChildItem (l_cGroupTreeItem);
		while (l_cItemTreeItem)
		{
			m_cItemTree.SetCheck (l_cItemTreeItem, true);
			l_cItemTreeItem = m_cItemTree.GetNextSiblingItem (l_cItemTreeItem);
		}

		l_cGroupTreeItem = m_cItemTree.GetNextSiblingItem (l_cGroupTreeItem);
	}

	m_cDeleteButton.EnableWindow (true);
}

void COrderDialog::OnSelectionInvertselection() 
{
	HTREEITEM l_cGroupTreeItem;
	HTREEITEM l_cItemTreeItem;
	//bool l_bGroupCheck;
	bool l_bItemCheck;
	bool l_bItemsSelected = false;
	
	l_cGroupTreeItem = m_cItemTree.GetRootItem ();
	while (l_cGroupTreeItem)
	{
		//l_bGroupCheck = m_cItemTree.GetCheck (l_cGroupTreeItem) != 0;
		//m_cItemTree.SetCheck (l_cGroupTreeItem, !l_bGroupCheck);

		l_cItemTreeItem = m_cItemTree.GetChildItem (l_cGroupTreeItem);
		while (l_cItemTreeItem)
		{
			l_bItemCheck = m_cItemTree.GetCheck (l_cItemTreeItem) != 0;
			l_bItemsSelected = l_bItemsSelected || !l_bItemCheck;
			m_cItemTree.SetCheck (l_cItemTreeItem, !l_bItemCheck);
			l_cItemTreeItem = m_cItemTree.GetNextSiblingItem (l_cItemTreeItem);
		}

		l_cGroupTreeItem = m_cItemTree.GetNextSiblingItem (l_cGroupTreeItem);
	}
	m_cDeleteButton.EnableWindow (l_bItemsSelected);
}

void COrderDialog::OnSelectionCopytoclipboard() 
{
	HTREEITEM l_cGroupTreeItem;
	HTREEITEM l_cItemTreeItem;
	COrderItem l_cOrderItem;
	CString l_csMsg;

	l_cGroupTreeItem = m_cItemTree.GetRootItem ();
	while (l_cGroupTreeItem)
	{
		l_cItemTreeItem = m_cItemTree.GetChildItem (l_cGroupTreeItem);
		while (l_cItemTreeItem)
		{
			if (m_cItemTree.GetCheck (l_cItemTreeItem))
			{
				if (CAppData::FindOrderItem (CAppData::m_cOrderWnd.m_cItemTree.GetItemData (l_cItemTreeItem), l_cOrderItem))
				{
					if (l_csMsg.IsEmpty())
					{
						l_csMsg = CAppData::FormatOrderItemText (l_cOrderItem);
					}
					else
					{
						l_csMsg = l_csMsg + ",\r\n" + CAppData::FormatOrderItemText (l_cOrderItem);
					}
				}
			}

			l_cItemTreeItem = m_cItemTree.GetNextSiblingItem (l_cItemTreeItem);
		}

		l_cGroupTreeItem = m_cItemTree.GetNextSiblingItem (l_cGroupTreeItem);
	}

	l_csMsg = l_csMsg + "\r\n";
	CAppData::CopyToClipboard (l_csMsg);	
}

void COrderDialog::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	Resize ();
	
}

void COrderDialog::OnChangeItemqty() 
{
	CString l_csQty;
	int l_iQty;
	COrderItem l_cOrderItem;
	CFormula *l_cpFormula;
	HTREEITEM l_cTreeItem;

	if (CAppData::FindOrderItem (CAppData::m_iCurrentOrderId, l_cOrderItem))
	{
		if (CAppData::FindFormula (l_cOrderItem.m_csCategory, l_cOrderItem.m_csFormulaName, &l_cpFormula))
		{
			m_cItemQty.GetWindowText (l_csQty);
			l_iQty = atoi (l_csQty);
			if (l_iQty > 100000)
			{
				l_iQty = 100000;
				m_cItemQty.SetWindowText ("100000");
			}

			DisplayTotalQty (l_iQty, l_cpFormula->m_iBatchQty);

			l_cOrderItem.m_iQty = l_iQty;
			CAppData::UpdateOrderItem (l_cOrderItem);
			CAppData::ChangeOrderState (true);

			l_cTreeItem = m_cItemTree.GetSelectedItem ();
			if (l_cTreeItem)
			{
				CString l_csItemName;
				l_csItemName.Format ("%d x %s", l_cOrderItem.m_iQty * l_cpFormula->m_iBatchQty, l_cOrderItem.m_csItemName);
				m_cItemTree.SetItemText (l_cTreeItem, l_csItemName);
			}
		}
	}
}

void COrderDialog::OnDeletebutton() 
{
	HTREEITEM l_cGroupTreeItem;
	HTREEITEM l_cItemTreeItem;
	CString l_csGroupname;
	int l_iItemId;
	bool l_bItemsDeleted = false;
	COrderItem l_cOrderItem;
	
	l_cGroupTreeItem = m_cItemTree.GetRootItem ();
	while (l_cGroupTreeItem)
	{
		if (m_cItemTree.GetCheck (l_cGroupTreeItem))
		{
			l_csGroupname = m_cItemTree.GetItemText (l_cGroupTreeItem);

			if (AfxMessageBox ("Do you really want to delete the group '" + l_csGroupname + "'?", MB_YESNO) == IDYES)
			{
				l_bItemsDeleted = true;
				CAppData::DeleteOrderGroup (l_csGroupname);
			}
		}
		else
		{
			l_cItemTreeItem = m_cItemTree.GetChildItem (l_cGroupTreeItem);
			while (l_cItemTreeItem)
			{
				if (m_cItemTree.GetCheck (l_cItemTreeItem))
				{
					l_iItemId = m_cItemTree.GetItemData (l_cItemTreeItem);
					l_bItemsDeleted = true;
					CAppData::DeleteOrderItem (l_iItemId);
				}

				l_cItemTreeItem = m_cItemTree.GetNextSiblingItem (l_cItemTreeItem);
			}
		}

		l_cGroupTreeItem = m_cItemTree.GetNextSiblingItem (l_cGroupTreeItem);
	}

	if (l_bItemsDeleted)
	{
		CAppData::ChangeOrderState (true);

		if (!CAppData::FindOrderItem (CAppData::m_cCurrentOrderItem.m_iId, l_cOrderItem))
		{
			m_cItemName.SetWindowText ("");
			m_cItemQty.SetWindowText ("");
			m_cItemTotalQty.SetWindowText ("");
			m_cTechList.DeleteAllItems ();
			m_cTechList.EnableWindow (false);
			m_cItemQty.EnableWindow (false);
			m_cQtySpin.EnableWindow (false);
			m_cCopyItemButton.EnableWindow (false);
			m_cAlignTiers.EnableWindow (false);
			m_cCopyToClipboardButton.EnableWindow (false);
		}

		DisplayOrder ();
	}
}

void COrderDialog::OnNewgroupbutton() 
{
	CInputDialog l_cInputDialog (this);

	l_cInputDialog.m_csInputMsg = "New Group Name";
	l_cInputDialog.m_csTitleMsg = "Please enter the Group name";
	if (l_cInputDialog.DoModal () == IDOK)
	{
		CAppData::AddOrderGroup (l_cInputDialog.m_csInput);
		CAppData::ChangeOrderState (true);
		DisplayOrder ();
	}
}

void COrderDialog::OnDeltaposQtyspin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	
	CString l_csQty;
	int l_iQty;

	m_cItemQty.GetWindowText (l_csQty);
	l_iQty = atoi (l_csQty);
	l_iQty -= pNMUpDown->iDelta;

	if (l_iQty < 1)
	{
		l_iQty = 1;
	}
	else if (l_iQty > 100000)
	{
		l_iQty = 100000;
	}

	l_csQty.Format ("%d", l_iQty);
	m_cItemQty.SetWindowText (l_csQty);
	CAppData::ChangeOrderState (true);
	
	*pResult = 0;
}

void COrderDialog::OnCopytoclipboard() 
{
	COrderItem l_cOrderItem;
	CString l_csMsg;

	if (CAppData::FindOrderItem (CAppData::m_iCurrentOrderId, l_cOrderItem))
	{
		l_csMsg = CAppData::FormatOrderItemText (l_cOrderItem) + "\r\n";
		CAppData::CopyToClipboard (l_csMsg);	
	}
}

void COrderDialog::OnCopyitem() 
{
	CAppData::m_bEditMode = false;	
	COrderItem l_cOrderItem;

	if (CAppData::FindOrderItem (CAppData::m_iCurrentOrderId, l_cOrderItem))
	{
		CAppData::m_cItemCreationWnd.SelectFormula (l_cOrderItem);
	}
}

BOOL COrderDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
   //remove some options from the system menu 
   CMenu* pSysMenu = GetSystemMenu(FALSE); 
   pSysMenu->RemoveMenu(SC_RESTORE,MF_BYCOMMAND); 
   pSysMenu->RemoveMenu(SC_MINIMIZE,MF_BYCOMMAND); 
   pSysMenu->RemoveMenu(SC_MAXIMIZE,MF_BYCOMMAND); 
   pSysMenu->RemoveMenu(SC_TASKLIST ,MF_BYCOMMAND); 

	m_cTechList.InsertColumn (0, "Tech", LVCFMT_LEFT, 170);
	
	m_cOS_ItemTree.InitState				(m_cItemTree,				*this, NULL,	NULL,				   1.0f, 1.0f);
	m_cOS_Delete.InitState					(m_cDeleteButton,		   *this, NULL,	&m_cOS_ItemTree,	0.0f, 0.0f);
	m_cOS_NewGroup.InitState				(m_cNewGroupButton,		*this, &m_cOS_ItemTree,	&m_cOS_ItemTree,	0.0f, 0.0f);
	m_cOS_OrderFrame.InitState				(m_cOrderFrame,			*this, NULL,	NULL,					1.0f, 1.0f);
	m_cOS_ItemInfoList.InitState			(m_cItemName,				*this, NULL,	&m_cOS_ItemTree,	1.0f, 0.0f);
	m_cOS_TechList.InitState			   (m_cTechList,			   *this, NULL,	&m_cOS_ItemTree,	1.0f, 0.0f);
	m_cOS_ItemQty.InitState					(m_cItemQty,				*this, NULL,	&m_cOS_ItemTree,	0.0f, 0.0f);
	m_cOS_ItemQtySpin.InitState			(m_cQtySpin,				*this, NULL,	&m_cOS_ItemTree,	0.0f, 0.0f);
	m_cOS_ItemTotalQty.InitState			(m_cItemTotalQty,			*this, NULL,	&m_cOS_ItemTree,	1.0f, 0.0f);
	m_cOS_CopyToClipboardButton.InitState(m_cCopyToClipboardButton,*this, NULL,	&m_cOS_ItemTree,	0.0f, 0.0f);
	m_cOS_AlignTiers.InitState				(m_cAlignTiers,			*this, &m_cOS_ItemTree,	&m_cOS_ItemTree,	0.0f, 0.0f);
	m_cOS_CopyItemButton.InitState		(m_cCopyItemButton,		*this, &m_cOS_ItemTree,	&m_cOS_ItemTree,	0.0f, 0.0f);
	Initialise ();
	
	CMenu *l_pMenu;
	l_pMenu = GetMenu ();
	if (l_pMenu)
	{
		CAppData::SetMenuItem(l_pMenu, ID_WINDOW_ALWAYSONTOP, m_cWindowState.m_bOnTop);
	}

	DisplayOrder ();
	DisplayOrderItem (CAppData::m_iCurrentOrderId);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

COrderDialog::Initialise()
{
	if (CAppData::m_bEnableIcons)
	{
		m_cItemTree.SetImageList (&CAppData::m_cpIconImages->m_cImageList, TVSIL_NORMAL);
		m_cTechList.SetImageList (&CAppData::m_cpIconImages->m_cImageList, LVSIL_SMALL);
	}
	else
	{
		m_cItemTree.SetImageList (NULL, TVSIL_NORMAL);
		m_cTechList.SetImageList (NULL, LVSIL_SMALL);
	}

	m_cItemTree.SetBkColor (CScheme::GetColour ("TREE_BACKCOLOUR"));
	m_bItemTreeExpand = false;

	m_cTechList.SetBkColor (CScheme::GetColour ("TREE_BACKCOLOUR"));
	m_cTechList.SetTextBkColor (CScheme::GetColour ("TREE_BACKCOLOUR"));
}

COrderDialog::StartUp()
{
	
	this->Create (IDD_ORDERDIALOG, CWnd::GetDesktopWindow ());
	m_cWindowState.m_bLoaded = true;

}

void COrderDialog::Resize()
{
	CDialog::RedrawWindow ();

	m_cOS_ItemTree.Resize ();
	m_cOS_Delete.Resize ();
	m_cOS_NewGroup.Resize ();
	m_cOS_ItemInfoList.Resize ();
	m_cOS_TechList.Resize ();
	m_cOS_ItemQty.Resize ();
	m_cOS_ItemQtySpin.Resize ();
	m_cOS_ItemTotalQty.Resize ();
	m_cOS_CopyToClipboardButton.Resize ();
	m_cOS_AlignTiers.Resize ();
	m_cOS_CopyItemButton.Resize ();
	m_cOS_OrderFrame.Resize ();

	if (m_cWindowState.m_bLoaded)
	{
		m_cTechList.SetColumnWidth (0, m_cOS_TechList.m_iCurWidth - 5);
	}
}

void COrderDialog::OnGetMinMaxInfo (MINMAXINFO FAR* lpMMI) 
{
	CDialog::OnGetMinMaxInfo (lpMMI);

	lpMMI->ptMinTrackSize.x = 250;
	lpMMI->ptMinTrackSize.y = 410;
	lpMMI->ptMaxTrackSize.x = 600;
	lpMMI->ptMaxTrackSize.y = 1280;

}

void COrderDialog::DisplayOrder()
{
	POSITION l_OrderPos;
	COrderItem l_cOrderItem;
	HTREEITEM l_cGroupItem;
	HTREEITEM l_cTreeItem;
	HTREEITEM l_cSelectedItem = NULL;
	CFormula *l_cpFormula;
	CString l_csItemName;

	m_bItemTreeExpand = true;
	DisplayOrderTitle();
	this->LockWindowUpdate ();
	m_cItemTree.DeleteAllItems ();

	l_OrderPos = CAppData::m_cOrderGroups.GetHeadPosition ();
	while (l_OrderPos)
	{
		m_cItemTree.InsertItem (CAppData::m_cOrderGroups.GetNext (l_OrderPos), 0, 0);	
	}

	l_OrderPos = CAppData::m_clOrderList.GetHeadPosition ();
	while (l_OrderPos)
	{
		l_cOrderItem = CAppData::m_clOrderList.GetNext (l_OrderPos);
		if (CAppData::FindFormula (l_cOrderItem.m_csCategory, l_cOrderItem.m_csFormulaName, &l_cpFormula))
		{

			l_cGroupItem = FindOrderGroup (l_cOrderItem.m_csOrderGroup);
			if (!l_cGroupItem)
			{
				l_cGroupItem = m_cItemTree.InsertItem (l_cOrderItem.m_csOrderGroup, 0, 0);	
				CAppData::AddOrderGroup (l_cOrderItem.m_csCategory);
			}

			l_csItemName.Format ("%d x %s", l_cOrderItem.m_iQty * l_cpFormula->m_iBatchQty, l_cOrderItem.m_csItemName);
			l_cTreeItem = m_cItemTree.InsertItem (l_csItemName, l_cpFormula->m_iIcon, l_cpFormula->m_iIcon, l_cGroupItem);
			m_cItemTree.SetItemData (l_cTreeItem, l_cOrderItem.m_iId);
			m_cItemTree.EnsureVisible (l_cTreeItem);

			if (l_cOrderItem.m_iId == CAppData::m_iCurrentOrderId)
			{
				l_cSelectedItem = l_cTreeItem;
			}
		}
	}

	if (l_cSelectedItem)
	{
		m_cItemTree.SelectItem (l_cSelectedItem);
		m_cItemTree.EnsureVisible (l_cSelectedItem);
	}

	this->UnlockWindowUpdate ();
	this->InvalidateRgn (NULL, false);
	m_bItemTreeExpand = false;

	if (CAppData::m_cItemCreationWnd.m_cWindowState.m_bLoaded)
	{
		CAppData::m_cItemCreationWnd.DisplayItems ();
	}

}

HTREEITEM COrderDialog::FindOrderGroup(CString &a_csGroup)
{
	HTREEITEM l_cTreeItem;
	CString l_csGroupName;

	l_cTreeItem = m_cItemTree.GetRootItem ();
	while (l_cTreeItem)
	{
		l_csGroupName = m_cItemTree.GetItemText (l_cTreeItem);
		if (l_csGroupName == a_csGroup)
		{
			return (l_cTreeItem);
		}
		
		l_cTreeItem = m_cItemTree.GetNextSiblingItem (l_cTreeItem);
	}

	return (NULL);
}

void COrderDialog::OnItemexpandingItemtree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	if (m_bItemTreeExpand)
	{
		*pResult = 0;
	}
	else
	{
		*pResult = 1;
	}
}

BOOL COrderDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
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
									pCustomDraw->clrText = CScheme::GetColour ("TREE_LVL3_SELECTED_FG");
									pCustomDraw->clrTextBk = CScheme::GetColour ("TREE_LVL3_SELECTED_BG");
								}
								else if (pCustomDraw->nmcd.uItemState & CDIS_HOT )
								{
									SelectObject (pCustomDraw->nmcd.hdc, CAppData::m_cTitleSelFont);
									pCustomDraw->clrText = CScheme::GetColour ("TREE_LVL3_HIGHLIGHT_FG");
									pCustomDraw->clrTextBk = CScheme::GetColour ("TREE_LVL3_HIGHLIGHT_BG");
								}
								else
								{
									SelectObject (pCustomDraw->nmcd.hdc, CAppData::m_cTitleFont);
									pCustomDraw->clrText = CScheme::GetColour ("TREE_LVL3_NORMAL_FG");
								}
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
					}
					
					*pResult = CDRF_SKIPDEFAULT;
					return false;

			}
		}
		break;
		case NM_CLICK:
		{
			if(pNmhdr->idFrom == IDC_ITEMTREE)
			{
				DWORD dwpos = GetMessagePos();
				TVHITTESTINFO ht = {0};

				// include <windowsx.h> and <windows.h> header files
				ht.pt.x = GET_X_LPARAM(dwpos);
				ht.pt.y = GET_Y_LPARAM(dwpos);
				::MapWindowPoints(HWND_DESKTOP, pNmhdr->hwndFrom, &ht.pt, 1);

				TreeView_HitTest(pNmhdr->hwndFrom, &ht);

				if(TVHT_ONITEMSTATEICON & ht.flags)
				{

					HTREEITEM l_cGroupTreeItem;
					HTREEITEM l_cItemTreeItem;
					bool l_bItemsToDelete = false;
					
					l_cGroupTreeItem = m_cItemTree.GetRootItem ();
					while (l_cGroupTreeItem)
					{
						if (l_cGroupTreeItem == ht.hItem)
						{
							l_bItemsToDelete = l_bItemsToDelete || (!m_cItemTree.GetCheck (l_cGroupTreeItem));

							l_cItemTreeItem = m_cItemTree.GetChildItem (l_cGroupTreeItem);
							while (l_cItemTreeItem)
							{
								m_cItemTree.SetCheck (l_cItemTreeItem, !m_cItemTree.GetCheck (l_cGroupTreeItem));
								l_cItemTreeItem = m_cItemTree.GetNextSiblingItem (l_cItemTreeItem);
							}
						}
						else
						{
							l_bItemsToDelete = l_bItemsToDelete || (m_cItemTree.GetCheck (l_cGroupTreeItem));
						}

						l_cItemTreeItem = m_cItemTree.GetChildItem (l_cGroupTreeItem);
						while (l_cItemTreeItem)
						{
							if (l_cItemTreeItem == ht.hItem)
							{
								l_bItemsToDelete = l_bItemsToDelete || (!m_cItemTree.GetCheck (l_cItemTreeItem));
								m_cItemTree.SetCheck (l_cGroupTreeItem, false);
							}
							else
							{
								l_bItemsToDelete = l_bItemsToDelete || (m_cItemTree.GetCheck (l_cItemTreeItem));
							}
							l_cItemTreeItem = m_cItemTree.GetNextSiblingItem (l_cItemTreeItem);
						}

						l_cGroupTreeItem = m_cItemTree.GetNextSiblingItem (l_cGroupTreeItem);
					}

					m_cDeleteButton.EnableWindow (l_bItemsToDelete);
				}
			}
		}
		break;
		case UM_CHECKSTATECHANGE:
		{
		}
		break;
	}

	
	return CDialog::OnNotify(wParam, lParam, pResult);
}

void COrderDialog::OnSelchangedItemtree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	if (!m_bItemTreeExpand)
	{
		HTREEITEM l_TreeItem = m_cItemTree.GetSelectedItem ();
		int l_iPrevOrderId = CAppData::m_iCurrentOrderId;

		if (m_cItemTree.GetChildItem (l_TreeItem) == NULL)
		{
			DisplayOrderItem (m_cItemTree.GetItemData (l_TreeItem));
			COrderItem l_cOrderItem;

			if (CAppData::FindOrderItem (CAppData::m_iCurrentOrderId, l_cOrderItem))
			{
				CAppData::m_bEditMode = true;	
				if (l_iPrevOrderId != CAppData::m_iCurrentOrderId)
				{
					CAppData::m_cItemCreationWnd.SelectFormula (l_cOrderItem);

					if (CAppData::m_cItemCreationWnd.m_cWindowState.m_bLoaded)
					{
						CAppData::m_cItemCreationWnd.DisplayItems ();
					}

					if (CAppData::m_cSkillLevelWnd.m_cWindowState.m_bVisible)
					{
						CAppData::m_cSkillLevelWnd.DisplaySkillLevels();
					}
				}
			}
		}
		else
		{
			DisplayOrderItem (0);
			if (CAppData::m_cItemCreationWnd.m_cWindowState.m_bLoaded)
			{
				CAppData::m_cItemCreationWnd.ResetItemEdit ();
			}
		}
	}

	*pResult = 0;
}

void COrderDialog::OnEndlabeleditItemtree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	COrderItem l_cOrderItem;
	HTREEITEM l_cSelectedItem;
	CString l_csPrevName;
	CString l_csNewName;
	CString l_csStr;
	int l_iOffset;

	if (pTVDispInfo->item.pszText != NULL)
	{
		if (pTVDispInfo->item.pszText[0] != NULL)
		{
			l_cSelectedItem = pTVDispInfo->item.hItem;

			if (m_cItemTree.GetParentItem (l_cSelectedItem) != NULL)
			{
				if (CAppData::FindOrderItem (pTVDispInfo->item.lParam, l_cOrderItem))
				{
					l_csNewName = pTVDispInfo->item.pszText;
					l_iOffset = l_csNewName.Find (" x ");

					if (l_iOffset > 0)
					{
						l_csNewName = l_csNewName.Mid (l_iOffset + 3);
					}
					l_csNewName.Replace ('<', '[');
					l_csNewName.Replace ('>', ']');
					l_csNewName.Replace ("&", "and");
					m_cItemTree.SetItemText (l_cSelectedItem, l_csNewName);
					l_cOrderItem.m_csItemName = l_csNewName;
					CAppData::UpdateOrderItem (l_cOrderItem);

					DisplayOrderItem (l_cOrderItem.m_iId);
				}
			}
			else
			{
				l_csPrevName = m_cItemTree.GetItemText (l_cSelectedItem);
				l_csNewName = pTVDispInfo->item.pszText;
				l_csNewName.Replace ('<', '[');
				l_csNewName.Replace ('>', ']');
				l_csNewName.Replace ("&", "and");
				m_cItemTree.SetItemText (l_cSelectedItem, l_csNewName);
				CAppData::UpdateOrderGroup (l_csPrevName, l_csNewName);
			}

			*pResult = 1;
		}
		else
		{
			*pResult = 0;
		}
	}
	else
	{
		*pResult = 0;
	}
}

COrderDialog::DisplayOrderItem(int a_iOrderId)
{
	COrderItem l_cOrderItem;
	POSITION l_Pos;
	CFormula *l_cpFormula;
	CFormulaTier *l_cpFormulaTier;
	CItemTech l_cItemTech;
	CTech *l_cpTech = NULL;
	CTechTier *l_cpTechTier = NULL;
	int l_iOffset = 0;
	bool l_bOrderItem = false;

	CAppData::m_iCurrentOrderId = 0;

	if (a_iOrderId > 0)
	{
		if (CAppData::FindOrderItem (a_iOrderId, l_cOrderItem))
		{
			if (CAppData::FindFormula (l_cOrderItem.m_csCategory, l_cOrderItem.m_csFormulaName, &l_cpFormula))
			{
				if (l_cpFormula->FindFormulaTier (l_cOrderItem.m_csTierName, &l_cpFormulaTier))
				{
					l_bOrderItem = true;

					m_cItemName.SetWindowText ("--- " + l_cpFormulaTier->m_csName + " ---");
					m_cTechList.DeleteAllItems ();

					l_Pos = l_cOrderItem.m_clTechList.GetHeadPosition ();
					while (l_Pos)
					{
						l_cItemTech = l_cOrderItem.m_clTechList.GetNext (l_Pos);

						if (CAppData::FindTech (l_cItemTech.m_csCategory, l_cItemTech.m_csTechName, &l_cpTech))
						{

							if (l_cpTech->FindTechTier (l_cItemTech.m_csTierName, &l_cpTechTier))
							{
								m_cTechList.InsertItem (l_iOffset, l_cpTechTier->m_csName, l_cpTech->m_iIcon);
								m_cTechList.SetItemData (l_iOffset++, 5);
							}
						}
					}

					CString l_csValue;

					l_csValue.Format ("%d", l_cOrderItem.m_iQty);
					m_cItemQty.SetWindowText (l_csValue);

					DisplayTotalQty (l_cOrderItem.m_iQty, l_cpFormula->m_iBatchQty);

					CAppData::m_iCurrentOrderId = l_cOrderItem.m_iId;

				}
			}

		}
	}
	else
	{
		m_cItemName.SetWindowText ("");
		m_cItemQty.SetWindowText ("");
		m_cItemTotalQty.SetWindowText ("");
		m_cTechList.DeleteAllItems ();
	}

	m_cTechList.EnableWindow (l_bOrderItem);
	m_cItemQty.EnableWindow (l_bOrderItem);
	m_cQtySpin.EnableWindow (l_bOrderItem);
	m_cCopyItemButton.EnableWindow (l_bOrderItem);
	m_cAlignTiers.EnableWindow (l_bOrderItem);
	m_cCopyToClipboardButton.EnableWindow (l_bOrderItem);
}


COrderDialog::DisplayTotalQty(int a_iQty, int a_iFormQty)
{
	CString l_csValue;

	l_csValue.Format ("batches x %d per batch = %d", a_iFormQty, a_iFormQty * a_iQty);
	m_cItemTotalQty.SetWindowText (l_csValue);
}


void COrderDialog::OnClose() 
{
	CAppData::SetOrderWindow (false);
	CDialog::OnClose();
}

void COrderDialog::OnOK() 
{
}

void COrderDialog::OnOptionsSnapshotwindow() 
{
	CAppData::SetOrderWindowState ();
}

void COrderDialog::OnOptionsRestorewindow() 
{
	CAppData::GetOrderWindowState ();
}

void COrderDialog::OnHelpIndex() 
{
	CAppData::LaunchWebLink ((CString) "orderwindow");	
}

void COrderDialog::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
}

void COrderDialog::OnWindowPosChanging( WINDOWPOS* lpwndpos )
{
	CRect l_cRect;
	this->GetWindowRect (l_cRect);
	
	m_cWindowState.SnapToWnd (lpwndpos, &l_cRect, NULL, CAppData::m_iStickyStrength);
	m_cWindowState.SnapToWnd (lpwndpos, &l_cRect, CAppData::m_cpHCCDlg, CAppData::m_iStickyStrength);
	
	if (CAppData::m_cItemCreationWnd.m_cWindowState.m_bVisible)
	{
		m_cWindowState.SnapToWnd (lpwndpos, &l_cRect, &CAppData::m_cItemCreationWnd, CAppData::m_iStickyStrength);
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

void COrderDialog::OnMoving( UINT nSide, LPRECT lpRect )
{

}

void COrderDialog::OnWindowAlwaysontop() 
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

void COrderDialog::OnClickItemtree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (!m_bItemTreeExpand)
	{
		HTREEITEM l_TreeItem = m_cItemTree.GetSelectedItem ();
		int l_iPrevOrderId = CAppData::m_iCurrentOrderId;

		if (m_cItemTree.GetChildItem (l_TreeItem) == NULL)
		{
			DisplayOrderItem (m_cItemTree.GetItemData (l_TreeItem));
			CAppData::m_bEditMode = true;	
			COrderItem l_cOrderItem;

			if (CAppData::FindOrderItem (CAppData::m_iCurrentOrderId, l_cOrderItem))
			{
				CAppData::m_bEditMode = true;	
				if (l_iPrevOrderId != CAppData::m_iCurrentOrderId)
				{
					CAppData::m_cItemCreationWnd.SelectFormula (l_cOrderItem);

					if (CAppData::m_cItemCreationWnd.m_cWindowState.m_bLoaded)
					{
						CAppData::m_cItemCreationWnd.DisplayItems ();
					}

					if (CAppData::m_cSkillLevelWnd.m_cWindowState.m_bVisible)
					{
						CAppData::m_cSkillLevelWnd.DisplaySkillLevels();
					}
				}
			}
		}
		else
		{
			DisplayOrderItem (0);
			if (CAppData::m_cItemCreationWnd.m_cWindowState.m_bLoaded)
			{
				CAppData::m_cItemCreationWnd.ResetItemEdit ();
			}
		}
	}
	*pResult = 0;
}

void COrderDialog::OnSelchangingItemtree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

COrderDialog::DisplayOrderTitle()
{
	CString l_csTitle;

	l_csTitle = CAppData::m_csCurrentOrderFilename;
	if (CAppData::m_bOrderChanged)
	{
		l_csTitle += "*";
	}
	m_cOrderFrame.SetWindowText (l_csTitle);
}

BOOL COrderDialog::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	return (TRUE);
}

COrderDialog::PromoteTechsTiersToFormulaTier()
{
	POSITION l_PrevPos;
	POSITION l_Pos;
	CFormula *l_cpFormula;
	CFormulaTier *l_cpFormulaTier;
	CItemTech l_cItemTech;
	CTech *l_cpTech = NULL;
	CTechTier *l_cpTechTier = NULL;
	int l_iTier = 0;
	bool l_bUpdate = false;

	if (CAppData::m_iCurrentOrderId > 0)
	{
		if (CAppData::FindFormula (CAppData::m_cCurrentOrderItem.m_csCategory, CAppData::m_cCurrentOrderItem.m_csFormulaName, &l_cpFormula))
		{
			if (l_cpFormula->FindFormulaTier (CAppData::m_cCurrentOrderItem.m_csTierName, &l_cpFormulaTier))
			{
				l_iTier = l_cpFormulaTier->m_iTierLevel;

				l_Pos = CAppData::m_cCurrentOrderItem.m_clTechList.GetHeadPosition ();
				while (l_Pos)
				{
					l_PrevPos = l_Pos;
					l_cItemTech = CAppData::m_cCurrentOrderItem.m_clTechList.GetNext (l_Pos);

					if (CAppData::FindTech (l_cItemTech.m_csCategory, l_cItemTech.m_csTechName, &l_cpTech))
					{

						if (l_cpTech->FindTechTier (CAppData::GetTierName (l_iTier), &l_cpTechTier))
						{
							if (l_cItemTech.m_csTierName != l_cpTechTier->m_csTierName)
							{
								l_cItemTech.m_csTierName = l_cpTechTier->m_csTierName;
								CAppData::m_cCurrentOrderItem.m_clTechList.SetAt (l_PrevPos, l_cItemTech);
								l_bUpdate= true;
							}
						}
					}
				}
			}

			if (l_bUpdate)
			{
				CAppData::UpdateOrderItem (CAppData::m_cCurrentOrderItem);
				DisplayOrderItem (CAppData::m_iCurrentOrderId);
				CAppData::m_cItemCreationWnd.DisplayFormulaTechs ();
			}
		}
	}

}

void COrderDialog::OnAligntiers() 
{
	PromoteTechsTiersToFormulaTier ();
	
}
