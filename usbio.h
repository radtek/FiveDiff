//****************************************
//**  Copyright  (C)  USBIO  2011-2031  **

//****************************************
//**  DLL for USB interface chip USB2uis**
//**                            **
//****************************************
//
// USBתUART,I2C,SPI Ӧ�ò�ӿڿ� V1.0
// ����: USB2uis  antony.wang
// USB2uis.DLL  V1.0
// ���л���: Windows XP vista window7

/***************history*******************
v1.0:
 1>  created        2011.12.07   by antony
*****************end*********************/

#ifndef		USBIO_H
#define		USBIO_H
#define DllExport extern "C"__declspec(dllimport)
#define FM_TIRGER_FUNCTION
//#ifdef __cplusplus
//extern "C" {
//#endif



// �豸�¼�֪ͨ�ص�����
// �豸�¼��͵�ǰ״̬(�����ж���): 0=�豸�γ�, 0x80=�豸����
//typedef	 VOID (CALLBACK* USB_MONITOR_CALLBACK )(BYTE iDevStatus);
//typedef  VOID (CALLBACK* USB_TRIG_CALLBACK )(DWORD iTrigInfo);
 typedef	 VOID (CALLBACK* USB_DLL_CALLBACK )(BYTE iDevIndex, DWORD iDevStatus);
//iTrigInfo���� 

//bit0~7���崥������ bit8~15 ������Ϣ,��16λ����
   
#define EXT_IO_TRIG          0xAA    //�ⲿIO�жϴ��� 
#define SPI_READ_TRIG        0xB0    //SPIԤ������,bit7~bit15   �����󳤶� 0~255�ֱ����1~256�ֽ�
#define SPI_WRITE_TRIG       0xB1    //SPIд����,  bit7~bit15   д���󳤶� 0~255�ֱ����1~256�ֽ�
#define SPI_INIT_READ_TRIG   0xB2    //SPIָʾ�ص�����ʼλ��(ʵ���������¶�,ֻ��Զ�д���ȴ���256�����ݶ�)
#define SPI_INIT_WRITE_TRIG  0xB3    //SPIָʾ�ص�д��ʼλ��(ʵ����������д,ֻ��Զ�д���ȴ���256�����ݶ�)
#define I2C_READ_TRIG        0xC0    //I2CԤ������,bit7~bit15   �����󳤶� 0~255�ֱ����1~256�ֽ�
#define I2C_WRITE_TRIG       0xC1    //I2Cд����,  bit7~bit15   д���󳤶� 0~255�ֱ����1~256�ֽ�

//ȡ���豸����汾��
DllExport bool                    //TRUE���ɹ�
		  USBIO_GetVersion(
							BYTE byIndex ,        // �豸��,
							BYTE byType,         //0->DLL�汾��Ϣ;1->��������汾��Ϣ;2->�̼��汾��Ϣ
							LPVOID lpBuffer      //��������汾��Ϣ�Ļ���
							);

 //ȡ�ÿ���ͬʱ�򿪵��豸�����ֵ
DllExport BYTE                     //�����豸��
					   USBIO_GetMaxNumofDev(
											void
											);

//ȡ��ָ���豸�ŵ����к�
DllExport BYTE      //���ص�ǰ�豸״̬   0->��ǰ�豸������; 1->δʹ��;  2->ʹ����

						USBIO_GetSerialNo
										   (
											 BYTE byIndex,     // �豸��,
											 char* lpBuff
										   );

//ȡ��ָ���豸�ŵ��豸·��
DllExport char*      //�����豸·��ָ��,�����NULL,ָ���豸������
						USBIO_GetDevicePath
										   (
											 BYTE byIndex     // �豸��,
										   );
//�õ���ǰ����ģʽ
/*
   *lpMode == 0x02 -->����ģʽ;
			  0x01 -->����ģʽ;
*/
DllExport bool                  //TRUE����ȡ�ɹ�
						USBIO_GetWorkMode
							(
                               BYTE byIndex,         //�豸��
							   BYTE* lpMode          //��ȡģʽֵ��ָ��
							);
