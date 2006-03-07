// Effect.h: interface for the CEffect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_Effect_H__5203D9A2_A223_4998_8D87_90AA7C5BE812__INCLUDED_)
#define AFX_Effect_H__5203D9A2_A223_4998_8D87_90AA7C5BE812__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FileHandler.h"

class CEffect : CFileHandler
{
public:
	TranslateEffectType();
	bool ReadFromFile(CStdioFile &a_cFile);
	WriteToFile (CStdioFile &a_cFile);
	Destroy();
	Clear();
	CEffect();
	virtual ~CEffect();

	CString m_csType;
	CString m_csDescription;

	CEffect(const CEffect *pSrc);
	operator =( const CEffect* pSrc );
	void CopyObject(const CEffect *pSrc);
};

#endif // !defined(AFX_Effect_H__5203D9A2_A223_4998_8D87_90AA7C5BE812__INCLUDED_)
