// WndX.cpp : implementation file
//

#include "stdafx.h"
#include "HCC.h"
#include "WndX.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWndX

CWndX::CWndX()
{
}

CWndX::~CWndX()
{
}


BEGIN_MESSAGE_MAP(CWndX, CWnd)
	//{{AFX_MSG_MAP(CWndX)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CWndX message handlers

CWndX::StartUp(int a_iDialogId)
{
	this->Create (a_iDialogId, NULL);
	m_cWindowState.m_bLoaded = true;
}

