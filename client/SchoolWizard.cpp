// SchoolWizard.cpp: implementation of the CSchoolWizard class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HCC.h"
#include "SchoolWizard.h"
#include "XMLParser.h"
#include "XMLTag.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSchoolWizard::CSchoolWizard()
{

}

CSchoolWizard::~CSchoolWizard()
{
	Destroy();
}

bool CSchoolWizard::LoadFromFile(CString &a_csFilename)
{
	bool l_bResult = true;
	XMLParser l_cParser;
	XMLTag l_cRootTag ("#ROOT#");
	XMLTag l_cWizardTag ("wizard");
	XMLTag l_cRacesTag ("races");
	XMLTag l_cSlotsTag ("slots");
	XMLTag l_cFormulaSetsTag ("formulasets");
	XMLTag l_cFormulaSetTag ("formulaset");
	XMLTag l_cTechsTag ("techs");
	CString l_csValue;
	CString l_csAttribute;
	CWizardInfo		*l_cpWizardInfo = NULL;
	CString l_csPriority;
	CString l_csOptional;

	l_cParser.OpenFile (a_csFilename);

	// Should be only one wizard Tag
	if (l_cWizardTag.GetNextTag (l_cParser, l_cRootTag))
	{
		l_cWizardTag.GetTagValue (l_cParser, (CString) "wizard-school", m_cSchoolName);
		l_cWizardTag.GetTagValue (l_cParser, (CString) "wizard-type", m_cSchoolType);
		l_cWizardTag.GetTagValue (l_cParser, (CString) "wizard-version", m_iVersion);

		if (l_cRacesTag.GetNextTag (l_cParser, l_cWizardTag))
		{
			while (l_cRacesTag.GetRepeatingTagValue (l_cParser, (CString) "race", l_csValue))
			{
				m_clRaceList.AddTail (l_csValue);
			}
		}

		if (l_cSlotsTag.GetNextTag (l_cParser, l_cWizardTag))
		{
			while (l_cSlotsTag.GetRepeatingTagValue (l_cParser, (CString) "slot", l_csValue))
			{
				m_clSlotList.AddTail (l_csValue);
			}
		}

		if (l_cFormulaSetsTag.GetNextTag (l_cParser, l_cWizardTag))
		{
			while (l_cFormulaSetTag.GetNextTag (l_cParser, l_cFormulaSetsTag))
			{
				l_cpWizardInfo = new CWizardInfo ();
				l_cFormulaSetTag.GetTagValue (l_cParser, (CString) "formulaset-name", l_cpWizardInfo->m_csFormulaSetName);
				l_cFormulaSetTag.GetTagValue (l_cParser, (CString) "formulaset-desc", l_cpWizardInfo->m_csDescription);
				l_cFormulaSetTag.GetTagValue (l_cParser, (CString) "formulaset-filter", l_cpWizardInfo->m_csFilter);
				l_cFormulaSetTag.GetTagValue (l_cParser, (CString) "formulaset-priority", l_csPriority);
				l_cFormulaSetTag.GetTagValue (l_cParser, (CString) "formulaset-optional", l_csOptional);
				l_cpWizardInfo->m_bPriority = (l_csPriority == "Y");
				l_cpWizardInfo->m_bOptional = (l_csOptional == "Y");

				m_clFormulaSetList.AddTail (l_cpWizardInfo);
			}
		}

		if (l_cTechsTag.GetNextTag (l_cParser, l_cWizardTag))
		{
			while (l_cTechsTag.GetRepeatingTagValue (l_cParser, (CString) "tech", l_csValue))
			{
				m_clTechList.AddTail (l_csValue);
			}
		}

	}

	return (l_bResult);
}


CSchoolWizard::Destroy()
{
	CWizardInfo *l_cpWizardInfo;

	POSITION l_Pos = m_clFormulaSetList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpWizardInfo = m_clFormulaSetList.GetNext (l_Pos);
		l_cpWizardInfo->Destroy ();
		delete (l_cpWizardInfo);
	}
	m_clFormulaSetList.RemoveAll ();

}

CSchoolWizard::WriteToFile(CStdioFile &a_cFile)
{
	CString l_csLine;

	l_csLine.Format ("%s|%s|%d|%d|%d|%d|%d\n", m_cSchoolName, m_cSchoolType, m_iVersion,
						  m_clRaceList.GetCount(), m_clSlotList.GetCount(), m_clFormulaSetList.GetCount(),
						  m_clTechList.GetCount());
	a_cFile.WriteString (l_csLine);

	POSITION l_Pos = m_clRaceList.GetHeadPosition ();
	while (l_Pos)
	{
		a_cFile.WriteString (m_clRaceList.GetNext (l_Pos) + "\n");
	}

	l_Pos = m_clSlotList.GetHeadPosition ();
	while (l_Pos)
	{
		a_cFile.WriteString (m_clSlotList.GetNext (l_Pos) + "\n");
	}

	l_Pos = m_clFormulaSetList.GetHeadPosition ();
	while (l_Pos)
	{
		m_clFormulaSetList.GetNext (l_Pos)->WriteToFile (a_cFile);
	}

	l_Pos = m_clTechList.GetHeadPosition ();
	while (l_Pos)
	{
		a_cFile.WriteString (m_clTechList.GetNext (l_Pos) + "\n");
	}

}

bool CSchoolWizard::ReadFromFile(CStdioFile &a_cFile)
{
	CString l_csLine;
	bool l_bSuccess = true;
	int l_iTokenOffset = 0;
	int l_iRaceCount = 0;
	int l_iSlotCount = 0;
	int l_iFormulaSetCount = 0;
	int l_iTechCount = 0;
	CWizardInfo *l_cpWizardInfo;

	if (a_cFile.ReadString (l_csLine))
	{
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_cSchoolName);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_cSchoolType);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_iVersion);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, l_iRaceCount);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, l_iSlotCount);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, l_iFormulaSetCount);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, l_iTechCount);

		if (l_bSuccess)
		{
			while (l_iRaceCount--)
			{
				l_bSuccess = l_bSuccess && a_cFile.ReadString (l_csLine);
				m_clRaceList.AddTail (l_csLine);
			}
		}
	
		if (l_bSuccess)
		{
			while (l_iSlotCount--)
			{
				l_bSuccess = l_bSuccess && a_cFile.ReadString (l_csLine);
				m_clSlotList.AddTail (l_csLine);
			}
		}
	
		if (l_bSuccess)
		{
			while (l_iFormulaSetCount--)
			{
				l_cpWizardInfo = new CWizardInfo ();
				l_bSuccess = l_bSuccess && l_cpWizardInfo->ReadFromFile (a_cFile);
				m_clFormulaSetList.AddTail (l_cpWizardInfo);
			}
		}
	
		if (l_bSuccess)
		{
			while (l_iTechCount--)
			{
				l_bSuccess = l_bSuccess && a_cFile.ReadString (l_csLine);
				m_clTechList.AddTail (l_csLine);
			}
		}
	}
	
	return (l_bSuccess);
}
