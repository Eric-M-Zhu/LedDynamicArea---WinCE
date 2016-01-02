#pragma once

#include "MyDataType.h"

#define WM_SENDSTATUS (WM_USER + 160)
#define WM_MODIFY_PING_BAUD (WM_USER + 131)

//------------------------------------------------------------------------------
// GetAckOrNAck�ж���Ack����NAck  ;����ֵ��0��NAck��1��Ack��2����������

//����˵����szBuf:���յ���Ϣ��
//------------------------------------------------------------------------------
DWORD GetAckOrNAck(tagstruct_PHY1Header srt_PHY1Header, DWORD nSendCmd, string szReadBuf,
	bool &bNeedReSend);

//------------------------------------------------------------------------------
// SendScreenInfo������ʾ����Ϣ����ʾ��
//����˵����
//nLangueID������ID��
//Screen_ja:��ʾ���б�
//nScreenOrd:��ʾ�����ļ��б��е���ţ�
//nSendMode:ͨѶģʽ��0�����ڣ�1��gprs��2�����ڡ�
//srt_PHY1Header:�����ṹ
//nSendCmd:�������
//pMessageStr����ʾ��Ϣ��
//pSendBuf:��������ָ��
//nSendLength���������ݳ���
//hdl:������Ϣ���
//pReadBuf���ӿ�������ȡ����Ϣָ�룻ֻ�ж�ȡ������ò�������Ч
//nReadLength���ӿ�������ȡ����Ϣ���ȣ�ֻ�ж�ȡ������ò�������Ч
//------------------------------------------------------------------------------
void FreeList(list<DWORD> lstSendInfo);

//���ز�ͬ״̬�µ�NAck����״̬��Ϣ
string GetNAckMessageInfo(DWORD nScreenOrd, Json::Value Screen_ja, string szSendMessage, DWORD nNAckOrd);

//nSendFileTypeΪҪ���͵��ļ����ͣ�û���ļ�����ʱ���ò���Ϊ0xFF
DWORD CreateSendThreadList(DWORD nSingleOrMulti, DWORD nIndex, DWORD nScreenOrd, HANDLE hdlResultHandle, PtagSendThread pSendThread,
	Json::Value Screen_ja, DWORD nSendMode, tagstruct_PHY1Header srt_PHY1Header, DWORD nSendCmd, BYTE nSendFileType, string wdszMessageStr,
	string szSendbuf, DWORD nSendLength, list<DWORD> &lstSendProgram, HANDLE hdl, bool bReadBufSaveAs, string szReadFileName);