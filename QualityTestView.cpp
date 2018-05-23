// QualityTestView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "QualityTestView.h"
#include "afxdialogex.h"
#include "TestmainView.h"
#include "QualityTargetValueView.h"
#include "QualityListView.h"
#include "QualityControlChartView.h"


// CQualityTestView �Ի���
#define LMNE_LEFT		0
#define LMNE_BOTTOM 	0
#define LMNE_WIDTH		255//540-340  [0,255]->[340,540]
#define LMNE_HEIGHT		255


IMPLEMENT_DYNAMIC(CQualityTestView, CDialogEx)
extern  qcresult_info	 qcresultdata;			//����潻�������ݿ⽻���ı���
extern  patient_info  patientdata;

unsigned int CQualityTestView::QcLjFileExistEdit=1;	//0:�ļ�û�б༭��Ϣ��1:�ļ��б༭��

extern CQualityListView			m_QualityListPage;
extern CQualityControlChartView		m_QualityChartPage;
CQualityTestView::CQualityTestView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQualityTestView::IDD, pParent)
{
	VERIFY(textfont.CreateFont(
		15,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		GB2312_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
		L"����"));                 // lpszFacename
}

CQualityTestView::~CQualityTestView()
{
}

void CQualityTestView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_QUALITY_WBCLIST, m_WBCList);
	DDX_Control(pDX, IDC_QUALITY_RBCLIST, m_RBCList);
	DDX_Control(pDX, IDC_QUALITY_PLTLIST, m_PLTList);
	DDX_Control(pDX, IDC_QUALITY_RETLIST, m_RETList);
	DDX_Control(pDX, IDC_QUALITY_CRPLIST, m_CRPList);
	DDX_Control(pDX, IDC_CHART, m_LmneChart);
	DDX_Control(pDX, IDC_CHART1, m_BASOChart);
	DDX_Control(pDX, IDC_CHART2, m_RBCChart);
	DDX_Control(pDX, IDC_CHART3, m_PLTChart);
	DDX_Control(pDX, IDC_CHART4, m_PieChart);
}


BEGIN_MESSAGE_MAP(CQualityTestView, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_MESSAGE(WM_QUALITYTEST, &CQualityTestView::OnQualitytest)
	ON_WM_TIMER()
	ON_MESSAGE(WM_ACKSPI, &CQualityTestView::OnAckspi)
END_MESSAGE_MAP()

// CQualityTestView ��Ϣ�������


void CQualityTestView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));

	PrintLMNEChart(&qcresultdata);
	LmneGraphPaint(&qcresultdata, patientdata.rangetype);
}


HBRUSH CQualityTestView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO:  �ڴ˸��� DC ���κ�����
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC0:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	default:
		break;
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

BOOL CQualityTestView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString item_temp;
	switch (Controltype)
	{
	case 0:
		item_temp.Format(L"L-J�ʿؼ������ļ� %02u��", Controlfile + 1);
		break;
	case 1:
		item_temp.Format(L"X�ʿؼ������ļ� %02u��", Controlfile + 1);
		break;
	case 2:
		item_temp.Format(L"X-R�ʿؼ������ļ� %02u��", Controlfile + 1);
		break;
	default:
		break;
	}
	//getqcresultRow();
	
	SetDlgItemText(IDC_STATIC0, item_temp);
	GetDlgItem(IDC_STATIC0)->SetFont(&textfont);
	InitForm(&qcresultdata);
	PrintChart(&qcresultdata);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


BOOL CQualityTestView::InitForm(qcresult_info *qcresultdata)
{
	InitWBCForm(qcresultdata);
	InitRBCForm(qcresultdata);
	InitPLTForm(qcresultdata);
	InitCRPForm();
	InitRETForm();
	//AfxMessageBox(_T("1112"));
	return TRUE;

}

BOOL CQualityTestView::UpdateForm(qcresult_info *qcresultdata)
{
	UpdateWBCForm(qcresultdata);
	UpdateRBCForm(qcresultdata);
	UpdatePLTForm(qcresultdata);
	UpdateRETForm();
	UpdateCRPForm();
	return TRUE;
}

void CQualityTestView::PrintChart(qcresult_info *qcresultdata)
{
	//PrintLMNEChart(qcresultdata);
	PrintBASOChart(qcresultdata);
	PrintRBCChart(qcresultdata);
	PrintPLTChart(qcresultdata);
	PrintPieChart();
	//AfxMessageBox(_T("1718"));
}

void CQualityTestView::UpdatePrintChart(qcresult_info *qcresultdata)
{
	UpdateData();
	OnPaint();
	UpdatePrintBASOChart(qcresultdata);
	UpdatePrintRBCChart(qcresultdata);
	UpdatePrintPLTChart(qcresultdata);
	UpdatePrintPieChart();
}

