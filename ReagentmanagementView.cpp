// ReagentmanagementView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "ReagentmanagementView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CReagentmanagementView �Ի���


static uchar 		DayConCleanFlag = 0;	//Ũ����ϴ��־��1-Ũ����ϴ(ȥ����Һ��ϴ)
static uchar 		DayConCleanStep = 0;	//0:��ʼ״̬,1:��һ��ִ����,2:�ڶ���ִ����

IMPLEMENT_DYNAMIC(CReagentmanagementView, CDialogEx)

CReagentmanagementView::CReagentmanagementView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CReagentmanagementView::IDD, pParent)
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

CReagentmanagementView::~CReagentmanagementView()
{
}

void CReagentmanagementView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CReagentmanagementView, CDialogEx)
	
	ON_BN_CLICKED(IDC_MAINTENANCE_WEEKLY_OK1, &CReagentmanagementView::OnBnClickedMaintenanceWeeklyOk1)
	ON_BN_CLICKED(IDC_MAINTENANCE_WEEKLY_OK2, &CReagentmanagementView::OnBnClickedMaintenanceWeeklyOk2)
	ON_BN_CLICKED(IDC_MAINTENANCE_YEARLY, &CReagentmanagementView::OnBnClickedMaintenanceYearly)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_MESSAGE(WM_ACKSPI, &CReagentmanagementView::OnAckspi)
END_MESSAGE_MAP()


// CReagentmanagementView ��Ϣ�������




void CReagentmanagementView::OnBnClickedMaintenanceWeeklyOk1()
{
	if(0 == DayConCleanStep)
		{
	//ARM_GPIOCMD(EN_RED);
	TRACE("DAILY MAINTENANCE---------!#\n");
	key_status = FALSE;		
	DSP_status = Busy;
	sdata_cmd[0] = SPI_CMD_CONCENTRATE_CLEAN1;	
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	
	if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			MessageBox(L"����Ͳ��ɹ���", L"ERROR", MB_OKCANCEL);
	else
	       {
			   SetTimer( POLLTIME,SPI_POLL_TIME1000,0);
			   GetDlgItem(IDC_STATIC_WEEKLY)->SetWindowText(L"����ִ�е�һ����");
			  DayConCleanFlag = 1;
	        }
			//ConcentratedCleaning_1(hDlg,"DAILY MAINTENANCE---------!#\n");
		}
	else
		MessageBox(L"��һ�������!",L"��ʾ",0);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CReagentmanagementView::OnBnClickedMaintenanceWeeklyOk2()
{
	if(1 == DayConCleanStep)
		{
	//ARM_GPIOCMD(EN_RED);
	TRACE("DAILY MAINTENANCE---------!#\n");
	key_status = FALSE;		
	DSP_status = Busy;
	sdata_cmd[0] = SPI_CMD_CONCENTRATE_CLEAN2;	
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	
	if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			MessageBox(L"����Ͳ��ɹ���", L"ERROR", MB_OKCANCEL);
	else
	       {
			   SetTimer( POLLTIME,SPI_POLL_TIME1000,0);
			   GetDlgItem(IDC_STATIC_WEEKLY)->SetWindowText(L"����ִ�еڶ�����");
			  // DayConCleanStep=0;
			   DayConCleanFlag = 1;
	        }
			//ConcentratedCleaning_1(hDlg,"DAILY MAINTENANCE---------!#\n");
		}
	else
		MessageBox(L"����ִ�е�һ��!",L"��ʾ",0);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CReagentmanagementView::OnBnClickedMaintenanceYearly()
{

	//ARM_GPIOCMD(EN_RED);
	TRACE("YEARLY MAINTENANCE----------!#\n");
	key_status = FALSE;		
	DSP_status = Busy;
	sdata_cmd[0] = SPI_CMD_MONTHLYMAINTAIN;	
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	
	if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			MessageBox(L"����Ͳ��ɹ���", L"ERROR", MB_OKCANCEL);
	else
	       {
			   SetTimer( POLLTIME,SPI_POLL_TIME3000,0);
			   GetDlgItem(IDC_STATIC_WEEKLY)->SetWindowText(L"����ִ���걣����");
			  // DayConCleanStep=0;
			  
	        }
			//ConcentratedCleaning_1(hDlg,"DAILY MAINTENANCE---------!#\n");
		
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


HBRUSH CReagentmanagementView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SelectObject(&m_Font);
		pDC->SetBkColor(RGB(255, 255, 255));//���ֱ���ɫ
		HBRUSH b = CreateSolidBrush(RGB(255, 255, 255));//�ؼ�����ɫ   
		return b;
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CReagentmanagementView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
		CRect   rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));   //����Ϊ��ɫ����
	dc.Rectangle(30, 20, rect.right/2-10 , rect.bottom - 70);
	dc.Rectangle(rect.right/2+10, 20, rect.right-30 , rect.bottom - 70);
		// TODO: �ڴ˴������Ϣ����������
		// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


void CReagentmanagementView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case POLLTIME:
		TRACE("MSG_TIMER:POLLTIME is due -------------#\n");
					sdata_cmd[0] = SPI_CMD_REQDSP_STATUS;	
				 	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
					PC_RECEIVE_FRAME(rdata_state,SPI_TYPE_STATE);	
					SendMessage(WM_ACKSPI,rdata_state[0],0);
					break;
				default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


afx_msg LRESULT CReagentmanagementView::OnAckspi(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
			{
				//�ճ�ά�����
				case SPI_STATE_INFO_END:
					if(1 == DayConCleanFlag)//����Ũ����ϴ
					{
						//ARM_GPIOCMD(EN_GREEN);
						KillTimer( POLLTIME);
						DSP_status = Free;
						DayConCleanStep++;
						if(1 == DayConCleanStep)
						{
							//if(systemcfg.language == CHINESE)
							MessageBox(L"����ÿ�����м�3ml ȥ����Һ,��ִ�еڶ���",L"��ʾ",0);
						//	else if(systemcfg.language == ENGLISH)
							//	SetDlgItemText(hDlg, IDC_MAINTENANCE_WEEKLY_MESS,"Add 3ml protein solution to each cup,and Excute the action of Concentrated Cleaning Step 2");
						}
						else if(2 == DayConCleanStep)
						{
							//if(systemcfg.language == CHINESE)
								MessageBox(L"Ũ����ϴ���",L"��ʾ",0);
								//SetDlgItemText(hDlg, IDC_MAINTENANCE_WEEKLY_MESS,"Ũ����ϴ���");
							//else if(systemcfg.language == ENGLISH)
							//	SetDlgItemText(hDlg, IDC_MAINTENANCE_WEEKLY_MESS,"Concentrated Cleaning Done");
							DayConCleanStep = 0;
						}
						DayConCleanFlag = 0;
						key_status = TRUE;
					}
					else
					{
						//ARM_GPIOCMD(EN_RED);
						KillTimer( POLLTIME);
						DSP_status = Free ;
						key_status = TRUE;
					}
					break;
				default:
					break;
			}
	return 0;
}
