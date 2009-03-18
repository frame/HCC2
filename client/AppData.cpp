// AppData.cpp: implementation of the CAppData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HCC.h"
#include "AppData.h"
#include "RegistryAccess.h"
#include "XMLParser.h"
#include "XMLTag.h"
#include "FileHandler.h"
#include "RecacheDialog.h"
#include "UpdateDialog.h"
#include "Scheme.h"
#include "direct.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CHCCApp				  *CAppData::m_cpHCCApp = NULL;
CHCCDlg				  *CAppData::m_cpHCCDlg = NULL;
COrderDialog			CAppData::m_cOrderWnd;
CItemCreation			CAppData::m_cItemCreationWnd;
CTechniqueSelection	CAppData::m_cTechSelectionWnd;
CComponentDialog		CAppData::m_cComponentWnd;
CSkillLevelDialog		CAppData::m_cSkillLevelWnd;
CReportDialog			CAppData::m_cReportWnd;
CProfileDialog			CAppData::m_cProfileWnd;

CImageStore  *CAppData::m_cpIconImages = NULL;

CTypedPtrList<CPtrList, CFormulaSet*>	CAppData::m_clFormulaSetList;
CList<CString, CString&> CAppData::m_clFormulaCategoryList;

CTypedPtrList <CPtrList, CTechSet*>	CAppData::m_clTechSetList;
CList<CString, CString&> CAppData::m_clTechCategoryList;

CTypedPtrList<CPtrList, CComponent*>	CAppData::m_clComponentList;

CList<COrderItem, COrderItem&>	CAppData::m_clOrderList;
CTypedPtrList<CPtrList, CProfile*>	CAppData::m_clProfileList;
CTypedPtrList<CPtrList, CSchoolWizard*> CAppData::m_clSchoolWizardList;

CTypedPtrList<CPtrList, CCategory*>	CAppData::m_clCategoryList;
CTypedPtrList<CPtrList, CSubCategory*>	CAppData::m_clSubCategoryList;

CFormula *CAppData::m_cpCurrentFormula = NULL;
CString   CAppData::m_csCurrentFormulaTierName = "";
CString   CAppData::m_csPreferedFormulaTierName = "";
int CAppData::m_csPreferedFormulaTier = 1;
CTypedPtrList<CPtrList, CFormulaSet*> CAppData::m_cResourceFormulaSetList;

CTech		*CAppData::m_cpCurrentTech = NULL;
CString   CAppData::m_csCurrentTechTierName = "";
CString   CAppData::m_csPreferedTechTierName = "";

COrderItem CAppData::m_cCurrentOrderItem;
int CAppData::m_iCurrentOrderId = 0;

CProfile *CAppData::m_cpCurrentProfile = NULL;
CProfile *CAppData::m_cpTemplateProfile = NULL;
CMapStringToString CAppData::m_cmHelpLinks;
CMapStringToString CAppData::m_cmComponentMap;

CString	CAppData::m_csCurrentProfile = "";
CString	CAppData::m_csCurrentProfileType = "";
CString	CAppData::m_csOrderDir = "";
CString 	CAppData::m_csProfileDir = "";
CString 	CAppData::m_csTmpDir = "";
CString 	CAppData::m_csLastFormulaCategory = "";
CString 	CAppData::m_csLastTechCategory = "";

CStringList CAppData::m_cOrderGroups;

CString CAppData::m_cFormFilter = cNone_Filter;
CString CAppData::m_cFormClassFilter = cNone_Filter;
CString CAppData::m_cFormClassFilterType = "";
CTech *CAppData::m_cpFormFilterTech = NULL;
bool CAppData::m_bEditMode = false;
bool CAppData::m_bFormSearchMode = false;
bool CAppData::m_bShowUsableTechs = true;
bool CAppData::m_bEnableCache = true;
bool CAppData::m_bEnableIcons = true;
bool CAppData::m_bAutoDock = true;
int  CAppData::m_iShowResourceMode = 0;
int  CAppData::m_iShowReportMode = 0;
int  CAppData::m_iReportType = 0;
int  CAppData::m_iReportFormat = 0;
int  CAppData::m_iShowReportResourceMode = 0;
int  CAppData::m_iShowReportBonusMode = 0;
int  CAppData::m_iItemResourceSize = 0;
int  CAppData::m_iExpandFormulaMode = 1;
int  CAppData::m_iExpandTechMode = 1;
int  CAppData::m_iIconSize = 16;
int  CAppData::m_iStickyStrength = 16;
bool CAppData::m_bGlobalHotkeys = true;
bool CAppData::m_bDragWithToolBar = false;
bool CAppData::m_bVerticalToolBar = true;
bool CAppData::m_bAutoShrink = true;
bool CAppData::m_bHighPriority = false;
bool CAppData::m_bAutoUpdate = false;
bool CAppData::m_bAutoUpdateQuery = true;

CString CAppData::m_csCurrentTheme = "hcctheme_default.xml";
CString CAppData::m_csAppBasePath = "";
CString CAppData::m_csGameBasePath = "";
CString CAppData::m_csCurrentOrderFilename = "Untitled.xml";
bool CAppData::m_bProfilesChanged = false;
CString CAppData::m_csDatabaseRevision = "Initial";
bool CAppData::m_bUpdateWindowOpen = false;

int CAppData::m_iCacheCount;
CProgressCtrl	*CAppData::m_cpCacheProgress = NULL;
COLORREF CAppData::m_iNeutralColour;

CStringList CAppData::m_csEffectList_Info;
CStringList CAppData::m_csEffectList_Bonuses;
CStringList CAppData::m_csEffectList_Requirements;
bool CAppData::m_bOrderChanged = false;
CFont CAppData::m_cTitleFont;
CFont CAppData::m_cTitleSelFont;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAppData::CAppData()
{

}

CAppData::~CAppData()
{

}

//////////////////////////////////////////////////////////////////////
// Window Routines
//////////////////////////////////////////////////////////////////////

int CAppData::SetToolbarState(CButtonST &a_cButton, bool a_bState, int a_iStateOff, int a_iStateOn)
{
	if (a_bState)
	{
		COLORREF l_iHighlight = 0xF8F8F8;
		a_cButton.SetBitmaps (a_iStateOff, 0);
		a_cButton.SetColor (CButtonST::BTNST_COLOR_BK_IN, CScheme::GetColour ("BUTTONCOLOUR_ON"));
		a_cButton.SetColor (CButtonST::BTNST_COLOR_BK_OUT, CScheme::GetColour ("BUTTONCOLOUR_ON"));
		a_cButton.SetColor (CButtonST::BTNST_COLOR_BK_FOCUS, CScheme::GetColour ("BUTTONCOLOUR_ON"));
		a_cButton.OffsetColor (CButtonST::BTNST_COLOR_BK_IN, -15);
		//a_cButton.OffsetColor (CButtonST::BTNST_COLOR_BK_OUT, +10);
	}
	else
	{
		a_cButton.SetBitmaps (a_iStateOn, 0);
		a_cButton.SetColor (CButtonST::BTNST_COLOR_BK_IN, CScheme::GetColour ("BUTTONCOLOUR_OFF"));
		a_cButton.SetColor (CButtonST::BTNST_COLOR_BK_OUT, CScheme::GetColour ("BUTTONCOLOUR_OFF"));
		a_cButton.SetColor (CButtonST::BTNST_COLOR_BK_FOCUS, CScheme::GetColour ("BUTTONCOLOUR_OFF"));
		a_cButton.OffsetColor (CButtonST::BTNST_COLOR_BK_IN, 15);
		//a_cButton.OffsetColor (CButtonST::BTNST_COLOR_BK_OUT, +10);
	}
}

int CAppData::ConvertScreenWidthToGrid(int a_iWidth)
{
	int l_iWidth;
   CDC* pDC = m_cpHCCDlg->GetDC ();
   double m_nLogX = (double) pDC->GetDeviceCaps(LOGPIXELSX);
   //int m_nLogY = pDC->GetDeviceCaps(LOGPIXELSY);

	m_cpHCCDlg->ReleaseDC(pDC);

	double l_fWidth = (double) a_iWidth;
	l_iWidth =  (int) ((l_fWidth * 1440.0f) / m_nLogX);

	if (l_iWidth < 100)
	{
		l_iWidth = 100;
	}

	return (l_iWidth);
}


int CAppData::ConvertGridWidthToScreen(int a_iWidth)
{
	int l_iWidth;
   CDC* pDC = m_cpHCCDlg->GetDC ();
   double m_nLogX = (double) pDC->GetDeviceCaps(LOGPIXELSX);
   //int m_nLogY = pDC->GetDeviceCaps(LOGPIXELSY);

	m_cpHCCDlg->ReleaseDC(pDC);

	double l_fWidth = (double) a_iWidth;
	l_fWidth =  ((l_fWidth * m_nLogX) / 1440.0f) ;
	l_iWidth = (int) l_fWidth;

	return (l_iWidth);
}

int CAppData::LoadWindowStates()
{
	GetMainWindowState ();
	GetOrderWindowState ();
	GetFormulaWindowState ();
	GetTechWindowState ();
	GetCompWindowState();
	GetReportWindowState();
	GetProfileWindowState();
}

int CAppData::SaveWindowStates()
{
	SetMainWindowState ();
	SetOrderWindowState ();
	SetFormulaWindowState ();
	SetTechWindowState ();
	SetCompWindowState();
	SetReportWindowState();
	SetProfileWindowState();

}

bool CAppData::SetOrderWindow(bool l_bOpen)
{
	if (l_bOpen)
	{
		if (m_cOrderWnd.m_cWindowState.m_bLoaded == false)
		{
			m_cOrderWnd.StartUp ();
			m_cOrderWnd.m_cWindowState.setWnd (&m_cOrderWnd);
		}

		m_cOrderWnd.ShowWindow (SW_SHOW);
	}
	else
	{
		m_cOrderWnd.ShowWindow (SW_HIDE);
	}

	m_cOrderWnd.m_cWindowState.m_bVisible = l_bOpen;
	CAppData::SetToolbarState (CAppData::m_cpHCCDlg->m_cOrderButton, l_bOpen, IDB_TOOLBARORDERS0, IDB_TOOLBARORDERS1);

	return (true);
}

bool CAppData::SetItemWindow(bool l_bOpen)
{
	if (l_bOpen)
	{
		if (m_cItemCreationWnd.m_cWindowState.m_bLoaded == false)
		{
			m_cItemCreationWnd.StartUp ();
			m_cItemCreationWnd.m_cWindowState.setWnd (&m_cItemCreationWnd);
		}

		m_cItemCreationWnd.ShowWindow (SW_SHOW);
	}
	else
	{
		m_cItemCreationWnd.ShowWindow (SW_HIDE);
	}

	m_cItemCreationWnd.m_cWindowState.m_bVisible = l_bOpen;
	CAppData::SetToolbarState (CAppData::m_cpHCCDlg->m_cFormButton, l_bOpen, IDB_TOOLBARFORM0, IDB_TOOLBARFORM1);

	return (true);
}

bool CAppData::SetTechWindow(bool l_bOpen)
{
	if (l_bOpen)
	{
		if (m_cTechSelectionWnd.m_cWindowState.m_bLoaded == false)
		{
			m_cTechSelectionWnd.StartUp ();
			m_cTechSelectionWnd.m_cWindowState.setWnd (&m_cTechSelectionWnd);
		}

		m_cTechSelectionWnd.ShowWindow (SW_SHOW);
	}
	else
	{
		m_cTechSelectionWnd.ShowWindow (SW_HIDE);
	}

	m_cTechSelectionWnd.m_cWindowState.m_bVisible = l_bOpen;
	CAppData::SetToolbarState (CAppData::m_cpHCCDlg->m_cTechButton, l_bOpen, IDB_TOOLBARTECH0, IDB_TOOLBARTECH1);

	return (true);
}

bool CAppData::SetComponentWindow(bool l_bOpen)
{
	if (l_bOpen)
	{
		if (m_cComponentWnd.m_cWindowState.m_bLoaded == false)
		{
			m_cComponentWnd.StartUp ();
			m_cComponentWnd.m_cWindowState.setWnd (&m_cComponentWnd);
		}

		m_cComponentWnd.ShowWindow (SW_SHOW);
	}
	else
	{
		m_cComponentWnd.ShowWindow (SW_HIDE);
	}

	if (m_cComponentWnd)
	{
		m_cComponentWnd.m_cWindowState.m_bVisible = l_bOpen;
	}

	CAppData::SetToolbarState (CAppData::m_cpHCCDlg->m_cCompButton, l_bOpen, IDB_TOOLBARCOMP0, IDB_TOOLBARCOMP1);

	return (true);
}

bool CAppData::SetSkillLevelWindow(bool l_bOpen)
{
	if (l_bOpen)
	{
		if (m_cSkillLevelWnd.m_cWindowState.m_bLoaded == false)
		{
			m_cSkillLevelWnd.StartUp ();
			m_cSkillLevelWnd.m_cWindowState.setWnd (&m_cSkillLevelWnd);
		}

		m_cSkillLevelWnd.ShowWindow (SW_SHOW);
	}
	else
	{
		m_cSkillLevelWnd.ShowWindow (SW_HIDE);
	}

	m_cSkillLevelWnd.m_cWindowState.m_bVisible = l_bOpen;

	return (true);
}

bool CAppData::SetReportWindow(bool l_bOpen)
{
	if (l_bOpen)
	{
		if (m_cReportWnd.m_cWindowState.m_bLoaded == false)
		{
			m_cReportWnd.StartUp ();
			m_cReportWnd.m_cWindowState.setWnd (&m_cReportWnd);
		}

		m_cReportWnd.ShowWindow (SW_SHOW);
	}
	else
	{
		m_cReportWnd.ShowWindow (SW_HIDE);
	}

	m_cReportWnd.m_cWindowState.m_bVisible = l_bOpen;
	CAppData::SetToolbarState (CAppData::m_cpHCCDlg->m_cReportButton, l_bOpen, IDB_TOOLBARREPORT0, IDB_TOOLBARREPORT1);

	return (true);
}

bool CAppData::SetProfileWindow(bool l_bOpen)
{
	if (l_bOpen)
	{
		if (m_cProfileWnd.m_cWindowState.m_bLoaded == false)
		{
			m_cProfileWnd.StartUp ();
			m_cProfileWnd.m_cWindowState.setWnd (&m_cProfileWnd);
		}

		m_cProfileWnd.ShowWindow (SW_SHOW);
	}
	else
	{
		m_cProfileWnd.ShowWindow (SW_HIDE);
	}

	m_cProfileWnd.m_cWindowState.m_bVisible = l_bOpen;
	CAppData::SetToolbarState (CAppData::m_cpHCCDlg->m_cProfileButton, l_bOpen, IDB_TOOLBARPROFILE0, IDB_TOOLBARPROFILE1);

	return (true);
}

CAppData::ClearComboBox(CComboBox &a_cCombo)
{
	while (a_cCombo.DeleteString (0) != CB_ERR)
	{
	}
}

CAppData::SetMainWindowState()
{
	CRegistryAccess l_cRegAccess;
	CString l_csBasePath = cAppData_RegWndPath;
	CString l_csWindowStr;

	m_cpHCCDlg->m_cWindowState.getWnd (*m_cpHCCDlg);
	l_csWindowStr = m_cpHCCDlg->m_cWindowState.toString ();
	l_cRegAccess.SaveKey (l_csBasePath, "ToolbarWnd", l_csWindowStr);
}

CAppData::SetOrderWindowState()
{
	CRegistryAccess l_cRegAccess;
	CString l_csBasePath = cAppData_RegWndPath;
	CString l_csWindowStr;

	if (m_cOrderWnd.m_cWindowState.m_bLoaded)
	{
		m_cOrderWnd.m_cWindowState.getWnd (m_cOrderWnd);
		l_csWindowStr = m_cOrderWnd.m_cWindowState.toString ();
		l_cRegAccess.SaveKey (l_csBasePath, "OrderWnd", l_csWindowStr);
	}
}

CAppData::SetFormulaWindowState()
{
	CRegistryAccess l_cRegAccess;
	CString l_csBasePath = cAppData_RegWndPath;
	CString l_csWindowStr;

	if (m_cItemCreationWnd.m_cWindowState.m_bLoaded)
	{
		m_cItemCreationWnd.m_cWindowState.getWnd (m_cItemCreationWnd);
		l_csWindowStr = m_cItemCreationWnd.m_cWindowState.toString ();
		l_cRegAccess.SaveKey (l_csBasePath, "ItemCreationWnd", l_csWindowStr);
	}
}

CAppData::SetTechWindowState()
{
	CRegistryAccess l_cRegAccess;
	CString l_csBasePath = cAppData_RegWndPath;
	CString l_csWindowStr;

	if (m_cTechSelectionWnd.m_cWindowState.m_bLoaded)
	{
		m_cTechSelectionWnd.m_cWindowState.getWnd (m_cTechSelectionWnd);
		l_csWindowStr = m_cTechSelectionWnd.m_cWindowState.toString ();
		l_cRegAccess.SaveKey (l_csBasePath, "TechSelectionWnd", l_csWindowStr);
	}
}

