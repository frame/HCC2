// Formula.cpp: implementation of the CFormula class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HCC.h"
#include "Formula.h"
#include "AppData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFormula::CFormula()
{
	m_iBatchQty = 1;
	m_bTierLevelKeywords = false;
}

CFormula::~CFormula()
{
	Destroy ();
}

CFormula::operator =( const CFormula* pSrc )
{
   CopyObject (pSrc);
   return true;
}


CFormula::CFormula(const CFormula *pSrc)
{
   CopyObject (pSrc);
}

void CFormula::CopyObject(const CFormula *pSrc)
{
	m_csName = pSrc->m_csName;
	m_csCategory = pSrc->m_csCategory;
	m_iBatchQty   = pSrc->m_iBatchQty;
	m_iIcon = pSrc->m_iIcon;
	m_csImage = pSrc->m_csImage;
	m_bTierLevelKeywords = pSrc->m_bTierLevelKeywords;

	m_clFormulaTierList.RemoveAll ();
	POSITION l_Pos = pSrc->m_clFormulaTierList.GetHeadPosition ();
	while (l_Pos)
	{
		m_clFormulaTierList.AddTail (pSrc->m_clFormulaTierList.GetNext (l_Pos));
	}

	m_clEffectsList.RemoveAll ();
	l_Pos = pSrc->m_clEffectsList.GetHeadPosition ();
	while (l_Pos)
	{
		m_clEffectsList.AddTail (pSrc->m_clEffectsList.GetNext (l_Pos));
	}

}

CFormula::Destroy()
{
	CFormulaTier *l_cpFormulaTier;
	CEffect *l_cpEffect;

	POSITION l_Pos = m_clFormulaTierList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpFormulaTier = m_clFormulaTierList.GetNext (l_Pos);
		l_cpFormulaTier->Destroy ();
		delete (l_cpFormulaTier);
	}
	m_clFormulaTierList.RemoveAll ();

	l_Pos = m_clEffectsList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpEffect = m_clEffectsList.GetNext (l_Pos);
		l_cpEffect->Destroy ();
		delete (l_cpEffect);
	}
	m_clEffectsList.RemoveAll ();
}

CFormula::Clear()
{
	m_csName.Empty ();

	Destroy ();
}