//��λ�豸
 /*
#define DEV_UART     0x80             //unused
#define DEV_I2C      0x81
#define DEV_SPI      0x82
#define DEV_HDQ      0x83
#define DEV_CAN      0x84             //unused
#define DEV_GPIO     0x85
#define DEV_ADC      0x86
#define DEV_PWM      0x87
#define DEV_PARALLEL 0x88             //unused
#define DEV_CE       0x8D             //unused
#define DEV_TRIG     0x8E             //unused
#define DEV_ALL      0x8F
*/
DllExport bool                    //TRUE����λ�ɹ�
		  USBIO_ResetDevice(
							BYTE byIndex,         // �豸��
							BYTE byDevId          //�豸����
		 );

//���ûص���������������USB����¼�

DllExport void   USBIO_SetUSBNotify(
                           bool bLog,
						   USB_DLL_CALLBACK pUSB_CallBack      //USB�ص�����ָ��
						   );

//���ûص���������������IO�����¼�
DllExport void
		 USBIO_SetTrigNotify(
							 BYTE byIndex,          //�豸��
							 USB_DLL_CALLBACK pTrig_CallBack   //�����ص�����ָ��
							 );

// ��ָ�����кŴ�һ��USB2uis�豸,һ���0��ʼ,����Ƿ���0xFF,�򿪲��ɹ�
DllExport BYTE
		 USBIO_OpenDeviceByNumber(
							 char* pSerialString     //�豸���к�
							 );

DllExport  BYTE               // �����һ��USB2uis�豸,һ���0��ʼ,����Ƿ���0xFF,�򿪲��ɹ�
		 USBIO_OpenDevice   (
								void
							  );


DllExport bool
          USBIO_CloseDevice  (                       // �ر�һ��USB2uis�豸
							   BYTE byIndex          //�豸��
							  );

DllExport bool
 USBIO_I2cSetConfig          (                        //����I2c�ӿ�
                               BYTE byIndex,          //�豸��
							   BYTE byDevAddr,        //�豸��ַ
							   BYTE byRate,           //I2cʱ��Ƶ��,0~3 ��λ100k~400k
							   DWORD dwMilliseconds   //I2c��д��ʱ,��λ:���� ;��16bitΪ����ʱ,��16bitΪд��ʱ
                               );
DllExport bool
 USBIO_I2cGetConfig          (                        //ȡ��I2c�ӿ�����
                               BYTE byIndex,           //�豸��
							   BYTE* pbyDevAddr,        //�豸��ַ
							   BYTE* byRate,           //I2cʱ��Ƶ��,0~3 ��λ100k~400k
							   DWORD* pdwMilliseconds   //I2c��д��ʱ,��λ:���� ;��16bitΪ����ʱ,��16bitΪд��ʱ
                               );

DllExport bool                                //ʵ�ʶ�����ֽ���
 USBIO_I2cRead               (                       //��I2c�ӿڶ�����
							   BYTE byIndex,         //�豸��
							   BYTE byDevAddr,       //i2c�豸��ַ
							   LPVOID lpParaBuffer,  //���������ڶ�I2c����֮ǰҪд���������ַ
							   BYTE  byParaSize,     //Ҫд������ݻ��泤��,�������Ҫд��,��Ϊ0
							   LPVOID lpReadBuffer,   //�������ݻ���
							   WORD wReadSize         //����������ݳ���
							   );
