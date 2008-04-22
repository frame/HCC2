// ItemTech.cpp: implementation of the CItemTech class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HCC.h"
#include "ItemTech.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CItemTech::CItemTech()
{

}

CItemTech::~CItemTech()
{

}

CItemTech::operator =( const CItemTech& pSrc )
{
   CopyObject (pSrc);
   return true;
}


CItemTech::CItemTech(const CItemTech &pSrc)
{
   CopyObject (pSrc);
}

void CItemTech::CopyObject(const CItemTech &pSrc)
{
	m_csCategory = pSrc.m_csCategory;
	m_csTechName = pSrc.m_csTechName;
	m_csTierName = pSrc.m_csTierName;
}


