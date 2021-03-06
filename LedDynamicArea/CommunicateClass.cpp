#include "stdafx.h"

#include <shlwapi.h>

#include "CommunicateClass.h"
#include "LedDynamicArea.h"
#include "SendCommUnit.h"
#include "SendSocketUnit.h"
#include "TranInfo.h"

extern Json::Value g_Controller_Supary;

CommunicateClass::CommunicateClass(Json::Value Screen_ja, DWORD nScreenOrd, DWORD nSendMode,
	DWORD nSendCmd, tagstruct_PHY1Header srt_PHY1Header,
	string szMessageStr, string szSendBuf,
	DWORD nSendLength, list<DWORD> lstSendProgram, HANDLE hdl, PtagSendThread ptagSendThread)
{
	thrd_ntmpBXCEColor = SCREEN_COLOR_SINGLE;
	thrd_Screen_ja = Screen_ja;
	thrd_nScreenOrd = nScreenOrd;
	thrd_nSendMode = nSendMode;
	thrd_srt_PHY1Header = srt_PHY1Header;
	thrd_nSendCmd = nSendCmd;
	thrd_szMessageStr = szMessageStr;
	thrd_szSendBuf = szSendBuf;
	thrd_nSendLength = nSendLength;
	thrd_hdl = hdl;
	thrd_ptagSendThread = ptagSendThread;

	switch (thrd_nSendMode)
	{
	case SEND_MODE_SERIALPORT:
	case SEND_MODE_NETWORK:
	case SEND_MODE_Server_2G:
	case SEND_MODE_Server_3G:
		SendScreenInfo(thrd_Screen_ja, thrd_nScreenOrd, thrd_nSendMode, COMMUNICATION_RtnReq,
			thrd_nSendCmd, thrd_szMessageStr, lstSendProgram, thrd_szSendBuf, thrd_nSendLength, thrd_hdl, thrd_ptagSendThread, thrd_srt_PHY1Header);
		break;
	}
}


CommunicateClass::~CommunicateClass()
{
}

