#include "stdafx.h"
#include "Unit_build.h"

#include "MyDataType.h"
#include "TranInfo.h"

#define NumCharSets 19

extern vector<DWORD> g_aryProFrameSingleColorBmp;
extern vector<DWORD> g_aryProFrameMuliColorBmp;

TCharSetRec CharSets[NumCharSets] = { { "ANSI_CHARSET",  0},
{"DEFAULT_CHARSET",  1},
{"SYMBOL_CHARSET",  2},
{"SHIFTJIS_CHARSET",  0x80},
{"HANGEUL_CHARSET",  129},
{"GB2312_CHARSET",  134},
{"CHINESEBIG5_CHARSET",  136},
{"OEM_CHARSET",  255},
{"JOHAB_CHARSET",  130},
{"HEBREW_CHARSET",  177},
{"ARABIC_CHARSET",  178},
{"GREEK_CHARSET",  161},
{"TURKISH_CHARSET",  162},
{"VIETNAMESE_CHARSET",  163},
{"THAI_CHARSET",  222},
{"EASTEUROPE_CHARSET",  238},
{"RUSSIAN_CHARSET",  204},
{"MAC_CHARSET",  77},
{"BALTIC_CHARSET",  186} };

void GetProgramFrameColorBmp(BYTE *pBits, DWORD nWidth, DWORD nHeight, DWORD nColorOrd);

int GetMaxInArray(int A[], size_t size)
{
	int tmpMax;

	if (size <= 0)
	{
		return 0;
	}

	tmpMax = A[0];
	for (size_t i = 1; i < size; ++i)
	{
		if (A[i] > tmpMax)
		{
			tmpMax = A[i];
		}
	}

	return tmpMax;
}

SYSTEMTIME StringToDatetime(string &DateStr) //将yyyy-mm-dd hh:nn:ss格式的字符串转为时间格式
{
	SYSTEMTIME dateTime;

	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;

	sscanf_s(DateStr.c_str(), "%d-%d-%d %d:%d:%d", &year, &month, &day,
		&hour, &minute, &second);

	dateTime.wYear = (WORD)year;
	dateTime.wMonth = (WORD)month;
	dateTime.wDay = (WORD)day;
	dateTime.wHour = (WORD)hour;
	dateTime.wMinute = (WORD)minute;
	dateTime.wSecond = (WORD)second;

	return dateTime;
}

list<string> SplitString(const string &Source, const string &Deli)
{
	list<string> result;
	char *pBuffer = new char[Source.size() + 1];
	char *pToken = NULL;
	char *next_token = NULL;

	strcpy_s(pBuffer, Source.size() + 1, Source.c_str());
	pToken = strtok_s(pBuffer, Deli.c_str(), &next_token);

	while (pToken)
	{
		result.push_back(pToken);
		pToken = strtok_s(NULL, Deli.c_str(), &next_token);
	}

	delete[] pBuffer;

	return result;
}

DWORD calpagesize(DWORD left, DWORD width, DWORD nPx, DWORD nKardPixType)
{
	DWORD nStartPoint, nEndPoint;
	DWORD nEndSpace, nStartSpace, nAllWidth;
	DWORD Result = width;

	switch (nPx)
	{
	case SCREEN_COLOR_SINGLE:
	case SCREEN_COLOR_DOUBLE:
	case SCREEN_COLOR_THREE:
		/////////////////////////协议的头
		nStartPoint = nKardPixType; //左边有效位数。
		if ((left % nKardPixType) != 0)
			nStartPoint = nKardPixType - left % nKardPixType;

		nEndPoint = nKardPixType; //右边的有效位数
		if ((left + width) % nKardPixType != 0)
			nEndPoint = (left + width) % nKardPixType;

		nStartSpace = left % nKardPixType; //左边的无效位数；

		nEndSpace = 0; //右边的无效位数
		if ((left + width) % nKardPixType != 0)
			nEndSpace = nKardPixType - (left + width) % nKardPixType;

		nAllWidth = width + nStartSpace + nEndSpace; //得到转换后的实际宽度
		Result = nAllWidth;
		break;
	case SCREEN_COLOR_FULLCOLOR:
		Result = width;
		break;
	}

	return Result;
}

string MakeNULLArea(string szAreaName, DWORD w, DWORD h, DWORD x, DWORD nPx, DWORD nMkStyle, DWORD nKardPixType,
					DWORD nScreenStyle, DWORD nStunt, DWORD nOutStunt, DWORD nRunSpeed, DWORD nShowTime,
					DWORD nShowCount, DWORD nReserved1, DWORD nReserved2, DWORD nReserved3, DWORD nReserved4, DWORD nReserved5,
					DWORD nReserved6, DWORD nReserved7)
{
	LPBYTE mBmpPage;
	string szBmpTextBuf;
	DWORD nAllWidth, nPageSize;
	DWORD nCurAddress;
	DWORD ncurPageAllLength;
	string szcurPagebuf;
	BOOL bInvalidData;
	HWND hDestopWnd = GetDesktopWindow();
	HDC hDesktopDC = GetWindowDC(hDestopWnd);
	HDC hMemoryDC = CreateCompatibleDC(hDesktopDC);
	BITMAPINFO bmpInfo;
	int bytesPerLine = (w * 3 + 1) / 2 * 2;

	nAllWidth = calpagesize(x, w, nPx, nKardPixType);
	memset(&bmpInfo, 0, sizeof(BITMAPINFOHEADER));
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth = w;
	bmpInfo.bmiHeader.biHeight = h;
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biSizeImage = bytesPerLine * h;
	bmpInfo.bmiHeader.biBitCount = 24;

	HBITMAP hCanvasBmp = CreateDIBSection(hMemoryDC, &bmpInfo, DIB_RGB_COLORS, (void**)&mBmpPage, NULL, 0);
	HBITMAP hOldBmp = (HBITMAP)SelectObject(hMemoryDC, hCanvasBmp);
	HBRUSH hBlackBrush = CreateSolidBrush(RGB(0, 0, 0));
	RECT rect = { 0, 0, (LONG)w, (LONG)h };
	LOGFONT logFont = { 10, 0, 0,  0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, TEXT("Tahoma")};
	HFONT hFont = CreateFontIndirect(&logFont);

	FillRect(hMemoryDC, &rect, hBlackBrush);
	SetTextColor(hMemoryDC, RGB(255, 0, 0));
	SelectObject(hMemoryDC, hFont);

	int areaNameLength = szAreaName.size() + 1;
	WCHAR *wszAreaName = new WCHAR[areaNameLength];
	memset(wszAreaName, 0, sizeof(WCHAR) * areaNameLength);
	MultiByteToWideChar(CP_ACP, 0, szAreaName.c_str(), -1, wszAreaName, areaNameLength);
	DrawText(hMemoryDC, wszAreaName, -1, &rect, DT_SINGLELINE);
	delete [] wszAreaName;

	szcurPagebuf = "";
	szcurPagebuf.push_back(char(0)); //数据类型
	szcurPagebuf.push_back(char(nStunt));
	szcurPagebuf.push_back(char(nOutStunt));
	szcurPagebuf.push_back(char(nRunSpeed));
	szcurPagebuf.push_back(char(nShowTime & 0xFF));
	szcurPagebuf.push_back(char((nShowTime >> 8) & 0xFF));
	szcurPagebuf.push_back(char(nShowCount));
	szcurPagebuf.push_back(char(nReserved1)); //保留字
	szcurPagebuf.push_back(char(nReserved2)); //保留字
	szcurPagebuf.push_back(char(nReserved3)); //保留字
	szcurPagebuf.push_back(char(nReserved4)); //保留字
	szcurPagebuf.push_back(char(nReserved5)); //保留字
	szcurPagebuf.push_back(char(nReserved6));; //保留字

	nCurAddress= szcurPagebuf.size();
	nPageSize= GetPageSize(nAllWidth, h, nPx);
	//SetLength(szcurPagebuf, nCurAddress + nPageSize);
	//Inc(nCurAddress);
	TranCanvToInfo(mBmpPage, szcurPagebuf, x, w, h, nPx, nMkStyle,
		nKardPixType, nScreenStyle, bInvalidData);
	ncurPageAllLength = szcurPagebuf.size();

	szBmpTextBuf.push_back((char)(ncurPageAllLength & 0xFF));
	szBmpTextBuf.push_back((char)((ncurPageAllLength >> 8) & 0xFF));
	szBmpTextBuf.push_back((char)((ncurPageAllLength >> 16) & 0xFF));
	szBmpTextBuf.push_back((char)((ncurPageAllLength >> 24) & 0xFF));
	szBmpTextBuf.append(szcurPagebuf);

	SelectObject(hMemoryDC, hOldBmp);
	DeleteObject(hBlackBrush);
	DeleteObject(hFont);
	DeleteObject(hCanvasBmp);
	DeleteDC(hMemoryDC);
	ReleaseDC(hDestopWnd, hDesktopDC);

	return szBmpTextBuf;
}

