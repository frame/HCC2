// InputDialog.cpp : implementation file
//

#include "stdafx.h"
#include "HCC.h"
#include "InputDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInputDialog dialog


CInputDialog::CInputDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CInputDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInputDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CInputDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputDialog)
	DDX_Control(pDX, IDC_INPUTMSG, m_cInputMsg);
	DDX_Control(pDX, IDC_INPUTEDIT, m_cInputEdit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInputDialog, CDialog)
	//{{AFX_MSG_MAP(CInputDialog)
	ON_WM_SHOWWINDOW()
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputDialog message handlers

void CInputDialog::OnOK() 
{
	m_cInputEdit.GetWindowText (m_csInput);

	if (!m_csInput.IsEmpty ())
	{
		m_csInput.Replace ('<', '[');
		m_csInput.Replace ('>', ']');
		m_csInput.Replace ("&", "and");
		CDialog::OnOK();
	}

}

BOOL CInputDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	this->SetWindowText (m_csTitleMsg);
	m_cInputMsg.SetWindowText (m_csInputMsg);
	m_cInputEdit.SetLimitText (64);
	m_cInputEdit.SetFocus ();
	m_cInputEdit.SetSel (-1);
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CInputDialog::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{

	return CDialog::Create(IDD, pParentWnd);
}

void CInputDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	if (bShow)
	{
		m_cInputEdit.SetFocus ();
		m_cInputEdit.SetSel (-1);
	}
}

BOOL CInputDialog::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	return (TRUE);
}
