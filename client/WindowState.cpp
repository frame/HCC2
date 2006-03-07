// WindowState.cpp: implementation of the CWindowState class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HCC.h"
#include "WindowState.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWindowState::CWindowState()
{
	m_bLoaded = false;
	m_bVisible = false;
	m_bOnTop = false;
	m_iPosX = -1;
	m_iPosY = -1;
	m_iWidth = -1;
	m_iHeight = -1;
}

CWindowState::~CWindowState()
{

}

CString CWindowState::toString()
{
	CString l_csStr;
	CString l_csVisible;
	CString l_csOnTop;

	if (m_bVisible)
	{
		l_csVisible = "Y";
	}
	else
	{
		l_csVisible = "N";
	}

	if (m_bOnTop)
	{
		l_csOnTop = "Y";
	}
	else
	{
		l_csOnTop = "N";
	}

	l_csStr.Format ("X:%d, Y:%d, W:%d, H:%d, V:%s T:%s", m_iPosX, m_iPosY, m_iWidth, m_iHeight, l_csVisible, l_csOnTop);
	return (l_csStr);
}

CWindowState::fromString(CString a_csStr)
{
	CString l_csVisible;
	CString l_csOnTop = "N";

	sscanf (a_csStr, "X:%d, Y:%d, W:%d, H:%d, V:%s T:%s", &m_iPosX, &m_iPosY, &m_iWidth, &m_iHeight, l_csVisible, l_csOnTop);

	m_bVisible = (l_csVisible == "Y");
	m_bOnTop = (l_csOnTop == "Y");
}

CWindowState::setWnd(CWnd &a_cWnd)
{
	if (&a_cWnd)
	{
		if (m_iWidth != -1)
		{
			if (m_bOnTop)
			{
				a_cWnd.SetWindowPos (&CWnd::wndTopMost, m_iPosX, m_iPosY, m_iWidth, m_iHeight, 0);
			}
			else
			{
				a_cWnd.SetWindowPos (&CWnd::wndNoTopMost, m_iPosX, m_iPosY, m_iWidth, m_iHeight, 0);
			}
		}
	}
}

CWindowState::setWnd(CWnd *a_cWnd)
{
	if (a_cWnd)
	{
		if (a_cWnd->m_hWnd)
		{
			if (m_iWidth != -1)
			{
				if (m_bOnTop)
				{
					a_cWnd->SetWindowPos (&CWnd::wndTopMost, m_iPosX, m_iPosY, m_iWidth, m_iHeight, 0);
				}
				else
				{
					a_cWnd->SetWindowPos (&CWnd::wndNoTopMost, m_iPosX, m_iPosY, m_iWidth, m_iHeight, 0);
				}
			}
		}
	}
}

CWindowState::getWnd(CWnd &a_cWnd)
{
	RECT l_cRect;

	if (a_cWnd)
	{
		a_cWnd.GetWindowRect(&l_cRect);
		m_iPosX = l_cRect.left;
		m_iPosY = l_cRect.top;
		m_iWidth = l_cRect.right - l_cRect.left;
		m_iHeight = l_cRect.bottom - l_cRect.top;
	}
}

CWindowState::getWnd(CWnd *a_cWnd)
{
	RECT l_cRect;

	if (a_cWnd)
	{
		a_cWnd->GetWindowRect(&l_cRect);
		m_iPosX = l_cRect.left;
		m_iPosY = l_cRect.top;
		m_iWidth = l_cRect.right - l_cRect.left;
		m_iHeight = l_cRect.bottom - l_cRect.top;
	}
}

