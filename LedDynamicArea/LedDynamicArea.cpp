#include "stdafx.h"
#include "LedDynamicArea.h"

#include "MyDataType.h"
#include "SendInfo.h"
#include "Unit_build.h"
#include "TranInfo.h"

//#pragma comment(lib, "../progwince_sdk (armv4i)/Debug/jsoncpp.lib")
//#pragma comment(lib, "ws2_32.lib")

static CRITICAL_SECTION g_cs;
static WSADATA wsaData;
static SOCKET g_socket;
Json::Value g_ControllerList_Obj;
Json::Value g_Controller_Supary;
Json::Value devicelist_root;
Json::Value devicelist_ja;
static vector<PtagSendThread> g_lstSendThread;

static void SaveScreenInfoToFile();

/*------------------------------------------------------------------------------ -
������:    Initialize
	��ʼ����̬�⣻�ú���������ʾ��ͨѶ��
���� :
����ֵ : �������״̬���붨�塣
------------------------------------------------------------------------------ -*/
int __stdcall Initialize()
{
	Json::Reader reader;

	InitializeCriticalSection(&g_cs);
	CreateFrameArray(PROGRAM_FRAME_SINGLE_COLOR_COUNT, PROGRAM_FRAME_MULI_COLOR_COUNT);
	//// TODO: GetCRC16ByteArray
	//// TODO: Create send threads list
	WSAStartup(MAKEWORD(1, 1), &wsaData);
	GetControllerList(g_ControllerList_Obj, g_Controller_Supary);

	reader.parse("{\"ScreenList\"] = []}", devicelist_root, false);
	devicelist_ja = devicelist_root["ScreenList"];

	return RETURN_NOERROR;
}

/*------------------------------------------------------------------------------ -
������:    Uninitialize
	�ͷŶ�̬�⣻�ú���������ʾ��ͨѶ��
���� :
����ֵ : �������״̬���붨�塣
------------------------------------------------------------------------------ -*/
int __stdcall Uninitialize()
{
	WSACleanup();
	for (vector<PtagSendThread>::iterator iter = g_lstSendThread.begin(); iter != g_lstSendThread.end(); ++iter)
	{
		delete *iter;
	}
	g_lstSendThread.clear();
	DeleteCriticalSection(&g_cs);
	return RETURN_NOERROR;
}

