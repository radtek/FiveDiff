// QcXrChartView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "QcXrChartView.h"
#include "afxdialogex.h"


// CQcXrChartView �Ի���

IMPLEMENT_DYNAMIC(CQcXrChartView, CDialogEx)

CQcXrChartView::CQcXrChartView(CWnd* pParent /*=NULL*/)
: CDialogEx(CQcXrChartView::IDD, pParent)
{
	curpage = 0;
	qcXrChartFileExistEdit = 0;
	qcXrChartGraphNum = 0;
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
		DEFAULT_PITCH | FF_SWISS,	 // nPitchAndFamily
		L"����"));                 // lpszFacename



	for (int i = 0; i < 26; i++)
		for (int j = 0; j < 31; j++)
			data[i][j] = -5.0;//��ʼ��Ϊ�������Ա���ͼ��ֻ��ʾ��Ч����
}

CQcXrChartView::~CQcXrChartView()
{
}

void CQcXrChartView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_QC_XR_CHART_LINECHART1, m_QcXrChartLineChart1);
	DDX_Control(pDX, IDC_QC_XR_CHART_LINECHART2, m_QcXrChartLineChart2);
	DDX_Control(pDX, IDC_QC_XR_CHART_MATERIALLIST, m_QcXrChartMaterialInfolist);
}


BEGIN_MESSAGE_MAP(CQcXrChartView, CDialogEx)
	ON_WM_PAINT()
	ON_MESSAGE(UM_REDRAW, OnRedraw)
	ON_WM_CTLCOLOR()

	ON_BN_CLICKED(IDC_QC_XR_CHART_GRAPH_UP, &CQcXrChartView::OnBnClickedQcXrChartGraphUp)
	ON_BN_CLICKED(IDC_QC_XR_CHART_GRAPH_DOWN, &CQcXrChartView::OnBnClickedQcXrChartGraphDown)
	ON_BN_CLICKED(IDC_PRINTXR, &CQcXrChartView::OnBnClickedPrintxr)
END_MESSAGE_MAP()


// CQcXrChartView ��Ϣ�������


void CQcXrChartView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
}


HBRUSH CQcXrChartView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_QC_XR_CHART_STATIC0:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	default:
		break;
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