string MakeDynamicAreaInfo(DWORD nScreenOrd, DWORD nDYAreaOrd, Json::Value Screen_ja,
						   DWORD &nSendLength)
{
	string Result;
	string szSendBuf, szTWSendBuf;
	DWORD I, J, /*nCurAddress,*/ nDataLength;
	BYTE nRunMode, nAllProRelate, nImmePlay;
	DWORD nTimeOut, nRelateProNum, nRelateProID, nAreaX, nAreaY, nAreaWidth, nAreaHeight;
	DWORD nTotlePagecount, ntmpPageCount;
	DWORD nScreenWidth, nScreenHeight, nScreenColor, nScreenPixels, nScreenPixType, nScreenStyle;
	DWORD nRealX, nRealY, nRealW, nRealH;
	TRVStyle t_rvstyle = 0;
	TRVReportHelper t_RVReportHelper = 0;
	TTntMemo t_memo = 0; ///主要操作txt文件

	nRunMode = (BYTE)Screen_ja[(int)nScreenOrd]["Screen_lstDYArea"][(int)nDYAreaOrd]["DY_RunMode"].asUInt();
	if ((nRunMode < 0) || (nRunMode > 4))
		nRunMode = 0;

	nTimeOut = Screen_ja[(int)nScreenOrd]["Screen_lstDYArea"][(int)nDYAreaOrd]["DY_TimeOut"].asUInt();
	nAllProRelate = (BYTE)Screen_ja[(int)nScreenOrd]["Screen_lstDYArea"][(int)nDYAreaOrd]["DY_AllProRelate"].asUInt();

	if (nAllProRelate != 0)
		nAllProRelate = 1;
	nImmePlay = (BYTE)Screen_ja[(int)nScreenOrd]["Screen_lstDYArea"][(int)nDYAreaOrd]["DY_PlayImmediately"].asUInt();
	nAreaX = Screen_ja[(int)nScreenOrd]["Screen_lstDYArea"][(int)nDYAreaOrd]["DY_AreaX"].asUInt();
	nAreaY = Screen_ja[(int)nScreenOrd]["Screen_lstDYArea"][(int)nDYAreaOrd]["DY_AreaY"].asUInt();
	nAreaWidth = Screen_ja[(int)nScreenOrd]["Screen_lstDYArea"][(int)nDYAreaOrd]["DY_AreaWidth"].asUInt();
	nAreaHeight = Screen_ja[(int)nScreenOrd]["Screen_lstDYArea"][(int)nDYAreaOrd]["DY_AreaHeight"].asUInt();
	nRelateProNum = Screen_ja[(int)nScreenOrd]["Screen_lstDYArea"][(int)nDYAreaOrd]["DY_ProRelateList"].size();

	nScreenWidth = Screen_ja[(int)nScreenOrd]["Screen_Width"].asUInt();
	nScreenHeight = Screen_ja[(int)nScreenOrd]["Screen_Height"].asUInt();
	nScreenColor = Screen_ja[(int)nScreenOrd]["Screen_color"].asUInt();
	nScreenPixels = Screen_ja[(int)nScreenOrd]["Screen_pixels"].asUInt();
	nScreenPixType = Screen_ja[(int)nScreenOrd]["Screen_nPixType"].asUInt();
	nScreenStyle = Screen_ja[(int)nScreenOrd]["Screen_control"].asUInt();

	//------------------------------------------------------------------------------
	// 所需控件初始化
	/*t_rvstyle = trvstyle.Create(nil);
	t_rvstyle.Color  = clblack;
	t_rvstyle.TextStyles.Add;
	t_rvstyle.ParaStyles.Add;
	t_rvstyle.TextStyles.Add.Unicode  = true;
	t_rvstyle.ParaStyles.Add.Standard  = true;
	t_RVReportHelper = tRVReportHelper.Create(nil);
	t_RVReportHelper.RichView.Style  = t_rvstyle;
	t_RVReportHelper.RichView.Parent  = Frm_parent;
	t_RVReportHelper.RichView.Visible  = false;
	t_RVReportHelper.RichView.LeftMargin  = 0;
	t_RVReportHelper.RichView.BottomMargin  = 0;
	t_RVReportHelper.RichView.RightMargin  = 0;
	t_RVReportHelper.RichView.TopMargin  = 0;
	t_RVReportHelper.RichView.RTFReadProperties.UnicodeMode  = rvruOnlyUnicode;
	t_RVReportHelper.RichView.RTFReadProperties.TextStyleMode  = rvrsAddIfNeeded;
	t_RVReportHelper.RichView.RTFReadProperties.ParaStyleMode  = rvrsAddIfNeeded;*/

	/*t_memo = TTntMemo.Create(nil);
	t_memo.left  = 200;
	t_memo.top  = 10;
	t_memo.Width  = 100;
	t_memo.height  = 100;
	t_memo.Font.Color  = clred;
	t_memo.Font.Charset  = DEFAULT_CHARSET;
	t_memo.Font.Name  = "Tahoma";
	t_memo.Font.Size  = 12;
	t_memo.Font.Style  = [];
	t_memo.BorderStyle  = bsNone;
	t_memo.Ctl3D  = false;
	t_memo.Parent  = Frm_parent;
	t_memo.Visible  = false;*/
	//------------------------------------------------------------------------------

	szSendBuf.clear();
	szSendBuf.push_back((char)Screen_ja[(int)nScreenOrd]["Screen_lstDYArea"][(int)nDYAreaOrd]["DY_AreaID"].asUInt());
	szSendBuf.push_back((char)nRunMode);
	szSendBuf.push_back((char)(nTimeOut & 0xFF));
	szSendBuf.push_back((char)((nTimeOut >> 8) & 0xFF));
	szSendBuf.push_back((char)nAllProRelate);
	szSendBuf.push_back((char)(nRelateProNum & 0xFF));
	szSendBuf.push_back((char)((nRelateProNum >> 8) & 0xFF));

	for (I = 0; I < nRelateProNum; ++I)
	{
		nRelateProID = Screen_ja[(int)nScreenOrd]["Screen_lstDYArea"][(int)nDYAreaOrd]["DY_ProRelateList"][(int)I]["RelateProID"].asUInt();
		szSendBuf.push_back((char)(nRelateProID & 0xFF));
		szSendBuf.push_back((char)((nRelateProID >> 8) & 0xFF));
	}

	szSendBuf.push_back((char)(nImmePlay));
	szSendBuf.push_back((char)(0));
	szSendBuf.push_back((char)(0));
	szSendBuf.push_back((char)(0));
	szSendBuf.push_back((char)(0));
	szSendBuf.push_back((char)(0x10));
	szSendBuf.push_back((char)(nAreaX & 0xFF));
	szSendBuf.push_back((char)((nAreaX >> 8) & 0xFF));
	szSendBuf.push_back((char)(nAreaY & 0xFF));
	szSendBuf.push_back((char)((nAreaY >> 8) & 0xFF));
	szSendBuf.push_back((char)(nAreaWidth & 0xFF));
	szSendBuf.push_back((char)((nAreaWidth >> 8) & 0xFF));
	szSendBuf.push_back((char)(nAreaHeight & 0xFF));
	szSendBuf.push_back((char)((nAreaHeight >> 8) & 0xFF));

	szSendBuf = szSendBuf + MakeFrameValue(Screen_ja[(int)nScreenOrd], nDYAreaOrd);
	GetRealDYAreaLocation(Screen_ja[(int)nScreenOrd]["Screen_lstDYArea"][(int)nDYAreaOrd], nRealX, nRealY, nRealW, nRealH);
	nTotlePagecount = 0;
	szTWSendBuf = "";

	if (Screen_ja[(int)nScreenOrd]["Screen_lstDYArea"][(int)nDYAreaOrd]["Area_lstfile"].size() > 0) //节目内有文件
	{
		for (J = 0; J < Screen_ja[(int)nScreenOrd]["Screen_lstDYArea"][(int)nDYAreaOrd]["Area_lstfile"].size(); ++J)
		{
			if (Screen_ja[(int)nScreenOrd]["Screen_lstDYArea"][(int)nDYAreaOrd]["Area_lstfile"][(int)J]["File_Style"].asInt() != 1) //图文格式数据；
			{
				switch (Screen_ja[(int)nScreenOrd]["Screen_lstDYArea"][(int)nDYAreaOrd]["Area_lstfile"][(int)J]["File_Style"].asUInt())
				{
					//case FILE_TYPE_BMP:
					//case FILE_TYPE_JPG:
					//	szTWSendBuf = szTWSendBuf + MakebmpJPGBMP(nScreenWidth, nScreenHeight, nScreenColor, nScreenPixels, nScreenPixType, nScreenStyle
					//		, Screen_ja[(int)nScreenOrd]["Screen_lstDYArea"][(int)nDYAreaOrd]["Area_lstfile"][(int)J]
					//		, nRealX, nRealY, nRealW, nRealH, ntmpPageCount); //打开图片文件，主要是外部打开
					//	nTotlePagecount = nTotlePagecount + ntmpPageCount;
					//	break;
					//case FILE_TYPE_GIF:
					//	szTWSendBuf = szTWSendBuf + MakebmpGIF(nScreenWidth, nScreenHeight, nScreenColor, nScreenPixels, nScreenPixType, nScreenStyle
					//		, Screen_ja[(int)nScreenOrd]["Screen_lstDYArea"][(int)nDYAreaOrd]["Area_lstfile"][(int)J]
					//		, nRealX, nRealY, nRealW, nRealH, ntmpPageCount); //打开GIF文件
					//	nTotlePagecount = nTotlePagecount + ntmpPageCount;
					//	break;
				case FILE_TYPE_TXT:
					szTWSendBuf = szTWSendBuf + MakebmpTxt(nScreenWidth, nScreenHeight, nScreenColor, nScreenPixels
						, nScreenPixType, nScreenStyle, t_rvstyle, t_memo, t_RVReportHelper
						, Screen_ja[(int)nScreenOrd]["Screen_lstDYArea"][(int)nDYAreaOrd]["Area_lstfile"][(int)J]
					, nRealX, nRealY, nRealW, nRealH, ntmpPageCount); //打开txt文本文件 ,其中包含外部打开，是否使用单行或多行
					nTotlePagecount = nTotlePagecount + ntmpPageCount;
					break;
					//case FILE_TYPE_RTF:
					//	szTWSendBuf = szTWSendBuf + MakebmpRTF(nScreenWidth, nScreenHeight, nScreenColor, nScreenPixels
					//		, nScreenPixType, nScreenStyle, t_RVReportHelper
					//		, Screen_ja[(int)nScreenOrd]["Screen_lstDYArea"][(int)nDYAreaOrd]["Area_lstfile"][(int)J]
					//		, nRealX, nRealY, nRealW, nRealH, ntmpPageCount); //打开RTF文件，其中包含外部打开
					//	nTotlePagecount = nTotlePagecount + ntmpPageCount;
					//	break;
					//case FILE_TYPE_TXTF:
					//case FILE_TYPE_TXTS:
					//	szTWSendBuf = szTWSendBuf + MakebmpRVF(nScreenWidth, nScreenHeight, nScreenColor, nScreenPixels
					//		, nScreenPixType, nScreenStyle, t_rvstyle, t_RVReportHelper
					//		, Screen_ja[(int)nScreenOrd]["Screen_lstDYArea"][(int)nDYAreaOrd]["Area_lstfile"][(int)J]
					//		, nRealX, nRealY, nRealW, nRealH, ntmpPageCount); //打开多行文本，单行文本RVF文t_rvstyle
					//	nTotlePagecount = nTotlePagecount + ntmpPageCount;
					//	break;
					//case FILE_TYPE_TBF:
					//	szTWSendBuf = szTWSendBuf + MakebmpGRID(nScreenWidth, nScreenHeight, nScreenColor, nScreenPixels
					//		, nScreenPixType, nScreenStyle, t_RVReportHelper
					//		, Screen_ja[(int)nScreenOrd]["Screen_lstDYArea"][(int)nDYAreaOrd]["Area_lstfile"][(int)J]
					//		, nRealX, nRealY, nRealW, nRealH, ntmpPageCount); //打开表格文件
					//	nTotlePagecount = nTotlePagecount + ntmpPageCount;
					//	break;
				case FILE_TYPE_TEXT:
					szTWSendBuf = szTWSendBuf + MakebmpText(nScreenWidth, nScreenHeight, nScreenColor, nScreenPixels
						, nScreenPixType, nScreenStyle, t_rvstyle, t_memo, t_RVReportHelper
						, Screen_ja[(int)nScreenOrd]["Screen_lstDYArea"][(int)nDYAreaOrd]["Area_lstfile"][(int)J]
					, nRealX, nRealY, nRealW, nRealH, ntmpPageCount); //打开txt文本文件 ,其中包含外部打开，是否使用单行或多行
					nTotlePagecount = nTotlePagecount + ntmpPageCount;
					break;
				}
			}
		}
	}
	else
	{
		char szAreaName[32];
		sprintf_s(szAreaName, sizeof(szAreaName), "Dynamic-%d", Screen_ja[(int)nScreenOrd]["Screen_lstDYArea"][(int)nDYAreaOrd]["DY_AreaID"].asUInt());
		szTWSendBuf = szTWSendBuf + MakeNULLArea(szAreaName
			, nRealW, nRealH, nRealX, nScreenColor, nScreenPixels, nScreenPixType, nScreenStyle
			, AREA_STUNT_DIRECTSHOW
			, AREA_STUNT_DIRECTSHOW
			, 1
			, 50
			, 1
			, 0
			, 0
			, 0
			, 0
			, 0
			, 0
			, 0);
		nTotlePagecount = nTotlePagecount + +1;
	}

	szSendBuf = szSendBuf + (char)(nTotlePagecount & 0xFF) + (char)((nTotlePagecount >> 8) & 0xFF) + szTWSendBuf;
	nDataLength = szSendBuf.size();

	Result = "";
	Result.push_back((char)(1));
	Result.push_back((char)(BYTE)0xA7);
	Result.push_back((char)(0));
	Result.push_back((char)(0));
	Result.push_back((char)(0));
	Result.push_back((char)(nDataLength & 0x00FF));
	Result.push_back((char)((nDataLength >> 8) & 0x00FF));
	Result.push_back((char)((nDataLength >> 16) & 0x00FF));
	Result.push_back((char)((nDataLength >> 24) & 0x00FF));
	Result += szSendBuf;

	nSendLength = Result.size();

	/*FreeAndNil(t_RVReportHelper);
	FreeAndNil(t_rvstyle);
	FreeAndNil(t_memo);*/
	return Result;
}

