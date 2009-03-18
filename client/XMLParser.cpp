// XMLParser.cpp: implementation of the XMLParser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XMLParser.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XMLParser::XMLParser()
{
	m_iIndent = 0;
	m_cFilePtr = NULL;
}

XMLParser::~XMLParser()
{

}

bool XMLParser::OpenFile(CString &a_csXMLFile)
{
	CString l_csLine;
	bool l_bResult = true;

	TRY
	{
		CStdioFile l_cFile (a_csXMLFile, CFile::modeRead);

		m_clLineList.RemoveAll ();

		while (l_cFile.ReadString (l_csLine))
		{
			l_csLine.TrimLeft ();
			m_clLineList.AddTail (l_csLine);
		}

	}
	CATCH( CFileException, e )
	{
		return (false);
	}
	END_CATCH

	return (l_bResult);
}

CString XMLParser::GetTagName(CString &a_csLine)
{
	int l_iTagStart;
	int l_iTagBreak;
	int l_iTagEnd;

	l_iTagStart = a_csLine.Find ('<', 0);
	l_iTagBreak = a_csLine.Find (' ', l_iTagStart);
	l_iTagEnd = a_csLine.Find ('>', l_iTagStart);

	if ((l_iTagBreak != -1) && (l_iTagBreak < l_iTagEnd))
	{
		l_iTagEnd = l_iTagBreak;
	}

	if ((l_iTagStart >=0) &&
		(l_iTagEnd >= 0) &&
		(l_iTagEnd > l_iTagStart))
	{
		return (a_csLine.Mid (l_iTagStart + 1, (l_iTagEnd - l_iTagStart) - 1));
	}
	else
	{
		return ("");
	}
}

CString XMLParser::GetTagName(int a_iLine)
{
	POSITION l_Pos;

	l_Pos = m_clLineList.FindIndex (a_iLine);
	if (l_Pos)
	{
		return (GetTagName (m_clLineList.GetAt (l_Pos)));
	}

	return ("");
}


CString XMLParser::GetTagClass(int a_iLine)
{
	POSITION l_Pos;

	l_Pos = m_clLineList.FindIndex (a_iLine);
	if (l_Pos)
	{
		return (GetTagClass (m_clLineList.GetAt (l_Pos)));
	}

	return ("");
}

CString XMLParser::GetTagClass(CString &a_csLine)
{
	int l_iTagStart;
	int l_iTagEnd;
	int l_iClassStart;
	int l_iClassEnd;

	l_iTagStart = a_csLine.Find ('<', 0);
	l_iTagEnd = a_csLine.Find ('>', l_iTagStart);

	if (l_iTagStart < l_iTagEnd)
	{
		l_iClassStart = a_csLine.Find ('\"', l_iTagStart);
		if (l_iClassStart >= 0)
		{
			l_iClassEnd = a_csLine.Find ('\"', l_iClassStart + 1);
			if (l_iClassEnd >= 0)
			{
				return (a_csLine.Mid (l_iClassStart + 1, (l_iClassEnd - l_iClassStart) - 1));
			}
		}
	}

	return ("");
}

CString XMLParser::GetTagValue(int a_iLine)
{
	POSITION l_Pos;

	l_Pos = m_clLineList.FindIndex (a_iLine);
	if (l_Pos)
	{
		return (GetTagValue (m_clLineList.GetAt (l_Pos)));
	}

	return ("");
}

CString XMLParser::GetTagValue(CString &a_csLine)
{
	CString l_csResult;
	CString l_csTagName = "";
	int l_iTagStart;
	int l_iTagEnd;

	l_csResult.Empty ();
	l_iTagStart = a_csLine.Find ('>', 0);
	l_iTagEnd = a_csLine.Find ("</", l_iTagStart);

	if ((l_iTagStart >=0) &&
		(l_iTagEnd >= 0) &&
		(l_iTagEnd > l_iTagStart))
	{
		if (l_iTagEnd != (l_iTagStart + 1))
		{
			l_csResult = (a_csLine.Mid (l_iTagStart + 1, (l_iTagEnd - l_iTagStart) - 1));
		}
	}

	return (l_csResult);
}

XMLParser::WriteTag(CString a_csTag, CString a_csTagValue)
{
	int i;

	for (i=0; i<m_iIndent; i++)
	{
		fprintf (m_cFilePtr, "\t");
	}

	if (a_csTagValue.IsEmpty ())
	{
		fprintf (m_cFilePtr, "<%s></%s>\n", a_csTag, a_csTag);
	}
	else
	{
	    a_csTagValue.Replace("&", "&amp;");
		fprintf (m_cFilePtr, "<%s>%s</%s>\n", a_csTag, a_csTagValue, a_csTag);
	}
}

XMLParser::WriteTag(CString a_csTag, int a_iTagValue)
{
	CString l_csValue;

	l_csValue.Format ("%d", a_iTagValue);
	WriteTag (a_csTag, l_csValue);
}

XMLParser::WriteAttributeTag(CString a_csTag, CString a_csAttribute, CString a_csTagValue)
{
	int i;

	for (i=0; i<m_iIndent; i++)
	{
		fprintf (m_cFilePtr, "\t");
	}

    a_csTagValue.Replace("&", "&amp;");
	fprintf (m_cFilePtr, "<%s %s>%s</%s>\n", a_csTag, a_csAttribute, a_csTagValue, a_csTag);
}

XMLParser::WriteOpenTag(CString a_csTag)
{
	int i;

	for (i=0; i<m_iIndent; i++)
	{
		fprintf (m_cFilePtr, "\t");
	}

	fprintf (m_cFilePtr, "<%s>\n", a_csTag);

	m_iIndent++;
}

XMLParser::WriteCloseTag(CString a_csTag)
{
	int i;

	m_iIndent--;

	for (i=0; i<m_iIndent; i++)
	{
		fprintf (m_cFilePtr, "\t");
	}

	fprintf (m_cFilePtr, "</%s>\n", a_csTag);
}

CString XMLParser::GetLine(int a_iLine)
{
	POSITION l_Pos;

	l_Pos = m_clLineList.FindIndex (a_iLine);
	if (l_Pos)
	{
		return (m_clLineList.GetAt (l_Pos));
	}

	return ("");
}

bool XMLParser::WriteFile(CString a_csFile)
{
	m_iIndent = 0;
	m_cFilePtr = NULL;

	m_cFilePtr = fopen (a_csFile, "w");

	if (m_cFilePtr)
	{
		fprintf (m_cFilePtr, "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n");
		return (true);
	}

	return (false);
}

XMLParser::CloseFile()
{
	if (m_cFilePtr)
	{
		fclose (m_cFilePtr);
	}
}
