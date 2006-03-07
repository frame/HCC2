// XMLTag.h: interface for the XMLTag class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMLTAG_H__63E7E115_67B5_478C_9F27_F77656ECBB9B__INCLUDED_)
#define AFX_XMLTAG_H__63E7E115_67B5_478C_9F27_F77656ECBB9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XMLParser.h"

class XMLTag  
{
public:
	bool GetRepeatingDoubleTagValue(XMLParser &a_cParser, CString &a_csTagName, int &a_iClassValue, int &a_iTagValue, bool a_bInitialise = true);
	bool GetRepeatingDoubleTagValue(XMLParser &a_cParser, CString &a_csTagName, CString &a_csClassValue, CString &a_csTagValue, bool a_bInitialise = true);
	bool GetRepeatingTagValue(XMLParser &a_cParser, CString &a_csTagName, int &a_iTagValue, bool a_bInitialise = true);
	bool GetRepeatingTagValue(XMLParser &a_cParser, CString &a_csTagName, CString &a_csTagValue, bool a_bInitialise = true);
	bool GetTagDoubleValue(XMLParser &a_cParser, CString &a_csTagName, CString &a_csClassValue, CString &a_csTagValue, bool a_bInitialise = true);
	bool GetTagDoubleValue(XMLParser &a_cParser, CString &a_csTagName, int &a_csClassValue, int &a_iTagValue, bool a_bInitialise = true);
	bool GetTagValue(XMLParser &a_cParser, CString &a_csTagName, int &a_iTagValue, bool a_bInitialise = true);
	bool GetTagValue(XMLParser &a_cParser, CString &a_csTagName, CString &a_csTagValue, bool a_bInitialise = true);
	bool GetNextTag (XMLParser &a_cParser, XMLTag &a_cParentTag);
	void SetTag (CString &a_csTag);
	CString GetTag();
	XMLTag();
	XMLTag(const CString &a_csTag);
	virtual ~XMLTag();

	int m_iCurrentLine;
	int m_iRepeatingOffset;
	CString m_csCurrentTag;
};

#endif // !defined(AFX_XMLTAG_H__63E7E115_67B5_478C_9F27_F77656ECBB9B__INCLUDED_)