DWORD GetPageSize(DWORD nAllWidth, DWORD nHeight, DWORD nPx)
{
	switch (nPx)
	{
	case SCREEN_COLOR_SINGLE:
	case SCREEN_COLOR_DOUBLE: 
	case SCREEN_COLOR_THREE:
		return ((nAllWidth * nHeight) / 8) * nPx;
		break;
	case SCREEN_COLOR_FULLCOLOR:
		return (nAllWidth * nHeight) * 2;
	default:
		return 0;
	}
}

void GetRealDYAreaLocation(Json::Value DYArea_Obj, DWORD &nRealX, DWORD &nRealY, DWORD &nRealW, DWORD &nRealH)
{
	DWORD nFrame_Width;

	if (DYArea_Obj["DY_AreaFMode"].asUInt() == 0xFF)
	{
		nRealX = DYArea_Obj["DY_AreaX"].asUInt();
		nRealY = DYArea_Obj["DY_AreaY"].asUInt();
		nRealW = DYArea_Obj["DY_AreaWidth"].asUInt();
		nRealH = DYArea_Obj["DY_AreaHeight"].asUInt();
	}
	else
	{
		nFrame_Width = DYArea_Obj["DY_AreaFWidth"].asUInt();
		nRealX = DYArea_Obj["DY_AreaX"].asUInt() + nFrame_Width;
		nRealY = DYArea_Obj["DY_AreaY"].asUInt() + nFrame_Width;
		nRealW = DYArea_Obj["DY_AreaWidth"].asUInt() - nFrame_Width * 2;
		nRealH = DYArea_Obj["DY_AreaHeight"].asUInt() - nFrame_Width * 2;
		if (nRealW < 0)
			nRealW = 1;
		if (nRealH < 0)
			nRealH = 1;
	}
}

