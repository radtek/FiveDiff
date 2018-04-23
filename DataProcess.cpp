#include "stdafx.h"
#include "BCGPChartExample.h"
#include "Includes_app.h"




DataProcess::DataProcess()
{
}


DataProcess::~DataProcess()
{
}


/*************************************************
Copyright (C), SINNOWA. Co., Ltd.
File name: 	DataProcess.c
Author:	liguoqing	Version:	1.0	Date: 2010-07-07
Description: 	���ݴ���
Others:     	���Ľ�: ResultsAnalysisֻ������ԭʼ����
���ǲ�ѯ��ʱ��û��ɢ��ͼ
��ͼ����Ϊһ�ڵ��ã����Ժ�ƽ���侲̬ȫ�ֱ��������乲��
2011.1.1���ݿ��д�ŵĶ���ԭʼ����(Ӱ��Ч�ʣ��������պ�Ķ�)
Important:
���뽫�洢�����ݿ��0x00�����⴦������һ������0x00�浽���ݿ�
����Ϊ���ַ�����ֹ��������ʽ�����е����ݴ����ʱ��ͳһ��1
�����ݿ�ȡ����¼����ʱ��ͳһ��ȥ1
Function List:
History:
create	wsm 	2010.11.4
*************************************************/

//������������궨��
#define VOLAMP_WBCBASO 	0.0015 	//WBCBASO����ͷŴ���ر���
#define VOL_RBCPLT			0.00027	//����������ϵ��
#define AMP_RBC				0.97		//RBC�Ŵ������
#define AMP_PLT				0.125	//PLT�Ŵ������

//��ͼ��غ궨��
#define LMNE_LEFT		340
#define LMNE_BOTTOM 	365
#define LMNE_WIDTH		200//540-340  [0,255]->[340,540]
#define LMNE_HEIGHT		200

#define BASO_LEFT		570
#define BASO_BOTTOM	305
#define BASO_WIDTH		204//774-570	[0,255]->[570,774]
#define BASO_HEIGHT		105

#define RBC_LEFT			340
#define RBC_BOTTOM		525
#define RBC_WIDTH		204//544-340
#define RBC_HEIGHT		105

#define PLT_LEFT			570
#define PLT_BOTTOM		525
#define PLT_WIDTH		204    //774-570
#define PLT_HEIGHT		105    //525-420

#define COECALNUM		10

//HWND MainTestDlg;

//int  PLTGraphEnd = 133;
extern int PLTGraphEnd=133;

float		wbc_lmne = 0.0;

//���ڿ������������� TestWin.c ���б�������
extern bool StartupBlankTestsflag;
extern float StartupBlankTestswbc;
extern float StartupBlankTestsrbc;
extern float StartupBlankTestsplt;
extern bool IsBlankTest;

extern char 	studyPara[8][6];



static char 		wbc_hided_1[6], wbc_hided_2[6];	//���ڼ�¼����WBC�Ľ��	
static char 		rbc_hided_1[6], rbc_hided_2[6];
static char 		plt_hided_1[6], plt_hided_2[6];


//�ӽ��ܵ�����֡�н����ĸ���ϸ���ĸ���������ֱ����sample_info�еĽṹ�����
//��ɢ��ͼ�ã��˱�������Ƚ����⣬ʹ��ʱҪע��
//���ʺ����б�:
//�ӽ��ܵ�����֡�н�����ɢ���ϸ������
static const char *static_param[28] =
{
	"WBC",
	"LYM%",
	"NEU%",
	"MONO%",
	"EOS%",
	"BASO%",
	"ALY%",
	"LIC%",
	"LYM#",
	"NEU#",
	"MONO#",
	"EOS#",
	"BASO#",
	"ALY#",
	"LIC#",
	"RBC",
	"HGB",
	"HCT",
	"MCV",
	"MCH",
	"MCHC",
	"RDW-CV",
	"RDW-SD",
	"PLT",
	"MPV",
	"PDW",
	"PCT",
	"P-LCR"
};
//����
static const char *static_sampinfo_cn[6] =
{
	"���:",
	"����:",
	"�Ա�:",
	"����:",
	"����:",
	"����:"
};
//Ӣ��
static const char *static_sampinfo_en[6] =
{
	"No.:",
	"Name:",
	"Sex:",
	"Dept.:",
	"Age:",
	"Code:"
};
static const char *static_unit_WBC[4] =
{
	"10^9/L",
	"10^3/uL",
	"10^2/uL",
	"/nL"
};
static const char *static_unit_RBC[4] =
{
	"10^12/L",
	"10^6/uL",
	"10^4/uL",
	"/pL"
};
static const char *static_unit_HGB[3] =
{
	"g/L",
	"g/dL",
	"mmol/L"
};
static const char *static_unit_MCVRDWSD[2] =
{
	"fL",
	"um^3"
};
static const char *static_unit_MCH[2] =
{
	"pg",
	"fmol"
};
static const char *static_unit_MCHC[3] =
{
	"g/L",
	"g/dL",
	"mmol/L"
};
static const char *static_unit_PLT[4] =
{
	"10^9/L",
	"10^3/uL",
	"10^4/uL",
	"/nL"
};
static const char *static_unit_MPV[2] =
{
	"fL",
	"um^3"
};
double DataProcess::WbcForCompare = 0.0;
/***********************************************************
*Function:
*Description:��WBC  RBC  PLT �������ݽ��бȽ�
*Called by:
*Params illustration:
*Data Access:
*History:
************************************************************/
void DataProcess::BasoLmneRbcPlt_2Analyse(sample_info *psampledata)
{
	unsigned short int i = 0;
	unsigned char start = 0, end = 0;
	signed int count_1, count_2;
	float countResult = 0.0;

	//count_wbc_flag = 0;
	//count_rbc_flag = 0;
	//count_plt_flag = 0;
	TRACE("\nTwoGroupResultsAnalysis()====================\n");
	//BASO
	count_1 = 0;
	count_2 = 0;
	start = systemcfg.range.thresholds[BA1];
	end = systemcfg.range.thresholds[BA3];
	for (i = start; i <= end; i++)
	{
		count_1 += (*psampledata).basograph[i];//��ϸ��ֱ��ͼ����[256]
		count_2 += basograph_2[i];//�ڶ�������
	}
	TRACE("WbcBaso->wbc_count_1=%d----------#\n", count_1);
	TRACE("WbcBaso->wbc_count_2=%d----------#\n", count_2);

	if (count_1 >= 200)				//��Ӧwbc >= 0.3�������ǿհײ���
	{
		if (count_1 <= 2666)		//��Ӧwbc < 4.0
		{
			//if(1.0*fabs(count_1 - count_2)/count_1 > 1.00)			//FDparam 0.50,0.20,0.15����ȷ��
			if (1.0*fabs((double)(count_1 - count_2)) / count_1 >= 0.50)
			{
				(*psampledata).flag_wrp[0] = 2;
				//count_wbc_flag = 1;
			}
		}
		else if (count_1 <= 6666)	//��Ӧwbc <= 10.0
		{
			//if(1.0*fabs(count_1 - count_2)/count_1 > 1.00)
			if (1.0*fabs((double)(count_1 - count_2)) / count_1 >= 0.20)

			{
				//count_wbc_flag = 1;
				(*psampledata).flag_wrp[0] = 2;
			}
		}
		else
		{
			//if(1.0*fabs(count_1 - count_2)/count_1 > 1.00)
			if (1.0*fabs((double)(count_1 - count_2)) / count_1 >= 0.15)
			{
				//count_wbc_flag = 1;
				(*psampledata).flag_wrp[0] = 2;
			}
		}
	}

	if (count_1 <= 66666)		//ȷ�����Խ��<100.00��Ȼ��ʹ��sprintfת����ʽ�浽���ݿ���û������
	{
		countResult = count_1*VOLAMP_WBCBASO;
		sprintf(wbc_hided_1, "%.2f", countResult);
	}

	if (count_2 <= 66666)		//ȷ�����Խ��<100.00��Ȼ��ʹ��sprintfת����ʽ�浽���ݿ���û������
	{
		countResult = count_2*VOLAMP_WBCBASO;
		sprintf(wbc_hided_2, "%.2f", countResult);
	}
	//RBC
	count_1 = 0;
	count_2 = 0;
	start = systemcfg.range.thresholds[RB1];
	end = systemcfg.range.thresholds[RB2];
	for (i = start; i <= end; i++)
	{
		count_1 += (((psampledata->rbcgraph[(i << 1) + 1]) << 8) + psampledata->rbcgraph[i << 1]);
		count_2 += (((rbcgraph_2[(i << 1) + 1]) << 8) + rbcgraph_2[i << 1]);
	}
	TRACE("Rbc->rbc_count_1=%d\n", count_1);
	TRACE("Rbc->rbc_count_2=%d\n", count_2);

	if (count_1 >= 186)					//��Ӧrbc >= 0.05������Ϊ���ǿհײ���	
	{
		if (count_1 <= 14814)			//��Ӧrbc < 4.0
		{
			//if(1.0*fabs(count_1 - count_2)/count_1 > 1.00)				//FDparam 0.50,0.20,0.15����ȷ��
			if (1.0*fabs((double)(count_1 - count_2)) / count_1 >= 0.50)
				//count_rbc_flag = 1;
				(*psampledata).flag_wrp[1] = 2;
		}
		else if (count_1 <= 20370)		//��Ӧwbc <= 5.5
		{
			//if(1.0*fabs(count_1 - count_2)/count_1 > 1.00)
			if (1.0*fabs((double)(count_1 - count_2)) / count_1 >= 0.20)
				//count_rbc_flag = 1;
				(*psampledata).flag_wrp[1] = 2;
		}
		else
		{
			//if(1.0*fabs(count_1 - count_2)/count_1 > 1.00)
			if (1.0*fabs((double)(count_1 - count_2)) / count_1 >= 0.15)
				//count_rbc_flag = 1;
				(*psampledata).flag_wrp[1] = 2;
		}
	}

	if (count_1 <= 370370)
	{
		countResult = count_1*VOL_RBCPLT;
		sprintf(rbc_hided_1, "%.2f", countResult);
	}

	if (count_2 <= 370370)
	{
		countResult = count_2*VOL_RBCPLT;
		sprintf(rbc_hided_2, "%.2f", countResult);
	}
	//PLT
	count_1 = 0;
	count_2 = 0;
	start = systemcfg.range.thresholds[PLT1];
	end = systemcfg.range.thresholds[PLT2];
	for (i = start; i <= end; i++)
	{
		count_1 += (*psampledata).pltgraph[i];
		count_2 += pltgraph_2[i];
	}
	TRACE("Plt->plt_count_1=%d\n", count_1);
	TRACE("Plt->plt_count_2=%d\n", count_2);

	if (count_1 >= 38)				//��ӦPLT >= 10 �����ǿհײ���
	{
		if (count_1 <= 370)			//��ӦPLT < 100
		{
			//if(1.0*fabs(count_1 - count_2)/count_1 > 1.00)				//FDparam 0.50,0.20,0.15����ȷ��
			if (1.0*fabs((double)(count_1 - count_2)) / count_1 >= 0.50)
				//count_plt_flag = 1;
				(*psampledata).flag_wrp[2] = 2;

		}
		else if (count_1 <= 1111)	//��ӦPLT <= 300
		{
			//if(1.0*fabs(count_1 - count_2)/count_1 > 1.00)
			if (1.0*fabs((double)(count_1 - count_2)) / count_1 >= 0.20)
				//count_plt_flag = 1;
				(*psampledata).flag_wrp[2] = 2;
		}
		else
		{
			//if(1.0*fabs(count_1 - count_2)/count_1 > 1.00)
			if (1.0*fabs((double)(count_1 - count_2))/ count_1 >= 0.15)
				//count_plt_flag = 1;
				(*psampledata).flag_wrp[2] = 2;
		}
	}

	if (count_1 <= 37037)
	{
		countResult = count_1*1000.0*VOL_RBCPLT;
		sprintf(plt_hided_1, "%.0f", countResult);
	}

	if (count_2 <= 37037)
	{
		countResult = count_2*1000.0*VOL_RBCPLT;
		sprintf(plt_hided_2, "%.0f", countResult);
	}
}

