// InputTextDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LedApp.h"
#include "InputTextDlg.h"


// CInputTextDlg dialog

IMPLEMENT_DYNAMIC(CInputTextDlg, CDialog)

CInputTextDlg::CInputTextDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInputTextDlg::IDD, pParent)
	, m_text(_T(""))
{

}

CInputTextDlg::~CInputTextDlg()
{
}

void CInputTextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TEXT, m_text);
}


BEGIN_MESSAGE_MAP(CInputTextDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CInputTextDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CInputTextDlg message handlers

void CInputTextDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	OnOK();
}
