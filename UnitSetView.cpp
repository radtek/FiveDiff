// UnitSetView.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "UnitSetView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"
#include "FilesOperation.h"

// CUnitSetView �Ի���

IMPLEMENT_DYNAMIC(CUnitSetView, CDialogEx)

CUnitSetView::CUnitSetView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUnitSetView::IDD, pParent)
	, m_WBCunitRadio(0)
	, m_RBCunitRadio(0)
	, m_HGBunitRadio(0)
	, m_MCVunitRadio(0)
	, m_MCHunitRadio(0)
	, m_MCHCunitRadio(0)
	, m_PLTunitRadio(0)
	, m_MPVunitRadio(0)
	, m_PDWunitRadio(0)
	, m_OtherunitRadio(0)
{

}

CUnitSetView::~CUnitSetView()
{
}

void CUnitSetView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_WBCunitRadio);
	DDX_Radio(pDX, IDC_RADIO5, m_RBCunitRadio);
	DDX_Radio(pDX, IDC_RADIO9, m_HGBunitRadio);
	DDX_Radio(pDX, IDC_RADIO12, m_MCVunitRadio);
	DDX_Radio(pDX, IDC_RADIO14, m_MCHunitRadio);
	DDX_Radio(pDX, IDC_RADIO16, m_MCHCunitRadio);
	DDX_Radio(pDX, IDC_RADIO19, m_PLTunitRadio);
	DDX_Radio(pDX, IDC_RADIO23, m_MPVunitRadio);
	DDX_Radio(pDX, IDC_RADIO25, m_PDWunitRadio);
	DDX_Radio(pDX, IDC_RADIO26, m_OtherunitRadio);
}


BEGIN_MESSAGE_MAP(CUnitSetView, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_UNIT_APPLICATE, &CUnitSetView::OnUnitApplicate)
END_MESSAGE_MAP()


// CUnitSetView ��Ϣ�������


void CUnitSetView::OnPaint()
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


BOOL CUnitSetView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_WBCunitRadio = systemcfg.unitWBC;
	m_RBCunitRadio = systemcfg.unitRBC;
	m_HGBunitRadio = systemcfg.unitHGB;
	m_MCVunitRadio = systemcfg.unitMCVRDWSD;
	m_MCHunitRadio = systemcfg.unitMCH;
	m_MCHCunitRadio = systemcfg.unitMCHC;
	m_PLTunitRadio = systemcfg.unitPLT;
	m_MPVunitRadio = systemcfg.unitMPV;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


HBRUSH CUnitSetView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_RADIO1:
	case IDC_RADIO2:
	case IDC_RADIO3:
	case IDC_RADIO4:
	case IDC_RADIO5:
	case IDC_RADIO6:
	case IDC_RADIO7:
	case IDC_RADIO8:
	case IDC_RADIO9:
	case IDC_RADIO10:
	case IDC_RADIO11:
	case IDC_RADIO12:
	case IDC_RADIO13:
	case IDC_RADIO14:
	case IDC_RADIO15:
	case IDC_RADIO16:
	case IDC_RADIO17:
	case IDC_RADIO18:
	case IDC_RADIO19:
	case IDC_RADIO20:
	case IDC_RADIO21:
	case IDC_RADIO22:
	case IDC_RADIO23:
	case IDC_RADIO24:
	case IDC_RADIO25:
	case IDC_RADIO26:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	default:
		break;
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

void CUnitSetView::OnUnitApplicate()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	systemcfg.unitWBC = m_WBCunitRadio;
	systemcfg.unitRBC = m_RBCunitRadio ;
	systemcfg.unitHGB = m_HGBunitRadio ;
	systemcfg.unitMCVRDWSD = m_MCVunitRadio;
	systemcfg.unitMCH = m_MCHunitRadio;
	systemcfg.unitMCHC = m_MCHCunitRadio;
	systemcfg.unitPLT = m_PLTunitRadio;
	systemcfg.unitMPV = m_MPVunitRadio;
	WriteSystemcfgFile();
	MessageBox(L"����ɹ�");
}
