// OrderItem.cpp: implementation of the COrderItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HCC.h"
#include "OrderItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

int COrderItem::m_iNextId = 1;


COrderItem::COrderItem()
{
	m_iId = 0;
}

COrderItem::~COrderItem()
{
	m_clTechList.RemoveAll ();
}

COrderItem::operator =( const COrderItem& pSrc )
{
   CopyObject (pSrc);
   return true;
}


COrderItem::COrderItem(const COrderItem &pSrc)
{
   CopyObject (pSrc);
}

void COrderItem::CopyObject(const COrderItem &pSrc)
{
	m_csItemName = pSrc.m_csItemName;
	m_csCategory = pSrc.m_csCategory;
	m_csFormulaName = pSrc.m_csFormulaName;
	m_csTierName = pSrc.m_csTierName;
	m_iQty = pSrc.m_iQty;
	m_csOrderGroup = pSrc.m_csOrderGroup;
	m_iId = pSrc.m_iId;

	m_clTechList.RemoveAll ();
	POSITION l_Pos = pSrc.m_clTechList.GetHeadPosition ();
	while (l_Pos)
	{
		m_clTechList.AddTail (pSrc.m_clTechList.GetNext (l_Pos));
	}

}


COrderItem::AssignId()
{
	m_iId = COrderItem::m_iNextId;
	COrderItem::m_iNextId++;
}

