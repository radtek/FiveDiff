// TemperaturecontrolView.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "TemperaturecontrolView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"
#include "FilesOperation.h"
// CTemperaturecontrolView �Ի���

float 	temper = 0.0;
uchar 	tempeReceived[9] = {0};
CString tmpeshow;

IMPLEMENT_DYNAMIC(CTemperaturecontrolView, CDialogEx)

CTemperaturecontrolView::CTemperaturecontrolView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTemperaturecontrolView::IDD, pParent)
	
{
	VERIFY(m_Font.CreateFont(
		20,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		GB2312_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
		L"����"));                 // lpszFacename

	
}

CTemperaturecontrolView::~CTemperaturecontrolView()
{
}

void CTemperaturecontrolView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
}


BEGIN_MESSAGE_MAP(CTemperaturecontrolView, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_TMCTRL_TMSET_OK, &CTemperaturecontrolView::OnBnClickedTmctrlTmsetOk)
END_MESSAGE_MAP()


// CTemperaturecontrolView ��Ϣ�������


HBRUSH CTemperaturecontrolView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

//#3018
//
//#3019
//	return hbr;
//
//#3018
//
//#3019
//	return hbr;
//	// TODO:  �ڴ˸��� DC ���κ�����
//
//#3019
//	return hbr;
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SelectObject(&m_Font);
		pDC->SetBkColor(RGB(255, 255, 255));//���ֱ���ɫ
		HBRUSH b = CreateSolidBrush(RGB(255, 255, 255));//�ؼ�����ɫ   
		return b;
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CTemperaturecontrolView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	/*@TG
#3073*/
	CRect   rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));   //����Ϊ��ɫ����
	dc.Rectangle(20, 20, rect.right - 20, rect.bottom - 180);
	dc.Rectangle(20, rect.bottom - 150, rect.right - 20, rect.bottom - 20);
	Tem_Env=(CEdit *)GetDlgItem(IDC_TMCTRL_TMSET_ENVIR_EDIT);
	Tem_Env->SetFont(&m_Font);
	Tem_Inc=(CEdit *)GetDlgItem(IDC_TMCTRL_TMSET_INCUB_EDIT);
	Tem_Inc->SetFont(&m_Font);

	sdata_cmd[0] = SPI_CMD_REQTEM;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);											
	PC_RECEIVE_FRAME(tempeReceived,SPI_TYPE_TEMRES);
	temper = tempeReceived[0]*10+tempeReceived[1]+tempeReceived[2]*0.1+tempeReceived[3]*0.01;
	//sprintf(tmpeshow, "%.2f", temper);
	tmpeshow.Format(L"%.2f",temper);
	GetDlgItem(IDC_TMCTRL_CURTM_INCUB_SHOW)->SetWindowText((LPCTSTR)tmpeshow);
			//SetWindowText(GetDlgItem(IDC_TMCTRL_CURTM_INCUB_SHOW), tmpeshow);
			temper = tempeReceived[4]*10+tempeReceived[5]+tempeReceived[6]*0.1+tempeReceived[7]*0.01;
			//sprintf(tmpeshow, "%.2f", temper);
			tmpeshow.Format(L"%.2f",temper);
			//SetWindowText(GetDlgItem(hDlg, IDC_TMCTRL_CURTM_ENVIR_SHOW), tmpeshow);
			GetDlgItem(IDC_TMCTRL_CURTM_ENVIR_SHOW)->SetWindowText((LPCTSTR)tmpeshow);			
			//sprintf(tmpeshow, "%.2f", systemcfg.tmp.env);
			tmpeshow.Format(L"%.2f",systemcfg.tmp.env);
			GetDlgItem(IDC_TMCTRL_TMSET_ENVIR_EDIT)->SetWindowText((LPCTSTR)tmpeshow);
			//SetWindowText(hEnv, tmpeshow);
			//sprintf(tmpeshow, "%.2f", systemcfg.tmp.incub);
		    tmpeshow.Format(L"%.2f",systemcfg.tmp.incub);
			GetDlgItem(IDC_TMCTRL_TMSET_INCUB_EDIT)->SetWindowText((LPCTSTR)tmpeshow);

			//SetWindowText(hCup, tmpeshow);
		// TODO: �ڴ˴������Ϣ����������
		// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


void CTemperaturecontrolView::OnBnClickedTmctrlTmsetOk()
{
	Tem_Set_Env = GetDlgItemInt(IDC_TMCTRL_TMSET_ENVIR_EDIT);
	Tem_Set_Inc = GetDlgItemInt(IDC_TMCTRL_TMSET_INCUB_EDIT);
	if(Tem_Set_Env>40||Tem_Set_Env<10||Tem_Set_Inc>40||Tem_Set_Inc<10)
	{
	if(Tem_Set_Env>40||Tem_Set_Env<10)
		MessageBox(L"�������¶����볬����Χ��", L"ERROR", MB_OK);
	else
		systemcfg.tmp.env = Tem_Set_Env;
	if(Tem_Set_Inc>40||Tem_Set_Inc<10)
		MessageBox(L"�Լ��¶����볬����Χ��", L"ERROR", MB_OK);
	else	
	systemcfg.tmp.incub = Tem_Set_Inc;
	}
	else
	{
	SendSysPara();
	WriteSystemcfgFile();
	MessageBox(L"�¶�������ɣ��뷵�أ�", L"OK", MB_OK);
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CTemperaturecontrolView::SendSysPara(void)
{
	int i = 0;
	uchar sdata[50] = { 0 };

	//��DSP���Ͳ�������˶�����
	for (i = XM_START_RINSE; i <= YM_STARTSAMPLE; i++)
	{
		sdata[2 * i] = systemcfg.mstp[i] & 0x00FF; 	//��8λ
		sdata[2 * i + 1] = systemcfg.mstp[i] >> 8;   	//��8λ
	}
	//�¶Ȳ���
	sdata[34] = (int)(systemcfg.tmp.env * 100) / 1000;
	sdata[35] = ((int)(systemcfg.tmp.env * 100) / 100) % 10;
	sdata[36] = ((int)(systemcfg.tmp.env * 100) / 10) % 10;
	sdata[37] = (int)(systemcfg.tmp.env * 100) % 10;
	//�Լ��¶�
	sdata[38] = (int)(systemcfg.tmp.incub * 100) / 1000;
	sdata[39] = ((int)(systemcfg.tmp.incub * 100) / 100) % 10;
	sdata[40] = ((int)(systemcfg.tmp.incub * 100) / 10) % 10;
	sdata[41] = (int)(systemcfg.tmp.incub * 100) % 10;

	sdata[42] = (systemcfg3.diluent == 1) ? 0 : 1;
	sdata[43] = (systemcfg.mode > 1) ? 0 : 1;

	//��ֹ�����쳣�趨�����ֵ
	for (i = 44; i < 50; i++)
		sdata[i] = 0x01;
	PC_SEND_FRAME(sdata, SPI_TYPE_SETTINGS);
}
