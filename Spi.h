/*************************************************
Copyright (C), SINNOWA. Co., Ltd.
File name: 	Spi.h
Author:	xubinbin	Version:	1.0	Date: 2016-02-25
Description: 	Spi����ͨ��h�ļ�����Ҫ������Ҫ��Э��֡
Others:       	// �������ݵ�˵��
*************************************************/

#ifndef __SPI_H__
#define __SPI_H__

#define SPI_TIMEOUT		5000   

//֡ͷ֡β����
#define SPI_FM_SYNC    		0x02//ͬ��֡ͷ
#define SPI_FM_HEADER   	0x68//��ʼ֡ͷ
#define SPI_FM_END       	0x16//֡β

//------------------------------------------------
//֡���ͺ궨��
#define SPI_TYPE_CMD				0x00//����֡
#define SPI_TYPE_STATE				0x01//״̬֡
#define SPI_TYPE_SETTINGS			0x02//���ò���

#define SPI_TYPE_HGBRES			0x03
#define SPI_TYPE_BASORES			0x04
#define SPI_TYPE_RBCRES				0x05
#define SPI_TYPE_PLTRES				0x06
#define SPI_TYPE_LMNERES			0x07

#define SPI_TYPE_TEMRES				0x08//DSP�¶���Ϣ
#define SPI_TYPE_DIFFADJUSTRES		0x09//����ϵͳ����SPIͨ����������
#define SPI_TYPE_HGBTESTRES			0x0A//����ʦά������->HGB���� �������������
#define SPI_TYPE_DSPVERSIONRES		0x0B//DSP�汾��
#define SPI_TYPE_ERRORRES			0x0C//����״̬����


//------------------------------------------------
//SPIͨ������֡�궨��

//#define    						0x00//����Ϊ��ʼֵ����ʾû��SPI������Ҫ��Ӧ


//Remark
//  	0x04		~	0x0B

//  	0x10		~	0x16(������),	
//	0x17		~	0x1D(�����V34-V40)

//  	0x20		~	0x2F(�����V1-V16)

//  	0x30		~	0x3F(�����V17-V32)

//  	0x40		~	0x46(��ע)	,	
//	0x48		~	0x49(��ϴ),
//	0x4A		~	0x4D(��������)

//  	0x50		~	0x59

//  	0x60		~	0x69

//  	0x70		~	0x77

//  	0x81

//  	0x92		~	0x9D

//  	0xA0		~	0xAE

//	0xE0		~	0xE5,	
//	0xEC		~	0xEE

//	0xF4			~	0xF9


//���˵�
#define SPI_CMD_SHUTDOWN			0x04
#define SPI_CMD_SELFTEST			0x05
#define SPI_CMD_STARTUP			0x06
#define SPI_CMD_DIFFADJUST       		0x07
#define SPI_CMD_REQDSPVERSION   	0x08
#define SPI_CMD_REQDSP_STATUS		0x09
#define SPI_CMD_REQERROR			0x0A//�����������
#define SPI_CMD_DILUENT_SAMPLE	0x0B//��ϡ��Һ

//ά��
//����������
#define SPI_CMD_TEST_YM		0x10			
#define SPI_CMD_TEST_XM		0x11	
#define SPI_CMD_TEST_SM		0x12
#define SPI_CMD_TEST_DRM		0x13
#define SPI_CMD_TEST_CTM		0x14
#define SPI_CMD_TEST_CYM		0x15	
#define SPI_CMD_TEST_DIM        	0x16
//���������
#define SPI_CMD_TEST_V1			0x20
#define SPI_CMD_TEST_V2			0x21
#define SPI_CMD_TEST_V3			0x22
#define SPI_CMD_TEST_V4			0x23
#define SPI_CMD_TEST_V5			0x24
#define SPI_CMD_TEST_V6			0x25
#define SPI_CMD_TEST_V7			0x26
#define SPI_CMD_TEST_V8			0x27
#define SPI_CMD_TEST_V9			0x28
#define SPI_CMD_TEST_V10		0x29
#define SPI_CMD_TEST_V11		0x2A
#define SPI_CMD_TEST_V12		0x2B
#define SPI_CMD_TEST_V13		0x2C
#define SPI_CMD_TEST_V14		0x2D
#define SPI_CMD_TEST_V15		0x2E
#define SPI_CMD_TEST_V16		0x2F
#define SPI_CMD_TEST_V17		0x30
#define SPI_CMD_TEST_V18		0x31
#define SPI_CMD_TEST_V19		0x32
#define SPI_CMD_TEST_V20		0x33
#define SPI_CMD_TEST_V21		0x34
#define SPI_CMD_TEST_V22		0x35
#define SPI_CMD_TEST_V23		0x36
#define SPI_CMD_TEST_V24		0x37
#define SPI_CMD_TEST_V25		0x38
#define SPI_CMD_TEST_V26		0x39
#define SPI_CMD_TEST_V27		0x3A
#define SPI_CMD_TEST_V28		0x3B
#define SPI_CMD_TEST_V29		0x3C
#define SPI_CMD_TEST_V30		0x3D
#define SPI_CMD_TEST_V31		0x3E
#define SPI_CMD_TEST_V32		0x3F
#define SPI_CMD_TEST_TUBE		0x47	//���Դ���ģ���ŷ�����  V33
#define SPI_CMD_TEST_V34		0x17
#define SPI_CMD_TEST_V35		0x18
#define SPI_CMD_TEST_V36		0x19
#define SPI_CMD_TEST_V37		0x1A
#define SPI_CMD_TEST_V38		0x1B
#define SPI_CMD_TEST_V39		0x1C
#define SPI_CMD_TEST_V40		0x1D

