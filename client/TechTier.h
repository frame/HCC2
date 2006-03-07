// Tech.h: interface for the CTechTier class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TechTIER_H__54230807_EE7D_4B6E_8C5A_92E4E5756835__INCLUDED_)
#define AFX_TechTIER_H__54230807_EE7D_4B6E_8C5A_92E4E5756835__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bonus.h"
#include "itemresource.h"
#include "iteminfo.h"
#include "FileHandler.h"
#include "KeywordGroup.h"
#include "Effect.h"
#include "Formula.h"
#include "FormulaTier.h"

class CTechTier : CFileHandler
{
public:
	bool CheckFormula(CFormula *a_cpFormula, CFormulaTier *a_cpFormulaTier);
	bool ReadFromFile(CStdioFile &a_cFile);
	WriteToFile(CStdioFile &a_cFile);
	Destroy();
	Clear();
	CTechTier();
	virtual ~CTechTier();

	operator =( const CTechTier* pSrc );
	CTechTier(const CTechTier *pSrc);
	void CopyObject(const CTechTier *pSrc);

	CString m_csName;
	CString m_csOrigin;
	int     m_iTierLevel;
	CString m_csTierName;
	CString m_csDescription;
	int	  m_iSkillAdjust;
	int	  m_iUsageAdjust;
	CString m_csPrefix;
	CString m_csSuffix;
	int	  m_iSize;

	CTypedPtrList<CPtrList, CKeywordGroup*>	m_clKeywordSets;
	CTypedPtrList<CPtrList, CKeywordGroup*>	m_clKeywordEffectSets;
	CTypedPtrList<CPtrList, CEffect*>			m_clEffectList;

	CTypedPtrList<CPtrList, CItemResource*>	m_clResourceList;

};

#endif // !defined(AFX_TechTIER_H__54230807_EE7D_4B6E_8C5A_92E4E5756835__INCLUDED_)

