// UpdateDialog.cpp : implementation file
//

#include "stdafx.h"
#include "HCC.h"
#include "UpdateDialog.h"
#include "AppData.h"
#include "XMLParser.h"
#include "XMLTag.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DownloadType_None 0
#define DownloadType_Config 1
#define DownloadType_Release 2
#define DownloadType_Zip 3

#define DownloadBuffer 4096

#include "unzip/structs.h"
#include "unzip/unzip.h"
#include "unzip/unzvers.h"
#include "unzip/decs.h"

int WINAPI UNZIP32_Print(LPSTR, unsigned long);
int WINAPI UNZIP32_Replace(LPSTR);
int WINAPI UNZIP32_Password(LPSTR, int, LPCSTR, LPCSTR);
void WINAPI UNZIP32_SendApplicationMessage(unsigned long, unsigned long, unsigned,
	 unsigned, unsigned, unsigned, unsigned, unsigned,
	 char, LPSTR, LPSTR, unsigned long, char);
int WINAPI UNZIP32_ServCallBk(LPCSTR , unsigned long);

/*************************************************************************************************/
/*                                   UNZIP32.DLL UNZIP32_ServCallBkS                                       */
/*************************************************************************************************/

int WINAPI UNZIP32_Replace(LPSTR filename)
{
	return 103;
}

void WINAPI UNZIP32_SendApplicationMessage(unsigned long ucsize, unsigned long csiz,
    unsigned cfactor,
    unsigned mo, unsigned dy, unsigned yr, unsigned hh, unsigned mm,
    char c, LPSTR filename, LPSTR methbuf, unsigned long crc, char fCrypt)
{
}

int WINAPI UNZIP32_Password(LPSTR p, int n, LPCSTR m, LPCSTR name)
{
	return 0;
}

int WINAPI UNZIP32_Print(LPSTR buf, unsigned long size)
{
	const CString func_name = "unzip32.dll";
	CString l_csStr;

	l_csStr = buf;
	l_csStr.Remove ('\n');
	l_csStr.TrimLeft ();
	l_csStr.TrimRight ();

	if (l_csStr.IsEmpty () == false)
	{
	}
	return 0;
}

int WINAPI UNZIP32_ServCallBk(LPCSTR buf, unsigned long size)
{
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CUpdateDialog dialog


CUpdateDialog::CUpdateDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CUpdateDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUpdateDialog)
	//}}AFX_DATA_INIT
	m_iDownloadType = DownloadType_None;
	m_bDownloading = false;
	m_clDownloadList.RemoveAll();
	m_cpCurrentFileItem = NULL;
	m_iBytesToRead = 0;
	m_iBytesRead = 0;
	m_iBytesReadSoFar = 0;
}


void CUpdateDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUpdateDialog)
	DDX_Control(pDX, IDC_VERSIONCOMMENT, m_cVersionComment);
	DDX_Control(pDX, IDC_CLIENTCOMMENT, m_cClientComment);
	DDX_Control(pDX, IDC_SERVERLIST, m_cServerList);
	DDX_Control(pDX, IDC_CLOSEBUTTON, m_cCloseButton);
	DDX_Control(pDX, IDC_TITLE, m_cTitle);
	DDX_Control(pDX, IDC_STATUSPROGRESSTOTAL, m_cStatusProgressTotal);
	DDX_Control(pDX, IDC_CLIENTVERSION, m_cClientVersion);
	DDX_Control(pDX, IDC_REVISION, m_cRevision);
	DDX_Control(pDX, IDC_CURRENTFILE, m_cCurrentFile);
	DDX_Control(pDX, IDC_SEARCHBUTTON, m_cSearchButton);
	DDX_Control(pDX, IDC_UPDATEBUTTON, m_cUpdateButton);
	DDX_Control(pDX, IDC_ARCHIVELIST, m_cArchiveList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUpdateDialog, CDialog)
	//{{AFX_MSG_MAP(CUpdateDialog)
	ON_BN_CLICKED(IDC_CREATEBUTTON, OnCreatebutton)
	ON_WM_TIMER()
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_SEARCHBUTTON, OnSearchbutton)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_UPDATEBUTTON, OnUpdatebutton)
	ON_BN_CLICKED(IDC_CLOSEBUTTON, OnClosebutton)
	ON_CBN_SELCHANGE(IDC_SERVERLIST, OnSelchangeServerlist)
	ON_COMMAND(ID_HELP_HELPWITHUPDATES, OnHelpHelpwithupdates)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUpdateDialog message handlers

void CUpdateDialog::OnCreatebutton()
{

}

