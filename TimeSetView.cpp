// TimeSetView.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "TimeSetView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CTimeSetView �Ի���

IMPLEMENT_DYNAMIC(CTimeSetView, CDialogEx)

CTimeSetView::CTimeSetView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTimeSetView::IDD, pParent)
{

}

CTimeSetView::~CTimeSetView()
{
}

void CTimeSetView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTimeSetView, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CTimeSetView ��Ϣ�������


void CTimeSetView::OnPaint()
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
