#if !defined(AFX_UPDATEDIALOG_H__27C3E712_C740_4671_8FD0_8C2396606CA5__INCLUDED_)
#define AFX_UPDATEDIALOG_H__27C3E712_C740_4671_8FD0_8C2396606CA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UpdateDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUpdateDialog dialog

#include "XMLParser.h"
#include "FileItem.h"
#include "wininet.h"
#include "ItemInfo.h"	// Added by ClassView
#include "databaserelease.h"

class CUpdateDialog : public CDialog
{
// Construction
public:
	INTERNET_PORT GetServiceType (CString &a_csURL);
	SplitURL (CString a_csURL, CString &a_csServer, CString &a_csPath);
	ClearReleaseInfo();
	MoveFolder (CString a_csSource, CString a_csDest, bool a_bVerbose = true);
	bool OpenArchive(CString &a_csFile, CString &a_csDest);
	ExtractArchive();
	ShowDownload();
	ShowRelease();
	PrepareDownloadForDatabase();
	PrepareDownloadForReleases();
	PrepareDownloadForConfig();
	bool FindNewerUpdate();
	DeleteFolder (CString a_csFolder, bool a_bDeleteFolder = false);
	CalculateBytesRead();
	UpdateReleaseInfo();
	Report (CString &a_csMsg);
	UpdateServerList();
	DetermineNextAction();
	bool ReadReleaseFile(CString &a_csFilename);
	bool ReadConfigFiles(CString &a_csPath);
	bool ReadConfigFile(CString &a_csFilename);
	ClearServerList();
	ClearReleaseList();
	ClearDownloadList();
	CFileItem *GetNextDownload();
	EndDownload();
	bool StartDownload();
	EndConnection();
	bool StartConnection();
	CUpdateDialog(CWnd* pParent = NULL);   // standard constructor

	int m_iDownloadType;
	bool m_bDownloading;
	CList <CDatabaseRelease,CDatabaseRelease&> m_clDatabaseReleaseList;
	CTypedPtrList <CPtrList, CFileItem*> m_clDownloadList;

	HINTERNET m_cInternetHandle;
	HINTERNET m_cInternetConnect;
	HINTERNET m_cHTTPHandle;
	FILE *m_cpFile;
	CFileItem *m_cpCurrentFileItem;
	char m_cBuffer[16384];
	int m_iBytesRead;
	int m_iBytesReadSoFar;
	int m_iBytesToRead;
	int m_iTimerId;
	CString m_csServerAddress;

	CMapStringToString m_clServerMap;
	CDatabaseRelease m_cLatestDatabaseRelease;

// Dialog Data
	//{{AFX_DATA(CUpdateDialog)
	enum { IDD = IDD_UPDATEDIALOG };
	CStatic	m_cVersionComment;
	CStatic	m_cClientComment;
	CComboBox	m_cServerList;
	CButton	m_cCloseButton;
	CEdit	m_cTitle;
	CProgressCtrl	m_cStatusProgressTotal;
	CStatic	m_cClientVersion;
	CStatic	m_cRevision;
	CStatic	m_cCurrentFile;
	CButton	m_cSearchButton;
	CButton	m_cUpdateButton;
	CListCtrl	m_cArchiveList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUpdateDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUpdateDialog)
	afx_msg void OnCreatebutton();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCancelMode();
	afx_msg void OnSearchbutton();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClose();
	afx_msg void OnUpdatebutton();
	afx_msg void OnClosebutton();
	afx_msg void OnSelchangeServerlist();
	afx_msg void OnHelpHelpwithupdates();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UPDATEDIALOG_H__27C3E712_C740_4671_8FD0_8C2396606CA5__INCLUDED_)