void CUpdateDialog::OnTimer(UINT nIDEvent)
{
	unsigned long l_iBytesRead;
	CString l_csStr;

	if (m_bDownloading)
	{
		if (InternetReadFile (m_cHTTPHandle, &m_cBuffer, DownloadBuffer, &l_iBytesRead))
		{
			if (l_iBytesRead > 0)
			{
				m_iBytesRead += l_iBytesRead;
				fwrite (m_cBuffer, l_iBytesRead, 1, m_cpFile);

				if (m_cpCurrentFileItem->m_iSize)
				{
					l_csStr.Format ("%s (%d/%d bytes)", m_cpCurrentFileItem->m_csSaveName, m_iBytesReadSoFar + m_iBytesRead, m_cpCurrentFileItem->m_iSize);
				}
				else
				{
					l_csStr.Format ("%s (%d bytes)", m_cpCurrentFileItem->m_csSaveName, m_iBytesReadSoFar + m_iBytesRead);
				}

				m_cStatusProgressTotal.SetPos (m_iBytesReadSoFar + m_iBytesRead);
				m_cCurrentFile.SetWindowText (l_csStr);
			}
			else
			{
				m_cpCurrentFileItem->m_iResult = FileItem_Downloaded;
				EndDownload ();
				m_cpCurrentFileItem = GetNextDownload ();

				if (m_cpCurrentFileItem == NULL)
				{
			  		KillTimer (m_iTimerId);
					DetermineNextAction();
				}
				else
				{
					StartDownload();
				}
			}
		}
		else
		{
			DWORD l_iError = GetLastError ();
		}
	}

	CDialog::OnTimer(nIDEvent);
}

void CUpdateDialog::OnCancelMode()
{
	CDialog::OnCancelMode();

	// TODO: Add your message handler code here
	ClearDownloadList	();
}

bool CUpdateDialog::StartConnection()
{
	if (InternetAttemptConnect (0) == ERROR_SUCCESS )
	{
		m_cInternetHandle = InternetOpen ("HCC/" + cAppData_Version, INTERNET_OPEN_TYPE_PRECONFIG_WITH_NO_AUTOPROXY, NULL, NULL, 0);
		if (m_cInternetHandle != NULL)
		{
			return (TRUE);
		}
	}

	return (FALSE);
}

CUpdateDialog::EndConnection()
{
	InternetCloseHandle (m_cInternetHandle);
}

bool CUpdateDialog::StartDownload()
{
	CString l_csServerName;
	CString l_csPath;

	if (!m_bDownloading)
	{
		m_cpCurrentFileItem = GetNextDownload ();
		if (m_cpCurrentFileItem == NULL)
		{
			return (false);
		}

		m_bDownloading = true;
		m_iTimerId = SetTimer (1, 25,  NULL);
		m_cCloseButton.SetWindowText ("Abort");
	}

	CalculateBytesRead ();

	CString l_csFile = m_cpCurrentFileItem->m_csSaveName;
	Report ("Downloading " + l_csFile + "...");
	m_cCurrentFile.SetWindowText (l_csFile);

	SplitURL ( m_cpCurrentFileItem->m_csFile, l_csServerName, l_csPath);

	m_cInternetConnect = InternetConnect (m_cInternetHandle, l_csServerName, GetServiceType (m_cpCurrentFileItem->m_csFile), NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
	if (m_cInternetConnect)
	{
		m_cHTTPHandle = HttpOpenRequest (m_cInternetConnect, "GET", l_csPath, NULL, NULL,  (const char**)"*/*\0",
													 INTERNET_FLAG_DONT_CACHE   , 0);
		if (m_cHTTPHandle)
		{
			char l_cBuffer[256];
			DWORD l_iBufferLength = 256;
			DWORD l_iIndex = 0;

			if (HttpSendRequest (m_cHTTPHandle, NULL, 0, NULL, 0))
			{
				if (HttpQueryInfo (m_cHTTPHandle, HTTP_QUERY_CONTENT_LENGTH  , l_cBuffer, &l_iBufferLength, &l_iIndex))
				{
					m_cpCurrentFileItem->m_iSize = atoi (l_cBuffer);
				}
				else
				{
					DWORD l_iError = GetLastError ();
					m_cpCurrentFileItem->m_iSize = 0;
				}

				m_cStatusProgressTotal.SetRange32 (0, m_cpCurrentFileItem->m_iSize);

				if ((m_cpFile = fopen (m_cpCurrentFileItem->m_csSaveName, "wb")) != 0)
				{
					m_iBytesRead = 0;
					return (true);
				}
				else
				{
					InternetCloseHandle (m_cHTTPHandle);
					InternetCloseHandle (m_cInternetConnect);
					m_cpCurrentFileItem->m_iResult = FileItem_Failed;
					m_cpCurrentFileItem = GetNextDownload ();
				}
			}
			else
			{
				InternetCloseHandle (m_cHTTPHandle);
				InternetCloseHandle (m_cInternetConnect);
				DWORD l_iError = GetLastError ();
				m_cpCurrentFileItem->m_iResult = FileItem_Failed;
				m_cpCurrentFileItem = GetNextDownload ();
			}
		}
		else
		{
			InternetCloseHandle (m_cInternetConnect);
			DWORD l_iError = GetLastError ();
			m_cpCurrentFileItem->m_iResult = FileItem_Failed;
			m_cpCurrentFileItem = GetNextDownload ();
		}
	}
	else
	{
		DWORD l_iError = GetLastError ();
		m_cpCurrentFileItem->m_iResult = FileItem_Failed;
		m_cpCurrentFileItem = GetNextDownload ();
	}

	AfxMessageBox ("Unable to access the update server");
	return (false);
}

CUpdateDialog::EndDownload()
{
	if (m_cHTTPHandle)
	{
		fclose (m_cpFile);
		InternetCloseHandle (m_cHTTPHandle);
	}
}

CFileItem *CUpdateDialog::GetNextDownload()
{
	CFileItem *l_cpFileItem;
	POSITION l_Pos;

	l_Pos = m_clDownloadList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpFileItem = m_clDownloadList.GetNext (l_Pos);
		if (l_cpFileItem == m_cpCurrentFileItem)
		{
			if (l_Pos)
			{
				return (m_clDownloadList.GetNext (l_Pos));
			}
		}
		else
		{
			if (m_cpCurrentFileItem == NULL)
			{
				return (l_cpFileItem);
			}
		}
	}

	m_bDownloading = false;
	return (NULL);
}

