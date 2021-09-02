#pragma once



// Form �� ���Դϴ�.
#include "ObjectTool.h"
class Form : public CFormView
{
	DECLARE_DYNCREATE(Form)

protected:
	Form();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~Form();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
public:
	CObjectTool m_tObjectTool;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedObjectTool();

	CListBox m_ListBox;
	DWORD dwDrawID;
	map<CString, OBJINFO*> m_InfoMap;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLbnSelchangePickTexture();
	afx_msg void OnBnClickedLoad();
};


