// Tech.cpp: implementation of the CTechTier class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HCC.h"
#include "Tech.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTechTier::CTechTier()
{
	m_iSkillAdjust = 0;
	m_iUsageAdjust = 0;
}

CTechTier::~CTechTier()
{
	Destroy();
}

CTechTier::operator =( const CTechTier* pSrc )
{
   CopyObject (pSrc);
   return true;
}


CTechTier::CTechTier(const CTechTier *pSrc)
{
   CopyObject (pSrc);
}

void CTechTier::CopyObject(const CTechTier *pSrc)
{
	m_csName = pSrc->m_csName;
	m_csOrigin = pSrc->m_csOrigin;
	m_iTierLevel = pSrc->m_iTierLevel;
	m_csTierName = pSrc->m_csTierName;
	m_csDescription = pSrc->m_csDescription;
	m_iSkillAdjust = pSrc->m_iSkillAdjust;
	m_iUsageAdjust = pSrc->m_iUsageAdjust;
	m_csPrefix = pSrc->m_csPrefix;
	m_csSuffix = pSrc->m_csSuffix;
	m_iSize = pSrc->m_iSize;

	m_clKeywordSets.RemoveAll ();
	POSITION l_Pos = pSrc->m_clKeywordSets.GetHeadPosition ();
	while (l_Pos)
	{
		m_clKeywordSets.AddTail (pSrc->m_clKeywordSets.GetNext (l_Pos));
	}

	m_clKeywordEffectSets.RemoveAll ();
	l_Pos = pSrc->m_clKeywordEffectSets.GetHeadPosition ();
	while (l_Pos)
	{
		m_clKeywordEffectSets.AddTail (pSrc->m_clKeywordEffectSets.GetNext (l_Pos));
	}

	m_clEffectList.RemoveAll ();
	l_Pos = pSrc->m_clEffectList.GetHeadPosition ();
	while (l_Pos)
	{
		m_clEffectList.AddTail (pSrc->m_clEffectList.GetNext (l_Pos));
	}

	m_clResourceList.RemoveAll ();
	l_Pos = pSrc->m_clResourceList.GetHeadPosition ();
	while (l_Pos)
	{
		m_clResourceList.AddTail (pSrc->m_clResourceList.GetNext (l_Pos));
	}

}

CTechTier::Destroy()
{
	CKeywordGroup *l_cpKeywordGroup;
	CEffect		  *l_cpEffect;
	CItemResource *l_cpItemResource;

	POSITION l_Pos = m_clKeywordSets.GetHeadPosition ();
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

	l_Pos = m_clEffectList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpEffect = m_clEffectList.GetNext (l_Pos);
		l_cpEffect->Destroy ();
		delete (l_cpEffect);
	}
	m_clEffectList.RemoveAll ();

	l_Pos = m_clResourceList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpItemResource = m_clResourceList.GetNext (l_Pos);
		l_cpItemResource->Destroy ();
		delete (l_cpItemResource);
	}
	m_clResourceList.RemoveAll ();
}

CTechTier::Clear()
{
	m_csName.Empty ();
	m_iTierLevel = 0;
	m_csTierName.Empty ();
	Destroy();
}

CTechTier::WriteToFile(CStdioFile &a_cFile)
{
	CString l_csLine;
	CKeywordGroup *l_cpKeywordGroup;
	CEffect		  *l_cpEffect;
	CItemResource *l_cpItemResource;

	l_csLine.Format ("%s|%s|%d|%s|%s|%d|%d|%s|%s|%d|%d|%d|%d|%d\n",
		              m_csName,
						  m_csOrigin,
						  m_iTierLevel,
						  m_csTierName,
						  m_csDescription,
						  m_iSkillAdjust,
						  m_iUsageAdjust,
						  m_csPrefix,
						  m_csSuffix,
						  m_iSize,
						  m_clKeywordSets.GetCount(),
						  m_clKeywordEffectSets.GetCount(),
						  m_clEffectList.GetCount(),
						  m_clResourceList.GetCount());
	a_cFile.WriteString (l_csLine);

	POSITION l_Pos = m_clKeywordSets.GetHeadPosition ();
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

	l_Pos = m_clEffectList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpEffect = m_clEffectList.GetNext (l_Pos);
		l_cpEffect->WriteToFile (a_cFile);
	}

	l_Pos = m_clResourceList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpItemResource = m_clResourceList.GetNext (l_Pos);
		l_cpItemResource->WriteToFile (a_cFile);
	}
}

bool CTechTier::ReadFromFile(CStdioFile &a_cFile)
{
	CString l_csLine;
	bool l_bSuccess = true;
	int l_iTokenOffset = 0;
	int l_iKeywordCount = 0;
	int l_iKeywordEffectCount = 0;
	int l_iEffectCount = 0;
	int l_iResourceCount = 0;
	CKeywordGroup *l_cpKeywordGroup;
	CEffect		  *l_cpEffect;
	CItemResource *l_cpItemResource;

	if (a_cFile.ReadString (l_csLine))
	{
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csName);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csOrigin);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_iTierLevel);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csTierName);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csDescription);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_iSkillAdjust);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_iUsageAdjust);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csPrefix);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csSuffix);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_iSize);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, l_iKeywordCount);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, l_iKeywordEffectCount);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, l_iEffectCount);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, l_iResourceCount);

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
			while (l_iEffectCount--)
			{
				l_cpEffect = new CEffect();
				l_bSuccess = l_bSuccess && l_cpEffect->ReadFromFile (a_cFile);
				m_clEffectList.AddTail (l_cpEffect);
			}
		}

		if (l_bSuccess)
		{
			while (l_iResourceCount--)
			{
				l_cpItemResource = new CItemResource();
				l_bSuccess = l_bSuccess && l_cpItemResource->ReadFromFile (a_cFile);
				m_clResourceList.AddTail (l_cpItemResource);
			}
		}
	}

	return (l_bSuccess);
}

bool CTechTier::CheckFormula(CFormula *a_cpFormula, CFormulaTier *a_cpFormulaTier)
{
	bool l_bResult = false;
	static CFormulaTier *l_cpFormulaTier = NULL;
	static CTechTier *l_cpTechTier = NULL;
	static CKeywordGroup *l_cpFormulaKeywordGroup;
	static CKeywordGroup *l_cpKeywordGroup;
	static POSITION l_Pos;

	if (a_cpFormula)
	{
		if (a_cpFormula->m_bTierLevelKeywords)
		{
			l_cpFormulaKeywordGroup = &a_cpFormulaTier->m_cKeywords;
		}
		else
		{
			l_cpFormulaKeywordGroup = &a_cpFormula->m_cKeywords;
		}

		l_bResult = true;
		l_Pos = m_clKeywordSets.GetHeadPosition ();
		while ((l_bResult) && (l_Pos))
		{
			l_cpKeywordGroup = m_clKeywordSets.GetNext (l_Pos);
			l_bResult = l_bResult && l_cpFormulaKeywordGroup->Match (l_cpKeywordGroup);
		}

		if (l_bResult)
		{
			l_Pos = m_clKeywordEffectSets.GetHeadPosition ();
			while ((l_bResult) && (l_Pos))
			{
				l_cpKeywordGroup = m_clKeywordEffectSets.GetNext (l_Pos);
				l_bResult = l_bResult && (!l_cpFormulaKeywordGroup->Match (l_cpKeywordGroup));
			}
		}
	}
	return (l_bResult);
}

