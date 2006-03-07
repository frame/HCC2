// ObjectSpace.cpp: implementation of the CObjectSpace class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HCC.h"
#include "ObjectSpace.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CObjectSpace::CObjectSpace()
{
	m_pWnd = NULL;
	m_pParentWnd = NULL;
	m_pLeftObjectLink = NULL;
	m_pTopObjectLink = NULL;
	m_pDeltaY = NULL;
}

CObjectSpace::~CObjectSpace()
{

}

CObjectSpace::InitState(CWnd &a_cDialog, CDialog &a_cParentDialog, CObjectSpace *a_cOS_Left, CObjectSpace *a_cOS_Top, double a_fWidth, double a_fHeight, int *a_pDeltaY)
{
	RECT l_cRect;
	RECT l_cParentRect;

	m_pWnd = &a_cDialog;
	m_pParentWnd = &a_cParentDialog;

	a_cDialog.GetWindowRect (&l_cRect);
	m_iOrigWidth = l_cRect.right - l_cRect.left;
	m_iOrigHeight = l_cRect.bottom - l_cRect.top;

	a_cParentDialog.ScreenToClient (&l_cRect);
	a_cParentDialog.GetWindowRect (&l_cParentRect);
	a_cParentDialog.ScreenToClient (&l_cParentRect);
	m_iOrigX = l_cRect.left;
	m_iOrigY = l_cRect.top;
	m_iParentWidth = l_cParentRect.right - l_cParentRect.left;
	m_iParentHeight = l_cParentRect.bottom - l_cParentRect.top;

	m_fPercentageWidth = a_fWidth;
	m_fPercentageHeight = a_fHeight;

	m_pLeftObjectLink = a_cOS_Left;
	m_pTopObjectLink = a_cOS_Top;

	if (m_pLeftObjectLink)
	{
		m_iLeftMargin = m_iOrigX - (m_pLeftObjectLink->m_iOrigX + m_pLeftObjectLink->m_iOrigWidth);
	}
	else
	{
		m_iLeftMargin = m_iOrigX;
	}

	if (m_pTopObjectLink)
	{
		m_iTopMargin = m_iOrigY - (m_pTopObjectLink->m_iOrigY + m_pTopObjectLink->m_iOrigHeight);
	}
	else
	{
		m_iTopMargin = m_iOrigY;
	}

	m_pDeltaY = a_pDeltaY;
}

CObjectSpace::Resize()
{
	double l_fX;
	double l_fY;
	double l_fWidth;
	double l_fHeight;
	double l_fSpareWidth;
	double l_fSpareHeight;
	RECT l_cParentRect;
	double l_fDeltaY;

	if (m_pWnd)
	{
		if (m_pDeltaY)
		{
			l_fDeltaY = (float) *(m_pDeltaY);
		}

		m_pParentWnd->GetWindowRect (&l_cParentRect);
		m_pParentWnd->ScreenToClient (&l_cParentRect);
		l_fSpareWidth = double ((l_cParentRect.right - l_cParentRect.left) - m_iParentWidth);
		l_fSpareHeight = double ((l_cParentRect.bottom - l_cParentRect.top) - m_iParentHeight);

		if (m_pLeftObjectLink)
		{
			l_fX = (double) m_pLeftObjectLink->m_iCurOrigX + m_pLeftObjectLink->m_iCurWidth + m_iLeftMargin;
		}
		else
		{
			l_fX = (double) m_iOrigX;
		}

		if (m_pTopObjectLink)
		{
			l_fY = (double) m_pTopObjectLink->m_iCurOrigY + m_pTopObjectLink->m_iCurHeight + m_iTopMargin;
		}
		else
		{
			l_fY = (double) m_iOrigY;
		}

		l_fWidth = (double) m_iOrigWidth + (m_fPercentageWidth * l_fSpareWidth);
		l_fHeight = (double) m_iOrigHeight + (m_fPercentageHeight * l_fSpareHeight);

		m_iCurOrigX = (int) l_fX;
		m_iCurOrigY = (int) l_fY;
		m_iCurWidth = (int) l_fWidth;
		m_iCurHeight = (int) l_fHeight - (int) l_fDeltaY;

		m_pWnd->SetWindowPos (NULL, m_iCurOrigX, m_iCurOrigY, m_iCurWidth, m_iCurHeight, 0);
	}
}

CObjectSpace::LinkToLeftObject(CObjectSpace &a_cObjectSpace)
{
	m_pLeftObjectLink = &a_cObjectSpace;
}

CObjectSpace::LinkToTopObject(CObjectSpace &a_cObjectSpace)
{
	m_pTopObjectLink = &a_cObjectSpace;
}