/*------------------------------------------------------------------------------ -
������:    AddScreen_Dynamic
	��̬���������ʾ����Ϣ���ú���������ʾ��ͨѶ��
���� :
	nControlType : ��ʾ���Ŀ������ͺţ�Ŀǰ�ö�̬����̬��ֻ֧��BX - 5E1��BX - 5E2��BX - 5E3��BX - 5Eϵ�к�5Q + ϵ�п�������
	nScreenNo����ʾ�����ţ��ò�����LedshowTW 2013�����"��������"ģ���"����"����һ�¡�
	nSendMode��ͨѶģʽ��Ŀǰ��̬����֧��0 : ����ͨѶ��2������ͨѶ��5�����浽�ļ�������ͨѶģʽ��
	nWidth����ʾ����ȣ���λ�����ء�
	nHeight����ʾ���߶ȣ���λ�����ء�
	nScreenType����ʾ�����ͣ�1������ɫ��2��˫��ɫ; 3:˫��ɫ 4 : ȫ��ɫ 5 : ˫��ɫ�Ҷȡ�
	nPixelMode���������ͣ�ֻ����ʾ������Ϊ˫��ɫʱ��Ч��1��R + G��2��G + R��
	pCom��ͨѶ���ڣ�ֻ���ڴ���ͨѶʱ�ò�����Ч������"COM1"
	nBaud��ͨѶ���ڲ����ʣ�ֻ���ڴ���ͨѶʱ�ò�����Ч��Ŀǰֻ֧��9600��57600���ֲ����ʡ�
	pSocketIP����������IP��ַ��ֻ��������ͨѶģʽ�¸ò�����Ч������"192.168.0.199"
	nSocketPort���������Ķ˿ڵ�ַ��ֻ��������ͨѶģʽ�¸ò�����Ч������5005
	nServerMode : 0 : ������ģʽδ������1��������ģʽ������
	pBarcode : �豸������
	pNetworkID : ����ID���
	pServerIP : ��ת������IP��ַ
	nServerPort : ��ת����������˿�
	pServerAccessUser : ��ת�����������û���
	pServerAccessPassword : ��ת��������������
	pCommandDataFile�����浽�ļ���ʽʱ������������ļ����ơ�ֻ���ڱ��浽�ļ�ģʽ�¸ò�����Ч������"curCommandData.dat"
����ֵ : �������״̬���붨�塣
------------------------------------------------------------------------------ - */
int __stdcall AddScreen_Dynamic(int nControlType, int nScreenNo, int nSendMode,
	int nWidth, int nHeight, int nScreenType, int nPixelMode, const char *pCom, int nBaud, const char *pSocketIP, int nSocketPort,
	int nServerMode, const char *pBarcode, const char *pNetworkID, const char *pServerIP, int nServerPort,
	const char *pServerAccessUser, const char *pServerAccessPassword, const char *pCommandDataFile)
{
	int nScreenOrd = GetSelScreenArrayOrd(nScreenNo, devicelist_ja);
	int nEncryptionType;
	SYSTEMTIME now;
	char tmpSrc[16];
	Json::Value Controller_obj;
	Json::Value newScreen;
	unsigned char nProtocolVer;
	PtagSendThread pNewThread;

	if (nScreenOrd >= 0)
	{
		return RETURN_ERROR_RA_SCREENNO;
	}

#ifdef _DEBUG
	nEncryptionType = ENCRYPTION_NONE;
#else // _DEBUG
	nEncryptionType = ENCRYPTION_STATIC;
#endif // _DEBUG

	GetLocalTime(&now);
	sprintf_s(tmpSrc, 16, "SC%02d%02d%02d%02d%02d%03d", now.wMonth,
		now.wDay,
		now.wHour,
		now.wMinute,
		now.wSecond,
		now.wMilliseconds);
	Controller_obj = GetControllerObject(g_Controller_Supary, nControlType, nProtocolVer);

	newScreen["Screen_src"] = tmpSrc;
	newScreen["Screen_CommandDataFile"] = pCommandDataFile;
	newScreen["Screen_Reality_Memory"] = MEMORY_REALITY_BX_4A;
	newScreen["Screen_control"] = nControlType; //����������� ���� ���� GPRS
	newScreen["Screen_SendMode"] = nSendMode; //ͨѶģʽ
	newScreen["Screen_ProtocolVer"] = nProtocolVer;
	newScreen["Screen_Width"] = nWidth; //���
	newScreen["Screen_Height"] = nHeight; //�߶�
	newScreen["Screen_color"] = nScreenType; //��ɫ
	newScreen["Screen_pixels"] = nPixelMode; //����
	newScreen["Screen_nPixType"] = 8; //���򳤶ȵ�����λ Ĭ��Ϊ8
	newScreen["Screen_ReadWaitTimeOut"] = WAIT_TIMEOUT_SERIALPORT + 2; //��2��֤���ƿ��ĺ����¼����ڿ��ƿ�ʱ��������ͣ��ʱ��

	//���ڵĲ���
	newScreen["Com_port"] = atoi(pCom + 3);
	newScreen["Com_baudrate"] = nBaud;
	newScreen["Com_address"] = nScreenNo;

	//GPRS�Ĳ���
	newScreen["Gprs_style"] = 0;
	newScreen["Gprs_ip"] = "192.168.0.235";
	newScreen["Gprs_id"] = "BX-GP000000";
	newScreen["Gprs_sim"] = "00000000000";
	newScreen["Gprs_port"] = 8000;
	newScreen["Gprs_level"] = 0;
	newScreen["Gprs_Unitsize"] = 900;
	newScreen["Gprs_Unittime"] = 2000;

	//���ڵĲ���
	newScreen["Net_IP"] = pSocketIP;
	newScreen["Net_ConnnectMode"] = NET_CONNECT_STATICIP;
	newScreen["Net_ServerMode"] = nServerMode; /* ������ģʽ�� 1--ʹ�ܣ�0-��ֹ */
	newScreen["Net_ServerIP"] = pServerIP;
	newScreen["Net_ServerPort"] = nServerPort;
	newScreen["Net_ServerAccessUser"] = pServerAccessUser;
	newScreen["Net_ServerAccessPassword"] = pServerAccessPassword;
	newScreen["Net_ServerHeartBeatInterval"] = 20; /* ����ʱ��������λ���룩*/
	newScreen["Net_mark"] = "255.255.255.0";
	newScreen["Net_port"] = nSocketPort;
	newScreen["Net_gateway"] = "192.168.0.1";
	newScreen["Transit_Barcode"] = pBarcode;
	newScreen["Network_ID"] = pNetworkID;
	newScreen["Net_mac"] = "";

	newScreen["Screen_Light"] = 15; //����
	newScreen["Screen_AdjustLightMode"] = 0; //���ȵ���ģʽ

	newScreen["Screen_LightTime1Use"] = false;
	newScreen["Screen_LightTime1"] = "06:30";
	newScreen["Screen_LightValue1"] = 15;
	newScreen["Screen_LightTime2Use"] = false;
	newScreen["Screen_LightTime2"] = "10:30";
	newScreen["Screen_LightValue2"] = 15;
	newScreen["Screen_LightTime3Use"] = false;
	newScreen["Screen_LightTime3"] = "12:30";
	newScreen["Screen_LightValue3"] = 15;
	newScreen["Screen_LightTime4Use"] = false;
	newScreen["Screen_LightTime4"] = "17:30";
	newScreen["Screen_LightValue4"] = 15;

	newScreen["Screen_Power"] = 0;
	newScreen["Screen_Powerstate"] = 0;
	newScreen["Screen_PowertimeEnabled"] = false; //��ʱ���ػ��Ƿ���Ч��
	newScreen["Screen_Powertime1use"] = false;
	newScreen["Screen_Powertime1on"] = "07:00";
	newScreen["Screen_Powertime1off"] = "07:00";
	newScreen["Screen_Powertime2use"] = false;
	newScreen["Screen_Powertime2on"] = "07:00";
	newScreen["Screen_Powertime2off"] = "07:00";
	newScreen["Screen_Powertime3use"] = false;
	newScreen["Screen_Powertime3on"] = "07:00";
	newScreen["Screen_Powertime3off"] = "07:00";
	newScreen["Screen_PA"] = nEncryptionType; //���������ܷ�ʽ�����Խ׶��趨Ϊ����ģʽ������ʱ����Ϊ�̶�����ģʽ
	newScreen["Screen_PA1"] = ""; //������������
	newScreen["Screen_PA2"] = ""; //������������
	newScreen["Screen_Reserved1"] = 0; //8������������4�����ͣ�4���ַ�����
	newScreen["Screen_Reserved2"] = 0;
	newScreen["Screen_Reserved3"] = 0;
	newScreen["Screen_Reserved4"] = 0;
	newScreen["Screen_Reserved5"] = "";
	newScreen["Screen_Reserved6"] = "";
	newScreen["Screen_Reserved7"] = "";
	newScreen["Screen_Reserved8"] = "";
	newScreen["Screen_lstDYArea"] = Json::arrayValue;
	devicelist_ja.append(newScreen);

	pNewThread = new tagSendThread;
	if (pNewThread)
	{
		memset(pNewThread, 0, sizeof(tagSendThread));
		pNewThread->szScreenSrc = tmpSrc;
	}
	else
	{
		return RETURN_ERROR_OTHER;
	}

	g_lstSendThread.push_back(pNewThread);

	return RETURN_NOERROR;
}

/*------------------------------------------------------------------------------ -
������:    AddScreenDynamicArea
	��̬����ָ����ʾ����Ӷ�̬���򣻸ú���������ʾ��ͨѶ��
	���� :
nScreenNo����ʾ�����ţ��ò�����AddScreen_Dynamic�����е�nScreenNo������Ӧ��
nDYAreaID����̬�����ţ�Ŀǰϵͳ�����5����̬���򣻸�ֵȡֵ��ΧΪ0~4;
nRunMode����̬��������ģʽ��
0:��̬������ѭ����ʾ��
1 : ��̬��������ʾ��ɺ�ֹ��ʾ���һҳ���ݣ�
2 : ��̬������ѭ����ʾ�������趨ʱ���������δ����ʱ������ʾ��
3 : ��̬������ѭ����ʾ�������趨ʱ���������δ����ʱ��ʾLogo��Ϣ, Logo ��Ϣ��Ϊ��̬��������һҳ��Ϣ
4 : ��̬������˳����ʾ����ʾ�����һҳ��Ͳ�����ʾ
nTimeOut����̬�����ݳ�ʱʱ�䣻��λ����
nAllProRelate����Ŀ������־��
1�����н�Ŀ����ʾ�ö�̬����
0����ָ����Ŀ����ʾ�ö�̬���������̬����Ҫ�����ڽ�Ŀ��ʾ������һ������Ϊ�ա�
pProRelateList����Ŀ�����б��ý�Ŀ��ű�ʾ����Ŀ��ż���","����, ��Ŀ��Ŷ���ΪLedshowTW 2013�����"P***"�е�"***"
nPlayPriority����̬���򲥷����ȼ���
0���ö�̬�������첽��Ŀһ�𲥷�(��̬�����й����첽��Ŀ����Ч)��
1���첽��Ŀֹͣ���ţ������Ÿö�̬����
nAreaX����̬������ʼ�����ꣻ��λ������
nAreaY����̬������ʼ�����ꣻ��λ������
nAreaWidth����̬�����ȣ���λ������
nAreaHeight����̬����߶ȣ���λ������
nAreaFMode����̬����߿���ʾ��־��0����ɫ��1����ɫ��255���ޱ߿�
nAreaFLine����̬����߿�����, ��ɫ���ȡֵΪFRAME_SINGLE_COLOR_COUNT����ɫ���ȡֵΪ��FRAME_MULI_COLOR_COUNT
nAreaFColor���߿���ʾ��ɫ��ѡ��Ϊ��ɫ�߿�����ʱ�ò�����Ч��
nAreaFStunt���߿������ؼ���
0����˸��1��˳ʱ��ת����2����ʱ��ת����3����˸��˳ʱ��ת����
4:��˸����ʱ��ת����5�����̽�����˸��6�����̽���ת����7����ֹ���
nAreaFRunSpeed���߿������ٶȣ�
nAreaFMoveStep���߿��ƶ���������ֵȡֵ��Χ��1~8��
����ֵ : �������״̬���붨�塣
------------------------------------------------------------------------------ - */

