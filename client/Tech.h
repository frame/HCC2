// Tech.h: interface for the CTech class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_Tech_H__54230807_EE7D_4B6E_8C5A_92E4E5756835__INCLUDED_)
#define AFX_Tech_H__54230807_EE7D_4B6E_8C5A_92E4E5756835__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bonus.h"
#include "itemresource.h"
#include "iteminfo.h"
#include "Techtier.h"
#include "Formula.h"
#include "FileHandler.h"
#include "KeywordGroup.h"
#include "XMLParser.h"
#include "XMLTag.h"

class CTech: CFileHandler
{
public:
	MoveKeywordsToTiers();
	bool LoadTech(CString &a_csCategory, XMLParser &a_cParser, XMLTag &a_cItemTag, bool a_bInitialise = true);
	bool ReadFromFile(CStdioFile &a_cFile);
	WriteToFile(CStdioFile &a_cFile);
	Destroy();
	bool CheckTech (CTech *a_cpTech);
	bool CheckFormula (CFormula *a_cpFormula, CFormulaTier *a_cpFormulaTier);
	bool FindTechTier (CString &a_csTier, CTechTier **a_cpTechTier);
	Clear();
	CTech();
	virtual ~CTech();

	operator =( const CTech* pSrc );
	CTech(const CTech *pSrc);
	void CopyObject(const CTech *pSrc);

	CString m_csName;
	int	  m_iIcon;
	CString m_csPrefix;
	CString m_csSuffix;
	CString m_csDescription;
	CString m_csSubDescription;

	bool	  m_bTierLevelKeywords;

	CTypedPtrList<CPtrList, CEffect*>	m_clEffectsList;
	CTypedPtrList<CPtrList, CKeywordGroup*>	m_clKeywordSets;
	CTypedPtrList<CPtrList, CKeywordGroup*>	m_clKeywordEffectSets;
	
	CTypedPtrList<CPtrList, CTechTier*>	m_clTechTierList;

};

#endif // !defined(AFX_Tech_H__54230807_EE7D_4B6E_8C5A_92E4E5756835__INCLUDED_)

