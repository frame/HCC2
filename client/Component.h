// Component.h: interface for the CComponent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPONENT_H__92A31C87_FF55_44D6_9C2A_214565E0D793__INCLUDED_)
#define AFX_COMPONENT_H__92A31C87_FF55_44D6_9C2A_214565E0D793__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FileHandler.h"
#include "CompGatherInfo.h"

class CComponent : CFileHandler
{
public:
	bool ReadFromFile(CStdioFile &a_cFile);
	WriteToFile(CStdioFile &a_cFile);
	Destroy();
	CComponent();
	virtual ~CComponent();

	CComponent(const CComponent *pSrc);
	operator =( const CComponent* pSrc );
	void CopyObject(const CComponent *pSrc);

	CString m_csComponentName;
	CString m_csDescription;
	CString m_csType;
	int	  m_iTier;
	int     m_iBulk;
	CString m_csPawnBuyPrice;
	CString m_csPawnSellPrice;
	CString m_csVieloSellPrice;

	CTypedPtrList<CPtrList, CCompGatherInfo*>	m_clCompGatherInfoList;
	CStringList m_csLocations;
};

#endif // !defined(AFX_COMPONENT_H__92A31C87_FF55_44D6_9C2A_214565E0D793__INCLUDED_)
