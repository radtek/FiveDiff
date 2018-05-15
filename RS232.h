#pragma once

#define MAX_PORTS 10

struct PortInfo
{
	bool	busy;	//�Ƿ��,1:��  //int->bool
	CString name;	//�豸��
	int		handle;		//�����
};



class CRS232
{
public:
	CRS232();
	~CRS232();
	BOOL OpenCom(int portNo, int baudrat);
	BOOL CloseCom(int portNo);
	BOOL ComRd(int portNo, unsigned char buf[], int maxCnt, int baudrat);//ms;
	BOOL ComWrt(int portNo, CString buf, int maxCnt, int baudrat);
	BOOL ComWrt1(int portNo, unsigned char buf[], int maxCnt, int baudrat);
	BOOL InitComConfig(int baudrat);

private:
	HANDLE hComm;//����ͨ��
	struct PortInfo ports[MAX_PORTS];
};