CAppData::SetCompWindowState()
{
	CRegistryAccess l_cRegAccess;
	CString l_csBasePath = cAppData_RegWndPath;
	CString l_csWindowStr;

	if (m_cComponentWnd.m_cWindowState.m_bLoaded)
	{
		m_cComponentWnd.m_cWindowState.getWnd (m_cComponentWnd);
		l_csWindowStr = m_cComponentWnd.m_cWindowState.toString ();
		l_cRegAccess.SaveKey (l_csBasePath, "ComponentWnd", l_csWindowStr);
	}
}

CAppData::SetReportWindowState()
{
	CRegistryAccess l_cRegAccess;
	CString l_csBasePath = cAppData_RegWndPath;
	CString l_csWindowStr;

	if (m_cReportWnd.m_cWindowState.m_bLoaded)
	{
		m_cReportWnd.m_cWindowState.getWnd (m_cReportWnd);
		l_csWindowStr = m_cReportWnd.m_cWindowState.toString ();
		l_cRegAccess.SaveKey (l_csBasePath, "ReportWnd", l_csWindowStr);
	}
}

CAppData::SetProfileWindowState()
{
	CRegistryAccess l_cRegAccess;
	CString l_csBasePath = cAppData_RegWndPath;
	CString l_csWindowStr;

	if (m_cProfileWnd.m_cWindowState.m_bLoaded)
	{
		m_cProfileWnd.m_cWindowState.getWnd (m_cProfileWnd);
		l_csWindowStr = m_cProfileWnd.m_cWindowState.toString ();
		l_cRegAccess.SaveKey (l_csBasePath, "ProfileWnd", l_csWindowStr);
	}
}

CAppData::GetMainWindowState()
{
	CRegistryAccess l_cRegAccess;
	CString l_csBasePath = cAppData_RegWndPath;
	CString l_csWindowStr;

	if (l_cRegAccess.LoadKey (l_csBasePath, "ToolbarWnd", l_csWindowStr))
	{
		CRect l_cRect;

		m_cpHCCDlg->GetWindowRect (l_cRect);
		m_cpHCCDlg->m_cWindowState.fromString (l_csWindowStr);
		// FIXME frame
		m_cpHCCDlg->m_cWindowState.m_iWidth = l_cRect.Width ();
		m_cpHCCDlg->m_cWindowState.m_iHeight = l_cRect.Height ();
		m_cpHCCDlg->m_cWindowState.setWnd (*m_cpHCCDlg);
		m_cpHCCDlg->m_cWindowState.m_bLoaded = true;
	}
}

CAppData::GetOrderWindowState()
{
	CRegistryAccess l_cRegAccess;
	CString l_csBasePath = cAppData_RegWndPath;
	CString l_csWindowStr;

	if (l_cRegAccess.LoadKey (l_csBasePath, "OrderWnd", l_csWindowStr))
	{
		m_cOrderWnd.m_cWindowState.fromString (l_csWindowStr);
		SetOrderWindow (m_cOrderWnd.m_cWindowState.m_bVisible);
		m_cOrderWnd.m_cWindowState.setWnd (&m_cOrderWnd);
	}
}

CAppData::GetFormulaWindowState()
{
	CRegistryAccess l_cRegAccess;
	CString l_csBasePath = cAppData_RegWndPath;
	CString l_csWindowStr;

	if (l_cRegAccess.LoadKey (l_csBasePath, "ItemCreationWnd", l_csWindowStr))
	{
		m_cItemCreationWnd.m_cWindowState.fromString (l_csWindowStr);
		SetItemWindow (m_cItemCreationWnd.m_cWindowState.m_bVisible);
		m_cItemCreationWnd.m_cWindowState.setWnd (&m_cItemCreationWnd);
	}

}

CAppData::GetTechWindowState ()
{
	CRegistryAccess l_cRegAccess;
	CString l_csBasePath = cAppData_RegWndPath;
	CString l_csWindowStr;

	if (l_cRegAccess.LoadKey (l_csBasePath, "TechSelectionWnd", l_csWindowStr))
	{
		m_cTechSelectionWnd.m_cWindowState.fromString (l_csWindowStr);
		SetTechWindow (m_cTechSelectionWnd.m_cWindowState.m_bVisible);
		m_cTechSelectionWnd.m_cWindowState.setWnd (&m_cTechSelectionWnd);
	}

}

CAppData::GetCompWindowState ()
{
	CRegistryAccess l_cRegAccess;
	CString l_csBasePath = cAppData_RegWndPath;
	CString l_csWindowStr;

	if (l_cRegAccess.LoadKey (l_csBasePath, "ComponentWnd", l_csWindowStr))
	{
		m_cComponentWnd.m_cWindowState.fromString (l_csWindowStr);
		SetComponentWindow (m_cComponentWnd.m_cWindowState.m_bVisible);
		m_cComponentWnd.m_cWindowState.setWnd (&m_cComponentWnd);
	}

}

CAppData::GetReportWindowState ()
{
	CRegistryAccess l_cRegAccess;
	CString l_csBasePath = cAppData_RegWndPath;
	CString l_csWindowStr;

	if (l_cRegAccess.LoadKey (l_csBasePath, "ReportWnd", l_csWindowStr))
	{
		m_cReportWnd.m_cWindowState.fromString (l_csWindowStr);
		SetReportWindow (m_cReportWnd.m_cWindowState.m_bVisible);
		m_cReportWnd.m_cWindowState.setWnd (&m_cReportWnd);
	}
}


CAppData::GetProfileWindowState ()
{
	CRegistryAccess l_cRegAccess;
	CString l_csBasePath = cAppData_RegWndPath;
	CString l_csWindowStr;

	if (l_cRegAccess.LoadKey (l_csBasePath, "ProfileWnd", l_csWindowStr))
	{
		m_cProfileWnd.m_cWindowState.fromString (l_csWindowStr);
		SetProfileWindow (m_cProfileWnd.m_cWindowState.m_bVisible);
		m_cProfileWnd.m_cWindowState.setWnd (&m_cProfileWnd);
	}
}

//////////////////////////////////////////////////////////////////////
// Load/Save Routines
//////////////////////////////////////////////////////////////////////

CAppData::LoadGameImages(CString &a_csGamePath, CString &a_csAppPath)
{
	CString l_cFormulaPath = a_csGamePath + cPath_Game_FormulaIcons;
	CString l_cTechPath = a_csGamePath + cPath_Game_TechIcons;
	CString l_CAppIconsPath = a_csAppPath + cPath_App_Icons;

	ClearImageCache();

	if (m_bEnableIcons)
	{
		CAppData::m_cpIconImages->LoadFromDirectory (l_CAppIconsPath);
		CAppData::m_cpIconImages->LoadFromDirectory (l_cFormulaPath);
		CAppData::m_cpIconImages->LoadFromDirectory (l_cTechPath);
	}

}

CAppData::LoadData()
{
	CString l_csCachePath = CAppData::m_csAppBasePath + cPath_App_Cache;

	if (!CAppData::LoadCache (l_csCachePath))
	{
		CRecacheDialog l_cRecacheDialog;
		l_cRecacheDialog.DoModal ();
		//m_cpCacheProgress = NULL;
		//l_cRecacheDialog.Recache (true);
	}

	CAppData::m_clOrderList.RemoveAll ();
	CAppData::m_cOrderGroups.RemoveAll ();
	CAppData::m_clProfileList.RemoveAll ();
	CAppData::m_cmHelpLinks.RemoveAll ();

	CAppData::m_csCurrentOrderFilename = "Untitled.xml";
	CAppData::m_cCurrentOrderItem.m_csItemName.Empty ();

	CAppData::m_cpCurrentProfile = NULL;
	CAppData::m_cpTemplateProfile = NULL;
	CAppData::m_bProfilesChanged = false;

	LoadEffectLists();
	CAppData::LoadHelpLinks (CAppData::m_csAppBasePath + cFile_App_Help);
	CAppData::LoadProfiles (CAppData::m_csAppBasePath + cPath_App_DefaultProfiles, cAppData_Profile_Defaults);
	CAppData::LoadProfiles (CAppData::m_csAppBasePath + cPath_App_LocalProfiles, cAppData_Profile_Local);

	if ((!m_cpCurrentProfile) && (m_clProfileList.GetCount() > 0))
	{
		m_cpCurrentProfile = m_clProfileList.GetHead ();
		m_csCurrentProfile = m_cpCurrentProfile->m_csProfileName;
		m_csCurrentProfileType = m_cpCurrentProfile->m_csProfileType;
	}

	CAppData::CacheInternalData ();

	if (!CScheme::LoadHCCScheme (CAppData::m_csAppBasePath + cPath_App_Theme + "\\" + CAppData::m_csCurrentTheme))
	{
		CScheme::LoadHCCScheme (CAppData::m_csAppBasePath + cPath_App_Theme + "\\" + cFile_App_DefaultTheme);
	}

	if (m_cItemCreationWnd.m_cWindowState.m_bLoaded)
	{
		m_cItemCreationWnd.DrawCategoryList ();
	}

	if (m_cTechSelectionWnd.m_cWindowState.m_bLoaded)
	{
		m_cTechSelectionWnd.DrawCategoryList ();
	}

	ApplyCurrentTheme(false);
}

CAppData::ReadDefaults()
{
	CRegistryAccess l_cRegAccess;
	CString l_csBasePath = cAppData_RegPath;

	m_csOrderDir = m_csAppBasePath + cPath_App_Orders;
	m_csProfileDir = m_csAppBasePath + cPath_App_LocalProfiles;
	m_csTmpDir = m_csAppBasePath + cPath_App_Temp;

    CString l_ErrMsg = "Error - Unable to create the folder \"%s\\\".\n\nPlease reinstall HCC using the installer or make sure the folder has write permissions.";
    CString l_ErrMsgOut = "";


    if (_chdir(m_csAppBasePath + cPath_App_Temp))
    {
        CreateDirectory(m_csAppBasePath + cPath_App_Temp,NULL);
        l_ErrMsgOut.Format(l_ErrMsg, cPath_App_Temp.Mid(1));
        if (_chdir(m_csAppBasePath + cPath_App_Temp)) AfxMessageBox (l_ErrMsgOut, MB_ICONEXCLAMATION );
    }
    if (_chdir(m_csAppBasePath + cPath_App_Orders))
    {
        CreateDirectory(m_csAppBasePath + cPath_App_Orders,NULL);
        l_ErrMsgOut.Format(l_ErrMsg, cPath_App_Orders.Mid(1));
        if (_chdir(m_csAppBasePath + cPath_App_Orders)) AfxMessageBox (l_ErrMsgOut, MB_ICONEXCLAMATION );
    }
    if (_chdir(m_csAppBasePath + cPath_App_Theme))
    {
        CreateDirectory(m_csAppBasePath + cPath_App_Theme,NULL);
        l_ErrMsgOut.Format(l_ErrMsg, cPath_App_Theme.Mid(1));
        if (_chdir(m_csAppBasePath + cPath_App_Theme)) AfxMessageBox (l_ErrMsgOut, MB_ICONEXCLAMATION );
    }
    if (_chdir(m_csAppBasePath + cPath_App_LocalProfiles))
    {
        CreateDirectory(m_csAppBasePath + cPath_App_LocalProfiles,NULL);
        l_ErrMsgOut.Format(l_ErrMsg, cPath_App_LocalProfiles.Mid(1));
        if (_chdir(m_csAppBasePath + cPath_App_LocalProfiles)) AfxMessageBox (l_ErrMsgOut, MB_ICONEXCLAMATION );
    }
    if (_chdir(m_csAppBasePath + cPath_App_Cache))
    {
        CreateDirectory(m_csAppBasePath + cPath_App_Cache,NULL);
        l_ErrMsgOut.Format(l_ErrMsg, cPath_App_Cache.Mid(1));
        if (_chdir(m_csAppBasePath + cPath_App_Cache)) AfxMessageBox (l_ErrMsgOut, MB_ICONEXCLAMATION );
    }
    if (_chdir(m_csAppBasePath + cPath_App_Config))
    {
        CreateDirectory(m_csAppBasePath + cPath_App_Config,NULL);
        l_ErrMsgOut.Format(l_ErrMsg, cPath_App_Config.Mid(1));
        if (_chdir(m_csAppBasePath + cPath_App_Config)) AfxMessageBox (l_ErrMsgOut, MB_ICONEXCLAMATION );
    }
    if (_chdir(m_csAppBasePath + cPath_App_Plugin))
    {
        CreateDirectory(m_csAppBasePath + cPath_App_Plugin,NULL);
        l_ErrMsgOut.Format(l_ErrMsg, cPath_App_Plugin.Mid(1));
        if (_chdir(m_csAppBasePath + cPath_App_Plugin)) AfxMessageBox (l_ErrMsgOut, MB_ICONEXCLAMATION );
    }

    _chdir(m_csAppBasePath);

    //CreateDirectory(cPath_App_Config,NULL);

	m_csLastFormulaCategory = "";
	m_csLastTechCategory = "";
	m_csCurrentTheme = cFile_App_DefaultTheme;

	l_cRegAccess.LoadKey (l_csBasePath, "GameBasePath", m_csGameBasePath);

	if (m_csGameBasePath.IsEmpty ())
	{
		m_csGameBasePath = "<Please Set Manually>";
	}

	l_cRegAccess.LoadKey (l_csBasePath, "CurrentProfile", m_csCurrentProfile);
	l_cRegAccess.LoadKey (l_csBasePath, "CurrentProfileType", m_csCurrentProfileType);
	//l_cRegAccess.LoadKey (l_csBasePath, "OrderDir", m_csOrderDir);
	//l_cRegAccess.LoadKey (l_csBasePath, "ProfileDir", m_csProfileDir);
	l_cRegAccess.LoadKey (l_csBasePath, "DatabaseRevision", m_csDatabaseRevision);
	l_cRegAccess.LoadKey (l_csBasePath, "LastFormulaCategory", m_csLastFormulaCategory);
	l_cRegAccess.LoadKey (l_csBasePath, "LastTechCategory", m_csLastTechCategory);
	l_cRegAccess.LoadKey (l_csBasePath, "CurrentTheme", m_csCurrentTheme);

	l_cRegAccess.LoadKey (l_csBasePath, "ItemResourceSize", m_iItemResourceSize);
	l_cRegAccess.LoadKey (l_csBasePath, "ShowResourceMode", m_iShowResourceMode);
	l_cRegAccess.LoadKey (l_csBasePath, "ShowReportMode", m_iShowReportMode);
	l_cRegAccess.LoadKey (l_csBasePath, "ExpandFormulaMode", m_iExpandFormulaMode);
	l_cRegAccess.LoadKey (l_csBasePath, "IconSize", m_iIconSize);
	l_cRegAccess.LoadKey (l_csBasePath, "ReportType", m_iReportType);
	//l_cRegAccess.LoadKey (l_csBasePath, "ReportFormat", m_iReportFormat);
	l_cRegAccess.LoadKey (l_csBasePath, "ShowReportResourceMode", m_iShowReportResourceMode);
	l_cRegAccess.LoadKey (l_csBasePath, "ShowReportBonusMode", m_iShowReportBonusMode);
	l_cRegAccess.LoadKey (l_csBasePath, "ExpandTechMode", m_iExpandTechMode);
	l_cRegAccess.LoadKey (l_csBasePath, "StickyStrength", m_iStickyStrength);

	l_cRegAccess.LoadKey (l_csBasePath, "ShowUsableTechs", m_bShowUsableTechs);
	l_cRegAccess.LoadKey (l_csBasePath, "EnableCache", m_bEnableCache);
	l_cRegAccess.LoadKey (l_csBasePath, "EnableIcons", m_bEnableIcons);
	l_cRegAccess.LoadKey (l_csBasePath, "DockingMode", m_bAutoDock);
	l_cRegAccess.LoadKey (l_csBasePath, "GlobalHotkeys", m_bGlobalHotkeys);
	l_cRegAccess.LoadKey (l_csBasePath, "DragWithToolbar", m_bDragWithToolBar);
	l_cRegAccess.LoadKey (l_csBasePath, "VerticalToolbar", m_bVerticalToolBar);
	l_cRegAccess.LoadKey (l_csBasePath, "AutoShrink", m_bAutoShrink);
	l_cRegAccess.LoadKey (l_csBasePath, "AutoUpdate", m_bAutoUpdate);
	l_cRegAccess.LoadKey (l_csBasePath, "AutoUpdateQuery", m_bAutoUpdateQuery);
	l_cRegAccess.LoadKey (l_csBasePath, "HighPriority", m_bHighPriority);

	if (m_csOrderDir.IsEmpty ())
	{
		m_csOrderDir = m_csAppBasePath + cPath_App_Orders;
	}

	if ((m_csLastFormulaCategory.IsEmpty ()) ||
		 (m_csLastFormulaCategory == cCustom_Filter))
	{
		m_csLastFormulaCategory = cNo_Filter;
	}

	if (m_csLastTechCategory.IsEmpty ())
	{
		m_csLastTechCategory = cNo_Filter;
	}

	if (CAppData::m_bHighPriority)
	{
		SetThreadPriority (GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);
	}
	else
	{
		SetThreadPriority (GetCurrentThread(), THREAD_PRIORITY_NORMAL);
	}

}