string MakeFrameValue(Json::Value Screen_Obj, DWORD nDYAreaOrd)
{
	DWORD nRealX, nRealY, nRealW, nRealH;
	BYTE nFrame_DispStype;
	string szSendBuf, szFrameData;
	HBITMAP bmp, bmp2;
	DWORD nIndex, n, nDataLength;
	BOOL bInvalidData;

	if (Screen_Obj["Screen_lstDYArea"][(int)nDYAreaOrd]["DY_AreaFMode"].asUInt() == 0xFF)
	{
		szSendBuf.clear();
		szSendBuf += (char)(0);
	}
	else
	{
		GetRealDYAreaLocation(Screen_Obj["Screen_lstDYArea"][(int)nDYAreaOrd], nRealX, nRealY, nRealW, nRealH);
		nFrame_DispStype = (BYTE)Screen_Obj["Screen_lstDYArea"][(int)nDYAreaOrd]["DY_AreaFStunt"].asUInt();

		if (nFrame_DispStype == 6) //因为在PC软件中屏蔽掉了“红绿交替转动”特技。因此当边框特技为6是设定为固定显示。
			nFrame_DispStype = 7;

		szSendBuf.clear();
		szSendBuf += (char)(1);
		szSendBuf += (char)(nFrame_DispStype);
		szSendBuf += (char)(Screen_Obj["Screen_lstDYArea"][(int)nDYAreaOrd]["DY_AreaFRunSpeed"].asUInt());
		szSendBuf += (char)(Screen_Obj["Screen_lstDYArea"][(int)nDYAreaOrd]["DY_AreaFMoveStep"].asUInt());
		szSendBuf += (char)(Screen_Obj["Screen_lstDYArea"][(int)nDYAreaOrd]["DY_AreaFWidth"].asUInt());
		szSendBuf += (char)(0);
		szSendBuf += (char)(0);

		HWND hDesktopWnd = GetDesktopWindow();
		HDC hDesktopDC = GetWindowDC(hDesktopWnd);
		HDC hMemoryDC = CreateCompatibleDC(hDesktopDC);
		HDC hMemoryDC2 = CreateCompatibleDC(hMemoryDC);
		BITMAPINFO bi;
		BYTE *pBmpBits = NULL;
		BYTE *pBmpBits2 = NULL;
		HBRUSH hBlackBrush = CreateSolidBrush(RGB(0, 0, 0));
		HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		RECT rect;
		RECT rect2;

		memset(&bi, 0, sizeof(BITMAPINFO));
		bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bi.bmiHeader.biWidth = PRO_FRAME_LENGTH;
		bi.bmiHeader.biHeight = Screen_Obj["Screen_lstDYArea"][(int)nDYAreaOrd]["DY_AreaFWidth"].asUInt();
		bi.bmiHeader.biBitCount = 24;
		bi.bmiHeader.biSizeImage = (bi.bmiHeader.biWidth * 3 + 1) / 2 * 2;
		bi.bmiHeader.biPlanes = 1;

		rect.left = 0;
		rect.top = 0;
		rect.right	 = bi.bmiHeader.biWidth;
		rect.bottom = bi.bmiHeader.biHeight;
		rect2.left = 0;
		rect2.top = 0;
		rect2.right	 = bi.bmiHeader.biWidth;
		rect2.bottom = bi.bmiHeader.biHeight;

		bmp = CreateDIBSection(hMemoryDC, &bi, DIB_RGB_COLORS, (void**)&pBmpBits, NULL, 0);
		bmp2 = NULL;
		SelectObject(hMemoryDC, bmp);
		FillRect(hMemoryDC, &rect, hBlackBrush);

		if (Screen_Obj["Screen_lstDYArea"][(int)nDYAreaOrd]["DY_AreaFMode"].asUInt() == 0) //单色
		{
			nIndex = Screen_Obj["Screen_lstDYArea"][(int)nDYAreaOrd]["DY_AreaFLine"].asUInt();

			if (g_aryProFrameSingleColorBmp.size() >= nIndex)
			{
				BITMAP bmp;
				bmp2 = LoadBitmap(GetModuleHandle(_T("LedDynamicArea.dll")), MAKEINTRESOURCE(g_aryProFrameSingleColorBmp[nIndex]));
				GetObject(bmp2, sizeof(BITMAP), &bmp);
				SelectObject(hMemoryDC2, bmp2);
				rect2.right = bmp.bmWidth;
				rect2.bottom = bmp.bmHeight;
				//if (g_aryProFrameSingleColorBmp[nIndex] != nil)
				//{
				//	bmp2.Width = g_aryProFrameSingleColorBmp[nIndex].Width;
				//	bmp2.Height = g_aryProFrameSingleColorBmp[nIndex].Height;
				//	bmp2.Canvas.CopyRect(Rect(0, 0, bmp2.Width, bmp2.Height), g_aryProFrameSingleColorBmp[nIndex].Canvas, Rect(0, 0, bmp2.Width, bmp2.Height));
				//}
				//else
				//{
				//	bmp2.Width = PRO_FRAME_LENGTH;
				//	bmp2.Height = Screen_Obj["Screen_lstDYArea"][(int)nDYAreaOrd]["DY_AreaFWidth"].asUInt();
				//	bmp2.Canvas.Brush.Color = clblack;
				//	bmp2.Canvas.FillRect(rect(0, 0, bmp2.Width, bmp2.Height));
				//	bmp2.Canvas.Pen.Width = 1;
				//	bmp2.Canvas.Pen.Color = clRed;
				//	for n = 0 to bmp2.Height - 1 do
				//	{
				//		bmp2.Canvas.MoveTo(0, n);
				//		bmp2.Canvas.LineTo(bmp2.Width div 2, n);
				//	}
				//}
			}
			else
			{
				//bmp2 = CreateDIBSection(hMemoryDC2, &bi, DIB_RGB_COLORS, (void**)&pBmpBits2, NULL, 0);
				HPEN hOldPen = (HPEN)SelectObject(hMemoryDC2, hRedPen);

				FillRect(hMemoryDC2, &rect2, hBlackBrush);

				for (n = 0; n < (DWORD)rect2.bottom; n++)
				{
					MoveToEx(hMemoryDC2, 0, n, NULL);
					LineTo(hMemoryDC2, rect2.right / 2, n);
				}

				SelectObject(hMemoryDC2, hOldPen);
				/*bmp2.Width = PRO_FRAME_LENGTH;
				bmp2.Height = Screen_Obj["Screen_lstDYArea"][(int)nDYAreaOrd]["DY_AreaFWidth"].asUInt();
				bmp2.Canvas.Brush.Color = clblack;
				bmp2.Canvas.FillRect(rect(0, 0, bmp2.Width, bmp2.Height));
				bmp2.Canvas.Pen.Width = 1;
				bmp2.Canvas.Pen.Color = clRed;
				for n = 0 to bmp2.Height - 1 do
				{
				bmp2.Canvas.MoveTo(0, n);
				bmp2.Canvas.LineTo(bmp2.Width div 2, n);
				}*/
			}
			//finally
			//}
			GetProgramFrameColorBmp(pBmpBits2, rect2.right, rect2.bottom
				, Screen_Obj["Screen_lstDYArea"][(int)nDYAreaOrd]["DY_AreaFColor"].asUInt());
		}
		else if (Screen_Obj["Screen_lstDYArea"][(int)nDYAreaOrd]["DY_AreaFMode"].asUInt() == 1) //花色
		{
			//try
			nIndex = Screen_Obj["Screen_lstDYArea"][(int)nDYAreaOrd]["DY_AreaFLine"].asUInt();
			if (g_aryProFrameMuliColorBmp.size() >= nIndex)
			{
				bmp2 = LoadBitmap(GetModuleHandle(_T("LedDynamicArea.dll")), MAKEINTRESOURCE(g_aryProFrameMuliColorBmp[nIndex]));

				/*if (g_aryProFrameMuliColorBmp[nIndex] != nil)
				{
				bmp2.Width = g_aryProFrameMuliColorBmp[nIndex].Width;
				bmp2.Height = g_aryProFrameMuliColorBmp[nIndex].Height;
				bmp2.Canvas.CopyRect(Rect(0, 0, bmp2.Width, bmp2.Height)
				, g_aryProFrameMuliColorBmp[nIndex].Canvas, Rect(0, 0, bmp2.Width, bmp2.Height));
				}
				else
				{
				bmp2.Width = PRO_FRAME_LENGTH;
				bmp2.Height = Screen_Obj["Screen_lstDYArea"][(int)nDYAreaOrd]["DY_AreaFWidth"].asUInt();
				bmp2.Canvas.Brush.Color = clblack;
				bmp2.Canvas.FillRect(rect(0, 0, bmp2.Width, bmp2.Height));
				bmp2.Canvas.Pen.Width = 1;
				bmp2.Canvas.Pen.Color = clRed;
				for n = 0 to bmp2.Height - 1 do
				{
				bmp2.Canvas.MoveTo(0, n);
				bmp2.Canvas.LineTo(bmp2.Width div 2, n);
				}
				}*/
			}
			else
			{
				HPEN hOldPen = (HPEN)SelectObject(hMemoryDC2, hRedPen);

				FillRect(hMemoryDC2, &rect, hBlackBrush);

				for (n = 0; n < (DWORD)bi.bmiHeader.biHeight; n++)
				{
					MoveToEx(hMemoryDC2, 0, n, NULL);
					LineTo(hMemoryDC2, bi.bmiHeader.biWidth / 2, n);
				}

				SelectObject(hMemoryDC2, hOldPen);

				/*bmp2.Width = PRO_FRAME_LENGTH;
				bmp2.Height = Screen_Obj["Screen_lstDYArea"][(int)nDYAreaOrd]["DY_AreaFWidth"].asUInt();
				bmp2.Canvas.Brush.Color = clblack;
				bmp2.Canvas.FillRect(rect(0, 0, bmp2.Width, bmp2.Height));
				bmp2.Canvas.Pen.Width = 1;
				bmp2.Canvas.Pen.Color = clRed;
				for n = 0 to bmp2.Height - 1 do
				{
				bmp2.Canvas.MoveTo(0, n);
				bmp2.Canvas.LineTo(bmp2.Width div 2, n);
				}*/
			}
			//finally
			//}
		}

		StretchBlt(hMemoryDC, 0, 0, bi.bmiHeader.biWidth, bi.bmiHeader.biHeight,
			hMemoryDC2, rect2.left, rect2.top, rect2.right, rect2.bottom, SRCCOPY);
		nDataLength = GetPageSize(PRO_FRAME_LENGTH, rect.bottom, Screen_Obj["Screen_color"].asUInt());
		TranCanvToInfo(pBmpBits, szFrameData
			, 0, bi.bmiHeader.biWidth, bi.bmiHeader.biHeight, Screen_Obj["Screen_color"].asUInt()
			, Screen_Obj["Screen_pixels"].asUInt(),
			Screen_Obj["Screen_nPixType"].asUInt()
			, Screen_Obj["Screen_nPixType"].asUInt(), bInvalidData);
		szSendBuf = szSendBuf + szFrameData;

		DeleteObject(hRedPen);
		DeleteObject(hBlackBrush);
		DeleteObject(bmp2);
		DeleteObject(bmp);
		DeleteDC(hMemoryDC2);
		DeleteDC(hMemoryDC);
		ReleaseDC(hDesktopWnd, hDesktopDC);
	}

	return szSendBuf;
}