DllExport bool                                       //ʵ��д����ֽ���
 USBIO_I2cWrite              (                       //д���ݵ�I2c�ӿ�
							   BYTE byIndex,         //�豸��
							   BYTE byDevAddr,       //i2c�豸��ַ
							   LPVOID lpParaBuffer,  //����������дI2c����֮ǰҪд���������ַ
							   BYTE  byParaSize,     //Ҫд���������ַ����,�������Ҫд��,��Ϊ0
							   LPVOID lpWriteBuffer,  //д�����ݻ���
							   WORD dWriteSize      //����д������ݳ���
							   );
 DllExport bool                              //ʵ�ʶ�����ֽ���
   USBIO_I2cReadEEProm       (                       //�����ݵ�I2c�ӿ�
							   BYTE byIndex,         //�豸��
							   BYTE byDevAddr,       //i2c�豸��ַ
							   BYTE byTypeIndex,     //EEProm �ͺ� 0~12 ��Ӧ24C01~24C4096
							   DWORD dwOffset,       //EEProm ��ʼ��ַ
							   BYTE* lpReadBuffer,   //�������ݻ���
							   WORD wReadSize        //����������ݳ���
							   );
 DllExport bool                               //ʵ��д����ֽ���
   USBIO_I2cWriteEEProm      (                        //д���ݵ�I2c�ӿ�
							   BYTE byIndex,          //�豸��
							   BYTE byDevAddr,        //i2c�豸��ַ
							   BYTE byTypeIndex,      //EEProm �ͺ� 0~12 ��Ӧ24C01~24C4096
							   DWORD dwOffset,         //EEProm ��ʼ��ַ
							   BYTE* lpWriteBuffer,    //д�����ݻ���
							   WORD dWriteSize          //����д������ݳ���
							   );

 DllExport bool
 USBIO_SPISetConfig          (
							  BYTE byIndex,          //�豸��
							  BYTE byRate,           //����λ�ǲ����� 0~8 ��Ӧ200k,400k,600k,800k,1000k,2000k,4000k,6000k,12000K
													  //bit4~bit5��SPI����ģʽ0~3  00=>(POL=0,PHA=0); 01=>(POL=0,PHA=1);10=>(POL=1,PHA=0);11=>(POL=1,PHA=1)
													  //bit6 δ��
													  //bit7 SPI�豸����  0=>���豸; 1=>���豸
							  DWORD dwMilliseconds    //SPI��д��ʱ,��λ:���� ;��16bitΪ����ʱ,��16bitΪд��ʱ
							  );
 DllExport bool
 USBIO_SPIGetConfig  	     (
							  BYTE byIndex,           //�豸��
							  BYTE* pbyRate,          //����λ�ǲ����� 0~8  ��Ӧ200k,400k,600k,800k,1000k,2000k,4000k,6000k,12000K
													  //bit4~bit5��SPI����ģʽ0~3  00=>(POL=0,PHA=0); 01=>(POL=0,PHA=1);10=>(POL=1,PHA=0);11=>(POL=1,PHA=1)
													  //bit6 δ��
													  //bit7 SPI�豸����  0=>���豸; 1=>���豸
							  DWORD* pdwMilliseconds  //SPI��д��ʱ,��λ:����;��16bitΪ����ʱ,��16bitΪд��ʱ
							  );
 DllExport bool
 USBIO_SPIRead              (
							  BYTE byIndex,           //�豸��
							  LPVOID lpComBuffer,     //���������ڶ�SPI����֮ǰҪд�������
							  BYTE  byComSize,        //Ҫд��������,�������Ҫд��,��Ϊ0
							  LPVOID lpBuffer,        //�������ݻ���
							  WORD wBuffSize          //����������ݳ���
							  );
 DllExport bool
 USBIO_SPIWrite              (
							  BYTE byIndex,            //�豸��
							  LPVOID lpComBuffer,      //���������ڶ�SPI����֮ǰҪд�������
							  BYTE  byComSize,         //Ҫд��������,�������Ҫд��,��Ϊ0
							  LPVOID lpBuffer,         //д�����ݻ���
							  WORD wBuffSize            //����д�����ݳ���
							  );
 DllExport bool
  USBIO_HDQSetConfig         (
							  BYTE byIndex,            //�豸��
							  DWORD dwMilliseconds,    //HDQ��д��ʱ
							  BYTE* lpParaBuffer,      //HDQʱ�����  һ��ָ��struct { 	WORD tCYCH,tHW1,tHW0,tBreak,tBR,tCYCD_min,tCYCD_max,tDW1_min,tDW1_max,tDW0_min,tDW0_max,tTO}��ָ��;}
							  BYTE byParaSize          //HDQʱ��������� ���̶�Ϊ24
							  );
 DllExport bool
 USBIO_HDQGetConfig          (
							  BYTE byIndex,        //�豸��
							  DWORD* pdwMilliseconds,    //HDQ��д��ʱ
							  BYTE* lpParaBuff,      //HDQʱ�����  һ��ָ��struct { 	WORD tCYCH,tHW1,tHW0,tBreak,tBR,tCYCD_min,tCYCD_max,tDW1_min,tDW1_max,tDW0_min,tDW0_max,tTO}��ָ��;
							  BYTE byParaSize       //HDQʱ��������� ���̶�Ϊ24
							  );
 DllExport bool
 USBIO_HDQWrite              (
							  BYTE byIndex,         //�豸��
							  BYTE addr,             //HDQ�豸��ַ,������0~0x7F֮��
							  LPVOID lpBuffer,      //д�뻺��
							  BYTE wBuffSize        //д�����ݳ��ȣ�BYTE modeΪ1��WORD mode Ϊ2
							  );
 DllExport bool
 USBIO_HDQRead               (
							  BYTE byIndex,       //�豸��
							  BYTE addr,          //HDQ�豸��ַ,������0~0x7F֮��
							  LPVOID lpBuffer,    //���뻺��
							  WORD wBuffSize      //�������ݳ��ȣ�BYTE modeΪ1��WORD mode Ϊ2
							  );
 DllExport bool
 USBIO_SetCE                  //           ����HDQ���ŵ�ƽ
							 (
							  BYTE byIndex,      //�豸��
							  bool bHigh         //true Ϊ�ߵ�ƽ, false Ϊ�͵�ƽ
							 );
 DllExport bool
 USBIO_GetCE                (
							  BYTE byIndex,      //�豸��
							  BYTE* pbyLevel     //ָ��CE pin��ƽ��ָ�� 1Ϊ�ߵ�ƽ, 0Ϊ�͵�ƽ
							  ) ;

 DllExport bool
 USBIO_GetGPIOConfig         (                   //��ȡGPIO�������� 1Ϊ����,0Ϊ���
							  BYTE byIndex,      //�豸��
							  BYTE* pbyValue      //���뻺��ָ��   b0~b7�ֱ��ӦJ7-10~J7~3
							  );

