// QcXChartView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "QcXChartView.h"
#include "afxdialogex.h"


// CQcXChartView �Ի���

IMPLEMENT_DYNAMIC(CQcXChartView, CDialogEx)

CQcXChartView::CQcXChartView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQcXChartView::IDD, pParent)
{
	curpage = 0;
	isQcXEditExist = 0;
	qcXGraphNum = 0;
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

	for (int i = 0; i < 26; i++)
	{
		upperlimit[i] = 0;
		lowerlimit[i] = 0;
	}

	for (int i = 0; i < 26; i++)
		for (int j = 0; j < 31; j++)
			data[i][j] = -5.0;//��ʼ��Ϊ�������Ա���ͼ��ֻ��ʾ��Ч����
}

CQcXChartView::~CQcXChartView()
{
}

void CQcXChartView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_QC_X_LINECHART, m_QcXLineChart);
	DDX_Control(pDX, IDC_QC_X_LINECHART2, m_QcXLineChart2);
	DDX_Control(pDX, IDC_QC_X_LINECHART3, m_QcXLineChart3);
	DDX_Control(pDX, IDC_QC_X_LINECHART4, m_QcXLineChart4);
	DDX_Control(pDX, IDC_QC_X_MATERIALLIST, m_QcXmaterialInfolist);
}


BEGIN_MESSAGE_MAP(CQcXChartView, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_QC_X_GRAPH_UP, &CQcXChartView::OnQcXGraphUp)
	ON_BN_CLICKED(IDC_QC_X_GRAPH_DOWN, &CQcXChartView::OnQcXGraphDown)
END_MESSAGE_MAP()


// CQcXChartView ��Ϣ�������


void CQcXChartView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
}


