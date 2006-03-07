// SchoolWizard.h: interface for the CSchoolWizard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCHOOLWIZARD_H__4D317431_0B07_4FF9_86F8_30254652EC40__INCLUDED_)
#define AFX_SCHOOLWIZARD_H__4D317431_0B07_4FF9_86F8_30254652EC40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FileHandler.h"
#include "WizardInfo.h"

class CSchoolWizard : CFileHandler
{
public:
	Destroy();
	CSchoolWizard();
	virtual ~CSchoolWizard();

	bool LoadFromFile(CString &a_csFilename);
	WriteToFile(CStdioFile &a_cFile);
	bool ReadFromFile(CStdioFile &a_cFile);

	CString m_cSchoolName;
	CString m_cSchoolType;
	int	  m_iVersion;

	CStringList m_clRaceList;
	CStringList m_clSlotList;
	CStringList m_clTechList;
	CTypedPtrList<CPtrList, CWizardInfo*> m_clFormulaSetList;
};

#endif // !defined(AFX_SCHOOLWIZARD_H__4D317431_0B07_4FF9_86F8_30254652EC40__INCLUDED_)
