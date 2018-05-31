// AutocleanView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "AutocleanView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CAutocleanView �Ի���

IMPLEMENT_DYNAMIC(CAutocleanView, CDialogEx)

CAutocleanView::CAutocleanView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAutocleanView::IDD, pParent)
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

CAutocleanView::~CAutocleanView()
{
}

void CAutocleanView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAutocleanView, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDM_MIAN_HYDR_AUTOCLEAN, &CAutocleanView::OnBnClickedMianHydrAutoclean)
	ON_WM_TIMER()
	ON_MESSAGE(WM_ACKSPI, &CAutocleanView::OnAckspi)
END_MESSAGE_MAP()


// CAutocleanView ��Ϣ�������


HBRUSH CAutocleanView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
	return hbr;
}


void CAutocleanView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect   rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));   //����Ϊ��ɫ����
	dc.Rectangle(40, 20, rect.right - 40, rect.bottom - 30);
}


void CAutocleanView::OnBnClickedMianHydrAutoclean()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (DSP_status == Free)
	{
	//////////////////////////////////////
		if (timeFrKd >= 60 * systemcfg.sleeptime)
		{
			timeFrKd = 0;
			
			fprintf(stderr, "..........active in the function activatescreen..............\n");
			sdata_cmd[0] = SPI_CMD_STANDBY_OVER;
			PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		}

	//////////////////////////////////////
		fprintf(stderr, "..........active in the function autoclean_mainwnd..............\n");
		NumFromBoot = 0;
		TRACE("IDM_MIAN_HYDR_AUTOCLEAN---------#\n");
		key_status = FALSE;
		
		sdata_cmd[0] = SPI_CMD_AUTOCLEAN;
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD, 0);
		if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			MessageBox(L"����Ͳ��ɹ���", L"ERROR", MB_OKCANCEL);
		else{
			GetDlgItem(IDC_AUTOCLEAN)->SetWindowText(L"����ִ���Զ���ϴ��");
			DSP_status = Busy;
			SetTimer(POLLTIME, SPI_POLL_TIME3000, 0);
			statusShowMess = 4;
		}
	}
}



void CAutocleanView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case POLLTIME:
		//DEBUG_PRINT1("MSG_TIMER:POLLTIME is due -------------#\n");
		sdata_cmd[0] = SPI_CMD_REQDSP_STATUS;
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		PC_RECEIVE_FRAME(rdata_state, SPI_TYPE_STATE);
		SendMessage(WM_ACKSPI, rdata_state[0], 0);
		break;
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


afx_msg LRESULT CAutocleanView::OnAckspi(WPARAM wParam, LPARAM lParam)
{
	//����SPI��Ϣ
	switch (wParam)
	{
	case SPI_STATE_INFO_END:
		TRACE(_T("SPI_STATE_INFO_END"));
		KillTimer(POLLTIME);
		DSP_status = Free;
		statusShowMess = 0;
		//InvalidateRect(hDlg, &STATUS, TRUE);
		key_status = TRUE;
		//Standby_EN = TRUE;
		GetDlgItem(IDC_AUTOCLEAN)->SetWindowText(L"�Զ���ϴ��ɣ�");
		break;
	}
	
	
	////////////////////////
	//�Զ���ϴ��ɵĶ���
	////////////////////////
	
	return 0;
}
