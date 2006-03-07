// WizardDialog.cpp : implementation file
//

#include "stdafx.h"
#include "HCC.h"
#include "WizardDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWizardDialog

IMPLEMENT_DYNAMIC(CWizardDialog, CPropertySheet)

CWizardDialog::CWizardDialog(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CWizardDialog::CWizardDialog(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CWizardDialog::~CWizardDialog()
{
}


BEGIN_MESSAGE_MAP(CWizardDialog, CPropertySheet)
	//{{AFX_MSG_MAP(CWizardDialog)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizardDialog message handlers

BOOL CWizardDialog::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
   CWnd *pWnd = GetDlgItem (IDHELP);
   pWnd->ShowWindow (FALSE);

	 return bResult;
}
