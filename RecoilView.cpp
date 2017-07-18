// RecoilView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "RecoilView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CRecoilView �Ի���

IMPLEMENT_DYNAMIC(CRecoilView, CDialogEx)

CRecoilView::CRecoilView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRecoilView::IDD, pParent)
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

CRecoilView::~CRecoilView()
{
}

void CRecoilView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRecoilView, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDM_MAIN_HYDR_BACKFLUSH, &CRecoilView::OnBnClickedMainHydrBackflush)
	ON_WM_TIMER()
	ON_MESSAGE(WM_ACKSPI, &CRecoilView::OnAckspi)
END_MESSAGE_MAP()


// CRecoilView ��Ϣ�������


HBRUSH CRecoilView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
	//GetDlgItem(IDC_RECOIL)->SetWindowText(L"�Ƿ�ִ�з��壿");
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CRecoilView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect   rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));   //����Ϊ��ɫ����
	dc.Rectangle(40, 20, rect.right - 40, rect.bottom - 30);
}


void CRecoilView::OnBnClickedMainHydrBackflush()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	TRACE("IDM_MAIN_HYDR_BACKFLUSH---------#\n");
	key_status = FALSE;
	DSP_status = Busy;
	sdata_cmd[0] = SPI_CMD_BACKFLUSH;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD,0);
	if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
		MessageBox(L"����Ͳ��ɹ���", L"ERROR", MB_OKCANCEL);
	else{
	GetDlgItem(IDC_RECOIL)->SetWindowText(L"����ִ�з��壡");

		SetTimer(POLLTIME, SPI_POLL_TIME3000, 0);
	}
}


void CRecoilView::OnTimer(UINT_PTR nIDEvent)
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


afx_msg LRESULT CRecoilView::OnAckspi(WPARAM wParam, LPARAM lParam)
{
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
		GetDlgItem(IDC_RECOIL)->SetWindowText(L"����ִ����ɣ�");
		break;
	}
	
	return 0;
}
