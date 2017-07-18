// LmnetestView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "LmnetestView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CLmnetestView �Ի���
 char buff[6] = {0};
static char SfPipeCheckQuery = 0;	//0����ѯ��1��ѯ
unsigned char buffer[8] = {0};		//����DSP������
static unsigned int CntNum = 0;
static float lamp = 0;			//���ݸ�ʽΪ12.34
unsigned char lamp_query[20][6]={"0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00"};			//20���������
unsigned char transfer_time_query[20][6]={"0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0"};	//���65535����6���ַ�
unsigned char res_time_query[20][6]={"0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0"};
unsigned char absorb_time_query[20][6]={"0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0"};

static unsigned int transfer_time = 0; 
static unsigned char res = 0;
static unsigned char absorb = 0;

IMPLEMENT_DYNAMIC(CLmnetestView, CDialogEx)

CLmnetestView::CLmnetestView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLmnetestView::IDD, pParent)
{
	 
}

CLmnetestView::~CLmnetestView()
{
}

void CLmnetestView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_LIST, my_List);
	//  DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_LIST, m_List);
}


BEGIN_MESSAGE_MAP(CLmnetestView, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_SFPIPECHECK_OK, &CLmnetestView::OnBnClickedSfpipecheckOk)
	ON_WM_TIMER()
	ON_MESSAGE(WM_ACKSPI, &CLmnetestView::OnAckspi)
	ON_BN_CLICKED(IDC_SFPIPECHECK_QUERY, &CLmnetestView::OnBnClickedSfpipecheckQuery)
	ON_BN_CLICKED(IDC_SFPIPECHECK_QUERY, &CLmnetestView::OnBnClickedSfpipecheckQuery)
	ON_BN_CLICKED(IDC_CANCEL, &CLmnetestView::OnBnClickedCancel)
END_MESSAGE_MAP()


// CLmnetestView ��Ϣ�������


void CLmnetestView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	static int i;
	CRect   rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));   //����Ϊ��ɫ����
	dc.Rectangle(40, 10, rect.right - 40, rect.bottom - 40);
	CString str;
	str.Format(L"%d",CntNum);
	GetDlgItem(IDC_LMNETest_2)->SetWindowText((LPCTSTR)str);
	//if(lamp >= 5.50 && lamp <= 6.50)		//������Χ��Ҫ������
	//		{
	//			sprintf(buff,"%.2f",lamp);
	//		}
	//		else if((lamp >= 4 && lamp < 5.50) || (lamp > 6.50 && lamp <= 8))		//������Χ��Ҫ������
	//		{
	//			dc.SetTextColor(RGB(255,0,0));
	//			sprintf(buff,"%.2f",lamp);
	//		}
	//		else 
	//		{
	//			//SetTextColor(hdc, COLOR_red);
	//			dc.SetTextColor(RGB(255,0,0));
	//			sprintf(buff,"%.2f",lamp);
	//		}	
			
			sprintf(buff,"%.2f",lamp);
			if(CntNum >= 1 && CntNum <= 20)
			{
				for(i  = 0;i < 6; i++)
					lamp_query[CntNum-1][i] = buff[i];
			}
			str.Format(L"%.2f",lamp);
			GetDlgItem(IDC_LV)->SetWindowText((LPCTSTR)str);

			sprintf(buff,"%d",transfer_time);
			if(CntNum >= 1 && CntNum <= 20)
			{
				for(i  = 0; i < 6; i++)
					transfer_time_query[CntNum-1][i] = buff[i];
			}
			str.Format(L"%d",transfer_time);
			GetDlgItem(IDC_Time)->SetWindowText((LPCTSTR)str);

			sprintf(buff,"%d",res);
			if(CntNum >= 1 && CntNum <= 20)
			{
				for(i  = 0; i < 6; i++)
					res_time_query[CntNum-1][i] = buff[i];
			}
			str.Format(L"%d",res);
			GetDlgItem(IDC_R)->SetWindowText((LPCTSTR)str);

			sprintf(buff,"%d",absorb);
			if(CntNum >= 1 && CntNum <= 20)
			{
				for(i  = 0; i < 6; i++)
					absorb_time_query[CntNum-1][i] = buff[i];	
			}
			str.Format(L"%d",absorb);
			GetDlgItem(IDC_L)->SetWindowText((LPCTSTR)str);


	/*@TG
#3073*/
		// TODO: �ڴ˴������Ϣ����������
		// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


