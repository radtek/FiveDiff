#include "stdafx.h"
#include "ThreadAS.h"
#include "TestmainView.h"
//#include "Includes_app.h"

#define		SMAX_AS			20
#define		LMAX_AS			50

bool Allow_ASOnLine;
bool AS_OnLine;				//�Զ�����ϵͳ��������������-1(START)��δ��������-0(OVER)
bool ASCur_EN;				//��ǰ����ʹ�ܡ�1��Ч���ܹ���������Ѫ������������Ѫ��(ִ���Զ�ά������ʾ���ݿ���������ʱ��ͣ)

CThreadAS::CThreadAS()
{

}


CThreadAS::~CThreadAS()
{
}

//�жϽ��յ����ַ����Ƿ����
int CThreadAS::CompDataRead(uchar * src, const uchar *obj)
{
	uchar*	smove = src;
	uchar*	omove = const_cast<uchar *>( obj);

	while (smove != src + SMAX_AS - 4 && omove != obj + 4)
	{
		if (*smove == *omove && *(smove + 1) == *(omove + 1))
		{
			if (*(smove + 2) == *(omove + 2) && *(smove + 3) == *(omove + 3))
				return 0;
		}

		smove++;
	}

	return RedWrong;
}

//��������,��ʼ����
int CThreadAS::TryConnect(const char *AllowStart, int* ASCur_Step)
{
	int		m_nwt = 0;
	int		m_nrd = 0;
	int		i;
	uchar	buffRd[SMAX_AS] = { 0 };

	m_nwt = m_newCom.ComWrt(2, AllowStart, 3,115200);	//���������Զ�����ϵͳ��������

	if (m_nwt ==false)
	{
		fprintf(stderr, "write AllowStart to ThreadAS failed---------!\n");
		return WrtErr;
	}

	timeFrKd9 = 0;
	while (1)		//ѭ��1s�ȴ�
	{
		if (timeFrKd9 > 0)
			return TimeOut;

		for (i = 0; i < SMAX_AS; i++)
			buffRd[i] = 0;
		if (Allow_ASOnLine)
		{
			m_nrd = m_newCom.ComRd(0, buffRd, SMAX_AS,115200);
			if (m_nrd ==false)
				continue;

			if (0 == CompDataRead(buffRd, (const unsigned char*)"STAT"))	//Ӧ���ź�Start����������
			{
				key_status = FALSE;		//��Ӧ���źź󣬽�ֹ�����������Զ�����
				AS_OnLine = TRUE;
				ASCur_EN = TRUE;
				*ASCur_Step = 0;

				//����ʼ����ʱ���ڴ���״̬���������Ļ	
				if (timeFrKd >= 60 * systemcfg.sleeptime) //60
				{
					fprintf(stderr, "..........active in the ThrsAS   tryconnect..............\n");
					//SendMessage(MainWindowhDlg, MSG_COMMAND, MSG_ACTIVATESCREEN, 0L);
				}
				return 0;
			}
		}
	}
}

int CThreadAS::Step0(int* ASCur_Step)
{
	int		i;
	int		m_nrd = 0;
	uchar	buffRd[SMAX_AS] = { 0 };

	//�ж��Ƿ�OVER�����OVER������
	for (i = 0; i < SMAX_AS; i++)
		buffRd[i] = 0;

	m_nrd = m_newCom.ComRd(0, buffRd, SMAX_AS,115200);
	if (m_nrd == false)
		return RedErr;

	if (0 == CompDataRead(buffRd, (const unsigned char*)"OVER"))     //Over
	{
		SendOver(ASCur_Step);
	}

	//�ж��Ƿ������һ��
	if (ASCur_EN)
	{
		if (Free == DSP_status || Clean == DSP_status)//����ͨ����(��ζ�ɽ����Զ�����ϵͳ��������)
		{
			*ASCur_Step = 1;
		}
	}

	return 0;
}

int CThreadAS::Step1(const char* wtData, const char* response, int* ASCur_Step)
{
	int		m_nwt = 0;
	int		m_nrd = 0;
	int		i;
	uchar	buffRd[SMAX_AS] = { 0 };

	m_nwt = m_newCom.ComWrt(0, wtData, 3,115200);	//�������������ź�
	if (m_nwt == false)
	{
		fprintf(stderr, "write AskSample to ThreadAS failed---------!\n");
		return -1;
	}

	timeFrKd9 = 0;
	while (1)		//ѭ��1s�ȴ�
	{
		if (timeFrKd9 > 0)
			return TimeOut;

		for (i = 0; i < SMAX_AS; i++)		//buffRe[4]�ַ���ֹλ
			buffRd[i] = 0;

		if (Allow_ASOnLine)
		{
			m_nrd = m_newCom.ComRd(0, buffRd, SMAX_AS,115200);
			if (m_nrd =false)
				continue;

			//�ж��Ƿ�Ӧ��
			if (0 == CompDataRead(buffRd, (const uchar*)response))	//Ӧ���ź�
			{
				key_status = FALSE;		//��Ӧ���źź�������
				*ASCur_Step = 2;

				break;
			}
			//�ж��Ƿ�OVER�����OVER������
			else if (0 == CompDataRead(buffRd, (const unsigned char*) "OVER"))
			{
				SendOver(ASCur_Step);

				break;
			}
			else
				return RedWrong;
		}
	}
	return 0;
}

