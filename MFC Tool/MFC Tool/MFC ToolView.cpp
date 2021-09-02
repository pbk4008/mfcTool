
// MFC ToolView.cpp : CMFCToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "MFC Tool.h"
#endif

#include "MFC ToolDoc.h"
#include "MFC ToolView.h"
#include "MainFrm.h"
#include "Form.h"
#include "Mouse.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCToolView

IMPLEMENT_DYNCREATE(CMFCToolView, CView)

BEGIN_MESSAGE_MAP(CMFCToolView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_DROPFILES()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CMFCToolView ����/�Ҹ�
HWND g_hWnd;
CMFCToolView::CMFCToolView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CMFCToolView::~CMFCToolView()
{
	Safe_Delete(mTerrain);
	Safe_Delete(mouse);
	CTexturMgr::DestoryInstacne();
	CGraphicDevice::DestoryInstacne();
}

BOOL CMFCToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMFCToolView �׸���

void CMFCToolView::OnDraw(CDC* /*pDC*/)
{
	CMFCToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	m_pDevice->BeginDraw();

	m_pDevice->getSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	const TEXINFO* ptextInfo = CTexturMgr::getInstance()->getTexture(L"bg");
	if (nullptr == ptextInfo)
		return;
	//float fCenterX = ptextInfo->tTextureInfo.Width >> 1;
	//float fCenterY = ptextInfo->tTextureInfo.Height >> 1;

	D3DXVECTOR3 pos = {WINCX>>1, WINCY>>1, 0.f};

	m_pDevice->getSprite()->Draw(ptextInfo->pTexture, nullptr, nullptr/*&D3DXVECTOR3(fCenterX, fCenterY, 0.f)*/, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	mouse->RenderMouse(m_hWnd);

	m_pDevice->getSprite()->End();

	mTerrain->RenderTerrain();

	m_pDevice->EndDraw();


	Invalidate(false);
	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CMFCToolView �μ�

BOOL CMFCToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMFCToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMFCToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CMFCToolView ����

#ifdef _DEBUG
void CMFCToolView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCToolDoc* CMFCToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCToolDoc)));
	return (CMFCToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCToolView �޽��� ó����


void CMFCToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	CMainFrame* pFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	RECT rcFrameWindow;
	pFrame->GetWindowRect(&rcFrameWindow);
	SetRect(&rcFrameWindow, 0, 0, rcFrameWindow.right - rcFrameWindow.left, rcFrameWindow.bottom - rcFrameWindow.top);

	RECT rcView;
	GetClientRect(&rcView);
	int iRow = rcFrameWindow.right - rcView.right;
	int iCol = rcFrameWindow.bottom - rcView.bottom;

	pFrame->SetWindowPos(nullptr, 0, 0, WINCX + iRow, WINCY + iCol, SWP_NOZORDER);
	g_hWnd = m_hWnd;
	if (FAILED(CGraphicDevice::getInstance()->Initialize()))
		AfxMessageBox(L"CDevice Create Fail");

	m_pDevice = CGraphicDevice::getInstance();
	CTexturMgr::getInstance();
	mTerrain = Terrain::Create();

	CTexturMgr::getInstance()->InsertTexture(TEXTYPE::SINGLE, L"../Source/chapterBG0001.png", L"bg");

	CTexturMgr::getInstance()->InsertTexture(TEXTYPE::SINGLE, L"../Texture/Monster/Octo/Walk/Octo01.png", L"Octo01");

	//CTexturMgr::getInstance()->InsertTexture(TEXTYPE::MULTI, L"../Texture/Monster/Octo/Walk/Octo%d.png", L"Octo", L"Walk", 2);
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	mouse = Mouse::getInstance();
}

void CMFCToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CView::OnLButtonDown(nFlags, point);
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	Form* cForm = dynamic_cast<Form*>(pMain->m_SecSplitter.GetPane(1, 0));

	int idx = cForm->m_ListBox.GetCurSel();
	CString str;
	cForm->m_ListBox.GetText(idx,str);

	auto& iter = cForm->m_InfoMap.find(str);


	m_pDevice->BeginDraw();

	m_pDevice->getSprite()->Begin(D3DXSPRITE_ALPHABLEND);


	mouse->RenderObj(m_hWnd, iter->second);

	m_pDevice->getSprite()->End();

	m_pDevice->EndDraw();


}
