#if !defined(AFX_TREECTRLX_H__02D65514_0E19_415B_8EDF_D3D4E9CA6B0C__INCLUDED_)
#define AFX_TREECTRLX_H__02D65514_0E19_415B_8EDF_D3D4E9CA6B0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TreeCtrlX.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlX window

class CTreeCtrlX : public CTreeCtrl
{
// Construction
public:
	CTreeCtrlX();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeCtrlX)
	//}}AFX_VIRTUAL

// Implementation
public:
	int GetItemLevel (HTREEITEM a_iTreeItem);
	virtual ~CTreeCtrlX();
	HTREEITEM FindTreeItem(CString a_csItemName, int a_iLevels);
	HTREEITEM FindTreeItem(CString &a_csItemName, HTREEITEM a_hParentTreeItem, int a_iLevels);

	// Generated message map functions
protected:
	//{{AFX_MSG(CTreeCtrlX)
	afx_msg void OnBeginDrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	BOOL CTreeCtrlX::PreTranslateMessage(MSG* pMsg);
	CImageList*	m_pDragImage;
	BOOL		m_bLDragging;
	HTREEITEM m_hitemDrag,m_hitemDrop;
	BOOL OnEraseBkgnd(CDC* pDC);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREECTRLX_H__02D65514_0E19_415B_8EDF_D3D4E9CA6B0C__INCLUDED_)