CUpdateDialog::ClearDownloadList()
{
	POSITION l_Pos;
	CFileItem *l_cpFileItem;

	l_Pos = m_clDownloadList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpFileItem = m_clDownloadList.GetNext (l_Pos);
		delete (l_cpFileItem);
	}

	m_clDownloadList.RemoveAll ();
}

CUpdateDialog::ClearReleaseList()
{
	m_clDatabaseReleaseList.RemoveAll ();
}

CUpdateDialog::ClearServerList()
{
	m_clServerMap.RemoveAll ();
}

void CUpdateDialog::OnSearchbutton()
{
	m_cArchiveList.DeleteAllItems ();
	PrepareDownloadForConfig ();
	ShowRelease ();
}

BOOL CUpdateDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	StartConnection();

	m_cArchiveList.InsertColumn (0, "Change", LVCFMT_LEFT, 382, -1);
	m_cArchiveList.InsertColumn (1, "Author", LVCFMT_CENTER, 100 -1);

	ReadConfigFiles (CAppData::m_csAppBasePath);
	UpdateServerList ();

	m_cLatestDatabaseRelease.m_ctRevision = 0;
	ShowRelease();
	m_cTitle.SetWindowText ("Database Information");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUpdateDialog::OnOK()
{
	EndConnection ();

	CDialog::OnOK();
}

void CUpdateDialog::OnClose()
{
	KillTimer (m_iTimerId);
	EndConnection ();

	ClearDownloadList();
	ClearReleaseList();
	ClearServerList ();

	CDialog::OnClose();
}

bool CUpdateDialog::ReadConfigFiles(CString &a_csPath)
{
	bool l_bResult = true;
	bool l_bAdded = false;
	bool l_bSearching;
	CFileFind l_cFileFind;

	m_clServerMap.RemoveAll ();
	l_bSearching = (l_cFileFind.FindFile (a_csPath + cFile_App_ConfigMask) != 0);
	while (l_bSearching)
	{
		l_bSearching = (l_cFileFind.FindNextFile () != 0);

		if (!l_cFileFind.IsDirectory ())
		{
			l_bResult = l_bResult && ReadConfigFile (l_cFileFind.GetFilePath ());
		}
	}
	l_cFileFind.Close ();

	return (l_bResult);
}

bool CUpdateDialog::ReadConfigFile(CString &a_csFilename)
{
	bool l_bResult = false;
	XMLParser l_cParser;
	XMLTag l_cRootTag ("#ROOT#");
	XMLTag l_cConfigTag ("config");
	XMLTag l_cServersTag ("servers");
	CString l_csValue;
	CString l_cServerName;
	CString l_cServerAddress;

	l_cParser.OpenFile (a_csFilename);

	// Should be only one config Tag
	if (l_cConfigTag.GetNextTag (l_cParser, l_cRootTag))
	{
		if (l_cServersTag.GetNextTag (l_cParser, l_cConfigTag))
		{
			while (l_cServersTag.GetRepeatingDoubleTagValue (l_cParser, (CString) "server", l_cServerName, l_cServerAddress))
			{
				m_clServerMap.SetAt (l_cServerName, l_cServerAddress);
			}

			l_bResult = true;
		}

	}

	return (l_bResult);
}