int CThreadAS::Step2(const char* CodeR, int* ASCur_Step)
{
	int		m_nwt = 0;
	int		m_nrd = 0;
	int		i;
	int		ASMode = -1;
	uchar	buffRd[LMAX_AS] = { 0 };
	uchar	buffGet[30] = { 0 };

	for (i = 0; i < LMAX_AS; i++)      //���ݳ���:24 + 5
		buffRd[i] = 0;
	m_nrd = m_newCom.ComRd(0, buffRd, LMAX_AS,115200);
	if (m_nrd = false)
		return RedErr;

	ASMode = getASMode(buffRd, buffGet);

	if (0x08 == ASMode || 0x0F == ASMode || 0x7F == ASMode)			//�Զ�������ֹ�ģʽ
	{
		//SendMessage(MainWindowhDlg, MSG_COMMAND, IDM_MAIN_TEST, 0L);//
		if (0x08 == ASMode)
		{
			CTestmainView::GetASBarcode((char*)buffGet);//�Զ�����ģʽ��������룬�����ֹ�ģʽ������������
		}
		for (i = 0; i < 6; i++)
		{
			m_nwt = m_newCom.ComWrt(0, CodeR, 3,115200);		//����Ӧ���źţ�����6��
			if (m_nwt == false)
			{
				fprintf(stderr, "write CodeR to ThreadAS failed---------!\n");
				return WrtErr;
			}
		}
		*ASCur_Step = 3;
	}//elseδ�����������ٴδ���
	else
		return RedWrong;

	return 0;
}

int CThreadAS::Step4(const char* wtData, const char* response, int* ASCur_Step)
{
	int		m_nwt = 0;
	int		m_nrd = 0;
	int		i;
	uchar	buffRd[SMAX_AS] = { 0 };

	m_nwt = m_newCom.ComWrt(0, wtData, 3,115200);		//���Ͳ�������ź�
	if (m_nwt == false)
	{
		fprintf(stderr, "write SampleOver to ThreadAS failed---------!\n");
		return WrtErr;
	}

	timeFrKd9 = 0;
	while (1)//ѭ��1s�ȴ�
	{
		if (timeFrKd9 > 0)
			return TimeOut;

		for (i = 0; i < SMAX_AS; i++)		//buffRe[4]�ַ���ֹλ
			buffRd[i] = 0;

		if (Allow_ASOnLine)
		{
			m_nrd = m_newCom.ComRd(0, buffRd, SMAX_AS,115200);
			if (m_nrd =false)
				continue;

			if (0 == CompDataRead(buffRd, (const uchar*)response))	//Ӧ���ź�
			{
				*ASCur_Step = 0;
				return 0;
			}
			else
				return RedWrong;
		}
	}
}

inline void CThreadAS::SendOver(int *ASCur_Step)
{
	int 			i;
	int			m_nwt;

	for (i = 0; i < 6; i++)
	{
		m_nwt = m_newCom.ComWrt(0, "OVR", 3,115200);	//����Ӧ���źţ�����6��
		if (m_nwt ==false)
			fprintf(stderr, "write OverR to ThreadAS failed---------!\n");
	}
	AS_OnLine = FALSE;
	ASCur_EN = FALSE;
	*ASCur_Step = 0;
}

