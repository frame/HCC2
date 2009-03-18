// HCCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HCC.h"
#include "HCCDlg.h"
#include "AppData.h"
#include "OptionsDialog.h"
#include "CrafterSearchDialog.h"
#include "UpdateDialog.h"
#include "WizardPage1.h"
#include "WizardPage2.h"
#include "WizardPage3.h"
#include "WizardDialog.h"
#include "Scheme.h"
#include "XWinVer.h"
#include "Regexp.h"

using namespace Gdiplus;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CButton	m_cTitle;
	CListCtrl	m_cCountList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_TITLE, m_cTitle);
	DDX_Control(pDX, IDC_COUNTLIST, m_cCountList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHCCDlg dialog

CHCCDlg::CHCCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHCCDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHCCDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	m_cpDockWnd = NULL;
	l_bRestored = false;
}

void CHCCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHCCDlg)
	DDX_Control(pDX, IDC_ORDERSHEADER, m_cOrdersHeader);
	DDX_Control(pDX, IDC_ONLINEHEADER, m_cOnlineHeader);
	DDX_Control(pDX, IDC_DATABASEHEADER, m_cDatabaseHeader);
	DDX_Control(pDX, IDC_SUBMIT, m_cSubmitOrder);
	DDX_Control(pDX, IDC_AUTODOCK, m_cAutoDock);
	DDX_Control(pDX, IDC_ORDERBUTTON, m_cOrderButton);
	DDX_Control(pDX, IDC_TITLEFRAME, m_cTitleFrame);
	DDX_Control(pDX, IDC_DATABASETITLE, m_cDatabaseTitle);
	DDX_Control(pDX, IDC_COMPBUTTON, m_cCompButton);
	DDX_Control(pDX, IDC_PROFILEBUTTON, m_cProfileButton);
	DDX_Control(pDX, IDC_REPORTBUTTON, m_cReportButton);
	DDX_Control(pDX, IDC_UPDATEBUTTON, m_cUpdateButton);
	DDX_Control(pDX, IDC_WIZARDBUTTON, m_cWizardButton);
	DDX_Control(pDX, IDC_CRAFTERSEARCH, m_cCrafterSearch);
	DDX_Control(pDX, IDC_TECHBUTTON, m_cTechButton);
	DDX_Control(pDX, IDC_FORMBUTTON, m_cFormButton);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHCCDlg, CDialog)
	//{{AFX_MSG_MAP(CHCCDlg)
	ON_WM_WINDOWPOSCHANGING ()
	ON_WM_PAINT()
	ON_WM_SYSCOMMAND()
	ON_COMMAND(ID_VIEW_ITEMS, OnViewItems)
	ON_COMMAND(ID_VIEW_TECHNIQUES, OnViewTechniques)
	ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_COMMAND(ID_SETTINGS_OPTIONS, OnSettingsOptions)
	ON_BN_CLICKED(IDC_FORMBUTTON, OnFormbutton)
	ON_BN_CLICKED(IDC_TECHBUTTON, OnTechbutton)
	ON_BN_CLICKED(IDC_CRAFTERSEARCH, OnCraftersearch)
	ON_COMMAND(ID_SETTINGS_ORDERWINDOW_SNAPSHOTWINDOW, OnSettingsOrderwindowSnapshotwindow)
	ON_COMMAND(ID_SETTINGS_ORDERWINDOW_RESTOREDEFAULTS, OnSettingsOrderwindowRestoredefaults)
	ON_COMMAND(ID_SETTINGS_ALLWINDOWS_SNAPSHOTWINDOWS, OnSettingsAllwindowsSnapshotwindows)
	ON_COMMAND(ID_SETTINGS_ALLWINDOWS_RESTOREALLDEFAULTS, OnSettingsAllwindowsRestorealldefaults)
	ON_COMMAND(ID_VIEW_COMPONENTS, OnViewComponents)
	ON_COMMAND(ID_VIEW_REPORTS, OnViewReports)
	ON_BN_CLICKED(IDC_WIZARDBUTTON, OnWizardbutton)
	ON_BN_CLICKED(IDC_COMPBUTTON, OnCompbutton)
	ON_BN_CLICKED(IDC_REPORTBUTTON, OnReportbutton)
	ON_BN_CLICKED(IDC_PROFILEBUTTON, OnProfilebutton)
	ON_BN_CLICKED(IDC_UPDATEBUTTON, OnUpdatebutton)
	ON_COMMAND(ID_SETTINGS_RELOADDATA, OnSettingsReloaddata)
	ON_COMMAND(ID_HELP_INDEX, OnHelpIndex)
	ON_COMMAND(ID_SETTINGS_FORMULAWINDOW_SNAPSHOTWINDOW, OnSettingsFormulawindowSnapshotwindow)
	ON_COMMAND(ID_SETTINGS_FORMULAWINDOW_RESTOREDEFAULTS, OnSettingsFormulawindowRestoredefaults)
	ON_COMMAND(ID_SETTINGS_TECHNIQUEWINDOW_SNAPSHOTWINDOW, OnSettingsTechniquewindowSnapshotwindow)
	ON_COMMAND(ID_SETTINGS_TECHNIQUEWINDOW_RESTOREDEFAULTS, OnSettingsTechniquewindowRestoredefaults)
	ON_COMMAND(ID_SETTINGS_COMPWINDOW_SNAPSHOTWINDOW, OnSettingsCompwindowSnapshotwindow)
	ON_COMMAND(ID_SETTINGS_COMPWINDOW_RESTOREDEFAULTS, OnSettingsCompwindowRestoredefaults)
	ON_COMMAND(ID_SETTINGS_REPORTWINDOW_SNAPSHOTWINDOW, OnSettingsReportwindowSnapshotwindow)
	ON_COMMAND(ID_SETTINGS_REPORTWINDOW_RESTOREDEFAULTS, OnSettingsReportwindowRestoredefaults)
	ON_COMMAND(ID_SETTINGS_PROFILEWINDOW_SNAPSHOTWINDOW, OnSettingsProfilewindowSnapshotwindow)
	ON_COMMAND(ID_SETTINGS_PROFILEWINDOW_RESTOREDEFAULTS, OnSettingsProfilewindowRestoredefaults)
	ON_WM_SHOWWINDOW()
	ON_MESSAGE(WM_HOTKEY, OnHotKey)
	ON_COMMAND(ID_VIEW_FORMULAWINDOW, OnViewFormulawindow)
	ON_COMMAND(ID_VIEW_TECHNIQUEWINDOW, OnViewTechniquewindow)
	ON_COMMAND(ID_VIEW_COMPONENTWINDOW, OnViewComponentwindow)
	ON_COMMAND(ID_VIEW_REPORTWINDOW, OnViewReportwindow)
	ON_COMMAND(ID_VIEW_PROFILEWINDOW, OnViewProfilewindow)
	ON_WM_SIZE()
	ON_COMMAND(ID_SETTINGS_WINDOW_TOOLBARWINDOW_SNAPSHOTWINDOW, OnSettingsWindowToolbarwindowSnapshotwindow)
	ON_COMMAND(ID_SETTINGS_TOOLBARWINDOW_RESTOREDEFAULTS, OnSettingsToolbarwindowRestoredefaults)
	ON_BN_CLICKED(IDC_ORDERBUTTON, OnOrderbutton)
	ON_COMMAND(ID_SETTINGS_VIEW_ORDERWINDOW, OnSettingsViewOrderwindow)
	ON_WM_MOVE()
	ON_BN_CLICKED(IDC_AUTODOCK, OnAutodock)
	ON_COMMAND(ID_WINDOW_ALWAYSONTOP, OnWindowAlwaysontop)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVEAS, OnFileSaveas)
	ON_COMMAND(ID_FILE_EXIT, OnFileExit)
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_KILLFOCUS()
	ON_WM_CAPTURECHANGED()
	ON_WM_CHAR()
	ON_COMMAND(ID_HELP_ONELINEMANUAL, OnHelpOnelinemanual)
	ON_COMMAND(ID_HELP_PLUGINS, OnHelpPlugins)
	ON_COMMAND(ID_HELP_REPORTABUG, OnHelpReportabug)
	ON_WM_HELPINFO()
	ON_COMMAND(ID_OPTIONS_VIEW_LIVEUPDATE, OnOptionsViewLiveupdate)
	ON_COMMAND(ID_OPTIONS_SETTINGS_REFRESHTHEME, OnOptionsSettingsRefreshtheme)
	ON_COMMAND(ID_OPTIONS_ORIENTATION_HORIZONTAL, OnOptionsOrientationHorizontal)
	ON_COMMAND(ID_OPTIONS_ORIENTATION_VERTICAL, OnOptionsOrientationVertical)
	ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
	ON_WM_ACTIVATE()
	ON_COMMAND(ID_SEARCH_BYNAME, OnSearchByname)
	ON_COMMAND(ID_SEARCH_BYFORMNAME, OnSearchByFormname)
	ON_COMMAND(ID_SEARCH_BYCLASS, OnSearchByclass)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHCCDlg message handlers