bool CUpdateDialog::ReadReleaseFile(CString &a_csFilename)
{
	bool l_bResult = false;
	XMLParser l_cParser;
	XMLTag l_cRootTag ("#ROOT#");
	XMLTag l_cReleaseTag ("release");
	XMLTag l_cNotesTag ("release-notes");
	CString l_csAuthor;
	CString l_csNote;
	CString l_csRevision;
	CDatabaseRelease l_cDatabaseRelease;
	int l_iDay;
	int l_iMonth;
	int l_iYear;

	l_cParser.OpenFile (a_csFilename);

	// Should be only one release Tag
	m_clDatabaseReleaseList.RemoveAll ();
	if (l_cReleaseTag.GetNextTag (l_cParser, l_cRootTag))
	{
		l_cReleaseTag.GetTagValue (l_cParser, (CString) "release-databaserevision", l_csRevision );
		l_cReleaseTag.GetTagValue (l_cParser, (CString) "release-title", l_cDatabaseRelease.m_csTitle );
		l_cReleaseTag.GetTagValue (l_cParser, (CString) "release-minclientversion", l_cDatabaseRelease.m_csMinClientVersion );

		sscanf (l_csRevision, "%d-%d-%d", &l_iYear, &l_iMonth, &l_iDay);
		if (l_iYear < 2000)
		{
			l_iYear += 2000;
		}

		l_cDatabaseRelease.m_ctRevision = CTime::CTime (l_iYear, l_iMonth, l_iDay, 0, 0, 0);
		l_cDatabaseRelease.m_clNoteList.RemoveAll ();

		if (l_cNotesTag.GetNextTag (l_cParser, l_cReleaseTag))
		{
			while (l_cNotesTag.GetRepeatingDoubleTagValue (l_cParser, (CString) "note", l_csAuthor, l_csNote))
			{
				l_cDatabaseRelease.m_clNoteList.AddTail (l_csNote + "|" + l_csAuthor);
			}
		}

		m_clDatabaseReleaseList.AddTail (l_cDatabaseRelease);
		l_bResult = true;
	}

	return (l_bResult);
}

CUpdateDialog::DetermineNextAction()
{
	switch (m_iDownloadType)
	{
		case (DownloadType_None) :
		{
			break;
		}
		case (DownloadType_Config) :
		{
			CString l_csBackupConfigPath = CAppData::m_csAppBasePath + cFile_App_ConfigBackup;
			CString l_csTmpConfigPath = CAppData::m_csAppBasePath + cFile_App_ConfigDownload;
			CString l_csConfigPath = CAppData::m_csAppBasePath + cFile_App_Config;

			DeleteFile (l_csBackupConfigPath);
			MoveFile (l_csConfigPath, l_csBackupConfigPath);
			MoveFile (l_csTmpConfigPath, l_csConfigPath);
			DeleteFile (l_csTmpConfigPath);

			if (ReadConfigFile (l_csConfigPath))
			{
				UpdateServerList();
				PrepareDownloadForReleases ();
				DeleteFile (l_csBackupConfigPath);
			}
			else
			{
				ClearReleaseInfo ();
				DeleteFile (l_csConfigPath);
				MoveFile (l_csBackupConfigPath, l_csConfigPath);
				m_iDownloadType = DownloadType_None;
				m_cCloseButton.SetWindowText ("Close");
				m_cSearchButton.EnableWindow (true);
				m_cUpdateButton.EnableWindow (false);
				AfxMessageBox ("Unable to access this Site for update information. Please try again when it is available", MB_ICONSTOP);
			}

			break;
		}
		case (DownloadType_Release) :
		{
			CString l_csBackupReleasePath = CAppData::m_csAppBasePath + cFile_App_ReleasesBackup;
			CString l_csTmpReleasePath = CAppData::m_csAppBasePath + cFile_App_ReleasesDownload;
			CString l_csReleasePath = CAppData::m_csAppBasePath + cFile_App_Releases;

			DeleteFile (l_csBackupReleasePath);
			MoveFile (l_csReleasePath, l_csBackupReleasePath);
			MoveFile (l_csTmpReleasePath, l_csReleasePath);
			DeleteFile (l_csTmpReleasePath);

			m_iDownloadType = DownloadType_None;
			m_cCloseButton.SetWindowText ("Close");
			m_cSearchButton.EnableWindow (true);
			if (FindNewerUpdate ())
			{
				DeleteFile (l_csBackupReleasePath);
			}
			else
			{
				DeleteFile (l_csReleasePath);
				MoveFile (l_csBackupReleasePath, l_csReleasePath);
				m_iDownloadType = DownloadType_None;
				m_cCloseButton.SetWindowText ("Close");
				m_cSearchButton.EnableWindow (true);
				m_cUpdateButton.EnableWindow (false);
				AfxMessageBox ("Unable to access this Site for release information. Please try again when it is available", MB_ICONSTOP);
			}

			break;
		}
		case (DownloadType_Zip) :
		{
			m_cSearchButton.EnableWindow (true);
			m_iDownloadType = DownloadType_None;
			m_cCloseButton.SetWindowText ("Close");
			ExtractArchive ();
			break;
		}
		default :
		{
			break;
		}
	}
}

CUpdateDialog::UpdateServerList()
{
	POSITION l_Pos;
	CString l_csServer;
	CString l_csAddress;
	CString l_csOldServer;

	m_cServerList.GetWindowText (l_csOldServer);
	CAppData::ClearComboBox (m_cServerList);

	l_Pos = m_clServerMap.GetStartPosition ();
	while (l_Pos)
	{
		m_clServerMap.GetNextAssoc (l_Pos, l_csServer, l_csAddress);
		m_cServerList.AddString (l_csServer);
	}

	/*if (m_cServerList.GetCount () > 1)
	{
		m_cServerList.EnableWindow (true);
	}
	else
	{
		m_cServerList.EnableWindow (false);
	}*/

	if (l_csOldServer.IsEmpty ())
	{
		m_cServerList.SetCurSel (0);
	}
	else
	{
		m_cServerList.SelectString (-1, l_csOldServer);
	}
}

