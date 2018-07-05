// DevelopmentSetView.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "DevelopmentSetView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"
#include "FilesOperation.h"


// CDevelopmentSetView �Ի���

IMPLEMENT_DYNAMIC(CDevelopmentSetView, CDialogEx)

CDevelopmentSetView::CDevelopmentSetView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDevelopmentSetView::IDD, pParent)
	, m_structureRadio(0)
	, m_diluentRadio(0)
{

}

CDevelopmentSetView::~CDevelopmentSetView()
{
}

void CDevelopmentSetView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_STRUCTURE_NOPUNCTURE, m_structureRadio);
	DDX_Radio(pDX, IDC_DEVELOPERSET_DILUENT_20UL, m_diluentRadio);
}


BEGIN_MESSAGE_MAP(CDevelopmentSetView, CDialogEx)
	ON_WM_PAINT()	
	ON_BN_CLICKED(IDC_APPLY, &CDevelopmentSetView::OnBnClickedApply)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDevelopmentSetView ��Ϣ�������
BOOL CDevelopmentSetView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_structureRadio = systemcfg3.structure;
	m_diluentRadio = systemcfg3.diluent;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CDevelopmentSetView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	dc.FillPath();

	CDialogEx::OnPaint();
}


void CDevelopmentSetView::OnBnClickedApply()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	systemcfg3.structure = m_structureRadio;
	systemcfg3.diluent = m_diluentRadio;


	WriteSystemcfg3File();
	MessageBox(L"����ɹ�");

}




HBRUSH CDevelopmentSetView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STRUCTURE_NOPUNCTURE:
	case IDC_STRUCTURE_PUNCTURE:
	case IDC_STRUCTURE_AUTOSAMPLE:
	case IDC_DEVELOPERSET_DILUENT_20UL:
	case IDC_DEVELOPERSET_DILUENT_50UL:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	default:
		break;
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
