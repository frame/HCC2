// AppData.h: interface for the CAppData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_APPDATA_H__1F5760AC_8792_4D86_B4EA_464378662B8E__INCLUDED_)
#define AFX_APPDATA_H__1F5760AC_8792_4D86_B4EA_464378662B8E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OrderDialog.h"
#include "ItemCreation.h"
#include "TechniqueSelection.h"
#include "ComponentDialog.h"
#include "SkillLevelDialog.h"
#include "ReportDialog.h"
#include "ProfileDialog.h"
#include "ProfilePage1.h"
#include "ProfilePage2.h"
#include "ProfilePage3.h"

#include "formulatier.h"
#include "formula.h"
#include "FormulaSet.h"
#include "techtier.h"
#include "tech.h"
#include "techSet.h"
#include "HCCDlg.h"
#include "ImageStore.h"
#include "OrderItem.h"
#include "Component.h"
#include "Profile.h"
#include "SchoolWizard.h"
#include "XMLParser.h"
#include "Category.h"
#include "SubCategory.h"

class CAppData
{
public:
	static  ApplyCurrentTheme(bool l_bRefresh = true);
	static ChangeOrderState (bool l_bState);
	static  LoadEffectLists();
	static bool SearchForComponents(CString &a_csFormulaName, CString &a_csComponentName);
	static OptimiseStoredComponents();
	static bool SetStoredComponent (CString &a_csComponent, int &a_iCount);
	static bool GetStoredComponent (CString &a_csComponent, int &a_iCount);
	static  InstallUpdate (CString &a_csFile);
	static  UnpackAvailableUpdates();
	static CString GetDatabaseZipName (CTime a_ctTime);
	static bool FindEffectType (CTypedPtrList<CPtrList, CEffect*> &a_clEffectsList,
										 CString a_csEffectType,
										 CString &a_csEffectName);
	static AddTitledEffectType (CTypedPtrList<CPtrList, CEffect*> &a_clEffectsList,
											 CString a_csEffectType,
											 CString a_csEffectName,
											 CMSFlexGrid &a_cFlexGrid,
											 int	 a_iStyle,
											 CEdit *a_cSizingBox);
	static AddEffectType (CTypedPtrList<CPtrList, CEffect*> &a_clEffectsList,
									 CString a_csEffectType,
									 CString a_csEffectName,
									 CMSFlexGrid &a_cFlexGrid,
									 int	 a_iStyle,
									 CEdit *a_cSizingBox,
									 CString a_csPrefix,
									 bool &a_bHeader);
	static  AddEffectType (CTypedPtrList<CPtrList, CEffect*> &a_clEffectsList,
								 CStringList &a_csEffectTypeList,
								 CString a_csEffectName,
								 CMSFlexGrid &a_cFlexGrid,
								 int	 a_iStyle,
								 CEdit *a_cSizingBox,
								 CString a_csPrefix,
								 bool &a_bHeader);
	static Reinitialise(bool a_cCheckForUpdates = true);
	static  UpdateDisplayedVersion();
	static SaveProfiles (bool a_bPrompt);
	static SetProfilesChangeState (bool a_bState);
	static  RestoreApp();
	static  MinimiseApp();
	static  Shutdown();
	static CString FindBestMatchingTier (CFormula *a_cpFormula, CString &a_csTierName);
	static CString FormatOrderItemText (COrderItem &a_cOrderItem);
	static  CopyToClipboard (CString &a_csStr);
	static LaunchWebLink (CString &a_csPage);
	static WriteUpdatesForDir(CString &a_csPath, XMLParser &a_cParser, int a_iBasePathLength);
	static int DetermineCurrentItemUsageOffset();
	static void SetMenuItem (CMenu *a_pMenu, UINT a_iMenuItem, bool a_bCheck);
	static ClearImageCache();
	static RefreshWindows();
	static ClearCache (bool a_bFull = false);
	static bool LoadCache (CString &a_csPath);
	static WriteCache (CString &a_csPath);
	static int CalculateEfficiencyPercentage(CItemResource *a_cpResource, CProfile *a_cpProfile, int a_iSkillOfset);
	static int CalculateEfficiency (CItemResource *a_cpResource, CProfile *a_cpProfile, int a_iSkillOfset);
	static bool FindComponent (CString &a_csCompName, CComponent **a_cpComponent);
	static bool FindProfile(CString &a_csProfileName, CString &a_csServerName, CProfile **a_cpProfile);
	static bool FindSubCategory(CString &a_csSubCategory, CSubCategory **a_cpSubCategory);

