#include "stdafx.h"
#include "MyDataType.h"
#include "TranInfo.h"

//extern Json::Value devicelist_ja;
//extern SYSTEMTIME StringToDatetime(string &DateStr);

//string GetPowerONOFF(BYTE nPowerStatus, DWORD nProtocolVer, BYTE nRtnReq) //ǿ�ƿ��ػ�������Ϣ
//{
//	string Result;
//	
//	Result.push_back((char)(0xA2));
//	Result.push_back((char)(05));
//	Result.push_back((char)(1));
//	Result.push_back((char)(0));
//	Result.push_back((char)(nPowerStatus));
//	if (nProtocolVer == PROTOCOLVER_FIFTH_CONTROL)
//		Result = (char)(nRtnReq) + Result;
//	return Result;
//}

//string GetTimerONOFFInfo(Json::Value Screen_ja, DWORD nScreenOrd, DWORD nProtocolVer, BYTE nRtnReq) //��ʱ���ػ���Ϣ
//{ 
//	//��Ļ�ṹ
//	string szSendBuf;
//	DWORD nDataLength;
//	BYTE nTimerArrayCount;
//	string szTime;
//	SYSTEMTIME dtTimeON, dtTimeOFF;
//	fstream fp;
//
//	szSendBuf += (char)(0xA2);
//	szSendBuf += (char)(06); 
//	szSendBuf += (char)(0); 
//	szSendBuf += (char)(0);
//	szSendBuf += (char)(0);
//
//	nDataLength= 1;
//	if (devicelist_ja[(int)nScreenOrd]["Screen_PowertimeEnabled"].asBool())
//	{
//		if (Screen_ja[(int)nScreenOrd]["Screen_Powertime1use"].asBool())
//		{
//			szTime = Screen_ja[(int)nScreenOrd]["Screen_Powertime1on"].asString();
//			dtTimeON= StringToDatetime(szTime);
//			szTime = Screen_ja[(int)nScreenOrd]["Screen_Powertime1off"].asString();
//			dtTimeOFF= StringToDatetime(szTime);
//
//			if ((dtTimeON.wYear != dtTimeOFF.wYear) ||
//				(dtTimeON.wMonth != dtTimeOFF.wMonth) ||
//				(dtTimeON.wDay != dtTimeOFF.wDay) ||
//				(dtTimeON.wHour != dtTimeOFF.wHour) ||
//				(dtTimeON.wMinute != dtTimeOFF.wMinute) ||
//				(dtTimeON.wSecond != dtTimeOFF.wSecond))
//			{
//				++nTimerArrayCount;
//				nDataLength= nDataLength + 4;
//				szSendBuf= szSendBuf + (char)(StrToInt("0x" + IntToStr(Hourof(dtTimeON)))) + (char)(StrToInt("0x" + IntToStr(MinuteOf(dtTimeON))));
//if (Hourof(dtTimeOFF) = 23) and (MinuteOf(dtTimeOFF) = 59) 
//szSendBuf = szSendBuf + (char)(StrToInt("0x" + IntToStr(24))) + (char)(StrToInt("0x" + IntToStr(00)))
//else
//szSendBuf = szSendBuf + (char)(StrToInt("0x" + IntToStr(Hourof(dtTimeOFF)))) + (char)(StrToInt("0x" + IntToStr(MinuteOf(dtTimeOFF))));
//}
//}
//if Screen_ja[(int)nScreenOrd].B["Screen_Powertime2use"] = True 
//{
//szTime = Screen_ja[(int)nScreenOrd].S["Screen_Powertime2on"];
//dtTimeON= StrToTime(szTime);
//szTime= Screen_ja[(int)nScreenOrd].S["Screen_Powertime2off"];
//dtTimeOFF= StrToTime(szTime);
//if dtTimeON != dtTimeOFF 
//{
//Inc(nTimerArrayCount);
//nDataLength= nDataLength + 4;
//szSendBuf= szSendBuf + (char)(StrToInt("0x" + IntToStr(Hourof(dtTimeON)))) + (char)(StrToInt("0x" + IntToStr(MinuteOf(dtTimeON))));
//if (Hourof(dtTimeOFF) = 23) and (MinuteOf(dtTimeOFF) = 59) 
//szSendBuf = szSendBuf + (char)(StrToInt("0x" + IntToStr(24))) + (char)(StrToInt("0x" + IntToStr(00)))
//else
//szSendBuf = szSendBuf + (char)(StrToInt("0x" + IntToStr(Hourof(dtTimeOFF)))) + (char)(StrToInt("0x" + IntToStr(MinuteOf(dtTimeOFF))));
//}
//}
//if Screen_ja[(int)nScreenOrd].B["Screen_Powertime3use"] = True 
//{
//szTime = Screen_ja[(int)nScreenOrd].S["Screen_Powertime3on"];
//dtTimeON= StrToTime(szTime);
//szTime= Screen_ja[(int)nScreenOrd].S["Screen_Powertime3off"];
//dtTimeOFF= StrToTime(szTime);
//if dtTimeON != dtTimeOFF 
//{
//Inc(nTimerArrayCount);
//nDataLength= nDataLength + 4;
//szSendBuf= szSendBuf + (char)(StrToInt("0x" + IntToStr(Hourof(dtTimeON)))) + (char)(StrToInt("0x" + IntToStr(MinuteOf(dtTimeON))));
//if (Hourof(dtTimeOFF) = 23) and (MinuteOf(dtTimeOFF) = 59) 
//szSendBuf = szSendBuf + (char)(StrToInt("0x" + IntToStr(24))) + (char)(StrToInt("0x" + IntToStr(00)))
//else
//szSendBuf = szSendBuf + (char)(StrToInt("0x" + IntToStr(Hourof(dtTimeOFF)))) + (char)(StrToInt("0x" + IntToStr(MinuteOf(dtTimeOFF))));
//}
//}
//if nTimerArrayCount = 0  //û�ж�ʱ������Ϣʱ����ȡ����ʱ������Ϣ
//{
//szSendBuf = GetUnTimerONOFFInfo(nProtocolVer, nRtnReq);
//end
//else
//{
//szSendBuf[3] = (char)(nDataLength and 0xFF);
//szSendBuf[4] = (char)((nDataLength shr 8) and 0xFF);
//szSendBuf[5] = (char)(nTimerArrayCount);
//}
//Result= szSendBuf;
//if nTimerArrayCount != 0 
//{
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//Result = (char)(nRtnReq) + Result;
//}
//end
//else
//{
//szSendBuf = GetUnTimerONOFFInfo(nProtocolVer, nRtnReq);
//Result= szSendBuf;
//}
//{0xIFDEF DEBUG}
//try
//AssignFile(fp, "c:\" + "TimerONOFF");
//	Rewrite(fp, 1);
//BlockWrite(fp, szSendBuf[1], Length(szSendBuf));
//finally
//CloseFile(fp);
//}
//{0xENDIF}
//
//}

//function GetUnTimerONOFFInfo(nProtocolVer: Cardinal; nRtnReq: Byte) : string;
//{
//Result = (char)(0xA2) + (char)(08) + (char)(0) + (char)(0);
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//Result = (char)(nRtnReq) + Result;
//}

