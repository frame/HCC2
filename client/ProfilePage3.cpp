// ProfilePage3.cpp : implementation file
//

#include "stdafx.h"
#include "HCC.h"
#include "ProfilePage3.h"
#include "Bonus.h"
#include "AppData.h"
#include "Skill.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProfilePage3 property page

IMPLEMENT_DYNCREATE(CProfilePage3, CPropertyPage)

CProfilePage3::CProfilePage3() : CPropertyPage(CProfilePage3::IDD)
{
	//{{AFX_DATA_INIT(CProfilePage3)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CProfilePage3::~CProfilePage3()
{
}

void CProfilePage3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProfilePage3)
	DDX_Control(pDX, IDC_OPTSKILLS, m_cOptSkills);
	DDX_Control(pDX, IDC_OPTSCHOOLS, m_cOptSchools);
	DDX_Control(pDX, IDC_ADVENTURELIST, m_cAdventureList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProfilePage3, CPropertyPage)
	//{{AFX_MSG_MAP(CProfilePage3)
	ON_BN_CLICKED(IDC_OPTSCHOOLS, OnOptschools)
	ON_BN_CLICKED(IDC_OPTSKILLS, OnOptskills)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProfilePage3 message handlers

void CProfilePage3::OnOptschools() 
{
	// TODO: Add your control notification handler code here
	DisplayProfile();
}

void CProfilePage3::OnOptskills() 
{
	// TODO: Add your control notification handler code here
	DisplayProfile();
}

void CProfilePage3::DisplayProfile() 
{
	// TODO: Add your control notification handler code here
	if (m_cOptSchools.GetCheck() == 1)
	{
		DisplayAdventureSchools();
	}
	else
	{
		DisplayAdventureSkills();
	}
}

CProfilePage3::DisplayAdventureSchools()
{
	POSITION l_Pos;
	POSITION l_Pos2;
	CSkill *l_cpSkill;
	CSkill *l_cpSkill1;
	CString l_csValue;
	int l_iOffset;
	double l_fRating;

	m_cAdventureList.DeleteAllItems ();
	m_cAdventureList.DeleteColumn (0);
	m_cAdventureList.DeleteColumn (0);
	m_cAdventureList.DeleteColumn (0);
	m_cAdventureList.InsertColumn (0, "School", LVCFMT_LEFT, 110, -1);
	m_cAdventureList.InsertColumn (1, "Level", LVCFMT_RIGHT, 50, -1);
	m_cAdventureList.InsertColumn (2, "Rating", LVCFMT_RIGHT, 50, -1);

	if (CAppData::m_cpCurrentProfile)
	{
		l_iOffset = 0;
		l_Pos = CAppData::m_cpCurrentProfile->m_clAdventureSchoolList.GetHeadPosition ();
		while (l_Pos)
		{
			l_cpSkill = CAppData::m_cpCurrentProfile->m_clAdventureSchoolList.GetNext (l_Pos);
			m_cAdventureList.InsertItem (l_iOffset, l_cpSkill->m_csSkillName);
			l_csValue.Format ("%d", l_cpSkill->m_iSkillValue);
			m_cAdventureList.SetItemText (l_iOffset, 1, l_csValue);

			l_fRating = 0.0f;
			l_Pos2 = CAppData::m_cpCurrentProfile->m_clAdventureSchoolList.GetHeadPosition ();
			while (l_Pos2)
			{
				l_cpSkill1 = CAppData::m_cpCurrentProfile->m_clAdventureSchoolList.GetNext (l_Pos2);

				if (l_cpSkill->m_csSkillName == l_cpSkill1->m_csSkillName)
				{
					l_fRating += (double) l_cpSkill1->m_iSkillValue * l_cpSkill1->m_iSkillValue;
				}
				else
				{
					l_fRating += (double) (l_cpSkill1->m_iSkillValue * l_cpSkill1->m_iSkillValue) / 4;
				}

			}

			l_fRating = sqrt (l_fRating);
			l_csValue.Format ("%3.0f", l_fRating);
			m_cAdventureList.SetItemText (l_iOffset, 2, l_csValue);

			l_iOffset++;
		}
	}
}

CProfilePage3::DisplayAdventureSkills()
{
	POSITION l_Pos;
	CBonus *l_cpBonus;
	CString l_csValue;
	int l_iOffset;

	m_cAdventureList.DeleteAllItems ();
	m_cAdventureList.DeleteColumn (0);
	m_cAdventureList.DeleteColumn (0);
	m_cAdventureList.DeleteColumn (0);
	m_cAdventureList.InsertColumn (0, "Skill", LVCFMT_LEFT, 130, -1);
	m_cAdventureList.InsertColumn (1, "Amount", LVCFMT_RIGHT, 68, -1);

	if (CAppData::m_cpCurrentProfile)
	{
		l_iOffset = 0;
		l_Pos = CAppData::m_cpCurrentProfile->m_clAdventureSkillsList.GetHeadPosition ();
		while (l_Pos)
		{
			l_cpBonus = CAppData::m_cpCurrentProfile->m_clAdventureSkillsList.GetNext (l_Pos);
			l_csValue.Format ("%d", l_cpBonus->m_iValue);
			m_cAdventureList.InsertItem (l_iOffset, l_cpBonus->m_csBonusName);
			m_cAdventureList.SetItemText (l_iOffset, 1, l_csValue);
			l_iOffset++;
		}
	}
}


BOOL CProfilePage3::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_cOptSchools.SetCheck(1);
	DisplayProfile() ;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CProfilePage3::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	return (TRUE);
}
