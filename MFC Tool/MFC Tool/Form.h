#pragma once



// Form �� ���Դϴ�.

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

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};


