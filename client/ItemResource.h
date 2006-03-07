// ItemResource.h: interface for the CItemResource class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITEMRESOURCE_H__550FA1D0_F9F0_4D34_9660_7584C305C6BD__INCLUDED_)
#define AFX_ITEMRESOURCE_H__550FA1D0_F9F0_4D34_9660_7584C305C6BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include "bonus.h"
#include "FileHandler.h"

class CItemResource  : CFileHandler
{
public:
	bool ReadFromFile(CStdioFile &a_cFile);
	WriteToFile(CStdioFile &a_cFile);
	Destroy();
	int DetermineSkillForAmount (int a_iAmount);
	Clear();
	CItemResource();
	virtual ~CItemResource();

	CString m_csName;
	CString m_csSkill;
	int		m_iUnits;
	int		m_iMinLvl;
	int		m_iMinAmt;
	int		m_iOptLvl;
	int		m_iOptAmt;

	CItemResource(const CItemResource *pSrc);
	operator =( const CItemResource* pSrc );
	void CopyObject(const CItemResource *pSrc);

};

#endif // !defined(AFX_ITEMRESOURCE_H__550FA1D0_F9F0_4D34_9660_7584C305C6BD__INCLUDED_)