CUpdateDialog::Report(CString &a_csMsg)
{
	int l_iOffset = m_cArchiveList.GetItemCount ();
	m_cArchiveList.InsertItem (l_iOffset, a_csMsg);
	m_cArchiveList.EnsureVisible (l_iOffset, false);
	m_cArchiveList.Update (l_iOffset);
}

CUpdateDialog::UpdateReleaseInfo()
{
	POSITION l_Pos;
	CString l_csNote;
	int l_iPos;
	int l_iOffset = 0;
	CString l_csThisVersion;
	double l_fCurrentVersion = atof (cAppData_Version);
	double l_fLatestVersion = atof (m_cLatestDatabaseRelease.m_csMinClientVersion);

	l_csThisVersion = "HCC_" + CAppData::m_csDatabaseRevision + ".zip";

	m_cArchiveList.DeleteAllItems ();
	m_cArchiveList.DeleteColumn (0);
	m_cArchiveList.DeleteColumn (0);
	m_cArchiveList.InsertColumn (0, "Change", LVCFMT_LEFT, 370, -1);
	m_cArchiveList.InsertColumn (1, "Author", LVCFMT_CENTER, 90 -1);

	l_Pos = m_cLatestDatabaseRelease.m_clNoteList.GetHeadPosition ();
	while (l_Pos)
	{
		l_csNote = m_cLatestDatabaseRelease.m_clNoteList.GetNext (l_Pos);
		l_iPos = l_csNote.Find("|");
		m_cArchiveList.InsertItem (l_iOffset, l_csNote.Left (l_iPos));
		m_cArchiveList.SetItemText (l_iOffset, 1, l_csNote.Mid (l_iPos + 1));
		l_iOffset++;
	}

	m_cTitle.SetWindowText (m_cLatestDatabaseRelease.m_csTitle);

	m_cClientVersion.SetWindowText (" "+ m_cLatestDatabaseRelease.m_csMinClientVersion );
	if (l_fLatestVersion > l_fCurrentVersion)
	{
		m_cClientComment.SetWindowText ("Your client '" + cAppData_Version + "' cannot support this update!");
	}
	else
	{
		m_cClientComment.SetWindowText ("");
	}

	m_cRevision.SetWindowText (" "+ CAppData::GetDatabaseZipName (m_cLatestDatabaseRelease.m_ctRevision));
	if (l_csThisVersion == CAppData::GetDatabaseZipName (m_cLatestDatabaseRelease.m_ctRevision))
	{
		m_cUpdateButton.SetWindowText ("Re-download");
		m_cVersionComment.SetWindowText ("You have this database already");
	}
	else
	{
		m_cUpdateButton.SetWindowText ("Start Download");
		m_cVersionComment.SetWindowText ("This is a new database ready for downloading");
	}
}

void CUpdateDialog::OnUpdatebutton()
{
	CString l_csCurrentServer;
	CString l_csVersion;
	CString l_csClearPath = CAppData::m_csAppBasePath + cPath_App_Temp;
	bool l_bProceed = true;
	ULARGE_INTEGER l_iFreeToUser;
	ULARGE_INTEGER l_iFree;
	ULARGE_INTEGER l_iInUse;

	if (m_bDownloading == false)
	{
		if (GetDiskFreeSpaceEx (CAppData::m_csAppBasePath + cPath_App_Temp, &l_iFreeToUser, &l_iFree, &l_iInUse))
		{
			if (l_iFreeToUser.QuadPart < 12582912)
			{
				AfxMessageBox ("There is not enough space on the partition (where HCC is installed) to install the update.\nPlease free up some space (at least 12Mb) and retry", MB_ICONSTOP);
				l_bProceed = false;
			}
			else if (CAppData::m_clOrderList.GetCount () > 0)
			{
				if (AfxMessageBox ("In order to perform the update, the current order must be reset. Proceed?", MB_YESNO) == IDNO)
				{
					l_bProceed = false;
				}
			}
		}

		if (l_bProceed)
		{
			PrepareDownloadForDatabase ();
			ShowDownload ();
		}
	}
}

CUpdateDialog::CalculateBytesRead()
{
	POSITION l_Pos;
	CFileItem *l_cpFileItem;

	m_iBytesReadSoFar = 0;
	m_iBytesToRead = 0;

	l_Pos = m_clDownloadList.GetHeadPosition ();
	while (l_Pos)
	{
		l_cpFileItem = m_clDownloadList.GetNext (l_Pos);
		if (l_cpFileItem->m_iResult == FileItem_Downloaded)
		{
			m_iBytesReadSoFar += l_cpFileItem->m_iSize;
		}

		m_iBytesToRead += l_cpFileItem->m_iSize;
	}

}

