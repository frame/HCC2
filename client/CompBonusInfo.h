// CompBonusInfo.h: interface for the CCompBonusInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CompBonusInfo_H__550FA1D0_F9F0_4D34_9660_7584C305C6BD__INCLUDED_)
#define AFX_CompBonusInfo_H__550FA1D0_F9F0_4D34_9660_7584C305C6BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include "FileHandler.h"

class CCompBonusInfo : CFileHandler
{
public:
	Destroy();
	Clear();
	CCompBonusInfo();
	virtual ~CCompBonusInfo();

	CString  m_csName;
	CString	m_csAmount;
	CString	m_csChance;

	CCompBonusInfo(const CCompBonusInfo *pSrc);
	operator =( const CCompBonusInfo* pSrc );
	void CopyObject(const CCompBonusInfo *pSrc);

	bool ReadFromFile(CStdioFile &a_cFile);
	WriteToFile(CStdioFile &a_cFile);
};

#endif // !defined(AFX_CompBonusInfo_H__550FA1D0_F9F0_4D34_9660_7584C305C6BD__INCLUDED_)
