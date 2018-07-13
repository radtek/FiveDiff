/*************************************************
Copyright (C), SINNOWA. Co., Ltd.
File name: 	Includes_app.h
Author:	xubinbin	Version:	1.0	Date: 2016-02-25
Description: 	�Զ���ṹ��
Struct List:
Others:      	// �������ݵ�˵��
�趨���ӵ�һЩ�������͵�Ҫ����ʵ�������
SPIͨ�ŵĴ��͸�ARM�����ݶ�δ�����������Բ����ϰ汾�Ľ��д�
ͨ����������ͼ�α�������Ĵ�С�Ķ��壬�������͵Ķ��嶼���ݾ������
*************************************************/
#ifndef _STRUCTDEFINE_H_
#define _STRUCTDEFINE_H_

#define ERRNUM 		20		//���������������DSP����һ��
#define MATRIX_POINT_MAX		3500
#define MATRIX_DATA_MAX		(MATRIX_POINT_MAX<<1)

typedef  unsigned char uchar;
typedef enum{ Free = 0, Busy = 1, Clean = 2 } status;

//----------------------------------------
//ʵʱʱ�ӽṹ��
struct rtc_time
{
	int sec;	//��
	int min;	//��
	int hour;//ʱ
	int day;	//��
	int mon;	//��
	int year;//��
	int tm_wday;
	int tm_yday;
	int tm_isdst;
};

//----------------------------------------
//�ʿذ�ϸ���������ݽṹ
struct qc_wbc_data
{
	 char  wbc[6];		//��ϸ������ ������Χ��4.0-10.0 G/L
	 char  lymp[6];	//�ܰ�ϸ���ٷֱ�������Χ��1.0-3.3 G/L
	 char  neup[6];	//������ϸ���ٷֱ� ������Χ��1.8-6.4 G/L
	 char  monop[6];	//��ֵϸ�ٷֱ� ������Χ��0.2-0.9 G/L 
	 char  eosp[6];	//���������ٷֱ�������Χ��20.0-40.0 %
	 char  basp[6];	//�ȼ������ٷֱ� ������Χ��3.0-8.0 %
	 char  licp[6];		//�޴󲻳���ٷֱ� ������Χ��3.0-8.0 %
	 char  alyp[6];		//�����ܰͰٷֱ� ������Χ��3.0-8.0 %
	 char  lym[6];		//�ܰ�ϸ������ ������Χ��1.0-3.3 G/L  
	 char  neu[6];		//������ϸ������ ������Χ��1.8-6.4 G/L
	 char  mono[6];	//��ֵϸ������ ������Χ��0.2-0.9 G/L
	 char  eos[6];		//��������ϸ������ ������Χ��20.0-40.0 %
	 char  bas[6];		//�ȼ�����ϸ������ ������Χ��3.0-8.0 %
	 char  lic[6];		//�޴󲻳���ϸ������ ������Χ��3.0-8.0 %
	 char  aly[6];		//�����ܰ�ϸ������ ������Χ��3.0-8.0 % 
};

//�ʿغ�ϸ���������ݽṹ
struct qc_rbc_data
{
	 char rbc[6]; 		//��ϸ������ ������Χ��3.50-5.50 T/L
	 char hgb[6]; 		//Ѫ�쵰��Ũ�� ������Χ��110.0-160.0g/L
	 char hct[6]; 		//��ϸ��ѹ�� ������Χ�� 37.0-49.0 %
	 char mcv[6]; 		//ƽ����ϸ�����  ������Χ��80.0-100.0 fl
	 char mch[6]; 		//ƽ����ϸ��Ѫ�쵰�׺���  ������Χ��27.0-33.0 Pg
	 char mchc[6];	//ƽ����ϸ��Ѫ�쵰��Ũ��  ������Χ��320-360  g/l
	 char rdw[6]; 		//��ϸ������ֲ���� ������Χ��1.0-14.0 %
};

//�ʿ�ѪС��������ݽṹ
struct qc_plt_data
{
	 char plt[6]; 		//ѪС����� ������Χ��120-300 G/L
	 char mpv[6]; 		//ƽ��ѪС����� ������Χ��9.4-12.5 fl
	 char pct[6]; 		//ѪС��Ȼ�  ������Χ��0.108-0.282 %
	 char pdw[6]; 		//ѪС������ֲ���� ������Χ��15.0-18.0 fl  	
};

