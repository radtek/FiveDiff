/*************************************************
Copyright (C), SINNOWA. Co., Ltd.
File name: 	Spi.c
Author:	xubinbin	Version:	1.0	Date: 2016-02-25
Description:	Spi����ͨѶ�ӿں���
Others:    	// �������ݵ�˵��
Function List:
History:
*************************************************/
#include "stdafx.h"
#include "Includes_app.h"
#include "Spi.h"

CSpi::CSpi()
{
}

CSpi::~CSpi()
{
}


/*****************************************************
*Function:	check_frame
*Description:	����֡У���
*Called by:
*Other:		ȥ��֡ͬ����֡ͷ��֡β
*History:	create	wsm		2010.9.9
******************************************************/
unsigned char CSpi::check_frame(unsigned char *pdata, unsigned int len)
{
	unsigned short i;
	unsigned char ret = 0;
	for (i = 0; i < len; i++)
		ret += pdata[i];
	return ret;
}

/*****************************************************
*Function:	open_spi
*Description:	��SPI����
*Called by:
*Other:      
*History:	create	wsm		2010.9.9
******************************************************/
int CSpi::open_spi(void)
{
	char serial[15];
	int spi_fd;
	byDevIndex = 0xFF;
	SPI_dev = new DevInfo(DEV_SPI);
	SPI_dev->byRateIndex = 0x04;
	SPI_dev->dwTimeout = 0x00C8000C8;
	
	byDevIndex = USBIO_OpenDevice();//ȡ���豸��
	if (byDevIndex == 0xFF)
	{
		TRACE("���豸ʧ��!    \n");
		return -1;
	}
	else
	{	
		SetSpiConfig();
		USBIO_GetSerialNo(byDevIndex, serial);
		//SetWindowText(serial);

		USBIO_SPIGetConfig(byDevIndex, &SPI_dev->byRateIndex, &SPI_dev->dwTimeout);
		spi_fd = 0;
	}
	//UpdateController();



	//gpio_cmd(EN_SPI);	//Enable spi communication	
	return (spi_fd);
}
/*****************************************************
*Function:	SetSpiConfig
*Description:	�����ƶ��豸spi�ӿ�
*Called by:
*Other: 		
*History:	create	wsm		2010.9.9
******************************************************/
void CSpi::SetSpiConfig()
{
	BYTE byRate;
	DWORD dwTimeout;
	byRate = 0 + (1 << 4);//0��ʾ������Ϊ200K��1<<4��ʾģʽ1
	dwTimeout = 200 + (200 << 16);
	if (USBIO_SPISetConfig(byDevIndex, byRate, dwTimeout))
	{
		SPI_dev->byRateIndex = byRate;
		SPI_dev->dwTimeout = dwTimeout;
	}
	//UpdateController();
}
/*****************************************************
*Function:	close_spi
*Description:	�ر�SPI����
*Called by:
*Other: 		gpio_cmd(DISABLE_SPI)��SPI���豸(DSP)ʹ����Ч
*History:	create	wsm		2010.9.9
******************************************************/
int CSpi::close_spi(int spi_fd)
{
	char serial[15] = { 0 };
	if (spi_fd < 0)
	{
		return -1;
	}
	else
	{
		if (byDevIndex != 0xFF)
		{
			if (USBIO_CloseDevice(byDevIndex) == false)
			{
				TRACE("�ر��豸ʧ��!    \n");
				return -1;
			}
			byDevIndex = 0xFF;
		}
	}
	return 0;
}

/***********************************************************
*Function:	make_frame
*Description:	����֡
*Called by:	send_frame
*Params illustration:  sdata[] :����֡��ԭʼ����
frametype:	����֡����������
pp_MyFrame:�������֡(Ϊʲô��ָ���ָ�룬��ʱ������
*Other:
*History:	create	wsm		2010.9.9
************************************************************/
void CSpi::make_frame(unsigned char sdata[], unsigned char frametype, unsigned char *psendframe)
{
	int i;
	unsigned char *pmyframe = NULL;
	pmyframe = psendframe;
	*pmyframe++ = SPI_FM_SYNC;
	*pmyframe++ = SPI_FM_HEADER;
	*pmyframe++ = frametype;
	for (i = 0; i < framelen[frametype]; i++)
		*pmyframe++ = sdata[i];
	*pmyframe++ = check_frame(sdata, framelen[frametype]);
	*pmyframe = SPI_FM_END;
}

