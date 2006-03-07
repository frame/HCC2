// WizardInfo.h: interface for the CWizardInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WizardInfo_H__8A46B7E1_C401_4CBD_A135_0FC9219C5BA9__INCLUDED_)
#define AFX_WizardInfo_H__8A46B7E1_C401_4CBD_A135_0FC9219C5BA9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FileHandler.h"

class CWizardInfo  : CFileHandler
{
public:
	bool ReadFromFile(CStdioFile &a_cFile);
	WriteToFile(CStdioFile &a_cFile);
	Destroy();
	Clear();
	CWizardInfo();
	virtual ~CWizardInfo();

	CString m_csFormulaSetName;
	CString m_csDescription;
	CString m_csFilter;
	bool	  m_bPriority;
	bool    m_bOptional;

	CWizardInfo(const CWizardInfo *pSrc);
	operator =( const CWizardInfo* pSrc );
	void CopyObject(const CWizardInfo *pSrc);
};

#endif // !defined(AFX_WizardInfo_H__8A46B7E1_C401_4CBD_A135_0FC9219C5BA9__INCLUDED_)
