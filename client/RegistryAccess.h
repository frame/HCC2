// RegistryAccess.h: interface for the CRegistryAccess class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGISTRYACCESS_H__DDDA0982_CAEA_4B70_9CD4_0A2107B84B61__INCLUDED_)
#define AFX_REGISTRYACCESS_H__DDDA0982_CAEA_4B70_9CD4_0A2107B84B61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRegistryAccess  
{
public:
	bool DetectFlexGrid();
	bool LoadKey(CString a__csKeyPath, CString a_csKey, int &a_iValue);
	bool LoadKey(CString a__csKeyPath, CString a_csKey, bool &a_bValue);
	bool LoadKey(CString a__csKeyPath, CString a_csKey, CString &a_csValue);
	bool SaveKey(CString a_csKeyPath, CString a_csKey, int a_iValue);
	bool SaveKey(CString a_csKeyPath, CString a_csKey, bool a_bValue);
	bool SaveKey (CString a_csKeyPath, CString a_csKey, CString a_csValue);
	CRegistryAccess();
	virtual ~CRegistryAccess();

};

#endif // !defined(AFX_REGISTRYACCESS_H__DDDA0982_CAEA_4B70_9CD4_0A2107B84B61__INCLUDED_)
