// UploadSetView.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "UploadSetView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CUploadSetView �Ի���

IMPLEMENT_DYNAMIC(CUploadSetView, CDialogEx)

CUploadSetView::CUploadSetView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUploadSetView::IDD, pParent)
{

}

CUploadSetView::~CUploadSetView()
{
}

void CUploadSetView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUploadSetView, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CUploadSetView ��Ϣ�������


void CUploadSetView::OnPaint()
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
