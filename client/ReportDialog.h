//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_REPORTDIALOG_H__5B673CD2_9E8A_48E6_90D1_EB5BF89ABE7B__INCLUDED_)
#define AFX_REPORTDIALOG_H__5B673CD2_9E8A_48E6_90D1_EB5BF89ABE7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportDialog.h : header file
//

#include "WindowState.h"
#include "ObjectSpace.h"
#include "ItemResource.h"
#include "Effect.h"

/////////////////////////////////////////////////////////////////////////////
// CReportDialog dialog

class CReportDialog : public CDialog
{
// Construction
public:
	GenerateBonusFromList(int a_iQty, CTypedPtrList<CPtrList, CEffect*>	&a_clEffectsList, CTypedPtrList<CPtrList,  CItemResource*> &a_clResourceList);
	DetermineIndirectBonus(CString a_csBonusName, int a_iAmount, CTypedPtrList<CPtrList,  CItemResource*> &a_clResourceList);
	bool IsComponent (int a_iRow, CString &a_csName, int &a_Min, int &a_iMax, bool &a_bSubComp);
	UpdateComponentCounts();
	SortResources (CTypedPtrList<CPtrList,  CItemResource*> &l_clResourceList, int a_iMode);
	ConvertToBaseResources (CTypedPtrList<CPtrList,  CItemResource*> &l_clResourceList);
	AddToBaseResources (CItemResource *a_cpItemResource, int a_iBaseQty, CTypedPtrList<CPtrList,  CItemResource*> &l_clBaseResourceList, int a_iSkillAdjust = 0);
	AddToResources(CItemResource *a_cpResource, int a_iStyle, int a_iBaseQty, int a_iIndent = 1, int a_iSkillAdjust = 0);
	int ReportSelection ();
	ResetSelection ();
	UpdateOrderMenu();
	GenerateDirectReport ();
	GenerateOrderList();
	GenerateResourceList ();
	GenerateBonusList();
	CReportDialog(CWnd* pParent = NULL);   // standard constructor
	void Resize();

	CString PrepareExportToTEXT();
	bool ExportToXML(CString a_csFilename);
	bool ExportToTEXT(CString a_csFilename);
    bool ExportToHTML(CString a_csFilename);
    ExportHTMLItemLine(FILE *a_cFilePtr, CString &a_csItemName, CString &a_csQty, CString &a_csTech, bool &a_bEven);
	ExportHTMLHeader(FILE *a_cFilePtr);
	ExportHTMLFooter(FILE *a_cFilePtr);
	ExportHTMLOrderHeader(FILE *a_cFilePtr);
	ExportHTMLLineFooter(FILE *a_cFilePtr);
	ExportHTMLResourceHeader(FILE *a_cFilePtr);
	ExportHTMLResourceFooter(FILE *a_cFilePtr);
	ExportHTMLResourceLine(FILE *a_cFilePtr, CString &m_csResourceName, CString &a_csQty, CString &a_csEff, bool &a_bEven);
	ExportHTMLBonusHeader(FILE *a_cFilePtr);
	ExportHTMLBonusFooter(FILE *a_cFilePtr);

	StartEditCell();
	EndEditCell();

	CObjectSpace m_cOS_ReportGrid;
	CObjectSpace m_cOS_GenerateButton;

	StartUp();
	CWindowState m_cWindowState;

	int m_iReportGridEditRow;
	int m_iReportGridEditCol;
// Dialog Data
	//{{AFX_DATA(CReportDialog)
	enum { IDD = IDD_REPORTDIALOG };
	CSpinButtonCtrl	m_cQtySpin;
	CComboBox	m_cReportType;
	CComboBox	m_cReportFormat;
	CButton	m_cGenerateButton;
	CMSFlexGrid	m_cReportGrid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReportDialog)
	afx_msg void OnWindowPosChanging( WINDOWPOS* lpwndpos );
	afx_msg void OnGeneratebutton();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo (MINMAXINFO* lpMMI) ;
	afx_msg void OnClose();
	virtual void OnOK();
	afx_msg void OnOptionsSnapshotwindow();
	afx_msg void OnOptionsRestorewindow();
	afx_msg void OnOptionsOrderbyResourcetype();
	afx_msg void OnOptionsOrderbyQuantity();
	afx_msg void OnHelpIndex();
	afx_msg void OnOptionsResourcebreakdownShowformularesource();
	afx_msg void OnOptionsShowsubcomponents();
	afx_msg void OnOptionsShowbaseresource();
	afx_msg void OnEnterCellReportgrid();
	afx_msg void OnLeaveCellReportgrid();
	afx_msg void OnMouseMoveReportgrid(short Button, short Shift, long x, long y);
	afx_msg void OnScrollReportgrid();
	afx_msg void OnDeltaposQtyspin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickReportgrid();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnWindowAlwaysontop();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnSelchangeReporttype();
	afx_msg void OnOptionsBonusesDirectonly();
	afx_msg void OnOptionsBonusesAll();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTDIALOG_H__5B673CD2_9E8A_48E6_90D1_EB5BF89ABE7B__INCLUDED_)
