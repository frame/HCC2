// ItemTech.h: interface for the CItemTech class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITEMTECH_H__9E817406_6847_4BD3_84B8_E85DDA54FFE3__INCLUDED_)
#define AFX_ITEMTECH_H__9E817406_6847_4BD3_84B8_E85DDA54FFE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CItemTech  
{
public:
	CItemTech();
	virtual ~CItemTech();
	operator =( const CItemTech& pSrc );
	CItemTech(const CItemTech &pSrc);
	void CopyObject(const CItemTech &pSrc);

	CString m_csCategory;
	CString m_csTechName;
	CString m_csTierName;
};

#endif // !defined(AFX_ITEMTECH_H__9E817406_6847_4BD3_84B8_E85DDA54FFE3__INCLUDED_)
