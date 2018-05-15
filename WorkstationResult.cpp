// WorkstationResult.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "WorkstationResult.h"
#include "afxdialogex.h"


// CWorkstationResult �Ի���

IMPLEMENT_DYNAMIC(CWorkstationResult, CDialogEx)

CWorkstationResult::CWorkstationResult(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWorkstationResult::IDD, pParent)
{

}

CWorkstationResult::~CWorkstationResult()
{
}

void CWorkstationResult::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WORKSTATION_RESULTLIST, m_resultlist);
}


BEGIN_MESSAGE_MAP(CWorkstationResult, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CWorkstationResult ��Ϣ�������


HBRUSH CWorkstationResult::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


int CWorkstationResult::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}


void CWorkstationResult::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	dc.FillPath();
}


void CWorkstationResult::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	// TODO:  �ڴ˴������Ϣ����������
	if (nType == 1) return;//��С����ʲô������  
	// TODO: Add your message handler code here  
	CWnd *pWnd;

	pWnd = GetDlgItem(IDC_WORKSTATION_RESULTLIST);
	ChangeSize(pWnd, cx, cy);
	GetClientRect(&m_rect);// ���仯��ĶԻ����С��Ϊ�ɴ�С 
}

BOOL CWorkstationResult::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void CWorkstationResult::ChangeSize(CWnd *pWnd, int cx, int cy)
{
	if (pWnd)  //�ж��Ƿ�Ϊ�գ���Ϊ�Ի��򴴽�ʱ����ô˺���������ʱ�ؼ���δ����	
	{
		CRect rect;   //��ȡ�ؼ��仯ǰ�Ĵ�С  
		pWnd->GetWindowRect(&rect);
		ScreenToClient(&rect);//���ؼ���Сת��Ϊ�ڶԻ����е���������

		//    cx/m_rect.Width()Ϊ�Ի����ں���ı仯����
		rect.left = rect.left*cx / m_rect.Width();//�����ؼ���С
		rect.right = rect.right*cx / m_rect.Width();
		rect.top = rect.top*cy / m_rect.Height();
		rect.bottom = rect.bottom*cy / m_rect.Height();
		pWnd->MoveWindow(rect);//���ÿؼ���С
	}
}
