/*************************************************
Copyright (C), SINNOWA. Co., Ltd.
File name: 	Global_def.h
Author:	xubinbin	Version:	1.0	Date: 2016-02-25
Description: 	ȫ�ֱ�������ͷ�ļ�
Others:       	// �������ݵ�˵��
*************************************************/
#ifndef _GLOBAL_DEF_H_
#define _GLOBAL_DEF_H_


#define SYSCFG3_PATH  	"/Config/syscfg_3.dat"       //75ha:�����ļ�����Ϊsyscfg_*.dat��Ϊ�������������ļ�������
#define SYSCFG2_PATH  	"/Config/syscfg_2.dat"
#define SYSCFG_PATH  	"/Config/syscfg_1.dat" 
#define MAINTAIN_PATH	"/Config/maintain.ini"
//#define LOGFILE_PATH  "/Config/logfile.dat"
#define DATABASE_PATH 	"/Config/appdata.db"
#define DEBUG_PATH  	"/debug/rdata.txt"


//Message Define



//LMNE thresholds
#define 	NoL		0
#define 	NoN		1
#define 	LL		2
#define 	LN		3
#define	NoE		4
#define	LMN		5
#define	AL		6
#define 	LMU		7
#define	LMD		8
#define	MN		9
#define	RM		10
#define	RN		11
#define	NL		12
#define	RMN		13
#define	NE		14
#define	FLN		15
#define	FNE		16
#define	FMN		17
//BASO thresholds
#define	BA1		18
#define	BA2		19
#define	BA3		20
//RBC thresholds
#define 	RB1		21
#define	RB2		22
//PLT thresholds
#define	PLT1	23
#define	PLT2	24

#define	QCBA1	0
#define	QCBA2	1
#define	QCBA3	2

//28������
#define WBCS	0
#define	LYMP	1
#define	NEUP	2
#define	MONOP	3
#define	EOSP	4
#define	BASOP	5
#define	ALYP	6
#define	LICP	7
#define	LYMS	8
#define NEUS	9
#define	MONOS	10
#define	EOSS	11
#define	BASOS	12
#define ALYS	13
#define	LICS	14
#define	RBCS	15
#define	HGBS	16
#define	HCTS	17
#define	MCVS	18
#define	MCHS	19
#define	MCHCS	20
#define	RDWCVS	21
#define	RDWSDS	22
#define	PLTS	23
#define	MPVS	24
#define	PDWS	25
#define	PCTS	26
#define PLCRS    27

//�������ӣ�ҽԺ��
#define CAL_WBCF 		0
#define CAL_RBCF 		1
#define CAL_HGBF 		2
#define CAL_MCVF 		3
#define CAL_PLTF 		4

//�������ӣ��ڲ�����ʦ��
#define MOD_WBCF 		0
#define MOD_RBCF 		1
#define MOD_HGBF 		2
#define MOD_MCVF 		3
#define MOD_RDWCVF 	4
#define MOD_RDWSDF 	5
#define MOD_PLTF 		6
#define MOD_MPVF 		7
#define MOD_PDWF 		8
#define MOD_PCTF 		9
#define MOD_PLCRF 		10

//����ģʽѡ��
#define   WHOLEDIFF		0x00
#define	WHOLECBC  		0x01
#define   DILUENTDIFF	0x02
#define	DILUENTCBC  	0x03

//����ѡ��
#define CHINESE  	0x01
#define ENGLISH  	0x02
#define FRENCH  		0x04
#define RUSSIAN  	0x08
#define SPANISH  	0x10

//��Χѡ��
#define RANGE_UNIVERSAL		0x00//ͨ��
#define RANGE_MAN			0x01//����
#define RANGE_WOMAN			0x02//��Ů
#define RANGE_CHILD			0x03//��ͯ
#define RANGE_BABY			0x04//Ӥ��
#define RANGE_OLD			0x05//����
#define RANGE_USERDEFINE1	0x06//�Զ���1	
#define RANGE_USERDEFINE2	0x07//�Զ���2

