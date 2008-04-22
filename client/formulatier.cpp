// Formula.cpp: implementation of the CFormulaTier class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HCC.h"
#include "Formula.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFormulaTier::CFormulaTier()
{
	m_iBatchQty = 1;
}

CFormulaTier::~CFormulaTier()
{
	Destroy ();
}

CFormulaTier::operator =( const CFormulaTier* pSrc )
{
   CopyObject (pSrc);
   return true;
}


CFormulaTier::CFormulaTier(const CFormulaTier *pSrc)
{
   CopyObject (pSrc);
}

void CFormulaTier::CopyObject(const CFormulaTier *pSrc)
{
	m_csName = pSrc->m_csName;
	m_csDescription = pSrc->m_csDescription;
	m_iTierLevel = pSrc->m_iTierLevel;
	m_csTierName = pSrc->m_csTierName;

	m_clResourceList.RemoveAll ();
	POSITION l_Pos = pSrc->m_clResourceList.GetHeadPosition ();
	while (l_Pos)
	{
		m_clResourceList.AddTail (pSrc->m_clResourceList.GetNext (l_Pos));
	}

	m_clEffectsList.RemoveAll ();
	l_Pos = pSrc->m_clEffectsList.GetHeadPosition ();
	while (l_Pos)
	{
		m_clEffectsList.AddTail (pSrc->m_clEffectsList.GetNext (l_Pos));
	}
}

CFormulaTier::Clear()
{
	m_csName.Empty ();
	m_iTierLevel = 0;
	m_csTierName.Empty ();
	Destroy ();
}

CFormulaTier::Destroy()
{
	CItemResource *l_cpItemResource;
	CEffect *l_cpEffect;

	POSITION l_Pos = m_clResourceList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpItemResource = m_clResourceList.GetNext (l_Pos);
		l_cpItemResource->Destroy ();
		delete (l_cpItemResource);
	}
	m_clResourceList.RemoveAll ();

	l_Pos = m_clEffectsList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpEffect = m_clEffectsList.GetNext (l_Pos);
		l_cpEffect->Destroy ();
		delete (l_cpEffect);
	}
	m_clEffectsList.RemoveAll ();
}

CFormulaTier::WriteToFile(CStdioFile &a_cFile)
{
	CString l_csLine;
	CItemResource *l_cpItemResource;
	CEffect *l_cpEffect;

	l_csLine.Format ("%s|%d|%s|%s|%d|%d|%d|%d\n",
						  m_csName,
						  m_iTierLevel,
						  m_csTierName,
						  m_csDescription,
						  m_iAllowedTechniques,
						  m_iBatchQty,
						  m_clEffectsList.GetCount(),
						  m_clResourceList.GetCount());
	a_cFile.WriteString (l_csLine);

	m_cKeywords.WriteToFile (a_cFile);

	POSITION l_Pos = m_clEffectsList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpEffect = m_clEffectsList.GetNext (l_Pos);
		l_cpEffect->WriteToFile (a_cFile);
	}

	l_Pos = m_clResourceList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpItemResource = m_clResourceList.GetNext (l_Pos);
		l_cpItemResource->WriteToFile (a_cFile);
	}
}

bool CFormulaTier::ReadFromFile(CStdioFile &a_cFile)
{
	CString l_csLine;
	bool l_bSuccess = true;
	int l_iTokenOffset = 0;
	int l_iEffectCount = 0;
	int l_iResourceCount = 0;
	CItemResource *l_cpItemResource;
	CEffect *l_cpEffect;

	if (a_cFile.ReadString (l_csLine))
	{
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csName);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_iTierLevel);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csTierName);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_csDescription);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_iAllowedTechniques);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, m_iBatchQty);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, l_iEffectCount);
		l_bSuccess = l_bSuccess && ReadToken (l_csLine, l_iTokenOffset, l_iResourceCount);

		l_bSuccess = l_bSuccess && m_cKeywords.ReadFromFile (a_cFile);

		if (l_bSuccess)
		{
			while (l_iEffectCount--)
			{
				l_cpEffect = new CEffect();
				l_bSuccess = l_bSuccess && l_cpEffect->ReadFromFile (a_cFile);
				m_clEffectsList.AddTail (l_cpEffect);
			}
		}

		if (l_bSuccess)
		{
			while (l_iResourceCount--)
			{
				l_cpItemResource = new CItemResource();
				l_bSuccess = l_bSuccess && l_cpItemResource->ReadFromFile (a_cFile);
				m_clResourceList.AddTail (l_cpItemResource);
			}
		}
	}

	return (l_bSuccess);
}
