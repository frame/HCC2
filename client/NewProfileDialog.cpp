// NewProfileDialog.cpp : implementation file
//

#include "stdafx.h"
#include "HCC.h"
#include "NewProfileDialog.h"
#include "Profile.h"
#include "AppData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewProfileDialog dialog


CNewProfileDialog::CNewProfileDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CNewProfileDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewProfileDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CNewProfileDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewProfileDialog)
	DDX_Control(pDX, IDC_SERVERCOMBO, m_cServerCombo);
	DDX_Control(pDX, IDC_NAME, m_cName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewProfileDialog, CDialog)
	//{{AFX_MSG_MAP(CNewProfileDialog)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewProfileDialog message handlers

BOOL CNewProfileDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
   SetWindowPos (NULL, m_cRect.left ,
	              m_cRect.top + ((m_cRect.bottom - m_cRect.top) / 2), 0, 0, SWP_NOSIZE);
	m_cName.SetWindowText (m_csName);
	m_cName.SetLimitText (32);

	m_cServerCombo.SelectString (-1, m_csServer);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNewProfileDialog::OnOK() 
{
	CProfile *l_cpProfile;

	m_cName.GetWindowText (m_csName);
	m_cServerCombo.GetWindowText (m_csServer);

	if (m_csName.IsEmpty ())
	{
		MessageBox ("Profile Name cannot be empty", "Input Error", MB_ICONEXCLAMATION);
	}
	else
	{
		m_csName.Replace ('<', '[');
		m_csName.Replace ('>', ']');
		m_csName.Replace ("&", "and");

		if (CAppData::FindProfile (m_csName, m_csServer, &l_cpProfile))
		{
			MessageBox ("Profile already exists for this Server. Please rename and try again", "Input Error", MB_ICONEXCLAMATION);
		}
		else
		{
			CDialog::OnOK();
		}
	}
}

BOOL CNewProfileDialog::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	return (TRUE);
}