//�ʿز��Խ��
struct qc_result_data
{
	unsigned int row;		//��¼��

	struct qc_wbc_data wbcdata;
	struct qc_rbc_data rbcdata;
	struct qc_plt_data pltdata;

	unsigned char lmnegraph[MATRIX_DATA_MAX];
	unsigned char basograph[256];
	unsigned char rbcgraph[512];
	unsigned char pltgraph[256];

	 char lmneflg[9];	//������1���쳣��2
	 char basoflg[1];
	 char rbcflg[2];
	 char pltflg[2];

	 char qctype;			//��Ӧ���ʿر༭����ʿ�����
	 char filenum;			//��Ӧ���ʿر༭����ļ���
	 int time;				//ʱ��
	 char date[11];
};
typedef struct qc_result_data qcresult_info;

//�ʿز������ʿ�Ʒ����
struct qc_edit_data
{
	 char qctype;			//�ʿ����ͣ�1:L-J�ʿأ�2:X�ʿأ�3:X-R�ʿ�
	 char filenum;			//�ļ���
	 char Number[13];		//����	
	 char Deadline[11];	//��ֹʱ��
	struct qc_wbc_data wbctarget;
	struct qc_rbc_data rbctarget;
	struct qc_plt_data plttarget;
	struct qc_wbc_data wbcsd;
	struct qc_rbc_data rbcsd;
	struct qc_plt_data pltsd;
};
typedef struct qc_edit_data qc_edit_data_info;

//----------------------------------------
//��ӡ�����ò���
struct printer_config
{
	unsigned char mode;	//0x00:�ֶ���ӡ,0x01:�Զ���ӡ
	unsigned char format;	//0x00:��ͼ,0x01:����ͼ		//xx22 ��ʱû����
	unsigned char size;	//0x00:A4,0x01:A5
};

//�ϴ�����
struct com_config
{
	unsigned char baudrate;	//��������ѡ��  0:9600  1:19200 2:57600  3:115200 
	unsigned char upload;    	//�ϴ���ʽ      0:automatic   1:manual
	//���ݸ�ʽѡ��
};

//��Χ����ֵ����
struct range_config
{
	//��Χ����
	unsigned char type;				//��������Ĭ�Ϸ�Χ����	
	float normal[8][56]; 			//����������Χ��[8][56]�ֱ�Ϊ ͨ�ã����У���Ů������������ͯ���Զ���1,2,3
	//��ֵ	
	unsigned char thresholds[25];	//��ֵ
	unsigned char	thresholds_qc[3];
};

//�¶ȿ���
struct temperature_param	//xx22 ��ɲ���С���ģ�̫��ȷû���塣��ʱû���õ����¶ȿ��ơ�DSP���¶ȴ�����
{
	float env;				//�����¶��趨ֵ(�������¶�)
	float incub;			//�������¶��趨ֵ�������¶ȿ���ֵ(��߱����ŵĹ�·���¶�)
};

struct regent_fullamount  	//�Լ�ÿƿ������
{
	unsigned int diluent;	//��λ0.1ml
	unsigned int rinse;			
	unsigned int hgblyse;
	unsigned int eoslyse;
	unsigned int baslyse;
};

struct regent_date
{	
	int startyear[5];
	int startmonth[5];
	int startday[5];
	int endyear[5];
	int endmonth[5];
	int endday[5];
};
//��������
struct modify_param
{
	//�������ӣ��������WBC, PLT, RBC, BASO ,HGB, LYM, MON, NEU, EOS, LAY, LIC��
	float a[11];
	float b[11];
	float c[11];
};

//�ʿ�ϵͳ����
struct qualitycontrol_config	//�ʿ�ֻ��ȫѪ+5Diffģʽ������ģʽ����Ҫ
{
	//X-B�ʿز���
	unsigned char XB_on;		//XB�ʿأ�1:�򿪣�0:�ر�
	unsigned int XB_group_num;	//ÿ����Ŀ,��Χ20-200
	unsigned char mcvtarget[6];
	unsigned char mchtarget[6];
	unsigned char mchctarget[6];
	unsigned char mcvsd[6];
	unsigned char mchsd[6];
	unsigned char mchcsd[6];
};