BOOL CQualityTestView::InitWBCForm(qcresult_info *qcresultdata)
{
	CRect rect;

	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_WBCList.GetClientRect(&rect);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_WBCList.SetExtendedStyle(m_WBCList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_WBCList.SetRowHeigt(20);

	m_WBCList.DeleteAllItems();//����б�ˢ��

	m_WBCList.DeleteColumn(0);
	m_WBCList.DeleteColumn(1);
	m_WBCList.DeleteColumn(2);
	m_WBCList.DeleteColumn(3);
	m_WBCList.DeleteColumn(4);
	m_WBCList.DeleteColumn(5);

	// ΪWBC�б���ͼ�ؼ��������   
	m_WBCList.InsertColumn(0, _T("WBC"), LVCFMT_CENTER, rect.Width() / 6, 0);
	m_WBCList.InsertColumn(1, _T("����"), LVCFMT_CENTER, rect.Width() / 6, 1);
	m_WBCList.InsertColumn(2, _T("��λ"), LVCFMT_CENTER, rect.Width() / 6, 2);
	m_WBCList.InsertColumn(3, _T("LL"), LVCFMT_CENTER, rect.Width() / 6, 3);
	m_WBCList.InsertColumn(4, _T("UL"), LVCFMT_CENTER, rect.Width() / 6, 4);
	m_WBCList.InsertColumn(5, _T("Flag"), LVCFMT_CENTER, rect.Width() / 6, 5);

	// ��WBC�б���ͼ�ؼ��в����б���������б������ı�   
	m_WBCList.InsertItem(0, _T("WBC"));
	m_WBCList.SetItemText(0, 2, _T("10^9/L"));
	m_WBCList.InsertItem(1, _T("LYM%"));
	m_WBCList.SetItemText(1, 2, _T("%"));
	m_WBCList.InsertItem(2, _T("NEU%"));
	m_WBCList.SetItemText(2, 2, _T("%"));
	m_WBCList.InsertItem(3, _T("MONO%"));
	m_WBCList.SetItemText(3, 2, _T("%"));
	m_WBCList.InsertItem(4, _T("EOS%"));
	m_WBCList.SetItemText(4, 2, _T("%"));
	m_WBCList.InsertItem(5, _T("BASO%"));
	m_WBCList.SetItemText(5, 2, _T("%"));
	m_WBCList.InsertItem(6, _T("ALY%"));
	m_WBCList.SetItemText(6, 2, _T("%"));
	m_WBCList.InsertItem(7, _T("LIC%"));
	m_WBCList.SetItemText(7, 2, _T("%"));
	m_WBCList.InsertItem(8, _T("LYM%"));
	m_WBCList.SetItemText(8, 2, _T("10^9/L"));
	m_WBCList.InsertItem(9, _T("NEU#"));
	m_WBCList.SetItemText(9, 2, _T("10^9/L"));
	m_WBCList.InsertItem(10, _T("MONO#"));
	m_WBCList.SetItemText(10, 2, _T("10^9/L"));
	m_WBCList.InsertItem(11, _T("EOS#"));
	m_WBCList.SetItemText(11, 2, _T("10^9/L"));
	m_WBCList.InsertItem(12, _T("BASO#"));
	m_WBCList.SetItemText(12, 2, _T("10^9/L"));
	m_WBCList.InsertItem(13, _T("ALY#"));
	m_WBCList.SetItemText(13, 2, _T("10^9/L"));
	m_WBCList.InsertItem(14, _T("LIC#"));
	m_WBCList.SetItemText(14, 2, _T("10^9/L"));

	int itemCount = 15;
	CString showbuffer;
	uchar type = systemcfg.range.type;

	for (int i = 0; i < itemCount; i++){
		//m_WBCList.InsertItem(i, itemName[i]);
		//m_WBCList.SetItemText(i, 2, unit[i]);
		showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][i]);
		m_WBCList.SetItemText(i, 3, showbuffer);
		showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][i + 28]);
		m_WBCList.SetItemText(i, 4, showbuffer);
		//m_WBCList.SetItemText(i, 5, _T("Flagi"));
		m_WBCList.SetItemText(i, 5, _T(" "));

	}

	m_WBCList.SetItemText(0, 1, (CString)(*qcresultdata).wbcdata.wbc);
	m_WBCList.SetItemText(1, 1, (CString)(*qcresultdata).wbcdata.lymp);
	m_WBCList.SetItemText(2, 1, (CString)(*qcresultdata).wbcdata.neup);
	m_WBCList.SetItemText(3, 1, (CString)(*qcresultdata).wbcdata.monop);
	m_WBCList.SetItemText(4, 1, (CString)(*qcresultdata).wbcdata.eosp);
	m_WBCList.SetItemText(5, 1, (CString)(*qcresultdata).wbcdata.basp);
	m_WBCList.SetItemText(6, 1, (CString)(*qcresultdata).wbcdata.alyp);
	m_WBCList.SetItemText(7, 1, (CString)(*qcresultdata).wbcdata.licp);
	m_WBCList.SetItemText(8, 1, (CString)(*qcresultdata).wbcdata.lym);
	m_WBCList.SetItemText(9, 1, (CString)(*qcresultdata).wbcdata.neu);
	m_WBCList.SetItemText(10, 1, (CString)(*qcresultdata).wbcdata.mono);
	m_WBCList.SetItemText(11, 1, (CString)(*qcresultdata).wbcdata.eos);
	m_WBCList.SetItemText(12, 1, (CString)(*qcresultdata).wbcdata.bas);
	m_WBCList.SetItemText(13, 1, (CString)(*qcresultdata).wbcdata.aly);
	m_WBCList.SetItemText(14, 1, (CString)(*qcresultdata).wbcdata.lic);
	//AfxMessageBox(_T("1213"));
	return TRUE;
}
BOOL CQualityTestView::UpdateWBCForm(qcresult_info *qcresultdata)
{
	/*
	m_WBCList.SetItemText(0, 1, ChartsToCString(((*qcresultdata).wbcdata.wbc), sizeof((*qcresultdata).wbcdata.wbc) / sizeof(char)));
	m_WBCList.SetItemText(1, 1, ChartsToCString(((*qcresultdata).wbcdata.lymp), sizeof((*qcresultdata).wbcdata.lymp) / sizeof(char)));
	m_WBCList.SetItemText(2, 1, ChartsToCString(((*qcresultdata).wbcdata.neup), sizeof((*qcresultdata).wbcdata.neup) / sizeof(char)));
	m_WBCList.SetItemText(3, 1, ChartsToCString(((*qcresultdata).wbcdata.monop), sizeof((*qcresultdata).wbcdata.monop) / sizeof(char)));
	m_WBCList.SetItemText(4, 1, ChartsToCString(((*qcresultdata).wbcdata.eosp), sizeof((*qcresultdata).wbcdata.eosp) / sizeof(char)));
	m_WBCList.SetItemText(5, 1, ChartsToCString(((*qcresultdata).wbcdata.basp), sizeof((*qcresultdata).wbcdata.basp) / sizeof(char)));
	m_WBCList.SetItemText(6, 1, ChartsToCString(((*qcresultdata).wbcdata.alyp), sizeof((*qcresultdata).wbcdata.alyp) / sizeof(char)));
	m_WBCList.SetItemText(7, 1, ChartsToCString(((*qcresultdata).wbcdata.licp), sizeof((*qcresultdata).wbcdata.licp) / sizeof(char)));
	m_WBCList.SetItemText(8, 1, ChartsToCString(((*qcresultdata).wbcdata.lym), sizeof((*qcresultdata).wbcdata.lym) / sizeof(char)));
	m_WBCList.SetItemText(9, 1, ChartsToCString(((*qcresultdata).wbcdata.neu), sizeof((*qcresultdata).wbcdata.neu) / sizeof(char)));
	m_WBCList.SetItemText(10, 1, ChartsToCString(((*qcresultdata).wbcdata.mono), sizeof((*qcresultdata).wbcdata.mono) / sizeof(char)));
	m_WBCList.SetItemText(11, 1, ChartsToCString(((*qcresultdata).wbcdata.eos), sizeof((*qcresultdata).wbcdata.eos) / sizeof(char)));
	m_WBCList.SetItemText(12, 1, ChartsToCString(((*qcresultdata).wbcdata.bas), sizeof((*qcresultdata).wbcdata.bas) / sizeof(char)));
	m_WBCList.SetItemText(13, 1, ChartsToCString(((*qcresultdata).wbcdata.aly), sizeof((*qcresultdata).wbcdata.aly) / sizeof(char)));
	m_WBCList.SetItemText(14, 1, ChartsToCString(((*qcresultdata).wbcdata.lic), sizeof((*qcresultdata).wbcdata.lic) / sizeof(char)));

	return TRUE;
	*/

	uchar type = systemcfg.range.type;

	m_WBCList.SetItemText(0, 1, ChartsToCString((qcresultdata->wbcdata.wbc), sizeof(qcresultdata->wbcdata.wbc) / sizeof(char)));
	if (atof(qcresultdata->wbcdata.wbc)<systemcfg.range.normal[type][0])
		m_WBCList.SetItemText(0, 5, _T("L"));
	else if (atof(qcresultdata->wbcdata.wbc)>systemcfg.range.normal[type][0 + 28])
		m_WBCList.SetItemText(0, 5, _T("H"));

	m_WBCList.SetItemText(1, 1, ChartsToCString((qcresultdata->wbcdata.lymp), sizeof(qcresultdata->wbcdata.lymp) / sizeof(char)));
	if (atof(qcresultdata->wbcdata.lymp)<systemcfg.range.normal[type][1])
		m_WBCList.SetItemText(1, 5, _T("L"));
	else if (atof(qcresultdata->wbcdata.lymp)>systemcfg.range.normal[type][1 + 28])
		m_WBCList.SetItemText(1, 5, _T("H"));

	m_WBCList.SetItemText(2, 1, ChartsToCString((qcresultdata->wbcdata.neup), sizeof(qcresultdata->wbcdata.neup) / sizeof(char)));
	if (atof(qcresultdata->wbcdata.neup)<systemcfg.range.normal[type][2])
		m_WBCList.SetItemText(2, 5, _T("L"));
	else if (atof(qcresultdata->wbcdata.neup)>systemcfg.range.normal[type][2 + 28])
		m_WBCList.SetItemText(2, 5, _T("H"));

	m_WBCList.SetItemText(3, 1, ChartsToCString((qcresultdata->wbcdata.monop), sizeof(qcresultdata->wbcdata.monop) / sizeof(char)));
	if (atof(qcresultdata->wbcdata.monop)<systemcfg.range.normal[type][3])
		m_WBCList.SetItemText(3, 5, _T("L"));
	else if (atof(qcresultdata->wbcdata.monop)>systemcfg.range.normal[type][3 + 28])
		m_WBCList.SetItemText(3, 5, _T("H"));

	m_WBCList.SetItemText(4, 1, ChartsToCString((qcresultdata->wbcdata.eosp), sizeof(qcresultdata->wbcdata.eosp) / sizeof(char)));
	if (atof(qcresultdata->wbcdata.eosp)<systemcfg.range.normal[type][4])
		m_WBCList.SetItemText(4, 5, _T("L"));
	else if (atof(qcresultdata->wbcdata.eosp)>systemcfg.range.normal[type][4 + 28])
		m_WBCList.SetItemText(4, 5, _T("H"));

	m_WBCList.SetItemText(5, 1, ChartsToCString((qcresultdata->wbcdata.basp), sizeof(qcresultdata->wbcdata.basp) / sizeof(char)));
	if (atof(qcresultdata->wbcdata.basp)<systemcfg.range.normal[type][5])
		m_WBCList.SetItemText(5, 5, _T("L"));
	else if (atof(qcresultdata->wbcdata.basp)>systemcfg.range.normal[type][5 + 28])
		m_WBCList.SetItemText(5, 5, _T("H"));

	m_WBCList.SetItemText(6, 1, ChartsToCString((qcresultdata->wbcdata.alyp), sizeof(qcresultdata->wbcdata.alyp) / sizeof(char)));
	if (atof(qcresultdata->wbcdata.alyp)<systemcfg.range.normal[type][6])
		m_WBCList.SetItemText(6, 5, _T("L"));
	else if (atof(qcresultdata->wbcdata.alyp)>systemcfg.range.normal[type][6 + 28])
		m_WBCList.SetItemText(6, 5, _T("H"));

	m_WBCList.SetItemText(7, 1, ChartsToCString((qcresultdata->wbcdata.licp), sizeof(qcresultdata->wbcdata.licp) / sizeof(char)));
	if (atof(qcresultdata->wbcdata.licp)<systemcfg.range.normal[type][7])
		m_WBCList.SetItemText(7, 5, _T("L"));
	else if (atof(qcresultdata->wbcdata.licp)>systemcfg.range.normal[type][7 + 28])
		m_WBCList.SetItemText(7, 5, _T("H"));

	m_WBCList.SetItemText(8, 1, ChartsToCString((qcresultdata->wbcdata.lym), sizeof(qcresultdata->wbcdata.lym) / sizeof(char)));
	if (atof(qcresultdata->wbcdata.lym)<systemcfg.range.normal[type][8])
		m_WBCList.SetItemText(8, 5, _T("L"));
	else if (atof(qcresultdata->wbcdata.lym)>systemcfg.range.normal[type][8 + 28])
		m_WBCList.SetItemText(8, 5, _T("H"));

	m_WBCList.SetItemText(9, 1, ChartsToCString((qcresultdata->wbcdata.neu), sizeof(qcresultdata->wbcdata.neu) / sizeof(char)));
	if (atof(qcresultdata->wbcdata.neu)<systemcfg.range.normal[type][9])
		m_WBCList.SetItemText(9, 5, _T("L"));
	else if (atof(qcresultdata->wbcdata.neu)>systemcfg.range.normal[type][9 + 28])
		m_WBCList.SetItemText(9, 5, _T("H"));

	m_WBCList.SetItemText(10, 1, ChartsToCString((qcresultdata->wbcdata.mono), sizeof(qcresultdata->wbcdata.mono) / sizeof(char)));
	if (atof(qcresultdata->wbcdata.mono)<systemcfg.range.normal[type][10])
		m_WBCList.SetItemText(10, 5, _T("L"));
	else if (atof(qcresultdata->wbcdata.mono)>systemcfg.range.normal[type][10 + 28])
		m_WBCList.SetItemText(10, 5, _T("H"));

	m_WBCList.SetItemText(11, 1, ChartsToCString((qcresultdata->wbcdata.eos), sizeof(qcresultdata->wbcdata.eos) / sizeof(char)));
	if (atof(qcresultdata->wbcdata.eos)<systemcfg.range.normal[type][11])
		m_WBCList.SetItemText(11, 5, _T("L"));
	else if (atof(qcresultdata->wbcdata.eos)>systemcfg.range.normal[type][11 + 28])
		m_WBCList.SetItemText(11, 5, _T("H"));

	m_WBCList.SetItemText(12, 1, ChartsToCString((qcresultdata->wbcdata.bas), sizeof(qcresultdata->wbcdata.bas) / sizeof(char)));
	if (atof(qcresultdata->wbcdata.bas)<systemcfg.range.normal[type][12])
		m_WBCList.SetItemText(12, 5, _T("L"));
	else if (atof(qcresultdata->wbcdata.bas)>systemcfg.range.normal[type][12 + 28])
		m_WBCList.SetItemText(12, 5, _T("H"));

	m_WBCList.SetItemText(13, 1, ChartsToCString((qcresultdata->wbcdata.aly), sizeof(qcresultdata->wbcdata.aly) / sizeof(char)));
	if (atof(qcresultdata->wbcdata.aly)<systemcfg.range.normal[type][13])
		m_WBCList.SetItemText(13, 5, _T("L"));
	else if (atof(qcresultdata->wbcdata.aly)>systemcfg.range.normal[type][13 + 28])
		m_WBCList.SetItemText(13, 5, _T("H"));

	m_WBCList.SetItemText(14, 1, ChartsToCString((qcresultdata->wbcdata.lic), sizeof(qcresultdata->wbcdata.lic) / sizeof(char)));
	if (atof(qcresultdata->wbcdata.lic)<systemcfg.range.normal[type][14])
		m_WBCList.SetItemText(14, 5, _T("L"));
	else if (atof(qcresultdata->wbcdata.lic)>systemcfg.range.normal[type][14 + 28])
		m_WBCList.SetItemText(14, 5, _T("H"));

	return TRUE;
}
BOOL CQualityTestView::InitRBCForm(qcresult_info *qcresultdata)
{
	CRect rect;


	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_RBCList.GetClientRect(&rect);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_RBCList.SetExtendedStyle(m_RBCList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_RBCList.SetRowHeigt(20);

	m_RBCList.DeleteAllItems();//����б�ˢ��
	m_RBCList.DeleteColumn(0);
	m_RBCList.DeleteColumn(1);
	m_RBCList.DeleteColumn(2);
	m_RBCList.DeleteColumn(3);
	m_RBCList.DeleteColumn(4);
	m_RBCList.DeleteColumn(5);
	// ΪRBC�б���ͼ�ؼ��������  
	m_RBCList.InsertColumn(0, _T("RBC"), LVCFMT_CENTER, rect.Width() / 6, 0);
	m_RBCList.InsertColumn(1, _T("����"), LVCFMT_CENTER, rect.Width() / 6, 1);
	m_RBCList.InsertColumn(2, _T("��λ"), LVCFMT_CENTER, rect.Width() / 6, 2);
	m_RBCList.InsertColumn(3, _T("LL"), LVCFMT_CENTER, rect.Width() / 6, 3);
	m_RBCList.InsertColumn(4, _T("UL"), LVCFMT_CENTER, rect.Width() / 6, 4);
	m_RBCList.InsertColumn(5, _T("Flag"), LVCFMT_CENTER, rect.Width() / 6, 5);

	// ��RBC�б���ͼ�ؼ��в����б���������б������ı�
	m_RBCList.InsertItem(0, _T("RBC"));
	m_RBCList.SetItemText(0, 2, _T("10^12/L"));
	m_RBCList.InsertItem(1, _T("HGB"));
	m_RBCList.SetItemText(1, 2, _T("g/L"));
	m_RBCList.InsertItem(2, _T("HCT"));
	m_RBCList.SetItemText(2, 2, _T("%"));
	m_RBCList.InsertItem(3, _T("MCV"));
	m_RBCList.SetItemText(3, 2, _T("fL"));
	m_RBCList.InsertItem(4, _T("MCH"));
	m_RBCList.SetItemText(4, 2, _T("pg"));
	m_RBCList.InsertItem(5, _T("MCHC"));
	m_RBCList.SetItemText(5, 2, _T("g/L"));
	m_RBCList.InsertItem(6, _T("RDW-CV"));
	m_RBCList.SetItemText(6, 2, _T("%"));

	uchar type = systemcfg.range.type;
	CString showbuffer;
	int preCount = 15;
	int rbcNum = 8;
	for (int i = 0; i < rbcNum; i++){
		//	m_RBCList.InsertItem(i, itemNames[i]);
		//	m_RBCList.SetItemText(i, 2, unit[i]);
		showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][i + preCount]);
		m_RBCList.SetItemText(i, 3, showbuffer);
		showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][i + preCount + 28]);
		m_RBCList.SetItemText(i, 4, showbuffer);
		m_RBCList.SetItemText(i, 5, _T(" "));
	}

	m_RBCList.SetItemText(0, 1, (CString)(*qcresultdata).rbcdata.rbc);
	m_RBCList.SetItemText(1, 1, (CString)(*qcresultdata).rbcdata.hgb);
	m_RBCList.SetItemText(2, 1, (CString)(*qcresultdata).rbcdata.hct);
	m_RBCList.SetItemText(3, 1, (CString)(*qcresultdata).rbcdata.mcv);
	m_RBCList.SetItemText(4, 1, (CString)(*qcresultdata).rbcdata.mch);
	m_RBCList.SetItemText(5, 1, (CString)(*qcresultdata).rbcdata.mchc);
	m_RBCList.SetItemText(6, 1, (CString)(*qcresultdata).rbcdata.rdw);
	//AfxMessageBox(_T("1314"));
	return TRUE;
}

BOOL CQualityTestView::UpdateRBCForm(qcresult_info *qcresultdata)
{
	/*m_RBCList.SetItemText(0, 1, ChartsToCString(((*qcresultdata).rbcdata.rbc), sizeof((*qcresultdata).rbcdata.rbc) / sizeof(char)));
	m_RBCList.SetItemText(1, 1, ChartsToCString(((*qcresultdata).rbcdata.hgb), sizeof((*qcresultdata).rbcdata.hgb) / sizeof(char)));
	m_RBCList.SetItemText(2, 1, ChartsToCString(((*qcresultdata).rbcdata.hct), sizeof((*qcresultdata).rbcdata.hct) / sizeof(char)));
	m_RBCList.SetItemText(3, 1, ChartsToCString(((*qcresultdata).rbcdata.mcv), sizeof((*qcresultdata).rbcdata.mcv) / sizeof(char)));
	m_RBCList.SetItemText(4, 1, ChartsToCString(((*qcresultdata).rbcdata.mch), sizeof((*qcresultdata).rbcdata.mch) / sizeof(char)));
	m_RBCList.SetItemText(5, 1, ChartsToCString(((*qcresultdata).rbcdata.mchc), sizeof((*qcresultdata).rbcdata.mchc) / sizeof(char)));
	m_RBCList.SetItemText(6, 1, ChartsToCString(((*qcresultdata).rbcdata.rdw), sizeof((*qcresultdata).rbcdata.rdw) / sizeof(char)));
	//MessageBox((CString)qcresultdata.rbcdata.rdwcv);

	return TRUE;*/

	uchar type = systemcfg.range.type;
	int wbcNum = 15;
	m_RBCList.SetItemText(0, 1, ChartsToCString((qcresultdata->rbcdata.rbc), sizeof(qcresultdata->rbcdata.rbc) / sizeof(char)));
	if (atof(qcresultdata->rbcdata.rbc)<systemcfg.range.normal[type][0 + wbcNum])
		m_RBCList.SetItemText(0, 5, _T("L"));
	else if (atof(qcresultdata->rbcdata.rbc)>systemcfg.range.normal[type][0 + wbcNum + 28])
		m_RBCList.SetItemText(0, 5, _T("H"));

	m_RBCList.SetItemText(1, 1, ChartsToCString((qcresultdata->rbcdata.hgb), sizeof(qcresultdata->rbcdata.hgb) / sizeof(char)));
	if (atof(qcresultdata->rbcdata.hgb)<systemcfg.range.normal[type][1 + wbcNum])
		m_RBCList.SetItemText(1, 5, _T("L"));
	else if (atof(qcresultdata->rbcdata.hgb)>systemcfg.range.normal[type][1 + wbcNum + 28])
		m_RBCList.SetItemText(1, 5, _T("H"));

	m_RBCList.SetItemText(2, 1, ChartsToCString((qcresultdata->rbcdata.hct), sizeof(qcresultdata->rbcdata.hct) / sizeof(char)));
	if (atof(qcresultdata->rbcdata.hct)<systemcfg.range.normal[type][2 + wbcNum])
		m_RBCList.SetItemText(2, 5, _T("L"));
	else if (atof(qcresultdata->rbcdata.hct)>systemcfg.range.normal[type][2 + wbcNum + 28])
		m_RBCList.SetItemText(2, 5, _T("H"));

	m_RBCList.SetItemText(3, 1, ChartsToCString((qcresultdata->rbcdata.mcv), sizeof(qcresultdata->rbcdata.mcv) / sizeof(char)));
	if (atof(qcresultdata->rbcdata.mcv)<systemcfg.range.normal[type][3 + wbcNum])
		m_RBCList.SetItemText(3, 5, _T("L"));
	else if (atof(qcresultdata->rbcdata.mcv)>systemcfg.range.normal[type][3 + wbcNum + 28])
		m_RBCList.SetItemText(3, 5, _T("H"));

	m_RBCList.SetItemText(4, 1, ChartsToCString((qcresultdata->rbcdata.mch), sizeof(qcresultdata->rbcdata.mch) / sizeof(char)));
	if (atof(qcresultdata->rbcdata.mch)<systemcfg.range.normal[type][4 + wbcNum])
		m_RBCList.SetItemText(4, 5, _T("L"));
	else if (atof(qcresultdata->rbcdata.mch)>systemcfg.range.normal[type][4 + wbcNum + 28])
		m_RBCList.SetItemText(4, 5, _T("H"));

	m_RBCList.SetItemText(5, 1, ChartsToCString((qcresultdata->rbcdata.mchc), sizeof(qcresultdata->rbcdata.mchc) / sizeof(char)));
	if (atof(qcresultdata->rbcdata.mchc)<systemcfg.range.normal[type][5 + wbcNum])
		m_RBCList.SetItemText(5, 5, _T("L"));
	else if (atof(qcresultdata->rbcdata.mchc)>systemcfg.range.normal[type][5 + wbcNum + 28])
		m_RBCList.SetItemText(5, 5, _T("H"));

	m_RBCList.SetItemText(6, 1, ChartsToCString((qcresultdata->rbcdata.rdw), sizeof(qcresultdata->rbcdata.rdw) / sizeof(char)));
	if (atof(qcresultdata->rbcdata.rdw)<systemcfg.range.normal[type][6 + wbcNum])
		m_RBCList.SetItemText(6, 5, _T("L"));
	else if (atof(qcresultdata->rbcdata.rdw)>systemcfg.range.normal[type][6 + wbcNum + 28])
		m_RBCList.SetItemText(6, 5, _T("H"));
	//MessageBox((CString)qcresultdata->rbcdata.rdw);
	//m_RBCList.SetItemText(7, 1, ChartsToCString((qcresultdata->rbcdata.rdwsd), sizeof(qcresultdata->rbcdata.rdwsd) / sizeof(char)));
	//if (atof(qcresultdata->rbcdata.rdwsd)<systemcfg.range.normal[type][7 + wbcNum])
	//	m_RBCList.SetItemText(7, 5, _T("L"));
	//else if (atof(qcresultdata->rbcdata.rdwsd)>systemcfg.range.normal[type][7 + wbcNum + 28])
	//	m_RBCList.SetItemText(7, 5, _T("H"));
	return TRUE;
}

