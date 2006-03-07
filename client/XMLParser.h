// XMLParser.h: interface for the XMLParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMLPARSER_H__5CA3A8C8_3892_4192_B896_D2CC2DFE3677__INCLUDED_)
#define AFX_XMLPARSER_H__5CA3A8C8_3892_4192_B896_D2CC2DFE3677__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class XMLParser  
{
public:
	CloseFile();
	bool WriteFile (CString a_csFile);
	CString GetLine (int a_iLine);
	CString GetTagClass (int a_iLine);
	CString GetTagClass(CString &a_csLine);
	WriteCloseTag(CString a_csTag);
	WriteOpenTag (CString a_csTag);
	WriteAttributeTag(CString a_csTag, CString a_csAttribute, CString a_csTagValue);
	WriteTag (CString a_csTag, CString a_csTagValue);
	WriteTag(CString a_csTag, int a_iTagValue);
	bool OpenFile (CString &a_csXMLFile);
	XMLParser();
	virtual ~XMLParser();

	CString GetTagValue (int a_iLine);
	CString GetTagValue(CString &a_csLine);
	CString GetTagName (int a_iLine);
	CString GetTagName(CString &a_csLine);

	int m_iIndent;
	FILE *m_cFilePtr;
	CStringList m_clLineList;
};

#endif // !defined(AFX_XMLPARSER_H__5CA3A8C8_3892_4192_B896_D2CC2DFE3677__INCLUDED_)