void GetProgramFrameColorBmp(BYTE *pBits, DWORD nWidth, DWORD nHeight, DWORD nColorOrd)
{
	DWORD w, h;
	COLORREF nColor;
	BYTE *Col, ColR/*, ColG*/;
	size_t bytesPerLine = (nWidth * 3 + 1) / 2 * 2;

	nColor = nColorOrd;

	for (w = 0; w < nWidth; ++w)
		for (h = 0; h < nHeight; ++h)
		{
			Col = &pBits[h * bytesPerLine + w * 3];
			ColR = Col[0];
			if (ColR > 127)
			{
				Col[0] = GetRValue(nColor);
				Col[1] = GetGValue(nColor);
				Col[2] = GetBValue(nColor);
			}
		}
}

void TranCanvToInfo(LPBYTE Bmp, string &pInfoBuf,
					DWORD nLeft, DWORD nWidth, DWORD nHeight, DWORD nPx, DWORD nMkStyle, DWORD nPixType,
					DWORD nControllerType, BOOL &bInvalidData)
{
	BYTE *bitsRed, *bitsGreen, *bitsBlue;
	DWORD nDimensions;
	DWORD nIndex;
	DWORD iLeftBit, iRightBit;
	DWORD h, w;
	COLORREF Col;
	BYTE ColR, ColG, ColB;
	bool bRed, bGreen, bBlue;
	DWORD nAllWidth;
	DWORD byRed, byGreen, byBlue;
	DWORD I;
	bool btmpInvalidData;
	BYTE *p;
	int bytesPerLine = (nWidth * 3 + 1) / 2 * 2;

	bRed = false;
	bGreen = false;
	bBlue = false;
	btmpInvalidData = true;
	nIndex = 0;

	switch (nPx)
	{
	case SCREEN_COLOR_SINGLE:
	case SCREEN_COLOR_DOUBLE:
	case SCREEN_COLOR_THREE:
		iRightBit = 0;

		if (((nLeft + nWidth) % nPixType) != 0)
			iRightBit = nPixType - ((nLeft + nWidth) % nPixType); //右边起始字节的多余位数

		iLeftBit = nLeft % nPixType; //左边起始字节的多余位数
		nAllWidth = iLeftBit + nWidth + iRightBit;
		nDimensions = nAllWidth * nHeight;
		bitsRed = new BYTE[nDimensions];
		bitsGreen = new BYTE[nDimensions];
		bitsBlue = new BYTE[nDimensions];

		for (h = 0; h < nHeight; ++h)
		{
			for (w = 0; w < nAllWidth; ++w)
			{
				if ((w < iLeftBit) || (w >= (iLeftBit + nWidth)))
					Col = RGB(0, 0, 0);
				else
					Col = RGB(Bmp[bytesPerLine * (nHeight - h - 1) + (w - iLeftBit) * 3 + 2],
					Bmp[bytesPerLine * (nHeight - h - 1) + (w - iLeftBit) * 3 + 1],
					Bmp[bytesPerLine * (nHeight - h - 1) + (w - iLeftBit) * 3 + 0]);

				ColR = GetRValue(Col);
				ColG = GetGValue(Col);
				ColB = GetBValue(Col);

				if (nPx == SCREEN_COLOR_DOUBLE)
				{
					if (nMkStyle == DOUBLE_COLOR_PIXTYPE_1) //双基色，R+G
						bRed = ColR > 127;
					else //双基色，G+R
						bGreen = ColR > 127;

					if (bRed || bGreen)
						btmpInvalidData = false;
				}
				else if (nPx == SCREEN_COLOR_SINGLE)
				{
					bRed = ColR > 127;
					if (bRed)
						btmpInvalidData = false;
				}
				else if (nPx == SCREEN_COLOR_THREE)
				{
					bRed = ColR > 127;

					if (bRed)
						btmpInvalidData = false;
				}

				if (nPx == SCREEN_COLOR_DOUBLE)
				{
					if (nMkStyle == DOUBLE_COLOR_PIXTYPE_1) //双基色，R+G
						bGreen = ColG > 127;
					else //双基色，G+R
						bRed = ColG > 127;

					if (bRed || bGreen)
						btmpInvalidData = false;
				}
				else if (nPx == SCREEN_COLOR_SINGLE)
				{
					bGreen = ColG > 127;
					//单基色去绿色数据没有用处。因此不作判断
				}
				else if (nPx == SCREEN_COLOR_THREE)
				{
					bGreen = ColG > 127;
					if (bGreen)
						btmpInvalidData = false;
				}

				if (nPx == SCREEN_COLOR_THREE)
				{
					bBlue = ColB > 127;

					if (bBlue)
						btmpInvalidData = false;
				}

				bitsRed[nIndex] = bRed ? 0 : 1;
				bitsGreen[nIndex] = bGreen ? 0 : 1;
				bitsBlue[nIndex] = bBlue ? 0 : 1;
				++nIndex;
			}
		}

		if (nPx == SCREEN_COLOR_THREE)
		{
			for (I = 0; I < (nDimensions / 8); ++I)
			{
				byRed = (bitsRed[I * 8] << 7) + (bitsRed[I * 8 + 1] << 6) + (bitsRed[I * 8 + 2] << 5) + (bitsRed[I * 8 + 3] << 4)
					+ (bitsRed[I * 8 + 4] << 3) + (bitsRed[I * 8 + 5] << 2) + (bitsRed[I * 8 + 6] << 1) + (bitsRed[I * 8 + 7]);
				byGreen = (bitsGreen[I * 8] << 7) + (bitsGreen[I * 8 + 1] << 6) + (bitsGreen[I * 8 + 2] << 5) + (bitsGreen[I * 8 + 3] << 4)
					+ (bitsGreen[I * 8 + 4] << 3) + (bitsGreen[I * 8 + 5] << 2) + (bitsGreen[I * 8 + 6] << 1) + bitsGreen[I * 8 + 7];
				byBlue = (bitsBlue[I * 8] << 7) + (bitsBlue[I * 8 + 1] << 6) + (bitsBlue[I * 8 + 2] << 5) + (bitsBlue[I * 8 + 3] << 4)
					+ (bitsBlue[I * 8 + 4] << 3) + (bitsBlue[I * 8 + 5] << 2) + (bitsBlue[I * 8 + 6] << 1) + bitsBlue[I * 8 + 7];

				pInfoBuf += char(byRed);
				pInfoBuf += char(byGreen);
				pInfoBuf += char(byBlue);
			}
		}
		else if (nPx == SCREEN_COLOR_DOUBLE)
		{
			for (I = 0; I < (nDimensions / 8); ++I)
			{
				byRed = (bitsRed[I * 8] << 7) + (bitsRed[I * 8 + 1] << 6) + (bitsRed[I * 8 + 2] << 5) + (bitsRed[I * 8 + 3] << 4)
					+ (bitsRed[I * 8 + 4] << 3) + (bitsRed[I * 8 + 5] << 2) + (bitsRed[I * 8 + 6] << 1) + bitsRed[I * 8 + 7];
				byGreen = (bitsGreen[I * 8] << 7) + (bitsGreen[I * 8 + 1] << 6) + (bitsGreen[I * 8 + 2] << 5) + (bitsGreen[I * 8 + 3] << 4)
					+ (bitsGreen[I * 8 + 4] << 3) + (bitsGreen[I * 8 + 5] << 2) + (bitsGreen[I * 8 + 6] << 1) + bitsGreen[I * 8 + 7];

				pInfoBuf += char(byRed);
				pInfoBuf += char(byGreen);
			}
		}
		else if (nPx == SCREEN_COLOR_SINGLE)
		{
			for (I = 0; (I < nDimensions / 8); ++I)
			{
				byRed = (bitsRed[I * 8] << 7) + (bitsRed[I * 8 + 1] << 6) + (bitsRed[I * 8 + 2] << 5) + (bitsRed[I * 8 + 3] << 4)
					+ (bitsRed[I * 8 + 4] << 3) + (bitsRed[I * 8 + 5] << 2) + (bitsRed[I * 8 + 6] << 1) + bitsRed[I * 8 + 7];
				pInfoBuf += char(byRed);

			}
		}
		delete[] bitsRed;
		delete[] bitsGreen;
		delete[] bitsBlue;
		bInvalidData = btmpInvalidData;
		break;

	case SCREEN_COLOR_FULLCOLOR:
		nAllWidth = nWidth;
		nDimensions = nAllWidth * nHeight;

		for (h = 0; h < nHeight; ++h)
		{
			p = &Bmp[bytesPerLine * h];

			for (w = 0; w < nAllWidth; ++w)
			{
				BYTE highByte, lowByte;

				byRed = p[w * 3 + 2];
				byGreen = p[w * 3 + 1];
				byBlue = p[w * 3 + 0];

				highByte = (BYTE)(((byRed / 8) << 3) & 0xF8 + ((byGreen / 4) >> 3) & 0x7);
				lowByte = (BYTE)(((byGreen / 4) << 5) & 0xE0 + ((byBlue / 8) >> 3) & 0x1F);

				if ((highByte != 0) || (lowByte != 0))
					btmpInvalidData = false;
				//双字节参数值表示为R(5bits)+G(6bits)+B(5bits) 生成数据时，先低字节，然后高字节。

				pInfoBuf += (char)lowByte; //低字节
				pInfoBuf += (char)highByte; //高字节
			}
		}
		bInvalidData = btmpInvalidData;
		DoEvents();
		break;
	case SCREEN_COLOR_TWO_COLOR_GRAY:
		nAllWidth = nWidth;
		nDimensions = nAllWidth * nHeight;

		for (h = 0; h < nHeight; ++h)
		{
			p = &Bmp[bytesPerLine * h];

			for (w = 0; w < nAllWidth; ++w)
			{
				BYTE highByte, lowByte;

				byRed = p[w * 3 + 2];
				byGreen = p[w * 3 + 1];
				byBlue = p[w * 3 + 0];

				highByte = (BYTE)(((byRed / 8) << 3) & 0xF8 + ((byGreen / 4) >> 3) & 0x7);
				lowByte = (BYTE)(((byGreen / 4) << 5) & 0xE0 + ((byBlue / 8) >> 3) & 0x1F);

				if ((highByte != 0) || (lowByte != 0))
					btmpInvalidData = false;
				//双字节参数值表示为R(5bits)+G(6bits)+B(5bits) 生成数据时，先低字节，然后高字节。

				pInfoBuf += (char)highByte; //低字节
				pInfoBuf += (char)lowByte; //高字节
			}
		}

		bInvalidData = btmpInvalidData;
		DoEvents();
		break;
	}
}

