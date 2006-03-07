// SubCategory.h: interface for the CSubCategory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SUBCATEGORY_H__87D8719E_B4BD_4953_9C00_408557646BB4__INCLUDED_)
#define AFX_SUBCATEGORY_H__87D8719E_B4BD_4953_9C00_408557646BB4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FileHandler.h"

class CSubCategory   : CFileHandler
{
public:
	CSubCategory();
	virtual ~CSubCategory();

	CSubCategory(const CSubCategory *pSrc);
	operator =( const CSubCategory* pSrc );
	void CopyObject(const CSubCategory *pSrc);
	Destroy();
	bool ReadFromFile(CStdioFile &a_cFile);
	WriteToFile(CStdioFile &a_cFile);

	CString m_csCategoryName;
	CString m_csSubCategoryName;
	CString m_csDescription;
	int	  m_iIcon;
};

#endif // !defined(AFX_SUBCATEGORY_H__87D8719E_B4BD_4953_9C00_408557646BB4__INCLUDED_)
