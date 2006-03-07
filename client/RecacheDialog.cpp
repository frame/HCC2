// RecacheDialog.cpp : implementation file
//

#include "stdafx.h"
#include "HCC.h"
#include "RecacheDialog.h"
#include "AppData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecacheDialog dialog


CRecacheDialog::CRecacheDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CRecacheDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRecacheDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CRecacheDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRecacheDialog)
	DDX_Control(pDX, IDC_STATUSPROGRESSTOTAL, m_cStatusProgress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRecacheDialog, CDialog)
	//{{AFX_MSG_MAP(CRecacheDialog)
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecacheDialog message handlers

BOOL CRecacheDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_bInProgress = false;	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CRecacheDialog::Recache(bool a_bQuiet)
{
	CString l_csCachePath = CAppData::m_csAppBasePath + cPath_App_Cache;
	CAppData::ClearCache (true);

	if (!a_bQuiet)
	{
		CAppData::m_cpCacheProgress = &m_cStatusProgress;
		CAppData::m_iCacheCount = CalculateFilesToCache (CAppData::m_csAppBasePath + cPath_App_Formulas);
		CAppData::m_iCacheCount += CalculateFilesToCache (CAppData::m_csAppBasePath + cPath_App_Techs);
		CAppData::m_iCacheCount += CalculateFilesToCache (CAppData::m_csAppBasePath + cPath_App_Wizards);

		m_cStatusProgress.SetRange32 (0, CAppData::m_iCacheCount);
		CAppData::m_iCacheCount = 0;
		m_cStatusProgress.SetPos (0);
	}

	CAppData::LoadGameImages (CAppData::m_csGameBasePath, CAppData::m_csAppBasePath);
	CAppData::LoadCategories (CAppData::m_csAppBasePath + cFile_App_Categories);
	CAppData::LoadFormulas (CAppData::m_csAppBasePath + cPath_App_Formulas, CAppData::m_clFormulaSetList);
	CAppData::LoadTechniques (CAppData::m_csAppBasePath + cPath_App_Techs);
	CAppData::LoadComponentFile (CAppData::m_csAppBasePath + cFile_App_ComponentFile);
	CAppData::LoadWizards (CAppData::m_csAppBasePath + cPath_App_Wizards);
	CAppData::LoadTechniqueFile (CAppData::m_csAppBasePath + cFile_App_TechniqueFile);
	CAppData::LoadFormulaFile (CAppData::m_csAppBasePath + cFile_App_FormulaFile);

	if (CAppData::m_bEnableCache)
	{
		CAppData::WriteCache (l_csCachePath);
	}

	if (!a_bQuiet)
	{
		m_cStatusProgress.SetPos (100);
		CAppData::m_cpCacheProgress = NULL;

		KillTimer (m_iTimerId);
		EndDialog (true);
	}
}

void CRecacheDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	if (bShow)
	{
		ULARGE_INTEGER l_iFreeToUser;
		ULARGE_INTEGER l_iFree;
		ULARGE_INTEGER l_iInUse;

		if (GetDiskFreeSpaceEx (CAppData::m_csAppBasePath + cPath_App_Temp, &l_iFreeToUser, &l_iFree, &l_iInUse))
		{
			if (l_iFreeToUser.QuadPart < 12582912)
			{
				AfxMessageBox ("There is not enough space on the partition (where HCC is installed) to recache the database.\nPlease free up some space (at least 12Mb) and retry", MB_ICONSTOP);

				EndDialog (true);
			}
		}

		m_iTimerId = SetTimer (1, 100,  NULL);
	}
}

void CRecacheDialog::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == 1)
	{
		if (!m_bInProgress)
		{
			m_bInProgress = false;
			Recache (false);
		}
	}

	CDialog::OnTimer(nIDEvent);
}

int CRecacheDialog::CalculateFilesToCache(CString &a_csPath)
{
	CFileFind l_cFileFind;
	bool l_bSearching;
	int l_iCount = 0;

	l_bSearching = (l_cFileFind.FindFile (a_csPath + "\\*.*") != 0);
	while (l_bSearching)
	{
		l_bSearching = (l_cFileFind.FindNextFile () != 0);

		if (l_cFileFind.IsDirectory ())
		{
			if (l_cFileFind.IsDots () == false)
			{
				l_iCount += CalculateFilesToCache (l_cFileFind.GetFilePath ());
			}
		}
		else
		{
			// Search for xml files
			if (l_cFileFind.GetFileName().Find (".xml") >= 0)
			{
				l_iCount++;
			}
		}
		
	}

	l_cFileFind.Close ();

	return (l_iCount);
}


BOOL CRecacheDialog::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	return (TRUE);
}
