#include "stdafx.h"
#include "Includes_app.h"
syscfg3 systemcfg3;
syscfg2 systemcfg2;
syscfg systemcfg;
lgfi logfile;
sMaintain m_sMaintain;
int cfg3_fd, cfg2_fd, cfg_fd, lgfi_fd;
int gpio_fd;
//extern sqlite3 *db;

unsigned int framelen[13];			//������֡����
//unsigned char key_status;  			//0:������Ч��1:������Ч
bool key_status;  			//0:������Ч��1:������Ч
unsigned int timeFrKd;					//���̰�����0��Ȼ��ʼ��ʱ�䣬��λΪ�룬�Զ�������
unsigned int DSPFreeTime;				//��¼DSP����ʱ�䣬��λΪ��
unsigned int timeFrKd9;				//�����Զ�����
unsigned int NumFromBoot;			//�����Ժ����Ĳ�������ִ�����Զ���ϴ����0
unsigned char sdata_cmd[1];
unsigned char rdata_state[1];

status DSP_status;
// 0(free):DSP���У�����ͨ����(ARM�ɷ����κ������DSP) 
// 1(busy):DSPæµ��ͨ����(���ܷ����κ������DSP)������1��ʱ�򣬿ɽ��в�ѯ������Ȳ��������漰DSP�Ĳ���(��ʱû��ô�ã���ʱ�����ɲ���)	
// 2(clean):DSP������������ϴ(�ܷ��Ͳ��������DSP������������ܷ���DSP)
unsigned char PC_status;


time_t systime;		//������ʱ��
struct tm rtm;  		//Ŀ���ʱ��
struct tm *caltime;	//ʱ��

unsigned char hgbgraph[4];		//DSP��������HGBֵ���ҳ���10
//�ڶ�������
unsigned char basograph_2[256];
unsigned char rbcgraph_2[512];
unsigned char pltgraph_2[256];

//������Ϣ
// 1-X�����2-Y�����3-SM�����4-DIM�����5-DRM�����6-CTM�����7-CYM�����8-WBC�¿ף�9-RBC�¿ף�10-��Һʱ�����
unsigned char errorShowMess;		//��ǰҪ��ʾ�Ĵ�������,0:û����
unsigned char errorShowNum;		//��ǰҪ��ʾ�Ĵ�������������errorMessage�е��±�
unsigned char errorNumber;		//���д���ĸ���
unsigned char errorMessage[ERRNUM];	//��Ҫ��ʾ�Ĵ������ͱ��룬���鳤��Ϊ����������
unsigned char errorReceive[ERRNUM + 1];	//��DSP���յ������ݣ�����������+1��errorReceive[0]�ò���
//״̬��Ϣ
unsigned char statusShowMess;		//����״̬��RECT STATUS������ʾ 0-���� 1-���� 2-��ϴ3-�ȴ�����4-�Զ���ϴ��

unsigned int		operator_right;

bool IsMainTop;

unsigned char 		PLTRightBorderStylus;
unsigned char		PLTRightBorderQuery;

unsigned int  Controltype;//L-J�ʿأ�0��X�ʿأ�1�� X-R�ʿأ�2��
unsigned int  Controlfile;//0,1,2,3,4,5,6,7,8��Ӧ�ļ�1,2,3,4,5,6,7,8,9

int				CurView;//��ǰ����
HANDLE			SendMutex;//�����������Ʒ�����Ϣ
HANDLE			SendEvent;//�����������Ʒ�����Ϣ
HANDLE			 TestmainEvent = NULL;//��ѯ�������߳̿����¼�
HANDLE			hEvent = NULL;//��ѯ�������߳̿����¼�

bool			Reconnection=FALSE;//�ж��Ƿ��ڽ���������

uchar		temp = 0;
uchar* 		pIsSuper=&temp;

int ListFocusItem;
//char	PC_status;