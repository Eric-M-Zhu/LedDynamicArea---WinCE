// LedAppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LedApp.h"
#include "LedAppDlg.h"

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
		delete *iter;
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
	ON_BN_CLICKED(IDC_DO, &CLedAppDlg::OnBnClickedDo)
	ON_BN_CLICKED(IDC_CLEAR, &CLedAppDlg::OnBnClickedClear)
	ON_BN_CLICKED(IDC_SET_SCREEN, &CLedAppDlg::OnBnClickedSetScreen)
	ON_CBN_SELCHANGE(IDC_AREA_LIST, &CLedAppDlg::OnCbnSelchangeAreaList)
	ON_BN_CLICKED(IDC_ADD_AREA, &CLedAppDlg::OnBnClickedAddArea)
	ON_BN_CLICKED(IDC_REMOVE_AREA, &CLedAppDlg::OnBnClickedRemoveArea)
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
	SetControllerType(BX_5E3);
	SetCommunicationMode(SEND_MODE_SERIALPORT);
	SetScreenWidth(96);
	SetScreenHeight(32);
	SetCOMPort(L"COM3");
	SetBaudRate(57600);

	SetAreaLeft(16);
	SetAreaTop(0);
	SetAreaWidth(64);
	SetAreaHeight(16);
	
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
}

void CLedAppDlg::OnBnClickedSetScreen()
{
	DeleteScreen_Dynamic(1);

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

void CLedAppDlg::OnCbnSelchangeAreaList()
{
	ShowAreaInfo();
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

	if (RETURN_NOERROR == DeleteScreenDynamicArea(1, pArea->areaID))
	{
		m_areaList.remove(pArea);
		pAreaListComboBox->DeleteString(index);
	}

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
	RefreshDynamicAreaContentControls();
}
