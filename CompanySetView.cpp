// CompanySetView.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "CompanySetView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CCompanySetView �Ի���

IMPLEMENT_DYNAMIC(CCompanySetView, CDialogEx)

CCompanySetView::CCompanySetView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCompanySetView::IDD, pParent)
{

}

CCompanySetView::~CCompanySetView()
{
}

void CCompanySetView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCompanySetView, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CCompanySetView ��Ϣ�������


void CCompanySetView::OnPaint()
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
