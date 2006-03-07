// OrderItem.h: interface for the COrderItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ORDERITEM_H__31A4AE90_5A5E_452B_AFF3_B15737F5C9AA__INCLUDED_)
#define AFX_ORDERITEM_H__31A4AE90_5A5E_452B_AFF3_B15737F5C9AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ItemTech.h"
#include "Tech.h"

class COrderItem  
{
public:
	AssignId ();
	COrderItem();
	virtual ~COrderItem();
	operator =( const COrderItem& pSrc );
	COrderItem(const COrderItem &pSrc);
	void CopyObject(const COrderItem &pSrc);

	CString m_csItemName;
	CString m_csOrderGroup;
	CString m_csFormulaName;
	CString m_csCategory;
	CString m_csTierName;
	int	  m_iQty;

	int	  m_iId;

	CList <CItemTech, CItemTech&>  m_clTechList;


	static int m_iNextId;
};

#endif // !defined(AFX_ORDERITEM_H__31A4AE90_5A5E_452B_AFF3_B15737F5C9AA__INCLUDED_)
