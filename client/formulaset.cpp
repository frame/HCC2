// FormulaSet.cpp: implementation of the CFormulaSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HCC.h"
#include "FormulaSet.h"
#include "XMLTag.h"
#include "XMLParser.h"
#include "AppData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "ItemInfo.h"
#include "Bonus.h"
#include "ItemResource.h"
#include "FormulaTier.h"
#include "Formula.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFormulaSet::CFormulaSet()
{

}

CFormulaSet::~CFormulaSet()
{
	Destroy (false);
}

CFormulaSet::operator =( const CFormulaSet* pSrc )
{
   CopyObject (pSrc);
   return true;
}


CFormulaSet::CFormulaSet(const CFormulaSet *pSrc)
{
   CopyObject (pSrc);
}

void CFormulaSet::CopyObject(const CFormulaSet *pSrc)
{
	m_csName = pSrc->m_csName;
	m_csCategory = pSrc->m_csCategory;
	m_csFormat = pSrc->m_csFormat;
	m_iIcon = pSrc->m_iIcon;

	m_clFormulaList.RemoveAll ();
	POSITION l_Pos = pSrc->m_clFormulaList.GetHeadPosition ();
	while (l_Pos)
	{
		m_clFormulaList.AddTail (pSrc->m_clFormulaList.GetNext (l_Pos));
	}

}

CFormulaSet::Destroy(bool a_bAll)
{
	CFormula *l_cpFormula;

	if (a_bAll)
	{
		POSITION l_Pos = m_clFormulaList.GetHeadPosition ();
		while (l_Pos)
		{
			l_cpFormula = m_clFormulaList.GetNext (l_Pos);
			l_cpFormula->Destroy ();
			delete (l_cpFormula);
		}
	}
	m_clFormulaList.RemoveAll ();
}

bool CFormulaSet::LoadFormulaSet(CString a_csFilename)
{
	bool l_bResult = true;

	XMLParser l_cParser;
	XMLTag l_cRootTag ("#ROOT#");
	XMLTag l_cFormulaSetTag ("formulaset");
	XMLTag l_cCategoryTag ("formulaset-categories");
	XMLTag l_cItemTag ("item");

	CFormula			*l_cpFormula;
	CSubCategory	*l_cpSubCategory;

	CString l_csIconName;
	CString l_csDescription;
	CString l_csValue;

	l_cParser.OpenFile (a_csFilename);

	// Should be only one Craft Tag
	if (l_cFormulaSetTag.GetNextTag (l_cParser, l_cRootTag))
	{
		l_cFormulaSetTag.GetTagValue (l_cParser, (CString) "formulaset-name", m_csName);
		if (CAppData::FindSubCategory (m_csName, &l_cpSubCategory))
		{
			m_iIcon = l_cpSubCategory->m_iIcon;
		}
		else
		{
			m_iIcon = 0;
		}

		if (l_cCategoryTag.GetNextTag (l_cParser, l_cFormulaSetTag))
		{
			l_cCategoryTag.GetTagValue (l_cParser, (CString) "formulaset-category", m_csCategory);
		}

		while (l_cItemTag.GetNextTag (l_cParser, l_cFormulaSetTag))
		{
			l_cpFormula = new CFormula ();
			l_cpFormula->LoadFormula (m_csCategory, l_cParser, l_cItemTag);
			m_clFormulaList.AddTail (l_cpFormula);
		}
	}

	return (l_bResult);
}

CFormulaSet::AddSet(CFormulaSet *a_cFormulaSet)
{
	POSITION l_Pos;
	CFormula *l_cpFormula;

	l_Pos = a_cFormulaSet->m_clFormulaList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpFormula = a_cFormulaSet->m_clFormulaList.GetNext (l_Pos);
		m_clFormulaList.AddTail (l_cpFormula);
	}
}

CFormulaSet::WriteToFile(CStdioFile &a_cFile)
{
	CString l_csLine;
	CFormula *l_cpFormula;

	l_csLine.Format ("%s|%s|%s|%d|%d\n", m_csName,
		                                  m_csCategory,
													 m_csFormat,
													 m_iIcon,
													 m_clFormulaList.GetCount());
	a_cFile.WriteString (l_csLine);

	POSITION l_Pos = m_clFormulaList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpFormula = m_clFormulaList.GetNext (l_Pos);
		l_cpFormula->WriteToFile (a_cFile);
	}
}

bool CFormulaSet::ReadFromFile(CStdioFile &a_cFile)
{
	CString l_csLine;
	bool l_bSuccess = true;
	int l_iTokenOffset = 0;
	int l_iFormulaCount = 0;
	CFormula *l_cpFormula;

	if (a_cFile.ReadString (l_csLine))
	{
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csName);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csCategory);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csFormat);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_iIcon);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, l_iFormulaCount);

		if (l_bSuccess)
		{
			while (l_iFormulaCount--)
			{
				l_cpFormula = new CFormula();
				l_bSuccess = l_bSuccess && l_cpFormula->ReadFromFile (a_cFile);
				m_clFormulaList.AddTail (l_cpFormula);
			}
		}
	}

	return (l_bSuccess);
}
