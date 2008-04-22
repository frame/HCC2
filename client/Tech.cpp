// Tech.cpp: implementation of the CTech class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HCC.h"
#include "Tech.h"
#include "ItemInfo.h"
#include "Bonus.h"
#include "ItemResource.h"
#include "TechTier.h"
#include "AppData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTech::CTech()
{
	m_bTierLevelKeywords = false;

}

CTech::~CTech()
{
	Destroy();
}

CTech::operator =( const CTech* pSrc )
{
   CopyObject (pSrc);
   return true;
}


CTech::CTech(const CTech *pSrc)
{
   CopyObject (pSrc);
}

void CTech::CopyObject(const CTech *pSrc)
{
	m_csName = pSrc->m_csName;
	m_iIcon = pSrc->m_iIcon;
	m_csPrefix = pSrc->m_csPrefix;
	m_csSuffix = pSrc->m_csSuffix;
	m_csDescription = pSrc->m_csDescription;
	m_csSubDescription = pSrc->m_csSubDescription;
	m_bTierLevelKeywords = pSrc->m_bTierLevelKeywords;

	m_clTechTierList.RemoveAll ();
	POSITION l_Pos = pSrc->m_clTechTierList.GetHeadPosition ();
	while (l_Pos)
	{
		m_clTechTierList.AddTail (pSrc->m_clTechTierList.GetNext (l_Pos));
	}

	m_clEffectsList.RemoveAll ();
	m_clKeywordSets.RemoveAll ();
	m_clKeywordEffectSets.RemoveAll ();

}

CTech::Destroy()
{
	CTechTier *l_cpTechTier;
	CKeywordGroup *l_cpKeywordGroup;
	CEffect *l_cpEffect;

	POSITION l_Pos = m_clTechTierList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpTechTier = m_clTechTierList.GetNext (l_Pos);
		l_cpTechTier->Destroy ();
		delete (l_cpTechTier);
	}
	m_clTechTierList.RemoveAll ();

	l_Pos = m_clEffectsList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpEffect = m_clEffectsList.GetNext (l_Pos);
		l_cpEffect->Destroy ();
		delete (l_cpEffect);
	}
	m_clEffectsList.RemoveAll ();

	l_Pos = m_clKeywordSets.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpKeywordGroup = m_clKeywordSets.GetNext (l_Pos);
		l_cpKeywordGroup->Destroy ();
		delete (l_cpKeywordGroup);
	}
	m_clKeywordSets.RemoveAll ();

	l_Pos = m_clKeywordEffectSets.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpKeywordGroup = m_clKeywordEffectSets.GetNext (l_Pos);
		l_cpKeywordGroup->Destroy ();
		delete (l_cpKeywordGroup);
	}
	m_clKeywordEffectSets.RemoveAll ();
}

CTech::Clear()
{
	m_csName.Empty ();

	Destroy();
}