	// Window Routines
	static int ConvertGridWidthToScreen (int a_iWidth);
	static int ConvertScreenWidthToGrid (int a_iWidth);
	static ClearComboBox (CComboBox &a_cCombo);
	static SetToolbarState(CButtonST &a_cButton, bool a_bState, int a_iStateOff, int a_iStateOn);

	static SetTechWindowState();
	static SetFormulaWindowState();
	static SetMainWindowState();
	static SetOrderWindowState ();
	static SetCompWindowState();
	static SetReportWindowState();
	static SetProfileWindowState();

	static GetTechWindowState();
	static GetFormulaWindowState();
	static GetOrderWindowState ();
	static GetMainWindowState();
	static GetCompWindowState ();
	static GetReportWindowState ();
	static GetProfileWindowState();

	static bool SetOrderWindow(bool l_bOpen);
	static bool SetItemWindow(bool l_bOpen);
	static bool SetTechWindow(bool l_bOpen);
	static bool SetComponentWindow(bool l_bOpen);
	static bool SetSkillLevelWindow(bool l_bOpen);
	static bool SetReportWindow(bool l_bOpen);
	static bool SetProfileWindow(bool l_bOpen);

	// Load/Save Routines
	static ReadDefaults();
	static LoadGameImages (CString &a_csGamePath, CString &a_csAppPath);
	static LoadData ();
	static LoadWindowStates();
	static bool LoadFormulas(CString &a_csPath, CTypedPtrList<CPtrList, CFormulaSet*> &a_clFormulaList);
	static bool LoadTechniques(CString &a_csPath);
	static bool LoadComponentFile(CString &a_csFilename);
	static bool LoadOrder (CString &a_csFilename);
	static bool LoadProfiles(CString &a_csPath, CString a_csType);
	static bool LoadWizards(CString &a_csPath);
	static bool LoadCategories(CString &a_csFilename);
	static bool LoadHelpLinks(CString &a_csFilename);
	static bool LoadTechniqueFile(CString &a_csFilename);
	static bool LoadFormulaFile(CString &a_csFilename);

	static bool SaveOrder (CString &a_csFilename);
	static bool ExportOrder (CString &a_csFilename);
	static bool ExportProfile (CString &a_csFilename);
	static SaveDefaults();
	static SaveWindowStates();

	// Logic Routines
	static int DetermineTechLimit (int a_iTier);
	static AddOrderGroup (CString &a_csOrderGroup);
	static DeleteOrderItem (int l_iItemId);
	static DeleteOrderGroup (CString &a_csGroup);
	static UpdateOrderGroup (CString &a_csOldGroup, CString &a_csNewGroup);
	static UpdateOrderItem (COrderItem &a_cOrderItem);
	static bool FindTechTier(CString a_csCategory, CString a_csName, CString &a_csTier, CTechTier **a_cpTechTier);
	static bool FindOrderItem (int a_iId, COrderItem &a_cOrderItem);
	static CString GetTierName (int a_iTier);
	static int GetTierLevel (CString a_csTier);
	static bool FindTech(CString a_csCategory, CString a_csName, CTech **a_cpTech);
	static bool FindFormulaTier (CString a_csCategory, CString a_csName, CString &a_csTier, CFormulaTier **a_cpFormulaTier);
	static bool FindFormula (CString a_csCategory, CString a_csName, CFormula **a_cpFormula);
	static bool FindResourceFormula(CString a_csName, CFormula **a_cpFormula);
	static bool FindResourceFormulaTier(CString a_csResourceName,  CFormula **a_cpFormula, CFormulaTier **a_cpFormulaTier);
	static CacheInternalData();
	static AddFormulaCategory (CString a_csCategory);
	static AddTechCategory (CString a_csCategory);


	CAppData();
	virtual ~CAppData();

