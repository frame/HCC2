// InputListDialog.cpp : implementation file
//

#include "stdafx.h"
#include "HCC.h"
#include "InputListDialog.h"
#include "AppData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInputListDialog dialog


CInputListDialog::CInputListDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CInputListDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInputListDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CInputListDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputListDialog)
	DDX_Control(pDX, IDC_INPUTCOMBO, m_cInputCombo);
	DDX_Control(pDX, IDC_INPUTMSG, m_cInputMsg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInputListDialog, CDialog)
	//{{AFX_MSG_MAP(CInputListDialog)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputListDialog message handlers

BOOL CInputListDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_cInputMsg.SetWindowText (m_csInputMsg);
	this->SetWindowText (m_csTitleMsg);
	CAppData::ClearComboBox (m_cInputCombo);

	POSITION l_Pos = m_csInputList.GetHeadPosition ();
	while (l_Pos)
	{
		m_cInputCombo.AddString (m_csInputList.GetNext (l_Pos));
	}
	m_cInputCombo.SetCurSel (0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInputListDialog::OnOK() 
{
	m_cInputCombo.GetWindowText (m_csSelectedInput);	
	CDialog::OnOK();
}

BOOL CInputListDialog::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	return (TRUE);
}
