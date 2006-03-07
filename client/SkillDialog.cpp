// SkillDialog.cpp : implementation file
//

#include "stdafx.h"
#include "HCC.h"
#include "SkillDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkillDialog dialog


CSkillDialog::CSkillDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSkillDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSkillDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSkillDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSkillDialog)
	DDX_Control(pDX, IDC_INPUTMSG, m_cInputMsg);
	DDX_Control(pDX, IDC_INPUTEDIT, m_cInputEdit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSkillDialog, CDialog)
	//{{AFX_MSG_MAP(CSkillDialog)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkillDialog message handlers

BOOL CSkillDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
   SetWindowPos (NULL, m_cRect.left ,
	              m_cRect.top + ((m_cRect.bottom - m_cRect.top) / 2), 0, 0, SWP_NOSIZE);
	m_cInputMsg.SetWindowText (m_csMsg);
	m_cInputEdit.SetWindowText (m_csValue);
	m_cInputEdit.SetLimitText (5);
	m_cInputEdit.SetFocus ();
	m_cInputEdit.SetSel (0, -1);
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSkillDialog::OnOK() 
{
	m_cInputEdit.GetWindowText (m_csValue);
	
	CDialog::OnOK();
}

BOOL CSkillDialog::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	return (TRUE);
}