CUpdateDialog::DeleteFolder(CString a_csFolder, bool a_bDeleteFolder)
{
	bool l_bSearching;
	CFileFind l_cFileFind;

	if (a_csFolder.IsEmpty () == false)
	{
		if (a_csFolder.Find (CAppData::m_csAppBasePath) >= 0)
		{
			l_bSearching = (l_cFileFind.FindFile (a_csFolder + "\\*.*") != 0);
			while (l_bSearching)
			{
				l_bSearching = (l_cFileFind.FindNextFile () != 0);

				if (l_cFileFind.IsDirectory ())
				{
					if (l_cFileFind.IsDots () == false)
					{
						// Delete sub-folders
						DeleteFolder (l_cFileFind.GetFilePath (), true);
					}
				}
				else
				{
					// Search for xml/png files
					//if ((l_cFileFind.GetFileName().Find (".xml") >= 0) ||
					//    (l_cFileFind.GetFileName().Find (".png") >= 0) ||
					//    (l_cFileFind.GetFileName().Find (".zip") >= 0))
					//{
						DeleteFile (l_cFileFind.GetFilePath ());
					//}
					//else
					//{
					//	Report ("Warning - Unexpected File '" + l_cFileFind.GetFileName() + "' found. Not deleting");
					//}
				}
			}

			l_cFileFind.Close ();

			if (a_bDeleteFolder)
			{
				RemoveDirectory (a_csFolder);
			}
		}
	}
}

bool CUpdateDialog::FindNewerUpdate()
{
	POSITION l_Pos;
	CDatabaseRelease l_cDatabaseRelease;
	bool l_bNewer = false;

	if (ReadReleaseFile (CAppData::m_csAppBasePath + cFile_App_Releases))
	{
		m_cLatestDatabaseRelease.m_ctRevision = 0;
		l_Pos = m_clDatabaseReleaseList.GetHeadPosition ();
		while (l_Pos)
		{
			l_cDatabaseRelease = m_clDatabaseReleaseList.GetNext (l_Pos);

			if (l_cDatabaseRelease.m_ctRevision > m_cLatestDatabaseRelease.m_ctRevision)
			{
				m_cLatestDatabaseRelease = l_cDatabaseRelease;
			}
		}

		l_bNewer = true;
	}

	if (l_bNewer)
	{
		double l_fCurrentVersion = atof (cAppData_Version);
		double l_fLatestVersion = atof (m_cLatestDatabaseRelease.m_csMinClientVersion);

		UpdateReleaseInfo ();

		if (l_fLatestVersion > l_fCurrentVersion)
		{
			m_cUpdateButton.EnableWindow (false);
			if (AfxMessageBox ("This version of HCC cannot support the latest database revision. Do you want to launch the HCC Client Upgrade page?", MB_ICONQUESTION|MB_YESNO) == IDYES)
			{
				CAppData::LaunchWebLink ((CString) "update");
			}
		}
		else
		{
			m_cUpdateButton.EnableWindow (true);
		}
	}

	return (l_bNewer);
}

CUpdateDialog::PrepareDownloadForConfig()
{
	CFileItem *l_cpFileItem;
	CString l_csCurrentServer;

	m_cServerList.GetWindowText (l_csCurrentServer);
	ClearDownloadList();
	if (m_clServerMap.Lookup (l_csCurrentServer, m_csServerAddress))
	{
		//Report ("Downloading from " + l_csCurrentServer + " site");
		l_cpFileItem = new CFileItem ();
		l_cpFileItem->m_csFile = m_csServerAddress + cFile_App_Config;
		l_cpFileItem->m_csSaveName = CAppData::m_csAppBasePath + cFile_App_ConfigDownload;
		m_clDownloadList.AddTail (l_cpFileItem);
		m_iDownloadType = DownloadType_Config;
		m_cSearchButton.EnableWindow (false);
		StartDownload ();
	}
}

CUpdateDialog::PrepareDownloadForReleases()
{
	CFileItem *l_cpFileItem;
	CString l_csCurrentServer;

	if (m_bDownloading == false)
	{
		ClearDownloadList();

		m_cServerList.GetWindowText (l_csCurrentServer);
		if (m_clServerMap.Lookup (l_csCurrentServer, m_csServerAddress))
		{
			//Report ("Downloading from " + l_csCurrentServer + " site");
			l_cpFileItem = new CFileItem ();
			l_cpFileItem->m_csFile = m_csServerAddress + cFile_App_Releases;
			l_cpFileItem->m_csSaveName = CAppData::m_csAppBasePath + cFile_App_ReleasesDownload;
			m_clDownloadList.AddTail (l_cpFileItem);
			m_iDownloadType = DownloadType_Release;
			m_cSearchButton.EnableWindow (false);
			StartDownload ();
		}
	}
}