CAppData::SaveDefaults()
{
	CRegistryAccess l_cRegAccess;
	CString l_csBasePath = cAppData_RegPath;

	SaveProfiles (true);

	l_cRegAccess.SaveKey (l_csBasePath, "GameBasePath", m_csGameBasePath);
	l_cRegAccess.SaveKey (l_csBasePath, "CurrentProfile", m_csCurrentProfile);
	l_cRegAccess.SaveKey (l_csBasePath, "CurrentProfileType", m_csCurrentProfileType);
	//l_cRegAccess.SaveKey (l_csBasePath, "OrderDir", m_csOrderDir);
	//l_cRegAccess.SaveKey (l_csBasePath, "ProfileDir", m_csProfileDir);
	l_cRegAccess.SaveKey (l_csBasePath, "LastFormulaCategory", m_csLastFormulaCategory);
	l_cRegAccess.SaveKey (l_csBasePath, "LastTechCategory", m_csLastTechCategory);
	l_cRegAccess.SaveKey (l_csBasePath, "DatabaseRevision", m_csDatabaseRevision);
	l_cRegAccess.SaveKey (l_csBasePath, "CurrentTheme", m_csCurrentTheme);

	l_cRegAccess.SaveKey (l_csBasePath, "ItemResourceSize", m_iItemResourceSize);
	l_cRegAccess.SaveKey (l_csBasePath, "ShowResourceMode", m_iShowResourceMode);
	l_cRegAccess.SaveKey (l_csBasePath, "ShowReportMode", m_iShowReportMode);
	l_cRegAccess.SaveKey (l_csBasePath, "ExpandFormulaMode", m_iExpandFormulaMode);
	l_cRegAccess.SaveKey (l_csBasePath, "ExpandTechMode", m_iExpandTechMode);
	l_cRegAccess.SaveKey (l_csBasePath, "IconSize", m_iIconSize);
	l_cRegAccess.SaveKey (l_csBasePath, "ReportType", m_iReportType);
	//l_cRegAccess.SaveKey (l_csBasePath, "ReportFormat", m_iReportFormat);
	l_cRegAccess.SaveKey (l_csBasePath, "ShowReportResourceMode", m_iShowReportResourceMode);
	l_cRegAccess.SaveKey (l_csBasePath, "ShowReportBonusMode", m_iShowReportBonusMode);
	l_cRegAccess.SaveKey (l_csBasePath, "StickyStrength", m_iStickyStrength);

	l_cRegAccess.SaveKey (l_csBasePath, "ShowUsableTechs", m_bShowUsableTechs);
	l_cRegAccess.SaveKey (l_csBasePath, "EnableCache", m_bEnableCache);
	l_cRegAccess.SaveKey (l_csBasePath, "EnableIcons", m_bEnableIcons);
	l_cRegAccess.SaveKey (l_csBasePath, "DockingMode", m_bAutoDock);
	l_cRegAccess.SaveKey (l_csBasePath, "GlobalHotkeys", m_bGlobalHotkeys);
	l_cRegAccess.SaveKey (l_csBasePath, "DragWithToolbar", m_bDragWithToolBar);
	l_cRegAccess.SaveKey (l_csBasePath, "VerticalToolbar", m_bVerticalToolBar);
	l_cRegAccess.SaveKey (l_csBasePath, "AutoShrink", m_bAutoShrink);
	l_cRegAccess.SaveKey (l_csBasePath, "AutoUpdate", m_bAutoUpdate);
	l_cRegAccess.SaveKey (l_csBasePath, "AutoUpdateQuery", m_bAutoUpdateQuery);
	l_cRegAccess.SaveKey (l_csBasePath, "HighPriority", m_bHighPriority);
}

bool CAppData::LoadFormulas(CString &a_csPath, CTypedPtrList<CPtrList, CFormulaSet*> &a_clFormulaList)
{
	bool l_bResult = true;
	bool l_bSearching;
	bool l_bAdded = false;
	CFileFind l_cFileFind;
	CFormulaSet *l_cpFormulaSet;
	CFormulaSet *l_cpSearchFormulaSet;
	POSITION l_Pos;
	POSITION l_PrevPos;

	l_bSearching = (l_cFileFind.FindFile (a_csPath + "\\*.*") != 0);
	while (l_bSearching)
	{
		l_bSearching = (l_cFileFind.FindNextFile () != 0);

		if (l_cFileFind.IsDirectory ())
		{
			if (l_cFileFind.IsDots () == false)
			{
				// Create New Category and get child elements
				l_bResult = LoadFormulas (l_cFileFind.GetFilePath (), a_clFormulaList);
			}
		}
		else
		{
			// Search for xml files
			if (l_cFileFind.GetFileName().Find (".xml") >= 0)
			{
				l_bAdded = false;

				l_cpFormulaSet = new CFormulaSet ();
				if (l_cpFormulaSet->LoadFormulaSet (l_cFileFind.GetFilePath ()))
				{
					l_Pos = a_clFormulaList.GetHeadPosition ();
					while ((l_Pos) && (!l_bAdded))
					{
						l_PrevPos = l_Pos;
						l_cpSearchFormulaSet = m_clFormulaSetList.GetNext (l_Pos);
						if ((l_cpSearchFormulaSet->m_csName == l_cpFormulaSet->m_csName) &&
							 (l_cpSearchFormulaSet->m_csCategory == l_cpFormulaSet->m_csCategory))
						{
							l_cpSearchFormulaSet->AddSet (l_cpFormulaSet);
							delete (l_cpFormulaSet);
							l_bAdded = true;
						}
					}

					if (!l_bAdded)
					{
						a_clFormulaList.AddTail (l_cpFormulaSet);

						if (l_cpFormulaSet->m_csCategory == cFormulaCategory_Resources)
						{
							CAppData::m_cResourceFormulaSetList.AddTail (l_cpFormulaSet);
						}
					}
				}

				m_iCacheCount++;
				if (m_cpCacheProgress)
				{
					m_cpCacheProgress->SetPos (m_iCacheCount);
				}
			}
		}

	}

	l_cFileFind.Close ();

	return (l_bResult);
}

bool CAppData::LoadTechniques(CString &a_csPath)
{
	bool l_bResult = true;
	bool l_bAdded = false;
	bool l_bSearching;
	CFileFind l_cFileFind;
	CTechSet *l_cpTechSet = NULL;
	CTechSet *l_cpSearchTechSet = NULL;
	POSITION l_Pos;
	POSITION l_PrevPos;

	l_bSearching = (l_cFileFind.FindFile (a_csPath + "\\*.*") != 0);
	while (l_bSearching)
	{
		l_bSearching = (l_cFileFind.FindNextFile () != 0);

		if (l_cFileFind.IsDirectory ())
		{
			if (l_cFileFind.IsDots () == false)
			{
				// Create New Category and get child elements
				l_bResult = LoadTechniques (l_cFileFind.GetFilePath ());
			}
		}
		else
		{
			// Search for xml files
			if (l_cFileFind.GetFileName().Find (".xml") >= 0)
			{
				l_bAdded = false;

				l_cpTechSet = new CTechSet ();
				if (l_cpTechSet->LoadTechSet (l_cFileFind.GetFilePath ()))
				{
					l_Pos = m_clTechSetList.GetHeadPosition ();
					while ((l_Pos) && (!l_bAdded))
					{
						l_PrevPos = l_Pos;
						l_cpSearchTechSet = m_clTechSetList.GetNext (l_Pos);
						if ((l_cpSearchTechSet->m_csName == l_cpTechSet->m_csName) &&
							 (l_cpSearchTechSet->m_csCategory == l_cpTechSet->m_csCategory))
						{
							l_cpSearchTechSet->AddSet (l_cpTechSet);
							delete (l_cpTechSet);
							l_bAdded = true;
						}
					}

					if (!l_bAdded)
					{
						m_clTechSetList.AddTail (l_cpTechSet);
					}
				}

				m_iCacheCount++;
				if (m_cpCacheProgress)
				{
					m_cpCacheProgress->SetPos (m_iCacheCount);
				}
			}
		}

	}

	l_cFileFind.Close ();
	return (l_bResult);
}

bool CAppData::LoadProfiles(CString &a_csPath, CString a_csType)
{
	bool l_bResult = true;
	bool l_bAdded = false;
	bool l_bSearching;
	CFileFind l_cFileFind;
	CProfile *l_cpProfile;

	// Default
	l_bSearching = (l_cFileFind.FindFile (a_csPath + "\\*.xml") != 0);
	while (l_bSearching)
	{
		l_bSearching = (l_cFileFind.FindNextFile () != 0);

		if (!l_cFileFind.IsDirectory ())
		{
			// Search for xml files
			if (l_cFileFind.GetFileName().Find (".xml") >= 0)
			{
				l_cpProfile = new CProfile ();
				l_cpProfile->m_csProfileType = a_csType;
				if (l_cpProfile->LoadFromFile (l_cFileFind.GetFilePath ()))
				{
					if ((l_cpProfile->m_csProfileName == m_csCurrentProfile) &&
						 (l_cpProfile->m_csProfileType == m_csCurrentProfileType))
					{
						m_cpCurrentProfile = l_cpProfile;
					}

					if ((l_cpProfile->m_csProfileName == cProfileName_Template) &&
						 (l_cpProfile->m_csProfileType == cAppData_Profile_Defaults))
					{
						m_cpTemplateProfile = l_cpProfile;
					}

					m_clProfileList.AddTail (l_cpProfile);
				}
			}
		}
	}
	l_cFileFind.Close ();

	return (l_bResult);
}

bool CAppData::LoadWizards(CString &a_csPath)
{
	bool l_bResult = true;
	bool l_bAdded = false;
	bool l_bSearching;
	CFileFind l_cFileFind;
	CSchoolWizard *l_cpSchoolWizard;

	// Default
	l_bSearching = (l_cFileFind.FindFile (a_csPath + "\\*.xml") != 0);
	while (l_bSearching)
	{
		l_bSearching = (l_cFileFind.FindNextFile () != 0);

		if (!l_cFileFind.IsDirectory ())
		{
			// Search for xml files
			if (l_cFileFind.GetFileName().Find (".xml") >= 0)
			{
				l_cpSchoolWizard = new CSchoolWizard ();
				if (l_cpSchoolWizard->LoadFromFile (l_cFileFind.GetFilePath ()))
				{
					m_clSchoolWizardList.AddTail (l_cpSchoolWizard);
				}

				m_iCacheCount++;
				if (m_cpCacheProgress)
				{
					m_cpCacheProgress->SetPos (m_iCacheCount);
				}
			}
		}
	}
	l_cFileFind.Close ();

	return (l_bResult);
}

bool CAppData::LoadComponentFile(CString &a_csFilename)
{
	bool l_bResult = false;
	CComponent *l_cpComponent;
	CCompGatherInfo *l_cpCompGatherInfo;
	CCompBonusInfo *l_cpCompBonusInfo;
	XMLParser l_cParser;
	XMLTag l_cRootTag ("#ROOT#");
	XMLTag l_cComponentsTag ("components");
	XMLTag l_cComponentTag ("comp");
	XMLTag l_cGatherMethodsTag ("gather-methods");
	XMLTag l_cGatherTag ("gather");
	XMLTag l_cBonusesTag ("bonuses");
	XMLTag l_cBonusTag ("bonus");
	XMLTag l_cLocTag ("locs");
	CString l_csLoc;

	m_clComponentList.RemoveAll ();
	l_cParser.OpenFile (a_csFilename);

	// Should be only one components Tag
	if (l_cComponentsTag.GetNextTag (l_cParser, l_cRootTag))
	{
		while (l_cComponentTag.GetNextTag (l_cParser, l_cComponentsTag))
		{
			l_cpComponent = new CComponent ();
			l_cComponentTag.GetTagValue (l_cParser, (CString) "comp-name", l_cpComponent->m_csComponentName);
			l_cComponentTag.GetTagValue (l_cParser, (CString) "comp-tier", l_cpComponent->m_iTier);
			l_cComponentTag.GetTagValue (l_cParser, (CString) "comp-desc", l_cpComponent->m_csDescription);
			l_cComponentTag.GetTagValue (l_cParser, (CString) "comp-type", l_cpComponent->m_csType);
			l_cComponentTag.GetTagValue (l_cParser, (CString) "comp-bulk", l_cpComponent->m_iBulk);
			l_cComponentTag.GetTagValue (l_cParser, (CString) "comp-pawnbuy", l_cpComponent->m_csPawnBuyPrice);
			l_cComponentTag.GetTagValue (l_cParser, (CString) "comp-pawnsell", l_cpComponent->m_csPawnSellPrice);
			l_cComponentTag.GetTagValue (l_cParser, (CString) "comp-vielosell", l_cpComponent->m_csVieloSellPrice);
			l_cpComponent->m_csLocations.RemoveAll();

			if (l_cGatherMethodsTag.GetNextTag (l_cParser, l_cComponentTag))
			{
				while (l_cGatherTag.GetNextTag (l_cParser, l_cGatherMethodsTag))
				{
					l_cpCompGatherInfo = new CCompGatherInfo ();
					l_cGatherTag.GetTagValue (l_cParser, (CString) "gather-skill", l_cpCompGatherInfo->m_csSkill);
					l_cGatherTag.GetTagValue (l_cParser, (CString) "gather-tool", l_cpCompGatherInfo->m_csTool);
					l_cGatherTag.GetTagValue (l_cParser, (CString) "gather-rate", l_cpCompGatherInfo->m_csRate);
					l_cGatherTag.GetTagValue (l_cParser, (CString) "min-skill", l_cpCompGatherInfo->m_csMinLvl);
					l_cGatherTag.GetTagValue (l_cParser, (CString) "max-skill", l_cpCompGatherInfo->m_csOptLvl);

					if (l_cBonusesTag.GetNextTag (l_cParser, l_cGatherTag))
					{
						while (l_cBonusTag.GetNextTag (l_cParser, l_cBonusesTag))
						{
							l_cpCompBonusInfo = new CCompBonusInfo ();
							l_cBonusTag.GetTagValue (l_cParser, (CString) "bonus-name", l_cpCompBonusInfo->m_csName);
							l_cBonusTag.GetTagDoubleValue (l_cParser, (CString) "bonus-amount",l_cpCompBonusInfo->m_csChance, l_cpCompBonusInfo->m_csAmount);

							l_cpCompGatherInfo->m_clCompBonusInfoList.AddTail (l_cpCompBonusInfo);
						}
					}

					l_cpComponent->m_clCompGatherInfoList.AddTail (l_cpCompGatherInfo);
				}
			}

			if (l_cLocTag.GetNextTag (l_cParser, l_cComponentTag))
			{
				while (l_cLocTag.GetRepeatingTagValue (l_cParser, (CString) "loc-coord", l_csLoc))
				{
					l_cpComponent->m_csLocations.AddTail (l_csLoc);
				}
			}

			m_clComponentList.AddTail (l_cpComponent);
		}

		l_bResult = true;
	}

	return (l_bResult);
}

bool CAppData::LoadTechniqueFile(CString &a_csFilename)
{
	bool l_bResult = false;
	CTech *l_cpTech;
	XMLParser l_cParser;
	XMLTag l_cRootTag ("#ROOT#");
	XMLTag l_cTechniquesTag ("techniques");
	XMLTag l_cTechTag ("tech");
	XMLTag l_cTechAttributesTag ("tech-attributes");
	CString l_csTechName;
	CString l_csCategory;
	CString l_csAttribute;
	CString l_csValue;
	CString l_csStr;

	l_cParser.OpenFile (a_csFilename);

	// Should be only one technique Tag
	if (l_cTechniquesTag.GetNextTag (l_cParser, l_cRootTag))
	{
		while (l_cTechTag.GetNextTag (l_cParser, l_cTechniquesTag))
		{
			l_cTechTag.GetTagValue (l_cParser, (CString) "tech-name", l_csTechName);
			l_cTechTag.GetTagValue (l_cParser, (CString) "tech-category", l_csCategory);
			if (FindTech (cNo_Filter, l_csTechName, &l_cpTech))
			{
				l_cpTech->LoadTech (l_csCategory, l_cParser, l_cTechTag, false);
			}

		}

		l_bResult = true;
	}

	return (l_bResult);
}

