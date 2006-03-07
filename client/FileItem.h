// FileItem.h: interface for the CFileItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEITEM_H__612EB2F2_4FF0_422A_B801_6EAA1D4C58C2__INCLUDED_)
#define AFX_FILEITEM_H__612EB2F2_4FF0_422A_B801_6EAA1D4C58C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define FileItem_Waiting 0
#define FileItem_Downloaded 1
#define FileItem_Failed 2
#define FileItem_Retry 3

class CFileItem  
{
public:
	CFileItem();
	virtual ~CFileItem();

	CString m_csFile;
	CString m_csSaveName;
	DWORD   m_iSize;
	int	  m_iResult;
};

#endif // !defined(AFX_FILEITEM_H__612EB2F2_4FF0_422A_B801_6EAA1D4C58C2__INCLUDED_)
