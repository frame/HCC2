// Scheme.cpp: implementation of the CScheme class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HCC.h"
#include "Scheme.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "XMLParser.h"
#include "XMLTag.h"

CMapStringToString CScheme::m_cmColourMap;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CScheme::CScheme()
{

}

CScheme::~CScheme()
{

}


COLORREF CScheme::GetColour(CString a_csName)
{
	CString l_csFormat;
	COLORREF l_iColourRef;

	if (m_cmColourMap.Lookup (a_csName, l_csFormat))
	{
		sscanf (l_csFormat, "%x", &l_iColourRef);
		return (l_iColourRef);
	}
	else
	{
		if (a_csName.Right (3) == "_FG")
		{
			return ((COLORREF) 0x00000000);
		}
		else
		{
			return ((COLORREF) 0x00ffffff);
		}
	}
}

bool CScheme::LoadHCCScheme(CString &a_csFilename)
{
	bool l_bResult = false;
	XMLParser l_cParser;
	XMLTag l_cRootTag ("#ROOT#");
	XMLTag l_cSchemeTag ("scheme");
	XMLTag l_cColoursTag ("colours");
	CString l_csFormat;
	CString l_csInternalFormat;
	CString l_csName;

	l_cParser.OpenFile (a_csFilename);

	// Should be only one scheme Tag
	if (l_cSchemeTag.GetNextTag (l_cParser, l_cRootTag))
	{
		// Should be only one colours Tag
		if (l_cColoursTag.GetNextTag (l_cParser, l_cSchemeTag))
		{
			while (l_cColoursTag.GetRepeatingDoubleTagValue (l_cParser, (CString) "colour", l_csFormat, l_csName))
			{
				if (l_csFormat.Left (6) == "COLOR_")
				{
					if (l_csFormat == "COLOR_3DDKSHADOW")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_3DDKSHADOW));
					}
					else if (l_csFormat == "COLOR_3DFACE")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_3DFACE));
					}
					else if (l_csFormat == "COLOR_3DHIGHLIGHT")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_3DHIGHLIGHT));
					}
					else if (l_csFormat == "COLOR_3DHILIGHT")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_3DHILIGHT));
					}
					else if (l_csFormat == "COLOR_3DLIGHT")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_3DLIGHT));
					}
					else if (l_csFormat == "COLOR_3DSHADOW")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_3DSHADOW));
					}
					else if (l_csFormat == "COLOR_ACTIVEBORDER")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_ACTIVEBORDER));
					}
					else if (l_csFormat == "COLOR_ACTIVECAPTION")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_ACTIVECAPTION));
					}
					else if (l_csFormat == "COLOR_APPWORKSPACE")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_APPWORKSPACE));
					}
					else if (l_csFormat == "COLOR_BACKGROUND")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_BACKGROUND));
					}
					else if (l_csFormat == "COLOR_BTNFACE")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_BTNFACE));
					}
					else if (l_csFormat == "COLOR_BTNHIGHLIGHT")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_BTNHIGHLIGHT));
					}
					else if (l_csFormat == "COLOR_BTNSHADOW")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_BTNSHADOW));
					}
					else if (l_csFormat == "COLOR_BTNTEXT")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_BTNTEXT));
					}
					else if (l_csFormat == "COLOR_CAPTIONTEXT")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_CAPTIONTEXT));
					}
					else if (l_csFormat == "COLOR_DESKTOP")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_DESKTOP));
					}
					else if (l_csFormat == "COLOR_GRADIENTACTIVECAPTION")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_GRADIENTACTIVECAPTION));
					}
					else if (l_csFormat == "COLOR_GRADIENTINACTIVECAPTION")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_GRADIENTINACTIVECAPTION));
					}
					else if (l_csFormat == "COLOR_GRAYTEXT")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_GRAYTEXT));
					}
					else if (l_csFormat == "COLOR_HIGHLIGHT")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_HIGHLIGHT));
					}
					else if (l_csFormat == "COLOR_HIGHLIGHTTEXT")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_HIGHLIGHTTEXT));
					}
					else if (l_csFormat == "COLOR_HOTLIGHT")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_HOTLIGHT));
					}
					else if (l_csFormat == "COLOR_INACTIVEBORDER")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_INACTIVEBORDER));
					}
					else if (l_csFormat == "COLOR_INACTIVECAPTION")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_INACTIVECAPTION));
					}
					else if (l_csFormat == "COLOR_INACTIVECAPTIONTEXT")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_INACTIVECAPTIONTEXT));
					}
					else if (l_csFormat == "COLOR_INFOBK")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_INFOBK));
					}
					else if (l_csFormat == "COLOR_INFOTEXT")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_INFOTEXT));
					}
					else if (l_csFormat == "COLOR_MENU")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_MENU));
					}
					else if (l_csFormat == "COLOR_MENUHILIGHT")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_MENUHILIGHT));
					}
					else if (l_csFormat == "COLOR_MENUBAR")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_MENUBAR));
					}
					else if (l_csFormat == "COLOR_MENUTEXT")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_MENUTEXT));
					}
					else if (l_csFormat == "COLOR_SCROLLBAR")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_SCROLLBAR));
					}
					else if (l_csFormat == "COLOR_WINDOW")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_WINDOW));
					}
					else if (l_csFormat == "COLOR_WINDOWFRAME")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_WINDOWFRAME));
					}
					else if (l_csFormat == "COLOR_WINDOWTEXT")
					{
						l_csInternalFormat.Format ("%x", GetSysColor (COLOR_WINDOWTEXT));
					}
					else 
					{
						l_csInternalFormat.Empty ();
					}
				}
				else
				{
					l_csInternalFormat = "0x00" + 
												l_csFormat.Mid (5, 2) +
												l_csFormat.Mid (3, 2) +
												l_csFormat.Mid (1, 2);
				}

				if (!l_csInternalFormat.IsEmpty ())
				{
					CScheme::m_cmColourMap.SetAt (l_csName, l_csInternalFormat);
				}
			}

			l_bResult = true;
		}
	}

	return (l_bResult);
}