int __stdcall AddScreenDynamicArea(int nScreenNo, int nDYAreaID, int nRunMode, int nTimeOut, int nAllProRelate,
	const char *pProRelateList, int nPlayPriority, int nAreaX, int nAreaY, int nAreaWidth, int nAreaHeight,
	int nAreaFMode, int nAreaFLine, int nAreaFColor, int nAreaFStunt, int nAreaFRunSpeed, int nAreaFMoveStep)
{
	int nScreenOrd = GetSelScreenArrayOrd(nScreenNo, devicelist_ja);
	int nDYAreaOrd;
	Json::Value newDynamicArea;
	string szProRelate;
	list<string> S;

	if (nScreenOrd < 0)
	{
		return RETURN_ERROR_NOFIND_SCREENNO;
	}

	// TODO: Check if is sending

	newDynamicArea["DY_AreaID"] = nDYAreaID;
	newDynamicArea["DY_RunMode"] = nRunMode;
	newDynamicArea["DY_TimeOut"] = nTimeOut;
	newDynamicArea["DY_AllProRelate"] = nAllProRelate;
	newDynamicArea["DY_ProRelateList"] = Json::arrayValue;
	newDynamicArea["DY_PlayImmediately"] = nPlayPriority;
	newDynamicArea["DY_AreaX"] = nAreaX;
	newDynamicArea["DY_AreaY"] = nAreaY;
	newDynamicArea["DY_AreaWidth"] = nAreaWidth;
	newDynamicArea["DY_AreaHeight"] = nAreaHeight;
	newDynamicArea["DY_AreaFStunt"] = nAreaFStunt;
	newDynamicArea["DY_AreaFRunSpeed"] = nAreaFRunSpeed;
	newDynamicArea["DY_AreaFMoveStep"] = nAreaFMoveStep;
	newDynamicArea["DY_AreaFMode"] = nAreaFMode; //0:��ɫ��1����ɫ��$FF:û�б߿�
	newDynamicArea["DY_AreaFWidth"] = 1;
	newDynamicArea["DY_AreaFLine"] = nAreaFLine;
	newDynamicArea["DY_AreaFColor"] = nAreaFColor;
	newDynamicArea["Area_lstfile"] = Json::arrayValue; //������ļ�����
	devicelist_ja[nScreenOrd]["Screen_lstDYArea"].append(newDynamicArea);
	nDYAreaOrd = devicelist_ja[nScreenOrd]["Screen_lstDYArea"].size() - 1;

	if (devicelist_ja[nScreenOrd]["Screen_lstDYArea"][nDYAreaOrd]["DY_AreaFMode"].asInt() == 0)
	{
		if (devicelist_ja[nScreenOrd]["Screen_lstDYArea"][nDYAreaOrd]["DY_AreaFLine"].asInt() >= PROGRAM_FRAME_SINGLE_COLOR_COUNT)
		{
			devicelist_ja[nScreenOrd]["Screen_lstDYArea"][nDYAreaOrd]["DY_AreaFLine"] = 0;
		}
		devicelist_ja[nScreenOrd]["Screen_lstDYArea"][nDYAreaOrd]["DY_AreaFWidth"] =
			GetSelFrameWidth(devicelist_ja[nScreenOrd]["Screen_lstDYArea"][nDYAreaOrd]["DY_AreaFMode"].asUInt(),
				devicelist_ja[nScreenOrd]["Screen_lstDYArea"][nDYAreaOrd]["DY_AreaFLine"].asUInt());
	}
	else if (devicelist_ja[nScreenOrd]["Screen_lstDYArea"][nDYAreaOrd]["DY_AreaFMode"].asInt() == 1)
	{
		if (devicelist_ja[nScreenOrd]["Screen_lstDYArea"][nDYAreaOrd]["DY_AreaFLine"].asInt() >= PROGRAM_FRAME_MULI_COLOR_COUNT)
		{
			devicelist_ja[nScreenOrd]["Screen_lstDYArea"][nDYAreaOrd]["DY_AreaFLine"] = 0;
		}
		devicelist_ja[nScreenOrd]["Screen_lstDYArea"][nDYAreaOrd]["DY_AreaFWidth"] =
			GetSelFrameWidth(devicelist_ja[nScreenOrd]["Screen_lstDYArea"][nDYAreaOrd]["DY_AreaFMode"].asUInt(),
				devicelist_ja[nScreenOrd]["Screen_lstDYArea"][nDYAreaOrd]["DY_AreaFLine"].asUInt());
	}
	else
	{
		devicelist_ja[nScreenOrd]["Screen_lstDYArea"][nDYAreaOrd]["DY_AreaFMode"] = 0xFF;
		devicelist_ja[nScreenOrd]["Screen_lstDYArea"][nDYAreaOrd]["DY_AreaFWidth"] = 0;
	}

	if (nAllProRelate == 0)
	{
		szProRelate = pProRelateList;
		S = SplitString(szProRelate, ",");

		for (list<string>::iterator iter = S.begin(); iter != S.end(); ++iter)
		{
			if (StrIsInt(*iter))
			{
				Json::Value proRelateID;
				proRelateID["RelateProID"] = *iter;
				devicelist_ja[nScreenOrd]["Screen_lstDYArea"][nDYAreaOrd]["DY_ProRelateList"].append(proRelateID);
			}
		}
	}
	else
	{
		devicelist_ja[nScreenOrd]["Screen_lstDYArea"][nDYAreaOrd]["DY_AllProRelate"] = 1;
	}

	return RETURN_NOERROR;
}

