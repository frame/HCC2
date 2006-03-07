// ProfilePage2.cpp : implementation file
//

#include "stdafx.h"
#include "HCC.h"
#include "ProfilePage2.h"
#include "Bonus.h"
#include "AppData.h"
#include "Skill.h"
#include "SkillDialog.h"
#include "Scheme.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProfilePage2 property page

IMPLEMENT_DYNCREATE(CProfilePage2, CPropertyPage)

CProfilePage2::CProfilePage2() : CPropertyPage(CProfilePage2::IDD)
{
	//{{AFX_DATA_INIT(CProfilePage2)
	//}}AFX_DATA_INIT
	m_bLoaded = false;
}

CProfilePage2::~CProfilePage2()
{
}

void CProfilePage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProfilePage2)
	DDX_Control(pDX, IDC_OPTSKILLS, m_cOptSkills);
	DDX_Control(pDX, IDC_OPTSCHOOLS, m_cOptSchools);
	DDX_Control(pDX, IDC_CRAFTLIST, m_cCraftList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProfilePage2, CPropertyPage)
	//{{AFX_MSG_MAP(CProfilePage2)
	ON_BN_CLICKED(IDC_OPTSCHOOLS, OnOptschools)
	ON_BN_CLICKED(IDC_OPTSKILLS, OnOptskills)
	ON_NOTIFY(NM_DBLCLK, IDC_CRAFTLIST, OnDblclkCraftlist)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProfilePage2 message handlers

void CProfilePage2::DisplayProfile() 
{
	// TODO: Add your control notification handler code here
	if (m_bLoaded)
	{
		if (m_cOptSchools.GetCheck() == 1)
		{
			DisplayCraftSchools();
		}
		else
		{
			DisplayCraftSkills();
		}
	}
}

CProfilePage2::DisplayCraftSchools()
{
	POSITION l_Pos;
	CSkill *l_cpSkill;
	CString l_csValue;
	int l_iOffset;

	m_cCraftList.DeleteAllItems ();
	m_cCraftList.DeleteColumn (0);
	m_cCraftList.DeleteColumn (0);
	m_cCraftList.DeleteColumn (0);
	m_cCraftList.InsertColumn (0, "School", LVCFMT_LEFT, 100, -1);
	m_cCraftList.InsertColumn (1, "Level", LVCFMT_RIGHT, 58, -1);
	//m_cCraftList.InsertColumn (2, "For Hire", LVCFMT_CENTER, 60, -1);

	if (CAppData::m_cpCurrentProfile)
	{
		l_iOffset = 0;
		l_Pos = CAppData::m_cpCurrentProfile->m_clCraftSchoolList.GetHeadPosition ();
		while (l_Pos)
		{
			l_cpSkill = CAppData::m_cpCurrentProfile->m_clCraftSchoolList.GetNext (l_Pos);
			m_cCraftList.InsertItem (l_iOffset, l_cpSkill->m_csSkillName);
			l_csValue.Format ("%d", l_cpSkill->m_iSkillValue);
			m_cCraftList.SetItemText (l_iOffset, 1, l_csValue);

			//if (l_cpSkill->m_iWorkTierMin > 0)
			//{
			//	if (l_cpSkill->m_iWorkTierMin == l_cpSkill->m_iWorkTierMax)
			//	{
			//		l_csValue.Format ("Tier %d", l_cpSkill->m_iWorkTierMin);
			//		m_cCraftList.SetItemText (l_iOffset, 2, l_csValue);
			//	}
			//	else
			//	{
			//		l_csValue.Format ("Tier %d->%d", l_cpSkill->m_iWorkTierMin, l_cpSkill->m_iWorkTierMax);
			//		m_cCraftList.SetItemText (l_iOffset, 2, l_csValue);
			//	}
			//}
			//else 
			//{
			//	m_cCraftList.SetItemText (l_iOffset, 2, "-");
			//}

			l_iOffset++;
		}
	}
}