HBRUSH CLmnetestView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		switch (pWnd->GetDlgCtrlID())
		{
		case IDC_LV:
		{
		if(lamp >= 5.50 && lamp <= 6.50)
		pDC->SetTextColor(RGB(0, 0, 0));
		else if((lamp >= 4 && lamp < 5.50) || (lamp > 6.50 && lamp <= 8))		//������Χ��Ҫ������
			{
				pDC->SetTextColor(RGB(255,0,0));				
			}
		else 
			{
				//SetTextColor(hdc, COLOR_red);
				pDC->SetTextColor(RGB(255,0,0));
				
			}	
		}break;
		case IDC_Time:
		{
		if(transfer_time >= 150 && transfer_time <= 250)
		pDC->SetTextColor(RGB(0, 0, 0));
		else if(((transfer_time >= 100 && transfer_time < 150) || (transfer_time > 250 && transfer_time <= 300)))		//������Χ��Ҫ������
			{
				pDC->SetTextColor(RGB(255,0,0));				
			}
		       else 
			{
				//SetTextColor(hdc, COLOR_red);
				pDC->SetTextColor(RGB(255,0,0));
				
			}	
		}break;

		case IDC_R:
		{
		if(res >= 10 && res <= 240)
		pDC->SetTextColor(RGB(0, 0, 0));
		else if((res >= 0 && res < 10) || (res > 240 && res <= 255))		//������Χ��Ҫ������
			{
				pDC->SetTextColor(RGB(255,0,0));				
			}
		       else 
			{
				//SetTextColor(hdc, COLOR_red);
				pDC->SetTextColor(RGB(255,0,0));
				
			}	
		}break;


		case IDC_L:
		{
		if(absorb >= 10 && absorb <= 240)
		pDC->SetTextColor(RGB(0, 0, 0));
		else if((absorb >= 0 && absorb < 10) || (absorb > 240&& absorb <= 255))		//������Χ��Ҫ������
			{
				pDC->SetTextColor(RGB(255,0,0));				
			}
		       else 
			{
				//SetTextColor(hdc, COLOR_red);
				pDC->SetTextColor(RGB(255,0,0));
				
			}	
		}break;

		default:
			pDC->SetTextColor(RGB(0, 0, 0));
			break;
		//pDC->SelectObject(&m_Font);
		}
		pDC->SetBkColor(RGB(255, 255, 255));//���ֱ���ɫ
		HBRUSH b = CreateSolidBrush(RGB(255, 255, 255));//�ؼ�����ɫ   
		return b;
	}

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
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CLmnetestView::OnBnClickedSfpipecheckOk()
{
	
	   key_status = FALSE;
       CntNum = 0;
	SfPipeCheckQuery = 0;
	DSP_status = Busy;
	sdata_cmd[0] = SPI_CMD_DIFFADJUST;
	PC_SEND_FRAME(sdata_cmd,SPI_TYPE_CMD);
	if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
		                MessageBox(L"����Ͳ��ɹ���", L"ERROR", MB_OKCANCEL);
	else 
	{
		 InvalidateRect(NULL,TRUE);
		 GetDlgItem(IDC_SFPIPECHECK_OK)->SetWindowText(L"���ڲ��ԣ�");
		 GetDlgItem(IDC_SFPIPECHECK_OK)->EnableWindow(FALSE);
		 GetDlgItem(IDC_SFPIPECHECK_QUERY)->EnableWindow(FALSE);
		 GetDlgItem(IDC_CANCEL)->EnableWindow(FALSE);
		 SetTimer(SLEEP_TIMER1,3500,0);
	}
		
					//������ѯ��ʱ��
   		//5000->3500,���ڲ���ʱ���
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CLmnetestView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case SLEEP_TIMER1:
		{
	KillTimer(SLEEP_TIMER1);
					TRACE("MSG_TIMER:SLEEP_TIMER1 is due -------------#\n");		
					PC_status = WAITING_DATA;
					//�趨��ѯ���ƻ�״̬�Ķ�ʱ��		
					SetTimer( POLLTIME, 500,0);    //��ѯʱ�䶨ʱ��
		}break;
		case POLLTIME:
					//ѯ�ʿ��ƻ���������Ƿ�׼����
					sdata_cmd[0] =  SPI_CMD_REQDSP_STATUS;
					PC_SEND_FRAME(sdata_cmd,SPI_TYPE_CMD);
					PC_RECEIVE_FRAME(rdata_state,SPI_TYPE_STATE);					
					SendMessage(WM_ACKSPI,rdata_state[0],0);					
					break;
	
	}
	CDialogEx::OnTimer(nIDEvent);
}

