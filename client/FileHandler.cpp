// FileHandler.cpp: implementation of the CFileHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HCC.h"
#include "FileHandler.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileHandler::CFileHandler()
{

}

CFileHandler::~CFileHandler()
{

}

bool CFileHandler::ReadToken (CString &a_csLine, int &a_iOffset, CString &a_cResult)
{
	int l_iTokenOffset;

	if (a_iOffset >= 0)
	{
		l_iTokenOffset = a_csLine.Find ('|', a_iOffset);
		if (l_iTokenOffset == -1)
		{
			a_cResult = a_csLine.Mid (a_iOffset);
		}
		else
		{
			if (l_iTokenOffset == a_iOffset)
			{
				a_cResult.Empty ();
			}
			else
			{
				a_cResult = a_csLine.Mid (a_iOffset, (l_iTokenOffset - a_iOffset));
			}
		}

		a_iOffset = l_iTokenOffset + 1;
		return (true);
	}
	else
	{
		return (false);
	}
}

bool CFileHandler::ReadToken (CString &a_csLine, int &a_iOffset, int &a_iResult)
{
	int l_iTokenOffset;

	if (a_iOffset >= 0)
	{
		l_iTokenOffset = a_csLine.Find ('|', a_iOffset);
		if (l_iTokenOffset == -1)
		{
			a_iResult = atoi (a_csLine.Mid (a_iOffset));
		}
		else
		{
			if (l_iTokenOffset == a_iOffset)
			{
				a_iResult = 0;
			}
			else
			{
				a_iResult = atoi (a_csLine.Mid (a_iOffset, (l_iTokenOffset - a_iOffset)));
			}
		}

		a_iOffset = l_iTokenOffset + 1;
		return (true);
	}
	else
	{
		return (false);
	}
}


CString CFileHandler::BoolToStr(bool a_bValue)
{
	if (a_bValue)
	{
		return ("Y");
	}
	else
	{
		return ("N");
	}
}

bool CFileHandler::StrToBool(CString &a_csValue)
{
	return ((a_csValue == "Y") || (a_csValue == "y"));
}
