// LedAppDlg.h : header file
//

#pragma once

#include <list>
#include <string>
using namespace std;

#include "LedDynamicArea.h"

#include "DynamicArea.h"

typedef int(__stdcall *pInitialize)();	//初始化动态库
typedef int(__stdcall *pUninitialize)();	//释放动态库
typedef int(__stdcall *pAddScreen_Dynamic)(int nControlType, int nScreenNo, int nSendMode, int nWidth, int nHeight,
      int nScreenType, int nPixelMode, char* pCom, int nBaud, char* pSocketIP, int nSocketPort, int nServerMode,
      char* pBarcode, char* pNetworkID, char* pServerIP, int nServerPort, char* pServerAccessUser, char* pServerAccessPassword,
      char* pCommandDataFile);
typedef int(__stdcall *pQuerryServerDeviceList)(int nScreenNo, byte pDeviceList[], int &nDeviceCount);
typedef int(__stdcall *pBindServerDevice)(int nScreenNo, char* pBarcode, char* pNetworkId);
typedef int(__stdcall *pAddScreenDynamicArea)(int nScreenNo, int nDYAreaID, int nRunMode,
    int nTimeOut, int nAllProRelate, char* pProRelateList, int nPlayImmediately,
    int nAreaX, int nAreaY, int nAreaWidth, int nAreaHeight, int nAreaFMode, int nAreaFLine, int nAreaFColor,
    int nAreaFStunt, int nAreaFRunSpeed, int nAreaFMoveStep);
typedef int(__stdcall *pAddScreenDynamicAreaFile)(int nScreenNo, int nDYAreaID,
    char* pFileName, int nShowSingle, char* pFontName, int nFontSize, int nBold, int nFontColor,
    int nStunt, int nRunSpeed, int nShowTime);
typedef int(__stdcall *pAddScreenDynamicAreaText)(int nScreenNo, int nDYAreaID,
    char* pText, int nShowSingle, char* pFontName, int nFontSize, int nBold, int nFontColor,
    int nStunt, int nRunSpeed, int nShowTime);
typedef int(__stdcall *pDeleteScreen_Dynamic)(int nScreenNo);
typedef int(__stdcall *pDeleteScreenDynamicArea)(int nScreenNo, int nDYAreaID);
typedef int(__stdcall *pDeleteScreenDynamicAreaFile)(int nScreenNo, int nDYAreaID, int nFileOrd);
typedef int(__stdcall *pSendDynamicAreaInfoCommand)(int nScreenNo, int nDYAreaID);
typedef int(__stdcall *pSendDeleteDynamicAreasCommand)(int nScreenNo, int nDelAllDYArea, char* pDYAreaIDList);

// CLedAppDlg dialog
class CLedAppDlg : public CDialog
{
// Construction
public:
	CLedAppDlg(CWnd* pParent = NULL);	// standard constructor
	~CLedAppDlg();

	void InsertFontName(CString fontName);


// Dialog Data
	enum { IDD = IDD_LEDAPP_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
#endif
	DECLARE_MESSAGE_MAP()

private:
	HINSTANCE m_hLedDynamicArea;

	pInitialize Initialize;
	pUninitialize Uninitialize;
	pAddScreen_Dynamic AddScreen_Dynamic;
	pQuerryServerDeviceList QuerryServerDeviceList;
	pBindServerDevice BindServerDevice;
	pAddScreenDynamicArea AddScreenDynamicArea;
	pAddScreenDynamicAreaFile AddScreenDynamicAreaFile;
	pAddScreenDynamicAreaText AddScreenDynamicAreaText;
	pDeleteScreen_Dynamic DeleteScreen_Dynamic;
	pDeleteScreenDynamicArea DeleteScreenDynamicArea;
	pDeleteScreenDynamicAreaFile DeleteScreenDynamicAreaFile;
	pSendDynamicAreaInfoCommand SendDynamicAreaInfoCommand;
	pSendDeleteDynamicAreasCommand SendDeleteDynamicAreasCommand;

	list<DynamicArea*> m_areaList;

	afx_msg void OnBnClickedSetScreen();
	afx_msg void OnBnClickedDo();
	afx_msg void OnBnClickedClear();
	afx_msg void OnCbnSelchangeAreaList();
	afx_msg void OnBnClickedAddArea();
	afx_msg void OnBnClickedRemoveArea();
	afx_msg void OnBnClickedAddFile();
	afx_msg void OnBnClickedAddText();
	afx_msg void OnBnClickedUpdateArea();
	afx_msg void OnBnClickedClearArea();
	afx_msg void OnBnClickedDeleteContent();
	afx_msg void OnCbnSelchangePortType();

	ControllerType GetControllerType();
	void SetControllerType(ControllerType type);
	CommunicationMode GetCommunicationMode();
	void SetCommunicationMode(CommunicationMode mode);
	int GetScreenWidth();
	void SetScreenWidth(int width);
	int GetScreenHeight();
	void SetScreenHeight(int height);
	char* GetCOMPort();
	void SetCOMPort(const WCHAR *pCOMPort);
	int GetBaudRate();
	void SetBaudRate(int baudRate);

	int GetAreaLeft();
	void SetAreaLeft(int left);
	int GetAreaTop();
	void SetAreaTop(int top);
	int GetAreaWidth();
	void SetAreaWidth(int width);
	int GetAreaHeight();
	void SetAreaHeight(int height);

	int GetSingleLine();
	void SetSingleLine(int singleLine);
	CString GetFontName();
	void SetFontName(CString fontName);
	int GetFontSize();
	void SetFontSize(int fontSize);
	COLORREF GetFontColor();
	void SetFontColor(int index);
	int GetContentStyle();
	void SetContentStyle(int style);
	int GetContentSpeed();
	void SetContentSpeed(int speed);
	int GetContentTime();
	void SetContentTime(int second);
	string GetIPAddress();
	void SetIPAddress(CString ipAddress);
	int GetTCPPort();
	void SetTCPPort(int tcpPort);

	int GetFirstFreeAreaID();

	void EnableDynamicArea(BOOL enable);
	void EnableDynamicAreaContent(BOOL enable);

	void ShowAreaInfo();
	void ShowAreaContents();
	void RefreshDynamicAreaContentControls();

	void FillCommunicationModeComboBox();
	void FillFontColorComboBox();
	void FillFontListComboBox();
	void FillContentStyle();

	void ShowSerialSetttings();
	void ShowNetworkSettings();
	void ShowPortGroupText();

	BOOL ValidateNetworkSetting();
	BOOL IsValidIP(string &ip);
};