UINT tbButtons[6] = { ID_VIEW_ITEMS, ID_VIEW_TECHNIQUES};

LRESULT  CHCCDlg::OnHotKey(WPARAM wp, LPARAM)
{
   if (wp == m_nHotKeyID_Forms)
	{
      OnViewFormulawindow ();
	}
	else if (wp == m_nHotKeyID_Techs)
	{
      OnViewTechniquewindow ();
	}
	else if (wp == m_nHotKeyID_Comps)
	{
      OnViewComponentwindow ();
	}
	else if (wp == m_nHotKeyID_Reports)
	{
      OnViewReportwindow ();
	}
	else if (wp == m_nHotKeyID_Updates)
	{
      OnOptionsViewLiveupdate ();
	}
	else if (wp == m_nHotKeyID_Profiles)
	{
      OnViewProfilewindow ();
	}
	else if (wp == m_nHotKeyID_Orders)
	{
      OnSettingsViewOrderwindow ();
	}
	else if (wp == m_nHotKeyID_App)
	{
		ShowWindow(SW_SHOWMINIMIZED    );
 		ShowWindow(SW_SHOWNORMAL );
      SetFocus();
		BringWindowToTop( );
	}

   return 0;
}

void CHCCDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	//http://www.functionx.com/visualc/Lesson02.htm
	CDialog::OnActivate(nState, pWndOther, bMinimized);

	switch( nState )
	{
		case WA_ACTIVE:
			CAppData::RestoreApp();
			break;
	}
}


HINTERNET    hInternetSession = NULL;
HINTERNET    hURL = NULL;

typedef struct
{
    HWND        hWindow;     // window handle

    HINTERNET   hResource;   // HINTERNET handle created by InternetOpenUrl

} REQUEST_CONTEXT;

REQUEST_CONTEXT    request_context;

void __stdcall InternetCallbackFunction(HINTERNET hInternet, DWORD dwContext, DWORD dwInternetStatus, LPVOID lpvStatusInformation, DWORD dwStatusInformationLength)
{
    REQUEST_CONTEXT* cpContext;
    INTERNET_ASYNC_RESULT* res;

    cpContext = (REQUEST_CONTEXT*)dwContext;

    // what has this callback function been told has happened?

    switch (dwInternetStatus)
    {
        case INTERNET_STATUS_HANDLE_CREATED:
            // get the handle now that it has been created so it can be freed up later

            res = (INTERNET_ASYNC_RESULT*)lpvStatusInformation;
            hURL = (HINTERNET)(res->dwResult);

            break;

        case INTERNET_STATUS_REQUEST_COMPLETE:

			char buffer[10*1024];
			DWORD dwBytesRead = 0;
			BOOL bRead = InternetReadFile(hURL,buffer,sizeof(buffer),&dwBytesRead);

			//AfxMessageBox (UpdateResult.Remove("\n") + "-", MB_ICONINFORMATION);
			//AfxMessageBox (CAppData::m_csDatabaseRevision + "-", MB_ICONINFORMATION);

			Regexp re_updatecheck("<update_check>([0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9])</update_check>");
			if ( re_updatecheck.Match( buffer ) )
			{
				//AfxMessageBox (re_updatecheck[1], MB_ICONINFORMATION); // min
				if (re_updatecheck[1] != CAppData::m_csDatabaseRevision)
				{
					AfxMessageBox ("A new update for HCC is available! Bwaaa-ak!!\n\nPlease click on \"Live Update\" to start the download.", MB_ICONINFORMATION);
				}
			}

            InternetCloseHandle(hURL);
            InternetSetStatusCallback(hInternetSession, NULL);
            InternetCloseHandle(hInternetSession);

            hURL = NULL;
            hInternetSession = NULL;

            break;
    }
}

CString CHCCDlg::ReadConfigFile()
{
	bool l_bResult = false;
	XMLParser l_cParser;
	XMLTag l_cRootTag ("#ROOT#");
	XMLTag l_cConfigTag ("config");

	CString updateURL = "http://hcc.reclamation.dk/update_check/";
	l_cParser.OpenFile (CAppData::m_csAppBasePath + cFile_App_Config);

	if (l_cConfigTag.GetNextTag (l_cParser, l_cRootTag))
	{
		l_cConfigTag.GetTagValue (l_cParser, (CString) "update_check", updateURL );
	}

	return updateURL;
}


void CHCCDlg::OnSearchByname()
{
	CAppData::m_cItemCreationWnd.OnSearchByname();
}

void CHCCDlg::OnSearchByFormname()
{
	CAppData::m_cItemCreationWnd.OnSearchByFormname();
}

void CHCCDlg::OnSearchByclass()
{
	CAppData::m_cItemCreationWnd.OnSearchByclass();
}


