// CleantankView.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "CleantankView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CCleantankView �Ի���

IMPLEMENT_DYNAMIC(CCleantankView, CDialogEx)

CCleantankView::CCleantankView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCleantankView::IDD, pParent)
{

}

CCleantankView::~CCleantankView()
{
}

void CCleantankView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCleantankView, CDialogEx)
END_MESSAGE_MAP()


// CCleantankView ��Ϣ�������
