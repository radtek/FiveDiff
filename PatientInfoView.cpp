// PatientInfoView.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "PatientInfoView.h"
//#include "Includes_app.h"

// CPatientInfoView

IMPLEMENT_DYNCREATE(CPatientInfoView, CBCGPChartExampleView)

CPatientInfoView::CPatientInfoView()
: CBCGPChartExampleView(CPatientInfoView::IDD)
{

}

CPatientInfoView::~CPatientInfoView()
{
}

void CPatientInfoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, m_PatientInfoList);
}

BEGIN_MESSAGE_MAP(CPatientInfoView, CFormView)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CPatientInfoView ���

#ifdef _DEBUG
void CPatientInfoView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPatientInfoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPatientInfoView ��Ϣ�������


BOOL CPatientInfoView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return CBCGPChartExampleView::OnEraseBkgnd(pDC);
}


void CPatientInfoView::OnInitialUpdate()
{
	CBCGPChartExampleView::OnInitialUpdate();

	// TODO:  �ڴ����ר�ô����/����û���
	InitPaitientInfoForm();
}



BOOL CPatientInfoView::InitPaitientInfoForm()
{
	CRect rect;

	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_PatientInfoList.GetClientRect(&rect);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_PatientInfoList.SetExtendedStyle(m_PatientInfoList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//m_worksheetList.SetItemColor(0, RGB(100, 125, 100), RGB(15, 235, 150));//�����ض�Item ���� ������ɫ
	m_PatientInfoList.SetRowHeigt(20);


	// ΪCRP�б���ͼ�ؼ��������
	m_PatientInfoList.InsertColumn(0, _T("����ID��"), LVCFMT_CENTER, rect.Width() / 8, 0);
	m_PatientInfoList.InsertColumn(1, _T("����"), LVCFMT_CENTER, rect.Width() / 8, 1);
	m_PatientInfoList.InsertColumn(2, _T("����"), LVCFMT_CENTER, rect.Width() / 8, 2);
	m_PatientInfoList.InsertColumn(3, _T("�Ա�"), LVCFMT_CENTER, rect.Width() / 8, 3);
	m_PatientInfoList.InsertColumn(4, _T("��������"), LVCFMT_CENTER, rect.Width() / 8, 4);
	m_PatientInfoList.InsertColumn(5, _T("����"), LVCFMT_CENTER, rect.Width() / 8, 5);
	m_PatientInfoList.InsertColumn(6, _T("ҽʦ"), LVCFMT_CENTER, rect.Width() / 8, 6);
	m_PatientInfoList.InsertColumn(7, _T("��������"), LVCFMT_CENTER, rect.Width() / 8, 6);

	// ��CRP�б���ͼ�ؼ��в����б���������б������ı�
	m_PatientInfoList.InsertItem(0, _T("123456"));
	m_PatientInfoList.SetItemText(0, 1, _T("NANCY"));
	m_PatientInfoList.SetItemText(0, 2, _T("HELLEN"));
	m_PatientInfoList.SetItemText(0, 3, _T("Ů"));
	m_PatientInfoList.SetItemText(0, 4, _T("1991/01/1"));
	m_PatientInfoList.SetItemText(0, 5, _T("1"));
	m_PatientInfoList.SetItemText(0, 7, _T("HPC test"));

	return TRUE;
}
