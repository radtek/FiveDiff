// WorkSheetView.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "WorkSheetView.h"
//#include "Includes_app.h"

// CWorkSheetView

IMPLEMENT_DYNCREATE(CWorkSheetView, CBCGPChartExampleView)

CWorkSheetView::CWorkSheetView()
: CBCGPChartExampleView(CWorkSheetView::IDD)
{

}

CWorkSheetView::~CWorkSheetView()
{

}

void CWorkSheetView::DoDataExchange(CDataExchange* pDX)
{
	CBCGPChartExampleView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WORK_LIST, m_worksheetList);
}


BEGIN_MESSAGE_MAP(CWorkSheetView, CFormView)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CWorkSheetView ���

#ifdef _DEBUG
void CWorkSheetView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CWorkSheetView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG



// CWorkSheetView ��Ϣ�������


void CWorkSheetView::OnInitialUpdate()
{
	CBCGPChartExampleView::OnInitialUpdate();

	// TODO:  �ڴ����ר�ô����/����û���
	InitWorksheetForm();

}



BOOL CWorkSheetView::InitWorksheetForm()
{
	CRect rect;

	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_worksheetList.GetClientRect(&rect);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_worksheetList.SetExtendedStyle(m_worksheetList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_worksheetList.SetItemColor(0, RGB(100, 125, 100), RGB(15, 235, 150));//�����ض�Item ���� ������ɫ
	m_worksheetList.SetRowHeigt(20);


	// ΪCRP�б���ͼ�ؼ��������
	m_worksheetList.InsertColumn(0, _T("������"), LVCFMT_CENTER, rect.Width() / 7, 0);
	m_worksheetList.InsertColumn(1, _T("����ID"), LVCFMT_CENTER, rect.Width() / 7, 1);
	m_worksheetList.InsertColumn(2, _T("����ģʽ"), LVCFMT_CENTER, rect.Width() / 7, 2);
	m_worksheetList.InsertColumn(3, _T("�Թܼ�"), LVCFMT_CENTER, rect.Width() / 7, 3);
	m_worksheetList.InsertColumn(4, _T("�Թ�"), LVCFMT_CENTER, rect.Width() / 7, 4);
	m_worksheetList.InsertColumn(5, _T("״̬"), LVCFMT_CENTER, rect.Width() / 7, 5);
	m_worksheetList.InsertColumn(6, _T("����"), LVCFMT_CENTER, rect.Width() / 7, 6);

	// ��CRP�б���ͼ�ؼ��в����б���������б������ı�
	m_worksheetList.InsertItem(0, _T("101"));
	m_worksheetList.SetItemText(0, 1, _T("Auto54321"));
	m_worksheetList.SetItemText(0, 2, _T("CBC+RET"));
	m_worksheetList.SetItemText(0, 3, _T("999999"));
	m_worksheetList.SetItemText(0, 4, _T("1"));
	m_worksheetList.SetItemText(0, 5, _T("�Ѳ�"));

	m_worksheetList.InsertItem(0, _T("102"));
	m_worksheetList.SetItemText(0, 1, _T("54321"));
	m_worksheetList.SetItemText(0, 2, _T("CBC+RET"));
	m_worksheetList.SetItemText(0, 3, _T("999999"));
	m_worksheetList.SetItemText(0, 4, _T("1"));
	m_worksheetList.SetItemText(0, 5, _T("����"));

	return TRUE;
}

void CWorkSheetView::UpdateWorksheetForm()
{
	m_worksheetList.DeleteAllItems();

}

BOOL CWorkSheetView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return CBCGPChartExampleView::OnEraseBkgnd(pDC);
}
