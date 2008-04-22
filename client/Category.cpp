// Category.cpp: implementation of the CCategory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HCC.h"
#include "Category.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCategory::CCategory()
{

}

CCategory::~CCategory()
{

}

CCategory::operator =( const CCategory* pSrc )
{
   CopyObject (pSrc);
   return true;
}


CCategory::CCategory(const CCategory *pSrc)
{
   CopyObject (pSrc);
}

void CCategory::CopyObject(const CCategory *pSrc)
{
	m_csCategoryName = pSrc->m_csCategoryName;
	m_csDescription = pSrc->m_csDescription;
	m_iIcon = pSrc->m_iIcon;
}

CCategory::Destroy()
{

}

CCategory::WriteToFile(CStdioFile &a_cFile)
{
	CString l_csLine;

	l_csLine.Format ("%s|%s|%s\n", m_csCategoryName, m_csDescription, m_iIcon);
	a_cFile.WriteString (l_csLine);
}

bool CCategory::ReadFromFile(CStdioFile &a_cFile)
{
	CString l_csLine;
	bool l_bSuccess = true;
	int l_iTokenOffset = 0;

	if (a_cFile.ReadString (l_csLine))
	{
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csCategoryName);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csDescription);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_iIcon);
	}

	return (l_bSuccess);
}