bool CAppData::LoadFormulaFile(CString &a_csFilename)
{
	bool l_bResult = false;
	CFormula *l_cpFormula;
	CFormulaSet *l_cpFormulaSet;
	XMLParser l_cParser;
	XMLTag l_cRootTag ("#ROOT#");
	XMLTag l_FormulasTag ("formulas");
	XMLTag l_cItemTag ("item");
	CString l_csFormulaName;
	CString l_csCategory;
	CString l_csFormulaSet;
	CString l_csAttribute;
	CString l_csValue;
	CString l_csStr;
	POSITION l_Pos;
	POSITION l_PrevPos;
	bool l_bFound = false;

	l_cParser.OpenFile (a_csFilename);

	// Should be only one technique Tag
	if (l_FormulasTag.GetNextTag (l_cParser, l_cRootTag))
	{
		while (l_cItemTag.GetNextTag (l_cParser, l_FormulasTag))
		{
			l_cItemTag.GetTagValue (l_cParser, (CString) "item-name", l_csFormulaName);
			l_cItemTag.GetTagValue (l_cParser, (CString) "item-category", l_csCategory);
			l_cItemTag.GetTagValue (l_cParser, (CString) "item-formulaset", l_csFormulaSet);
			if (FindFormula (cNo_Filter, l_csFormulaName, &l_cpFormula))
			{
				l_cpFormula->LoadFormula (l_cpFormula->m_csCategory, l_cParser, l_cItemTag, false);
			}
			else
			{
				if ((!l_csCategory.IsEmpty ()) && (!l_csFormulaSet.IsEmpty ()))
				{
					l_bFound = false;
					l_Pos = m_clFormulaSetList.GetHeadPosition ();
					while ((l_Pos) && (!l_bFound))
					{
						l_PrevPos = l_Pos;
						l_cpFormulaSet = m_clFormulaSetList.GetNext (l_Pos);
						if ((l_cpFormulaSet->m_csName == l_csFormulaSet) &&
							 (l_cpFormulaSet->m_csCategory == l_csCategory))
						{
							l_bFound = true;
						}
					}

					if (!l_bFound)
					{
						l_cpFormulaSet = new CFormulaSet ();
						l_cpFormulaSet->m_csName = l_csFormulaSet;
						l_cpFormulaSet->m_csCategory = l_csCategory;
						m_clFormulaSetList.AddTail (l_cpFormulaSet);
					}

					l_cpFormula = new CFormula ();
					l_cpFormula->LoadFormula (l_csCategory, l_cParser, l_cItemTag, false);
					l_cpFormulaSet->m_clFormulaList.AddTail (l_cpFormula);
				}
			}

		}

		l_bResult = true;
	}

	return (l_bResult);
}

bool CAppData::LoadCategories(CString &a_csFilename)
{
	bool l_bResult = false;
	CCategory *l_cpCategory;
	CSubCategory *l_cpSubCategory;
	XMLParser l_cParser;
	XMLTag l_cRootTag ("#ROOT#");
	XMLTag l_cCategoriesTag ("categories");
	XMLTag l_cCategoryTag ("category");
	XMLTag l_cSubCategoriesTag ("subcategories");
	XMLTag l_cSubCategoryTag ("subcategory");
	CString l_csIconName;

	l_cParser.OpenFile (a_csFilename);

	// Should be only one categories Tag
	if (l_cCategoriesTag.GetNextTag (l_cParser, l_cRootTag))
	{
		while (l_cCategoryTag.GetNextTag (l_cParser, l_cCategoriesTag))
		{
			l_cpCategory = new CCategory ();
			l_cCategoryTag.GetTagValue (l_cParser, (CString) "category-name", l_cpCategory->m_csCategoryName);
			l_cCategoryTag.GetTagValue (l_cParser, (CString) "category-desc", l_cpCategory->m_csDescription);
			l_cCategoryTag.GetTagValue (l_cParser, (CString) "category-icon", l_csIconName);
			l_cpCategory->m_iIcon = CAppData::m_cpIconImages->FindImageOffset (l_csIconName);
			m_clCategoryList.AddTail (l_cpCategory);

			if (l_cSubCategoriesTag.GetNextTag (l_cParser, l_cCategoryTag))
			{
				while (l_cSubCategoryTag.GetNextTag (l_cParser, l_cSubCategoriesTag))
				{
					l_cpSubCategory = new CSubCategory ();
					l_cpSubCategory->m_csCategoryName = l_cpCategory->m_csCategoryName;
					l_cSubCategoryTag.GetTagValue (l_cParser, (CString) "subcategory-name", l_cpSubCategory->m_csSubCategoryName);
					l_cSubCategoryTag.GetTagValue (l_cParser, (CString) "subcategory-desc", l_cpSubCategory->m_csDescription);
					l_cSubCategoryTag.GetTagValue (l_cParser, (CString) "subcategory-icon", l_csIconName);
					l_cpSubCategory->m_iIcon = CAppData::m_cpIconImages->FindImageOffset (l_csIconName);
					m_clSubCategoryList.AddTail (l_cpSubCategory);
				}
			}
		}

		l_bResult = true;
	}

	return (l_bResult);
}

bool CAppData::LoadHelpLinks(CString &a_csFilename)
{
	bool l_bResult = false;
	XMLParser l_cParser;
	XMLTag l_cRootTag ("#ROOT#");
	XMLTag l_cHelpTag ("help");
	XMLTag l_cPagesTag ("pages");
	CString l_csPage;
	CString l_csLink;

	l_cParser.OpenFile (a_csFilename);

	// Should be only one help Tag
	if (l_cHelpTag.GetNextTag (l_cParser, l_cRootTag))
	{
		// Should be only one pages Tag
		if (l_cPagesTag.GetNextTag (l_cParser, l_cHelpTag))
		{
			while (l_cPagesTag.GetRepeatingDoubleTagValue (l_cParser, (CString) "page", l_csPage, l_csLink))
			{
				CAppData::m_cmHelpLinks.SetAt (l_csPage, l_csLink);
			}

			l_bResult = true;
		}
	}

	return (l_bResult);
}

bool CAppData::SaveOrder(CString &a_csFilename)
{
	POSITION l_cPos;
	COrderItem l_cOrderItem;
	CItemTech l_cItemTech;
	POSITION l_TechPos;
	XMLParser l_cParser;
	CString l_csTier;
	CString l_csCompName;
	CString l_csCount;
	CString l_csStr;
	bool l_bResult = false;

	OptimiseStoredComponents ();

	if (l_cParser.WriteFile (a_csFilename))
	{
		l_cParser.WriteOpenTag ("order");
		l_cParser.WriteTag ("order-format", "1.1");
		l_cParser.WriteOpenTag ("generator");
        l_cParser.WriteTag ("application", "HCC");
		l_cParser.WriteTag ("version", cAppData_Version);
		l_cParser.WriteTag ("database", CAppData::m_csDatabaseRevision);
		l_cParser.WriteCloseTag ("generator");

		l_cParser.WriteOpenTag ("groups");
		l_cPos = m_cOrderGroups.GetHeadPosition ();
		while (l_cPos)
		{
			l_cParser.WriteTag ("group", m_cOrderGroups.GetNext (l_cPos));
		}
		l_cParser.WriteCloseTag ("groups");

		l_cPos = m_clOrderList.GetHeadPosition ();
		while (l_cPos)
		{
			l_cOrderItem = m_clOrderList.GetNext (l_cPos);

			l_cParser.WriteOpenTag ("item");
			l_cParser.WriteTag ("item-name", l_cOrderItem.m_csItemName);
			l_cParser.WriteTag ("item-group", l_cOrderItem.m_csOrderGroup);
			l_cParser.WriteTag ("item-formula", l_cOrderItem.m_csFormulaName);
			//l_cParser.WriteTag ("item-category", l_cOrderItem.m_csCategory);
			l_cParser.WriteTag ("item-tierlvlname", l_cOrderItem.m_csTierName);
			l_cParser.WriteTag ("item-qty", l_cOrderItem.m_iQty);

			l_cParser.WriteOpenTag ("techs");

			l_TechPos = l_cOrderItem.m_clTechList.GetHeadPosition ();
			while (l_TechPos)
			{
				l_cItemTech = l_cOrderItem.m_clTechList.GetNext (l_TechPos);

				l_csTier.Format ("tier=\"%s\"", l_cItemTech.m_csTierName);
				l_cParser.WriteAttributeTag ("tech", l_csTier, l_cItemTech.m_csTechName);
			}

			l_cParser.WriteCloseTag ("techs");

			l_cParser.WriteCloseTag ("item");
		}

		l_cParser.WriteOpenTag ("components");
		l_cPos = m_cmComponentMap.GetStartPosition ();
		while (l_cPos)
		{
			m_cmComponentMap.GetNextAssoc (l_cPos, l_csCompName, l_csCount);
			l_csStr.Format ("qty=\"%s\"", l_csCount);
			l_cParser.WriteAttributeTag ("component", l_csStr, l_csCompName);
		}
		l_cParser.WriteCloseTag ("components");

		l_cParser.WriteCloseTag ("order");

		l_cParser.CloseFile ();

		m_csCurrentOrderFilename = a_csFilename;
		CAppData::m_bOrderChanged = false;
		l_bResult = true;
	}

	return (l_bResult);
}

bool CAppData::ExportOrder(CString &a_csFilename)
{
	POSITION l_cPos;
	COrderItem l_cOrderItem;
	CItemTech l_cItemTech;
	POSITION l_TechPos;
	XMLParser l_cParser;
	CString l_csTier;
	CString l_csCompName;
	CString l_csCount;
	CString l_csStr;
	bool l_bResult = false;

	OptimiseStoredComponents ();

	if (l_cParser.WriteFile (a_csFilename))
	{
		l_cParser.WriteOpenTag ("order");
		l_cParser.WriteTag ("order-format", "1.1");
		l_cParser.WriteOpenTag ("generator");
        l_cParser.WriteTag ("application", "HCC");
		l_cParser.WriteTag ("version", cAppData_Version);
		l_cParser.WriteTag ("database", CAppData::m_csDatabaseRevision);
		l_cParser.WriteCloseTag ("generator");

		l_cParser.WriteOpenTag ("groups");
		l_cPos = m_cOrderGroups.GetHeadPosition ();
		while (l_cPos)
		{
			l_cParser.WriteTag ("group", m_cOrderGroups.GetNext (l_cPos));
		}
		l_cParser.WriteCloseTag ("groups");

		l_cPos = m_clOrderList.GetHeadPosition ();
		while (l_cPos)
		{
		    l_bResult = true;
			l_cOrderItem = m_clOrderList.GetNext (l_cPos);

			l_cParser.WriteOpenTag ("item");
			l_cParser.WriteTag ("item-name", l_cOrderItem.m_csItemName);
			l_cParser.WriteTag ("item-group", l_cOrderItem.m_csOrderGroup);
			l_cParser.WriteTag ("item-formula", l_cOrderItem.m_csFormulaName);
			//l_cParser.WriteTag ("item-category", l_cOrderItem.m_csCategory);
			l_cParser.WriteTag ("item-tierlvlname", l_cOrderItem.m_csTierName);
			l_cParser.WriteTag ("item-qty", l_cOrderItem.m_iQty);

			l_cParser.WriteOpenTag ("techs");

			l_TechPos = l_cOrderItem.m_clTechList.GetHeadPosition ();
			while (l_TechPos)
			{
				l_cItemTech = l_cOrderItem.m_clTechList.GetNext (l_TechPos);

				l_csTier.Format ("tier=\"%s\"", l_cItemTech.m_csTierName);
				l_cParser.WriteAttributeTag ("tech", l_csTier, l_cItemTech.m_csTechName);
			}

			l_cParser.WriteCloseTag ("techs");

			l_cParser.WriteCloseTag ("item");
		}

		l_cParser.WriteOpenTag ("components");
		l_cPos = m_cmComponentMap.GetStartPosition ();
		while (l_cPos)
		{
		    l_bResult = true;
			m_cmComponentMap.GetNextAssoc (l_cPos, l_csCompName, l_csCount);
			l_csStr.Format ("qty=\"%s\"", l_csCount);
			l_cParser.WriteAttributeTag ("component", l_csStr, l_csCompName);
		}
		l_cParser.WriteCloseTag ("components");

		l_cParser.WriteCloseTag ("order");

		l_cParser.CloseFile ();
	}

	return (l_bResult);
}

bool CAppData::ExportProfile(CString &a_csFilename)
{
	POSITION l_cPos;
	CBonus *l_cpBonus;
	CSkill *l_cpSkill;
	XMLParser l_cParser;
	CString l_csStr;
	bool l_bResult = false;

    if (CAppData::m_csCurrentProfileType != "Local")
    {
        return true;
    }

	if (l_cParser.WriteFile (a_csFilename))
	{

        l_cParser.WriteOpenTag ("profile");
        l_cParser.WriteTag ("profile-format", "1.1");
        l_cParser.WriteTag ("profile-name", CAppData::m_cpCurrentProfile->m_csProfileName);
        l_cParser.WriteTag ("profile-server", CAppData::m_cpCurrentProfile->m_csProfileServer);
        l_cParser.WriteTag ("profile-email", CAppData::m_cpCurrentProfile->m_csProfileEmail);
        l_cParser.WriteOpenTag ("generator");
        l_cParser.WriteTag ("application", "HCC");
		l_cParser.WriteTag ("version", cAppData_Version);
		l_cParser.WriteTag ("database", CAppData::m_csDatabaseRevision);
		l_cParser.WriteCloseTag ("generator");

        l_cParser.WriteOpenTag ("statistics");
        l_cPos = CAppData::m_cpCurrentProfile->m_clStatisticList.GetHeadPosition ();
        while (l_cPos)
        {
            l_cpBonus = CAppData::m_cpCurrentProfile->m_clStatisticList.GetNext (l_cPos);
            l_csStr.Format ("value=\"%d\"", l_cpBonus->m_iValue);
            l_cParser.WriteAttributeTag ("statistic", l_csStr, l_cpBonus->m_csBonusName);
        }
        l_cParser.WriteCloseTag ("statistics");

        l_cParser.WriteOpenTag ("adventurelevels");
        l_cPos = CAppData::m_cpCurrentProfile->m_clAdventureSchoolList.GetHeadPosition ();
        while (l_cPos)
        {
            l_cParser.WriteOpenTag ("adventure");
            l_cpSkill = CAppData::m_cpCurrentProfile->m_clAdventureSchoolList.GetNext (l_cPos);
            l_cParser.WriteTag ("adventure-name", l_cpSkill->m_csSkillName);
            l_cParser.WriteTag ("adventure-level", l_cpSkill->m_iSkillValue);
            l_cParser.WriteCloseTag ("adventure");
        }
        l_cParser.WriteCloseTag ("adventurelevels");

        l_cParser.WriteOpenTag ("adventureskills");
        l_cPos = CAppData::m_cpCurrentProfile->m_clAdventureSkillsList.GetHeadPosition ();
        while (l_cPos)
        {
            l_cpBonus = CAppData::m_cpCurrentProfile->m_clAdventureSkillsList.GetNext (l_cPos);
            l_csStr.Format ("level=\"%d\"", l_cpBonus->m_iValue);
            l_cParser.WriteAttributeTag ("adventureskill", l_csStr, l_cpBonus->m_csBonusName);
        }
        l_cParser.WriteCloseTag ("adventureskills");

        l_cParser.WriteOpenTag ("craftlevels");
        l_cPos = CAppData::m_cpCurrentProfile->m_clCraftSchoolList.GetHeadPosition ();
        while (l_cPos)
        {
            l_cParser.WriteOpenTag ("craft");
            l_cpSkill = CAppData::m_cpCurrentProfile->m_clCraftSchoolList.GetNext (l_cPos);
            l_cParser.WriteTag ("craft-name", l_cpSkill->m_csSkillName);
            l_cParser.WriteTag ("craft-level", l_cpSkill->m_iSkillValue);
            l_cParser.WriteTag ("craft-worktiermin", l_cpSkill->m_iWorkTierMin);
            l_cParser.WriteTag ("craft-worktiermax", l_cpSkill->m_iWorkTierMax);
            l_cParser.WriteCloseTag ("craft");
        }
        l_cParser.WriteCloseTag ("craftlevels");

        l_cParser.WriteOpenTag ("craftskills");
        l_cPos = CAppData::m_cpCurrentProfile->m_clCraftSkillsList.GetHeadPosition ();
        while (l_cPos)
        {
            l_cpBonus = CAppData::m_cpCurrentProfile->m_clCraftSkillsList.GetNext (l_cPos);
            l_csStr.Format ("level=\"%d\"", l_cpBonus->m_iValue);
            l_cParser.WriteAttributeTag ("craftskill", l_csStr, l_cpBonus->m_csBonusName);
        }
        l_cParser.WriteCloseTag ("craftskills");

        l_cParser.WriteCloseTag ("profile");

        l_cParser.CloseFile ();

        l_bResult = true;
	}

	return (l_bResult);
}