BOOL CQualityTestView::InitPLTForm(qcresult_info *qcresultdata)
{
	CRect rect;

	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_PLTList.GetClientRect(&rect);
	m_PLTList.SetRowHeigt(20);

	m_PLTList.DeleteAllItems();//����б�ˢ��

	m_PLTList.DeleteColumn(0);
	m_PLTList.DeleteColumn(1);
	m_PLTList.DeleteColumn(2);
	m_PLTList.DeleteColumn(3);
	m_PLTList.DeleteColumn(4);
	m_PLTList.DeleteColumn(5);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_PLTList.SetExtendedStyle(m_PLTList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	// ΪPLT�б���ͼ�ؼ��������
	m_PLTList.InsertColumn(0, _T("PLT"), LVCFMT_CENTER, rect.Width() / 6, 0);
	m_PLTList.InsertColumn(1, _T("����"), LVCFMT_CENTER, rect.Width() / 6, 1);
	m_PLTList.InsertColumn(2, _T("��λ"), LVCFMT_CENTER, rect.Width() / 6, 2);
	m_PLTList.InsertColumn(3, _T("LL"), LVCFMT_CENTER, rect.Width() / 6, 3);
	m_PLTList.InsertColumn(4, _T("UL"), LVCFMT_CENTER, rect.Width() / 6, 4);
	m_PLTList.InsertColumn(5, _T("Flag"), LVCFMT_CENTER, rect.Width() / 6, 5);

/*	// ��PLT�б���ͼ�ؼ��в����б���������б������ı�
	m_PLTList.InsertItem(0, _T("PLT"));
	m_PLTList.SetItemText(0, 2, _T("10^9/L"));
	m_PLTList.InsertItem(1, _T("MPV"));
	m_PLTList.SetItemText(1, 2, _T("fL"));
	m_PLTList.InsertItem(2, _T("PDW"));
	m_PLTList.SetItemText(2, 2, _T("fL"));
	m_PLTList.InsertItem(3, _T("PCT"));
	m_PLTList.SetItemText(3, 2, _T("%"));

	CString showbuffer;
	//showbuffer.Format(L"%0.1f", atof(qcresultdata.pltdata.plt)/10);
	showbuffer.Format(L"%0.1f", atof((*qcresultdata).pltdata.plt));
	m_PLTList.SetItemText(0, 1, showbuffer);
	m_PLTList.SetItemText(1, 1, (CString)(*qcresultdata).pltdata.mpv);
	m_PLTList.SetItemText(2, 1, (CString)(*qcresultdata).pltdata.pdw);
	m_PLTList.SetItemText(3, 1, (CString)(*qcresultdata).pltdata.pct);
	*/
	CString showbuffer;
	//JYP
	uchar type = systemcfg.range.type;

	// ��PLT�б���ͼ�ؼ��в����б���������б������ı�
	m_PLTList.InsertItem(0, _T("PLT"));
	m_PLTList.SetItemText(0, 2, _T("10^9/L"));
	showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][23]);
	m_PLTList.SetItemText(0, 3, showbuffer);
	showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][23 + 28]);
	m_PLTList.SetItemText(0, 4, showbuffer);
	m_PLTList.SetItemText(0, 5, _T(" "));

	m_PLTList.InsertItem(1, _T("MPV"));
	m_PLTList.SetItemText(1, 2, _T("fL"));
	showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][24]);
	m_PLTList.SetItemText(1, 3, showbuffer);
	showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][24 + 28]);
	m_PLTList.SetItemText(1, 4, showbuffer);
	m_PLTList.SetItemText(1, 5, _T(" "));

	m_PLTList.InsertItem(2, _T("PDW"));
	m_PLTList.SetItemText(2, 2, _T("fL"));
	showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][25]);
	m_PLTList.SetItemText(2, 3, showbuffer);
	showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][25 + 28]);
	m_PLTList.SetItemText(2, 4, showbuffer);
	m_PLTList.SetItemText(2, 5, _T(" "));

	m_PLTList.InsertItem(3, _T("PCT"));
	m_PLTList.SetItemText(3, 2, _T("%"));
	showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][26]);
	m_PLTList.SetItemText(3, 3, showbuffer);
	showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][26 + 28]);
	m_PLTList.SetItemText(3, 4, showbuffer);
	m_PLTList.SetItemText(3, 5, _T(" "));

	//m_PLTList.InsertItem(4, _T("P-LCR"));
	//m_PLTList.SetItemText(4, 2, _T("%"));
	//showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][27]);
	//m_PLTList.SetItemText(4, 3, showbuffer);
	//showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][27 + 28]);
	//m_PLTList.SetItemText(4, 4, showbuffer);
	//m_PLTList.SetItemText(4, 5, _T(" "));

	//showbuffer.Format(L"%0.1f", atof(qcresultdata.pltdata.plt)/10);
	showbuffer.Format(L"%0.1f", atof((*qcresultdata).pltdata.plt));
	m_PLTList.SetItemText(0, 1, showbuffer);
	m_PLTList.SetItemText(1, 1, (CString)(*qcresultdata).pltdata.mpv);
	m_PLTList.SetItemText(2, 1, (CString)(*qcresultdata).pltdata.pdw);
	m_PLTList.SetItemText(3, 1, (CString)(*qcresultdata).pltdata.pct);
	//AfxMessageBox(_T("1415"));
	return TRUE;
}
BOOL CQualityTestView::UpdatePLTForm(qcresult_info *qcresultdata)
{

	uchar type = systemcfg.range.type;
	int preNum = 23
		;
	m_PLTList.SetItemText(0, 1, ChartsToCString((qcresultdata->pltdata.plt), sizeof(qcresultdata->pltdata.plt) / sizeof(char)));
	if (atof(qcresultdata->pltdata.plt)<systemcfg.range.normal[type][0 + preNum])
		m_PLTList.SetItemText(0, 5, _T("L"));
	else if (atof(qcresultdata->pltdata.plt)>systemcfg.range.normal[type][0 + preNum + 28])
		m_PLTList.SetItemText(0, 5, _T("H"));

	m_PLTList.SetItemText(1, 1, ChartsToCString((qcresultdata->pltdata.mpv), sizeof(qcresultdata->pltdata.mpv) / sizeof(char)));
	if (atof(qcresultdata->pltdata.mpv)<systemcfg.range.normal[type][1 + preNum])
		m_PLTList.SetItemText(1, 5, _T("L"));
	else if (atof(qcresultdata->pltdata.mpv)>systemcfg.range.normal[type][1 + preNum + 28])
		m_PLTList.SetItemText(1, 5, _T("H"));

	m_PLTList.SetItemText(2, 1, ChartsToCString((qcresultdata->pltdata.pdw), sizeof(qcresultdata->pltdata.pdw) / sizeof(char)));
	if (atof(qcresultdata->pltdata.pdw)<systemcfg.range.normal[type][2 + preNum])
		m_PLTList.SetItemText(2, 5, _T("L"));
	else if (atof(qcresultdata->pltdata.pdw)>systemcfg.range.normal[type][2 + preNum + 28])
		m_PLTList.SetItemText(2, 5, _T("H"));

	m_PLTList.SetItemText(3, 1, ChartsToCString((qcresultdata->pltdata.pct), sizeof(qcresultdata->pltdata.pct) / sizeof(char)));
	if (atof(qcresultdata->pltdata.pct)<systemcfg.range.normal[type][3 + preNum])
		m_PLTList.SetItemText(3, 5, _T("L"));
	else if (atof(qcresultdata->pltdata.pct)>systemcfg.range.normal[type][3 + preNum] + 28)
		m_PLTList.SetItemText(3, 5, _T("H"));

	//m_PLTList.SetItemText(4, 1, ChartsToCString((qcresultdata->pltdata.plcr), sizeof(qcresultdata->pltdata.plcr) / sizeof(char)));
	//if (atof(qcresultdata->pltdata.plcr)<systemcfg.range.normal[type][4 + preNum])
	//	m_PLTList.SetItemText(4, 5, _T("L"));
	//else if (atof(qcresultdata->pltdata.plcr)>systemcfg.range.normal[type][4 + preNum + 28])
	//	m_PLTList.SetItemText(4, 5, _T("H"));

	return TRUE;

	//m_PLTList.SetItemText(0, 1, ChartsToCString((qcresultdata.pltdata.plt), sizeof(qcresultdata.pltdata.plt) / sizeof(char)));
	//m_PLTList.SetItemText(1, 1, ChartsToCString((qcresultdata.pltdata.mpv), sizeof(qcresultdata.pltdata.mpv) / sizeof(char)));
	//m_PLTList.SetItemText(2, 1, ChartsToCString((qcresultdata.pltdata.pdw), sizeof(qcresultdata.pltdata.pdw) / sizeof(char)));
	//m_PLTList.SetItemText(3, 1, ChartsToCString((qcresultdata.pltdata.pct), sizeof(qcresultdata.pltdata.pct) / sizeof(char)));


	//return TRUE;
}
BOOL CQualityTestView::InitRETForm()
{
	CRect rect;
	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_RETList.GetClientRect(&rect);
	m_RETList.SetRowHeigt(20);
	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_RETList.SetExtendedStyle(m_RETList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_RETList.DeleteAllItems();//����б�ˢ��
	m_RETList.DeleteColumn(0);
	m_RETList.DeleteColumn(1);
	m_RETList.DeleteColumn(2);
	m_RETList.DeleteColumn(3);
	m_RETList.DeleteColumn(4);
	m_RETList.DeleteColumn(5);

	// ΪRET�б���ͼ�ؼ��������
	m_RETList.InsertColumn(0, _T("RET"), LVCFMT_CENTER, rect.Width() / 6, 0);
	m_RETList.InsertColumn(1, _T("����"), LVCFMT_CENTER, rect.Width() / 6, 1);
	m_RETList.InsertColumn(2, _T("��λ"), LVCFMT_CENTER, rect.Width() / 6, 2);
	m_RETList.InsertColumn(3, _T("LL"), LVCFMT_CENTER, rect.Width() / 6, 3);
	m_RETList.InsertColumn(4, _T("UL"), LVCFMT_CENTER, rect.Width() / 6, 4);
	m_RETList.InsertColumn(5, _T("Flag"), LVCFMT_CENTER, rect.Width() / 6, 5);

	// ��RET�б���ͼ�ؼ��в����б���������б������ı�
	m_RETList.InsertItem(0, _T("RET%"));
	m_RETList.SetItemText(0, 2, _T("10^9/L"));
	m_RETList.InsertItem(1, _T("RET#"));
	m_RETList.SetItemText(1, 2, _T("fL"));
	m_RETList.InsertItem(2, _T("RETL"));
	m_RETList.SetItemText(2, 2, _T("fL"));
	m_RETList.InsertItem(3, _T("RETM"));
	m_RETList.SetItemText(3, 2, _T("%"));
	m_RETList.InsertItem(4, _T("RETH"));
	m_RETList.SetItemText(4, 2, _T("%"));
	m_RETList.InsertItem(5, _T("MFI"));
	m_RETList.SetItemText(5, 2, _T("%"));
	m_RETList.InsertItem(6, _T("IMM"));
	m_RETList.SetItemText(6, 2, _T("%"));
	m_RETList.InsertItem(7, _T("MRV"));
	m_RETList.SetItemText(7, 2, _T("fL"));
	m_RETList.InsertItem(8, _T("IRF"));
	m_RETList.SetItemText(8, 2, _T("%"));
	m_RETList.InsertItem(9, _T("CRC"));
	m_RETList.SetItemText(9, 2, _T("%"));
	//AfxMessageBox(_T("1516"));
	return TRUE;
}
BOOL CQualityTestView::UpdateRETForm()
{
	return TRUE;
}
BOOL CQualityTestView::InitCRPForm()
{
	CRect rect;

	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_CRPList.GetClientRect(&rect);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_CRPList.SetExtendedStyle(m_CRPList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_CRPList.SetItemColor(0, RGB(100, 125, 100), RGB(15, 235, 150));//�����ض�Item ���� ������ɫ
	m_CRPList.SetRowHeigt(20);

	m_CRPList.DeleteAllItems();//����б�ˢ��
	m_CRPList.DeleteColumn(0);
	m_CRPList.DeleteColumn(1);
	m_CRPList.DeleteColumn(2);
	m_CRPList.DeleteColumn(3);
	m_CRPList.DeleteColumn(4);
	m_CRPList.DeleteColumn(5);

	// ΪCRP�б���ͼ�ؼ��������
	m_CRPList.InsertColumn(0, _T("CRP"), LVCFMT_CENTER, rect.Width() / 6, 0);
	m_CRPList.InsertColumn(1, _T("����"), LVCFMT_CENTER, rect.Width() / 6, 1);
	m_CRPList.InsertColumn(2, _T("��λ"), LVCFMT_CENTER, rect.Width() / 6, 2);
	m_CRPList.InsertColumn(3, _T("LL"), LVCFMT_CENTER, rect.Width() / 6, 3);
	m_CRPList.InsertColumn(4, _T("UL"), LVCFMT_CENTER, rect.Width() / 6, 4);
	m_CRPList.InsertColumn(5, _T("Flag"), LVCFMT_CENTER, rect.Width() / 6, 5);

	// ��CRP�б���ͼ�ؼ��в����б���������б������ı�
	m_CRPList.InsertItem(0, _T("CRP"));
	m_CRPList.SetItemText(0, 2, _T("10^9/L"));

	//AfxMessageBox(_T("1617"));
	return TRUE;
}

BOOL CQualityTestView::UpdateCRPForm()
{
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////	
//Description:	��̬��ʼ��LMNEɢ��ͼ��������ֵ						  	//
//Called by: LmneAnalysis																	//
//Params illustration:																		//
//Data Access:																			//
//Other:																					//
//*History:																				//
//	(1)Created:20150121																	//
//////////////////////////////////////////////////////////////////////////////////////////

void CQualityTestView::Init_B_LMNE(float	coefficient, B_LMNE* p_blmne)
{
	float		coe_rtoabs;

	//Resistance
	p_blmne->X_NOL = (uchar)systemcfg.range.thresholds[NoL] * coefficient;
	p_blmne->X_NON = (uchar)systemcfg.range.thresholds[NoN] * coefficient;
	p_blmne->X_LL = (uchar)systemcfg.range.thresholds[LL] * coefficient;
	p_blmne->X_LN = (uchar)systemcfg.range.thresholds[LN] * coefficient;
	p_blmne->X_AL = (uchar)systemcfg.range.thresholds[AL] * coefficient;
	p_blmne->X_LMN = (uchar)systemcfg.range.thresholds[LMN] * coefficient;
	p_blmne->X_LMU = (uchar)systemcfg.range.thresholds[LMU] * coefficient;
	p_blmne->X_MN = (uchar)systemcfg.range.thresholds[MN] * coefficient;
	p_blmne->X_LMD = (uchar)systemcfg.range.thresholds[LMD] * coefficient;

	p_blmne->X_NOE = (uchar)systemcfg.range.thresholds[NoE] * 1.0;
	p_blmne->X_RM = (uchar)systemcfg.range.thresholds[RM] * 1.0;
	p_blmne->X_RN = (uchar)systemcfg.range.thresholds[RN] * 1.0;

	coe_rtoabs = coefficient * 1.0;
	//Absorbance
	p_blmne->Y_NL = (uchar)systemcfg.range.thresholds[NL] * coe_rtoabs;
	p_blmne->Y_RMN = (uchar)systemcfg.range.thresholds[RMN] * coe_rtoabs;
	p_blmne->Y_NE = (uchar)systemcfg.range.thresholds[NE] * coe_rtoabs;
}
/***********************************************************
*Function:
*Description:	��ɢ��ͼ
*Called by:
*Params illustration:
*Data Access:	��ȫ�ֱ���
*History:	create	lgq		2010.12.31
************************************************************/
void CQualityTestView::LmneGraphPaint(qcresult_info *qcresultdata, const unsigned char rangetype)
{
	unsigned int i;
	unsigned char res = 0, scatter = 0;	//���迹�źţ���ɢ���ź�
	unsigned char rangeFlag = ' ', doubtFlag = ' ';
	char showbuff[9] = { 0 };
	unsigned char graphbuff[MATRIX_DATA_MAX] = { 0 };

	B_LMNE		m_blmne;
	CRect rect;
	CWnd* pWnd = GetDlgItem(IDC_CHART);
	pWnd->GetClientRect(&rect); // ��ȡ�ؼ���Ļ����
	CDC* pDC = pWnd->GetDC();

	pDC->SetViewportOrg(0, rect.Height());
	//if (qcresultdata.coeoflmne > 1.3)
	//	qcresultdata.coeoflmne = 1.3;
	//else if (qcresultdata.coeoflmne < 0.7)
	//	qcresultdata.coeoflmne = 0.7;

	//Init_B_LMNE((*qcresultdata).coeoflmne, &m_blmne);
	Init_B_LMNE(1, &m_blmne);
	//SetTextColor(hdc, COLOR_black);
	if ((*qcresultdata).wbcdata.wbc[0] == '*')//δ������
	{
		sprintf(showbuff, "%s%s", "   ", (*qcresultdata).wbcdata.lymp);
		//TextOut(hdc, 85, 35 + 18, showbuff);
		sprintf(showbuff, "%s%s", "   ", (*qcresultdata).wbcdata.neup);
		//TextOut(hdc, 85, 35 + 36, showbuff);
		sprintf(showbuff, "%s%s", "   ", (*qcresultdata).wbcdata.monop);
		//TextOut(hdc, 85, 35 + 54, showbuff);
		sprintf(showbuff, "%s%s", "   ", (*qcresultdata).wbcdata.eosp);
		//TextOut(hdc, 85, 35 + 72, showbuff);
		sprintf(showbuff, "%s%s", "   ", (*qcresultdata).wbcdata.alyp);
		//TextOut(hdc, 85, 35 + 108, showbuff);
		sprintf(showbuff, "%s%s", "   ", (*qcresultdata).wbcdata.licp);
		//TextOut(hdc, 85, 35 + 126, showbuff);

		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%s%.1f", "   ", 10 * atof((*qcresultdata).wbcdata.lym));
		else
			sprintf(showbuff, "%s%s", "   ", (*qcresultdata).wbcdata.lym);
		//TextOut(hdc, 85, 35 + 144, showbuff);

		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%s%.1f", "   ", 10 * atof((*qcresultdata).wbcdata.neu));
		else
			sprintf(showbuff, "%s%s", "   ", (*qcresultdata).wbcdata.neu);
		//TextOut(hdc, 85, 35 + 162, showbuff);

		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%s%.1f", "   ", 10 * atof((*qcresultdata).wbcdata.mono));
		else
			sprintf(showbuff, "%s%s", "   ", (*qcresultdata).wbcdata.mono);
		//TextOut(hdc, 85, 35 + 180, showbuff);

		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%s%.1f", "   ", 10 * atof((*qcresultdata).wbcdata.eos));
		else
			sprintf(showbuff, "%s%s", "   ", (*qcresultdata).wbcdata.eos);
		//TextOut(hdc, 85, 35 + 198, showbuff);

		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%s%.1f", "   ", 10 * atof((*qcresultdata).wbcdata.aly));
		else
			sprintf(showbuff, "%s%s", "   ", (*qcresultdata).wbcdata.aly);
		//TextOut(hdc, 85, 35 + 234, showbuff);

		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%s%.1f", "   ", 10 * atof((*qcresultdata).wbcdata.lic));
		else
			sprintf(showbuff, "%s%s", "   ", (*qcresultdata).wbcdata.lic);
		//TextOut(hdc, 85, 35 + 252, showbuff);
	}
	else//���˲���
	{
		//if (1 == (*qcresultdata).flag_wrp[0])
		//	doubtFlag = ' ';
		//else if (2 == (*qcresultdata).flag_wrp[0])
		//	doubtFlag = '?';
		//else
		//	doubtFlag = '*';

		//LYMP
		if (atof((*qcresultdata).wbcdata.lymp) < systemcfg.range.normal[rangetype][LYMP])
			rangeFlag = 'L';
		else if (atof((*qcresultdata).wbcdata.lymp) > systemcfg.range.normal[rangetype][LYMP + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*qcresultdata).wbcdata.lymp);
		//TextOut(hdc, 85, 35 + 18, showbuff);
		//NEUP
		if (atof((*qcresultdata).wbcdata.neup) < systemcfg.range.normal[rangetype][NEUP])
			rangeFlag = 'L';
		else if (atof((*qcresultdata).wbcdata.neup) > systemcfg.range.normal[rangetype][NEUP + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*qcresultdata).wbcdata.neup);
		//TextOut(hdc, 85, 35 + 36, showbuff);
		//MONOP
		if (atof((*qcresultdata).wbcdata.monop) < systemcfg.range.normal[rangetype][MONOP])
			rangeFlag = 'L';
		else if (atof((*qcresultdata).wbcdata.monop) > systemcfg.range.normal[rangetype][MONOP + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*qcresultdata).wbcdata.monop);
		//TextOut(hdc, 85, 35 + 54, showbuff);
		//EOSP
		if (atof((*qcresultdata).wbcdata.eosp) < systemcfg.range.normal[rangetype][EOSP])
			rangeFlag = 'L';
		else if (atof((*qcresultdata).wbcdata.eosp) > systemcfg.range.normal[rangetype][EOSP + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*qcresultdata).wbcdata.eosp);
		//TextOut(hdc, 85, 35 + 72, showbuff);
		//ALYP
		if (atof((*qcresultdata).wbcdata.alyp) < systemcfg.range.normal[rangetype][ALYP])
			rangeFlag = 'L';
		else if (atof((*qcresultdata).wbcdata.alyp) > systemcfg.range.normal[rangetype][ALYP + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*qcresultdata).wbcdata.alyp);
		//TextOut(hdc, 85, 35 + 108, showbuff);
		//LICP
		if (atof((*qcresultdata).wbcdata.licp) < systemcfg.range.normal[rangetype][LICP])
			rangeFlag = 'L';
		else if (atof((*qcresultdata).wbcdata.licp) > systemcfg.range.normal[rangetype][LICP + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*qcresultdata).wbcdata.licp);
		//TextOut(hdc, 85, 35 + 126, showbuff);

		//LYM
		if (atof((*qcresultdata).wbcdata.lym) < systemcfg.range.normal[rangetype][LYMS])
			rangeFlag = 'L';
		else if (atof((*qcresultdata).wbcdata.lym) > systemcfg.range.normal[rangetype][LYMS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%c%c %.1f", rangeFlag, doubtFlag, 10 * atof((*qcresultdata).wbcdata.lym));
		else
			sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*qcresultdata).wbcdata.lym);
		//TextOut(hdc, 85, 35 + 144, showbuff);
		//NEU
		if (atof((*qcresultdata).wbcdata.neu) < systemcfg.range.normal[rangetype][NEUS])
			rangeFlag = 'L';
		else if (atof((*qcresultdata).wbcdata.neu) > systemcfg.range.normal[rangetype][NEUS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%c%c %.1f", rangeFlag, doubtFlag, 10 * atof((*qcresultdata).wbcdata.neu));
		else
			sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*qcresultdata).wbcdata.neu);
		//TextOut(hdc, 85, 35 + 162, showbuff);
		//MONO
		if (atof((*qcresultdata).wbcdata.mono) < systemcfg.range.normal[rangetype][MONOS])
			rangeFlag = 'L';
		else if (atof((*qcresultdata).wbcdata.mono) > systemcfg.range.normal[rangetype][MONOS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%c%c %.1f", rangeFlag, doubtFlag, 10 * atof((*qcresultdata).wbcdata.mono));
		else
			sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*qcresultdata).wbcdata.mono);
		//TextOut(hdc, 85, 35 + 180, showbuff);
		//EOS
		if (atof((*qcresultdata).wbcdata.eos) < systemcfg.range.normal[rangetype][EOSS])
			rangeFlag = 'L';
		else if (atof((*qcresultdata).wbcdata.eos) > systemcfg.range.normal[rangetype][EOSS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%c%c %.1f", rangeFlag, doubtFlag, 10 * atof((*qcresultdata).wbcdata.eos));
		else
			sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*qcresultdata).wbcdata.eos);
		//TextOut(hdc, 85, 35 + 198, showbuff);
		//ALY
		if (atof((*qcresultdata).wbcdata.aly) < systemcfg.range.normal[rangetype][ALYS])
			rangeFlag = 'L';
		else if (atof((*qcresultdata).wbcdata.aly) > systemcfg.range.normal[rangetype][ALYS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%c%c %.1f", rangeFlag, doubtFlag, 10 * atof((*qcresultdata).wbcdata.aly));
		else
			sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*qcresultdata).wbcdata.aly);
		//TextOut(hdc, 85, 35 + 234, showbuff);
		//LIC
		if (atof((*qcresultdata).wbcdata.lic) < systemcfg.range.normal[rangetype][LICS])
			rangeFlag = 'L';
		else if (atof((*qcresultdata).wbcdata.lic) > systemcfg.range.normal[rangetype][LICS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%c%c %.1f", rangeFlag, doubtFlag, 10 * atof((*qcresultdata).wbcdata.lic));
		else
			sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*qcresultdata).wbcdata.lic);
		//TextOut(hdc, 85, 35 + 252, showbuff);
	}

	//SetTextColor(hdc, COLOR_red);
	//WBC������Ϣ	if (2 == (*qcresultdata).lmneflg[0])
		//TextOut(hdc, 265, 65, "NO");
		//if (2 == (*qcresultdata).lmneflg[1])
		//	//TextOut(hdc, 265, 83, "LL");
		//	if (2 == (*qcresultdata).lmneflg[2])
		//		//TextOut(hdc, 265, 101, "LL1");
		//		if (2 == (*qcresultdata).lmneflg[3])
		//			//TextOut(hdc, 265, 119, "NL");
		//			if (2 == (*qcresultdata).lmneflg[4])
		//				//TextOut(hdc, 265, 137, "MN");
		//				if (2 == (*qcresultdata).lmneflg[5])
		//					//TextOut(hdc, 265, 155, "RM");
		//					if (2 == (*qcresultdata).lmneflg[6])
		//						//TextOut(hdc, 265, 173, "LN");
		//						if (2 == (*qcresultdata).lmneflg[7])
		//							//TextOut(hdc, 265, 191, "RN");
		//							if (2 == (*qcresultdata).lmneflg[8])
		//								//TextOut(hdc, 265, 209, "NE");

										//------------------------------------------------
										//LMNEɢ��ͼ		
										//����0x00�����⴦��ȥ��,�ָ�ԭʼ����
										for (i = 0; i < MATRIX_DATA_MAX - 1; i++)
											graphbuff[i] = (*qcresultdata).lmnegraph[i] - 1;

	for (i = 0; i < MATRIX_POINT_MAX - 1; i++)
	{
		res = graphbuff[(i << 1)];
		scatter = graphbuff[(i << 1) + 1];
		if (scatter >= m_blmne.Y_NE)
		{
			if (res < m_blmne.X_NOE)
				pDC->SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 0, 0));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_lightwhite);
			else
				pDC->SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(255, 0, 0));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_red);
		}
		else if (scatter >= m_blmne.Y_RMN)
		{
			if (res < m_blmne.X_NON)
				pDC->SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 0, 0));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_lightwhite);
			else if (res < m_blmne.X_LN)
				pDC->SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 250, 0));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_green);
			else if (m_blmne.X_RN)
				pDC->SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 250, 0));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_green);
			else
				pDC->SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 250, 0));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_green);
		}
		else if (scatter >= m_blmne.Y_NL)
		{
			if (res < m_blmne.X_NON)
				pDC->SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 0, 0));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_lightwhite);
			else if (res < m_blmne.X_LN)
				pDC->SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 250, 0));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_green);
			else if (res < m_blmne.X_LMN)
				pDC->SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 250, 0));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_green);
			else if (res < m_blmne.X_MN)
			{
				if ((res - m_blmne.X_LMN)*(m_blmne.Y_RMN - m_blmne.Y_NL) < (m_blmne.X_MN - m_blmne.X_LMN)*(scatter - m_blmne.Y_NL))
					pDC->SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 250, 0));
				//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_green);
				else
					pDC->SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(230, 30, 70));
				//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_magenta);
			}
			else if (res < m_blmne.X_RM)
				pDC->SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(230, 30, 70));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_magenta);
			else
				pDC->SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(230, 30, 70));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_magenta);
		}
		else
		{
			if (res < m_blmne.X_NOL)
				pDC->SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 0, 0));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_lightwhite);
			else if (res < m_blmne.X_LL)
				pDC->SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 0, 255));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_blue);
			else if (res< m_blmne.X_AL)
				pDC->SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 0, 255));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_blue);
			else if (res < m_blmne.X_LMU)
				pDC->SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 0, 255));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_blue);
			else if (res < m_blmne.X_LMD)
			{
				if ((m_blmne.X_LMD - res*m_blmne.Y_NL) >(m_blmne.X_LMD - m_blmne.X_LMU)*scatter)
					pDC->SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter * LMNE_HEIGHT / 255, RGB(0, 0, 255));
				//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter * LMNE_HEIGHT / 255, COLOR_blue);
				else
					pDC->SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter* LMNE_HEIGHT / 255, RGB(230, 30, 70));
				//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter* LMNE_HEIGHT / 255, COLOR_magenta);
			}
			else if (res < m_blmne.X_RM)
				pDC->SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(230, 30, 70));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_magenta);
			else
				pDC->SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(230, 30, 70));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_magenta);
		}
	}
}

