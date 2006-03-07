// ImageStore.h: interface for the CImageStore class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGESTORE_H__FDA91A3D_D00D_4A40_A8FE_E8EF751FEA42__INCLUDED_)
#define AFX_IMAGESTORE_H__FDA91A3D_D00D_4A40_A8FE_E8EF751FEA42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CImageStore  
{
public:
	bool LoadFromArchive (CArchive &a_cArchive);
	AddCustomIcons (UINT l_iImageRef, int a_iAmount);
	int FindImageOffset (CString &a_csIconName);
	Initialise();
	bool LoadImage(WCHAR *a_cFile);
	bool LoadFromDirectory (CString &a_csPath, bool a_bClear = false);
	CImageStore();
	virtual ~CImageStore();

	CString							m_csSubDirectory;
	CArray<CString, CString>	m_cImageNameList;
	CImageList						m_cImageList;
	int								m_iSize;
};

#endif // !defined(AFX_IMAGESTORE_H__FDA91A3D_D00D_4A40_A8FE_E8EF751FEA42__INCLUDED_)