//��Ȩ�û�ϵͳ���ò���
struct system_config3
{
	unsigned char first_use;		//�����ʾ����

	unsigned char structure;		//�����ṹ��1:������,2:����,3:�Զ�����
	unsigned char screen;			//��Ļ��    1:�Ǵ�����,2:������
	unsigned char diluent;			//ȡ����:1->20UL;	2->50UL
};
typedef struct system_config3 syscfg3;

//�����û�ϵͳ���ò���
struct system_config2
{
	unsigned char first_use;		//�����ʾ����

	char company[31];	//��˾����
	char model[16];		//�����ͺ�
	//unsigned char regentwarn_on;	//�Լ����������1:�򿪣�0:�ر�
	bool warn_diluent;
	bool warn_rinse;
	bool warn_hgb;
	bool warn_fix;
	bool warn_baso;
	bool warn_waste;
	unsigned char PcConMode;		// 1-���ڣ�2-����
	char ipaddr[16];
	int netport;
	int rsspeed;					//��λus�ϴ����ã������֮�䴫���ʱ���������������������ڵĻ��Ͳ���Ҫ���������
};
typedef struct system_config2 syscfg2;

//��ͨ�û�ϵͳ���ò���
struct system_config
{
	unsigned char first_use;		//�����ʾ����

	unsigned char hospital[41];		//ҽԺ��������,40��Ӣ���ַ���20������
	unsigned char cleanperiod;		//�Զ���ϴʱ�����������೤ʱ��δ����DSP���������Զ���ϴ
	unsigned char washfrequency;	//�Զ���ϴ����(�����������ٴ��Զ���ϴ)���ػ��Ժ�����
	unsigned char sleeptime;		//����ʱ�䣬sleep_time30,40,50,60����
	unsigned char miniprimetime;	//΢��ע��30,40,50,60���ӣ���ʱ�䲻�����ԣ����ٲ�����ʾ��MiniPrime	//xx22 miniprime ��Ҫ���������ʱ������ʱprime��ֻ��Ҫ��AutoClean��ʱ��˳��ִ������prime�Ϳ���(����prime���̷��뵽AutoClean������ȥ)
	unsigned char datetype;		//���ڸ�ʽ

	unsigned char mode;			//����ģʽ 0:ȫѪ+CBC5DIFF,1:ȫѪ+CBC,2:Ԥϡ��+CBC5DIFF,3:Ԥϡ��+CBC
	unsigned char language;		//����ѡ��	
	unsigned char unitWBC;		//��λѡ��:0��1��2��3
	unsigned char unitRBC;
	unsigned char unitHGB;
	unsigned char unitMCVRDWSD;
	unsigned char unitMCH;
	unsigned char unitMCHC;
	unsigned char unitPLT;
	unsigned char unitMPV;

	struct printer_config printercfg;//��ӡ����
	struct com_config com;		//�ϴ�����
	struct range_config range;		//��Χ���ü���ֵ����
	struct temperature_param tmp;	//�¶Ȳ���
	struct regent_fullamount regentfull;	//�Լ�����
	struct regent_date regentdate;
	struct modify_param modify[4];//�������ӣ�ȫѪ+CBC5DIFF��ȫѪ+CBC��ϡ��Ѫ+CBC5DIFF��ϡ��Ѫ+CBC
	struct qualitycontrol_config qualitycontrol;		//�ʿز�������Ҫ��¼�ģ���Ҫ��X-B�ʿ�

	unsigned char lmnepeak1;		//ɢ��ͼ���迹��ֵ1
	unsigned char lmnepeak2;

	unsigned char PltRightThresholdMode;	//PLT����ֵģʽ��0:�ֶ�,1:�Զ�
	unsigned char LMNEMarkMode;				//LMNE������ƶ�ģʽ,0:�ֶ�,1:�Զ�

	unsigned int mstp[17];					//�������
	float calibration[4][5];				//�������ӣ�ȫѪ+CBC5DIFF��ȫѪ+CBC��ϡ��Ѫ+CBC5DIFF��ϡ��Ѫ+CBC

	unsigned int Autosamplerpara[10];//�Զ������������
};
typedef struct system_config syscfg;