BOOL CQcXrChartView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//��ʾ�ʿ����ͺ��ļ���
	CString item_temp, done_temp, pageInfo;
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
	SetDlgItemText(IDC_QC_XR_CHART_STATIC0, item_temp);
	GetDlgItem(IDC_QC_XR_CHART_STATIC0)->SetFont(&textfont);

	pageInfo.Format(L"00%d/00%d", curpage + 1, 26);
	GetDlgItem(IDC_QC_XR_CHART_PAGE_NUM)->SetWindowText(pageInfo);

	//����db
	GetQcXrResult(Controltype, Controlfile);

	//������ƽ����Ave��Ran���ػ溯������Ҫ���¼��㣩
	setQcAveRan();

	done_temp.Format(L"����������%d", qcXrChartGraphNum);
	SetDlgItemText(IDC_QC_XR_CHART_STATIC_DONE, done_temp);

	InitLineChart1();
	InitLineChart2();
	InitmaterialInfoList();
	GetDlgItem(IDC_QC_XR_CHART_GRAPH_UP)->EnableWindow(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void CQcXrChartView::InitLineChart1()
{
	pChart1 = m_QcXrChartLineChart1.GetChart();
	ASSERT_VALID(pChart1);

	BCGPChartType type = BCGP_CT_SIMPLE;

	pChart1->CleanUpChartData();

	pChart1->SetChartType(BCGPChartLine, type);

	CBCGPChartSeries* pSeries1 = pChart1->CreateSeries(_T("�ʿ�ֵ"));
	CBCGPChartSeries* pSeries2 = pChart1->CreateSeries(_T("��ֵ����"));
	CBCGPChartSeries* pSeries3 = pChart1->CreateSeries(_T("��ֵ����"));

	for (int i = 0; i < 62; i += 2){
		if (data[curpage][i] >= 0)
			pSeries1->AddDataPoint(data[curpage][i]);
		pSeries2->AddDataPoint(qcAve[curpage] + qcRan[curpage]);
		pSeries3->AddDataPoint(qcAve[curpage] - qcRan[curpage]);
	}
	CBCGPChartAxis* pYAxis = pChart1->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
	ASSERT_VALID(pYAxis);

	pYAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_CROSS;
	pYAxis->m_minorTickMarkType = CBCGPChartAxis::TMT_CROSS;

	CBCGPChartAxis* pXAxis = pChart1->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
	ASSERT_VALID(pXAxis);

	pXAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_CROSS;
	pXAxis->m_minorTickMarkType = CBCGPChartAxis::TMT_CROSS;

	OnUpdateChart(1);

}

void CQcXrChartView::InitLineChart2()
{
	pChart2 = m_QcXrChartLineChart2.GetChart();
	ASSERT_VALID(pChart2);

	BCGPChartType type = BCGP_CT_SIMPLE;

	pChart2->CleanUpChartData();
	pChart2->SetChartType(BCGPChartLine, type);

	CBCGPChartSeries* pSeries1 = pChart2->CreateSeries(_T("�ʿ�ֵ"));
	CBCGPChartSeries* pSeries2 = pChart2->CreateSeries(_T("��ֵ����"));
	CBCGPChartSeries* pSeries3 = pChart2->CreateSeries(_T("��ֵ����"));

	for (int i = 1; i < 31 * 2; i += 2){
		if (data[curpage][i] >= 0)
			pSeries1->AddDataPoint(data[curpage][i]);
		pSeries2->AddDataPoint(3 * qcRan[curpage]);
		pSeries3->AddDataPoint(0 * qcRan[curpage]);
	}

	CBCGPChartAxis* pYAxis = pChart2->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
	ASSERT_VALID(pYAxis);

	pYAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_CROSS;
	pYAxis->m_minorTickMarkType = CBCGPChartAxis::TMT_CROSS;

	CBCGPChartAxis* pXAxis = pChart2->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
	ASSERT_VALID(pXAxis);

	pXAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_CROSS;
	pXAxis->m_minorTickMarkType = CBCGPChartAxis::TMT_CROSS;

	OnUpdateChart(2);
}

void CQcXrChartView::OnUpdateChart(int num)
{
	UpdateData();
	CBCGPChartVisualObject* pChart;
	switch (num)
	{
	case 1:
		pChart = m_QcXrChartLineChart1.GetChart();
		break;
	case 2:
		pChart = m_QcXrChartLineChart2.GetChart();
		break;
	default:
		break;
	}
	ASSERT_VALID(pChart);
	pChart->ShowDataMarkers(TRUE, max(7, 5 * (0 + 1)),
		(BCGPChartMarkerOptions::MarkerShape)0);

	pChart->SetLegendPosition(BCGPChartLayout::LP_NONE);

	for (int i = 0; i < pChart->GetSeriesCount(); i++)
	{
		CBCGPChartSeries* pSeries = pChart->GetSeries(i);
		ASSERT_VALID(pSeries);

		BCGPChartFormatSeries style = pSeries->GetSeriesFormat();
		style.m_curveType = BCGPChartFormatSeries::CCT_SPLINE;
		style.SetSeriesOutlineDashStyle((CBCGPStrokeStyle::BCGP_DASH_STYLE)0);
		style.SetSeriesLineWidth(0 + 1);
		style.m_shadowType.m_bDisplayShadow = 1;
		pSeries->SetSeriesFormat(style);
	}
	pChart->Redraw();
}
bool CQcXrChartView::InitmaterialInfoList()
{
	CRect rect;

	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_QcXrChartMaterialInfolist.GetClientRect(&rect);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_QcXrChartMaterialInfolist.SetExtendedStyle(m_QcXrChartMaterialInfolist.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_QcXrChartMaterialInfolist.SetRowHeigt(20);

	m_QcXrChartMaterialInfolist.DeleteAllItems();//����б�ˢ��

	m_QcXrChartMaterialInfolist.DeleteColumn(0);
	m_QcXrChartMaterialInfolist.DeleteColumn(1);
	m_QcXrChartMaterialInfolist.DeleteColumn(2);
	m_QcXrChartMaterialInfolist.DeleteColumn(3);
	// ΪWBC�б���ͼ�ؼ��������   
	m_QcXrChartMaterialInfolist.InsertColumn(0, _T("����"), LVCFMT_CENTER, rect.Width() / 4, 0);
	m_QcXrChartMaterialInfolist.InsertColumn(1, _T("�������ţ�"), LVCFMT_CENTER, rect.Width() / 4, 1);
	m_QcXrChartMaterialInfolist.InsertColumn(2, _T("����"), LVCFMT_CENTER, rect.Width() / 4, 2);
	m_QcXrChartMaterialInfolist.InsertColumn(3, _T("ʧЧ��"), LVCFMT_CENTER, rect.Width() / 4, 3);
	// ��WBC�б���ͼ�ؼ��в����б���������б������ı�   

	m_QcXrChartMaterialInfolist.InsertItem(0, _T("LYM%"));
	m_QcXrChartMaterialInfolist.SetItemText(0, 0, _T("�ʿ�ͼ"));
	m_QcXrChartMaterialInfolist.SetItemText(0, 1, _T("����2����ǰ��"));
	m_QcXrChartMaterialInfolist.SetItemText(0, 2, (number));
	m_QcXrChartMaterialInfolist.SetItemText(0, 3, (deadline));
	//AfxMessageBox(_T("1213"));
	return TRUE;
}

bool CQcXrChartView::UpdateMaterialInfoList(){
	m_QcXrChartMaterialInfolist.DeleteAllItems();//����б�ˢ��

	m_QcXrChartMaterialInfolist.InsertItem(0, _T("LYM%"));
	m_QcXrChartMaterialInfolist.SetItemText(0, 0, _T("�ʿ�ͼ"));
	m_QcXrChartMaterialInfolist.SetItemText(0, 1, _T("����2����ǰ��"));
	m_QcXrChartMaterialInfolist.SetItemText(0, 2, (number));
	m_QcXrChartMaterialInfolist.SetItemText(0, 3, (deadline));
	return true;
}

void CQcXrChartView::OnBnClickedQcXrChartGraphUp()
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
		GetDlgItem(IDC_QC_XR_CHART_GRAPH_UP)->EnableWindow(false);
	}
	if (curpage != 25)
		GetDlgItem(IDC_QC_XR_CHART_GRAPH_DOWN)->EnableWindow(true);
	pageInfo.Format(L"00%d/00%d", curpage + 1, 26);

	GetDlgItem(IDC_QC_XR_CHART_STATIC_ITEM)->SetWindowText(quality_table[curpage]);
	/*GetDlgItem(IDC_STATIC2)->SetWindowText(quality_table[curpage * 4 + 1]);
	GetDlgItem(IDC_STATIC3)->SetWindowText(quality_table[curpage * 4 + 2]);
	GetDlgItem(IDC_STATIC4)->SetWindowText(quality_table[curpage * 4 + 3]);*/
	GetDlgItem(IDC_QC_XR_CHART_PAGE_NUM)->SetWindowText(pageInfo);

	InitLineChart1();
	InitLineChart2();

}


