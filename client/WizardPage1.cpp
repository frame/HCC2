// WizardPage1.cpp : implementation file
//

#include "stdafx.h"
#include "HCC.h"
#include "WizardPage1.h"
#include "AppData.h"
#include "SchoolWizard.h"
#include "Profile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWizardPage1 property page

IMPLEMENT_DYNCREATE(CWizardPage1, CPropertyPage)

CWizardPage1::CWizardPage1() : CPropertyPage(CWizardPage1::IDD)
{
	//{{AFX_DATA_INIT(CWizardPage1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CWizardPage1::~CWizardPage1()
{
}

void CWizardPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWizardPage1)
	DDX_Control(pDX, IDC_OPTPROFILE, m_cOptProfile);
	DDX_Control(pDX, IDC_OPTMANUAL, m_cOptManual);
	DDX_Control(pDX, IDC_SCHOOLTYPECOMBO, m_cSchoolTypeCombo);
	DDX_Control(pDX, IDC_SCHOOLNAMECOMBO, m_cSchoolNameCombo);
	DDX_Control(pDX, IDC_SCHOOLLEVELSPIN, m_cSchoolLevelSpin);
	DDX_Control(pDX, IDC_SCHOOLLEVEL, m_cSchoolLevel);
	DDX_Control(pDX, IDC_RACECOMBO, m_cRaceCombo);
	DDX_Control(pDX, IDC_PROFILESCHOOLCOMBO, m_cProfileSchoolCombo);
	DDX_Control(pDX, IDC_PROFILELIST, m_cProfileList);
	DDX_Control(pDX, IDC_INFO, m_cInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWizardPage1, CPropertyPage)
	//{{AFX_MSG_MAP(CWizardPage1)
	ON_CBN_SELCHANGE(IDC_RACECOMBO, OnSelchangeRacecombo)
	ON_CBN_SELCHANGE(IDC_SCHOOLTYPECOMBO, OnSelchangeSchooltypecombo)
	ON_CBN_SELCHANGE(IDC_SCHOOLNAMECOMBO, OnSelchangeSchoolnamecombo)
	ON_NOTIFY(NM_CLICK, IDC_PROFILELIST, OnClickProfilelist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizardPage1 message handlers

BOOL CWizardPage1::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnSetActive();
}

BOOL CWizardPage1::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_cpWizardDialog->SetWizardButtons (PSWIZB_NEXT);
	UpdateWizard();
	m_cSchoolLevel.SetWindowText ("1");
	m_cOptManual.SetCheck (1);
	m_cOptProfile.SetCheck (0);
	m_cpSchoolWizard = NULL;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CWizardPage1::UpdateWizard()
{
	CSchoolWizard *l_cpWizard;
	CProfile *l_cpProfile;
	POSITION l_Pos;
	POSITION l_RacePos;
	CString l_csStr;
	int l_iOffset = 0;

	m_cInfo.SetWindowText ("Welcome to the Order Creation Wizard. Choose whether you'd like to create an order based on manual selection or by using information gathered from an existing Local Profile. For manual creations, select the race, whether your after adventuring or crafting gear, the school that you want to create an order for and the level of that school. For profile based orders, just select the profile, and the particular school you want to deal with.");	

	CAppData::ClearComboBox (m_cRaceCombo);
	l_Pos = CAppData::m_clSchoolWizardList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpWizard = CAppData::m_clSchoolWizardList.GetNext (l_Pos);

		l_RacePos = l_cpWizard->m_clRaceList.GetHeadPosition ();
		while (l_RacePos)
		{
			l_csStr = l_cpWizard->m_clRaceList.GetNext (l_RacePos);
			if (m_cRaceCombo.FindStringExact (-1, l_csStr) == CB_ERR)
			{
				m_cRaceCombo.AddString (l_csStr);
			}
		}
	}

	m_cRaceCombo.SetCurSel (0);
	UpdateClassTypes();

	m_cProfileList.DeleteAllItems ();
	m_cProfileList.DeleteColumn (0);
	m_cProfileList.DeleteColumn (0);
	m_cProfileList.InsertColumn (0, "Player", LVCFMT_LEFT, 100, -1);
	m_cProfileList.InsertColumn (1, "Server", LVCFMT_LEFT, 80, -1);

	l_Pos = CAppData::m_clProfileList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpProfile = CAppData::m_clProfileList.GetNext (l_Pos);
		if (l_cpProfile->m_csProfileType == cAppData_Profile_Local)
		{
			m_cProfileList.InsertItem (l_iOffset, l_cpProfile->m_csProfileName);
			m_cProfileList.SetItemText (l_iOffset, 1, l_cpProfile->m_csProfileServer);
			l_iOffset++;
		}
	}
}

CWizardPage1::UpdateClassTypes()
{
	CSchoolWizard *l_cpWizard;
	CString l_csRace;
	POSITION l_Pos;
	POSITION l_RacePos;
	CString l_csStr;
	CString l_csPreviousValue;

	m_cSchoolTypeCombo.GetWindowText (l_csPreviousValue);
	m_cRaceCombo.GetWindowText (l_csRace);
	CAppData::ClearComboBox (m_cSchoolTypeCombo);

	l_Pos = CAppData::m_clSchoolWizardList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpWizard = CAppData::m_clSchoolWizardList.GetNext (l_Pos);

		l_RacePos = l_cpWizard->m_clRaceList.GetHeadPosition ();
		while (l_RacePos)
		{
			l_csStr = l_cpWizard->m_clRaceList.GetNext (l_RacePos);
			if (l_csStr == l_csRace)
			{
				if (m_cSchoolTypeCombo.FindStringExact (-1, l_cpWizard->m_cSchoolType) == CB_ERR)
				{
					m_cSchoolTypeCombo.AddString (l_cpWizard->m_cSchoolType);
				}
			}
		}
	}

	if (m_cSchoolTypeCombo.SelectString (-1, l_csPreviousValue) == CB_ERR)
	{
		m_cSchoolTypeCombo.SetCurSel (0);
	}

	UpdateClassChoices();
}

