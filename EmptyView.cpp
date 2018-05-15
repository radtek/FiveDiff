// EmptyView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "EmptyView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CEmptyView �Ի���

IMPLEMENT_DYNAMIC(CEmptyView, CDialogEx)

CEmptyView::CEmptyView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEmptyView::IDD, pParent)
{

}

CEmptyView::~CEmptyView()
{
}

void CEmptyView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEmptyView, CDialogEx)
	
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_DRAIN_WASTE, &CEmptyView::OnBnClickedDrainWaste)
	ON_BN_CLICKED(IDC_DRAIN_RINSE, &CEmptyView::OnBnClickedDrainRinse)
	ON_BN_CLICKED(IDC_DRAIN_HGB, &CEmptyView::OnBnClickedDrainHgb)
	ON_BN_CLICKED(IDC_DRAIN_RBC, &CEmptyView::OnBnClickedDrainRbc)
	ON_BN_CLICKED(IDC_DRAIN_BASO, &CEmptyView::OnBnClickedDrainBaso)
	ON_BN_CLICKED(IDC_DRAIN_LMNE, &CEmptyView::OnBnClickedDrainLmne)
	ON_BN_CLICKED(IDC_DRAIN_ALL, &CEmptyView::OnBnClickedDrainAll)
	ON_BN_CLICKED(IDC_DRAIN_DILUENT_POT, &CEmptyView::OnBnClickedDrainDiluentPot)
	ON_BN_CLICKED(IDC_DRAIN_CTM, &CEmptyView::OnBnClickedDrainCtm)
	ON_BN_CLICKED(IDC_DRAIN_PIPE, &CEmptyView::OnBnClickedDrainPipe)
	ON_BN_CLICKED(IDC_DRAIN_ESCAPE, &CEmptyView::OnBnClickedDrainEscape)
	ON_WM_TIMER()
	ON_MESSAGE(WM_ACKSPI, &CEmptyView::OnAckspi)
END_MESSAGE_MAP()


// CEmptyView ��Ϣ�������





void CEmptyView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect   rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));   //����Ϊ��ɫ����
	dc.Rectangle(40, 20, rect.right - 70, rect.bottom - 50);
}


void CEmptyView::OnBnClickedDrainWaste()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	DrainReagent("DRAIN WASTE--------#\n", SPI_CMD_DRAIN_WASTE, SPI_POLL_TIME1000);
	
}


void CEmptyView::DrainReagent(char * Mess, uchar CMD, unsigned int m_ntime)
{
	TRACE(Mess);
	DSP_status = Busy;
	sdata_cmd[0] = CMD;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
	{
		//DrainReagent(Mess, CMD, m_ntime);
		MessageBox(L"����Ͳ��ɹ���", L"ERROR", MB_OK);
	}
		
	else//����ͳɹ�
	{
		SetTimer(POLLTIME2, m_ntime, 0);
		SetWindowDisable();
	}
	
}


void CEmptyView::OnBnClickedDrainRinse()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	DrainReagent("DRAIN RINSE--------#\n", SPI_CMD_DRAIN_RINSE,SPI_POLL_TIME1000);
}

void CEmptyView::OnBnClickedDrainHgb()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	DrainReagent("DRAIN HGB--------#\n", SPI_CMD_DRAIN_HGB, SPI_POLL_TIME1000);

}

void CEmptyView::OnBnClickedDrainRbc()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	DrainReagent("DRAIN RBC--------#\n", SPI_CMD_DRAIN_RBC, SPI_POLL_TIME1000);

}

void CEmptyView::OnBnClickedDrainBaso()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	DrainReagent("DRAIN BASO--------#\n", SPI_CMD_DRAIN_BASO, SPI_POLL_TIME1000);

}

void CEmptyView::OnBnClickedDrainLmne()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	DrainReagent("DRAIN LMNE--------#\n", SPI_CMD_DRAIN_LMNE, SPI_POLL_TIME1000);

}

void CEmptyView::OnBnClickedDrainAll()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	DrainReagent("DRAIN ALL--------#\n", SPI_CMD_DRAIN_ALL, SPI_POLL_TIME1000);

}

