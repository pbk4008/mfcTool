// Form.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFC Tool.h"
#include "Form.h"
#include "MainFrm.h"
#include "MFC ToolView.h"
#include "Mouse.h"

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
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
}

BEGIN_MESSAGE_MAP(Form, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &Form::OnBnClickedObjectTool)
	ON_WM_DROPFILES()
	ON_WM_LBUTTONDOWN()
	ON_LBN_SELCHANGE(IDC_LIST1, &Form::OnLbnSelchangePickTexture)
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


void Form::OnDropFiles(HDROP hDropInfo)
{
	int iCount = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0);
	TCHAR szFilePath[MAX_PATH]{};

	for (int i = 0; i < iCount; ++i)
	{
		DragQueryFile(hDropInfo, i, szFilePath, MAX_PATH);
		CString wstrRelativePath = CFileInfo::ChangeRelativePath(szFilePath);
		TCHAR szFileName[MAX_PATH]{};
		CString wstrFileName = PathFindFileName(szFilePath);
		lstrcpy(szFileName, wstrFileName.GetString());
		PathRemoveExtension(szFileName);
		m_ListBox.AddString(szFileName);
	}

	m_ListBox.SetHorizontalExtent(800);
	UpdateData(FALSE);
	CFormView::OnDropFiles(hDropInfo);
}


void Form::OnLButtonDown(UINT nFlags, CPoint point) {

	CFormView::OnLButtonDown(nFlags, point);
}


void Form::OnLbnSelchangePickTexture()
{
	int index = m_ListBox.GetCurSel();
	CString wstrTextureName;

	int textueNameSize = wstrTextureName.GetLength();
	int i = 0;

	for (; i < textueNameSize; i++) {
		if (isdigit(wstrTextureName[i])) {
			break;
		}
	}
	wstrTextureName.Delete(0, i);
	dwDrawID = _ttoi(wstrTextureName.GetString());

	CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitter.GetPane(0, 1));
	pView->mouse->SetRenderID(dwDrawID);
}
