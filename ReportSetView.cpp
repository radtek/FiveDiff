// ReportSetView.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "ReportSetView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CReportSetView �Ի���

IMPLEMENT_DYNAMIC(CReportSetView, CDialogEx)

CReportSetView::CReportSetView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CReportSetView::IDD, pParent)
{

}

CReportSetView::~CReportSetView()
{
}

void CReportSetView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CReportSetView, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CReportSetView ��Ϣ�������


void CReportSetView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	dc.FillPath();

	CDialogEx::OnPaint();
}