	static CHCCApp				  *m_cpHCCApp;
	static CHCCDlg				  *m_cpHCCDlg;
	static COrderDialog			m_cOrderWnd;
	static CItemCreation			m_cItemCreationWnd;
	static CTechniqueSelection m_cTechSelectionWnd;
	static CComponentDialog	   m_cComponentWnd;
	static CSkillLevelDialog	m_cSkillLevelWnd;
	static CReportDialog			m_cReportWnd;
	static CProfileDialog		m_cProfileWnd;

	static CImageStore *m_cpIconImages;

	static CTypedPtrList<CPtrList, CFormulaSet*>	m_clFormulaSetList;
	static CList<CString, CString&> m_clFormulaCategoryList;
	static CTypedPtrList<CPtrList, CComponent*>	m_clComponentList;
	static CTypedPtrList<CPtrList, CFormulaSet*> m_cResourceFormulaSetList;

	static CTypedPtrList <CPtrList , CTechSet*>	m_clTechSetList;
	static CList<CString, CString&> m_clTechCategoryList;

	static CList<COrderItem, COrderItem&>	m_clOrderList;

	static CTypedPtrList<CPtrList, CProfile*>	m_clProfileList;

	static CTypedPtrList<CPtrList, CSchoolWizard*>	m_clSchoolWizardList;

	static CTypedPtrList<CPtrList, CCategory*>	m_clCategoryList;
	static CTypedPtrList<CPtrList, CSubCategory*>	m_clSubCategoryList;
	static CMapStringToString m_cmHelpLinks;
	static CMapStringToString m_cmComponentMap;

	static CString m_csCurrentProfile;
	static CString m_csCurrentProfileType;
	static CString m_csOrderDir;
	static CString m_csProfileDir;
	static CString m_csTmpDir;
	static CString m_csLastFormulaCategory;
	static CString m_csLastTechCategory;

	static CFormula *m_cpCurrentFormula;
	static CString   m_csCurrentFormulaTierName;
	static CString   m_csPreferedFormulaTierName;
	static int       m_csPreferedFormulaTier;

	static CTech	*m_cpCurrentTech;
	static CString  m_csCurrentTechTierName;
	static CString  m_csPreferedTechTierName;

	static COrderItem m_cCurrentOrderItem;
	static int m_iCurrentOrderId;

	static CProfile *m_cpCurrentProfile;
	static CProfile *m_cpTemplateProfile;

	static CStringList m_cOrderGroups;

	static CString m_cFormFilter;
	static CString m_cFormClassFilter;
	static CString m_cFormClassFilterType;
	static CTech *m_cpFormFilterTech;

	static bool m_bEditMode;
	static bool m_bFormSearchMode;
	static bool m_bShowUsableTechs;
	static bool m_bEnableIcons;
	static bool m_bEnableCache;
	static bool m_bAutoDock;
	static int  m_iShowResourceMode;
	static int  m_iShowReportMode;
	static int  m_iReportType;
	static int  m_iReportFormat;
	static int  m_iShowReportResourceMode;
	static int  m_iShowReportBonusMode;
	static int  m_iExpandFormulaMode;
	static int  m_iExpandTechMode;
	static int  m_iItemResourceSize;
	static int  m_iIconSize;
	static int  m_iStickyStrength;
	static bool m_bGlobalHotkeys;
	static bool m_bDragWithToolBar;
	static bool m_bVerticalToolBar;
	static bool m_bAutoShrink;
	static bool m_bHighPriority;
	static bool m_bAutoUpdate;
	static bool m_bAutoUpdateQuery;

	static bool m_bProfilesChanged;

	static CString m_csCurrentTheme;
	static CString m_csAppBasePath;
	static CString m_csGameBasePath;
	static CString m_csCurrentOrderFilename;

	static CString m_csDatabaseRevision;
	static bool m_bUpdateWindowOpen;

	static int m_iCacheCount;
	static CProgressCtrl	*m_cpCacheProgress;
	static COLORREF m_iNeutralColour;

	// Effect Lists
	static CStringList m_csEffectList_Info;
	static CStringList m_csEffectList_Bonuses;
	static CStringList m_csEffectList_Requirements;

	static bool m_bOrderChanged;

	static CFont m_cTitleFont;
	static CFont m_cTitleSelFont;

};

#endif // !defined(AFX_APPDATA_H__1F5760AC_8792_4D86_B4EA_464378662B8E__INCLUDED_)