string MakebmpTxt(DWORD thrd_ScreenWidth, DWORD thrd_ScreenHeight,
				  DWORD thrd_ScreenColor, DWORD thrd_ScreenPixels, DWORD thrd_ScreenPixType, DWORD thrd_ScreenStyle,
				  TRVStyle t_rvstyle, TTntMemo t_memo, TRVReportHelper t_RVReportHelper,
				  Json::Value AreaFile_Obj, DWORD nX, DWORD nY, DWORD nWidth, DWORD nHeight, DWORD &nFilePageCount) //打开图文区域的外部文件txt文件
{
	const char *filename = AreaFile_Obj["File_Name"].asCString();
	WCHAR wFileName[MAX_PATH];
	string result;

	MultiByteToWideChar(CP_ACP, 0, filename, strlen(filename), wFileName, MAX_PATH);
	nFilePageCount = 0;

	HANDLE hFile = CreateFile(wFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		size_t fileSize = GetFileSize(hFile, NULL);
		char *pFileContent = new char[fileSize + 1];

		if (pFileContent)
		{
			DWORD readLength;
			ReadFile(hFile, pFileContent, fileSize, &readLength, NULL);
			pFileContent[fileSize] = '\0';
			result = MakebmpText(thrd_ScreenWidth, thrd_ScreenHeight, thrd_ScreenColor, thrd_ScreenPixels,
				thrd_ScreenPixType, thrd_ScreenStyle, t_rvstyle, t_memo, t_RVReportHelper, AreaFile_Obj,
				nX, nY, nWidth, nHeight, nFilePageCount);
			delete [] pFileContent;
		}

		CloseHandle(hFile);
	}

	return result;
}

string&   replace_all_distinct(string&   str,const   string&   old_value,const   string&   new_value)     
{     
	for(string::size_type pos(0); pos != string::npos; pos += new_value.length())  
	{     
		if((pos=str.find(old_value,pos)) != string::npos)     
			str.replace(pos,old_value.length(),new_value);     
		else  
			break;
	}     
	return   str;     
}     