bool CWindowState::SnapToWnd(CWnd *a_cpThisWnd, CWnd *a_cpWnd, int a_iRange)
{
	CRect l_cWndRect;
	CRect l_cThisRect;
	int l_iWndHeight;
	int l_iWndWidth;
	bool l_bMoved = false;

	if ((a_cpThisWnd) && (m_bLoaded))
	{
		a_cpThisWnd->GetWindowRect (l_cThisRect);
		l_iWndHeight = l_cThisRect.Height ();
		l_iWndWidth = l_cThisRect.Width ();

		if (a_cpWnd)
		{
			a_cpWnd->GetWindowRect (l_cWndRect);

			if ((l_cThisRect.top > (l_cWndRect.top - l_iWndHeight)) &&
             (l_cThisRect.top < l_cWndRect.bottom))
			{
				if  ((l_cThisRect.left > (l_cWndRect.right - a_iRange)) &&
					  (l_cThisRect.left < (l_cWndRect.right + a_iRange)))
				{
					l_cThisRect.left = l_cWndRect.right;
					l_cThisRect.right = l_cWndRect.left + l_iWndWidth;
					l_bMoved = true;
				}
				else if ((l_cThisRect.right > (l_cWndRect.left - a_iRange)) &&
							(l_cThisRect.right < (l_cWndRect.left + a_iRange)))
				{
					l_cThisRect.right = l_cWndRect.left;
					l_cThisRect.left = l_cThisRect.right - l_iWndWidth;
					l_bMoved = true;
				}
			}

			if ((l_cThisRect.left > (l_cWndRect.left - l_iWndWidth)) &&
             (l_cThisRect.left < l_cWndRect.right))
			{
				if  ((l_cThisRect.top > (l_cWndRect.bottom - a_iRange)) &&
					  (l_cThisRect.top < (l_cWndRect.bottom + a_iRange)))
				{
					l_cThisRect.top = l_cWndRect.bottom;
					l_cThisRect.bottom = l_cWndRect.top + l_iWndHeight;
					l_bMoved = true;
				}
				else if ((l_cThisRect.bottom > (l_cWndRect.top - a_iRange)) &&
							(l_cThisRect.bottom < (l_cWndRect.top + a_iRange)))
				{
					l_cThisRect.bottom = l_cWndRect.top;
					l_cThisRect.top = l_cThisRect.bottom - l_iWndHeight;
					l_bMoved = true;
				}
			}
		}
		else
		{
			//l_cWndRect.left = 0;
			//l_cWndRect.top  = 0;
			//l_cWndRect.right = l_cWndRect.left + GetSystemMetrics (SM_CXSCREEN);
			//l_cWndRect.bottom = l_cWndRect.top + GetSystemMetrics (SM_CYSCREEN);
			SystemParametersInfo (SPI_GETWORKAREA, 0, &l_cWndRect, 0);

			if  ((l_cThisRect.left > (l_cWndRect.left - a_iRange)) &&
				  (l_cThisRect.left < (l_cWndRect.left + a_iRange)))
			{
				l_cThisRect.left = l_cWndRect.left;
				l_cThisRect.right = l_cWndRect.left + l_iWndWidth;
				l_bMoved = true;
			}
			else if ((l_cThisRect.right > (l_cWndRect.right - a_iRange)) &&
				      (l_cThisRect.right < (l_cWndRect.right + a_iRange)))
			{
				l_cThisRect.right = l_cWndRect.right;
				l_cThisRect.left = l_cWndRect.right - l_iWndWidth;
				l_bMoved = true;
			}

			if  ((l_cThisRect.top > (l_cWndRect.top - a_iRange)) &&
				  (l_cThisRect.top < (l_cWndRect.top + a_iRange)))
			{
				l_cThisRect.top = l_cWndRect.top;
				l_cThisRect.bottom = l_cWndRect.top + l_iWndHeight;
				l_bMoved = true;
			}
			else if ((l_cThisRect.bottom > (l_cWndRect.bottom - a_iRange)) &&
				      (l_cThisRect.bottom < (l_cWndRect.bottom + a_iRange)))
			{
				l_cThisRect.bottom = l_cWndRect.bottom;
				l_cThisRect.top = l_cWndRect.bottom - l_iWndHeight;
				l_bMoved = true;
			}

		}

		if (l_bMoved)
		{
			//m_iPosX = l_cThisRect.left;
			a_cpThisWnd->SetWindowPos (0, l_cThisRect.left, l_cThisRect.top, 0, 0, SWP_NOSIZE   );
		}
	}

	return (l_bMoved);
}