bool CAppData::LoadOrder(CString &a_csFilename)
{
	bool l_bResult = false;
	CFormula *l_cpFormula = NULL;
	COrderItem l_cOrderItem;
	CItemTech l_cItemTech;
	XMLParser l_cParser;
	XMLTag l_cRootTag ("#ROOT#");
	XMLTag l_cOrderTag ("order");
	XMLTag l_cGroupTag ("groups");
	XMLTag l_cItemTag ("item");
	XMLTag l_cTechTag ("techs");
	XMLTag l_cComponentTag ("components");
	CString l_cGroupName;
	CString l_csTierName;
	CString l_csCompName;
	CString l_csCount;
	CString l_csVersion = "0.0";

	m_clOrderList.RemoveAll ();
	m_cOrderGroups.RemoveAll ();

	l_cParser.OpenFile (a_csFilename);
	m_cmComponentMap.RemoveAll ();

	// Should be only one order Tag
	if (l_cOrderTag.GetNextTag (l_cParser, l_cRootTag))
	{
		if (l_cOrderTag.GetTagValue (l_cParser, (CString) "order-format", l_csVersion))
		{
		}

		if (l_csVersion != "1.0" && l_csVersion != "1.1")
		{
			return (false);
		}

		if (l_cGroupTag.GetNextTag (l_cParser, l_cOrderTag))
		{
			while (l_cGroupTag.GetRepeatingTagValue (l_cParser, (CString) "group", l_cGroupName))
			{
				AddOrderGroup (l_cGroupName);
			}
		}

		while (l_cItemTag.GetNextTag (l_cParser, l_cOrderTag))
		{
			l_cItemTag.GetTagValue (l_cParser, (CString) "item-name", l_cOrderItem.m_csItemName);
			l_cItemTag.GetTagValue (l_cParser, (CString) "item-group", l_cOrderItem.m_csOrderGroup);
			l_cItemTag.GetTagValue (l_cParser, (CString) "item-formula", l_cOrderItem.m_csFormulaName);
			//l_cItemTag.GetTagValue (l_cParser, (CString) "item-category", l_cOrderItem.m_csCategory);
			l_cItemTag.GetTagValue (l_cParser, (CString) "item-tierlvlname", l_cOrderItem.m_csTierName);
			l_cItemTag.GetTagValue (l_cParser, (CString) "item-qty", l_cOrderItem.m_iQty);
			l_cOrderItem.AssignId ();
			l_cOrderItem.m_clTechList.RemoveAll();

			if (l_cTechTag.GetNextTag (l_cParser, l_cItemTag))
			{
				while (l_cTechTag.GetRepeatingDoubleTagValue (l_cParser, (CString) "tech", l_csTierName, l_cItemTech.m_csTechName))
				{
					l_cItemTech.m_csCategory = cNo_Filter;
					l_cItemTech.m_csTierName = l_csTierName;
					l_cOrderItem.m_clTechList.AddTail (l_cItemTech);
				}
			}

			if (CAppData::FindFormula (cNo_Filter, l_cOrderItem.m_csFormulaName, &l_cpFormula))
			{
				l_cOrderItem.m_csCategory = l_cpFormula->m_csCategory;
			}
			else
			{
				l_cOrderItem.m_csCategory = cNo_Filter;
			}

			m_clOrderList.AddTail (l_cOrderItem);
		}

		if (l_cComponentTag.GetNextTag (l_cParser, l_cOrderTag))
		{
			while (l_cComponentTag.GetRepeatingDoubleTagValue (l_cParser, (CString) "component", l_csCount, l_csCompName))
			{
				m_cmComponentMap.SetAt (l_csCompName, l_csCount);
			}
		}

		l_bResult = true;
		m_csCurrentOrderFilename = a_csFilename;
		CAppData::m_bOrderChanged = false;
	}

	return (l_bResult);
}

CAppData::WriteCache(CString &a_csPath)
{
	CString l_csLine;
	CFormulaSet *l_cpFormulaSet;
	CTechSet *l_cpTechSet;
	CComponent *l_cpComponent;
	CSchoolWizard *l_cpSchoolWizard;
	CString l_csConfigFile = a_csPath + cFile_App_ConfigCache;
	CString l_csConfigFormIcons = a_csPath + cFile_App_IconCache;

	TRY
	{
		CStdioFile l_cFormIconFile (l_csConfigFormIcons, CFile::modeCreate|CFile::modeWrite|CFile::typeBinary);
		CArchive l_cFormIconArchive (&l_cFormIconFile, CArchive::store);
		m_cpIconImages->m_cImageList.Write (&l_cFormIconArchive);
		l_cFormIconArchive.Close ();

		CStdioFile l_cFile (l_csConfigFile, CFile::modeCreate|CFile::modeWrite|CFile::typeText);

		l_cFile.WriteString (cAppData_CacheHeader + "\n");
		l_csLine.Format ("%d|%d|%d|%d\n", m_clFormulaSetList.GetCount (),
							  m_clTechSetList.GetCount (), m_clComponentList.GetCount (), m_clSchoolWizardList.GetCount ());
		l_cFile.WriteString (l_csLine);

		POSITION l_Pos = m_clFormulaSetList.GetHeadPosition ();
		while (l_Pos)
		{
			l_cpFormulaSet = m_clFormulaSetList.GetNext (l_Pos);
			l_cpFormulaSet->WriteToFile (l_cFile);
		}

		l_Pos = m_clTechSetList.GetHeadPosition ();
		while (l_Pos)
		{
			l_cpTechSet = m_clTechSetList.GetNext (l_Pos);
			l_cpTechSet->WriteToFile (l_cFile);
		}

		l_Pos = m_clComponentList.GetHeadPosition ();
		while (l_Pos)
		{
			l_cpComponent = m_clComponentList.GetNext (l_Pos);
			l_cpComponent->WriteToFile (l_cFile);
		}

		l_Pos = m_clSchoolWizardList.GetHeadPosition ();
		while (l_Pos)
		{
			l_cpSchoolWizard = m_clSchoolWizardList.GetNext (l_Pos);
			l_cpSchoolWizard->WriteToFile (l_cFile);
		}

		l_cFile.Close ();
	}
	CATCH( CFileException, e )
	{
	}
	END_CATCH

}

bool CAppData::LoadCache(CString &a_csPath)
{
	CString l_csLine;
	CFormulaSet *l_cpFormulaSet;
	CTechSet *l_cpTechSet;
	CComponent *l_cpComponent;
	CSchoolWizard *l_cpSchoolWizard;
	CString l_csConfigFile = a_csPath + cFile_App_ConfigCache;
	CString l_csConfigFormIcons = a_csPath + cFile_App_IconCache;
	bool l_bSuccess = true;
	int l_iTokenOffset = 0;
	int l_iFormCount = 0;
	int l_iTechCount = 0;
	int l_iCompCount = 0;
	int l_iWizardCount = 0;
	CFileHandler l_cFileHandler;

	if (!m_bEnableCache)
	{
		return (false);
	}

	ClearCache (true);
	ClearImageCache();

	TRY
	{
		CStdioFile l_cFormIconFile (l_csConfigFormIcons, CFile::modeRead|CFile::typeBinary);
		CArchive l_cFormIconArchive (&l_cFormIconFile, CArchive::load);
		l_bSuccess = l_bSuccess && m_cpIconImages->LoadFromArchive (l_cFormIconArchive);
		l_cFormIconArchive.Close ();

		CStdioFile l_cFile (l_csConfigFile, CFile::modeRead|CFile::typeText);

		l_cFile.ReadString (l_csLine);
		if (l_csLine == cAppData_CacheHeader)
		{
			l_cFile.ReadString (l_csLine);
			l_bSuccess = l_bSuccess && l_cFileHandler.ReadToken (l_csLine, l_iTokenOffset, l_iFormCount);
			l_bSuccess = l_bSuccess && l_cFileHandler.ReadToken (l_csLine, l_iTokenOffset, l_iTechCount);
			l_bSuccess = l_bSuccess && l_cFileHandler.ReadToken (l_csLine, l_iTokenOffset, l_iCompCount);
			l_bSuccess = l_bSuccess && l_cFileHandler.ReadToken (l_csLine, l_iTokenOffset, l_iWizardCount);

			if (l_bSuccess)
			{
				while (l_iFormCount--)
				{
					l_cpFormulaSet = new CFormulaSet();
					l_bSuccess = l_bSuccess && l_cpFormulaSet->ReadFromFile (l_cFile);
					m_clFormulaSetList.AddTail (l_cpFormulaSet);

					if (l_cpFormulaSet->m_csCategory == cFormulaCategory_Resources)
					{
						CAppData::m_cResourceFormulaSetList.AddTail (l_cpFormulaSet);
					}
				}
			}

			if (l_bSuccess)
			{
				while (l_iTechCount--)
				{
					l_cpTechSet = new CTechSet();
					l_bSuccess = l_bSuccess && l_cpTechSet->ReadFromFile (l_cFile);
					m_clTechSetList.AddTail (l_cpTechSet);
				}
			}

			if (l_bSuccess)
			{
				while (l_iCompCount--)
				{
					l_cpComponent = new CComponent();
					l_bSuccess = l_bSuccess && l_cpComponent->ReadFromFile (l_cFile);
					m_clComponentList.AddTail (l_cpComponent);
				}
			}

			if (l_bSuccess)
			{
				while (l_iWizardCount--)
				{
					l_cpSchoolWizard = new CSchoolWizard();
					l_bSuccess = l_bSuccess && l_cpSchoolWizard->ReadFromFile (l_cFile);
					m_clSchoolWizardList.AddTail (l_cpSchoolWizard);
				}
			}
		}
		else
		{
			l_bSuccess = false;
		}

		l_cFile.Close ();
	}
	CATCH( CFileException, e )
	{
		l_bSuccess = false;
	}
	END_CATCH

	return (l_bSuccess);
}


CAppData::ClearCache(bool a_bFull)
{
	CFormulaSet *l_cpFormulaSet;
	CTechSet *l_cpTechSet;
	CComponent *l_cpComponent;
	CProfile *l_cpProfile;
	CSchoolWizard *l_cpSchoolWizard;
	CCategory *l_cpCategory;
	CSubCategory *l_cpSubCategory;

	ClearImageCache();
	m_clFormulaCategoryList.RemoveAll ();
	m_clTechCategoryList.RemoveAll ();
	m_clOrderList.RemoveAll ();
	m_cOrderGroups.RemoveAll ();
	m_csCurrentFormulaTierName.Empty ();
	m_csCurrentTechTierName.Empty ();
	m_cFormFilter.Empty();
	m_cFormClassFilter.Empty();
	m_cFormClassFilterType.Empty();

	m_cpFormFilterTech = NULL;
	m_cpCurrentFormula = NULL;
	m_cpCurrentTech = NULL;
	m_iCurrentOrderId = 0;
	m_bEditMode = false;
	m_cResourceFormulaSetList.RemoveAll ();

	POSITION l_Pos = m_clFormulaSetList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpFormulaSet = m_clFormulaSetList.GetNext (l_Pos);
		l_cpFormulaSet->Destroy (true);
		delete (l_cpFormulaSet);
	}
	m_clFormulaSetList.RemoveAll ();

	l_Pos = m_clTechSetList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpTechSet = m_clTechSetList.GetNext (l_Pos);
		l_cpTechSet->Destroy (true);
		delete (l_cpTechSet);
	}
	m_clTechSetList.RemoveAll ();

	l_Pos = m_clComponentList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpComponent = m_clComponentList.GetNext (l_Pos);
		l_cpComponent->Destroy ();
		delete (l_cpComponent);
	}
	m_clComponentList.RemoveAll ();

	l_Pos = m_clSchoolWizardList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpSchoolWizard = m_clSchoolWizardList.GetNext (l_Pos);
		l_cpSchoolWizard->Destroy ();
		delete (l_cpSchoolWizard);
	}
	m_clSchoolWizardList.RemoveAll ();

	l_Pos = m_clCategoryList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpCategory = m_clCategoryList.GetNext (l_Pos);
		l_cpCategory->Destroy ();
		delete (l_cpCategory);
	}
	m_clCategoryList.RemoveAll ();

	l_Pos = m_clSubCategoryList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpSubCategory = m_clSubCategoryList.GetNext (l_Pos);
		l_cpSubCategory->Destroy ();
		delete (l_cpSubCategory);
	}
	m_clSubCategoryList.RemoveAll ();

	if (a_bFull)
	{
		l_Pos = m_clProfileList.GetHeadPosition ();
		while (l_Pos)
		{
			l_cpProfile = m_clProfileList.GetNext (l_Pos);
			l_cpProfile->Destroy ();
			delete (l_cpProfile);
		}
		m_clProfileList.RemoveAll ();

		m_cpCurrentProfile = NULL;
	}
}

//////////////////////////////////////////////////////////////////////
// Logic Routines
//////////////////////////////////////////////////////////////////////


CAppData::AddFormulaCategory(CString a_csCategory)
{
	POSITION l_Pos;
	POSITION l_PrevPos;
	bool l_bAdded = false;
	CString l_csListCategory;

	l_Pos = m_clFormulaCategoryList.GetHeadPosition ();

	while ((!l_bAdded) && (l_Pos))
	{
		l_PrevPos = l_Pos;
		l_csListCategory = m_clFormulaCategoryList.GetNext (l_Pos);
		if (l_csListCategory == a_csCategory)
		{
			l_bAdded = true;
		}
		else if (l_csListCategory > a_csCategory)
		{
			m_clFormulaCategoryList.InsertBefore (l_PrevPos, a_csCategory);
			l_bAdded = true;
		}
	}

	if (!l_bAdded)
	{
			m_clFormulaCategoryList.AddTail (a_csCategory);
	}
}

CAppData::AddTechCategory(CString a_csCategory)
{
	POSITION l_Pos;
	POSITION l_PrevPos;
	bool l_bAdded = false;
	CString l_csListCategory;

	l_Pos = m_clTechCategoryList.GetHeadPosition ();

	while ((!l_bAdded) && (l_Pos))
	{
		l_PrevPos = l_Pos;
		l_csListCategory = m_clTechCategoryList.GetNext (l_Pos);
		if (l_csListCategory == a_csCategory)
		{
			l_bAdded = true;
		}
		else if (l_csListCategory > a_csCategory)
		{
			m_clTechCategoryList.InsertBefore (l_PrevPos, a_csCategory);
			l_bAdded = true;
		}
	}

	if (!l_bAdded)
	{
			m_clTechCategoryList.AddTail (a_csCategory);
	}
}

CAppData::CacheInternalData()
{
	POSITION l_Pos;
	CFormulaSet l_cFormulaSet;
	CTechSet *l_cpTechSet;

	l_Pos = m_clFormulaSetList.GetHeadPosition ();

	while (l_Pos)
	{
		l_cFormulaSet = m_clFormulaSetList.GetNext (l_Pos);
		AddFormulaCategory (l_cFormulaSet.m_csCategory);
	}

	l_Pos = m_clTechSetList.GetHeadPosition ();

	while (l_Pos)
	{
		l_cpTechSet = m_clTechSetList.GetNext (l_Pos);
		AddTechCategory (l_cpTechSet->m_csCategory);
	}
}

bool CAppData::FindFormula(CString a_csCategory, CString a_csName, CFormula **a_cpFormula)
{
	bool l_bFound = false;
	POSITION l_SetPos;
	POSITION l_Pos;
	CFormulaSet *l_cpFormulaSet;
	CFormula *l_cpFormula;

	l_SetPos = m_clFormulaSetList.GetHeadPosition ();

	while (l_SetPos)
	{
		l_cpFormulaSet = m_clFormulaSetList.GetNext (l_SetPos);
		if ((l_cpFormulaSet->m_csCategory == a_csCategory) ||
			 (a_csCategory == cNo_Filter) ||
			 (a_csCategory == cCustom_Filter))
		{
			l_Pos = l_cpFormulaSet->m_clFormulaList.GetHeadPosition ();

			while (l_Pos)
			{
				l_cpFormula = l_cpFormulaSet->m_clFormulaList.GetNext (l_Pos);

				if (l_cpFormula->m_csName == a_csName)
				{
					*a_cpFormula = l_cpFormula;
					return (true);
				}
			}
		}
	}
	return (l_bFound);
}

bool CAppData::FindResourceFormula(CString a_csName, CFormula **a_cpFormula)
{
	bool l_bFound = false;
	POSITION l_SetPos;
	POSITION l_Pos;
	CFormulaSet *l_cpFormulaSet;
	CFormula *l_cpFormula;

	l_SetPos = m_cResourceFormulaSetList.GetHeadPosition ();

	while (l_SetPos)
	{
		l_cpFormulaSet = m_cResourceFormulaSetList.GetNext (l_SetPos);
		l_Pos = l_cpFormulaSet->m_clFormulaList.GetHeadPosition ();

		while (l_Pos)
		{
			l_cpFormula = l_cpFormulaSet->m_clFormulaList.GetNext (l_Pos);

			if (l_cpFormula->m_csName == a_csName)
			{
				*a_cpFormula = l_cpFormula;
				return (true);
			}
		}
	}
	return (l_bFound);
}

bool CAppData::FindResourceFormulaTier(CString a_csResourceName,  CFormula **a_cpFormula, CFormulaTier **a_cpFormulaTier)
{
	bool l_bFound = false;
	POSITION l_SetPos;
	POSITION l_TierPos;
	POSITION l_Pos;
	CFormulaSet *l_cpFormulaSet;
	CFormula *l_cpFormula;
	CFormulaTier *l_cpFormulaTier;

	l_SetPos = m_cResourceFormulaSetList.GetHeadPosition ();

	while (l_SetPos)
	{
		l_cpFormulaSet = m_cResourceFormulaSetList.GetNext (l_SetPos);
		l_Pos = l_cpFormulaSet->m_clFormulaList.GetHeadPosition ();

		while (l_Pos)
		{
			l_cpFormula = l_cpFormulaSet->m_clFormulaList.GetNext (l_Pos);
			l_TierPos = l_cpFormula->m_clFormulaTierList.GetHeadPosition ();

			while (l_TierPos)
			{
				l_cpFormulaTier = l_cpFormula->m_clFormulaTierList.GetNext (l_TierPos);
				if (l_cpFormulaTier->m_csName == a_csResourceName)
				{
					*a_cpFormula = l_cpFormula;
					*a_cpFormulaTier = l_cpFormulaTier;
					return (true);
				}
			}

		}
	}
	return (l_bFound);
}

