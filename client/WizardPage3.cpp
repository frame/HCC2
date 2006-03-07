// WizardPage3.cpp : implementation file
//

#include "stdafx.h"
#include "HCC.h"
#include "WizardPage3.h"
#include "AppData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWizardPage3 property page

IMPLEMENT_DYNCREATE(CWizardPage3, CPropertyPage)

CWizardPage3::CWizardPage3() : CPropertyPage(CWizardPage3::IDD)
{
	//{{AFX_DATA_INIT(CWizardPage3)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CWizardPage3::~CWizardPage3()
{
}

void CWizardPage3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWizardPage3)
	DDX_Control(pDX, IDC_DESC, m_cDesc);
	DDX_Control(pDX, IDC_TECHTREE, m_cTechTree);
	DDX_Control(pDX, IDC_INFO, m_cInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWizardPage3, CPropertyPage)
	//{{AFX_MSG_MAP(CWizardPage3)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TECHTREE, OnSelchangedTechtree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizardPage3 message handlers


BOOL CWizardPage3::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	//m_cpWizardDialog->SetFinishText ("Generate");
	m_cpWizardDialog->SetWizardButtons (PSWIZB_BACK|PSWIZB_FINISH);
	m_cInfo.SetWindowText ("Choose the Techniques you are most interested in for this order. By default, the techniques shown have been carefully selected and ordered based on the class you have chosen. Use the Higher/Lower buttons to adjust the importance of each one to your liking. Click 'Create!' to generate your order (this will remove any existing order if you do not choose to append).");	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CWizardPage3::UpdateTechs()
{
	POSITION l_Pos;
	CSchoolWizard *l_cpWizard = m_cpWizardDialog1->m_cpSchoolWizard;
	CString l_csStr;
	HTREEITEM l_Item;
	int l_iCount;
	int l_iOffset = 0;

	m_cTechTree.ModifyStyle (TVS_CHECKBOXES, 0, 0 );
	m_cTechTree.ModifyStyle (0, TVS_CHECKBOXES, 0 );

	if (l_cpWizard)
	{
		l_iCount = m_cTechTree.GetCount ();
		//m_cCategoryTree.DeleteAllItems ();

		l_Pos = l_cpWizard->m_clTechList.GetHeadPosition ();
		while (l_Pos)
		{
			l_csStr = l_cpWizard->m_clTechList.GetNext (l_Pos);

			l_Item = m_cTechTree.InsertItem (l_csStr,0,0,TVI_ROOT, TVI_LAST);
			m_cTechTree.SetItemData (l_Item, l_iOffset++);
			m_cTechTree.SetCheck (l_Item, true);
		}

		while (l_iCount--)
		{
			m_cTechTree.DeleteItem (m_cTechTree.GetRootItem ());
		}
	}
}

BOOL CWizardPage3::OnSetActive() 
{
	UpdateTechs();	
	return CPropertyPage::OnSetActive();
}

void CWizardPage3::OnSelchangedTechtree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	HTREEITEM l_Item;
	CString l_csTech;
	CTech *l_cpTech;

	l_Item = m_cTechTree.GetSelectedItem ();
	if (l_Item)
	{
		l_csTech = m_cTechTree.GetItemText (l_Item);
		if (CAppData::FindTech (cNo_Filter, l_csTech, &l_cpTech))
		{
			m_cDesc.SetWindowText (l_cpTech->m_csDescription);
		}
	}

	*pResult = 0;
}