/*------------------------------------------------------------------------------ -
������:    AddScreenDynamicAreaText
	��̬����ָ����ʾ����ָ����̬���������Ϣ�ı����ú���������ʾ��ͨѶ��
	���� :
nScreenNo����ʾ�����ţ��ò�����AddScreen_Dynamic�����е�nScreenNo������Ӧ��
nDYAreaID����̬�����ţ��ò�����AddScreenDynamicArea�����е�nDYAreaID������Ӧ
pText����ӵ���Ϣ�ļ����ƣ�Ŀǰֻ֧��txt(֧��ANSI��UTF - 8��Unicode�ȸ�ʽ����)��bmp���ļ���ʽ
nShowSingle��������Ϣ�Ƿ�����ʾ��0��������ʾ��1��������ʾ����ʾ�ò���ֻ��szFileNameΪtxt��ʽ�ĵ�ʱ����Ч��
pFontName��������Ϣ��ʾ���壻�ò���ֻ��szFileNameΪtxt��ʽ�ĵ�ʱ����Ч��
nFontSize��������Ϣ��ʾ������ֺţ��ò���ֻ��szFileNameΪtxt��ʽ�ĵ�ʱ����Ч��
nBold��������Ϣ�Ƿ������ʾ��0��������1��������ʾ���ò���ֻ��szFileNameΪtxt��ʽ�ĵ�ʱ����Ч��
nFontColor��������Ϣ��ʾ��ɫ���ò���ֻ��szFileNameΪtxt��ʽ�ĵ�ʱ����Ч��
nStunt����̬������Ϣ�����ؼ���
00�������ʾ
01����ֹ��ʾ
02�����ٴ��
03�������ƶ�
04����������
05�������ƶ�
06����������
07����˸
08��Ʈѩ
09��ð��
10���м��Ƴ�
11����������
12�����ҽ�������
13�����½�������
14������պ�
15�������
16����������
17����������
18����������
19����������
20����������
21����������
22����������
23����������
24�����ҽ�����Ļ
25�����½�����Ļ
26����ɢ����
27��ˮƽ��ҳ
28����ֱ��ҳ
29��������Ļ
30��������Ļ
31��������Ļ
32��������Ļ
33�����ұպ�
34�����ҶԿ�
35�����±պ�
36�����¶Կ�
37�������ƶ�
38����������
39�������ƶ�
40����������
nRunSpeed����̬������Ϣ�����ٶ�
nShowTime����̬������Ϣ��ʾʱ�䣻��λ��10ms
����ֵ : �������״̬���붨�塣
	------------------------------------------------------------------------------ - */

int __stdcall AddScreenDynamicAreaText(int nScreenNo, int nDYAreaID,
	const char *pText, int nShowSingle, const char *pFontName, int nFontSize,
	int nBold, int nFontColor, int nStunt, int nRunSpeed, int nShowTime)
{
	int nScreenOrd, nDYAreaOrd;
	PtagSendThread ptmptagSendThread;
	string szFileName;
	string szFontName;
	UINT ntmpFileStyle;
	string Ext;
	Json::Value newAreaText;

	nScreenOrd = GetSelScreenArrayOrd(nScreenNo, devicelist_ja);
	if (nScreenOrd == -1)
	{
		return RETURN_ERROR_NOFIND_SCREENNO;
	}

	if ((g_lstSendThread.size() > (size_t)nScreenOrd) && (nScreenOrd >= 0))
	{
		ptmptagSendThread = g_lstSendThread[nScreenOrd];
		if (ptmptagSendThread->bSending)
		{
			return RETURN_ERROR_NOW_SENDING;
		}
	}

	nDYAreaOrd = GetSelScreenDYAreaOrd(nDYAreaID, devicelist_ja[nScreenOrd]["Screen_lstDYArea"]);
	if (nDYAreaOrd == -1)
	{
		return RETURN_ERROR_NOFIND_DYNAMIC_AREA;
	}
	szFileName = pText;
	szFontName = pFontName;
	if (nShowSingle == 1)
		ntmpFileStyle = FILE_SHOWSTYLE_SINGLE;
	else
		ntmpFileStyle = FILE_SHOWSTYLE_NORMAL;

	newAreaText["File_Name"] = szFileName; //�ı�
	newAreaText["File_Style"] = FILE_TYPE_TEXT; //�ı�
	newAreaText["File_ShowStyle"] = ntmpFileStyle; //�ı���ʾ��ʽ
	newAreaText["File_FontName"] = szFontName; // ��������
	newAreaText["File_Bold"] = nBold; //�����Ƿ����
	newAreaText["File_FontSize"] = nFontSize; //�����ֺ�
	newAreaText["File_FontColor"] = nFontColor; //������ɫ
	newAreaText["File_PageCount"] = 0; //ת���ɵ�����ҳ
	newAreaText["File_Speed"] = nRunSpeed; //�ļ��ٶ�
	newAreaText["File_Stunt"] = nStunt; //�ļ��ؼ���ʽ
	newAreaText["File_OutsStunt"] = 0; //�˳���ʽ
	newAreaText["File_Showtime"] = nShowTime; //�ļ�ͣ��ʱ��
	newAreaText["File_ShowCount"] = 1; //�ظ����Ŵ���
	newAreaText["File_Reserved1"] = 0; //��������
	newAreaText["File_Reserved2"] = 0; //��������
	newAreaText["File_Reserved3"] = 0; //��������
	newAreaText["File_Reserved4"] = 0; //��������
	newAreaText["File_Reserved5"] = 0; //��������
	newAreaText["File_Reserved6"] = 0; //��������
	newAreaText["File_Reserved7"] = 0; //��������
	devicelist_ja[nScreenOrd]["Screen_lstDYArea"][nDYAreaOrd]["Area_lstfile"].append(newAreaText);

#ifdef _DEBUG
	SaveScreenInfoToFile();
#endif

	return RETURN_NOERROR;
}