//procedure Bublerank(var a : array of string; var b : array of Cardinal; maxtomin: boolean);
//var
//i, j              : integer;
//str: string;
//n: Cardinal;
//{
//if maxtomin  //�ɴ�У����
//{
//for i = low(a) to high(a) - 1 do
//for j = low(a) to high(a) - i - 1 do // �������
//if StrToTime(a[j]) < StrToTime(a[j + 1]) 
//	{
//	str = a[j];
//a[j] = a[j + 1];
//a[j + 1] = str;
//
//n= b[j];
//b[j] = b[j + 1];
//b[j + 1] = n;
//}
//end //end if
//else //��С��������
//{
//for i = low(a) to high(a) - 1 do
//for j = low(a) to high(a) - i - 1 do // �������
//if StrToTime(a[j]) > StrToTime(a[j + 1]) 
//{
//str = a[j];
//a[j] = a[j + 1];
//a[j + 1] = str;
//
//n= b[j];
//b[j] = b[j + 1];
//b[j + 1] = n;
//}
//} //end else
//}
//
//function GetAdjustLightInfo(Screen_ja: TSuperArray; nScreenOrd: Cardinal; nProtocolVer: Cardinal; nRtnReq: Byte) : string; //������Ϣ
//var
//szSendBuf : string;
//aryStr: array of string;
//aryInt: array of Cardinal;
//szcurStr: string;
//ncurInt: Cardinal;
//dtcurTime, dtcuraryItem, dtMinaryItem: TTime;
//ncuraryItem, nMaxaryItem: Cardinal;
//n, ncurAryOrd     : Cardinal;
//v: tstringlist;
//szcurTime: string;
//fp: file;
//{
//szSendBuf = (char)(0xA2) + (char)(07) + (char)(49) + (char)(0) + (char)(Screen_ja[(int)nScreenOrd].I["Screen_AdjustLightMode"]);
//SetLength(szSendBuf, 53);
//if Screen_ja[(int)nScreenOrd].I["Screen_AdjustLightMode"] = 1 
//{
//SetLength(aryStr, 0);
//SetLength(aryInt, 0);
//if Screen_ja[(int)nScreenOrd].B["Screen_LightTime1Use"] = True 
//{
//SetLength(aryStr, Length(aryStr) + 1);
//SetLength(aryInt, Length(aryInt) + 1);
//aryStr[Length(aryStr) - 1] = Screen_ja[(int)nScreenOrd].S["Screen_LightTime1"];
//aryInt[Length(aryInt) - 1] = Screen_ja[(int)nScreenOrd].I["Screen_LightValue1"];
//}
//if Screen_ja[(int)nScreenOrd].B["Screen_LightTime2Use"] = True 
//{
//SetLength(aryStr, Length(aryStr) + 1);
//SetLength(aryInt, Length(aryInt) + 1);
//aryStr[Length(aryStr) - 1] = Screen_ja[(int)nScreenOrd].S["Screen_LightTime2"];
//aryInt[Length(aryInt) - 1] = Screen_ja[(int)nScreenOrd].I["Screen_LightValue2"];
//}
//if Screen_ja[(int)nScreenOrd].B["Screen_LightTime3Use"] = True 
//{
//SetLength(aryStr, Length(aryStr) + 1);
//SetLength(aryInt, Length(aryInt) + 1);
//aryStr[Length(aryStr) - 1] = Screen_ja[(int)nScreenOrd].S["Screen_LightTime3"];
//aryInt[Length(aryInt) - 1] = Screen_ja[(int)nScreenOrd].I["Screen_LightValue3"];
//}
//if Screen_ja[(int)nScreenOrd].B["Screen_LightTime4Use"] = True 
//{
//SetLength(aryStr, Length(aryStr) + 1);
//SetLength(aryInt, Length(aryInt) + 1);
//aryStr[Length(aryStr) - 1] = Screen_ja[(int)nScreenOrd].S["Screen_LightTime4"];
//aryInt[Length(aryInt) - 1] = Screen_ja[(int)nScreenOrd].I["Screen_LightValue4"];
//}
//if Length(aryStr) > 0 
//{
//Bublerank(aryStr, aryInt, True);
//dtcurTime= EncodeTime(23, 30, 0, 0);
//n= 53;
//ncurAryOrd= 0;
//v= TStringList.Create; //��ȡ�����ʱ�������ֵ��
//v= SplitString(aryStr[0], ":");
//ncuraryItem= aryInt[0];
//dtcuraryItem= EncodeTime(StrToInt(v[0]), StrToInt(v[1]), 0, 0);
//v.Free;
//
//nMaxaryItem= ncuraryItem; //������Сʱ�䷶Χ֮ǰ������
//v= TStringList.Create;
//v= SplitString(aryStr[0], ":");
//dtcuraryItem= EncodeTime(StrToInt(v[0]), StrToInt(v[1]), 0, 0); // �õ���Сʱ��ֵ��
//v.Free;
//
//v= TStringList.Create;
//v= SplitString(aryStr[Length(aryStr) - 1], ":");
//dtMinaryItem= EncodeTime(StrToInt(v[0]), StrToInt(v[1]), 0, 0); // �õ���Сʱ��ֵ��
//v.Free;
//
//while FormatDateTime("HH:nn", dtcurTime) != FormatDateTime("HH:nn", dtMinaryItem) do //����ʱ��23:30������С�ıȽϣ�
//{
//if FormatDateTime("HH:nn", dtcurTime) != FormatDateTime("HH:nn", dtcuraryItem)  //��ǰʱ���뵱ǰ����ʱ��ֵ��һ��ʱ
//{
//szcurTime = FormatDateTime("HH:nn", dtcurTime);
//dtcurTime= dtcurTime - EncodeTime(0, 30, 0, 0);
//szSendBuf[n] = (char)(ncuraryItem);
//Dec(n);
//end
//else
//{ //��ǰʱ���뵱ǰ����ʱ��ֵһ��ʱ,��ȡֵ��ȥ��һ��������
//szcurTime = FormatDateTime("HH:nn", dtcurTime);
//dtcurTime= dtcurTime - EncodeTime(0, 30, 0, 0);
//szSendBuf[n] = (char)(ncuraryItem);
//Dec(n);
//if ncurAryOrd < Length(aryStr) - 1 
//	{
//	Inc(ncurAryOrd);
//v= TStringList.Create;
//v= SplitString(aryStr[ncurAryOrd], ":");
//ncuraryItem= aryInt[ncurAryOrd];
//szcurTime= FormatDateTime("HH:nn", dtcuraryItem);
//dtcuraryItem= EncodeTime(StrToInt(v[0]), StrToInt(v[1]), 0, 0);
//v.Free;
//}
//}
//}
//szSendBuf[n] = (char)(ncuraryItem);
//Dec(n);
//if FormatDateTime("HH:nn", dtcurTime) != FormatDateTime("HH:nn", EncodeTime(0, 0, 0, 0))  //����С����ֵΪ00:00�ų����⡣
//{
////dtcurTime := dtcurTime - EncodeTime(0, 30, 0, 0);
//repeat
//{
//szcurTime = FormatDateTime("HH:nn", dtcurTime);
//dtcurTime= dtcurTime - EncodeTime(0, 30, 0, 0);
//szSendBuf[n] = (char)(nMaxaryItem);
//Dec(n);
//}
//until FormatDateTime("HH:nn", dtcurTime) = FormatDateTime("HH:nn", EncodeTime(0, 0, 0, 0));
//}
//end
//else
//{
//for n = 1 to 48 do
//szSendBuf[5 + n] = (char)(15);
//}
//end
//else
//{
//for n = 1 to 48 do
//szSendBuf[5 + n] = (char)(Screen_ja[(int)nScreenOrd].I["Screen_Light"]);
//}
//Result= szSendBuf;
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//Result = (char)(nRtnReq) + Result;
//{0xIFDEF DEBUG}
//try
//AssignFile(fp, "AdjustLight");
//Rewrite(fp, 1);
//BlockWrite(fp, szSendBuf[1], Length(szSendBuf));
//finally
//CloseFile(fp);
//}
//{0xENDIF}
//}

//function GetPingCommandInfo(nProtocolVer: Cardinal; nRtnReq: Byte) : string; //Ping���
//{
//Result = (char)(0xA2) + (char)(0) + (char)(0) + (char)(0);
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//Result = (char)(nRtnReq) + Result;
//}
//
//function GetSystemResetInfo(nProtocolVer: Cardinal; nRtnReq: Byte) : string; //ϵͳ��λ����
//{
//Result = (char)(0xA2) + (char)(01) + (char)(0) + (char)(0);
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//Result = (char)(nRtnReq) + Result;
//}
//
//function GetFormatInfo(nProtocolVer: Cardinal; nRtnReq: Byte) : string; //��ʽ������
//{
//Result = (char)(0xA1) + (char)(00) + (char)(0) + (char)(0);
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//Result = (char)(nRtnReq) + Result;
//}
//
//function GetDeleteAllProgram(nProtocolVer: Cardinal; nRtnReq: Byte) : string;
//{
//Result = (char)(0xA1) + (char)(01) + (char)(2) + (char)(0) + (char)(0) + (char)(0);
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//Result = (char)(nRtnReq) + Result;
//}
//
//function GetStartFileFlagInfo(nProtocolVer: Cardinal; nRtnReq: Byte) : string; //���Ͷ��Ŀ��ʼ��־��Ϣ��
//{
//Result = (char)(0xA1) + (char)(08) + (char)(0) + (char)(0);
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//Result = (char)(nRtnReq) + Result;
//}
//
//function GetEndFileFlagInfo(nProtocolVer: Cardinal; nRtnReq: Byte) : string;
//{
//Result = (char)(0xA1) + (char)(09) + (char)(0) + (char)(0);
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//Result = (char)(nRtnReq) + Result;
//}
//
//function GetMemoryVolume(nProtocolVer: Cardinal; nRtnReq: Byte) : string;
//{
//Result = (char)(0xA1) + (char)(0x12) + (char)(0) + (char)(0);
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//Result = (char)(nRtnReq) + Result;
//}
//
//function GetDeleteProgramFile(var SendProgramList : TList; var QueryProgramList : TList;
//var nDeleteCount : Cardinal; var nDeleteSectors : Cardinal; var nValidProgramSectors : Cardinal;
//nProtocolVer: Cardinal; nRtnReq: Byte) : string; //�õ���ǰ
//var
//I, J              : Cardinal;
//ptmptagReadDir: PtagReadDir;
//ptmptagSendInfo: PtagSendInfo;
//szDeleteFileDir: string;
//nLength: Cardinal;
//ncurProDeleteSectors, ntmpDeleteSectors: Cardinal;
//{
//ntmpDeleteSectors = 0;
//for I = 1 to QueryProgramList.Count do
//{
//ptmptagReadDir = QueryProgramList.Items[I - 1];
//for J = 1 to SendProgramList.Count do
//{
//ptmptagSendInfo = SendProgramList.Items[J - 1];
//if ptmptagReadDir.szQueryFile = ptmptagSendInfo.szSendFile 
//{
////�������ļ���Ҫ���͵��ļ�һ�£�����У��һ��ʱ������Ҫ�·�ɾ���ö���Ŀ¼���Ҳ����Ҫ�ٷ��͸ý�Ŀ��Ϣ��
//if ptmptagReadDir.szQueryCRC = ptmptagSendInfo.szSendCRC 
//{
//ptmptagReadDir^.bNeedDelete = False; // ����λ��һ��ʱ�����ٶԸý�Ŀ����ɾ�����
//ptmptagSendInfo^.bNeedSend = False; //����λ��һ��ʱ�����ٷ���
//SendProgramList.Items[J - 1] = ptmptagSendInfo;
//QueryProgramList.Items[I - 1] = ptmptagReadDir;
//Break;
//}
//}
//}
//}
//nDeleteCount= 0;
//szDeleteFileDir= "";
//for i = 1 to QueryProgramList.Count do
//{
//ptmptagReadDir = QueryProgramList.Items[I - 1];
//if ptmptagReadDir.bNeedDelete = True 
//{
//szDeleteFileDir = szDeleteFileDir + ptmptagReadDir.szQueryFile;
//
//ncurProDeleteSectors= ptmptagReadDir^.nQueryFileLength;
//if ncurProDeleteSectors mod 4096 != 0 
//ncurProDeleteSectors = ncurProDeleteSectors div 4096 + 1
//else
//ncurProDeleteSectors = ncurProDeleteSectors div 4096;
//ntmpDeleteSectors= ntmpDeleteSectors + ncurProDeleteSectors;
//
//Inc(nDeleteCount);
//}
//}
//szDeleteFileDir= (char)(nDeleteCount and 0xFF) + (char)((nDeleteCount shr 8)and0xFF) + szDeleteFileDir;
//nLength= Length(szDeleteFileDir);
//Result= (char)(0xA1) + (char)(0x01) + (char)(nLength and 0xFF) + (char)((nLength shr 8)and0xFF) + szDeleteFileDir;
//nValidProgramSectors= 0;
//for I = 1 to SendProgramList.Count do
//{
//ptmptagSendInfo = SendProgramList.Items[I - 1];
//if ptmptagSendInfo^.bNeedSend = True 
//nValidProgramSectors = nValidProgramSectors + ptmptagSendInfo^.nSendnSectors;
//}
//nDeleteSectors= ntmpDeleteSectors;
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//Result = (char)(nRtnReq) + Result;
//}
//
//function DeleteAllProgramFiles(nProtocolVer: Cardinal; nRtnReq: Byte) : string;
//{
//Result = (char)(0xA1) + (char)(0x01)
//	+ (char)(2) + (char)(0)
//	+ (char)(0) + (char)(0);
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//Result = (char)(nRtnReq) + Result;
//}
//
//function GetAllSendProgramSectors(var SendProgramList : TList) : Cardinal;
//var
//I, nValidProgramSectors: Cardinal;
//ptmptagSendInfo: PtagSendInfo;
//{
//nValidProgramSectors = 0;
//for I = 1 to SendProgramList.Count do
//{
//ptmptagSendInfo = SendProgramList.Items[I - 1];
//nValidProgramSectors= nValidProgramSectors + ptmptagSendInfo^.nSendnSectors;
//}
//Result= nValidProgramSectors;
//}