bool CWindowState::SnapToWnd(WINDOWPOS* lpwndpos, CRect *a_cpOrigRect, CWnd *a_cpWnd, int a_iRange)
{
	CRect l_cWndRect;
	CRect l_cThisRect;
	int l_iWndHeight;
	int l_iWndWidth;
	bool l_bMoved = false;
	bool l_bLeftResize = false;
	bool l_bRightResize = false;
	bool l_bTopResize = false;
	bool l_bBottomResize = false;

	if (m_bLoaded)
	{
		l_cThisRect.left = lpwndpos->x;
		l_cThisRect.top = lpwndpos->y;
		l_cThisRect.right = lpwndpos->x + lpwndpos->cx;
		l_cThisRect.bottom = lpwndpos->y + lpwndpos->cy;
		l_iWndHeight = l_cThisRect.Height ();
		l_iWndWidth = l_cThisRect.Width ();

		if (a_cpOrigRect->Width() != lpwndpos->cx)
		{
			l_bLeftResize  = (a_cpOrigRect->left  != lpwndpos->x);
			l_bRightResize = (a_cpOrigRect->right != (lpwndpos->x + lpwndpos->cx));
		}

		if (a_cpOrigRect->Height() != lpwndpos->cy)
		{
			l_bTopResize  =   (a_cpOrigRect->top    != lpwndpos->y);
			l_bBottomResize = (a_cpOrigRect->bottom != (lpwndpos->y + lpwndpos->cy));
		}

		if (a_cpWnd)
		{
			a_cpWnd->GetWindowRect (l_cWndRect);

			if ((l_cThisRect.top > (l_cWndRect.top - l_iWndHeight)) &&
             (l_cThisRect.top < l_cWndRect.bottom))
			{
				if  ((l_cThisRect.left > (l_cWndRect.right - a_iRange)) &&
					  (l_cThisRect.left < (l_cWndRect.right + a_iRange)) &&
					  (l_cThisRect.left != l_cWndRect.right))
				{
					l_cThisRect.left = l_cWndRect.right;

					if (!l_bLeftResize)
					{
						l_cThisRect.right = l_cThisRect.left + l_iWndWidth;
					}
					l_bMoved = true;
				}
				else if ((l_cThisRect.right > (l_cWndRect.left - a_iRange)) &&
							(l_cThisRect.right < (l_cWndRect.left + a_iRange)) &&
							(l_cThisRect.right != l_cWndRect.left))
				{
					l_cThisRect.right = l_cWndRect.left;

					if (!l_bRightResize)
					{
						l_cThisRect.left = l_cThisRect.right - l_iWndWidth;
					}
					l_bMoved = true;
				}
			}

			if ((l_cThisRect.left > (l_cWndRect.left - l_iWndWidth)) &&
             (l_cThisRect.left < l_cWndRect.right))
			{
				if  ((l_cThisRect.top > (l_cWndRect.bottom - a_iRange)) &&
					  (l_cThisRect.top < (l_cWndRect.bottom + a_iRange)))
				{
					l_cThisRect.top = l_cWndRect.bottom;

					if (!l_bTopResize)
					{
						l_cThisRect.bottom = l_cThisRect.top + l_iWndHeight;
					}
					l_bMoved = true;
				}
				else if ((l_cThisRect.bottom > (l_cWndRect.top - a_iRange)) &&
							(l_cThisRect.bottom < (l_cWndRect.top + a_iRange)))
				{
					l_cThisRect.bottom = l_cWndRect.top;

					if (!l_bBottomResize)
					{
						l_cThisRect.top = l_cThisRect.bottom - l_iWndHeight;
					}
					l_bMoved = true;
				}
			}
		}
		else
		{
			//l_cWndRect.left = 0;
			//l_cWndRect.top  = 0;
			//l_cWndRect.right = l_cWndRect.left + GetSystemMetrics (SM_CXSCREEN);
			//l_cWndRect.bottom = l_cWndRect.top + GetSystemMetrics (SM_CYSCREEN);
			SystemParametersInfo (SPI_GETWORKAREA, 0, &l_cWndRect, 0);

			if  ((l_cThisRect.left > (l_cWndRect.left - a_iRange)) &&
				  (l_cThisRect.left < (l_cWndRect.left + a_iRange)))
			{
				l_cThisRect.left = l_cWndRect.left;

				if (!l_bLeftResize)
				{
					l_cThisRect.right = l_cWndRect.left + l_iWndWidth;
				}
				l_bMoved = true;
			}
			else if ((l_cThisRect.right > (l_cWndRect.right - a_iRange)) &&
				      (l_cThisRect.right < (l_cWndRect.right + a_iRange)))
			{
				l_cThisRect.right = l_cWndRect.right;

				if (!l_bRightResize)
				{
					l_cThisRect.left = l_cWndRect.right - l_iWndWidth;
				}
				l_bMoved = true;
			}

			if  ((l_cThisRect.top > (l_cWndRect.top - a_iRange)) &&
				  (l_cThisRect.top < (l_cWndRect.top + a_iRange)))
			{
				l_cThisRect.top = l_cWndRect.top;

				if (!l_bTopResize)
				{
					l_cThisRect.bottom = l_cWndRect.top + l_iWndHeight;
				}
				l_bMoved = true;
			}
			else if ((l_cThisRect.bottom > (l_cWndRect.bottom - a_iRange)) &&
				      (l_cThisRect.bottom < (l_cWndRect.bottom + a_iRange)))
			{
				l_cThisRect.bottom = l_cWndRect.bottom;

				if (!l_bBottomResize)
				{
					l_cThisRect.top = l_cWndRect.bottom - l_iWndHeight;
				}
				l_bMoved = true;
			}

		}

		if (l_bMoved)
		{
			lpwndpos->x = l_cThisRect.left;
			lpwndpos->y = l_cThisRect.top;
			lpwndpos->cx = l_cThisRect.Width ();
			lpwndpos->cy = l_cThisRect.Height ();
		}
	}

	return (l_bMoved);
}
