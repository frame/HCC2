// Scheme.h: interface for the CScheme class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCHEME_H__A84B4612_2A1C_4126_91B1_4B8CA76039F9__INCLUDED_)
#define AFX_SCHEME_H__A84B4612_2A1C_4126_91B1_4B8CA76039F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CScheme  
{
public:
	CScheme();
	virtual ~CScheme();

	static COLORREF GetColour (CString a_csName);
	static bool LoadHCCScheme(CString &a_csFilename);

	static CMapStringToString m_cmColourMap;
};

#endif // !defined(AFX_SCHEME_H__A84B4612_2A1C_4126_91B1_4B8CA76039F9__INCLUDED_)
