#pragma once


// CInputTextDlg dialog

class CInputTextDlg : public CDialog
{
	DECLARE_DYNAMIC(CInputTextDlg)

public:
	CInputTextDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CInputTextDlg();

	CString GetText() { return m_text; }

// Dialog Data
	enum { IDD = IDD_INPUT_TEXT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CString m_text;

	afx_msg void OnBnClickedOk();
};
