// DevelopmentSetView.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "DevelopmentSetView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CDevelopmentSetView �Ի���

IMPLEMENT_DYNAMIC(CDevelopmentSetView, CDialogEx)

CDevelopmentSetView::CDevelopmentSetView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDevelopmentSetView::IDD, pParent)
{

}

CDevelopmentSetView::~CDevelopmentSetView()
{
}

void CDevelopmentSetView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDevelopmentSetView, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDevelopmentSetView ��Ϣ�������


void CDevelopmentSetView::OnPaint()
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