//procedure GetReadFileDirList(szReadBuf: string; var QueryProgramList : TList);
//var
//nFileCount : Cardinal;
//I, J              : Cardinal;
//ptmptagReadDir: PtagReadDir;
//ntmpLength: Cardinal;
//sztmpCRC: string;
//{
//nFileCount = Length(szReadBuf) div 13;
//for I = 1 to nFileCount do
//{
//New(ptmptagReadDir);
//ptmptagReadDir^.szQueryFile = szReadBuf[(I - 1) * 13 + 1] + szReadBuf[(I - 1) * 13 + 2] + szReadBuf[(I - 1) * 13 + 3] + szReadBuf[(I - 1) * 13 + 4];
//ntmpLength= Byte(szReadBuf[(I - 1) * 13 + 6]) and 0xFF
//+ (Byte(szReadBuf[(I - 1) * 13 + 7]) shl 8) and 0xFF00
//+ (Byte(szReadBuf[(I - 1) * 13 + 8]) shl 16) and 0xFF0000
//+ (Byte(szReadBuf[(I - 1) * 13 + 9]) shl 24) and 0xFF000000;
//ptmptagReadDir^.nQueryFileLength = ntmpLength;
//sztmpCRC= szReadBuf[(I - 1) * 13 + 10]
//+ szReadBuf[(I - 1) * 13 + 11]
//+ szReadBuf[(I - 1) * 13 + 12]
//+ szReadBuf[(I - 1) * 13 + 13];
//ptmptagReadDir^.szQueryCRC = sztmpCRC; //���յĽ�Ŀ�ļ�CRC32У��ֵ��
//ptmptagReadDir^.bNeedDelete = True; //Ĭ����Ҫɾ��True���������ļ�У��һ��ʱ����ɾ���ļ����������ļ�һ�¡�У�鲻һ�£��������ļ�PC��������ʱɾ���ļ���
//QueryProgramList.Add(ptmptagReadDir);
//}
//
//}

