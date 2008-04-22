// WizardInfo.cpp: implementation of the CWizardInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WizardInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWizardInfo::CWizardInfo()
{

}

CWizardInfo::~CWizardInfo()
{

}

CWizardInfo::operator =( const CWizardInfo* pSrc )
{
   CopyObject (pSrc);
   return true;
}


CWizardInfo::CWizardInfo(const CWizardInfo *pSrc)
{
   CopyObject (pSrc);
}

void CWizardInfo::CopyObject(const CWizardInfo *pSrc)
{
	m_csFormulaSetName	= pSrc->m_csFormulaSetName;
	m_csDescription	= pSrc->m_csDescription;
	m_csFilter	= pSrc->m_csFilter;
	m_bPriority	= pSrc->m_bPriority;
	m_bOptional	= pSrc->m_bOptional;
}

CWizardInfo::Clear()
{
	m_csFormulaSetName.Empty ();
	m_csDescription.Empty ();
	m_csFilter.Empty ();
	m_bPriority = false;
	m_bOptional = false;
}

CWizardInfo::Destroy()
{

}

CWizardInfo::WriteToFile(CStdioFile &a_cFile)
{
	CString l_csLine;
	CString l_csPriority;
	CString l_csOptional;

	if (m_bPriority)
	{
		l_csPriority = "Y";
	}
	else
	{
		l_csPriority = "N";
	}

	if (m_bOptional)
	{
		l_csOptional = "Y";
	}
	else
	{
		l_csOptional = "N";
	}

	l_csLine.Format ("%s|%s|%s|%s|%s\n", m_csFormulaSetName, m_csDescription, m_csFilter, l_csPriority, l_csOptional);
	a_cFile.WriteString (l_csLine);
}

bool CWizardInfo::ReadFromFile(CStdioFile &a_cFile)
{
	CString l_csLine;
	CString l_csPriority;
	CString l_csOptional;
	bool l_bSuccess = true;
	int l_iTokenOffset = 0;

	if (a_cFile.ReadString (l_csLine))
	{
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csFormulaSetName);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csDescription);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csFilter);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, l_csPriority);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, l_csOptional);

		m_bPriority = (l_csPriority == "Y");
		m_bOptional = (l_csOptional == "Y");
	}

	return (l_bSuccess);
}