bool CTech::LoadTech(CString &a_csCategory, XMLParser &a_cParser, XMLTag &a_cItemTag, bool a_bInitialise)
{
	bool l_bResult = true;

	XMLTag l_cItemKeywordTag				("tech-keywords");
	XMLTag l_cItemKeywordSetTag			("tech-keywordset");
	XMLTag l_cItemEffectKeywordTag		("tech-effectkeywords");
	XMLTag l_cItemEffectKeywordSetTag	("tech-effectkeywordset");
	XMLTag l_cItemAttributesTag			("tech-attributes");
	XMLTag l_cTierTag							("tier");
	XMLTag l_cTierKeywordTag				("tier-keywords");
	XMLTag l_cTierKeywordSetTag			("tier-keywordset");
	XMLTag l_cTierEffectKeywordTag		("tier-effectkeywords");
	XMLTag l_cTierEffectKeywordSetTag	("tier-effectkeywordset");
	XMLTag l_cTierAttributesTag			("tier-attributes");
	XMLTag l_cResourceTag					("components");

	CKeywordGroup	 l_cKeywordGroup;
	CKeywordGroup	*l_cpKeywordGroup;
	CEffect			*l_cpEffect;
	CItemResource	 l_cItemResource;
	CItemResource	*l_cpItemResource = NULL;
	CTechTier		*l_cpTechTier = NULL;
	CTechTier		*l_cpSearchTechTier = NULL;
	CString l_csTechName;
	CString l_csTierName;
	int	  l_iTierLvl;
	CString l_csIconName;
	CString l_csValue;
	CString l_csAttribute;
	POSITION l_Pos;
	POSITION l_PrevPos;
	POSITION l_InsertPos;
	bool l_bTechBonus = false;

	if (a_bInitialise)
	{
		Destroy ();
	}

	a_cItemTag.GetTagValue (a_cParser, (CString) "tech-name", m_csName, a_bInitialise);
	a_cItemTag.GetTagValue (a_cParser, (CString) "tech-desc", m_csDescription, a_bInitialise);
	a_cItemTag.GetTagValue (a_cParser, (CString) "tech-subdesc", m_csSubDescription, a_bInitialise);
	a_cItemTag.GetTagValue (a_cParser, (CString) "tech-prefix", m_csPrefix, a_bInitialise);
	a_cItemTag.GetTagValue (a_cParser, (CString) "tech-suffix", m_csSuffix, a_bInitialise);

	if (a_cItemTag.GetTagValue (a_cParser, (CString) "tech-icon", l_csIconName, a_bInitialise))
	{
		m_iIcon		= CAppData::m_cpIconImages->FindImageOffset (l_csIconName);
	}

	if (l_cItemKeywordTag.GetNextTag (a_cParser, a_cItemTag))
	{

		while (l_cItemKeywordSetTag.GetNextTag (a_cParser, l_cItemKeywordTag))
		{
			l_cpKeywordGroup = new CKeywordGroup ();
			while (l_cItemKeywordSetTag.GetRepeatingTagValue (a_cParser, (CString) "tech-keyword", l_csValue, a_bInitialise))
			{
				if ((l_csValue.Left (10) != cTechKeyword_TechClass) &&
					 (l_csValue.Left (5) != cTechKeyword_Tier))
				{
					l_cpKeywordGroup->m_clKeywordList.AddTail (l_csValue);
				}
			}
			if (l_cpKeywordGroup->m_clKeywordList.GetCount () > 0)
			{
				m_clKeywordSets.AddTail (l_cpKeywordGroup);
			}
			else
			{
				delete (l_cpKeywordGroup);
			}
		}
	}

	if (l_cItemEffectKeywordTag.GetNextTag (a_cParser, a_cItemTag))
	{

		while (l_cItemEffectKeywordSetTag.GetNextTag (a_cParser, l_cItemEffectKeywordTag))
		{
			l_cpKeywordGroup = new CKeywordGroup ();
			while (l_cItemEffectKeywordSetTag.GetRepeatingTagValue (a_cParser, (CString) "tech-effectkeyword", l_csValue, a_bInitialise))
			{
				l_cpKeywordGroup->m_clKeywordList.AddTail (l_csValue);
			}
			m_clKeywordEffectSets.AddTail (l_cpKeywordGroup);
		}
	}

	if (l_cItemAttributesTag.GetNextTag (a_cParser, a_cItemTag))
	{
		while (l_cItemAttributesTag.GetRepeatingDoubleTagValue (a_cParser, (CString) "tech-attribute", l_csAttribute, l_csValue))
		{
			l_cpEffect = new CEffect();
			l_cpEffect->m_csType = l_csAttribute;
			l_cpEffect->m_csDescription = l_csValue;
			l_cpEffect->TranslateEffectType ();

			m_clEffectsList.AddTail (l_cpEffect);
		}
	}

	while (l_cTierTag.GetNextTag (a_cParser, a_cItemTag))
	{
		l_bTechBonus = false;

		l_cTierTag.GetTagValue (a_cParser, (CString) "tier-name", l_csTechName, a_bInitialise);
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
		l_cpTechTier = NULL;
		l_PrevPos = NULL;
		l_Pos = m_clTechTierList.GetHeadPosition ();
		while (l_Pos)
		{
			l_PrevPos = l_Pos;
			l_cpSearchTechTier = m_clTechTierList.GetNext (l_Pos);
			if (l_cpSearchTechTier->m_csName == l_csTechName)
			{
				l_InsertPos = NULL;
				l_cpTechTier = l_cpSearchTechTier;
				l_Pos = NULL;
			}
			else if ((l_iTierLvl != -1) && (l_cpSearchTechTier->m_iTierLevel > l_iTierLvl))
			{
				l_InsertPos = l_PrevPos;
				l_Pos = NULL;
			}
		}

		if (l_cpTechTier == NULL)
		{
			l_cpTechTier = new CTechTier ();
			l_cpTechTier->m_csName = l_csTechName;
			l_cpTechTier->m_csTierName = l_csTierName;
			l_cpTechTier->m_iTierLevel = l_iTierLvl;

			if (l_InsertPos)
			{
				m_clTechTierList.InsertBefore (l_InsertPos, l_cpTechTier);
			}
			else
			{
				m_clTechTierList.AddTail (l_cpTechTier);
			}
		}
		else
		{
			l_Pos = l_cpTechTier->m_clEffectList.GetHeadPosition ();
			while ((l_Pos) && (!l_bTechBonus))
			{
				l_cpEffect = l_cpTechTier->m_clEffectList.GetNext (l_Pos);
				l_bTechBonus = l_bTechBonus || l_cpEffect->m_csType == cXMLAttribute_Bonus;
			}
		}

		l_cTierTag.GetTagValue (a_cParser, (CString) "tier-origin", l_cpTechTier->m_csOrigin, a_bInitialise);
		l_cTierTag.GetTagValue (a_cParser, (CString) "tier-desc", l_cpTechTier->m_csDescription, a_bInitialise);

		if (!l_cTierTag.GetTagValue (a_cParser, (CString) "tier-skilladjust", l_cpTechTier->m_iSkillAdjust, a_bInitialise))
		{
			if (l_cpTechTier->m_iSkillAdjust == 0)
			{
				l_cpTechTier->m_iSkillAdjust = l_cpTechTier->m_iTierLevel * 10;
			}
		}

		if (!l_cTierTag.GetTagValue (a_cParser, (CString) "tier-usageadjust", l_cpTechTier->m_iUsageAdjust, a_bInitialise))
		{
			if ((a_csCategory == "Spell") && (l_cpTechTier->m_iUsageAdjust == 0))
			{
				l_cpTechTier->m_iUsageAdjust = l_cpTechTier->m_iSkillAdjust;
			}
		}

		if (!l_cTierTag.GetTagValue (a_cParser, (CString) "tier-techsize", l_cpTechTier->m_iSize, a_bInitialise))
		{
			l_cpTechTier->m_iSize = 1;
		}


		l_cTierTag.GetTagValue (a_cParser, (CString) "tier-prefix", l_cpTechTier->m_csPrefix, a_bInitialise);
		l_cTierTag.GetTagValue (a_cParser, (CString) "tier-suffix", l_cpTechTier->m_csSuffix, a_bInitialise);

		if (l_cTierKeywordTag.GetNextTag (a_cParser, l_cTierTag))
		{

			while (l_cTierKeywordSetTag.GetNextTag (a_cParser, l_cTierKeywordTag))
			{
				l_cpKeywordGroup = new CKeywordGroup ();
				while (l_cTierKeywordSetTag.GetRepeatingTagValue (a_cParser, (CString) "tier-keyword", l_csValue, a_bInitialise))
				{
					if ((l_csValue.Left (10) != cTechKeyword_TechClass) &&
						 (l_csValue.Left (5) != cTechKeyword_Tier))
					{
						l_cpKeywordGroup->m_clKeywordList.AddTail (l_csValue);
						m_bTierLevelKeywords = true;
					}
				}

				if (l_cpKeywordGroup->m_clKeywordList.GetCount () > 0)
				{
					l_cpTechTier->m_clKeywordSets.AddTail (l_cpKeywordGroup);
				}
				else
				{
					delete (l_cpKeywordGroup);
				}
			}
		}

		if (l_cTierEffectKeywordTag.GetNextTag (a_cParser, l_cTierTag))
		{

			while (l_cTierEffectKeywordSetTag.GetNextTag (a_cParser, l_cTierEffectKeywordTag))
			{
				l_cpKeywordGroup = new CKeywordGroup ();
				while (l_cTierEffectKeywordSetTag.GetRepeatingTagValue (a_cParser, (CString) "tier-effectkeyword", l_csValue, a_bInitialise))
				{
					l_cpKeywordGroup->m_clKeywordList.AddTail (l_csValue);
				}
				l_cpTechTier->m_clKeywordEffectSets.AddTail (l_cpKeywordGroup);
			}
		}

		if (l_cTierAttributesTag.GetNextTag (a_cParser, l_cTierTag))
		{
			while (l_cTierAttributesTag.GetRepeatingDoubleTagValue (a_cParser, (CString) "tier-attribute", l_csAttribute, l_csValue))
			{
				l_cpEffect = new CEffect();
				l_cpEffect->m_csType = l_csAttribute;
				l_cpEffect->m_csDescription = l_csValue;
				l_cpEffect->TranslateEffectType ();

				l_cpTechTier->m_clEffectList.AddTail (l_cpEffect);

				if (l_cpEffect->m_csType == cXMLAttribute_Bonus)
				{
					l_bTechBonus = true;
				}
			}
		}

		if (l_cResourceTag.GetNextTag (a_cParser, l_cTierTag))
		{
			while (l_cResourceTag.GetRepeatingDoubleTagValue (a_cParser, (CString) "component", l_csValue, l_cItemResource.m_csName, a_bInitialise))
			{
				l_cpItemResource = new CItemResource ();
				l_cpItemResource->m_csName = l_cItemResource.m_csName;
				l_cpItemResource->m_iMinAmt = atoi (l_csValue);
				l_cpItemResource->m_iOptAmt = l_cpItemResource->m_iMinAmt;

				l_cpTechTier->m_clResourceList.AddTail (l_cpItemResource);
			}
		}

		// Temporary fix to add bonus data, remove when real data arrives
		if (!l_bTechBonus)
		{
			int l_iStatStart;
			int l_iStatStop;
			CString l_csAttributeText;
			CString l_csBonusText;

			l_csAttributeText = l_cpTechTier->m_csDescription;
			l_iStatStart = l_csAttributeText.Find ("Health and Armor");
			if (l_iStatStart >= 0)
			{
				l_cpEffect = new CEffect();
				l_cpEffect->m_csType = cXMLAttribute_Bonus;
				l_cpEffect->m_csDescription = "+5 Health";
				l_cpTechTier->m_clEffectList.AddTail (l_cpEffect);

				l_cpEffect = new CEffect();
				l_cpEffect->m_csType = cXMLAttribute_Bonus;
				l_cpEffect->m_csDescription = "+5 Armor";
				l_cpTechTier->m_clEffectList.AddTail (l_cpEffect);
			}
			else
			{
				l_csAttributeText.Replace ("addtional", "additional");
				l_csAttributeText.Replace ("This technique gives the user +", "an additional +");
				l_csAttributeText.Replace ("to give a +", "an additional +");
				l_iStatStart = l_csAttributeText.Find ("an additional +");
				if (l_iStatStart >= 0)
				{
					l_csAttributeText = l_csAttributeText.Mid (l_iStatStart + 14);
					l_csAttributeText.Replace ("to the ", "");
					l_csAttributeText.Replace ("in the ", "");
					l_csAttributeText.Replace (" trade skill.", "");
					l_csAttributeText.Replace (" magic skill.", "");
					l_csAttributeText.Replace (" adventure skill.", "");
					l_csAttributeText.Replace (" defense.", "");
					l_csAttributeText.Replace (" statistic.", "");
					l_csAttributeText.Replace (" skill when it is equipped.", "");
					l_csAttributeText.Replace (" skill.", "");

					l_cpEffect = new CEffect();
					l_cpEffect->m_csType = cXMLAttribute_Bonus;
					l_cpEffect->m_csDescription = l_csAttributeText;

					l_cpTechTier->m_clEffectList.AddTail (l_cpEffect);
				}
				else
				{
					l_iStatStart = l_csAttributeText.Find ("certain objects with +");
					if (l_iStatStart >= 0)
					{
						l_csAttributeText = l_cpTechTier->m_csDescription.Mid (l_iStatStart + 21);
						l_csAttributeText.Replace ("in the ", "");
						l_csAttributeText.Replace (" craft skills.", "");
						l_csAttributeText.Replace (" and", "");
						l_iStatStop = l_csAttributeText.Find (' ');
						if (l_iStatStop >= 0)
						{
							l_csBonusText = l_csAttributeText.Left (l_iStatStop);
							l_csAttributeText.Replace (",", "," + l_csBonusText);

							l_iStatStart = 0;
							while (l_iStatStart >= 0)
							{
								l_iStatStop = l_csAttributeText.Find (",", l_iStatStart);
								if (l_iStatStop >= 0)
								{
									l_cpEffect = new CEffect();
									l_cpEffect->m_csType = cXMLAttribute_Bonus;
									l_cpEffect->m_csDescription = l_csAttributeText.Mid (l_iStatStart, (l_iStatStop - l_iStatStart));

									l_cpTechTier->m_clEffectList.AddTail (l_cpEffect);

									l_iStatStart = l_iStatStop + 1;
								}
								else
								{
									l_cpEffect = new CEffect();
									l_cpEffect->m_csType = cXMLAttribute_Bonus;
									l_cpEffect->m_csDescription = l_csAttributeText.Mid (l_iStatStart);

									l_cpTechTier->m_clEffectList.AddTail (l_cpEffect);

									l_iStatStart = -1;
								}
							}
						}
					}
				}
			}
		}

	}


	if (m_bTierLevelKeywords)
	{
		MoveKeywordsToTiers ();
	}

	return (l_bResult);
}