//����ʱ���ʽ
#define YYYYMMDD 0
#define MMDDYYYY 1
#define DDMMYYYY 2

//����
//������� 					//sdata[0]-sdata[31]
#define XM_START_RINSE  	0x00
#define XM_START_HGB		0x01
#define XM_START_LMNE    	0x02
#define XM_START_RBC		0x03
#define XM_START_WBCBASO 	0x04
#define XM_CUP_RADIUS       	0x05

#define DIM_DILUENT			0x06

#define YM_REF                     	0x07
#define YM_HIGH_RINSE        	0x08
#define YM_LOW_RINSE          	0x09
#define YM_MID_HGB              	0x0A
#define YM_LOW_HGB           	0x0B
#define YM_HIGH_HGB           	0x0C
#define YM_WBCLMNE            	0x0D
#define YM_RBCPLT              	0x0E
#define YM_WBCBASO            	0x0F
#define YM_STARTSAMPLE     	0x10

#define PUSH_SHELF     	0x00
#define  J_MOTOR  		0x01
#define  HAND_X			0x02
#define  HAND_Y  		0x03
#define  HAND_MIXER  	0x04
#define  FLAT			0x05
#define  POP_SHELF  		0x06
#define  HAND_TAKETOROUNG  	0x07
#define  HAND_ENDTOTEST  		0x08
#define  HAND_Y_UPTOROUNG  		0x09

//�Լ�
#define DILUENT		0
#define Rinse		1
#define HGBLyse		2	
#define EOSLyse		3
#define BASLyse		4


//�����������¶Ȳ���	//sdata[32]-sdata[39]
extern syscfg3 systemcfg3;
extern syscfg2 systemcfg2;
extern syscfg systemcfg;
extern lgfi logfile;
extern sMaintain m_sMaintain;
extern int cfg3_fd, cfg2_fd, cfg_fd, lgfi_fd;
extern int gpio_fd;
//extern sqlite3 *db;

extern uchar* 	pIsSuper;
//extern char	PC_status;

 extern unsigned int framelen[13];			//������֡����
//unsigned char key_status;  			//0:������Ч��1:������Ч
 extern bool key_status;  			//0:������Ч��1:������Ч
 extern unsigned int timeFrKd;					//���̰�����0��Ȼ��ʼ��ʱ�䣬��λΪ�룬�Զ�������
 extern unsigned int DSPFreeTime;				//��¼DSP����ʱ�䣬��λΪ��
 extern unsigned int timeFrKd9;				//�����Զ�����
 extern  unsigned char sdata_cmd[1];
 extern unsigned char rdata_state[1];
 extern unsigned int NumFromBoot;			//�����Ժ����Ĳ�������ִ�����Զ���ϴ����0

 extern status DSP_status;
// 0(free):DSP���У�����ͨ����(ARM�ɷ����κ������DSP) 
// 1(busy):DSPæµ��ͨ����(���ܷ����κ������DSP)������1��ʱ�򣬿ɽ��в�ѯ������Ȳ��������漰DSP�Ĳ���(��ʱû��ô�ã���ʱ�����ɲ���)	
// 2(clean):DSP������������ϴ(�ܷ��Ͳ��������DSP������������ܷ���DSP)
extern unsigned char PC_status;

//ARM��״̬
#define WAITING_PUNCTURE_OVER		0x01
#define WAITING_DATA    			0x02//�����ںܶ�ط���ֻҪ�������ڽ�����λ�����ֵĶ�������
#define WAITING_TEST_OVER    		0x08
#define TEST_OVER                   0x09

extern time_t systime;			//������ʱ��
extern struct tm rtm;  			//Ŀ���ʱ��
extern struct tm *caltime;		//ʱ��

