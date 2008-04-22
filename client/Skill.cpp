// Skill.cpp: implementation of the CSkill class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Skill.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSkill::CSkill()
{

}

CSkill::~CSkill()
{

}

CSkill::operator =( const CSkill* pSrc )
{
   CopyObject (pSrc);
   return true;
}


CSkill::CSkill(const CSkill *pSrc)
{
   CopyObject (pSrc);
}

void CSkill::CopyObject(const CSkill *pSrc)
{
	m_csSkillName = pSrc->m_csSkillName;
	m_iSkillValue = pSrc->m_iSkillValue;
	m_iWorkTierMin  = pSrc->m_iWorkTierMin;
	m_iWorkTierMax  = pSrc->m_iWorkTierMax;
}

CSkill::Destroy()
{

}