//function GetReviseTimeInfo(nYear, nMonth, nDay, nHour, nMinute, nSecond, nWeek: Cardinal;
//nProtocolVer: Cardinal; nRtnReq: Byte) : string; //У��ʱ������;nWeek:��һΪ1������Ϊ7
//var
//sztmpYear : string;
//{
//sztmpYear = Format("%.4d", [nYear]);
//Result= (char)(0xA2) + (char)(02) + (char)(08) + (char)(0)
//+ (char)(StrToInt("0x" + sztmpYear[3] + sztmpYear[4])) //����ֽ�
//+ (char)(StrToInt("0x" + sztmpYear[1] + sztmpYear[2])) //����ֽ�
//+ (char)(StrToInt("0x" + IntToStr(nMonth)))
//+ (char)(StrToInt("0x" + IntToStr(nDay)))
//+ (char)(StrToInt("0x" + IntToStr(nHour)))
//+ (char)(StrToInt("0x" + IntToStr(nMinute)))
//+ (char)(StrToInt("0x" + IntToStr(nSecond)))
//+ (char)(StrToInt("0x" + IntToStr(nWeek)));
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//	Result = (char)(nRtnReq) + Result;
//}
//
//function GetScreenParameterInfo(Screen_ja: TSuperArray; nScreenOrd: Integer; ntmpBXCEColor: Byte) : string;
//var //��Ļ�ṹ
//	szValue : string;
//nValue: Cardinal;
//szSendBuf: string;
//wCRCCheck: Word;
//fp: file;
//{
//
//	szSendBuf = (char)(1);
//szValue= Screen_ja[(int)nScreenOrd].S["Screen_controllerName"];
//if Length(szValue) < 8 
//	{
//	while Length(szValue) < 8 do
//		szValue = szValue + "0";
//end
//else
//	szValue = Copy(szValue, 1, 8); //���������Ƴ���Ϊ8���ֽڡ�
//szSendBuf= szSendBuf + (char)(Ord(szValue[1])) + (char)(Ord(szValue[2])) + (char)(Ord(szValue[3])) + (char)(Ord(szValue[4]))
//+ (char)(Ord(szValue[5])) + (char)(Ord(szValue[6])) + (char)(Ord(szValue[7])) + (char)(Ord(szValue[8]));
//	nValue= Screen_ja[(int)nScreenOrd].I["Com_address"]; //��Ļ��ַ
//	szSendBuf= szSendBuf + (char)(nValue and 0xFF) + (char)((nValue shr 8) and 0xFF);
//		if Screen_ja[(int)nScreenOrd].I["Com_baudrate"] = baudrate[0] 
//			nValue = 1
//		else
//			nValue = 2; //������
//	szSendBuf= szSendBuf + (char)(nValue);
//	nValue= Screen_ja[(int)nScreenOrd].I["Screen_Width"]; //��Ļ���
//	szSendBuf= szSendBuf + (char)(nValue and 0xFF) + (char)((nValue shr 8) and 0xFF);
//	nValue= Screen_ja[(int)nScreenOrd].I["Screen_Height"]; //��Ļ���
//	szSendBuf= szSendBuf + (char)(nValue and 0xFF) + (char)((nValue shr 8) and 0xFF);
//		if ntmpBXCEColor = SCREEN_COLOR_DOUBLE 
//			nValue = GetScreenColorType(ntmpBXCEColor)
//		else
//			nValue = GetScreenColorType(Screen_ja[(int)nScreenOrd].I["Screen_color"]); //������
//	szSendBuf= szSendBuf + (char)(nValue);
//
//	nValue= Screen_ja[(int)nScreenOrd].I["Screen_MirrorMode"]; //����ģʽ����������
//	szSendBuf= szSendBuf + (char)(nValue);
//	nValue= Screen_ja[(int)nScreenOrd].I["Screen_oe"]; //OE����
//	szSendBuf= szSendBuf + (char)(nValue);
//	nValue= Screen_ja[(int)nScreenOrd].I["Screen_da"]; //DA����
//	szSendBuf= szSendBuf + (char)(nValue);
//	nValue= Screen_ja[(int)nScreenOrd].I["Screen_roworder"]; //��˳��
//	szSendBuf= szSendBuf + (char)(nValue);
//		if Screen_ja[(int)nScreenOrd].I["Screen_FreqPar"] < 0  //CLK��Ƶ����;û�з�Ƶ����Ĭ�ϴ���ֵΪ2��
//			nValue = 2
//		else
//			nValue = Screen_ja[(int)nScreenOrd].I["Screen_FreqPar"];
//	szSendBuf= szSendBuf + (char)(nValue);
//	nValue= Screen_ja[(int)nScreenOrd].I["Screen_oewidth"]; //OE���
//	szSendBuf= szSendBuf + (char)(nValue);
//
//	nValue= CONTROLLER_TYPE_OEFRONT[Screen_ja[(int)nScreenOrd].I["Screen_oefront"]]; //OE��ǰ��
//	szSendBuf= szSendBuf + (char)(nValue);
//	nValue= 0; //Screen_ja[i].I["Screen_color"];  //�������Ĵ�����ģʽ
//	szSendBuf= szSendBuf + (char)(nValue);
//	nValue= Screen_ja[(int)nScreenOrd].I["Screen_ReadWaitTimeOut"]; //ͨѶ��ʱ����
//	szSendBuf= szSendBuf + (char)(nValue);
//		if not (Screen_ja[(int)nScreenOrd].i["Screen_control"] in[CONTROLLER_TYPE_3T
//			, CONTROLLER_TYPE_3A, CONTROLLER_TYPE_3A1, CONTROLLER_TYPE_3A2, CONTROLLER_TYPE_3M])  //4���������˿��ƿ�����ģʽ����־ģʽ
//			{
//			nValue = 0; //���ƿ�����ģʽ;Ĭ��Ϊ����ģʽ
//	szSendBuf= szSendBuf + (char)(nValue);
//	nValue= 0; //��־ģʽ��Ĭ��Ϊ����־ģʽ
//	szSendBuf= szSendBuf + (char)(nValue);
//		}
//	nValue= 0; //Screen_ja[i].I["Screen_color"];  //����ֵ1
//	szSendBuf= szSendBuf + (char)(nValue);
//	nValue= 0; // Screen_ja[i].I["Screen_color"];  //����ֵ2
//	szSendBuf= szSendBuf + (char)(nValue);
//	nValue= 0; // Screen_ja[i].I["Screen_color"];  //����ֵ3
//	szSendBuf= szSendBuf + (char)(nValue);
//	nValue= 0; // Screen_ja[i].I["Screen_color"];  //����ֵ4
//	szSendBuf= szSendBuf + (char)(nValue);
//	nValue= 0; // Screen_ja[i].I["Screen_color"];  //����ֵ5
//	szSendBuf= szSendBuf + (char)(nValue);
//	nValue= 0; // Screen_ja[i].I["Screen_color"];  //����ֵ6
//	szSendBuf= szSendBuf + (char)(nValue);
//	nValue= 0; // Screen_ja[i].I["Screen_color"];  //����ֵ7
//	szSendBuf= szSendBuf + (char)(nValue);
//	nValue= 0; // Screen_ja[i].I["Screen_color"];  //����ֵ8
//	szSendBuf= szSendBuf + (char)(nValue);
//	wCRCCheck= 0;
//		GetCRCCheck(@szSendBuf[1], Length(szSendBuf), wCRCCheck); //�õ�������У��ֵwPhy1Check
//	szSendBuf= szSendBuf + (char)(wCRCCheck and 0xFF) + (char)((wCRCCheck shr 8) and 0xFF);
//	Result= szSendBuf;
//	{0xIFDEF DEBUG}
//	try
//		AssignFile(fp, "c:\ScreenParamerer");
//	Rewrite(fp, 1);
//	BlockWrite(fp, szSendBuf[1], Length(szSendBuf));
//	finally
//		CloseFile(fp);
//	}
//	{0xENDIF}
//
//	}
//
//function SetScreenIPAddressInfo(Screen_ja: TSuperArray; nScreenOrd: Integer;
//nProtocolVer: Cardinal; nRtnReq: Byte;
//szIP, szSubMask, szGateWay: string;
//nPort, nServerMode, nServerPort, nHeartBeatInterval: Cardinal;
//szServerIP, szServerAccessPassword, szNetID: string;
//bWildCardsSend: Boolean; szMacInfo: string) : string;
//var
//i : Cardinal;
//s: TStringList;
//nValue, nLength   : Cardinal;
//szValue: string;
//szSendBuf: string;
//{
//szSendBuf = "";
//if bWildCardsSend = False 
//{
//szSendBuf = (char)(0xA4) + (char)(01) + (char)(44) + (char)(0)
//+ (char)(Screen_ja[i].I["Net_ConnnectMode"]);
//S= SplitString(Screen_ja[(int)nScreenOrd].S["Net_IP"], ".");
//szSendBuf= szSendBuf + (char)(StrToInt(s[0])) + (char)(StrToInt(s[1])) + (char)(StrToInt(s[2])) + (char)(StrToInt(s[3]));
//s.Free;
//S= SplitString(Screen_ja[(int)nScreenOrd].S["Net_mark"], ".");
//szSendBuf= szSendBuf + (char)(StrToInt(s[0])) + (char)(StrToInt(s[1])) + (char)(StrToInt(s[2])) + (char)(StrToInt(s[3]));
//s.Free;
//S= SplitString(Screen_ja[(int)nScreenOrd].S["Net_gateway"], ".");
//szSendBuf= szSendBuf + (char)(StrToInt(s[0])) + (char)(StrToInt(s[1])) + (char)(StrToInt(s[2])) + (char)(StrToInt(s[3]));
//s.Free;
//nValue= Screen_ja[(int)nScreenOrd].I["Net_port"];
//szSendBuf= szSendBuf + (char)(nValue and 0xFF) + (char)((nValue shr 8) and 0xFF);
//
//szSendBuf= szSendBuf + (char)(Screen_ja[(int)nScreenOrd].I["Net_ServerMode"]);
//S= SplitString(Screen_ja[i].S["Net_ServerIP"], ".");
//szSendBuf= szSendBuf + (char)(StrToInt(s[0])) + (char)(StrToInt(s[1])) + (char)(StrToInt(s[2])) + (char)(StrToInt(s[3]));
//s.Free;
//
//nValue= Screen_ja[(int)nScreenOrd].I["Net_ServerPort"];
//szSendBuf= szSendBuf + (char)(nValue and 0xFF) + (char)((nValue shr 8) and 0xFF);
//
//szValue= Screen_ja[(int)nScreenOrd].S["Net_ServerAccessPassword"];
//if Length(szValue) < 8 
//{
//while Length(szValue) < 8 do
//szValue = szValue + "0";
//end
//else
//szValue = Copy(szValue, 1, 8); //�������������볤��Ϊ8���ֽڡ�
//szSendBuf= szSendBuf + szValue;
//nValue= Screen_ja[(int)nScreenOrd].I["Net_ServerHeartBeatInterval"];
//szSendBuf= szSendBuf + (char)(nValue and 0xFF) + (char)((nValue shr 8) and 0xFF);
//szValue= Screen_ja[(int)nScreenOrd].S["Network_ID"];
//if Length(szValue) < 12 
//{
//while Length(szValue) < 12 do
//szValue = szValue + "0";
//end
//else
//szValue = Copy(szValue, 1, 12); //���ƿ������š�
//szSendBuf= szSendBuf + szValue;
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//{
//nLength = Byte(szSendBuf[3]) + (Byte(szSendBuf[4]) shl 8) and 0xFF00 + 7;
//szSendBuf[3] = (char)(nLength and 0xFF);
//szSendBuf[4] = (char)((nLength shr 8) and 0xFF);
//szSendBuf= szSendBuf + (char)(0); //��ȷ���͵�ʱ�򲻽���MAC��ַ�жϡ�
//szSendBuf= szSendBuf + (char)(0) + (char)(0) + (char)(0) + (char)(0) + (char)(0) + (char)(0);
//}
//end
//else
//{
//szSendBuf = (char)(0xA4) + (char)(01) + (char)(44) + (char)(0);
//szSendBuf= szSendBuf + (char)(NET_CONNECT_STATICIP);
//S= SplitString(szIP, ".");
//szSendBuf= szSendBuf + (char)(StrToInt(s[0])) + (char)(StrToInt(s[1])) + (char)(StrToInt(s[2])) + (char)(StrToInt(s[3]));
//s.Free;
//S= SplitString(szSubMask, ".");
//szSendBuf= szSendBuf + (char)(StrToInt(s[0])) + (char)(StrToInt(s[1])) + (char)(StrToInt(s[2])) + (char)(StrToInt(s[3]));
//s.Free;
//S= SplitString(szGateWay, ".");
//szSendBuf= szSendBuf + (char)(StrToInt(s[0])) + (char)(StrToInt(s[1])) + (char)(StrToInt(s[2])) + (char)(StrToInt(s[3]));
//s.Free;
//nValue= nPort;
//szSendBuf= szSendBuf + (char)(nValue and 0xFF) + (char)((nValue shr 8) and 0xFF);
//
//szSendBuf= szSendBuf + (char)(nServerMode);
//S= SplitString(szServerIP, ".");
//szSendBuf= szSendBuf + (char)(StrToInt(s[0])) + (char)(StrToInt(s[1])) + (char)(StrToInt(s[2])) + (char)(StrToInt(s[3]));
//s.Free;
//
//nValue= nServerPort;
//szSendBuf= szSendBuf + (char)(nValue and 0xFF) + (char)((nValue shr 8) and 0xFF);
//
//szValue= szServerAccessPassword;
//if Length(szValue) < 8 
//{
//while Length(szValue) < 8 do
//szValue = szValue + "0";
//end
//else
//szValue = Copy(szValue, 1, 8); //�������������볤��Ϊ8���ֽڡ�
//szSendBuf= szSendBuf + szValue;
//nValue= nHeartBeatInterval;
//szSendBuf= szSendBuf + (char)(nValue and 0xFF) + (char)((nValue shr 8) and 0xFF);
//szValue= szNetID;
//if Length(szValue) < 12 
//{
//while Length(szValue) < 12 do
//szValue = szValue + "0";
//end
//else
//szValue = Copy(szValue, 1, 12); //���ƿ������š�
//szSendBuf= szSendBuf + szValue;
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//{
//nLength = Byte(szSendBuf[3]) + (Byte(szSendBuf[4]) shl 8) and 0xFF00 + 7;
//szSendBuf[3] = (char)(nLength and 0xFF);
//szSendBuf[4] = (char)((nLength shr 8) and 0xFF);
//szSendBuf= szSendBuf + (char)(1);
//szValue= szMacInfo;
//s= SplitString(szValue, "-");
//if s.Count >= 1 
//szSendBuf = szSendBuf + (char)(StrToInt("0x" + s[0]))
//else
//szSendBuf = szSendBuf + (char)(0);
//if s.Count >= 2 
//szSendBuf = szSendBuf + (char)(StrToInt("0x" + s[1]))
//else
//szSendBuf = szSendBuf + (char)(0);
//if s.Count >= 3 
//szSendBuf = szSendBuf + (char)(StrToInt("0x" + s[2]))
//else
//szSendBuf = szSendBuf + (char)(0);
//if s.Count >= 4 
//szSendBuf = szSendBuf + (char)(StrToInt("0x" + s[3]))
//else
//szSendBuf = szSendBuf + (char)(0);
//if s.Count >= 5 
//szSendBuf = szSendBuf + (char)(StrToInt("0x" + s[4]))
//else
//szSendBuf = szSendBuf + (char)(0);
//if s.Count >= 6 
//szSendBuf = szSendBuf + (char)(StrToInt("0x" + s[5]))
//else
//szSendBuf = szSendBuf + (char)(0);
//}
//}
//Result= szSendBuf;
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//Result = (char)(nRtnReq) + Result;
//}
//
//function SetScreenNetMACInfo(Screen_ja: TSuperArray; nScreenOrd: Integer;
//nProtocolVer: Cardinal; nRtnReq: Byte) : string;
//var
//i : Cardinal;
//nValue: Cardinal;
//szSendBuf: string;
//slst: TStringList;
//szStr: string;
//{
//szSendBuf = "";
//szSendBuf= (char)(0xA4) + (char)(00) + (char)(6) + (char)(0);
//
//szStr= Screen_ja[(int)nScreenOrd].S["Net_mac"];
//slst= SplitString(szStr, "-");
//if slst.Count >= 1 
//szSendBuf = szSendBuf + (char)(StrToInt("0x" + slst[0]))
//else
//szSendBuf = szSendBuf + (char)(0);
//if slst.Count >= 2 
//szSendBuf = szSendBuf + (char)(StrToInt("0x" + slst[1]))
//else
//szSendBuf = szSendBuf + (char)(0);
//if slst.Count >= 3 
//szSendBuf = szSendBuf + (char)(StrToInt("0x" + slst[2]))
//else
//szSendBuf = szSendBuf + (char)(0);
//if slst.Count >= 4 
//szSendBuf = szSendBuf + (char)(StrToInt("0x" + slst[3]))
//else
//szSendBuf = szSendBuf + (char)(0);
//if slst.Count >= 5 
//szSendBuf = szSendBuf + (char)(StrToInt("0x" + slst[4]))
//else
//szSendBuf = szSendBuf + (char)(0);
//if slst.Count >= 6 
//szSendBuf = szSendBuf + (char)(StrToInt("0x" + slst[5]))
//else
//szSendBuf = szSendBuf + (char)(0);
//Result= szSendBuf;
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//Result = (char)(nRtnReq) + Result;
//}
//
//function GetReadScreenTCPIPInfo(nProtocolVer: Cardinal; nRtnReq: Byte) : string;
//{
//Result = (char)(0xA4) + (char)(02) + (char)(0) + (char)(0);
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//Result = (char)(nRtnReq) + Result;
//}
//
//function GetTransStatus(nProtocolVer: Cardinal; nRtnReq: Byte) : string;
//{
//Result = (char)(0xA1) + (char)(0x13) + (char)(0) + (char)(0);
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//Result = (char)(nRtnReq) + Result;
//}
//
//function GetTransStatusInfo(szReadBuf: string; nReadLength: Cardinal; var nTransRW : Byte;
//var szTransFileName, szTransFileCrc: string; var nTransFileOffset : Cardinal) : Boolean;
//{
//if nReadLength >= 10 
//nTransRW = Byte(szReadBuf[10])
//else
//nTransRW = 2; //�޲�����
//if nTransRW = 2 
//{
//szTransFileName = "";
//szTransFileCrc= "";
//nTransFileOffset= 0;
//Exit;
//}
//if nReadLength >= 14 
//szTransFileName = szReadBuf[11] + szReadBuf[12] + szReadBuf[13] + szReadBuf[14]
//else
//szTransFileName = "";
//if nReadLength >= 18 
//szTransFileCrc = szReadBuf[15] + szReadBuf[16] + szReadBuf[17] + szReadBuf[18]
//else
//szTransFileCrc = "";
//if nReadLength >= 22 
//nTransFileOffset = Byte(szReadBuf[19]) + ((byte(szReadBuf[20]) shl 8) and 0xFF00)
//+ ((byte(szReadBuf[21]) shl 16) and 0xFF0000) + ((byte(szReadBuf[22]) shl 24) and 0xFF000000)
//else
//nTransFileOffset = 0;
//}
//
//function AutoGetUserMAC(dtDateTime: TDateTime) : string;
//var
//tmpDateTime : TDateTime;
//nSecondBetween, nSecondBetweenDiv5: Int64;
//nNum4, nNum5, nNum6: Byte;
//nxorNum4, nxorNum5, nxorNum6: Byte;
//szUserMac: string;
//{
//tmpDateTime = EncodeDateTime(2010, 1, 1, 0, 0, 0, 0);
//nSecondBetween= SecondsBetween(dtDateTime, tmpDateTime);
//nSecondBetweenDiv5= nSecondBetween div 5;
//nNum4= (nSecondBetweenDiv5 shr 16) and 0xFF;
//nNum5= (nSecondBetweenDiv5 shr 8) and 0xFF;
//nNum6= nSecondBetweenDiv5 and 0xFF;
//nxorNum4= nNum4 xor 0xAA;
//nxorNum5= nNum5 xor 0xAA;
//nxorNum6= nNum6 xor 0xAA;
//szUserMac= "-" + IntToHex(nxorNum4, 2) + "-"
//+ IntToHex(nxorNum5, 2) + "-"
//+ IntToHex(nxorNum6, 2);
//Result= szUserMac;
//
//}
//
//function GetScanData(nControlType: Cardinal; pScreenFlowItem: ptagScreenFlowItem; nIndex: Cardinal) : string;
//var
//i : Cardinal;
//szSendBuf: string;
//wCRCCheck: Word;
//{
//szSendBuf = (char)(SEND_FILE_TYPE_SCREENSCAN);
//with pScreenFlowItem^ do
//{
//case nControlType of
//CONTROLLER_TYPE_3T, CONTROLLER_TYPE_3A
//, CONTROLLER_TYPE_3A1, CONTROLLER_TYPE_3A2, CONTROLLER_TYPE_3M:
//	{
//		szSendBuf = szSendBuf + (char)(nScreen_Scan)
//		+ (char)(nData_Row_Per_Data)
//		+ (char)(nData_Decoder_Uen)
//		+ (char)(nData_U_Mode)
//		+ (char)(nData_Col_Flod_Mode)
//		+ (char)(nData_Wu)
//		+ (char)(nData_Hu);
//	//+ (char)(nData_WtMax) //ȡ����ת����ÿ����С��Ԫ�Ŀ�ȡ���λΪbyte�������ֽ�����
//
//szSendBuf= szSendBuf + (char)(nReserved1)
//	+ (char)(nReserved2)
//	+ (char)(nReserved3)
//	+ (char)(nReserved4)
//	+ (char)(nReserved5)
//	+ (char)(nReserved6);
//			}
//else
//{
//szSendBuf = szSendBuf + (char)(nScreen_Scan) + (char)(nIndex)
//+ (char)(nData_Row_Per_Data)
//+ (char)(nData_Decoder_Uen)
//+ (char)(nData_U_Mode)
//+ (char)(nData_Col_Flod_Mode)
//+ (char)(nData_Wu)
//+ (char)(nData_Hu);
//szSendBuf= szSendBuf + (char)(nReserved1)
//+ (char)(nReserved2)
//+ (char)(nReserved3)
//+ (char)(nReserved4)
//+ (char)(nReserved5);
//}
//}
//szSendBuf= szSendBuf + (char)(nData_Con_Table_Length);
//for I = 1 to nData_Con_Table_Length do
//{
//szSendBuf = szSendBuf + pData_Con_Table[i - 1];
//}
//}
//wCRCCheck= 0;
//GetCRCCheck(@szSendBuf[1], Length(szSendBuf), wCRCCheck); //�õ�������У��ֵwPhy1Check
//szSendBuf= szSendBuf + (char)(wCRCCheck and 0xFF) + (char)((wCRCCheck shr 8) and 0xFF);
//Result= szSendBuf;
//}
//
//function GetFirmwareActivateInf(szFirmwareFile: WideString;
//nProtocolVer: Cardinal; nRtnReq: Byte) : string;
//{
//	Result = (char)(0xA2) + (char)(03) + (char)(4) + (char)(0) + (char)(Ord(szFirmwareFile[1])) + (char)(Ord(szFirmwareFile[2]))
//	+ (char)(Ord(szFirmwareFile[3])) + (char)(Ord(szFirmwareFile[4]));
//; //�ļ�����
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//	Result = (char)(nRtnReq) + Result;
//}
//
//function GetQueryFirmwareStatus(nProtocolVer: Cardinal; nRtnReq: Byte) : string;
//{
//	Result = (char)(0xA2) + (char)(04) + (char)(0) + (char)(0);
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//	Result = (char)(nRtnReq) + Result;
//}
//
//function GetReadControlID(nProtocolVer: Cardinal; nRtnReq: Byte) : string;
//{
//	Result = (char)(0xA2) + (char)(0x0A) + (char)(0) + (char)(0);
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//	Result = (char)(nRtnReq) + Result;
//}
//
//function GetReadCopyrightInfo(nProtocolVer: Cardinal; nRtnReq: Byte) : string;
//{
//	Result = (char)(0xA2) + (char)(0x0B) + (char)(0) + (char)(0);
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//	Result = (char)(nRtnReq) + Result;
//}