DllExport bool
USBIO_SetGPIOConfig          (                   //����GPIO���� 1Ϊ����,0Ϊ���
							  BYTE byIndex,      //�豸��
							  BYTE byValue      //д�뻺��   b0~b7�ֱ��ӦJ7-10~J7~3
							  );
 DllExport bool
 USBIO_GPIOWrite             (                   //����GPIO��ƽ 1Ϊ�ߵ�ƽ,0Ϊ�͵�ƽ
							  BYTE byIndex,      //�豸��
							  BYTE byValue,     //���뻺��   b0~b7�ֱ��ӦJ7-10~J7~3
							  BYTE byMask        //��������,   b0~b7λ��Ϊ1ʱ����λ��ֵ���ı�
							  );

DllExport bool
USBIO_GPIORead               (                   //��ȡGPIO��ƽ 1Ϊ�ߵ�ƽ,0Ϊ���
							  BYTE byIndex,      //�豸��
							  BYTE* pbyValue     //���뻺��ָ��   b0~b7�ֱ��ӦJ7-10~J7~3
							  );
DllExport bool
USBIO_TrigGetConfig          (
							   BYTE byIndex,    //�豸��
							   BYTE* pbySelect  //��������ָ��
							   );

DllExport bool
USBIO_TrigSetConfig          (
							   BYTE byIndex,    //�豸��
							   BYTE bySelect    //��������  0:����Ե 1:�½�Ե 2:�ߵ�ƽ 3:�͵�ƽ
							  );

DllExport bool         //���봥���ȴ�״̬
USBIO_WaitForTrig               (
							  BYTE byIndex      //�豸��
							  );

DllExport bool         //�˳������ȴ�״̬
USBIO_ExitTrig               (
							  BYTE byIndex       //�豸��
							  );

