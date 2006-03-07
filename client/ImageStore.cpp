// ImageStore.cpp: implementation of the CImageStore class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HCC.h"
#include "ImageStore.h"
#include "AppData.h"

using namespace Gdiplus;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImageStore::CImageStore()
{
	m_iSize = CAppData::m_iIconSize;

	Initialise();
}

CImageStore::~CImageStore()
{
	Initialise();
}

CImageStore::Initialise()
{
	m_cImageList.DeleteImageList ();
	m_cImageNameList.RemoveAll ();

	m_cImageList.Create (m_iSize, m_iSize, ILC_COLOR32, 256, 64);
	m_cImageList.SetBkColor (CLR_NONE);
}

bool CImageStore::LoadFromDirectory(CString &a_csPath, bool a_bClear)
{
	bool l_bSearching;
	CFileFind l_cFileFind;
	unsigned short l_cFilename[4096];
	CString l_csIconName;
	int l_iOffset;

	if (a_bClear)
	{
		m_csSubDirectory = a_csPath;
		Initialise();
	}

	if (!(m_csSubDirectory.IsEmpty()) && (m_csSubDirectory != a_csPath))
	{
		//return (false);
	}

	l_bSearching = (l_cFileFind.FindFile (a_csPath + "\\*.*") != 0);
	while (l_bSearching)
	{
		l_bSearching = (l_cFileFind.FindNextFile () != 0);

		if (l_cFileFind.IsDirectory ())
		{
			// Ignore
		}
		else
		{
			// Search for png files
			if ((l_cFileFind.GetFileName().Right (4) == ".png") ||
			    (l_cFileFind.GetFileName().Right (4) == ".tif"))
			{
				CString l_csPath = l_cFileFind.GetFilePath ();
				MultiByteToWideChar (CP_ACP, MB_PRECOMPOSED, l_csPath, -1, l_cFilename, 4096);
				if (LoadImage (l_cFilename))
				{
					l_csIconName = l_cFileFind.GetFileName ();
					l_iOffset = l_csIconName.ReverseFind ('.');
					if (l_iOffset >= 0)
					{
						l_csIconName = l_csIconName.Left (l_iOffset);
					}

					m_cImageNameList.Add (l_csIconName);
				}

			}
		}
		
	}

	l_cFileFind.Close ();
	return (true);

}

bool CImageStore::LoadImage(WCHAR *a_cFile)
{
	HICON l_HIcon;
	Gdiplus::Bitmap *l_pBitmap;
	Gdiplus::Bitmap l_cImage(a_cFile, false);
	CString l_csText;
	CString l_csDebug;

	RectF boundsRect;
	Unit unit;
	float l_iScale = 1.0f; //(float) m_iSize / 24.0f;

	l_cImage.GetBounds(&boundsRect, &unit);


	if ((boundsRect.Width > 0)   && (boundsRect.Height > 0))
	{
		if	 ((boundsRect.Width < 32) && (boundsRect.Height < 32))
		{
			l_pBitmap = l_cImage.Clone (0,0,24,24, PixelFormatDontCare );
		}
		else
		{
			l_pBitmap = l_cImage.Clone (0,8,24,24, PixelFormatDontCare );
		}

		l_pBitmap->GetHICON (&l_HIcon);		
		m_cImageList.Add (l_HIcon);

		delete (l_pBitmap);
		return (true);
	}
	else
	{
		return (false);
	}
}

int CImageStore::FindImageOffset(CString &a_csIconName)
{
	int l_iOffset;
	CString l_csIconName = a_csIconName;

	l_iOffset = a_csIconName.ReverseFind ('.');
	if (l_iOffset >= 0)
	{
		l_csIconName = a_csIconName.Left (l_iOffset);
	}

	for (l_iOffset=0; l_iOffset<=m_cImageNameList.GetUpperBound (); l_iOffset++)
	{
		if (m_cImageNameList.GetAt (l_iOffset) == l_csIconName)
		{
			return (l_iOffset);
		}
	}

	return (0);
}

CImageStore::AddCustomIcons(UINT l_iImageRef, int a_iAmount)
{
	CBitmap ImageBitmap;
	ImageBitmap.LoadBitmap (l_iImageRef);
	m_cImageList.Add (&ImageBitmap, (COLORREF) 0x00000000);
	int l_iOffset = m_cImageNameList.GetSize ();
	CString l_csName;

	while (a_iAmount--)
	{
		l_csName.Format ("Internal_%03d", l_iOffset++);
		m_cImageNameList.Add (l_csName);
	}
}

bool CImageStore::LoadFromArchive(CArchive &a_cArchive)
{
	m_cImageList.DeleteImageList( );
	return (m_cImageList.Read (&a_cArchive) != 0);
}
