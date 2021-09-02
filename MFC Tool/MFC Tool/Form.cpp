// Form.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFC Tool.h"
#include "Form.h"
#include "MainFrm.h"
#include "MFC ToolView.h"
#include "Mouse.h"
#include "ObjectTool.h"

// Form

IMPLEMENT_DYNCREATE(Form, CFormView)

Form::Form()
	: CFormView(IDD_FORMVIEW)
{
	
}

Form::~Form()
{
	for (auto& rPair : m_InfoMap) {
		Safe_Delete(rPair.second);
	}
	m_InfoMap.clear();
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
	ON_BN_CLICKED(IDC_BUTTON2, &Form::OnBnClickedLoad)
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


void Form::OnBnClickedObjectTool()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (nullptr == m_tObjectTool.GetSafeHwnd())
		m_tObjectTool.Create(IDD_OBJECTTOOL);
	m_tObjectTool.ShowWindow(SW_SHOW);
}


void Form::OnDropFiles(HDROP hDropInfo)
{
	/*int iCount = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0);
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
*/

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


void Form::OnBnClickedLoad()
{
	CFileDialog Dlg(true, L"dat", L"*.dat");

	TCHAR szFilePath[MAX_PATH] = L"";

	GetCurrentDirectory(MAX_PATH, szFilePath);
	PathRemoveFileSpec(szFilePath);
	lstrcat(szFilePath, L"../Data");
	Dlg.m_ofn.lpstrInitialDir = szFilePath;
	if (IDOK == Dlg.DoModal())
	{
		CString strFilePath = Dlg.GetPathName();
		HANDLE hFile = CreateFile(strFilePath, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (INVALID_HANDLE_VALUE == hFile)
			return;
		for (auto&rPair : m_InfoMap)
			Safe_Delete(rPair.second);
		m_InfoMap.clear();

		DWORD dwByte = 0;
		DWORD dwStrByte = 0;
		TCHAR* pStr = nullptr;
		OBJINFO* pInfo = nullptr;
		while (true)
		{
			pInfo = new OBJINFO;

			ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
			pStr = new TCHAR[dwStrByte];
			ReadFile(hFile, pStr, dwStrByte, &dwByte, nullptr);
			pInfo->strObjKey = pStr;
			delete[] pStr;
			pStr = nullptr;


			ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
			pStr = new TCHAR[dwStrByte];
			ReadFile(hFile, pStr, dwStrByte, &dwByte, nullptr);
			pInfo->strName = pStr;
			delete[] pStr;
			pStr = nullptr;


			ReadFile(hFile, &pInfo->bMove, sizeof(bool), &dwByte, nullptr);
			ReadFile(hFile, &pInfo->bDestroy, sizeof(bool), &dwByte, nullptr);
			ReadFile(hFile, &pInfo->eID, sizeof(OBJID), &dwByte, nullptr);
			if (0 == dwByte)
			{
				Safe_Delete(pInfo);
				break;
			}
			m_InfoMap.emplace(pInfo->strName, pInfo);
			m_ListBox.AddString(pInfo->strName);
		}
		CloseHandle(hFile);
	}
	
}
