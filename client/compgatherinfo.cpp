// Item.cpp: implementation of the CCompGatherInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CompGatherInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCompGatherInfo::CCompGatherInfo()
{
	Clear();
}

CCompGatherInfo::~CCompGatherInfo()
{

}

CCompGatherInfo::operator =( const CCompGatherInfo* pSrc )
{
   CopyObject (pSrc);
   return true;
}


CCompGatherInfo::CCompGatherInfo(const CCompGatherInfo *pSrc)
{
   CopyObject (pSrc);
}

void CCompGatherInfo::CopyObject(const CCompGatherInfo *pSrc)
{
	m_csTool = pSrc->m_csSkill;
	m_csSkill = pSrc->m_csTool;
	m_csRate = pSrc->m_csRate;
	m_csMinLvl = pSrc->m_csMinLvl;
	m_csOptLvl = pSrc->m_csOptLvl;

}

CCompGatherInfo::Clear()
{
	m_csTool.Empty ();
	m_csSkill.Empty ();
	m_csRate.Empty ();
	m_csMinLvl.Empty ();
	m_csOptLvl.Empty ();
}

CCompGatherInfo::Destroy()
{
	CCompBonusInfo *l_cpCompBonusInfo;

	POSITION l_Pos = m_clCompBonusInfoList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpCompBonusInfo = m_clCompBonusInfoList.GetNext (l_Pos);
		l_cpCompBonusInfo->Destroy ();
		delete (l_cpCompBonusInfo);
	}
}

CCompGatherInfo::WriteToFile(CStdioFile &a_cFile)
{
	CString l_csLine;
	CCompBonusInfo *l_cpCompBonusInfo;

	l_csLine.Format ("%s|%s|%s|%s|%s|%d\n", 	m_csTool,
															m_csSkill,
															m_csRate,
															m_csMinLvl,
															m_csOptLvl,
															m_clCompBonusInfoList.GetCount());
	a_cFile.WriteString (l_csLine);

	POSITION l_Pos = m_clCompBonusInfoList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpCompBonusInfo = m_clCompBonusInfoList.GetNext (l_Pos);
		l_cpCompBonusInfo->WriteToFile (a_cFile);
	}

}

bool CCompGatherInfo::ReadFromFile(CStdioFile &a_cFile)
{
	CString l_csLine;
	CCompBonusInfo *l_cpCompBonusInfo;
	bool l_bSuccess = true;
	int l_iTokenOffset = 0;
	int l_iBonusCount = 0;

	if (a_cFile.ReadString (l_csLine))
	{
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csTool);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csSkill);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csRate);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csMinLvl);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csOptLvl);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, l_iBonusCount);

		if (l_bSuccess)
		{
			while (l_iBonusCount--)
			{
				l_cpCompBonusInfo = new CCompBonusInfo();
				l_bSuccess = l_bSuccess && l_cpCompBonusInfo->ReadFromFile (a_cFile);
				m_clCompBonusInfoList.AddTail (l_cpCompBonusInfo);
			}
		}
	}

	return (l_bSuccess);
}