//��ע����
#define SPI_CMD_PRIME_DILUENT 				0x40            
#define SPI_CMD_PRIME_WBCRINSE			0x41
#define SPI_CMD_PRIME_LMNEFIX				0x42
#define SPI_CMD_PRIME_WBCLYSE				0x43
#define SPI_CMD_PRIME_HGBLYSE				0x44
#define SPI_CMD_PRIMEALL					0x45
#define SPI_CMD_REVERSEDPRIME				0x46

//�ſ�����
#define SPI_CMD_DRAIN_WASTE					0x50
#define SPI_CMD_DRAIN_RINSE					0x51
#define SPI_CMD_DRAIN_HGB						0x52
#define SPI_CMD_DRAIN_RBC						0x53
#define SPI_CMD_DRAIN_BASO					0x54
#define SPI_CMD_DRAIN_LMNE					0x55
#define SPI_CMD_DRAIN_ALL       					0x56
#define SPI_CMD_DRAIN_DILUENT_RESERVOIR		0x57
#define SPI_CMD_DRAIN_CTM						0x58
#define SPI_CMD_DRAIN_PIPE						0x59
//��ϴ����
#define SPI_CMD_CLEAN_COUNTCHAMBER		0x48
#define SPI_CMD_CLEAN_SHEATHFLOWPOOL   	0x49
#define SPI_CMD_CLEAN_RINSEBASO		0x60
#define SPI_CMD_CLEAN_DILUENTINTINE   	0x61
#define SPI_CMD_CLEAN_RINSEINTINE		0x62
#define SPI_CMD_CLEAN_DILUENTEXTINE	0x63
#define SPI_CMD_CLEAN_RINSEEXTINE		0x64
#define SPI_CMD_CLEAN_SHEATFLOWPIPE	0x65
#define SPI_CMD_CLEAN_GEM				0x66
#define SPI_CMD_BACKFLUSH_LMNE		0xE3

//�Զ�ά��
#define SPI_CMD_RINSEBATHS				0x67
#define SPI_CMD_MINIPRIME				0x68
#define SPI_CMD_BACKFLUSH				0x69

//����ʦά��

//����Դ����
#define SPI_CMD_BASOCURON					0x70
#define SPI_CMD_BASOCUROFF				0x71
#define SPI_CMD_RBCCURON					0x72
#define SPI_CMD_RBCCUROFF					0x73
#define SPI_CMD_LMNECURON					0x74
#define SPI_CMD_LMNECUROFF				0x75

#define SPI_CMD_CONCENTRATE_CLEAN1		0x76//Ũ����ϴ��һ��
#define SPI_CMD_CONCENTRATE_CLEAN2		0x77//Ũ����ϴ�ڶ���

//��������
#define SPI_CMD_HGB_MAINTAIN		0x81

//�ճ�ά���ͱ���
//#define SPI_CMD_WEEKLYMAINTAIN	0x91
#define SPI_CMD_MONTHLYMAINTAIN	0x92

//����ʦά��
//��λ�붨��
#define SPI_CMD_SAMPLERATION		0xA0//������������
#define SPI_CMD_HGBLYSERATION		0xA1//HGBLYSE��������
#define SPI_CMD_RINSERATION		0xA2//RINSE������������
#define SPI_CMD_FIXRATION			0xA3//FIX������������
#define SPI_CMD_DILUETNRATION		0xA4//Diluent������������
#define SPI_CMD_WBCLYSERATION		0xA5//WBCLYSE������������
#define SPI_CMD_XYRATION			0xA6//XYλ�õ���

#define SPI_CMD_TEST_PUNCTURE		0xAD//��⴩����

//Xλ�õ���
#define SPI_CMD_XMSET_START_RINSE		0xA7
#define SPI_CMD_XMSET_START_HGB		0xA8
#define SPI_CMD_XMSET_START_LMNE		0xA9
#define SPI_CMD_XMSET_START_RBC    	0xAA
#define SPI_CMD_XMSET_START_WBCBASO 	0xAB
#define SPI_CMD_XMSET_CUP_RADIUS 		0xAC

//ϡ�͵������
#define SPI_CMD_DIMSET					0xAE

//Yλ�õ���
#define SPI_CMD_YMSET_REF				0x93
#define SPI_CMD_YMSET_HIGH_RINSE		0x94
#define SPI_CMD_YMSET_LOW_RINSE		0x95
#define SPI_CMD_YMSET_MID_HGB			0x96
#define SPI_CMD_YMSET_LOW_HGB		0x97
#define SPI_CMD_YMSET_HIGH_HGB		0x98
#define SPI_CMD_YMSET_WBCLMNE		0x99
#define SPI_CMD_YMSET_RBCPLT			0x9A
#define SPI_CMD_YMSET_WBCBASO		0x9B
#define SPI_CMD_YMSET_STARTSAMPLE   	0x9C

#define SPI_CMD_XYMSET_RESET			0x9D//�˳�����������ý���ʱ,XY����ص���λλ��

//������ģʽ�趨
#define SPI_CMD_CBC5DIFF_MODE   	0xE0
#define SPI_CMD_CBC_MODE			0xE1

////////////////////////////////////////////////////////////����////////////////////////////////////////////////////////////////////////

//�¿׷���
#define 	SPI_CMD_BACKSWING_WBCPH		0xE2
#define	SPI_CMD_BACKSWING_LMNEPH	0xE3
#define	SPI_CMD_BACKSWING_RBCPH		0xE4

#define SPI_CMD_AUTOCLEAN			0xE5
#define SPI_CMD_REQTEM				0xEC	//�����¶ȼ������¶ȣ���35.25,36.23����ܵ�35253623
#define SPI_CMD_REQDIFFADJUST       0xED   	//��������ϵͳ��������

#define SPI_CMD_REQHGB				0xEE
#define SPI_CMD_REQBASO				0xF4
#define SPI_CMD_REQRBC				0xF5
#define SPI_CMD_REQPLT				0xF6
#define SPI_CMD_REQLMNE				0xF7

#define SPI_CMD_STANDBY_IN			0xF8    //hw:20140520   
#define SPI_CMD_STANDBY_OVER		0xF9

#define SPI_CMD_REQSWITCH			0xFA//���󿪹�״̬

#define SPI_CMD_REQBASO_2			0x4A
#define SPI_CMD_REQRBC_2			0x4B
#define SPI_CMD_REQPLT_2			0x4C
#define SPI_CMD_REQHGBTEST		0x4D	//����HGBά��ʱ�������	

//#define							0xFF		//����Ϊ���ͽ���ʱ��α��
//------------------------------------------------
//״̬֡�궨��
#define SPI_STATE_DATAISOK				0x09	//�������׼����
#define SPI_STATE_TESTISOVER	      	0x0A	//�����Թ��̽���

#define SPI_STATE_INFO_START        	0x12 	//���̿�ʼ״̬��Ϣ
#define SPI_STATE_INFO_END         		0x39 	//���̽���״̬��Ϣ����TestIsOver��һ����TEST_OVER����Ӹ��ӵĺ���������SPI_STATE_INFO_END����Ҫ��ͬ��SPI_STATE_READY

#define SPI_STATE_INFO_NOTREADY				0x45//����δ׼���ã������ز���ʱ�õ�
#define SPI_STATE_PUNCTURE_OVER				0x46//�������
#define SPI_STATE_ERROR_YM						0x47//YM�����λ����
#define SPI_STATE_ERROR_DRM					0x48//��Һ��ʱ

#define SPI_STATE_SWITCHON					0x49//

#define SPI_STATE_SYSPARAM_UNRECEIVED  		0x36//����������δ���Ͳ�������˶������ɹ�
#define SPI_STATE_SYSPARAM_RECEIVED  		0x37//�����������Ѵ��Ͳ�������˶������ɹ�

class CSpi
{
public:
	CSpi();
	~CSpi();
	BYTE byDevIndex;
	DevInfo* SPI_dev;
	DevInfo* TRIG_dev;
	unsigned char check_frame(unsigned char *pdata, unsigned int len);
	void SetSpiConfig();
	int open_spi(void);
	int close_spi(int spi_fd);
	void make_frame(unsigned char sdata[], unsigned char frametype, unsigned char *psendframe);
	int send_frame(unsigned char *sdata, unsigned char frametype);
	int receive_frame(unsigned char *rdata, unsigned char frametype);
	

private:

};


#endif
