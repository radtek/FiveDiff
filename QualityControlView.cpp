// QualityControlView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "QualityControlView.h"
#include "ControlChooese.h"


// CQualityControlView
CQualityTestView	m_QualityTestPage;

IMPLEMENT_DYNCREATE(CQualityControlView, CBCGPChartExampleView)

CQualityControlView::CQualityControlView()
: CBCGPChartExampleView(CQualityControlView::IDD)
{

}

CQualityControlView::~CQualityControlView()
{

}

void CQualityControlView::DoDataExchange(CDataExchange* pDX)
{
	CBCGPChartExampleView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CQualityControlView, CBCGPChartExampleView)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CQualityControlView ���

#ifdef _DEBUG
void CQualityControlView::AssertValid() const
{
	CBCGPChartExampleView::AssertValid();
}

#ifndef _WIN32_WCE
void CQualityControlView::Dump(CDumpContext& dc) const
{
	CBCGPChartExampleView::Dump(dc);
}
#endif
#endif //_DEBUG


// CQualityControlView ��Ϣ�������


void CQualityControlView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CBCGPChartExampleView::OnPaint()
}


void CQualityControlView::OnInitialUpdate()
{
	CBCGPChartExampleView::OnInitialUpdate();

	CRect rectTab;
	GetDlgItem(IDC_QUALITYCONTROL_TAB)->GetWindowRect(&rectTab);
	ScreenToClient(&rectTab);

	m_QualityTab.Create(CBCGPTabWnd::STYLE_3D, rectTab, this, 1, CBCGPTabWnd::LOCATION_TOP);


	m_RadarPage.Create(IDD_RADARCHART, &m_QualityTab);
	m_QualityChartPage.Create(IDD_QUALITY_CONTROL_CHART, &m_QualityTab);
	m_QualityTargetPage.Create(IDD_QUALITY_TARGETVALUE, &m_QualityTab);
	m_QualityTestPage.Create(IDD_QUALITY_TESTVIEW, &m_QualityTab);

	m_QualityTab.AddTab(&m_RadarPage, L"�״�ͼ", 0);
	m_QualityTab.AddTab(&m_QualityChartPage, L"�ʿ�ͼ", 1);
	m_QualityTab.AddTab(&m_QualityTargetPage, L"��ֵ", 2);
	m_QualityTab.AddTab(&m_QualityTestPage, L"�ʿؼ���", 3);

	CRect rc;
	m_QualityTab.GetClientRect(rc);
	m_QualityTab.SetResizeMode(CBCGPTabWnd::RESIZE_VERT);
	rc.top += 27;
	rc.bottom -= 5;
	rc.left += 5;
	rc.right -= 10;

	m_RadarPage.MoveWindow(&rc);
	m_QualityChartPage.MoveWindow(&rc);
	m_QualityTargetPage.MoveWindow(&rc);
	m_QualityTestPage.MoveWindow(&rc);


	//m_QualityTab.InsertItem(0,_T("�״�ͼ"));
	//m_QualityTab.InsertItem(1,_T("�ʿ�ͼ"));
	//m_QualityTab.InsertItem(2,_T("��ֵ"));
	//m_QualityTab.InsertItem(3,_T("�ʿؼ���"));
	//m_QualityTab.InsertItem(3,_T("����2"));
	//���������Ի���
	//m_RadarPage.Create(IDD_RADARCHART, &m_QualityTab);
	//m_QualityChartPage.Create(IDD_QUALITY_CONTROL_CHART, &m_QualityTab);
	//m_QualityTargetPage.Create(IDD_QUALITY_TARGETVALUE, &m_QualityTab);
	//m_QualityTestPage.Create(IDD_QUALITY_TESTVIEW, &m_QualityTab);
	//�趨��Tab����ʾ�ķ�Χ
	//CRect rc;
	//m_QualityTab.GetClientRect(rc);
	//rc.top += 20;
	//rc.bottom -= 0;
	//rc.left += 0;
	//rc.right -= 0;
	//m_RadarPage.MoveWindow(&rc);
	//m_QualityChartPage.MoveWindow(&rc);
	//m_QualityTargetPage.MoveWindow(&rc);
	//m_QualityTestPage.MoveWindow(&rc);

	//�ѶԻ������ָ�뱣������
	//pDialog[0] = &m_RadarPage;
	//pDialog[1] = &m_QualityChartPage;
	//pDialog[2] = &m_QualityTargetPage;
	//pDialog[3] = &m_QualityTestPage;
	//��ʾ��ʼҳ��
	//pDialog[0]->ShowWindow(SW_SHOW);
	//pDialog[1]->ShowWindow(SW_HIDE);
	//pDialog[2]->ShowWindow(SW_HIDE);
	//pDialog[3]->ShowWindow(SW_HIDE);

	// TODO:  �ڴ����ר�ô����/����û���
}

HBRUSH CQualityControlView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CBCGPChartExampleView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_QUALITY_TAB:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CQualityControlView::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//�ѵ�ǰ��ҳ����������
	//pDialog[m_CurSelTab]->ShowWindow(SW_HIDE);
	//�õ��µ�ҳ������
	//m_CurSelTab = m_QualityTab.GetCurSel();
	//���µ�ҳ����ʾ����
	//pDialog[m_CurSelTab]->ShowWindow(SW_SHOW);
	*pResult = 0;
}



BOOL CQualityControlView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ����ר�ô����/����û���

	//CLoginDlg	m_LoginDlg;
	//if (m_LoginDlg.DoModal() != IDOK)
	//{
	//return FALSE;
	//}
	CControlChooese m_ControlChoose;
	m_ControlChoose.DoModal();

	return CBCGPChartExampleView::PreCreateWindow(cs);
}
