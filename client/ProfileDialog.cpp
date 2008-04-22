// ProfileDialog.cpp : implementation file
//

#include "stdafx.h"
#include "HCC.h"
#include "ProfileDialog.h"
#include "AppData.h"
#include "NewProfileDialog.h"
#include "Scheme.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProfileDialog dialog


CProfileDialog::CProfileDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CProfileDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProfileDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CProfileDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProfileDialog)
	DDX_Control(pDX, IDC_COPYBUTTON, m_cCopyButton);
	DDX_Control(pDX, IDC_NEWBUTTON, m_cNewButton);
	DDX_Control(pDX, IDC_DELETEBUTTON, m_cDeleteButton);
	DDX_Control(pDX, IDC_UPDATE, m_cUpdateButton);
	DDX_Control(pDX, IDC_PROFILETREE, m_cProfileTree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProfileDialog, CDialog)
	//{{AFX_MSG_MAP(CProfileDialog)
	ON_WM_WINDOWPOSCHANGING ()
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZE()
	ON_NOTIFY(TVN_SELCHANGED, IDC_PROFILETREE, OnSelchangedProfiletree)
	ON_WM_CLOSE()
	ON_COMMAND(ID_WINDOW_SNAPSHOTWINDOW, OnWindowSnapshotwindow)
	ON_COMMAND(ID_WINDOW_RESTOREWINDOW, OnWindowRestorewindow)
	ON_COMMAND(ID_HELP_INDEX, OnHelpIndex)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_CLICKED(IDC_NEWBUTTON, OnNewbutton)
	ON_BN_CLICKED(IDC_COPYBUTTON, OnCopybutton)
	ON_BN_CLICKED(IDC_DELETEBUTTON, OnDeletebutton)
	ON_WM_MOVE()
	ON_COMMAND(ID_WINDOW_ALWAYSONTOP, OnWindowAlwaysontop)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProfileDialog message handlers

CProfileDialog::StartUp()
{
	this->Create (IDD_PROFILEDIALOG, CWnd::GetDesktopWindow ());
	m_cWindowState.m_bLoaded = true;
}

CProfileDialog::Initialise()
{
	m_cProfileTree.SetBkColor (CScheme::GetColour ("TREE_BACKCOLOUR"));
}

void CProfileDialog::OnClose()
{
	CAppData::SetProfileWindow (false);

	CDialog::OnClose();
}

void CProfileDialog::OnOK()
{
}

void CProfileDialog::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

}

void CProfileDialog::OnGetMinMaxInfo (MINMAXINFO FAR* lpMMI)
{
	CDialog::OnGetMinMaxInfo (lpMMI);

}