BOOL CHCCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	static char l_cFaceName[32] = "Arial Bold";

	LOGFONT logfont;
	CFont *pFont = GetFont();
	pFont->GetLogFont( &logfont );
	logfont.lfHeight  = 14;
	logfont.lfWeight  = FW_NORMAL;
	strcpy (logfont.lfFaceName, l_cFaceName);
	CAppData::m_cTitleFont.CreateFontIndirect (&logfont);
	logfont.lfUnderline = true;
	CAppData::m_cTitleSelFont.CreateFontIndirect (&logfont);

	/*CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}*/

    CMenu* pSysMenu = GetSystemMenu(FALSE);
     //remove some options from the system menu
     pSysMenu->RemoveMenu(SC_MAXIMIZE,MF_BYCOMMAND);
     pSysMenu->RemoveMenu(SC_TASKLIST ,MF_BYCOMMAND);
     pSysMenu->RemoveMenu(SC_SIZE,MF_BYCOMMAND);

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_cOrderButton.GetColor (CButtonST::BTNST_COLOR_BK_IN, &CAppData::m_iNeutralColour);

	ghDlg = m_hWnd;

	//Create a hot key for the application
	m_nHotKeyID_Orders = GlobalAddAtom("ID_HK_ORDERS");
	m_nHotKeyID_Forms = GlobalAddAtom("ID_HK_FORMS");
	m_nHotKeyID_Techs = GlobalAddAtom("ID_HK_TECHS");
	m_nHotKeyID_Comps = GlobalAddAtom("ID_HK_COMPS");
	m_nHotKeyID_Reports = GlobalAddAtom("ID_HK_REPORTS");
	m_nHotKeyID_Updates = GlobalAddAtom("ID_HK_UPDATES");
	m_nHotKeyID_Profiles = GlobalAddAtom("ID_HK_PROFILES");
	m_nHotKeyID_App = GlobalAddAtom("ID_HK_APP");


	if (CAppData::m_bGlobalHotkeys)
	{
		RegisterHotKey(GetSafeHwnd(), m_nHotKeyID_Orders,   MOD_SHIFT|MOD_CONTROL, VK_F1);
		RegisterHotKey(GetSafeHwnd(), m_nHotKeyID_Reports,  MOD_SHIFT|MOD_CONTROL, VK_F2);
		RegisterHotKey(GetSafeHwnd(), m_nHotKeyID_Forms,    MOD_SHIFT|MOD_CONTROL, VK_F3);
		RegisterHotKey(GetSafeHwnd(), m_nHotKeyID_Techs,    MOD_SHIFT|MOD_CONTROL, VK_F4);
		RegisterHotKey(GetSafeHwnd(), m_nHotKeyID_Comps,    MOD_SHIFT|MOD_CONTROL, VK_F5);
		RegisterHotKey(GetSafeHwnd(), m_nHotKeyID_Profiles, MOD_SHIFT|MOD_CONTROL, VK_F6);
		RegisterHotKey(GetSafeHwnd(), m_nHotKeyID_Updates,  MOD_SHIFT|MOD_CONTROL, VK_F7);
		RegisterHotKey(GetSafeHwnd(), m_nHotKeyID_App,		 MOD_SHIFT|MOD_CONTROL, 0x41);
	}

	CAppData::UpdateDisplayedVersion ();

	CAppData::LoadWindowStates ();

	//CAppData::SetToolbarState (m_cWizardButton, false, IDB_TOOLBARWIZARD0, IDB_TOOLBARWIZARD1);
	CAppData::SetToolbarState (m_cOrderButton, CAppData::m_cOrderWnd.m_cWindowState.m_bVisible, IDB_TOOLBARORDERS0, IDB_TOOLBARORDERS1);
	CAppData::SetToolbarState (m_cFormButton, CAppData::m_cItemCreationWnd.m_cWindowState.m_bVisible, IDB_TOOLBARFORM0, IDB_TOOLBARFORM1);
	CAppData::SetToolbarState (m_cTechButton, CAppData::m_cTechSelectionWnd.m_cWindowState.m_bVisible, IDB_TOOLBARTECH0, IDB_TOOLBARTECH1);
	CAppData::SetToolbarState (m_cCompButton, CAppData::m_cComponentWnd.m_cWindowState.m_bVisible, IDB_TOOLBARCOMP0, IDB_TOOLBARCOMP1);
	CAppData::SetToolbarState (m_cReportButton, CAppData::m_cReportWnd.m_cWindowState.m_bVisible, IDB_TOOLBARREPORT0, IDB_TOOLBARREPORT1);
	CAppData::SetToolbarState (m_cProfileButton, false, IDB_TOOLBARPROFILE0, IDB_TOOLBARPROFILE1);
	CAppData::SetToolbarState (m_cUpdateButton, false, IDB_TOOLBARUPDATES0, IDB_TOOLBARUPDATES1);
	//CAppData::SetToolbarState (m_cCrafterSearch, false, IDB_TOOLBARSEARCH0, IDB_TOOLBARSEARCH1);
	//CAppData::SetToolbarState (m_cSubmitOrder, false, IDB_TOOLBARSUBMIT0, IDB_TOOLBARSUBMIT1);

	//StickButtonBelow (m_cWizardButton, m_cOrderButton);
	StickButtonBelow (m_cOrderButton, m_cReportButton);

	StickButtonBelow (m_cFormButton, m_cTechButton);
	StickButtonBelow (m_cTechButton, m_cCompButton);
	StickButtonBelow (m_cCompButton, m_cProfileButton);

	//StickButtonBelow (m_cSubmitOrder, m_cUpdateButton);
	//StickButtonBelow (m_cCrafterSearch, m_cUpdateButton);

	m_cOrderButton.SetTooltipText ("Toggles the display of items associated with this order (F1)");
	m_cReportButton.SetTooltipText ("Toggles the Report screen (F2)");
	m_cFormButton.SetTooltipText ("Toggles the Formulae database (F3)");
	m_cTechButton.SetTooltipText ("Toggles the Technique database (F4)");
	m_cCompButton.SetTooltipText ("Toggles the Component database (F5)");
	m_cProfileButton.SetTooltipText ("Toggles the Profile Manager (F6)");
	m_cUpdateButton.SetTooltipText ("Performs a Live Update on the database (F7)");

	if (CAppData::m_bAutoDock)
	{
		m_cAutoDock.SetCheck (1);
	}
	else
	{
		m_cAutoDock.SetCheck (0);
	}
	OnAutodock();

	CMenu *l_pMenu;
	l_pMenu = GetMenu ();
	if (l_pMenu)
	{
		CAppData::SetMenuItem(l_pMenu, ID_WINDOW_ALWAYSONTOP, m_cWindowState.m_bOnTop);
	}



	if (WinVersion.GetMajorVersion() >= 6)
	{
	    //AfxMessageBox (WinVersion.GetWinVersionString(), MB_ICONINFORMATION);
		l_pMenu->ModifyMenu(2,MF_BYPOSITION|MF_STRING, 2, "?");
		//this->ModifyStyle(WS_MINIMIZEBOX, WS_POPUP);
	}

	//this->ModifyStyle(WS_SYSMENU, WS_CAPTION | WS_POPUP | WS_MINIMIZEBOX);
	//this->ModifyStyle(WS_MINIMIZEBOX, WS_POPUP);
	//ShowWindow(SW_MAXIMIZE);


	this->GetWindowRect (m_cOrigWnd);
	this->GetClientRect (m_cOrigClientWnd);
	ArrangeToolBar();

	UpdateToolBarMenu();

	ShowWindow(SW_SHOW);

	if (CAppData::m_bAutoUpdateQuery)
	{
		int nResult = AfxMessageBox ("Would you like HCC to check automatically if there is a more recent version available?\n\nYou can change this setting in the configuration screen.", MB_ICONQUESTION|MB_YESNOCANCEL);

		if (nResult == IDYES)
		{
			CAppData::m_bAutoUpdate = true;
			CAppData::m_bAutoUpdateQuery = false;
		}
		else if (nResult == IDNO)
		{
			CAppData::m_bAutoUpdate = false;
			CAppData::m_bAutoUpdateQuery = false;
		}
		else
		{
			CAppData::m_bAutoUpdate = false;
			CAppData::m_bAutoUpdateQuery = true;
		}
	}


	if (CAppData::m_bAutoUpdate)
	{
		;
		hInternetSession = InternetOpen("HCC/" + cAppData_Version, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, INTERNET_FLAG_ASYNC);
		if (hInternetSession != NULL)
        {
            InternetSetStatusCallback(hInternetSession, (INTERNET_STATUS_CALLBACK)InternetCallbackFunction);
            hURL = InternetOpenUrl(hInternetSession, CHCCDlg::ReadConfigFile() + "?client=" + cAppData_Version + "&database=" + CAppData::m_csDatabaseRevision, NULL, 0, INTERNET_FLAG_RELOAD | INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_NO_CACHE_WRITE, (unsigned long)(&request_context));

        }
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

CHCCDlg::StickButtonBelow(CWnd &a_cTopWnd, CWnd &a_cWnd)
{
	CRect l_cRect;
	a_cTopWnd.GetWindowRect (l_cRect);
	this->ScreenToClient (l_cRect);
	a_cWnd.SetWindowPos (0, l_cRect.left, l_cRect.bottom - 2, 0, 0, SWP_NOSIZE);
}

CHCCDlg::DockWndToBar(CWnd &a_cWnd)
{
	CRect l_cBarRect;
	CRect l_cWndRect;
	CRect l_cSnapRect;
	SystemParametersInfo (SPI_GETWORKAREA, 0, &l_cWndRect, 0);

	this->GetWindowRect (l_cBarRect);
	if (CAppData::m_bVerticalToolBar)
	{
		l_cSnapRect.left = l_cBarRect.right;
		l_cSnapRect.top = l_cBarRect.top;
	}
	else
	{
		l_cSnapRect.left = l_cBarRect.left;
		l_cSnapRect.top = l_cBarRect.bottom;
	}

	a_cWnd.SetWindowPos (0, l_cSnapRect.left, l_cSnapRect.top, 0, 0, SWP_NOSIZE);
	m_cpDockWnd = &a_cWnd;

	if (CAppData::m_cOrderWnd.m_cWindowState.m_bVisible)
	{
		CAppData::SetOrderWindow(&a_cWnd == &CAppData::m_cOrderWnd);
	}

	if (CAppData::m_cItemCreationWnd.m_cWindowState.m_bVisible)
	{
		CAppData::SetItemWindow(&a_cWnd == &CAppData::m_cItemCreationWnd);
	}

	if (CAppData::m_cTechSelectionWnd.m_cWindowState.m_bVisible)
	{
		CAppData::SetTechWindow(&a_cWnd == &CAppData::m_cTechSelectionWnd);
	}

	if (CAppData::m_cComponentWnd.m_cWindowState.m_bVisible)
	{
		CAppData::SetComponentWindow(&a_cWnd == &CAppData::m_cComponentWnd);
	}

	if (CAppData::m_cReportWnd.m_cWindowState.m_bVisible)
	{
		CAppData::SetReportWindow(&a_cWnd == &CAppData::m_cReportWnd);
	}

	if (CAppData::m_cProfileWnd.m_cWindowState.m_bVisible)
	{
		CAppData::SetProfileWindow(&a_cWnd == &CAppData::m_cProfileWnd);
	}

	if (l_cWndRect.Width () > 800)
	{
		if ((CAppData::m_cTechSelectionWnd.m_cWindowState.m_bLoaded) && (CAppData::m_cItemCreationWnd.m_cWindowState.m_bLoaded))
		{
			CAppData::SetTechWindow((&a_cWnd == &CAppData::m_cTechSelectionWnd) ||
											(&a_cWnd == &CAppData::m_cItemCreationWnd));

			if ((CAppData::m_cItemCreationWnd.m_cWindowState.m_bVisible) &&
				 (CAppData::m_cTechSelectionWnd.m_cWindowState.m_bVisible))
			{
				CAppData::m_cItemCreationWnd.GetWindowRect (l_cBarRect);
				CAppData::m_cTechSelectionWnd.SetWindowPos (0, l_cBarRect.right, l_cBarRect.top, 0, 0, SWP_NOSIZE);
			}
		}

		if ((CAppData::m_cReportWnd.m_cWindowState.m_bLoaded) && (CAppData::m_cOrderWnd.m_cWindowState.m_bLoaded))
		{
			CAppData::SetReportWindow((&a_cWnd == &CAppData::m_cReportWnd)||
											  (&a_cWnd == &CAppData::m_cOrderWnd));

			if ((CAppData::m_cOrderWnd.m_cWindowState.m_bVisible) &&
				 (CAppData::m_cReportWnd.m_cWindowState.m_bVisible))
			{
				CAppData::m_cOrderWnd.GetWindowRect (l_cBarRect);
				CAppData::m_cReportWnd.SetWindowPos (0, l_cBarRect.right, l_cBarRect.top, 0, 0, SWP_NOSIZE);
			}
		}
	}
}

void CHCCDlg::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);

	bool l_bMoved = false;

	CRect l_cBarRect;
	CRect l_cSnapRect;

	this->GetWindowRect (l_cBarRect);
	if (CAppData::m_bVerticalToolBar)
	{
		l_cSnapRect.left = l_cBarRect.right;
		l_cSnapRect.top = l_cBarRect.top;
	}
	else
	{
		l_cSnapRect.left = l_cBarRect.left;
		l_cSnapRect.top = l_cBarRect.bottom;
	}

	if (m_cpDockWnd)
	{
		m_cpDockWnd->SetWindowPos (0, l_cSnapRect.left, l_cSnapRect.top, 0, 0, SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE);

		if ((CAppData::m_cItemCreationWnd.m_cWindowState.m_bVisible) &&
			 (CAppData::m_cTechSelectionWnd.m_cWindowState.m_bVisible))
		{
			CAppData::m_cItemCreationWnd.GetWindowRect (l_cBarRect);
			CAppData::m_cTechSelectionWnd.SetWindowPos (0, l_cBarRect.right, l_cBarRect.top, 0, 0, SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE);
		}

		if ((CAppData::m_cOrderWnd.m_cWindowState.m_bVisible) &&
			 (CAppData::m_cReportWnd.m_cWindowState.m_bVisible))
		{
			CAppData::m_cOrderWnd.GetWindowRect (l_cBarRect);
			CAppData::m_cReportWnd.SetWindowPos (0, l_cBarRect.right, l_cBarRect.top, 0, 0, SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE);
		}
	}
}

