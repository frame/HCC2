// TreeCtrlX.cpp : implementation file
//

#include "stdafx.h"
#include "HCC.h"
#include "TreeCtrlX.h"
#include "AppData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlX

CTreeCtrlX::CTreeCtrlX()
{
	m_bLDragging = false;
}	

CTreeCtrlX::~CTreeCtrlX()
{
}


BEGIN_MESSAGE_MAP(CTreeCtrlX, CTreeCtrl)
	//{{AFX_MSG_MAP(CTreeCtrlX)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBeginDrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CTreeCtrlX::PreTranslateMessage(MSG* pMsg) 
{
        if( pMsg->message == WM_KEYDOWN )
        {
                // When an item is being edited make sure the edit control
                // receives certain important key strokes
                if( GetEditControl() 
                                && (pMsg->wParam == VK_RETURN 
                                        || pMsg->wParam == VK_DELETE 
                                        || pMsg->wParam == VK_ESCAPE
                                        || GetKeyState( VK_CONTROL) 
                                        )
                        )
                {
                        ::TranslateMessage(pMsg);
                        ::DispatchMessage(pMsg);
                        return TRUE;                            // DO NOT process further
                }
        }

        return CTreeCtrl::PreTranslateMessage(pMsg);
}
/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlX message handlers

void CTreeCtrlX::OnBeginDrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	*pResult = 0;

	m_hitemDrag = pNMTreeView->itemNew.hItem;
	m_hitemDrop = NULL;

	m_pDragImage = CreateDragImage(m_hitemDrag);  // get the image list for dragging
	// CreateDragImage() returns NULL if no image list
	// associated with the tree view control
	if( !m_pDragImage )
		return;

	m_bLDragging = TRUE;
	m_pDragImage->BeginDrag(0, CPoint(-5,0));
	POINT pt = pNMTreeView->ptDrag;
	ClientToScreen( &pt );
	m_pDragImage->DragEnter(NULL, pt);
	SetCapture();
}

void CTreeCtrlX::OnMouseMove(UINT nFlags, CPoint point) 
{
	HTREEITEM	hitem;
	UINT		flags;

	if (m_bLDragging)
	{
		POINT pt = point;
		ClientToScreen( &pt );
		CImageList::DragMove(pt);
		if ((hitem = HitTest(point, &flags)) != NULL)
		{
			CImageList::DragShowNolock(FALSE);
			SelectDropTarget(hitem);
			m_hitemDrop = hitem;
			CImageList::DragShowNolock(TRUE);
		}
	}

	CTreeCtrl::OnMouseMove(nFlags, point);
}

void CTreeCtrlX::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CTreeCtrl::OnLButtonUp(nFlags, point);
	HTREEITEM l_ParentStart;
	HTREEITEM l_ParentEnd;
	int l_iStartOrderId;
	//int l_iEndOrderId;
	CString l_csGroup;
	COrderItem l_cOrderItem;

	if (m_bLDragging)
	{
		m_bLDragging = FALSE;
		CImageList::DragLeave(this);
		CImageList::EndDrag();
		ReleaseCapture();

		delete m_pDragImage;

		// Remove drop target highlighting
		SelectDropTarget(NULL);

		if( m_hitemDrag == m_hitemDrop )
			return;

		l_ParentStart = GetParentItem (m_hitemDrag);
		l_ParentEnd = GetParentItem (m_hitemDrop);

		// Is this an OrderItem
		if (l_ParentStart)
		{
			l_iStartOrderId = GetItemData (m_hitemDrag);

			if (!l_ParentEnd)
			{
				l_ParentEnd = m_hitemDrop;
			}

			l_csGroup = GetItemText (l_ParentEnd);

			if (CAppData::FindOrderItem (l_iStartOrderId, l_cOrderItem))
			{
				l_cOrderItem.m_csOrderGroup = l_csGroup;
				CAppData::UpdateOrderItem (l_cOrderItem);
				CAppData::m_cOrderWnd.DisplayOrder ();
			}

		}
		else
		{
			// Else Ordergroup
		}

	}

}

HTREEITEM CTreeCtrlX::FindTreeItem(CString a_csItemName, int a_iLevels)
{
	return (FindTreeItem (a_csItemName, GetRootItem (), a_iLevels));
}

HTREEITEM CTreeCtrlX::FindTreeItem(CString &a_csItemName, HTREEITEM a_hParentTreeItem, int a_iLevels)
{
	HTREEITEM l_hChildItem = NULL;
	CString l_csText;
	int l_iOffset;

	if (a_hParentTreeItem)
	{
		l_csText = GetItemText (a_hParentTreeItem);
		l_iOffset = l_csText.Find ('(');
		if (l_iOffset >= 0)
		{
			l_csText = l_csText.Left (l_iOffset);
			l_csText.TrimRight ();
		}

		if (l_csText == a_csItemName)
		{
			return (a_hParentTreeItem);
		}

		if (a_iLevels > 0)
		{
			l_hChildItem = FindTreeItem (a_csItemName, GetChildItem (a_hParentTreeItem), a_iLevels - 1);
		}

		if (!l_hChildItem)
		{
			return (FindTreeItem (a_csItemName, GetNextSiblingItem (a_hParentTreeItem), a_iLevels));
		}
		else
		{
			return (l_hChildItem);
		}
	}

	return (NULL);
}


int CTreeCtrlX::GetItemLevel(HTREEITEM a_iTreeItem)
{
	int l_iLevel = 0;
	HTREEITEM l_LvlTreeItem;

	l_LvlTreeItem = a_iTreeItem;
	while (l_LvlTreeItem)
	{
		l_LvlTreeItem = GetParentItem (l_LvlTreeItem);
		l_iLevel++;
	}

	return (l_iLevel);
}

BOOL CTreeCtrlX::OnEraseBkgnd(CDC* pDC)
{
   return FALSE;
}
