#pragma once

#include "MyDataType.h"

bool OpenSerialComm(tagSerialComm &tag_SerialComm);
bool CloseSerialComm(tagSerialComm tag_SerialComm);

DWORD SendCommData(tagSerialComm tag_SerialComm, tagstruct_PHY1Header &m_srt_PHY1Header, const char *pSendBuf, DWORD nSendLength,
	tagstruct_PHY1Header &m_srt_ReadPHY1Header, char *pReadBuf, DWORD &nReadLength);

//GetReadInfo:�Ӵ��ڶ�����ʾ����Ϣ��ComPort�����ڿؼ���nSleepValue:���ȴ�ʱ�䣬��λ���룻nSleepUnit����λ�ȴ�ʱ�䣬��λ���룻nReadLength�����������ݳ��ȣ����ض��������ݡ�
string GetReadInfo(HANDLE ComPort, DWORD nSleepValue, DWORD nSleepUnit, DWORD &nReadLength);
string GetSerialPortsInValid(const list<string> &Ports, string &szFirstComName); //�жϴ����Ƿ����������ڣ����������⴮��
void EnumComPorts(list<string> &Ports);