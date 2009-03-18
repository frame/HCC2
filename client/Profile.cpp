// Profile.cpp: implementation of the CProfile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Profile.h"
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


CProfile::CProfile()
{
	m_bChanged = false;
}

CProfile::~CProfile()
{
	Destroy ();
}

CProfile::operator =( const CProfile* pSrc )
{
   CopyObject (pSrc);
   return true;
}


CProfile::CProfile(const CProfile *pSrc)
{
   CopyObject (pSrc);
}

void CProfile::CopyObject(const CProfile *pSrc)
{
	CBonus *l_cpBonus;
	CSkill *l_cpSkill;

	m_csProfileName = pSrc->m_csProfileName;
	m_csProfileServer = pSrc->m_csProfileServer;
	m_csProfileEmail = pSrc->m_csProfileEmail;
	m_csProfileType = pSrc->m_csProfileType;
	m_bChanged = pSrc->m_bChanged;

	m_clStatisticList.RemoveAll ();
	POSITION l_Pos = pSrc->m_clStatisticList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpBonus = new CBonus ();
		l_cpBonus->CopyObject (pSrc->m_clStatisticList.GetNext (l_Pos));
		m_clStatisticList.AddTail (l_cpBonus);
	}

	m_clAdventureSkillsList.RemoveAll ();
	l_Pos = pSrc->m_clAdventureSkillsList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpBonus = new CBonus ();
		l_cpBonus->CopyObject (pSrc->m_clAdventureSkillsList.GetNext (l_Pos));
		m_clAdventureSkillsList.AddTail (l_cpBonus);
	}

	m_clAdventureSchoolList.RemoveAll ();
	l_Pos = pSrc->m_clAdventureSchoolList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpSkill = new CSkill ();
		l_cpSkill->CopyObject (pSrc->m_clAdventureSchoolList.GetNext (l_Pos));
		m_clAdventureSchoolList.AddTail (l_cpSkill);
	}

	m_clCraftSkillsList.RemoveAll ();
	l_Pos = pSrc->m_clCraftSkillsList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpBonus = new CBonus ();
		l_cpBonus->CopyObject (pSrc->m_clCraftSkillsList.GetNext (l_Pos));
		m_clCraftSkillsList.AddTail (l_cpBonus);
	}

	m_clCraftSchoolList.RemoveAll ();
	l_Pos = pSrc->m_clCraftSchoolList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpSkill = new CSkill ();
		l_cpSkill->CopyObject (pSrc->m_clCraftSchoolList.GetNext (l_Pos));
		m_clCraftSchoolList.AddTail (l_cpSkill);
	}

}

bool CProfile::LoadFromFile(CString &a_csFilename)
{
	bool l_bResult = true;
	CBonus l_cBonus;
	CBonus *l_cpBonus;
	CSkill *l_cpSkill;
	XMLParser l_cParser;
	XMLTag l_cRootTag ("#ROOT#");
	XMLTag l_cProfileTag ("profile");
	XMLTag l_cStatisticsTag ("statistics");
	XMLTag l_cAdventureLevelsTag ("adventurelevels");
	XMLTag l_cAdventureTag ("adventure");
	XMLTag l_cAdventureSkillsTag ("adventureskills");
	XMLTag l_cCraftLevelsTag ("craftlevels");
	XMLTag l_cCraftTag ("craft");
	XMLTag l_cCraftSkillsTag ("craftskills");
	CString l_csValue;

	l_cParser.OpenFile (a_csFilename);

	// Should be only one Profile Tag
	if (l_cProfileTag.GetNextTag (l_cParser, l_cRootTag))
	{
		m_bChanged = false;
		m_csProfileEmail.Empty ();
		l_cProfileTag.GetTagValue (l_cParser, (CString) "profile-name", m_csProfileName);
		l_cProfileTag.GetTagValue (l_cParser, (CString) "profile-server", m_csProfileServer);
		l_cProfileTag.GetTagValue (l_cParser, (CString) "profile-email", m_csProfileEmail);

		if (l_cStatisticsTag.GetNextTag (l_cParser, l_cProfileTag))
		{
			while (l_cStatisticsTag.GetRepeatingDoubleTagValue (l_cParser, (CString) "statistic", l_csValue, l_cBonus.m_csBonusName ))
			{
				l_cpBonus = new CBonus ();
				l_cpBonus->m_csBonusName = l_cBonus.m_csBonusName ;
				l_cpBonus->m_iValue = atoi (l_csValue);
				m_clStatisticList.AddTail (l_cpBonus);
			}
		}

		if (l_cAdventureLevelsTag.GetNextTag (l_cParser, l_cProfileTag))
		{
			while (l_cAdventureTag.GetNextTag (l_cParser, l_cAdventureLevelsTag))
			{
				l_cpSkill = new CSkill ();
				l_cAdventureTag.GetTagValue (l_cParser, (CString) "adventure-name", l_cpSkill->m_csSkillName);
				l_cAdventureTag.GetTagValue (l_cParser, (CString) "adventure-level", l_cpSkill->m_iSkillValue);
				l_cpSkill->m_iWorkTierMin = 0;
				l_cpSkill->m_iWorkTierMax = 0;
				m_clAdventureSchoolList.AddTail (l_cpSkill);
			}
		}

		if (l_cAdventureSkillsTag.GetNextTag (l_cParser, l_cProfileTag))
		{
			while (l_cAdventureSkillsTag.GetRepeatingDoubleTagValue (l_cParser, (CString) "adventureskill", l_csValue, l_cBonus.m_csBonusName ))
			{
				l_cpBonus = new CBonus ();
				l_cpBonus->m_csBonusName = l_cBonus.m_csBonusName ;
				l_cpBonus->m_iValue = atoi (l_csValue);
				m_clAdventureSkillsList.AddTail (l_cpBonus);
			}
		}

		if (l_cCraftLevelsTag.GetNextTag (l_cParser, l_cProfileTag))
		{
			while (l_cCraftTag.GetNextTag (l_cParser, l_cCraftLevelsTag))
			{
				l_cpSkill = new CSkill ();
				l_cCraftTag.GetTagValue (l_cParser, (CString) "craft-name", l_cpSkill->m_csSkillName);
				l_cCraftTag.GetTagValue (l_cParser, (CString) "craft-level", l_cpSkill->m_iSkillValue);
				l_cCraftTag.GetTagValue (l_cParser, (CString) "craft-worktiermin", l_cpSkill->m_iWorkTierMin);
				l_cCraftTag.GetTagValue (l_cParser, (CString) "craft-worktiermax", l_cpSkill->m_iWorkTierMax);
				m_clCraftSchoolList.AddTail (l_cpSkill);
			}
		}

		if (l_cCraftSkillsTag.GetNextTag (l_cParser, l_cProfileTag))
		{
			while (l_cCraftSkillsTag.GetRepeatingDoubleTagValue (l_cParser, (CString) "craftskill", l_csValue, l_cBonus.m_csBonusName))
			{
				l_cpBonus = new CBonus ();
				l_cpBonus->m_csBonusName = l_cBonus.m_csBonusName ;
				l_cpBonus->m_iValue = atoi (l_csValue);
				m_clCraftSkillsList.AddTail (l_cpBonus);
			}
		}

	}

	return (l_bResult);
}