BOOL CProfileDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

   //remove some options from the system menu
   CMenu* pSysMenu = GetSystemMenu(FALSE);
   pSysMenu->RemoveMenu(SC_RESTORE,MF_BYCOMMAND);
   pSysMenu->RemoveMenu(SC_MINIMIZE,MF_BYCOMMAND);
   pSysMenu->RemoveMenu(SC_MAXIMIZE,MF_BYCOMMAND);
   pSysMenu->RemoveMenu(SC_TASKLIST ,MF_BYCOMMAND);
   pSysMenu->RemoveMenu(SC_SIZE,MF_BYCOMMAND);

	m_cProfilePage1.Construct (IDD_PROFILE1DIALOG,0);
	m_cProfilePage2.Construct (IDD_PROFILE2DIALOG,0);
	//m_cProfilePage3.Construct (IDD_PROFILE3DIALOG,0);
	m_ProfileSheet.Construct ("Horizon Crafting Calculator", NULL, 0);
	m_ProfileSheet.AddPage (&m_cProfilePage1);
	m_ProfileSheet.AddPage (&m_cProfilePage2);
	//m_ProfileSheet.AddPage (&m_cProfilePage3);
	m_ProfileSheet.Create (this, WS_CHILD | WS_VISIBLE, WS_EX_CONTROLPARENT);
	m_ProfileSheet.SetWindowPos(NULL, 192, 0, 259, 470, SWP_NOZORDER);

	m_cProfilePage1.m_cStatistcsList.InsertColumn (0, "Statistic", LVCFMT_LEFT, 150, -1);
	m_cProfilePage1.m_cStatistcsList.InsertColumn (1, "Amount", LVCFMT_RIGHT, 68, -1);

	Initialise ();

	DrawProfileTree();

	CMenu *l_pMenu;
	l_pMenu = GetMenu ();
	if (l_pMenu)
	{
		CAppData::SetMenuItem(l_pMenu, ID_WINDOW_ALWAYSONTOP, m_cWindowState.m_bOnTop);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


CProfileDialog::DrawProfileTree()
{
	CProfile *l_cpProfile;
	POSITION l_Pos;
	CString l_csType;
	HTREEITEM l_cDefaultTreeItem;
	HTREEITEM l_cLocalTreeItem;
	//HTREEITEM l_cRemoteTreeItem;
	HTREEITEM l_cCurrentItem;
	HTREEITEM l_cSelectedItem = NULL;
	CString l_csProfileName;

	m_cProfileTree.DeleteAllItems ();
	m_cUpdateButton.EnableWindow (CAppData::m_bProfilesChanged);

	l_cDefaultTreeItem = m_cProfileTree.InsertItem (cAppData_Profile_Defaults, 0, 0, TVI_ROOT, TVI_LAST);
	l_cLocalTreeItem = m_cProfileTree.InsertItem (cAppData_Profile_Local, 0, 0, TVI_ROOT, TVI_LAST);
	//l_cRemoteTreeItem = m_cProfileTree.InsertItem (cAppData_Profile_Server, 0, 0, TVI_ROOT, TVI_LAST);

	l_Pos = CAppData::m_clProfileList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpProfile = CAppData::m_clProfileList.GetNext (l_Pos);
		if (l_cpProfile != CAppData::m_cpTemplateProfile)
		{
			if (l_cpProfile->m_bChanged)
			{
				l_csProfileName = l_cpProfile->m_csProfileServer + ":" + l_cpProfile->m_csProfileName + "*";
			}
			else
			{
				l_csProfileName = l_cpProfile->m_csProfileServer + ":" + l_cpProfile->m_csProfileName;
			}

			if (l_cpProfile->m_csProfileType == cAppData_Profile_Defaults)
			{
				l_cCurrentItem = m_cProfileTree.InsertItem (l_csProfileName, 0, 0, l_cDefaultTreeItem, TVI_LAST);
			}
			else if (l_cpProfile->m_csProfileType == cAppData_Profile_Local)
			{
				l_cCurrentItem = m_cProfileTree.InsertItem (l_csProfileName, 0, 0, l_cLocalTreeItem, TVI_LAST);
			}
			//else if (l_cpProfile->m_csProfileType == cAppData_Profile_Server)
			//{
			//	l_cCurrentItem = m_cProfileTree.InsertItem (l_csProfileName, 0, 0, l_cRemoteTreeItem, TVI_LAST);
			//}

			if (l_cpProfile == CAppData::m_cpCurrentProfile)
			{
				l_cSelectedItem = l_cCurrentItem;
			}
		}
	}

	m_cProfileTree.Expand (l_cDefaultTreeItem,  TVE_EXPAND);
	m_cProfileTree.Expand (l_cLocalTreeItem,  TVE_EXPAND);
	//m_cProfileTree.Expand (l_cRemoteTreeItem,  TVE_EXPAND);

	if (l_cSelectedItem)
	{
		m_cProfileTree.SelectItem (l_cSelectedItem);
	}
}


void CProfileDialog::OnSelchangedProfiletree(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	HTREEITEM l_TreeItem = m_cProfileTree.GetSelectedItem ();
	CString l_csCurProfile;
	CString l_csProfileName;
	CString l_csProfileServer;
	int l_iOffset;

	m_cCopyButton.EnableWindow (false);
	m_cDeleteButton.EnableWindow (false);
	l_csCurProfile = m_cProfileTree.GetItemText (l_TreeItem);
	CAppData::m_cItemCreationWnd.m_cProfileSelecter.SelectString (0, l_csCurProfile);

	l_csCurProfile = GetProfileName (l_csCurProfile);
	l_iOffset = l_csCurProfile.Find (':', 0);
	if (l_iOffset > 0)
	{
		l_csProfileServer = l_csCurProfile.Left (l_iOffset);
		l_csProfileName = l_csCurProfile.Mid (l_iOffset + 1);

		if (CAppData::FindProfile (l_csProfileName, l_csProfileServer, &CAppData::m_cpCurrentProfile))
		{

			DisplayProfile ();
			m_cProfilePage2.DisplayProfile ();
			//m_cProfilePage3.DisplayProfile();

			CAppData::m_csCurrentProfile = CAppData::m_cpCurrentProfile->m_csProfileName;
			CAppData::m_csCurrentProfileType = CAppData::m_cpCurrentProfile->m_csProfileType;
			CAppData::m_cItemCreationWnd.DisplayFormula (false);

			m_cCopyButton.EnableWindow (true);
			m_cDeleteButton.EnableWindow (CAppData::m_csCurrentProfileType != cAppData_Profile_Defaults);
		}
	}

	*pResult = 0;
}

