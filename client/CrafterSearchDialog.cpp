// CrafterSearchDialog.cpp : implementation file
//

#include "stdafx.h"
#include "HCC.h"
#include "CrafterSearchDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCrafterSearchDialog dialog


CCrafterSearchDialog::CCrafterSearchDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CCrafterSearchDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCrafterSearchDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCrafterSearchDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCrafterSearchDialog)
	DDX_Control(pDX, IDC_VIEWPROFILEBUTTON, m_cViewProfileButton);
	DDX_Control(pDX, IDC_SUBMITREQUESTBUTTON, m_cSubmitRequestButton);
	DDX_Control(pDX, IDC_SHARDCOMBO, m_cShardCombo);
	DDX_Control(pDX, IDC_SEARCHLIST, m_cSearchList);
	DDX_Control(pDX, IDC_SEARCHFRAME, m_cSearchFrame);
	DDX_Control(pDX, IDC_SEARCHBUTTON, m_cSearchButton);
	DDX_Control(pDX, IDC_NAMECOMBO, m_cNameCombo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCrafterSearchDialog, CDialog)
	//{{AFX_MSG_MAP(CCrafterSearchDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCrafterSearchDialog message handlers