//����lmne�������
void CQualityTestView::PrintLMNEChart(qcresult_info *qcresultdata)
{
	CRect rect;
	CWnd* pWnd = GetDlgItem(IDC_CHART);
	pWnd->GetClientRect(&rect); // ��ȡ�ؼ���Ļ����

	CDC* pDC = pWnd->GetDC();
	pDC->SelectStockObject(WHITE_BRUSH);
	pDC->Rectangle(rect);
	CPen cpen, pen;
	pen.CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	pDC->SelectObject(&pen);
	pDC->SetViewportOrg(0, 0);
	pDC->LineTo(0, rect.Height());
	pDC->LineTo(rect.Width(), rect.Height());
	pDC->LineTo(rect.Width(), 0);
	pDC->LineTo(0, 0);
	pen.~CPen();
	pen.CreatePen(PS_SOLID, 1, RGB(96, 96, 96));
	pDC->SelectObject(&pen);
	pDC->SetViewportOrg(0, rect.Height());
	pDC->LineTo(255, 0);
	pDC->LineTo(255, -255);
	pDC->LineTo(0, -255);
	pDC->LineTo(0, 0);
	pDC->TextOut(0, -280, "LMNE:");
	pDC->MoveTo(255, 0);
	pDC->LineTo(265, 0);
	pDC->LineTo(265, -255);
	pDC->LineTo(255, -255);
	unsigned char i;
	int 	x1, x2, y1, y2;
	B_LMNE		m_blmne;
	double		coe_w = LMNE_WIDTH / 255.0;
	double		coe_h = LMNE_HEIGHT / 255.0;

	//if (qcresultdata.coeoflmne > 1.3)
	//	qcresultdata.coeoflmne = 1.3;
	//else if (qcresultdata.coeoflmne < 0.7)
	//	qcresultdata.coeoflmne = 0.7;

	//Init_B_LMNE(qcresultdata.coeoflmne, &m_blmne);
	Init_B_LMNE(1, &m_blmne);
	//------------------------------------------------
	//LMNE
	//line 1 (NOL,0)->(NOL,NL)
	x1 = m_blmne.X_NOL * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM;
	x2 = x1;
	y2 = LMNE_BOTTOM - m_blmne.Y_NL * coe_h;
	pDC->MoveTo(x1, y1);
	pDC->LineTo(x2, y2);

	//line 2 (NON,NL)->(NON,NE)
	x1 = m_blmne.X_NON * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_NL * coe_h;
	x2 = x1;
	y2 = LMNE_BOTTOM - m_blmne.Y_NE * coe_h;
	pDC->MoveTo(x1, y1);
	pDC->LineTo(x2, y2);
	//line 3 (LL,0)->(LL,NL)
	x1 = m_blmne.X_LL * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM;
	x2 = x1;
	y2 = LMNE_BOTTOM - m_blmne.Y_NL * coe_h;
	for (i = 0; i * 3 < y1 - y2;)
	{
		pDC->MoveTo(x1, y2 + i * 3);
		pDC->LineTo(x1, y2 + i * 3 + 3);
		i += 2;	// ....  ....  ....
	}
	//line 4 (LN,NL)->(LN,NE)
	x1 = m_blmne.X_LN * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_NL * coe_h;
	x2 = x1;
	y2 = LMNE_BOTTOM - m_blmne.Y_NE * coe_h;
	for (i = 0; i * 3 < y1 - y2;)
	{
		pDC->MoveTo(x1, y2 + i * 3);
		pDC->LineTo(x1, y2 + i * 3 + 3);
		i += 2;
	}

	//line 5 (NOE,NE)->(NOE,256)
	x1 = m_blmne.X_NOE*coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_NE*coe_h;
	x2 = x1;
	y2 = LMNE_BOTTOM - LMNE_HEIGHT;
	pDC->MoveTo(x1, y1);
	pDC->LineTo(x2, y2);

	//line 6/10 (LMN,NL)->(MN,RMN)
	x1 = m_blmne.X_LMN * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_NL * coe_h;
	x2 = m_blmne.X_MN * coe_w + LMNE_LEFT;
	y2 = LMNE_BOTTOM - m_blmne.Y_RMN * coe_h;
	pDC->MoveTo(x1, y1);
	pDC->LineTo(x2, y2);

	//line 7 (AL,0)->(AL,NL)
	x1 = m_blmne.X_AL * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM;
	x2 = x1;
	y2 = LMNE_BOTTOM - m_blmne.Y_NL*coe_h;
	for (i = 0; i * 3 < y1 - y2;)
	{
		pDC->MoveTo(x1, y2 + i * 3);
		pDC->LineTo(x1, y2 + i * 3 + 3);
		i += 2;
	}

	//line 8/9 (LMU,NL)->(LMD,0)
	x1 = m_blmne.X_LMU * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_NL * coe_h;
	x2 = m_blmne.X_LMD * coe_w + LMNE_LEFT;
	y2 = LMNE_BOTTOM;
	pDC->MoveTo(x1, y1);
	pDC->LineTo(x2, y2);

	//line 11 (RM,0)->(RM,RMN)
	x1 = m_blmne.X_RM * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM;
	x2 = x1;
	y2 = LMNE_BOTTOM - m_blmne.Y_RMN * coe_h;
	pDC->MoveTo(x1, y1);
	pDC->LineTo(x2, y2);

	//line 12 (RN,RMN)->(RN,NE)
	x1 = m_blmne.X_RN * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_RMN * coe_h;
	x2 = x1;
	y2 = LMNE_BOTTOM - m_blmne.Y_NE * coe_h;
	pDC->MoveTo(x1, y1);
	pDC->LineTo(x2, y2);

	//line 13 (NOL,NL)->(LMU,NL)
	x1 = m_blmne.X_NOL * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_NL * coe_h;
	x2 = m_blmne.X_LMU * coe_w + LMNE_LEFT;
	y2 = y1;
	pDC->MoveTo(x1, y1);
	pDC->LineTo(x2, y2);

	//line 14 (MN,RMN)->(256,RMN)
	x1 = m_blmne.X_MN * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_RMN * coe_h;
	x2 = LMNE_WIDTH + LMNE_LEFT;
	y2 = y1;
	pDC->MoveTo(x1, y1);
	pDC->LineTo(x2, y2);

	//line 15 (NON,NE)->(256,NE)
	x1 = m_blmne.X_NON * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_NE * coe_h;
	x2 = LMNE_WIDTH + LMNE_LEFT;
	y2 = y1;
	pDC->MoveTo(x1, y1);
	pDC->LineTo(x2, y2);

	//�˴����г���δ���
	LmneGraphPaint(qcresultdata, patientdata.rangetype);
	GetDlgItem(IDC_CHART)->EnableWindow(FALSE);
}