DWORD CommunicateClass::SendSingleCommand(string szSendBuf, DWORD nSendLength, DWORD nScreenOrd, DWORD nSendMode,
	string szSingleCommandInfo, tagCommunication &tag_Communication, tagstruct_PHY1Header &srt_PHY1Header,
	HANDLE hdl, Json::Value Screen_Supary, BYTE nRtnReq, DWORD &nStatus,
	DWORD &nErrorNumber, tagSendStatus &tmptagSendStatus, string &szReadBuf, DWORD &nReadLength)
{
	string szRequest;
	DWORD nErrSendedTimes, nErrReSendTimes; //已经重新发送次数；
	DWORD /*nAllReadLength, nReadedLength, ntmpDataLength,*/ nResult, nAckOrNAckResult/*, nReadCount*/;
	char tmpReadBuf[4096]; // COMPORT_MAX_READ_LENGTH
	string tmpReadPackageBuf, szCurReadBuf;
	string szMessageStr, szSendFail, szSendSucessed;
	tagstruct_PHY1Header srt_ReadPHY1Header;
	bool bNeedReSend;
	DWORD Result = 0;

	szSendFail = " failed!";
	szSendSucessed = " Successfully!";

	if (nSendMode == SEND_MODE_SERIALPORT)
		nErrReSendTimes = tag_Communication.tag_SerialComm.nErrReSendTimes;
	else if (nSendMode == SEND_MODE_NETWORK)
		nErrReSendTimes = 0;//tag_Communication.tag_Network.nErrReSendTimes;
	//else if (nSendMode == SEND_MODE_GPRS)
	//	nErrReSendTimes = tag_Communication.tag_GPRS.nErrReSendTimes;

	szRequest = szSendBuf;
	nErrSendedTimes = 0;
SingleCommandRequest:
	nReadLength = 0;
	szMessageStr = szSingleCommandInfo + "......"; //正在通讯中
	tmptagSendStatus.nPercentValue = 0;
	tmptagSendStatus.szMessagestr = szMessageStr;
	SendMessage((HWND)hdl, WM_SENDSTATUS, WPARAM(nScreenOrd), (LPARAM)&tmptagSendStatus);

	switch (nSendMode)
	{
	case SEND_MODE_SERIALPORT:
		nResult = SendCommData(tag_Communication.tag_SerialComm, srt_PHY1Header, szRequest.c_str(),
					szRequest.size(), srt_ReadPHY1Header, tmpReadBuf, nReadLength);
		break;
	case SEND_MODE_NETWORK:
		nResult = SendSocketData(tag_Communication.tag_Network, srt_PHY1Header, szRequest.c_str(),
					szRequest.size(), srt_ReadPHY1Header, tmpReadBuf, nReadLength);
		break;
	
	//SEND_MODE_Server_2G, SEND_MODE_Server_3G:
	//	begin
	//		//Frm_Main.FListLock.Enter;
	//		nResult = SendServerSocketData(tag_Communication.tag_Network, srt_PHY1Header, @szRequest[1],
	//				  Length(szRequest), srt_ReadPHY1Header, pChar(tmpReadBuf), nReadLength);
	//	//Frm_Main.FListLock.leave;
	//	end;
	}

	szReadBuf.append(tmpReadBuf, nReadLength);
	nAckOrNAckResult = GetAckOrNAck(srt_ReadPHY1Header, SEND_ACK, szReadBuf, bNeedReSend);
	if ((nAckOrNAckResult != 0) || (nResult != seOK)) //发送错误重新发送信息。
	{
		if ((nErrSendedTimes < nErrReSendTimes) && bNeedReSend) //判断是否达到重发次数
		{
			++nErrSendedTimes;
			goto SingleCommandRequest;
		}
		else
		{
			szMessageStr = szSingleCommandInfo + szSendFail + GetNAckMessageInfo(nScreenOrd, Screen_Supary, "", nAckOrNAckResult);
			tmptagSendStatus.nPercentValue = 0;
			tmptagSendStatus.szMessagestr = szMessageStr;
			Result = nResult;
			nErrorNumber = nAckOrNAckResult;
			SendMessage((HWND)hdl, WM_SENDSTATUS, WPARAM(nScreenOrd), (LPARAM)&tmptagSendStatus);
			return Result;
		}
	}

	szMessageStr = szSingleCommandInfo + szSendSucessed;
	tmptagSendStatus.nPercentValue = 0;
	tmptagSendStatus.szMessagestr = szMessageStr;
	Result = nResult;
	nErrorNumber = nAckOrNAckResult;
	SendMessage((HWND)hdl, WM_SENDSTATUS, WPARAM(nScreenOrd), (LPARAM)&tmptagSendStatus);

	return Result;
}