//��ʱ���궨��
#define SYSPARAM_TIMER 	    99	//��DSP��������Ķ�ʱ��
#define POLL_TIMER		    115
#define WAIT_TIMER		 	101	//�����ȴ��������붨ʱ��
#define SYSTIME				103	//ϵͳʱ�Ӷ�ʱ��
#define SLEEP_TIMER1		105	//���߶�ʱ��1������ʱ��ϳ�������
#define SLEEP_TIMER2		105
#define POLLTIME			107	//��ѯ��ʱ��
#define POLLTIME2			108
#define ERROR_TIMER 		109	//���ڴ��󱨾�
#define UPDATE_STATUS		111 //ˢ�������Խ���״̬��
#define CHECKERR_TIMER		113
#define POLLTIME3			114

#define PROGRESS_TIMER		116//��������ʱ��
#define CLOCK_TIMER			117//ʼ�ն�ʱ��

#define CHECK_BARCODEINPUT  118//����ǹ��ʱ��

#define SPI_POLL_TIME500			500	//��ѯ���ʱ��0.5s����Ҫ����ʵʱ�Ľ������ݣ��������ؼ��ģ�顢RBCPLT��BASOҺ·���
#define SPI_POLL_TIME1000			1000	//��ѯ���ʱ��1s����Ҫ���ڳ��������������������,�������ԣ�HGB���ȣ�ʱ����Խ϶�
#define SPI_POLL_TIME3000			3000	//��ѯ���ʱ��3s���������������̣��Լ�����һЩʱ���Գ��Ŀ��ƹ���

extern unsigned char hgbgraph[4];		//DSP��������HGBֵ���ҳ���10
//�ڶ�������
extern unsigned char basograph_2[256];
extern unsigned char rbcgraph_2[512];
extern unsigned char pltgraph_2[256];

//������Ϣ
// 1-X�����2-Y�����3-SM�����4-DIM�����5-DRM�����6-CTM�����7-CYM�����8-WBC�¿ף�9-RBC�¿ף�10-��Һʱ�����
extern unsigned char errorShowMess;		//��ǰҪ��ʾ�Ĵ�������,0:û����
extern unsigned char errorShowNum;		//��ǰҪ��ʾ�Ĵ�������������errorMessage�е��±�
extern unsigned char errorNumber;		//���д���ĸ���
extern unsigned char errorMessage[ERRNUM];	//��Ҫ��ʾ�Ĵ������ͱ��룬���鳤��Ϊ����������
extern unsigned char errorReceive[ERRNUM + 1];	//��DSP���յ������ݣ�����������+1��errorReceive[0]�ò���
//״̬��Ϣ
extern unsigned char statusShowMess;		//����״̬��RECT STATUS������ʾ 0-���� 1-���� 2-��ϴ3-�ȴ�����4-�Զ���ϴ��

extern bool IsMainTop;

extern unsigned char 	PLTRightBorderStylus;
extern unsigned char	PLTRightBorderQuery;

extern unsigned int		operator_right;

extern unsigned int  Controltype;//L-J�ʿأ�0��X�ʿأ�1�� X-R�ʿأ�2��
extern unsigned int  Controlfile;//0,1,2,3,4,5,6,7,8��Ӧ�ļ�1,2,3,4,5,6,7,8,9

extern int ListFocusItem;

extern int CurView;

extern	HANDLE		SendMutex;//�����������Ʒ�����Ϣ��
extern	HANDLE		SendEvent;//�����������Ʒ�����Ϣ��
extern  HANDLE		TestmainEvent;//��ѯ�������߳̿����¼�
extern  HANDLE		hEvent;
extern bool			Reconnection;

#define	TableColor		PIXEL_darkgray
#define	TableColor_QC 	PIXEL_lightwhite


#define		MBOX_YESNO		0
#define		MBOX_OKCANCEL		1

#define          SetBkColor_LightGray()		//SetWindowBkColor(hDlg,PIXEL_lightgray)
#define          SetBkColor_LightGray_2()	//SetWindowBkColor(hDlg,PIXEL_lightgray)                //Include GroupBox
#define          SetBkColor_LightGray_3()			//SetWindowBkColor(hDlg,PIXEL_lightgray)      //Only Buttons



#endif


//extern sqlite3 *db;