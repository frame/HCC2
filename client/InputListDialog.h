#if !defined(AFX_INPUTLISTDIALOG_H__21C41220_0F12_47BE_8392_DAC7F9881CE5__INCLUDED_)
#define AFX_INPUTLISTDIALOG_H__21C41220_0F12_47BE_8392_DAC7F9881CE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputListDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInputListDialog dialog

class CInputListDialog : public CDialog
{
// Construction
public:
	CInputListDialog(CWnd* pParent = NULL);   // standard constructor
	CStringList m_csInputList;
	CString m_csInputMsg;
	CString m_csTitleMsg;
	CString m_csSelectedInput;

// Dialog Data
	//{{AFX_DATA(CInputListDialog)
	enum { IDD = IDD_INPUTLISTDIALOG };
	CComboBox	m_cInputCombo;
	CStatic	m_cInputMsg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInputListDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInputListDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTLISTDIALOG_H__21C41220_0F12_47BE_8392_DAC7F9881CE5__INCLUDED_)