struct regent_amount  	//the amount of regent �Լ�ʣ����
{
	unsigned int diluent;	//��λ0.1ml
	unsigned int rinse;		
	unsigned int hgblyse;
	unsigned int eoslyse;
	unsigned int baslyse;
};

//��־�ļ�����
struct log_file
{
	unsigned char first_use;		//�����ʾ����
	unsigned char totaltimesoftest;

	struct regent_amount regent;
	struct regent_date	regentdate;
	//����ͳ��
	unsigned int alertnum[ERRNUM + 1];	//alertnum[0]�ò���
};
typedef struct log_file lgfi;

struct Maintenance{
	int			first_use;
	int			TimesOfFriday;   		//����Ĵ���
	bool		m_bIs2ndFriday;
	int			TestedDay;
};
typedef struct Maintenance sMaintain;

//----------------------------------------
//������Ϣ���ݽṹ����Ա��Ҫ����ϵͳ��Ϣ���˹�������Ϣ
struct Patient_data_struct
{
	int			 row;				//���ݿ��¼��
	int			 number;			//���=���ڼӵ�����
	 char		 name[21];		//�������ȣ�������10�����֣���20��Ӣ���ַ�
     char		 sex;			//�Ա�0:��,1:Ů,2:��
	 char		 rangetype;		//���ݷ�Χ���
	 char		 age[4];			//���䣬��int�Ͳ��ܽ�Լ�ռ䣬ֱ����char�ͣ���ʾ��ӡʱ���������ж�
	 char		 code[22];		//������21λ���ȵ�����
	 char		 technician[31];	//���ҳ��ȣ�������15�����֣���30��Ӣ���ַ�
	 char		 doctor[21];		 //ҽ��������������10�����֣���20��Ӣ���ַ�
};
typedef struct Patient_data_struct patient_info;

//ҽ����Ϣ���ݽṹ����Ա��Ҫ����ϵͳ��Ϣ���˹�������Ϣ
struct Doctor_data_struct
{
	long			 id;				//id
	//int			 row;			//�к�
	
	char		 name[21];		//�������ȣ�������10�����֣���20��Ӣ���ַ�
	char		 memo[100];		//��ע��100���ֽ�

};
typedef struct Doctor_data_struct doctor_info;


//----------------------------------------
//��ϸ���������ݽṹ
struct wbc_data
{
	char		wbc[6];		//��ϸ������ ������Χ��4.0-10.0 G/L
	char		lymp[6];	//�ܰ�ϸ���ٷֱ�������Χ��
	char		neup[6];	//������ϸ���ٷֱ� ������Χ��
	char		monop[6];	//��ֵϸ�ٷֱ� ������Χ��
	char		eosp[6];	//���������ٷֱ�������Χ��20.0-40.0 %
	char		basp[6];	//�ȼ������ٷֱ� ������Χ��3.0-8.0 %
	char		alyp[6];		//�����ܰͰٷֱ� ������Χ��3.0-8.0 %
	char		licp[6];		//�޴󲻳���ٷֱ� ������Χ��3.0-8.0 %
	char		lym[6];		//�ܰ�ϸ������ ������Χ��1.0-3.3 G/L  
	char		neu[6];		//������ϸ������ ������Χ��1.8-6.4 G/L
	char		mono[6];	//��ֵϸ������ ������Χ��0.2-0.9 G/L
	char		eos[6];		//��������ϸ������ ������Χ��
	char		bas[6];		//�ȼ�����ϸ������ ������Χ��
	char		aly[6];		//�����ܰ�ϸ������ ������Χ��
	char		lic[6];		//�޴󲻳���ϸ������ ������Χ��
};

//��ϸ���������ݽṹ
struct rbc_data
{
	char		rbc[6];		//��ϸ������ ������Χ��3.50-5.50 T/L
	char		hgb[6];		//Ѫ�쵰��Ũ�� ������Χ��110.0-160.0g/L
	char		hct[6];		//��ϸ��ѹ�� ������Χ�� 37.0-49.0 %
	char		mcv[6];		//ƽ����ϸ�����  ������Χ��80.0-100.0 fl
	char		mch[6];		//ƽ����ϸ��Ѫ�쵰�׺���  ������Χ��27.0-33.0 Pg
	char		mchc[6];	//ƽ����ϸ��Ѫ�쵰��Ũ��  ������Χ��320-360  g/l
	char		rdwcv[6];	//��ϸ������ֲ���� ������Χ��1.0-14.0 %
	char		rdwsd[6];	//��ϸ������ֲ���ȱ�׼��    �ο�:  35��45fl 
};

