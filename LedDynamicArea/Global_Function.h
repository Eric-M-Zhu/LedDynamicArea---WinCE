#pragma once

//void LanguageUse(TComponent AnObject; int lan_i);
void SaveBinFile(const char *pdata, UINT nDataLen, string szFileName);
//void ClearTransitList(TList &lstTransit);
//�ж���ת���������Ϳ������Ƿ����ߡ�True�����ߣ��������ߡ�
//bool GetTransitScreenStatus(TList lstTransit; UINT ScreenOrd; TSuperArray Screen_Ary);
bool Judge_Scan_File_Detail_Exist(Json::Value ScanObj, string szSmartScanPath, string &szSameScanName);
bool SaveScanData(Json::Value SmartScanFile_root, Json::Value ScanObj,
	string szSmartScanPath, string szcurScanName, string szScanFile);
string Transit_Message(BYTE errid);