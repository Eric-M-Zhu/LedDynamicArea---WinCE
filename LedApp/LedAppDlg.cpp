// LedAppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LedApp.h"
#include "LedAppDlg.h"

#include "InputTextDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAX_AREA_COUNT 16

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
	DeleteScreenDynamicArea = (pDeleteScreenDynamicArea)GetProcAddress(m_hLedDynamicArea, L"DeleteScreenDynamicArea");
	DeleteScreenDynamicAreaFile = (pDeleteScreenDynamicAreaFile)GetProcAddress(m_hLedDynamicArea, L"DeleteScreenDynamicAreaFile");
	SendDynamicAreaInfoCommand = (pSendDynamicAreaInfoCommand)GetProcAddress(m_hLedDynamicArea, L"SendDynamicAreaInfoCommand");
	SendDeleteDynamicAreasCommand = (pSendDeleteDynamicAreasCommand)GetProcAddress(m_hLedDynamicArea, L"SendDeleteDynamicAreasCommand");

	Initialize();
}

CLedAppDlg::~CLedAppDlg()
{
	for	(list<DynamicArea*>::iterator iter = m_areaList.begin(); iter != m_areaList.end(); ++iter)
	{
		DynamicArea *pArea = *iter;

		/*for	(list<AreaContent*>::iterator iter2 = pArea->contents.begin(); iter2 != pArea->contents.end(); ++iter2)
		{
			delete *iter2;
		}*/

		delete pArea;
	}

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
	ON_BN_CLICKED(IDC_SET_SCREEN, &CLedAppDlg::OnBnClickedSetScreen)
	ON_CBN_SELCHANGE(IDC_AREA_LIST, &CLedAppDlg::OnCbnSelchangeAreaList)
	ON_BN_CLICKED(IDC_ADD_AREA, &CLedAppDlg::OnBnClickedAddArea)
	ON_BN_CLICKED(IDC_REMOVE_AREA, &CLedAppDlg::OnBnClickedRemoveArea)
	ON_BN_CLICKED(IDC_ADD_FILE, &CLedAppDlg::OnBnClickedAddFile)
	ON_BN_CLICKED(IDC_ADD_TEXT, &CLedAppDlg::OnBnClickedAddText)
	ON_BN_CLICKED(IDC_UPDATE_AREA, &CLedAppDlg::OnBnClickedUpdateArea)
	ON_BN_CLICKED(IDC_CLEAR_AREA, &CLedAppDlg::OnBnClickedClearArea)
	ON_BN_CLICKED(IDC_DELETE_CONTENT, &CLedAppDlg::OnBnClickedDeleteContent)
	ON_CBN_SELCHANGE(IDC_PORT_TYPE, &CLedAppDlg::OnCbnSelchangePortType)
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
	FillCommunicationModeComboBox();
	FillFontColorComboBox();
	FillContentStyle();
	FillFontListComboBox();

	SetControllerType(BX_5E3);
	SetCommunicationMode(SEND_MODE_SERIALPORT);
	SetScreenWidth(96);
	SetScreenHeight(32);
	SetCOMPort(L"COM3");
	SetBaudRate(57600);
	SetIPAddress(L"192.168.2.199");
	SetTCPPort(5005);

	SetAreaLeft(16);
	SetAreaTop(0);
	SetAreaWidth(64);
	SetAreaHeight(16);

	SetFontName(L"Tahoma");
	SetFontSize(12);
	SetFontColor(0);
	SetContentStyle(2);
	SetContentSpeed(8);
	SetContentTime(5);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLedAppDlg::FillCommunicationModeComboBox()
{
	CComboBox *pCommunicationModeComboBox = (CComboBox*)GetDlgItem(IDC_PORT_TYPE);

	pCommunicationModeComboBox->AddString(L"串口通讯");
	pCommunicationModeComboBox->AddString(L"网络通讯");
}

void CLedAppDlg::FillFontColorComboBox()
{
	CComboBox *pFontColorComboBox = (CComboBox*)GetDlgItem(IDC_FONT_COLOR);

	pFontColorComboBox->AddString(L"红色");
	pFontColorComboBox->AddString(L"绿色");
	pFontColorComboBox->AddString(L"黄色");
}

void CLedAppDlg::FillContentStyle()
{
	CComboBox *pContentStyleComboBox = (CComboBox*)GetDlgItem(IDC_CONTENT_STYLE);

	pContentStyleComboBox->AddString(L"随机显示");
	pContentStyleComboBox->AddString(L"静止显示");
	pContentStyleComboBox->AddString(L"快速打出");
	pContentStyleComboBox->AddString(L"向左移动");
	pContentStyleComboBox->AddString(L"向左连移");
	pContentStyleComboBox->AddString(L"向上移动");
	pContentStyleComboBox->AddString(L"向上连移");
	pContentStyleComboBox->AddString(L"闪烁");
	pContentStyleComboBox->AddString(L"飘雪");
	pContentStyleComboBox->AddString(L"冒泡");
	pContentStyleComboBox->AddString(L"中间移出");
	pContentStyleComboBox->AddString(L"左右移入");
	pContentStyleComboBox->AddString(L"左右交叉移入");
	pContentStyleComboBox->AddString(L"上下交叉移入");
	pContentStyleComboBox->AddString(L"画卷闭合");
	pContentStyleComboBox->AddString(L"画卷打开");
	pContentStyleComboBox->AddString(L"向左拉伸");
	pContentStyleComboBox->AddString(L"向右拉伸");
	pContentStyleComboBox->AddString(L"向上拉伸");
	pContentStyleComboBox->AddString(L"向下拉伸");
	pContentStyleComboBox->AddString(L"向左镭射");
	pContentStyleComboBox->AddString(L"向右镭射");
	pContentStyleComboBox->AddString(L"向上镭射");
	pContentStyleComboBox->AddString(L"向下镭射");
	pContentStyleComboBox->AddString(L"左右交叉拉幕");
	pContentStyleComboBox->AddString(L"上下交叉拉幕");
	pContentStyleComboBox->AddString(L"分散左拉");
	pContentStyleComboBox->AddString(L"水平百页");
	pContentStyleComboBox->AddString(L"垂直百页");
	pContentStyleComboBox->AddString(L"向左拉幕");
	pContentStyleComboBox->AddString(L"向右拉幕");
	pContentStyleComboBox->AddString(L"向上拉幕");
	pContentStyleComboBox->AddString(L"向下拉幕");
	pContentStyleComboBox->AddString(L"左右闭合");
	pContentStyleComboBox->AddString(L"左右对开");
	pContentStyleComboBox->AddString(L"上下闭合");
	pContentStyleComboBox->AddString(L"上下对开");
	pContentStyleComboBox->AddString(L"向右移动");
	pContentStyleComboBox->AddString(L"向右连移");
	pContentStyleComboBox->AddString(L"向下移动");
	pContentStyleComboBox->AddString(L"向下连移");
}

int CALLBACK EnumFontProc(const LOGFONT *lpFont, const TEXTMETRIC *lpTM, DWORD fontType, LPARAM lParam)
{
	CLedAppDlg *pDlg = (CLedAppDlg*)lParam;

	pDlg->InsertFontName(lpFont->lfFaceName);

	return 1;
}

void CLedAppDlg::FillFontListComboBox()
{
	HWND hDesktopWnd = ::GetDesktopWindow();
	HDC hDesktopDC = ::GetWindowDC(hDesktopWnd);

	EnumFontFamilies(hDesktopDC, NULL, EnumFontProc, (LPARAM)this);
}

void CLedAppDlg::InsertFontName(CString fontName)
{
	CComboBox *pFontListComboBox = (CComboBox*)GetDlgItem(IDC_FONT_LIST);

	pFontListComboBox->AddString(fontName);
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

ControllerType CLedAppDlg::GetControllerType()
{
	CComboBox *pControllerTypeComboBox = (CComboBox*)GetDlgItem(IDC_CONTROLLER_TYPE);

	switch (pControllerTypeComboBox->GetCurSel())
	{
	case 0:
		return BX_5E1;
	case 1:
		return BX_5E2;
	case 2:
		return BX_5E3;
	case 3:
		return BX_5Q0P;
	case 4:
		return BX_5Q1P;
	case 5:
		return BX_5Q2P;
	}

	return BX_5E3;
}

void CLedAppDlg::SetControllerType(ControllerType type)
{
	CComboBox *pControllerTypeComboBox = (CComboBox*)GetDlgItem(IDC_CONTROLLER_TYPE);
	int curSel = 0;

	switch (type)
	{
	case BX_5E1:
		curSel = 0;
		break;
	case BX_5E2:
		curSel = 1;
		break;
	case BX_5E3:
		curSel = 2;
		break;
	case BX_5Q0P:
		curSel = 3;
		break;
	case BX_5Q1P:
		curSel = 4;
		break;
	case BX_5Q2P:
		curSel = 5;
		break;
	}

	pControllerTypeComboBox->SetCurSel(curSel);
}

CommunicationMode CLedAppDlg::GetCommunicationMode()
{
	CComboBox *pCommunicationModeComboBox = (CComboBox*)GetDlgItem(IDC_PORT_TYPE);

	switch (pCommunicationModeComboBox->GetCurSel())
	{
	case 0:
		return SEND_MODE_SERIALPORT;
	case 1:
		return SEND_MODE_NETWORK;
	}

	return SEND_MODE_SERIALPORT;
}

void CLedAppDlg::SetCommunicationMode(CommunicationMode mode)
{
	CComboBox *pCommunicationModeComboBox = (CComboBox*)GetDlgItem(IDC_PORT_TYPE);
	int curSel = 0;

	switch (mode)
	{
	case SEND_MODE_SERIALPORT:
		curSel = 0;
		break;
	case SEND_MODE_NETWORK:
		curSel = 1;
		break;
	}

	pCommunicationModeComboBox->SetCurSel(curSel);
}

int CLedAppDlg::GetScreenWidth()
{
	CString screenWidthText;
	
	GetDlgItem(IDC_SCREEN_WIDTH)->GetWindowTextW(screenWidthText);

	return _wtoi(screenWidthText);
}

void CLedAppDlg::SetScreenWidth(int width)
{
	CString screenWidthText;
	
	screenWidthText.Format(L"%d", width);
	GetDlgItem(IDC_SCREEN_WIDTH)->SetWindowTextW(screenWidthText);
}
	
int CLedAppDlg::GetScreenHeight()
{
	CString screenHeightText;
	
	GetDlgItem(IDC_SCREEN_HEIGHT)->GetWindowTextW(screenHeightText);

	return _wtoi(screenHeightText);
}

void CLedAppDlg::SetScreenHeight(int height)
{
	CString screenHeightText;
	
	screenHeightText.Format(L"%d", height);
	GetDlgItem(IDC_SCREEN_HEIGHT)->SetWindowTextW(screenHeightText);
}

char* CLedAppDlg::GetCOMPort()
{
	CComboBox *pCOMPortComboBox = (CComboBox*)GetDlgItem(IDC_SERIAL_PORT);

	switch (pCOMPortComboBox->GetCurSel())
	{
	case 0:
		return "COM1";
	case 1:
		return "COM2";
	case 2:
		return "COM3";
	case 3:
		return "COM4";
	case 4:
		return "COM5";
	case 5:
		return "COM6";
	case 6:
		return "COM7";
	case 7:
		return "COM8";
	case 8:
		return "COM9";
	}

	return "COM1";
}

void CLedAppDlg::SetCOMPort(const WCHAR *pCOMPort)
{
	CComboBox *pCOMPortComboBox = (CComboBox*)GetDlgItem(IDC_SERIAL_PORT);
	int count = pCOMPortComboBox->GetCount();
	int i = 0;

	for	(; i < count; ++i)
	{
		CString curText;

		pCOMPortComboBox->GetLBText(i, curText);
		if (curText.CompareNoCase(pCOMPort) == 0)
		{
			break;
		}
	}

	pCOMPortComboBox->SetCurSel(i);
}

int CLedAppDlg::GetBaudRate()
{
	return 57600;
}

void CLedAppDlg::SetBaudRate(int baudRate)
{
	((CComboBox*)GetDlgItem(IDC_BAUD_RATE))->SetCurSel(0);
}

int CLedAppDlg::GetAreaLeft()
{
	CString text;

	GetDlgItem(IDC_AREA_LEFT)->GetWindowTextW(text);

	return _wtoi(text);
}

void CLedAppDlg::SetAreaLeft(int left)
{
	CString text;

	text.Format(L"%d", left);
	GetDlgItem(IDC_AREA_LEFT)->SetWindowTextW(text);
}

int CLedAppDlg::GetAreaTop()
{
	CString text;

	GetDlgItem(IDC_AREA_TOP)->GetWindowTextW(text);

	return _wtoi(text);
}

void CLedAppDlg::SetAreaTop(int top)
{
	CString text;

	text.Format(L"%d", top);
	GetDlgItem(IDC_AREA_TOP)->SetWindowTextW(text);
}

int CLedAppDlg::GetAreaWidth()
{
	CString text;

	GetDlgItem(IDC_AREA_WIDTH)->GetWindowTextW(text);

	return _wtoi(text);
}

void CLedAppDlg::SetAreaWidth(int width)
{
	CString text;

	text.Format(L"%d", width);
	GetDlgItem(IDC_AREA_WIDTH)->SetWindowTextW(text);
}

int CLedAppDlg::GetAreaHeight()
{
	CString text;

	GetDlgItem(IDC_AREA_HEIGHT)->GetWindowTextW(text);

	return _wtoi(text);
}

void CLedAppDlg::SetAreaHeight(int height)
{
	CString text;

	text.Format(L"%d", height);
	GetDlgItem(IDC_AREA_HEIGHT)->SetWindowTextW(text);
}

int CLedAppDlg::GetSingleLine()
{
	CButton *pSingleLineCheckBox = (CButton*)GetDlgItem(IDC_SINGLE_LINE);

	return pSingleLineCheckBox->GetCheck() == BST_CHECKED ? 1 : 0;
}

void CLedAppDlg::SetSingleLine(int singleLine)
{
	CButton *pSingleLineCheckBox = (CButton*)GetDlgItem(IDC_SINGLE_LINE);
	
	pSingleLineCheckBox->SetCheck(singleLine == 0 ? BST_UNCHECKED : BST_CHECKED);
}

CString CLedAppDlg::GetFontName()
{
	CString fontName;
	CComboBox *pFontNameComboBox = (CComboBox*)GetDlgItem(IDC_FONT_LIST);
	int index = pFontNameComboBox->GetCurSel();

	if (index >= 0)
	{
		pFontNameComboBox->GetLBText(index, fontName);
	}

	return fontName;
}

void CLedAppDlg::SetFontName(CString fontName)
{
	CComboBox *pFontNameComboBox = (CComboBox*)GetDlgItem(IDC_FONT_LIST);

	for	(int i = 0; i < pFontNameComboBox->GetCount(); ++i)
	{
		CString curFontName;

		pFontNameComboBox->GetLBText(i, curFontName);

		if (curFontName.CompareNoCase(fontName) == 0)
		{
			pFontNameComboBox->SetCurSel(i);
		}
	}
}

int CLedAppDlg::GetFontSize()
{
	CString text;

	GetDlgItem(IDC_FONT_SIZE)->GetWindowTextW(text);

	return _wtoi(text);
}

void CLedAppDlg::SetFontSize(int size)
{
	CString text;

	text.Format(L"%d", size);
	GetDlgItem(IDC_FONT_SIZE)->SetWindowTextW(text);
}

COLORREF CLedAppDlg::GetFontColor()
{
	CComboBox *pFontColorComboBox = (CComboBox*)GetDlgItem(IDC_FONT_COLOR);
	int index = pFontColorComboBox->GetCurSel();

	switch (index)
	{
	case 0:
		return RGB(255, 0, 0);
	case 1:
		return RGB(0, 255, 0);
	case 2:
		return RGB(255, 255, 0);
	}

	return RGB(255, 0, 0);
}

void CLedAppDlg::SetFontColor(int index)
{
	CComboBox *pFontColorComboBox = (CComboBox*)GetDlgItem(IDC_FONT_COLOR);
	pFontColorComboBox->SetCurSel(index);
}

int CLedAppDlg::GetContentStyle()
{
	CComboBox *pContentStyleComboBox = (CComboBox*)GetDlgItem(IDC_CONTENT_STYLE);
	
	return pContentStyleComboBox->GetCurSel();
}

void CLedAppDlg::SetContentStyle(int style)
{
	CComboBox *pContentStyleComboBox = (CComboBox*)GetDlgItem(IDC_CONTENT_STYLE);
	
	pContentStyleComboBox->SetCurSel(style);
}

int CLedAppDlg::GetContentSpeed()
{
	CString text;

	GetDlgItem(IDC_CONTENT_SPEED)->GetWindowTextW(text);

	return _wtoi(text);
}

void CLedAppDlg::SetContentSpeed(int speed)
{
	CString text;

	text.Format(L"%d", speed);
	GetDlgItem(IDC_CONTENT_SPEED)->SetWindowTextW(text);
}

int CLedAppDlg::GetContentTime()
{
	CString text;

	GetDlgItem(IDC_CONTENT_TIME)->GetWindowTextW(text);

	return _wtoi(text);
}

void CLedAppDlg::SetContentTime(int second)
{
	CString text;

	text.Format(L"%d", second);
	GetDlgItem(IDC_CONTENT_TIME)->SetWindowTextW(text);
}

string CLedAppDlg::GetIPAddress()
{
	CString ipAddress;
	char ansiIPAddress[128];

	GetDlgItem(IDC_IP_ADDRESS)->GetWindowTextW(ipAddress);
	WideCharToMultiByte(CP_ACP, 0, ipAddress, -1, ansiIPAddress, 128, NULL, NULL);

	return ansiIPAddress;
}

void CLedAppDlg::SetIPAddress(CString ipAddress)
{
	GetDlgItem(IDC_IP_ADDRESS)->SetWindowTextW(ipAddress);
}

int CLedAppDlg::GetTCPPort()
{
	CString text;

	GetDlgItem(IDC_TCP_PORT)->GetWindowTextW(text);

	return _wtoi(text);
}

void CLedAppDlg::SetTCPPort(int tcpPort)
{
	CString text;

	text.Format(L"%d", tcpPort);
	GetDlgItem(IDC_TCP_PORT)->SetWindowTextW(text);
}

void CLedAppDlg::EnableDynamicArea(BOOL enable)
{
	GetDlgItem(IDC_AREA_LIST)->EnableWindow(enable);
	//GetDlgItem(IDC_DELETE_AREA)->EnableWindow(enable);
	GetDlgItem(IDC_AREA_LEFT)->EnableWindow(enable);
	GetDlgItem(IDC_AREA_TOP)->EnableWindow(enable);
	GetDlgItem(IDC_AREA_WIDTH)->EnableWindow(enable);
	GetDlgItem(IDC_AREA_HEIGHT)->EnableWindow(enable);
	GetDlgItem(IDC_ADD_AREA)->EnableWindow(enable);
}
	
void CLedAppDlg::EnableDynamicAreaContent(BOOL enable)
{
	GetDlgItem(IDC_CONTENT_LIST)->EnableWindow(enable);
	GetDlgItem(IDC_ADD_FILE)->EnableWindow(enable);
	GetDlgItem(IDC_ADD_TEXT)->EnableWindow(enable);
	GetDlgItem(IDC_DELETE_CONTENT)->EnableWindow(enable);
	GetDlgItem(IDC_SINGLE_LINE)->EnableWindow(enable);
	GetDlgItem(IDC_FONT_LIST)->EnableWindow(enable);
	GetDlgItem(IDC_FONT_SIZE)->EnableWindow(enable);
	GetDlgItem(IDC_FONT_COLOR)->EnableWindow(enable);
	GetDlgItem(IDC_CONTENT_STYLE)->EnableWindow(enable);
	GetDlgItem(IDC_CONTENT_SPEED)->EnableWindow(enable);
	GetDlgItem(IDC_CONTENT_TIME)->EnableWindow(enable);
	GetDlgItem(IDC_UPDATE_AREA)->EnableWindow(enable);
	GetDlgItem(IDC_REMOVE_AREA)->EnableWindow(enable);
	GetDlgItem(IDC_CLEAR_AREA)->EnableWindow(enable);
}

void CLedAppDlg::OnBnClickedSetScreen()
{
	DeleteScreen_Dynamic(1);

	CommunicationMode mode = GetCommunicationMode();

	if (mode == SEND_MODE_SERIALPORT)
	{
		if (RETURN_NOERROR == AddScreen_Dynamic(
			(int)GetControllerType(),
			1,
			(int)GetCommunicationMode(),
			GetScreenWidth(),
			GetScreenHeight(),
			2,
			1,
			GetCOMPort(),
			GetBaudRate(),
			"",
			5005,
			0,
			"",
			"",
			"",
			5005,
			"",
			"",
			""
			))
		{
			EnableDynamicArea(TRUE);
		}
	}
	else if (mode == SEND_MODE_NETWORK)
	{
		if (!ValidateNetworkSetting())
		{
			return;
		}

		string ipAddress = GetIPAddress();
		char *pIPAddress = (char*)ipAddress.c_str();

		if (RETURN_NOERROR == AddScreen_Dynamic(
			(int)GetControllerType(),
			1,
			(int)GetCommunicationMode(),
			GetScreenWidth(),
			GetScreenHeight(),
			2,
			1,
			GetCOMPort(),
			GetBaudRate(),
			pIPAddress,
			GetTCPPort(),
			0,
			"",
			"",
			"",
			5005,
			"",
			"",
			""
			))
		{
			EnableDynamicArea(TRUE);
		}
	}
}

void CLedAppDlg::OnCbnSelchangeAreaList()
{
	ShowAreaInfo();
	ShowAreaContents();
	RefreshDynamicAreaContentControls();
}

void CLedAppDlg::OnBnClickedAddArea()
{
	CComboBox *pAreaListComboBox = (CComboBox*)GetDlgItem(IDC_AREA_LIST);
	int areaID = GetFirstFreeAreaID();
	int left = GetAreaLeft();
	int top = GetAreaTop();
	int width = GetAreaWidth();
	int height = GetAreaHeight();

	if (areaID == -1)
	{
		MessageBox(L"Can't add more area", L"Error", MB_OK | MB_ICONERROR);
		return ;
	}

	if (RETURN_NOERROR == AddScreenDynamicArea(1, areaID, 0, 1, 1, "", 1, left, top, width, height, 255, 0, 255, 1, 0, 1))
	{
		DynamicArea *pNewArea = new DynamicArea();
		pNewArea->areaID = areaID;
		pNewArea->left = left;
		pNewArea->top = top;
		pNewArea->width = width;
		pNewArea->height = height;
		m_areaList.push_back(pNewArea);

		CString text;
		text.Format(L"%d", areaID);
		
		int index = pAreaListComboBox->AddString(text);
		pAreaListComboBox->SetItemData(index, (DWORD_PTR)pNewArea);

		pAreaListComboBox->SetCurSel(index);
		ShowAreaInfo();
		ShowAreaContents();
		RefreshDynamicAreaContentControls();
	}

	GetDlgItem(IDC_REMOVE_AREA)->EnableWindow(TRUE);
	GetDlgItem(IDC_CLEAR_AREA)->EnableWindow(TRUE);
}

int CLedAppDlg::GetFirstFreeAreaID()
{
	BOOL areaStatus[MAX_AREA_COUNT];

	for (int i = 0; i < MAX_AREA_COUNT; ++i)
	{
		areaStatus[i] = FALSE;
	}

	for	(list<DynamicArea*>::iterator iter = m_areaList.begin(); iter != m_areaList.end(); ++iter)
	{
		areaStatus[(*iter)->areaID] = TRUE;
	}

	for	(int i = 0; i < MAX_AREA_COUNT; ++i)
	{
		if (!areaStatus[i])
			return i;
	}

	return -1;
}

void CLedAppDlg::ShowAreaInfo()
{
	CComboBox *pAreaListComboBox = (CComboBox*)GetDlgItem(IDC_AREA_LIST);
	CString areaInfo;
	int index = pAreaListComboBox->GetCurSel();

	if (index >= 0)
	{
		DynamicArea *pArea = (DynamicArea*)pAreaListComboBox->GetItemData(index);

		areaInfo.Format(L"x = %d, y = %d, w = %d, h = %d", pArea->left, pArea->top, pArea->width, pArea->height);
	}

	GetDlgItem(IDC_AREA_INFO)->SetWindowTextW(areaInfo);
}

void CLedAppDlg::ShowAreaContents()
{
	CListBox *pAreaContentsListBox = (CListBox*)GetDlgItem(IDC_CONTENT_LIST);
	pAreaContentsListBox->ResetContent();

	CComboBox *pAreaListComboBox = (CComboBox*)GetDlgItem(IDC_AREA_LIST);
	int index = pAreaListComboBox->GetCurSel();

	if (index >= 0)
	{
		DynamicArea *pArea = (DynamicArea*)pAreaListComboBox->GetItemData(index);

		for (vector<CString>::iterator iter = pArea->contents.begin(); iter != pArea->contents.end(); ++iter)
		{
			pAreaContentsListBox->AddString(*iter);
		}
	}
}

void CLedAppDlg::RefreshDynamicAreaContentControls()
{
	CComboBox *pAreaListComboBox = (CComboBox*)GetDlgItem(IDC_AREA_LIST);
	int index = pAreaListComboBox->GetCurSel();

	EnableDynamicAreaContent(index >= 0);
}

void CLedAppDlg::OnBnClickedRemoveArea()
{
	CComboBox *pAreaListComboBox = (CComboBox*)GetDlgItem(IDC_AREA_LIST);
	int index = pAreaListComboBox->GetCurSel();

	if (index == -1)
		return;

	DynamicArea *pArea = (DynamicArea*)pAreaListComboBox->GetItemData(index);

	/*if (RETURN_NOERROR == DeleteScreenDynamicArea(1, pArea->areaID))
	{
		m_areaList.remove(pArea);
		pAreaListComboBox->DeleteString(index);
	}*/

	char areaIDText[8];
	sprintf_s(areaIDText, 8, "%d", pArea->areaID);

	SendDeleteDynamicAreasCommand(1, 0, areaIDText);
	m_areaList.remove(pArea);
	pAreaListComboBox->DeleteString(index);

	if (pAreaListComboBox->GetCount() > 0)
	{
		pAreaListComboBox->SetCurSel(0);
	}
	else
	{
		pAreaListComboBox->SetCurSel(-1);
		GetDlgItem(IDC_REMOVE_AREA)->EnableWindow(FALSE);
		GetDlgItem(IDC_CLEAR_AREA)->EnableWindow(FALSE);
	}

	ShowAreaInfo();
	ShowAreaContents();
	RefreshDynamicAreaContentControls();
}

void CLedAppDlg::OnBnClickedAddFile()
{
	CComboBox *pAreaListComboBox = (CComboBox*)GetDlgItem(IDC_AREA_LIST);
	int index = pAreaListComboBox->GetCurSel();

	if (index == -1)
		return;

	DynamicArea *pArea = (DynamicArea*)pAreaListComboBox->GetItemData(index);

	CFileDialog ofd(TRUE, L".txt", L"", OFN_FILEMUSTEXIST, L"Txt Files (*.txt)|*.txt||", this);

	if (ofd.DoModal() == IDOK)
	{
		CString filename = ofd.GetPathName();
		HANDLE hFile = CreateFile(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
		
		if (hFile != INVALID_HANDLE_VALUE)
		{
			DWORD textLength = GetFileSize(hFile, NULL) + 10;
			char *ansiText = new char[textLength];
			DWORD readLength;

			memset(ansiText, 0, textLength);
			ReadFile(hFile, (LPVOID)ansiText, textLength, &readLength, NULL);

			CString fontName = GetFontName();
			char ansiFontName[MAX_PATH];
			int fontSize = GetFontSize();
			int fontColor = (int)GetFontColor();
			int contentStyle = GetContentStyle();
			int contentSpeed = GetContentSpeed();
			int contentTime = GetContentTime();

			if (RETURN_NOERROR == AddScreenDynamicAreaText(1, pArea->areaID, ansiText, GetSingleLine(), ansiFontName, fontSize, 0, fontColor, contentStyle, contentSpeed, contentTime))
			{
				int wideTextLength = MultiByteToWideChar(CP_ACP, 0, ansiText, -1, NULL, 0);
				WCHAR *wideText = new WCHAR[wideTextLength];

				MultiByteToWideChar(CP_ACP, 0, ansiText, -1, wideText, wideTextLength);
				pArea->contents.push_back(CString(wideText));

				delete [] wideText;
			}

			delete [] ansiText;

			CloseHandle(hFile);
		}
	}

	ShowAreaContents();
}

void CLedAppDlg::OnBnClickedAddText()
{
	CInputTextDlg dlg;

	if (dlg.DoModal() == IDOK)
	{
		CComboBox *pAreaListComboBox = (CComboBox*)GetDlgItem(IDC_AREA_LIST);
		int index = pAreaListComboBox->GetCurSel();
		DynamicArea *pArea = (DynamicArea*)pAreaListComboBox->GetItemData(index);

		CString text = dlg.GetText();
		int ansiTextLength = WideCharToMultiByte(CP_ACP, 0, text, -1, NULL, 0, NULL, NULL);

		char *ansiText = new char[ansiTextLength];
		memset(ansiText, 0, ansiTextLength);
		WideCharToMultiByte(CP_ACP, 0, text, -1, ansiText, ansiTextLength, NULL, NULL);

		int singleLine = GetSingleLine();
		CString fontName = GetFontName();
		char ansiFontName[MAX_PATH];
		int fontSize = GetFontSize();
		int fontColor = (int)GetFontColor();
		int contentStyle = GetContentStyle();
		int contentSpeed = GetContentSpeed();
		int contentTime = GetContentTime();

		if (RETURN_NOERROR == AddScreenDynamicAreaText(1, pArea->areaID, ansiText, GetSingleLine(), ansiFontName, fontSize, 0, fontColor, contentStyle, contentSpeed, contentTime))
		{
			pArea->contents.push_back(text);
		}

		delete [] ansiText;
	}

	ShowAreaContents();
}

void CLedAppDlg::OnBnClickedUpdateArea()
{
	CComboBox *pAreaListComboBox = (CComboBox*)GetDlgItem(IDC_AREA_LIST);
	int index = pAreaListComboBox->GetCurSel();
	DynamicArea *pArea = (DynamicArea*)pAreaListComboBox->GetItemData(index);
	SendDynamicAreaInfoCommand(1, pArea->areaID);
}

void CLedAppDlg::OnBnClickedClearArea()
{
	SendDeleteDynamicAreasCommand(1, 1, "");

	CComboBox *pAreaListComboBox = (CComboBox*)GetDlgItem(IDC_AREA_LIST);
	pAreaListComboBox->ResetContent();
	ShowAreaInfo();
	ShowAreaContents();
	RefreshDynamicAreaContentControls();
}

void CLedAppDlg::OnBnClickedDeleteContent()
{
	CListBox *pAreaContentListBox = (CListBox*)GetDlgItem(IDC_CONTENT_LIST);
	int index = pAreaContentListBox->GetCurSel();

	if (index >= 0)
	{
		CComboBox *pAreaListComboBox = (CComboBox*)GetDlgItem(IDC_AREA_LIST);
		int index2 = pAreaListComboBox->GetCurSel();

		if (index2 == -1)
			return;

		DynamicArea *pArea = (DynamicArea*)pAreaListComboBox->GetItemData(index2);

		DeleteScreenDynamicAreaFile(1, pArea->areaID, index);
		pArea->contents.erase(pArea->contents.begin() + index);
	}

	ShowAreaContents();
}

void CLedAppDlg::OnCbnSelchangePortType()
{
	CommunicationMode mode = GetCommunicationMode();

	ShowPortGroupText();

	if (mode == SEND_MODE_SERIALPORT)
	{
		ShowSerialSetttings();
	}
	else if (mode == SEND_MODE_NETWORK)
	{
		ShowNetworkSettings();
	}
}

void CLedAppDlg::ShowSerialSetttings()
{
	GetDlgItem(IDC_SERIAL_LABEL)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_SERIAL_PORT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BAUDRATE_LABEL)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BAUD_RATE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_IPADDR_LABEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_IP_ADDRESS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_PORT_LABEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TCP_PORT)->ShowWindow(SW_HIDE);
}
	
void CLedAppDlg::ShowNetworkSettings()
{
	GetDlgItem(IDC_SERIAL_LABEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_SERIAL_PORT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BAUDRATE_LABEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BAUD_RATE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_IPADDR_LABEL)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_IP_ADDRESS)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_PORT_LABEL)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_TCP_PORT)->ShowWindow(SW_SHOW);
}

void CLedAppDlg::ShowPortGroupText()
{
	CString text;
	CComboBox *pPortComboBox = (CComboBox*)GetDlgItem(IDC_PORT_TYPE);

	pPortComboBox->GetLBText(pPortComboBox->GetCurSel(), text);
	GetDlgItem(IDC_PORT_GROUP)->SetWindowTextW(text);
}

BOOL CLedAppDlg::ValidateNetworkSetting()
{
	CString INVALID_IP_ADDRESS = L"无效的IP地址";
	CString INVALID_TCP_PORT = L"无效的端口(1 - 65535)";

	string ipAddress = GetIPAddress();
	if (!IsValidIP(ipAddress))
	{
		MessageBox(INVALID_IP_ADDRESS, L"Error", MB_OK | MB_ICONERROR);
		GetDlgItem(IDC_IP_ADDRESS)->SetFocus();
		return FALSE;
	}

	int port = GetTCPPort();
	if ((port <= 0) || (port > 65535))
	{
		MessageBox(INVALID_TCP_PORT, L"Error", MB_OK | MB_ICONERROR);
		GetDlgItem(IDC_TCP_PORT)->SetFocus();
		return FALSE;
	}

	return TRUE;
}

BOOL CLedAppDlg::IsValidIP(string &ip)
{
    string delim=".";
    string ret[4];
 
    string::size_type loc=0,start =0;
    for(int i=0;i<4;i++){
        loc = ip.find(delim, start);
        if(loc != string::npos){
            ret[i]=ip.substr(start,loc-start);
            start=loc+1;
        }else if(i==3){
            ret[i]=ip.substr(start);
        }else{
            //格式不对，应该有3个.
            return FALSE;
        }
    }
    for(int i=0;i<4;i++){
        int num=atoi(ret[i].c_str());
        if(num>255){
            return FALSE;
        }else if((num==0)&&(ret[i].compare("0"))){
            return FALSE;
        }
    }
 
    return TRUE;
}