SYSTEMTIME GetVersionDateTime(string szFirmWareVersion)
{
	SYSTEMTIME Result;
	string szStr;
	WORD nYear;
	WORD nMonth;
	WORD nDay;
	
	szStr = szFirmWareVersion;
	
	while (szStr.size() < 3)
		szStr = szStr + "1";

	nYear= (WORD)(2000 + szStr[0]);
	nMonth= (WORD)szStr[1];
	nDay= (WORD)szStr[2];
	if ((nYear > 2050) || (nYear < 2000))
		nYear = 2010;
	if ((nMonth < 1) || (nMonth > 12))	
		nMonth = 1;
	if ((nDay < 1) || (nDay > 31))
		nDay = 1;
	
	Result.wYear = nYear;
	Result.wMonth = nMonth;
	Result.wDay = nDay;

	return Result;
}

//function GetVersionDateTimeFifthProtocol(szFirmWareVersion: string) : TDate;
//var
//szStr : string;
//nYear: Integer;
//nMonth: Integer;
//nDay: Integer;
//{
//szStr = szFirmWareVersion;
//while Length(szStr) < 6 do
//szStr = szStr + "1";
//nYear= 2000 + StrToInt(copy(szStr, 1, 2));
//nMonth= StrToInt(copy(szStr, 3, 2));
//nDay= StrToInt(copy(szStr, 5, 2));
//if (nYear > 2050) or (nYear < 2000) 
//nYear = 2010;
//if (nMonth < 1) or (nMonth > 12) 
//nMonth = 1;
//if (nDay < 1) or (nDay > 31) 
//nDay = 1;
//Result= EncodeDate(nYear, nMonth, nDay);
//}

