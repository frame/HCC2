// ItemInfo.cpp: implementation of the CItemInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ItemInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CItemInfo::CItemInfo()
{

}

CItemInfo::~CItemInfo()
{

}

CItemInfo::operator =( const CItemInfo* pSrc )
{
   CopyObject (pSrc);
   return true;
}


CItemInfo::CItemInfo(const CItemInfo *pSrc)
{
   CopyObject (pSrc);
}

void CItemInfo::CopyObject(const CItemInfo *pSrc)
{
	m_csInfoName	= pSrc->m_csInfoName;
	m_csInfoValue	= pSrc->m_csInfoValue;
}

CItemInfo::Clear()
{
	m_csInfoName.Empty ();
	m_csInfoValue.Empty ();
}

CItemInfo::Destroy()
{

}

CItemInfo::WriteToFile(CStdioFile &a_cFile)
{
	CString l_csLine;

	l_csLine.Format ("%s|%s\n", m_csInfoName, m_csInfoValue);
	a_cFile.WriteString (l_csLine);
}

bool CItemInfo::ReadFromFile(CStdioFile &a_cFile)
{
	CString l_csLine;
	bool l_bSuccess = true;
	int l_iTokenOffset = 0;

	if (a_cFile.ReadString (l_csLine))
	{
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csInfoName);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csInfoValue);
	}

	return (l_bSuccess);
}
