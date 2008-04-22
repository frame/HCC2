// KeywordGroup.cpp: implementation of the CKeywordGroup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "KeywordGroup.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKeywordGroup::CKeywordGroup()
{

}

CKeywordGroup::~CKeywordGroup()
{

}

CKeywordGroup::operator =( const CKeywordGroup* pSrc )
{
   CopyObject (pSrc);
   return true;
}


CKeywordGroup::CKeywordGroup(const CKeywordGroup *pSrc)
{
   CopyObject (pSrc);
}

void CKeywordGroup::CopyObject(const CKeywordGroup *pSrc)
{
	m_clKeywordList.RemoveAll ();

	POSITION l_Pos = pSrc->m_clKeywordList.GetHeadPosition ();
	while (l_Pos)
	{
		m_clKeywordList.AddTail (pSrc->m_clKeywordList.GetNext (l_Pos));
	}
}

CKeywordGroup::Clear()
{
	m_clKeywordList.RemoveAll ();
}

CKeywordGroup::Destroy()
{
	Clear();
}

CKeywordGroup::WriteToFile(CStdioFile &a_cFile)
{
	CString l_csLine;
	POSITION l_Pos;

	l_csLine.Format ("%d\n", m_clKeywordList.GetCount ());
	a_cFile.WriteString (l_csLine);

	l_Pos = m_clKeywordList.GetHeadPosition ();
	while (l_Pos)
	{
		a_cFile.WriteString (m_clKeywordList.GetNext (l_Pos)+ "\n");
	}
}

bool CKeywordGroup::ReadFromFile(CStdioFile &a_cFile)
{
	CString l_csLine;
	bool l_bSuccess = true;
	int l_iTokenOffset = 0;
	int l_iCount;

	m_clKeywordList.RemoveAll ();
	if (a_cFile.ReadString (l_csLine))
	{
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, l_iCount);

		if (l_bSuccess)
		{
			while (l_iCount--)
			{
				l_bSuccess = l_bSuccess && a_cFile.ReadString (l_csLine);
				m_clKeywordList.AddTail (l_csLine);
			}
		}
	}

	return (l_bSuccess);
}

bool CKeywordGroup::Match(CKeywordGroup *a_pKeywordGroup)
{
	POSITION l_LocalPos;
	POSITION l_RemotePos;
	CString  l_csLocalKeyword;

	l_LocalPos = m_clKeywordList.GetHeadPosition ();
	while (l_LocalPos)
	{
		l_csLocalKeyword = m_clKeywordList.GetNext (l_LocalPos);

		l_RemotePos = a_pKeywordGroup->m_clKeywordList.GetHeadPosition ();
		while (l_RemotePos)
		{
			if (l_csLocalKeyword == a_pKeywordGroup->m_clKeywordList.GetNext (l_RemotePos))
			{
				return (true);
			}
		}
	}
	return (false);
}
