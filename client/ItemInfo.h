// ItemInfo.h: interface for the CItemInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITEMINFO_H__8A46B7E1_C401_4CBD_A135_0FC9219C5BA9__INCLUDED_)
#define AFX_ITEMINFO_H__8A46B7E1_C401_4CBD_A135_0FC9219C5BA9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FileHandler.h"

class CItemInfo  : CFileHandler
{
public:
	bool ReadFromFile(CStdioFile &a_cFile);
	WriteToFile(CStdioFile &a_cFile);
	Destroy();
	Clear();
	CItemInfo();
	virtual ~CItemInfo();

	CString m_csInfoName;
	CString m_csInfoValue;

	CItemInfo(const CItemInfo *pSrc);
	operator =( const CItemInfo* pSrc );
	void CopyObject(const CItemInfo *pSrc);
};

#endif // !defined(AFX_ITEMINFO_H__8A46B7E1_C401_4CBD_A135_0FC9219C5BA9__INCLUDED_)
