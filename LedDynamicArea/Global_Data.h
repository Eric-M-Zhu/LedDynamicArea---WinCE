#pragma once

//------------------------------------------------------------------------------
// �����Э��ջ�汾��
const BYTE ProtocolVer_Third = 0x00; //3�����ƿ���Э��汾��λ00��
const BYTE ProtocolVer_Fourth = 0x04; //4�����ƿ���Э��汾��λ04��
const BYTE ProtocolVer_Fifth = 0x05; //5�����ƿ���Э��汾��λ05��
const BYTE ProtocolVer_Sixth = 0x06;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// ����ת��ģʽ
const UINT Tran_Pixel_Mode0 = 0; //0��8bit��+8bit�̣�
const UINT Tran_Pixel_Mode1 = 1; //1���Ӹߵ���λ5bit��+6bit��+5bit����������BX-5Q+ϵ�У�BX-5QL����
const UINT Tran_Pixel_Mode2 = 2; //2���Ӹߵ���λ5bit��+5bit��+5bit����������BX-5QL
const UINT Tran_Pixel_Mode3 = 3; //3���Ӹߵ���λ5bit��+6bit��+5bit�죻������BX-5QSϵ��
const UINT Tran_Pixel_Mode4 = 4; //4���������ֱ������ֿ���������λΪ32bit���Ӹ�λ����λ31λ��Ӧ0,0�㡣�����ȵ��ֽں���ֽ�
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ��ת��������ض���
const BYTE Transit_Error_Other = 0xFF; //����ʧ��
const BYTE Transit_Success = 0x00; //�����ɹ�
const BYTE Transit_Error = 0x01; //	Э�����ʧ��
const BYTE Transit_User_Error = 0x02; //	�û��������
const BYTE Transit_User_NotExist = 0x03; //	�û�������
const BYTE Transit_User_Logged = 0x04; //	�û��Ѿ���¼
const BYTE Transit_User_Unavailable = 0x05; //	�û�������ʹ�ã���ʾ�Ѿ�����
const BYTE Transit_User_NotSend = 0x06; //	�û��������ͣ��û��������˳�״̬��
const BYTE Transit_User_Mismatching = 0x07; // ��½�û��͹����豸�û���ƥ��
const BYTE Transit_User_Deleted = 0x08; //�û��Ѿ�ɾ��

const BYTE Transit_Device_Unknown = 0x10; //	�豸δ֪
const BYTE Transit_Device_Online = 0x11; //	�豸����
const BYTE Transit_Device_Offline = 0x12; //	�豸������
const BYTE Transit_Device_Overdue = 0x13; //	�豸���ڣ�Ƿ��
const BYTE Transit_Device_Deleted = 0x14; //	�豸�Ѿ�ɾ��
const BYTE Transit_Device_NotExist = 0x15; //	�豸������
const BYTE Transit_Device_2G = 0x16; //	�豸Ϊ2G
const BYTE Transit_Device_3G = 0x17; //	�豸Ϊ3G
const BYTE Transit_Device_Sending = 0x18; //	�豸���ڷ�����
const BYTE Transit_Device_Idle = 0x19; //	�豸������

const BYTE Transit_Control_NotExist = 0x20; //	����������ID������
const BYTE Transit_Control_Offline = 0x21; //	������������
const BYTE Transit_Control_OutTime = 0x22; //	������ͨ�ų�ʱ
const BYTE Transit_Control_Online = 0x23; //	����������
const BYTE Transit_Device_Invalidation = 0x27; //	�豸ʧЧ
const BYTE Transit_Device_Type_Error = 0x28; //  �豸���ʹ���

const int NetID_Len = 12;
const int Transit_Def_TimeoutSec = 5; //��ת������ͨѶĬ����ʱ��

const int Logo_Width_Default = 64;
const int Logo_Height_Default = 64;

typedef enum
{
	TCP_StaticIPMode = 0,
	UDP_StaticIPMode = 1
} TNetwork_StaticIPMode;

typedef enum
{
	Manual_Adjust = 0,
	Timer_Adjust = 1,
	Auto_Adjust = 2
} TAdjustBright;

typedef enum
{
	LogoAlign_Center = 0,
	LogoAlign_TopRight = 1,
	LogoAlign_TopLeft = 2
} TLogoAlign;

typedef enum
{
	LogoMode_Pic = 0,
	LogoMode_Txt = 1
} TLogoMode;

typedef struct
{
	string Name; //�豸����
	string BarCode; //�豸������
	UINT Status; //�豸����״̬
	HANDLE Transit_Type; //�豸���ͣ�2G ? 3G
	bool Matched; // �豸�Ƿ��Ѿ�ƥ��
	int Matche_ScreenOrd; //�豸ƥ������������
	string NetworkID; //����ID,ֻ��3G����ʱ�����Բ���Ч
} tag_Transit, Ttag_Transit, *Ptag_Transit;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ȫ�ֱ�����
typedef void (__stdcall *TProcessMessageEvent)(string szMessagge, int nProcess);

string g_szDefFont;
//��ת��������ip��ַ�Ͷ˿ڣ���SysSetup.ini�ж�ȡ
string g_Transit_Server_IP;
int g_Transit_ServerCon_Port, g_Transit_ServerUser_Port;
string g_Transit_User;
string g_Transit_Pwd;
bool g_bTransit_Login, g_bHaveTransit;
HANDLE g_Transit_CheckThread;
TProcessMessageEvent g_OnProcessMessage;

//g_lstTransit: TList;