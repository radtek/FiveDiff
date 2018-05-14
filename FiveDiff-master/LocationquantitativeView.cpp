// LocationquantitativeView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "LocationquantitativeView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CLocationquantitativeView �Ի���

IMPLEMENT_DYNAMIC(CLocationquantitativeView, CDialogEx)

CLocationquantitativeView::CLocationquantitativeView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLocationquantitativeView::IDD, pParent)
{

}

CLocationquantitativeView::~CLocationquantitativeView()
{
}

void CLocationquantitativeView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLocationquantitativeView, CDialogEx)
	ON_BN_CLICKED(IDC_DEBUG_XYRATION, &CLocationquantitativeView::OnBnClickedDebugXyration)
	ON_BN_CLICKED(IDC_DEBUG_SAMPLERATION, &CLocationquantitativeView::OnBnClickedDebugSampleration)
	ON_BN_CLICKED(IDC_DEBUG_HGBLYSERATION, &CLocationquantitativeView::OnBnClickedDebugHgblyseration)
	ON_BN_CLICKED(IDC_DEBUG_RINSERATION, &CLocationquantitativeView::OnBnClickedDebugRinseration)
	ON_BN_CLICKED(IDC_DEBUG_FIXRATION, &CLocationquantitativeView::OnBnClickedDebugFixration)
	ON_BN_CLICKED(IDC_DEBUG_DILUENTRATION, &CLocationquantitativeView::OnBnClickedDebugDiluentration)
	ON_BN_CLICKED(IDC_DEBUG_WBCLYSERATION, &CLocationquantitativeView::OnBnClickedDebugWbclyseration)
	ON_BN_CLICKED(IDC_DEBUG_ESCAPE, &CLocationquantitativeView::OnBnClickedDebugEscape)
	ON_WM_TIMER()
	ON_MESSAGE(WM_ACKSPI, &CLocationquantitativeView::OnAckspi)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CLocationquantitativeView ��Ϣ�������


void CLocationquantitativeView::OnBnClickedDebugXyration()
{
		//ARM_GPIOCMD(EN_RED);
				  TRACE("XY  RATION---------#\n");
					key_status = FALSE;
					DSP_status = Busy;
					sdata_cmd[0] = SPI_CMD_XYRATION;	
					PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			MessageBox(L"����Ͳ��ɹ���", L"ERROR", MB_OKCANCEL);
	   else{
		    GetDlgItem(IDC_DEBUG_XYRATION)->SetWindowText(L"����ִ��XY��λ��");
			SetWindowDisable();
			SetTimer( POLLTIME, SPI_POLL_TIME1000,0);
	   }
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CLocationquantitativeView::SetWindowEnable(void)
{
	GetDlgItem(IDC_DEBUG_XYRATION)->EnableWindow(TRUE);
	GetDlgItem(IDC_DEBUG_SAMPLERATION)->EnableWindow(TRUE);
	GetDlgItem(IDC_DEBUG_HGBLYSERATION)->EnableWindow(TRUE);
	GetDlgItem(IDC_DEBUG_RINSERATION)->EnableWindow(TRUE);
	GetDlgItem(IDC_DEBUG_FIXRATION)->EnableWindow(TRUE);
	GetDlgItem(IDC_DEBUG_DILUENTRATION)->EnableWindow(TRUE);
	GetDlgItem(IDC_DEBUG_WBCLYSERATION)->EnableWindow(TRUE);
	GetDlgItem(IDC_DEBUG_ESCAPE)->EnableWindow(TRUE);
	
}


void CLocationquantitativeView::SetWindowDisable(void)
{
	GetDlgItem(IDC_DEBUG_XYRATION)->EnableWindow(FALSE);
	GetDlgItem(IDC_DEBUG_SAMPLERATION)->EnableWindow(FALSE);
	GetDlgItem(IDC_DEBUG_HGBLYSERATION)->EnableWindow(FALSE);
	GetDlgItem(IDC_DEBUG_RINSERATION)->EnableWindow(FALSE);
	GetDlgItem(IDC_DEBUG_FIXRATION)->EnableWindow(FALSE);
	GetDlgItem(IDC_DEBUG_DILUENTRATION)->EnableWindow(FALSE);
	GetDlgItem(IDC_DEBUG_WBCLYSERATION)->EnableWindow(FALSE);
	GetDlgItem(IDC_DEBUG_ESCAPE)->EnableWindow(FALSE);
}


void CLocationquantitativeView::OnBnClickedDebugSampleration()
{
	        TRACE("SAMPLE  RATION---------#\n");
		    key_status = FALSE;
			DSP_status = Busy;
			sdata_cmd[0] = SPI_CMD_SAMPLERATION;	
			PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			MessageBox(L"����Ͳ��ɹ���", L"ERROR", MB_OKCANCEL);
	   else{
		    GetDlgItem(IDC_DEBUG_SAMPLERATION)->SetWindowText(L"����ִ�в���������");
			SetWindowDisable();
			SetTimer( POLLTIME, SPI_POLL_TIME1000,0);
	   }
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CLocationquantitativeView::OnBnClickedDebugHgblyseration()
{
	   TRACE("HGB  LYSERATION---------#\n");
		    key_status = FALSE;
			DSP_status = Busy;
			sdata_cmd[0] =  SPI_CMD_HGBLYSERATION;	
			PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			MessageBox(L"����Ͳ��ɹ���", L"ERROR", MB_OKCANCEL);
	   else{
		    GetDlgItem(IDC_DEBUG_HGBLYSERATION)->SetWindowText(L"����ִ��HGB������");
			SetWindowDisable();
			SetTimer( POLLTIME, SPI_POLL_TIME1000,0);
	   }
	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CLocationquantitativeView::OnBnClickedDebugRinseration()
{
	 TRACE("RINSE  RATION---------#\n");
		    key_status = FALSE;
			DSP_status = Busy;
			sdata_cmd[0] = SPI_CMD_RINSERATION;	
			PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			MessageBox(L"����Ͳ��ɹ���", L"ERROR", MB_OKCANCEL);
	   else{
		    GetDlgItem(IDC_DEBUG_RINSERATION)->SetWindowText(L"����ִ��RINSE������");
			SetWindowDisable();
			SetTimer( POLLTIME, SPI_POLL_TIME1000,0);
	   }
	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CLocationquantitativeView::OnBnClickedDebugFixration()
{
	        TRACE("FIX  RATION---------#\n");
		    key_status = FALSE;
			DSP_status = Busy;
			sdata_cmd[0] = SPI_CMD_FIXRATION;	
			PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			MessageBox(L"����Ͳ��ɹ���", L"ERROR", MB_OKCANCEL);
	   else{
		    GetDlgItem(IDC_DEBUG_FIXRATION)->SetWindowText(L"����ִ�����ᶨ����");
			SetWindowDisable();
			SetTimer( POLLTIME, SPI_POLL_TIME1000,0);
	   }
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CLocationquantitativeView::OnBnClickedDebugDiluentration()
{
	
	        TRACE("DILUETN  RATION---------#\n");
		    key_status = FALSE;
			DSP_status = Busy;
			sdata_cmd[0] = SPI_CMD_DILUETNRATION;	
			PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			MessageBox(L"����Ͳ��ɹ���", L"ERROR", MB_OKCANCEL);
	   else{
		    GetDlgItem(IDC_DEBUG_DILUENTRATION)->SetWindowText(L"����ִ��HB-5D������");
			SetWindowDisable();
			SetTimer( POLLTIME, SPI_POLL_TIME1000,0);
	   }
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CLocationquantitativeView::OnBnClickedDebugWbclyseration()
{
	        TRACE("DILUETN  RATION---------#\n");
		    key_status = FALSE;
			DSP_status = Busy;
			sdata_cmd[0] = SPI_CMD_WBCLYSERATION;	
			PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			MessageBox(L"����Ͳ��ɹ���", L"ERROR", MB_OKCANCEL);
	   else{
		    GetDlgItem(IDC_DEBUG_WBCLYSERATION)->SetWindowText(L"����ִ��BAS������");
			SetWindowDisable();
			SetTimer( POLLTIME, SPI_POLL_TIME1000,0);
	   }
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CLocationquantitativeView::OnBnClickedDebugEscape()
{
	
	CDialogEx::OnCancel();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CLocationquantitativeView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch(nIDEvent)
			{
				case POLLTIME:
					{
					TRACE("MSG_TIMER:POLLTIME is due -------------#\n");
					sdata_cmd[0] = SPI_CMD_REQDSP_STATUS;	
				 	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
					PC_RECEIVE_FRAME(rdata_state,SPI_TYPE_STATE);	
					SendMessage(WM_ACKSPI,rdata_state[0],0);
					}
					break;
				default:
					break;
			}
	CDialogEx::OnTimer(nIDEvent);
}


afx_msg LRESULT CLocationquantitativeView::OnAckspi(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
			{
				//��λ�붨�����
				case SPI_STATE_INFO_END:
					//ARM_GPIOCMD(EN_GREEN);
					KillTimer( POLLTIME); 
					DSP_status = Free ;
					key_status = TRUE;
					SetWindowEnable();
					break;
				default:
					break;
			}
	
	
	return 0;
}


void CLocationquantitativeView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	/*@TG
#3073*/
	CRect   rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));   //����Ϊ��ɫ����
	dc.Rectangle(30, 10, rect.right - 30, rect.bottom - 30);
		// TODO: �ڴ˴������Ϣ����������
		// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}