void CHCCDlg::OnSize(UINT nType, int cx, int cy)
{
		CDialog::OnSize(nType, cx, cy);


		if (nType == SIZE_RESTORED)
		{
			CAppData::RestoreApp();
		}
		else if (nType == SIZE_MINIMIZED)
		{
			CAppData::MinimiseApp();
		}

}

void CHCCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		if ((nID & 0xFFF0) == SC_MOVE)
		{
			//if (!l_bRestored)
			{
				l_bRestored = true;

				CAppData::RestoreApp();
			}
		}
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHCCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
/*HCURSOR CHCCDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}*/

//////////////////////////////////////////////////////////
// Handle Menu Items here
//////////////////////////////////////////////////////////

void CHCCDlg::OnViewItems()
{
	OnFormbutton() ;
}

void CHCCDlg::OnViewTechniques()
{
	OnTechbutton() ;
}

void CHCCDlg::OnViewComponents()
{
	OnCompbutton();
}

void CHCCDlg::OnViewReports()
{
	OnReportbutton();
}

void CHCCDlg::OnSettingsOrderwindowSnapshotwindow()
{
	CAppData::SetOrderWindowState ();
}

void CHCCDlg::OnSettingsOrderwindowRestoredefaults()
{
	CAppData::GetOrderWindowState ();
}

void CHCCDlg::OnSettingsAllwindowsSnapshotwindows()
{
	CAppData::SaveWindowStates ();
}

void CHCCDlg::OnSettingsAllwindowsRestorealldefaults()
{
	CAppData::LoadWindowStates ();
}

void CHCCDlg::OnSettingsOptions()
{
	COptionsDialog l_cOptionsDialog;
	l_cOptionsDialog.DoModal ();
}

//////////////////////////////////////////////////////////

void CHCCDlg::OnOrderbutton()
{
	CAppData::SetOrderWindow(!CAppData::m_cOrderWnd.m_cWindowState.m_bVisible);

	if ((m_cAutoDock.GetCheck () > 0) && (CAppData::m_cOrderWnd.m_cWindowState.m_bVisible))
	{
		DockWndToBar (CAppData::m_cOrderWnd);
	}
	else if ((m_cAutoDock.GetCheck () > 0) && (CAppData::m_cReportWnd.m_cWindowState.m_bVisible))
	{
		DockWndToBar (CAppData::m_cReportWnd);
	}

}

