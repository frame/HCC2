// XMLTag.cpp: implementation of the XMLTag class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XMLTag.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XMLTag::XMLTag()
{
	m_iCurrentLine = -1;
	m_iRepeatingOffset = 0;
}

XMLTag::XMLTag(const CString &a_csTag)
{
	m_csCurrentTag = a_csTag;
	m_iCurrentLine = -1;
	m_iRepeatingOffset = 0;
}

XMLTag::~XMLTag()
{

}

CString XMLTag::GetTag()
{
	return (m_csCurrentTag);
}

void XMLTag::SetTag(CString &a_csTag)
{
	m_csCurrentTag = a_csTag;
}

bool XMLTag::GetNextTag(XMLParser &a_cParser, XMLTag &a_cParentTag)
{
	bool l_bFound = false;
	int l_iLine = m_iCurrentLine + 1;
	CString l_csTagName;

	if (l_iLine <= a_cParentTag.m_iCurrentLine)
	{
		l_iLine = a_cParentTag.m_iCurrentLine + 1;
	}

	while ((l_bFound == false) && (l_iLine < a_cParser.m_clLineList.GetCount ()))
	{
		l_csTagName = a_cParser.GetTagName (l_iLine);
		if (m_csCurrentTag == l_csTagName)
		{
			m_iCurrentLine = l_iLine;
			l_bFound = true;
		}
		else if (("/" + a_cParentTag.m_csCurrentTag) == l_csTagName)
		{
			l_iLine = a_cParser.m_clLineList.GetCount ();
		}
		else
		{
			l_iLine++;
		}
	}

	return (l_bFound);
}

bool XMLTag::GetTagValue(XMLParser &a_cParser, CString &a_csTagName, CString &a_csTagValue, bool a_bInitialise)
{
	int l_iLine = m_iCurrentLine + 1;
	CString l_csTagName;

	if (a_bInitialise)
	{
		a_csTagValue.Empty ();
	}

	while (l_iLine < a_cParser.m_clLineList.GetCount ())
	{
		l_csTagName = a_cParser.GetTagName (l_iLine);
		if (a_csTagName == l_csTagName)
		{
			a_csTagValue = a_cParser.GetTagValue (l_iLine);
			a_csTagValue.Replace("&amp;", "&");
			return (true);
		}
		else if (("/" + m_csCurrentTag) == l_csTagName)
		{
			return (false);
		}
		else
		{
			l_iLine++;
		}
	}

	return (false);
}

bool XMLTag::GetTagValue(XMLParser &a_cParser, CString &a_csTagName, int &a_iTagValue, bool a_bInitialise)
{
	CString l_csTagValue;

	if (a_bInitialise)
	{
		a_iTagValue = 0;
	}

	if (GetTagValue(a_cParser, a_csTagName, l_csTagValue))
	{
		a_iTagValue = atoi(l_csTagValue);
		return (true);
	}

	return (false);
}

bool XMLTag::GetTagDoubleValue(XMLParser &a_cParser, CString &a_csTagName, CString &a_csClassValue, CString &a_csTagValue, bool a_bInitialise)
{
	int l_iLine = m_iCurrentLine + 1;
	CString l_csTagName;
	CString l_csLine;

	if (a_bInitialise)
	{
		a_csClassValue.Empty ();
		a_csTagValue.Empty ();
	}

	while (l_iLine < a_cParser.m_clLineList.GetCount ())
	{
		l_csLine = a_cParser.GetLine (l_iLine);
		l_csTagName = a_cParser.GetTagName (l_csLine);
		if (a_csTagName == l_csTagName)
		{
			a_csTagValue = a_cParser.GetTagValue (l_csLine);
			a_csTagValue.Replace("&amp;", "&");
			a_csClassValue = a_cParser.GetTagClass (l_csLine);
			a_csClassValue.Replace("&amp;", "&");

			return (true);
		}
		else if (("/" + m_csCurrentTag) == l_csTagName)
		{
			return (false);
		}
		else
		{
			l_iLine++;
		}
	}

	return (false);
}

