#include"StdAfx.h"
#include "Includes_app.h"

void ReadSystemcfgFile()
{
	DWORD dwWritenSize;
	HANDLE hFile = ::CreateFile(_T(".//Config//systemcfg.dat"),     //�����ļ������ơ�
		GENERIC_WRITE | GENERIC_READ,          // д�Ͷ��ļ���
		FILE_SHARE_READ | FILE_SHARE_WRITE,                      // �����д��
		NULL,                   // ȱʡ��ȫ���ԡ�
		OPEN_ALWAYS,          // ����ļ����ڣ�ֱ�Ӵ򿪡�
		FILE_ATTRIBUTE_NORMAL, // һ����ļ���      
		NULL);                 // ģ���ļ�Ϊ�ա�
	ReadFile(hFile, &systemcfg, sizeof(systemcfg), &dwWritenSize, NULL);
	CloseHandle;
}

void WriteSystemcfgFile()
{
	DWORD dwWritenSize;
	HANDLE hFile = ::CreateFile(_T(".//Config//systemcfg.dat"),     //�����ļ������ơ�
		GENERIC_WRITE | GENERIC_READ,          // д�Ͷ��ļ���
		FILE_SHARE_READ | FILE_SHARE_WRITE,                      // �����д��
		NULL,                   // ȱʡ��ȫ���ԡ�
		OPEN_ALWAYS,          // ����ļ����ڣ�ֱ�Ӵ򿪡�
		FILE_ATTRIBUTE_NORMAL, // һ����ļ���      
		NULL);                 // ģ���ļ�Ϊ�ա�
	WriteFile(hFile, &systemcfg, sizeof(systemcfg), &dwWritenSize, NULL);
	FlushFileBuffers(hFile);
	CloseHandle;

}

void ReadSystemcfg2File()
{
	DWORD dwWritenSize;
	HANDLE hFile = ::CreateFile(_T(".//Config//systemcfg2.dat"),     //�����ļ������ơ�
		GENERIC_WRITE | GENERIC_READ,          // д�Ͷ��ļ���
		FILE_SHARE_READ | FILE_SHARE_WRITE,                      // �����д��
		NULL,                   // ȱʡ��ȫ���ԡ�
		OPEN_ALWAYS,          // ����ļ����ڣ�ֱ�Ӵ򿪡�
		FILE_ATTRIBUTE_NORMAL, // һ����ļ���      
		NULL);                 // ģ���ļ�Ϊ�ա�
	ReadFile(hFile, &systemcfg2, sizeof(systemcfg2), &dwWritenSize, NULL);
	CloseHandle;
}

void WriteSystemcfg2File()
{
	DWORD dwWritenSize;
	HANDLE hFile = ::CreateFile(_T(".//Config//systemcfg2.dat"),     //�����ļ������ơ�
		GENERIC_WRITE | GENERIC_READ,          // д�Ͷ��ļ���
		FILE_SHARE_READ | FILE_SHARE_WRITE,                      // �����д��
		NULL,                   // ȱʡ��ȫ���ԡ�
		OPEN_ALWAYS,          // ����ļ����ڣ�ֱ�Ӵ򿪡�
		FILE_ATTRIBUTE_NORMAL, // һ����ļ���      
		NULL);                 // ģ���ļ�Ϊ�ա�
	WriteFile(hFile, &systemcfg2, sizeof(systemcfg2), &dwWritenSize, NULL);
	FlushFileBuffers(hFile);
	CloseHandle;

}


void ReadSystemcfg3File()
{
	DWORD dwWritenSize;
	HANDLE hFile = ::CreateFile(_T(".//Config//systemcfg3.dat"),     //�����ļ������ơ�
		GENERIC_WRITE | GENERIC_READ,          // д�Ͷ��ļ���
		FILE_SHARE_READ | FILE_SHARE_WRITE,                      // �����д��
		NULL,                   // ȱʡ��ȫ���ԡ�
		OPEN_ALWAYS,          // ����ļ����ڣ�ֱ�Ӵ򿪡�
		FILE_ATTRIBUTE_NORMAL, // һ����ļ���      
		NULL);                 // ģ���ļ�Ϊ�ա�
	ReadFile(hFile, &systemcfg3, sizeof(systemcfg3), &dwWritenSize, NULL);
	CloseHandle;
}

