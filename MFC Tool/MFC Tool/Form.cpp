// Form.cpp : ���� �����Դϴ�.
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
END_MESSAGE_MAP()


// Form �����Դϴ�.

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


// Form �޽��� ó�����Դϴ�.