CUpdateDialog::PrepareDownloadForDatabase()
{
	CString l_csVersion;
	CString l_csCurrentServer;
	CFileItem *l_cpFileItem;

	if (m_cLatestDatabaseRelease.m_ctRevision != 0)
	{
		m_cArchiveList.DeleteAllItems ();
		m_cArchiveList.DeleteColumn (0);
		m_cArchiveList.DeleteColumn (0);
		m_cArchiveList.InsertColumn (0, "Operation", LVCFMT_LEFT, 464, -1);

		ClearDownloadList();
		l_csVersion = CAppData::GetDatabaseZipName (m_cLatestDatabaseRelease.m_ctRevision);

		m_cServerList.GetWindowText (l_csCurrentServer);
		if (m_clServerMap.Lookup (l_csCurrentServer, m_csServerAddress))
		{
			//Report ("Downloading Database Revision '" + m_cLatestDatabaseRelease.m_ctRevision.Format ("%d-%m-%Y") + "' from " + l_csCurrentServer + " site");
			l_cpFileItem = new CFileItem ();
			l_cpFileItem->m_csFile = m_csServerAddress + "\\" + l_csVersion;
			l_cpFileItem->m_iSize = 0;
			l_cpFileItem->m_csSaveName = CAppData::m_csAppBasePath + cPath_App_Temp + "\\" + l_csVersion;
			l_cpFileItem->m_iResult = FileItem_Waiting;
			m_clDownloadList.AddTail (l_cpFileItem);
			m_iDownloadType = DownloadType_Zip;
			m_cSearchButton.EnableWindow (false);
			m_cUpdateButton.EnableWindow (false);
			StartDownload ();
		}
	}
}

CUpdateDialog::ShowRelease()
{
	m_cTitle.SetWindowText (m_cLatestDatabaseRelease.m_csTitle);
}

CUpdateDialog::ShowDownload()
{
}

CUpdateDialog::ExtractArchive()
{
	// Do unzip

	CString l_csArchiveFile = CAppData::m_csAppBasePath + cPath_App_Temp + "\\" + CAppData::GetDatabaseZipName(m_cLatestDatabaseRelease.m_ctRevision);
	CString l_csExtractPath = CAppData::m_csAppBasePath + cPath_App_TempArchive;
	CString l_csConfigPath = CAppData::m_csAppBasePath + cPath_App_Config;
	CString l_csCacheConfigPath = CAppData::m_csAppBasePath + cPath_App_Cache + cFile_App_ConfigCache;
	CString l_csCacheFormIconPath = CAppData::m_csAppBasePath + cPath_App_Cache + cFile_App_IconCache;

	DeleteFolder (l_csExtractPath, true);
	Report ((CString) "Extracting database archive...");
	if (OpenArchive (l_csArchiveFile, l_csExtractPath))
	{
		Report ((CString) "Extraction complete, starting installation...");
		BeginWaitCursor();
		DeleteFile (l_csCacheConfigPath);
		DeleteFile (l_csCacheFormIconPath);
		DeleteFolder (l_csConfigPath, true);
		MoveFolder (l_csExtractPath, l_csConfigPath);
		Report ((CString) "Installation complete, restarting database...");
		CAppData::Reinitialise (false);
		EndWaitCursor( );
		Report ((CString) "Configuration complete.");

		CAppData::m_csDatabaseRevision = m_cLatestDatabaseRelease.m_ctRevision.Format ("%Y-%m-%d");
		CAppData::UpdateDisplayedVersion ();
	}
	else
	{
		Report ((CString) "Update failed, database archive is corrupt");
	}
	DeleteFolder (l_csExtractPath, true);
	DeleteFile (l_csArchiveFile);
}

bool CUpdateDialog::OpenArchive(CString &a_csFile, CString &a_csDest)
{
	bool l_bResult = true;
	DCL l_cDCL;
	USERFUNCTIONS l_cUserFunctions;
	char l_cFileName[1024];
	char l_cDestinationPath[1024];
	int l_iArchiveReturnCode;

	// Copy to zip structure
	strcpy (l_cFileName, LPCTSTR (a_csFile));
	strcpy (l_cDestinationPath, LPCTSTR (a_csDest));

	l_cDCL.ncflag = 0; /* Write to stdout if true */
	l_cDCL.fQuiet = 0; /* We want all messages.
								 1 = fewer messages,
								 2 = no messages */
	l_cDCL.ntflag = 0; /* test zip file if true */
	l_cDCL.nvflag = 0; /* give a verbose listing if true */
	l_cDCL.nzflag = 0; /* display a zip file comment if true */
	l_cDCL.ndflag = 1; /* Recreate directories != 0, skip "../" if < 2 */
	l_cDCL.naflag = 0; /* Do not convert CR to CRLF */
	l_cDCL.nfflag = 0; /* Do not freshen existing files only */
	l_cDCL.noflag = 0; /* Over-write all files if true */
	l_cDCL.nZIflag = 0;
	l_cDCL.C_flag = 0;
	l_cDCL.fPrivilege = 0;
	l_cDCL.ExtractOnlyNewer = 0; /* Do not extract only newer */
	l_cDCL.SpaceToUnderscore = 0;
	l_cDCL.PromptToOverwrite = 1; /* "Overwrite all" selected -> no query mode */
	l_cDCL.lpszZipFN = l_cFileName; /* The archive name */
	l_cDCL.lpszExtractDir = l_cDestinationPath; /* The directory to extract to. This is set */

	l_cUserFunctions.print = UNZIP32_Print;
	l_cUserFunctions.sound = NULL;
	l_cUserFunctions.replace = UNZIP32_Replace;
	l_cUserFunctions.password = UNZIP32_Password;
	l_cUserFunctions.SendApplicationMessage = UNZIP32_SendApplicationMessage;
	l_cUserFunctions.ServCallBk = UNZIP32_ServCallBk;
	l_cUserFunctions.TotalSizeComp = 0;
	l_cUserFunctions.TotalSize = 0;
	l_cUserFunctions.CompFactor = 0;
	l_cUserFunctions.NumMembers = 0;
	l_cUserFunctions.cchComment = 0;

	l_iArchiveReturnCode = Wiz_SingleEntryUnzip (0, NULL, 0, NULL, &l_cDCL, &l_cUserFunctions);

	if (l_iArchiveReturnCode != 0)
	{
		l_bResult = false;
	}

	return (l_bResult);
}