/***********************************************************
*Function:	send_frame
*Description:	����֡
*Called by:
*Params illustration:	sdata[] :����֡��ԭʼ����
frametype:	����֡������
*Other:	���͸������͵�֡DSP
*History:	create	wsm		2010.9.9
************************************************************/
/*int CSpi::send_frame(unsigned char *sdata, unsigned char frametype)
{
	int spi_fd;
	unsigned char *psendframe = NULL;
	BYTE Temp[128];
	BYTE comLen;
	AfxMessageBox(_T("���ͳɹ�1"));

	if ((spi_fd = open_spi()) < 0)
		return -1;
	//֡����Ҫ��������֡sync, head,type, cs, end   
	AfxMessageBox(_T("���ͳɹ�1"));
	if ((psendframe = (unsigned char *)malloc(framelen[frametype] + 5)) == NULL)
	{
		TRACE("malloc failed during send_frame---------!\n");
		exit(1);
	}
	make_frame(sdata, frametype, psendframe);	//send frame length is normally 5  
	comLen = sizeof(psendframe) / 2;
	//if (comLen)
		//StrToVal(Temp, psendframe);
	AfxMessageBox(_T("���ͳɹ�2"));
	if (USBIO_SPIWrite(byDevIndex, psendframe, framelen[frametype] + 5, (void*)SPI_dev->GetWriteBuf(), SPI_dev->GetWriteCnt()) == 0)//ͨ��ָ�����豸�� SPI �ӿ�д����
	{
		TRACE("write to spi_fd failed---------!\n");
		return -1;
	}

	free(psendframe);
	psendframe = NULL;
	close_spi(spi_fd);
	AfxMessageBox(_T("���ͳɹ�3"));
	return 0;
}*/