void CQualityTestView::PrintBASOChart(qcresult_info *qcresultdata)
{
	unsigned short int i;
	unsigned char graphbuff[256] = { 0 };


	//------------------------------------------------
	//BASOֱ��ͼ
	CBCGPChartVisualObject* pChart = m_BASOChart.GetChart();
	ASSERT_VALID(pChart);

	pChart->SetChartType(BCGPChartArea, BCGP_CT_SIMPLE);
	pChart->SetChartTitle(_T("BASO"));
	pChart->ShowChartTitle(TRUE, TRUE);
	pChart->SetLegendPosition(BCGPChartLayout::LP_NONE);
	pChart->SetCurveType(BCGPChartFormatSeries::CCT_SPLINE);
	pChart->SetColors((CBCGPChartTheme::ChartTheme)3);//0:��ɫ��1����ɫ��2��īɫ��3����ɫ��4������ɫ��5���Ȼƣ�6�����죻 7��black and yellow ��8����ɫ......

	CBCGPChartSeries* pSeries1 = pChart->CreateSeries(_T("Series 1"));



	//����0x00�����⴦��ȥ��
	for (i = 0; i < 255; i++)	//255����ǽ�����־���������������ʾ
		graphbuff[i] = ((*qcresultdata).basograph[i] - 1);

	//������[0,204]��204����ʾ��ȥ��һЩ�㣬ÿ���Ԫ��ȥ���м�һ����
	for (i = 0; i < 204; i++)
	{
		graphbuff[i] = graphbuff[i + (i + 2) / 4];
		pSeries1->AddDataPoint(graphbuff[i]);
	}

	//SetDefaultLineWidth();
	//SetObjectColors();

	pChart->SetSeriesShadow();

	//AfxMessageBox(_T("2021"));

}

void CQualityTestView::UpdatePrintBASOChart(qcresult_info *qcresultdata)
{	
	/*
	UpdateData();
	unsigned short int i;
	unsigned char graphbuff[256] = { 0 };

	//------------------------------------------------
	//BASOֱ��ͼ
	CBCGPChartVisualObject* pChart = m_BASOChart.GetChart();
	ASSERT_VALID(pChart);
	//CBCGPChartSeries* pSeries1 = pChart->CreateSeries(_T("Series 1"));

	int num = pChart->GetSeriesCount();
	CBCGPChartSeries* pSeries1 = pChart->GetSeries(num - 1);
	pSeries1->RemoveAllDataPoints();
	//����0x00�����⴦��ȥ��
	for (i = 0; i < 255; i++)	//255����ǽ�����־���������������ʾ
		graphbuff[i] = ((*qcresultdata).basograph[i] - 1);

	//������[0,204]��204����ʾ��ȥ��һЩ�㣬ÿ���Ԫ��ȥ���м�һ����
	for (i = 0; i < 204; i++)
	{
		graphbuff[i] = graphbuff[i + (i + 2) / 4];
		pSeries1->AddDataPoint(graphbuff[i]);
	}

	//SetDefaultLineWidth();
	//SetObjectColors();
	pChart->SetSeriesShadow();

	pChart->Redraw();
	*/
	const unsigned char rangetype = 0;
	UpdateData();
	unsigned short int i;
	unsigned char graphbuff[256] = { 0 };
	uchar 		rangeFlag = ' ', doubtFlag = ' ';
	char 		showbuff[9 + 1] = { 0 };	//PLT***->**.*(��λ:10^4uL)������һ���ַ�����

	if ((*qcresultdata).wbcdata.wbc[0] == '*')//δ������
	{
		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%s%.1f", "   ", 10 * atof((*qcresultdata).wbcdata.wbc));
		else
			sprintf(showbuff, "%s%s", "   ", (*qcresultdata).wbcdata.wbc);
		m_WBCList.SetItemText(WBCS - WBCS, 3, (CString)showbuff);

		//5DIFFģʽ�²���ʾ
		if (systemcfg.mode == 0 || systemcfg.mode == 2)
		{
			sprintf(showbuff, "%s%s", "   ", (*qcresultdata).wbcdata.basp);
			m_WBCList.SetItemText(BASOP - WBCS, 3, (CString)showbuff);

			if (systemcfg.unitWBC == 2)
				sprintf(showbuff, "%s%.1f", "   ", 10 * atof((*qcresultdata).wbcdata.bas));
			else
				sprintf(showbuff, "%s%s", "   ", (*qcresultdata).wbcdata.bas);
			m_WBCList.SetItemText(BASOS - WBCS, 3, (CString)showbuff);
		}
	}
	else//���˲���
	{
		/*if (1 == (*qcresultdata).flag_wrp[0])
		doubtFlag = ' ';
		else if (2 == (*qcresultdata).flag_wrp[0])
		doubtFlag = '?';
		else
		doubtFlag = '*';*/

		//WBC
		if (atof((*qcresultdata).wbcdata.wbc) < 0.5)//���Է�Χ���޲���ʾ'?'
		{
			if (systemcfg.unitWBC == 2)
				sprintf(showbuff, "%c%c %.1f", 'L', 'L', 10 * atof((*qcresultdata).wbcdata.wbc));
			else
				sprintf(showbuff, "%c%c %s", 'L', 'L', (*qcresultdata).wbcdata.wbc);
		}
		else if (atof((*qcresultdata).wbcdata.wbc) > 80)//���Է�Χ���޲���ʾ'?'
		{
			if (systemcfg.unitWBC == 2)
				sprintf(showbuff, "%c%c %.1f", 'H', 'H', 10 * atof((*qcresultdata).wbcdata.wbc));
			else
				sprintf(showbuff, "%c%c %s", 'H', 'H', (*qcresultdata).wbcdata.wbc);
		}
		else
		{
			if (atof((*qcresultdata).wbcdata.wbc) < systemcfg.range.normal[rangetype][WBCS])
				rangeFlag = 'L';
			else if (atof((*qcresultdata).wbcdata.wbc) > systemcfg.range.normal[rangetype][WBCS + 28])
				rangeFlag = 'H';
			else
				rangeFlag = ' ';
			if (systemcfg.unitWBC == 2)
				sprintf(showbuff, "%c%c %.1f", rangeFlag, doubtFlag, 10 * atof((*qcresultdata).wbcdata.wbc));
			else
				sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*qcresultdata).wbcdata.wbc);
		}
		m_WBCList.SetItemText(WBCS - WBCS, 3, (CString)showbuff);

		if (systemcfg.mode == 0 || systemcfg.mode == 2)      //5DIFFģʽ�²���ʾ
		{
			//BASOP
			if (atof((*qcresultdata).wbcdata.basp) < systemcfg.range.normal[rangetype][BASOP])
				rangeFlag = 'L';
			else if (atof((*qcresultdata).wbcdata.basp) > systemcfg.range.normal[rangetype][BASOP + 28])
				rangeFlag = 'H';
			else
				rangeFlag = ' ';
			sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*qcresultdata).wbcdata.basp);
			m_WBCList.SetItemText(BASOP - WBCS, 3, (CString)showbuff);
			//BASO
			if (atof((*qcresultdata).wbcdata.bas) < systemcfg.range.normal[rangetype][BASOS])
				rangeFlag = 'L';
			else if (atof((*qcresultdata).wbcdata.bas) > systemcfg.range.normal[rangetype][BASOS + 28])
				rangeFlag = 'H';
			else
				rangeFlag = ' ';
			if (systemcfg.unitWBC == 2)
				sprintf(showbuff, "%c%c %.1f", rangeFlag, doubtFlag, 10 * atof((*qcresultdata).wbcdata.bas));
			else
				sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*qcresultdata).wbcdata.bas);
			m_WBCList.SetItemText(BASOS - WBCS, 3, (CString)showbuff);
		}
	}
	//UpdateWBCBasoFlagBox(qcresultdata);
	//------------------------------------------------
	//BASOֱ��ͼ
	CBCGPChartVisualObject* pChart = m_BASOChart.GetChart();
	ASSERT_VALID(pChart);
	//CBCGPChartSeries* pSeries1 = pChart->CreateSeries(_T("Series 1"));

	int num = pChart->GetSeriesCount();
	CBCGPChartSeries* pSeries1 = pChart->GetSeries(num - 1);
	pSeries1->RemoveAllDataPoints();
	//����0x00�����⴦��ȥ��
	for (i = 0; i < 255; i++)	//255����ǽ�����־���������������ʾ
		graphbuff[i] = (qcresultdata->basograph[i] - 1);

	//������[0,204]��204����ʾ��ȥ��һЩ�㣬ÿ���Ԫ��ȥ���м�һ����
	for (i = 0; i < 204; i++)
	{
		graphbuff[i] = graphbuff[i + (i + 2) / 4];
		pSeries1->AddDataPoint(graphbuff[i]);
	}

	/*SetDefaultLineWidth();
	SetObjectColors();*/
	pChart->SetSeriesShadow();
	pChart->Redraw();

}