void CHCCDlg::OnFormbutton()
{
	CAppData::SetItemWindow(!CAppData::m_cItemCreationWnd.m_cWindowState.m_bVisible);

	if ((m_cAutoDock.GetCheck () > 0) && (CAppData::m_cItemCreationWnd.m_cWindowState.m_bVisible))
	{
		DockWndToBar (CAppData::m_cItemCreationWnd);
	}
	else if ((m_cAutoDock.GetCheck () > 0) && (CAppData::m_cTechSelectionWnd.m_cWindowState.m_bVisible))
	{
		DockWndToBar (CAppData::m_cTechSelectionWnd);
	}

}

void CHCCDlg::OnTechbutton()
{
	CAppData::SetTechWindow(!CAppData::m_cTechSelectionWnd.m_cWindowState.m_bVisible);

	if ((m_cAutoDock.GetCheck () > 0) && (CAppData::m_cTechSelectionWnd.m_cWindowState.m_bVisible))
	{
		DockWndToBar (CAppData::m_cTechSelectionWnd);
	}
}


void CHCCDlg::OnCraftersearch()
{
	//CAppData::SetToolbarState (m_cCrafterSearch, true, IDB_TOOLBARSEARCH0, IDB_TOOLBARSEARCH1);
	//AfxMessageBox ("This feature is currently still in progress, and will be made available in a future release", MB_ICONEXCLAMATION );
	//CAppData::SetToolbarState (m_cCrafterSearch, false, IDB_TOOLBARSEARCH0, IDB_TOOLBARSEARCH1);

	/*CCrafterSearchDialog l_cCrafterSearchDialog;
	l_cCrafterSearchDialog.DoModal ();*/
}

void CHCCDlg::OnWizardbutton()
{
	//CAppData::SetToolbarState (m_cWizardButton, true, IDB_TOOLBARWIZARD0, IDB_TOOLBARWIZARD1);
	//AfxMessageBox ("This feature is currently still in progress, and will be made available in a future release", MB_ICONEXCLAMATION );
	//CAppData::SetToolbarState (m_cWizardButton, false, IDB_TOOLBARWIZARD0, IDB_TOOLBARWIZARD1);

	CWizardPage1 l_cWizardPage1;
	CWizardPage2 l_cWizardPage2;
	CWizardPage3 l_cWizardPage3;
	CWizardDialog l_cWizardDialog(IDD_WIZARDPAGE1);


	l_cWizardPage1.m_cpWizardDialog  = &l_cWizardDialog;
	l_cWizardPage2.m_cpWizardDialog  = &l_cWizardDialog;
	l_cWizardPage2.m_cpWizardDialog1 = &l_cWizardPage1;
	l_cWizardPage3.m_cpWizardDialog1 = &l_cWizardPage1;
	l_cWizardPage3.m_cpWizardDialog  = &l_cWizardDialog;
	l_cWizardDialog.AddPage (&l_cWizardPage1);
	l_cWizardDialog.AddPage (&l_cWizardPage2);
	l_cWizardDialog.AddPage (&l_cWizardPage3);
	//l_cWizardDialog.SetWizardMode( );
	//l_cWizardDialog.SetWizardButtons(0 );
	l_cWizardDialog.DoModal ();

}

void CHCCDlg::OnCompbutton()
{
	CAppData::SetComponentWindow (!CAppData::m_cComponentWnd.m_cWindowState.m_bVisible);

	if ((m_cAutoDock.GetCheck () > 0) && (CAppData::m_cComponentWnd.m_cWindowState.m_bVisible))
	{
		DockWndToBar (CAppData::m_cComponentWnd);
	}
}

void CHCCDlg::OnReportbutton()
{
	CAppData::SetReportWindow (!CAppData::m_cReportWnd.m_cWindowState.m_bVisible);

	if ((m_cAutoDock.GetCheck () > 0) && (CAppData::m_cReportWnd.m_cWindowState.m_bVisible))
	{
		DockWndToBar (CAppData::m_cReportWnd);
	}
}

void CHCCDlg::OnProfilebutton()
{
	CAppData::SetProfileWindow (!CAppData::m_cProfileWnd.m_cWindowState.m_bVisible);

	if ((m_cAutoDock.GetCheck () > 0) && (CAppData::m_cProfileWnd.m_cWindowState.m_bVisible))
	{
		DockWndToBar (CAppData::m_cProfileWnd);
	}
}

void CHCCDlg::OnUpdatebutton()
{
	if (CAppData::m_bUpdateWindowOpen == false)
	{
		CAppData::m_bUpdateWindowOpen = true;
		CAppData::SetToolbarState (m_cUpdateButton, true, IDB_TOOLBARUPDATES0, IDB_TOOLBARUPDATES1);
		CUpdateDialog l_cUpdateDialog;
		l_cUpdateDialog.DoModal ();
		CAppData::SetToolbarState (m_cUpdateButton, false, IDB_TOOLBARUPDATES0, IDB_TOOLBARUPDATES1);
		CAppData::m_bUpdateWindowOpen = false;
	}
}

//////////////////////////////////////////////////////////

void CHCCDlg::OnClose()
{
	CAppData::Shutdown ();
	CDialog::OnCancel();
}

int CHCCDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

BOOL CHCCDlg::PreCreateWindow(CREATESTRUCT& cs)
{
	return (CDialog::PreCreateWindow (cs));
}

BOOL CHCCDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	return CDialog::OnNotify(wParam, lParam, pResult);
}

void CHCCDlg::OnOK()
{
}

void CHCCDlg::OnCancel()
{
}

void CHCCDlg::OnSettingsReloaddata()
{
	CString l_csMsg;

	l_csMsg =  "Recaching of the database should be done if you've manually updated the database,\n";
	l_csMsg += "or the database is corrupt, or if icons appear incorrectly. There is no danger in\n";
	l_csMsg += "performing a recache, just that it may take some time.\n\n";
	l_csMsg += "Do you really want to reload all configuration data (This will clear the current order)?";
	if (AfxMessageBox (l_csMsg, MB_ICONQUESTION|MB_YESNO) == IDYES)
	{
		CString l_csCacheConfigPath = CAppData::m_csAppBasePath + cPath_App_Cache + cFile_App_ConfigCache;
		CString l_csCacheFormIconPath = CAppData::m_csAppBasePath + cPath_App_Cache + cFile_App_IconCache;

		DeleteFile (l_csCacheConfigPath);
		DeleteFile (l_csCacheFormIconPath);

		BeginWaitCursor();
		CAppData::SaveDefaults();
		CAppData::Reinitialise ();
		EndWaitCursor( );
	}
}

void CHCCDlg::OnHelpIndex()
{
	CAppData::LaunchWebLink ((CString) "officialsite");
}

void CHCCDlg::OnSettingsFormulawindowSnapshotwindow()
{
	CAppData::SetFormulaWindowState ();
}

void CHCCDlg::OnSettingsFormulawindowRestoredefaults()
{
	CAppData::GetFormulaWindowState ();
}

void CHCCDlg::OnSettingsTechniquewindowSnapshotwindow()
{
	CAppData::SetTechWindowState ();
}

void CHCCDlg::OnSettingsTechniquewindowRestoredefaults()
{
	CAppData::GetTechWindowState ();
}

void CHCCDlg::OnSettingsCompwindowSnapshotwindow()
{
	CAppData::SetCompWindowState ();
}

void CHCCDlg::OnSettingsCompwindowRestoredefaults()
{
	CAppData::GetCompWindowState ();
}

void CHCCDlg::OnSettingsReportwindowSnapshotwindow()
{
	CAppData::SetReportWindowState ();
}

void CHCCDlg::OnSettingsReportwindowRestoredefaults()
{
	CAppData::GetReportWindowState ();
}

