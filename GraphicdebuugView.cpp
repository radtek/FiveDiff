// GraphicdebuugView.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "GraphicdebuugView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CGraphicdebuugView �Ի���

IMPLEMENT_DYNAMIC(CGraphicdebuugView, CDialogEx)

CGraphicdebuugView::CGraphicdebuugView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGraphicdebuugView::IDD, pParent)
{

}

CGraphicdebuugView::~CGraphicdebuugView()
{
}

void CGraphicdebuugView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGraphicdebuugView, CDialogEx)
END_MESSAGE_MAP()


// CGraphicdebuugView ��Ϣ�������
