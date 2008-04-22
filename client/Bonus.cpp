// Bonus.cpp: implementation of the CBonus class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Bonus.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBonus::CBonus()
{

}

CBonus::~CBonus()
{

}

CBonus::operator =( const CBonus* pSrc )
{
   CopyObject (pSrc);
   return true;
}


CBonus::CBonus(const CBonus *pSrc)
{
   CopyObject (pSrc);
}

void CBonus::CopyObject(const CBonus *pSrc)
{
	m_csBonusName = pSrc->m_csBonusName;
	m_iValue	  = pSrc->m_iValue;
}

CBonus::Clear()
{
	m_csBonusName.Empty ();
	m_iValue = 0;
}

CBonus::Destroy()
{

}

CBonus::WriteToFile(CStdioFile &a_cFile)
{
	CString l_csLine;

	l_csLine.Format ("%s|%d\n", m_csBonusName, m_iValue);
	a_cFile.WriteString (l_csLine);
}

bool CBonus::ReadFromFile(CStdioFile &a_cFile)
{
	CString l_csLine;
	bool l_bSuccess = true;
	int l_iTokenOffset = 0;

	if (a_cFile.ReadString (l_csLine))
	{
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csBonusName);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_iValue);
	}

	return (l_bSuccess);
}