BOOL CQcXChartView::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//��ʾ�ʿ����ͺ��ļ���
	CString item_temp, done_temp;
	int nRow, mRow;
	switch (Controltype)
	{
	case 0:
		item_temp.Format(L"L-J�ʿ�ͼ���ļ� %02u��", Controlfile + 1);
		break;
	case 1:
		item_temp.Format(L"X�ʿ�ͼ���ļ� %02u��", Controlfile + 1);
		break;
	case 2:
		item_temp.Format(L"X-R�ʿ�ͼ���ļ� %02u��", Controlfile + 1);
		break;
	default:
		break;
	}
	SetDlgItemText(IDC_QC_X_STATIC0, item_temp);
	GetDlgItem(IDC_QC_X_STATIC0)->SetFont(&textfont);

	curpage = 0;
	//TRACE("\n======ControlType=%d\n",Controltype);
	//TRACE("\n======Controlfile=%d\n", Controlfile);
	//��ѯ�ļ��Ƿ���ڣ�������־λ��λ
	nRow = GetNumDea(Controltype, Controlfile);
	if (nRow == 0)
		isQcXEditExist = 0;
	else
		isQcXEditExist = 1;

	//��ȡ��Ч���ʿؽ������
	if (1 == isQcXEditExist)
	{
		//MessageBox(L"getDetail");
		mRow = GetDetail(Controltype, Controlfile);
		qcXGraphNum = mRow;
		if (mRow > 31)
			qcXGraphNum = 31;
	}
	else{
		qcXGraphNum = 0;
	}
	done_temp.Format(L"����������%d", qcXGraphNum);
	SetDlgItemText(IDC_QC_X_STATIC_DONE, done_temp);

	InitLineChart();
	InitLineChart2();
	InitLineChart3();
	InitLineChart4();
	InitQcXMaterialInfoList();
	UpdateMSC();
	GetDlgItem(IDC_QC_X_GRAPH_UP)->EnableWindow(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


HBRUSH CQcXChartView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_QC_X_STATIC0:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	default:
		break;
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

void CQcXChartView::InitLineChart()
{
	pChart = m_QcXLineChart.GetChart();
	ASSERT_VALID(pChart);

	/*BCGPChartType type =
	(m_Feature == CDemoFeature::BCGP_StackedLine || m_Feature == CDemoFeature::BCGP_StackedLineSpline) ? BCGP_CT_STACKED :
	(m_Feature == CDemoFeature::BCGP_StackedLine100) ?
	BCGP_CT_100STACKED : BCGP_CT_SIMPLE;*/
	BCGPChartType type = BCGP_CT_SIMPLE;
	//BCGPChartType type = BCGP_CT_100STACKED;
	//pChart->RemoveAllChartObjects();
	pChart->CleanUpChartData();

	pChart->SetChartType(BCGPChartLine, type);

	//pChart->SetChartTitle(_T("Furniture Sales"));
	CBCGPChartSeries* pSeries1 = pChart->CreateSeries(_T("�ʿ�ֵ"));
	CBCGPChartSeries* pSeries2 = pChart->CreateSeries(_T("��ֵ����"));
	CBCGPChartSeries* pSeries3 = pChart->CreateSeries(_T("��ֵ����"));

	//CString m_arYears[5] = { "2010", "2011", "2012", "2013", "2014" };
	//pSeries1->AddDataPoint(m_arYears[4], 5.);
	//pSeries1->AddDataPoint(m_arYears[3], 8.);
	//pSeries1->AddDataPoint(m_arYears[2], 12.);
	//pSeries1->AddDataPoint(m_arYears[1], 13.);
	//pSeries1->AddDataPoint(m_arYears[0], 15.);
	//pSeries2->AddDataPoint(9.);
	//pSeries2->AddDataPoint(15.);
	//pSeries2->AddDataPoint(19.);
	//pSeries2->AddDataPoint(21.);
	//pSeries2->AddDataPoint(23.);
	/*	//�˶�Ϊʦ�ִ��룬�����޾�������
	CArray <double, double> m_upperarray, m_lowerarray, m_dataarray;
	m_upperarray.SetSize(31);
	m_lowerarray.SetSize(31);
	m_dataarray.SetSize(31);
	for (int i = 0; i < 31; i++)
	{
	//m_upperarray.SetAtGrow(i, upperlimit[0]);
	m_upperarray.SetAtGrow(i, upperlimit[curpage * 4]);
	m_lowerarray.SetAtGrow(i, lowerlimit[curpage * 4]);
	m_dataarray.SetAtGrow(i, data[curpage * 4][i]);
	}
	//pSeries2->AddDataPoint(upperlimit[0]);
	pSeries1->AddDataPoints(m_dataarray);
	pSeries2->AddDataPoints(m_upperarray);
	pSeries3->AddDataPoints(m_lowerarray);
	*/


	for (int i = 0; i < 31; i++){
		if (data[curpage * 4][i] >= 0)
			pSeries1->AddDataPoint(data[curpage * 4][i]);
		pSeries2->AddDataPoint(upperlimit[curpage * 4]);
		pSeries3->AddDataPoint(lowerlimit[curpage * 4]);
	}


	CBCGPChartAxis* pYAxis = pChart->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
	ASSERT_VALID(pYAxis);

	pYAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_CROSS;
	pYAxis->m_minorTickMarkType = CBCGPChartAxis::TMT_CROSS;

	CBCGPChartAxis* pXAxis = pChart->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
	ASSERT_VALID(pXAxis);

	pXAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_CROSS;
	pXAxis->m_minorTickMarkType = CBCGPChartAxis::TMT_CROSS;

	//if (m_QualityLineChart.GetGraphicsManager()->GetType() == CBCGPGraphicsManager::BCGP_GRAPHICS_MANAGER_GDI)
	//{
	//	m_wndDisplayShadow.EnableWindow(FALSE);
	//	m_wndDisplayShadow.ShowWindow(SW_HIDE);
	//	m_bDisplayShadow = FALSE;
	//}
	OnUpdateChart(1);
}


void CQcXChartView::InitLineChart2()
{
	pChart2 = m_QcXLineChart2.GetChart();
	ASSERT_VALID(pChart2);

	/*BCGPChartType type =
	(m_Feature == CDemoFeature::BCGP_StackedLine || m_Feature == CDemoFeature::BCGP_StackedLineSpline) ? BCGP_CT_STACKED :
	(m_Feature == CDemoFeature::BCGP_StackedLine100) ?
	BCGP_CT_100STACKED : BCGP_CT_SIMPLE;*/
	BCGPChartType type = BCGP_CT_SIMPLE;
	//BCGPChartType type = BCGP_CT_100STACKED;
	pChart2->CleanUpChartData();
	pChart2->SetChartType(BCGPChartLine, type);

	//pChart->SetChartTitle(_T("Furniture Sales"));
	CBCGPChartSeries* pSeries1 = pChart2->CreateSeries(_T("�ʿ�ֵ"));
	CBCGPChartSeries* pSeries2 = pChart2->CreateSeries(_T("��ֵ����"));
	CBCGPChartSeries* pSeries3 = pChart2->CreateSeries(_T("��ֵ����"));

	//CString m_arYears[5] = { "2010", "2011", "2012", "2013", "2014" };
	//pSeries1->AddDataPoint(m_arYears[4], 5.);
	//pSeries1->AddDataPoint(m_arYears[3], 8.);
	//pSeries1->AddDataPoint(m_arYears[2], 12.);
	//pSeries1->AddDataPoint(m_arYears[1], 13.);
	//pSeries1->AddDataPoint(m_arYears[0], 15.);

	CArray <double, double> m_upperarray, m_lowerarray, m_dataarray;
	for (int i = 0; i < 31; i++){
		if (data[curpage * 4][i] >= 0)
			pSeries1->AddDataPoint(data[curpage * 4][i]);
		pSeries2->AddDataPoint(upperlimit[curpage * 4]);
		pSeries3->AddDataPoint(lowerlimit[curpage * 4]);
	}

	CBCGPChartAxis* pYAxis = pChart2->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
	ASSERT_VALID(pYAxis);

	pYAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_CROSS;
	pYAxis->m_minorTickMarkType = CBCGPChartAxis::TMT_CROSS;

	CBCGPChartAxis* pXAxis = pChart2->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
	ASSERT_VALID(pXAxis);

	pXAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_CROSS;
	pXAxis->m_minorTickMarkType = CBCGPChartAxis::TMT_CROSS;

	//if (m_QcXLineChart.GetGraphicsManager()->GetType() == CBCGPGraphicsManager::BCGP_GRAPHICS_MANAGER_GDI)
	//{
	//	m_wndDisplayShadow.EnableWindow(FALSE);
	//	m_wndDisplayShadow.ShowWindow(SW_HIDE);
	//	m_bDisplayShadow = FALSE;
	//}
	OnUpdateChart(2);
}

void CQcXChartView::InitLineChart3()
{
	pChart3 = m_QcXLineChart3.GetChart();
	ASSERT_VALID(pChart3);

	BCGPChartType type = BCGP_CT_SIMPLE;
	pChart3->CleanUpChartData();
	pChart3->SetChartType(BCGPChartLine, type);

	//pChart->SetChartTitle(_T("Furniture Sales"));
	if (curpage < 6)
	{
		CBCGPChartSeries* pSeries1 = pChart3->CreateSeries(_T("�ʿ�ֵ"));
		CBCGPChartSeries* pSeries2 = pChart3->CreateSeries(_T("��ֵ����"));
		CBCGPChartSeries* pSeries3 = pChart3->CreateSeries(_T("��ֵ����"));

		//CString m_arYears[5] = { "2010", "2011", "2012", "2013", "2014" };
		//pSeries1->AddDataPoint(m_arYears[4], 5.);
		//pSeries1->AddDataPoint(m_arYears[3], 8.);
		//pSeries1->AddDataPoint(m_arYears[2], 12.);
		//pSeries1->AddDataPoint(m_arYears[1], 13.);
		//pSeries1->AddDataPoint(m_arYears[0], 15.);

		CArray <double, double> m_upperarray, m_lowerarray, m_dataarray;
		for (int i = 0; i < 31; i++){
			if (data[curpage * 4][i] >= 0)
				pSeries1->AddDataPoint(data[curpage * 4][i]);
			pSeries2->AddDataPoint(upperlimit[curpage * 4]);
			pSeries3->AddDataPoint(lowerlimit[curpage * 4]);
		}

		CBCGPChartAxis* pYAxis = pChart3->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
		ASSERT_VALID(pYAxis);

		pYAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_CROSS;
		pYAxis->m_minorTickMarkType = CBCGPChartAxis::TMT_CROSS;

		CBCGPChartAxis* pXAxis = pChart3->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
		ASSERT_VALID(pXAxis);

		pXAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_CROSS;
		pXAxis->m_minorTickMarkType = CBCGPChartAxis::TMT_CROSS;

		OnUpdateChart(3);
	}
	else if (curpage == 6)
	{
		pChart3->RemoveAllChartObjects();
		pChart3->Redraw();
		return;
	}
	//if (m_QcXLineChart.GetGraphicsManager()->GetType() == CBCGPGraphicsManager::BCGP_GRAPHICS_MANAGER_GDI)
	//{
	//	m_wndDisplayShadow.EnableWindow(FALSE);
	//	m_wndDisplayShadow.ShowWindow(SW_HIDE);
	//	m_bDisplayShadow = FALSE;
	//}
}

void CQcXChartView::InitLineChart4()
{
	pChart4 = m_QcXLineChart4.GetChart();
	ASSERT_VALID(pChart4);

	/*BCGPChartType type =
	(m_Feature == CDemoFeature::BCGP_StackedLine || m_Feature == CDemoFeature::BCGP_StackedLineSpline) ? BCGP_CT_STACKED :
	(m_Feature == CDemoFeature::BCGP_StackedLine100) ?
	BCGP_CT_100STACKED : BCGP_CT_SIMPLE;*/
	BCGPChartType type = BCGP_CT_SIMPLE;
	//BCGPChartType type = BCGP_CT_100STACKED;
	pChart4->CleanUpChartData();
	pChart4->SetChartType(BCGPChartLine, type);

	if (curpage < 6)
	{
		//pChart->SetChartTitle(_T("Furniture Sales"));
		CBCGPChartSeries* pSeries1 = pChart4->CreateSeries(_T("�ʿ�ֵ"));
		CBCGPChartSeries* pSeries2 = pChart4->CreateSeries(_T("��ֵ����"));
		CBCGPChartSeries* pSeries3 = pChart4->CreateSeries(_T("��ֵ����"));


		CArray <double, double> m_upperarray, m_lowerarray, m_dataarray;
		for (int i = 0; i < 31; i++){
			if (data[curpage * 4][i] >= 0)
				pSeries1->AddDataPoint(data[curpage * 4][i]);
			pSeries2->AddDataPoint(upperlimit[curpage * 4]);
			pSeries3->AddDataPoint(lowerlimit[curpage * 4]);
		}


		CBCGPChartAxis* pYAxis = pChart4->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
		ASSERT_VALID(pYAxis);

		pYAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_CROSS;
		pYAxis->m_minorTickMarkType = CBCGPChartAxis::TMT_CROSS;

		CBCGPChartAxis* pXAxis = pChart4->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
		ASSERT_VALID(pXAxis);

		pXAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_CROSS;
		pXAxis->m_minorTickMarkType = CBCGPChartAxis::TMT_CROSS;
		//if (m_QcXLineChart.GetGraphicsManager()->GetType() == CBCGPGraphicsManager::BCGP_GRAPHICS_MANAGER_GDI)
		//{
		//	m_wndDisplayShadow.EnableWindow(FALSE);
		//	m_wndDisplayShadow.ShowWindow(SW_HIDE);
		//	m_bDisplayShadow = FALSE;
		//}
		OnUpdateChart(4);
	}
	else if (curpage == 6)
	{
		pChart4->RemoveAllChartObjects();
		pChart4->Redraw();
		return;
	}
}


void CQcXChartView::OnUpdateChart(int num)
{
	UpdateData();
	//m_wndMarkerShape.EnableWindow(m_bShowDataMarkers);
	//m_wndMarkerSize.EnableWindow(m_bShowDataMarkers);
	//m_wndDataLabelAngle.EnableWindow(m_bShowDataLabels);
	CBCGPChartVisualObject* pChart;
	switch (num)
	{
	case 1:
		pChart = m_QcXLineChart.GetChart();
		break;
	case 2:
		pChart = m_QcXLineChart2.GetChart();
		break;
	case 3:
		pChart = m_QcXLineChart3.GetChart();
		break;
	case 4:
		pChart = m_QcXLineChart4.GetChart();
		break;
	default:
		break;
	}
	ASSERT_VALID(pChart);
	pChart->ShowDataMarkers(TRUE, max(7, 5 * (0 + 1)),
		(BCGPChartMarkerOptions::MarkerShape)0);

	pChart->SetLegendPosition(BCGPChartLayout::LP_NONE);
	//double dblDataLabelAngle = (m_nDataLabelAngle - 2) * 45;

	//pChart->ShowDataLabels(m_bShowDataLabels, TRUE, TRUE, dblDataLabelAngle);
	//pChart->CleanUpChartData();

	for (int i = 0; i < pChart->GetSeriesCount(); i++)
	{
		CBCGPChartSeries* pSeries = pChart->GetSeries(i);
		ASSERT_VALID(pSeries);

		BCGPChartFormatSeries style = pSeries->GetSeriesFormat();

		//style.m_curveType = (m_Feature == CDemoFeature::BCGP_StackedLineSpline) ?
		//BCGPChartFormatSeries::CCT_SPLINE :
		//(m_Feature == CDemoFeature::BCGP_StepLine) ?
		//BCGPChartFormatSeries::CCT_STEP :
		//BCGPChartFormatSeries::CCT_LINE;

		style.m_curveType = BCGPChartFormatSeries::CCT_SPLINE;

		style.SetSeriesOutlineDashStyle((CBCGPStrokeStyle::BCGP_DASH_STYLE)0);
		style.SetSeriesLineWidth(0 + 1);

		style.m_shadowType.m_bDisplayShadow = 1;

		pSeries->SetSeriesFormat(style);
	}
	pChart->Redraw();
}



void CQcXChartView::UpdateLineChart()
{

}

void CQcXChartView::UpdateLineChart2()
{

}

void CQcXChartView::UpdateLineChart3()
{

}

void CQcXChartView::UpdateLineChart4()
{

}


bool CQcXChartView::InitQcXMaterialInfoList()
{
	CRect rect;

	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_QcXmaterialInfolist.GetClientRect(&rect);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_QcXmaterialInfolist.SetExtendedStyle(m_QcXmaterialInfolist.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_QcXmaterialInfolist.SetRowHeigt(20);

	m_QcXmaterialInfolist.DeleteAllItems();//����б�ˢ��

	m_QcXmaterialInfolist.DeleteColumn(0);
	m_QcXmaterialInfolist.DeleteColumn(1);
	m_QcXmaterialInfolist.DeleteColumn(2);
	m_QcXmaterialInfolist.DeleteColumn(3);
	// ΪWBC�б���ͼ�ؼ��������   
	m_QcXmaterialInfolist.InsertColumn(0, _T("����"), LVCFMT_CENTER, rect.Width() / 4, 0);
	m_QcXmaterialInfolist.InsertColumn(1, _T("�������ţ�"), LVCFMT_CENTER, rect.Width() / 4, 1);
	m_QcXmaterialInfolist.InsertColumn(2, _T("����"), LVCFMT_CENTER, rect.Width() / 4, 2);
	m_QcXmaterialInfolist.InsertColumn(3, _T("ʧЧ��"), LVCFMT_CENTER, rect.Width() / 4, 3);
	// ��WBC�б���ͼ�ؼ��в����б���������б������ı�   

	m_QcXmaterialInfolist.InsertItem(0, _T("LYM%"));
	m_QcXmaterialInfolist.SetItemText(0, 0, _T("�ʿ�ͼ"));
	m_QcXmaterialInfolist.SetItemText(0, 1, _T("����2����ǰ��"));
	m_QcXmaterialInfolist.SetItemText(0, 2, (number));
	m_QcXmaterialInfolist.SetItemText(0, 3, (deadline));
	//AfxMessageBox(_T("1213"));
	return TRUE;
}

bool CQcXChartView::UpdateQcXMaterialInfoList(){
	m_QcXmaterialInfolist.DeleteAllItems();//����б�ˢ��

	m_QcXmaterialInfolist.InsertItem(0, _T("LYM%"));
	m_QcXmaterialInfolist.SetItemText(0, 0, _T("�ʿ�ͼ"));
	m_QcXmaterialInfolist.SetItemText(0, 1, _T("����2����ǰ��"));
	m_QcXmaterialInfolist.SetItemText(0, 2, (number));
	m_QcXmaterialInfolist.SetItemText(0, 3, (deadline));
	return true;
}


void CQcXChartView::OnQcXGraphUp()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString pageInfo;
	CString table_temp[] = { "WBC", "LYM%", "NEU%", "MONO%", "EOS%", "BASO%", "ALY%", "LIC%",
		"LYM#", "NEU#", "MONO#", "EOS#", "BASO#", "ALY#", "LIC#", "RBC", "HGB",
		"HCT", "MCV", "MCH", "MCHC", "RDW", "PLT", "MPV", "PDW", "PCT" };
	memcpy(quality_table, table_temp, sizeof(table_temp));

	if (curpage > 0)
	{
		curpage--;
	}
	if (curpage == 0)
	{
		GetDlgItem(IDC_QC_X_GRAPH_UP)->EnableWindow(false);
	}
	if (curpage != 6)
		GetDlgItem(IDC_QC_X_GRAPH_DOWN)->EnableWindow(true);
	pageInfo.Format(L"000%d/0007", curpage + 1);

	GetDlgItem(IDC_QC_X_STATIC1)->SetWindowText(quality_table[curpage * 4]);
	GetDlgItem(IDC_QC_X_STATIC2)->SetWindowText(quality_table[curpage * 4 + 1]);
	GetDlgItem(IDC_QC_X_STATIC3)->SetWindowText(quality_table[curpage * 4 + 2]);
	GetDlgItem(IDC_QC_X_STATIC4)->SetWindowText(quality_table[curpage * 4 + 3]);
	GetDlgItem(IDC_QC_X_STATIC5)->SetWindowText(pageInfo);

	InitLineChart();
	InitLineChart2();
	InitLineChart3();
	InitLineChart4();
	UpdateMSC();
}

void CQcXChartView::OnQcXGraphDown()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString pageInfo;
	CString table_temp[] = { "WBC", "LYM%", "NEU%", "MONO%", "EOS%", "BASO%", "ALY%", "LIC%",
		"LYM#", "NEU#", "MONO#", "EOS#", "BASO#", "ALY#", "LIC#", "RBC", "HGB",
		"HCT", "MCV", "MCH", "MCHC", "RDW", "PLT", "MPV", "PDW", "PCT" };
	memcpy(quality_table, table_temp, sizeof(table_temp));
	if (curpage<6)
		curpage++;
	if (curpage == 6)
	{
		GetDlgItem(IDC_QC_X_GRAPH_DOWN)->EnableWindow(false);
		//pChart3->CleanUpChartData();
		//pChart4->CleanUpChartData();
	}
	if (curpage != 0)
		GetDlgItem(IDC_QC_X_GRAPH_UP)->EnableWindow(true);
	pageInfo.Format(L"000%d/0007", curpage + 1);
	GetDlgItem(IDC_QC_X_STATIC1)->SetWindowText(quality_table[curpage * 4]);
	GetDlgItem(IDC_QC_X_STATIC2)->SetWindowText(quality_table[curpage * 4 + 1]);
	GetDlgItem(IDC_QC_X_STATIC3)->SetWindowText(quality_table[curpage * 4 + 2]);
	GetDlgItem(IDC_QC_X_STATIC4)->SetWindowText(quality_table[curpage * 4 + 3]);
	GetDlgItem(IDC_QC_X_STATIC5)->SetWindowText(pageInfo);

	InitLineChart();
	InitLineChart2();
	InitLineChart3();
	InitLineChart4();
	UpdateMSC();
}

