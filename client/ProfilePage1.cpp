// ProfilePage1.cpp : implementation file
//

#include "stdafx.h"
#include "HCC.h"
#include "ProfilePage1.h"
#include "SkillDialog.h"
#include "AppData.h"
#include "Scheme.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProfilePage1 property page

IMPLEMENT_DYNCREATE(CProfilePage1, CPropertyPage)

CProfilePage1::CProfilePage1() : CPropertyPage(CProfilePage1::IDD)
{
	//{{AFX_DATA_INIT(CProfilePage1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CProfilePage1::~CProfilePage1()
{
}

void CProfilePage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProfilePage1)
	DDX_Control(pDX, IDC_STATISTICSLIST, m_cStatistcsList);
	DDX_Control(pDX, IDC_SERVERCOMBO, m_cProfileServerCombo);
	DDX_Control(pDX, IDC_EMAIL, m_cProfileEmail);
	DDX_Control(pDX, IDC_NAME, m_cProfileName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProfilePage1, CPropertyPage)
	//{{AFX_MSG_MAP(CProfilePage1)
	ON_NOTIFY(NM_DBLCLK, IDC_STATISTICSLIST, OnDblclkStatisticslist)
	ON_EN_CHANGE(IDC_NAME, OnChangeName)
	ON_CBN_SELCHANGE(IDC_SERVERCOMBO, OnSelchangeServercombo)
	ON_EN_CHANGE(IDC_EMAIL, OnChangeEmail)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProfilePage1 message handlers

BOOL CProfilePage1::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cStatistcsList.SetBkColor (CScheme::GetColour ("TREE_BACKCOLOUR"));
	m_cStatistcsList.SetTextBkColor (CScheme::GetColour ("TREE_BACKCOLOUR"));
	m_cProfileEmail.SetLimitText (64);
	m_cProfileName.SetLimitText (32);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CProfilePage1::OnDblclkStatisticslist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int l_iOffset = m_cStatistcsList.GetSelectionMark ();
	CString l_csItem;
	CString l_csItemValue;

	if ((l_iOffset >= 0) && (CAppData::m_cpCurrentProfile))
	{
		if (CAppData::m_cpCurrentProfile->m_csProfileType != cAppData_Profile_Defaults)
		{
			l_csItem = m_cStatistcsList.GetItemText (l_iOffset, 0);
			l_csItemValue = m_cStatistcsList.GetItemText (l_iOffset, 1);

			CSkillDialog l_cSkillDialog (this);
			l_cSkillDialog.m_csMsg = l_csItem;
			l_cSkillDialog.m_csValue = l_csItemValue;
			GetWindowRect (l_cSkillDialog.m_cRect);
			this->EnableWindow (false);
			if (l_cSkillDialog.DoModal () == IDOK)
			{
				if (CAppData::m_cpCurrentProfile->UpdateStatistic (l_csItem, atoi (l_cSkillDialog.m_csValue)))
				{
					CAppData::SetProfilesChangeState (true);
					CAppData::m_cProfileWnd.DrawProfileTree ();

					m_cStatistcsList.SetItemText (l_iOffset, 1, l_cSkillDialog.m_csValue);
				}
			}
			this->EnableWindow (true);
		}
	}
	
	*pResult = 0;
}

void CProfilePage1::OnChangeName() 
{
}

void CProfilePage1::OnSelchangeServercombo() 
{
}

void CProfilePage1::OnChangeEmail() 
{
	CString l_csText;

	if (CAppData::m_cpCurrentProfile)
	{
		m_cProfileEmail.GetWindowText (l_csText);
		
		if (l_csText != CAppData::m_cpCurrentProfile->m_csProfileEmail)
		{
			CAppData::m_cpCurrentProfile->m_csProfileEmail = l_csText;
			CAppData::SetProfilesChangeState (true);
			CAppData::m_cpCurrentProfile->m_bChanged = true;
		}
	}
}

BOOL CProfilePage1::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	return (TRUE);
}
