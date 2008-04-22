// DatabaseRelease.cpp: implementation of the CDatabaseRelease class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DatabaseRelease.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDatabaseRelease::CDatabaseRelease()
{
}

CDatabaseRelease::~CDatabaseRelease()
{
	m_clNoteList.RemoveAll ();
}

CDatabaseRelease::operator =( const CDatabaseRelease& pSrc )
{
   CopyObject (pSrc);
   return true;
}


CDatabaseRelease::CDatabaseRelease(const CDatabaseRelease &pSrc)
{
   CopyObject (pSrc);
}

void CDatabaseRelease::CopyObject(const CDatabaseRelease &pSrc)
{
	m_ctRevision = pSrc.m_ctRevision;
	m_csTitle = pSrc.m_csTitle;
	m_csMinClientVersion = pSrc.m_csMinClientVersion;

	m_clNoteList.RemoveAll ();
	POSITION l_Pos = pSrc.m_clNoteList.GetHeadPosition ();
	while (l_Pos)
	{
		m_clNoteList.AddTail (pSrc.m_clNoteList.GetNext (l_Pos));
	}

}