CProfileDialog::DisplayProfile()
{
	POSITION l_Pos;
	CBonus *l_cpBonus;
	CString l_csValue;
	int l_iOffset;

	if (CAppData::m_cpCurrentProfile)
	{
		m_cProfilePage1.m_cProfileName.SetWindowText (CAppData::m_cpCurrentProfile->m_csProfileName);
		m_cProfilePage1.m_cProfileServerCombo.SelectString (-1, CAppData::m_cpCurrentProfile->m_csProfileServer);
		if (CAppData::m_cpCurrentProfile->m_csProfileEmail.IsEmpty ())
		{
			m_cProfilePage1.m_cProfileEmail.SetWindowText ("");
		}
		else
		{
			m_cProfilePage1.m_cProfileEmail.SetWindowText (CAppData::m_cpCurrentProfile->m_csProfileEmail);
		}

		m_cProfilePage1.m_cStatistcsList.DeleteAllItems ();
		l_iOffset = 0;
		l_Pos = CAppData::m_cpCurrentProfile->m_clStatisticList.GetHeadPosition ();
		while (l_Pos)
		{
			l_cpBonus = CAppData::m_cpCurrentProfile->m_clStatisticList.GetNext (l_Pos);
			l_csValue.Format ("%d", l_cpBonus->m_iValue);
			m_cProfilePage1.m_cStatistcsList.InsertItem (l_iOffset, l_cpBonus->m_csBonusName);
			m_cProfilePage1.m_cStatistcsList.SetItemText (l_iOffset, 1, l_csValue);
			l_iOffset++;
		}
	}
}

CProfileDialog::SelectProfile(CString &a_csProfileName)
{
	HTREEITEM l_cParentItem;
	HTREEITEM l_cChildItem;
	CString l_csProfileName;

	if (m_cWindowState.m_bLoaded)
	{
		l_cParentItem = m_cProfileTree.GetRootItem ();

		while (l_cParentItem)
		{
			l_cChildItem = m_cProfileTree.GetChildItem (l_cParentItem);
			while (l_cChildItem)
			{
				l_csProfileName = GetProfileName (m_cProfileTree.GetItemText (l_cChildItem));

				if (l_csProfileName == a_csProfileName)
				{
					m_cProfileTree.SelectItem (l_cChildItem);
					l_cChildItem = NULL;
					l_cParentItem = NULL;
				}
				else
				{
					l_cChildItem = m_cProfileTree.GetNextSiblingItem (l_cChildItem);
				}
			}

			if (l_cParentItem)
			{
				l_cParentItem = m_cProfileTree.GetNextSiblingItem (l_cParentItem);
			}
		}
	}
}


void CProfileDialog::OnWindowSnapshotwindow()
{
	CAppData::SetProfileWindowState ();
}

void CProfileDialog::OnWindowRestorewindow()
{
	CAppData::GetProfileWindowState ();
}

void CProfileDialog::OnHelpIndex()
{
	CAppData::LaunchWebLink ((CString) "profilewindow");
}

CString CProfileDialog::GetProfileName(CString &a_csProfileText)
{
	if (a_csProfileText[a_csProfileText.GetLength () - 1] == '*')
	{
		return (a_csProfileText.Left (a_csProfileText.GetLength () - 1));
	}

	return (a_csProfileText);
}

void CProfileDialog::OnUpdate()
{
	CAppData::SaveProfiles (false);
	DrawProfileTree ();
}

void CProfileDialog::OnNewbutton()
{
	CNewProfileDialog l_cNewProfileDialog(this);

	if (CAppData::m_cpTemplateProfile)
	{
		l_cNewProfileDialog.m_csName = "";
		l_cNewProfileDialog.m_csServer = "Blight";
		GetWindowRect (l_cNewProfileDialog.m_cRect);
		this->EnableWindow (false);
		if (l_cNewProfileDialog.DoModal () == IDOK)
		{
			CProfile *l_cpNewProfile = new CProfile ();
			l_cpNewProfile->CopyObject (CAppData::m_cpTemplateProfile);
			l_cpNewProfile->m_csProfileName = l_cNewProfileDialog.m_csName;
			l_cpNewProfile->m_csProfileServer = l_cNewProfileDialog.m_csServer;
			l_cpNewProfile->m_csProfileType = cAppData_Profile_Local;
			l_cpNewProfile->m_bChanged = true;
			CAppData::m_clProfileList.AddTail (l_cpNewProfile);
			CAppData::SetProfilesChangeState (true);
			CAppData::m_cpCurrentProfile = l_cpNewProfile;
			CAppData::m_cItemCreationWnd.DisplayProfiles ();
			DrawProfileTree ();
		}
		this->EnableWindow (true);
	}
	else
	{
		AfxMessageBox ("Error - No Default Template Found", MB_ICONEXCLAMATION );
	}
}