CProfile::Clear()
{
	m_csProfileName.Empty ();
	m_csProfileServer.Empty ();
	m_csProfileEmail.Empty ();
	m_csProfileType.Empty ();
	m_bChanged = false;
	Destroy ();
}

CProfile::Destroy()
{
	CBonus *l_cpBonus;
	CSkill *l_cpSkill;

	POSITION l_Pos = m_clStatisticList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpBonus = m_clStatisticList.GetNext (l_Pos);
		l_cpBonus->Destroy ();
		delete (l_cpBonus);
	}
	m_clStatisticList.RemoveAll ();

	l_Pos = m_clAdventureSkillsList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpBonus = m_clAdventureSkillsList.GetNext (l_Pos);
		l_cpBonus->Destroy ();
		delete (l_cpBonus);
	}
	m_clAdventureSkillsList.RemoveAll ();

	l_Pos = m_clAdventureSchoolList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpSkill = m_clAdventureSchoolList.GetNext (l_Pos);
		l_cpSkill->Destroy ();
		delete (l_cpSkill);
	}
	m_clAdventureSchoolList.RemoveAll ();

	l_Pos = m_clCraftSkillsList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpBonus = m_clCraftSkillsList.GetNext (l_Pos);
		l_cpBonus->Destroy ();
		delete (l_cpBonus);
	}
	m_clCraftSkillsList.RemoveAll ();

	l_Pos = m_clCraftSchoolList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpSkill = m_clCraftSchoolList.GetNext (l_Pos);
		l_cpSkill->Destroy ();
		delete (l_cpSkill);
	}
	m_clCraftSchoolList.RemoveAll ();
}

int CProfile::FindCraftSkill(CString &a_csCraft)
{
	CBonus *l_cpBonus;
	POSITION l_Pos;

	l_Pos = m_clCraftSkillsList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpBonus = m_clCraftSkillsList.GetNext (l_Pos);
		if (l_cpBonus->m_csBonusName == a_csCraft)
		{
			return (l_cpBonus->m_iValue);
		}
	}

	return (0);
}

bool CProfile::UpdateStatistic(CString &a_csStatistic, int a_iValue)
{
	CBonus *l_cpBonus;
	POSITION l_Pos;

	if ((a_iValue >= 0) && (a_iValue <= 5000))
	{
		l_Pos = m_clStatisticList.GetHeadPosition ();
		while (l_Pos)
		{
			l_cpBonus = m_clStatisticList.GetNext (l_Pos);
			if ((l_cpBonus->m_csBonusName == a_csStatistic) &&
				 (m_csProfileType != cAppData_Profile_Defaults))
			{
				l_cpBonus->m_iValue = a_iValue;
				m_bChanged = true;
				return (true);
			}
		}
	}

	return (false);
}