bool CAppData::FindTech(CString a_csCategory, CString a_csName, CTech **a_cpTech)
{
	bool l_bFound = false;
	POSITION l_SetPos;
	POSITION l_Pos;
	CTechSet *l_cpTechSet;
	CTech *l_cpTech;

	l_SetPos = m_clTechSetList.GetHeadPosition ();

	while (l_SetPos)
	{
		l_cpTechSet = m_clTechSetList.GetNext (l_SetPos);
		if ((l_cpTechSet->m_csCategory == a_csCategory) ||
			 (a_csCategory == cNo_Filter) ||
			 (a_csCategory == cCustom_Filter))
		{
			l_Pos = l_cpTechSet->m_clTechList.GetHeadPosition ();

			while (l_Pos)
			{
				l_cpTech = l_cpTechSet->m_clTechList.GetNext (l_Pos);

				if (l_cpTech->m_csName == a_csName)
				{
					*a_cpTech = l_cpTech;
					return (true);
				}
			}
		}
	}
	return (l_bFound);
}

bool CAppData::FindFormulaTier(CString a_csCategory, CString a_csName, CString &a_csTier, CFormulaTier **a_cpFormulaTier)
{
	CFormula *l_cpFormula;

	if (FindFormula (a_csCategory, a_csName, &l_cpFormula))
	{
		if (l_cpFormula->FindFormulaTier (a_csTier, a_cpFormulaTier))
		{
			return (true);
		}
	}

	return (false);
}

bool CAppData::FindTechTier(CString a_csCategory, CString a_csName, CString &a_csTier, CTechTier **a_cpTechTier)
{
	CTech *l_cpTech = NULL;

	if (FindTech (a_csCategory, a_csName, &l_cpTech))
	{
		if (l_cpTech->FindTechTier (a_csTier, a_cpTechTier))
		{
			return (true);
		}
	}

	return (false);
}

int CAppData::GetTierLevel(CString a_csTier)
{
	if (a_csTier == "Tier I")
	{
		return (1);
	}
	else if (a_csTier == "Tier II")
	{
		return (2);
	}
	else if (a_csTier == "Tier III")
	{
		return (3);
	}
	else if (a_csTier == "Tier IV")
	{
		return (4);
	}
	else if (a_csTier == "Tier V")
	{
		return (5);
	}
	else if (a_csTier == "Tier VI")
	{
		return (6);
	}
	else if (a_csTier == "Tier VII")
	{
		return (7);
	}
	else if (a_csTier == "Tier VIII")
	{
		return (8);
	}
	else if (a_csTier == "Tier IX")
	{
		return (9);
	}
	else if (a_csTier == "Tier X")
	{
		return (10);
	}

	return (0);
}

CString CAppData::GetTierName(int a_iTier)
{
	switch (a_iTier)
	{
		case (1) :
		{
			return ("Tier I");
			break;
		}
		case (2) :
		{
			return ("Tier II");
			break;
		}
		case (3) :
		{
			return ("Tier III");
			break;
		}
		case (4) :
		{
			return ("Tier IV");
			break;
		}
		case (5) :
		{
			return ("Tier V");
			break;
		}
		case (6) :
		{
			return ("Tier VI");
			break;
		}
		case (7) :
		{
			return ("Tier VII");
			break;
		}
		case (8) :
		{
			return ("Tier VIII");
			break;
		}
		case (9) :
		{
			return ("Tier IX");
			break;
		}
		case (10) :
		{
			return ("Tier X");
			break;
		}
		default :
		{
			return ("Default");
			break;
		}
	}
	return ("???");
}

bool CAppData::FindOrderItem(int a_iId, COrderItem &a_cOrderItem)
{
	bool l_bFound = false;
	POSITION l_Pos;
	COrderItem l_cOrderItem;

	l_Pos = m_clOrderList.GetHeadPosition ();

	while (l_Pos)
	{
		l_cOrderItem = m_clOrderList.GetNext (l_Pos);
		if (l_cOrderItem.m_iId == a_iId)
		{
			a_cOrderItem = l_cOrderItem;
			return (true);
		}
	}
	return (l_bFound);
}

CAppData::UpdateOrderItem(COrderItem &a_cOrderItem)
{
	POSITION l_Pos;
	POSITION l_PrevPos;
	COrderItem l_cOrderItem;

	l_Pos = m_clOrderList.GetHeadPosition ();

	while (l_Pos)
	{
		l_PrevPos = l_Pos;
		l_cOrderItem = m_clOrderList.GetNext (l_Pos);
		if (l_cOrderItem.m_iId == a_cOrderItem.m_iId)
		{
			m_clOrderList.SetAt (l_PrevPos, a_cOrderItem);
		}
	}
}

CAppData::UpdateOrderGroup(CString &a_csOldGroup, CString &a_csNewGroup)
{
	POSITION l_Pos;
	POSITION l_PrevPos;
	CString l_csOrderGroup;
	COrderItem l_cOrderItem;

	l_Pos = m_cOrderGroups.GetHeadPosition ();

	while (l_Pos)
	{
		l_PrevPos = l_Pos;
		l_csOrderGroup = m_cOrderGroups.GetNext (l_Pos);
		if (l_csOrderGroup == a_csOldGroup)
		{
			m_cOrderGroups.SetAt (l_PrevPos, a_csNewGroup);
		}
	}

	l_Pos = m_clOrderList.GetHeadPosition ();

	while (l_Pos)
	{
		l_PrevPos = l_Pos;
		l_cOrderItem = m_clOrderList.GetNext (l_Pos);
		if (l_cOrderItem.m_csOrderGroup == a_csOldGroup)
		{
			l_cOrderItem.m_csOrderGroup = a_csNewGroup;
			m_clOrderList.SetAt (l_PrevPos, l_cOrderItem);
		}
	}
}


CAppData::DeleteOrderGroup(CString &a_csGroup)
{
	POSITION l_Pos;
	POSITION l_PrevPos;
	CString l_csOrderGroup;
	COrderItem l_cOrderItem;

	l_Pos = m_cOrderGroups.GetHeadPosition ();

	while (l_Pos)
	{
		l_PrevPos = l_Pos;
		l_csOrderGroup = m_cOrderGroups.GetNext (l_Pos);
		if (l_csOrderGroup == a_csGroup)
		{
			m_cOrderGroups.RemoveAt (l_PrevPos);
		}
	}

	l_Pos = m_clOrderList.GetHeadPosition ();

	while (l_Pos)
	{
		l_PrevPos = l_Pos;
		l_cOrderItem = m_clOrderList.GetNext (l_Pos);
		if (l_cOrderItem.m_csOrderGroup == a_csGroup)
		{
			m_clOrderList.RemoveAt (l_PrevPos);
		}
	}
}

CAppData::DeleteOrderItem(int l_iItemId)
{
	POSITION l_Pos;
	POSITION l_PrevPos;
	COrderItem l_cOrderItem;

	l_Pos = m_clOrderList.GetHeadPosition ();

	while (l_Pos)
	{
		l_PrevPos = l_Pos;
		l_cOrderItem = m_clOrderList.GetNext (l_Pos);
		if (l_cOrderItem.m_iId == l_iItemId)
		{
			m_clOrderList.RemoveAt (l_PrevPos);
			CAppData::m_cItemCreationWnd.ResetItemEdit();
		}
	}
}

CAppData::AddOrderGroup(CString &a_csOrderGroup)
{
	POSITION l_Pos;
	CString l_csOrderGroup;
	bool l_bFound = false;

	l_Pos = m_cOrderGroups.GetHeadPosition ();

	while (l_Pos)
	{
		l_csOrderGroup = m_cOrderGroups.GetNext (l_Pos);
		if (l_csOrderGroup == a_csOrderGroup)
		{
			l_bFound = true;
		}
	}

	if (!l_bFound)
	{
		m_cOrderGroups.AddTail (a_csOrderGroup);
	}
}


int CAppData::DetermineTechLimit(int a_iTier)
{
	return ((a_iTier + 1) / 2);
}


bool CAppData::FindComponent(CString &a_csCompName, CComponent **a_cpComponent)
{
	CComponent *l_cpComponent;
	POSITION l_Pos;

	l_Pos = m_clComponentList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpComponent = CAppData::m_clComponentList.GetNext (l_Pos);
		if (l_cpComponent->m_csComponentName == a_csCompName)
		{
			*a_cpComponent = l_cpComponent;
			return (true);
		}
	}

	return (false);
}

bool CAppData::FindSubCategory(CString &a_csSubCategory, CSubCategory **a_cpSubCategory)
{
	CSubCategory *l_cpSubCategory;
	POSITION l_Pos;

	l_Pos = m_clSubCategoryList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpSubCategory = CAppData::m_clSubCategoryList.GetNext (l_Pos);
		if (l_cpSubCategory->m_csSubCategoryName == a_csSubCategory)
		{
			*a_cpSubCategory = l_cpSubCategory;
			return (true);
		}
	}

	return (false);
}

bool CAppData::FindProfile(CString &a_csProfileName, CString &a_csServerName, CProfile **a_cpProfile)
{
	CProfile *l_cpProfile;
	POSITION l_Pos;

	l_Pos = m_clProfileList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpProfile = CAppData::m_clProfileList.GetNext (l_Pos);
		if ((l_cpProfile->m_csProfileName == a_csProfileName) &&
			 (l_cpProfile->m_csProfileServer == a_csServerName))
		{
			*a_cpProfile = l_cpProfile;
			return (true);
		}
	}

	return (false);
}

int CAppData::CalculateEfficiency(CItemResource *a_cpResource, CProfile *a_cpProfile, int a_iSkillAdjust)
{
	double l_fRatio;
	double l_fAmountRange;
	int l_iSkillRange;
	int l_iSkillAdjust;
	int l_iAmount = 0;
	int l_iProfileSkill;
	int l_iUnitMultiplier;

	if (a_cpProfile)
	{
		if (a_cpResource->m_iUnits == 0)
		{
			l_iUnitMultiplier = 1;
		}
		else
		{
			l_iUnitMultiplier  = a_cpResource->m_iUnits;
		}

		l_iProfileSkill = a_cpProfile->FindCraftSkill (a_cpResource->m_csSkill);

		if (l_iProfileSkill < (a_cpResource->m_iMinLvl + a_iSkillAdjust))
		{
			return (a_cpResource->m_iMinAmt * l_iUnitMultiplier);
		}

		if (l_iProfileSkill >= (a_cpResource->m_iOptLvl + a_iSkillAdjust))
		{
			return (a_cpResource->m_iOptAmt * l_iUnitMultiplier);
		}

		l_iSkillRange = a_cpResource->m_iOptLvl - a_cpResource->m_iMinLvl;
		l_iSkillAdjust = l_iProfileSkill - (a_cpResource->m_iMinLvl + a_iSkillAdjust);
		l_fRatio = (double) l_iSkillAdjust / (double) l_iSkillRange;

		l_fAmountRange = (double) a_cpResource->m_iMinAmt - a_cpResource->m_iOptAmt;
		l_iAmount = (a_cpResource->m_iMinAmt - (int) (l_fRatio * l_fAmountRange)) * l_iUnitMultiplier;
	}

	return (l_iAmount);
}

int CAppData::CalculateEfficiencyPercentage(CItemResource *a_cpResource, CProfile *a_cpProfile, int a_iSkillAdjust)
{
	double l_fRatio = 0.0f;
	int l_iSkillRange;
	int l_iSkillAdjust;
	int l_iProfileSkill;

	if (a_cpProfile)
	{
		l_iProfileSkill = a_cpProfile->FindCraftSkill (a_cpResource->m_csSkill);
		l_iProfileSkill = a_cpProfile->FindCraftSkill (a_cpResource->m_csSkill);

		if (l_iProfileSkill < (a_cpResource->m_iMinLvl + a_iSkillAdjust))
		{
			return (-1);
		}

		if (l_iProfileSkill >= (a_cpResource->m_iOptLvl + a_iSkillAdjust))
		{
			return (100);
		}

		l_iSkillRange = a_cpResource->m_iOptLvl - a_cpResource->m_iMinLvl;
		l_iSkillAdjust = l_iProfileSkill - (a_cpResource->m_iMinLvl + a_iSkillAdjust);
		l_fRatio = (double) (l_iSkillAdjust * 100) / (double) l_iSkillRange;
	}

	return ((int) l_fRatio);
}

CAppData::RefreshWindows()
{
	CImageList *l_cImageList = NULL;

	if (CAppData::m_bEnableIcons)
	{
		l_cImageList = &m_cpIconImages->m_cImageList;
	}

	if (m_cOrderWnd.m_cWindowState.m_bLoaded)
	{
		m_cOrderWnd.m_cTechList.SetImageList (l_cImageList, LVSIL_SMALL);
		m_cOrderWnd.m_cItemTree.SetImageList (l_cImageList, TVSIL_NORMAL);
		m_cOrderWnd.DisplayOrder ();
	}

	if (m_cComponentWnd.m_cWindowState.m_bLoaded)
	{
		m_cComponentWnd.DrawCompTree ();
	}

	if (m_cItemCreationWnd.m_cWindowState.m_bLoaded)
	{
		m_cItemCreationWnd.m_cFormulaTree.SetImageList (l_cImageList, TVSIL_NORMAL);
		m_cItemCreationWnd.DrawFormulaList ();
	}

	if (m_cTechSelectionWnd.m_cWindowState.m_bLoaded)
	{
		m_cTechSelectionWnd.m_cTechTree.SetImageList (l_cImageList, TVSIL_NORMAL);
		m_cTechSelectionWnd.DrawTechList ();
	}

	if (m_cProfileWnd.m_cWindowState.m_bLoaded)
	{
		m_cProfileWnd.DrawProfileTree ();
	}
}

CAppData::ClearImageCache()
{
	if (m_cpIconImages)
	{
		delete (m_cpIconImages);
	}
	m_cpIconImages = new CImageStore ();
}

void CAppData::SetMenuItem(CMenu *a_pMenu, UINT a_iMenuItem, bool a_bCheck)
{
	if (a_bCheck)
	{
		a_pMenu->CheckMenuItem (a_iMenuItem,MF_BYCOMMAND |MF_CHECKED);
	}
	else
	{
		a_pMenu->CheckMenuItem (a_iMenuItem,MF_BYCOMMAND |MF_UNCHECKED);
	}
}

int CAppData::DetermineCurrentItemUsageOffset()
{
	int l_iOffset = 0;
	CItemTech l_cItemTech;
	CTechTier *l_cpTechTier;
	POSITION l_Pos = CAppData::m_cCurrentOrderItem.m_clTechList.GetHeadPosition ();

	while (l_Pos)
	{
		l_cItemTech = CAppData::m_cCurrentOrderItem.m_clTechList.GetNext (l_Pos);

		if (CAppData::FindTechTier (l_cItemTech.m_csCategory, l_cItemTech.m_csTechName, l_cItemTech.m_csTierName, &l_cpTechTier))
		{
			l_iOffset += l_cpTechTier->m_iUsageAdjust;
		}
	}
	return (l_iOffset);
}

CAppData::WriteUpdatesForDir(CString &a_csPath, XMLParser &a_cParser, int a_iBasePathLength)
{
	bool l_bSearching;
	bool l_bAdded = false;
	CString l_csSize;
	CFileFind l_cFileFind;

	l_bSearching = (l_cFileFind.FindFile (a_csPath + "\\*.*") != 0);
	while (l_bSearching)
	{
		l_bSearching = (l_cFileFind.FindNextFile () != 0);

		if (l_cFileFind.IsDirectory ())
		{
			if (l_cFileFind.IsDots () == false)
			{
				// Find in sub directories
				WriteUpdatesForDir (l_cFileFind.GetFilePath (), a_cParser, a_iBasePathLength);
			}
		}
		else
		{
			l_csSize.Format ("size=\"%d\"", l_cFileFind.GetLength());
			a_cParser.WriteAttributeTag ("file", l_csSize, l_cFileFind.GetFilePath().Mid (a_iBasePathLength));
		}

	}

	l_cFileFind.Close ();
}


CAppData::LaunchWebLink(CString &a_csPage)
{
	CString l_csLink;

	if (m_cmHelpLinks.Lookup (a_csPage, l_csLink))
	{
		ShellExecute (m_cpHCCDlg->m_hWnd, "open", l_csLink, NULL, NULL, SW_SHOWNORMAL );
	}
	else
	{
		AfxMessageBox ("Error - Cannot Find Requested Link", MB_ICONEXCLAMATION );
	}
}

