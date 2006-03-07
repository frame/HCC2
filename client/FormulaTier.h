// Formula.h: interface for the CFormulaTier class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FORMULATIER_H__54230807_EE7D_4B6E_8C5A_92E4E5756835__INCLUDED_)
#define AFX_FORMULATIER_H__54230807_EE7D_4B6E_8C5A_92E4E5756835__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bonus.h"
#include "itemresource.h"
#include "iteminfo.h"
#include "FileHandler.h"
#include "KeywordGroup.h"
#include "effect.h"

class CFormulaTier  : CFileHandler
{
public:
	bool ReadFromFile(CStdioFile &a_cFile);
	WriteToFile(CStdioFile &a_cFile);
	Destroy();
	Clear();
	CFormulaTier();
	virtual ~CFormulaTier();

	CString m_csName;
	int     m_iTierLevel;
	CString m_csTierName;
	CString m_csDescription;
	int	  m_iAllowedTechniques;
	int	  m_iBatchQty;
	CKeywordGroup m_cKeywords;

	CTypedPtrList<CPtrList, CEffect*>	m_clEffectsList;
	CTypedPtrList<CPtrList, CItemResource*>	m_clResourceList;

	CFormulaTier(const CFormulaTier *pSrc);
	operator =( const CFormulaTier* pSrc );
	void CopyObject(const CFormulaTier *pSrc);
};

#endif // !defined(AFX_FORMULATIER_H__54230807_EE7D_4B6E_8C5A_92E4E5756835__INCLUDED_)