bool XMLTag::GetTagDoubleValue(XMLParser &a_cParser, CString &a_csTagName, int &a_csClassValue, int &a_iTagValue, bool a_bInitialise)
{
	CString l_csTagValue;
	CString l_csClassValue;

	if (a_bInitialise)
	{
		a_iTagValue = 0;
		a_csClassValue = 0;
	}

	if (GetTagDoubleValue(a_cParser, a_csTagName, l_csClassValue, l_csTagValue))
	{
		a_iTagValue = atoi(l_csTagValue);
		a_csClassValue = atoi(l_csClassValue);
		return (true);
	}

	return (false);
}

bool XMLTag::GetRepeatingTagValue(XMLParser &a_cParser, CString &a_csTagName, CString &a_csTagValue, bool a_bInitialise)
{
	int l_iLine = m_iCurrentLine + 1 + 	m_iRepeatingOffset;
	CString l_csTagName;
	CString l_csTagValue = "";
	CString l_csLine;

	if (a_bInitialise)
	{
		a_csTagValue.Empty ();
	}

	while (l_iLine < a_cParser.m_clLineList.GetCount ())
	{
		l_csLine = a_cParser.GetLine (l_iLine);
		l_csTagName = a_cParser.GetTagName (l_csLine);
		if (a_csTagName == l_csTagName)
		{
			a_csTagValue = a_cParser.GetTagValue (l_csLine);
			m_iRepeatingOffset++;
			return (true);
		}
		else if (("/" + m_csCurrentTag) == l_csTagName)
		{
			m_iRepeatingOffset = 0;
			return (false);
		}
		else
		{
			l_iLine++;
		}
	}

	m_iRepeatingOffset = 0;
	return (false);
}

bool XMLTag::GetRepeatingTagValue(XMLParser &a_cParser, CString &a_csTagName, int &a_iTagValue, bool a_bInitialise)
{
	CString l_csTagValue;

	if (a_bInitialise)
	{
		a_iTagValue = 0;
	}

	if (GetRepeatingTagValue(a_cParser, a_csTagName, l_csTagValue))
	{
		a_iTagValue = atoi(l_csTagValue);
		return (true);
	}

	a_iTagValue = 0;
	return (false);
}

bool XMLTag::GetRepeatingDoubleTagValue(XMLParser &a_cParser, CString &a_csTagName, CString &a_csClassValue, CString &a_csTagValue, bool a_bInitialise)
{
	int l_iLine = m_iCurrentLine + 1 + 	m_iRepeatingOffset;
	CString l_csTagName;
	CString l_csTagValue = "";
	CString l_csLine;

	if (a_bInitialise)
	{
		a_csTagValue.Empty ();
		a_csClassValue.Empty ();
	}

	while (l_iLine < a_cParser.m_clLineList.GetCount ())
	{
		l_csLine = a_cParser.GetLine (l_iLine);
		l_csTagName = a_cParser.GetTagName (l_csLine);
		if (a_csTagName == l_csTagName)
		{
			a_csTagValue = a_cParser.GetTagValue (l_csLine);
			a_csTagValue.Replace("&amp;", "&");
			a_csClassValue = a_cParser.GetTagClass (l_csLine);
			m_iRepeatingOffset++;
			return (true);
		}
		else if (("/" + m_csCurrentTag) == l_csTagName)
		{
			m_iRepeatingOffset = 0;
			return (false);
		}
		else
		{
			l_iLine++;
		}
	}

	m_iRepeatingOffset = 0;
	return (false);
}

bool XMLTag::GetRepeatingDoubleTagValue(XMLParser &a_cParser, CString &a_csTagName, int &a_iClassValue, int &a_iTagValue, bool a_bInitialise)
{
	CString l_csClassValue;
	CString l_csTagValue;

	if (a_bInitialise)
	{
		a_iClassValue = 0;
		a_iTagValue = 0;
	}
	if (GetRepeatingDoubleTagValue(a_cParser, a_csTagName, l_csClassValue, l_csTagValue))
	{
		a_iClassValue = atoi(l_csClassValue);
		a_iTagValue = atoi(l_csTagValue);
		return (true);
	}

	return (false);
}