/*------------------------------------------------------------------------------ -
������:    AddScreenDynamicAreaFile
	��̬����ָ����ʾ����ָ����̬���������Ϣ�ļ����ú���������ʾ��ͨѶ��
	���� :
nScreenNo����ʾ�����ţ��ò�����AddScreen_Dynamic�����е�nScreenNo������Ӧ��
nDYAreaID����̬�����ţ��ò�����AddScreenDynamicArea�����е�nDYAreaID������Ӧ
pFileName����ӵ���Ϣ�ļ����ƣ�Ŀǰֻ֧��txt(֧��ANSI��UTF - 8��Unicode�ȸ�ʽ����)��bmp���ļ���ʽ
nShowSingle��������Ϣ�Ƿ�����ʾ��0��������ʾ��1��������ʾ����ʾ�ò���ֻ��szFileNameΪtxt��ʽ�ĵ�ʱ����Ч��
pFontName��������Ϣ��ʾ���壻�ò���ֻ��szFileNameΪtxt��ʽ�ĵ�ʱ����Ч��
nFontSize��������Ϣ��ʾ������ֺţ��ò���ֻ��szFileNameΪtxt��ʽ�ĵ�ʱ����Ч��
nBold��������Ϣ�Ƿ������ʾ��0��������1��������ʾ���ò���ֻ��szFileNameΪtxt��ʽ�ĵ�ʱ����Ч��
nFontColor��������Ϣ��ʾ��ɫ���ò���ֻ��szFileNameΪtxt��ʽ�ĵ�ʱ����Ч��
nStunt����̬������Ϣ�����ؼ���
00�������ʾ
01����ֹ��ʾ
02�����ٴ��
03�������ƶ�
04����������
05�������ƶ�
06����������
07����˸
08��Ʈѩ
09��ð��
10���м��Ƴ�
11����������
12�����ҽ�������
13�����½�������
14������պ�
15�������
16����������
17����������
18����������
19����������
20����������
21����������
22����������
23����������
24�����ҽ�����Ļ
25�����½�����Ļ
26����ɢ����
27��ˮƽ��ҳ
28����ֱ��ҳ
29��������Ļ
30��������Ļ
31��������Ļ
32��������Ļ
33�����ұպ�
34�����ҶԿ�
35�����±պ�
36�����¶Կ�
37�������ƶ�
38����������
39�������ƶ�
40����������
nRunSpeed����̬������Ϣ�����ٶ�
nShowTime����̬������Ϣ��ʾʱ�䣻��λ��10ms
����ֵ : �������״̬���붨�塣
	------------------------------------------------------------------------------ - */

int __stdcall AddScreenDynamicAreaFile(int nScreenNo, int nDYAreaID,
	const char *pFileName, int nShowSingle, const char *pFontName, int nFontSize, int nBold, int nFontColor,
	int nStunt, int nRunSpeed, int nShowTime)
{
	int nScreenOrd, nDYAreaOrd;
	PtagSendThread ptmptagSendThread;
	string szFileName;
	string szFontName;
	int v6;
	UINT ntmpFileStyle;
	string Ext;
	Json::Value newAreaFile;

	nScreenOrd = GetSelScreenArrayOrd(nScreenNo, devicelist_ja);
	if (nScreenOrd == -1)
	{
		return RETURN_ERROR_NOFIND_SCREENNO;
	}

	if ((g_lstSendThread.size() > (size_t)nScreenOrd) && (nScreenOrd >= 0))
	{
		ptmptagSendThread = g_lstSendThread[nScreenOrd];
		if (ptmptagSendThread->bSending)
		{
			return RETURN_ERROR_NOW_SENDING;
		}
	}

	nDYAreaOrd = GetSelScreenDYAreaOrd(nDYAreaID, devicelist_ja[nScreenOrd]["Screen_lstDYArea"]);
	if (nDYAreaOrd == -1)
	{
		return RETURN_ERROR_NOFIND_DYNAMIC_AREA;
	}
	szFileName = pFileName;
	szFontName = pFontName;

	Ext = szFileName.substr(szFileName.find_last_of('.'));
	transform(Ext.begin(), Ext.end(), Ext.begin(), ::toupper);
	if (Ext == ".BMP") //BMP�ļ�
	{
		v6 = FILE_TYPE_BMP;
		ntmpFileStyle = FILE_SHOWSTYLE_NORMAL;
	}
	else if (Ext == ".TXT") //TXT�ļ�
	{
		v6 = FILE_TYPE_TXT;
		if (nShowSingle == 1)
			ntmpFileStyle = FILE_SHOWSTYLE_SINGLE;
		else
			ntmpFileStyle = FILE_SHOWSTYLE_NORMAL;
	}
	else if (Ext == ".RTF") //RTF�ļ�
	{
		v6 = FILE_TYPE_RTF;
		ntmpFileStyle = FILE_SHOWSTYLE_NORMAL;
	}
	else
	{
		return RETURN_ERROR_NOSUPPORT_FILETYPE;
	}

	newAreaFile["File_Name"] = szFileName; //�ļ�����
	newAreaFile["File_Style"] = v6; //�ļ�����  //�ⲿͼƬ���ı�����񣬶��� 0��ͼƬ�ı���1��ʱ���ࣻ
	newAreaFile["File_ShowStyle"] = ntmpFileStyle; //�ı���ʾ��ʽ
	newAreaFile["File_FontName"] = szFontName; //��������
	newAreaFile["File_Bold"] = nBold; //�����Ƿ����
	newAreaFile["File_FontSize"] = nFontSize; //�����ֺ�
	newAreaFile["File_FontColor"] = nFontColor; //������ɫ
	newAreaFile["File_PageCount"] = 0; //ת���ɵ�����ҳ
	newAreaFile["File_Speed"] = nRunSpeed; //�ļ��ٶ�
	newAreaFile["File_Stunt"] = nStunt; //�ļ��ؼ���ʽ
	newAreaFile["File_OutsStunt"] = 0; //�˳���ʽ
	newAreaFile["File_Showtime"] = nShowTime; //�ļ�ͣ��ʱ��
	newAreaFile["File_ShowCount"] = 1; //�ظ����Ŵ���
	newAreaFile["File_Reserved1"] = 0; //��������
	newAreaFile["File_Reserved2"] = 0; //��������
	newAreaFile["File_Reserved3"] = 0; //��������
	newAreaFile["File_Reserved4"] = 0; //��������
	newAreaFile["File_Reserved5"] = 0; //��������
	newAreaFile["File_Reserved6"] = 0; //��������
	newAreaFile["File_Reserved7"] = 0; //��������
	devicelist_ja[nScreenOrd]["Screen_lstDYArea"][nDYAreaOrd]["Area_lstfile"].append(newAreaFile);

#ifdef _DEBUG
	SaveScreenInfoToFile();
#endif

	return RETURN_NOERROR;
}

/*------------------------------------------------------------------------------ -
������:    DeleteScreen_Dynamic
	ɾ����̬����ָ����ʾ����������Ϣ���ú���������ʾ��ͨѶ��
	���� :
nScreenNo����ʾ�����ţ��ò�����AddScreen_Dynamic�����е�nScreenNo������Ӧ��
����ֵ : �������״̬���붨��
	------------------------------------------------------------------------------ - */

