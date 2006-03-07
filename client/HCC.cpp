// HCC.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "HCC.h"
#include "HCCDlg.h"
#include "AppData.h"
#include "RegistryAccess.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace Gdiplus;

HWND    ghDlg = 0;          // Handle to main dialog box.
HACCEL  ghAccelTable = 0;   // Handle to accelerator table.

/////////////////////////////////////////////////////////////////////////////
// CHCCApp

BEGIN_MESSAGE_MAP(CHCCApp, CWinApp)
	//{{AFX_MSG_MAP(CHCCApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHCCApp construction

CHCCApp::CHCCApp()
{
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CHCCApp object

CHCCApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CHCCApp initialization

BOOL CHCCApp::ProcessMessageFilter(int code, LPMSG lpMsg)
 {
    if (code < 0)
       CWinApp::ProcessMessageFilter(code, lpMsg);

    if (ghDlg && ghAccelTable)
       {
       if (::TranslateAccelerator(ghDlg, ghAccelTable, lpMsg))
          return(TRUE);
       }

   return CWinApp::ProcessMessageFilter(code, lpMsg);
}

BOOL CHCCApp::InitInstance()
{
	CRegistryAccess l_cRegAccess;

	if (!l_cRegAccess.DetectFlexGrid ())
	{
		AfxMessageBox ("HCC requires the registration of MSFlexGrid in order to run.\nThis should have been performed during the install.\nPlease exit HCC and reinstall again");
	}

	{
		AfxEnableControlContainer();

		// Standard initialization
		// If you are not using these features and wish to reduce the size
		//  of your final executable, you should remove from the following
		//  the specific initialization routines you do not need.
	  InitCommonControls();    // initialize common control library
	  CWinApp::InitInstance(); // call parent class method
		ghAccelTable = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_TOOLBARACCEL));
	#ifdef _AFXDLL
		Enable3dControls();			// Call this when using MFC in a shared DLL
	#else
		Enable3dControlsStatic();	// Call this when linking to MFC statically
	#endif
		CHCCDlg dlg;
		m_pMainWnd = &dlg;
		char l_cPath[512];
		int l_iSize = 512;
		CString l_csAppPath;
		CString l_csGamePath;
	
		GdiplusStartupInput gdiplusStartupInput;
		ULONG_PTR gdiplusToken;
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

		GetCurrentDirectory (l_iSize, l_cPath);
		CAppData::m_cpHCCDlg = &dlg;
		l_cRegAccess.LoadKey ("SOFTWARE\\ArtifactEntertainment\\Horizons", "", l_csGamePath);
		l_csAppPath = l_cPath;
		CAppData::m_csAppBasePath = l_csAppPath;
		CAppData::m_csGameBasePath = l_csGamePath;

		CAppData::ReadDefaults ();
		CAppData::UnpackAvailableUpdates ();
		CAppData::LoadData ();

		int nResponse = dlg.DoModal();
		if (nResponse == IDOK)
		{
			//  dismissed with OK
		}
		else if (nResponse == IDCANCEL)
		{
			//  dismissed with Cancel
		}

		GdiplusShutdown(gdiplusToken);

		CAppData::ClearCache (true);
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


void CHCCApp::SetDialogColors(COLORREF a_iFg, COLORREF a_iBg)
{
	SetDialogBkColor(a_iFg, a_iBg);

}

CHCCApp::SetPriority(int Priority)
{
	SetThreadPriority (Priority);
}
