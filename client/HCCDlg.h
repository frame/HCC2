// HCCDlg.h : header file
//
//{{AFX_INCLUDES()
//}}AFX_INCLUDES

#if !defined(AFX_HCCDLG_H__F9CBB5A7_35EE_4163_9287_DD3D890A857D__INCLUDED_)
#define AFX_HCCDLG_H__F9CBB5A7_35EE_4163_9287_DD3D890A857D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHCCDlg dialog

#include "WindowState.h"
#include "wininet.h"

class CHCCDlg : public CDialog
{
// Construction
public:
	UpdateToolBarMenu();
	ArrangeToolBar ();
	DockWndToBar (CWnd &a_cWnd);
	StickButtonBelow (CWnd &a_cTopWnd, CWnd &a_cWnd);
	CHCCDlg(CWnd* pParent = NULL);	// standard constructor


	CWindowState m_cWindowState;
	ATOM m_nHotKeyID_Orders;
	ATOM m_nHotKeyID_Forms;
	ATOM m_nHotKeyID_Techs;
	ATOM m_nHotKeyID_Comps;
	ATOM m_nHotKeyID_Reports;
	ATOM m_nHotKeyID_Updates;
	ATOM m_nHotKeyID_Profiles;
	ATOM m_nHotKeyID_App;

	CWnd *m_cpDockWnd;
	bool l_bRestored;
	CRect m_cOrigWnd;
	CRect m_cOrigClientWnd;

	// Dialog Data
	//{{AFX_DATA(CHCCDlg)
	enum { IDD = IDD_HCC_DIALOG };
	CStatic	m_cOrdersHeader;
	CStatic	m_cOnlineHeader;
	CStatic	m_cDatabaseHeader;
	CButtonST	m_cSubmitOrder;
	CButton	m_cAutoDock;
	CButtonST	m_cOrderButton;
	CButton	m_cTitleFrame;
	CStatic	m_cDatabaseTitle;
	CButtonST	m_cCompButton;
	CButtonST	m_cProfileButton;
	CButtonST	m_cReportButton;
	CButtonST	m_cUpdateButton;
	CButtonST	m_cWizardButton;
	CButtonST	m_cCrafterSearch;
	CButtonST	m_cTechButton;
	CButtonST	m_cFormButton;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHCCDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHCCDlg)
	afx_msg void OnWindowPosChanging( WINDOWPOS* lpwndpos );
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnViewItems();
	afx_msg void OnViewTechniques();
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSettingsOptions();
	afx_msg void OnFormbutton();
	afx_msg void OnTechbutton();
	afx_msg void OnCraftersearch();
	virtual void OnOK();
	virtual void OnCancel();
	CString ReadConfigFile();
	afx_msg void OnSettingsOrderwindowSnapshotwindow();
	afx_msg void OnSettingsOrderwindowRestoredefaults();
	afx_msg void OnSettingsAllwindowsSnapshotwindows();
	afx_msg void OnSettingsAllwindowsRestorealldefaults();
	afx_msg void OnViewComponents();
	afx_msg void OnViewReports();
	afx_msg void OnWizardbutton();
	afx_msg void OnCompbutton();
	afx_msg void OnReportbutton();
	afx_msg void OnProfilebutton();
	afx_msg void OnUpdatebutton();
	afx_msg void OnSettingsReloaddata();
	afx_msg void OnHelpIndex();
	afx_msg void OnSettingsFormulawindowSnapshotwindow();
	afx_msg void OnSettingsFormulawindowRestoredefaults();
	afx_msg void OnSettingsTechniquewindowSnapshotwindow();
	afx_msg void OnSettingsTechniquewindowRestoredefaults();
	afx_msg void OnSettingsCompwindowSnapshotwindow();
	afx_msg void OnSettingsCompwindowRestoredefaults();
	afx_msg void OnSettingsReportwindowSnapshotwindow();
	afx_msg void OnSettingsReportwindowRestoredefaults();
	afx_msg void OnSettingsProfilewindowSnapshotwindow();
	afx_msg void OnSettingsProfilewindowRestoredefaults();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg LRESULT  OnHotKey(WPARAM wp, LPARAM) ;
	afx_msg void OnViewFormulawindow();
	afx_msg void OnViewTechniquewindow();
	afx_msg void OnViewComponentwindow();
	afx_msg void OnViewReportwindow();
	afx_msg void OnViewProfilewindow();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSettingsWindowToolbarwindowSnapshotwindow();
	afx_msg void OnSettingsToolbarwindowRestoredefaults();
	afx_msg void OnOrderbutton();
	afx_msg void OnSettingsViewOrderwindow();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnSearchByname();
	afx_msg void OnSearchByFormname();
	afx_msg void OnSearchByclass();
	afx_msg void OnAutodock();
	afx_msg void OnWindowAlwaysontop();
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveas();
	afx_msg void OnFileExit();
	afx_msg void OnFilePrint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnHelpOnelinemanual();
	afx_msg void OnHelpPlugins();
	afx_msg void OnHelpReportabug();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnOptionsViewLiveupdate();
	afx_msg void OnOptionsSettingsRefreshtheme();
	afx_msg void OnOptionsOrientationHorizontal();
	afx_msg void OnOptionsOrientationVertical();
	afx_msg void OnHelpAbout();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HCCDLG_H__F9CBB5A7_35EE_4163_9287_DD3D890A857D__INCLUDED_)