void CHCCDlg::OnSettingsProfilewindowSnapshotwindow()
{
	CAppData::SetProfileWindowState ();
}

void CHCCDlg::OnSettingsProfilewindowRestoredefaults()
{
	CAppData::GetProfileWindowState ();
}

void CHCCDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	CAppData::GetMainWindowState ();

}

void CHCCDlg::OnSettingsViewOrderwindow()
{
	CAppData::SetOrderWindow(true);
	CAppData::m_cOrderWnd.SetFocus ();
}

void CHCCDlg::OnViewFormulawindow()
{
	CAppData::SetItemWindow(true);
	CAppData::m_cItemCreationWnd.SetFocus ();
}

void CHCCDlg::OnViewTechniquewindow()
{
	CAppData::SetTechWindow(true);
	CAppData::m_cTechSelectionWnd.SetFocus ();
}

void CHCCDlg::OnViewComponentwindow()
{
	CAppData::SetComponentWindow(true);
	CAppData::m_cComponentWnd.SetFocus ();
}

void CHCCDlg::OnViewReportwindow()
{
	CAppData::SetReportWindow(true);
	CAppData::m_cReportWnd.SetFocus ();
	CAppData::m_cReportWnd.GenerateDirectReport ();
}

void CHCCDlg::OnViewProfilewindow()
{
	CAppData::SetProfileWindow(true);
	CAppData::m_cProfileWnd.SetFocus ();
}

void CHCCDlg::OnSettingsWindowToolbarwindowSnapshotwindow()
{
	CAppData::SetMainWindowState ();
}

void CHCCDlg::OnSettingsToolbarwindowRestoredefaults()
{
	CAppData::GetMainWindowState ();
}





void CHCCDlg::OnAutodock()
{
	if (m_cAutoDock.GetCheck () == 0)
	{
		bool l_bOrderWndVisible = CAppData::m_cOrderWnd.m_cWindowState.m_bVisible;
		bool l_bFormWndVisible = CAppData::m_cItemCreationWnd.m_cWindowState.m_bVisible;
		bool l_bTechWndVisible = CAppData::m_cTechSelectionWnd.m_cWindowState.m_bVisible;
		bool l_bCompWndVisible = CAppData::m_cComponentWnd.m_cWindowState.m_bVisible;
		bool l_bProfileWndVisible = CAppData::m_cProfileWnd.m_cWindowState.m_bVisible;
		bool l_bReportWndVisible = CAppData::m_cReportWnd.m_cWindowState.m_bVisible;

		CAppData::m_bAutoDock = false;
		m_cpDockWnd = NULL;
		CAppData::GetOrderWindowState ();
		CAppData::GetFormulaWindowState ();
		CAppData::GetTechWindowState ();
		CAppData::GetCompWindowState();
		CAppData::GetReportWindowState();
		CAppData::GetProfileWindowState();

		CAppData::SetOrderWindow(l_bOrderWndVisible);
		CAppData::SetItemWindow(l_bFormWndVisible);
		CAppData::SetTechWindow(l_bTechWndVisible);
		CAppData::SetComponentWindow(l_bCompWndVisible);
		CAppData::SetReportWindow(l_bReportWndVisible);
		CAppData::SetProfileWindow(l_bProfileWndVisible);
	}
	else
	{
		CAppData::m_bAutoDock = true;
		if (CAppData::m_cItemCreationWnd.m_cWindowState.m_bVisible)
		{
			DockWndToBar (CAppData::m_cItemCreationWnd);
		}
		else if (CAppData::m_cTechSelectionWnd.m_cWindowState.m_bVisible)
		{
			DockWndToBar (CAppData::m_cTechSelectionWnd);
		}
		else if (CAppData::m_cOrderWnd.m_cWindowState.m_bVisible)
		{
			DockWndToBar (CAppData::m_cOrderWnd);
		}
		else if (CAppData::m_cReportWnd.m_cWindowState.m_bVisible)
		{
			DockWndToBar (CAppData::m_cReportWnd);
		}
		else if (CAppData::m_cComponentWnd.m_cWindowState.m_bVisible)
		{
			DockWndToBar (CAppData::m_cComponentWnd);
		}
		else if (CAppData::m_cProfileWnd.m_cWindowState.m_bVisible)
		{
			DockWndToBar (CAppData::m_cProfileWnd);
		}
	}
}

void CHCCDlg::OnWindowAlwaysontop()
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

void CHCCDlg::OnFileNew()
{
	if (CAppData::m_clOrderList.GetCount () > 0)
	{
		if (AfxMessageBox ("Do you really want to clear this order?", MB_YESNO) == IDYES)
		{
			CAppData::m_clOrderList.RemoveAll ();
			CAppData::m_cOrderGroups.RemoveAll ();

			CAppData::m_cmComponentMap.RemoveAll ();
			CAppData::m_csCurrentOrderFilename = "Untitled.xml";
			CAppData::ChangeOrderState (false);
			if (CAppData::m_cOrderWnd.m_cWindowState.m_bLoaded)
			{
				CAppData::m_cOrderWnd.DisplayOrder ();
				CAppData::m_cOrderWnd.DisplayOrderItem (0);
			}

			if (CAppData::m_cItemCreationWnd.m_cWindowState.m_bLoaded)
			{
				CAppData::m_cItemCreationWnd.DisplayItems ();
				CAppData::m_cItemCreationWnd.ResetItemEdit();
			}

			if (CAppData::m_cReportWnd.m_cWindowState.m_bLoaded)
			{
				CAppData::m_cReportWnd.GenerateDirectReport ();
			}

		}
	}
	else
	{
		CAppData::m_clOrderList.RemoveAll ();
		CAppData::m_cOrderGroups.RemoveAll ();

		if (CAppData::m_cOrderWnd.m_cWindowState.m_bLoaded)
		{
			CAppData::m_cOrderWnd.DisplayOrder ();
		}

		if (CAppData::m_cItemCreationWnd.m_cWindowState.m_bLoaded)
		{
			CAppData::m_cItemCreationWnd.DisplayItems ();
		}
	}
}

void CHCCDlg::OnFileOpen()
{
	CFileDialog LoadDlg (true, ".xml", NULL, NULL, "XML Files (*.xml)|*.xml||", NULL);

	LoadDlg.m_ofn.lpstrInitialDir = CAppData::m_csOrderDir;
	LoadDlg.m_ofn.Flags = OFN_HIDEREADONLY;

	if (LoadDlg.DoModal () == IDOK)
	{
		if (CAppData::LoadOrder (LoadDlg.GetPathName ()) == false)
		{
			AfxMessageBox ("Sorry, HCC doesn't support this version of the order file", MB_ICONSTOP);
		}

		{
			if (CAppData::m_cOrderWnd.m_cWindowState.m_bLoaded)
			{
				CAppData::m_cOrderWnd.DisplayOrder ();
				CAppData::m_cOrderWnd.DisplayOrderItem (0);
			}

			if (CAppData::m_cItemCreationWnd.m_cWindowState.m_bLoaded)
			{
				CAppData::m_cItemCreationWnd.DisplayItems ();
				CAppData::m_cItemCreationWnd.ResetItemEdit();
			}

			if (CAppData::m_cReportWnd.m_cWindowState.m_bLoaded)
			{
				CAppData::m_cReportWnd.GenerateDirectReport ();
			}
		}
	}
}

