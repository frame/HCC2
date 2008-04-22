// Item.cpp: implementation of the CCompBonusInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CompBonusInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCompBonusInfo::CCompBonusInfo()
{
	Clear();
}

CCompBonusInfo::~CCompBonusInfo()
{

}

CCompBonusInfo::operator =( const CCompBonusInfo* pSrc )
{
   CopyObject (pSrc);
   return true;
}


CCompBonusInfo::CCompBonusInfo(const CCompBonusInfo *pSrc)
{
   CopyObject (pSrc);
}

void CCompBonusInfo::CopyObject(const CCompBonusInfo *pSrc)
{
	m_csName = pSrc->m_csName;
	m_csAmount = pSrc->m_csAmount;
	m_csChance = pSrc->m_csChance;
}

CCompBonusInfo::Clear()
{
	m_csName.Empty ();;
	m_csChance.Empty ();
	m_csAmount.Empty ();;
}

CCompBonusInfo::Destroy()
{

}

CCompBonusInfo::WriteToFile(CStdioFile &a_cFile)
{
	CString l_csLine;

	l_csLine.Format ("%s|%s|%s\n", 	m_csName,
												m_csChance,
												m_csAmount);
	a_cFile.WriteString (l_csLine);
}

bool CCompBonusInfo::ReadFromFile(CStdioFile &a_cFile)
{
	CString l_csLine;
	bool l_bSuccess = true;
	int l_iTokenOffset = 0;

	if (a_cFile.ReadString (l_csLine))
	{
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csName);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csChance);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csAmount);
	}

	return (l_bSuccess);
}