afx_msg LRESULT CLmnetestView::OnAckspi(WPARAM wParam, LPARAM lParam)
{
				switch(wParam)
			{
				case SPI_STATE_INFO_NOTREADY://����δ׼���ã�����ѯ��
					break;
				case SPI_STATE_DATAISOK:
					if(CntNum < 20)
					{
						KillTimer(POLLTIME);
						//����  ����
						sdata_cmd[0] = SPI_CMD_REQDIFFADJUST;	
						PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);											
						PC_RECEIVE_FRAME(buffer,SPI_TYPE_DIFFADJUSTRES);
						//���ݽ���	
						CntNum = CntNum +1;				
						lamp = (float)(buffer[0]*1000 + buffer[1]*100 + buffer[2]*10 + buffer[3])/100.0;				
						transfer_time = (buffer[5]<<8) + buffer[4];
						absorb = buffer[6];					
						res = buffer[7];
						//�Խ��չ������ݣ������жϣ����ݴ����쳣����Ϊ0
						if(!(lamp > 0.0 && lamp < 12.0))	
							lamp = 0.0;
						if(!(transfer_time >= 0 && transfer_time <= 300))		//300����
							transfer_time = 0;
						if(!(absorb >= 0 && absorb <= 255))
							absorb = 0;
						if(!(res >= 0 && res <= 255))
							res = 0;
						TRACE("CntNum:---- %d ---\n", CntNum);
						InvalidateRect(NULL,TRUE);	
						SetTimer(POLLTIME, 500,0);
					}
					break;
				case SPI_STATE_INFO_END:
					//ARM_GPIOCMD(EN_GREEN);
					TRACE("SPI_STATE_INFO_END\n");
					key_status = TRUE;
					KillTimer(POLLTIME);
					DSP_status = Free ;
				   GetDlgItem(IDC_SFPIPECHECK_OK)->EnableWindow(TRUE);
		            GetDlgItem(IDC_SFPIPECHECK_QUERY)->EnableWindow(TRUE);
		             GetDlgItem(IDC_CANCEL)->EnableWindow(TRUE);
					break;
				default:
					break;
	
				}
	return 0;
}