string MakebmpText(DWORD thrd_ScreenWidth, DWORD thrd_ScreenHeight, DWORD thrd_ScreenColor,
				   DWORD thrd_ScreenPixels, DWORD thrd_ScreenPixType, DWORD thrd_ScreenStyle, TRVStyle t_rvstyle,
				   TTntMemo t_memo, TRVReportHelper t_RVReportHelper, Json::Value AreaFile_Obj,
				   DWORD nX, DWORD nY, DWORD nWidth, DWORD nHeight, DWORD  &nFilePageCount)
{
	//fd                : TtntFileStream;
	string s, ansitxt;
	//unicodetxt        : widestring;
	DWORD nAlignment;
	BOOL nbold, nItalic, nUnderline, nStrikeout;
	string sztmpSendbuf;
	DWORD nRealityRunSpeed, nDefaultRunSpeed;
	string szFontName;
	DWORD nFontSize, nFontColor;
	DWORD ntmpFilePageCount, nRealPageCount;
	//tntmmostream      : TTNTMemoryStream;
	DWORD nDocHeight;

	nAlignment = 0;
	szFontName = AreaFile_Obj["File_FontName"].asString();
	if (AreaFile_Obj["File_Bold"] == 1)
		nbold = TRUE;
	else
		nbold = FALSE;
	nItalic = FALSE;
	nUnderline = FALSE;
	nStrikeout = FALSE;
	nFontSize = AreaFile_Obj["File_FontSize"].asUInt();
	nFontColor = AreaFile_Obj["File_FontColor"].asUInt();

	sztmpSendbuf = "";
	ansitxt = "";
	//unicodetxt = "";
	nRealPageCount = 0;

	LOGFONT logFont = { nFontSize, 0, 0, 0, nbold ? FW_BOLD : FW_DONTCARE, nItalic, nUnderline, nStrikeout, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, 0};

	MultiByteToWideChar(CP_ACP, 0, szFontName.c_str(), -1, logFont.lfFaceName, LF_FACESIZE);

	HFONT hFont = CreateFontIndirect(&logFont);

	s = AreaFile_Obj["File_Name"].asString();
	ansitxt = s;
	ntmpFilePageCount = 1;
	nDocHeight = nHeight;

	nRealityRunSpeed = GetControlStuntRealityRunSpeed(thrd_ScreenWidth, thrd_ScreenHeight, thrd_ScreenColor, AreaFile_Obj["File_Stunt"].asUInt(),
		AreaFile_Obj["File_Speed"].asUInt(), nDefaultRunSpeed);

	if (AreaFile_Obj["File_ShowStyle"].asUInt() == FILE_SHOWSTYLE_SINGLE)
	{
		sztmpSendbuf += MakeSingleLineTextImage(hFont, nFontColor, ansitxt, nWidth, nHeight, nX, thrd_ScreenColor, thrd_ScreenPixels,
			thrd_ScreenPixType, thrd_ScreenStyle, AreaFile_Obj["File_Stunt"].asUInt(), AreaFile_Obj["File_OutsStunt"].asUInt(), nRealityRunSpeed,
			AreaFile_Obj["File_Showtime"].asUInt() * AREA_SHOWTIME_BASIC, AreaFile_Obj["File_ShowCount"].asUInt()
			, AreaFile_Obj["File_Reserved1"].asUInt()
			, AreaFile_Obj["File_Reserved2"].asUInt()
			, AreaFile_Obj["File_Reserved3"].asUInt()
			, AreaFile_Obj["File_Reserved4"].asUInt()
			, AreaFile_Obj["File_Reserved5"].asUInt()
			, AreaFile_Obj["File_Reserved6"].asUInt(),
			nRealPageCount);
	}
	else
	{
		sztmpSendbuf += MakeDoubleImage(hFont, nFontColor, ansitxt, ntmpFilePageCount, nWidth, nHeight, nX, thrd_ScreenColor, thrd_ScreenPixels,
			thrd_ScreenPixType, thrd_ScreenStyle
			, AreaFile_Obj["File_Stunt"].asUInt()
			, AreaFile_Obj["File_OutsStunt"].asUInt()
			, nRealityRunSpeed
			, AreaFile_Obj["File_Showtime"].asUInt() * AREA_SHOWTIME_BASIC
			, AreaFile_Obj["File_ShowCount"].asUInt()
			, AreaFile_Obj["File_Reserved1"].asUInt()
			, AreaFile_Obj["File_Reserved2"].asUInt()
			, AreaFile_Obj["File_Reserved3"].asUInt()
			, AreaFile_Obj["File_Reserved4"].asUInt()
			, AreaFile_Obj["File_Reserved5"].asUInt()
			, AreaFile_Obj["File_Reserved6"].asUInt()
			, AreaFile_Obj["File_Reserved7"].asUInt()
			, FALSE, nRealPageCount);
	}

	DeleteObject(hFont);

	nFilePageCount = nRealPageCount;
	return sztmpSendbuf;
}

string MakeSingleLineTextImage(HFONT hFont, COLORREF fontColor, const string &str, DWORD w, DWORD h, DWORD x, DWORD nPx, DWORD nMkStyle, DWORD nKardPixType, DWORD nScreenStyle,
							   DWORD nStunt, DWORD nOutStunt, DWORD nRunSpeed, DWORD nShowTime, DWORD nShowCount,
							   DWORD nReserved1, DWORD nReserved2, DWORD nReserved3, DWORD nReserved4, DWORD nReserved5, DWORD nReserved6, DWORD &nRealPageCount)
{
	string result = "";
	HWND hDesktopWnd = GetDesktopWindow();
	HDC hDesktopDC = GetWindowDC(hDesktopWnd);
	HFONT hOldDesktopFont = (HFONT)SelectObject(hDesktopDC, hFont);
	int strLength = str.size() + 1;
	WCHAR *wszStr = new WCHAR[strLength];
	RECT rect = { 0, 0, w, h};

	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wszStr, strLength);
	DrawText(hDesktopDC, wszStr, -1, &rect, DT_SINGLELINE | DT_CALCRECT);

	HDC hAreaDC = CreateCompatibleDC(hDesktopDC);
	BITMAPINFO areaBmpInfo;

	memset(&areaBmpInfo, 0, sizeof(areaBmpInfo));
	areaBmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	areaBmpInfo.bmiHeader.biWidth = (rect.right + w - 1) / w * w;
	areaBmpInfo.bmiHeader.biHeight = h;
	areaBmpInfo.bmiHeader.biBitCount = 24;
	areaBmpInfo.bmiHeader.biSizeImage = (areaBmpInfo.bmiHeader.biWidth  * 3 + 1) / 2 * 2 * h;
	areaBmpInfo.bmiHeader.biPlanes = 1;

	BYTE *pAreaBmpBits = NULL;
	HBITMAP hAreaBmp = CreateDIBSection(hAreaDC, &areaBmpInfo, DIB_RGB_COLORS, (void**)&pAreaBmpBits, NULL, 0);
	HBRUSH bBlackBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBITMAP hOldAreaBmp = (HBITMAP)SelectObject(hAreaDC, hAreaBmp);

	rect.right = areaBmpInfo.bmiHeader.biWidth;
	rect.bottom = areaBmpInfo.bmiHeader.biHeight;
	FillRect(hAreaDC, &rect, bBlackBrush);
	SetTextColor(hAreaDC, fontColor);
	SetBkColor(hAreaDC, RGB(0, 0, 0));

	HFONT hOldAreaFont = (HFONT)SelectObject(hAreaDC, hFont);

	DrawText(hAreaDC, wszStr, -1, &rect, DT_SINGLELINE);

	SelectObject(hAreaDC, hOldAreaFont);

	int pageCount = (rect.right + w - 1) / w;
	HDC hPageDC = CreateCompatibleDC(hDesktopDC);
	BITMAPINFO pageBmpInfo;

	memset(&pageBmpInfo, 0, sizeof(pageBmpInfo));
	pageBmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pageBmpInfo.bmiHeader.biWidth = w;
	pageBmpInfo.bmiHeader.biHeight = h;
	pageBmpInfo.bmiHeader.biBitCount = 24;
	pageBmpInfo.bmiHeader.biSizeImage = (pageBmpInfo.bmiHeader.biWidth  * 3 + 1) / 2 * 2 * h;
	pageBmpInfo.bmiHeader.biPlanes = 1;

	BYTE *pPageBmpBits = NULL;
	HBITMAP hPageBmp = CreateDIBSection(hPageDC, &pageBmpInfo, DIB_RGB_COLORS, (void**)&pPageBmpBits, NULL, 0);
	HBITMAP hOldPageBmp = (HBITMAP)SelectObject(hPageDC, hPageBmp);

	string pageParams;

	pageParams += (char)0;
	pageParams += (char)nStunt;
	pageParams += (char)nOutStunt;
	pageParams += (char)nRunSpeed;
	pageParams += (char)(nShowTime & 0xff);
	pageParams += (char)((nShowTime >> 8) & 0xff);
	pageParams += (char)(nShowCount);
	pageParams += (char)nReserved1;
	pageParams += (char)nReserved2;
	pageParams += (char)nReserved3;
	pageParams += (char)nReserved4;
	pageParams += (char)nReserved5;
	pageParams += (char)nReserved6;

	nRealPageCount = (DWORD)pageCount;

	for	(int i = 0; i < pageCount; ++i)
	{
		if ((nStunt == STUNT_MOVE_RIGHT) || (nStunt == STUNT_CONTINUOUS_MOVE_RIGHT))
			BitBlt(hPageDC, 0, 0, w, h, hAreaDC, (pageCount - i - 1) * w, 0, SRCCOPY);
		else
			BitBlt(hPageDC, 0, 0, w, h, hAreaDC, i * w, 0, SRCCOPY);

		string curPage;
		BOOL bInvalidData;

		TranCanvToInfo(pPageBmpBits, curPage, x, w, h, nPx, nMkStyle, nKardPixType, nScreenStyle, bInvalidData);

		DWORD curPageLength = pageParams.size() + curPage.size();

		result += (char)(curPageLength & 0xff);
		result += (char)((curPageLength >> 8) & 0xff);
		result += (char)((curPageLength >> 16) & 0xff);
		result += (char)((curPageLength >> 24) & 0xff);
		result += pageParams;
		result += curPage;
	}

	SelectObject(hPageDC, hOldPageBmp);
	DeleteObject(hPageBmp);
	DeleteDC(hPageDC);

	SelectObject(hAreaDC, hOldAreaBmp);
	DeleteObject(bBlackBrush);
	DeleteObject(hAreaBmp);
	DeleteDC(hAreaDC);
	delete [] wszStr;
	SelectObject(hDesktopDC, hOldDesktopFont);
	ReleaseDC(hDesktopWnd, hDesktopDC);

	return result;
}

