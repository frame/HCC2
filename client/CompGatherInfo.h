// CompGatherInfo.h: interface for the CCompGatherInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CompGatherInfo_H__550FA1D0_F9F0_4D34_9660_7584C305C6BD__INCLUDED_)
#define AFX_CompGatherInfo_H__550FA1D0_F9F0_4D34_9660_7584C305C6BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include "FileHandler.h"
#include "CompBonusInfo.h"

class CCompGatherInfo : CFileHandler
{
public:
	Destroy();
	Clear();
	CCompGatherInfo();
	virtual ~CCompGatherInfo();

	CString  m_csTool;
	CString  m_csSkill;
	CString	m_csRate;
	CString	m_csMinLvl;
	CString	m_csOptLvl;

	CTypedPtrList<CPtrList, CCompBonusInfo*>	m_clCompBonusInfoList;

	CCompGatherInfo(const CCompGatherInfo *pSrc);
	operator =( const CCompGatherInfo* pSrc );
	void CopyObject(const CCompGatherInfo *pSrc);

	bool ReadFromFile(CStdioFile &a_cFile);
	WriteToFile(CStdioFile &a_cFile);
};

#endif // !defined(AFX_CompGatherInfo_H__550FA1D0_F9F0_4D34_9660_7584C305C6BD__INCLUDED_)