int __stdcall DeleteScreen_Dynamic(int nScreenNo)
{
	int nScreenOrd;
	PtagSendThread ptmptagSendThread;
	string v;
	char screenOrdText[8];

	nScreenOrd = GetSelScreenArrayOrd(nScreenNo, devicelist_ja);
	v = _itoa_s(nScreenOrd, screenOrdText, 8, 10);
	v += "-";
	if (nScreenOrd == -1)
	{
		return RETURN_ERROR_NOFIND_SCREENNO;
	}

	if ((g_lstSendThread.size() > (size_t)nScreenOrd) && (nScreenOrd >= 0))
	{
		ptmptagSendThread = g_lstSendThread[nScreenOrd];
		if (ptmptagSendThread->bSending)
		{
			return RETURN_ERROR_NOW_SENDING;
		}
	}

	devicelist_ja.removeIndex(nScreenOrd);
	return RETURN_NOERROR;
}

/*------------------------------------------------------------------------------ -
������:    DeleteScreenDynamicArea
	ɾ����̬����ָ����ʾ��ָ���Ķ�̬������Ϣ���ú���������ʾ��ͨѶ
	���� :
nScreenNo����ʾ�����ţ��ò�����AddScreen_Dynamic�����е�nScreenNo������Ӧ��
nDYAreaID����̬�����ţ��ò�����AddScreenDynamicArea�����е�nDYAreaID������Ӧ
����ֵ : �������״̬���붨��
	------------------------------------------------------------------------------ - */

int __stdcall DeleteScreenDynamicArea(int nScreenNo, int nDYAreaID)
{
	int nScreenOrd, nDYAreaOrd;
	PtagSendThread ptmptagSendThread;

	nScreenOrd = GetSelScreenArrayOrd(nScreenNo, devicelist_ja);
	if (nScreenOrd == -1)
	{
		return RETURN_ERROR_NOFIND_SCREENNO;
	}

	if ((g_lstSendThread.size() > (size_t)nScreenOrd) && (nScreenOrd >= 0))
	{
		ptmptagSendThread = g_lstSendThread[nScreenOrd];
		if (ptmptagSendThread->bSending)
		{
			return RETURN_ERROR_NOW_SENDING;
		}
	}

	nDYAreaOrd = GetSelScreenDYAreaOrd(nDYAreaID, devicelist_ja[nScreenOrd]["Screen_lstDYArea"]);
	if (nDYAreaOrd == -1)
	{
		return RETURN_ERROR_NOFIND_DYNAMIC_AREA;
	}

	devicelist_ja[nScreenOrd]["Screen_lstDYArea"].removeIndex(nDYAreaOrd);
	return RETURN_NOERROR;
}

/*------------------------------------------------------------------------------ -
������:    DeleteScreenDynamicAreaFile
	ɾ����̬����ָ����ʾ��ָ���Ķ�̬����ָ���ļ���Ϣ���ú���������ʾ��ͨѶ��
	���� :
nScreenNo����ʾ�����ţ��ò�����AddScreen_Dynamic�����е�nScreenNo������Ӧ��
nDYAreaID����̬�����ţ��ò�����AddScreenDynamicArea�����е�nDYAreaID������Ӧ
nFileOrd����̬�����ָ���ļ����ļ���ţ�����Ű����ļ����˳�򣬴�0˳���������ɾ���м���ļ���������ļ�����Զ���䡣
����ֵ : �������״̬���붨��
	------------------------------------------------------------------------------ - */

int __stdcall DeleteScreenDynamicAreaFile(int nScreenNo, int nDYAreaID, int nFileOrd)
{
	int nScreenOrd, nDYAreaOrd;
	PtagSendThread ptmptagSendThread;

	nScreenOrd = GetSelScreenArrayOrd(nScreenNo, devicelist_ja);
	if (nScreenOrd == -1)
	{
		return RETURN_ERROR_NOFIND_SCREENNO;
	}

	if ((g_lstSendThread.size() > (size_t)nScreenOrd) && (nScreenOrd >= 0))
	{
		ptmptagSendThread = g_lstSendThread[nScreenOrd];
		if (ptmptagSendThread->bSending)
		{
			return RETURN_ERROR_NOW_SENDING;
		}
	}

	nDYAreaOrd = GetSelScreenDYAreaOrd(nDYAreaID, devicelist_ja[nScreenOrd]["Screen_lstDYArea"]);
	if (nDYAreaOrd == -1)
	{
		return RETURN_ERROR_NOFIND_DYNAMIC_AREA;
	}
	if ((size_t)nFileOrd >= devicelist_ja[nScreenOrd]["Screen_lstDYArea"][nDYAreaOrd]["Area_lstfile"].size())
	{
		return RETURN_ERROR_NOFIND_AREA;
	}
	devicelist_ja[nScreenOrd]["Screen_lstDYArea"][nDYAreaOrd]["Area_lstfile"].removeIndex(nFileOrd);
	return RETURN_NOERROR;
}

/*------------------------------------------------------------------------------ -
������:    SendDynamicAreaInfoCommand
	���Ͷ�̬����ָ����ʾ��ָ���Ķ�̬������Ϣ����ʾ�����ú�������ʾ��ͨѶ��
	���� :
nScreenNo����ʾ�����ţ��ò�����AddScreen_Dynamic�����е�nScreenNo������Ӧ��
nDYAreaID����̬�����ţ��ò�����AddScreenDynamicArea�����е�nDYAreaID������Ӧ
����ֵ : �������״̬���붨��
	------------------------------------------------------------------------------ - */

