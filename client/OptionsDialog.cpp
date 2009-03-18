// OptionsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "HCC.h"
#include "OptionsDialog.h"
#include "AppData.h"
#include "Scheme.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsDialog dialog


COptionsDialog::COptionsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(COptionsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionsDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void COptionsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsDialog)
	DDX_Control(pDX, IDC_PRIORITYCHECK, m_cPriorityCheck);
	DDX_Control(pDX, IDC_AUTOUPDATECHECK, m_cAutoUpdateCheck);
	DDX_Control(pDX, IDC_THEMECOMBO, m_cThemeCombo);
	DDX_Control(pDX, IDC_TOOLBARDRAGCHECK, m_cToolbarCheck);
	DDX_Control(pDX, IDC_DOCKINGCOMBO, m_cDockingCombo);
	DDX_Control(pDX, IDC_HOTKEYCHECK, m_cHotKeyCheck);
	DDX_Control(pDX, IDC_ICONSIZECOMBO, m_cIconSizeCombo);
	DDX_Control(pDX, IDC_ICONCHECK, m_cIconCheck);
	DDX_Control(pDX, IDC_GAMEDIR, m_cGameDir);
	DDX_Control(pDX, IDC_CACHECHECK, m_cCacheCheck);
	DDX_Control(pDX, IDC_BROWSEBUTTON, m_cBrowseButton);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsDialog, CDialog)
	//{{AFX_MSG_MAP(COptionsDialog)
	ON_BN_CLICKED(IDC_BROWSEBUTTON, OnBrowsebutton)
	ON_COMMAND(ID_HELP_INDEX, OnHelpIndex)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsDialog message handlers

BOOL COptionsDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	Initialise();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

COptionsDialog::Initialise()
{
	m_cGameDir.SetWindowText (CAppData::m_csGameBasePath);

	if (CAppData::m_bEnableCache)
	{
		m_cCacheCheck.SetCheck (1);
	}
	else
	{
		m_cCacheCheck.SetCheck (0);
	}

	if (CAppData::m_bEnableIcons)
	{
		m_cIconCheck.SetCheck (1);
	}
	else
	{
		m_cIconCheck.SetCheck (0);
	}

	if (CAppData::m_bGlobalHotkeys)
	{
		m_cHotKeyCheck.SetCheck (1);
	}
	else
	{
		m_cHotKeyCheck.SetCheck (0);
	}

	if (CAppData::m_bDragWithToolBar)
	{
		m_cToolbarCheck.SetCheck (1);
	}
	else
	{
		m_cToolbarCheck.SetCheck (0);
	}

	if (CAppData::m_bAutoUpdate)
	{
		m_cAutoUpdateCheck.SetCheck (1);
	}
	else
	{
		m_cAutoUpdateCheck.SetCheck (0);
	}

	if (CAppData::m_bHighPriority)
	{
		m_cPriorityCheck.SetCheck (1);
	}
	else
	{
		m_cPriorityCheck.SetCheck (0);
	}

	if (CAppData::m_iIconSize == 12)
	{
		m_cIconSizeCombo.SetCurSel (0);
	}
	else if (CAppData::m_iIconSize == 16)
	{
		m_cIconSizeCombo.SetCurSel (1);
	}
	else if (CAppData::m_iIconSize == 20)
	{
		m_cIconSizeCombo.SetCurSel (2);
	}
	else if (CAppData::m_iIconSize == 24)
	{
		m_cIconSizeCombo.SetCurSel (3);
	}

	if (CAppData::m_iStickyStrength == 0)
	{
		m_cDockingCombo.SetCurSel (0);
	}
	else if (CAppData::m_iStickyStrength == 8)
	{
		m_cDockingCombo.SetCurSel (1);
	}
	else if (CAppData::m_iStickyStrength == 16)
	{
		m_cDockingCombo.SetCurSel (2);
	}
	else if (CAppData::m_iStickyStrength == 24)
	{
		m_cDockingCombo.SetCurSel (3);
	}

	CFileFind l_cFileFind;
	bool l_bSearching;

	CAppData::ClearComboBox (m_cThemeCombo);
	l_bSearching = (l_cFileFind.FindFile (CAppData::m_csAppBasePath + cPath_App_Theme + "\\*.xml") != 0);
	while (l_bSearching)
	{
		l_bSearching = (l_cFileFind.FindNextFile () != 0);

		if (!l_cFileFind.IsDirectory ())
		{
			// Search for xml files
			if (l_cFileFind.GetFileName().Find (".xml") >= 0)
			{
				m_cThemeCombo.AddString (l_cFileFind.GetFileName());
			}
		}

	}

	l_cFileFind.Close ();

	m_cThemeCombo.SelectString (-1, CAppData::m_csCurrentTheme);
}