bool CProfile::UpdateCraftSkill(CString &a_csCraft, int a_iValue)
{
	CBonus *l_cpBonus;
	POSITION l_Pos;

	if ((a_iValue >= 0) && (a_iValue <= 3000))
	{
		l_Pos = m_clCraftSkillsList.GetHeadPosition ();
		while (l_Pos)
		{
			l_cpBonus = m_clCraftSkillsList.GetNext (l_Pos);
			if ((l_cpBonus->m_csBonusName == a_csCraft) &&
				 (m_csProfileType != cAppData_Profile_Defaults))
			{
				l_cpBonus->m_iValue = a_iValue;
				m_bChanged = true;
				return (true);
			}
		}
	}
	return (false);
}

bool CProfile::UpdateCraftSchool(CString &a_csCraftSchool, int a_iValue)
{
	CSkill *l_cpSkill;
	POSITION l_Pos;

	if ((a_iValue >= 0) && (a_iValue <= 200))
	{
		l_Pos = m_clCraftSchoolList.GetHeadPosition ();
		while (l_Pos)
		{
			l_cpSkill = m_clCraftSchoolList.GetNext (l_Pos);
			if ((l_cpSkill->m_csSkillName == a_csCraftSchool) &&
				 (m_csProfileType != cAppData_Profile_Defaults))
			{
				l_cpSkill->m_iSkillValue = a_iValue;
				m_bChanged = true;
				return (true);
			}
		}
	}
	return (false);
}

bool CProfile::SaveProfile(CString &a_csFilename)
{
	POSITION l_cPos;
	CBonus *l_cpBonus;
	CSkill *l_cpSkill;
	XMLParser l_cParser;
	CString l_csStr;
	bool l_bResult = false;

	if (l_cParser.WriteFile (a_csFilename))
	{
		l_cParser.WriteOpenTag ("profile");
		l_cParser.WriteTag ("profile-format", "1.1");
		l_cParser.WriteTag ("profile-name", m_csProfileName);
		l_cParser.WriteTag ("profile-server", m_csProfileServer);
		l_cParser.WriteTag ("profile-email", m_csProfileEmail);

		l_cParser.WriteOpenTag ("statistics");
		l_cPos = m_clStatisticList.GetHeadPosition ();
		while (l_cPos)
		{
			l_cpBonus = m_clStatisticList.GetNext (l_cPos);
			l_csStr.Format ("value=\"%d\"", l_cpBonus->m_iValue);
			l_cParser.WriteAttributeTag ("statistic", l_csStr, l_cpBonus->m_csBonusName);
		}
		l_cParser.WriteCloseTag ("statistics");

		l_cParser.WriteOpenTag ("adventurelevels");
		l_cPos = m_clAdventureSchoolList.GetHeadPosition ();
		while (l_cPos)
		{
			l_cParser.WriteOpenTag ("adventure");
			l_cpSkill = m_clAdventureSchoolList.GetNext (l_cPos);
			l_cParser.WriteTag ("adventure-name", l_cpSkill->m_csSkillName);
			l_cParser.WriteTag ("adventure-level", l_cpSkill->m_iSkillValue);
			l_cParser.WriteCloseTag ("adventure");
		}
		l_cParser.WriteCloseTag ("adventurelevels");

		l_cParser.WriteOpenTag ("adventureskills");
		l_cPos = m_clAdventureSkillsList.GetHeadPosition ();
		while (l_cPos)
		{
			l_cpBonus = m_clAdventureSkillsList.GetNext (l_cPos);
			l_csStr.Format ("level=\"%d\"", l_cpBonus->m_iValue);
			l_cParser.WriteAttributeTag ("adventureskill", l_csStr, l_cpBonus->m_csBonusName);
		}
		l_cParser.WriteCloseTag ("adventureskills");

		l_cParser.WriteOpenTag ("craftlevels");
		l_cPos = m_clCraftSchoolList.GetHeadPosition ();
		while (l_cPos)
		{
			l_cParser.WriteOpenTag ("craft");
			l_cpSkill = m_clCraftSchoolList.GetNext (l_cPos);
			l_cParser.WriteTag ("craft-name", l_cpSkill->m_csSkillName);
			l_cParser.WriteTag ("craft-level", l_cpSkill->m_iSkillValue);
			l_cParser.WriteTag ("craft-worktiermin", l_cpSkill->m_iWorkTierMin);
			l_cParser.WriteTag ("craft-worktiermax", l_cpSkill->m_iWorkTierMax);
			l_cParser.WriteCloseTag ("craft");
		}
		l_cParser.WriteCloseTag ("craftlevels");

		l_cParser.WriteOpenTag ("craftskills");
		l_cPos = m_clCraftSkillsList.GetHeadPosition ();
		while (l_cPos)
		{
			l_cpBonus = m_clCraftSkillsList.GetNext (l_cPos);
			l_csStr.Format ("level=\"%d\"", l_cpBonus->m_iValue);
			l_cParser.WriteAttributeTag ("craftskill", l_csStr, l_cpBonus->m_csBonusName);
		}
		l_cParser.WriteCloseTag ("craftskills");

		l_cParser.WriteCloseTag ("profile");

		l_cParser.CloseFile ();

		m_bChanged = false;
		l_bResult = true;
	}

	return (l_bResult);
}