DllExport bool
USBIO_GetPWMConfig           (
							  BYTE byIndex,      //�豸��
							  BYTE* pbyRate,     //PWM������ 0~10�ֱ��Ӧ1k,2k,4k,6k,8k,10k,20k,40k,60k,80k,100k
							  BYTE* pbyNum,      //PWMͨ����,����λ��ʾ,����λָʾPWM�Ƿ������� ,1ָʾPWM������
							  WORD* pwDuty      //��СΪ4���ֵĻ��棬���������ĸ�ͨ����ռ�ձ� ,ÿ��ͨ����ռ�ձ�������bytes��ʾ
							  );

DllExport bool
USBIO_SetPWMConfig           (
							  BYTE byIndex,     //�豸��
							  BYTE byRate,      //PWM������ 0~10�ֱ��Ӧ1k,2k,4k,6k,8k,10k,20k,40k,60k,80k,100k
							  BYTE byNum,       //PWMͨ����,����λ��ʾ
							  WORD* pwDuty     //��СΪ4���ֵĻ��棬�����ĸ�ͨ����ռ�ձȣ�ÿ��ͨ����ռ�ձ�������bytes��ʾ
							  );

DllExport bool
USBIO_StartPWM               (
							  BYTE byIndex     //�豸��
							 );

DllExport bool
USBIO_StopPWM               (
							  BYTE byIndex     //�豸��
							 );

DllExport bool
USBIO_GetADCConfig			(
							 BYTE byIndex,     //�豸��
							 BYTE* pbyMask,    //ָ��ADCͨ���Ŀ��ص�ָ��;Bit0~3�ֱ�Ϊͨ��1~4,���Ϊ1,ָʾ��ͨ����
							 BYTE* pbyIOSelect //ָ��4��byte��ָ��,ÿ��BYTE��Ӧһ��ͨ����IOѡ��;�Ͱ��ֽڲ���ͨ����������ѡ��,�߰��ֽڲ���ͨ����������ѡ��;
											   //��������ͨ��ֵ0~9�ֱ��ӦJ7-03~J7-10,�ڲ��¶ȴ�������VDD
											   //���ڸ���ͨ��ֵ0~9�ֱ��ӦJ7-03~J7-10,�ڲ��ο���ѹ��GND
							 );

DllExport bool
USBIO_SetADCConfig           (
							   BYTE byIndex,    //�豸��
							   BYTE byMask,     //ָ��ADCͨ���Ŀ���;Bit0~3�ֱ�Ϊͨ��1~4,���Ϊ1,ָʾ��ͨ����
							   BYTE* pbyIOSelect //ָ��4��byte��ָ��,ÿ��BYTE��Ӧһ��ͨ����IOѡ��;�Ͱ��ֽڲ���ͨ����������ѡ��,�߰��ֽڲ���ͨ����������ѡ��;
												 //��������ͨ��ֵ0~9�ֱ��ӦJ7-03~J7-10,�ڲ��¶ȴ�������VDD
											     //���ڸ���ͨ��ֵ0~9�ֱ��ӦJ7-03~J7-10,�ڲ��ο���ѹ��GND
							  );

DllExport bool
USBIO_ADCRead               (
							  BYTE byIndex,         //�豸��
							  WORD* lpReadBuffer,   //������ȡADC���õ�����ָ��
							  WORD wBuffSize        //ָ��ADC lpReadBuffer�Ĵ�С,����Ϊͨ�����ı���  wBuffSize = chan x ��������
							 );

DllExport bool
 USBIO_UpdateSector          (                       //������������
                               BYTE byIndex,         //�豸��
                               WORD wIndex,             //��������
                               LPVOID lpBuffer,   //д�����ݻ��棬512 bytes
                               BYTE* lpResult       //0x00 -->�ɹ�; 0x01 -->����� ;0x02-->crc��;0x04-->������
                              );

//#ifdef __cplusplus
//}
//#endif

#endif		// _mUSBIO_PACKET_LENGTH_DLL_H
