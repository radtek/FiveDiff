// QualityControlView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "QualityControlView.h"
#include "ControlChooese.h"


// CQualityControlView
//CQualityTestView	m_QualityTestPage;

IMPLEMENT_DYNCREATE(CQualityControlView, CBCGPChartExampleView)

CQualityControlChartView	m_QualityChartPage;
CQualityListView			m_QualityListPage;

CQcXChartView				m_QcXChartPage;
CQcXListView				m_QcXListPage;

CQcXrChartView			m_QcXrChartPage;
CQcXrListView				m_QcXrListPage;

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
	ON_BN_CLICKED(IDC_QUALITY_FILEINFO, &CQualityControlView::OnBnClickedQualityFileinfo)
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
	CRect rc;
	m_QualityTab.GetClientRect(rc);
	m_QualityTab.SetResizeMode(CBCGPTabWnd::RESIZE_VERT);
	rc.top += 27;
	rc.bottom -= 5;
	rc.left += 5;
	rc.right -= 10;

	if (0 == Controltype){			//LJ�ʿ�
		m_QualityTab.RemoveAllTabs();

		m_RadarPage.Create(IDD_RADARCHART, &m_QualityTab);
		m_QualityChartPage.Create(IDD_QUALITY_CONTROL_CHART, &m_QualityTab);
		m_QualityTargetPage.Create(IDD_QUALITY_TARGETVALUE, &m_QualityTab);
		m_QualityTestPage.Create(IDD_QUALITY_TESTVIEW, &m_QualityTab);
		m_QualityListPage.Create(IDD_QUALITY_LIST, &m_QualityTab);

		m_QualityTab.AddTab(&m_RadarPage, L"�״�ͼ", 0);
		m_QualityTab.AddTab(&m_QualityChartPage, L"�ʿ�ͼ", 1);
		m_QualityTab.AddTab(&m_QualityTargetPage, L"��ֵ", 2);
		m_QualityTab.AddTab(&m_QualityTestPage, L"�ʿؼ���", 3);
		m_QualityTab.AddTab(&m_QualityListPage, L"�ʿ��б�", 4);

	}
	else if (1 == Controltype){		//X�ʿ�
		m_QualityTab.RemoveAllTabs();

		m_RadarPage.Create(IDD_RADARCHART, &m_QualityTab);
		m_QcXChartPage.Create(IDD_QC_X_CHART, &m_QualityTab);
		m_QcXTargetPage.Create(IDD_QC_X_TARGETVALUE, &m_QualityTab);
		m_QcXTestPage.Create(IDD_QC_X_TESTVIEW, &m_QualityTab);
		m_QcXListPage.Create(IDD_QC_X_LIST, &m_QualityTab);

		m_QualityTab.AddTab(&m_RadarPage, L"�״�ͼ", 0);
		m_QualityTab.AddTab(&m_QcXChartPage, L"X�ʿ�ͼ", 1);
		m_QualityTab.AddTab(&m_QcXTargetPage, L"X�ʿر༭", 2);
		m_QualityTab.AddTab(&m_QcXTestPage, L"X�ʿؼ���", 3);
		m_QualityTab.AddTab(&m_QcXListPage, L"X�ʿ��б�", 4);
		
	}
	else if (2 == Controltype){	//XR�ʿ�ҳ����л�

		m_QualityTab.RemoveAllTabs();
		m_RadarPage.Create(IDD_RADARCHART, &m_QualityTab);
		m_QcXrEditPage.Create(IDD_QC_XR_EDIT, &m_QualityTab);
		m_QcXrTestPage.Create(IDD_QC_XR_TEST, &m_QualityTab);
		m_QcXrChartPage.Create(IDD_QC_XR_CHART, &m_QualityTab);
		m_QcXrListPage.Create(IDD_QC_XR_LIST, &m_QualityTab);

		m_QualityTab.AddTab(&m_RadarPage, L"�״�ͼ", 0);
		m_QualityTab.AddTab(&m_QcXrChartPage, L"Xr�ʿ�ͼ", 1);
		m_QualityTab.AddTab(&m_QcXrEditPage, L"Xr�ʿر༭", 2);
		m_QualityTab.AddTab(&m_QcXrTestPage, L"Xr�ʿز���", 3);
		m_QualityTab.AddTab(&m_QcXrListPage, L"Xr�ʿ��б�", 4);
	}




	//m_RadarPage.MoveWindow(&rc);
	//m_QualityChartPage.MoveWindow(&rc);
	//m_QualityTargetPage.MoveWindow(&rc);
	//m_QualityTestPage.MoveWindow(&rc);
	//m_QualityListPage.MoveWindow(&rc);
	//m_QcXTargetPage.MoveWindow(&rc);

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
	//MessageBox(L"open here!");
	m_ControlChoose.DoModal();

	return CBCGPChartExampleView::PreCreateWindow(cs);
}