void CQcXrChartView::OnBnClickedQcXrChartGraphDown()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString pageInfo;
	CString table_temp[] = { "WBC", "LYM%", "NEU%", "MONO%", "EOS%", "BASO%", "ALY%", "LIC%",
		"LYM#", "NEU#", "MONO#", "EOS#", "BASO#", "ALY#", "LIC#", "RBC", "HGB",
		"HCT", "MCV", "MCH", "MCHC", "RDW", "PLT", "MPV", "PDW", "PCT" };
	memcpy(quality_table, table_temp, sizeof(table_temp));
	if (curpage<25)
		curpage++;
	if (curpage == 25)
	{
		GetDlgItem(IDC_QC_XR_CHART_GRAPH_DOWN)->EnableWindow(false);
		//pChart3->CleanUpChartData();
		//pChart4->CleanUpChartData();
	}
	if (curpage != 0)
		GetDlgItem(IDC_QC_XR_CHART_GRAPH_UP)->EnableWindow(true);
	pageInfo.Format(L"00%d/00%d", curpage + 1, 26);
	GetDlgItem(IDC_QC_XR_CHART_STATIC_ITEM)->SetWindowText(quality_table[curpage]);
	//GetDlgItem(IDC_STATIC2)->SetWindowText(quality_table[curpage * 4 + 1]);
	//GetDlgItem(IDC_STATIC3)->SetWindowText(quality_table[curpage * 4 + 2]);
	//GetDlgItem(IDC_STATIC4)->SetWindowText(quality_table[curpage * 4 + 3]);
	GetDlgItem(IDC_QC_XR_CHART_PAGE_NUM)->SetWindowText(pageInfo);

	InitLineChart1();
	InitLineChart2();

}

