// MiniView.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFC Tool.h"
#include "MainFrm.h"
#include "MFC ToolView.h"
#include "MiniView.h"

// CMiniView

IMPLEMENT_DYNCREATE(CMiniView, CView)

CMiniView::CMiniView() : m_pDevice(nullptr), m_pTexture(nullptr),m_pSprite(nullptr)
{

}

CMiniView::~CMiniView()
{
}

BEGIN_MESSAGE_MAP(CMiniView, CView)
END_MESSAGE_MAP()


// CMiniView 그리기

void CMiniView::OnDraw(CDC* /*pDC*/)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
	
	m_pDevice->BeginDraw();
	m_pDevice->EndDraw(m_hWnd);
}


// CMiniView 진단

#ifdef _DEBUG
void CMiniView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMiniView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMiniView 메시지 처리기


void CMiniView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	m_pDevice = CGraphicDevice::getInstance();
	m_pSprite = m_pDevice->getSprite();

	CMainFrame* mainFrm = dynamic_cast<CMainFrame*>(AfxGetMainWnd());

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}
