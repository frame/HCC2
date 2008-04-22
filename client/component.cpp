// Component.cpp: implementation of the CComponent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HCC.h"
#include "Component.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComponent::CComponent()
{

}

CComponent::~CComponent()
{

}

CComponent::operator =( const CComponent* pSrc )
{
   CopyObject (pSrc);
   return true;
}


CComponent::CComponent(const CComponent *pSrc)
{
   CopyObject (pSrc);
}

void CComponent::CopyObject(const CComponent *pSrc)
{
	m_csComponentName = pSrc->m_csComponentName;
	m_csDescription = pSrc->m_csDescription;
	m_csType = pSrc->m_csType;
	m_iTier = pSrc->m_iTier;
	m_iBulk = pSrc->m_iBulk;
	m_csPawnBuyPrice = pSrc->m_csPawnBuyPrice;
	m_csPawnSellPrice = pSrc->m_csPawnSellPrice;
	m_csVieloSellPrice = pSrc->m_csVieloSellPrice;

	m_csLocations.RemoveAll ();
	POSITION l_Pos = pSrc->m_csLocations.GetHeadPosition ();
	while (l_Pos)
	{
		m_csLocations.AddTail (pSrc->m_csLocations.GetNext (l_Pos));
	}
}

CComponent::Destroy()
{
	CCompGatherInfo *l_cpCompGatherInfo;

	POSITION l_Pos = m_clCompGatherInfoList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpCompGatherInfo = m_clCompGatherInfoList.GetNext (l_Pos);
		l_cpCompGatherInfo->Destroy ();
		delete (l_cpCompGatherInfo);
	}
}

CComponent::WriteToFile(CStdioFile &a_cFile)
{
	CCompGatherInfo *l_cpCompGatherInfo;
	CString l_csLine;

	l_csLine.Format ("%s|%s|%s|%d|%d|%s|%s|%s|%d|%d\n", 	m_csComponentName,
																		m_csDescription,
																		m_csType,
																		m_iTier,
																		m_iBulk,
																		m_csPawnBuyPrice,
																		m_csPawnSellPrice,
																		m_csVieloSellPrice,
																		m_clCompGatherInfoList.GetCount(),
																		m_csLocations.GetCount());
	a_cFile.WriteString (l_csLine);

	POSITION l_Pos = m_clCompGatherInfoList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpCompGatherInfo = m_clCompGatherInfoList.GetNext (l_Pos);
		l_cpCompGatherInfo->WriteToFile (a_cFile);
	}

	l_Pos = m_csLocations.GetHeadPosition ();
	while (l_Pos)
	{
		a_cFile.WriteString (m_csLocations.GetNext (l_Pos) + "\n");
	}

}

bool CComponent::ReadFromFile(CStdioFile &a_cFile)
{
	CCompGatherInfo *l_cpCompGatherInfo;
	CString l_csLine;
	bool l_bSuccess = true;
	int l_iTokenOffset = 0;
	int l_iGatherCount = 0;
	int l_iLocCount = 0;

	if (a_cFile.ReadString (l_csLine))
	{
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csComponentName);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csDescription);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csType);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_iTier);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_iBulk);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csPawnBuyPrice);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csPawnSellPrice);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csVieloSellPrice);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, l_iGatherCount);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, l_iLocCount);

		if (l_bSuccess)
		{
			while (l_iGatherCount--)
			{
				l_cpCompGatherInfo = new CCompGatherInfo();
				l_bSuccess = l_bSuccess && l_cpCompGatherInfo->ReadFromFile (a_cFile);
				m_clCompGatherInfoList.AddTail (l_cpCompGatherInfo);
			}

			while (l_iLocCount--)
			{
				l_bSuccess = l_bSuccess && a_cFile.ReadString (l_csLine);
				m_csLocations.AddTail (l_csLine);
			}
		}
	}

	return (l_bSuccess);
}
