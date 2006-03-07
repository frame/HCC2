// SkillLevelDialog.cpp : implementation file
//

#include "stdafx.h"
#include "HCC.h"
#include "SkillLevelDialog.h"
#include "AppData.h"
#include "Scheme.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkillLevelDialog dialog


CSkillLevelDialog::CSkillLevelDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSkillLevelDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSkillLevelDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSkillLevelDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSkillLevelDialog)
	DDX_Control(pDX, IDC_SKILLNAME, m_cSkillName);
	DDX_Control(pDX, IDC_RESOURCELIST, m_cResourceList);
	DDX_Control(pDX, IDC_SKILLGRID, m_cSkillGrid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSkillLevelDialog, CDialog)
	//{{AFX_MSG_MAP(CSkillLevelDialog)
	ON_LBN_SELCHANGE(IDC_RESOURCELIST, OnSelchangeResourcelist)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkillLevelDialog message handlers

CSkillLevelDialog::StartUp()
{
	this->Create (IDD_LEVELDIALOG, CWnd::GetDesktopWindow ());
	m_cWindowState.m_bLoaded = true;
	m_cSkillGrid.SetBackColor (CScheme::GetColour ("GRID_BACKCOLOUR"));
	m_cSkillGrid.SetBackColorBkg (CScheme::GetColour ("GRID_BACKCOLOUR"));
	m_cSkillGrid.SetGridColor (CScheme::GetColour ("GRID_LINECOLOUR_LIGHT"));
	m_cSkillGrid.SetGridColorFixed (CScheme::GetColour ("GRID_LINECOLOUR_DARK"));
	m_cSkillGrid.SetForeColorSel (CScheme::GetColour ("SELECTCOLOUR_FG"));
	m_cSkillGrid.SetBackColorSel (CScheme::GetColour ("SELECTCOLOUR_BG"));
}


CSkillLevelDialog::DisplaySkillLevels()
{
	CFormulaTier *l_cpFormulaTier;
	CItemResource *l_cpItemResource;
	POSITION l_Pos;
	CString l_csSelectName;

	if (CAppData::m_cpCurrentFormula)
	{
		m_cResourceList.GetText (m_cResourceList.GetCurSel (), l_csSelectName);

		while (m_cResourceList.DeleteString (0) != LB_ERR );

		if (CAppData::FindFormulaTier (CAppData::m_cpCurrentFormula->m_csCategory, CAppData::m_cpCurrentFormula->m_csName, CAppData::m_csCurrentFormulaTierName, &l_cpFormulaTier))
		{
			l_Pos = l_cpFormulaTier->m_clResourceList.GetHeadPosition ();
			while (l_Pos)
			{
				l_cpItemResource = l_cpFormulaTier->m_clResourceList.GetNext (l_Pos);
				m_cResourceList.AddString (l_cpItemResource->m_csName);

				if (l_csSelectName.IsEmpty ())
				{
					l_csSelectName = l_cpItemResource->m_csName;
				}
			}

			if (m_cResourceList.SelectString (-1, l_csSelectName) == LB_ERR)
			{
				m_cResourceList.SetCurSel (0);
			}

			OnSelchangeResourcelist();
		}
	}
}

void CSkillLevelDialog::OnSelchangeResourcelist() 
{
	CFormulaTier *l_cpFormulaTier;
	CItemResource *l_cpItemResource;
	POSITION l_Pos;
	CString l_csSelectName;
	int l_iIndex;
	CString l_csStr;

	if (CAppData::m_cpCurrentFormula)
	{
		if (CAppData::FindFormulaTier (CAppData::m_cpCurrentFormula->m_csCategory, CAppData::m_cpCurrentFormula->m_csName, CAppData::m_csCurrentFormulaTierName, &l_cpFormulaTier))
		{
			l_Pos = l_cpFormulaTier->m_clResourceList.GetHeadPosition ();
			while (l_Pos)
			{
				l_cpItemResource = l_cpFormulaTier->m_clResourceList.GetNext (l_Pos);
				m_cResourceList.GetText (m_cResourceList.GetCurSel (), l_csSelectName);

				if (l_cpItemResource->m_csName == l_csSelectName)
				{
					m_cSkillName.SetWindowText (l_cpItemResource->m_csSkill);
					m_cSkillGrid.SetRows (1);
					m_cSkillGrid.SetFormatString ("^Efficiency|^Skill Needed");
					m_cSkillGrid.SetColWidth (1, 1300);

					for (l_iIndex=l_cpItemResource->m_iMinAmt; l_iIndex>=l_cpItemResource->m_iOptAmt; l_iIndex--)
					{
						l_csStr.Format ("%d:%d\t%d", l_iIndex, CAppData::m_cpCurrentFormula->m_iBatchQty, l_cpItemResource->DetermineSkillForAmount (l_iIndex));
						m_cSkillGrid.AddRow (l_csStr,GRID_SKILL);
					}
				}

				m_cSkillGrid.SelectRow (1,true);
			}
		}
	}
}

BOOL CSkillLevelDialog::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	return (TRUE);
}

void CSkillLevelDialog::OnOK() 
{
	m_cWindowState.m_bVisible = false;
	
	CDialog::OnOK();
}

void CSkillLevelDialog::OnClose() 
{	
	m_cWindowState.m_bVisible = false;
	CDialog::OnClose();
}

void CSkillLevelDialog::OnCancel() 
{
	m_cWindowState.m_bVisible = false;
	CDialog::OnCancel();
}

