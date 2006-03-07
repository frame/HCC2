// TechSet.h: interface for the CTechSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TechSET_H__2A3326E1_87A1_47DB_AC38_9BC5E93D571F__INCLUDED_)
#define AFX_TechSET_H__2A3326E1_87A1_47DB_AC38_9BC5E93D571F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Tech.h"
#include "FileHandler.h"

class CTechSet: CFileHandler
{
public:
	bool ReadFromFile(CStdioFile &a_cFile);
	WriteToFile(CStdioFile &a_cFile);
	Destroy(bool a_bAll = true);
	AddSet(CTechSet *a_cTechSet);
	bool LoadTechSet (CString a_csFilename);
	CTechSet();
	virtual ~CTechSet();

	operator =( const CTechSet* pSrc );
	CTechSet(const CTechSet *pSrc);
	void CopyObject(const CTechSet *pSrc);

	CString m_csName;
	CString m_csCategory;
	CString m_csFormat;
	int	  m_iIcon;

	CTypedPtrList<CPtrList, CTech*>	m_clTechList;
};

#endif // !defined(AFX_TechSET_H__2A3326E1_87A1_47DB_AC38_9BC5E93D571F__INCLUDED_)