int __stdcall SendDynamicAreaInfoCommand(int nScreenNo, int nDYAreaID)
{
	int nScreenOrd, nDYAreaOrd;
	PtagSendThread ptmptagSendThread;
	string szSendBuf;
	DWORD nSendLength, ntmpSendCmd, ntmpSendFileType;
	tagstruct_PHY1Header srt_PHY1Header;
	list<DWORD> lstSendPrograms;
	ofstream fp;
	int Result;
	
	//__try
	//{
	Result = RETURN_ERROR_OTHER; //��������
	EnterCriticalSection(&g_cs);
		//__try
		//{
	nScreenOrd = GetSelScreenArrayOrd(nScreenNo, devicelist_ja);
	if (nScreenOrd == -1)
	{
		return RETURN_ERROR_NOFIND_SCREENNO;
	}

	if (g_lstSendThread.size() <= (size_t)nScreenOrd)
	{
		return RETURN_ERROR_OTHER;
	}

	ptmptagSendThread = g_lstSendThread[nScreenOrd];
	if (ptmptagSendThread->bSending)
	{
		return RETURN_ERROR_NOW_SENDING;
	}

	nDYAreaOrd = GetSelScreenDYAreaOrd(nDYAreaID, devicelist_ja[nScreenOrd]["Screen_lstDYArea"]);
	if (nDYAreaOrd == -1)
	{
		return RETURN_ERROR_NOFIND_DYNAMIC_AREA;
	}

	// TODO: Uncomment following code
	szSendBuf = MakeDynamicAreaInfo(nScreenOrd, nDYAreaOrd, devicelist_ja, nSendLength);

	ntmpSendCmd = SEND_DYNAMIC_AREA_INFO;
	ntmpSendFileType = 0xFF;

	memset(&srt_PHY1Header, 0, sizeof(srt_PHY1Header));
	srt_PHY1Header.DstAddr = 1;
	srt_PHY1Header.SrcAddr = 32768;
	srt_PHY1Header.ProtocolVer = PROTOCOLVER_FIFTH_DYNAMIC;
	srt_PHY1Header.Datalen = 1024;

	switch (devicelist_ja[nScreenOrd]["Screen_SendMode"].asUInt())
	{
	case SEND_MODE_NETWORK:
	case SEND_MODE_Server_2G:
	case SEND_MODE_Server_3G:
		srt_PHY1Header.DstAddr = CONTROLLER_ADDRESS_WILDCARD;
		srt_PHY1Header.DeviceType = devicelist_ja[nScreenOrd]["Screen_control"].asUInt();
		break;
	case SEND_MODE_SAVEFILE:
	{
		const char *pFileName = devicelist_ja[nScreenOrd]["Screen_CommandDataFile"].asCString();
		WCHAR wszFileName[MAX_PATH];
		MultiByteToWideChar(CP_ACP, 0, pFileName, -1, wszFileName, MAX_PATH);
		HANDLE hFile = CreateFile(wszFileName, GENERIC_ALL,
			0, NULL, CREATE_ALWAYS, 0, NULL);
		DWORD writtenLength;
		WriteFile(hFile, szSendBuf.c_str(), szSendBuf.size(), &writtenLength, NULL);
		CloseHandle(hFile);

		Result = RETURN_NOERROR;
		return Result;
	}
	default:
		srt_PHY1Header.DstAddr = devicelist_ja[nScreenOrd]["Com_address"].asUInt();
		srt_PHY1Header.DeviceType = devicelist_ja[nScreenOrd]["Screen_control"].asUInt();
		break;
	}
		//finally
		//{
	LeaveCriticalSection(&g_cs);
		//}

	ptmptagSendThread->bSending = true;
		//try
			// TODO: Uncomment following code
			Result = CreateSendThreadList(SEND_SINGLE_COMMUNICATION, 0xFF, nScreenOrd, NULL
				, ptmptagSendThread, devicelist_ja, devicelist_ja[nScreenOrd]["Screen_SendMode"].asUInt(),
				srt_PHY1Header, ntmpSendCmd, (BYTE)ntmpSendFileType, "", szSendBuf, nSendLength, lstSendPrograms, NULL, false, "");
		//finally
	ptmptagSendThread->bSending = false;
		//end;
	/*except
	}*/

	return Result;
}

/*------------------------------------------------------------------------------ -
������:    SendDeleteDynamicAreasCommand
	ɾ����̬����ָ����ʾ��ָ���Ķ�̬������Ϣ��ͬʱ����ʾ��ͨѶɾ��ָ���Ķ�̬������Ϣ���ú�������ʾ��ͨѶ
	���� :
nScreenNo����ʾ�����ţ��ò�����AddScreen_Dynamic�����е�nScreenNo������Ӧ��
nDYAreaID����̬�����ţ��ò�����AddScreenDynamicArea�����е�nDYAreaID������Ӧ
pDYAreaIDList����̬�������б����ͬʱɾ�������̬���򣬶�̬�����ż���","��������"0,1"
����ֵ : �������״̬���붨��
	------------------------------------------------------------------------------ - */

int __stdcall SendDeleteDynamicAreasCommand(int nScreenNo, int nDelAllDYArea, char *pDYAreaIDList)
{
	int Result = RETURN_NOERROR;
	int nScreenOrd, nDYAreaOrd;
	PtagSendThread ptmptagSendThread;
	string szSendBuf;
	DWORD nSendLength, ntmpSendCmd, ntmpSendFileType;
	tagstruct_PHY1Header srt_PHY1Header;
	list<DWORD> lstSendPrograms;
	list<string> S;
	string szDYAreaIDList;
	DWORD nDelAreaCount;
	string szDelAreaInfo;
	DWORD nDYAreaID;
	fstream fp;

	EnterCriticalSection(&g_cs);
	nDelAreaCount = 0;
	szDelAreaInfo = "";
	nScreenOrd = GetSelScreenArrayOrd(nScreenNo, devicelist_ja);

	if (nScreenOrd == -1)
	{
		return RETURN_ERROR_NOFIND_SCREENNO;
	}

	if ((int)g_lstSendThread.size() <= nScreenOrd)
	{
		return RETURN_ERROR_OTHER;
	}

	ptmptagSendThread = g_lstSendThread[nScreenOrd];
	if (ptmptagSendThread->bSending)
	{
		return RETURN_ERROR_NOW_SENDING;
	}

	if (nDelAllDYArea == 1)
	{
		szDelAreaInfo += (char)0xFF;
		devicelist_ja[nScreenOrd]["Screen_lstDYArea"].clear();
	}
	else
	{
		szDYAreaIDList = pDYAreaIDList;
		S = SplitString(szDYAreaIDList, ",");
		for (list<string>::iterator iter = S.begin(); iter != S.end(); ++iter)
		{
			nDYAreaID = atoi(iter->c_str());
			nDYAreaOrd = GetSelScreenDYAreaOrd(nDYAreaID, devicelist_ja[nScreenOrd]["Screen_lstDYArea"]);
			if (nDYAreaOrd >= 0)
			{
				/*for (int i = 0; i < devicelist_ja[nScreenOrd]["Screen_lstDYArea"][nDYAreaOrd]["Area_lstfile"].size(); ++i)
				{
					DeleteScreenDynamicAreaFile(nScreenNo, nDYAreaID, 0);
				}*/
				devicelist_ja[nScreenOrd]["Screen_lstDYArea"].removeIndex(nDYAreaOrd);
			}
			++nDelAreaCount;
			szDelAreaInfo += (char)nDYAreaID;
		}
		szDelAreaInfo = (char)nDelAreaCount + szDelAreaInfo;
	}

	szSendBuf = MakeDeleteDynamicAreas(szDelAreaInfo, nSendLength);
	ntmpSendCmd = SEND_DELETE_DYNAMIC_AREA;
	ntmpSendFileType = 0xFF;

	srt_PHY1Header.DstAddr = 1;
	srt_PHY1Header.SrcAddr = 32768;
	srt_PHY1Header.ProtocolVer = PROTOCOLVER_FIFTH_DYNAMIC;
	srt_PHY1Header.DeviceType = 0;
	srt_PHY1Header.Datalen = 1024;
	srt_PHY1Header.Reserved1 = 0;
	srt_PHY1Header.Reserved2 = 0;

	switch (devicelist_ja[nScreenOrd]["Screen_SendMode"].asUInt())
	{
	case SEND_MODE_NETWORK: 
	case SEND_MODE_Server_2G:
	case SEND_MODE_Server_3G:
		srt_PHY1Header.DstAddr = CONTROLLER_ADDRESS_WILDCARD;
		srt_PHY1Header.DeviceType = devicelist_ja[nScreenOrd]["Screen_control"].asUInt();
		break;
	case SEND_MODE_SAVEFILE:
		{
			const char *pFileName = devicelist_ja[nScreenOrd]["Screen_CommandDataFile"].asCString();
			
			WCHAR wszFileName[MAX_PATH];
			MultiByteToWideChar(CP_ACP, 0, pFileName, -1, wszFileName, MAX_PATH);

			HANDLE hFile = CreateFile(wszFileName, GENERIC_ALL,
				0, NULL, CREATE_ALWAYS, 0, NULL);
			DWORD writtenLength;
			WriteFile(hFile, szSendBuf.c_str(), szSendBuf.size(), &writtenLength, NULL);
			CloseHandle(hFile);
		}
		return RETURN_NOERROR;
	default:
		srt_PHY1Header.DstAddr = devicelist_ja[nScreenOrd]["Com_address"].asUInt();
		srt_PHY1Header.DeviceType = devicelist_ja[nScreenOrd]["Screen_control"].asUInt();
		break;
	}

	LeaveCriticalSection(&g_cs);

	ptmptagSendThread->bSending = TRUE;
	Result = CreateSendThreadList(SEND_SINGLE_COMMUNICATION, 0xFF, nScreenOrd, NULL
		, ptmptagSendThread, devicelist_ja, devicelist_ja[nScreenOrd]["Screen_SendMode"].asUInt(),
		srt_PHY1Header, ntmpSendCmd, (BYTE)ntmpSendFileType, "", szSendBuf, nSendLength, lstSendPrograms, 
		NULL, FALSE, "");
	ptmptagSendThread->bSending = FALSE;

	return Result;
}

