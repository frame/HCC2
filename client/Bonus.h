// Bonus.h: interface for the CBonus class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BONUS_H__5203D9A2_A223_4998_8D87_90AA7C5BE812__INCLUDED_)
#define AFX_BONUS_H__5203D9A2_A223_4998_8D87_90AA7C5BE812__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FileHandler.h"

class CBonus : CFileHandler
{
public:
	bool ReadFromFile(CStdioFile &a_cFile);
	WriteToFile (CStdioFile &a_cFile);
	Destroy();
	Clear();
	CBonus();
	virtual ~CBonus();

	CString m_csBonusName;
	int		m_iValue;

	CBonus(const CBonus *pSrc);
	operator =( const CBonus* pSrc );
	void CopyObject(const CBonus *pSrc);
};

#endif // !defined(AFX_BONUS_H__5203D9A2_A223_4998_8D87_90AA7C5BE812__INCLUDED_)
