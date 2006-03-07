// FormulaSet.h: interface for the CFormulaSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FORMULASET_H__2A3326E1_87A1_47DB_AC38_9BC5E93D571F__INCLUDED_)
#define AFX_FORMULASET_H__2A3326E1_87A1_47DB_AC38_9BC5E93D571F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "formula.h"
#include "FileHandler.h"

class CFormulaSet  : CFileHandler
{
public:
	bool ReadFromFile(CStdioFile &a_cFile);
	WriteToFile(CStdioFile &a_cFile);
	Destroy(bool a_bAll = true);
	AddSet (CFormulaSet *a_cpFormulaSet);
	bool LoadFormulaSet (CString a_csFilename);
	CFormulaSet();
	virtual ~CFormulaSet();

	CString m_csName;
	CString m_csCategory;
	CString m_csFormat;
	int	  m_iIcon;

	CTypedPtrList<CPtrList, CFormula*>	m_clFormulaList;

	CFormulaSet(const CFormulaSet *pSrc);
	operator =( const CFormulaSet* pSrc );
	void CopyObject(const CFormulaSet *pSrc);
};

#endif // !defined(AFX_FORMULASET_H__2A3326E1_87A1_47DB_AC38_9BC5E93D571F__INCLUDED_)
