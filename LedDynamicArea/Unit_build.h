#pragma once

const DWORD VERYLARGEVALUE = 0xFFFFFFF;
const int START_YEAR = 1901;
const int END_YEAR = 2050;

typedef DWORD TTntMemo;
typedef DWORD TRVReportHelper;
typedef DWORD TRVStyle;
typedef DWORD TCustomRVData;
typedef DWORD IGPImage;
typedef DWORD TCanvas;
typedef DWORD TBitmap;

const string stylelist[] = { "tm_year", "tm_month", "tm_day", "tm_hour",
"tm_minute", "tm_second", "tm_apm", "tm_week", "tm_bp", "tm_js", "tm_jr",
"tm_ymd", "tm_hns", "tm_txt" };
//const string stylearr[] = { "year_list", "month_list", "day_list", "hour_list", "minute_list", "second_list",
//"ampm_list", "week_list", "bp_list", "js_list", "jr_list", "ymd_list", "hns_list" };
const string Decimal[] = { "12", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11" };
const string Roman[] = { "XII", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI" };

typedef struct
{
	string Name;
	int ID;
} TCharSetRec;

string MakeTWValue(Json::Value Controller_obj, BYTE nProtocolVer,
	DWORD thrd_ScreenWidth, DWORD thrd_ScreenHeight, DWORD thrd_ScreenColor, DWORD thrd_ScreenPixels,
	DWORD thrd_ScreenPixType, DWORD thrd_ScreenStyle, SYSTEMTIME &dtFirmwareDateTimeVer, TRVStyle t_rvstyle,
	TTntMemo t_memo, TRVReportHelper t_RVReportHelper, Json::Value Screen_Supary, Json::Value project_Supary,
	DWORD nX, DWORD nY, DWORD nWidth, DWORD nHeight, DWORD nRimTop, DWORD nRimLeft, DWORD nRimRight, DWORD nRimBottom,
	DWORD nScreenOrd, DWORD nProgramOrd, DWORD nAreaOrd); //������Ŀ��ͼ����������� ------�¿�

string MakeNULLArea(string szAreaName, DWORD w, DWORD h, DWORD x, DWORD nPx, DWORD nMkStyle,
	DWORD nKardPixType, DWORD nScreenStyle, DWORD nStunt, DWORD nOutStunt, DWORD nRunSpeed, DWORD nShowTime, DWORD nShowCount, 
	DWORD nReserved1, DWORD nReserved2, DWORD nReserved3, DWORD nReserved4, DWORD nReserved5, DWORD nReserved6, DWORD nReserved7);
DWORD calpagesize(DWORD left, DWORD width, DWORD nPx, DWORD nKardPixType); //�����ҳ�Ŀ��

void calRTFsingalpage(TRVReportHelper t_RVReportHelper, DWORD w, DWORD h,
	DWORD &realw, DWORD &realh, DWORD &nrealw); //: Cardinal; //���RTF������ʾ��ʱ���ʵ�ʿ��

string MakeString(DWORD thrd_ScreenWidth, DWORD thrd_ScreenHeight, DWORD thrd_ScreenColor,
	DWORD thrd_ScreenPixels, DWORD thrd_ScreenPixType, DWORD thrd_ScreenStyle, TRVStyle t_rvstyle,
	TRVReportHelper t_RVReportHelper, Json::Value project_Supary, DWORD nX, DWORD nY,
	DWORD nWidth, DWORD nHeight, DWORD nProgramOrd, DWORD nAreaOrd, DWORD &nFilePageCount); //��txt�ı��ļ� ,���а����ⲿ�򿪣��Ƿ�ʹ�õ��л����
void RemoveParagraphBreaks(TCustomRVData RVData);
//ת��ÿһ����Ϣ�����ݣ���Щ��Ϣ����txt,jpg,gif,�����ı��������ı���ʱ�䣬���
//ͼ�������е��ļ�ת��
string MakebmpTxt(DWORD thrd_ScreenWidth, DWORD thrd_ScreenHeight, DWORD thrd_ScreenColor,
	DWORD thrd_ScreenPixels, DWORD thrd_ScreenPixType, DWORD thrd_ScreenStyle, TRVStyle t_rvstyle,
	TTntMemo t_memo, TRVReportHelper t_RVReportHelper, Json::Value AreaFile_Obj,
	DWORD nX, DWORD nY, DWORD nWidth, DWORD nHeight, DWORD &nFilePageCount); //��txt�ı��ļ� ,���а����ⲿ�򿪣��Ƿ�ʹ�õ��л����
string MakebmpText(DWORD thrd_ScreenWidth, DWORD thrd_ScreenHeight, DWORD thrd_ScreenColor,
	DWORD thrd_ScreenPixels, DWORD thrd_ScreenPixType, DWORD thrd_ScreenStyle, TRVStyle t_rvstyle,
	TTntMemo t_memo, TRVReportHelper t_RVReportHelper, Json::Value AreaFile_Obj,
	DWORD nX, DWORD nY, DWORD nWidth, DWORD nHeight, DWORD  &nFilePageCount); //�ı�

string MakebmpRTF(DWORD thrd_ScreenWidth, DWORD thrd_ScreenHeight, DWORD thrd_ScreenColor,
	DWORD thrd_ScreenPixels, DWORD thrd_ScreenPixType, DWORD thrd_ScreenStyle,
	TRVReportHelper t_RVReportHelper, Json::Value AreaFile_Obj,
	DWORD nX, DWORD nY, DWORD nWidth, DWORD nHeight, DWORD &nFilePageCount); //��RTF�ļ������а����ⲿ��
string  MakebmpJPGBMP(DWORD thrd_ScreenWidth, DWORD thrd_ScreenHeight, DWORD thrd_ScreenColor,
	DWORD thrd_ScreenPixels, DWORD thrd_ScreenPixType, DWORD thrd_ScreenStyle,
	Json::Value AreaFile_Obj, DWORD nX, DWORD nY, DWORD nWidth, DWORD nHeight,
	DWORD &nFilePageCount); //��ͼƬ�ļ�����Ҫ���ⲿ��
string MakebmpRVF(DWORD thrd_ScreenWidth, DWORD thrd_ScreenHeight, DWORD thrd_ScreenColor,
	DWORD thrd_ScreenPixels, DWORD thrd_ScreenPixType, DWORD thrd_ScreenStyle, TRVStyle t_rvstyle,
	TRVReportHelper t_RVReportHelper, Json::Value AreaFile_Obj,
	DWORD nX, DWORD nY, DWORD nWidth, DWORD nHeight, DWORD &nFilePageCount); //�򿪶����ı��������ı�RVF�ļ�
string MakebmpGRID(DWORD thrd_ScreenWidth, DWORD thrd_ScreenHeight, DWORD thrd_ScreenColor,
	DWORD thrd_ScreenPixels, DWORD thrd_ScreenPixType, DWORD thrd_ScreenStyle,
	TRVReportHelper t_RVReportHelper, Json::Value AreaFile_Obj,
	DWORD nX, DWORD nY, DWORD nWidth, DWORD nHeight, DWORD &nFilePageCount); //�򿪱���ļ�
string MakebmpGIF(DWORD thrd_ScreenWidth, DWORD thrd_ScreenHeight, DWORD thrd_ScreenColor,
	DWORD thrd_ScreenPixels, DWORD thrd_ScreenPixType, DWORD thrd_ScreenStyle, Json::Value AreaFile_Obj,
	DWORD nX, DWORD nY, DWORD nWidth, DWORD nHeight, DWORD &nFilePageCount); //��GIF�ļ�

string MakegifImage(DWORD count, DWORD w, DWORD h, DWORD x, DWORD nPx, DWORD nMkStyle, DWORD nKardPixType, DWORD nScreenStyle, IGPImage t_img,
	DWORD nDataStyle, DWORD nStunt, DWORD nOutStunt, DWORD nRunSpeed, DWORD nShowTime, DWORD nShowCount
	, DWORD nReserved1, DWORD nReserved2, DWORD nReserved3, DWORD nReserved4, DWORD nReserved5
	, DWORD nReserved6, DWORD nReserved7, DWORD &nRealPageCount); //ת��GIF����

string MakeDoubleImage(HFONT hFont, COLORREF fontColor, const string &str, DWORD count, DWORD w, DWORD h, DWORD x, DWORD nPx, DWORD nMkStyle, DWORD nKardPixType, DWORD nScreenStyle,
	DWORD nStunt, DWORD nOutStunt, DWORD nRunSpeed, DWORD nShowTime, DWORD nShowCount, DWORD nReserved1
	, DWORD nReserved2, DWORD nReserved3, DWORD nReserved4, DWORD nReserved5, DWORD nReserved6
	, DWORD nReserved7, bool bOnePage, DWORD &nRealPageCount); //ת����������

string MakeGridImage(TRVReportHelper t_RVReportHelper, DWORD count, DWORD w, DWORD h, DWORD x, DWORD nPx, DWORD nMkStyle, DWORD nKardPixType, DWORD nScreenStyle,
	DWORD nDataStyle, DWORD nStunt, DWORD nOutStunt, DWORD nRunSpeed, DWORD nShowTime, DWORD nShowCount
	, DWORD nReserved1, DWORD nReserved2, DWORD nReserved3, DWORD nReserved4, DWORD nReserved5
	, DWORD nReserved6, DWORD nReserved7, DWORD &nRealPageCount); //ת���������

string MakeSigalImage(TRVReportHelper t_RVReportHelper,
	DWORD count, DWORD w, DWORD h, DWORD x, DWORD nPx, DWORD nMkStyle, DWORD nKardPixType, DWORD nScreenStyle,
	DWORD nStunt, DWORD nOutStunt, DWORD nRunSpeed, DWORD nShowTime, DWORD nShowCount,
	DWORD nReserved1, DWORD nReserved2, DWORD nReserved3, DWORD nReserved4, DWORD nReserved5, DWORD nReserved6,
	DWORD nReserved7, DWORD nrealwidth, bool bOnePage, DWORD &nRealPageCount);

string MakeRightSigalImage(TRVReportHelper t_RVReportHelpe,
	DWORD count, DWORD w, DWORD h, DWORD x, DWORD nPx, DWORD nMkStyle, DWORD nKardPixType, DWORD nScreenStyle,
	DWORD nStunt, DWORD nOutStunt, DWORD nRunSpeed, DWORD nShowTime, DWORD nShowCount,
	DWORD nReserved1, DWORD nReserved2, DWORD nReserved3, DWORD nReserved4, DWORD nReserved5, DWORD nReserved6,
	DWORD nReserved7, DWORD nrealwidth, bool bOnePage, DWORD &nRealPageCount); //ת���������Ƶ�������

string MakebmpImage(string filename, DWORD w, DWORD h, DWORD x, DWORD nPx, DWORD nMkStyle, DWORD nKardPixType, DWORD nScreenStyle
	, DWORD nStunt, DWORD nOutStunt, DWORD nRunSpeed, DWORD nShowTime, DWORD nShowCount
	, DWORD nReserved1, DWORD nReserved2, DWORD nReserved3, DWORD nReserved4, DWORD nReserved5, DWORD nReserved6
	, DWORD nReserved7, DWORD &nRealPageCount); //ת��ͼƬ����
string MakePageImageupscroll(TRVReportHelper t_RVReportHelper, DWORD count, DWORD w, DWORD h, DWORD x, DWORD nPx, DWORD nMkStyle, DWORD nKardPixType, DWORD nScreenStyle,
	DWORD nStunt, DWORD nOutStunt, DWORD nRunSpeed, DWORD nShowTime, DWORD nShowCount
	, DWORD nReserved1, DWORD nReserved2, DWORD nReserved3, DWORD nReserved4, DWORD nReserved5
	, DWORD nReserved6, DWORD nReserved7, bool bOnePage, DWORD &nRealPageCount);

void FillPageInfoupscroll(TRVReportHelper t_RVReportHelper, DWORD w, DWORD h, DWORD &nupscrollPageCount); //�������Ƶ�ʱ����

DWORD MMToPixels(DWORD mm, DWORD ppi);
void FillPageInfo(TRVReportHelper t_RVReportHelper, DWORD w, DWORD h);
void DrawPage(TRVReportHelper t_RVReportHelper, TCanvas Canvas, DWORD PageNo, DWORD h);
void DrawGRIDPage(TRVReportHelper t_RVReportHelper, TCanvas Canvas, DWORD PageNo, DWORD h);
void DrawsingalPage(TRVReportHelper t_RVReportHelper, TCanvas Canvas, DWORD h); //�����д���

DWORD realspeed(DWORD w, DWORD h, DWORD sped, string c_style); //����ʵ�ʵ��ٶ�ֵ
int rgbshow(int rgb, DWORD nScreenColor, DWORD nMkStyle); //������ɫ��ת���㷨
DWORD ColorOrdShow(DWORD nColorOrd, DWORD nScreenColor, DWORD nMkStyle); //ͨ����ɫ��ŵõ���ɫֵ��
																			   //�����������ת��ͼƬΪʵ�����ݵĹ���
list<string> SplitString(const string &Source, string &Ch);
string IntConvertHex(DWORD A, DWORD Len);
string tohex(string s);

//���ֶ���
void DrawFinalImage(int File_Width, int File_Height, int Screen_color, int Screen_pix, TBitmap bmp2);

string MakeProValue(DWORD nScreenOrd, DWORD nProgramOrd,
	SYSTEMTIME dtFirmwareDateTimeVer, BYTE ntmpBXCEColor,
	Json::Value Screen_Supary, Json::Value project_Supary, DWORD &nSendLength); //������Ŀ�����Բ���  ------�¿�
string BuildProgramInfo(DWORD screenid, DWORD proid,
	SYSTEMTIME dtFirmwareDateTimeVer, Json::Value Screen_Supary, Json::Value project_Supary,
	DWORD &nSendLength, BYTE ntmpBXCEColor);

void ScreenProgramsInfo(DWORD nScreenOrd, list<DWORD> lstSendProgram, Json::Value Screen_ja, Json::Value Program_ja);

//nPlayMode:�ϵ��Ƿ���ʾ��0���ϵ粻��ʾ��1���ϵ���ʾ
string MakeScreenLOGOValue(Json::Value Screen_Supary, DWORD nScreenOrd, DWORD &nSendLength); //����LOGO������档

DWORD GetPageSize(DWORD nAllWidth, DWORD nHeight, DWORD nPx);

void TranCanvToInfo(LPBYTE Bmp, string &pInfoBuf,
	DWORD nLeft, DWORD nWidth, DWORD nHeight, DWORD nPx, DWORD nMkStyle, DWORD nPixType,
	DWORD nControllerType, BOOL &bInvalidData);

string MakeFrameValue(Json::Value Screen_Obj, DWORD nDYAreaOrd);
void GetRealDYAreaLocation(Json::Value DYArea_Obj, DWORD &nRealX, DWORD &nRealY, DWORD &nRealW, DWORD &nRealH);


string MakeDynamicAreaInfo(DWORD nScreenOrd, DWORD nDYAreaOrd, Json::Value Screen_ja,
	DWORD &nSendLength);

string MakebmpTxtSinglePage(DWORD thrd_ScreenWidth, DWORD thrd_ScreenHeight, DWORD thrd_ScreenColor,
	DWORD thrd_ScreenPixels, DWORD thrd_ScreenPixType, DWORD thrd_ScreenStyle, TRVStyle t_rvstyle,
	TTntMemo t_memo, TRVReportHelper t_RVReportHelper, Json::Value AreaFile_Obj,
	DWORD nX, DWORD nY, DWORD nWidth, DWORD nHeight, DWORD &nFilePageCount); //��txt�ı��ļ� ,���а����ⲿ�򿪣��Ƿ�ʹ�õ��л����

string MakebmpTextSinglePage(DWORD thrd_ScreenWidth, DWORD thrd_ScreenHeight, DWORD thrd_ScreenColor,
	DWORD thrd_ScreenPixels, DWORD thrd_ScreenPixType, DWORD thrd_ScreenStyle, TRVStyle t_rvstyle,
	TTntMemo t_memo, TRVReportHelper t_RVReportHelper, Json::Value AreaFile_Obj,
	DWORD nX, DWORD nY, DWORD nWidth, DWORD nHeight, DWORD &nFilePageCount); //��txt�ı��ļ� ,���а����ⲿ�򿪣��Ƿ�ʹ�õ��л����

string MakeDynamicAreaPageInfo(DWORD nScreenOrd, DWORD nDYAreaOrd, DWORD nFileOrd, DWORD nPageOrd, Json::Value Screen_ja,
	DWORD &nSendLength);

SYSTEMTIME StringToDatetime(string &DateStr);