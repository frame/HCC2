// Profile.h: interface for the CProfile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROFILE_H__DC567DBA_3C0D_455B_8B12_7FB8E44A7D1E__INCLUDED_)
#define AFX_PROFILE_H__DC567DBA_3C0D_455B_8B12_7FB8E44A7D1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Bonus.h"
#include "Skill.h"

class CProfile  
{
public:
	bool SaveProfile (CString &a_csFilename);
	bool UpdateStatistic(CString &a_csStatistic, int a_iValue);
	bool UpdateCraftSchool(CString &a_csCraftSchool, int a_iValue);
	bool UpdateCraftSkill (CString &a_csCraft, int a_iValue);
	int FindCraftSkill (CString &a_csCraft);
	Clear ();
	Destroy();
	bool LoadFromFile (CString &a_csFilename);
	CProfile();
	virtual ~CProfile();

	bool m_bChanged;

	CString m_csProfileEmail;
	CString m_csProfileName;
	CString m_csProfileServer;
	CString m_csProfileType;

	CTypedPtrList<CPtrList, CBonus*>  m_clStatisticList;
	CTypedPtrList<CPtrList, CBonus*>  m_clAdventureSkillsList;
	CTypedPtrList<CPtrList, CSkill*>  m_clAdventureSchoolList;
	CTypedPtrList<CPtrList, CBonus*>  m_clCraftSkillsList;
	CTypedPtrList<CPtrList, CSkill*>	 m_clCraftSchoolList;

	CProfile(const CProfile *pSrc);
	operator =( const CProfile* pSrc );
	void CopyObject(const CProfile *pSrc);
};

#endif // !defined(AFX_PROFILE_H__DC567DBA_3C0D_455B_8B12_7FB8E44A7D1E__INCLUDED_)