void CQualityTestView::PrintRBCChart(qcresult_info *qcresultdata)
{
	unsigned short int i;
	unsigned char graphbuff[256] = { 0 };
	CBCGPChartVisualObject* pChart = m_RBCChart.GetChart();
	ASSERT_VALID(pChart);

	pChart->SetChartType(BCGPChartArea, BCGP_CT_SIMPLE);
	pChart->SetChartTitle(_T("RBC"));
	pChart->ShowChartTitle(TRUE, TRUE);
	pChart->SetLegendPosition(BCGPChartLayout::LP_NONE);
	pChart->SetCurveType(BCGPChartFormatSeries::CCT_SPLINE);
	pChart->SetColors((CBCGPChartTheme::ChartTheme)8);//0:��ɫ��1����ɫ��2��īɫ��3����ɫ��4������ɫ��5���Ȼƣ�6�����죻 7��black and yellow ��8����ɫ......
	//pChart->SetChartFillColor(const CBCGPBrush& 0);
	CBCGPChartSeries* pSeries1 = pChart->CreateSeries("RBC");

	COleDateTime today = COleDateTime::GetCurrentTime();

	for (i = 0; i < 255; i++)	//��ʵ����������ѹ���Ŵ���󣬼���ֵ�Ѿ�С��RBC_HEIGHT<255�ˣ�������ʵrbcgraph���ֽڴ�Ķ���0
		graphbuff[i] = (((*qcresultdata).rbcgraph[(i << 1) + 1] - 1) << 8) + (*qcresultdata).rbcgraph[i << 1] - 1;

	//������[0,204]��204����ʾ��ȥ��һЩ�㣬ÿ���Ԫ��ȥ���м�һ����
	for (i = 0; i < 204; i++)
	{
		graphbuff[i] = graphbuff[i + (i + 2) / 4];
		pSeries1->AddDataPoint(graphbuff[i]);
	}
	//AfxMessageBox(_T("2122"));
	pChart->Redraw();
}
void CQualityTestView::UpdatePrintRBCChart(qcresult_info *qcresultdata)
{
/*	
	UpdateData();
	unsigned short int i;
	unsigned char graphbuff[256] = { 0 };
	CBCGPChartVisualObject* pChart = m_RBCChart.GetChart();
	ASSERT_VALID(pChart);
	//CBCGPChartSeries* pSeries1 = pChart->CreateSeries("RBC");
	int num = pChart->GetSeriesCount();
	CBCGPChartSeries* pSeries1 = pChart->GetSeries(num - 1);
	pSeries1->RemoveAllDataPoints();
	COleDateTime today = COleDateTime::GetCurrentTime();

	for (i = 0; i < 255; i++)	//��ʵ����������ѹ���Ŵ���󣬼���ֵ�Ѿ�С��RBC_HEIGHT<255�ˣ�������ʵrbcgraph���ֽڴ�Ķ���0
		graphbuff[i] = (((*qcresultdata).rbcgraph[(i << 1) + 1] - 1) << 8) + (*qcresultdata).rbcgraph[i << 1] - 1;

	//������[0,204]��204����ʾ��ȥ��һЩ�㣬ÿ���Ԫ��ȥ���м�һ����
	for (i = 0; i < 204; i++)
	{
		graphbuff[i] = graphbuff[i + (i + 2) / 4];
		pSeries1->AddDataPoint(graphbuff[i]);
	}
	pChart->Redraw();
	*/
	//JYP
	const unsigned char rangetype = 0;
	UpdateData();
	unsigned short int i;
	uchar 		rangeFlag = ' ', doubtFlag = ' ';
	char 		showbuff[9 + 1] = { 0 };	//PLT***->**.*(��λ:10^4uL)������һ���ַ�����

	if ((*qcresultdata).rbcdata.rbc[0] == '*')//δ������
	{
		if (systemcfg.unitRBC == 2)
			sprintf(showbuff, "%s%.0f", "   ", 100 * atof((*qcresultdata).rbcdata.rbc));
		else
			sprintf(showbuff, "%s%s", "   ", (*qcresultdata).rbcdata.rbc);
		m_RBCList.SetItemText(RBCS - RBCS, 3, (CString)showbuff);

		if (systemcfg.unitHGB == 1)
			sprintf(showbuff, "%s%.2f", "   ", atof((*qcresultdata).rbcdata.hgb) / 10);
		else if (systemcfg.unitHGB == 2)
			sprintf(showbuff, "%s%.2f", "   ", atof((*qcresultdata).rbcdata.hgb) / 68);	//68=68000/1000(Ѫ�쵰�׵���Է����������ü����õ�68)    68000 FDparam
		else
			sprintf(showbuff, "%s%s", "   ", (*qcresultdata).rbcdata.hgb);
		m_RBCList.SetItemText(HGBS - RBCS, 3, (CString)showbuff);

		sprintf(showbuff, "%s%s", "   ", (*qcresultdata).rbcdata.hct);
		m_RBCList.SetItemText(HCTS - RBCS, 3, (CString)showbuff);
		sprintf(showbuff, "%s%s", "   ", (*qcresultdata).rbcdata.mcv);
		m_RBCList.SetItemText(MCVS - RBCS, 3, (CString)showbuff);

		if (systemcfg.unitMCH == 1)
			sprintf(showbuff, "%s%.2f", "   ", atof((*qcresultdata).rbcdata.mch) / 68);
		else
			sprintf(showbuff, "%s%s", "   ", (*qcresultdata).rbcdata.mch);
		m_RBCList.SetItemText(MCHS - RBCS, 3, (CString)showbuff);

		if (systemcfg.unitMCHC == 1)
			sprintf(showbuff, "%s%.2f", "   ", atof((*qcresultdata).rbcdata.mchc) / 10);
		else if (systemcfg.unitMCHC == 2)
			sprintf(showbuff, "%s%.2f", "   ", atof((*qcresultdata).rbcdata.mchc) / 68);
		else
			sprintf(showbuff, "%s%s", "   ", (*qcresultdata).rbcdata.mchc);
		m_RBCList.SetItemText(MCHCS - RBCS, 3, (CString)showbuff);
		sprintf(showbuff, "%s%s", "   ", (*qcresultdata).rbcdata.rdw);
		m_RBCList.SetItemText(RDWCVS - RBCS, 3, (CString)showbuff);
		/*sprintf(showbuff, "%s%s", "   ", (*qcresultdata).rbcdata.rdwsd);
		m_RBCList.SetItemText(RDWSDS - RBCS, 3, (CString)showbuff);*/
	}
	else//���˲���
	{
		////if(1 == count_rbc_flag)
		//if (1 == (*qcresultdata).flag_wrp[1])
		//	doubtFlag = ' ';
		////else if(2 == count_rbc_flag)
		//else if (2 == (*qcresultdata).flag_wrp[1])
		//	doubtFlag = '?';
		//else
		//	doubtFlag = '*';

		//RBC
		if (atof((*qcresultdata).rbcdata.rbc) < 0.2)
		{
			if (systemcfg.unitRBC == 2)
				sprintf(showbuff, "%c%c %.0f", 'L', 'L', 100 * atof((*qcresultdata).rbcdata.rbc));
			else
				sprintf(showbuff, "%c%c %s", 'L', 'L', (*qcresultdata).rbcdata.rbc);
		}
		else if (atof((*qcresultdata).rbcdata.rbc) > 7.5)
		{
			if (systemcfg.unitRBC == 2)
				sprintf(showbuff, "%c%c %.0f", 'H', 'H', 100 * atof((*qcresultdata).rbcdata.rbc));
			else
				sprintf(showbuff, "%c%c %s", 'H', 'H', (*qcresultdata).rbcdata.rbc);
		}
		else
		{
			if (atof((*qcresultdata).rbcdata.rbc) < systemcfg.range.normal[rangetype][RBCS])
				rangeFlag = 'L';
			else if (atof((*qcresultdata).rbcdata.rbc) > systemcfg.range.normal[rangetype][RBCS + 28])
				rangeFlag = 'H';
			else
				rangeFlag = ' ';
			if (systemcfg.unitRBC == 2)
				sprintf(showbuff, "%c%c %.0f", rangeFlag, doubtFlag, 100 * atof((*qcresultdata).rbcdata.rbc));
			else
				sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*qcresultdata).rbcdata.rbc);
		}
		m_RBCList.SetItemText(RBCS - RBCS, 3, (CString)showbuff);
		//HGB
		if (atof((*qcresultdata).rbcdata.hgb) < 25)
		{
			if (systemcfg.unitHGB == 1)
				sprintf(showbuff, "%c%c %.2f", 'L', 'L', atof((*qcresultdata).rbcdata.hgb) / 10);
			else if (systemcfg.unitHGB == 2)
				sprintf(showbuff, "%c%c %.2f", 'L', 'L', atof((*qcresultdata).rbcdata.hgb) / 68);
			else
				sprintf(showbuff, "%c%c %s", 'L', 'L', (*qcresultdata).rbcdata.hgb);
		}
		else if (atof((*qcresultdata).rbcdata.hgb) > 230)
		{
			if (systemcfg.unitHGB == 1)
				sprintf(showbuff, "%c%c %.2f", 'H', 'H', atof((*qcresultdata).rbcdata.hgb) / 10);
			else if (systemcfg.unitHGB == 2)
				sprintf(showbuff, "%c%c %.2f", 'H', 'H', atof((*qcresultdata).rbcdata.hgb) / 68);
			else
				sprintf(showbuff, "%c%c %s", 'H', 'H', (*qcresultdata).rbcdata.hgb);
		}
		else
		{
			if (atof((*qcresultdata).rbcdata.hgb) < systemcfg.range.normal[rangetype][HGBS])
				rangeFlag = 'L';
			else if (atof((*qcresultdata).rbcdata.hgb) > systemcfg.range.normal[rangetype][HGBS + 28])
				rangeFlag = 'H';
			else
				rangeFlag = ' ';
			if (systemcfg.unitHGB == 1)
				sprintf(showbuff, "%c%c %.2f", rangeFlag, doubtFlag, atof((*qcresultdata).rbcdata.hgb) / 10);
			else if (systemcfg.unitHGB == 2)
				sprintf(showbuff, "%c%c %.2f", rangeFlag, doubtFlag, atof((*qcresultdata).rbcdata.hgb) / 68);
			else
				sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*qcresultdata).rbcdata.hgb);
		}
		m_RBCList.SetItemText(HGBS - RBCS, 3, (CString)showbuff);
		//HCT
		if (atof((*qcresultdata).rbcdata.hct) < 11.6)
		{
			sprintf(showbuff, "%c%c %s", 'L', 'L', (*qcresultdata).rbcdata.hct);
		}
		else if (atof((*qcresultdata).rbcdata.hct) > 55)
		{
			sprintf(showbuff, "%c%c %s", 'H', 'H', (*qcresultdata).rbcdata.hct);
		}
		else
		{
			if (atof((*qcresultdata).rbcdata.hct) < systemcfg.range.normal[rangetype][HCTS])
				rangeFlag = 'L';
			else if (atof((*qcresultdata).rbcdata.hct) > systemcfg.range.normal[rangetype][HCTS + 28])
				rangeFlag = 'H';
			else
				rangeFlag = ' ';
			sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*qcresultdata).rbcdata.hct);
		}
		m_RBCList.SetItemText(HCTS - RBCS, 3, (CString)showbuff);
		//MCV
		if (atof((*qcresultdata).rbcdata.mcv) < systemcfg.range.normal[rangetype][MCVS])
			rangeFlag = 'L';
		else if (atof((*qcresultdata).rbcdata.mcv) > systemcfg.range.normal[rangetype][MCVS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*qcresultdata).rbcdata.mcv);
		m_RBCList.SetItemText(MCVS - RBCS, 3, (CString)showbuff);
		//MCH
		if (atof((*qcresultdata).rbcdata.mch) < systemcfg.range.normal[rangetype][MCHS])
			rangeFlag = 'L';
		else if (atof((*qcresultdata).rbcdata.mch) > systemcfg.range.normal[rangetype][MCHS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		if (systemcfg.unitMCH == 1)
			sprintf(showbuff, "%c%c %.2f", rangeFlag, doubtFlag, atof((*qcresultdata).rbcdata.mch) / 68);
		else
			sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*qcresultdata).rbcdata.mch);
		m_RBCList.SetItemText(MCHS - RBCS, 3, (CString)showbuff);
		//MCHC
		if (atof((*qcresultdata).rbcdata.mchc) < systemcfg.range.normal[rangetype][MCHCS])
			rangeFlag = 'L';
		else if (atof((*qcresultdata).rbcdata.mchc) > systemcfg.range.normal[rangetype][MCHCS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		if (systemcfg.unitMCHC == 1)
			sprintf(showbuff, "%c%c %.2f", rangeFlag, doubtFlag, atof((*qcresultdata).rbcdata.mchc) / 10);
		else if (systemcfg.unitMCHC == 2)
			sprintf(showbuff, "%c%c %.2f", rangeFlag, doubtFlag, atof((*qcresultdata).rbcdata.mchc) / 68);
		else
			sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*qcresultdata).rbcdata.mchc);
		m_RBCList.SetItemText(MCHCS - RBCS, 3, (CString)showbuff);
		//RDW-CV
		if (atof((*qcresultdata).rbcdata.rdw) < systemcfg.range.normal[rangetype][RDWCVS])
			rangeFlag = 'L';
		else if (atof((*qcresultdata).rbcdata.rdw) > systemcfg.range.normal[rangetype][RDWCVS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*qcresultdata).rbcdata.rdw);
		m_RBCList.SetItemText(RDWCVS - RBCS, 3, (CString)showbuff);
		////RDW-SD
		//if (atof((*qcresultdata).rbcdata.rdwsd) < systemcfg.range.normal[rangetype][RDWSDS])
		//	rangeFlag = 'L';
		//else if (atof((*qcresultdata).rbcdata.rdwsd) > systemcfg.range.normal[rangetype][RDWSDS + 28])
		//	rangeFlag = 'H';
		//else
		//	rangeFlag = ' ';
		//sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*qcresultdata).rbcdata.rdwsd);
		//m_RBCList.SetItemText(RDWSDS - RBCS, 3, (CString)showbuff);
	}
	//UpdateRBCFlagBox(qcresultdata);

	//RBCֱ��ͼ
	unsigned char graphbuff[256] = { 0 };
	CBCGPChartVisualObject* pChart = m_RBCChart.GetChart();
	ASSERT_VALID(pChart);
	//CBCGPChartSeries* pSeries1 = pChart->CreateSeries("RBC");
	int num = pChart->GetSeriesCount();
	CBCGPChartSeries* pSeries1 = pChart->GetSeries(num - 1);
	pSeries1->RemoveAllDataPoints();
	COleDateTime today = COleDateTime::GetCurrentTime();

	for (i = 0; i < 255; i++)	//��ʵ����������ѹ���Ŵ���󣬼���ֵ�Ѿ�С��RBC_HEIGHT<255�ˣ�������ʵrbcgraph���ֽڴ�Ķ���0
		graphbuff[i] = ((qcresultdata->rbcgraph[(i << 1) + 1] - 1) << 8) + qcresultdata->rbcgraph[i << 1] - 1;

	//������[0,204]��204����ʾ��ȥ��һЩ�㣬ÿ���Ԫ��ȥ���м�һ����
	for (i = 0; i < 204; i++)
	{
		graphbuff[i] = graphbuff[i + (i + 2) / 4];
		pSeries1->AddDataPoint(graphbuff[i]);
	}
	//UpdateRBCFlagBox(qcresultdata);

	pChart->Redraw();

}
void CQualityTestView::PrintPLTChart(qcresult_info *qcresultdata)
{
/*	unsigned short int i;
	unsigned char graphbuff[256] = { 0 };
	CBCGPChartVisualObject* pChart = m_PLTChart.GetChart();
	ASSERT_VALID(pChart);

	pChart->SetChartType(BCGPChartArea, BCGP_CT_SIMPLE);
	pChart->SetChartTitle(_T("BASO"));
	pChart->ShowChartTitle(TRUE, TRUE);
	pChart->SetLegendPosition(BCGPChartLayout::LP_NONE);
	pChart->SetCurveType(BCGPChartFormatSeries::CCT_SPLINE);
	pChart->SetColors((CBCGPChartTheme::ChartTheme)5);//0:��ɫ��1����ɫ��2��īɫ��3����ɫ��4������ɫ��5���Ȼƣ�6�����죻 7��black and yellow ��8����ɫ......

	CBCGPChartSeries* pSeries1 = pChart->CreateSeries(_T("Series 1"));

	//����0x00�����⴦��ȥ��		
	for (i = 0; i < 255; i++)
		graphbuff[i] = (*qcresultdata).pltgraph[i] - 1;

	for (i = 0; i < 204; i++)
	{
		pSeries1->AddDataPoint(graphbuff[i]);
	}

	//pSeries1->AddDataPoint(0.);
	//pSeries1->AddDataPoint(2.);
	//pSeries1->AddDataPoint(4.);
	//pSeries1->AddDataPoint(7.);
	//pSeries1->AddDataPoint(6.);
	//pSeries1->AddDataPoint(3.);
	//pSeries1->AddDataPoint(1.);
	//pSeries1->AddDataPoint(0.);

	//SetDefaultLineWidth();
	//SetObjectColors();

	pChart->SetSeriesShadow();
	//AfxMessageBox(_T("2223"));
	pChart->Redraw();*/

	unsigned short int i;
	unsigned char graphbuff[256] = { 0 };
	CBCGPChartVisualObject* pChart = m_PLTChart.GetChart();
	ASSERT_VALID(pChart);

	pChart->SetChartType(BCGPChartArea, BCGP_CT_SIMPLE);
	pChart->SetChartTitle(_T("PLT"));
	pChart->ShowChartTitle(TRUE, TRUE);
	pChart->SetLegendPosition(BCGPChartLayout::LP_NONE);
	pChart->SetCurveType(BCGPChartFormatSeries::CCT_SPLINE);
	pChart->SetColors((CBCGPChartTheme::ChartTheme)5);//0:��ɫ��1����ɫ��2��īɫ��3����ɫ��4������ɫ��5���Ȼƣ�6�����죻 7��black and yellow ��8����ɫ......

	CBCGPChartSeries* pSeries1 = pChart->CreateSeries(_T("Series 1"));

	//����0x00�����⴦��ȥ��		
	for (i = 0; i < 255; i++)
		graphbuff[i] = (*qcresultdata).pltgraph[i] - 1;

	for (i = 0; i < 204; i++)
	{
		pSeries1->AddDataPoint(graphbuff[i]);
	}

	//pSeries1->AddDataPoint(0.);
	//pSeries1->AddDataPoint(2.);
	//pSeries1->AddDataPoint(4.);
	//pSeries1->AddDataPoint(7.);
	//pSeries1->AddDataPoint(6.);
	//pSeries1->AddDataPoint(3.);
	//pSeries1->AddDataPoint(1.);
	//pSeries1->AddDataPoint(0.);

	//SetDefaultLineWidth();
	//SetObjectColors();

	pChart->SetSeriesShadow();
	//AfxMessageBox(_T("2223"));
	pChart->Redraw();
}
void CQualityTestView::UpdatePrintPLTChart(qcresult_info *qcresultdata)
{
	/*
	UpdateData();
	unsigned short int i;
	unsigned char graphbuff[256] = { 0 };
	CBCGPChartVisualObject* pChart = m_PLTChart.GetChart();
	ASSERT_VALID(pChart);

	//CBCGPChartSeries* pSeries1 = pChart->CreateSeries(_T("Series 1"));
	int num = pChart->GetSeriesCount();
	CBCGPChartSeries* pSeries1 = pChart->GetSeries(num - 1);
	pSeries1->RemoveAllDataPoints();
	//����0x00�����⴦��ȥ��		
	for (i = 0; i < 255; i++)
		graphbuff[i] = (*qcresultdata).pltgraph[i] - 1;

	for (i = 0; i < 204; i++)
	{
		pSeries1->AddDataPoint(graphbuff[i]);
	}

	//pSeries1->AddDataPoint(0.);
	//pSeries1->AddDataPoint(2.);
	//pSeries1->AddDataPoint(4.);
	//pSeries1->AddDataPoint(7.);
	//pSeries1->AddDataPoint(6.);
	//pSeries1->AddDataPoint(3.);
	//pSeries1->AddDataPoint(1.);
	//pSeries1->AddDataPoint(0.);

	//SetDefaultLineWidth();
	//SetObjectColors();

	pChart->SetSeriesShadow();
	pChart->Redraw();
	*/

	const unsigned char rangetype = 0;
	UpdateData();
	unsigned short int i;
	uchar 		rangeFlag = ' ', doubtFlag = ' ';
	char 		showbuff[9 + 1] = { 0 };	//PLT***->**.*(��λ:10^4uL)������һ���ַ�����

	unsigned char graphbuff[256] = { 0 };
	CBCGPChartVisualObject* pChart = m_PLTChart.GetChart();
	ASSERT_VALID(pChart);

	//CBCGPChartSeries* pSeries1 = pChart->CreateSeries(_T("Series 1"));
	int num = pChart->GetSeriesCount();
	CBCGPChartSeries* pSeries1 = pChart->GetSeries(num - 1);
	pSeries1->RemoveAllDataPoints();
	//����0x00�����⴦��ȥ��		
	for (i = 0; i < 255; i++)
		graphbuff[i] = qcresultdata->pltgraph[i] - 1;

	for (i = 0; i < 204; i++)
	{
		pSeries1->AddDataPoint(graphbuff[i]);
	}

	//SetDefaultLineWidth();
	//SetObjectColors();

	//ZWH 20170221���
	if ((*qcresultdata).pltdata.plt[0] == '*')//δ������
	{
		if (systemcfg.unitPLT == 2)
			sprintf(showbuff, "%s%.1f", "   ", atof((*qcresultdata).pltdata.plt) / 10);
		else
			sprintf(showbuff, "%s%s", "   ", (*qcresultdata).pltdata.plt);
		m_PLTList.SetItemText(PLTS - PLTS, 3, (CString)showbuff);
		sprintf(showbuff, "%s%s", "   ", (*qcresultdata).pltdata.mpv);
		m_PLTList.SetItemText(MPVS - PLTS, 3, (CString)showbuff);
		sprintf(showbuff, "%s%s", "   ", (*qcresultdata).pltdata.pdw);
		m_PLTList.SetItemText(PDWS - PLTS, 3, (CString)showbuff);
		sprintf(showbuff, "%s%s", "   ", (*qcresultdata).pltdata.pct);
		m_PLTList.SetItemText(PCTS - PLTS, 3, (CString)showbuff);
		//sprintf(showbuff, "%s%s", "   ", (*qcresultdata).pltdata.plcr);
		//m_PLTList.SetItemText(PLCRS - PLTS, 3, (CString)showbuff);
	}
	else//���˲���
	{
		////if(1 == count_plt_flag)
		//if (1 == (*qcresultdata).flag_wrp[2])
		//	doubtFlag = ' ';
		////else if(2 == count_plt_flag)
		//else if (2 == (*qcresultdata).flag_wrp[2])
		//	doubtFlag = '?';
		//else
		//	doubtFlag = '*';
		//PLT
		if (atof((*qcresultdata).pltdata.plt) < 10)
		{
			if (systemcfg.unitPLT == 2)
				sprintf(showbuff, "%c%c %.1f", 'L', 'L', atof((*qcresultdata).pltdata.plt) / 10);
			else
				sprintf(showbuff, "%c%c %s", 'L', 'L', (*qcresultdata).pltdata.plt);
		}
		else if (atof((*qcresultdata).pltdata.plt) > 1000)
		{
			if (systemcfg.unitPLT == 2)
				sprintf(showbuff, "%c%c %.1f", 'H', 'H', atof((*qcresultdata).pltdata.plt) / 10);
			else
				sprintf(showbuff, "%c%c %s", 'H', 'H', (*qcresultdata).pltdata.plt);
		}
		else
		{
			if (atof((*qcresultdata).pltdata.plt) < systemcfg.range.normal[rangetype][PLTS])
				rangeFlag = 'L';
			else if (atof((*qcresultdata).pltdata.plt) > systemcfg.range.normal[rangetype][PLTS + 28])
				rangeFlag = 'H';
			else
				rangeFlag = ' ';
			if (systemcfg.unitPLT == 2)
				sprintf(showbuff, "%c%c %.1f", rangeFlag, doubtFlag, atof((*qcresultdata).pltdata.plt) / 10);
			else
				sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*qcresultdata).pltdata.plt);
		}
		m_PLTList.SetItemText(PLTS - 23, 3, (CString)showbuff);
		//MPV
		if (atof((*qcresultdata).pltdata.mpv) < systemcfg.range.normal[rangetype][MPVS])
			rangeFlag = 'L';
		else if (atof((*qcresultdata).pltdata.mpv) > systemcfg.range.normal[rangetype][MPVS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*qcresultdata).pltdata.mpv);
		m_PLTList.SetItemText(MPVS - 23, 3, (CString)showbuff);
		//PDW
		if (atof((*qcresultdata).pltdata.pdw) < systemcfg.range.normal[rangetype][PDWS])
			rangeFlag = 'L';
		else if (atof((*qcresultdata).pltdata.pdw) > systemcfg.range.normal[rangetype][PDWS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*qcresultdata).pltdata.pdw);
		m_PLTList.SetItemText(PDWS - 23, 3, (CString)showbuff);
		//PCT
		if (atof((*qcresultdata).pltdata.pct) < systemcfg.range.normal[rangetype][PCTS])
			rangeFlag = 'L';
		else if (atof((*qcresultdata).pltdata.pct) > systemcfg.range.normal[rangetype][PCTS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*qcresultdata).pltdata.pct);
		m_PLTList.SetItemText(PCTS - 23, 3, (CString)showbuff);
		////PLCR
		//if (atof((*qcresultdata).pltdata.plcr) < systemcfg.range.normal[rangetype][PLCRS])
		//	rangeFlag = 'L';
		//else if (atof((*qcresultdata).pltdata.plcr) > systemcfg.range.normal[rangetype][PLCRS + 28])
		//	rangeFlag = 'H';
		//else
		//	rangeFlag = ' ';
		//sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*qcresultdata).pltdata.plcr);
		//m_PLTList.SetItemText(PLCRS - 23, 3, (CString)showbuff);
	}
	//UpdatePLTFlagBox(qcresultdata);

	pChart->SetSeriesShadow();
	pChart->Redraw();

}
void CQualityTestView::PrintPieChart()
{
	unsigned short int i;
	m_PieChart.EnableTooltip();

	CBCGPChartVisualObject* pChart = m_PieChart.GetChart();
	ASSERT_VALID(pChart);
	pChart->CleanUpChartData();

	pChart->SetChartType(BCGPChartPie3D);

	//m_wndRotate.GetRotationObject()->SetAutorepeatMode(100);
	//m_wndRotate.GetRotationObject()->SetColorTheme(CBCGPRotationObject::BCGP_COLOR_THEME_VISUAL_MANAGER);

	//pChart->SetChartTitle(_T(" Proportion of blood cells"));
	pChart->SetLegendPosition(BCGPChartLayout::LP_NONE);

	pChart->AddChartData(_T("NEU%"), 6700);
	pChart->AddChartData(_T("MONO%"), 4500);
	pChart->AddChartData(_T("EOS%"), 2200);
	pChart->AddChartData(_T("ALY%"), 1500);
	pChart->AddChartData(_T("LYM%"), 1400);

	pChart->ShowDataLabels(TRUE);
	int m_nDataLabelPosition = 0;
	BCGPChartDataLabelOptions dataLabelOptions = pChart->GetDataLabelOptions();
	dataLabelOptions.m_position = (BCGPChartDataLabelOptions::LabelPosition)m_nDataLabelPosition;
	dataLabelOptions.m_bUnderlineDataLabel = TRUE;
	dataLabelOptions.m_content = BCGPChartDataLabelOptions::LC_PIE_NAME_PERCENTAGE; //:BCGPChartDataLabelOptions::LC_DP_INDEX;
	dataLabelOptions.m_bDrawDataLabelBorder = dataLabelOptions.m_position != BCGPChartDataLabelOptions::LP_DEFAULT_POS && dataLabelOptions.m_position != BCGPChartDataLabelOptions::LP_OUTSIDE_END;

	pChart->SetDataLabelsOptions(dataLabelOptions);
	//AfxMessageBox(_T("2324"));
	pChart->Redraw();
}
void CQualityTestView::UpdatePrintPieChart()
{
	UpdateData();
	m_PieChart.EnableTooltip();

	CBCGPChartVisualObject* pChart = m_PieChart.GetChart();

	pChart->CleanUpChartData();//�����һ�ε����ݣ�����ͼ����ص�

	ASSERT_VALID(pChart);
	pChart->SetChartType(BCGPChartPie3D);
	pChart->SetLegendPosition(BCGPChartLayout::LP_NONE);
	pChart->CleanUpChartData();
	pChart->AddChartData(_T("NEU%"), 5700);
	pChart->AddChartData(_T("MONO%"), 4500);
	pChart->AddChartData(_T("EOS%"), 2200);
	pChart->AddChartData(_T("ALY%"), 1500);
	pChart->AddChartData(_T("LYM%"), 2400);

	pChart->ShowDataLabels(TRUE);
	int m_nDataLabelPosition = 0;
	BCGPChartDataLabelOptions dataLabelOptions = pChart->GetDataLabelOptions();
	dataLabelOptions.m_position = (BCGPChartDataLabelOptions::LabelPosition)m_nDataLabelPosition;
	dataLabelOptions.m_bUnderlineDataLabel = TRUE;
	dataLabelOptions.m_content = BCGPChartDataLabelOptions::LC_PIE_NAME_PERCENTAGE; //:BCGPChartDataLabelOptions::LC_DP_INDEX;
	dataLabelOptions.m_bDrawDataLabelBorder = dataLabelOptions.m_position != BCGPChartDataLabelOptions::LP_DEFAULT_POS && dataLabelOptions.m_position != BCGPChartDataLabelOptions::LP_OUTSIDE_END;

	pChart->SetDataLabelsOptions(dataLabelOptions);

	pChart->Redraw();
}