string MakeDoubleImage(HFONT hFont, COLORREF fontColor, const string &str, DWORD count, DWORD w, DWORD h, DWORD x, DWORD nPx, DWORD nMkStyle, DWORD nKardPixType, DWORD nScreenStyle,
					   DWORD nStunt, DWORD nOutStunt, DWORD nRunSpeed, DWORD nShowTime, DWORD nShowCount, DWORD nReserved1
					   , DWORD nReserved2, DWORD nReserved3, DWORD nReserved4, DWORD nReserved5, DWORD nReserved6
					   , DWORD nReserved7, bool bOnePage, DWORD &nRealPageCount)
{
	string result;
	HWND hDesktopWnd = GetDesktopWindow();
	HDC hDesktopDC = GetWindowDC(hDesktopWnd);
	HFONT hOldDesktopFont = (HFONT)SelectObject(hDesktopDC, hFont);
	int strLength = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	WCHAR *wszStr = new WCHAR[strLength];
	RECT areaRect = { 0, 0, w, h };

	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wszStr, strLength);

	DrawText(hDesktopDC, wszStr, -1, &areaRect, DT_WORDBREAK | DT_CALCRECT);

	HDC hAreaDC = CreateCompatibleDC(hDesktopDC);

	BITMAPINFO areaBmpInfo;
	memset(&areaBmpInfo, 0, sizeof(areaBmpInfo));
	areaBmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	areaBmpInfo.bmiHeader.biWidth = areaRect.right;
	areaBmpInfo.bmiHeader.biHeight = areaRect.bottom;
	areaBmpInfo.bmiHeader.biBitCount = 24;
	areaBmpInfo.bmiHeader.biSizeImage = (areaRect.right * 3 + 1) / 2 * 2 * areaRect.bottom;
	areaBmpInfo.bmiHeader.biPlanes = 1;

	BYTE *pAreaBmpBits = NULL;
	HBITMAP hAreaBmp = CreateDIBSection(hAreaDC, &areaBmpInfo, DIB_RGB_COLORS, (void**)&pAreaBmpBits, NULL, 0);
	HBRUSH hBlackBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBITMAP hOldAreaBitmap = (HBITMAP)SelectObject(hAreaDC, hAreaBmp);
	HFONT hOldAreaFont = (HFONT)SelectObject(hAreaDC, hFont);

	FillRect(hAreaDC, &areaRect, hBlackBrush);
	SetTextColor(hAreaDC, fontColor);
	SetBkColor(hAreaDC, RGB(0, 0, 0));

	DrawText(hAreaDC, wszStr, -1, &areaRect, DT_WORDBREAK);

	TEXTMETRIC tm;
	GetTextMetrics(hAreaDC, &tm);

	int maxPageHeight = h / tm.tmHeight * tm.tmHeight;

	HDC hPageDC = CreateCompatibleDC(hAreaDC);

	BITMAPINFO pageBmpInfo;
	memset(&pageBmpInfo, 0, sizeof(pageBmpInfo));
	pageBmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pageBmpInfo.bmiHeader.biWidth = w;
	pageBmpInfo.bmiHeader.biHeight = h;
	pageBmpInfo.bmiHeader.biBitCount = 24;
	pageBmpInfo.bmiHeader.biSizeImage = (w * 3 + 1) / 2 * 2 * h;
	pageBmpInfo.bmiHeader.biPlanes = 1;

	BYTE *pPageBmpBits = NULL;
	HBITMAP hPageBmp = CreateDIBSection(hPageDC, &pageBmpInfo, DIB_RGB_COLORS, (void**)&pPageBmpBits, NULL, 0);
	HBITMAP hOldPageBmp = (HBITMAP)SelectObject(hPageDC, hPageBmp);

	int pageCount = areaRect.bottom / maxPageHeight + ((areaRect.bottom % maxPageHeight != 0) ? 1 : 0);

	string pageParams;

	pageParams += (char)0;
	pageParams += (char)nStunt;
	pageParams += (char)nOutStunt;
	pageParams += (char)nRunSpeed;
	pageParams += (char)(nShowTime & 0xff);
	pageParams += (char)((nShowTime >> 8) & 0xff);
	pageParams += (char)(nShowCount);
	pageParams += (char)nReserved1;
	pageParams += (char)nReserved2;
	pageParams += (char)nReserved3;
	pageParams += (char)nReserved4;
	pageParams += (char)nReserved5;
	pageParams += (char)nReserved6;

	nRealPageCount = (DWORD)pageCount;

	for (int i = 0; i < pageCount; ++i)
	{
		int actualPageHeight = maxPageHeight;
		bool isLastPage = false;

		if ((nStunt == STUNT_MOVE_UP) || (nStunt == STUNT_CONTINUOUS_MOVE_UP))
			isLastPage = (i == 0);
		else
			isLastPage = (i == (pageCount - 1));

		if (isLastPage)
			actualPageHeight = areaRect.bottom - i * maxPageHeight;

		RECT pageRect = { 0, 0, w, h };

		FillRect(hPageDC, &pageRect, hBlackBrush);

		if ((nStunt == STUNT_MOVE_DOWN) || (nStunt == STUNT_CONTINUOUS_MOVE_DOWN))
			BitBlt(hPageDC, 0, 0, w, actualPageHeight, hAreaDC, 0, (pageCount - i - 1) * maxPageHeight, SRCCOPY);
		else
			BitBlt(hPageDC, 0, 0, w, actualPageHeight, hAreaDC, 0, i * maxPageHeight, SRCCOPY);

		string curPage;
		BOOL bInvalidData;

		TranCanvToInfo(pPageBmpBits, curPage, x, w, h, nPx, nMkStyle, nKardPixType, nScreenStyle, bInvalidData);

		DWORD curPageLength = pageParams.size() + curPage.size();

		result += (char)(curPageLength & 0xff);
		result += (char)((curPageLength >> 8) & 0xff);
		result += (char)((curPageLength >> 16) & 0xff);
		result += (char)((curPageLength >> 24) & 0xff);
		result += pageParams;
		result += curPage;
	}

	SelectObject(hPageDC, hOldPageBmp);
	DeleteObject(hPageBmp);
	DeleteDC(hPageDC);

	SelectObject(hAreaDC, hOldAreaFont);
	SelectObject(hAreaDC, hOldAreaBitmap);
	DeleteObject(hBlackBrush);
	DeleteObject(hAreaBmp);
	DeleteDC(hAreaDC);
	SelectObject(hDesktopDC, hOldDesktopFont);
	delete [] wszStr;
	ReleaseDC(hDesktopWnd, hDesktopDC);

	return result;
}
