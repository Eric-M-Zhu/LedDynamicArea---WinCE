#pragma once

//string GetPingCommandInfo(DWORD nProtocolVer, BYTE nRtnReq); //Ping���
//string GetReviseTimeInfo(DWORD nYear, DWORD nMonth, DWORD nDay, DWORD nHour, DWORD nMinute, DWORD nSecond, DWORD nWeek,
//	DWORD nProtocolVer, BYTE nRtnReq); //У��ʱ������;nWeek:��һΪ1������Ϊ7
//string GetStartFileFlagInfo(DWORD nProtocolVer, BYTE nRtnReq); //���Ͷ��Ŀ��ʼ��־��Ϣ��
//string GetEndFileFlagInfo(DWORD nProtocolVer, BYTE nRtnReq); //���Ͷ��Ŀ������־��Ϣ
//																			 //nSendCmd�������飻nFileType��Ҫ��ȡ���ļ����ͣ�$FF:��ȡ�����ļ�����
//string GetReadDir(DWORD nSendCmd, DWORD nFileType,
//	DWORD nProtocolVer, DWORD nMaxReadDir, BYTE nRtnReq); //��ȡĿ¼
//string GetMemoryVolume(DWORD nProtocolVer, BYTE nRtnReq); //��ѯ�ļ�ϵͳ������
//string GetDeleteProgramFile(list<DWORD> &SendProgramList, list<DWORD> QueryProgramList,
//	DWORD &nDeleteCount, DWORD &nDeleteSectors, DWORD &nValidProgramSectors,
//	DWORD nProtocolVer, BYTE nRtnReq); //�õ���ǰҪɾ�����ļ��б�
//string DeleteAllProgramFiles(DWORD nProtocolVer, BYTE nRtnReq);
//string GetFormatInfo(DWORD nProtocolVer, BYTE nRtnReq); //��ʽ������
//string GetDeleteAllProgram(DWORD nProtocolVer, BYTE nRtnReq); //ɾ�����н�Ŀ��Ϣ��
//string GetPowerONOFF(BYTE nPowerStatus, DWORD nProtocolVer, BYTE nRtnReq); //ǿ�ƿ��ػ�������Ϣ
//string GetTimerONOFFInfo(Json::Value Screen_ja, DWORD nScreenOrd, DWORD nProtocolVer, BYTE nRtnReq); //��ʱ���ػ���Ϣ
//string GetUnTimerONOFFInfo(DWORD nProtocolVer, BYTE nRtnReq); //ȡ����ʱ���ػ���Ϣ
//string GetAdjustLightInfo(Json::Value Screen_ja, DWORD nScreenOrd, DWORD nProtocolVer, BYTE nRtnReq); //������Ϣ
//string GetReadControlID(DWORD nProtocolVer, BYTE nRtnReq); //��ȡ���ƿ�ID����
//string GetReadCopyrightInfo(DWORD nProtocolVer, BYTE nRtnReq); //��ȡ���ƿ���Ȩ��Ϣ
//string GetDisplayOptimization(DWORD nScanTime, DWORD nProtocolVer, BYTE nRtnReq); //�õ��趨��CPU�ܹ����ƿ���ʾ�Ż���Ϣ��
//string GetScreenLockScreenStatusInfo(BYTE nLock_Status, BYTE nNonvolatile, DWORD nProtocolVer, BYTE nRtnReq); //nLock_Status:0:������1:������nNonvolatile:0:���粻���棻1:���籣�棻
//string GetScreenLockProgramStatusInfo(string szProgramName, BYTE nLock_Status, BYTE nNonvolatile,
//	DWORD nProtocolVer, BYTE nRtnReq); //szProgramName:��Ŀ���ƣ�nLock_Status:0:������1:������nNonvolatile:0:���粻���棻1:���籣�棻
//string GetReadFile(DWORD nSendCmd, string szFileName, DWORD nProtocolVer, BYTE nRtnReq); //��ȡ�ļ���
//string GetReadScreenStatusInfo(DWORD nProtocolVer, BYTE nRtnReq); //��ȡ������״̬
//string GetSystemResetInfo(DWORD nProtocolVer, BYTE nRtnReq); //ϵͳ��λ����
//
//string GetSetPasswordInfo(string szOldPassword, string szNewPassword, DWORD nProtocolVer, BYTE nRtnReq); //�趨����������
//string GetDeletePasswordInfo(Json::Value Screen_ja, DWORD nScreenOrd, DWORD nProtocolVer, BYTE nRtnReq); //�������������
//
//string GetControlDelayStartSecondInfo(DWORD nSecond,
//	DWORD nProtocolVer, BYTE nRtnReq); //ת��������ʱ����
//string GetControlDisplayModeInfo(DWORD nDisplayMode,
//	DWORD nProtocolVer, BYTE nRtnReq); //�趨��ʾ����ʾģʽ����
//
//string GetControlButtonModeInfo(BYTE nMode,
//	DWORD nProtocolVer, BYTE nRtnReq);
//string GetScreenLOGOInfo(Json::Value Screen_ja, DWORD nScreenOrd, DWORD &nSendLength,
//	DWORD nProtocolVer, BYTE nRtnReq);
//string GetDleteScreenLOGOInfo(string szLOGOFileNamde,
//	DWORD nProtocolVer, BYTE nRtnReq);
//string GetScreenParameterInfo(Json::Value Screen_ja, int nScreenOrd, BYTE ntmpBXCEColor);
//string GetScanData(DWORD nControlType, ptagScreenFlowItem pScreenFlowItem, DWORD nIndex); //�õ�ɨ�����õĲ�����Ϣ
//void GetReadFileDirList(string szReadBuf, list<DWORD> QueryProgramList);
//string GetScreenMessage(DWORD nControlType);
//
//string GetFirmwareFormatInfo(string szFirmwareName);
//string GetFirmwareActivateInf(string szFirmwareFile,
//	DWORD nProtocolVer, BYTE nRtnReq); //���������������򣻸��ͻ�ֻ��һ���������������������ƹ̶�Ϊ"F001"��ԭ�����ƹ̶�Ϊ"F000"
//string GetQueryFirmwareStatus(DWORD nProtocolVer, BYTE nRtnReq); //��ѯ��ǰFirmware״̬
//string GetFormatExternalFlash(DWORD nProtocolVer, BYTE nRtnReq);
//string SetScreenIPAddressInfo(Json::Value Screen_ja, int nScreenOrd,
//	DWORD nProtocolVer, BYTE nRtnReq,
//	string szIP, string szSubMask, string szGateWay,
//	DWORD nPort, DWORD nServerMode, DWORD nServerPort, DWORD nHeartBeatInterval,
//	string szServerIP, string szServerAccessPassword, string szNetID,
//	bool bWildCardsSend, string szMacInfo);
//string SetScreenNetMACInfo(Json::Value Screen_ja, int nScreenOrd,
//	DWORD nProtocolVer, BYTE nRtnReq);
//
//string GetReadScreenTCPIPInfo(DWORD nProtocolVer, BYTE nRtnReq);
//string GetTransStatus(DWORD nProtocolVer, BYTE nRtnReq);
//bool GetTransStatusInfo(string szReadBuf, DWORD nReadLength, BYTE nTransRW,
//	string &szTransFileName, string &szTransFileCrc, DWORD &nTransFileOffset);
SYSTEMTIME GetVersionDateTime(string szFirmWareVersion);
//SYSTEMTIME GetVersionDateTimeFifthProtocol(string szFirmWareVersion);
//
//DWORD GetAllSendProgramSectors(list<DWORD> &SendProgramList);
////void Bublerank(var a : array of string; var b : array of Cardinal; maxtomin: boolean); //ð���㷨��ʱ�����򿪣�MaxtoMin=True���Ӹߵ��ף�False���ӵ͵���
//string AutoGetUserMAC(SYSTEMTIME dtDateTime);
DWORD GetControlStuntRealityRunSpeed(DWORD nWidth, DWORD nHeight, DWORD nScreenColor, DWORD nStuntIndex, DWORD nRunSpeed, DWORD &nDefaultRunSpeed);
DWORD GetControlFrameStuntRealityRunSpeed(DWORD nWidth, DWORD nHeight, DWORD nScreenColor, DWORD nStuntIndex, DWORD nRunSpeed, DWORD &nDefaultRunSpeed);
//DWORD GetControlStuntDefaultRunSpeed(DWORD nControlType, DWORD nWidth, DWORD nHeight, DWORD nScreenColor); //���ݿ��ƿ��ͺš���������Ĭ���ؼ��������ٶȵȼ�
//DWORD GetControlFrameStuntDefaultRunSpeed(DWORD nWidth, DWORD nHeight, DWORD nScreenColor); //���ݿ��ƿ��ͺš����������߿�Ĭ���ؼ��������ٶȵȼ�
//tagServerModeLookUpRecord GetServerModeLookUp(string szReadInfo, DWORD nReadLength);
////nFileType���ļ�����;
//// nControlType�����������ͣ�
//// szFirmwareVersion:�������汾��4λ�ַ�����
//// szFirmwareDatetime�������޸����ڣ�19λ�ַ�����
////szFilrmware:���ؿ����������ļ�������ʽ��F***��
//// szFirmwareName: ���ؿ�������������Դ�ļ�����
//
//DWORD GetMAXMovieExtractFrameCount(DWORD nLeft, DWORD nWidth, DWORD nHeight, DWORD nScreenType, DWORD nPixType);
//
string MakeDeleteDynamicAreas(string szDelAreaInfo, DWORD &nSendLength);
string MakeDeleteDynamicAreaPages(DWORD nDYAreaID, string szDelPageInfo, DWORD &nSendLength);