CAppData::CopyToClipboard(CString &a_csStr)
{
	char FAR *str;
	HGLOBAL hg;
	int lenstr = a_csStr.GetLength () + 1;
	BOOL success = FALSE;

	if (hg = GlobalAlloc(GHND|GMEM_DDESHARE,lenstr))
	{
		str = (char *) GlobalLock(hg);
		if (str)
		{
			sprintf (str, "%s", a_csStr);
			GlobalUnlock(hg);

			if (OpenClipboard(m_cpHCCDlg->m_hWnd))
			{
				if (EmptyClipboard() )
				{
					if (SetClipboardData(CF_TEXT,hg))
					{
						success = TRUE;
					}
				}

				CloseClipboard();
			}
		}
	}

	if (!success)
	{
		GlobalFree(hg);
	}

}

CString CAppData::FormatOrderItemText(COrderItem &a_cOrderItem)
{
	CString l_csForm;
	CString l_csTechs;
	POSITION l_ItemPos;
	CTech *l_cpTech = NULL;
	CTechTier *l_cpTechTier = NULL;
	CFormulaTier *l_cpFormulaTier = NULL;
	CItemTech l_cItemTech;
	CString l_csMsg;

	if (CAppData::FindFormulaTier (a_cOrderItem.m_csCategory, a_cOrderItem.m_csFormulaName, a_cOrderItem.m_csTierName, &l_cpFormulaTier))
	{
		l_csForm.Format ("%d x %s", a_cOrderItem.m_iQty * l_cpFormulaTier->m_iBatchQty, l_cpFormulaTier->m_csName);
		l_csMsg = l_csForm;

		l_csTechs.Empty ();
		l_ItemPos = a_cOrderItem.m_clTechList.GetHeadPosition ();
		while (l_ItemPos)
		{
			l_cItemTech = a_cOrderItem.m_clTechList.GetNext (l_ItemPos);
			if (CAppData::FindTech (l_cItemTech.m_csCategory, l_cItemTech.m_csTechName, &l_cpTech))
			{
				if (l_cpTech->FindTechTier (l_cItemTech.m_csTierName, &l_cpTechTier))
				{
					if (l_csTechs.IsEmpty ())
					{
						l_csTechs = l_cpTechTier->m_csName;
					}
					else
					{
						l_csTechs = l_csTechs + ", " + l_cpTechTier->m_csName;
					}
				}
			}
		}

		if (!l_csTechs.IsEmpty ())
		{
			l_csMsg = l_csMsg + " (" + l_csTechs + ")";
		}
	}

	return (l_csMsg);
}

CString CAppData::FindBestMatchingTier(CFormula *a_cpFormula, CString &a_csTierName)
{
	CFormulaTier *l_cpFormulaTier = NULL;
	POSITION l_Pos;

	l_Pos = a_cpFormula->m_clFormulaTierList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpFormulaTier = a_cpFormula->m_clFormulaTierList.GetNext (l_Pos);
		if (l_cpFormulaTier->m_csTierName == a_csTierName)
		{
			return (l_cpFormulaTier->m_csTierName);
		}
	}

	if (l_cpFormulaTier)
	{
		return (l_cpFormulaTier->m_csTierName);
	}
	else
	{
		return ("");
	}
}

CAppData::Shutdown()
{
	SaveDefaults ();
	m_cOrderWnd.DestroyWindow ();
	m_cItemCreationWnd.DestroyWindow ();
	m_cTechSelectionWnd.DestroyWindow ();
	m_cComponentWnd.DestroyWindow ();
	m_cSkillLevelWnd.DestroyWindow ();
	m_cReportWnd.DestroyWindow ();
	m_cProfileWnd.DestroyWindow ();
}

CAppData::MinimiseApp()
{
	if (m_cOrderWnd.m_cWindowState.m_bLoaded)
	{
		m_cOrderWnd.ShowWindow (false);
	}

	if (m_cItemCreationWnd.m_cWindowState.m_bLoaded)
	{
		m_cItemCreationWnd.ShowWindow (false);
	}

	if (m_cTechSelectionWnd.m_cWindowState.m_bLoaded)
	{
		m_cTechSelectionWnd.ShowWindow (false);
	}

	if (m_cComponentWnd.m_cWindowState.m_bLoaded)
	{
		m_cComponentWnd.ShowWindow (false);
	}

	if (m_cSkillLevelWnd.m_cWindowState.m_bLoaded)
	{
		m_cSkillLevelWnd.ShowWindow (false);
	}

	if (m_cReportWnd.m_cWindowState.m_bLoaded)
	{
		m_cReportWnd.ShowWindow (false);
	}

	if (m_cProfileWnd.m_cWindowState.m_bLoaded)
	{
		m_cProfileWnd.ShowWindow (false);
	}

}