bool CTech::FindTechTier(CString &a_csTier, CTechTier **a_cpTechTier)
{
	bool l_bFound = false;
	POSITION l_Pos;
	CTechTier *l_cpTechTier;

	l_Pos = m_clTechTierList.GetHeadPosition ();

	while (l_Pos)
	{
		l_cpTechTier = m_clTechTierList.GetNext (l_Pos);

		if (l_cpTechTier->m_csTierName == a_csTier)
		{
			*a_cpTechTier = l_cpTechTier;
			return (true);
		}
	}

	return (l_bFound);
}

bool CTech::CheckFormula(CFormula *a_cpFormula, CFormulaTier *a_cpFormulaTier)
{
	bool l_bResult = false;
	static bool l_bLoopResult;
	static CFormulaTier *l_cpFormulaTier = NULL;
	static CTechTier *l_cpTechTier = NULL;
	static CKeywordGroup *l_cpFormulaKeywordGroups[50];
	static CTypedPtrList<CPtrList, CKeywordGroup*> *l_cpTechKeywordSets[50];
	static CTypedPtrList<CPtrList, CKeywordGroup*> *l_cpTechKeywordEffectSets[50];
	static CKeywordGroup *l_cpKeywordGroup;
	static POSITION l_Pos;
	static int l_iFormOffset;
	static int l_iTechOffset;
	static int l_iFormulaCount;
	static int l_iTechCount;

	if (a_cpFormula)
	{
		l_iFormulaCount = 0;
		l_iTechCount = 0;

		if (a_cpFormula->m_bTierLevelKeywords)
		{
			l_Pos = a_cpFormula->m_clFormulaTierList.GetHeadPosition ();
			while (l_Pos)
			{
				l_cpFormulaTier = a_cpFormula->m_clFormulaTierList.GetNext (l_Pos);

				if (l_cpFormulaTier->m_iAllowedTechniques > 0)
				{
					l_cpFormulaKeywordGroups[l_iFormulaCount++] = &l_cpFormulaTier->m_cKeywords;
				}
			}
		}
		else
		{
			l_cpFormulaKeywordGroups[l_iFormulaCount++] = &a_cpFormula->m_cKeywords;
		}

		if (m_bTierLevelKeywords)
		{
			l_Pos = m_clTechTierList.GetHeadPosition ();
			while (l_Pos)
			{
				l_cpTechTier = m_clTechTierList.GetNext (l_Pos);
				l_cpTechKeywordSets[l_iTechCount] = &l_cpTechTier->m_clKeywordSets;
				l_cpTechKeywordEffectSets[l_iTechCount++] = &l_cpTechTier->m_clKeywordEffectSets;
			}
		}
		else
		{
			l_cpTechKeywordSets[l_iTechCount] = &m_clKeywordSets;
			l_cpTechKeywordEffectSets[l_iTechCount++] = &m_clKeywordEffectSets;
		}

		l_bResult = false;
		l_iTechOffset = 0;
		while ((!l_bResult) && (l_iTechOffset < l_iTechCount))
		{
			l_iFormOffset = 0;
			while ((!l_bResult) && (l_iFormOffset < l_iFormulaCount))
			{
				l_bLoopResult = true;
				l_Pos = l_cpTechKeywordSets[l_iTechOffset]->GetHeadPosition ();
				while ((l_bLoopResult) && (l_Pos))
				{
					l_cpKeywordGroup = l_cpTechKeywordSets[l_iTechOffset]->GetNext (l_Pos);
					l_bLoopResult = l_bLoopResult && l_cpFormulaKeywordGroups[l_iFormOffset]->Match (l_cpKeywordGroup);
				}
				l_iFormOffset++;

				if (l_bLoopResult)
				{
					l_bResult = true;
				}
			}
			l_iTechOffset++;
		}

		if (l_bResult)
		{
			l_bResult = false;
			l_iTechOffset = 0;
			while ((!l_bResult) && (l_iTechOffset < l_iTechCount))
			{
				l_iFormOffset = 0;
				while ((!l_bResult) && (l_iFormOffset < l_iFormulaCount))
				{
					l_bLoopResult = true;
					l_Pos = l_cpTechKeywordEffectSets[l_iTechOffset]->GetHeadPosition ();
					while ((l_bLoopResult) && (l_Pos))
					{
						l_cpKeywordGroup = l_cpTechKeywordEffectSets[l_iTechOffset]->GetNext (l_Pos);
						l_bLoopResult = l_bLoopResult && (!l_cpFormulaKeywordGroups[l_iFormOffset]->Match (l_cpKeywordGroup));
					}
					l_iFormOffset++;

					if (l_bLoopResult)
					{
						l_bResult = true;
					}
				}
				l_iTechOffset++;
			}
		}

		/*if ((l_bResult) && (a_cpFormulaTier))
		{
			if (a_cpFormula->m_bTierLevelKeywords)
			{
				l_Pos = m_clKeywordSets.GetHeadPosition ();
				while ((l_bResult) && (l_Pos))
				{
					l_cpKeywordGroup = m_clKeywordSets.GetNext (l_Pos);
					l_bResult = l_bResult && a_cpFormulaTier->m_cKeywords.Match (l_cpKeywordGroup);
				}

				if (l_bResult)
				{
					l_Pos = m_clKeywordEffectSets.GetHeadPosition ();
					while (l_Pos)
					{
						l_cpKeywordGroup = m_clKeywordEffectSets.GetNext (l_Pos);
						l_bResult = l_bResult && (!a_cpFormulaTier->m_cKeywords.Match (l_cpKeywordGroup));
					}
				}
			}
		}*/
	}
	return (l_bResult);
}

