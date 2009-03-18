// Effect.cpp: implementation of the CEffect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Effect.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEffect::CEffect()
{

}

CEffect::~CEffect()
{

}

CEffect::operator =( const CEffect* pSrc )
{
   CopyObject (pSrc);
   return true;
}


CEffect::CEffect(const CEffect *pSrc)
{
   CopyObject (pSrc);
}

void CEffect::CopyObject(const CEffect *pSrc)
{
	m_csType = pSrc->m_csType;
	m_csDescription = pSrc->m_csDescription;
}

CEffect::Clear()
{
}

CEffect::Destroy()
{

}

CEffect::WriteToFile(CStdioFile &a_cFile)
{
	CString l_csLine;

	l_csLine.Format ("%s|%s\n", m_csType, m_csDescription);
	a_cFile.WriteString (l_csLine);
}

bool CEffect::ReadFromFile(CStdioFile &a_cFile)
{
	CString l_csLine;
	bool l_bSuccess = true;
	int l_iTokenOffset = 0;

	if (a_cFile.ReadString (l_csLine))
	{
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csType);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csDescription);
	}

	return (l_bSuccess);
}

CEffect::TranslateEffectType()
{
	static int l_iValue1;
	static int l_iValue2;
	static int l_iValue3;

/*
hoardCost







healAmount
healPercentage

descriptionResurrect





*/
	m_csType.MakeLower ();

	if (m_csType == "equipslot")
	{
		m_csType = cXMLAttribute_EquipSlot;
	}

	else if (m_csType == "bulk")
	{
		m_csType = cXMLAttribute_Bulk;
	}

	else if (m_csType == "bulkcapacity")
	{
		m_csType = cXMLAttribute_Capacity;
	}

	else if (m_csType == "reqclass")
	{
		m_csType = cXMLAttribute_ReqClass;
	}

	else if ((m_csType == "reqadvskill") ||
			   (m_csType == "reqcraftskill"))
	{
		m_csType = cXMLAttribute_ReqSkill;
	}

	else if ((m_csType == "reqanycraftlevel") ||
		      (m_csType == "reqanyschoollevel") ||
		      (m_csType == "reqcurrentadvlevel") ||
		      (m_csType == "reqcurrentcraftlevel") ||
		      (m_csType == "reqcurrentschoollevel"))
	{
		m_csType = cXMLAttribute_ReqLevel;
	}

	else if (m_csType == "reqrace")
	{
		m_csType = cXMLAttribute_ReqRace;
	}

	else if ((m_csType == "reqanyadvlevelbelow") ||
				(m_csType == "equipstatcap"))
	{
		m_csType = cXMLAttribute_Requirement;
	}

	else if (m_csType == "statbonus")
	{
		m_csType = cXMLAttribute_Bonus;
	}

	else if ((m_csType == "castdelay") ||
		      (m_csType == "delay"))
	{
		m_csType = cXMLAttribute_Delay;
		l_iValue1 = atoi (m_csDescription);
		m_csDescription.Format ("%d", l_iValue1);
	}

	else if (m_csType == "recycle")
	{
		m_csType = cXMLAttribute_Recycle;
		if (m_csDescription == "Repeating")
		{
		}
		else if (m_csDescription.Find (':') < 0)
		{
			l_iValue1 = atoi (m_csDescription);
			l_iValue2 = l_iValue1 % 60;
			l_iValue1 /= 60;
			m_csDescription.Format ("%d:%02d", l_iValue1, l_iValue2);
		}
	}

	else if (m_csType == "range")
	{
		m_csType = cXMLAttribute_Range;
	}

	else if (m_csType == "area")
	{
		m_csType = cXMLAttribute_Area;
	}

	else if (m_csType == "damage")
	{
		m_csType = cXMLAttribute_Damage;
	}

	else if (m_csType == "damagemodifier")
	{
		m_csType = cXMLAttribute_DamageModifier;
	}

	else if (m_csType == "healamount")
	{
		m_csType = cXMLAttribute_HealAmount;
	}

	else if (m_csType == "damagetype")
	{
		m_csType = cXMLAttribute_Type;
	}

	else if (m_csType == "skill")
	{
		m_csType = cXMLAttribute_Skill;
	}

	else if (m_csType == "damagetype")
	{
		m_csType = cXMLAttribute_Type;
	}

	else if (m_csType == "hoardvalue")
	{
		m_csType = cXMLAttribute_HoardValue;
	}

	else if (m_csType == "hoardcost")
	{
		m_csType = cXMLAttribute_HoardCost;
	}

	else if ((m_csType == "consumes") ||
		      (m_csType == "rechargeconsumes"))
	{
		m_csType = cXMLAttribute_Effect;
		m_csDescription = "Consumes '" + m_csDescription + "'";
	}

	else if (m_csType == "maxremovals")
	{
		m_csType = cXMLAttribute_Effect;
		m_csDescription = "Max Removals: " + m_csDescription;
	}

	else if (m_csType == "dispellstrength")
	{
		m_csType = cXMLAttribute_Effect;
		m_csDescription = "Dispel Strength: " + m_csDescription;
	}

	else if (m_csType == "dispelquality")
	{
		m_csType = cXMLAttribute_Effect;
		m_csDescription = "Dispel Quality: " + m_csDescription;
	}

	else if (m_csType == "dpreduction")
	{
		m_csType = cXMLAttribute_Timer;
		m_csDescription = m_csDescription;
	}

	else if ((m_csType == "chance") ||
		      (m_csType == "statmultiplier") ||
		      (m_csType == "statbonusvariable") ||
		      (m_csType == "capacitybonus") ||
		      (m_csType == "shieldon") ||
		      (m_csType == "statcap") ||
		      (m_csType == "preventteleport") ||
		      (m_csType == "preventrecall") ||
		      (m_csType == "rechargereduce") ||
		      (m_csType == "dpreductionreqlvl") ||
		      (m_csType == "dpreductionminlvl") ||
		      (m_csType == "dispelquality") ||
		      (m_csType == "description") ||
		      (m_csType == "convertdamage") ||
		      (m_csType == "info") ||
		      (m_csType == "frequency") ||
		      (m_csType == "delaymod") ||
		      (m_csType == "recyclemod") ||
		      (m_csType == "descriptionresurrect"))
	{
		m_csType = cXMLAttribute_Effect;
	}

	else if ((m_csType == "rangemodifier") ||
			   (m_csType == "delaymodifier") ||
			   (m_csType == "recyclemodifier") ||
			   (m_csType == "attackmodifier") ||
			   (m_csType == "healmodifier") ||
			   (m_csType == "usageadjust") ||
			   (m_csType == "structurestacks") ||
			   (m_csType == "structurebulk") ||
			   (m_csType == "structurenpc") ||
			   (m_csType == "structuremachine") ||
			   (m_csType == "structurebind") ||
			   (m_csType == "spelldefense") ||
			   (m_csType == "meleedefense") ||
			   (m_csType == "meleeoffense") ||
			   (m_csType == "lowresist") ||
			   (m_csType == "highresist") ||
			   (m_csType == "percentagestatbonus") ||
			   (m_csType == "schoolbonus"))
	{
	}

	else if ((m_csType == "effectreq") ||
				(m_csType == "effectstatmultiplier") ||
				(m_csType == "effectstatbonusvariable") ||
				(m_csType == "effectstatbonus") ||
				(m_csType == "effectcapacitybonus") ||
				(m_csType == "effectshieldon") ||
				(m_csType == "effectstatcap") ||
				(m_csType == "effectpreventteleport") ||
				(m_csType == "effectpreventrecall") ||
				(m_csType == "effectconsumes") ||
				(m_csType == "effecthoardcost") ||
				(m_csType == "effectrange") ||
				(m_csType == "effectcastdelay") ||
				(m_csType == "effectdelay") ||
				(m_csType == "effectrecycle") ||
				(m_csType == "effecteffect") ||
				(m_csType == "effectinfo") ||
				(m_csType == "effectarea") ||
				(m_csType == "effectdamage") ||
				(m_csType == "effectdamagetype") ||
				(m_csType == "effectskill") ||
				(m_csType == "effecthealpercentage") ||
				(m_csType == "effectmaxremovals") ||
				(m_csType == "effectdispelquality") ||
				(m_csType == "effecttakedamage") ||
				(m_csType == "effectdescriptionresurrect") ||
				(m_csType == "effectdpreduction") ||
				(m_csType == "effectdpreductionreqlvl") ||
				(m_csType == "effectdpreductionminlvl") ||
				(m_csType == "effectconvertdamage") ||
				(m_csType == "effectrechargeconsumes") ||
				(m_csType == "effectrechargereduce") ||
				(m_csType == "effectdelaymod"))
	{
		m_csType = cXMLAttribute_TargetEffect;
	}

	else if (m_csType == "effectfrequency")
	{
		m_csType = cXMLAttribute_TargetFrequency;
	}

	else if (m_csType == "effect")
	{
		m_csType = cXMLAttribute_TargetName;
		m_csDescription = "Effect: " + m_csDescription;

	}

	else if (m_csType == "effecthealamount")
	{
		m_csType = cXMLAttribute_TargetEffect;
		m_csDescription = "Heals: " + m_csDescription;
	}

	else if (m_csType == "effectdescription")
	{
		m_csType = cXMLAttribute_TargetDescription;
	}

 else if (m_csType == "effectchance")
	{
	    m_csType = cXMLAttribute_EffectChance;
		m_csDescription = m_csDescription;
	}

	else if (m_csType == "effectduration")
	{
		m_csType = cXMLAttribute_TargetDuration;
		if (m_csDescription.Find (':') < 0)
		{
			l_iValue1 = atoi (m_csDescription);
			l_iValue2 = (l_iValue1 / 60) % 60;
			l_iValue3 = l_iValue1 % 60;
			l_iValue1 /= 3600;

			if (l_iValue1 > 0)
			{
				m_csDescription.Format ("%d:%02d:%02d", l_iValue1, l_iValue2, l_iValue3);
			}
			else
			{
				m_csDescription.Format ("%d:%02d", l_iValue2, l_iValue3);
			}
		}
	}

	else if ((m_csType == "extradamage") ||
		      (m_csType == "takedamage"))
	{
		m_csType = cXMLAttribute_ExtraDamage;
	}

    else if ((m_csType == "reqRace"))
	{
		m_csType = cXMLAttribute_ReqRace;
	}
	else if (m_csType == "techeffect")
	{
		m_csType = cXMLAttribute_Effect;
	}

	else
	{
		//FIXME frame
		//m_csDescription = "? " + m_csType + ":" + m_csDescription + " ?";
		m_csDescription = m_csDescription;
		m_csType = cXMLAttribute_Effect;
	}
}
