// HCC.h : main header file for the HCC application
//

#if !defined(AFX_HCC_H__6D13ABCF_7191_4EE1_9318_A08E79E1E00F__INCLUDED_)
#define AFX_HCC_H__6D13ABCF_7191_4EE1_9318_A08E79E1E00F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHCCApp:
// See HCC.cpp for the implementation of this class
//

class CHCCApp : public CWinApp
{
public:
	SetPriority (int Priority);
	void SetDialogColors (COLORREF a_iFg, COLORREF  a_iBg);
	CHCCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHCCApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL ProcessMessageFilter(int code, LPMSG lpMsg);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHCCApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HCC_H__6D13ABCF_7191_4EE1_9318_A08E79E1E00F__INCLUDED_)