void WriteSystemcfg3File()
{
	DWORD dwWritenSize;
	HANDLE hFile = ::CreateFile(_T(".//Config//systemcfg3.dat"),     //�����ļ������ơ�
		GENERIC_WRITE | GENERIC_READ,          // д�Ͷ��ļ���
		FILE_SHARE_READ | FILE_SHARE_WRITE,                      // �����д��
		NULL,                   // ȱʡ��ȫ���ԡ�
		OPEN_ALWAYS,          // ����ļ����ڣ�ֱ�Ӵ򿪡�
		FILE_ATTRIBUTE_NORMAL, // һ����ļ���      
		NULL);                 // ģ���ļ�Ϊ�ա�
	WriteFile(hFile, &systemcfg3, sizeof(systemcfg3), &dwWritenSize, NULL);
	FlushFileBuffers(hFile);
	CloseHandle;

}

void ReadLogFile()
{
	DWORD dwWritenSize;
	HANDLE hFile = ::CreateFile(_T(".//Config//logfile.dat"),     //�����ļ������ơ�
		GENERIC_WRITE | GENERIC_READ,          // д�Ͷ��ļ���
		FILE_SHARE_READ | FILE_SHARE_WRITE,                      // �����д��
		NULL,                   // ȱʡ��ȫ���ԡ�
		OPEN_ALWAYS,          // ����ļ����ڣ�ֱ�Ӵ򿪡�
		FILE_ATTRIBUTE_NORMAL, // һ����ļ���      
		NULL);                 // ģ���ļ�Ϊ�ա�
	ReadFile(hFile, &logfile, sizeof(logfile), &dwWritenSize, NULL);
	CloseHandle;
}

void WriteLogFile()
{
	DWORD dwWritenSize;
	HANDLE hFile = ::CreateFile(_T(".//Config//logfile.dat"),     //�����ļ������ơ�
		GENERIC_WRITE | GENERIC_READ,          // д�Ͷ��ļ���
		FILE_SHARE_READ | FILE_SHARE_WRITE,                      // �����д��
		NULL,                   // ȱʡ��ȫ���ԡ�
		OPEN_ALWAYS,          // ����ļ����ڣ�ֱ�Ӵ򿪡�
		FILE_ATTRIBUTE_NORMAL, // һ����ļ���      
		NULL);                 // ģ���ļ�Ϊ�ա�
	WriteFile(hFile, &logfile, sizeof(logfile), &dwWritenSize, NULL);
	FlushFileBuffers(hFile);
	CloseHandle;

}

void ReadMaintainFile()
{
	DWORD dwWritenSize;
	HANDLE hFile = ::CreateFile(_T(".//Config//maintain.dat"),     //�����ļ������ơ�
		GENERIC_WRITE | GENERIC_READ,          // д�Ͷ��ļ���
		FILE_SHARE_READ | FILE_SHARE_WRITE,                      // �����д��
		NULL,                   // ȱʡ��ȫ���ԡ�
		OPEN_ALWAYS,          // ����ļ����ڣ�ֱ�Ӵ򿪡�
		FILE_ATTRIBUTE_NORMAL, // һ����ļ���      
		NULL);                 // ģ���ļ�Ϊ�ա�
	ReadFile(hFile, &m_sMaintain, sizeof(m_sMaintain), &dwWritenSize, NULL);
	CloseHandle;
}

void WriteMaintainFile()
{
	DWORD dwWritenSize;
	HANDLE hFile = ::CreateFile(_T(".//Config//maintain.dat"),     //�����ļ������ơ�
		GENERIC_WRITE | GENERIC_READ,          // д�Ͷ��ļ���
		FILE_SHARE_READ | FILE_SHARE_WRITE,                      // �����д��
		NULL,                   // ȱʡ��ȫ���ԡ�
		OPEN_ALWAYS,          // ����ļ����ڣ�ֱ�Ӵ򿪡�
		FILE_ATTRIBUTE_NORMAL, // һ����ļ���      
		NULL);                 // ģ���ļ�Ϊ�ա�
	WriteFile(hFile, &m_sMaintain, sizeof(m_sMaintain), &dwWritenSize, NULL);
	FlushFileBuffers(hFile);
	CloseHandle;
}