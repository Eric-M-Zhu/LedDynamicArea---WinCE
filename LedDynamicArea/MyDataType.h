#pragma once

const char NEW_CONTROL_DISTINGUISH[] = { 0x01, 0x02, (char)0xFE, (char)0xFF, 0x00 };
const char STATIC_ENCRYPTION_KEY[] = { 0x37, 0x45, 0x32, 0x68, (char)0x96, (char)0xAA, 0x00 };
const char CUR_COMPATIBLE_FIRMWARE_VERSION[] = { 10, 8, 10, 00 };
const char BX_4C_4E_SINGLECOLOR_FIRMWARE_VERSION[] = { 11, 5, 5, 00};
const char FIFTH_BREAKPOINT_FIRMWARE_VERSION[] = { 12, 4, 18, 00};
const char BE_5X_SINGLECOLOR_FIRMWARE_VERSION[] = { 12, 6, 29, 00 };

const int FIND_SERIAL_PING_WAITOUT = 500; //ping����Ĵ��ڵȴ�ʱ�䡣
const int FIND_NETWORK_PING_WAITOUT = 500; //ping��������ڵȴ�ʱ�䡣

//------------------------------------------------------------------------------
// �����Э��汾��
const BYTE PROTOCOLVER_THIRD_CONTROL = 0x00;
const BYTE PROTOCOLVER_FOURTH_CONTROL = 0x04;
const BYTE PROTOCOLVER_FIFTH_CONTROL = 0x05;
const BYTE PROTOCOLVER_FIFTH_DYNAMIC = 0xF0;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ͨѶ�Ƿ񷵻�״̬
const int COMMUNICATION_RtnReq = 1; //����״̬��
const int COMMUNICATION_NORtnReq = 1; //������״̬
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// �����㷨�����ȡֵ��Χ
const int RANDOM_FROM = 2;
const int RANDOM_TO = 255;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// �����������ֽ�
const int COM_FRAMELENMAX = 132; //����ģʽ������ֽڳ���16
const int NET_FRAMELENMAX = 132; //����ģʽ������ֽڳ���16
const int GPRS_FRAMELENMAX = 8; //GPRSģʽ������ֽڳ���16
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ���ܷ�ʽ
const BYTE ENCRYPTION_NONE = 0x96; //����ģʽ
const BYTE ENCRYPTION_STATIC = 1; //Ĭ���������ģʽ
const BYTE ENCRYPTION_USER = 2; //�û��������ģʽ
const int ENCRYPTION_LENGTH = 112; //��Կ���ܳ���
//------------------------------------------------------------------------------

const int USB_FIFTH_PARAMETERS_FILECOUNT = 11; //��ǰ5��USB���ƿ���11�������ļ�

//------------------------------------------------------------------------------
// ����������
const BYTE CONTROLLER_TYPE_FOURTH = 0x40; //�ж�3������4��������ʼֵ

const BYTE CONTROLLER_TYPE_4VERSION2 = 0xF0;
const BYTE CONTROLLER_TYPE_4VERSION3 = 0xEF;
const unsigned short CONTROLLER_TYPE_WILDCARD = 0xFFFE; //����������ͨ���
const unsigned short CONTROLLER_TYPE_3T = 0x10;
const unsigned short CONTROLLER_TYPE_3A = 0x20;
const unsigned short CONTROLLER_TYPE_3A1 = 0x21;
const unsigned short CONTROLLER_TYPE_3A2 = 0x22;
const unsigned short CONTROLLER_TYPE_3M = 0x30;
const unsigned short CONTROLLER_TYPE_4A = 0x0041;

const unsigned short CONTROLLER_TYPE_4C = 0x0043;
const unsigned short CONTROLLER_TYPE_4E1 = 0x0144;
const unsigned short CONTROLLER_TYPE_4E = 0x0044;
const unsigned short CONTROLLER_TYPE_4EL = 0x0844;

const unsigned short CONTROLLER_TYPE_4U0 = 0x0045;
const unsigned short CONTROLLER_TYPE_4U1 = 0x0145;
const unsigned short CONTROLLER_TYPE_4U2 = 0x0245;
const unsigned short CONTROLLER_TYPE_4U3 = 0x0345;
const unsigned short CONTROLLER_TYPE_4UT = 0x0445;
const unsigned short CONTROLLER_TYPE_4U2X = 0x0545;

const unsigned short CONTROLLER_TYPE_5E1 = 0x0154;
const unsigned short CONTROLLER_TYPE_5E2 = 0x0254;
const unsigned short CONTROLLER_TYPE_5E3 = 0x0354;
const unsigned short CONTROLLER_TYPE_5EC = 0x0454;
//------------------------------------------------------------------------------

const int BX5E_SERIAL_FIRWAREVERSION = 0; //BX-5E���ڰ汾
const int BX5E_NETWORK_FIRWAREVERSION = 1; //BX-5E���ڿڰ汾

const int CONTROLLER_TYPE_OEFRONT[3] = { 0, 2, 4 };

//------------------------------------------------------------------------------
// �ؼ��б�궨��
const int STUNT_RANDOM = 0; //�����ʾ
const int STUNT_STATIC = 1; //��̬
const int STUNT_DIRECT_SHOW = 2; //���ٴ��
const int STUNT_MOVE_LEFT = 3; //�����ƶ�
const int STUNT_CONTINUOUS_MOVE_LEFT = 4; //��������
const int STUNT_MOVE_UP = 5; //�����ƶ�
const int STUNT_CONTINUOUS_MOVE_UP = 6; //��������
const int STUNT_FLICKER = 7; //��˸
const int STUNT_SNOWING = 8; //Ʈѩ
const int STUNT_BUBBLING = 9; //ð��
const int STUNT_MIDDLE_OUT = 10; //�м��Ƴ�
const int STUNT_MOVED_AROUND = 11; //��������
const int STUNT_HORIZONTAL_CROSS_MOVE = 12; //���ҽ�������
const int STUNT_VERTICAL_CROSS_MOVE = 13; //���½�������
const int STUNT_SCROLL_CLOSED = 14; //����պ�
const int STUNT_SCROLL_OPENED = 15; //�����
const int STUNT_LEFT_STRETCH = 16; //��������
const int STUNT_RIGHT_STRETCH = 17; //��������
const int STUNT_UP_STRETCH = 18; //��������
const int STUNT_DOWN_STRETCH = 19; //��������
const int STUNT_LEFT_LASER = 20; //��������
const int STUNT_RIGHT_LASER = 21; //��������
const int STUNT_UP_LASER = 22; //��������
const int STUNT_DOWN_LASER = 23; //��������
const int STUNT_CROSS_CURTAIN_LEFT_AND_RIGHT = 24; //���ҽ�����Ļ
const int STUNT_CROSS_CURTAIN_UP_AND_DOWN = 25; //���½�����Ļ
const int STUNT_CURTAIN_SCATTERED_TO_THE_LEFT = 26; //��ɢ����
const int STUNT_HORIZONTAL_BLINDS = 27; //ˮƽ��ҳ
const int STUNT_VERTICAL_BLINDS = 28; //��ֱ��ҳ
const int STUNT_CURTAIN_LEFT = 29; //������Ļ
const int STUNT_CURTAIN_RIGHT = 30; //������Ļ
const int STUNT_CURTAIN_UP = 31; //������Ļ
const int STUNT_CURTAIN_DOWN = 32; //������Ļ
const int STUNT_MOVE_TO_CENTER_FROM_LEFT_AND_RIGHT = 33; //���ұպ�
const int STUNT_SPLIT_TO_LEFT_AND_RIGHT = 34; //���ҶԿ�
const int STUNT_MOVE_TO_CENTER_FROM_UP_AND_DOWN = 35; //���±պ�
const int STUNT_SPLIT_TO_UP_AND_DOWN = 36; //���¶Կ�
const int STUNT_MOVE_RIGHT = 37; //�����ƶ�
const int STUNT_CONTINUOUS_MOVE_RIGHT = 38; //��������
const int STUNT_MOVE_DOWN = 39; //�����ƶ�
const int STUNT_CONTINUOUS_MOVE_DOWN = 40; //��������
//------------------------------------------------------------------------------

const UINT AreaMovieRunSpeed[16] = { 30, 28, 26, 24, 22, 20, 18, 16, 14, 12, 10, 8, 6, 4, 2, 1 }; // ����ÿһ����������֡����

//------------------------------------------------���������е�combobox���в�������
const string COMBOBOX_TYPE_Pro_FrameStunt[7] = { "Flicker", "Clockwise rotation", "Counterclockwise rotation",
	"Flicker and clockwise rotation", "Flicker and counterclockwise rotation", "Colors alternating", "Static" }; //�߿�����з�ʽ
