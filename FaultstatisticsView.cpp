// FaultstatisticsView.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "FaultstatisticsView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CFaultstatisticsView �Ի���

IMPLEMENT_DYNAMIC(CFaultstatisticsView, CDialogEx)

CFaultstatisticsView::CFaultstatisticsView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFaultstatisticsView::IDD, pParent)
{

}

CFaultstatisticsView::~CFaultstatisticsView()
{
}

void CFaultstatisticsView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFaultstatisticsView, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_ALERT_XMEMPTY, &CFaultstatisticsView::OnBnClickedAlertXmempty)
	ON_BN_CLICKED(IDC_ALERT_YMEMPTY, &CFaultstatisticsView::OnBnClickedAlertYmempty)
	ON_BN_CLICKED(IDC_ALERT_SMEMPTY, &CFaultstatisticsView::OnBnClickedAlertSmempty)
	ON_BN_CLICKED(IDC_ALERT_DIMEMPTY, &CFaultstatisticsView::OnBnClickedAlertDimempty)
	ON_BN_CLICKED(IDC_ALERT_DRMEMPTY, &CFaultstatisticsView::OnBnClickedAlertDrmempty)
	ON_BN_CLICKED(IDC_ALERT_CTMEMPTY, &CFaultstatisticsView::OnBnClickedAlertCtmempty)
	ON_BN_CLICKED(IDC_ALERT_CYMEMPTY, &CFaultstatisticsView::OnBnClickedAlertCymempty)
	ON_BN_CLICKED(IDC_ALERT_WBCEMPTY, &CFaultstatisticsView::OnBnClickedAlertWbcempty)
	ON_BN_CLICKED(IDC_ALERT_RBCEMPTY, &CFaultstatisticsView::OnBnClickedAlertRbcempty)
	ON_BN_CLICKED(IDC_ALERT_WLEMPTY, &CFaultstatisticsView::OnBnClickedAlertWlempty)
	ON_BN_CLICKED(IDC_ALERT_DILTMEMPTY, &CFaultstatisticsView::OnBnClickedAlertDiltmempty)
	ON_BN_CLICKED(IDC_ALERT_WLFEMPTY, &CFaultstatisticsView::OnBnClickedAlertWlfempty)
	ON_BN_CLICKED(IDC_ALERT_TNEMPTY, &CFaultstatisticsView::OnBnClickedAlertTnempty)
	ON_BN_CLICKED(IDC_ALERT_ALLMEMPTY, &CFaultstatisticsView::OnBnClickedAlertAllmempty)
END_MESSAGE_MAP()


// CFaultstatisticsView ��Ϣ�������


void CFaultstatisticsView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	/*@TG
#3073*/
	int i=0;
	CString str;
	CRect   rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));   //����Ϊ��ɫ����
	dc.Rectangle(20, 20, rect.right/2-5 , rect.bottom - 50);
	dc.Rectangle(rect.right/2+5, 20, rect.right - 20, rect.bottom - 50);
	for (i=1;i<13;i++)
	{
		str.Format(L"%d",logfile.alertnum[i]);
		GetDlgItem(IDC_ALERT_XM+i-1)->SetWindowText((LPCTSTR)str);	
	}
	str.Format(L"%d",logfile.totaltimesoftest);
		GetDlgItem(IDC_ALERT_TN)->SetWindowText((LPCTSTR)str);	
		// TODO: �ڴ˴������Ϣ����������
		// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


HBRUSH CFaultstatisticsView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
		//pDC->SelectObject(&m_Font);
		pDC->SetBkColor(RGB(255, 255, 255));//���ֱ���ɫ
		HBRUSH b = CreateSolidBrush(RGB(255, 255, 255));//�ؼ�����ɫ   
		return b;
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CFaultstatisticsView::OnBnClickedAlertXmempty()
{
	logfile.alertnum[1] = 0;
	SendMessage(WM_PAINT);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CFaultstatisticsView::OnBnClickedAlertYmempty()
{
	logfile.alertnum[2] = 0;
	SendMessage(WM_PAINT);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CFaultstatisticsView::OnBnClickedAlertSmempty()
{
	logfile.alertnum[3] = 0;
	SendMessage(WM_PAINT);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CFaultstatisticsView::OnBnClickedAlertDimempty()
{
	logfile.alertnum[4] = 0;
	SendMessage(WM_PAINT);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CFaultstatisticsView::OnBnClickedAlertDrmempty()
{
	logfile.alertnum[5] = 0;
	SendMessage(WM_PAINT);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CFaultstatisticsView::OnBnClickedAlertCtmempty()
{
	logfile.alertnum[6] = 0;
	SendMessage(WM_PAINT);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CFaultstatisticsView::OnBnClickedAlertCymempty()
{
	logfile.alertnum[7] = 0;
	SendMessage(WM_PAINT);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CFaultstatisticsView::OnBnClickedAlertWbcempty()
{
	logfile.alertnum[8] = 0;
	SendMessage(WM_PAINT);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CFaultstatisticsView::OnBnClickedAlertRbcempty()
{
	logfile.alertnum[9] = 0;
	SendMessage(WM_PAINT);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CFaultstatisticsView::OnBnClickedAlertWlempty()
{
	logfile.alertnum[10] = 0;
	SendMessage(WM_PAINT);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CFaultstatisticsView::OnBnClickedAlertDiltmempty()
{
	logfile.alertnum[11] = 0;
	SendMessage(WM_PAINT);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CFaultstatisticsView::OnBnClickedAlertWlfempty()
{
	logfile.alertnum[12] = 0;
	SendMessage(WM_PAINT);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CFaultstatisticsView::OnBnClickedAlertTnempty()
{
	logfile.totaltimesoftest = 0;
	SendMessage(WM_PAINT);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CFaultstatisticsView::OnBnClickedAlertAllmempty()
{
	int i = 0;
	for(i=1;i<13;i++)
		logfile.alertnum[i] = 0;
	logfile.totaltimesoftest = 0;
	SendMessage(WM_PAINT);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