void CQcXChartView::UpdateLUlimit()
{




}

//���㡢���� Mean��SD��CV ��ֵ����ʾ
void CQcXChartView::UpdateMSC()
{
	int ColCount = 4;
	float sum = 0;
	float square = 0;
	float Y = 0;
	float Meantemp[4] = { 0.0 };
	float SDtemp[4] = { 0.0 };
	float CVtemp[4] = { 0.0 };
	CString Mean[4];
	CString SD[4];
	CString CV[4];

	for (int i = 0; i < ColCount; i++)
	{
		sum = 0;
		for (int j = 0; j < qcXGraphNum; j++)
		{
			Y = data[i + curpage * 4][j];
			sum += Y;
		}
		Meantemp[i] = sum / qcXGraphNum;//��ֵ

		if (qcXGraphNum > 1)
		{
			sum = 0;
			square = 0;
			for (int j = 0; j < qcXGraphNum; j++)
			{
				Y = data[i + curpage * 4][j];
				square += (Y - Meantemp[i])*(Y - Meantemp[i]);
			}
			SDtemp[i] = sqrt(square / (qcXGraphNum - 1));//��׼��

			if (Meantemp[i] < 0.00001)//��֤�����ĳ�����Ϊ0
				CVtemp[i] = 0.00;
			else
			{
				CVtemp[i] = SDtemp[i] / Meantemp[i] * 100;//����ϵ��=��׼�� / ��ֵ * 100%
			}
		}

	}
	for (int i = 0; i < 4; i++)
	{
		Mean[i].Format(L"%.2f", Meantemp[i]);
		SD[i].Format(L"%.2f", SDtemp[i]);
		CV[i].Format(L"%.2f", CVtemp[i]);
	}

	SetDlgItemText(IDC_QC_X_MEAN1, Mean[0]);
	SetDlgItemText(IDC_QC_X_MEAN2, Mean[1]);
	SetDlgItemText(IDC_QC_X_MEAN3, Mean[2]);
	SetDlgItemText(IDC_QC_X_MEAN4, Mean[3]);

	SetDlgItemText(IDC_QC_X_SD1, SD[0]);
	SetDlgItemText(IDC_QC_X_SD2, SD[1]);
	SetDlgItemText(IDC_QC_X_SD3, SD[2]);
	SetDlgItemText(IDC_QC_X_SD4, SD[3]);

	SetDlgItemText(IDC_QC_X_CV1, CV[0]);
	SetDlgItemText(IDC_QC_X_CV2, CV[1]);
	SetDlgItemText(IDC_QC_X_CV3, CV[2]);
	SetDlgItemText(IDC_QC_X_CV4, CV[3]);

}