CProfilePage2::DisplayCraftSkills()
{
	POSITION l_Pos;
	CBonus *l_cpBonus;
	CString l_csValue;
	int l_iOffset;

	m_cCraftList.DeleteAllItems ();
	m_cCraftList.DeleteColumn (0);
	m_cCraftList.DeleteColumn (0);
	m_cCraftList.DeleteColumn (0);
	m_cCraftList.InsertColumn (0, "Skill", LVCFMT_LEFT, 130, -1);
	m_cCraftList.InsertColumn (1, "Amount", LVCFMT_RIGHT, 68, -1);

	if (CAppData::m_cpCurrentProfile)
	{
		l_iOffset = 0;
		l_Pos = CAppData::m_cpCurrentProfile->m_clCraftSkillsList.GetHeadPosition ();
		while (l_Pos)
		{
			l_cpBonus = CAppData::m_cpCurrentProfile->m_clCraftSkillsList.GetNext (l_Pos);
			l_csValue.Format ("%d", l_cpBonus->m_iValue);
			m_cCraftList.InsertItem (l_iOffset, l_cpBonus->m_csBonusName);
			m_cCraftList.SetItemText (l_iOffset, 1, l_csValue);
			l_iOffset++;
		}
	}
}

void CProfilePage2::OnOptschools() 
{
	// TODO: Add your control notification handler code here
	DisplayProfile() ;
}

void CProfilePage2::OnOptskills() 
{
	// TODO: Add your control notification handler code here
	DisplayProfile() ;
}

BOOL CProfilePage2::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_cCraftList.SetBkColor (CScheme::GetColour ("TREE_BACKCOLOUR"));
	m_cCraftList.SetTextBkColor (CScheme::GetColour ("TREE_BACKCOLOUR"));
	m_bLoaded = true;
	m_cOptSkills.SetCheck(1);
	DisplayProfile() ;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CProfilePage2::OnDblclkCraftlist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int l_iOffset = m_cCraftList.GetSelectionMark ();
	CString l_csItem;
	CString l_csItemValue;

	if (l_iOffset >= 0)
	{
		if (CAppData::m_cpCurrentProfile->m_csProfileType != cAppData_Profile_Defaults)
		{
			l_csItem = m_cCraftList.GetItemText (l_iOffset, 0);
			l_csItemValue = m_cCraftList.GetItemText (l_iOffset, 1);

			if (m_cOptSchools.GetCheck () != 0)
			{
				CSkillDialog l_cSkillDialog(this);
				l_cSkillDialog.m_csMsg = l_csItem;
				l_cSkillDialog.m_csValue = l_csItemValue;
				GetWindowRect (l_cSkillDialog.m_cRect);
				this->EnableWindow (false);
				if (l_cSkillDialog.DoModal () == IDOK)
				{
					if (CAppData::m_cpCurrentProfile->UpdateCraftSchool (l_csItem, atoi (l_cSkillDialog.m_csValue)))
					{
						CAppData::SetProfilesChangeState (true);
						CAppData::m_cProfileWnd.DrawProfileTree ();

						m_cCraftList.SetItemText (l_iOffset, 1, l_cSkillDialog.m_csValue);
					}
				}
				this->EnableWindow (true);
			}
			else
			{
				CSkillDialog l_cSkillDialog(this);
				l_cSkillDialog.m_csMsg = l_csItem;
				l_cSkillDialog.m_csValue = l_csItemValue;
				GetWindowRect (l_cSkillDialog.m_cRect);
				this->EnableWindow (false);
				if (l_cSkillDialog.DoModal () == IDOK)
				{
					if (CAppData::m_cpCurrentProfile->UpdateCraftSkill (l_csItem, atoi (l_cSkillDialog.m_csValue)))
					{
						CAppData::SetProfilesChangeState (true);
						CAppData::m_cItemCreationWnd.DisplayFormula (false);

						m_cCraftList.SetItemText (l_iOffset, 1, l_cSkillDialog.m_csValue);
					}
				}
				this->EnableWindow (true);
			}
		}
	}
	*pResult = 0;
}

BOOL CProfilePage2::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	return (TRUE);
}
