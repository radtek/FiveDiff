/*************************************************
Copyright (C), SINNOWA. Co., Ltd.
File name: 	Includes_app.h
Version:	1.0	Date: 2016-02-25
Description: 	ͷ�ļ�����ͷ�ļ�
Others:       	// �������ݵ�˵��
*************************************************/
#ifndef _INCLUDES_APP_H_
#define _INCLUDES_APP_H_
//=====================================//
//============����ϵͳ�е�h�ļ�====================//
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>       //20140630
#include <stdlib.h>
//=======================================//

#include "StdAfx.h"
#include "afxdialogex.h"
#include "locale.h"
//=====================================//
#include "dev_info.h"
#include "usbio.h"
#include "StructDefine.h"     //�Զ���ṹ��
#include "Global_def.h"       //ȫ�ֱ���
#include "Database.h"         //���ݿ������������
#include "DataProcess.h"      //���ݷ���������������
#include "Spi.h"              //usb��dspͨ�Ų���
#include "RS232.h"            //RS232ͨ�Ż�������
//#include "CommonOtherFuncs.h"   //������ͨ�Ĺ�������
#include "DataTransmission.h"    //���ݴ����������
#include "picture.h"
#include "StructDefine.h"
#include "CommonFunc.h"

#include<atlconv.h>//T2A W2A A2W

#include "Resource.h"
//#include "AutocleanView.h"
//#include "AutoMaintenanceSetView.h"
//#include "AutoSamplingSetView.h"
//#include "BCGPChartExample.h"
#include "BCGPChartExampleDoc.h"
#include "BCGPChartExampleView.h"
//#include "CalibrationView.h"
//#include "ChangeAllReagentView.h"
//#include "ChangeReagentView.h"
//#include "CleantankView.h"
//#include "CleanView.h"
//#include "CMyBCGPHeaderCtrl.h"
//#include "CMyBCGPListCtrl.h"
//#include "CompanySetView.h"
//#include "ConcentratecleanView.h"
//#include "ConfigSetView.h"
//#include "CorrectParaSetView.h"
//#include "DevelopmentSetView.h"
//#include "DoctorInfoView.h"
//#include "EmptyView.h"
//#include "FaultstatisticsView.h"
//#include "GraphicdebuugView.h"
//#include "HeaderCtrl.h"
//#include "HgbtestView.h"
//#include "ListCtrl.h"
//#include "LMNESetView.h"
//#include "LmnetestView.h"
//#include "LocationquantitativeView.h"
//#include "LoginDlg.h"
#include "LogProcedure.h"
//#include "LogView.h"
#include "MainFrm.h"
//#include "MaintainView.h"
//#include "MicroperfusionView.h"
//#include "MotorSetView.h"
//#include "MotortestView.h"
//#include "PatientInfoView.h"
//#include "PatientResultView.h"
//#include "PerfusionView.h"
//#include "PLTSetView.h"
//#include "PrintSetView.h"
//#include "RangeSetView.h"
//#include "ReabentalarmView.h"
//#include "Reagentmanagement2View.h"
//#include "ReagentmanagementView.h"
//#include "RecoilView.h"
//#include "ReportGenerator\ReportGenerator.h"
//#include "ReportSetView.h"
//#include "ResetView.h"
//#include "ResultDetails.h"
//#include "ResultListView.h"
//#include "SelftestView.h"
//#include "SourcemanagementView.h"
//
//#include"TemperaturecontrolView.h"
//#include "TestmainView.h"
//#include "ThreadAS.h"
//#include "ThresholdSetView.h"
//#include "TimeSetView.h"
//#include "UnitSetView.h"
//#include "UploadSetView.h"
//#include "ValvetestView.h"
//#include "WorkSheetView.h"
//#include "WorkspaceBar.h"


#include "CMyBCGPListCtrl.h"
#include "ListCtrl.h"
#include "HeaderCtrl.h"
#include "CMyBCGPHeaderCtrl.h"


#define PC_RECEIVE_FRAME(arg1,arg2)  m_spidev.receive_frame(arg1,arg2)
#define PC_SEND_FRAME(arg1,arg2)  m_spidev.send_frame(arg1,arg2)


#endif 