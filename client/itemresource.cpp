// Item.cpp: implementation of the CItemResource class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ItemResource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CItemResource::CItemResource()
{
	Clear();
}

CItemResource::~CItemResource()
{

}

CItemResource::operator =( const CItemResource* pSrc )
{
   CopyObject (pSrc);
   return true;
}


CItemResource::CItemResource(const CItemResource *pSrc)
{
   CopyObject (pSrc);
}

void CItemResource::CopyObject(const CItemResource *pSrc)
{
	m_csName = pSrc->m_csName;
	m_csSkill = pSrc->m_csSkill;
	m_iUnits = pSrc->m_iUnits;
	m_iMinLvl = pSrc->m_iMinLvl;
	m_iMinAmt = pSrc->m_iMinAmt;
	m_iOptLvl = pSrc->m_iOptLvl;
	m_iOptAmt = pSrc->m_iOptAmt;

}

CItemResource::Clear()
{
	m_csName.Empty ();;
	m_csSkill.Empty ();
	m_iUnits = 0;
	m_iMinLvl = 0;
	m_iMinAmt = 0;
	m_iOptLvl = 0;
	m_iOptAmt = 0;
}

int CItemResource::DetermineSkillForAmount(int a_iAmount)
{
	float l_fAmountRange;
	float l_fSkillRange;
	float l_fSkill;

	if (m_iOptAmt == m_iMinAmt)
	{
		return (m_iMinLvl);
	}

	l_fAmountRange = float (a_iAmount - m_iOptAmt) / float (m_iMinAmt - m_iOptAmt);
	l_fSkillRange = float (m_iOptLvl - m_iMinLvl);
	l_fSkill = l_fSkillRange * l_fAmountRange;

	return (m_iOptLvl - int (l_fSkill));
}

CItemResource::Destroy()
{

}

CItemResource::WriteToFile(CStdioFile &a_cFile)
{
	CString l_csLine;

	l_csLine.Format ("%s|%s|%d|%d|%d|%d|%d\n", m_csName, m_csSkill, m_iMinLvl, m_iMinAmt, m_iOptLvl, m_iOptAmt, m_iUnits);
	a_cFile.WriteString (l_csLine);
}

bool CItemResource::ReadFromFile(CStdioFile &a_cFile)
{
	CString l_csLine;
	bool l_bSuccess = true;
	int l_iTokenOffset = 0;

	if (a_cFile.ReadString (l_csLine))
	{
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csName);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csSkill);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_iMinLvl);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_iMinAmt);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_iOptLvl);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_iOptAmt);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_iUnits);
	}

	return (l_bSuccess);
}