bool CTech::CheckTech(CTech *a_cpTech)
{
	bool l_bResult = false;
	CKeywordGroup *l_cpLocalKeywordGroup;
	CKeywordGroup *l_cpRemoteKeywordGroup;
	POSITION l_LocalPos;
	POSITION l_RemotePos;

	if (a_cpTech)
	{
		l_bResult = true;
		l_LocalPos = m_clKeywordEffectSets.GetHeadPosition ();
		while (l_LocalPos)
		{
			l_cpLocalKeywordGroup = m_clKeywordEffectSets.GetNext (l_LocalPos);
			l_RemotePos = a_cpTech->m_clKeywordEffectSets.GetHeadPosition ();
			while ((l_bResult) && (l_RemotePos))
			{
				l_cpRemoteKeywordGroup = m_clKeywordEffectSets.GetNext (l_RemotePos);
				l_bResult = l_bResult && (!l_cpLocalKeywordGroup->Match (l_cpRemoteKeywordGroup));
			}
		}
	}

	return (l_bResult);
}

CTech::WriteToFile(CStdioFile &a_cFile)
{
	CString l_csLine;
	CKeywordGroup *l_cpKeywordGroup;
	CEffect *l_cpEffectGroup;
	CTechTier *l_cpTechTier;

	l_csLine.Format ("%s|%d|%s|%s|%s|%s|%s|%d|%d|%d|%d\n",
		              m_csName,
						  m_iIcon,
						  m_csPrefix,
						  m_csSuffix,
						  m_csDescription,
						  m_csSubDescription,
						  BoolToStr(m_bTierLevelKeywords),
						  m_clEffectsList.GetCount(),
						  m_clKeywordSets.GetCount(),
						  m_clKeywordEffectSets.GetCount(),
						  m_clTechTierList.GetCount());
	a_cFile.WriteString (l_csLine);

	POSITION l_Pos = m_clEffectsList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpEffectGroup = m_clEffectsList.GetNext (l_Pos);
		l_cpEffectGroup->WriteToFile (a_cFile);
	}

	l_Pos = m_clKeywordSets.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpKeywordGroup = m_clKeywordSets.GetNext (l_Pos);
		l_cpKeywordGroup->WriteToFile (a_cFile);
	}

	l_Pos = m_clKeywordEffectSets.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpKeywordGroup = m_clKeywordEffectSets.GetNext (l_Pos);
		l_cpKeywordGroup->WriteToFile (a_cFile);
	}

	l_Pos = m_clTechTierList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpTechTier = m_clTechTierList.GetNext (l_Pos);
		l_cpTechTier->WriteToFile (a_cFile);
	}
}

