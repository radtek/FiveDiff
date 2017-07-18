#include "stdafx.h"
#include "RS232.h"



CRS232::CRS232()
{

	for (int i = 0; i < 10; i++)
	{
		ports[i].busy = false;
	}
}


CRS232::~CRS232()
{

}

BOOL CRS232::OpenCom(int portNo, int baudrat)
{
	
	switch (portNo){
	case 0:ports[portNo].name = "COM1"; break;
	case 1:ports[portNo].name = "COM2"; break;
	case 2:ports[portNo].name = "COM3"; break;
	case 3:ports[portNo].name = "COM4"; break;
	case 4:ports[portNo].name = "COM5"; break;
	case 5:ports[portNo].name = "COM6"; break;
	case 6:ports[portNo].name = "COM7"; break;
	case 7:ports[portNo].name = "COM8"; break;
	case 8:ports[portNo].name = "COM9"; break;
	case 9:ports[portNo].name = "COM10"; break;

	default:break;
	}
	hComm = CreateFile(ports[portNo].name, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0);
	if (hComm == INVALID_HANDLE_VALUE)       //�������δ��
	{
		//m_chush1.EnableWindow(true);
		TRACE(_T("��ͨ�Ŷ˿ڴ���!! "));
		return FALSE;
	}
	ports[portNo].busy = true;
	return InitComConfig(baudrat);
}

BOOL CRS232::CloseCom(int portNo)
{
	//if (CloseHandle(hComm)&& (ports[portNo].busy = false))
	//{
	//	return true;
	//}
	if (CloseHandle(hComm))
		return true;
	return false;
}

BOOL  CRS232::ComRd(int portNo, unsigned char buf[], int maxCnt,int baudrat)
{
	DWORD count;
	if (!OpenCom(portNo,baudrat))
	{
		TRACE(L"ComRd��comʧ��\n");
		return false;
	}
	if (!ReadFile(hComm, buf, maxCnt, &count, NULL)){
		AfxMessageBox(_T("���ڹر�! "));
	}
	if (!CloseCom(portNo))
	{
		TRACE(L"ComRd�ر�comʧ��\n");
		TRACE("Open file filed with error %d \n", GetLastError());
		return false;
	}
	return true;
}

BOOL CRS232::ComWrt(int portNo, CString buf, int maxCnt, int baudrat)
{
	unsigned long lrc;

	if (!OpenCom(portNo,baudrat))
	{
		TRACE(L"ComWrt��comʧ��\n");
		return false;
	}
	if (hComm == 0) return false;					 //���Handleֵ
	WriteFile(hComm, buf, maxCnt, &lrc, NULL);  //�ͳ�����
	if (!CloseCom(portNo))
	{
		TRACE(L"ComWrt�ر�comʧ��\n");
	}
	return true;
}

/******************���ܲ�̫�Եĳ���*********************/
BOOL CRS232::ComWrt1(int portNo, unsigned char buf[], int maxCnt, int baudrat)
{
	unsigned long lrc;

	if (!OpenCom(portNo, baudrat))
	{
		TRACE(L"ComWrt��comʧ��\n");
		return false;
	}
	if (hComm == 0) return false;					 //���Handleֵ
	WriteFile(hComm, buf, maxCnt, &lrc, NULL);  //�ͳ�����
	if (!CloseCom(portNo))
	{
		TRACE(L"ComWrt�ر�comʧ��\n");
	}
	return true;
}

BOOL CRS232::InitComConfig(int baudrat)
{
	DCB dcb;

	SetupComm(hComm, 1024, 1024); //���뻺����������������Ĵ�С����1024 
	//��dcb��ַ���룬��ȡ��ͨ�Ų���
	GetCommState(hComm, &dcb);      //��֪Ŀǰ���ж˿ڵ�״̬

	COMMTIMEOUTS TimeOuts; //�趨����ʱ

	TimeOuts.ReadIntervalTimeout = 1000;  //���ַ�֮��������ʱ������ȡ��������ʱ��һ�������ַ������ʱ������ʱ�䣬��ȡ�������������е����ݡ�����Ϊ0��ʾ�ò����������á�

	TimeOuts.ReadTotalTimeoutMultiplier = 500;//��ȡÿ�ַ���ĳ�ʱ

	TimeOuts.ReadTotalTimeoutConstant = 5000; //�趨д��ʱ

	TimeOuts.WriteTotalTimeoutMultiplier = 500;//һ�ζ�ȡ�������ݵĹ̶���ʱ

	TimeOuts.WriteTotalTimeoutConstant = 2000; //д��ÿ�ַ���ĳ�ʱ

	SetCommTimeouts(hComm, &TimeOuts); //���ó�ʱ

	switch (baudrat)
	{
	case 4800:
		dcb.BaudRate = CBR_4800;	//�����ʣ�CBR_4800,CBR_9600,CBR_19200,CBR_38400��CBR_57600��CBR_115200
		break;
	case 9600:
		dcb.BaudRate = CBR_9600;
		break;
	case 19200:
		dcb.BaudRate = CBR_19200;
		break;
	case 38400:
		dcb.BaudRate = CBR_38400;
		break;
	case 57600:
		dcb.BaudRate = CBR_57600;
		break;
	case 115200:
		dcb.BaudRate = CBR_115200;
		break;
	default:
		AfxMessageBox(L"���ڲ����ʴ���,����Ĭ�ϲ�����");
		break;
	}
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY; //��żУ�飺EVENPARITY,ODDPARITY,NOPARITY
	dcb.StopBits = ONESTOPBIT;     //1��ֹͣλ

	if (!SetCommState(hComm, &dcb))
	{
		AfxMessageBox(_T("ͨ�Ŷ˿����ô���!! "));
		CloseHandle(hComm);
		return FALSE;
	}
	//AfxMessageBox(_T("ͨ�Ŷ˿����óɹ�!! "));
	PurgeComm(hComm, PURGE_TXCLEAR | PURGE_RXCLEAR);   //����������������
	return TRUE;
}