//�����ʿ����ͺ��ļ��Ų�ѯ���ʿر༭��Ϣ�������ж��ʿ��ļ��Ƿ��ѱ༭��,����ʿر༭�ļ������޺�����
int CQcXChartView::GetNumDea(int controltype, int controlfile)//�������������
{
	CString select_qc_edit;
	CString filename;
	int rownum = 0;
	filename.Format(_T("appdata.accdb"));
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	_variant_t var;
	CString strTemp;
	double deviationTemp;
	double targetTemp;
	for (int i = 0; i < 26; i++){
		lowerlimit[i] = 0;
		upperlimit[i] = 0;
	}

	//getNumdea = L"select * from qceditdata where qctype = " + controltype + " and filenum =" + controlfile + ";";// , controltype, controlfile);
	select_qc_edit.Format(L"select * from qceditdata where qctype ='%d' and filenum ='%d';", controltype, controlfile);

	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return -1;
	ExeSql(m_pDB, m_pRs, select_qc_edit);
	rownum = int(m_pRs->GetRecordCount());
	try
	{
		if (!m_pRs->BOF){
			m_pRs->MoveFirst();
		}
		else
		{
			TRACE("��������Ϊ��\n");
			return -1;
		}
		if (var.vt != VT_NULL)
		{
			strTemp = m_pRs->GetCollect("number");
			_tcscpy(number.GetBuffer(strTemp.GetLength() + 1), strTemp);

			//��������
		}
		var = m_pRs->GetCollect("deadline");
		if (var.vt != VT_NULL)
		{
			strTemp = m_pRs->GetCollect("deadline");
			_tcscpy(deadline.GetBuffer(strTemp.GetLength() + 1), strTemp);
			//�����ֹ����
		}
		while (!m_pRs->adoEOF)
		{
			for (int i = 0; i < 26; i++)
			{
				var = m_pRs->GetFields()->GetItem((long)5 + i)->Value;//�������Ǹ�������ֵ��,�˴�ֱ�ӱ����ˣ�������
				if (var.vt != VT_NULL){
					strTemp = (LPCSTR)_bstr_t(var);
					targetTemp = _wtof(strTemp);

				}
				var = m_pRs->GetFields()->GetItem((long)5 + 26 + i)->Value;
				if (var.vt != VT_NULL){
					strTemp = (LPCSTR)_bstr_t(var);
					deviationTemp = _wtof(strTemp);
				}
				lowerlimit[i] = targetTemp - deviationTemp;
				upperlimit[i] = targetTemp + deviationTemp;
			}
			m_pRs->MoveNext();
		}
	}
	catch (_com_error &e)
	{
		TRACE("GetNumDea���������쳣\n");
	}
	CloseDataBase(m_pDB, m_pRs);
	return rownum;
}