/*------------------------------------------------------------------------------ -
������:    SendUpdateDynamicAreaPageInfoCommand
	��̬����ָ����ʾ��ָ���Ķ�̬���򵥶�����ָ��������ҳ��Ϣ���ú�������ʾ��ͨѶ
	�ú���ʹ��ʱ����������ȷ�õ�ǰԤ������Ϣ����ʾ���е���ʾҳ�룬������ܸ��³���
	���� :
nScreenNo����ʾ�����ţ��ò�����AddScreen_Dynamic�����е�nScreenNo������Ӧ��
nDYAreaID����̬�����ţ��ò�����AddScreenDynamicArea�����е�nDYAreaID������Ӧ
nFileOrd����̬�����ָ���ļ����ļ���ţ�����Ű����ļ����˳�򣬴�0˳���������ɾ���м���ļ���������ļ�����Զ���䡣
nPageOrd��Ԥ��������ҳ��ҳ��š���0��ʼ˳�������
����ֵ : �������״̬���붨��
	------------------------------------------------------------------------------ - */
int __stdcall SendUpdateDynamicAreaPageInfoCommand(int nScreenNo, int nDYAreaID, int nFileOrd, int nPageOrd)
{
	return RETURN_NOERROR;
}

/*------------------------------------------------------------------------------ -
������:    SendDeleteDynamicAreaPageCommand
	ɾ����̬����ָ����ʾ����ָ����̬����ָ��������ҳ��Ϣ���ú�������ʾ��ͨѶ
	�ú���ʹ��ʱ����������ȷ�õ�ǰԤɾ������ҳ��Ϣ����ʾ���е���ʾҳ�룬�������ɾ������
	���� :
nScreenNo����ʾ�����ţ��ò�����AddScreen_Dynamic�����е�nScreenNo������Ӧ��
nDYAreaID����̬�����ţ��ò�����AddScreenDynamicArea�����е�nDYAreaID������Ӧ
pDYAreaPageOrdList��Ԥɾ����̬��������ҳ����б����ͬʱɾ���������ҳ��Ϣ������ҳ��ż���","��������"0,1"��
ɾ������ҳ��Ϣִ�гɹ��󣬺��������ҳ��Ϣ������ҳ����Զ���ǰ���롣
����ֵ : �������״̬���붨��
	------------------------------------------------------------------------------ - */

int __stdcall SendDeleteDynamicAreaPageCommand(int nScreenNo, int nDYAreaID, char *pDYAreaPageOrdList)
{
	return RETURN_NOERROR;
}

/*------------------------------------------------------------------------------ -
������:    StartServer
	����������, ��������ģʽ�µķ�����ģʽ��GPRSͨѶģʽ��
	���� :
nSendMode : ����ʾ����ͨѶģʽ��
	0 : ����ͨѶ��
	2������ͨѶ(ֻ֧�̶ֹ�IPģʽ)��
	5��ONBON������ - GPRS
	6��ONBON������ - 3G
	7�����浽�ļ�������ͨѶģʽ��
	pServerIP : ������IP��ַ
	nServerPort : ����������˿�
	����ֵ : �������״̬���붨�塣
	------------------------------------------------------------------------------ - */
int __stdcall StartServer(int nSendMode, char *pServerIP, int nServerPort)
{
	return RETURN_NOERROR;
}

/*------------------------------------------------------------------------------ -
������:    StopServer
	�رշ�����, ��������ģʽ�µķ�����ģʽ��GPRSͨѶģʽ��
	���� :
nSendMode : ����ʾ����ͨѶģʽ��
	0 : ����ͨѶ��
	2������ͨѶ(ֻ֧�̶ֹ�IPģʽ)��
	5��ONBON������ - GPRS
	6��ONBON������ - 3G
	7�����浽�ļ�������ͨѶģʽ��
	����ֵ : �������״̬���붨�塣
	------------------------------------------------------------------------------ - */
int __stdcall StopServer(int nSendMode)
{
	return RETURN_NOERROR;
}


static void SaveScreenInfoToFile()
{
	Json::FastWriter writer;
	string jsonFileContent = writer.write(devicelist_root);
	ofstream ofs;
	ofs.open("screenlist.json");
	ofs << jsonFileContent;
	ofs.close();
}