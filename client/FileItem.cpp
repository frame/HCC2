// FileItem.cpp: implementation of the CFileItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HCC.h"
#include "FileItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileItem::CFileItem()
{
	m_iResult = FileItem_Waiting;
	m_iSize = 0;
}

CFileItem::~CFileItem()
{

}
