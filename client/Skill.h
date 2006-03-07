// Skill.h: interface for the CSkill class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKILL_H__7A516318_047C_406F_B245_B16DAA7158B6__INCLUDED_)
#define AFX_SKILL_H__7A516318_047C_406F_B245_B16DAA7158B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSkill  
{
public:
	Destroy();
	CSkill();
	virtual ~CSkill();

	CString m_csSkillName;
	int m_iSkillValue;
	int m_iWorkTierMin;
	int m_iWorkTierMax;

	CSkill(const CSkill *pSrc);
	operator =( const CSkill* pSrc );
	void CopyObject(const CSkill *pSrc);
};

#endif // !defined(AFX_SKILL_H__7A516318_047C_406F_B245_B16DAA7158B6__INCLUDED_)
