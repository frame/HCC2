// SubCategory.cpp: implementation of the CSubCategory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HCC.h"
#include "SubCategory.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSubCategory::CSubCategory()
{

}

CSubCategory::~CSubCategory()
{

}

CSubCategory::operator =( const CSubCategory *pSrc )
{
   CopyObject (pSrc);
   return true;
}


CSubCategory::CSubCategory(const CSubCategory *pSrc)
{
   CopyObject (pSrc);
}

void CSubCategory::CopyObject(const CSubCategory *pSrc)
{
	m_csCategoryName = pSrc->m_csCategoryName;
	m_csSubCategoryName = pSrc->m_csSubCategoryName;
	m_csDescription = pSrc->m_csDescription;
	m_iIcon = pSrc->m_iIcon;
}

CSubCategory::Destroy()
{

}

CSubCategory::WriteToFile(CStdioFile &a_cFile)
{
	CString l_csLine;

	l_csLine.Format ("%s|%s|%s|%s\n", m_csCategoryName, m_csSubCategoryName, m_csDescription, m_iIcon);
	a_cFile.WriteString (l_csLine);
}

bool CSubCategory::ReadFromFile(CStdioFile &a_cFile)
{
	CString l_csLine;
	bool l_bSuccess = true;
	int l_iTokenOffset = 0;

	if (a_cFile.ReadString (l_csLine))
	{
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csCategoryName);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csSubCategoryName);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csDescription);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_iIcon);
	}

	return (l_bSuccess);
}
