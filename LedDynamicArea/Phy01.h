#pragma once

#include "MyDataType.h"

void GetDecipheringData(tagstruct_PHY1Header_5th srt_PHY1Header, DWORD nEncryptionLength,
	string szData, DWORD nLength, string &szDecipheringData); //����CRC16��g_aryCRC16Byte�����ָ��nEncryptionLength�����ܳ����ݽ���ָ���������ݣ�Ŀǰ��ʵ������㷨һ�¡�
string GetUSBUserEncryption(string szdef_encryption, string szuser_encryption); //USB��Phy1�㷢�͵ļ�����Ϣ
string GetXorPassword(string szPassword, string szDef_Password);
void GetPhy1Data(tagstruct_PHY1Header srt_PHY1Header,
	const char *pData, DWORD nLength, string &szPhy1Data); //�õ����������(ת��ǰ)
void GetAllPhy1Data(tagstruct_PHY1Header srt_PHY1Header, const char *pData, DWORD nLength, string &szPhy1AllData); //�õ����������(ת���)
string GetReadPhy1Data(string szReadOriginalData, tagstruct_PHY1Header &srt_ReadPHY1Header, DWORD &nSendError); //������յ�����Ϣ
DWORD GetStrInt(string Str); //���ַ�������ȡ����
DWORD GetRandomValue(int AFrom, int ATo); //��AFrom��ATo֮��ȡһ���������