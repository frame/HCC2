// WizardPage2.cpp : implementation file
//

#include "stdafx.h"
#include "HCC.h"
#include "WizardPage2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWizardPage2 property page

IMPLEMENT_DYNCREATE(CWizardPage2, CPropertyPage)

CWizardPage2::CWizardPage2() : CPropertyPage(CWizardPage2::IDD)
{
	//{{AFX_DATA_INIT(CWizardPage2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CWizardPage2::~CWizardPage2()
{
}

void CWizardPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWizardPage2)
	DDX_Control(pDX, IDC_DESC, m_cDesc);
	DDX_Control(pDX, IDC_INFO, m_cInfo);
	DDX_Control(pDX, IDC_CATEGORYTREE, m_cCategoryTree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWizardPage2, CPropertyPage)
	//{{AFX_MSG_MAP(CWizardPage2)
	ON_NOTIFY(TVN_SELCHANGED, IDC_CATEGORYTREE, OnSelchangedCategorytree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizardPage2 message handlers

BOOL CWizardPage2::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_cpWizardDialog->SetWizardButtons (PSWIZB_BACK|PSWIZB_NEXT);
	m_cInfo.SetWindowText ("Select the categories of items you wish to include as part of the automatic order creation process. A description of each category will be displayed to the right when you select a category. At this stage don't worry about being too precise about which ones you are interested in, as you can always delete the ones you don't want in the Order Window.");	

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CWizardPage2::UpdateCategories()
{
	CWizardInfo *l_cpWizardInfo;
	POSITION l_Pos;
	CSchoolWizard *l_cpWizard = m_cpWizardDialog1->m_cpSchoolWizard;
	CString l_csStr;
	HTREEITEM l_Item;
	int l_iCount;
	int l_iOffset = 0;

	m_cCategoryTree.ModifyStyle (TVS_CHECKBOXES, 0, 0 );
	m_cCategoryTree.ModifyStyle (0, TVS_CHECKBOXES, 0 );

	if (l_cpWizard)
	{
		l_iCount = m_cCategoryTree.GetCount ();
		//m_cCategoryTree.DeleteAllItems ();

		l_Pos = l_cpWizard->m_clFormulaSetList.GetHeadPosition ();
		while (l_Pos)
		{
			l_cpWizardInfo = l_cpWizard->m_clFormulaSetList.GetNext (l_Pos);

			if (l_cpWizardInfo->m_csFilter.IsEmpty ())
			{
				l_csStr = l_cpWizardInfo->m_csFormulaSetName;
			}
			else
			{
				l_csStr = l_cpWizardInfo->m_csFormulaSetName + " (" + l_cpWizardInfo->m_csFilter + ")";
			}

			l_Item = m_cCategoryTree.InsertItem (l_csStr,0,0,TVI_ROOT, TVI_LAST);
			m_cCategoryTree.SetItemData (l_Item, l_iOffset++);

			if (!l_cpWizardInfo->m_bOptional)
			{
				m_cCategoryTree.SetCheck (l_Item, true);
			}
		}

		while (l_iCount--)
		{
			m_cCategoryTree.DeleteItem (m_cCategoryTree.GetRootItem ());
		}
	}
}


BOOL CWizardPage2::OnSetActive() 
{
	UpdateCategories();
	
	return CPropertyPage::OnSetActive();
}

void CWizardPage2::OnSelchangedCategorytree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	CWizardInfo *l_cpWizardInfo = NULL;
	CSchoolWizard *l_cpWizard = m_cpWizardDialog1->m_cpSchoolWizard;
	POSITION l_Pos;
	HTREEITEM l_Item;
	int l_iOffset;

	if (l_cpWizard)
	{
		l_Item = m_cCategoryTree.GetSelectedItem ();
		if (l_Item)
		{
			l_iOffset = m_cCategoryTree.GetItemData (l_Item);
			l_Pos = l_cpWizard->m_clFormulaSetList.GetHeadPosition ();

			while (l_Pos)
			{
				l_cpWizardInfo = l_cpWizard->m_clFormulaSetList.GetNext (l_Pos);

				if (l_iOffset == 0)
				{
					l_Pos = NULL;
				}
				else
				{
					l_iOffset--;
				}
			}

			if (l_cpWizardInfo)
			{
				m_cDesc.SetWindowText (l_cpWizardInfo->m_csDescription);
			}
		}
	}

	*pResult = 0;
}