//function GetReadFile(nSendCmd: Cardinal; szFileName: string;
//nProtocolVer: Cardinal; nRtnReq: Byte) : string; //��ȡ�ļ���
//{
//Result = (char)((nSendCmd shr 8) and 0xFF) + (char)(nSendCmd and 0xFF)
//+ (char)(4) + (char)(0)
//+ (char)(Ord(szFileName[1])) + (char)(Ord(szFileName[2]))
//+ (char)(Ord(szFileName[3])) + (char)(Ord(szFileName[4]));
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//Result = (char)(nRtnReq) + Result;
//}
//
//function GetReadDir(nSendCmd: Cardinal; nFileType: Cardinal;
//nProtocolVer, nMaxReadDir: Cardinal; nRtnReq: Byte) : string; //��ȡĿ¼
//{
//case nProtocolVer of
//PROTOCOLVER_FIFTH_CONTROL :
//{
//Result = (char)(nRtnReq) + (char)((nSendCmd shr 8) and 0xFF) + (char)(nSendCmd and 0xFF)
//+ (char)(2) + (char)(0)
//+ (char)(nFileType)
//+ (char)(nMaxReadDir);
//}
//else
//{
//Result = (char)((nSendCmd shr 8) and 0xFF) + (char)(nSendCmd and 0xFF)
//+ (char)(1) + (char)(0)
//+ (char)(nFileType);
//}
//}
//
//}
//
//function GetFormatExternalFlash(nProtocolVer: Cardinal; nRtnReq: Byte) : string;
//{
//Result = (char)(0xA2) + (char)(09)
//	+ (char)(0) + (char)(0);
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//Result = (char)(nRtnReq) + Result;
//}
//
//function GetDisplayOptimization(nScanTime: Cardinal; nProtocolVer: Cardinal; nRtnReq: Byte) : string;
//{
//Result = (char)(0xA2) + (char)(0x0C)
//+ (char)(0x02) + (char)(0) + (char)(nScanTime);
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//Result = (char)(nRtnReq) + Result;
//}
//
//function GetSetPasswordInfo(szOldPassword, szNewPassword: string; nProtocolVer: Cardinal; nRtnReq: Byte) : string;
//var
//tmpOldPassword, tmpNewPassword: string;
//{
//tmpOldPassword = szOldPassword;
//tmpNewPassword= szNewPassword;
//SetLength(tmpOldPassword, Length(STATIC_ENCRYPTION_KEY));
//SetLength(tmpNewPassword, Length(STATIC_ENCRYPTION_KEY));
//Result= (char)(0xA2) + (char)(0x10)
//+ (char)(12) + (char)(0) + GetXorPassword(tmpOldPassword, STATIC_ENCRYPTION_KEY)
//+ GetXorPassword(tmpNewPassword, STATIC_ENCRYPTION_KEY);
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//	Result = (char)(nRtnReq) + Result;
//
//}

//function GetDeletePasswordInfo(Screen_ja: TSuperArray; nScreenOrd: Cardinal;
//nProtocolVer: Cardinal; nRtnReq: Byte) : string;
//var
//szOldPassword, szNewPassword: string;
//{
//szOldPassword = Screen_ja[(int)nScreenOrd].S["Screen_PA1"];
//szNewPassword= Screen_ja[(int)nScreenOrd].S["Screen_PA2"];
//SetLength(szOldPassword, Length(STATIC_ENCRYPTION_KEY));
//SetLength(szNewPassword, Length(STATIC_ENCRYPTION_KEY));
//Result= (char)(0xA2) + (char)(0x11)
//+ (char)(6) + (char)(0) + GetXorPassword(szOldPassword, STATIC_ENCRYPTION_KEY);
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//Result = (char)(nRtnReq) + Result;
//}
//
//function GetFirmwareFormatInfo(szFirmwareName: WideString) : string;
//var
//szSendBuf : string;
//nSendLength: Cardinal;
//fp: file;
//{
//if WideFileExists(szFirmwareName) = true 
//{
//AssignFile(fp, szFirmwareName);
//Reset(fp, 1);
//nSendLength= FileSize(fp);
//SetLength(szSendBuf, nSendLength);
//BlockRead(fp, szSendBuf[1], nSendLength);
//CloseFile(fp);
//Result= szSendBuf;
//}
//}

DWORD GetControlStuntRealityRunSpeed(DWORD nWidth, DWORD nHeight, DWORD nScreenColor, DWORD nStuntIndex, DWORD nRunSpeed, DWORD &nDefaultRunSpeed)
{
	UNREFERENCED_PARAMETER(nWidth);
	UNREFERENCED_PARAMETER(nHeight);
	UNREFERENCED_PARAMETER(nScreenColor);
	UNREFERENCED_PARAMETER(nStuntIndex);
	UNREFERENCED_PARAMETER(nDefaultRunSpeed);

	return nRunSpeed;
}

DWORD GetControlFrameStuntRealityRunSpeed(DWORD nWidth, DWORD nHeight, DWORD nScreenColor, DWORD nStuntIndex, DWORD nRunSpeed, DWORD &nDefaultRunSpeed)
{
	UNREFERENCED_PARAMETER(nWidth);
	UNREFERENCED_PARAMETER(nHeight);
	UNREFERENCED_PARAMETER(nScreenColor);
	UNREFERENCED_PARAMETER(nStuntIndex);
	UNREFERENCED_PARAMETER(nDefaultRunSpeed);

	return nRunSpeed;
}

//function GetControlStuntDefaultRunSpeed(nControlType, nWidth, nHeight, nScreenColor: Cardinal) : Cardinal;
//{
//	if (nControlType = CONTROLLER_TYPE_5E1)
//		or (nControlType = CONTROLLER_TYPE_5E2)
//		or (nControlType = CONTROLLER_TYPE_5E3)
//												
//		{
//		if nHeight <= 64 
//			Result = 3
//		else
//			Result = 2;
//end
//	else
//	Result = 1;
//}

//function GetControlFrameStuntDefaultRunSpeed(nWidth, nHeight, nScreenColor: Cardinal) : Cardinal;
//var
//nScreenAreaSize : Cardinal;
//{
//Result = 5;
//nScreenAreaSize= nWidth * nHeight;
//Result= 5;
//}

//function GetScreenLockScreenStatusInfo(nLock_Status, nNonvolatile: Byte; nProtocolVer: Cardinal; nRtnReq: Byte) : string; //nLock_Status:0:������1:������nNonvolatile:0:���粻���棻1:���籣�棻
//{
//	Result = (char)(0xA2) + (char)(0x0D) + (char)(0x02) + (char)(0);
//if nNonvolatile = 1 
//	Result = Result + (char)(0x01) //���籣�棻
//else
//	Result = Result + (char)(0x00); //���粻����
//if nLock_Status = 1 
//	Result = Result + (char)(0x01) //������Ļ��
//else
//	Result = Result + (char)(0x00); //������Ļ
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//	Result = (char)(nRtnReq) + Result;
//}

//function GetScreenLockProgramStatusInfo(szProgramName: string; nLock_Status, nNonvolatile: Byte;
//nProtocolVer: Cardinal; nRtnReq: Byte) : string; //szProgramName:��Ŀ���ƣ�nLock_Status:0:������1:������nNonvolatile:0:���粻���棻1:���籣�棻
//var
//	tmpProgramName : string;
//{
//	Result = (char)(0xA2) + (char)(0x0E) + (char)(0x06) + (char)(0);
//if nNonvolatile = 1 
//	Result = Result + (char)(0x01) //���籣�棻
//else
//	Result = Result + (char)(0x00); //���粻����
//if nLock_Status = 1 
//	Result = Result + (char)(0x01) //������
//else
//	Result = Result + (char)(0x00); //����
//tmpProgramName= szProgramName;
//SetLength(tmpProgramName, 4); //��Ŀ�ļ�������Ϊ4���ֽڡ�
//Result= Result + tmpProgramName;
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//	Result = (char)(nRtnReq) + Result;
//}

