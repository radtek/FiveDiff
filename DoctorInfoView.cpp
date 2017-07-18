// DoctorInfoView.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "DoctorInfoView.h"
//#include "Includes_app.h"

// CDoctorInfoView

IMPLEMENT_DYNCREATE(CDoctorInfoView, CBCGPChartExampleView)

CDoctorInfoView::CDoctorInfoView()
: CBCGPChartExampleView(CDoctorInfoView::IDD)
{


}

CDoctorInfoView::~CDoctorInfoView()
{

}

void CDoctorInfoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST1, m_DoctorInfoList);
}

BEGIN_MESSAGE_MAP(CDoctorInfoView, CFormView)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CDoctorInfoView ���

#ifdef _DEBUG
void CDoctorInfoView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDoctorInfoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDoctorInfoView ��Ϣ�������
BOOL CDoctorInfoView::InitDoctorInfoForm()
{
	CRect rect;

	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_DoctorInfoList.GetClientRect(&rect);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_DoctorInfoList.SetExtendedStyle(m_DoctorInfoList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//m_worksheetList.SetItemColor(0, RGB(100, 125, 100), RGB(15, 235, 150));//�����ض�Item ���� ������ɫ
	m_DoctorInfoList.SetRowHeigt(20);


	// ΪCRP�б���ͼ�ؼ��������
	m_DoctorInfoList.InsertColumn(0, _T("NO."), LVCFMT_CENTER, rect.Width() / 4, 0);
	m_DoctorInfoList.InsertColumn(1, _T("ҽʦ"), LVCFMT_CENTER, rect.Width() / 4, 1);
	m_DoctorInfoList.InsertColumn(2, _T("��ע"), LVCFMT_CENTER, rect.Width() /2 , 2);

	// ��CRP�б���ͼ�ؼ��в����б���������б������ı�
	m_DoctorInfoList.InsertItem(0, _T("123456"));
	m_DoctorInfoList.SetItemText(0, 1, _T("NANCY"));
	m_DoctorInfoList.SetItemText(0, 2, _T("��"));


	return TRUE;
}

void CDoctorInfoView::OnInitialUpdate()
{
	CBCGPChartExampleView::OnInitialUpdate();

	// TODO:  �ڴ����ר�ô����/����û���
	InitDoctorInfoForm();
}


BOOL CDoctorInfoView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return CBCGPChartExampleView::OnEraseBkgnd(pDC);
}
