// Formula.h: interface for the CFormula class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FORMULA_H__54230807_EE7D_4B6E_8C5A_92E4E5756835__INCLUDED_)
#define AFX_FORMULA_H__54230807_EE7D_4B6E_8C5A_92E4E5756835__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bonus.h"
#include "itemresource.h"
#include "iteminfo.h"
#include "formulatier.h"
#include "FileHandler.h"
#include "KeywordGroup.h"
#include "effect.h"
#include "XMLParser.h"
#include "XMLTag.h"

class CFormula  : CFileHandler
{
public:
	MoveKeywordsToTiers ();
	bool LoadFormula(CString &a_csCategory, XMLParser &a_cParser, XMLTag &a_cItemTag, bool a_bInitialise = true);
	bool ReadFromFile(CStdioFile &a_cFile);
	WriteToFile(CStdioFile &a_cFile);
	bool FindFormulaTier (CString &a_csTier, CFormulaTier **a_cFormulaTier);
	Destroy();
	Clear();
	CFormula();
	virtual ~CFormula();

	// XML Driven
	CString m_csName;
	int	  m_iBatchQty;
	int	  m_iIcon;
	CKeywordGroup m_cKeywords;

	CString m_csImage;

	// Passdown
	CString m_csCategory;
	bool	  m_bTierLevelKeywords;

	CTypedPtrList<CPtrList, CEffect*>	m_clEffectsList;
	CTypedPtrList<CPtrList, CFormulaTier*>	m_clFormulaTierList;

	CFormula(const CFormula *pSrc);
	operator =( const CFormula* pSrc );
	void CopyObject(const CFormula *pSrc);
};

#endif // !defined(AFX_FORMULA_H__54230807_EE7D_4B6E_8C5A_92E4E5756835__INCLUDED_)