bool CommunicateClass::InitCommunication(DWORD nSendMode, DWORD nSendCmd, DWORD nBaud, tagCommunication &tag_Communication,
	Json::Value Screen_Obj, string szFileName, tagstruct_PHY1Header &srt_PHY1Header, tagSendStatus &tmptagSendStatus)
{
	Json::Value Controller_obj;
	BYTE nProtocolVer;
	tagSerialComm &tag_SerialComm = tag_Communication.tag_SerialComm;
	tagNetwork &tag_Network = tag_Communication.tag_Network;
	bool Result = false;
	char convertIntString[16];
	WCHAR wszFileName[MAX_PATH];

	Controller_obj = GetControllerObject(g_Controller_Supary, Screen_Obj["Screen_control"].asUInt(), nProtocolVer);
	MultiByteToWideChar(CP_ACP, 0, szFileName.c_str(), -1, wszFileName, MAX_PATH);
	
	switch (nSendMode)
	{
	case SEND_MODE_SERIALPORT:
		if (Controller_obj["Serial_Communication_Mode"] == 1)
		{
			tag_SerialComm.nCommDataBits = 3; //GetPrivateProfileInt(L"Com_RF", L"nComDataBits", 3, wszFileName);
			tag_SerialComm.nCommStopBits = 0; //GetPrivateProfileInt(L"Com_RF", L"nComStopBits", 0, wszFileName);
			tag_SerialComm.nCommParity = 0; //GetPrivateProfileInt(L"Com_RF", L"nComParity", 0, wszFileName);
			tag_SerialComm.nInputSize = 400; //GetPrivateProfileInt(L"Com_RF", L"nInputSize", 400, wszFileName);
			tag_SerialComm.nOutputSize = 400; //GetPrivateProfileInt(L"Com_RF", L"nOutputSize", 400, wszFileName);
			tag_SerialComm.nSendUnit = 128; //GetPrivateProfileInt(L"Com_RF", L"nSendUnit", 128, wszFileName);
			tag_SerialComm.nUnitSleepValue = 0; //GetPrivateProfileInt(L"Com_RF", L"nUnitSleepValue", 0, wszFileName);
			tag_SerialComm.nPackageDataLength = 400; //GetPrivateProfileInt(L"Com_RF", L"DataLen", 400, wszFileName);
			tag_SerialComm.nPackageSleep = 0; //GetPrivateProfileInt(L"Com_RF", L"nPackageSleep", 0, wszFileName);
			tag_SerialComm.nErrReSendTimes = 1; //GetPrivateProfileInt(L"Com_RF", "nErrReSendTimes", 1, wszFileName);
			tag_SerialComm.nReadWaitTimeOut = WAIT_TIMEOUT_REALITY_SERIALPORT; //GetPrivateProfileInt(L"Com_RF", L"nRealityReadWaitTimeOut", WAIT_TIMEOUT_REALITY_SERIALPORT, wszFileName);
			tag_SerialComm.nFrameLenMax = COM_FRAMELENMAX;
			srt_PHY1Header.Datalen = tag_SerialComm.nPackageDataLength;
		}
		else
		{
			tag_SerialComm.nCommDataBits = 3; //GetPrivateProfileInt(L"Com", L"nComDataBits", 3, wszFileName);
			tag_SerialComm.nCommStopBits = 0; //GetPrivateProfileInt(L"Com", L"nComStopBits", 0, wszFileName);
			tag_SerialComm.nCommParity = 0; //GetPrivateProfileInt(L"Com", L"nComParity", 0, wszFileName);
			tag_SerialComm.nInputSize = 4096; //GetPrivateProfileInt(L"Com", L"nInputSize", 4096, wszFileName);
			tag_SerialComm.nOutputSize = 4096; //GetPrivateProfileInt(L"Com", L"nOutputSize", 4096, wszFileName);
			tag_SerialComm.nSendUnit = 128; //GetPrivateProfileInt(L"Com", L"nSendUnit", 128, wszFileName);
			tag_SerialComm.nUnitSleepValue = 0; //GetPrivateProfileInt(L"Com", L"nUnitSleepValue", 0, wszFileName);
			tag_SerialComm.nPackageDataLength = 1024; //GetPrivateProfileInt(L"Com", L"DataLen", 1024, wszFileName);
			tag_SerialComm.nPackageSleep = 0; //GetPrivateProfileInt(L"Com", L"nPackageSleep", 0, wszFileName);
			tag_SerialComm.nErrReSendTimes = 1; //GetPrivateProfileInt(L"Com", L"nErrReSendTimes", 1, wszFileName);
			tag_SerialComm.nReadWaitTimeOut = WAIT_TIMEOUT_REALITY_SERIALPORT; //GetPrivateProfileInt(L"Com", L"nRealityReadWaitTimeOut", WAIT_TIMEOUT_REALITY_SERIALPORT, wszFileName);
			srt_PHY1Header.Datalen = tag_SerialComm.nPackageDataLength;
		}
		if (tag_SerialComm.nReadWaitTimeOut < WAIT_TIMEOUT_REALITY_SERIALPORT)
			tag_SerialComm.nReadWaitTimeOut = Screen_Obj["Screen_RealityReadWaitTimeOut"].asUInt();

		tag_SerialComm.szCommName = "COM"; 
		//tag_SerialComm.szCommName += Screen_Obj["Com_port"].asCString();
		_itoa_s(Screen_Obj["Com_port"].asInt(), convertIntString, 16, 10);
		tag_SerialComm.szCommName.append(convertIntString);
		tag_SerialComm.nCommBaud = nBaud;
		tag_SerialComm.nFrameLenMax = COM_FRAMELENMAX;
		Result = OpenSerialComm(tag_SerialComm);
		break;
	case SEND_MODE_NETWORK:
		tag_Network.nSendUnit = 1400; //iniMyFile.ReadInteger(L"Static_Net", "nSendUnit", 1048);
		tag_Network.nUnitSleepValue = 0; //iniMyFile.ReadInteger(L"Static_Net", "nUnitSleepValue", 0);
		tag_Network.nPackageDataLength = 600; //iniMyFile.ReadInteger(L"Static_Net", "DataLen", 1024);
		tag_Network.nPackageSleep = 0; //iniMyFile.ReadInteger(L"Static_Net", "nPackageSleep", 0);
		tag_Network.nErrReSendTimes = 1; //iniMyFile.ReadInteger(L"Static_Net", "nErrReSendTimes", 1);

		tag_Network.nReadWaitTimeOut = WAIT_TIMEOUT_REALITY_NET; //GetPrivateProfileInt(L"Static_Net", L"nRealityReadWaitTimeOut", WAIT_TIMEOUT_REALITY_NET, wszFileName);

		if (tag_Network.nReadWaitTimeOut < WAIT_TIMEOUT_REALITY_NET)
			tag_Network.nReadWaitTimeOut = 15000; //Screen_Obj.I["Screen_RealityReadWaitTimeOut"];
		/*if (nSendMode == SEND_MODE_WiFi)
		{
			tag_Network.Network_Mode = NET_CONNECT_STATICIP;
			tag_Network.nServerMode = 0;
			tag_Network.szServerMode_ID = "";
			tag_Network.Network_IP = Screen_Obj.S["Screen_WiFi_NetIP"];
			tag_Network.Network_Port = Screen_Obj.I["Screen_WiFi_NetPort"];
		}
		else*/
		{
			tag_Network.Network_Mode = Screen_Obj["Net_ConnnectMode"].asUInt();
			tag_Network.nServerMode = Screen_Obj["Net_ServerMode"].asUInt();
			tag_Network.szServerMode_ID = Screen_Obj["Network_ID"].asCString();
			tag_Network.Network_IP = Screen_Obj["Net_IP"].asCString();
			tag_Network.Network_Port = Screen_Obj["Net_port"].asUInt();
		}
		tag_Network.nFrameLenMax = NET_FRAMELENMAX;
		srt_PHY1Header.Datalen = tag_Network.nPackageDataLength;

		if ((nSendCmd == SEND_ETHERNETSET_IP) || (nSendCmd == SEND_ETHERNETSET_MAC) || (nSendCmd == SEND_READ_IPINFO))
		{
			tag_Network.Network_Mode = NET_CONNECT_DIRECT;
			tag_Network.Network_IP = NET_UDP_BROADCAST;
			tag_Network.nServerMode = 0;
		}
		else if (tag_Network.Network_Mode == NET_CONNECT_DIRECT)
			tag_Network.Network_IP = NET_UDP_BROADCAST;

		if (tag_Network.nServerMode == 0)
		{
			Result = CreateMySocket(tag_Network.Network_Mode, tag_Network.Network_IP, tag_Network.Network_Port, tag_Network.Network_Skt) == seSocket_OK;
		}
		else
			Result = true;
		break;
	//case SEND_MODE_Server_2G:
	//case SEND_MODE_Server_3G:
	//	break;
	//default:
	//	break;
	}

	return Result;
}