//�����ʿ����ͺ��ļ��Ų�ѯ���ʿؽ����Ϣ
int CQcXChartView::GetDetail(int controltype, int controlfile)
{
	CString select_detail;
	CString filename;
	int rownum = 0;
	filename.Format(_T("appdata.accdb"));
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	_variant_t var;
	CString strTemp;
	int k = 0;
	for (int i = 0; i < 26; i++){//����������data��ʼ���
		for (int j = 0; j < 31; j++){
			data[i][j] = -5.0;
		}
	}

	select_detail.Format(L"select * from qcresultdata where qctype = '%d' and filenum = '%d';", controltype, controlfile);

	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return -1;
	ExeSql(m_pDB, m_pRs, select_detail);
	rownum = int(m_pRs->GetRecordCount());

	try
	{
		if (!m_pRs->BOF){
			m_pRs->MoveFirst();
		}
		else
		{
			TRACE("��������Ϊ��\n");
			return -1;
		}


		while ((!m_pRs->adoEOF))
		{
			for (int i = 0; i < 26; i++)
			{
				var = m_pRs->GetFields()->GetItem((long)2 + i)->Value;
				if (var.vt != VT_NULL){
					strTemp = (LPCSTR)_bstr_t(var);
					data[i][k] = _wtof(strTemp);
				}
			}
			k++;
			m_pRs->MoveNext();
		}
		if (k != 0)
			qcXGraphNum = k / 2;
		else
			qcXGraphNum = 0;
	}
	catch (_com_error &e)
	{
		TRACE("GetDetail���������쳣\n");
	}
	CloseDataBase(m_pDB, m_pRs);
	return rownum;
}

void CQcXChartView::UpdateView()
{
	CString item_temp, done_temp;
	int nRow, mRow;
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
	SetDlgItemText(IDC_QC_X_STATIC0, item_temp);
	GetDlgItem(IDC_QC_X_STATIC0)->SetFont(&textfont);

	nRow = GetNumDea(Controltype, Controlfile);
	if (nRow == 0)
		isQcXEditExist = 0;
	else
		isQcXEditExist = 1;

	//��ȡ��Ч���ʿؽ������
	if (1 == isQcXEditExist)
	{
		//MessageBox(L"getDetail");
		mRow = GetDetail(Controltype, Controlfile);
		qcXGraphNum = mRow;
		if (mRow > 31)
			qcXGraphNum = 31;
	}
	else
		qcXGraphNum = 0;
	done_temp.Format(L"����������%d", qcXGraphNum);
	SetDlgItemText(IDC_QC_X_STATIC_DONE, done_temp);


	InitLineChart();
	InitLineChart2();
	InitLineChart3();
	InitLineChart4();
	UpdateQcXMaterialInfoList();
	UpdateMSC();

}