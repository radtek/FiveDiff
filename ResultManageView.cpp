// ResultManage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "ResultManageView.h"
//#include "afxdialogex.h"


// CResultManageView �Ի���

IMPLEMENT_DYNCREATE(CResultManageView, CBCGPChartExampleView)

CResultManageView::CResultManageView()
: CBCGPChartExampleView(CResultManageView::IDD)
{

}

CResultManageView::~CResultManageView()
{
}

void CResultManageView::DoDataExchange(CDataExchange* pDX)
{
	CBCGPChartExampleView::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_RESULT_TAB, m_ResultManageTab);
}


BEGIN_MESSAGE_MAP(CResultManageView, CBCGPChartExampleView)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

#ifdef _DEBUG
void CResultManageView::AssertValid() const
{
	CBCGPChartExampleView::AssertValid();
}

#ifndef _WIN32_WCE
void CResultManageView::Dump(CDumpContext& dc) const
{
	CBCGPChartExampleView::Dump(dc);
}
#endif
#endif //_DEBUG

// CResultManageView ��Ϣ�������


void CResultManageView::OnInitialUpdate()
{
	CBCGPChartExampleView::OnInitialUpdate();

	// TODO:  �ڴ����ר�ô����/����û���

	CRect rectTab;
	GetDlgItem(IDC_RESULT_TAB)->GetWindowRect(&rectTab);
	ScreenToClient(&rectTab);

	m_ResultManageTab.Create(CBCGPTabWnd::STYLE_3D, rectTab, this, 1, CBCGPTabWnd::LOCATION_TOP);
	CRect rc;
	m_ResultManageTab.GetClientRect(rc);
	m_ResultManageTab.SetResizeMode(CBCGPTabWnd::RESIZE_VERT);
	rc.top += 27;
	rc.bottom -= 5;
	rc.left += 5;
	rc.right -= 10;

	m_ResultManageTab.RemoveAllTabs();


	m_PatientResultPage.Create(IDD_PAITIENTRESULT, &m_ResultManageTab);
	m_ResultListPage.Create(IDD_RESULTLIST, &m_ResultManageTab);

	
	m_ResultManageTab.AddTab(&m_PatientResultPage, L"���˽��", 0);
	m_ResultManageTab.AddTab(&m_ResultListPage, L"ÿ�ս��", 1);
	


}


void CResultManageView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CBCGPChartExampleView::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
}


BOOL CResultManageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ����ר�ô����/����û���

	return CBCGPChartExampleView::PreCreateWindow(cs);
}

HBRUSH CResultManageView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CBCGPChartExampleView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_RESULT_TAB:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}