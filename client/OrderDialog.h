#if !defined(AFX_ORDERDIALOG_H__3A324D32_3697_40D4_AA76_DF8BDC5845FD__INCLUDED_)
#define AFX_ORDERDIALOG_H__3A324D32_3697_40D4_AA76_DF8BDC5845FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OrderDialog.h : header file
//

#include "WindowState.h"
#include "ObjectSpace.h"
#include "TreeCtrlX.h"

/////////////////////////////////////////////////////////////////////////////
// COrderDialog dialog

class COrderDialog : public CDialog
{
// Construction
public:
	PromoteTechsTiersToFormulaTier();
	DisplayOrderTitle();
	COrderDialog(CWnd* pParent = NULL);   // standard constructor

	DisplayTotalQty (int a_iQty, int a_iFormQty);
	DisplayOrderItem (int a_iOrderId);
	HTREEITEM FindOrderGroup (CString &a_csGroup);
	void DisplayOrder();
	Initialise();
	void Resize();
	StartUp();

// Dialog Data
	//{{AFX_DATA(COrderDialog)
	enum { IDD = IDD_ORDERDIALOG };
	CButton	m_cAlignTiers;
	CListCtrl	m_cTechList;
	CSpinButtonCtrl	m_cQtySpin;
	CButton	m_cOrderFrame;
	CButton	m_cNewGroupButton;
	CTreeCtrlX	m_cItemTree;
	CStatic	m_cItemTotalQty;
	CEdit	m_cItemQty;
	CStatic	m_cItemName;
	CButton	m_cDeleteButton;
	CButton	m_cCopyToClipboardButton;
	CButton	m_cCopyItemButton;
	//}}AFX_DATA

	CWindowState m_cWindowState;
	CObjectSpace m_cOS_ItemTree;
	CObjectSpace m_cOS_OrderFrame;
	CObjectSpace m_cOS_ItemInfoList;
	CObjectSpace m_cOS_ItemQty;
	CObjectSpace m_cOS_ItemQtySpin;
	CObjectSpace m_cOS_ItemTotalQty;
	CObjectSpace m_cOS_CopyToClipboardButton;
	CObjectSpace m_cOS_CopyItemButton;
	CObjectSpace m_cOS_AlignTiers;
	CObjectSpace m_cOS_Delete;
	CObjectSpace m_cOS_TechList;
	CObjectSpace m_cOS_NewGroup;

	bool m_bItemTreeExpand;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COrderDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COrderDialog)
	afx_msg void OnWindowPosChanging( WINDOWPOS* lpwndpos );
	afx_msg void OnMoving( UINT nSide, LPRECT lpRect );
	afx_msg void OnGetMinMaxInfo (MINMAXINFO* lpMMI) ;
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveas();
	afx_msg void OnSelectionSelectnone();
	afx_msg void OnSelectionSelectall();
	afx_msg void OnSelectionInvertselection();
	afx_msg void OnSelectionCopytoclipboard();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnChangeItemqty();
	afx_msg void OnDeletebutton();
	afx_msg void OnNewgroupbutton();
	afx_msg void OnDeltaposQtyspin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCopytoclipboard();
	afx_msg void OnCopyitem();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnItemexpandingItemtree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangedItemtree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeleditItemtree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClose();
	afx_msg void OnOptionsSnapshotwindow();
	afx_msg void OnOptionsRestorewindow();
	afx_msg void OnHelpIndex();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnWindowAlwaysontop();
	afx_msg void OnClickItemtree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangingItemtree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnAligntiers();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ORDERDIALOG_H__3A324D32_3697_40D4_AA76_DF8BDC5845FD__INCLUDED_)