void CEmptyView::OnBnClickedDrainDiluentPot()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	DrainReagent("DRAIN DILUENT_POT--------#\n", SPI_CMD_DRAIN_DILUENT_RESERVOIR, SPI_POLL_TIME1000);

}

void CEmptyView::OnBnClickedDrainCtm()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	DrainReagent("DRAIN CTM--------#\n", SPI_CMD_DRAIN_CTM, SPI_POLL_TIME1000);

}

void CEmptyView::OnBnClickedDrainPipe()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	DrainReagent("DRAIN PIPE--------#\n", SPI_CMD_DRAIN_PIPE, SPI_POLL_TIME1000);

}

void CEmptyView::OnBnClickedDrainEscape()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
	//SetWindowEnable();
}

void CEmptyView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent){
	case POLLTIME2:
		TRACE("MSG_TIMER:POLLTIME is due -------------#\n");
		sdata_cmd[0] = SPI_CMD_REQDSP_STATUS;
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		PC_RECEIVE_FRAME(rdata_state, SPI_TYPE_STATE);
		SendMessage(WM_ACKSPI, rdata_state[0], 0);

		SetWindowEnable();//ʹ����ʹ��
		break;
	//case POLLTIME3:
	//	break;
	}
CDialogEx::OnTimer(nIDEvent);

}


afx_msg LRESULT CEmptyView::OnAckspi(WPARAM wParam, LPARAM lParam)
{

	switch (wParam)
	{
		//�ſ����
	case SPI_STATE_INFO_END:
				TRACE(_T("SPI_STATE_INFO_END"));
		KillTimer(POLLTIME2);
		DSP_status = Free;
		statusShowMess = 0;
		//InvalidateRect(hDlg, &STATUS, TRUE);
		key_status = TRUE;
		//Standby_EN = TRUE;
		break;
		case SPI_STATE_ERROR_DRM:
				//	if(systemcfg.language == CHINESE)
						MessageBox(L"��Һ��ʱ,��ػ����",L"����!",MB_OK | MB_ICONINFORMATION);
				//	else if(systemcfg.language == ENGLISH)
				//		CreateWarningBoxNonCHDlg(hDlg, "Drain over time,please shutdown and have a check", "Warning!");
					while(1)
						Sleep(100);
					break;
	default:
		break;
	}
	return 0;
}


void CEmptyView::SetWindowDisable()
{

	GetDlgItem(IDC_DRAIN_WASTE)->EnableWindow(FALSE);
	GetDlgItem(IDC_DRAIN_RINSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_DRAIN_HGB)->EnableWindow(FALSE);
	GetDlgItem(IDC_DRAIN_RBC)->EnableWindow(FALSE);
	GetDlgItem(IDC_DRAIN_BASO)->EnableWindow(FALSE);

	GetDlgItem(IDC_DRAIN_LMNE)->EnableWindow(FALSE);
	GetDlgItem(IDC_DRAIN_ALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_DRAIN_DILUENT_POT)->EnableWindow(FALSE);
	GetDlgItem(IDC_DRAIN_CTM)->EnableWindow(FALSE);
	GetDlgItem(IDC_DRAIN_PIPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_DRAIN_ESCAPE)->EnableWindow(FALSE);

}


void CEmptyView::SetWindowEnable()
{

	GetDlgItem(IDC_DRAIN_WASTE)->EnableWindow(TRUE);
	GetDlgItem(IDC_DRAIN_RINSE)->EnableWindow(TRUE);
	GetDlgItem(IDC_DRAIN_HGB)->EnableWindow(TRUE);
	GetDlgItem(IDC_DRAIN_RBC)->EnableWindow(TRUE);
	GetDlgItem(IDC_DRAIN_BASO)->EnableWindow(TRUE);

	GetDlgItem(IDC_DRAIN_LMNE)->EnableWindow(TRUE);
	GetDlgItem(IDC_DRAIN_ALL)->EnableWindow(TRUE);
	GetDlgItem(IDC_DRAIN_DILUENT_POT)->EnableWindow(TRUE);
	GetDlgItem(IDC_DRAIN_CTM)->EnableWindow(TRUE);
	GetDlgItem(IDC_DRAIN_PIPE)->EnableWindow(TRUE);
	GetDlgItem(IDC_DRAIN_ESCAPE)->EnableWindow(TRUE);
}