BOOL CQualityTestView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	OnPaint();

	return CDialogEx::OnEraseBkgnd(pDC);
}

afx_msg LRESULT CQualityTestView::OnQualitytest(WPARAM wParam, LPARAM lParam)
{
	MessageBox(L"QC test in QualityTestView");
	{
		if (0 == QcLjFileExistEdit)
		{
			if (systemcfg.language == CHINESE)
				MessageBox(L"��Ӧ�ʿ��ļ�δ�༭!", L"����!");
			//else if (systemcfg.language == ENGLISH)
			//	CreateWarningBoxNonCHDlg(hDlg, "Refered QC File has not been edited", "Warning!");
			return 0;
		}
		key_status = FALSE;
		initQcLjData();	//���ݳ�ʼ��
		DSP_status = Busy;
		sdata_cmd[0] = SPI_CMD_CBC5DIFF_MODE;
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		//statusShowMess = 1;
		//��ʾ����
		SetTimer(SLEEP_TIMER1, 30000, 0);
	}
	return 0;
}

void CQualityTestView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent){
		case SLEEP_TIMER1:
		{
			KillTimer(SLEEP_TIMER1);
			TRACE("MSG_TIMER:SLEEP_TIMER1 is due -------------#\n");
			PC_status = WAITING_DATA;
			SetTimer(POLLTIME, SPI_POLL_TIME1000, 0);
			break;
			//if (0 == QcLjFileExistEdit)
			//{
			//	if (systemcfg.language == CHINESE)
			//		MessageBox(L"��Ӧ�ʿ��ļ�δ�༭!",L"����!");
			//	//else if (systemcfg.language == ENGLISH)
			//	//	CreateWarningBoxNonCHDlg(hDlg, "Refered QC File has not been edited", "Warning!");
			//	return;
			//}
			//key_status = FALSE;
			//initQcLjData();	//���ݳ�ʼ��
			//DSP_status = Busy;
			//sdata_cmd[0] = SPI_CMD_CBC5DIFF_MODE;
			//PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
			////statusShowMess = 1;
			////��ʾ����
			//SetTimer(SLEEP_TIMER1, 30000,0); 
		}
		case POLLTIME:
		{
			TRACE("MSG_TIMER:POLLTIME is due -------------#\n");

			sdata_cmd[0] =  SPI_CMD_REQDSP_STATUS;	
			PC_SEND_FRAME(sdata_cmd,SPI_TYPE_CMD);
			PC_RECEIVE_FRAME(rdata_state,SPI_TYPE_STATE);						
			SendMessage(WM_ACKSPI, rdata_state[0], 0);
		}
		default:
			break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CQualityTestView::initQcLjData()//�ʿز��Բ�������26����û�б�Ҫ28���������������̲�һ��
{
	unsigned int i = 0;

	//Ĭ���ַ�Ϊ""
	qcresultdata.row = 0;//�кţ�������֤ĳһ���ʿ��ļ��ļ�¼��������31�򶥳������һ��

	qcresultdata.qctype = Controltype+48;
	qcresultdata.filenum = Controlfile+48;
	qcresultdata.time = 0;
	strcpy(qcresultdata.date, "");

	strcpy(qcresultdata.wbcdata.wbc, "**.**");

	strcpy(qcresultdata.wbcdata.lymp, "**.*");
	strcpy(qcresultdata.wbcdata.neup, "**.*");
	strcpy(qcresultdata.wbcdata.monop, "*.*");
	strcpy(qcresultdata.wbcdata.eosp, "*.*");
	strcpy(qcresultdata.wbcdata.basp, "*.*");
	strcpy(qcresultdata.wbcdata.alyp, "*.*");
	strcpy(qcresultdata.wbcdata.licp, "*.*");

	strcpy(qcresultdata.wbcdata.lym, "*.**");
	strcpy(qcresultdata.wbcdata.neu, "*.**");
	strcpy(qcresultdata.wbcdata.mono, "*.**");
	strcpy(qcresultdata.wbcdata.eos, "*.**");
	strcpy(qcresultdata.wbcdata.bas, "*.**");
	strcpy(qcresultdata.wbcdata.aly, "*.**");
	strcpy(qcresultdata.wbcdata.lic, "*.**");
	//RBC
	strcpy(qcresultdata.rbcdata.rbc, "*.**");
	strcpy(qcresultdata.rbcdata.hgb, "***.*");
	strcpy(qcresultdata.rbcdata.hct, "**.*");
	strcpy(qcresultdata.rbcdata.mcv, "***.*");
	strcpy(qcresultdata.rbcdata.mch, "**.*");
	strcpy(qcresultdata.rbcdata.mchc, "***.*");
	strcpy(qcresultdata.rbcdata.rdw, "**.*");
	//PLT
	strcpy(qcresultdata.pltdata.plt, "***");
	strcpy(qcresultdata.pltdata.mpv, "**.**");
	strcpy(qcresultdata.pltdata.pdw, "**.*");
	strcpy(qcresultdata.pltdata.pct, "**.**");
	//ɢ��ͼ
	for (i = 0; i < MATRIX_DATA_MAX; i++)
		qcresultdata.lmnegraph[i] = 1;
	//BASOֱ��ͼ
	for (i = 0; i < 256; i++)
		qcresultdata.basograph[i] = 1;
	//RBCֱ��ͼ
	for (i = 0; i < 512; i++)
		qcresultdata.rbcgraph[i] = 1;
	//PLTֱ��ͼ
	for (i = 0; i < 256; i++)
		qcresultdata.pltgraph[i] = 1;
	//���
	for (i = 0; i < 9; i++)
		qcresultdata.lmneflg[i] = 1;
	qcresultdata.basoflg[0] = 1;
	for (i = 0; i < 2; i++)
		qcresultdata.rbcflg[i] = 1;
	for (i = 0; i < 2; i++)
		qcresultdata.pltflg[i] = 1;

}
extern CQualityListView m_QualityListPage;

afx_msg LRESULT CQualityTestView::OnAckspi(WPARAM wParam, LPARAM lParam)
{
	int rowCount;
	switch (wParam)
	{
	case SPI_STATE_DATAISOK:
		if (PC_status != WAITING_DATA)
			break;
		KillTimer(POLLTIME);
		//����BASO  ����
		sdata_cmd[0] = SPI_CMD_REQBASO;
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		PC_RECEIVE_FRAME(qcresultdata.basograph, SPI_TYPE_BASORES);
		//����LMNE  ����
		sdata_cmd[0] = SPI_CMD_REQLMNE;
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		PC_RECEIVE_FRAME(qcresultdata.lmnegraph, SPI_TYPE_LMNERES);
		//����HGB  ����
		sdata_cmd[0] = SPI_CMD_REQHGB;
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		PC_RECEIVE_FRAME(hgbgraph, SPI_TYPE_HGBRES);
		//����RBC ����
		sdata_cmd[0] = SPI_CMD_REQRBC;
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		PC_RECEIVE_FRAME(qcresultdata.rbcgraph, SPI_TYPE_RBCRES);
		//����PLT   ����
		sdata_cmd[0] = SPI_CMD_REQPLT;
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		PC_RECEIVE_FRAME(qcresultdata.pltgraph, SPI_TYPE_PLTRES);

		m_qcDataProcess.QcWbcBasoAnalysis(&qcresultdata);	//�������Թ��̶�����
		m_qcDataProcess.QcLmneAnalysis(&qcresultdata);		//�������BASO��������						
		m_qcDataProcess.QcHgbAnalysis(&qcresultdata);		//�������BASO����ǰ��
		m_qcDataProcess.QcRbcAnalysis(&qcresultdata);
		m_qcDataProcess.QcPltAnalysis(&qcresultdata);

		//���ݿⱣ��	
		rowCount = getqcresultRow();
		TRACE(L"\nqc basograph=");
		for (int i = 0; i < 256;i++)
			TRACE(L"%c ", qcresultdata.basograph[i]);
		TRACE(L"\n");
		if (rowCount >= 31)//����ǰ���һ����¼ɾ��
			DelQcLjXXrResult(Controltype, Controlfile, qcresultdata.row - 31);
		AddQcLjXXrResult(&qcresultdata);//

		//ˢ�±�����
		UpdateData(false);
		UpdateForm(&qcresultdata);
		UpdatePrintChart(&qcresultdata);
		//ˢ���ʿص�����ҳ�桪���ʿ�ͼ���ʿ��б�		
		::PostMessage(m_QualityChartPage, UM_REDRAW, 0, 0);
		::PostMessage(m_QualityListPage, UM_REDRAW, 0, 0);
		

		//�ȴ����̽���
		PC_status = WAITING_TEST_OVER;
		SetTimer( POLLTIME, SPI_POLL_TIME3000,0);
		break;
		//���Թ��̽���
	case SPI_STATE_TESTISOVER:
		PC_status = TEST_OVER;
		KillTimer(POLLTIME);
		DSP_status = Free;
		//ARM_GPIOCMD(EN_GREEN);
		key_status = true;
		TRACE("\nMSG_ACKSPI: Test Proc is over -------------#\n");
		break;
	default:
		break;
	}
	
	return 0;
}

//�������¼��
int CQualityTestView::getqcresultRow()
{
	//���ݿ����ӣ��Ķ���ϴ�
	//���ݿ⴦�������쳣
	CString filename;
	CString	qctypetemp;
	CString qcFileNumtemp;
	int 			rc = 0;
	int minRow,maxRow,rowCount;
	int i = 0;
	filename.Format(_T("appdata.accdb"));
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	_variant_t var;

	qctypetemp.Format(L"%d", Controltype);
	qcFileNumtemp.Format(L"%d", Controlfile);
	CString getQcRes = _T("select min(row),max(row) from qcresultdata where qctype ='") + qctypetemp + "'and filenum ='" + qcFileNumtemp + "';";
	if (-1 == OpenDataBase(filename, m_pDB, m_pRs)){
		MessageBox(L"Open Failure!");
		return false;
	}
	rc=ExeSql(m_pDB, m_pRs, getQcRes);
	
	try{
		if (!m_pRs->BOF){
			m_pRs->MoveFirst();
		}
		else
		{
			TRACE("��������Ϊ��");
			return FALSE;
		}
		minRow = int(m_pRs->GetFields()->GetItem((long)0)->Value);
		maxRow = int(m_pRs->GetFields()->GetItem((long)1)->Value);
		rowCount = maxRow - minRow+1;
		if (0 == maxRow-minRow){
			qcresultdata.row = 1;
		}
		else{
			qcresultdata.row = maxRow + 1;
		}
		TRACE("\n######maxRow=%d\n", maxRow);
	}
	catch (_com_error &e)
	{
		TRACE("getQcResultRow�쳣");
	}
	CloseDataBase(m_pDB, m_pRs);
	return rowCount;

	/************************************/
	//char **		Result_R;
	//int 			nRow_R = 0;
	//int 			nCol_R = 0;
	//int 			rc = 0;
	//char *		zErrMsg = NULL;
	//char *		zStatement = NULL;
	//char 		select_row[] = "select row from qcresultdata where qctype = %d and filenum = %d;";
	//if ((OpenDataBase(DATABASE_PATH, &db)) == -1)
	//	return -1;
	//zStatement = sqlite3_mprintf(select_row, 1, QcLjFileNum);
	//rc = sqlite3_get_table(db, zStatement, &Result_R, &nRow_R, &nCol_R, &zErrMsg);
	//sqlite3_free(zStatement);
	//zStatement = NULL;
	//CloseDataBase(db);
	//if (rc == 0)
	//{
	//	if (nRow_R == 0)//��һ����������
	//		qcresultdata.row = 1;
	//	else
	//		qcresultdata.row = atoi(Result_R[nRow_R*nCol_R]) + 1;	//���һ����¼��Row+1
	//}
	//return 0;
}