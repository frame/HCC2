// TechSet.cpp: implementation of the CTechSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HCC.h"
#include "TechSet.h"
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
#include "TechTier.h"
#include "Tech.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTechSet::CTechSet()
{

}

CTechSet::~CTechSet()
{
	Destroy(false);
}

CTechSet::operator =( const CTechSet* pSrc )
{
   CopyObject (pSrc);
   return true;
}


CTechSet::CTechSet(const CTechSet *pSrc)
{
   CopyObject (pSrc);
}

void CTechSet::CopyObject(const CTechSet *pSrc)
{
	m_csName = pSrc->m_csName;
	m_csCategory = pSrc->m_csCategory;
	m_csFormat = pSrc->m_csFormat;
	m_iIcon = pSrc->m_iIcon;

	m_clTechList.RemoveAll ();
	POSITION l_Pos = pSrc->m_clTechList.GetHeadPosition ();
	while (l_Pos)
	{
		m_clTechList.AddTail (pSrc->m_clTechList.GetNext (l_Pos));
	}

}

CTechSet::Destroy(bool a_bAll)
{
	CTech *l_cpTech;

	if (a_bAll)
	{
		POSITION l_Pos = m_clTechList.GetHeadPosition ();
		while (l_Pos)
		{
			l_cpTech = m_clTechList.GetNext (l_Pos);
			l_cpTech->Destroy ();
			delete (l_cpTech);
		}
	}
	m_clTechList.RemoveAll ();
}

bool CTechSet::LoadTechSet(CString a_csFilename)
{
	bool l_bResult = true;

	XMLParser l_cParser;
	XMLTag l_cRootTag							("#ROOT#");
	XMLTag l_cTechSetTag						("techniqueset");
	XMLTag l_cCategoryTag					("techniqueset-categories");
	XMLTag l_cItemTag							("tech");

	CTech				*l_cpTech = NULL;
	CSubCategory	*l_cpSubCategory;

	l_cParser.OpenFile (a_csFilename);
	m_clTechList.RemoveAll ();

	// Should be only one Craft Tag
	if (l_cTechSetTag.GetNextTag (l_cParser, l_cRootTag))
	{
		l_cTechSetTag.GetTagValue (l_cParser, (CString) "techniqueset-name", m_csName);
		if (l_cCategoryTag.GetNextTag (l_cParser, l_cTechSetTag))
		{
			l_cCategoryTag.GetTagValue (l_cParser, (CString) "techniqueset-category", m_csCategory);
		}

		if (CAppData::FindSubCategory (m_csCategory, &l_cpSubCategory))
		{
			m_iIcon = l_cpSubCategory->m_iIcon;
		}
		else
		{
			m_iIcon = 0;
		}


		while (l_cItemTag.GetNextTag (l_cParser, l_cTechSetTag))
		{
			l_cpTech = new CTech ();
			l_cpTech->LoadTech (m_csCategory, l_cParser, l_cItemTag);
			m_clTechList.AddTail (l_cpTech);
		}
	}

	return (l_bResult);
}

CTechSet::AddSet(CTechSet *a_cpTechSet)
{
	POSITION l_Pos;
	CTech *l_cpTech;

	l_Pos = a_cpTechSet->m_clTechList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpTech = a_cpTechSet->m_clTechList.GetNext (l_Pos);
		m_clTechList.AddTail (l_cpTech);
	}
}

CTechSet::WriteToFile(CStdioFile &a_cFile)
{
	CString l_csLine;
	CTech *l_cpTech;

	l_csLine.Format ("%s|%s|%s|%d|%d\n",
		              m_csName,
						  m_csFormat,
						  m_csCategory,
						  m_iIcon,
						  m_clTechList.GetCount());
	a_cFile.WriteString (l_csLine);

	POSITION l_Pos = m_clTechList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpTech = m_clTechList.GetNext (l_Pos);
		l_cpTech->WriteToFile (a_cFile);
	}
}

bool CTechSet::ReadFromFile(CStdioFile &a_cFile)
{
	CString l_csLine;
	bool l_bSuccess = true;
	int l_iTokenOffset = 0;
	int l_iTechCount = 0;
	CTech *l_cpTech;

	if (a_cFile.ReadString (l_csLine))
	{
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csName);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csFormat);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csCategory);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_iIcon);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, l_iTechCount);

		if (l_bSuccess)
		{
			while (l_iTechCount--)
			{
				l_cpTech = new CTech();
				l_bSuccess = l_bSuccess && l_cpTech->ReadFromFile (a_cFile);
				m_clTechList.AddTail (l_cpTech);
			}
		}
	}

	return (l_bSuccess);
}
