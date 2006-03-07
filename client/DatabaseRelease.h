// DatabaseRelease.h: interface for the CDatabaseRelease class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DatabaseRelease_H__31A4AE90_5A5E_452B_AFF3_B15737F5C9AA__INCLUDED_)
#define AFX_DatabaseRelease_H__31A4AE90_5A5E_452B_AFF3_B15737F5C9AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDatabaseRelease  
{
public:
	CDatabaseRelease();
	virtual ~CDatabaseRelease();
	operator =( const CDatabaseRelease& pSrc );
	CDatabaseRelease(const CDatabaseRelease &pSrc);
	void CopyObject(const CDatabaseRelease &pSrc);

	CTime	  m_ctRevision;
	CString m_csTitle;
	CString m_csMinClientVersion;

	CStringList m_clNoteList;

};

#endif // !defined(AFX_DatabaseRelease_H__31A4AE90_5A5E_452B_AFF3_B15737F5C9AA__INCLUDED_)