bool CFormula::LoadFormula(CString &a_csCategory, XMLParser &a_cParser, XMLTag &a_cItemTag, bool a_bInitialise)
{
	bool l_bResult = true;

	XMLTag l_cItemAttributeTag ("item-attributes");
	XMLTag l_cItemKeywordTag ("item-keywords");
	XMLTag l_cTierTag ("tier");
	XMLTag l_cTierAttributeTag ("tier-attributes");
	XMLTag l_cTierKeywordTag ("tier-keywords");
	XMLTag l_cResourcesTag ("resources");
	XMLTag l_cResourceTag ("resource");

	CItemResource	*l_cpItemResource;
	CFormulaTier	*l_cpFormulaTier;
	CFormulaTier	*l_cpSearchFormulaTier;
	CEffect		   *l_cpEffect;

	CString l_csFormulaName;
	CString l_csTierName;
	int	  l_iTierLvl;
	CString l_csIconName;
	CString l_csDescription;
	CString l_csValue;
	POSITION l_Pos;
	POSITION l_PrevPos;
	POSITION l_InsertPos;

	if (a_bInitialise)
	{
		Destroy ();
	}


	a_cItemTag.GetTagValue (a_cParser, (CString) "item-name", m_csName, a_bInitialise);
	if (a_cItemTag.GetTagValue (a_cParser, (CString) "item-icon", l_csIconName, a_bInitialise))
	{
		m_iIcon = CAppData::m_cpIconImages->FindImageOffset (l_csIconName);
	}

	m_csCategory	= a_csCategory;
	if (a_cItemTag.GetTagValue (a_cParser, (CString) "item-batchqty", m_iBatchQty, a_bInitialise))
	{
	}

	if (m_iBatchQty == 0)
	{
		m_iBatchQty = 1;
	}

	if (l_cItemAttributeTag.GetNextTag (a_cParser, a_cItemTag))
	{

		while (l_cItemAttributeTag.GetRepeatingDoubleTagValue (a_cParser, (CString) "item-attribute", l_csValue, l_csDescription, a_bInitialise))
		{
			l_cpEffect = new CEffect ();
			l_cpEffect->m_csType = l_csValue;
			l_cpEffect->m_csDescription = l_csDescription;
			l_cpEffect->TranslateEffectType ();
			m_clEffectsList.AddTail (l_cpEffect);
		}
	}

	if (l_cItemKeywordTag.GetNextTag (a_cParser, a_cItemTag))
	{

		while (l_cItemKeywordTag.GetRepeatingTagValue (a_cParser, (CString) "item-keyword", l_csValue, a_bInitialise))
		{
			if ((l_csValue.Left (10) != cTechKeyword_TechClass) &&
				 (l_csValue.Left (5) != cTechKeyword_Tier))
			{
				m_cKeywords.m_clKeywordList.AddTail (l_csValue);
			}
		}
	}


	while (l_cTierTag.GetNextTag (a_cParser, a_cItemTag))
	{
		l_cTierTag.GetTagValue (a_cParser, (CString) "tier-name", l_csFormulaName, a_bInitialise);
		if (l_cTierTag.GetTagDoubleValue (a_cParser, (CString) "tier-lvl", l_csTierName, l_csValue, a_bInitialise))
		{
			l_iTierLvl = atoi (l_csValue);
			if (l_csTierName.IsEmpty ())
			{
				l_csTierName = CAppData::GetTierName (l_iTierLvl);
			}
		}
		else
		{
			l_iTierLvl = -1;
		}

		l_InsertPos = NULL;
		l_cpFormulaTier = NULL;
		l_PrevPos = NULL;
		l_Pos = m_clFormulaTierList.GetHeadPosition ();
		while (l_Pos)
		{
			l_PrevPos = l_Pos;
			l_cpSearchFormulaTier = m_clFormulaTierList.GetNext (l_Pos);
			if (l_cpSearchFormulaTier->m_csName == l_csFormulaName)
			{
				l_InsertPos = NULL;
				l_cpFormulaTier = l_cpSearchFormulaTier;
				l_Pos = NULL;
			}
			else if ((l_iTierLvl != -1) && (l_cpSearchFormulaTier->m_iTierLevel > l_iTierLvl))
			{
				l_InsertPos = l_PrevPos;
				l_Pos = NULL;
			}
		}

		if (l_cpFormulaTier == NULL)
		{
			l_cpFormulaTier = new CFormulaTier ();
			l_cpFormulaTier->m_csName = l_csFormulaName;
			l_cpFormulaTier->m_csTierName = l_csTierName;
			l_cpFormulaTier->m_iTierLevel = l_iTierLvl;

			if (l_InsertPos)
			{
				m_clFormulaTierList.InsertBefore (l_InsertPos, l_cpFormulaTier);
			}
			else
			{
				m_clFormulaTierList.AddTail (l_cpFormulaTier);
			}
		}

		if (!l_cTierTag.GetTagValue (a_cParser, (CString) "tier-batchqty", l_cpFormulaTier->m_iBatchQty, a_bInitialise))
		{
			l_cpFormulaTier->m_iBatchQty = m_iBatchQty;
		}

		if (l_cpFormulaTier->m_iBatchQty == 0)
		{
			l_cpFormulaTier->m_iBatchQty = 1;
		}

		l_cTierTag.GetTagValue (a_cParser, (CString) "tier-desc", l_cpFormulaTier->m_csDescription, a_bInitialise);
		l_cTierTag.GetTagValue (a_cParser, (CString) "tier-allowedtechniques", l_cpFormulaTier->m_iAllowedTechniques, a_bInitialise);
		if (l_cpFormulaTier->m_iAllowedTechniques == 0)
		{
			l_cpFormulaTier->m_iAllowedTechniques = (l_cpFormulaTier->m_iTierLevel + 1) / 2;
		}

		if (l_cTierAttributeTag.GetNextTag (a_cParser, l_cTierTag))
		{

			while (l_cTierAttributeTag.GetRepeatingDoubleTagValue (a_cParser, (CString) "tier-attribute", l_csValue, l_csDescription, a_bInitialise))
			{
				l_cpEffect = new CEffect ();
				l_cpEffect->m_csType = l_csValue;
				l_cpEffect->m_csDescription = l_csDescription;
				l_cpEffect->TranslateEffectType ();
				l_cpFormulaTier->m_clEffectsList.AddTail (l_cpEffect);
			}
		}

		if (l_cTierKeywordTag.GetNextTag (a_cParser, l_cTierTag))
		{
			while (l_cTierKeywordTag.GetRepeatingTagValue (a_cParser, (CString) "tier-keyword", l_csValue, a_bInitialise))
			{
				if ((l_csValue.Left (10) != cTechKeyword_TechClass) &&
					 (l_csValue.Left (5) != cTechKeyword_Tier))
				{
					m_bTierLevelKeywords = true;
					l_cpFormulaTier->m_cKeywords.m_clKeywordList.AddTail (l_csValue);
				}
			}
		}

		if (l_cResourcesTag.GetNextTag (a_cParser, l_cTierTag))
		{
			while (l_cResourceTag.GetNextTag (a_cParser, l_cResourcesTag))
			{
				l_cpItemResource = new CItemResource ();

				l_cResourceTag.GetTagValue (a_cParser, (CString) "resource-name", l_cpItemResource->m_csName, a_bInitialise);
				l_cResourceTag.GetTagValue (a_cParser, (CString) "resource-skill", l_cpItemResource->m_csSkill, a_bInitialise);
				l_cResourceTag.GetTagValue (a_cParser, (CString) "resource-units", l_cpItemResource->m_iUnits, a_bInitialise);
				l_cResourceTag.GetTagDoubleValue (a_cParser, (CString) "resource-min", l_cpItemResource->m_iMinAmt, l_cpItemResource->m_iMinLvl, a_bInitialise);
				l_cResourceTag.GetTagDoubleValue (a_cParser, (CString) "resource-opt", l_cpItemResource->m_iOptAmt, l_cpItemResource->m_iOptLvl, a_bInitialise);

				if (l_cpItemResource->m_iMinAmt == 0)
				{
					l_cpItemResource->m_iMinAmt = l_cpItemResource->m_iOptAmt * 2;
				}

				l_cpFormulaTier->m_clResourceList.AddTail (l_cpItemResource);
			}
		}

	}

	if (m_bTierLevelKeywords)
	{
		MoveKeywordsToTiers ();
	}

	return (l_bResult);
}

