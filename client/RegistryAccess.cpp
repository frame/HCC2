// RegistryAccess.cpp: implementation of the CRegistryAccess class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HCC.h"
#include "RegistryAccess.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRegistryAccess::CRegistryAccess()
{

}

CRegistryAccess::~CRegistryAccess()
{

}

bool CRegistryAccess::SaveKey(CString a_csKeyPath, CString a_csKey, CString a_csValue)
{
	char Str[512];
	unsigned long Size;
	HKEY Key;
	bool l_bResult = false;

	if (RegCreateKey (HKEY_LOCAL_MACHINE, a_csKeyPath, &Key) == ERROR_SUCCESS)
	{
		sprintf (Str, "%s", a_csValue);
		Size = strlen (Str);
		l_bResult = (RegSetValueEx (Key, a_csKey, 0, REG_SZ, (const unsigned char *) Str, Size) == ERROR_SUCCESS);
	}
	return (l_bResult);
}

bool CRegistryAccess::SaveKey(CString a_csKeyPath, CString a_csKey, int a_iValue)
{
	CString l_csStr;

	l_csStr.Format ("%d", a_iValue);
	return (SaveKey (a_csKeyPath, a_csKey, l_csStr));
}

bool CRegistryAccess::SaveKey(CString a_csKeyPath, CString a_csKey, bool a_bValue)
{
	CString l_csStr;

	if (a_bValue)
	{
		l_csStr = "Y";
	}
	else
	{
		l_csStr = "N";
	}

	return (SaveKey (a_csKeyPath, a_csKey, l_csStr));
}

bool CRegistryAccess::LoadKey(CString a__csKeyPath, CString a_csKey, CString &a_csValue)
{
	HKEY Key;
   int i = 0;
	char ValueName[512];
	unsigned char Data[512];
	unsigned long ValueSize  = 512;
	unsigned long DataSize = 512;
	CString l_csStr;

	if (RegOpenKey (HKEY_LOCAL_MACHINE, a__csKeyPath, &Key) == ERROR_SUCCESS)
	{
		while (RegEnumValue (Key, i, ValueName, &ValueSize, NULL, NULL, Data, &DataSize) == ERROR_SUCCESS)
		{
			if (stricmp (ValueName, a_csKey) == 0)
			{
				if (DataSize > 0)
				{
					a_csValue.Format ("%s", Data);
				}
				else
				{
					a_csValue = "";
				}
				return (true);
			}

			ValueSize = 512;
			DataSize = 512;
			i++;
		}
	}
	return (false);
}

bool CRegistryAccess::DetectFlexGrid()
{
	HKEY Key;
   int i = 0;
	char ValueName[512];
	unsigned char Data[512];
	unsigned long ValueSize  = 512;
	unsigned long DataSize = 512;
	CString l_csStr = "";

	if (RegOpenKey (HKEY_CLASSES_ROOT, "TypeLib\\{5E9E78A0-531B-11CF-91F6-C2863C385E30}\\1.0\\0\\win32", &Key) == ERROR_SUCCESS)
	{
		while (RegEnumValue (Key, i, ValueName, &ValueSize, NULL, NULL, Data, &DataSize) == ERROR_SUCCESS)
		{
			if (ValueName[0] == 0)
			{
				l_csStr.Format ("%s", Data);
			}
			ValueSize = 512;
			DataSize = 512;
			i++;
		}

		FILE *l_cFilePtr;

		l_cFilePtr = fopen (l_csStr, "r");
		if (l_cFilePtr)
		{
			fclose (l_cFilePtr);
			return (true);
		}
	}
	return (false);
}

bool CRegistryAccess::LoadKey(CString a__csKeyPath, CString a_csKey, bool &a_bValue)
{
	CString l_csStr;

	if (LoadKey (a__csKeyPath, a_csKey, l_csStr))
	{
		a_bValue = (l_csStr == "Y") || (l_csStr == "y");
		return (true);
	}

	return (false);
}

bool CRegistryAccess::LoadKey(CString a__csKeyPath, CString a_csKey, int &a_iValue)
{
	CString l_csStr;

	if (LoadKey (a__csKeyPath, a_csKey, l_csStr))
	{
		a_iValue = atoi (l_csStr);
		return (true);
	}

	return (false);
}