CAppData::RestoreApp()
{
	if (m_cOrderWnd.m_cWindowState.m_bVisible)
	{
		m_cOrderWnd.ShowWindow (true);
		m_cOrderWnd.SetWindowPos (&m_cOrderWnd.wndTop, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
	}

	if (m_cItemCreationWnd.m_cWindowState.m_bVisible)
	{
		m_cItemCreationWnd.ShowWindow (true);
		m_cItemCreationWnd.SetWindowPos (&m_cItemCreationWnd.wndTop, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
	}

	if (m_cTechSelectionWnd.m_cWindowState.m_bVisible)
	{
		m_cTechSelectionWnd.ShowWindow (true);
		m_cTechSelectionWnd.SetWindowPos (&m_cTechSelectionWnd.wndTop, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
	}

	if (m_cComponentWnd.m_cWindowState.m_bVisible)
	{
		m_cComponentWnd.ShowWindow (true);
		m_cComponentWnd.SetWindowPos (&m_cComponentWnd.wndTop, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
	}

	if (m_cSkillLevelWnd.m_cWindowState.m_bVisible)
	{
		m_cSkillLevelWnd.ShowWindow (true);
		m_cSkillLevelWnd.SetWindowPos (&m_cSkillLevelWnd.wndTop, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
	}

	if (m_cReportWnd.m_cWindowState.m_bVisible)
	{
		m_cReportWnd.ShowWindow (true);
		m_cReportWnd.SetWindowPos (&m_cReportWnd.wndTop, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
	}

	if (m_cProfileWnd.m_cWindowState.m_bVisible)
	{
		m_cProfileWnd.ShowWindow (true);
		m_cProfileWnd.SetWindowPos (&m_cProfileWnd.wndTop, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
	}

		m_cpHCCDlg->SetWindowPos (&m_cpHCCDlg->wndTop, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
}

CAppData::SetProfilesChangeState(bool a_bState)
{
	CAppData::m_bProfilesChanged = a_bState;

	if (m_cProfileWnd.m_cWindowState.m_bLoaded)
	{
		if (a_bState)
		{
			//m_cProfileWnd.SetWindowText ("Profile Manager");
			m_cProfileWnd.m_cUpdateButton.EnableWindow (true);
		}
		else
		{
			//m_cProfileWnd.SetWindowText ("Profile Manager");
			m_cProfileWnd.m_cUpdateButton.EnableWindow (false);
		}
	}
}

CAppData::SaveProfiles(bool a_bPrompt)
{
	bool l_bSave = true;
	POSITION l_Pos;
	CProfile *l_cpProfile;
	CString l_csFilePath;
	CString l_csMsg;

	if (m_bProfilesChanged)
	{
		if (a_bPrompt)
		{
			l_csMsg = "";
			l_Pos = m_clProfileList.GetHeadPosition ();
			while (l_Pos)
			{
				l_cpProfile = m_clProfileList.GetNext (l_Pos);
				if (l_cpProfile->m_bChanged)
				{
					if (l_csMsg.IsEmpty ())
					{
						l_csMsg = "Profile(s) '" + l_cpProfile->m_csProfileServer + ":" + l_cpProfile->m_csProfileName + "'";
					}
					else
					{
						l_csMsg = l_csMsg + ", '" + l_cpProfile->m_csProfileServer + ":" + l_cpProfile->m_csProfileName + "'";
					}
				}
			}

			l_csMsg = l_csMsg + " have been changed, do you want to save these changes?";
			if (AfxMessageBox (l_csMsg, MB_YESNO) == IDNO)
			{
				l_bSave = false;
			}
		}

		if (l_bSave)
		{
			l_Pos = m_clProfileList.GetHeadPosition ();
			while (l_Pos)
			{
				l_cpProfile = m_clProfileList.GetNext (l_Pos);
				if (l_cpProfile->m_bChanged)
				{
					if (l_cpProfile->m_csProfileType == cAppData_Profile_Defaults)
					{
						l_csFilePath = m_csAppBasePath + cPath_App_DefaultProfiles + "\\" + l_cpProfile->m_csProfileName + ".xml";
						l_cpProfile->SaveProfile (l_csFilePath);
					}
					else if (l_cpProfile->m_csProfileType == cAppData_Profile_Local)
					{
						l_csFilePath = m_csAppBasePath + cPath_App_LocalProfiles + "\\" + l_cpProfile->m_csProfileName + ".xml";
						l_cpProfile->SaveProfile (l_csFilePath);
					}
					else if (l_cpProfile->m_csProfileType == cAppData_Profile_Server)
					{
						l_csFilePath = m_csAppBasePath + cPath_App_ServerProfiles + "\\" + l_cpProfile->m_csProfileName + ".xml";
						l_cpProfile->SaveProfile (l_csFilePath);
					}
				}
			}

			m_bProfilesChanged = false;
		}
	}
}

CAppData::UpdateDisplayedVersion()
{
	if (!m_bVerticalToolBar)
	{
		m_cpHCCDlg->SetWindowText ("HCC v" + cAppData_Version + " (Database Revision: " + m_csDatabaseRevision + ")");
	}
	else
	{
		m_cpHCCDlg->SetWindowText ("HCC");
	}

	m_cpHCCDlg->m_cTitleFrame.SetWindowText ("HCC v" + cAppData_Version );

	if (m_csDatabaseRevision.IsEmpty ())
	{
		m_cpHCCDlg->m_cDatabaseTitle.SetWindowText ("DB: Default" );
	}
	else
	{
		m_cpHCCDlg->m_cDatabaseTitle.SetWindowText ("DB: " + m_csDatabaseRevision );
	}
}

CAppData::Reinitialise(bool a_cCheckForUpdates)
{
	if (a_cCheckForUpdates)
	{
		UnpackAvailableUpdates ();
	}

	CAppData::ClearImageCache ();
	CAppData::LoadData();
	CAppData::RefreshWindows();
}

CAppData::AddEffectType (CTypedPtrList<CPtrList, CEffect*> &a_clEffectsList,
								 CStringList &a_csEffectTypeList,
								 CString a_csEffectName,
								 CMSFlexGrid &a_cFlexGrid,
								 int	 a_iStyle,
								 CEdit *a_cSizingBox,
								 CString a_csPrefix,
								 bool &a_bHeader)
{
	POSITION l_Pos;
	POSITION l_TypePos;
	CEffect *l_cpEffect;
	CString l_csEffectType;

	l_Pos = a_clEffectsList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpEffect = a_clEffectsList.GetNext (l_Pos);

		l_TypePos = a_csEffectTypeList.GetHeadPosition ();

		while (l_TypePos)
		{
			l_csEffectType = a_csEffectTypeList.GetNext (l_TypePos);
			if (l_cpEffect->m_csType == l_csEffectType)
			{
				if (!a_bHeader)
				{
					a_bHeader = true;
					a_cFlexGrid.AddRow (a_csEffectName + "|" + a_csPrefix + l_cpEffect->m_csDescription, a_iStyle, a_cSizingBox);
				}
				else
				{
					a_cFlexGrid.AddRow ("|" + a_csPrefix + l_cpEffect->m_csDescription, a_iStyle, a_cSizingBox);
				}
			}
		}
	}
}

CAppData::AddEffectType (CTypedPtrList<CPtrList, CEffect*> &a_clEffectsList,
								 CString a_csEffectType,
								 CString a_csEffectName,
								 CMSFlexGrid &a_cFlexGrid,
								 int	 a_iStyle,
								 CEdit *a_cSizingBox,
								 CString a_csPrefix,
								 bool &a_bHeader)
{
	POSITION l_Pos;
	CEffect *l_cpEffect;

	l_Pos = a_clEffectsList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpEffect = a_clEffectsList.GetNext (l_Pos);
		if (l_cpEffect->m_csType == a_csEffectType)
		{
			if (!a_bHeader)
			{
				a_bHeader = true;
				a_cFlexGrid.AddRow (a_csEffectName + "|" + a_csPrefix + l_cpEffect->m_csDescription, a_iStyle, a_cSizingBox);
			}
			else
			{
				a_cFlexGrid.AddRow ("|" + a_csPrefix + l_cpEffect->m_csDescription, a_iStyle, a_cSizingBox);
			}
		}
	}
}

bool CAppData::FindEffectType (CTypedPtrList<CPtrList, CEffect*> &a_clEffectsList,
										 CString a_csEffectType,
										 CString &a_csEffectName)
{
	POSITION l_Pos;
	CEffect *l_cpEffect;

	l_Pos = a_clEffectsList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpEffect = a_clEffectsList.GetNext (l_Pos);
		if (l_cpEffect->m_csType == a_csEffectType)
		{
			a_csEffectName = l_cpEffect->m_csDescription;
			return (true);
		}
	}

	return (false);
}

CAppData::AddTitledEffectType (CTypedPtrList<CPtrList, CEffect*> &a_clEffectsList,
										 CString a_csEffectType,
										 CString a_csEffectName,
										 CMSFlexGrid &a_cFlexGrid,
										 int	 a_iStyle,
										 CEdit *a_cSizingBox)
{
	POSITION l_Pos;
	CEffect *l_cpEffect;
	bool l_bTitle = false;
	VARIANT l_cSVariant;
	l_cSVariant.vt = VT_I4;

	l_Pos = a_clEffectsList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpEffect = a_clEffectsList.GetNext (l_Pos);
		if (l_cpEffect->m_csType == a_csEffectType)
		{
			if (!l_bTitle)
			{
				a_cFlexGrid.AddRow (a_csEffectName + "|" + a_csEffectName, GRID_MINORTITLE, 1);
				a_cFlexGrid.AddRow ("|", GRID_MINORTITLE, 1);
				l_bTitle = true;
			}

			l_cSVariant.intVal = a_cFlexGrid.GetRows ();
			a_cFlexGrid.AddItem ("\t" + l_cpEffect->m_csDescription, l_cSVariant);
		}
	}

	if (l_bTitle)
	{
		a_cFlexGrid.AddRow ("|", GRID_MINORTITLE, 1);
	}
}

CString CAppData::GetDatabaseZipName(CTime a_ctTime)
{
	return ("HCC_" + a_ctTime.Format (cAppData_DateFormat) + ".zip");
}

CAppData::UnpackAvailableUpdates()
{
	CFileFind l_cFileFind;
	bool l_bOthers;
	int l_iCount = 0;

	if (l_cFileFind.FindFile (m_csAppBasePath + cPath_App_Temp + "/HCC_*.zip"))
	{
		l_bOthers = (l_cFileFind.FindNextFile () != 0);

		if (l_bOthers)
		{
			AfxMessageBox ("More then one database update file (*.zip) exists in '" +
				            m_csAppBasePath + cPath_App_Temp + "'.\nPlease remove all but one and restart the client for the update to take effect!", MB_ICONEXCLAMATION);
		}
		else
		{
			InstallUpdate (l_cFileFind.GetFilePath ());
		}
	}

	l_cFileFind.Close ();

}

CAppData::InstallUpdate(CString &a_csFile)
{
	CString l_csArchiveFile = a_csFile;
	CString l_csExtractPath = CAppData::m_csAppBasePath + cPath_App_TempArchive;
	CString l_csConfigPath = CAppData::m_csAppBasePath + cPath_App_Config;
	CString l_csCacheConfigPath = CAppData::m_csAppBasePath + cPath_App_Cache + cFile_App_ConfigCache;
	CString l_csCacheFormIconPath = CAppData::m_csAppBasePath + cPath_App_Cache + cFile_App_IconCache;
	CUpdateDialog l_cUpdateDialog;
	CString l_csVersion;

	l_cUpdateDialog.DeleteFolder (l_csExtractPath, true);
	if (l_cUpdateDialog.OpenArchive (l_csArchiveFile, l_csExtractPath))
	{
		DeleteFile (l_csCacheConfigPath);
		DeleteFile (l_csCacheFormIconPath);
		l_cUpdateDialog.DeleteFolder (l_csConfigPath, true);
		l_cUpdateDialog.MoveFolder (l_csExtractPath, l_csConfigPath, false);
		CAppData::Reinitialise (false);

		l_csVersion = a_csFile.Mid (a_csFile.Find ("HCC_") + 4);
		l_csVersion.Replace (".zip", "");
		CAppData::m_csDatabaseRevision = l_csVersion;
		CAppData::UpdateDisplayedVersion ();
	}
	else
	{
		AfxMessageBox ("Update failed, database archive is corrupt.\nRemoving update file", MB_ICONEXCLAMATION);
	}
	l_cUpdateDialog.DeleteFolder (l_csExtractPath, true);
	DeleteFile (l_csArchiveFile);
}

bool CAppData::GetStoredComponent(CString &a_csComponent, int &a_iCount)
{
	CString l_csValue;

	if (m_cmComponentMap.Lookup (a_csComponent, l_csValue))
	{
		a_iCount = atoi (l_csValue);
		return (true);
	}

	return (false);
}

bool CAppData::SetStoredComponent(CString &a_csComponent, int &a_iCount)
{
	CString l_csValue;

	l_csValue.Format ("%d", a_iCount);
	m_cmComponentMap.SetAt (a_csComponent, l_csValue);
	return (true);
}

CAppData::OptimiseStoredComponents()
{
	POSITION l_Pos;
	POSITION l_OrderPos;
	POSITION l_TechPos;
	POSITION l_ResourcePos;
	CString l_csComponentName;
	CString l_csCount;
	COrderItem l_cOrderItem;
	CItemTech l_cItemTech;
	CFormulaTier *l_cpFormulaTier;
	CTechTier *l_cpTechTier;
	CItemResource *l_cpItemResource;
	bool l_bKeepComponent;

	l_Pos = m_cmComponentMap.GetStartPosition ();
	while (l_Pos)
	{
		m_cmComponentMap.GetNextAssoc (l_Pos, l_csComponentName, l_csCount);
		l_bKeepComponent = false;

		if (l_csCount == "0")
		{
			l_bKeepComponent = false;
		}
		else
		{
			l_OrderPos = m_clOrderList.GetHeadPosition ();
			while ((!l_bKeepComponent) && (l_OrderPos))
			{
				l_cOrderItem = m_clOrderList.GetNext (l_OrderPos);

				if (FindFormulaTier (l_cOrderItem.m_csCategory, l_cOrderItem.m_csFormulaName, l_cOrderItem.m_csTierName, &l_cpFormulaTier))
				{
					l_ResourcePos = l_cpFormulaTier->m_clResourceList.GetHeadPosition ();
					while ((!l_bKeepComponent) && (l_ResourcePos))
					{
						l_cpItemResource = l_cpFormulaTier->m_clResourceList.GetNext (l_ResourcePos);
						l_bKeepComponent = SearchForComponents (l_cpItemResource->m_csName, l_csComponentName);
					}
				}

				l_TechPos = l_cOrderItem.m_clTechList.GetHeadPosition ();
				while ((!l_bKeepComponent) && (l_TechPos))
				{
					l_cItemTech = l_cOrderItem.m_clTechList.GetNext (l_TechPos);

					if (FindTechTier (l_cItemTech.m_csCategory, l_cItemTech.m_csTechName, l_cItemTech.m_csTierName, &l_cpTechTier))
					{
						l_ResourcePos = l_cpTechTier->m_clResourceList.GetHeadPosition ();
						while ((!l_bKeepComponent) && (l_ResourcePos))
						{
							l_cpItemResource = l_cpTechTier->m_clResourceList.GetNext (l_ResourcePos);
							l_bKeepComponent = SearchForComponents (l_cpItemResource->m_csName, l_csComponentName);
						}
					}
				}
			}
		}

		if (!l_bKeepComponent)
		{
			m_cmComponentMap.RemoveKey (l_csComponentName);
		}
	}

}

bool CAppData::SearchForComponents(CString &a_csFormulaName, CString &a_csComponentName)
{
	CFormula *l_cpFormula;
	CFormulaTier *l_cpFormulaTier;
	CItemResource *l_cpItemResource;
	POSITION l_Pos;

	if (a_csFormulaName == a_csComponentName)
	{
		return (true);
	}

	if (FindResourceFormulaTier (a_csFormulaName, &l_cpFormula, &l_cpFormulaTier))
	{
		l_Pos = l_cpFormulaTier->m_clResourceList.GetHeadPosition ();
		while (l_Pos)
		{
			l_cpItemResource = l_cpFormulaTier->m_clResourceList.GetNext (l_Pos);
			if (SearchForComponents (l_cpItemResource->m_csName, a_csComponentName))
			{
				return (true);
			}
		}

	}

	return (false);
}

CAppData::LoadEffectLists()
{
	m_csEffectList_Info.RemoveAll ();
	m_csEffectList_Bonuses.RemoveAll ();
	m_csEffectList_Requirements.RemoveAll ();

	m_csEffectList_Bonuses.AddTail (cXMLAttribute_Bonus);
	m_csEffectList_Bonuses.AddTail (cXMLAttribute_Effect);

	m_csEffectList_Requirements.AddTail (cXMLAttribute_ReqSkill);
	m_csEffectList_Requirements.AddTail (cXMLAttribute_ReqLevel);
	m_csEffectList_Requirements.AddTail (cXMLAttribute_ReqRace);
	m_csEffectList_Requirements.AddTail (cXMLAttribute_Requirement);
}

CAppData::ChangeOrderState(bool l_bState)
{
	CAppData::m_bOrderChanged = l_bState;
	if (m_cOrderWnd.m_cWindowState.m_bLoaded)
	{
		m_cOrderWnd.DisplayOrderTitle ();
	}
}

CAppData::ApplyCurrentTheme(bool l_bRefresh)
{
	m_cpHCCApp->SetDialogColors(CScheme::GetColour ("DIALOGCOLOUR_BG"), CScheme::GetColour ("DIALOGCOLOUR_FG"));

	if (l_bRefresh)
	{
		m_cpHCCDlg->RedrawWindow ();
		if (m_cOrderWnd.m_cWindowState.m_bLoaded)
		{
			m_cOrderWnd.m_cItemTree.SetBkColor (CScheme::GetColour ("TREE_BACKCOLOUR"));
			m_cOrderWnd.m_cTechList.SetBkColor (CScheme::GetColour ("TREE_BACKCOLOUR"));
			m_cOrderWnd.m_cTechList.SetTextBkColor (CScheme::GetColour ("TREE_BACKCOLOUR"));
			m_cOrderWnd.RedrawWindow ();
		}

		if (m_cComponentWnd.m_cWindowState.m_bLoaded)
		{
			m_cComponentWnd.m_cCompTree.SetBkColor (CScheme::GetColour ("TREE_BACKCOLOUR"));
			m_cComponentWnd.m_cResourceGrid.SetBackColor (CScheme::GetColour ("GRID_INFOBACKCOLOUR"));
			m_cComponentWnd.m_cResourceGrid.SetBackColorBkg (CScheme::GetColour ("GRID_INFOBACKCOLOUR"));
			m_cComponentWnd.m_cResourceGrid.SetGridColorFixed (CScheme::GetColour ("GRID_INFOBACKCOLOUR"));
			m_cComponentWnd.m_cResourceGrid.SetForeColorSel (CScheme::GetColour ("SELECTCOLOUR_FG"));
			m_cComponentWnd.m_cResourceGrid.SetBackColorSel (CScheme::GetColour ("SELECTCOLOUR_BG"));
			m_cComponentWnd.DisplayComponent ();
			m_cComponentWnd.RedrawWindow ();
		}

		if (m_cItemCreationWnd.m_cWindowState.m_bLoaded)
		{
			m_cItemCreationWnd.m_cFilterList.SetBkColor (CScheme::GetColour ("TREE_BACKCOLOUR"));
			m_cItemCreationWnd.m_cFilterList.SetTextBkColor (CScheme::GetColour ("TREE_BACKCOLOUR"));
			m_cItemCreationWnd.m_cFormulaTree.SetBkColor (CScheme::GetColour ("TREE_BACKCOLOUR"));
			m_cItemCreationWnd.m_cItemInfoGrid.SetBackColor (CScheme::GetColour ("GRID_INFOBACKCOLOUR"));
			m_cItemCreationWnd.m_cItemInfoGrid.SetBackColorBkg (CScheme::GetColour ("GRID_INFOBACKCOLOUR"));
			m_cItemCreationWnd.m_cItemInfoGrid.SetGridColorFixed (CScheme::GetColour ("GRID_INFOBACKCOLOUR"));
			m_cItemCreationWnd.m_cItemInfoGrid.SetForeColorSel (CScheme::GetColour ("SELECTCOLOUR_FG"));
			m_cItemCreationWnd.m_cItemInfoGrid.SetBackColorSel (CScheme::GetColour ("SELECTCOLOUR_BG"));
			m_cItemCreationWnd.m_cResourceGrid.SetBackColor (CScheme::GetColour ("GRID_BACKCOLOUR"));
			m_cItemCreationWnd.m_cResourceGrid.SetBackColorBkg (CScheme::GetColour ("GRID_BACKCOLOUR"));
			m_cItemCreationWnd.m_cResourceGrid.SetGridColor (CScheme::GetColour ("GRID_LINECOLOUR_LIGHT"));
			m_cItemCreationWnd.m_cResourceGrid.SetGridColorFixed (CScheme::GetColour ("GRID_LINECOLOUR_DARK"));
			m_cItemCreationWnd.m_cResourceGrid.SetForeColorSel (CScheme::GetColour ("SELECTCOLOUR_FG"));
			m_cItemCreationWnd.m_cResourceGrid.SetBackColorSel (CScheme::GetColour ("SELECTCOLOUR_BG"));
			m_cItemCreationWnd.m_cTierGrid.SetBackColor (CScheme::GetColour ("GRID_LISTBACKCOLOUR"));
			m_cItemCreationWnd.m_cTierGrid.SetBackColorBkg (CScheme::GetColour ("GRID_LISTBACKCOLOUR"));
			m_cItemCreationWnd.m_cTierGrid.SetGridColorFixed (CScheme::GetColour ("GRID_LISTBACKCOLOUR"));
			m_cItemCreationWnd.m_cTierGrid.SetForeColorSel (CScheme::GetColour ("SELECTCOLOUR_FG"));
			m_cItemCreationWnd.m_cTierGrid.SetBackColorSel (CScheme::GetColour ("SELECTCOLOUR_BG"));
			m_cItemCreationWnd.m_cTechGrid.SetBackColor (CScheme::GetColour ("GRID_LISTBACKCOLOUR"));
			m_cItemCreationWnd.m_cTechGrid.SetBackColorBkg (CScheme::GetColour ("GRID_LISTBACKCOLOUR"));
			m_cItemCreationWnd.m_cTechGrid.SetGridColorFixed (CScheme::GetColour ("GRID_LISTBACKCOLOUR"));
			m_cItemCreationWnd.m_cTechGrid.SetForeColorSel (CScheme::GetColour ("SELECTCOLOUR_FG"));
			m_cItemCreationWnd.m_cTechGrid.SetBackColorSel (CScheme::GetColour ("SELECTCOLOUR_BG"));

			if (CAppData::m_cpCurrentFormula)
			{
				m_cItemCreationWnd.DisplayFormula (false);
			}

			m_cItemCreationWnd.RedrawWindow ();
		}

		if (m_cTechSelectionWnd.m_cWindowState.m_bLoaded)
		{
			m_cTechSelectionWnd.m_cTechTree.SetBkColor (CScheme::GetColour ("TREE_BACKCOLOUR"));
			m_cTechSelectionWnd.m_cFilterList.SetBkColor (CScheme::GetColour ("TREE_BACKCOLOUR"));
			m_cTechSelectionWnd.m_cFilterList.SetTextBkColor (CScheme::GetColour ("TREE_BACKCOLOUR"));
			m_cTechSelectionWnd.m_cTechInfoGrid.SetBackColor (CScheme::GetColour ("GRID_INFOBACKCOLOUR"));
			m_cTechSelectionWnd.m_cTechInfoGrid.SetBackColorBkg (CScheme::GetColour ("GRID_INFOBACKCOLOUR"));
			m_cTechSelectionWnd.m_cTechInfoGrid.SetGridColorFixed (CScheme::GetColour ("GRID_INFOBACKCOLOUR"));
			m_cTechSelectionWnd.m_cTechInfoGrid.SetForeColorSel (CScheme::GetColour ("SELECTCOLOUR_FG"));
			m_cTechSelectionWnd.m_cTechInfoGrid.SetBackColorSel (CScheme::GetColour ("SELECTCOLOUR_BG"));
			m_cTechSelectionWnd.m_cTechComponentGrid.SetBackColor (CScheme::GetColour ("GRID_BACKCOLOUR"));
			m_cTechSelectionWnd.m_cTechComponentGrid.SetBackColorBkg (CScheme::GetColour ("GRID_BACKCOLOUR"));
			m_cTechSelectionWnd.m_cTechComponentGrid.SetGridColor (CScheme::GetColour ("GRID_LINECOLOUR_LIGHT"));
			m_cTechSelectionWnd.m_cTechComponentGrid.SetGridColorFixed (CScheme::GetColour ("GRID_LINECOLOUR_DARK"));
			m_cTechSelectionWnd.m_cTechComponentGrid.SetForeColorSel (CScheme::GetColour ("SELECTCOLOUR_FG"));
			m_cTechSelectionWnd.m_cTechComponentGrid.SetBackColorSel (CScheme::GetColour ("SELECTCOLOUR_BG"));
			m_cTechSelectionWnd.m_cTechTierGrid.SetBackColor (CScheme::GetColour ("GRID_LISTBACKCOLOUR"));
			m_cTechSelectionWnd.m_cTechTierGrid.SetBackColorBkg (CScheme::GetColour ("GRID_LISTBACKCOLOUR"));
			m_cTechSelectionWnd.m_cTechTierGrid.SetGridColorFixed (CScheme::GetColour ("GRID_LISTBACKCOLOUR"));
			m_cTechSelectionWnd.m_cTechTierGrid.SetForeColorSel (CScheme::GetColour ("SELECTCOLOUR_FG"));
			m_cTechSelectionWnd.m_cTechTierGrid.SetBackColorSel (CScheme::GetColour ("SELECTCOLOUR_BG"));

			if (CAppData::m_cpCurrentTech)
			{
				m_cTechSelectionWnd.DisplayTech (CAppData::m_cpCurrentTech, CAppData::m_csCurrentTechTierName);
			}

			m_cTechSelectionWnd.m_cFilterList.RedrawWindow ();
			m_cTechSelectionWnd.RedrawWindow ();
		}

		if (m_cReportWnd.m_cWindowState.m_bLoaded)
		{
			m_cReportWnd.m_cReportGrid.SetBackColor (CScheme::GetColour ("GRID_REPORTBACKCOLOUR"));
			m_cReportWnd.m_cReportGrid.SetBackColorBkg (CScheme::GetColour ("GRID_REPORTBACKCOLOUR"));
			m_cReportWnd.m_cReportGrid.SetGridColorFixed (CScheme::GetColour ("GRID_REPORTBACKCOLOUR"));
			m_cReportWnd.m_cReportGrid.SetBackColorSel (CScheme::GetColour ("SELECTCOLOUR_FG"));
			m_cReportWnd.m_cReportGrid.SetForeColorSel (CScheme::GetColour ("SELECTCOLOUR_BG"));
			m_cReportWnd.GenerateDirectReport ();
			m_cReportWnd.RedrawWindow ();
		}

		if (m_cSkillLevelWnd.m_cWindowState.m_bLoaded)
		{
			m_cSkillLevelWnd.m_cSkillGrid.SetBackColor (CScheme::GetColour ("GRID_BACKCOLOUR"));
			m_cSkillLevelWnd.m_cSkillGrid.SetBackColorBkg (CScheme::GetColour ("GRID_BACKCOLOUR"));
			m_cSkillLevelWnd.m_cSkillGrid.SetGridColor (CScheme::GetColour ("GRID_LINECOLOUR_LIGHT"));
			m_cSkillLevelWnd.m_cSkillGrid.SetGridColorFixed (CScheme::GetColour ("GRID_LINECOLOUR_DARK"));
			m_cSkillLevelWnd.m_cSkillGrid.SetForeColorSel (CScheme::GetColour ("SELECTCOLOUR_FG"));
			m_cSkillLevelWnd.m_cSkillGrid.SetBackColorSel (CScheme::GetColour ("SELECTCOLOUR_BG"));
			m_cSkillLevelWnd.DisplaySkillLevels ();
			m_cSkillLevelWnd.RedrawWindow ();
		}

		if (m_cProfileWnd.m_cWindowState.m_bLoaded)
		{
			m_cProfileWnd.m_cProfileTree.SetBkColor (CScheme::GetColour ("TREE_BACKCOLOUR"));
			m_cProfileWnd.m_cProfilePage1.m_cStatistcsList.SetBkColor (CScheme::GetColour ("TREE_BACKCOLOUR"));
			m_cProfileWnd.m_cProfilePage1.m_cStatistcsList.SetTextBkColor (CScheme::GetColour ("TREE_BACKCOLOUR"));
			m_cProfileWnd.m_cProfilePage2.m_cCraftList.SetBkColor (CScheme::GetColour ("TREE_BACKCOLOUR"));
			m_cProfileWnd.m_cProfilePage2.m_cCraftList.SetTextBkColor (CScheme::GetColour ("TREE_BACKCOLOUR"));
			m_cProfileWnd.RedrawWindow ();
			m_cProfileWnd.m_cProfilePage1.RedrawWindow ();
			m_cProfileWnd.m_cProfilePage2.RedrawWindow ();
		}
	}
}