int CSpi::send_frame(unsigned char *sdata, unsigned char frametype)
{
	int spi_fd;
	unsigned char *psendframe = NULL;
	unsigned char *psendframe2 = NULL;
	BYTE Temp[128];
	BYTE comLen;
	if ((spi_fd = open_spi()) < 0)
		return -1;
	//֡����Ҫ��������֡sync, head,type, cs, end   
	if ((psendframe = (unsigned char *)malloc(framelen[frametype] + 5)) == NULL)
	{
		TRACE("malloc failed during send_frame---------!\n");
		exit(1);
	}
	make_frame(sdata, frametype, psendframe);	//send frame length is normally 5  
	comLen = sizeof(psendframe) / 2;
	//if (comLen)
	//StrToVal(Temp, psendframe);
	int len = framelen[frametype] + 5;
	psendframe2 = psendframe;
	while (len > 0)
	{
		if (USBIO_SPIWrite(byDevIndex, psendframe2, 1, (void*)SPI_dev->GetWriteBuf(), SPI_dev->GetWriteCnt()) == 0)//ͨ��ָ�����豸�� SPI �ӿ�д����
		{
			TRACE("write to spi_fd failed---------!\n");
			return -1;
		}
		//AfxMessageBox(*psendframe);
		psendframe2++;
		len--;
	}
	free(psendframe);
	psendframe2 = NULL;
	psendframe = NULL;
	close_spi(spi_fd);
	return 0;
}
/***********************************************************
*Function:	receive_frame
*Description:	����֡,�����ܵ�״̬ʵʱ֪ͨ��������
*Called by:
*Params illustration:
*Other:	����ģʽ��ͨ����DSP����α��0xFF
�Ӷ�����DSP�ϴ�������֡
*History:	create	wsm		2010.9.9
************************************************************/
int CSpi::receive_frame(unsigned char *rdata, unsigned char frametype)
{
	int spi_fd, i;
	int retu;
	int tout = SPI_TIMEOUT;
	unsigned char *receivebuff = NULL;
	unsigned char *temp = NULL;
	temp = (unsigned char *)malloc(1);
	if ((spi_fd = open_spi()) < 0)
		return -1;
	//ʵ��֡��Ҫ��������֡sync, head,type, cs, end   	
	if ((receivebuff = (unsigned char *)malloc(framelen[frametype] + 5)) == NULL)//������ڴ��ں�������ǰҪ�ͷ�
	{
		TRACE("malloc failed during receive_frame---------!\n");
		exit(1);
	}

	do
	{
		//if (USBIO_SPIRead(byDevIndex, receivebuff, 1, (void*)SPI_dev->GetWriteBuf(), SPI_dev->GetWriteCnt())==0)
		if (USBIO_SPIRead(byDevIndex, 0, 0, receivebuff, 1) == 0)//USBIO_SPIRead(byDevIndex, receivebuff, 1, receivebuff, 1)
		{
			TRACE("read spi_fd failed---------!\n");
			return -1;
		}
		TRACE("receivebuff:%X---------#\n", receivebuff[0]);
		tout--;
	} while ((*receivebuff) != 0x02 && tout);//
	if (!tout)
	{
		//�����贰�ڷ��ͽ��ܳ�ʱ������Ϣ���������ݴ���
		TRACE("SPI_TIMEOUT---------!\n");
		//return -1;//��ʱ����
		retu = -1;
	}
	else
	{
		TRACE("sync:%X---------#\n", receivebuff[0]);
		//USBIO_SPIRead(byDevIndex, receivebuff, framelen[frametype] + 4, (void*)SPI_dev->GetWriteBuf(), SPI_dev->GetWriteCnt());
		int len = framelen[frametype] + 4;
		int index = 0;
		while (len > 0)
		{
			USBIO_SPIRead(byDevIndex, 0, 0, temp, 1);
			receivebuff[index] = *temp;
			index++;
			len--;
		}
		//USBIO_SPIRead(byDevIndex, receivebuff, framelen[frametype] + 4, receivebuff, framelen[frametype] + 4);
		if (receivebuff[0] == 0x68 && receivebuff[framelen[frametype] + 3] == 0x16)
		{
			TRACE("head:%X---------#\n", receivebuff[0]);
			if (receivebuff[1] == frametype)
			{
				TRACE("frametype:%X---------#\n", receivebuff[1]);
				if (receivebuff[framelen[frametype] + 2] == check_frame(receivebuff + 2, framelen[frametype]))
				{
					for (i = 0; i < framelen[frametype]; i++)
					{
						rdata[i] = receivebuff[i + 2];
						TRACE("i:%d----------#\n",i);
						TRACE("rxdata:%X---------#\n", rdata[i]);
					}
					TRACE("cs:%X---------#\n", receivebuff[framelen[frametype] + 2]);
					TRACE("tail:%X---------#\n", receivebuff[framelen[frametype] + 3]);
					//return 0;	
					retu = 0;
				}
				else
				{
					TRACE("**********frame check error*********************\n");
					//�����贰�ڷ��ͽ������ݴ�����Ϣ
					//return -4;//֡У�����
					retu = -4;
				}
			}
			else
			{
				TRACE("frametype:%X---------#\n", receivebuff[1]);
				TRACE("**********frame type error****************\n");
				//�����贰�ڷ��ͽ������ݴ�����Ϣ
				//return -3;//֡���ʹ���	
				retu = -3;
			}
		}
		else
		{
			TRACE("head:%X---------#\n", receivebuff[0]);
			TRACE("tail:%X---------#\n", receivebuff[framelen[frametype] + 3]);
			TRACE("**********frame structure error**************\n");
			//�����贰�ڷ��ͽ������ݴ�����Ϣ
			//return -2;	//֡�ṹ����
			retu = -2;
		}
	}
	//TRACE("rxdata:%X---------#\n", rdata[0]);
	free(receivebuff);
	free(temp);
	receivebuff = NULL;
	temp = NULL;
	close_spi(spi_fd);
	return retu;
	//�����贰�ڷ��ͳɹ�����������Ϣ
}
//=============================//