void CLmnetestView::OnBnClickedSfpipecheckQuery()
{
	int i = 0;
	CString str,str1,str2,str3;
	SfPipeCheckQuery = 1;
	//InvalidateRect(NULL,TRUE);
	//SendMessage(WM_PAINT,0,0);
	for(i=0;i<20;i++)
	{
		/*  str="0";*/
		//str.Format(L"%.2f",lamp_query[i]);
		//str.Format(L"%.2f",lamp_query[i]);
		str=lamp_query[i];
	   m_List.SetItemText(i, 1, (LPCTSTR)str);
	  
	str1.Format(L"%d", transfer_time_query[i]);
	str1=transfer_time_query[i];
	   m_List.SetItemText(i, 2,(LPCTSTR)str1);
	 
	  // str2.Format(L"%d", res_time_query[i]);
		str2=res_time_query[i];
	   m_List.SetItemText(i, 3, (LPCTSTR)str2);
		
		  //str3.Format(L"%d",  absorb_time_query[i]);
	str3=absorb_time_query[i];
		
	
		 m_List.SetItemText(i, 4, (LPCTSTR)str3); /**/
		 
	 	
	}

					//
	//���ɲ�ѯ�б���
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CLmnetestView::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


BOOL CLmnetestView::InitForm(void)
{
	CRect rect;
	m_List.GetClientRect(&rect);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_List.SetExtendedStyle(m_List.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_List.SetRowHeigt(20);

	m_List.DeleteAllItems();//����б�ˢ��

	/*m_List.DeleteColumn(0);
	m_List.DeleteColumn(1);
	m_List.DeleteColumn(2);
	m_List.DeleteColumn(3);
	m_List.DeleteColumn(4);
	m_List.DeleteColumn(5);*/

	// ΪWBC�б���ͼ�ؼ��������   
	m_List.InsertColumn(0, _T("�������"), LVCFMT_CENTER, rect.Width() / 5, 1);
	m_List.InsertColumn(1, _T("���ݵ�ѹֵ"), LVCFMT_CENTER, rect.Width() / 5, 1);
	m_List.InsertColumn(2, _T("ת��ʱ��"), LVCFMT_CENTER, rect.Width() / 5, 2);
	m_List.InsertColumn(3, _T("���迹ͨ��"), LVCFMT_CENTER, rect.Width() / 5, 3);
	m_List.InsertColumn(4, _T("�����ͨ��"), LVCFMT_CENTER, rect.Width() / 5, 4);
	

	// ��WBC�б���ͼ�ؼ��в����б���������б������ı�   
	m_List.InsertItem(0, _T("1"));
		//m_List.SetItemText(0, 2, _T("10^9/L"));
	m_List.InsertItem(1, _T("2"));
		//m_List.SetItemText(1, 2, _T("%"));
	m_List.InsertItem(2, _T("3"));
		//m_List.SetItemText(2, 2, _T("%"));
	m_List.InsertItem(3, _T("4"));
		//m_List.SetItemText(3, 2, _T("%"));
	m_List.InsertItem(4, _T("5"));
		//m_List.SetItemText(4, 2, _T("%"));
	m_List.InsertItem(5, _T("6"));
		//m_List.SetItemText(5, 2, _T("%"));
	m_List.InsertItem(6, _T("7"));
		//m_List.SetItemText(6, 2, _T("%"));
	m_List.InsertItem(7, _T("8"));
		//m_List.SetItemText(7, 2, _T("%"));
	m_List.InsertItem(8, _T("9"));
		//m_List.SetItemText(8, 2, _T("10^9/L"));
	m_List.InsertItem(9, _T("10"));
		//m_List.SetItemText(9, 2, _T("10^9/L"));
	m_List.InsertItem(10, _T("11"));
		//m_List.SetItemText(10, 2, _T("10^9/L"));
	m_List.InsertItem(11, _T("12"));
		//m_List.SetItemText(11, 2, _T("10^9/L"));
	m_List.InsertItem(12, _T("13"));
		//m_List.SetItemText(12, 2, _T("10^9/L"));
	m_List.InsertItem(13, _T("14"));
		//m_List.SetItemText(13, 2, _T("10^9/L"));
	m_List.InsertItem(14, _T("15"));
		//m_List.SetItemText(14, 2, _T("10^9/L"));
	m_List.InsertItem(15, _T("16"));
	m_List.InsertItem(16, _T("17"));
	m_List.InsertItem(17, _T("18"));
	m_List.InsertItem(18, _T("19"));
	m_List.InsertItem(19, _T("20"));

	
	return 0;
}


//void CLmnetestView::OnInitialUpdat(void)
//{
//	InitFor();
//}


//void CLmnetestView::OnInitialUpdate(void)
//{
//	CDialogEx::OnInitialUpdate();
//	InitFor();
//}


BOOL CLmnetestView::OnInitDialog()
{
		
	CDialogEx::OnInitDialog();
	InitForm();
	return TRUE;
//#5312
//
//	return TRUE;  // return TRUE unless you set the focus to a control
//#5313
//
//#5312
//
//	return TRUE;  // return TRUE unless you set the focus to a control
//#5313
//	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
//
//	return TRUE;  // return TRUE unless you set the focus to a control
//#5313
//	return TRUE;  // return TRUE unless you set the focus to a control
//#5313
	// �쳣: OCX ����ҳӦ���� FALSE
}
