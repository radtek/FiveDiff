
#pragma once
//#include <stdafx.h>
#include "Includes_app.h"
class CCommonFunc
{
public:
	CCommonFunc();
	~CCommonFunc();
	bool GetFriday();													//�жϵ����Ƿ�����
	//void SaveMaintenanceParas(sMaintain * temp_sMaintain);     				//���汣����ز���

	//�������
	//void RepeatTest(HWND hDlg, uchar* en_repeat, sample_info* CurSample);     	//���²���

	//���ݴ������
	inline double Fabs(double Item);		//ȡ�Ǹ���
	//void IsBlocking_RBC(HWND, sample_info*);

	//����ͨ�����
	void SendSysPara(void);		//��DSP���͵������������
private:

};
