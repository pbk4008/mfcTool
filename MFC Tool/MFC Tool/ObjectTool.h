#pragma once
#include "afxwin.h"


// CObjectTool ��ȭ �����Դϴ�.

class CObjectTool : public CDialog
{
	DECLARE_DYNAMIC(CObjectTool)

public:
	CObjectTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CObjectTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OBJECTTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
private:
	bool CheckRadioBtn(const CButton* pBtn);
public:
	CListBox m_ListBox;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CStatic m_Picture;
	afx_msg void OnLbnSelchangeTexture();
	virtual BOOL OnInitDialog();
	// enum���� �߰� �ϸ� �˴ϴ�.
	CComboBox m_tComboBox;
	CButton m_tMoveCheck[2];
	CButton m_tDestroyCheck[2];
	CListBox m_tObjListBox;
	CString m_tName;
	map<CString, OBJINFO*> m_InfoMap;
	afx_msg void OnBnClickedInitialize();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();
};