bool CFormula::FindFormulaTier(CString &a_csTier, CFormulaTier **a_cpFormulaTier)
{
	bool l_bFound = false;
	POSITION l_Pos;
	CFormulaTier *l_cpFormulaTier;

	l_Pos = m_clFormulaTierList.GetHeadPosition ();

	while (l_Pos)
	{
		l_cpFormulaTier = m_clFormulaTierList.GetNext (l_Pos);

		if (l_cpFormulaTier->m_csTierName == a_csTier)
		{
			*a_cpFormulaTier = l_cpFormulaTier;
			return (true);
		}
	}

	return (l_bFound);
}

CFormula::WriteToFile(CStdioFile &a_cFile)
{
	CString l_csLine;
	CFormulaTier *l_cpFormulaTier;
	CEffect *l_cpEffect;

	l_csLine.Format ("%s|%d|%d|%s|%s|%s|%d|%d\n",
						  m_csName,
						  m_iBatchQty,
						  m_iIcon,
						  m_csImage,
						  m_csCategory,
						  BoolToStr(m_bTierLevelKeywords),
						  m_clEffectsList.GetCount(),
						  m_clFormulaTierList.GetCount());
	a_cFile.WriteString (l_csLine);

	m_cKeywords.WriteToFile (a_cFile);

	POSITION l_Pos = m_clEffectsList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpEffect = m_clEffectsList.GetNext (l_Pos);
		l_cpEffect->WriteToFile (a_cFile);
	}

	l_Pos = m_clFormulaTierList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpFormulaTier = m_clFormulaTierList.GetNext (l_Pos);
		l_cpFormulaTier->WriteToFile (a_cFile);
	}
}

bool CFormula::ReadFromFile(CStdioFile &a_cFile)
{
	CString l_csLine;
	bool l_bSuccess = true;
	int l_iTokenOffset = 0;
	int l_iEffectCount = 0;
	int l_iFormulaTierCount = 0;
	CFormulaTier *l_cpFormulaTier;
	CEffect *l_cpEffect;
	CString l_csValue;

	if (a_cFile.ReadString (l_csLine))
	{
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csName);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_iBatchQty);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_iIcon);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csImage);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csCategory);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, l_csValue);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, l_iEffectCount);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, l_iFormulaTierCount);
		m_bTierLevelKeywords = StrToBool (l_csValue);

		l_bSuccess = l_bSuccess && m_cKeywords.ReadFromFile (a_cFile);

		if (l_bSuccess)
		{
			while (l_iEffectCount--)
			{
				l_cpEffect = new CEffect();
				l_bSuccess = l_bSuccess && l_cpEffect->ReadFromFile (a_cFile);
				m_clEffectsList.AddTail (l_cpEffect);
			}
		}

		if (l_bSuccess)
		{
			while (l_iFormulaTierCount--)
			{
				l_cpFormulaTier = new CFormulaTier();
				l_bSuccess = l_bSuccess && l_cpFormulaTier->ReadFromFile (a_cFile);
				m_clFormulaTierList.AddTail (l_cpFormulaTier);
			}
		}
	}

	return (l_bSuccess);
}

CFormula::MoveKeywordsToTiers()
{
	POSITION l_GroupPos;
	POSITION l_TierPos;
	CFormulaTier *l_cpFormulaTier;

	l_TierPos = m_clFormulaTierList.GetHeadPosition ();
	while (l_TierPos)
	{
		l_cpFormulaTier = m_clFormulaTierList.GetNext (l_TierPos);

		l_GroupPos = m_cKeywords.m_clKeywordList.GetHeadPosition ();
		while (l_GroupPos)
		{
			l_cpFormulaTier->m_cKeywords.m_clKeywordList.AddTail (m_cKeywords.m_clKeywordList.GetNext (l_GroupPos));
		}
	}

}