//ѪС��������ݽṹ
struct plt_data
{
	char		plt[6];		//ѪС����� ������Χ��120-300 G/L
	char		mpv[6];		//ƽ��ѪС����� ������Χ��9.4-12.5 fl	
	char		pdw[6];		//ѪС������ֲ���� ������Χ��15.0-18.0 fl
	char		pct[6];		//ѪС��Ȼ�  ������Χ��0.108-0.282 %	
	char		plcr[12];		//12fL���ϴ���ѪС����� % 	
};

//������Ϣ�ṹ��
struct blood_data
{
	int				row;			//���ݿ��¼��
	struct wbc_data wbcdata;		//��ϸ��������Ϣ
	struct rbc_data rbcdata;		//��ϸ��������Ϣ
	struct plt_data pltdata;		//ѪС���������	

	unsigned char			lmnegraph[MATRIX_DATA_MAX];	//ɢ��ͼֱ��ͼ2011.1.27 wsm,���������Ȼ��������
	unsigned char			basograph[256];	//��ϸ��ֱ��ͼ
	unsigned char			rbcgraph[512];	//��ϸ��ֱ��ͼ
	unsigned char			pltgraph[256];	//ѪС��ֱ��ͼ

	char			lmneflg[9];		//NO, LL, LL1, NL, MN, RM, LN, RN, NE���
	char			basoflg[1];		//L1���
	char			rbcflg[2];		//MIC, MAC���
	char			pltflg[4];		//Ԥ�����,��ʾ��־

	 int			number;			//���=���ڼӵ�����
	int				time;				//ʱ��
	char			mode;			//����ģʽ
	char			flag_wrp[4];         //�ж�wbc,rbc & plt���β����Ƿ����ϴ�ı�־ add:20150104
	float			coeoflmne;	//���float��
};
typedef struct blood_data sample_info;

//����ṹ��
struct task_data
{
	int				number;
	int				row;			//���ݿ��¼��
	char			sex;			//�Ա�0:��,1:��,2:Ů
	char			age[4];
	char			mode;			//����ģʽ 0:ȫѪ+CBC5DIFF,1:ȫѪ+CBC,2:Ԥϡ��+CBC5DIFF,3:Ԥϡ��+CBC
	char			name[21];		//�������ȣ�������10�����֣���20��Ӣ���ַ�
	char			doctor[21];		//ҽ��������������10�����֣���20��Ӣ���ַ�
	char			status[10];		//����״̬
	char			time[10];		//����ʱ��
	char			barcode[15];	//������
	char			department[20];	//����
	int				taskmode;	    //������ʽ��0���������� 1����ϴ����
};
typedef struct task_data task_info;

//Yes_No�Ի���
typedef struct{
	const char* 	caption;    //�Ի������
	const char* 	message;	//��ʾ��Ϣ
	uchar 		type;			//MBOX_YESNO | MBOX_OKCANCEL
}MesBox;
typedef MesBox* pMesBox;

//��ѯ���ݿ�
typedef struct{
	char*	sqlque;			//SQL���
	char**	dbResult;		//�洢��������
	int		nRow;			//��������
	int		nColumn;		//��������
	char*	zErrMsg;		//������Ϣ
}SqliteQue;
typedef SqliteQue*	pSqliteQue;

//LMNEɢ��ͼ��������
typedef struct{
	uchar	X_NOL;
	uchar	X_NON;
	uchar	X_LL;
	uchar	X_LN;
	uchar	X_NOE;
	uchar	X_AL;
	uchar	X_LMN;
	uchar	X_LMU;
	uchar	X_MN;
	uchar	X_LMD;
	uchar	X_RM;
	uchar	X_RN;
	uchar	Y_NL;
	uchar	Y_RMN;
	uchar	Y_NE;
} B_LMNE;

/*
typedef struct{
uchar 	ErrRecv[ERRNUM+1];
uchar 	ErrMess[ERRNUM];
uchar	ErrNum;
uchar	ErrMessShow;
} ErrorInfo;
typedef ErrorInfo* pErrorInfo;
*/

#endif
