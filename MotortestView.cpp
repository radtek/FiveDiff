// MotortestView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "MotortestView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CMotortestView �Ի���

IMPLEMENT_DYNAMIC(CMotortestView, CDialogEx)

CMotortestView::CMotortestView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMotortestView::IDD, pParent)
{

}

CMotortestView::~CMotortestView()
{
}

void CMotortestView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMotortestView, CDialogEx)
	ON_WM_TIMER()
	ON_MESSAGE(WM_ACKSPI, &CMotortestView::OnAckspi)
	ON_BN_CLICKED(IDC_CHMOTORS_SAMNDLE, &CMotortestView::OnChmotorsSamndle)
	ON_BN_CLICKED(IDC_CHMOTORS_CAR, &CMotortestView::OnChmotorsCar)
	ON_BN_CLICKED(IDC_CHMOTORS_SAMSYR, &CMotortestView::OnChmotorsSamsyr)
	ON_BN_CLICKED(IDC_CHMOTORS_DRAINSYR, &CMotortestView::OnChmotorsDrainsyr)
	ON_BN_CLICKED(IDC_CHMOTORS_COUNTSYR, &CMotortestView::OnChmotorsCountsyr)
	ON_BN_CLICKED(IDC_CHMOTORS_CYTOSYR, &CMotortestView::OnChmotorsCytosyr)
	ON_BN_CLICKED(IDC_CHMOTORS_DILUSYR, &CMotortestView::OnChmotorsDilusyr)
	ON_BN_CLICKED(IDC_CHMOTORS_PUNCTURE, &CMotortestView::OnChmotorsPuncture)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CMotortestView ��Ϣ�������


BOOL CMotortestView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CMotortestView::CheckMoters(const char* Mess, uchar CMD)
{
	TRACE(Mess);
	key_status = FALSE;
	DSP_status = Busy;
	sdata_cmd[0] = CMD;
	if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD)==-1)
	{
		//GetDlgItem(IDC_CHMOTORS_SAMNDLE)->EnableWindow(TRUE);
		//GetDlgItem(IDC_CHMOTORS_CAR)->EnableWindow(TRUE);
		//GetDlgItem(IDC_CHMOTORS_SAMSYR)->EnableWindow(TRUE);
		//GetDlgItem(IDC_CHMOTORS_DRAINSYR)->EnableWindow(TRUE);
		//GetDlgItem(IDC_CHMOTORS_COUNTSYR)->EnableWindow(TRUE);
		//GetDlgItem(IDC_CHMOTORS_CYTOSYR)->EnableWindow(TRUE);
		//GetDlgItem(IDC_CHMOTORS_DILUSYR)->EnableWindow(TRUE);
		//GetDlgItem(IDC_CHMOTORS_PUNCTURE)->EnableWindow(TRUE);
		return;
	}
	else
	{
		GetDlgItem(IDC_CHMOTORS_SAMNDLE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHMOTORS_CAR)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHMOTORS_SAMSYR)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHMOTORS_DRAINSYR)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHMOTORS_COUNTSYR)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHMOTORS_CYTOSYR)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHMOTORS_DILUSYR)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHMOTORS_PUNCTURE)->EnableWindow(FALSE);
		SetTimer(POLLTIME, 1000, 0);

	}
}



void CMotortestView::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���

	CDialogEx::OnOK();
}


void CMotortestView::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���

	CDialogEx::OnCancel();
}


void CMotortestView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case POLLTIME:
		TRACE("MSG_TIMER:POLLTIME is due -------------#\n");
		sdata_cmd[0] = SPI_CMD_REQDSP_STATUS;
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		PC_RECEIVE_FRAME(rdata_state, SPI_TYPE_STATE);
		SendMessage(WM_ACKSPI, rdata_state[0], 0);
	default:
		break;
	
	}
	CDialogEx::OnTimer(nIDEvent);
}


afx_msg LRESULT CMotortestView::OnAckspi(WPARAM wParam, LPARAM lParam)
{

	switch (wParam)
	{
		//��������
	case SPI_STATE_INFO_END:
		KillTimer(POLLTIME);
		DSP_status = Free;
		key_status = TRUE;
		GetDlgItem(IDC_CHMOTORS_SAMNDLE)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHMOTORS_CAR)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHMOTORS_SAMSYR)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHMOTORS_DRAINSYR)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHMOTORS_COUNTSYR)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHMOTORS_CYTOSYR)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHMOTORS_DILUSYR)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHMOTORS_PUNCTURE)->EnableWindow(TRUE);
		break;
	default:
		break;
	}
	return 0;
}


void CMotortestView::OnChmotorsSamndle()//Y���
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CheckMoters("Test YM---------#\n", SPI_CMD_TEST_YM);
	//GetDlgItem(IDC_CHMOTORS_SAMNDLE)->EnableWindow(FALSE);
}


void CMotortestView::OnChmotorsCar()//XM���
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CheckMoters("Test XM---------#\n", SPI_CMD_TEST_XM);
	//GetDlgItem(IDC_CHMOTORS_CAR)->EnableWindow(FALSE);
}


void CMotortestView::OnChmotorsSamsyr()//��Ʒע����
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CheckMoters("Test SM---------#\n", SPI_CMD_TEST_SM);
	//GetDlgItem(IDC_CHMOTORS_SAMSYR)->EnableWindow(FALSE);
}


void CMotortestView::OnChmotorsDrainsyr()//��Һע����
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CheckMoters("Test DRM---------#\n", SPI_CMD_TEST_DRM);
	//GetDlgItem(IDC_CHMOTORS_DRAINSYR)->EnableWindow(FALSE);
}


void CMotortestView::OnChmotorsCountsyr()//����ע����
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CheckMoters("Test CTM---------#\n", SPI_CMD_TEST_CTM);
	//GetDlgItem(IDC_CHMOTORS_COUNTSYR)->EnableWindow(FALSE);
}


void CMotortestView::OnChmotorsCytosyr()//����ע����
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CheckMoters("Test CYM---------#\n", SPI_CMD_TEST_CYM);
	//GetDlgItem(IDC_CHMOTORS_CYTOSYR)->EnableWindow(FALSE);
}


void CMotortestView::OnChmotorsDilusyr()//�Լ�ע����
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CheckMoters("Test DIM---------#\n", SPI_CMD_TEST_DIM);
	//GetDlgItem(IDC_CHMOTORS_DILUSYR)->EnableWindow(FALSE);
}


void CMotortestView::OnChmotorsPuncture()//����
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CheckMoters("Test PUNCTURE---------#\n", SPI_CMD_TEST_PUNCTURE);
	//GetDlgItem(IDC_CHMOTORS_PUNCTURE)->EnableWindow(FALSE);
}



HBRUSH CMotortestView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CMotortestView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect   rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255,255));   //����Ϊ��ɫ����
}