/***********************************************************
*Function:
*Description:	�Խ��յ�����֡������(rdata��ָ�ռ�)����
����(�����жϣ�������sampledata.basograph��ָ��Ŀռ�)
*Called by:
*Params illustration:
*Data Access:
*Other:
*History:	create	wsm		2010.12.31
************************************************************/
void DataProcess::WbcBasoAnalysis(sample_info *psampledata, uchar * pIsSuper)
{
	unsigned short int i, j;
	unsigned short int pointnum = 0;
	float dist_temp = 0.0;
	unsigned char tempbuff[256] = { 0 };
	unsigned char start = 0, mid = 0, end = 0;
	unsigned char maxval = 0;
	unsigned char threshold = 0;
	unsigned short int count_baso = 0;
	unsigned short int count_wbc = 0;
	unsigned short int temp0_BA1 = 0;	//[0,BA1)֮��ļ���
	float a = 0, b = 1.0, c = 0;
	float cal = 1.0;
	float wbc = 0;
	float baso = 0;
	float basop = 0;
	TRACE("\nBasoAnalysis()====================\n");

	for (i = 0; i < 256; i++)	//BASO���ݣ���256ͨ��
		tempbuff[i] = ((*psampledata).basograph[i] + basograph_2[i]) / 2;   // hw:20140521

	//ȡ��Ч���ݶ�(��ֵ�˲�)
	start = systemcfg.range.thresholds[BA1];
	mid = systemcfg.range.thresholds[BA2];
	end = systemcfg.range.thresholds[BA3];

	//��BASO����
	count_baso = 0;
	for (i = mid; i <= end; i++)
		count_baso += tempbuff[i];
	TRACE("count_baso=%d---------#\n", count_baso);

	//��WBC����
	count_wbc = count_baso;
	for (i = start; i < mid; i++)
		count_wbc += tempbuff[i];
	TRACE("count_wbc=%d---------#\n", count_wbc);

	//��[0,BA1)֮�������
	temp0_BA1 = 0;
	for (i = 0; i < start; i++)
		temp0_BA1 += tempbuff[i];
	TRACE("temp0_BA1=%d---------#\n", temp0_BA1);

	if (count_wbc > 0)//��֤��Ϊ0
	{
		//L1
		if ((float)temp0_BA1 / (temp0_BA1 + count_wbc) > 0.03)	//FDparam �ο�ABX
			(*psampledata).basoflg[0] = 2;
	}

	if (count_wbc <= 66666 && count_wbc > 0)	//ȷ�����Խ��<100.00��Ȼ��ʹ��sprintfת����ʽ�浽���ݿ���û������
	{
		//baso
		basop = (100.0*count_baso) / count_wbc;
		//baso#
		baso = count_baso*VOLAMP_WBCBASO;
		//wbc
		a = systemcfg.modify[systemcfg.mode].a[MOD_WBCF];
		b = systemcfg.modify[systemcfg.mode].b[MOD_WBCF];
		c = systemcfg.modify[systemcfg.mode].c[MOD_WBCF];
		wbc = count_wbc*VOLAMP_WBCBASO;
		WbcForCompare = wbc;
		wbc = systemcfg.calibration[systemcfg.mode][CAL_WBCF] * fabs(a*wbc*a*wbc + b*wbc + c);
	}

	maxval = tempbuff[start];
	for (i = start + 1; i <= end; i++)
		if (tempbuff[i] > maxval)
			maxval = tempbuff[i];
	TRACE("BASO->maxval=%d---------#\n", maxval);

	//threshold = (int)(maxval*(BASO_HEIGHT)/(BASO_HEIGHT+55.0));
	threshold = (int)((float)maxval*(BASO_HEIGHT) / (BASO_HEIGHT + 58.33));	//58.33��ʲô����û  xx22
	if (threshold != 0)
		cal = (float)BASO_HEIGHT / threshold;
	else
		cal = 1.0;

	//ͼ�ε���
	for (i = start; i <= end; i++)
	{
		if (tempbuff[i] > threshold)
			tempbuff[i] = BASO_HEIGHT;
		else
			tempbuff[i] *= cal;
	}

	//WBCֵС��0.3ͼ�β���ʾ
	if (wbc < 0.3)
	{
		for (i = 0; i < 256; i++)
			tempbuff[i] = 0;
	}
	else
	{
		//hw_temp:
		//	pointnum = 4;
		//	for(i = 0;i < 63;i++)
		//	{
		//		dist_temp = tempbuff[1 + pointnum*(i+1)] -tempbuff[1 + pointnum*i];
		//		for(j = 2; j <= pointnum; j++)
		//			tempbuff[j + pointnum*i] = dist_temp*(j-1)/pointnum + tempbuff[1 + pointnum*i] ; 
		//	}
		//	tempbuff[254] = tempbuff[253]*2/3;
		//	tempbuff[255] = tempbuff[253]*1/3;
		//------------------------------------
		//��Ȩ�˲�
		for (i = start + 1; i <= end - 1; i++)
			tempbuff[i] = 0.4*tempbuff[i - 1] + 0.4*tempbuff[i] + 0.2*tempbuff[i + 1];
		for (i = start + 3; i <= end - 3; i++)
			tempbuff[i] = 0.3*tempbuff[i - 2] + 0.3*tempbuff[i - 1] + 0.2*tempbuff[i] + 0.1*tempbuff[i + 1] + 0.1*tempbuff[i + 1];
	}

	//��1��������0x00��ֹ��,������TEXT��ʽ�������ݿ��������
	for (i = 0; i < start; i++)
		(*psampledata).basograph[i] = 1;
	for (i = start; i <= end; i++)
		(*psampledata).basograph[i] = tempbuff[i] + 1;
	for (i = end + 1; i < 255; i++)
		(*psampledata).basograph[i] = 1;
	psampledata->basograph[255] = 0;

	//------------------------------------------------
	//������п����������ԭʼ���ݽ��б���
	if (StartupBlankTestsflag)
	{
		StartupBlankTestswbc = wbc;
	}

	//----------------------------------------
	//�жϲ���ʽת��
	if (*pIsSuper == 0 && (!IsBlankTest))     //���������ǿհ�
	{
		if (wbc < 0.5)
		{
			if (wbc < 0.3)
				wbc = 0;
			sprintf((*psampledata).wbcdata.wbc, "%.2f", wbc);

			//������ز������ǳ�ʼ����ֵ��"*"��
			(*psampledata).basoflg[0] = 1;
		}
		else if (basop < 8.0)    //BASO������8%      hw_temp:20141231
		{
			sprintf((*psampledata).wbcdata.wbc, "%.2f", wbc);
			sprintf((*psampledata).wbcdata.basp, "%.1f", basop);
			sprintf((*psampledata).wbcdata.bas, "%.2f", baso);
		}
		else
		{
			printf("basop:%.2f\n", basop);
		}
	}
	else
	{
		if (wbc < 0.5)
		{
			if (wbc < 0.3)
				wbc = 0;
			sprintf((*psampledata).wbcdata.wbc, "%.2f", wbc);
			//������ز������ǳ�ʼ����ֵ��"*"��
			(*psampledata).basoflg[0] = 1;
		}
		else
		{
			sprintf((*psampledata).wbcdata.wbc, "%.2f", wbc);
			sprintf((*psampledata).wbcdata.basp, "%.1f", basop);
			sprintf((*psampledata).wbcdata.bas, "%.2f", baso);
		}
	}
}

