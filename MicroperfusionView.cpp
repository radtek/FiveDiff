// MicroperfusionView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "MicroperfusionView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CMicroperfusionView �Ի���

IMPLEMENT_DYNAMIC(CMicroperfusionView, CDialogEx)

CMicroperfusionView::CMicroperfusionView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMicroperfusionView::IDD, pParent)
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

CMicroperfusionView::~CMicroperfusionView()
{
}

void CMicroperfusionView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMicroperfusionView, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDM_MAIN_HYDR_MINIPRIME, &CMicroperfusionView::OnBnClickedMainHydrMiniprime)
	ON_WM_TIMER()
	ON_MESSAGE(WM_ACKSPI, &CMicroperfusionView::OnAckspi)
END_MESSAGE_MAP()


// CMicroperfusionView ��Ϣ�������


HBRUSH CMicroperfusionView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void CMicroperfusionView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect   rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));   //����Ϊ��ɫ����
	dc.Rectangle(40, 20, rect.right - 40, rect.bottom - 30);
}


void CMicroperfusionView::OnBnClickedMainHydrMiniprime()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	TRACE("IDM_MAIN_HYDR_MINIPRIME---------#\n");
	key_status = FALSE;
	DSP_status = Busy;
	sdata_cmd[0] = SPI_CMD_MINIPRIME;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
		MessageBox(L"����Ͳ��ɹ���", L"ERROR", MB_OKCANCEL);
	else{
	GetDlgItem(IDC_MICROPERFUSION)->SetWindowText(L"����ִ��΢��ע��");
		SetTimer(POLLTIME, SPI_POLL_TIME3000, 0);
	}
}


void CMicroperfusionView::OnTimer(UINT_PTR nIDEvent)
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


afx_msg LRESULT CMicroperfusionView::OnAckspi(WPARAM wParam, LPARAM lParam)
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
		GetDlgItem(IDC_MICROPERFUSION)->SetWindowText(L"ִ��΢��ע��ɣ�");
		break;
	}
	//�����ɣ�
	//
	
	return 0;
}