//function GetReadScreenStatusInfo(nProtocolVer: Cardinal; nRtnReq: Byte) : string;
//{
//Result = (char)(0xA2) + (char)(0x0F) + (char)(0x00) + (char)(0);
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//Result = (char)(nRtnReq) + Result;
//}
//
//function GetControlDelayStartSecondInfo(nSecond: Cardinal;
//nProtocolVer: Cardinal; nRtnReq: Byte) : string; //ת��������ʱ����
//{
//Result = (char)(0xA2) + (char)(0x12) + (char)(0x02) + (char)(0)
//+ (char)(nSecond and 0xFF) + (char)((nSecond shr 8) and 0xFF);
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//Result = (char)(nRtnReq) + Result;
//}
//
//function GetControlButtonModeInfo(nMode: Byte;
//nProtocolVer: Cardinal; nRtnReq: Byte) : string;
//{
//Result = (char)(0xA2) + (char)(0x13) + (char)(0x06) + (char)(0)
//+ (char)(nMode)
//+ (char)(0)
//+ (char)(0)
//+ (char)(0)
//+ (char)(0)
//+ (char)(0);
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//Result = (char)(nRtnReq) + Result;
//}
//
//function GetScreenLOGOInfo(Screen_ja: TSuperArray; nScreenOrd: Cardinal; var nSendLength : Cardinal;
//nProtocolVer: Cardinal; nRtnReq: Byte) : string;
//{
//Result = MakeScreenLOGOValue(Screen_ja
//, nScreenOrd
//, nSendLength);
////  if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
////    Result := (char)(nRtnReq) + Result;
//}
//
//function GetDleteScreenLOGOInfo(szLOGOFileNamde: string;
//nProtocolVer: Cardinal; nRtnReq: Byte) : string;
//{
//Result = (char)(0xA1) + (char)(0x0A) + (char)(0x06) + (char)(0)
//+ (char)(1)
//+ (char)(0)
//+ szLOGOFileNamde[1]
//+ szLOGOFileNamde[2]
//+ szLOGOFileNamde[3]
//+ szLOGOFileNamde[4];
//if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//Result = (char)(nRtnReq) + Result;
//}
//
//function GetServerModeLookUp(szReadInfo: string; nReadLength: Cardinal) : tagServerModeLookUpRecord;
//var
//tmptagServerModeLookUpRecord : tagServerModeLookUpRecord;
//szValue: string;
//nProtocolVer, nOffect: Byte;
//{
//nProtocolVer = Byte(szReadInfo[1]);
//if (nProtocolVer = PROTOCOLVER_THIRD_CONTROL) or
//(nProtocolVer = PROTOCOLVER_FOURTH_CONTROL) 
//nOffect = 0
//else if (nProtocolVer = PROTOCOLVER_FIFTH_CONTROL) 
//nOffect = 1;
//if nReadLength >= 17 + nOffect 
//tmptagServerModeLookUpRecord.szServerAccessPassword = copy(szReadInfo, 9, 8);
//if nReadLength >= 21 + nOffect 
//{
//szValue = copy(szReadInfo, 18 + nOffect, 4);
//tmptagServerModeLookUpRecord.szIPAddress = IntToStr(Byte(szValue[1])) + "." + IntToStr(Byte(szValue[2]))
//+ "." + IntToStr(Byte(szValue[3])) + "." + IntToStr(Byte(szValue[4]));
//}
//if nReadLength >= 25 + nOffect 
//{
//szValue = copy(szReadInfo, 22 + nOffect, 4);
//tmptagServerModeLookUpRecord.szSubnetMask = IntToStr(Byte(szValue[1])) + "." + IntToStr(Byte(szValue[2]))
//+ "." + IntToStr(Byte(szValue[3])) + "." + IntToStr(Byte(szValue[4]));
//}
//if nReadLength >= 29 + nOffect 
//{
//szValue = copy(szReadInfo, 26 + nOffect, 4);
//tmptagServerModeLookUpRecord.szGateway = IntToStr(Byte(szValue[1])) + "." + IntToStr(Byte(szValue[2]))
//+ "." + IntToStr(Byte(szValue[3])) + "." + IntToStr(Byte(szValue[4]));
//}
//if nReadLength >= 31 + nOffect 
//{
//tmptagServerModeLookUpRecord.nPort = (Byte(szReadInfo[31 + nOffect]) shl 8) and 0xFF00 + Byte(szReadInfo[30 + nOffect]);
//}
//if nReadLength >= 37 + nOffect 
//{
//szValue = copy(szReadInfo, 32 + nOffect, 6);
//tmptagServerModeLookUpRecord.szMac = IntToHex(Byte(szValue[1]), 2) + "-" + IntToHex(Byte(szValue[2]), 2)
//+ "-" + IntToHex(Byte(szValue[3]), 2) + "-" + IntToHex(Byte(szValue[4]), 2) + "-" + IntToHex(Byte(szValue[5]), 2)
//+ "-" + IntToHex(Byte(szValue[6]), 2);
//}
//if nReadLength >= 49 + nOffect 
//{
//szValue = copy(szReadInfo, 38 + nOffect, 12);
//tmptagServerModeLookUpRecord.szNetwork_ID = szValue;
//}
//Result= tmptagServerModeLookUpRecord;
//}
//
//function GetScreenMessage(nControlType: Cardinal) : string;
//var
//I : Cardinal;
//szSendbuf, sztmpBuf: string;
//tmpBmp, desBmp    : TBitmap;
//nCurAddress, nDataLength, nPageSize, nDataOffest: Cardinal;
//nAllWidth, nRealWidth: Byte;
//wCRCCheck: Word;
//bInvalidData: Boolean;
//szSceenPara, szPlsProgram, szScreenNo,
//szBaudate, szMemory_error, szParameter_outof_range,
//szUnauthorized_access, szStart_the_program, szDevice_Access,
//szUnknown_Disk, szNo_data, szData_error,
//szUpload_successful, szRemove_the_disk, szRemove_devices,
//szUnknown_device, szPower_overload, szUpload_error,
//szUpdated_successfully, szUpdate_failed, szPassword_error,
//szSpecification, szUpdate, szUpload, szRemoveUDisk, szFont: WideString;
//iniMyFile: TINIFile;
//nTempleCount, nOrd: Cardinal;
//Controller_obj: ISuperObject;
//nProtocolVer: Byte;
//szcurText: widestring;
//nTextWidth, nTextHeight: Cardinal;
//{
//iniMyFile = TIniFile.Create(ExtractFilePath(Application.ExeName) + "Setup.ini");
//try
//szSceenPara = iniMyFile.ReadString("InformationLibrary", "SetPara", "�������");
//szPlsProgram= iniMyFile.ReadString("InformationLibrary", "LoadProgram", "��ӽ�Ŀ");
//szScreenNo= iniMyFile.ReadString("InformationLibrary", "ScreenNo:", "����:");
//szBaudate= iniMyFile.ReadString("InformationLibrary", "Baudrate:", "������:");
//szSpecification= iniMyFile.ReadString("InformationLibrary", "Specification", "���");
//szMemory_error= iniMyFile.ReadString("InformationLibrary", "Memory error", "�洢������");
//szParameter_outof_range= iniMyFile.ReadString("InformationLibrary", "Parameter out of range", "����Խ��");
//szUnauthorized_access= iniMyFile.ReadString("InformationLibrary", "Unauthorized access", "�Ƿ�����");
//szStart_the_program= iniMyFile.ReadString("InformationLibrary", "Start the program", "��������");
//szDevice_Access= iniMyFile.ReadString("InformationLibrary", "Device Access", "�豸����");
//szUnknown_Disk= iniMyFile.ReadString("InformationLibrary", "Unknown Disk", "δ֪����");
//szNo_data= iniMyFile.ReadString("InformationLibrary", "No data", "û������");
//szData_error= iniMyFile.ReadString("InformationLibrary", "Data error", "���ݴ���");
//szUpload_successful= iniMyFile.ReadString("InformationLibrary", "Upload successful", "�ϴ��ɹ�");
//szRemove_the_disk= iniMyFile.ReadString("InformationLibrary", "Remove the disk", "�����Ƴ�");
//szRemove_devices= iniMyFile.ReadString("InformationLibrary", "Remove devices", "�Ƴ��豸");
//szUnknown_device= iniMyFile.ReadString("InformationLibrary", "Unknown device", "δ֪�豸");
//szPower_overload= iniMyFile.ReadString("InformationLibrary", "Power overload", "��Դ����");
//szUpload_error= iniMyFile.ReadString("InformationLibrary", "Upload error", "�ϴ�����");
//szUpdated_successfully= iniMyFile.ReadString("InformationLibrary", "Updated successfully", "�����ɹ�");
//szUpdate_failed= iniMyFile.ReadString("InformationLibrary", "Update failed", "����ʧ��");
//szPassword_error= iniMyFile.ReadString("InformationLibrary", "Password error", "�������");
//szUpdate= iniMyFile.ReadString("InformationLibrary", "Update", "����");
//szUpload= iniMyFile.ReadString("InformationLibrary", "Upload", "�ϴ�");
//szRemoveUDisk= iniMyFile.ReadString("InformationLibrary", "Remove the U disk", "�Ƴ�U��");
//szFont= iniMyFile.ReadString("InformationLibrary", "InformationFont:", "����");
//finally
//iniMyFile.Free;
//}
//
//if szSceenPara = ""  szSceenPara = " ";
//if szPlsProgram = ""  szPlsProgram = " ";
//if szScreenNo = ""  szScreenNo = " ";
//if szBaudate = ""  szBaudate = " ";
//if szSpecification = ""  szSpecification = " ";
//if szMemory_error = ""  szMemory_error = " ";
//if szParameter_outof_range = ""  szParameter_outof_range = " ";
//if szUnauthorized_access = ""  szUnauthorized_access = " ";
//if szStart_the_program = ""  szStart_the_program = " ";
//if szDevice_Access = ""  szDevice_Access = " ";
//if szUnknown_Disk = ""  szUnknown_Disk = " ";
//if szNo_data = ""  szNo_data = " ";
//if szData_error = ""  szData_error = " ";
//if szUpload_successful = ""  szUpload_successful = " ";
//if szRemove_the_disk = ""  szRemove_the_disk = " ";
//if szRemove_devices = ""  szRemove_devices = " ";
//if szUnknown_device = ""  szUnknown_device = " ";
//if szPower_overload = ""  szPower_overload = " ";
//if szUpload_error = ""  szUpload_error = " ";
//if szUpdated_successfully = ""  szUpdated_successfully = " ";
//if szUpdate_failed = ""  szUpdate_failed = " ";
//if szPassword_error = ""  szPassword_error = " ";
//if szUpdate = ""  szUpdate = " ";
//if szUpload = ""  szUpload = " ";
//if szRemoveUDisk = ""  szRemoveUDisk = " ";
//if szFont = ""  szFont = " ";
//
//Controller_obj= GetControllerObject(g_Controller_Supary,
//nControlType, nProtocolVer);
//nTempleCount= Controller_obj.I["Screen_Msg_Count"];
//
//szSendBuf= (char)(SEND_FILE_TYPE_INFORMATION);
//szSendbuf= szSendbuf + (char)(0) + (char)(0) + (char)(0) + (char)(0);
//szSendbuf= szSendbuf + (char)(nTempleCount and 0xFF) + (char)((nTempleCount shr 8) and 0xFF);
//nCurAddress= Length(szSendbuf) + 4 * nTempleCount;
//SetLength(szSendbuf, nCurAddress);
//
//nPageSize= 0;
//nDataLength= 0;
//nDataOffest= 0;
//for I = 1 to nTempleCount do
//	{
//	case I of
//	1: szcurText= szSceenPara;
//2: szcurText = szPlsProgram;
//3: szcurText = szScreenNo;
//4: szcurText = szBaudate;
//5: szcurText = szSpecification;
//
//6: szcurText = szMemory_error;
//7: szcurText = szParameter_outof_range;
//8: szcurText = szUnauthorized_access;
//9: szcurText = szStart_the_program;
//10: szcurText = szDevice_Access;
//11: szcurText = szUnknown_Disk;
//12: szcurText = szNo_data;
//13: szcurText = szData_error;
//
//14: szcurText = szUpload_successful;
//15: szcurText = szRemove_the_disk;
//16: szcurText = szRemove_devices;
//17: szcurText = szUnknown_device;
//18: szcurText = szPower_overload;
//19: szcurText = szUpload_error;
//20: szcurText = szUpdated_successfully;
//21: szcurText = szUpdate_failed;
//22: szcurText = szPassword_error;
//23: szcurText = szUpdate;
//24: szcurText = szUpload;
//25: szcurText = szRemoveUDisk;
//}
//tmpBmp= TBitmap.Create;
//desBmp= TBitmap.Create;
//tmpBmp.Canvas.Lock;
//desBmp.Canvas.Lock;
//
//tmpBmp.Canvas.Brush.Color = clBlack;
//tmpBmp.PixelFormat = pf4bit;
//tmpBmp.Canvas.Font.Name = szFont;
//tmpBmp.Canvas.Font.Size = 12;
//tmpBmp.Canvas.Font.Color = clRed;
//nTextWidth= WideCanvasTextWidth(tmpBmp.Canvas, szcurText);
//nTextHeight= WideCanvasTextHeight(tmpBmp.Canvas, szcurText);
//tmpBmp.Width = nTextWidth;
//tmpBmp.Height = nTextHeight;
//WideCanvasTextOut(tmpBmp.Canvas, 0, 0, szcurText);
//
//try
//	if tmpBmp.Width > SCREEN_MESSAGE_BMP_MAXWIDTH 
//		nRealWidth = SCREEN_MESSAGE_BMP_MAXWIDTH
//	else
//		nRealWidth = tmpBmp.Width;
//if tmpBmp.Height > SCREEN_MESSAGE_BMP_MAXHEIGHT 
//	desBmp.Height = SCREEN_MESSAGE_BMP_MAXHEIGHT
//else
//	desBmp.Height = tmpBmp.Height;
//if nRealWidth mod 8 != 0 
//	nAllWidth = nRealWidth + (8 - nRealWidth mod 8)
//else
//	nAllWidth = nRealWidth;
//desBmp.Width = nAllWidth;
//desBmp.Canvas.Brush.Color = clBlack;
//desBmp.Canvas.FillRect(Rect(0, 0, desBmp.Width, desBmp.Height));
//desBmp.Canvas.CopyRect(Rect((desBmp.Width - tmpBmp.Width), 0, desBmp.Width, tmpBmp.Height)
//	, tmpBmp.Canvas, Rect(0, 0, tmpBmp.Width, tmpBmp.Height));
//szSendbuf[7 + (I - 1) * 4 + 1] = (char)(nDataOffest and 0xFF);
//szSendbuf[7 + (I - 1) * 4 + 2] = (char)((nDataOffest shr 8) and 0xFF);
//szSendbuf[7 + (I - 1) * 4 + 3] = (char)((nDataOffest shr 16) and 0xFF);
//szSendbuf[7 + (I - 1) * 4 + 4] = (char)((nDataOffest shr 24) and 0xFF);
//
//nPageSize= GetPageSize(desBmp.Width, desBmp.Height, 1); //��ģֻת������ɫ�ġ�
//nDataOffest= nDataOffest + nPageSize + 3;
//szSendbuf= szSendbuf + (char)(nAllWidth div 8) + (char)(nAllWidth) + (char)(desBmp.Height);
//SetLength(sztmpBuf, nPageSize);
//Inc(nCurAddress);
//
//TranCanvToInfo(desBmp, @sztmpBuf[1], 0, desBmp.Width
//, desBmp.Height, 1, 1, 8, 1, bInvalidData);
//szSendbuf= szSendbuf + sztmpBuf;
//finally
//	tmpBmp.Canvas.UnLock;
//desBmp.Canvas.UnLock;
//FreeAndNil(tmpBmp);
//FreeAndNil(desBmp);
//}
//}
//nDataLength= Length(szSendbuf) - 5; //��ȥ�ļ����ͺ��ĸ��ֽڵ��ļ����ȡ�
//szSendbuf[2] = (char)(nDataLength and 0xFF);
//szSendbuf[3] = (char)((nDataLength shr 8) and 0xFF);
//szSendbuf[4] = (char)((nDataLength shr 16) and 0xFF);
//szSendbuf[5] = (char)((nDataLength shr 24) and 0xFF);
//wCRCCheck= 0;
//GetCRCCheck(@szSendBuf[1], Length(szSendBuf), wCRCCheck); //�õ�������У��ֵwPhy1Check
//szSendBuf= szSendBuf + (char)(wCRCCheck and 0xFF) + (char)((wCRCCheck shr 8) and 0xFF);
//
//Result= szSendbuf;
//}
//
//function GetMAXMovieExtractFrameCount(nLeft, nWidth, nHeight, nScreenType, nPixType: Cardinal) : Cardinal;
//var
//	nArea_Area : Cardinal;
//iLeftBit, iRightBit: Cardinal;
//nAllWidth, nDimensions, nPageSize: Cardinal;
//{
//	if ((nLeft + nWidth) mod nPixType != 0) 
//		iRightBit = nPixType - ((nLeft + nWidth) mod nPixType); //�ұ���ʼ�ֽڵĶ���λ��
//iLeftBit= nLeft mod nPixType; //�����ʼ�ֽڵĶ���λ��
//nAllWidth= iLeftBit + nWidth + iRightBit;
//nDimensions= (nAllWidth * nHeight);
//nPageSize= (nDimensions div 8) * nScreenType + 17; //17���ֽ�Ϊ����������������������ݡ�
//Result= MOVIE_AREA_SINGLE_FILE_MAX_LENGTH div nPageSize;
//}
//
//function GetControlDisplayModeInfo(nDisplayMode: Cardinal;
//nProtocolVer: Cardinal; nRtnReq: Byte) : string; //�趨��ʾ����ʾģʽ����
//var
//	nData : Byte;
//{
//	case nDisplayMode of
//	0: nData= 0 + 0 shl 1;
//1: nData = 1 + 0 shl 1;
//2: nData = 0 + 1 shl 1;
//3: nData = 1 + 1 shl 1;
//}
//Result= (char)(0xA2) + (char)(0x15) + (char)(0x06) + (char)(0)
//+ (char)(nData and 0xFF)
//+ (char)(0xFF) + (char)(0xFF) + (char)(0xFF) + (char)(0xFF) + (char)(0xFF);
//	if nProtocolVer = PROTOCOLVER_FIFTH_CONTROL 
//		Result = (char)(nRtnReq) + Result;
//	}

string MakeDeleteDynamicAreas(string szDelAreaInfo, DWORD &nSendLength)
{
	string Result;

	Result += (char)(1);
	Result += (char)((BYTE)167);
	Result += (char)((BYTE)1);
	Result += (char)(0);
	Result += (char)(0);
	Result += szDelAreaInfo;
	nSendLength = Result.size();

	return Result;
}

string MakeDeleteDynamicAreaPages(DWORD nDYAreaID, string szDelPageInfo, DWORD &nSendLength)
{
	string Result;
	Result += (char)(1);
	Result += (char)((BYTE)167);
	Result += (char)(3);
	Result += (char)(0);
	Result += (char)(0);
	Result += (char)(nDYAreaID);
	Result += szDelPageInfo;
	
	nSendLength = Result.size();

	return Result;
}