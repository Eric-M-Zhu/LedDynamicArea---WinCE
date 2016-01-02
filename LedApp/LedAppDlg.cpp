// LedAppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LedApp.h"
#include "LedAppDlg.h"

#include "LedDynamicArea.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLedAppDlg dialog

CLedAppDlg::CLedAppDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLedAppDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_hLedDynamicArea = LoadLibrary(L"LedDynamicArea.dll");
	Initialize = (pInitialize)GetProcAddress(m_hLedDynamicArea, L"Initialize");
	Uninitialize = (pUninitialize)GetProcAddress(m_hLedDynamicArea, L"Uninitialize");
	AddScreen_Dynamic = (pAddScreen_Dynamic)GetProcAddress(m_hLedDynamicArea, L"AddScreen_Dynamic");
	QuerryServerDeviceList = (pQuerryServerDeviceList)GetProcAddress(m_hLedDynamicArea, L"QuerryServerDeviceList");
	BindServerDevice = (pBindServerDevice)GetProcAddress(m_hLedDynamicArea, L"BindServerDevice");
	AddScreenDynamicArea = (pAddScreenDynamicArea)GetProcAddress(m_hLedDynamicArea, L"AddScreenDynamicArea");
	AddScreenDynamicAreaFile = (pAddScreenDynamicAreaFile)GetProcAddress(m_hLedDynamicArea, L"AddScreenDynamicAreaFile");
	AddScreenDynamicAreaText = (pAddScreenDynamicAreaText)GetProcAddress(m_hLedDynamicArea, L"AddScreenDynamicAreaText");
	DeleteScreen_Dynamic = (pDeleteScreen_Dynamic)GetProcAddress(m_hLedDynamicArea, L"DeleteScreen_Dynamic");
	DeleteScreenDynamicAreaFile = (pDeleteScreenDynamicAreaFile)GetProcAddress(m_hLedDynamicArea, L"DeleteScreenDynamicAreaFile");
	SendDynamicAreaInfoCommand = (pSendDynamicAreaInfoCommand)GetProcAddress(m_hLedDynamicArea, L"SendDynamicAreaInfoCommand");
	SendDeleteDynamicAreasCommand = (pSendDeleteDynamicAreasCommand)GetProcAddress(m_hLedDynamicArea, L"SendDeleteDynamicAreasCommand");

	Initialize();
}

CLedAppDlg::~CLedAppDlg()
{
	Uninitialize();
	FreeLibrary(m_hLedDynamicArea);
}

void CLedAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLedAppDlg, CDialog)
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_DO, &CLedAppDlg::OnBnClickedDo)
	ON_BN_CLICKED(IDC_CLEAR, &CLedAppDlg::OnBnClickedClear)
END_MESSAGE_MAP()


// CLedAppDlg message handlers

BOOL CLedAppDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
void CLedAppDlg::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	if (AfxIsDRAEnabled())
	{
		DRA::RelayoutDialog(
			AfxGetResourceHandle(), 
			this->m_hWnd, 
			DRA::GetDisplayMode() != DRA::Portrait ? 
			MAKEINTRESOURCE(IDD_LEDAPP_DIALOG_WIDE) : 
			MAKEINTRESOURCE(IDD_LEDAPP_DIALOG));
	}
}
#endif


void CLedAppDlg::OnBnClickedDo()
{
	int result;

	AddScreen_Dynamic(0x0354, 1, SEND_MODE_SERIALPORT, 192, 20, 2, 1, "COM3", 57600, "", 5005, 0, "", "", "", 5005, "", "", "curCommandData.dat");
	AddScreenDynamicArea(1, 0, 0, 1, 1, "", 1, 16, 0, 192, 20, 255, 0, 255, 1, 0, 1);

	WCHAR text[32];
	char ansiText[32];
	GetDlgItem(IDC_EDIT1)->GetWindowText(text, 32);
	WideCharToMultiByte(CP_ACP, 0, text, -1, ansiText, 32, NULL, NULL);

	result = AddScreenDynamicAreaText(1, 0, ansiText, 1, "Tahoma", 12, 0, 255, 2, 8, 5);
	result = SendDynamicAreaInfoCommand(1, 0);
}

void CLedAppDlg::OnBnClickedClear()
{
	int result;

	result = SendDeleteDynamicAreasCommand(1, 1, "");
}