void CQualityControlView::OnBnClickedQualityFileinfo()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//�ڴ˴����봰�ڸ��µĴ���
	CControlChooese m_controlChoose;
	m_controlChoose.DoModal();
	//OnInitialUpdate();
	//RedrawWindow();
	//if (m_RadarPage)
	//	m_RadarPage.UpdateView();
	//m_QualityTargetPage.UpdateView();	
	//m_QualityChartPage.UpdateView();
	//m_QualityTestPage.UpdateView();	
	//UpdateData(false);
	///////////���Դ���//////////
	CString str;
	str.Format(L"%d", Controltype);
	//MessageBox(str);
	if (0 == Controltype){			//LJ�ʿ�
		m_QualityTab.RemoveAllTabs();
		
		//MessageBox(L"22");
		m_RadarPage.Create(IDD_RADARCHART, &m_QualityTab);
		m_QualityChartPage.Create(IDD_QUALITY_CONTROL_CHART, &m_QualityTab);
		m_QualityTargetPage.Create(IDD_QUALITY_TARGETVALUE, &m_QualityTab);
		m_QualityTestPage.Create(IDD_QUALITY_TESTVIEW, &m_QualityTab);
		m_QualityListPage.Create(IDD_QUALITY_LIST, &m_QualityTab);

		m_QualityTab.AddTab(&m_RadarPage, L"�״�ͼ", 0);
		m_QualityTab.AddTab(&m_QualityChartPage, L"�ʿ�ͼ", 1);
		m_QualityTab.AddTab(&m_QualityTargetPage, L"��ֵ", 2);
		m_QualityTab.AddTab(&m_QualityTestPage, L"�ʿؼ���", 3);
		m_QualityTab.AddTab(&m_QualityListPage, L"�ʿ��б�", 4);

		//m_QualityTab.InsertTab(&m_QualityTargetPage, L"LJ�ʿر༭", 2);
		//m_QualityTab.AddTab(&m_QcXTargetPage, L"X�ʿر༭", 0);
	}
	else if (1 == Controltype){		//X�ʿ�
		m_QualityTab.RemoveAllTabs();

		m_RadarPage.Create(IDD_RADARCHART, &m_QualityTab);
		m_QcXChartPage.Create(IDD_QC_X_CHART, &m_QualityTab);
		m_QcXTargetPage.Create(IDD_QC_X_TARGETVALUE, &m_QualityTab);
		m_QcXTestPage.Create(IDD_QC_X_TESTVIEW, &m_QualityTab);
		m_QcXListPage.Create(IDD_QC_X_LIST, &m_QualityTab);
		
		m_QualityTab.AddTab(&m_RadarPage, L"�״�ͼ", 0);
		m_QualityTab.AddTab(&m_QcXChartPage, L"X�ʿ�ͼ", 1);
		m_QualityTab.AddTab(&m_QcXTargetPage, L"X�ʿر༭", 2);
		m_QualityTab.AddTab(&m_QcXTestPage, L"X�ʿؼ���", 3);
		m_QualityTab.AddTab(&m_QcXListPage, L"X�ʿ��б�",4);
		//MessageBox(L"22");
		//m_QualityTargetPage.CloseWindow();
		//m_QualityTab.InsertTab(&m_QcXTargetPage, L"X�ʿر༭", 2);
		//m_QualityTab.AddTab(&m_QcXTargetPage, L"X�ʿر༭", 0);
	}
	else if (2 == Controltype){	//XR�ʿ�ҳ����л�
	
		m_QualityTab.RemoveAllTabs();
		m_RadarPage.Create(IDD_RADARCHART, &m_QualityTab);
		m_QcXrEditPage.Create(IDD_QC_XR_EDIT, &m_QualityTab);
		m_QcXrTestPage.Create(IDD_QC_XR_TEST, &m_QualityTab);
		m_QcXrChartPage.Create(IDD_QC_XR_CHART, &m_QualityTab);
		m_QcXrListPage.Create(IDD_QC_XR_LIST, &m_QualityTab);

		m_QualityTab.AddTab(&m_RadarPage, L"�״�ͼ", 0);
		m_QualityTab.AddTab(&m_QcXrChartPage, L"Xr�ʿ�ͼ",1);
		m_QualityTab.AddTab(&m_QcXrEditPage, L"Xr�ʿر༭", 2);
		m_QualityTab.AddTab(&m_QcXrTestPage, L"Xr�ʿز���", 3);
		m_QualityTab.AddTab(&m_QcXrListPage, L"Xr�ʿ��б�",4);
	}

	/////////////////////////////

	return;

}



