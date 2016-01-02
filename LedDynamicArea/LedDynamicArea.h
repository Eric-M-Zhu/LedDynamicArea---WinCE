#ifndef _LEDDYNAMICAREA_H
#define _LEDDYNAMICAREA_H

//#ifdef __cplusplus
extern "C" {
//#endif // __cplusplus

#ifdef _USRDLL
#define LEDDYNAMICAREA_LIB_API __declspec(dllexport)
#else
#define LEDDYNAMICAREA_LIB_API __declspec(dllimport)
#endif

	// ����������
	typedef enum
	{
		BX_5E1	=	0x0154,
		BX_5E2	=	0x0254,
		BX_5E3	=	0x0354,
		BX_5Q0P	=	0x1056,
		BX_5Q1P	=	0x1156,
		BX_5Q2P	=	0x1256,
	} ControllerType;

	#define	FRAME_SINGLE_COLOR_COUNT	23	// ��ɫ�߿�ͼƬ����
	#define	FRAME_MULI_COLOR_COUNT		47	// ��ɫ�߿�ͼƬ����

	// ͨѶģʽ
	typedef enum
	{
		SEND_MODE_SERIALPORT	=	0,
		SEND_MODE_NETWORK		=	2,
		SEND_MODE_Server_2G		=	5,
		SEND_MODE_Server_3G		=	6,
		SEND_MODE_SAVEFILE		=	7,
	} CommunicationMode;

	// ��̬��������ģʽ
	typedef enum
	{
		RUN_MODE_CYCLE_SHOW					=	0, //��̬������ѭ����ʾ��
		RUN_MODE_SHOW_LAST_PAGE				=	1, //��̬��������ʾ��ɺ�ֹ��ʾ���һҳ���ݣ�
		RUN_MODE_SHOW_CYCLE_WAITOUT_NOSHOW	=	2, //��̬������ѭ����ʾ�������趨ʱ���������δ����ʱ������ʾ��
		RUN_MODE_SHOW_ORDERPLAYED_NOSHOW	=	4, //��̬������˳����ʾ����ʾ�����һҳ��Ͳ�����ʾ
	} DynamicAreaRunMode;

	// ����״̬���붨��
	#define RETURN_NOERROR								0    // û�д���
	#define RETURN_ERROR_NOFIND_DYNAMIC_AREA			0xE1 // û���ҵ���Ч�Ķ�̬����
	#define RETURN_ERROR_NOFIND_DYNAMIC_AREA_FILE_ORD	0xE2 // ��ָ���Ķ�̬����û���ҵ�ָ�����ļ����
	#define RETURN_ERROR_NOFIND_DYNAMIC_AREA_PAGE_ORD	0xE3 // ��ָ���Ķ�̬����û���ҵ�ָ����ҳ���
	#define RETURN_ERROR_NOSUPPORT_FILETYPE				0xE4 // ��֧�ָ��ļ�����
	#define RETURN_ERROR_RA_SCREENNO					0xF8 // �Ѿ��и���ʾ����Ϣ. ��Ҫ�����趨����DeleteScreenɾ������ʾ�������
	#define RETURN_ERROR_NOFIND_AREA					0xFA // û���ҵ���Ч����ʾ����. ����ʹ��AddScreenProgramBmpTextArea���������Ϣ
	#define RETURN_ERROR_NOFIND_SCREENNO				0xFC // ϵͳ��û�в��ҵ�����ʾ��. ����ʹ��AddScreen���������ʾ��
	#define RETURN_ERROR_NOW_SENDING					0xFD // ϵͳ�����������ʾ��ͨѶ. ���Ժ���ͨѶ
	#define RETURN_ERROR_OTHER							0xFF // ��������

	/*LEDDYNAMICAREA_LIB_API int __stdcall Initialize();
	LEDDYNAMICAREA_LIB_API int __stdcall Uninitialize();
	LEDDYNAMICAREA_LIB_API int __stdcall AddScreen_Dynamic(int nControlType, int nScreenNo, int nSendMode,
		int nWidth, int nHeight, int nScreenType, int nPixelMode, const char *pCom, int nBaud, const char *pSocketIP, int nSocketPort,
		int nServerMode, const char *pBarcode, const char *pNetworkID, const char *pServerIP, int nServerPort,
		const char *pServerAccessUser, const char *pServerAccessPassword, const char *pCommandDataFile);
	LEDDYNAMICAREA_LIB_API int __stdcall AddScreenDynamicArea(int nScreenNo, int nDYAreaID, int nRunMode, int nTimeOut, int nAllProRelate,
		const char *pProRelateList, int nPlayPriority, int nAreaX, int nAreaY, int nAreaWidth, int nAreaHeight,
		int nAreaFMode, int nAreaFLine, int nAreaFColor, int nAreaFStunt, int nAreaFRunSpeed, int nAreaFMoveStep);
	LEDDYNAMICAREA_LIB_API int __stdcall AddScreenDynamicAreaText(int nScreenNo, int nDYAreaID,
		const char *pText, int nShowSingle, const char *pFontName, int nFontSize,
		int nBold, int nFontColor, int nStunt, int nRunSpeed, int nShowTime);
	LEDDYNAMICAREA_LIB_API int __stdcall AddScreenDynamicAreaFile(int nScreenNo, int nDYAreaID,
		const char *pFileName, int nShowSingle, const char *pFontName, int nFontSize, int nBold, int nFontColor,
		int nStunt, int nRunSpeed, int nShowTime);
	LEDDYNAMICAREA_LIB_API int __stdcall DeleteScreen_Dynamic(int nScreenNo);
	LEDDYNAMICAREA_LIB_API int __stdcall DeleteScreenDynamicArea(int nScreenNo, int nDYAreaID);
	LEDDYNAMICAREA_LIB_API int __stdcall DeleteScreenDynamicAreaFile(int nScreenNo, int nDYAreaID, int nFileOrd);

	LEDDYNAMICAREA_LIB_API int __stdcall SendDynamicAreaInfoCommand(int nScreenNo, int nDYAreaID);
	LEDDYNAMICAREA_LIB_API int __stdcall SendDeleteDynamicAreasCommand(int nScreenNo, int nDelAllDYArea, char *pDYAreaIDList);
	LEDDYNAMICAREA_LIB_API int __stdcall SendUpdateDynamicAreaPageInfoCommand(int nScreenNo, int nDYAreaID, int nFileOrd, int nPageOrd);
	LEDDYNAMICAREA_LIB_API int __stdcall SendDeleteDynamicAreaPageCommand(int nScreenNo, int nDYAreaID, char *pDYAreaPageOrdList);
	LEDDYNAMICAREA_LIB_API int __stdcall StartServer(int nSendMode, char *pServerIP, int nServerPort);
	LEDDYNAMICAREA_LIB_API int __stdcall StopServer(int nSendMode);*/


#undef LEDDYNAMICAREA_LIB_API

//#ifdef __cplusplus
}
//#endif // __cplusplus

#endif // _LEDDYNAMICAREA_H