void COptionsDialog::OnOK()
{
	bool l_bRecache = false;
	CString l_csSize;
	int l_iSize;
	bool l_bIconCheck;
	bool l_bCacheCheck;
	CString l_csPath;
	CString l_csTheme;

	CAppData::m_bGlobalHotkeys = m_cHotKeyCheck.GetCheck () > 0;
	CAppData::m_bDragWithToolBar = m_cToolbarCheck.GetCheck () > 0;
	CAppData::m_bHighPriority = m_cPriorityCheck.GetCheck () > 0;
	CAppData::m_bAutoUpdate = m_cAutoUpdateCheck.GetCheck () > 0;

	if (CAppData::m_bHighPriority)
	{
		SetThreadPriority (GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);
	}
	else
	{
		SetThreadPriority (GetCurrentThread(), THREAD_PRIORITY_NORMAL);
	}

	if (m_cDockingCombo.GetCurSel () == 0)
	{
		CAppData::m_iStickyStrength = 0;
	}
	else if (m_cDockingCombo.GetCurSel () == 1)
	{
		CAppData::m_iStickyStrength = 8;
	}
	else if (m_cDockingCombo.GetCurSel () == 2)
	{
		CAppData::m_iStickyStrength = 16;
	}
	else if (m_cDockingCombo.GetCurSel () == 3)
	{
		CAppData::m_iStickyStrength = 24;
	}

	if (m_cIconSizeCombo.GetCurSel () == 0)
	{
		l_iSize = 12;
	}
	else if (m_cIconSizeCombo.GetCurSel () == 1)
	{
		l_iSize = 16;
	}
	else if (m_cIconSizeCombo.GetCurSel () == 2)
	{
		l_iSize = 20;
	}
	else if (m_cIconSizeCombo.GetCurSel () == 3)
	{
		l_iSize = 24;
	}

	if (l_iSize != CAppData::m_iIconSize)
	{
		l_bRecache = true;
	}

	l_bIconCheck = m_cIconCheck.GetCheck () > 0;
	if (l_bIconCheck != CAppData::m_bEnableIcons)
	{
		l_bRecache = true;
	}

	l_bCacheCheck = m_cCacheCheck.GetCheck () > 0;
	if (l_bCacheCheck != CAppData::m_bEnableCache)
	{
		l_bRecache = true;
	}

	m_cGameDir.GetWindowText (l_csPath);
	if (l_csPath != CAppData::m_csGameBasePath)
	{
		CAppData::m_csGameBasePath = l_csPath;
		l_bRecache = true;
	}

	CAppData::m_iIconSize = l_iSize;
	CAppData::m_bEnableIcons = l_bIconCheck;
	CAppData::m_bEnableCache = l_bCacheCheck;
	m_cGameDir.GetWindowText (CAppData::m_csGameBasePath);

	if (l_bRecache)
	{
		CString l_csCacheConfigPath = CAppData::m_csAppBasePath + cPath_App_Cache + cFile_App_ConfigCache;
		CString l_csCacheFormIconPath = CAppData::m_csAppBasePath + cPath_App_Cache + cFile_App_IconCache;

		DeleteFile (l_csCacheConfigPath);
		DeleteFile (l_csCacheFormIconPath);

		if (AfxMessageBox ("In order for these changes to take effect, the database must be recached, this may take some time and will reset any current order. Proceed now, or perform on next start?", MB_YESNO) == IDYES)
		{
			BeginWaitCursor();
			CAppData::SaveDefaults();
			CAppData::Reinitialise ();
			EndWaitCursor( );
		}
	}

	m_cThemeCombo.GetWindowText (l_csTheme);

	if (l_csTheme != CAppData::m_csCurrentTheme)
	{
		CAppData::m_csCurrentTheme = l_csTheme;
		CScheme::LoadHCCScheme (CAppData::m_csAppBasePath + cPath_App_Theme + "\\" + l_csTheme);
		CAppData::ApplyCurrentTheme ();
	}

	CDialog::OnOK();
}

void COptionsDialog::OnBrowsebutton()
{
	BROWSEINFO lpbi;
	char DisplayName [MAX_PATH];
	char Title [] = "Please select the Horizons Installation folder.";
	LPITEMIDLIST m_pItemIdList;
	CString l_csPath;

	lpbi.hwndOwner = this->m_hWnd;
	lpbi.pidlRoot  = NULL;
	lpbi.pszDisplayName = DisplayName;
	lpbi.lpszTitle = Title;
	lpbi.ulFlags = BIF_RETURNONLYFSDIRS;
	lpbi.lpfn  = NULL;
	lpbi.lParam  = NULL;
	lpbi.iImage  = NULL;

	m_pItemIdList = SHBrowseForFolder (&lpbi);

	if (m_pItemIdList)
	{
		SHGetPathFromIDList(m_pItemIdList, l_csPath.GetBufferSetLength(MAX_PATH));
		m_cGameDir.SetWindowText (l_csPath);
	}

}

void COptionsDialog::OnHelpIndex()
{
	CAppData::LaunchWebLink ((CString) "optionwindow");
}

BOOL COptionsDialog::OnHelpInfo(HELPINFO* pHelpInfo)
{
	return (TRUE);
}