void CProfileDialog::OnCopybutton()
{
	CNewProfileDialog l_cNewProfileDialog(this);

	if (CAppData::m_cpCurrentProfile)
	{
		l_cNewProfileDialog.m_csName = "";
		l_cNewProfileDialog.m_csServer = CAppData::m_cpCurrentProfile->m_csProfileServer;
		GetWindowRect (l_cNewProfileDialog.m_cRect);
		this->EnableWindow (false);
		if (l_cNewProfileDialog.DoModal () == IDOK)
		{
			CProfile *l_cpNewProfile = new CProfile ();
			l_cpNewProfile->CopyObject (CAppData::m_cpCurrentProfile);
			l_cpNewProfile->m_csProfileName = l_cNewProfileDialog.m_csName;
			l_cpNewProfile->m_csProfileServer = l_cNewProfileDialog.m_csServer;
			l_cpNewProfile->m_csProfileType = cAppData_Profile_Local;
			l_cpNewProfile->m_bChanged = true;
			CAppData::m_clProfileList.AddTail (l_cpNewProfile);
			CAppData::SetProfilesChangeState (true);
			CAppData::m_cpCurrentProfile = l_cpNewProfile;
			CAppData::m_cItemCreationWnd.DisplayProfiles ();
			DrawProfileTree ();
		}
		this->EnableWindow (true);
	}
}

void CProfileDialog::OnDeletebutton()
{
	CString l_csFilePath = "";
	CProfile *l_cpProfile = NULL;
	POSITION l_PrevPos;
	POSITION l_Pos;

	if (CAppData::m_cpCurrentProfile)
	{
		if (CAppData::m_cpCurrentProfile->m_csProfileType != cAppData_Profile_Defaults)
		{
			if (MessageBox ("Do you really want to delete this profile?", "Confirmation Required", MB_YESNO) == IDYES)
			{
				if (CAppData::m_cpCurrentProfile->m_csProfileType == cAppData_Profile_Local)
				{
					l_csFilePath = CAppData::m_csAppBasePath + cPath_App_LocalProfiles + "\\" + CAppData::m_cpCurrentProfile->m_csProfileName + ".xml";
				}
				else if (CAppData::m_cpCurrentProfile->m_csProfileType == cAppData_Profile_Server)
				{
					l_csFilePath = CAppData::m_csAppBasePath + cPath_App_ServerProfiles + "\\" + CAppData::m_cpCurrentProfile->m_csProfileName + ".xml";
				}

				if (!l_csFilePath.IsEmpty ())
				{
					DeleteFile (l_csFilePath);
				}

				l_Pos = CAppData::m_clProfileList.GetHeadPosition ();
				while (l_Pos)
				{
					l_PrevPos = l_Pos;
					l_cpProfile = CAppData::m_clProfileList.GetNext (l_Pos);

					if (l_cpProfile == CAppData::m_cpCurrentProfile)
					{
						CAppData::m_clProfileList.RemoveAt (l_PrevPos);
					}
				}

				CAppData::m_cpCurrentProfile->Destroy ();
				delete (CAppData::m_cpCurrentProfile);

				CAppData::m_cpCurrentProfile = CAppData::m_cpTemplateProfile;
				CAppData::m_cItemCreationWnd.DisplayProfiles ();
				DrawProfileTree ();
			}

		}
		else
		{
			AfxMessageBox ("Error - Cannot delete Default Templates, these are required by the application!", MB_ICONEXCLAMATION );
		}
	}
}

void CProfileDialog::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);
}

void CProfileDialog::OnWindowPosChanging( WINDOWPOS* lpwndpos )
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

	if (CAppData::m_cReportWnd.m_cWindowState.m_bVisible)
	{
		m_cWindowState.SnapToWnd (lpwndpos, &l_cRect, &CAppData::m_cReportWnd, CAppData::m_iStickyStrength);
	}

	CDialog::OnWindowPosChanging(lpwndpos);
}

void CProfileDialog::OnWindowAlwaysontop()
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

BOOL CProfileDialog::OnHelpInfo(HELPINFO* pHelpInfo)
{
	return (TRUE);
}
