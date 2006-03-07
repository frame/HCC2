// FileHandler.h: interface for the CFileHandler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEHANDLER_H__4C9959D3_0B4C_4A16_B78D_1163D95DB9D4__INCLUDED_)
#define AFX_FILEHANDLER_H__4C9959D3_0B4C_4A16_B78D_1163D95DB9D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFileHandler  
{
public:
	bool StrToBool (CString &a_csValue);
	CString BoolToStr (bool a_bValue);
	CFileHandler();
	virtual ~CFileHandler();

	bool ReadToken (CString &a_csLine, int &a_iOffset, CString &a_cResult);
	bool ReadToken (CString &a_csLine, int &a_iOffset, int &a_iResult);
};

#endif // !defined(AFX_FILEHANDLER_H__4C9959D3_0B4C_4A16_B78D_1163D95DB9D4__INCLUDED_)
