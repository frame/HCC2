// Category.h: interface for the CCategory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CATEGORY_H__2B74AD64_DABD_4D9C_A21B_EB46AD18F805__INCLUDED_)
#define AFX_CATEGORY_H__2B74AD64_DABD_4D9C_A21B_EB46AD18F805__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FileHandler.h"

class CCategory   : CFileHandler
{
public:
	CCategory();
	virtual ~CCategory();

	CCategory(const CCategory *pSrc);
	operator =( const CCategory* pSrc );
	void CopyObject(const CCategory *pSrc);
	Destroy();
	bool ReadFromFile(CStdioFile &a_cFile);
	WriteToFile(CStdioFile &a_cFile);

	CString m_csCategoryName;
	CString m_csDescription;
	int	  m_iIcon;
};

#endif // !defined(AFX_CATEGORY_H__2B74AD64_DABD_4D9C_A21B_EB46AD18F805__INCLUDED_)