//�����ʿ����ͺ��ļ��Ų�ѯ���ʿر༭��Ϣ�������ж��ʿ��ļ��Ƿ��ѱ༭��,����ʿر༭�ļ������޺�����
int CQcXrChartView::GetQcXrEdit(int controltype, int controlfile)
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
		//	lowerlimit[i] = 0;
		//	upperlimit[i] = 0;
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
		while (!m_pRs->adoEOF)
		{
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
int CQcXrChartView::GetQcXrResult(int controltype, int controlfile)
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
		for (int j = 0; j < 62; j++){
			data[i][j] = -5.0;
		}
	}

	select_detail.Format(L"select * from qcresultdata where qctype = '%d' and filenum = '%d' order by row asc;", controltype, controlfile);

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


		while ((!m_pRs->adoEOF))//�˴�װ������
		{
			//qcAve[][],qcRan[][];
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
			qcXrChartGraphNum = (k + 1) / 2;
		else
			qcXrChartGraphNum = 0;
	}
	catch (_com_error &e)
	{
		TRACE("GetDetail���������쳣\n");
	}
	CloseDataBase(m_pDB, m_pRs);
	return rownum;
}

void CQcXrChartView::setQcAveRan(){
	if (qcXrChartGraphNum == 0) return;
	double aveSum = 0, ranSum = 0;
	for (int i = 0; i < 26; i++){
		for (int j = 0; j < qcXrChartGraphNum * 2; j += 2){
			aveSum += data[i][j];
			ranSum += data[i][j + 1];
		}
		qcAve[i] = aveSum / qcXrChartGraphNum;
		qcRan[i] = ranSum / qcXrChartGraphNum;
		aveSum = 0;
		ranSum = 0;
	}

}


afx_msg LRESULT CQcXrChartView::OnRedraw(WPARAM, LPARAM){
	//RecalcLayout(TRUE);
	//GetActiveView()->UpdateWindow();
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
	SetDlgItemText(IDC_QC_XR_CHART_STATIC0, item_temp);
	GetDlgItem(IDC_QC_XR_CHART_STATIC0)->SetFont(&textfont);

	nRow = GetQcXrEdit(Controltype, Controlfile);
	if (nRow == 0)
		qcXrChartFileExistEdit = 0;
	else
		qcXrChartFileExistEdit = 1;

	//��ȡ��Ч���ʿؽ������
	if (1 == qcXrChartFileExistEdit)
	{
		//MessageBox(L"getDetail");
		mRow = GetQcXrResult(Controltype, Controlfile);
		qcXrChartGraphNum = mRow;
		if (mRow > 31)
			qcXrChartGraphNum = 31;
	}
	else{
		qcXrChartGraphNum = 0;
	}
	done_temp.Format(L"����������%d", qcXrChartGraphNum);
	SetDlgItemText(IDC_QC_XR_CHART_STATIC_DONE, done_temp);


	InitLineChart1();
	InitLineChart2();

	UpdateMaterialInfoList();

	//RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_ALLCHILDREN | RDW_FRAME);
	return 0;
}