/***********************************************************
*Function:
*Description:	�Խ��ܵ�ɢ��ͼ�ĵ��迹�Ŵ�
*Called by:
*Params illustration:
*Data Access:
*Other:
*History:
1.�źŷŴ󲿷�
2.�����ǹ���ʦ����	������迹ֵ�����Զ��������߹���ʦ��������Ҫ��Ҫ�Զ�����
************************************************************/
void DataProcess::LmneAmpRes(sample_info *psampledata)	//xx22 ��ʱû�õ�
{
	unsigned int i;
	unsigned char res = 0;		//���迹�ź�

	unsigned char mark1 = 0;
	unsigned char mark2 = 0;
	unsigned short int resb[256] = { 0 };
	unsigned short int numtemp = 0;

	unsigned short int max1num = 0;
	unsigned short int max2num = 0;
	unsigned char max1res = 0;
	unsigned char max2res = 0;

	float amp1 = 0.0, amp3 = 0.0;
	unsigned char max1res_amped = 0;	//�Ŵ��ķ�ֵ���迹
	unsigned char max2res_amped = 0;

	mark1 = systemcfg.lmnepeak1;
	mark2 = systemcfg.lmnepeak2;
	for (i = 0; i < 256; i++)
		resb[i] = 0;
	for (i = 0; i < MATRIX_POINT_MAX; i++)
	{
		res = (*psampledata).lmnegraph[(i << 1)];
		resb[res]++;
	}

	//[mark1-10,mark1+10]	//10 xx22
	max1num = resb[mark1 - 10 - 2] + resb[mark1 - 10 - 1] + resb[mark1 - 10] + resb[mark1 - 10 + 1] + resb[mark1 - 10 + 2];	//�Ȳ���5�����⾫����ʧ
	max1res = mark1 - 10;
	for (i = mark1 - 9; i <= mark1 + 10; i++)
	{
		numtemp = resb[i - 2] + resb[i - 1] + resb[i] + resb[i + 1] + resb[i + 2];
		if (numtemp > max1num)
		{
			max1num = numtemp;
			max1res = i;
		}
	}

	//[mark2-10,mark2+10]	//10 xx22
	max2num = resb[mark2 - 10 - 2] + resb[mark2 - 10 - 1] + resb[mark2 - 10] + resb[mark2 - 10 + 1] + resb[mark2 - 10 + 2];//�Ȳ���5�����⾫����ʧ
	max2res = mark2 - 10;
	for (i = mark2 - 9; i <= mark2 + 10; i++)
	{
		numtemp = resb[i - 2] + resb[i - 1] + resb[i] + resb[i + 1] + resb[i + 2];
		if (numtemp > max2num)
		{
			max2num = numtemp;
			max2res = i;
		}
	}

	if (mark1 / max1res < 0.7)
		amp1 = 0.7;
	else if (mark1 / max1res > 1.3)
		amp1 = 1.3;
	else
		amp1 = mark1 / max1res;
	max1res_amped = amp1*max1res;

	if (mark2 / max2res < 0.7)
		amp3 = 0.7;
	else if (mark1 / max1res > 1.3)
		amp3 = 1.3;
	else
		amp3 = mark2 / max1res;
	max2res_amped = amp3*max2res;

	//��֤max1res < max2res
	for (i = 0; i < MATRIX_POINT_MAX; i++)
	{
		res = (*psampledata).lmnegraph[(i << 1)];
		if (res <= max1res)
			(*psampledata).lmnegraph[(i << 1)] = res*amp1;
		else if (res >= max2res)
			(*psampledata).lmnegraph[(i << 1)] = max2res_amped + (res - max2res)*(255 - max2res_amped) / (255 - max2res);
		else
			(*psampledata).lmnegraph[(i << 1)] = max1res_amped + (res - max1res)*(max2res_amped - max1res_amped) / (max2res - max1res);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////	
//Description:	����ɢ��ͼ����ƶ�ϵ��						  					//
//Called by: LmneAnalysis																	//
//Params illustration:																		//
//Data Access:																			//
//Other:																					//
//*History:																				//
//	(1)Created:20150127																	//
//////////////////////////////////////////////////////////////////////////////////////////
void DataProcess::LmneCoeCalculate(sample_info *psampledata)	//xx22 ��ʱû�õ�
{
	unsigned int i;
	unsigned char res = 0;		//���迹�ź�

	unsigned char mark1 = 0;
	unsigned short int resb[256] = { 0 };
	unsigned short int numtemp = 0;

	unsigned short int max1num = 0;
	unsigned char max1res = 0;

	float coe = 1.0;
	int	board = 3 * systemcfg.lmnepeak1 / 10;
	int	calboard = 2 * systemcfg.lmnepeak1 / 10;

	printf("board:%d  calboard:%d\n", board, calboard);

	mark1 = systemcfg.lmnepeak1;

	for (i = 0; i < 256; i++)
		resb[i] = 0;
	for (i = 0; i < MATRIX_POINT_MAX; i++)
	{
		res = (*psampledata).lmnegraph[(i << 1)];
		resb[res]++;
	}

	//[mark1-10,mark1+10]	//10 xx22
	max1num = resb[mark1 - board - 2] + resb[mark1 - board - 1] + resb[mark1 - board] + resb[mark1 - board + 1] + resb[mark1 - board + 2];	//�Ȳ���5�����⾫����ʧ
	max1res = mark1 - board;
	for (i = mark1 - board + 1; i <= mark1 + board; i++)
	{
		numtemp = resb[i - 2] + resb[i - 1] + resb[i] + resb[i + 1] + resb[i + 2];
		if (numtemp > max1num)
		{
			max1num = numtemp;
			max1res = i;
		}
	}

	printf("mark1:%d  res:%d\n", mark1, max1res);

	if ((max1res < (mark1 - calboard)) || (max1res >(mark1 + calboard)))
		coe = (float)max1res / mark1;     //����ϵ��

	printf("coe:%.2f\n", coe);

	if (coe < (1.0 - 0.3))
		coe = 1.0 - 0.3;
	else if (coe > 1.0 + 0.3)
		coe = 1.0 + 0.3;

	psampledata->coeoflmne = coe;
}

//////////////////////////////////////////////////////////////////////////////////////////	
//Description:	��̬��ʼ��LMNEɢ��ͼ��������ֵ						  				//
//Called by: LmneAnalysis																//
//Params illustration:																	//
//Data Access:																			//
//Other:																				//
//*History:																				//
//	(1)Created:20150121																	//
//////////////////////////////////////////////////////////////////////////////////////////
void DataProcess::Init_B_LMNE(float	coefficient, B_LMNE* p_blmne)
{
	float		coe_rtoabs;

	//Resistance
	p_blmne->X_NOL = (uchar)systemcfg.range.thresholds[NoL] * coefficient;
	p_blmne->X_NON = (uchar)systemcfg.range.thresholds[NoN] * coefficient;
	p_blmne->X_LL = (uchar)systemcfg.range.thresholds[LL] * coefficient;
	p_blmne->X_LN = (uchar)systemcfg.range.thresholds[LN] * coefficient;
	p_blmne->X_AL = (uchar)systemcfg.range.thresholds[AL] * coefficient;
	p_blmne->X_LMN = (uchar)systemcfg.range.thresholds[LMN] * coefficient;
	p_blmne->X_LMU = (uchar)systemcfg.range.thresholds[LMU] * coefficient;
	p_blmne->X_MN = (uchar)systemcfg.range.thresholds[MN] * coefficient;
	p_blmne->X_LMD = (uchar)systemcfg.range.thresholds[LMD] * coefficient;

	p_blmne->X_NOE = (uchar)systemcfg.range.thresholds[NoE] * 1.0;
	p_blmne->X_RM = (uchar)systemcfg.range.thresholds[RM] * 1.0;
	p_blmne->X_RN = (uchar)systemcfg.range.thresholds[RN] * 1.0;

	coe_rtoabs = coefficient * 1.0;
	//Absorbance
	p_blmne->Y_NL = (uchar)systemcfg.range.thresholds[NL] * coe_rtoabs;
	p_blmne->Y_RMN = (uchar)systemcfg.range.thresholds[RMN] * coe_rtoabs;
	p_blmne->Y_NE = (uchar)systemcfg.range.thresholds[NE] * coe_rtoabs;
}

/***********************************************************
*Function:
*Description:	�Խ������ݵ�matrix_lmen[MATRIX_POINT_MAX]����
*Called by:
*Params illustration:
*Data Access:
*Other:
1������ʱ�������ܵ�LMNE���� ����������������������ɢ��ͼ
2����ѯ���ݿ�ʱ�������ݿ��е�LMNE���ݽ���������ɢ��ͼ
*History:	create	lgq		2010.7.20
mod		wsm		2010.11.5
************************************************************/
int DataProcess::LmneAnalysis(sample_info *psampledata, uchar* pIsSuper)
{
	unsigned int i;
	unsigned char res = 0, scatter = 0;		//���迹�źš���ɢ���ź�

	unsigned short int count_eos = 0;
	unsigned short int count_neu = 0;
	unsigned short int count_lneu = 0;
	unsigned short int count_rneu = 0;
	unsigned short int count_lym = 0;
	unsigned short int count_llym = 0;
	unsigned short int count_rlym = 0;
	unsigned short int count_mono = 0;
	unsigned short int count_rmono = 0;

	unsigned short int count_fln = 0;	//�������ļ���
	unsigned short int count_fne = 0;	//�������ļ���
	unsigned short int count_fmn = 0;	//�������ļ���

	unsigned short int count_aly = 0;
	unsigned short int count_lic = 0;
	unsigned short int count_noise = 0;
	unsigned short int count_blood = 0;

	float coefficient = 0.0;
	float wbc = 0.0;
	float lymp = 0.0;
	float neup = 0.0;
	float monop = 0.0;
	float eosp = 0.0;
	float alyp = 0.0;
	float licp = 0.0;

	float lym = 0.0;
	float neu = 0.0;
	float mono = 0.0;
	float eos = 0.0;
	float aly = 0.0;
	float lic = 0.0;
	//�о�����
	unsigned short int count_blasts = 0;
	float blastsp = 0.0;
	float leftp = 0.0;
	float nrbcp = 0.0;
	float blasts = 0.0;
	float left = 0.0;
	float nrbc = 0.0;

	int		retn = 0;
	B_LMNE	m_blmne;

	TRACE("\nLmneAnalysis()====================\n");
	for (i = 0; i < MATRIX_DATA_MAX; i++)
	{
		if ((*psampledata).lmnegraph[i] != 0)
		{
			retn++;
			if (255 == (*psampledata).lmnegraph[i])
				(*psampledata).lmnegraph[i] = 254;
		}
	}
	if (retn == 0)
		return -1;

	//�жϣ�����psampledata->coeoflmneֵ(��ͨ�û�ģʽ�ǿհײ���)
	if (*pIsSuper == 0 && (!IsBlankTest) && systemcfg.LMNEMarkMode == 1)
	{
		LmneCoeCalculate(psampledata);
	}

	//printf("coeoflmne:%.1f\n",psampledata->coeoflmne);

	Init_B_LMNE(psampledata->coeoflmne, &m_blmne);

	for (i = 0; i < MATRIX_POINT_MAX; i++)
	{
		res = (*psampledata).lmnegraph[(i << 1)];
		scatter = (*psampledata).lmnegraph[(i << 1) + 1];
		if (scatter >= m_blmne.Y_NE)
		{
			if (res < m_blmne.X_NOE)
				count_noise++;
			else
			{
				count_eos++;
				if (scatter < m_blmne.Y_NE + systemcfg.range.thresholds[FNE])
					count_fne++;
			}
			if (res >= 250)//�о�����	//xx21 250ֻ��һ����ʱ�ı���������Ҳ��
			{
				count_blasts++;
			}
		}
		else if (scatter >= m_blmne.Y_RMN)
		{
			if (res < m_blmne.X_NON)
				count_noise++;
			else if (res < m_blmne.X_LN)
				count_lneu++;
			else if (res < m_blmne.X_RN)
				count_neu++;
			else
				count_rneu++;
			if (res >= 250)//�о�����
			{
				count_blasts++;
			}
		}
		else if (scatter >= m_blmne.Y_NL)
		{
			if (res < m_blmne.X_NON)
				count_noise++;
			else if (res < m_blmne.X_LN)
			{
				count_lneu++;
				if (scatter < m_blmne.Y_NL + systemcfg.range.thresholds[FLN])
					count_fln++;
			}
			else if (res < m_blmne.X_LMN)
			{
				count_neu++;
				if (scatter < m_blmne.Y_NL + systemcfg.range.thresholds[FLN])
					count_fln++;
			}
			else if (res < m_blmne.X_MN)
			{
				if ((res - m_blmne.X_LMN)*(m_blmne.Y_RMN - m_blmne.Y_NL) <
					(m_blmne.X_MN - m_blmne.X_LMN)*(scatter - m_blmne.Y_NL))
				{
					count_neu++;
					if (scatter <= m_blmne.Y_NL + systemcfg.range.thresholds[FMN] || res >= m_blmne.X_MN - systemcfg.range.thresholds[FMN] ||
						((res - m_blmne.X_LMN)*(m_blmne.Y_RMN - m_blmne.Y_NL - systemcfg.range.thresholds[FMN]) >
						(m_blmne.X_MN - m_blmne.X_LMN - systemcfg.range.thresholds[FMN])*(scatter - m_blmne.Y_NL - systemcfg.range.thresholds[FMN])))
						count_fmn++;
				}
				else
					count_mono++;
			}
			else if (res < m_blmne.X_RM)
				count_mono++;
			else
				count_rmono++;
			if (res >= 250)//�о�����
			{
				count_blasts++;
			}
		}
		else
		{
			if (res < m_blmne.X_NOL)
				count_noise++;
			else if (res < m_blmne.X_LL)
				count_llym++;
			else if (res < m_blmne.X_AL)
				count_lym++;
			else if (res < m_blmne.X_LMU)
				count_rlym++;
			else if (res < m_blmne.X_LMD)
			{
				if ((m_blmne.X_LMD - res)*m_blmne.Y_NL >
					(m_blmne.X_LMD - m_blmne.X_LMU)*scatter)
					count_rlym++;
				else
					count_mono++;
			}
			else if (res < m_blmne.X_RM)
				count_mono++;
			else
				count_rmono++;
			if (res >= 250)//�о�����
			{
				count_blasts++;
			}
		}
	}

	count_blood = count_llym + count_rlym + count_lym + count_lneu + count_rneu + count_neu + count_rmono + count_mono + count_eos;
	count_lic = count_rneu + count_rmono;
	count_aly = count_rlym;
	//blood	
	TRACE("count_blood=%d---------#\n", count_blood);

	//lym
	TRACE("count_llym=%d---------#\n", count_llym);
	TRACE("count_rlym=%d---------#\n", count_rlym);
	TRACE("count_lym=%d---------#\n", count_lym);
	//neu
	TRACE("count_lneu=%d---------#\n", count_lneu);
	TRACE("count_rneu=%d---------#\n", count_rneu);
	TRACE("count_neu=%d---------#\n", count_neu);
	//mono
	TRACE("count_rmono=%d---------#\n", count_rmono);
	TRACE("count_mono=%d---------#\n", count_mono);
	//eos
	TRACE("count_eos=%d---------#\n", count_eos);

	//aly
	TRACE("count_aly=%d---------#\n", count_aly);
	//lic
	TRACE("count_lic=%d---------#\n", count_lic);

	//nosie
	TRACE("count_noise=%d---------#\n", count_noise);

	//�о�����
	//blasts
	TRACE("count_blasts=%d---------#\n", count_blasts);
	//left
	TRACE("count_left=%d---------#\n", count_lneu);
	//nrbc
	TRACE("count_nrbc=%d---------#\n", count_llym);

	if (count_blood > 0)//������Ϊ0
	{
		//NO
		if (count_noise > 120)				//FDparam �����漸�����ο�ABX
			(*psampledata).lmneflg[0] = 2;
		//LL
		if (count_llym > 50)
			(*psampledata).lmneflg[1] = 2;
		//LL1
		if (count_llym > 45 && (float)count_llym / count_blood > 0.05)
			(*psampledata).lmneflg[2] = 2;
		//NL
		if (count_fln > 120 || (float)count_fln / count_blood > 0.03)
			(*psampledata).lmneflg[3] = 2;
		//MN
		if (count_fmn > 120)
			(*psampledata).lmneflg[4] = 2;
		//RM
		if (count_rmono > 999 || (float)count_rmono / count_blood > 0.011)
			(*psampledata).lmneflg[5] = 2;
		//LN
		if (count_lneu > 999 || (float)count_lneu / count_blood > 0.025)
			(*psampledata).lmneflg[6] = 2;
		//RN
		if (count_rneu > 999 || (float)count_rneu / count_blood > 0.011)
			(*psampledata).lmneflg[7] = 2;
		//NE
		if (count_fne > 60 || (float)count_fne / count_blood > 0.011)
			(*psampledata).lmneflg[8] = 2;
	}

	//��1��������0x00��ֹ��,������TEXT��ʽ�������ݿ��������
	for (i = 0; i < MATRIX_DATA_MAX - 1; i++)
		(*psampledata).lmnegraph[i] += 1;
	(*psampledata).lmnegraph[MATRIX_DATA_MAX - 1] = 0;

	if (count_blood > 0)	//���count_bloosΪ0���������������쳣
	{
		int 		cal_blood = count_blood * VOLAMP_WBCBASO * 1.19;

		wbc = atof(psampledata->wbcdata.wbc);
		wbc_lmne = cal_blood;

		//�����������Ҫ�ж�
		if (*pIsSuper == 0 && (!IsBlankTest))
		{
			if (WbcForCompare > 0.5 || cal_blood > 0.5)
			{
				if (cal_blood > 2 * WbcForCompare)             //��WBC�¿ף����������ݲ���ʾ
				{
					wbc = 0.0;
					strcpy((*psampledata).wbcdata.wbc, "**.**");
					strcpy((*psampledata).wbcdata.basp, "*.*");
					strcpy((*psampledata).wbcdata.bas, "*.**");

					CView* pActiveView = ((CFrameWnd*)(AfxGetApp()->m_pMainWnd))->GetActiveView();
					HWND testwnd = pActiveView->GetSafeHwnd();
					SendMessage(testwnd, WM_BLOCKER, (WPARAM)1, 0L);
				}
				//20150427Del
				//else if(WbcForCompare > 2 * cal_blood)      //��LMNE�¿ף���������ʾ
				//{
				//wbc = 0.0;
				//strcpy((*psampledata).wbcdata.basp,"*.*");
				//strcpy((*psampledata).wbcdata.bas,"*.**");
				//	SendMessage(MainWindowhDlg,MSG_BLOCKERR,(WPARAM)2,0L);
				//}
			}
		}

		if (wbc >= 0.3)       //wbc >= 0.3��������
		{
			coefficient = (100 - atof(psampledata->wbcdata.basp)) / count_blood;

			lymp = coefficient*(count_llym + count_lym);
			neup = coefficient*(count_lneu + count_neu);
			monop = coefficient*(count_mono);
			eosp = coefficient*count_eos;

			alyp = coefficient*count_aly;
			licp = coefficient*count_lic;
			//�о�����
			blastsp = coefficient*count_blasts;
			leftp = coefficient*count_lneu;
			nrbcp = coefficient*count_llym;

			//lym#
			lym = wbc*lymp / 100;
			//neu#
			neu = wbc*neup / 100;
			//mon#
			mono = wbc*monop / 100;
			//eos#
			eos = wbc*eosp / 100;

			//aly#
			aly = wbc*alyp / 100;
			//lic#
			lic = wbc*licp / 100;
			//�о�����
			blasts = wbc*blastsp / 100;
			left = wbc*leftp / 100;
			nrbc = wbc*nrbcp / 100;
		}
	}

	if (wbc < 0.3)		//wbc < 0.3,display *****
	{
		(*psampledata).lmneflg[0] = 1;
		(*psampledata).lmneflg[1] = 1;
		(*psampledata).lmneflg[2] = 1;
		(*psampledata).lmneflg[3] = 1;
		(*psampledata).lmneflg[4] = 1;
		(*psampledata).lmneflg[5] = 1;
		(*psampledata).lmneflg[6] = 1;
		(*psampledata).lmneflg[7] = 1;
		(*psampledata).lmneflg[8] = 1;
	}
	else
	{
		//�о�����
		sprintf(studyPara[0], "%.1f", blastsp);
		sprintf(studyPara[1], "%.1f", blasts);
		sprintf(studyPara[2], "%.1f", leftp);
		sprintf(studyPara[3], "%.1f", left);
		sprintf(studyPara[4], "%.1f", nrbcp);
		sprintf(studyPara[5], "%.1f", nrbc);

		//LYMP
		sprintf((*psampledata).wbcdata.lymp, "%.1f", lymp);
		//NEUP
		sprintf((*psampledata).wbcdata.neup, "%.1f", neup);
		//MONOP
		sprintf((*psampledata).wbcdata.monop, "%.1f", monop);
		//EOSP
		sprintf((*psampledata).wbcdata.eosp, "%.1f", eosp);
		//ALYP
		sprintf((*psampledata).wbcdata.alyp, "%.1f", alyp);
		//LICP
		sprintf((*psampledata).wbcdata.licp, "%.1f", licp);

		//LYM
		sprintf((*psampledata).wbcdata.lym, "%.2f", lym);
		//NEU
		sprintf((*psampledata).wbcdata.neu, "%.2f", neu);
		//MONO
		sprintf((*psampledata).wbcdata.mono, "%.2f", mono);
		//EOS
		sprintf((*psampledata).wbcdata.eos, "%.2f", eos);
		//ALY
		sprintf((*psampledata).wbcdata.aly, "%.2f", aly);
		//LIC
		sprintf((*psampledata).wbcdata.lic, "%.2f", lic);
	}

	return retn;
}

/***********************************************************
*Function:
*Description:	�Խ��յ�����֡������(rdata��ָ�ռ�)����
*Called by:
*Params illustration:
*Data Access:
*Other:
*History:	create	wsm		2010.12.31
************************************************************/
void DataProcess::HgbAnalysis(sample_info *psampledata)
{
	unsigned short int tmp_hgb = 0;
	float hgb = 0.0;
	float a = 0, b = 1.0, c = 0;

	TRACE("\nHgbAnalysis()====================\n");
	tmp_hgb = hgbgraph[0] * 1000 + hgbgraph[1] * 100 + hgbgraph[2] * 10 + hgbgraph[3];
	if (tmp_hgb <= 8310)	//8310 �Ǹ�����λ������������tmp_hgb������ֵ
	{
		//hgb
		a = systemcfg.modify[systemcfg.mode].a[MOD_HGBF];
		b = systemcfg.modify[systemcfg.mode].b[MOD_HGBF];
		c = systemcfg.modify[systemcfg.mode].c[MOD_HGBF];
		hgb = (float)tmp_hgb / 10;		//��λ���г�10�����Ҫ����10
		hgb = systemcfg.calibration[systemcfg.mode][CAL_HGBF] * fabs(a*hgb*a*hgb + b*hgb + c);
	}
	TRACE("hgb=%.1f---------#\n", hgb);

	//------------------------------------------------
	//�жϲ����и�ʽת��
	if (hgb < 3.0)
	{
		hgb = 0;
		sprintf((*psampledata).rbcdata.hgb, "%.1f", hgb);

	}
	else if (hgb > 300.0)	//һ�㲻�����300�����ھ�Ҫ���ƴ��󣬲��ҽ����*�š���ֵ����Ҫ����
	{
		printf("HGB  is higher than 300.0----------#\n");
		//xx22  �����ο�������ı�������
	}
	else
	{
		sprintf((*psampledata).rbcdata.hgb, "%.1f", hgb);
	}
}

/***********************************************************
*Function:
*Description:	�Խ��յ�����֡������(rdata��ָ�ռ�)����
����(�����жϣ�������sampledata.rbcgraph��ָ��Ŀռ�)
*Called by:
*Params illustration:  ��Ҫ�Ķ�ԭʼͼ�����ݣ���ֱ��ͼ����
*Data Access:
*Other:
*History:	create	wsm		2010.12.31
************************************************************/
void DataProcess::RbcAnalysis(sample_info *psampledata, const uchar* pIsSuper)	//xx22 ��RbcAnalysis���������Ƿ�������ֵ����MCV��RBC�ļ��㹫ʽ
{
	unsigned short int i, j;
	unsigned short int pointnum = 0;
	float dist_temp = 0.0;
	unsigned short int transbuff1[256] = { 0 };
	unsigned short int transbuff2[256] = { 0 };
	unsigned short int tempbuff[256] = { 0 };
	unsigned short int count_rbc = 0;
	unsigned short int count_rbc_amp = 0;//������Ŵ��ļ�������	
	unsigned int count_hct = 0;
	unsigned char volume_mcv = 0;
	float hgb = 0.0;
	float rbc = 0.0;
	float hct = 0.0;
	float mcv = 0.0;
	float mch = 0.0;
	float mchc = 0.0;
	float rdwcv = 0.0;
	float rdwsd = 0.0;
	unsigned char start, end;
	unsigned char rightend = 0;
	unsigned char L1 = 0, L2 = 0;		//����rdwcv���������
	unsigned char maxnum = 0; 			//��ϸ���ֲ�ϸ���������ֵ��Ӧ�����
	unsigned short int maxval = 0; 		//������ֵ
	unsigned int count_temp = 0; 		//����rdwcv����ʱ��������
	float temp1 = 0.0;
	float temp2 = 0.0;
	float cal = 1.0;
	float a = 0, b = 1.0, c = 0;

	start = systemcfg.range.thresholds[RB1];
	end = systemcfg.range.thresholds[RB2];

	for (i = 0; i < 256; i++)
	{
		transbuff1[i] = ((psampledata->rbcgraph[(i << 1) + 1]) << 8) + psampledata->rbcgraph[i << 1];
		transbuff2[i] = (rbcgraph_2[(i << 1) + 1] << 8) + rbcgraph_2[i << 1];
		tempbuff[i] = (transbuff1[i] + transbuff2[i]) / 2;
	}

	maxval = tempbuff[start];
	for (i = start + 1; i <= end; i++)
		if (tempbuff[i] > maxval)
			maxval = tempbuff[i];
	TRACE("rbc maxval=%d---------#\n", maxval);

	if (maxval > start)
	{
		if (2 * maxval - start < end)
		{
			rightend = 2 * maxval - start;
			for (i = 2 * maxval - start; i <= end; i++)
			{
				if (tempbuff[i] < 0.02*maxval)
					rightend = i;
			}
		}
		else//�쳣���
			rightend = end;
	}
	else//�쳣���
		rightend = end;

	//�����������ϸ��������HCT����	
	count_rbc = 0;
	count_hct = 0;
	for (i = start; i <= rightend; i++)
	{
		count_rbc += tempbuff[i];
		count_hct += tempbuff[i] * i;	//��HCT(��ϸ��ѹ��)��һ���ݻ�ȫѪ�к�ϸ�������ռ�İٷֱȣ�HCT��%��=RBC*MCV/ʵ�ʲ�����Ѫ�������	
	}
	TRACE("count_rbc=%d---------#\n", count_rbc);
	TRACE("count_hct=%d---------#\n", count_hct);

	if (count_rbc <= 370370 && count_rbc > 0)	//ȷ�����Խ��<100.00��Ȼ��ʹ��sprintfת����ʽ�浽���ݿ���û������
	{
		//��MCV(ƽ����ϸ�����)������ֱ��ͼ(�˴��Ȳ���ԭʼ����)����	
		volume_mcv = count_hct / count_rbc;
		TRACE("volume_mcv=%d---------#\n", volume_mcv);

		//------------------------------------------------
		//�ü�����ѪҺ�������Ϊ(1/VOL_RBCPLT)pl
		//AD�ķֱ�������AMP_RBC(fL)

		//rbc
		a = systemcfg.modify[systemcfg.mode].a[MOD_RBCF];
		b = systemcfg.modify[systemcfg.mode].b[MOD_RBCF];
		c = systemcfg.modify[systemcfg.mode].c[MOD_RBCF];
		rbc = count_rbc*VOL_RBCPLT;
		rbc = systemcfg.calibration[systemcfg.mode][CAL_RBCF] * fabs(a*rbc*a*rbc + b*rbc + c);  	//���У��,��λ1E12/L	
		//MCV
		a = systemcfg.modify[systemcfg.mode].a[MOD_MCVF];
		b = systemcfg.modify[systemcfg.mode].b[MOD_MCVF];
		c = systemcfg.modify[systemcfg.mode].c[MOD_MCVF];
		mcv = volume_mcv*AMP_RBC;	//fL
		mcv = systemcfg.calibration[systemcfg.mode][CAL_MCVF] * fabs(a*mcv*a*mcv + b*mcv + c);

		hct = rbc*mcv / 10;
		//------------------------------------------------
		//MIC
		if (mcv < 70)		//MCV<70fl FDparam
			(*psampledata).rbcflg[0] = 2;
		//MAC
		if (mcv > 110)		//MCV>110fl FDparam
			(*psampledata).rbcflg[1] = 2;

		hgb = atof(psampledata->rbcdata.hgb);
		if (rbc < 0.00001)
			mch = 0;
		else//������Ϊ0
			mch = hgb / rbc;

		//��MCHC(��ϸ��ƽ��Ѫ�쵰��Ũ��)
		//MCHC = HGB/HCT (ABX�Ĺ�ʽ)			
		if (hct < 0.00001)
			mchc = 0;
		else
			mchc = 100 * hgb / hct;

		if (mchc > 999.9)//�쳣,��������治��
			mchc = 0;

		//----------------------------------------
		//������Ŵ󣬼���RDW-SD��RDW-CV
		if (maxval != 0)
			cal = (float)RBC_HEIGHT / maxval;
		else
			cal = 1.0;
		TRACE("rbc cal=%.2f---------#\n", cal);

		//ͼ�ε���
		for (i = start; i <= end; i++)
			tempbuff[i] *= cal;

		//��Ȩ�˲�
		for (i = start + 1; i <= end - 1; i++)
			tempbuff[i] = 0.4*tempbuff[i - 1] + 0.4*tempbuff[i] + 0.2*tempbuff[i + 1];
		for (i = start + 3; i <= end - 3; i++)
			tempbuff[i] = 0.3*tempbuff[i - 2] + 0.3*tempbuff[i - 1] + 0.2*tempbuff[i] + 0.1*tempbuff[i + 1] + 0.1*tempbuff[i + 1];

		//�˲�ʱ�����ֵ���ܻ�仯�����������ֵ
		//Ѱ�����ֵ���Ŵ����źż������Ŵ����ź�ֻ���ڼ���RDW-CV,RDW-SD	
		count_rbc_amp = tempbuff[start];
		maxval = tempbuff[start];
		maxnum = start;
		for (i = start + 1; i <= end; i++)
		{
			count_rbc_amp += tempbuff[i];
			if (tempbuff[i] > maxval)
			{
				maxval = tempbuff[i];
				maxnum = i;
			}
		}

		if (0 == count_rbc_amp)//��֤������Ϊ0
			count_rbc_amp = 1;

		//------------------------------------------------
		//RDW-CV(%) = (L2-L1)/(L2+L1)*100%  zxg Sysmex��ʽ
		count_temp = tempbuff[volume_mcv];
		//Ѱ�ҷֲ���ȱ��ֵL1,L2
		for (L1 = volume_mcv - 1, L2 = volume_mcv + 1; L1 >= start && L2 <= end; L1--, L2++)
		{
			count_temp += (tempbuff[L1] + tempbuff[L2]);
			if ((1.0*count_temp) / count_rbc_amp > 0.6826)
				break;
		}
		//ѡ�����ű߽�ֵ
		temp1 = 1.0*(count_temp - tempbuff[L1] - tempbuff[L2]) - 0.6862*count_rbc_amp;
		temp2 = 1.0*count_temp - 0.6862*count_rbc_amp;
		if (temp1 < temp2)   //�߽�ֵȡL1+1��L2-1����
		{
			L1++;
			L2--;
		}
		rdwcv = (float)(L2 - L1) / (L2 + L1) * 100;//��ϸ������ֲ���Ⱥ�ѪС����

		//------------------------------------------------
		//RDW-SD			
		for (L1 = start; L1 < maxnum; L1++)
		{
			if ((1.0*tempbuff[L1] / maxval) > 0.2)
				break;
		}
		for (L2 = end; L2 > maxnum; L2--)
		{
			if ((1.0*tempbuff[L2] / maxval) > 0.2)
				break;
		}
		//ѡ�����ű��ֵ
		//L1
		temp1 = 1.0*(tempbuff[L1] - 0.2*maxval);
		temp2 = 1.0*(tempbuff[L1 - 1] - 0.2*maxval);
		if (temp1 > temp2)
			L1--;
		//L2
		temp1 = 1.0*(tempbuff[L2] - 0.2*maxval);
		temp2 = 1.0*(tempbuff[L2 + 1] - 0.2*maxval);
		if (temp1 > temp2)
			L2++;
		rdwsd = L2 - L1;

		a = systemcfg.modify[systemcfg.mode].a[MOD_RDWCVF];
		b = systemcfg.modify[systemcfg.mode].b[MOD_RDWCVF];
		c = systemcfg.modify[systemcfg.mode].c[MOD_RDWCVF];
		rdwcv = fabs(a*rdwcv*a*rdwcv + b*rdwcv + c);

		a = systemcfg.modify[systemcfg.mode].a[MOD_RDWSDF];
		b = systemcfg.modify[systemcfg.mode].b[MOD_RDWSDF];
		c = systemcfg.modify[systemcfg.mode].c[MOD_RDWSDF];
		rdwsd = rdwsd*AMP_RBC;
		rdwsd = fabs(a*rdwsd*a*rdwsd + b*rdwsd + c);
	}

	//RBCֵС��0.05ͼ�β���ʾ
	if (rbc < 0.05)
	{
		for (i = 0; i < 256; i++)
			tempbuff[i] = 0;
	}

	//���ձ�������+1�Կ��ܵ�0x00����		
	for (i = 0; i < (start << 1); i++)
		psampledata->rbcgraph[i] = 1;
	for (i = start; i <= end; i++)
	{
		psampledata->rbcgraph[(i << 1)] = (tempbuff[i] & 0x00ff) + 1;
		psampledata->rbcgraph[(i << 1) + 1] = (tempbuff[i] >> 8) + 1;		//��ʵ����������ѹ���Ŵ���󣬼���ֵ�Ѿ�С��RBC_HEIGHT<255�ˣ�������ʵrbcgraph���ֽڴ�Ķ���0
	}
	for (i = ((end + 1) << 1); i < 511; i++)
		psampledata->rbcgraph[i] = 1;
	psampledata->rbcgraph[511] = 0;

	//------------------------------------------------
	//������п����������ԭʼ���ݽ��б���
	if (StartupBlankTestsflag)
	{
		StartupBlankTestsrbc = rbc;
	}

	//----------------------------------------
	//�жϲ���ʽת��
	if (rbc < 0.05)	//����0.05	
	{
		rbc = 0;
		sprintf((*psampledata).rbcdata.rbc, "%.2f", rbc);
		//������ز������ǳ�ʼ����ֵ��"*"��
		(*psampledata).rbcflg[0] = 1;
		(*psampledata).rbcflg[1] = 1;
	}
	else
	{
		//RBC
		sprintf((*psampledata).rbcdata.rbc, "%.2f", rbc);
		//HCT
		sprintf((*psampledata).rbcdata.hct, "%.1f", hct);
		//MCV
		sprintf((*psampledata).rbcdata.mcv, "%.1f", mcv);
		//MCH
		sprintf((*psampledata).rbcdata.mch, "%.1f", mch);
		//MCHC
		sprintf((*psampledata).rbcdata.mchc, "%.1f", mchc);
		//RDW-CV
		sprintf((*psampledata).rbcdata.rdwcv, "%.1f", rdwcv);
		//RDW-SD
		sprintf((*psampledata).rbcdata.rdwsd, "%.1f", rdwsd);
	}

	if (*pIsSuper == 0 && (!IsBlankTest))
		IsBlocking_RBC( psampledata);
}

//PLTͼ��������ʾ�ж�
bool DataProcess::PLTDisplayGraph(float plt)
{
	//PLTֵС��30ͼ�β���ʾ
	if (plt < 30 && systemcfg.mode < 2)
		return FALSE;
	else
		return TRUE;
}
//PLT������ʾ�ж�
bool PLTDisplayItem(float plt)
{
	//ȫѪģʽ,PLT<10,����ʾ
	if (plt < 10 && systemcfg.mode < 2)
		return FALSE;
	else
		return TRUE;
}

/***********************************************************
*Function:
*Description:	�Խ��յ�����֡������(rdata��ָ�ռ�)����
����(�����жϣ�������sampledata.basograph��ָ��Ŀռ�)
*Called by:
*Params illustration:
*Data Access:
*Other:
*History:	create	wsm		2010.12.31
************************************************************/
void DataProcess::PltAnalysis(sample_info *psampledata)	//xx21 ��ʱ�俴һ�£�����һ��
{
	unsigned short int 	i;
	unsigned short int 	pointnum = 4;
	float 			dist_temp = 0.0;
	uchar 			tempbuff[256];
	unsigned short int 	count_plt = 0;
	unsigned short int 	count_plt2 = 0;
	unsigned int 		count_pct = 0;
	uchar 			colume_mpv = 0;
	float plt = 0.0;
	float mpv = 0.0;
	float pdw = 0.0;
	float pct = 0.0;
	float plcr = 0.0;
	uchar 	start, end;
	uchar 	maxnum = 0; 	//��ϸ���ֲ�ϸ���������ֵ��Ӧ�����
	unsigned short int maxval = 0;
	unsigned char L1 = 0, L2 = 0;	//����pdw���������
	float temp1 = 0.0;
	float temp2 = 0.0;
	float cal = 1.0;
	float a = 0, b = 1.0, c = 0;
	unsigned int count_temp = 0;	//����PLCR����ʱ��������
	float  proportion = 0.3;//�����ж�����ֵ��Ӧ��ֵ����

	TRACE("\nPltAnalysis()====================\n");
	for (i = 0; i < 256; i++)
		tempbuff[i] = (*psampledata).pltgraph[i];     //hw:20140521

	start = systemcfg.range.thresholds[PLT1];
	end = systemcfg.range.thresholds[PLT2];
	PLTRightBorderQuery = end;

	if (0 == systemcfg.PltRightThresholdMode)
	{
		TRACE("0 == PltRightThresholdMode\n");

		//��PLT(ѪС������)��PLT���У������PCT(ѪС��ѹ��)
		count_plt = 0;
		count_plt2 = 0;
		count_pct = 0;
		for (i = start; i <= end; i++)
		{
			count_plt += tempbuff[i];
			count_plt2 += pltgraph_2[i];
			count_pct += tempbuff[i] * i;	//һ���ݻ�ȫѪ��ѪС����ռ�İٷֱ� PCT = PLT*MPV/10000	
		}
		count_plt = (count_plt + count_plt2) / 2;           //ȡ����ƽ��ֵ
		TRACE("count_plt=%d---------#\n", count_plt);
		TRACE("count_pct=%d---------#\n", count_pct);

		if (count_plt <= 37037 && count_plt > 0)	//ȷ�����Խ��<10000��Ȼ��ʹ��sprintfת����ʽ�浽���ݿ���û������
		{
			//��MPV(ƽ��ѪС�����)
			//�˷Ŵ����Ⱥ�ϸ����ֵҲ���ܱ�MCV��
			colume_mpv = count_pct / count_plt;
			TRACE("colume_mpv=%d---------#\n", colume_mpv);

			//��P-LCR
			count_temp = 0;
			//for(i = 120;i <= end;i++)  		//��ʱ��Ϊ12uL��Ӧ�ĵ�Ϊ120		///FDparam		//xx21    
			//hw_change:20140723    ori:i=120
			for (i = 60; i <= end; i++)     //200/40*12
				count_temp += tempbuff[i];
			plcr = 100.0*count_temp / count_plt;

			a = systemcfg.modify[systemcfg.mode].a[MOD_PCTF];
			b = systemcfg.modify[systemcfg.mode].b[MOD_PCTF];
			c = systemcfg.modify[systemcfg.mode].c[MOD_PCTF];
			pct = count_pct*VOL_RBCPLT*AMP_PLT / 10;
			pct = fabs(a*pct*a*pct + b*pct + c);

			a = systemcfg.modify[systemcfg.mode].a[MOD_PLCRF];
			b = systemcfg.modify[systemcfg.mode].b[MOD_PLCRF];
			c = systemcfg.modify[systemcfg.mode].c[MOD_PLCRF];
			plcr = fabs(a*plcr*a*plcr + b*plcr + c);
			//----------------------------------------
			//�ü�����ѪҺ�������Ϊ(1/VOL_RBCPLT)pl
			//AD�ķֱ�������AMP_PLT(fL)  

			//plt
			a = systemcfg.modify[systemcfg.mode].a[MOD_PLTF];
			b = systemcfg.modify[systemcfg.mode].b[MOD_PLTF];
			c = systemcfg.modify[systemcfg.mode].c[MOD_PLTF];
			plt = count_plt*1000.0*VOL_RBCPLT;
			plt = systemcfg.calibration[systemcfg.mode][CAL_PLTF] * fabs(a*plt*a*plt + b*plt + c);

			a = systemcfg.modify[systemcfg.mode].a[MOD_MPVF];
			b = systemcfg.modify[systemcfg.mode].b[MOD_MPVF];
			c = systemcfg.modify[systemcfg.mode].c[MOD_MPVF];
			mpv = colume_mpv*AMP_PLT;
			mpv = fabs(a*mpv*a*mpv + b*mpv + c);
			//----------------------------------------
			//������Ŵ󣬼���PDW��������RDW-SD

			//PLT�ļ������٣��������֮��ļ����β��ɹ⻬���ߣ�ֻ�ܼ�����ȡƽ��ֵ��Ȼ�����γ�����
			//256�����ݷֳ�64*4��ȡ64���ƽ��ֵ���ڱ���ĵڶ���(Ҳ���Էŵ�����)
			for (i = 0; i < 64; i++)
				tempbuff[1 + 4 * i] = (float)(tempbuff[4 * i] + tempbuff[1 + 4 * i] + tempbuff[2 + 4 * i] + tempbuff[3 + 4 * i]) / 4;

			//�����ֵ
			maxnum = 1;
			maxval = tempbuff[1];
			for (i = 1; 4 * i + 1 < end; i++)
			{
				if (tempbuff[4 * i + 1] > maxval)
				{
					maxval = tempbuff[4 * i + 1];
					maxnum = 4 * i + 1;
				}
			}
			TRACE("plt maxval=%d---------#\n", maxval);

			if (maxval != 0)
				cal = (float)PLT_HEIGHT / maxval;
			else
				cal = 1.0;
			TRACE("PLT cal=%.2f---------#\n", cal);

			for (i = start; i <= end; i++)
			{
				tempbuff[i] = tempbuff[i] * cal;	//ͼ���������ѹ��
			}

			tempbuff[0] = tempbuff[1] / 2;
			pointnum = 4;
			for (i = 0; i < 63; i++)
			{
				tempbuff[2 + pointnum*i] = (float)(tempbuff[5 + pointnum*i] - tempbuff[1 + pointnum*i]) / pointnum + tempbuff[1 + pointnum*i];
				tempbuff[3 + pointnum*i] = (float)(tempbuff[5 + pointnum*i] - tempbuff[1 + pointnum*i]) * 2 / pointnum + tempbuff[1 + pointnum*i];
				tempbuff[4 + pointnum*i] = (float)(tempbuff[5 + pointnum*i] - tempbuff[1 + pointnum*i]) * 3 / pointnum + tempbuff[1 + pointnum*i];
			}
			tempbuff[254] = tempbuff[253] * 2 / 3;
			tempbuff[255] = tempbuff[253] * 1 / 3;

			//��Ȩ�˲�	
			for (i = start + 1; i <= end - 1; i++)
				tempbuff[i] = 0.4*tempbuff[i - 1] + 0.4*tempbuff[i] + 0.2*tempbuff[i + 1];
			//��Ȩ�˲�	
			for (i = start + 3; i <= end - 3; i++)
				tempbuff[i] = 0.3*tempbuff[i - 2] + 0.3*tempbuff[i - 1] + 0.2*tempbuff[i] + 0.1*tempbuff[i + 1] + 0.1*tempbuff[i + 1];

			maxval = tempbuff[start];
			maxnum = start;
			for (i = start + 1; i <= end; i++)
				if (tempbuff[i] > maxval)
				{
					maxval = tempbuff[i];
					maxnum = i;
				}

			for (L1 = start; L1 < maxnum; L1++)
			{
				if ((1.0*tempbuff[L1] / maxval) > 0.2)
					break;
			}
			for (L2 = end; L2 > maxnum; L2--)
			{
				if ((1.0*tempbuff[L2] / maxval) > 0.2)
					break;
			}
			//ѡ�����ű��ֵ
			//L1
			temp1 = 1.0*(tempbuff[L1] - 0.2*maxval);
			temp2 = 1.0*(tempbuff[L1 - 1] - 0.2*maxval);
			if (temp1 > temp2)
				L1--;
			//L2
			temp1 = 1.0*(tempbuff[L2] - 0.2*maxval);
			temp2 = 1.0*(tempbuff[L2 + 1] - 0.2*maxval);
			if (temp1 > temp2)
				L2++;

			pdw = L2 - L1;
			a = systemcfg.modify[systemcfg.mode].a[MOD_PDWF];
			b = systemcfg.modify[systemcfg.mode].b[MOD_PDWF];
			c = systemcfg.modify[systemcfg.mode].c[MOD_PDWF];
			pdw = pdw*AMP_PLT;
			pdw = fabs(a*pdw*a*pdw + b*pdw + c);
		}

		//PLTֵС��30ͼ�β���ʾ
		if (!PLTDisplayGraph(plt))
		{
			for (i = 0; i < 256; i++)
				tempbuff[i] = 0;
		}

		for (i = 0; i < start; i++)
			(*psampledata).pltgraph[i] = 1;
		for (i = start; i <= end*PLT_WIDTH / 255; i++)       //20141124_75ha_temp:��Ч���ݲ��ܳ����ҽ��
			(*psampledata).pltgraph[i] = tempbuff[i] + 1;
		for (i = end*PLT_WIDTH / 255 + 1; i < 255; i++)
			(*psampledata).pltgraph[i] = 1;
		psampledata->pltgraph[255] = 0;
		if (plt>30)//20151104 zwh�����ӦPLT�������ֵproportion ��ʾ
		{
			if (tempbuff[systemcfg.range.thresholds[PLT1]]>(float)proportion*maxval)
				(*psampledata).pltflg[2] = 2;
		}


	}
	else ///1 == systemcfg.PltRightThresholdMode
	{
		uchar		oribuff[256];
		uchar 		methodUsed;
		uchar 		minnum;
		unsigned int 	minval;
		unsigned int	transnum;
		uchar 		tempnum1;
		uchar		tempnum2;
		bool			FindMax_EN =TRUE;
		uchar		EffectiveBorder = end;
		uchar 		j;
		/******Debug********
		for(i = 0; i< 20; i++)
		tempbuff[i] = i;
		for(i = 20; i< 30; i++)
		tempbuff[i] = 40-i;
		for(i = 30; i< 80; i++)
		tempbuff[i] = 2*(i-30) + 10;
		for(i = 80; i< 100; i++)
		tempbuff[i] = 110-5*(i-80);
		for(i = 100; i < 120; i++)
		tempbuff[i] = 10+i-100;
		for(i = 120; i< 130; i++)
		tempbuff[i] = 150-i;
		for(i = 130; i< 140; i++)
		tempbuff[i] = i-100;
		******Debug********/

		for (i = 0; i < 255; i++)
			oribuff[i] = tempbuff[i];

		while (FindMax_EN)
		{
			FindMax_EN = FALSE;
			maxnum = 2;				//[2,128-1]	
			maxval = tempbuff[1] + tempbuff[2] + tempbuff[3];
			for (i = 3; i < 96; i++)
			{
				transnum = tempbuff[i - 1] + tempbuff[i] + tempbuff[i + 1];
				if (transnum >= maxval)
				{
					maxnum = i;
					maxval = transnum;
				}
			}
			maxval = (tempbuff[maxnum - 1] + tempbuff[maxnum] + tempbuff[maxnum + 1]) / 3;

			tempnum1 = tempbuff[maxnum - 3];
			tempnum2 = tempbuff[maxnum + 3];
			if (maxval - tempnum1 > 0.3 * maxval && maxval - tempnum2 > 0.3 * maxval)
			{
				tempnum2 = (tempnum2 - tempnum1) / 6;
				for (j = maxnum - 2, i = 1; j < maxnum + 3; j++, i++)
					tempbuff[j] = tempnum1 + tempnum2*i;
				FindMax_EN = TRUE;
			}
		}

		//�ȵ�ֵ
		minnum = maxnum;	//[maxnum,139]	
		minval = tempbuff[maxnum - 1] + tempbuff[maxnum] + tempbuff[maxnum + 1];
		//puts("---------------------------------------------------------------");
		for (i = maxnum + 1; i < 139; i++)	//FDparam ��DSPͳһ���� 140��DSP�ɼ��źŵ�����	//xx21
			if (tempbuff[i - 1] + tempbuff[i] + tempbuff[i + 1] <= minval)
			{
				minnum = i;
				minval = tempbuff[i - 1] + tempbuff[i] + tempbuff[i + 1];
				//printf("minnum[%d]:%d minval[%d]:%d\n",i,minnum,i,minval);
			}
		minval = (tempbuff[minnum - 1] + tempbuff[minnum] + tempbuff[minnum + 1]) / 3;
		//printf("minnum:%d minval:%d\n",minnum,minval);
		//puts("---------------------------------------------------------------");

		TRACE("plt maxnum=%d---------#\n", maxnum);
		TRACE("plt maxval=%d---------#\n", maxval);
		TRACE("plt minnum=%d---------#\n", minnum);
		TRACE("plt minval=%d---------#\n", minval);

		//������Ϣ(18,30)fL��[115,191]ȡ����ֵ�ĺͿɼ�С���
		if (minnum > 191 || minnum < 115)
		{
			(*psampledata).pltflg[0] = 2;
		}
		count_temp = 0;
		for (i = 192; i < 256; i++)		//30fl֮��
			count_temp += tempbuff[i];
		if (count_temp > 30000)			//FDparam �ο�ABX
			(*psampledata).pltflg[0] = 2;

		count_temp = 0;
		for (i = 0; i < 20; i++)			//02~3fl
			count_temp += tempbuff[i];
		if (count_temp > 3000)			//FDparam �ο�ABX
			(*psampledata).pltflg[1] = 2;

		{
			uchar compch = (tempbuff[PLTGraphEnd] + tempbuff[PLTGraphEnd + 1] + tempbuff[PLTGraphEnd + 2]) / 3;

			if (minnum <= 191 && compch <= 0.3*maxval)		//�ȵ���30fL��ǰ��30fL��<=���ֵ��40%
			{
				methodUsed = 1;
			}
			else	 if (minnum <= 191 && compch > 0.3*maxval)		//�ȵ���30fL��ǰ��30fL��>���ֵ��40%
			{
				methodUsed = 2;
			}
			else if (minnum > 191 && compch <= 0.3*maxval)		//�ȵ���30fL�Ժ�30fL��<=���ֵ��40%
			{
				methodUsed = 3;
			}
			else													//�ȵ���30fL�Ժ�30fL��>���ֵ��40%
			{
				methodUsed = 4;
			}
		}

		TRACE("methodUsed= %d\n", methodUsed);
		if (methodUsed == 1)//��һ��ģʽ�£���һ������(���������)���õ�����ģʽ����(�쳣�����)
		{
			if (maxval > minval)
			{
				//���������һ�飬�쳣����²���
				if (minval*(minnum - maxnum) / (maxval - minval) > 0 && 2.0*minval*(minnum - maxnum) / (maxval - minval) + minnum < 255)
				{
					tempnum1 = 2.0*minval*(minnum - maxnum) / (maxval - minval) + minnum;	//minnumһ��>maxnum��2.0ʹ������ƽ��
					for (i = minnum; i <= tempnum1; i++)
						tempbuff[i] = minval*(tempnum1 - i) / (tempnum1 - minnum);
				}
				else//�쳣���
					methodUsed = 3;
			}
			else//�쳣���
				methodUsed = 3;
		}

		//���ڶ�����ֵ���ͣ���ֹ�ڶ�����ֵ�ܴ�
		for (i = minnum + 1; i < 255; i++)
			if (tempbuff[i] > maxval)
			{
				tempbuff[i] = maxval;
			}
		//PLT�ļ������٣��������֮��ļ����β��ɹ⻬���ߣ�ֻ�ܼ�����ȡƽ��ֵ��Ȼ�����γ�����
		//256�����ݷֳ�64*4��ȡ64���ƽ��ֵ���ڱ���ĵڶ���(Ҳ���Էŵ�����)
		for (i = 0; i < 64; i++)
			tempbuff[1 + 4 * i] = (float)(tempbuff[4 * i] + tempbuff[1 + 4 * i] + tempbuff[2 + 4 * i] + tempbuff[3 + 4 * i]) / 4;

		//�����ֵ
		maxnum = 1;
		maxval = tempbuff[1];
		for (i = 1; i < 64; i++)
		{
			if (tempbuff[4 * i + 1] > maxval)
			{
				maxval = tempbuff[4 * i + 1];
				maxnum = 4 * i + 1;
			}
		}
		TRACE("plt maxval=%d---------#\n", maxval);

		if (maxval != 0)
			cal = (float)PLT_HEIGHT / maxval;
		else
			cal = 1.0;
		TRACE("PLT cal=%.2f---------#\n", cal);

		for (i = start; i <= end; i++)
		{
			tempbuff[i] = tempbuff[i] * cal;	//ͼ���������ѹ��
		}

		tempbuff[0] = tempbuff[1] / 2;
		for (i = 0; i < 63; i++)
		{
			tempbuff[2 + 4 * i] = (float)(tempbuff[5 + 4 * i] - tempbuff[1 + 4 * i]) / 4 + tempbuff[1 + 4 * i];
			tempbuff[3 + 4 * i] = (float)(tempbuff[5 + 4 * i] - tempbuff[1 + 4 * i]) * 2 / 4 + tempbuff[1 + 4 * i];
			tempbuff[4 + 4 * i] = (float)(tempbuff[5 + 4 * i] - tempbuff[1 + 4 * i]) * 3 / 4 + tempbuff[1 + 4 * i];
		}
		tempbuff[254] = tempbuff[253] / 3;
		tempbuff[255] = tempbuff[253] * 2 / 3;
		//----------------------------------------

		//��Ȩ�˲�	
		for (i = start + 1; i <= end - 1; i++)
			tempbuff[i] = 0.4*tempbuff[i - 1] + 0.4*tempbuff[i] + 0.2*tempbuff[i + 1];
		//��Ȩ�˲�	
		for (i = start + 3; i <= end - 3; i++)
			tempbuff[i] = 0.3*tempbuff[i - 2] + 0.3*tempbuff[i - 1] + 0.2*tempbuff[i] + 0.1*tempbuff[i + 1] + 0.1*tempbuff[i + 1];

		TRACE("methodUsed= %d\n", methodUsed);
		if (methodUsed == 2)
		{
			//�¹ȵ�ֵ
			minnum = 139;
			minval = tempbuff[138] + tempbuff[139] + tempbuff[140];
			for (j = 138; j > 70; j--)	//FDparam ��DSPͳһ���� 140��DSP�ɼ��źŵ�����	//xx21
			{
				transnum = tempbuff[j - 1] + tempbuff[j] + tempbuff[j + 1];
				if (transnum < minval)
				{
					minnum = j;
					minval = transnum;
				}
			}
			EffectiveBorder = minnum;
			PLTRightBorderQuery = minnum * 255 / PLT_WIDTH;
		}
		else if (methodUsed == 3 || methodUsed == 4)
			EffectiveBorder = systemcfg.range.thresholds[PLT2];


		//----------------------------------------		
		//��PLT(ѪС������)��PLT���У������PCT(ѪС��ѹ��)
		count_plt = 0;
		count_pct = 0;
		count_plt2 = 0;
		for (j = start; j <= EffectiveBorder; j++)     //
		{
			count_plt += oribuff[j];
			count_plt2 += pltgraph_2[j];
			count_pct += oribuff[j] * j;	//һ���ݻ�ȫѪ��ѪС����ռ�İٷֱ� PCT = PLT*MPV/10000	
		}
		count_plt = (count_plt + count_plt2) / 2;
		TRACE("count_plt=%d---------#\n", count_plt);
		TRACE("count_pct=%d---------#\n", count_pct);

		if (count_plt <= 37037 && count_plt > 0)	//ȷ�����Խ��<10000��Ȼ��ʹ��sprintfת����ʽ�浽���ݿ���û������
		{
			//��MPV(ƽ��ѪС�����)
			//�˷Ŵ����Ⱥ�ϸ����ֵҲ���ܱ�MCV��
			colume_mpv = count_pct / count_plt;
			TRACE("colume_mpv=%d---------#\n", colume_mpv);

			//��P-LCR			
			count_temp = 0;
			//for(i = 120;i <= end;i++)  		//��ʱ��Ϊ12uL��Ӧ�ĵ�Ϊ120		///FDparam		//xx21
			for (i = 60; i <= EffectiveBorder; i++)
				count_temp += oribuff[i];
			plcr = 100.0*count_temp / count_plt;
			//---------------------------------
			a = systemcfg.modify[systemcfg.mode].a[MOD_PCTF];
			b = systemcfg.modify[systemcfg.mode].b[MOD_PCTF];
			c = systemcfg.modify[systemcfg.mode].c[MOD_PCTF];
			pct = count_pct*VOL_RBCPLT*AMP_PLT / 10;
			pct = fabs(a*pct*a*pct + b*pct + c);

			a = systemcfg.modify[systemcfg.mode].a[MOD_PLCRF];
			b = systemcfg.modify[systemcfg.mode].b[MOD_PLCRF];
			c = systemcfg.modify[systemcfg.mode].c[MOD_PLCRF];
			plcr = fabs(a*plcr*a*plcr + b*plcr + c);
			//----------------------------------------
			//�ü�����ѪҺ�������Ϊ(1/VOL_RBCPLT)pl
			//AD�ķֱ�������AMP_PLT(fL)  

			//plt
			a = systemcfg.modify[systemcfg.mode].a[MOD_PLTF];
			b = systemcfg.modify[systemcfg.mode].b[MOD_PLTF];
			c = systemcfg.modify[systemcfg.mode].c[MOD_PLTF];
			plt = count_plt*1000.0*VOL_RBCPLT;
			plt = systemcfg.calibration[systemcfg.mode][CAL_PLTF] * fabs(a*plt*a*plt + b*plt + c);

			a = systemcfg.modify[systemcfg.mode].a[MOD_MPVF];
			b = systemcfg.modify[systemcfg.mode].b[MOD_MPVF];
			c = systemcfg.modify[systemcfg.mode].c[MOD_MPVF];
			mpv = colume_mpv*AMP_PLT;
			mpv = fabs(a*mpv*a*mpv + b*mpv + c);

			maxval = tempbuff[start];
			maxnum = start;
			for (i = start + 1; i <= EffectiveBorder; i++)
				if (tempbuff[i] > maxval)
				{
					maxval = tempbuff[i];
					maxnum = i;
				}

			for (L1 = start; L1 < maxnum; L1++)
			{
				if ((1.0*tempbuff[L1] / maxval) > 0.2)
					break;
			}
			for (L2 = EffectiveBorder; L2 > maxnum; L2--)      //end -> EffectiveBorder
			{
				if ((1.0*tempbuff[L2] / maxval) > 0.2)
					break;
			}
			//ѡ�����ű��ֵ
			//L1
			temp1 = 1.0*(tempbuff[L1] - 0.2*maxval);
			temp2 = 1.0*(tempbuff[L1 - 1] - 0.2*maxval);
			if (temp1 > temp2)
				L1--;
			//L2
			temp1 = 1.0*(tempbuff[L2] - 0.2*maxval);
			temp2 = 1.0*(tempbuff[L2 + 1] - 0.2*maxval);
			if (temp1 > temp2)
				L2++;

			pdw = L2 - L1;
			a = systemcfg.modify[systemcfg.mode].a[MOD_PDWF];
			b = systemcfg.modify[systemcfg.mode].b[MOD_PDWF];
			c = systemcfg.modify[systemcfg.mode].c[MOD_PDWF];
			pdw = pdw*AMP_PLT;
			pdw = fabs(a*pdw*a*pdw + b*pdw + c);
		}

		//PLTֵС��30ͼ�β���ʾ
		if (!PLTDisplayGraph(plt))
		{
			for (i = 0; i < 256; i++)
				tempbuff[i] = 0;
		}

		for (i = 0; i < start; i++)
			(*psampledata).pltgraph[i] = 1;
		for (i = start; i <= end*PLT_WIDTH / 255; i++)       //20141124_75ha_temp:��Ч���ݲ��ܳ����ҽ��
			(*psampledata).pltgraph[i] = tempbuff[i] + 1;
		for (i = end*PLT_WIDTH / 255 + 1; i < 255; i++)
			(*psampledata).pltgraph[i] = 1;
		psampledata->pltgraph[255] = 0;

		if (plt>30)//20151104 zwh�����ӦPLT�������ֵproportion ��ʾ
		{
			if (tempbuff[systemcfg.range.thresholds[PLT1]]>(float)proportion*maxval)
				(*psampledata).pltflg[2] = 2;
		}

	}

	//------------------------------------------------
	//�����������ԭʼ���ݽ��б���
	if (StartupBlankTestsflag)
	{
		StartupBlankTestsplt = plt;
	}

	//------------------------------------------------
	//�жϺ͸�ʽת��,�ɷ����˲�֮ǰ

	if (plt < 0.1)    //ori:30
	{
		plt = 0;
		sprintf((*psampledata).pltdata.plt, "%.0f", plt);
		(*psampledata).pltflg[0] = 1;
		(*psampledata).pltflg[1] = 1;
	}
	else if (!PLTDisplayItem(plt))    //PLT<10,����4���������ʾ
	{
		sprintf((*psampledata).pltdata.plt, "%.0f", plt);
		(*psampledata).pltflg[0] = 1;
		(*psampledata).pltflg[1] = 1;
	}
	else
	{
		//PLT
		sprintf((*psampledata).pltdata.plt, "%.0f", plt);
		//PCT
		sprintf((*psampledata).pltdata.pct, "%.2f", pct);
		//MPV
		sprintf((*psampledata).pltdata.mpv, "%.2f", mpv);
		//PDW
		sprintf((*psampledata).pltdata.pdw, "%.1f", pdw);
		//P_LCR
		sprintf((*psampledata).pltdata.plcr, "%.1f", plcr);
	}
}

void DataProcess::IsBlocking_RBC( sample_info* pSampleData)
{
	double rbc = atof(pSampleData->rbcdata.rbc);
	double hgb = atof(pSampleData->rbcdata.hgb);

	if (hgb > 50 && rbc < hgb / 50)
	{	
		CView* pActiveView = ((CFrameWnd*)(AfxGetApp()->m_pMainWnd))->GetActiveView();
		HWND testwnd = pActiveView->GetSafeHwnd();
		SendMessage(testwnd,WM_BLOCKER, (WPARAM)3, 0L);
	}
}