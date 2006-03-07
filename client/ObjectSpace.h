// ObjectSpace.h: interface for the CObjectSpace class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBJECTSPACE_H__FC29AA2A_BA4B_4138_8B5C_93F1666B64DD__INCLUDED_)
#define AFX_OBJECTSPACE_H__FC29AA2A_BA4B_4138_8B5C_93F1666B64DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CObjectSpace  
{
public:
	LinkToTopObject (CObjectSpace &a_cObjectSpace);
	LinkToLeftObject (CObjectSpace &a_cObjectSpace);
	Resize ();
	InitState (CWnd &a_cDialog, CDialog &a_cParentDialog, CObjectSpace *a_cOS_Left, CObjectSpace *a_cOS_Top, double a_fWidth, double a_fHeight, int *a_pDeltaY = NULL);
	CObjectSpace();
	virtual ~CObjectSpace();

	CWnd *m_pWnd;
	CWnd *m_pParentWnd;
	int m_iOrigX;
	int m_iOrigY;
	int m_iOrigWidth;
	int m_iOrigHeight;

	int m_iLeftMargin;
	int m_iRightMargin;
	int m_iTopMargin;
	int m_iBottomMargin;

	int m_iCurOrigX;
	int m_iCurOrigY;
	int m_iCurWidth;
	int m_iCurHeight;

	int m_iParentWidth;
	int m_iParentHeight;

	double m_fPercentageWidth;
	double m_fPercentageHeight;

	CObjectSpace *m_pLeftObjectLink;
	CObjectSpace *m_pTopObjectLink;

	int *m_pDeltaY;
};

#endif // !defined(AFX_OBJECTSPACE_H__FC29AA2A_BA4B_4138_8B5C_93F1666B64DD__INCLUDED_)