bool CommunicateClass::CloseCommunication(DWORD nSendMode, tagCommunication &tag_Communication)
{
	switch (nSendMode)
	{
	case SEND_MODE_SERIALPORT:
		if (tag_Communication.tag_SerialComm.CommPort != INVALID_HANDLE_VALUE)
		{
			CloseHandle(tag_Communication.tag_SerialComm.CommPort);
		}
		break;
	case SEND_MODE_NETWORK:
		if (tag_Communication.tag_Network.nServerMode == 0)
		{
			CloseMySocket(tag_Communication.tag_Network.Network_Skt);
		}
		break;
	}
	return true;
}

DWORD CommunicateClass::SendScreenInfo(Json::Value Screen_Supary, DWORD nScreenOrd, DWORD nSendMode, BYTE nRtnReq,
	DWORD nSendCmd, string wdszMessageStr, list<DWORD> lstSendInfo, string szSendbuf, DWORD nSendLength, HANDLE hdl,
	PtagSendThread ptmptagSendThread, tagstruct_PHY1Header &srt_PHY1Header)
{
	string szCom, szNet_IP;
	string szFileName, szFileCrc;
	//int ntmpSendCmd;
	string tmpSendBuf;
	string tmpProgramBuf; //ÁÙÊ±Éú³ÉµÄµ±Ç°½ÚÄ¿ÎÄ¼þ
	//DWORD ntmpProgramLength; //ÁÙÊ±Éú³ÉÎÄ¼þ½ÚÄ¿³¤¶È
	string tmpReadBuf, tmpReadPackageBuf, szReadBuf, szCurReadBuf;
	//DWORD /*nAllReadLength, nReadedLength, ntmpReadLength,*/ ntmpReadPackageLength, ntmpReadResponseLength;
	string szRequest;
	//DWORD I, N, J;
	//DWORD nSendCount, nReadCount;
	//DWORD ntmpDataLength, nSendedLength;
	//DWORD nCurSendLength;
	//DWORD nLastPackage; //ÊÇ·ñÎª×îºóÒ»°üµÄ±êÖ¾;0:²»ÊÇ×îºóÒ»°ü£»1£ºÊÇ×îºóÒ»°ü¡£
	//DWORD nErrSendedTimes; //ÒÑ¾­ÖØÐÂ·¢ËÍ´ÎÊý£»
	//tagstruct_PHY1Header tmpsrt_PHY1Header/*, srt_ReadPHY1Header*/;
	//DWORD nPercentValue;
	string szMessageStr;
	string tmpMessageStr;
	string szNewcommumication, szConnectFail, szConnectFail_NET, szConnectFail_GP, szSendSucessed
		, szSendSucessed2, szSendFail, szScreenParameterError
		, szScreenControlTypeError, szunCompatibleFirmware;
	string szFirmware_First_Incomp, szFirmware_Second_Incomp, szFirmware_Third_Incomp;
	string szFormatStr, szAllProgramStartFileStr, szAllProgramEndFileStr;
	string szNoParameterInfo;
	string szMemoryOutInfo;
	string szMemoryErrInfo;
	//BYTE ntmpValue1, ntmpValue2;
	DWORD nReadLength;
	string sztmpProgramBuf;
	string sztmpProgramMessageStr, sztmpProgramMessageStr2;
	//PtagSendInfo ptmptagSendInfo;
	//PtagReadDir ptmptagReadDir;
	tagSendStatus tmptagSendStatus;
	fstream fp;
	//DWORD ntmp;
	//DWORD nCurrentBrigtness, nCurrentOnOffStatus, nCurScan, nCurFlow;
	string szSendInfo;
	DWORD nSendInfoLength;
	//DWORD nReadWaitTimeOut;
	//nAckOrNAckResult: Cardinal; //Ack·µ»ØÖµ¡£
	string szDeleteProgramDir;
	//DWORD nDeleteProgramCount/*, nDeleteProgramSectors*/;
	//DWORD nAllSendProgramSectors; //ËùÓÐ·¢ËÍ½ÚÄ¿µÄÉÈÇøÊý¡£
	//DWORD nQueryValidMemoy, nControlRealityMemoySectors;
	string szFirmwareInfo, szFirmwareInfo2;
	//DWORD nFirmwareLength, nFirmwareLength2;

	tagCommunication tag_Communication;
	//BYTE nReadScreenParaStatus;
	//DWORD nReadControllerType;
	/*DWORD nReadWidth, nReadHeight, nReadScreenType,
		nReadBrigtness, nReadOnOffStatus, nReadScan, nReadFlow;*/
	DWORD nErrorNumber;
	DWORD nStatus, nResult;
	//SYSTEMTIME dtReadFirmwareVersion;
	string szReadFirmwareVersion, szDownloadFirmwareVersion;
	SYSTEMTIME dtCompatibleVersion, dtBX4C4E_SingleColor_FIrmwareVersion
		, dtFifthBreakpoint_FIrmwareVersion;
	//DWORD nSendCommand;
	string szCurFirmwareName, szCurFirmwareVersion, szCurFirmwareModiTime,
		szNewFirmwareName, szBX5EFirmwareVersion;
	//BYTE /*nReadBX5EExFIrmwareVersion,*/ nBX5EExFIrmwareVersion;
	Json::Value Controller_obj;
	BYTE nProtocolVer;

	string szReadSendFile;
	DWORD nReadSendAddress;
	BYTE nTransRW;
	string szTransFileName, szTransFileCrc;
	DWORD nTransFileOffset;

	ptmptagSendThread->nSendCmd = nSendCmd;
	nTransRW = TRANS_STATUS_NONE;
	szTransFileName = "";
	szTransFileCrc = "";
	nTransFileOffset = 0;

	szReadSendFile = "";
	nReadSendAddress = 0;
	szSendInfo = szSendbuf;
	nSendInfoLength = nSendLength;
	dtCompatibleVersion = GetVersionDateTime(CUR_COMPATIBLE_FIRMWARE_VERSION);
	dtBX4C4E_SingleColor_FIrmwareVersion = GetVersionDateTime(BX_4C_4E_SINGLECOLOR_FIRMWARE_VERSION);
	dtFifthBreakpoint_FIrmwareVersion = GetVersionDateTime(FIFTH_BREAKPOINT_FIRMWARE_VERSION);
	tmpMessageStr = wdszMessageStr;
	Controller_obj = GetControllerObject(g_Controller_Supary,
						Screen_Supary[nScreenOrd]["Screen_control"].asUInt(), nProtocolVer);

	char szComBuffer[16];
	sprintf_s(szComBuffer, 16, "COM%d", Screen_Supary[nScreenOrd]["Com_port"].asUInt());
	szCom = szComBuffer;
	szNet_IP = Screen_Supary[nScreenOrd]["Net_IP"].asString();

	//char szFormat[256];

	szConnectFail = ("Open the serial port (%s) failed!");
	szConnectFail_NET = ("Connected to the screen(IP: %s) failed!");
	szConnectFail_GP = ("Connected to the screen(GPRS: %s) failed!");
	szunCompatibleFirmware = ("Program version is not compatible with the controller, use the 2010 version of software!");
	szFirmware_First_Incomp = ("Please use the version number like (V ******** 00 ******) the Firmware file to upgrade the controller");
	szFirmware_Second_Incomp = ("Please use the version number like (V ******** 01 ******) the Firmware file to upgrade the controller");
	szFirmware_Third_Incomp = ("Please use the version number like (V ******** 02 ******) the Firmware file to upgrade the controller");

	szSendSucessed = (" Successfully!");
	szSendSucessed2 = (" Completed!");
	szSendFail = (" failed!");
	szNewcommumication = ("Establishing the communication of the controller");
	szScreenParameterError = ("Parameter inconsistency, reload the LED parameters!");
	szScreenControlTypeError = ("Controller type inconsistencies, please re-select the controller model");
	/*sprintf_s(szFormat, sizeof(szFormat), "Begin sending %s of the program data", Screen_Supary[nScreenOrd]["Screen_name"].asCString());
	szAllProgramStartFileStr = szFormat;
	sprintf_s(szFormat, sizeof(szFormat), "Send %s of the program data", Screen_Supary[nScreenOrd]["Screen_name"].asCString());
	szAllProgramEndFileStr = szFormat;
	sprintf_s(szFormat, sizeof(szFormat), "Remove %s of the program data", Screen_Supary[nScreenOrd]["Screen_name"].asCString());
	*/szNoParameterInfo = ("Controller is currently in reset state, reset the parameters of the controller!");
	szMemoryOutInfo = ("The available storage is not enough!");
	szMemoryErrInfo = ("Failed to check the storage volume!");
	//try
	char sysSetupFileName[MAX_PATH];
	//GetModuleFileNameA(NULL, sysSetupFileName, MAX_PATH);
	//
	//char *pFileSpec = strrchr(sysSetupFileName, '\\');
	//if (pFileSpec != NULL)
	//	*pFileSpec = '\0';

	//strcat(sysSetupFileName, "\\SysSetup.ini");

	InitCommunication(nSendMode, nSendCmd, Screen_Supary[nScreenOrd]["Com_baudrate"].asUInt()
		, tag_Communication, Screen_Supary[nScreenOrd]
		, sysSetupFileName, srt_PHY1Header, tmptagSendStatus);
	/*except
		szMessagestr = szNewcommumication + szSendFail;
	nPercentValue = 0;
	tmptagSendStatus.nPercentValue = nPercentValue;
	tmptagSendStatus.szMessagestr = szMessagestr;
	ptmptagSendThread->nSendedStatus = SEND_FAILED;
	ptmptagSendThread->nErrorNumber = nErrorNumber;
	Screen.Cursor = crDefault;
	CloseCommunication(nSendMode, tag_Communication);
	SendMessage(hdl, WM_SENDSTATUS, WPARAM(nScreenOrd), Longint(@tmptagSendStatus));
	exit;
	end;*/

	ptmptagSendThread->nSendCmd = nSendCmd;
	switch (nSendCmd)
	{
	case SEND_DYNAMIC_AREA_INFO:
	case SEND_DELETE_DYNAMIC_AREA:
	case SEND_DYNAMIC_AREA_PAGE:
	case SEND_DELETE_DYNAMIC_AREA_PAGE: //µ¥°ü¡¢ÃüÁîÀà²Ù×÷
		nResult = SendSingleCommand(szSendInfo, szSendInfo.size(), nScreenOrd, nSendMode,
			tmpMessageStr, tag_Communication, srt_PHY1Header,
			hdl, Screen_Supary, nRtnReq, nStatus, nErrorNumber, tmptagSendStatus, szReadBuf, nReadLength);

		if ((nErrorNumber != 0) || (nResult != seOK))
		{
			ptmptagSendThread->nSendedStatus = SEND_FAILED;
			ptmptagSendThread->nErrorNumber = nErrorNumber;
			ptmptagSendThread->szReadBuf = szReadBuf;
			ptmptagSendThread->nReadLength = szReadBuf.size();
			CloseCommunication(nSendMode, tag_Communication);
			//SendMessage(hdl, WM_SENDSTATUS, WPARAM(nScreenOrd), Longint(@tmptagSendStatus));
			return 0;
		}

		ptmptagSendThread->nSendedStatus = SEND_SUCESSED;
		ptmptagSendThread->nErrorNumber = nErrorNumber;
		ptmptagSendThread->szReadBuf = szReadBuf;
		ptmptagSendThread->nReadLength = szReadBuf.size();
		CloseCommunication(nSendMode, tag_Communication);
		tmptagSendStatus.nPercentValue = 100;
		//SendMessage(hdl, WM_SENDSTATUS, WPARAM(nScreenOrd), Longint(@tmptagSendStatus));
		return 0;
	}

	return 0;
}

void CommunicateClass::ReSetstruct_PHY1Header(tagstruct_PHY1Header &srt_PHY1Header, tagstruct_PHY1Header Source_srt_PHY1Header)
{
	tagstruct_PHY1Header tmpsrt_PHY1Header;
	memcpy(&tmpsrt_PHY1Header, &Source_srt_PHY1Header, sizeof(tagstruct_PHY1Header));
	tmpsrt_PHY1Header.DeviceType = srt_PHY1Header.DeviceType;
	tmpsrt_PHY1Header.ProtocolVer = srt_PHY1Header.ProtocolVer;
	memcpy(&srt_PHY1Header, &Source_srt_PHY1Header, sizeof(tagstruct_PHY1Header));
}