void CHCCDlg::OnFileSave()
{
	if ((CAppData::m_csCurrentOrderFilename.IsEmpty ()) ||
		 (CAppData::m_csCurrentOrderFilename == "Untitled.xml"))
	{
		CFileDialog SaveDlg (false, ".xml", NULL, OFN_OVERWRITEPROMPT, "XML Files (*.xml)|*.xml||", NULL);

		SaveDlg.m_ofn.lpstrInitialDir = CAppData::m_csOrderDir;

		if (SaveDlg.DoModal () == IDOK)
		{
			CAppData::SaveOrder (SaveDlg.GetPathName ());

			if (CAppData::m_cOrderWnd.m_cWindowState.m_bLoaded)
			{
				CAppData::m_cOrderWnd.DisplayOrderTitle ();
			}
		}
	}
	else
	{
		CAppData::SaveOrder (CAppData::m_csCurrentOrderFilename);

		if (CAppData::m_cOrderWnd.m_cWindowState.m_bLoaded)
		{
			CAppData::m_cOrderWnd.DisplayOrderTitle ();
		}
	}
}

void CHCCDlg::OnFileSaveas()
{
	CFileDialog SaveDlg (false, ".xml", NULL, OFN_OVERWRITEPROMPT, "XML Files (*.xml)|*.xml||", NULL);

	SaveDlg.m_ofn.lpstrInitialDir = CAppData::m_csOrderDir;

	if (SaveDlg.DoModal () == IDOK)
	{
		CAppData::SaveOrder (SaveDlg.GetPathName ());

		if (CAppData::m_cOrderWnd.m_cWindowState.m_bLoaded)
		{
			CAppData::m_cOrderWnd.DisplayOrderTitle ();
		}
	}
}

void CHCCDlg::OnFileExit()
{
	OnClose ();

}

void CHCCDlg::OnFilePrint()
{
	CAppData::SetReportWindow(true);
	CAppData::m_cReportWnd.SetFocus ();
	CAppData::m_cReportWnd.GenerateDirectReport ();
}

void CHCCDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonUp(nFlags, point);
}

void CHCCDlg::OnKillFocus(CWnd* pNewWnd)
{
	CDialog::OnKillFocus(pNewWnd);


}

void CHCCDlg::OnCaptureChanged(CWnd *pWnd)
{
	//l_bRestored = false;

	CDialog::OnCaptureChanged(pWnd);
}

void CHCCDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnChar(nChar, nRepCnt, nFlags);
}

void CHCCDlg::OnWindowPosChanging( WINDOWPOS* lpwndpos )
{
	CRect l_cRect;
	CRect l_cWndRect;
	this->GetWindowRect (l_cRect);
	int dx;
	int dy;

	if (lpwndpos->flags & SWP_NOMOVE)
	{
	}
	else
	{
		m_cWindowState.SnapToWnd (lpwndpos, &l_cRect, NULL, CAppData::m_iStickyStrength);

		if (!m_cpDockWnd)
		{
			if (!CAppData::m_bDragWithToolBar)
			{
				if (CAppData::m_cItemCreationWnd.m_cWindowState.m_bVisible)
				{
					m_cWindowState.SnapToWnd (lpwndpos, &l_cRect, &CAppData::m_cItemCreationWnd, 18);
				}

				if (CAppData::m_cOrderWnd.m_cWindowState.m_bVisible)
				{
					m_cWindowState.SnapToWnd (lpwndpos, &l_cRect, &CAppData::m_cOrderWnd, 18);
				}

				if (CAppData::m_cTechSelectionWnd.m_cWindowState.m_bVisible)
				{
					m_cWindowState.SnapToWnd (lpwndpos, &l_cRect, &CAppData::m_cTechSelectionWnd, 18);
				}

				if (CAppData::m_cComponentWnd.m_cWindowState.m_bVisible)
				{
					m_cWindowState.SnapToWnd (lpwndpos, &l_cRect, &CAppData::m_cComponentWnd, 18);
				}

				if (CAppData::m_cReportWnd.m_cWindowState.m_bVisible)
				{
					m_cWindowState.SnapToWnd (lpwndpos, &l_cRect, &CAppData::m_cReportWnd, 18);
				}

				if (CAppData::m_cProfileWnd.m_cWindowState.m_bVisible)
				{
					m_cWindowState.SnapToWnd (lpwndpos, &l_cRect, &CAppData::m_cProfileWnd, 18);
				}
			}
			else
			{
				this->GetWindowRect (l_cRect);
				this->SetWindowPos (NULL, lpwndpos->x, lpwndpos->y, 0, 0, SWP_NOSIZE|SWP_NOSENDCHANGING );

				if (CAppData::m_cItemCreationWnd.m_cWindowState.m_bVisible)
				{
					CAppData::m_cItemCreationWnd.GetWindowRect (l_cWndRect);
					dx = l_cWndRect.left - l_cRect.left;
					dy = l_cWndRect.top - l_cRect.top;
					CAppData::m_cItemCreationWnd.SetWindowPos (NULL, lpwndpos->x + dx, lpwndpos->y + dy, 0, 0, SWP_NOSIZE|SWP_NOACTIVATE);
				}

				if (CAppData::m_cTechSelectionWnd.m_cWindowState.m_bVisible)
				{
					CAppData::m_cTechSelectionWnd.GetWindowRect (l_cWndRect);
					dx = l_cWndRect.left - l_cRect.left;
					dy = l_cWndRect.top - l_cRect.top;
					CAppData::m_cTechSelectionWnd.SetWindowPos (NULL, lpwndpos->x + dx, lpwndpos->y + dy, 0, 0, SWP_NOSIZE|SWP_NOACTIVATE);
				}

				if (CAppData::m_cOrderWnd.m_cWindowState.m_bVisible)
				{
					CAppData::m_cOrderWnd.GetWindowRect (l_cWndRect);
					dx = l_cWndRect.left - l_cRect.left;
					dy = l_cWndRect.top - l_cRect.top;
					CAppData::m_cOrderWnd.SetWindowPos (NULL, lpwndpos->x + dx, lpwndpos->y + dy, 0, 0, SWP_NOSIZE|SWP_NOACTIVATE);
				}

				if (CAppData::m_cComponentWnd.m_cWindowState.m_bVisible)
				{
					CAppData::m_cComponentWnd.GetWindowRect (l_cWndRect);
					dx = l_cWndRect.left - l_cRect.left;
					dy = l_cWndRect.top - l_cRect.top;
					CAppData::m_cComponentWnd.SetWindowPos (NULL, lpwndpos->x + dx, lpwndpos->y + dy, 0, 0, SWP_NOSIZE|SWP_NOACTIVATE);
				}

				if (CAppData::m_cReportWnd.m_cWindowState.m_bVisible)
				{
					CAppData::m_cReportWnd.GetWindowRect (l_cWndRect);
					dx = l_cWndRect.left - l_cRect.left;
					dy = l_cWndRect.top - l_cRect.top;
					CAppData::m_cReportWnd.SetWindowPos (NULL, lpwndpos->x + dx, lpwndpos->y + dy, 0, 0, SWP_NOSIZE|SWP_NOACTIVATE);
				}

				if (CAppData::m_cProfileWnd.m_cWindowState.m_bVisible)
				{
					CAppData::m_cProfileWnd.GetWindowRect (l_cWndRect);
					dx = l_cWndRect.left - l_cRect.left;
					dy = l_cWndRect.top - l_cRect.top;
					CAppData::m_cProfileWnd.SetWindowPos (NULL, lpwndpos->x + dx, lpwndpos->y + dy, 0, 0, SWP_NOSIZE|SWP_NOACTIVATE);
				}
			}
		}
	}


	CDialog::OnWindowPosChanging(lpwndpos);
}

void CHCCDlg::OnHelpOnelinemanual()
{
	CAppData::LaunchWebLink ((CString) "onlinemanual");
}

void CHCCDlg::OnHelpPlugins()
{
	CAppData::LaunchWebLink ((CString) "plugins");
}

