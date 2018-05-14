// LogView.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "LogView.h"
//#include "Includes_app.h"

// CLogView

IMPLEMENT_DYNCREATE(CLogView, CBCGPChartExampleView)

CLogView::CLogView()
: CBCGPChartExampleView(CLogView::IDD), m_Logtype(0)
{

}

CLogView::~CLogView()
{
}

void CLogView::DoDataExchange(CDataExchange* pDX)
{
	CBCGPChartExampleView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_LogList);
	DDX_Radio(pDX, IDC_REAGENT_RADIO1, m_Logtype);
}

BEGIN_MESSAGE_MAP(CLogView, CFormView)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_REAGENT_RADIO1, &CLogView::OnBnClickedLogtypeRadio1)
	ON_BN_CLICKED(IDC_CALIBRATION_RADIO2, &CLogView::OnBnClickedLogtypeRadio1)
	ON_BN_CLICKED(IDC_USER_RADIO3, &CLogView::OnBnClickedLogtypeRadio1)
	ON_BN_CLICKED(IDC_DEVELOPMENT_RADIO4, &CLogView::OnBnClickedLogtypeRadio1)
	ON_BN_CLICKED(IDC_ERROR_RADIO5, &CLogView::OnBnClickedLogtypeRadio1)
	ON_BN_CLICKED(IDC_STARTUP_RADIO6, &CLogView::OnBnClickedLogtypeRadio1)
END_MESSAGE_MAP()


// CLogView ���

#ifdef _DEBUG
void CLogView::AssertValid() const
{
	CBCGPChartExampleView::AssertValid();
}

#ifndef _WIN32_WCE
void CLogView::Dump(CDumpContext& dc) const
{
	CBCGPChartExampleView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLogView ��Ϣ�������

void CLogView::OnInitialUpdate()
{
	CBCGPChartExampleView::OnInitialUpdate();

	// TODO:  �ڴ����ר�ô����/����û���
	InitLogForm();
}


BOOL CLogView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return CBCGPChartExampleView::OnEraseBkgnd(pDC);
}


BOOL CLogView::InitLogForm()
{
	CRect rect;

	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_LogList.GetClientRect(&rect);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_LogList.SetExtendedStyle(m_LogList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//m_worksheetList.SetItemColor(0, RGB(100, 125, 100), RGB(15, 235, 150));//�����ض�Item ���� ������ɫ
	m_LogList.SetRowHeigt(20);


	// ΪCRP�б���ͼ�ؼ��������
	m_LogList.InsertColumn(0, _T("����/ʱ��"), LVCFMT_CENTER, rect.Width() /6 , 0);
	m_LogList.InsertColumn(1, _T("������"), LVCFMT_CENTER, rect.Width() / 6, 1);
	m_LogList.InsertColumn(2, _T("����"), LVCFMT_CENTER, rect.Width() / 2, 2);
	m_LogList.InsertColumn(3, _T("����"), LVCFMT_CENTER, rect.Width() / 6, 3);


	// ��CRP�б���ͼ�ؼ��в����б���������б������ı�
	m_LogList.InsertItem(0, _T("04/11/2016 15:02:30"));
	m_LogList.SetItemText(0, 1, _T("Technican"));
	m_LogList.SetItemText(0, 2, _T("Modification: Forced WBC=128.78, RBC=154.13, HGB=42.37, HCT=174.16, PLT=192.12, RDW=0.35,LMNE=0.95 BY Technican"));
	m_LogList.SetItemText(0, 3, _T(""));
	m_LogList.InsertItem(1, _T("04/11/2016 15:02:30"));
	m_LogList.SetItemText(1, 1, _T("Technican"));
	m_LogList.SetItemText(1, 2, _T("Modification: Forced WBC=128.78, RBC=154.13, HGB=42.37, HCT=174.16, PLT=192.12, RDW=0.35,LMNE=0.95 BY Technican"));
	m_LogList.SetItemText(1, 3, _T(""));



	return TRUE;
}


void CLogView::OnBnClickedLogtypeRadio1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	switch(m_Logtype)
	{
	case 0:
		MessageBox(L"1");
		break;
	case 1:
		MessageBox(L"2");
		break;
	case 2:
		MessageBox(L"3");
		break;
	case 3:
		MessageBox(L"4");
		break;
	case 4:
		MessageBox(L"5");
		break;
	case 5:
		MessageBox(L"6");
		break;
	default: 
		break;
	
	}
}
