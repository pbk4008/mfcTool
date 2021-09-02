#pragma once
#include "afxwin.h"


// CObjectTool 대화 상자입니다.

class CObjectTool : public CDialog
{
	DECLARE_DYNAMIC(CObjectTool)

public:
	CObjectTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CObjectTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OBJECTTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
private:
	bool CheckRadioBtn(const CButton* pBtn);
public:
	CListBox m_ListBox;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CStatic m_Picture;
	afx_msg void OnLbnSelchangeTexture();
	virtual BOOL OnInitDialog();
	// enum값을 추가 하면 됩니다.
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