void CQcXrChartView::OnBnClickedPrintxr()
{
	PRINTDLG pd;
	// Initialize PRINTDLG
	ZeroMemory(&pd, sizeof(PRINTDLG));
	pd.lStructSize = sizeof(PRINTDLG);
	pd.hwndOwner = NULL;
	pd.hDevMode = NULL;     // Don't forget to free or store hDevMode
	pd.hDevNames = NULL;     // Don't forget to free or store hDevNames
	pd.Flags = PD_USEDEVMODECOPIESANDCOLLATE | PD_RETURNDC;
	pd.nCopies = 1;
	pd.nFromPage = 0xFFFF;
	pd.nToPage = 0xFFFF;
	pd.nMinPage = 1;
	pd.nMaxPage = 0xFFFF;
	//PrintDlg(&pd);
	if (PrintDlg(&pd) == TRUE)
	{
		// GDI calls to render output. 
		DOCINFO di;
		ZeroMemory(&di, sizeof(DOCINFO));
		di.cbSize = sizeof(DOCINFO);
		di.lpszDocName = _T("NewDoc");
		StartDoc(pd.hDC, &di);
		StartPage(pd.hDC);
		CDC pDC;
		pDC.Attach(pd.hDC);
		pDC.TextOutW(2300, 200, L"X-R�ʿ�ͼ");
		Draw_Xr(L"WBC", pDC, 450, 1300, 0.2, 0.2, 0, 0);
		Draw_Xr(L"LYM%", pDC, 450, 3300, 7, 7, 0, 1);
		Draw_Xr(L"NEU%", pDC, 450, 5300, 10, 10, 0, 2);
		EndPage(pd.hDC);

		StartPage(pd.hDC);
		pDC.TextOutW(2300, 200, L"X-R�ʿ�ͼ");
		Draw_Xr(L"MONO%", pDC, 450, 1300, 12.5, 12.5, 0, 3);
		Draw_Xr(L"EOS%", pDC, 450, 3300, 12.5, 15, 0, 4);
		Draw_Xr(L"BASO%", pDC, 450, 5300, 10, 12.5, 0, 5);
		EndPage(pd.hDC);

		StartPage(pd.hDC);
		pDC.TextOutW(2300, 200, L"X-R�ʿ�ͼ");
		Draw_Xr(L"ALY%", pDC, 450, 1300, 5, 7, -1, 6);
		Draw_Xr(L"LIC%", pDC, 450, 3300, 12.5, 15, 0, 7);
		Draw_Xr(L"LYM#", pDC, 450, 5300, 0.05, 0.05, -1, 8);
		EndPage(pd.hDC);

		StartPage(pd.hDC);
		pDC.TextOutW(2300, 200, L"X-R�ʿ�ͼ");
		Draw_Xr(L"NEU#", pDC, 450, 1300, 0.05, 0.05, 0, 9);
		Draw_Xr(L"MONO#", pDC, 450, 3300, 0.07, 0.1, -1, 10);
		Draw_Xr(L"EOS#", pDC, 450, 5300, 0.02, 0.02, -1, 11);
		EndPage(pd.hDC);

		StartPage(pd.hDC);
		pDC.TextOutW(2300, 200, L"X-R�ʿ�ͼ");
		Draw_Xr(L"BASO#", pDC, 450, 1300, 0.04, 0.04, -1, 12);
		Draw_Xr(L"ALY#", pDC, 450, 3300, 0.01, 0.01, -1, 13);
		Draw_Xr(L"LIC#", pDC, 450, 5300, 0.02, 0.02, 0, 14);
		EndPage(pd.hDC);

		StartPage(pd.hDC);
		pDC.TextOutW(2300, 200, L"X-R�ʿ�ͼ");
		Draw_Xr(L"RBC", pDC, 450, 1300, 0.01, 0.01, -1, 15);
		Draw_Xr(L"HGB", pDC, 450, 3300, 0.1, 0.05, 0, 16);
		Draw_Xr(L"HCT", pDC, 450, 5300, 0.1, 0.05, 0, 17);
		EndPage(pd.hDC);

		StartPage(pd.hDC);
		pDC.TextOutW(2300, 200, L"X-R�ʿ�ͼ");
		Draw_Xr(L"MCV", pDC, 450, 1300, 40, 7, 0, 18);
		Draw_Xr(L"MCH", pDC, 450, 3300, 0.1, 0.05, 0, 19);
		Draw_Xr(L"MCHC", pDC, 450, 5300, 0.02, 0.02, 0, 20);
		EndPage(pd.hDC);

		StartPage(pd.hDC);
		pDC.TextOutW(2300, 200, L"X-R�ʿ�ͼ");
		Draw_Xr(L"RDW", pDC, 450, 1300, 20, 7, 0, 21);
		Draw_Xr(L"PLT", pDC, 450, 3300, 2.5, 2, 0, 22);
		Draw_Xr(L"MPV", pDC, 450, 5300, 2.5, 1, 0, 23);
		EndPage(pd.hDC);

		StartPage(pd.hDC);
		pDC.TextOutW(2300, 200, L"X-R�ʿ�ͼ");
		Draw_Xr(L"PDW", pDC, 450, 1300, 2, 2, -1, 24);
		Draw_Xr(L"PCT", pDC, 450, 3300, 0.003, 0.004, 0, 25);
		EndPage(pd.hDC);
		EndDoc(pd.hDC);
		// Delete DC when done.
		DeleteDC(pd.hDC);
	}
}
void CQcXrChartView::Draw_Xr(CString type, CDC &pDC, int Xorg, int Yorg, double y1, double y2, int flag, int num)
{
	CPen penBlack;
	LOGBRUSH redBrush, greenBrush;
	CPen penData;
	CFont font;
	CString str;
	//pDC.Attach(hdc);
	//�������߻������ڻ��ư�ֵ���޺�����
	redBrush.lbStyle = BS_SOLID;
	redBrush.lbColor = RGB(255, 192, 203);
	CPen penUpperlimit(PS_DASH | PS_GEOMETRIC | PS_ENDCAP_ROUND, 10, &redBrush);

	greenBrush.lbStyle = BS_SOLID;
	greenBrush.lbColor = RGB(48, 128, 20);
	CPen penLowerlimit(PS_DASH | PS_GEOMETRIC | PS_ENDCAP_ROUND, 10, &greenBrush);
	//����
	font.CreateFont(60, 25, 0, 0, 400, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, _T("Arial"));
	//��ɫ����
	penBlack.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	//penUpperlimit.CreatePen(PS_DOT, 1, RGB(255, 192, 203));
	//penLowerlimit.CreatePen(PS_DOT, 10, RGB(48, 128, 20));
	penData.CreatePen(PS_SOLID, 10, RGB(30, 144, 255));
	CFont *poldfont = pDC.SelectObject(&font);
	CPen *pOldpen = pDC.SelectObject(&penBlack);

	//дX ������̶�
	for (int i = 1; i < 32; i++)
	{
		pDC.MoveTo(i * 120, -10);
		pDC.LineTo(i * 120, 10);
		str.Format(L"%d", i);
		pDC.TextOutW(i * 119, 20, str);
	}
	if (flag == -1)
	{
		//X�ʿ�ͼ
		pDC.SetViewportOrg(Xorg, Yorg - 200);
		//����������
		pDC.MoveTo(0, 0);
		pDC.LineTo(3720, 0);
		pDC.MoveTo(0, 200);
		pDC.LineTo(0, -600);
		//д������̶�
		for (int i = -1; i < 4; i++)
		{
			pDC.MoveTo(-10, -i * 200);
			pDC.LineTo(10, -i * 200);
		}
		//����y��̶ȱ�����ͬ��С��λ����д������̶�
		if (y1 > 1)
		{
			str.Format(L"%.1f", -y1);
			pDC.TextOutW(-150, 200, str);
			pDC.TextOutW(-100, 0, L"0");
			str.Format(L"%.1f", y1);
			pDC.TextOutW(-150, -200, str);
			str.Format(L"%.1f", y1 * 2);
			pDC.TextOutW(-150, -400, str);
			str.Format(L"%.1f", y1 * 3);
			pDC.TextOutW(-150, -600, str);
		}
		else if (y1 <= 1 && y1 >= 0.01)
		{
			str.Format(L"%.2f", -y1);
			pDC.TextOutW(-150, 200, str);
			pDC.TextOutW(-100, 0, L"0");
			str.Format(L"%.2f", y1);
			pDC.TextOutW(-150, -200, str);
			str.Format(L"%.2f", y1 * 2);
			pDC.TextOutW(-150, -400, str);
			str.Format(L"%.2f", y1 * 3);
			pDC.TextOutW(-150, -600, str);
		}
		//if (y1<0.01)
		else
		{
			str.Format(L"%.3f", -y1);
			pDC.TextOutW(-200, 200, str);
			pDC.TextOutW(-100, 0, L"0");
			str.Format(L"%.3f", y1);
			pDC.TextOutW(-200, -200, str);
			str.Format(L"%.3f", y1 * 2);
			pDC.TextOutW(-200, -400, str);
			str.Format(L"%.3f", y1 * 3);
			pDC.TextOutW(-200, -600, str);
		}

		pDC.TextOutW(-350, -600, L"X");
		pDC.TextOutW(-350, -700, type);
		//���ư�ֵ���޺Ͱ�ֵ����
		pDC.SelectObject(&penUpperlimit);
		pDC.MoveTo(120, -600 / (y1 * 3)*(qcAve[num] + qcRan[num]));
		pDC.LineTo(120 * 31, -600 / (y1 * 3)*(qcAve[num] + qcRan[num]));
		pDC.SelectObject(&penLowerlimit);
		pDC.MoveTo(120, -200 / y1*(qcAve[num] - qcRan[num]));
		pDC.LineTo(120 * 31, -200 / y1 *(qcAve[num] - qcRan[num]));
		//���ư�ֵ
		pDC.SelectObject(&penData);
		for (int i = 2; i < 62; i += 2)
		{
			if (data[num][i] >= 0)
			{
				pDC.MoveTo(120 * ((i - 2) / 2 + 1), -600 / (y1 * 3)*data[num][i - 2]);
				pDC.LineTo(120 * (i / 2 + 1), -600 / (y1 * 3)*data[num][i]);
			}
		}
	}
	else
	{
		pDC.SetViewportOrg(Xorg, Yorg);
		//����������
		pDC.MoveTo(0, 0);
		pDC.LineTo(3720, 0);
		pDC.MoveTo(0, 0);
		pDC.LineTo(0, -800);
		//д������̶�
		for (int i = 0; i < 5; i++)
		{
			pDC.MoveTo(-10, -i * 200);
			pDC.LineTo(10, -i * 200);
		}
		//����y��̶ȱ�����ͬ��С��λ����д������̶�
		if (y1 > 1)
		{
			pDC.TextOutW(-100, 0, L"0");
			str.Format(L"%.1f", y1);
			pDC.TextOutW(-150, -200, str);
			str.Format(L"%.1f", y1 * 2);
			pDC.TextOutW(-150, -400, str);
			str.Format(L"%.1f", y1 * 3);
			pDC.TextOutW(-150, -600, str);
			str.Format(L"%.1f", y1 * 4);
			pDC.TextOutW(-150, -800, str);
		}
		else if (y1 <= 1 && y1 >= 0.01)
		{
			pDC.TextOutW(-100, 0, L"0");
			str.Format(L"%.2f", y1);
			pDC.TextOutW(-150, -200, str);
			str.Format(L"%.2f", y1 * 2);
			pDC.TextOutW(-150, -400, str);
			str.Format(L"%.2f", y1 * 3);
			pDC.TextOutW(-150, -600, str);
			str.Format(L"%.2f", y1 * 4);
			pDC.TextOutW(-150, -800, str);
		}
		else
		{
			pDC.TextOutW(-100, 0, L"0");
			str.Format(L"%.3f", y1);
			pDC.TextOutW(-200, -200, str);
			str.Format(L"%.3f", y1 * 2);
			pDC.TextOutW(-200, -400, str);
			str.Format(L"%.3f", y1 * 3);
			pDC.TextOutW(-200, -600, str);
			str.Format(L"%.3f", y1 * 4);
			pDC.TextOutW(-200, -800, str);
		}

		pDC.TextOutW(-350, -800, L"X");
		pDC.TextOutW(-350, -900, type);
		//���ư�ֵ���޺Ͱ�ֵ����
		pDC.SelectObject(&penUpperlimit);
		pDC.MoveTo(120, -800 / (y1 * 4)*(qcAve[num] + qcRan[num]));
		pDC.LineTo(120 * 31, -800 / (y1 * 4)*(qcAve[num] + qcRan[num]));
		pDC.SelectObject(&penLowerlimit);
		pDC.MoveTo(120, -800 / (y1 * 4)*(qcAve[num] - qcRan[num]));
		pDC.LineTo(120 * 31, -800 / (y1 * 4)*(qcAve[num] - qcRan[num]));
		//���ư�ֵ
		pDC.SelectObject(&penData);
		for (int i = 2; i < 62; i += 2)
		{
			if (data[num][i] >= 0)
			{
				pDC.MoveTo(120 * ((i - 2) / 2 + 1), -800 / (y1 * 4)*data[num][i - 2]);
				pDC.LineTo(120 * (i / 2 + 1), -800 / (y1 * 4)*data[num][i]);
			}
		}
	}
	pDC.SelectObject(&font);
	pDC.SelectObject(&penBlack);
	//R�ʿ�ͼ
	pDC.SetViewportOrg(Xorg, Yorg + 1000);
	//����������
	pDC.MoveTo(0, 0);
	pDC.LineTo(3720, 0);
	pDC.MoveTo(0, 0);
	pDC.LineTo(0, -800);
	//дR ������̶�
	for (int i = 0; i < 5; i++)
	{
		pDC.MoveTo(-10, -i * 200);
		pDC.LineTo(10, -i * 200);
	}
	//����y��̶ȱ�����ͬ��С��λ����д������̶�
	if (y2 > 1)
	{
		pDC.TextOutW(-100, 0, L"0");
		str.Format(L"%.1f", y2);
		pDC.TextOutW(-150, -200, str);
		str.Format(L"%.1f", y2 * 2);
		pDC.TextOutW(-150, -400, str);
		str.Format(L"%.1f", y2 * 3);
		pDC.TextOutW(-150, -600, str);
		str.Format(L"%.1f", y2 * 4);
		pDC.TextOutW(-150, -800, str);
	}
	else if (y2 <= 1 && y2 >= 0.01)
	{
		pDC.TextOutW(-100, 0, L"0");
		str.Format(L"%.2f", y2);
		pDC.TextOutW(-150, -200, str);
		str.Format(L"%.2f", y2 * 2);
		pDC.TextOutW(-150, -400, str);
		str.Format(L"%.2f", y2 * 3);
		pDC.TextOutW(-150, -600, str);
		str.Format(L"%.2f", y2 * 4);
		pDC.TextOutW(-150, -800, str);
	}
	else
	{
		pDC.TextOutW(-100, 0, L"0");
		str.Format(L"%.3f", y2);
		pDC.TextOutW(-200, -200, str);
		str.Format(L"%.3f", y2 * 2);
		pDC.TextOutW(-200, -400, str);
		str.Format(L"%.3f", y2 * 3);
		pDC.TextOutW(-200, -600, str);
		str.Format(L"%.3f", y2 * 4);
		pDC.TextOutW(-200, -800, str);
	}

	pDC.TextOutW(-350, -800, L"R");
	//д������̶�
	for (int i = 1; i < 32; i++)
	{
		pDC.MoveTo(i * 120, -10);
		pDC.LineTo(i * 120, 10);
		str.Format(L"%d", i);
		pDC.TextOutW(i * 119, 20, str);
	}
	//���ư�ֵ���޺Ͱ�ֵ����
	pDC.SelectObject(&penUpperlimit);
	pDC.MoveTo(120, -800 / (y2 * 4) * 3 * qcRan[num]);
	pDC.LineTo(120 * 31, -800 / (y2 * 4) * 3 * qcRan[num]);
	pDC.SelectObject(&penLowerlimit);
	pDC.MoveTo(120, -800 / (y2 * 4) * 0 * qcRan[num]);
	pDC.LineTo(120 * 31, -800 / (y2 * 4) * 0 * qcRan[num]);
	//���ư�ֵ
	pDC.SelectObject(&penData);
	for (int i = 3; i < 62; i += 2)
	{
		if (data[num][i] >= 0)
		{
			pDC.MoveTo(120 * ((i - 2) / 2 + 1), -800 / (y2 * 4)*data[num][i - 2]);
			pDC.LineTo(120 * (i / 2 + 1), -800 / (y2 * 4)*data[num][i]);
		}
	}
	//�ָ�ԭ���Ļ��ʺ�����
	pDC.SelectObject(pOldpen);
	pDC.SelectObject(poldfont);
	font.DeleteObject();
	penBlack.DeleteObject();
}