CWizardPage1::UpdateClassChoices()
{
	CSchoolWizard *l_cpWizard;
	CString l_csRace;
	CString l_csClassType;
	POSITION l_Pos;
	POSITION l_RacePos;
	CString l_csStr;
	CString l_csPreviousValue;
		
	m_cSchoolNameCombo.GetWindowText (l_csPreviousValue);
	m_cRaceCombo.GetWindowText (l_csRace);
	m_cSchoolTypeCombo.GetWindowText (l_csClassType);
	CAppData::ClearComboBox (m_cSchoolNameCombo);

	l_Pos = CAppData::m_clSchoolWizardList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpWizard = CAppData::m_clSchoolWizardList.GetNext (l_Pos);

		if (l_cpWizard->m_cSchoolType == l_csClassType)
		{
			l_RacePos = l_cpWizard->m_clRaceList.GetHeadPosition ();
			while (l_RacePos)
			{
				l_csStr = l_cpWizard->m_clRaceList.GetNext (l_RacePos);
				if (l_csStr == l_csRace)
				{
					m_cSchoolNameCombo.AddString (l_cpWizard->m_cSchoolName);
				}
			}
		}
	}

	if (m_cSchoolNameCombo.SelectString (-1, l_csPreviousValue) == CB_ERR)
	{
		m_cSchoolNameCombo.SetCurSel (0);
	}
}

void CWizardPage1::OnSelchangeRacecombo() 
{
	UpdateClassTypes();
	m_cOptManual.SetCheck (1);
	m_cOptProfile.SetCheck (0);
	SetChosenWizard();
}

void CWizardPage1::OnSelchangeSchooltypecombo() 
{
	UpdateClassChoices();
	m_cOptManual.SetCheck (1);
	m_cOptProfile.SetCheck (0);
	SetChosenWizard();
}

void CWizardPage1::OnSelchangeSchoolnamecombo() 
{
	m_cOptManual.SetCheck (1);
	m_cOptProfile.SetCheck (0);
	SetChosenWizard();
}

void CWizardPage1::OnClickProfilelist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cOptManual.SetCheck (0);
	m_cOptProfile.SetCheck (1);	
	UpdateProfileClassChoices();
	SetChosenWizard();

	*pResult = 0;
}

CWizardPage1::UpdateProfileClassChoices()
{
	CProfile *l_cpProfile;
	CSkill *l_cpSkill;
	POSITION l_Pos;
	CString l_csNameStr;
	CString l_csServerStr;
	int l_iOffset = m_cProfileList.GetSelectionMark ();
		
	if (l_iOffset != -1)
	{
		l_csNameStr = m_cProfileList.GetItemText (l_iOffset, 0 );
		l_csServerStr = m_cProfileList.GetItemText (l_iOffset, 1 );
		CAppData::ClearComboBox (m_cProfileSchoolCombo);

		if (CAppData::FindProfile (l_csNameStr, l_csServerStr, &l_cpProfile))
		{
			l_Pos = l_cpProfile->m_clAdventureSchoolList.GetHeadPosition ();
			while (l_Pos)
			{
				l_cpSkill = l_cpProfile->m_clAdventureSchoolList.GetNext (l_Pos);
				m_cProfileSchoolCombo.AddString (l_cpSkill->m_csSkillName);
			}

			l_Pos = l_cpProfile->m_clCraftSchoolList.GetHeadPosition ();
			while (l_Pos)
			{
				l_cpSkill = l_cpProfile->m_clCraftSchoolList.GetNext (l_Pos);
				m_cProfileSchoolCombo.AddString (l_cpSkill->m_csSkillName);
			}
		}

		m_cProfileSchoolCombo.SetCurSel (0);
	}
}

CWizardPage1::SetChosenWizard() 
{
	CString l_csStr;
	POSITION l_Pos;
	CSchoolWizard *l_cpWizard;
	CString l_csSchool;

	if (m_cOptManual.GetCheck () > 0)
	{
		m_cRaceCombo.GetWindowText (m_csRace);
		m_cSchoolNameCombo.GetWindowText (l_csSchool);
		m_cSchoolLevel.GetWindowText (l_csStr);
		m_iLevel = atoi (l_csStr);
		m_cpProfile = NULL;
	}
	else
	{
		CString l_csName;
		CString l_csServer;

		m_csRace = "";
		m_cProfileSchoolCombo.GetWindowText (l_csSchool);

		l_csName = m_cProfileList.GetItemText (m_cProfileList.GetSelectionMark (), 0);
		l_csServer = m_cProfileList.GetItemText (m_cProfileList.GetSelectionMark (), 1);

		if (CAppData::FindProfile (l_csName, l_csServer, &m_cpProfile))
		{
		}
	}

	l_Pos = CAppData::m_clSchoolWizardList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpWizard = CAppData::m_clSchoolWizardList.GetNext (l_Pos);
		if (l_cpWizard->m_cSchoolName == l_csSchool)
		{
			m_cpSchoolWizard = l_cpWizard;

			if (m_cpProfile)
			{
				m_csRace = l_cpWizard->m_clRaceList.GetHead ();
			}
		}
	}
	
}


LRESULT CWizardPage1::OnWizardNext() 
{
	// TODO: Add your specialized code here and/or call the base class
	SetChosenWizard();
	return CPropertyPage::OnWizardNext();
}