bool CTech::ReadFromFile(CStdioFile &a_cFile)
{
	CString l_csLine;
	bool l_bSuccess = true;
	int l_iTokenOffset = 0;
	int l_iEffectCount = 0;
	int l_iKeywordCount = 0;
	int l_iKeywordEffectCount = 0;
	int l_iTechTierCount = 0;
	CEffect *l_cpEffectGroup;
	CKeywordGroup *l_cpKeywordGroup;
	CTechTier *l_cpTechTier;
	CString l_csValue;

	if (a_cFile.ReadString (l_csLine))
	{
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csName);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_iIcon);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csPrefix);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csSuffix);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csDescription);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csSubDescription);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, l_csValue);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, l_iEffectCount);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, l_iKeywordCount);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, l_iKeywordEffectCount);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, l_iTechTierCount);
		m_bTierLevelKeywords = StrToBool (l_csValue);

		if (l_bSuccess)
		{
			while (l_iEffectCount--)
			{
				l_cpEffectGroup = new CEffect();
				l_bSuccess = l_bSuccess && l_cpEffectGroup->ReadFromFile (a_cFile);
				m_clEffectsList.AddTail (l_cpEffectGroup);
			}
		}

		if (l_bSuccess)
		{
			while (l_iKeywordCount--)
			{
				l_cpKeywordGroup = new CKeywordGroup();
				l_bSuccess = l_bSuccess && l_cpKeywordGroup->ReadFromFile (a_cFile);
				m_clKeywordSets.AddTail (l_cpKeywordGroup);
			}
		}

		if (l_bSuccess)
		{
			while (l_iKeywordEffectCount--)
			{
				l_cpKeywordGroup = new CKeywordGroup();
				l_bSuccess = l_bSuccess && l_cpKeywordGroup->ReadFromFile (a_cFile);
				m_clKeywordEffectSets.AddTail (l_cpKeywordGroup);
			}
		}

		if (l_bSuccess)
		{
			while (l_iTechTierCount--)
			{
				l_cpTechTier = new CTechTier();
				l_bSuccess = l_bSuccess && l_cpTechTier->ReadFromFile (a_cFile);
				m_clTechTierList.AddTail (l_cpTechTier);
			}
		}
	}

	return (l_bSuccess);
}