const string COMBOBOX_TYPE_Pro_FrameSpeed[16] = {
	"1(Fastest)", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16(Slowest)" }; // �߿�������ٶ�
const string COMBOBOX_TYPE_Device_SendMode[3] = { "Serial communication", "Network Communication", "GPRS Communication" }; //����ģʽ
const string COMBOBOX_TYPE_Device_Color[3] = { "Single color", "Two colors", "Three colors" }; //��ɫ
const string COMBOBOX_TYPE_Device_DA[2] = { "Negative", "Positive" }; //DA����
const string COMBOBOX_TYPE_Device_OE[2] = { "Low", "High" }; //OE����
const string COMBOBOX_TYPE_Device_RowOrder[3] = { "Normal", "+1", "-1" }; //��˳��
const string COMBOBOX_TYPE_Device_MirrorMode[2] = { "Normal", "Mirror" }; //��������

const UINT BaudRate[2] = { 9600, 57600 };
const int SCREEN_ADDRESS_LISTCOUNT = 5;
const int PRO_FRAME_LENGTH = 32; //��Ŀ��ˮ�߿�ͼ������Ϊ�Ķ���Ϊ32.
const int PRO_FRAME_MAX_HEIGHT = 8; //��Ŀ��ˮ�߿�ͼ�����߶�.
const string USER_PASSWORD_ADMIN = "888";
const string USER_PASSWORD_GUEST = "168";
const string USER_PASSWORD_SUPER = "onbonbx";
const int GROUP_MAX_LEVEL = 5; //�������󼶱�������0��ʼ��
const int AREA_SHOWTIME_BASIC = 50; //Ŀǰ��������ͣ��ʱ��Ϊ10���룻��ͼ�ġ���Ļ����Ļ�����λΪ0.5�룻��˴˴�Ϊ500/10=50��
const string SERIAL_PORT_NONE = "COM0"; //�޴��ڱ�־�����趨Ϊ�ô�������ʾ�û�ѡ�񴮿�
const int CONTROLLER_ADDRESS_WILDCARD = 0xFFFE; //��������ַͨ���
const string NET_UDP_BROADCAST = "255.255.255.255"; //���ڼ��������ֱ�������UDP��ֱ��IP��ַ��
const string NET_AUTO_MAC = "00-FF-FE"; //�Զ�����MAC��ַ��ǰ���Σ�
const int PROGRAM_FRAME_MAX_WIDTH = 8; //��ˮ�߿����ֵ
const int COMPORT_MAX_READ_LENGTH = 4096; //�Ӵ�������ȡһ�����ݳ��ȡ�
const int COMPORT_MAX_READ_SLEEP_UNIT = 5; //�Ӵ�������ȡһ�����ݳ��ȵȴ�ʱ�䵥λ�����롣
const int BXGPRS_MAX_READ_SLEEP_UNIT = 100; //��BXGPRS����ȡһ�����ݳ��ȵȴ�ʱ�䵥λ�����롣
const int DEFAULT_BX_GPRS_SERVER_PORT = 8000; //BX-GPRS�������Ķ˿�
const int BX_GPRS_ERROR_SLEEP = 2000; //GPRSģʽ�����ط�ǰ�ĵȴ�ʱ�䣻��λ������
const int MULTI_COMMUNICATION_COUNT = 20; //���ͨѶͬʱͨѶ��������
const int SEND_SINGLE_COMMUNICATION = 0; //����ͨѶģʽ
const int SEND_MULTI_COMMUNICATION = 1; //���ͨѶģʽ

//------------------------------------------------------------------------------
// ��������������ģʽ
const int NET_CONNECT_DIRECT = 0; //����ֱ��ģʽ��UDP
const int NET_CONNECT_DHCP = 1; // �Զ���ȡIP��DHCP����
const int NET_CONNECT_STATICIP = 2; //�ֶ�����IP��Static IP����
//------------------------------------------------------------------------------

const int AREA_MOVIE_FRAME_UNIT = 1000; //���������֡���ŵ�λΪ1�룻1000����
const int AREA_MOVIE_FRAME_STUNT = 0xFE; //��������Ĳ����ؼ�Ϊ1�����ٴ����
const int AREA_MOVIE_FRAME_OUTSTUNT = 1; //����������˳��ؼ�Ĭ��Ϊ��Ч��
const int AREA_SHOWTIME_UNIT = 10; //ͼ�������ͣ��ʱ��ʵ�ʵ�λΪ10����

//------------------------------------------------------------------------------
// ��ͬͨѶģʽ�µ�ͨѶ��ʱ����
const int WAIT_TIMEOUT_SERIALPORT = 15;
const int WAIT_TIMEOUT_NET = 6;
const int WAIT_TIMEOUT_GPRS = 40;
const int WAIT_TIMEOUT_PCVALUE = 1000; //������õ��ķ���ֵ�ĳ�ʱʱ������Ҫ�ȿ�������50%,���ҽ���ת��Ϊ����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ��ͬͨѶģʽ�µ�ͨѶ��ʱ���ã�ʵ�ʵȴ��Ĳ�������λΪ����
const int WAIT_TIMEOUT_REALITY_SERIALPORT = 2500;
const int WAIT_TIMEOUT_REALITY_NET = 15000;
const int WAIT_TIMEOUT_REALITY_GPRS = 40000;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ������Ϣ���
const int SEND_SENDING = 0; //:���ڷ����У���û����ɣ�
const int SEND_FAILED = 1; //��������ɣ���û�з��ͳɹ���
const int SEND_SUCESSED = 2; //����������ҳɹ��� ������ɺ�Ҫɾ���ýṹָ��ģ�
const int SEND_PARAMETER_DISACCORD = 3; //������ping����ط��ֲ�������Ӧ��
const int SEND_UNCOMPATIBLE = 4; //Firmware�汾�����ݣ�
const int SEND_NOSTART_SEND = 5; //��δ��ʼ����
const int SEND_FIRMWARE_FIRST_INCOMP = 6; //����ƿ��ĵ�һ�汾�����ݡ�
const int SEND_FIRMWARE_SECOND_INCOMP = 7; //����ƿ��ĵڶ��汾�����ݡ�
const int SEND_FIRMWARE_THIRD_INCOMP = 8; //����ƿ��ĵ����������ݡ�
const int SEND_BX_5E_FIRMWARE_INCOMP_0 = 9; //��BX-5E���ƿ����Ӱ汾������,������0���Ӱ汾��
const int SEND_BX_5E_FIRMWARE_INCOMP_1 = 10; //��BX-5E���ƿ����Ӱ汾������,������1���Ӱ汾��
const int SEND_BX_5E_FIRMWARE_INCOMP = 11; //��BX-5E���ƿ��İ汾�����ݣ���ʾ�û���������
//------------------------------------------------------------------------------

//==============================================================================
// �������ݵ��ļ�����    ��ֵҪ��Screen_Control����Ŷ�Ӧ��
const int SEND_FILE_P = 0x00; //��Ŀ�ļ�
const int SEND_FILE_C = 0x01; // ���������������ļ�
const int SEND_FILE_S = 0x02; // ɨ�������ļ�
const int SEND_FILE_L = 0x03; // �����б��ļ�
const int SEND_FILE_F = 0x04; // �������̼�
const int SEND_FILE_O = 0x05; //�ֿ��ļ�
//==============================================================================

//------------------------------------------------------------------------------
// Ĭ�ϱ߿����͡����
const int PROGRAM_FRAME_16_DEFAULT_LINE_SINGLE_COLOR = 0; //��ɫС�ڵ���16��ʱĬ�ϵı߿�����
const int PROGRAM_FRAME_16_DEFAULT_WIDTH_SINGLE_COLOR = 1; //��ɫС�ڵ���16��ʱĬ�ϵı߿���
const int PROGRAM_FRAME_32_DEFAULT_LINE_SINGLE_COLOR = 2; //��ɫ����16С�ڵ���32��ʱĬ�ϵı߿�����
const int PROGRAM_FRAME_32_DEFAULT_WIDTH_SINGLE_COLOR = 2; //��ɫ����16С�ڵ���32��ʱĬ�ϵı߿���
const int PROGRAM_FRAME_MORE_32_DEFAULT_LINE_SINGLE_COLOR = 11; //��ɫ����32��ʽĬ�ϵı߿�����;�޸��˱߿�ͼ�κ�ò���ֵ��Ҫ���¶��塣
const int PROGRAM_FRAME_MORE_32_DEFAULT_WIDTH_SINGLE_COLOR = 4; //��ɫ���ڵ���32��ʱĬ�ϵı߿���

const int PROGRAM_FRAME_16_DEFAULT_LINE_MULI_COLOR = 0; //˫��ɫС�ڵ���16��ʱĬ�ϵı߿�����
const int PROGRAM_FRAME_16_DEFAULT_WIDTH_MULI_COLOR = 1; //˫��ɫС�ڵ���16��ʱĬ�ϵı߿���
const int PROGRAM_FRAME_32_DEFAULT_LINE_MULI_COLOR = 2; //˫��ɫ����16С�ڵ���32��ʱĬ�ϵı߿�����
const int PROGRAM_FRAME_32_DEFAULT_WIDTH_MULI_COLOR = 2; //˫��ɫ����16С�ڵ���32��ʱĬ�ϵı߿���
const int PROGRAM_FRAME_MORE_32_DEFAULT_LINE_MULI_COLOR = 12; //˫��ɫ����32��ʽĬ�ϵı߿�����;�޸��˱߿�ͼ�κ�ò���ֵ��Ҫ���¶��塣
const int PROGRAM_FRAME_MORE_32_DEFAULT_WIDTH_MULI_COLOR = 4; //˫��ɫ���ڵ���32��ʱĬ�ϵı߿���
const int PROGRAM_FRAME_SINGLE_COLOR_COUNT = 23; //��ɫ�߿�ͼƬ����
const int PROGRAM_FRAME_MULI_COLOR_COUNT = 47; //��ɫ�߿�ͼƬ����
const int SCREEN_MESSAGE_BMP_MAXWIDTH = 128;
const int SCREEN_MESSAGE_BMP_MAXHEIGHT = 16;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// �������洢�ռ�  ��λ:Kbytes
const int MEMORY_BX_3T = 1024;
const int MEMORY_BX_3A1 = 1024;
const int MEMORY_BX_3A2 = 1024;
const int MEMORY_BX_3A = 2048;
const int MEMORY_BX_3M = 2048;
const int MEMORY_BX_4A1 = 1024;
const int MEMORY_BX_4A2 = 1024;
const int MEMORY_BX_4A3 = 1024;
const int MEMORY_BX_4AQ = 1024;
const int MEMORY_BX_4A = 2048;

const int MEMORY_BX_4M1 = 2048;
const int MEMORY_BX_4M = 2048;
const int MEMORY_BX_4MC = 2048;
const int MEMORY_BX_4E = 2048;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ������ʵ����Ч�洢�ռ�  ��λ:Kbytes
const int MEMORY_REALITY_BX_3T = 756;
const int MEMORY_REALITY_BX_3A1 = 756;
const int MEMORY_REALITY_BX_3A2 = 756;
const int MEMORY_REALITY_BX_3A = 1500;
const int MEMORY_REALITY_BX_3M = 1552;
const int MEMORY_REALITY_BX_4A1 = 716;
const int MEMORY_REALITY_BX_4A2 = 716;
const int MEMORY_REALITY_BX_4A3 = 716;
const int MEMORY_REALITY_BX_4AQ = 716;
const int MEMORY_REALITY_BX_4A = 1484;
const int MEMORY_REALITY_BX_4M1 = 1496;
const int MEMORY_REALITY_BX_4M = 1496;
const int MEMORY_REALITY_BX_4MC = 1496;
const int MEMORY_REALITY_BX_4E = 1496;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// �����¹̼�����Ҫ���¼�����λ����
const int FIRMWARE_UPDATE_3A = 10000;
const int FIRMWARE_UPDATE_4A = 20000;
const int FIRMWARE_UPDATE_3M = 30000;
const int FIRMWARE_UPDATE_4M = 50000;
const int FIRMWARE_UPDATE_OTHER = 50000;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// USB��Դ���Ŀ¼
const string USB_DISK_DIRCECTORY = "onbonbx";
const string USB_DISK_OPTION_FILE = "bxconfig.bin";
const string USB_DISK_PROGRAM_FILE = "bxdata.dat";
const string USB_DISK_BXSET_FILE = "bxset.bin";
const string USB_DISK_SET0_FILE = "SET0";
//------------------------------------------------------------------------------

const int MOVIE_AREA_SINGLE_FILE_MAX_LENGTH = 150 * 1024; //���������ļ������������Ϊ150Kbytes
const int MOVIE_AREA_WIDTH = 768; //�����������Ϊ768�㡣
const int MOVIE_AREA_HEIGHT = 256; //�����������Ϊ256�㡣
const int MOVIE_AREA_AREA = 768 * 64; //�����ļ����������Ϊ��ɫ768*64��˫ɫΪ768*64/2;

//------------------------------------------------------------------------------
// �����ƽ�Ŀ����
const int PROGRAM_MAX_3T = 8;
const int PROGRAM_MAX_3A = 16;
const int PROGRAM_MAX_3M = 192;
const int PROGRAM_MAX_4A1 = 16;
const int PROGRAM_MAX_4A2 = 16;
const int PROGRAM_MAX_4A3 = 16;
const int PROGRAM_MAX_4AQ = 128;
const int PROGRAM_MAX_4A = 16;
const int PROGRAM_MAX_4M1 = 192;
const int PROGRAM_MAX_4M = 192;
const int PROGRAM_MAX_4MC = 192;
const int PROGRAM_MAX_4E = 192;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ����Ŀ������������
const int AREA_MAX_3T = 4;
const int AREA_MAX_3A = 8;
const int AREA_MAX_3M = 32;
const int AREA_MAX_4A1 = 8;
const int AREA_MAX_4A2 = 8;
const int AREA_MAX_4A3 = 8;
const int AREA_MAX_4AQ = 8;
const int AREA_MAX_4A = 8;

const int AREA_MAX_4M1 = 32;
const int AREA_MAX_4M = 32;
const int AREA_MAX_4MC = 32;
const int AREA_MAX_4E = 32;
const int TIMER_AREA_MAX_SINGLE = 1; //��CPU����ƿ�����ʱ�������������
const int TIMER_AREA_MAX_BX_4M = 2;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ϵͳ���֧�ֵ���ʾ������
const int SYSTEM_MAXSCREEN_COUNT = 255;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ��ʾ������
const int SCREEN_COLOR_SINGLE = 1; //����ɫ
const int SCREEN_COLOR_DOUBLE = 2; //˫��ɫ
const int SCREEN_COLOR_THREE = 3; //˫��ɫ
const int SCREEN_COLOR_FULLCOLOR = 4; //ȫ��ɫ
const int SCREEN_COLOR_TWO_COLOR_GRAY = 5; //˫��ɫ�Ҷ�

const int DOUBLE_COLOR_PIXTYPE_1 = 1; //˫��ɫ1��R+G
const int DOUBLE_COLOR_PIXTYPE_2 = 2; //˫��ɫ2��G+R

const int FULL_COLOR_NOGRAY = 0; //ȫ���޻Ҷȣ�
const int FULL_COLOR_GRAY = 1; //ȫ���лҶ�
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// �ı��ļ������ʾ��ʽ
//------------------------------------------------------------------------------
const int FILE_SHOWSTYLE_NORMAL = 0; //������ʾ��ʽ
const int FILE_SHOWSTYLE_SINGLE = 1; //������ʾ��ʽ
const int FILE_SHOWSTYLE_AUTO = 2; //����Ӧ��ʾ��ʽ

//------------------------------------------------------------------------------
// Ĭ����ʾ�������ꡢ��С
//------------------------------------------------------------------------------
const int DEFAULT_AREA_TW_WIDTH = 64;
const int DEFAULT_AREA_TW_HEIGHT = 64;
const int DEFAULT_AREA_ZM_WIDTH = 64;
const int DEFAULT_AREA_ZM_HEIGHT = 16;
const int DEFAULT_AREA_MOV_WIDTH = 64;
const int DEFAULT_AREA_MOV_HEIGHT = 64;
const int DEFAULT_AREA_TMDEFAULT_WIDTH = 64;
const int DEFAULT_AREA_TMDEFAULT_HEIGHT = 16;
const int DEFAULT_AREA_TM_WIDTH = 81;
const int DEFAULT_AREA_TM_HEIGHT = 13;
const int DEFAULT_AREA_CHONO_WIDTH = 41;
const int DEFAULT_AREA_CHONO_HEIGHT = 13;
const int DEFAULT_AREA_CLOCK_WIDTH = 48;
const int DEFAULT_AREA_CLOCK_HEIGHT = 48;
const int DEFAULT_AREA_LUNAR_WIDTH = 52;
const int DEFAULT_AREA_LUNAR_HEIGHT = 13;
const int DEFAULT_AREA_FONT_WIDTH = 64;
const int DEFAULT_AREA_FONT_HEIGHT = 32;
const int DEFAULT_AREA_TMP_WIDTH = 64;
const int DEFAULT_AREA_TMP_HEIGHT = 16;
const int DEFAULT_AREA_HUM_WIDTH = 64;
const int DEFAULT_AREA_HUM_HEIGHT = 16;
const int DEFAULT_AREA_NOS_WIDTH = 64;
const int DEFAULT_AREA_NOS_HEIGHT = 16;

//------------------------------------------------------------------------------
// ��������
const int AREA_TYPE_BMPTEXT = 0;
const int AREA_TYPE_FONT = 1;
const int AREA_TYPE_TIME = 2;
const int AREA_TYPE_TEMPERATURE = 3;
const int AREA_TYPE_HUMIDITY = 4;
const int AREA_TYPE_NOISE = 5;
const int AREA_TYPE_SINGLETEXT = 0x80;
const int AREA_TYPE_MOVIE = 6;
const int AREA_TYPE_TIMEDEFAULT = 7;
const int AREA_TYPE_CHRONOGRAPY = 8;
const int AREA_TYPE_TIMELUNAR = 9;
const int AREA_TYPE_TIMECLOCK = 10;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// �ؼ��б�
const BYTE AREA_STUNT_RANDOM = 0x00; //0x00 �C �����ʾ
const BYTE AREA_STUNT_STATIC = 0x01; //0x01 �C ��ֹ��ʾ
const BYTE AREA_STUNT_DIRECTSHOW = 0x02; //0x02 �C ���ٴ��
const BYTE AREA_STUNT_LMOVE = 0x03; //0x03 �C �����ƶ�
const BYTE AREA_STUNT_LCONTIMOVE = 0x04; //0x04 �C ��������
const BYTE AREA_STUNT_UMOVE = 0x05; //0x05 �C �����ƶ�
const BYTE AREA_STUNT_UCONTIMOVE = 0x06; //0x06 �C ��������
const BYTE AREA_STUNT_FICKER = 0x07; //0x07 �C ��˸
const BYTE AREA_STUNT_SNOWING = 0x08; //0x08 �C Ʈѩ
const BYTE AREA_STUNT_BUBBING = 0x09; //0x09 �C ð��
const BYTE AREA_STUNT_MIDMOVE = 0x0A; //0x0a �C �м��Ƴ�
const BYTE AREA_STUNT_LRMOVE = 0x0B; //0x0b �C ��������
const BYTE AREA_STUNT_LRCROSSMOVE = 0x0C; //0x0c �C ���ҽ�������
const BYTE AREA_STUNT_UDCROSSMOVE = 0x0D; //0x0d �C ���½�������
const BYTE AREA_STUNT_SCROLLCLOSE = 0x0E; //0x0e �C ����պ�
const BYTE AREA_STUNT_SCROLLOPEN = 0x0F; //0x0f �C �����
const BYTE AREA_STUNT_LSTRETCH = 0x10; //0x10 �C ��������
const BYTE AREA_STUNT_RSTRETCH = 0x11; //0x11 �C ��������
const BYTE AREA_STUNT_USTRETCH = 0x12; //0x12 �C ��������
const BYTE AREA_STUNT_DSTRETCH = 0x13; //0x13 �C ��������
const BYTE AREA_STUNT_LLASER = 0x14; //0x14 �C ��������
const BYTE AREA_STUNT_RLASER = 0x15; //0x15 �C ��������
const BYTE AREA_STUNT_ULASER = 0x16; //0x16 �C ��������
const BYTE AREA_STUNT_DLASER = 0x17; //0x17 �C ��������
const BYTE AREA_STUNT_LRCROSSCURTAIN = 0x18; //0x18 �C ���ҽ�����Ļ
const BYTE AREA_STUNT_UDCROSSCURTAIN = 0x19; //0x19 �C ���½�����Ļ
const BYTE AREA_STUNT_DISPERSELCURTAIN = 0x1A; //0x1a �C ��ɢ����
const BYTE AREA_STUNT_HORLAYER = 0x1B; //0x1b �C ˮƽ��ҳ
const BYTE AREA_STUNT_VERLAYER = 0x1C; //0x1c �C ��ֱ��ҳ
const BYTE AREA_STUNT_LCURTAIN = 0x1D; //0x1d �C ������Ļ
const BYTE AREA_STUNT_RCURTAIN = 0x1E; //0x1e �C ������Ļ
const BYTE AREA_STUNT_UCURTAIN = 0x1F; //0x1f �C ������Ļ
const BYTE AREA_STUNT_DCURTAIN = 0x20; //0x20 �C ������Ļ
const BYTE AREA_STUNT_LRCLOSE = 0x21; //0x21 �C ���ұպ�
const BYTE AREA_STUNT_LROPEN = 0x22; //0x22 �C ���ҶԿ�
const BYTE AREA_STUNT_UDCLOSE = 0x23; //0x23 �C ���±պ�
const BYTE AREA_STUNT_UPOPEN = 0x24; //0x24 �C ���¶Կ�
const BYTE AREA_STUNT_RMOVE = 0x25; //0x25 �C �����ƶ�
const BYTE AREA_STUNT_RCONTIMOVE = 0x26; //0x26 - ��������
const BYTE AREA_STUNT_DMOVE = 0x27; //0x27 �C �����ƶ�
const BYTE AREA_STUNT_DCONTIMOVE = 0x28; //0x28 - ��������
const BYTE AREA_STUNT_MOVIE = 0xFE; //����ģʽ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ���顢ѡ��״̬����ʾ������Ŀ�������ͼƬ����ֵ
const int IMAGEINDEX_GROUP = 0;
const int IMAGEINDEX_SUBGROUP = 1;
const int IMAGEINDEX_DELETE = 2;
const int IMAGEINDEX_SCREEN = 3;
const int IMAGEINDEX_UNCHECK = 4;
const int IMAGEINDEX_CHECK = 5;
const int IMAGEINDEX_PROGRAM_OVERALL = 6;
const int IMAGEINDEX_PROGRAM_NORMAL = 7;
const int IMAGEINDEX_PROGRAM_SHARE = 8;
const int IMAGEINDEX_PROGRAM_AUTO = 9;
const int IMAGEINDEX_AREA_BMPTEXT = 10;
const int IMAGEINDEX_AREA_TITLE = 11;
const int IMAGEINDEX_AREA_TIME = 12;
const int IMAGEINDEX_AREA_FONT = 13;
const int IMAGEINDEX_AREA_TEMPERATURE = 14;
const int IMAGEINDEX_AREA_HUMIDITY = 15;
const int IMAGEINDEX_AREA_NOISE = 16;
const int IMAGEINDEX_AREA_MOVIE = 18;
const int IMAGEINDEX_AREA_TIMEDEFAULT = 19; //�ϵ�ʱ������
const int IMAGEINDEX_AREA_CHRONOGRAPY = 20; //�ϵļ�ʱ����
const int IMAGEINDEX_AREA_TIMELUNAR = 21;
const int IMAGEINDEX_AREA_TIMECLOCK = 22;
const int IMAGEINDEX_GPRS_OUTLINE_SCREEN = 23; //�����ߵ�GPRS�նˡ�
//IMAGEINDEX_
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// �ļ�����
const int FILE_TYPE_TMF = 1; //ʱ���ļ�
const int FILE_TYPE_TXTF = 2; //TXTF�ļ�
const int FILE_TYPE_TXTS = 3; //TXTS�ļ�
const int FILE_TYPE_TBF = 4; //����ļ�
const int FILE_TYPE_TXT = 5; //TXT�ļ�
const int FILE_TYPE_RTF = 6; //RTF�ļ�
const int FILE_TYPE_BMP = 7; //BMP�ļ�
const int FILE_TYPE_JPG = 8; //JPG�ļ�
const int FILE_TYPE_GIF = 9; //GIF�ļ�
const int FILE_TYPE_JPEG = 10; //JPEG�ļ�
const int FILE_TYPE_AVI = 11; //AVI�ļ�
const int FILE_TYPE_SWF = 12; //SWF�ļ�
const int FILE_TYPE_TXTA = 13; //TXTA�ļ�,����Ӧ�ļ�
const int FILE_TYPE_TXTSWF = 14; //TXTA�ļ�,����Ӧ�ļ�
const int FILE_TYPE_TEXT = 15; //TEXT�ı�
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// �̶��ļ�����
const string SEND_FIXEDFILE_PARAMETER = "C000";
const string SEND_FIXEDFILE_SCREENSCAN = "S000";
const string SEND_FIXEDFILE_FIRMWARE = "F001";
const string SEND_FIXEDFILE_FIRMWARE2 = "F003";
const string SEND_FIXEDFILE_FACTORYFIRMWARE = "F000";
const string SEND_FIXEDFILE_FACTORYFIRMWARE2 = "F002";
const string SEND_FIXEDFILE_INFORMATION = "I000";
const string SEND_FIXEDFILE_LOGO = "A001"; //LOGO�ļ�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ������������

//OFSά��������
const unsigned short SEND_ACK = 0xA000; //Ack
const unsigned short SEND_NACK = 0xA001; //NAck
const unsigned short SEND_FORMAT = 0xA100; //��ʽ��
const unsigned short SEND_DELETE_FILE = 0xA101; //�ļ�ɾ��
const unsigned short SEND_ADD_FILE = 0xA102; //�ļ����
const unsigned short SEND_READ_FILE = 0xA104; //�ļ���ȡ
const unsigned short SEND_READ_DIR = 0xA106; //��ȡĿ¼
const unsigned short SEND_MULIADD_STARTFLAG = 0xA108; //���Ͷ��Ŀ��ʼ��־��
const unsigned short SEND_MULIADD_ENDFLAG = 0xA109; //���Ͷ��Ŀ������־��

const unsigned short SEND_MULIADD_FILE = 0xA110; //���ļ���ӣ����ڷ��Ͷ��Ŀʱ���з��ͽ�Ŀ֡ͷʱ�����ͽ�Ŀ��Ϣ�������֡�
const unsigned short SEND_ADDALL_FILE = 0xA1FF; //������н�Ŀ
//������ά��������
const unsigned short SEND_PING = 0xA200; //Ping����
const unsigned short SEND_SYSTEMRESET = 0xA201; //ϵͳ��λ
const unsigned short SEND_RESIVETIME = 0xA202; //У��ʱ��
//FIRMWARE�ļ�ά��
const unsigned short SEND_DELETE_FIXEDFILE = 0xA10A; //�̶��ļ�ɾ��
const unsigned short SEND_ADD_FIXEDFILE = 0xA10B; //�̶��ļ����
const unsigned short SEND_ADD_FACTORYFIRMWARE = 0xA1FB; //����ԭ���̼�����
const unsigned short SEND_READ_FIXEDFILE = 0xA10D; //�̶��ļ���ȡ

const unsigned short SEND_FIRMWARE_ACTIVATE = 0xA203; //firmware����
const unsigned short SEND_FIRMWARE_FACTORYRESET_ACTIVATE = 0xA2E3; //firmware�ָ����Ҷ���״̬

const unsigned short SEND_FIRMWARE_CURRENTSTATUE = 0xA204; //��ѯ��ǰfirmware״̬��
const unsigned short SEND_READ_CONTROLID = 0xA20A; //��ѯ���ƿ�ID��š�
const unsigned short SEND_READ_COPYRIGHT = 0xA20B; //��ѯ���ƿ���Ȩ��Ϣ��
const unsigned short SEND_POWERONOFF = 0xA205; //ǿ�ƿ��ػ�
const unsigned short SEND_TIMERPOWERONOFF = 0xA206; //��ʱ���ػ�
const unsigned short SEND_UNTIMERPOWERONOFF = 0xA208; //ȡ����ʱ���ػ�
const unsigned short SEND_ADJUST_LIGHT = 0xA207; //���ȵ���
const unsigned short SEND_QUERY_MEMORY = 0xA112; //��ѯ�洢�ռ�����
const unsigned short SEND_SCREEN_LOGO = 0xA1FE; //������ʾ��LOGO��Ϣ
const unsigned short SEND_SCREENSCAN_SWITCHMODE = 0xA2E4; //BX-3A�������л�����Firmwareģʽ��
const unsigned short SEND_ETHERNETSET_IP = 0xA401; //���ÿ��ƿ���IP��ַ��Ϣ��
const unsigned short SEND_READ_IPINFO = 0xA402; //��ȡ��ʾ����IP��Ϣ��
const unsigned short SEND_ETHERNETSET_MAC = 0xA400; //���ÿ��ƿ���mac��ַ��Ϣ��
const unsigned short SEND_ETHERNETSET_IP_EX = 0xA4FE; //���ÿ��ƿ���IP��ַ��Ϣ,��MAC��ַ���ˡ�
const unsigned short SEND_ETHERNETSET_IP_CASCADE = 0xA4FF; //���ü������ƿ���IP��ַ��Ϣ�������б���Ϣ��
const unsigned short SEND_FORMAT_EXTERNALFLASH = 0xA209; //����Ƭ��FLASH�ռ䡣
const unsigned short SEND_SCAN_TIME = 0xA20C; //�趨��ʾ�Ż���
const unsigned short SEND_LOCK_SCREEN = 0xA20D; //��Ļ����������
const unsigned short SEND_LOCK_PROGRAM = 0xA20E; //������Ŀ��������
const unsigned short SEND_MULI_TIMERPOWERON = 0xA2FE; //Ⱥ�鿪��
const unsigned short SEND_MULI_TIMERPOWEROFF = 0xA2FF; //Ⱥ��ػ�

const unsigned short SEND_SET_ENCRYPTION = 0xA210; //���ÿ�������������
const unsigned short SEND_ABOLISH_ENCRYPTION = 0xA211; //ȡ����������������
const unsigned short SEND_DELAY_START_SECOND = 0xA212; //���ÿ�����ʱ
const unsigned short SEND_BUTTON_MODE = 0xA213; //���ð�ť���ܡ�
const unsigned short SEND_DISPLAY_MODE = 0xA215; //���ÿ�������ʾģʽ

const unsigned short SEND_READ_SCREEN_STATUS = 0xA20F; //��ѯ������״̬��

const unsigned short SEND_DYNAMIC_AREA_INFO = 0xA700; //���¶�̬������Ϣ
const unsigned short SEND_DELETE_DYNAMIC_AREA = 0xA701; //ɾ����̬������Ϣ
const unsigned short SEND_DYNAMIC_AREA_PAGE = 0xA702; //���¶�̬����ҳ��Ϣ
const unsigned short SEND_DELETE_DYNAMIC_AREA_PAGE = 0xA703; //ɾ����̬����ҳ��Ϣ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// �����ļ�����
const int SEND_FILE_TYPE_PROGRAM = 0; //��Ŀ�ļ�����
const int SEND_FILE_TYPE_PARAMETER = 1; //�����ļ�����
const int SEND_FILE_TYPE_SCREENSCAN = 2; //ɨ���ļ�����
const int SEND_FILE_TYPE_PROGRAM_LIST = 3; //�����б��ļ�����
const int SEND_FILE_TYPE_FIRMWARE = 4; //Firmware�ļ�����
const int SEND_FILE_TYPE_FONT = 5; //�ֿ��ļ�����
const int SEND_FILE_TYPE_ALL = 0xFF; //δָ���ļ�����
const int SEND_FILE_TYPE_INFORMATION = 7; //��ʾ��Ϣ�ļ�����
const int SEND_FILE_TYPE_LOGO = 8; //��ʾ��LOGO�ļ�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ������ͨѶģʽ
//const int SEND_MODE_COMM = 0;
//const int SEND_MODE_GPRS = 1;
//const int SEND_MODE_NET = 2;
//const int SEND_MODE_USB = 3;
//const int SEND_MODE_WiFi = 4;
//const int SEND_MODE_Server_2G = 5;
//const int SEND_MODE_Server_3G = 6;
//const int SEND_MODE_SAVEFILE = 7; //���浽�ļ�ģʽ��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ���ͨѶ����״̬��־
const int SEND_STATUS_NONEED = 0xFF; //���跢��
const int SEND_STATUS_NOSTART = 0; //δ���͡�
const int SEND_STATUS_SENDING = 1; //���ڷ��͹����С�
const int SEND_STATUS_COMPLETE = 2; //������ɡ�
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// �ϵ�������д��־
const int TRANS_STATUS_READ = 0; //��ȡ����״̬
const int TRANS_STATUS_WRITE = 1; //д����״̬
const int TRANS_STATUS_NONE = 2; //�޶�д״̬
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// NOACK���ش������
const int ERR_NO = 0; //No error
const int ERR_OUTOFGROUP = 1; //Command Group Error
const int ERR_NOCMD = 2; //Command Not Found
const int ERR_BUSY = 3; //The Controller is busy now
const int ERR_MEMORYVOLUME = 4; // Out of the Memory Volume
const int ERR_CHECKSUM = 5; //CRC16 Checksum Error
const int ERR_FILENOTEXIST = 6; // File Not Exist
const int ERR_FLASH = 7; //Flash Access Error
const int ERR_FILE_DOWNLOAD = 8; // File Download Error
const int ERR_FILE_NAME = 9; //Filename Error
const int ERR_FILE_TYPE = 10; // File type Error
const int ERR_FILE_CRC16 = 11; //File CRC16 Error
const int ERR_FONT_NOT_EXIST = 12; // Font Library Not Exist
const int ERR_FIRMWARE_TYPE = 13; //Firmware Type Error (Check the controller type)
const int ERR_DATE_TIME_FORMAT = 14; // Date Time format error
const int ERR_FILE_EXIST = 15; //File Exist for File overwrite
const int ERR_FILE_BLOCK_NUM = 16; //File block number error
const int ERR_CONTROLLER_TYPE = 17; //Controller Type Error��
const int Err_SCREEN_PARA = 18; //����������Խ������
const int ERR_CONTROLLER_ID = 19; //��ȡ������ ID����
const int ERR_USER_SECRET = 20; //ͨѶʱ�û��������
const int ERR_OLD_SECRET = 21; //�޸�����ʱ��������������
const int ERR_PHY1_NO_SECRET = 22; //ͨѶʱ�Լ���2��ʽ������ʾ����� PHY1û���趨������
const int ERR_PHY1_USE_SECRET = 23; //ͨѶʱ�Թ̶�����1��ʽ������ʾ����� PHY1���趨������
const int ERR_OTHER = 0xFE; //Other Error;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ��ͬ���򡢲�ͬ���ƿ����ؼ��б�
const string SINGLE_TEXT_STUNT[1] = { "Continuous move left" };
const string BX3T_BMPTEXT_STUNT[] = { "Random" //�����ʾ
	, "Static" //��̬
	, "Direct show" //���ٴ��
	, "Move Left" //�����ƶ�
	, "Continuous move left" //��������
							 //    , "Move Up" //�����ƶ�
							 //    , "Continuous move up" //��������
							 //    , "Flicker" //��˸
	, "Snowing" //Ʈѩ
	, "Bubbling" //ð��
	, "Middle Out" //�м��Ƴ�
	, "Moved Around" //��������
	, "Horizontal cross move" //���ҽ�������
	, "Vertical cross move" //���½�������
	, "Scroll Closed" //����պ�
	, "Scroll Opened" //�����
	, "Left Stretch" //��������
	, "Right Stretch" //��������
	, "Up Stretch" //��������
				   //    , "Down Stretch" //��������
	, "Left Laser" //��������
	, "Right Laser" //��������
	, "Up Laser" //��������
	, "Down Laser" //��������
	, "Cross Curtain Left And Right" //���ҽ�����Ļ
	, "Cross Curtain Up And Down" //���½�����Ļ
	, "Curtain Scattered To The Left" //��ɢ����
									  //    , "Horizontal Blinds" //ˮƽ��ҳ
									  //    , "Vertical Blinds" //��ֱ��ҳ
									  //    , "Curtain Left" //������Ļ
									  //    , "Curtain Right" //������Ļ
									  //    , "Curtain Up" //������Ļ
									  //    , "Curtain Down" //������Ļ
									  //    , "Move To Center From Left And Right" //���ұպ�
									  //    , "Split To Left And Right" //���ҶԿ�
									  //    , "Move To Center From Up And Down" //���±պ�
									  //    , "Split To Up And Down" //���¶Կ�
	, "Move Right" //�����ƶ�
	, "Continuum Move Right" //��������
//    , "Move Down" //�����ƶ�
//    , "Continuum Move Down" //��������
};

const string BX3A_BMPTEXT_STUNT[] = { "Random" //�����ʾ
	, "Static" //��̬
	, "Direct show" //���ٴ��
	, "Move Left" //�����ƶ�
	, "Continuous move left" //��������
	, "Move Up" //�����ƶ�
	, "Continuous move up" //��������
	, "Flicker" //��˸
	, "Snowing" //Ʈѩ
	, "Bubbling" //ð��
	, "Middle Out" //�м��Ƴ�
	, "Moved Around" //��������
	, "Horizontal cross move" //���ҽ�������
	, "Vertical cross move" //���½�������
	, "Scroll Closed" //����պ�
	, "Scroll Opened" //�����
	, "Left Stretch" //��������
	, "Right Stretch" //��������
	, "Up Stretch" //��������
	, "Down Stretch" //��������
	, "Left Laser" //��������
	, "Right Laser" //��������
	, "Up Laser" //��������
	, "Down Laser" //��������
	, "Cross Curtain Left And Right" //���ҽ�����Ļ
	, "Cross Curtain Up And Down" //���½�����Ļ
	, "Curtain Scattered To The Left" //��ɢ����
									  //    , "Horizontal Blinds" //ˮƽ��ҳ
									  //    , "Vertical Blinds" //��ֱ��ҳ
									  //    , "Curtain Left" //������Ļ
									  //    , "Curtain Right" //������Ļ
									  //    , "Curtain Up" //������Ļ
									  //    , "Curtain Down" //������Ļ
	, "Move To Center From Left And Right" //���ұպ�
	, "Split To Left And Right" //���ҶԿ�
	, "Move To Center From Up And Down" //���±պ�
	, "Split To Up And Down" //���¶Կ�
	, "Move Right" //��������
	, "Continuum Move Right" //��������
	, "Move Down" //�����ƶ�
	, "Continuum Move Down" }; //��������

const string BXOTHER_A_BMPTEXT_STUNT[] = { "Random" //�����ʾ
					, "Static" //��̬
					, "Direct show" //���ٴ��
					, "Move Left" //�����ƶ�
					, "Continuous move left" //��������
					, "Move Up" //�����ƶ�
					, "Continuous move up" //��������
					, "Flicker" //��˸
					, "Snowing" //Ʈѩ
					, "Bubbling" //ð��
					, "Middle Out" //�м��Ƴ�
					, "Moved Around" //��������
					, "Horizontal cross move" //���ҽ�������
					, "Vertical cross move" //���½�������
					, "Scroll Closed" //����պ�
					, "Scroll Opened" //�����
					, "Left Stretch" //��������
					, "Right Stretch" //��������
					, "Up Stretch" //��������
					, "Down Stretch" //��������
					, "Left Laser" //��������
					, "Right Laser" //��������
					, "Up Laser" //��������
					, "Down Laser" //��������
					, "Cross Curtain Left And Right" //���ҽ�����Ļ
					, "Cross Curtain Up And Down" //���½�����Ļ
					, "Curtain Scattered To The Left" //��ɢ����
													  //    , "Horizontal Blinds" //ˮƽ��ҳ
													  //    , "Vertical Blinds" //��ֱ��ҳ
					, "Curtain Left" //������Ļ
					, "Curtain Right" //������Ļ
					, "Curtain Up" //������Ļ
					, "Curtain Down" //������Ļ
					, "Move To Center From Left And Right" //���ұպ�
					, "Split To Left And Right" //���ҶԿ�
					, "Move To Center From Up And Down" //���±պ�
					, "Split To Up And Down" //���¶Կ�
					, "Move Right" //��������
					, "Continuum Move Right" //��������
					, "Move Down" //�����ƶ�
					, "Continuum Move Down" }; //��������

const string BXOTHER_BMPTEXT_STUNT[] = { "Random" //�����ʾ
										 , "Static" //��̬
										 , "Direct show" //���ٴ��
										 , "Move Left" //�����ƶ�
										 , "Continuous move left" //��������
										 , "Move Up" //�����ƶ�
										 , "Continuous move up" //��������
										 , "Flicker" //��˸
										 , "Snowing" //Ʈѩ
										 , "Bubbling" //ð��
										 , "Middle Out" //�м��Ƴ�
										 , "Moved Around" //��������
										 , "Horizontal cross move" //���ҽ�������
										 , "Vertical cross move" //���½�������
										 , "Scroll Closed" //����պ�
										 , "Scroll Opened" //�����
										 , "Left Stretch" //��������
										 , "Right Stretch" //��������
										 , "Up Stretch" //��������
										 , "Down Stretch" //��������
										 , "Left Laser" //��������
										 , "Right Laser" //��������
										 , "Up Laser" //��������
										 , "Down Laser" //��������
										 , "Cross Curtain Left And Right" //���ҽ�����Ļ
										 , "Cross Curtain Up And Down" //���½�����Ļ
										 , "Curtain Scattered To The Left" //��ɢ����
										 , "Horizontal Blinds" //ˮƽ��ҳ
															   //    , "Vertical Blinds" //��ֱ��ҳ
										 , "Curtain Left" //������Ļ
										 , "Curtain Right" //������Ļ
										 , "Curtain Up" //������Ļ
										 , "Curtain Down" //������Ļ
										 , "Move To Center From Left And Right" //���ұպ�
										 , "Split To Left And Right" //���ҶԿ�
										 , "Move To Center From Up And Down" //���±պ�
										 , "Split To Up And Down" //���¶Կ�
										 , "Move Right" //��������
										 , "Continuum Move Right" //��������
										 , "Move Down" //�����ƶ�
										 , "Continuum Move Down" }; //��������
//------------------------------------------------------------------------------

//==============================================================================
// �������ش���ֵ
//const int RETURN_ERROR_NOFIND_DYNAMIC_AREA = 0xE1; //û���ҵ���Ч�Ķ�̬����
//const int RETURN_ERROR_NOFIND_DYNAMIC_AREA_FILE_ORD = 0xE2; //��ָ���Ķ�̬����û���ҵ�ָ�����ļ���š�
//const int RETURN_ERROR_NOFIND_DYNAMIC_AREA_PAGE_ORD = 0xE3; //��ָ���Ķ�̬����û���ҵ�ָ����ҳ��š�
//const int RETURN_ERROR_NOSUPPORT_FILETYPE = 0xE4; //��֧�ָ��ļ����͡�
//const int RETURN_ERROR_RA_SCREENNO = 0xF8; //�Ѿ��и���ʾ����Ϣ����Ҫ�����趨����DeleteScreenɾ������ʾ������ӣ�
//const int RETURN_ERROR_NOFIND_AREA = 0xFA; //û���ҵ���Ч����ʾ���򣻿���ʹ��AddScreenProgramBmpTextArea���������Ϣ��
//const int RETURN_ERROR_NOFIND_SCREENNO = 0xFC; //ϵͳ��û�в��ҵ�����ʾ��������ʹ��AddScreen���������ʾ��
//const int RETURN_ERROR_NOW_SENDING = 0xFD; //ϵͳ�����������ʾ��ͨѶ�����Ժ���ͨѶ��
//const int RETURN_ERROR_OTHER = 0xFF; //��������
//const int RETURN_NOERROR = 0; //û�д���
//==============================================================================

//--------------------------------------------------
//����Ӧ�õ��ĳ���
const int clred = 0;
const int cllime = 1;
const int clYellow = 2;
const int Colors[3] = { clred, cllime, clYellow }; //
const string ymdlist[] = {
	"2003��12��30��", "00��12��30��", "12/30/2000", "2000/12/30", "00-12-30", "00.12.30",
	"12��30��", "12.30.2000", "2000-12-30", "30 12 2000", "30:12:2000", "30:00:00",
	"2000", "12", "30" };
const string ymdreallist[] = {
"[Y1]��[M1]��[D1]��", "[Y2]��[M1]��[D1]��", "[M1]/[D1]/[Y1]", "[Y1]/[M1]/[D1]",
"[Y2]-[M1]-[D1]", "[Y2].[M1].[D1]", "[M1]��[D1]��", "[M1].[D1].[Y1]",
"[Y1]-[M1]-[D1]", "[D1] [M1] [Y1]", "[D1]:[M1]:[Y1]", "[D1]:[M1]:[Y2]",
"[Y1]", "[M1]", "[D1]" };
const string weeklist[] = { "����һ", "Wednesday", "Tues" };
const string timelist[] = {
	"20ʱ59��59��", "20�r59��59��", "20:59:59", "20 59 59", "8 59 59", "20ʱ59��",
	"20�r59��", "20:59", "����", "AM", "20(ʱ)", "59(��)", "59(��)", "���� 8:59",
	"AM 8:59", "8:59 AM", "AM 8 59", "8 59 AM", "8:59 ����" };
const string timereallist[] = {
	"[H1]ʱ[N1]��[S1]��", "[H1]�r[N1]��[S1]��", "[H1]:[N1]:[S1]", "[H1] [N1] [S1]", "[H2] [N1] [S1]",
	"[H1]ʱ[N1]��", "[H1]�r[N1]��", "[H1]:[N1]", "[P1]", "[P2]", "[H1]", "[N1]", "[S1]", "[P1] [H2]:[N1]",
	"[P2] [H2]:[N1]", "[H2]:[N1] [P2]", "[P2] [H2] [N1]", "[H2] [N1] [P2]", "[H2]:[N1] [P1]" };
const string stylearr[] = {
"year_list", "month_list", "day_list", "hour_list", "minute_list", "second_list",
"ampm_list", "week_list", "bp_list", "js_list", "jr_list", "ymd_list", "hns_list" };
//-----------------------------------------------------------------------

//type
//
//TPoints = array of TPoint;
//PPoints = ^TPoints;
//

typedef enum
{
	seInteger,
	seString,
	seBoolean
} TDataType;

typedef enum
{
	cdttxtf = 0,
	cdttxts = 1,
	cdtgrid = 2,
	cdttime = 3,
	cdttimeclear = 4,
	cdttimesize = 5,
	cdttimeimage = 6, 
	cdtotherimage = 7, 
	cdtnormaltimedata = 8, 
	cdtchonodata = 9,
	cdtymdlist = 10, 
	cdtweeklist = 11, 
	cdthnslist = 12, 
	cdtnormaltimeimage = 13,
	cdtchonoimage = 14, 
	cdtgridimage = 15, 
	cdtlunardata = 16, 
	cdtlunarimage = 17,
	cdtclockdata = 18, 
	cdtclockimage = 19, 
	cdttxtfimage = 20, 
	cdttxtsimage = 21,
	cdttimeauto = 22, 
	cdtlunarauto = 23, 
	cdtchonoauto = 24
} TCopyDataType;

typedef struct
{
	string szCom;
	UINT nComBaud;
	UINT nComDataBits;
	UINT nComStopBits;
	UINT nComParity;
	UINT nSendUnit;
	UINT nUnitSleepValue;
	UINT nInputSize;
	UINT nOutputSize;
} tagCommRecord, *PtagCommRecord;

typedef struct
{
	char *xname;
	int xleft;
	int xtop;
	int xwidth;
	int xheight;
	char *xstyle;
} tagSampleRecord, *PtagSampleRecord;

typedef struct
{
	int nWidth;
	int nHeight;
} tagAreaSize;

typedef struct
{
	BYTE nScreen_Scan; //ɨ�跽ʽ;1/16:0x10;1/8:0x08;1/4:0x04;1/2:0x02;��̬:0x01
	UINT nData_FlowLength; //����������������
	string szData_Flow; //������������
	UINT nData_Flow_MemoLength; //��ע��Ϣ����
	string szData_Flow_Memo; //��ע��Ϣ
	BYTE nData_Row_Per_Data; //һ·���ݴ�����
	BYTE nData_Decoder_Uen; //138�����Ƿ�ʹ��
	BYTE nData_U_Mode; //U��ģʽ��Ĭ��Ϊ0:ֱ�У�1:U��ģʽ
	BYTE nData_Col_Flod_Mode; //����ģʽ��0:ֱ�У�1:2�����У�2��4�����У�3:8������
	BYTE nData_Wu; //��Сѭ����Ԫ��ȡ���λΪbyte
	BYTE nData_Hu; //��Сѭ����Ԫ�߶ȡ���λΪλ��
	BYTE nData_WtMax; //ת����ÿ����С��Ԫ�Ŀ�ȡ���λΪbyte
	BYTE nData_Con_Table_Length; //��ַת������
	char pData_Con_Table[256]; //��ַת����
	BYTE nReserved1; //������1
	BYTE nReserved2; //������2
	BYTE nReserved3; //������3
	BYTE nReserved4; //������4
	BYTE nReserved5; //������5
	BYTE nReserved6; //������6
	BYTE nReserved7; //������7
} tagScreenFlowItem, *ptagScreenFlowItem;

//����״̬��������ֵ��
typedef struct
{
	UINT nPercentValue; //���Ͱٷֱȡ�
	string szMessagestr; //����״̬��ʾ�ַ���
} tagSendStatus, *PtagSendStatus;

//�����߳̽ṹ��
typedef struct
{
	UINT nSingleOrMulti; //���������ͨѶģʽ  0��������1�����
	UINT nIndex; //����ʾ�б��е���š�        ֻ�е�nSingleOrMulti=0ʱ�ò�������Ч��
	UINT nScreenOrd; //��ʾ����ţ�
	HANDLE hdlResultForm; //���ش��ڵľ��
	string szScreenSrc; //��ʾ������
							 //    SendThread: TCommunicate; //�����߳�
	bool bSending; //True:���ڷ��͹����У�False:ĿǰΪ����״̬��
	UINT nSendCmd; //��������
	BYTE nFileType; //������͵����ļ�����ȡ�ļ��ļ����͡�
	string szReadBuf; //���ص�����
	UINT nReadLength; //�������ݳ��ȡ�
	bool bReadSaveAs; //���ص������Ƿ񱣴棻//False:�����棻True:����
	string szReadFile; //�������ݱ�����ļ���
	BYTE nSendedStatus; //������ɲ��ҳɹ���־ :0:���ڷ����У���û����ɣ�1��������ɣ���û�з��ͳɹ���2����������ҳɹ��� ������ɺ�Ҫɾ���ýṹָ��ģ�3������ping����ط��ֲ�������Ӧ��
	UINT nErrorNumber; //���ʹ��������룻���NOACK���ش������
} tagSendThread, *PtagSendThread;

typedef struct
{
	UINT nParentIndex; //���ڵ����
	string szScreenSrc; //��ʾ������
} tagScreenNodeData, *PtagScreenNodeData;

typedef struct
{
	string szSendbuf;
	UINT nSendLength;
	UINT nSendnSectors; //�������ǰ��Ŀ��ռ������
	string szSendFile; //���͵Ľ�Ŀ�ļ�����
	string szSendCRC; //���͵Ľ�Ŀ�ļ�CRC32У��ֵ��
	bool bNeedSend; //Ĭ����Ҫ���ͣ�True
	string szSendMessage;
} tagSendInfo, *PtagSendInfo;

typedef struct
{
	string szQueryFile; //���յ���Ŀ�ļ�����
	UINT nQueryFileLength; //���յ��Ľ�Ŀ�ļ�����
	string szQueryCRC; //���յĽ�Ŀ�ļ�CRC32У��ֵ��
	bool bNeedDelete; //Ĭ����Ҫɾ��True���������ļ�У��һ��ʱ����ɾ���ļ����������ļ�һ�¡�У�鲻һ�£��������ļ�PC��������ʱɾ���ļ���
} tagReadDir, *PtagReadDir;

//���ڽṹ
typedef struct
{
	HANDLE CommPort;
	string szCommName; //���ڵı��
	UINT nCommBaud; //���ڲ�����
	UINT nCommDataBits; //��������λ
	UINT nCommStopBits; //����ֹͣλ
	UINT nCommParity; //����У��λ
	UINT nPackageDataLength; //����ÿ�����ݴ�С����λ���ֽ�
	UINT nPackageSleep; //����ÿ�����ݳɹ����뷢����һ�����ݵĵȴ�ʱ�䣻��λ������
	UINT nSendUnit; //����һ�����ݵĵ�Ԫ����
	UINT nUnitSleepValue; //����һ�ε�Ԫ�������ݵ�ͣ��ʱ��,��λ����
	UINT nReadWaitTimeOut; //�������ݵ����ȴ�ʱ�䣻��λ����
	UINT nInputSize; //���ջ�������С
	UINT nOutputSize; //���ͻ�������С
	UINT nErrReSendTimes;
	UINT nFrameLenMax;
} tagSerialComm, *PtagSerialComm;

//����ṹ
typedef struct
{
	UINT Network_Mode; //0:����ֱ����1���̶�IPģʽ��2��������ģʽ��
	UINT nServerMode; //0:������ģʽδ������1��������ģʽ������
	string szServerMode_ID; //������ģʽʱ������ID��š�
	string Network_IP; //����IP��ַ
	UINT Network_Port; //����˿�
	SOCKET Network_Skt; //Socket�׽���
	UINT nPackageDataLength; //����ÿ�����ݴ�С����λ���ֽ�
	UINT nPackageSleep; //����ÿ�����ݳɹ����뷢����һ�����ݵĵȴ�ʱ�䣻��λ������
	UINT nSendUnit; //����һ�����ݵĵ�Ԫ����
	UINT nUnitSleepValue; //����һ�ε�Ԫ�������ݵ�ͣ��ʱ��,��λ����
	UINT nReadWaitTimeOut; //�������ݵ����ȴ�ʱ�䣻��λ����
	UINT nErrReSendTimes;
	UINT nFrameLenMax;

	//��ת������ʹ��
	UINT Network_HwdId; //��������Ψһֵ
	string Barcodeid; //��ά��
	string Usename; //�û���
	string Password; //����
	BYTE errorid; //������
	UINT GPRSMODE; //gprsģʽ 0��2g   1��3g
	bool start_send; //Ĭ��Ϊfalse
} tagNetwork, *PtagNetwork;

//GPRS�ṹ
typedef struct
{
	UINT GPRS_Mode; //0:BX-GPRSģʽ��
	string GPRS_ID; //GPRS�ն˱��
					 //    GPRS_UnitSize: Cardinal; //��λ�ķְ���С
					 //    Gprs_UnitTime: Cardinal; //��λ�ķְ����ͼ��
	UINT nPackageDataLength; //����ÿ�����ݴ�С����λ���ֽ�
	UINT nPackageSleep; //����ÿ�����ݳɹ����뷢����һ�����ݵĵȴ�ʱ�䣻��λ������
	UINT nSendUnit; //����һ�����ݵĵ�Ԫ����
	UINT nUnitSleepValue; //����һ�ε�Ԫ�������ݵ�ͣ��ʱ��,��λ����
	UINT nReadWaitTimeOut; //�������ݵ����ȴ�ʱ�䣻��λ����
	UINT nErrReSendTimes;
	UINT nFrameLenMax;
} tagGPRS, *PtagGPRS;

typedef struct
{
	BYTE nCommunicationType; //0:����ģʽ��1������ģʽ��2��GPRSͨѶģʽ
	tagSerialComm tag_SerialComm; //���ڽӿڡ�
	tagNetwork tag_Network; //����ӿ�
	tagGPRS tag_GPRS; //GPRS�ӿ�
} tagCommunication, *PtagCommunication;

//�����ṹ�����ڶ�̬�����
typedef struct
{
	UINT DstAddr; ///Ŀ���ַ
	UINT SrcAddr; ////Դ��ַ
	UINT ProtocolVer; ////Э��ջ�汾;ͨ�����ֽ����ж���3������4�����ƿ���3����Э��汾Ϊ$00��4������Э��汾Ϊ$04
	UINT Reserved1; //������1
	UINT DeviceType; ////�豸����   3����1���ֽڣ�4����2���ֽڡ�
	UINT Reserved2; //������2
	UINT Reserved3; //������2
	UINT Reserved4; //������2
	UINT Reserved5; //������2
	UINT Datalen; ////֡����
} tagstruct_PHY1Header, *Ptagstruct_PHY1Header;

//�����ṹ������һ���Э��
typedef struct
{
	UINT DstAddr; ///Ŀ���ַ
	UINT SrcAddr; ////Դ��ַ
	UINT ProtocolVer; ////Э��ջ�汾;ͨ�����ֽ����ж���3������4�����ƿ���3����Э��汾Ϊ$00��4������Э��汾Ϊ$04
	UINT ProtecolType; ////Э������
	UINT DeviceType; ////�豸����   3����1���ֽڣ�4����2���ֽڡ�
	UINT PHYType; ////����������
	UINT Reserved1; //������1
	UINT MsgSeq; ////֡ID��
	UINT Reserved2; //������2
	UINT FrameLenMax; ////֧��PHY1��ת������ݵ���󳤶� ��1byte
	UINT EncryptionType; ////���ݼ���ģʽ��$96������ģʽ�������ܣ�$01��Ĭ��ģʽ�����ù̶�����ģʽ���ܣ�$02���û��Զ���ģʽ���Զ�������6bytes
	UINT RandomNumber; //�����������1���ֽڣ����ֽ�ȡֵΪ0~200��ȡ��CRC16�������ʼλ��ȡ3�����6���ֽڡ�����������ַ���
	char Secret[6]; //PC��������ʱ�û������Զ����Ĭ�ϼ��ܺ���ֶ��������ܳף�������Ч�ֽڣ�PC��������ʱ�������������λ��Чֵ(���ƿ����跢�ͼ����ܳ׸�PC)��
	UINT Datalen; ////֡����
	UINT DataChecksum; ////֡������CRC16
	UINT HeaderChecksum; /////֡ͷУ�飬������
} tagstruct_PHY1Header_5th, *Ptagstruct_PHY1Header_5th;

//������ͨѶͨѶ�б�
typedef struct
{
	UINT nScreenOrd; //��devicelist_ja�豸�б��е���š�
	string szScreen_src; //��ʾ����š���Ӧdevicelist_ja�е�Screen_src�ֶΡ�
	UINT nSendCmd; //��Ⱥ���������֣�
	UINT nSended; //��Ⱥ������ɱ�־��$FF�����跢�ͣ�1���Ѿ�������ɣ�0��δ������ɣ�2�����ڷ��͹����С�
	UINT nSendMode; //��Ļ��ͨѶ���ͣ�Ĭ��Ϊ����ͨ��
	BYTE nCom_port; //������ģʽΪ����ģʽʱ���ÿ��ƿ��Ĵ��ںš�
} tagMultiSendRecord, *PtagMultiSendRecord;

//������ģʽ��ACK��LookUp�ṹ��
typedef struct
{
	string szServerAccessPassword;
	string szIPAddress;
	string szSubnetMask;
	string szGateway;
	UINT nPort;
	string szMac;
	string szNetwork_ID;
} tagServerModeLookUpRecord, *PtagServerModeLookUpRecord;

typedef struct
{
	SOCKET socket; //Socket��š�
	sockaddr_in addr;
	string szNetworkID; //������
	string szRecvBuf;
	UINT gbytes;
	UINT nRecvLength;
	bool bLogin; //�Ƿ��¼
	UINT timecnt;
	UINT nNetworkOrd; //���
} Client_Record, *PClient_Record;

typedef struct
{
	BYTE nCom_port; //���ںš�
	bool bBusyStatus; //����״̬��False������״̬��True��æµ״̬��
} tagCommStatusRecord, *PtagCommStatusRecord;

typedef struct
{
	string IP; //IP��ַ
	int port1; //�˿�1��ַ  BX-GPRS
	int port2; //�˿�2��ַ  zw-GPRS
	int port3; //�˿�2��ַ  QT-GPRS
	int languageid; //���Ե���ʾ
	int sendtime; //���͵ĳ�ʱʱ������ֵĳ�ʱʱ��
	int refresh; //���߼��ˢ��ʱ��
	bool useuser; //ʹ���û���½�Ĺ���
	string urltime; //����Уʱ��ַ
	bool autotime; //�Զ�����Уʱ
	bool noblank; //ʹ�ò�����Ļ�ķ�ʽ  ��β����
	bool singalsend; //ʹ�õ�������Ⱥ��
	bool bTiming_Communicaion; //�Ƿ�ʱ������Ϣ��
	UINT nTiming_Communication_CMD; //��ʱ�������
	UINT nTiming_Communication_Interval; //��ʱ���ͼ����
	string ApplicationTitle;
	bool bShowHelpMenu;
} SysParameter;

typedef struct
{
	string szRELBuf;
	UINT nRELLength;
	UINT nRELAddress;
} tagUSBFirmwareRecord, *PtagUSBFirmwareRecord;

typedef enum
{
	seOpenCommError //�򿪴���ʧ��
	, seSendError //��������ʧ��
	, SeNoAnswer //û��Ӧ��
	, seAnswerError //Ӧ��ʧ��
	, seSrcAddrError //Ӧ��Դ��ַ(��ʾ����ַ)��ַ��Ϣ����Ӧ���뷢�͵�Ŀ���ַ��Ϣһ����
	, seDstAddrError //Ӧ��Ŀ���ַ(��������Ͷ�)��ַ��Ϣ����Ӧ���뷢�͵�Դ��ַ��Ϣһ����
	, seProtocolVerError //Э��ջ�汾��һ���Ҳ����� ��Ӧ���뷢�͵İ汾һ�»��߼��ݡ�
	, seProtecolTypeError //Э��ջ���Ͳ�һ�µ��´��� ��Ӧ���뷢�͵�����һ��
	, seDeviceTypeError //�豸���Ͳ�һ�µ��´���   ��Ӧ���뷢�͵�����һ��
	, sePHYTypeError //��������Ͳ�һ�µ��´��� ��Ӧ���뷢�͵�����һ��
	, seMsgSeqError //��Ϣ��Ų�һ�µ��´���   ��Ӧ�õ��ڷ��͵���Ϣ��ż���$8000
	, seOK //���ͳɹ�
	, seNoneSerialProt //δ�趨���ڴ���
	, seInvalid_Socket //����Socketʧ��
	, seSocket_Error //Socket���Ӵ���
	, seSocket_OK //Socket������
	, seUnCompatbile //Firmware�汾�����ݣ�

					 //��ת��������Ϣ
	, seTranitSocket_LinkError //������ת������ʧ��
	, seTranit_Error //����ת������ͨ��ʧ��
	, seTranit_OK //����ת������ͨ�ųɹ�
} TSendError;

//DWORD GetStrInt(string Str);
bool StrIsInt(string Source);
list<string> SplitString(string Source, string Deli);
//COLORREF GetColorOrdToColorValue(DWORD nColorOrd);
//void streamToBmp(ifstream Stream, DWORD Width, DWORD Height, DWORD ColorDepth, DWORD OffBits, HBITMAP &Bmp);

//function GetNewProgramID(tmpProject_ja: TSuperArray) : Cardinal; //�õ���ǰ��ʾ����Ŀ��Ĭ�����ơ�
//function GetNewAreaID(tmpProject_ja: TSuperArray; nProID: Cardinal; nAreaType: Cardinal) : Cardinal; //�õ���ǰ��Ŀ�������Ĭ�����ơ�
//function GetScreenColorType(nScreenColor: Cardinal) : Cardinal; //ͨ����ʾ����ɫ��ŵõ���ʾ�������ͱ���
//function GetScreenColor(nScreenColorType: Cardinal) : Cardinal; //ͨ����ʾ�������ͱ���õ���ʾ����ɫ��š�
//procedure GetProgramFrameColorBmp(canv: TCanvas; nWidth, nHeight, nColorOrd: Cardinal);
//procedure DeleteDir(sDirectory: string);
//function GetValidString(const Source, Ch: string) : string;
void CreateFrameArray(UINT singleColorCount, UINT multiColorCount);
UINT GetSelFrameWidth(UINT nDY_AreaFMode, UINT nDY_AreaFLine);
//; var arySingleColorBmp: array of TBitmap;var aryMuliColorBmp: array of TBitmap);
//procedure RestartApplication(bIsRunAgain: Boolean); // �������
int GetSelScreenArrayOrd(int nScreenNo, const Json::Value &Screen_Ja);
int GetSelScreenDYAreaOrd(int nDYAreaID, Json::Value &DYArea_Ja);
//procedure SaveCurUSBOptive(nDataFormat, nSetParameter, nSetScanConfigurations, nAdjustLight, nTimerSwitch
//	, nFirmwareUpdate, nProgramUpdate, nCorrectTime: Byte;
//nAdvanceMinute, nAdvanceSecond: Byte; szSetupFile: WideString);

BYTE GetBmpPixelFormat(BYTE nPx);
void DoEvents();

void GetControllerList(Json::Value &ControllerList_Obj, Json::Value &Controller_Supary);
Json::Value GetControllerObject(const Json::Value &Controller_Supary, UINT nControllerType, BYTE &nProtocolVer);
//function GetControllerObject(Controller_Supary: TSuperArray;
//const nProtocolVerOrd, nControllerTypeOrd: Cardinal;
//var nProtocolVer : Byte) : ISuperObject; overload;
void GetController_DecomposeType(int nControllerType, BYTE &nTypeValue1, BYTE &nTypeValue2);//ͨ�����ƿ��ͺŵõ����ƿ��ķֽ��ͺ�
Json::Value GetDefaultController(BYTE &nProtocolVer, UINT &nControllerType);
UINT GetControllerType(Json::Value Controller_obj);

//function UnicodeToAnsi(const s : string; const nLength : Cardinal) : string;
//procedure SaveToFile(Text:string; Filename:String);