void CHCCDlg::OnHelpReportabug()
{
	CAppData::LaunchWebLink ((CString) "reportbug");
}

BOOL CHCCDlg::OnHelpInfo(HELPINFO* pHelpInfo)
{
	return (TRUE);
}

void CHCCDlg::OnOptionsViewLiveupdate()
{
	OnUpdatebutton() ;
}

void CHCCDlg::OnOptionsSettingsRefreshtheme()
{
	CScheme::LoadHCCScheme (CAppData::m_csAppBasePath + cPath_App_Theme + "\\" + CAppData::m_csCurrentTheme);
	CAppData::ApplyCurrentTheme ();

}

void CHCCDlg::OnOptionsOrientationHorizontal()
{
	CAppData::m_bVerticalToolBar = false;
	ArrangeToolBar();
	UpdateToolBarMenu();
}

CHCCDlg::ArrangeToolBar()
{
	int l_iNonClientWidth = m_cOrigWnd.Width() - m_cOrigClientWnd.Width ();
	int l_iNonClientHeight = m_cOrigWnd.Height() - m_cOrigClientWnd.Height ();

	if (CAppData::m_bVerticalToolBar)
	{
		this->SetWindowPos (NULL, 0, 0, 120 + l_iNonClientWidth, 341 + l_iNonClientHeight, SWP_NOMOVE);
		m_cTitleFrame.ShowWindow (true);
		m_cDatabaseTitle.ShowWindow (true);

		m_cOrdersHeader.SetWindowPos (NULL, 11, 39, 0, 0, SWP_NOSIZE);
		m_cOrderButton.SetWindowPos (NULL, 9, 55, 0, 0, SWP_NOSIZE);
		StickButtonBelow (m_cOrderButton, m_cReportButton);

		m_cDatabaseHeader.SetWindowPos (NULL, 11, 124, 0, 0, SWP_NOSIZE);
		m_cFormButton.SetWindowPos (NULL, 9, 140, 0, 0, SWP_NOSIZE);
		StickButtonBelow (m_cFormButton, m_cTechButton);
		StickButtonBelow (m_cTechButton, m_cCompButton);
		StickButtonBelow (m_cCompButton, m_cProfileButton);

		m_cOnlineHeader.SetWindowPos (NULL, 11, 265, 0, 0, SWP_NOSIZE);
		m_cUpdateButton.SetWindowPos (NULL, 9, 281, 0, 0, SWP_NOSIZE);
		m_cAutoDock.SetWindowPos (NULL, 24, 325, 0, 0, SWP_NOSIZE);
	}
	else
	{
		this->SetWindowPos (NULL, 0, 0, 428 + l_iNonClientWidth, 80 + l_iNonClientHeight, SWP_NOMOVE);
		m_cTitleFrame.ShowWindow (false);
		m_cDatabaseTitle.ShowWindow (false);

		m_cOrdersHeader.SetWindowPos (NULL, 8, 4, 0, 0, SWP_NOSIZE);
		m_cOrderButton.SetWindowPos (NULL, 4, 20, 0, 0, SWP_NOSIZE);
		StickButtonBelow (m_cOrderButton, m_cReportButton);

		m_cDatabaseHeader.SetWindowPos (NULL, 118, 4, 0, 0, SWP_NOSIZE);
		m_cFormButton.SetWindowPos (NULL, 114, 20, 0, 0, SWP_NOSIZE);
		StickButtonBelow (m_cFormButton, m_cTechButton);

		m_cCompButton.SetWindowPos (NULL, 214, 20, 0, 0, SWP_NOSIZE);
		StickButtonBelow (m_cCompButton, m_cProfileButton);

		m_cOnlineHeader.SetWindowPos (NULL, 328, 4, 0, 0, SWP_NOSIZE);
		m_cUpdateButton.SetWindowPos (NULL, 324, 20, 0, 0, SWP_NOSIZE);
		m_cAutoDock.SetWindowPos (NULL, 344, 58, 0, 0, SWP_NOSIZE);
	}

	OnAutodock();
	CAppData::UpdateDisplayedVersion();
}

void CHCCDlg::OnOptionsOrientationVertical()
{
	CAppData::m_bVerticalToolBar = true;
	ArrangeToolBar();
	UpdateToolBarMenu();
}

CHCCDlg::UpdateToolBarMenu()
{
	CMenu *l_pMenu;
	l_pMenu = GetMenu ();
	if (l_pMenu)
	{
		CAppData::SetMenuItem(l_pMenu, ID_OPTIONS_ORIENTATION_HORIZONTAL, !CAppData::m_bVerticalToolBar);
		CAppData::SetMenuItem(l_pMenu, ID_OPTIONS_ORIENTATION_VERTICAL, CAppData::m_bVerticalToolBar);
	}
}

void CHCCDlg::OnHelpAbout()
{
	CAboutDlg l_cAboutDlg;

	l_cAboutDlg.DoModal ();
}


void CHCCDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
    //AfxMessageBox ("meep.", MB_ICONINFORMATION);
    //DefWindowProc(m_hWnd, SC_SYSCOMMAND, SC_MOVE+1,MAKELPARAM(point.x,point.y));
    SendMessage(WM_SYSCOMMAND, SC_MOVE|0x0002);
}

BOOL CAboutDlg::OnInitDialog()
{
	CFormulaSet *l_cpFormulaSet;
	CFormula    *l_cpFormula;
	CTechSet *l_cpTechSet;
	CTech    *l_cpTech;
	POSITION l_SetPos;
	POSITION l_Pos;
	int l_iOffset = 0;
	int l_iCount;
	CString l_csCount;
	CDialog::OnInitDialog();

	m_cTitle.SetWindowText ("HCC v" + cAppData_Version + " (Database Revision: " + CAppData::m_csDatabaseRevision + ")");
	m_cCountList.InsertColumn (0, "Section", LVCFMT_LEFT, 160, -1);
	m_cCountList.InsertColumn (1, "Count", LVCFMT_CENTER, 55, -1);

	l_iCount = 0;
	l_SetPos = CAppData::m_clFormulaSetList.GetHeadPosition ();
	while (l_SetPos)
	{
		l_cpFormulaSet = CAppData::m_clFormulaSetList.GetNext (l_SetPos);

		l_Pos = l_cpFormulaSet->m_clFormulaList.GetHeadPosition ();
		while (l_Pos)
		{
			l_cpFormula = l_cpFormulaSet->m_clFormulaList.GetNext (l_Pos);
			l_iCount += l_cpFormula->m_clFormulaTierList.GetCount ();
		}
	}

	l_csCount.Format ("%d", l_iCount);
	m_cCountList.InsertItem (l_iOffset, "Formula Database");
	m_cCountList.SetItemText (l_iOffset++, 1, l_csCount);

	l_iCount = 0;
	l_SetPos = CAppData::m_clTechSetList.GetHeadPosition ();
	while (l_SetPos)
	{
		l_cpTechSet = CAppData::m_clTechSetList.GetNext (l_SetPos);

		l_Pos = l_cpTechSet->m_clTechList.GetHeadPosition ();
		while (l_Pos)
		{
			l_cpTech = l_cpTechSet->m_clTechList.GetNext (l_Pos);
			l_iCount += l_cpTech->m_clTechTierList.GetCount ();
		}
	}

	l_csCount.Format ("%d", l_iCount);
	m_cCountList.InsertItem (l_iOffset, "Technique Database");
	m_cCountList.SetItemText (l_iOffset++, 1, l_csCount);

	l_csCount.Format ("%d", CAppData::m_clComponentList.GetCount ());
	m_cCountList.InsertItem (l_iOffset, "Component Database");
	m_cCountList.SetItemText (l_iOffset++, 1, l_csCount);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