CTech::MoveKeywordsToTiers()
{
	POSITION l_SetPos;
	POSITION l_GroupPos;
	POSITION l_TierPos;
	CTechTier *l_cpTechTier;
	CKeywordGroup *l_cpKeywordGroup;
	CKeywordGroup *l_cpNewKeywordGroup;

	l_TierPos = m_clTechTierList.GetHeadPosition ();
	while (l_TierPos)
	{
		l_cpTechTier = m_clTechTierList.GetNext (l_TierPos);

		l_SetPos = m_clKeywordSets.GetHeadPosition ();
		while (l_SetPos)
		{
			l_cpKeywordGroup = m_clKeywordSets.GetNext (l_SetPos);
			l_cpNewKeywordGroup = new CKeywordGroup ();
			l_cpTechTier->m_clKeywordSets.AddTail (l_cpNewKeywordGroup);

			l_GroupPos = l_cpKeywordGroup->m_clKeywordList.GetHeadPosition ();
			while (l_GroupPos)
			{
				l_cpNewKeywordGroup->m_clKeywordList.AddTail (l_cpKeywordGroup->m_clKeywordList.GetNext (l_GroupPos));
			}
		}

		l_SetPos = m_clKeywordEffectSets.GetHeadPosition ();
		while (l_SetPos)
		{
			l_cpKeywordGroup = m_clKeywordEffectSets.GetNext (l_SetPos);
			l_cpNewKeywordGroup = new CKeywordGroup ();
			l_cpTechTier->m_clKeywordEffectSets.AddTail (l_cpNewKeywordGroup);

			l_GroupPos = l_cpKeywordGroup->m_clKeywordList.GetHeadPosition ();
			while (l_GroupPos)
			{
				l_cpNewKeywordGroup->m_clKeywordList.AddTail (l_cpKeywordGroup->m_clKeywordList.GetNext (l_GroupPos));
			}
		}
	}

}