CUpdateDialog::MoveFolder(CString a_csSource, CString a_csDest, bool a_bVerbose)
{
	bool l_bSearching;
	CFileFind l_cFileFind;

	if (a_csSource.IsEmpty () == false)
	{
		// Make sure destination exists
		CreateDirectory (a_csDest, NULL);

		l_bSearching = (l_cFileFind.FindFile (a_csSource + "\\*.*") != 0);
		while (l_bSearching)
		{
			l_bSearching = (l_cFileFind.FindNextFile () != 0);

			if (l_cFileFind.IsDirectory ())
			{
				if (l_cFileFind.IsDots () == false)
				{
					// move sub-folders
					MoveFolder (a_csSource + "\\" + l_cFileFind.GetFileName (), a_csDest + "\\" + l_cFileFind.GetFileName (), a_bVerbose);
				}
			}
			else
			{
				// Search for xml/png files
				if ((l_cFileFind.GetFileName().Find (".xml") >= 0) ||
				    (l_cFileFind.GetFileName().Find (".tif") >= 0) ||
				    (l_cFileFind.GetFileName().Find (".png") >= 0) ||
				    (l_cFileFind.GetFileName().Find (".zip") >= 0))
				{
					CString l_csBasePath = CAppData::m_csAppBasePath + cPath_App_TempArchive;
					CString l_csMsg;

					l_csMsg = a_csSource.Right (a_csSource.GetLength () - l_csBasePath.GetLength ()) + "\\" + l_cFileFind.GetFileName ();

					if (a_bVerbose)
					{
						Report ("Moving '" + l_csMsg + "'...");
					}

					MoveFile (a_csSource + "\\" + l_cFileFind.GetFileName (), a_csDest + "\\" + l_cFileFind.GetFileName ());
				}
				else
				{
					if (a_bVerbose)
					{
						Report ("Warning - Unexpected File '" + l_cFileFind.GetFileName() + "' found. This file will be deleted.");
					}
				}
			}
		}

		l_cFileFind.Close ();

	}
}

void CUpdateDialog::OnClosebutton()
{
	KillTimer (m_iTimerId);
	EndConnection ();

	ClearDownloadList();
	ClearReleaseList();
	ClearServerList ();

	CDialog::OnOK();
}

CUpdateDialog::ClearReleaseInfo()
{
	m_cArchiveList.DeleteAllItems ();
	m_cRevision.SetWindowText ("");
	m_cClientVersion.SetWindowText ("");
	m_cTitle.SetWindowText ("Database Information");
	m_cClientComment.SetWindowText ("");
	m_cVersionComment.SetWindowText ("");
}

void CUpdateDialog::OnSelchangeServerlist()
{
	ClearReleaseInfo ();
	m_cUpdateButton.EnableWindow (false);
}

CUpdateDialog::SplitURL(CString a_csURL, CString &a_csServer, CString &a_csPath)
{
	int l_iOffset;

	a_csURL.Replace ("http://", "");
	a_csURL.Replace ("https://", "");
	l_iOffset = a_csURL.Find ('/');
	if (l_iOffset >= 0)
	{
		a_csServer = a_csURL.Left (l_iOffset);
		a_csPath = a_csURL.Mid (l_iOffset + 1);
		a_csPath.Replace ("//", "/");
	}
	else
	{
		a_csServer.Empty ();
		a_csPath.Empty ();
	}
}

INTERNET_PORT CUpdateDialog::GetServiceType(CString &a_csURL)
{
	if (a_csURL.Left(7) == "http://")
	{
		return (INTERNET_DEFAULT_HTTP_PORT);
	}

	if (a_csURL.Left(8) == "https://")
	{
		return (INTERNET_DEFAULT_HTTPS_PORT);
	}

	return (INTERNET_DEFAULT_HTTP_PORT);
}

void CUpdateDialog::OnHelpHelpwithupdates()
{
	CAppData::LaunchWebLink ((CString) "updatewindow");
}

BOOL CUpdateDialog::OnHelpInfo(HELPINFO* pHelpInfo)
{
	return (TRUE);
}
