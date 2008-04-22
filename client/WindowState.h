// WindowState.h: interface for the CWindowState class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINDOWSTATE_H__8432B504_C7B2_4BD6_A197_8DCB184E2D82__INCLUDED_)
#define AFX_WINDOWSTATE_H__8432B504_C7B2_4BD6_A197_8DCB184E2D82__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWindowState
{
public:
	bool SnapToWnd(WINDOWPOS* lpwndpos, CRect *a_cpOrigRect, CWnd *a_cpWnd, int a_iRange);
	bool SnapToWnd (CWnd *a_cpThisWnd, CWnd *a_cpWnd, int a_iRange);
	getWnd (CWnd &a_cWnd);
	getWnd(CWnd *a_cWnd);
	setWnd (CWnd &a_cWnd);
	setWnd (CWnd *a_cWnd);
	fromString (CString a_csStr);
	CString toString();
	CWindowState();
	virtual ~CWindowState();

	int m_iPosX;
	int m_iPosY;
	int m_iWidth;
	int m_iHeight;
	bool m_bOnTop;

	bool m_bVisible;
	bool m_bLoaded;

};

#endif // !defined(AFX_WINDOWSTATE_H__8432B504_C7B2_4BD6_A197_8DCB184E2D82__INCLUDED_)