//��������ģʽ
int CThreadAS::getASMode(const uchar *buffRd, uchar* buffGet)
{
	uchar 	i;
	uchar 	checknum = 0;
	int		Mode = 0;

	const uchar* 	move = buffRd;

	while (move != buffRd + LMAX_AS - 29)
	{
		if (*move == 0x02)
		{
			if (*(move + 1) == 0x68)
			{
				if (*(move + 3) == 0x08)
				{
					//У��ͼ���
					checknum = 0;
					for (i = 0; i < 28; i++)
						checknum += *(move + i);

					if (*(move + 28) == checknum)//�Զ�ģʽ
					{
						fprintf(stderr, "AutoSample Automatical Model\n");
						Mode = 0x08;
						break;         //����������ȷ
					}
					else
					{
						fprintf(stderr, "ThreadAS->checknum error:%0X---------#\n", *(move + 28));
						Mode = -4;
					}
				}
				else if (*(move + 3) == 0x0F)//����ģʽ
				{
					fprintf(stderr, "AutoSample Emergency model\n");
					Mode = 0x0F;
					break;
				}
				else if (*(move + 3) == 0x7F)//�ֹ�ģʽ
				{
					fprintf(stderr, "AutoSample Manual model\n");
					Mode = 0x7F;
					break;
				}
				else
				{
					fprintf(stderr, "ThreadAS->0x0F or 0x08 error:%0X---------#\n", *(move + 3));
					Mode = -3;
				}
			}
			else
			{
				fprintf(stderr, "ThreadAS->0x68 error:%0X---------#\n", *(move + 1));
				Mode = -1;
			}
		}
		else
		{
			Mode = 0;
		}

		move++;
	}

	memset(buffGet, 0, 29);

	if (Mode == 0x08 || Mode == 0x0F || Mode == 0x7F)
		for (i = 0; i < 29; i++)
			*(buffGet + i) = *(move + i);

	return Mode;
}

/***********************************************************
*Function:	ThreadAS
*Description:	�Զ����������߳���ں���
*Called by:
*Params illustration:
*Other:
*History:
************************************************************/
void *CThreadAS::ThreadAS(void)
{
	int 			ASCur_Step;
	int			Flag;

	const char 	AllowStart[] = "AST";	//����:�����Զ�����ϵͳ��������Allow Start	
	const char 	OverR[] = "OVR";		//���յ��Զ�����ϵͳ��"OVER"�ظ�һ��Ӧ�𣬶Ͽ����Ӽ�AS_OnLine��0
	const char 	AskSample[] = "ASK";	//����:��������	
	const char 	SampleOver[] = "SOK";	//����:������ɣ������Թ�
	const char 	CodeR[] = "CDR";		//������Ӧ���ź�

	Allow_ASOnLine = FALSE;
	AS_OnLine = FALSE;
	ASCur_EN = FALSE;
	ASCur_Step = -1;

	while (1)
	{
		//��������?
		if (!Allow_ASOnLine)
		{
			Sleep(100);//��λus������һֱ��Allow_ASOnLine��1�Ƚϣ��׳�����
			continue;
		}
		if (!AS_OnLine)
		{
			Flag = TryConnect(AllowStart, &ASCur_Step);
			if (Flag < 0)
			{
				fprintf(stderr, "Connecting Error info: Flag %d \n", Flag);
				Sleep(100);
			}
		}
		//�������������ڵ�״̬	
		if (AS_OnLine && 0 == ASCur_Step)
		{
			Flag = Step0(&ASCur_Step);
			if (Flag < 0)
			{
				fprintf(stderr, "Step0 Error info: Flag %d \n", Flag);
				Sleep(1);    //0.1s
			}
		}
		//��������
		if (AS_OnLine && 1 == ASCur_Step)
		{
			Flag = Step1(AskSample, "ASKR", &ASCur_Step);
			if (Flag < 0)
			{
				fprintf(stderr, "Step1 Error info: Flag %d \n", Flag);
				Sleep(1);    //0.1s
			}
		}
		//����ģʽ������Ϣ
		if (AS_OnLine && 2 == ASCur_Step)
		{
			static int TimesofStep2 = 0;

			Flag = Step2(CodeR, &ASCur_Step);
			if (Flag < 0)
			{
				fprintf(stderr, "Step2 Error info: Flag %d \n", Flag);
				TimesofStep2++;
				Sleep(1);     // 1ms
			}
			else
				TimesofStep2 = 0;

			if (TimesofStep2 == 9)
			{
				int i;
				for (i = 0; i < 6; i++)
					m_newCom.ComWrt(0, CodeR, 3,115200);
				SendOver(&ASCur_Step);
			}
		}
		//�ȴ����Խ���
		if (AS_OnLine && 3 == ASCur_Step)
		{
			if (WAITING_DATA == PC_status)//���������ѽ�������ȴ�����״̬
				ASCur_Step = 4;
		}
		//֪ͨASװ�ò��Խ���
		if (AS_OnLine && 4 == ASCur_Step)
		{
			Flag = Step4(SampleOver, "SOKR", &ASCur_Step);
			if (Flag < 0)
			{
				fprintf(stderr, "Step4 Error info: Flag %d \n", Flag);
				Sleep(1);    // 1ms
			}
		}
	}
}
