// Form.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFC Tool.h"
#include "Form.h"


// Form

IMPLEMENT_DYNCREATE(Form, CFormView)

Form::Form()
	: CFormView(IDD_FORMVIEW)
{

}

Form::~Form()
{
}

void Form::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Form, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &Form::OnBnClickedObjectTool)
END_MESSAGE_MAP()


// Form 진단입니다.

#ifdef _DEBUG
void Form::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void Form::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// Form 메시지 처리기입니다.


void Form::OnBnClickedObjectTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (nullptr == m_tObjectTool.GetSafeHwnd())
		m_tObjectTool.Create(IDD_OBJECTTOOL);
	m_tObjectTool.ShowWindow(SW_SHOW);
}
