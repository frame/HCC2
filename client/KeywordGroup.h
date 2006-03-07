// KeywordGroup.h: interface for the CKeywordGroup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KeywordGroup_H__5203D9A2_A223_4998_8D87_90AA7C5BE812__INCLUDED_)
#define AFX_KeywordGroup_H__5203D9A2_A223_4998_8D87_90AA7C5BE812__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FileHandler.h"

class CKeywordGroup : CFileHandler
{
public:
	bool Match (CKeywordGroup *a_pKeywordGroup);
	bool ReadFromFile(CStdioFile &a_cFile);
	WriteToFile (CStdioFile &a_cFile);
	Destroy();
	Clear();
	CKeywordGroup();
	virtual ~CKeywordGroup();

	CStringList m_clKeywordList;

	CKeywordGroup(const CKeywordGroup *pSrc);
	operator =( const CKeywordGroup* pSrc );
	void CopyObject(const CKeywordGroup *pSrc);
};

#endif // !defined(AFX_KeywordGroup_H__5203D9A2_A223_4998_8D87_90AA7C5BE812__INCLUDED_)
