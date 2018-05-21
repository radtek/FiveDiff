// ResultDetails.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "ResultDetails.h"
#include "PatientResultView.h"
//#include "MainFrm.h"
//#include "Includes_app.h"
// CResultDetails
#include <string.h>
//��ͼ
#define RealCO_Dot_LBRP			256
#define RealCO_DOT_PLT			210
#define TotalCO_Dot_LB			(255 + 3*120)
#define TotalCO_Dot_RP			(255 + 3*120)

//��ͼ��غ궨��
#define LMNE_LEFT		0
#define LMNE_BOTTOM 	0
#define LMNE_WIDTH		255//540-340  [0,255]->[340,540]
#define LMNE_HEIGHT		255

IMPLEMENT_DYNCREATE(CResultDetails, CBCGPChartExampleView)

CResultDetails::CResultDetails()
: CBCGPChartExampleView(CResultDetails::IDD)
{
	if ((patientdata = (patient_info*)malloc(sizeof(patient_info))) == NULL)
	{
		TRACE("Memory allocation for ppatientdata failed--------!\n");
		exit(1);
	}
	//Ϊsampledata����ռ� 
	if ((sampledata = (sample_info*)malloc(sizeof(sample_info))) == NULL)
	{
		TRACE("Memory allocation for psampledata failed--------!\n");
		exit(1);
	}

	sampleID = "";

	itemhead = "#|��Ŀ|ȫ��|����|���|��λ|�ο�ֵ";
	CString items_fullname_temp[] = { "��ϸ����Ŀ",
		"�ܰ�ϸ���ٷֱ�",
		"������ϸ���ٷֱ�",
		"����ϸ���ٷֱ�",
		"����ϸ���ٷֱ�",
		"�ȼ�ϸ���ٷֱ�",
		"δ����ϸ���ٷֱ�",
		"�쳣ϸ���ٷֱ�",
		"�ܰ�ϸ����Ŀ",
		"������ϸ����Ŀ",
		"����ϸ����Ŀ",
		"������ϸ����Ŀ",
		"�ȼ�ϸ����Ŀ",
		"δ����ϸ����Ŀ",
		"�쳣ϸ����Ŀ",
		"��ϸ����Ŀ",
		"Ѫ�쵰��",
		"��ϸ��ѹ��",
		"ƽ����ϸ�����",
		"ƽ��Ѫ�쵰�׺���",
		"ƽ��Ѫ�쵰��Ũ��",
		"��ϸ���ֲ����",
		"��ϸ���ֲ����",
		"ѪС����Ŀ",
		"ƽ��ѪС�����",
		"ѪС��ֲ����",
		"ѪС��ѹ��",
		"����ѪС�����" };
	CString		items_shortname_temp[] = { "WBC",
		"  LYM%",
		"  NEU%",
		"  MONO%",
		"  EOS%",
		"  BASO%",
		"  ALY%",
		"  LIC%",
		"  LYM#",
		"  NEU#",
		"  MONO#",
		"  EOS#",
		"  BASO#",
		"  ALY#",
		"  LIC#",
		"RBC",
		"  HGB",
		"  HCT",
		"  MCV",
		"  MCH",
		"  MCHC",
		"  RDW-CV",
		"  RDW-SD",
		"PLT",
		"  MPV",
		"  PDW",
		"  PCT",
		"  P-LCR" };
	CString		unit_info_temp[] = { "10^9/L",
		"%", "%", "%", "%", "%", "%", "%",
		"10^9/L", "10^9/L", "10^9/L", "10^9/L", "10^9/L", "10^9/L", "10^9/L",
		"10^12/L", " g/L", "%", "fL", "Pg", "g/L", "%", "fL",
		"10^9/L", "fL", "fL", "%", "%" };
	//��Ʋſ���ɹ���
	for (int i = 0; i < 28; i++){
		_tcscpy(items_shortname[i].GetBuffer(items_shortname_temp[i].GetLength()+1), items_shortname_temp[i]);
		items_shortname[i].ReleaseBuffer();
	}
	for (int i = 0; i < 28; i++){
		_tcscpy(items_fullname[i].GetBuffer(items_fullname_temp[i].GetLength() + 1), items_fullname_temp[i]);
		items_fullname[i].ReleaseBuffer();
	}
	for (int i = 0; i < 28; i++){
		_tcscpy(unit_info[i].GetBuffer(unit_info_temp[i].GetLength() + 1), unit_info_temp[i]);
		unit_info[i].ReleaseBuffer();
	}

}

CResultDetails::~CResultDetails()
{
	//delete pThisResult;
	free(patientdata);
	free(sampledata);
}

void CResultDetails::DoDataExchange(CDataExchange* pDX)
{
	CBCGPChartExampleView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RESULT_LIST1, m_Details_WBCList);
	DDX_Control(pDX, IDC_RESULT_LIST2, m_Details_RBClist);
	DDX_Control(pDX, IDC_RESULT_LIST3, m_Details_PLTlist);
	DDX_Control(pDX, IDC_RESULT_LIST4, m_Details_RETlist);
	DDX_Control(pDX, IDC_RESULT_LIST5, m_Details_CRPlist);
	DDX_Control(pDX, IDC_RESULT_LMNE_CHART, m_LMNEChart);
	DDX_Control(pDX, IDC_RESULT_BASO_CHART, m_BASOChart);
	DDX_Control(pDX, IDC_RESULT_RBC_CHART, m_RBCChart);
	DDX_Control(pDX, IDC_RESULT_PLT_CHART, m_PLTChart);
	DDX_Control(pDX, IDC_RESULT_PIE_CHART, m_PieChart);
	DDX_Control(pDX, IDC_RESULT_LIST8, m_WBCFlag);
	DDX_Control(pDX, IDC_RESULT_LIST9, m_RBCFlag);
	DDX_Control(pDX, IDC_RESULT_LIST10, m_PLTFlag);
	DDX_Control(pDX, IDC_RESULT_LIST11, m_RETFlag);
	DDX_Control(pDX, IDC_RESULT_COMBO_SEX, m_sex_combo);
	DDX_Control(pDX, IDC_RESULT_COMBO_DOCTOR, m_doctor_combo);
}

BEGIN_MESSAGE_MAP(CResultDetails, CBCGPChartExampleView)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_RESULT_UPLOAD, &CResultDetails::OnResultUpload)
	ON_BN_CLICKED(IDC_BUTTON1, &CResultDetails::OnViewBack)
	ON_BN_CLICKED(IDC_BUTTON2, &CResultDetails::OnViewForward)
	ON_BN_CLICKED(IDC_RESULT_PRINT, &CResultDetails::OnSelectResultPrint)
	ON_BN_CLICKED(IDC_DELETERECORD, &CResultDetails::OnDeleteRecord)
	ON_BN_CLICKED(IDC_RESULT_RETURN, &CResultDetails::OnBnClickedResultReturn)
	//ON_BN_CLICKED(IDC_RESULT_SAVE, &CResultDetails::OnBnClickedResultSave)
	ON_EN_SETFOCUS(IDC_RESULT_EDIT3, &CResultDetails::OnEnSetfocusResultEdit3)
	ON_EN_KILLFOCUS(IDC_RESULT_EDIT3, &CResultDetails::OnEnKillfocusResultEdit3)
	ON_EN_SETFOCUS(IDC_RESULT_EDIT4, &CResultDetails::OnEnSetfocusResultEdit4)
	ON_EN_KILLFOCUS(IDC_RESULT_EDIT4, &CResultDetails::OnEnKillfocusResultEdit4)
	ON_EN_SETFOCUS(IDC_RESULT_EDIT5, &CResultDetails::OnEnSetfocusResultEdit5)
	ON_EN_KILLFOCUS(IDC_RESULT_EDIT5, &CResultDetails::OnEnKillfocusResultEdit5)
	ON_EN_SETFOCUS(IDC_RESULT_EDIT2, &CResultDetails::OnEnSetfocusResultEdit2)
	ON_EN_KILLFOCUS(IDC_RESULT_EDIT2, &CResultDetails::OnEnKillfocusResultEdit2)
	ON_BN_CLICKED(IDC_BUTTON3, &CResultDetails::OnBnClickedButton3)
END_MESSAGE_MAP()




// CResultDetails ���

#ifdef _DEBUG
void CResultDetails::AssertValid() const
{
	CBCGPChartExampleView::AssertValid();
}

#ifndef _WIN32_WCE
void CResultDetails::Dump(CDumpContext& dc) const
{
	CBCGPChartExampleView::Dump(dc);
}
#endif
#endif //_DEBUG


// CResultDetails ��Ϣ�������
sample_info* CResultDetails::sampledata = NULL;
patient_info* CResultDetails::patientdata = NULL;
pResultToDisplay CResultDetails::pThisResult = NULL;
unsigned char graphbu[3500] = { 0 };

void CResultDetails::OnInitialUpdate()
{
	CBCGPChartExampleView::OnInitialUpdate();

	// TODO:  �ڴ����ר�ô����/����û���	
	m_sex_combo.InsertString(0, _T("(��)"));
	m_sex_combo.InsertString(1, _T("��"));
	m_sex_combo.InsertString(2, _T("Ů"));

	LoadChoseRecord(pThisResult);
	InitForm(sampledata);
	PrintChart(sampledata);
	InitPaitientInfo(patientdata);
	if (pThisResult->nownum == 0)
	{
		CButton *pBtn = (CButton *)GetDlgItem(IDC_BUTTON1);
		pBtn->EnableWindow(FALSE);
	}
	if (pThisResult->nownum == (*pThisResult).totalnums - 1)
	{
		CButton *pBtn = (CButton *)GetDlgItem(IDC_BUTTON2);
		pBtn->EnableWindow(FALSE);
	}
	//m_Result_sex.SetCurSel(0);
	//GernerateLMNEBGP();
}

void CResultDetails::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CBCGPChartExampleView::OnPaint()

	/*LoadChoseRecord(pThisResult);
	InitForm(sampledata);
	PrintChart(sampledata);
	InitPaitientInfo(patientdata);*/

	PrintLMNEChart(sampledata);
	//	LmneGraphPaint(sampledata, patientdata->rangetype);


}

BOOL CResultDetails::InitPaitientInfo(patient_info* ppatientdata)
{
	USES_CONVERSION;
	CString numtemp = "20";
	CString rangetype;
	CString nametemp = A2W(ppatientdata->name);
	CString agetemp = ppatientdata->age;
	CString doctor = A2W(ppatientdata->doctor);
	CString barcode = ppatientdata->code;

	/*
	����ȥ�����߿ո�
	���ж������Ƿ�ΪĬ�ϵ������ֵ������ǣ���ֵΪ��
	*/
	nametemp = nametemp.Trim();
	agetemp = agetemp.Trim();
	doctor = doctor.Trim();
	barcode = barcode.Trim();

	if (doctor.GetLength() == 0)
		doctor = "6";

	///********doct_id������ƥ��***************/

	CString filename;
	filename.Format(_T("appdata.accdb"));
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return -1;

	CString doc_check = _T("select * from doctordata where doct_id =") + doctor;
	ExeSql(m_pDB, m_pRs, doc_check);
	_variant_t var;
	try
	{
		if (!m_pRs->BOF){
			m_pRs->MoveFirst();
		}
		else
		{
			TRACE("��������Ϊ��");

		}
		while (!m_pRs->adoEOF)
		{

			var = m_pRs->GetCollect("doct_name");
			if (var.vt != VT_NULL)
				doctor = (LPCSTR)_bstr_t(var);
			m_pRs->MoveNext();
		}

	}
	catch (_com_error &e)
	{
		TRACE("UpdateResultList�쳣");
	}
	CloseDataBase(m_pDB, m_pRs);


	/******************************/



	if (nametemp == "")
		nametemp = "(��)";
	if (ppatientdata->age[0] <= 0 || (agetemp.GetLength() == 0))
		agetemp = "(��)";
	if (doctor == "")
		doctor = "(��)";
	if (ppatientdata->code[0] <= 0 || (barcode.GetLength() == 0))
		barcode = "(��)";
	rangetype.Format(L"%d", ppatientdata->rangetype);
	numtemp = numtemp + pThisResult->numofrs[pThisResult->nownum];


	//MessageBox(rangetype);
	GetDlgItem(IDC_RESULT_EDIT1)->SetWindowText(numtemp);//���
	GetDlgItem(IDC_RESULT_EDIT2)->SetWindowText(rangetype);//����
	GetDlgItem(IDC_RESULT_EDIT3)->SetWindowText(nametemp);//����
	GetDlgItem(IDC_RESULT_EDIT4)->SetWindowText(agetemp);//����
	GetDlgItem(IDC_RESULT_EDIT5)->SetWindowText(barcode);//������
	//m_sex_combo.SetCurSel(1);
	GetDlgItem(IDC_RESULT_COMBO_DOCTOR)->SetWindowTextW(doctor);//ҽ��
	m_sex_combo.SetCurSel((int)ppatientdata->sex);
	int tetetete = 0;
	UpdateData(false);
	return TRUE;
}
/********************�������*************************/
BOOL CResultDetails::InitWBCForm(sample_info* psampledata)
{
	CRect rect;

	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_Details_WBCList.GetClientRect(&rect);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_Details_WBCList.SetExtendedStyle(m_Details_WBCList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_Details_WBCList.SetRowHeigt(20);
	// ΪWBC�б���ͼ�ؼ��������  
	m_Details_WBCList.InsertColumn(0, _T("WBC��Ŀ"), LVCFMT_CENTER, rect.Width() / 6, 0);
	m_Details_WBCList.InsertColumn(1, _T("����"), LVCFMT_CENTER, rect.Width() / 6, 1);
	m_Details_WBCList.InsertColumn(2, _T("��λ"), LVCFMT_CENTER, rect.Width() / 6, 2);
	m_Details_WBCList.InsertColumn(3, _T("LL"), LVCFMT_CENTER, rect.Width() / 6, 3);
	m_Details_WBCList.InsertColumn(4, _T("UL"), LVCFMT_CENTER, rect.Width() / 6, 4);
	m_Details_WBCList.InsertColumn(5, _T("Flag"), LVCFMT_CENTER, rect.Width() / 6, 5);

	// ��WBC�б���ͼ�ؼ��в����б���������б������ı�   
	m_Details_WBCList.InsertItem(0, _T("WBC"));
	m_Details_WBCList.SetItemText(0, 2, _T("10^9/L"));
	m_Details_WBCList.InsertItem(1, _T("LYM%"));
	m_Details_WBCList.SetItemText(1, 2, _T("%"));
	m_Details_WBCList.InsertItem(2, _T("NEU%"));
	m_Details_WBCList.SetItemText(2, 2, _T("%"));
	m_Details_WBCList.InsertItem(3, _T("MONO%"));
	m_Details_WBCList.SetItemText(3, 2, _T("%"));
	m_Details_WBCList.InsertItem(4, _T("EOS%"));
	m_Details_WBCList.SetItemText(4, 2, _T("%"));
	m_Details_WBCList.InsertItem(5, _T("BASO%"));
	m_Details_WBCList.SetItemText(5, 2, _T("%"));
	m_Details_WBCList.InsertItem(6, _T("ALY%"));
	m_Details_WBCList.SetItemText(6, 2, _T("%"));
	m_Details_WBCList.InsertItem(7, _T("LIC%"));
	m_Details_WBCList.SetItemText(7, 2, _T("%"));
	m_Details_WBCList.InsertItem(8, _T("LYM%"));
	m_Details_WBCList.SetItemText(8, 2, _T("10^9/L"));
	m_Details_WBCList.InsertItem(9, _T("NEU#"));
	m_Details_WBCList.SetItemText(9, 2, _T("10^9/L"));
	m_Details_WBCList.InsertItem(10, _T("MONO#"));
	m_Details_WBCList.SetItemText(10, 2, _T("10^9/L"));
	m_Details_WBCList.InsertItem(11, _T("EOS#"));
	m_Details_WBCList.SetItemText(11, 2, _T("10^9/L"));
	m_Details_WBCList.InsertItem(12, _T("BASO#"));
	m_Details_WBCList.SetItemText(12, 2, _T("10^9/L"));
	m_Details_WBCList.InsertItem(13, _T("ALY#"));
	m_Details_WBCList.SetItemText(13, 2, _T("10^9/L"));
	m_Details_WBCList.InsertItem(14, _T("LIC#"));
	m_Details_WBCList.SetItemText(14, 2, _T("10^9/L"));

	m_Details_WBCList.SetItemText(0, 1, (CString)psampledata->wbcdata.wbc);
	m_Details_WBCList.SetItemText(1, 1, (CString)psampledata->wbcdata.lymp);
	m_Details_WBCList.SetItemText(2, 1, (CString)psampledata->wbcdata.neup);
	m_Details_WBCList.SetItemText(3, 1, (CString)psampledata->wbcdata.monop);
	m_Details_WBCList.SetItemText(4, 1, (CString)psampledata->wbcdata.eosp);
	m_Details_WBCList.SetItemText(5, 1, (CString)psampledata->wbcdata.basp);
	m_Details_WBCList.SetItemText(6, 1, (CString)psampledata->wbcdata.alyp);
	m_Details_WBCList.SetItemText(7, 1, (CString)psampledata->wbcdata.licp);
	m_Details_WBCList.SetItemText(8, 1, (CString)psampledata->wbcdata.lym);
	m_Details_WBCList.SetItemText(9, 1, (CString)psampledata->wbcdata.neu);
	m_Details_WBCList.SetItemText(10, 1, (CString)psampledata->wbcdata.mono);
	m_Details_WBCList.SetItemText(11, 1, (CString)psampledata->wbcdata.eos);
	m_Details_WBCList.SetItemText(12, 1, (CString)psampledata->wbcdata.bas);
	m_Details_WBCList.SetItemText(13, 1, (CString)psampledata->wbcdata.aly);
	m_Details_WBCList.SetItemText(14, 1, (CString)psampledata->wbcdata.lic);


	int itemCount = 15;
	CString showbuffer;
	uchar type = systemcfg.range.type;
	CString asterisk = "*";
	CString temp[15];
	float tmp[15];
	for (int i = 0; i < itemCount; i++)
	{
		showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][i]);
		m_Details_WBCList.SetItemText(i, 3, showbuffer);
		showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][i + 28]);
		m_Details_WBCList.SetItemText(i, 4, showbuffer);

		if (i == 0){
			temp[i] = (CString)psampledata->wbcdata.wbc;
			tmp[i] = atof(psampledata->wbcdata.wbc);
		}
		if (i == 1){
			temp[i] = (CString)psampledata->wbcdata.lymp;
			tmp[i] = atof(psampledata->wbcdata.lymp);
		}
		if (i == 2){
			temp[i] = (CString)psampledata->wbcdata.neup;
			tmp[i] = atof(psampledata->wbcdata.neup);
		}
		if (i == 3){
			temp[i] = (CString)psampledata->wbcdata.monop;
			tmp[i] = atof(psampledata->wbcdata.monop);
		}
		if (i == 4){
			temp[i] = (CString)psampledata->wbcdata.eosp;
			tmp[i] = atof(psampledata->wbcdata.eosp);
		}
		if (i == 5){
			temp[i] = (CString)psampledata->wbcdata.basp;
			tmp[i] = atof(psampledata->wbcdata.basp);
		}
		if (i == 6){
			temp[i] = (CString)psampledata->wbcdata.alyp;
			tmp[i] = atof(psampledata->wbcdata.alyp);
		}
		if (i == 7)
		{
			temp[i] = (CString)psampledata->wbcdata.licp;
			tmp[i] = atof(psampledata->wbcdata.licp);
		}
		if (i == 8){
			temp[i] = (CString)psampledata->wbcdata.lym;
			tmp[i] = atof(psampledata->wbcdata.lym);
		}
		if (i == 9){
			temp[i] = (CString)psampledata->wbcdata.neu;
			tmp[i] = atof(psampledata->wbcdata.neu);
		}
		if (i == 10){
			temp[i] = (CString)psampledata->wbcdata.mono;
			tmp[i] = atof(psampledata->wbcdata.mono);
		}
		if (i == 11){
			temp[i] = (CString)psampledata->wbcdata.eos;
			tmp[i] = atof(psampledata->wbcdata.eos);
		}
		if (i == 12){
			temp[i] = (CString)psampledata->wbcdata.bas;
			tmp[i] = atof(psampledata->wbcdata.bas);
		}
		if (i == 13){
			temp[i] = (CString)psampledata->wbcdata.aly;
			tmp[i] = atof(psampledata->wbcdata.aly);
		}
		if (i == 14){
			temp[i] = (CString)psampledata->wbcdata.lic;
			tmp[i] = atof(psampledata->wbcdata.lic);
		}
		if (temp[i].Find(asterisk, 0) >= 0)
			m_Details_WBCList.SetItemText(i, 5, _T("*"));
		else if (tmp[i] < systemcfg.range.normal[type][i])
			m_Details_WBCList.SetItemText(i, 5, _T("L"));
		else if (tmp[i] > systemcfg.range.normal[type][i + 28])
			m_Details_WBCList.SetItemText(i, 5, _T("H"));
		else
			m_Details_WBCList.SetItemText(i, 5, _T("N"));
	}

	return TRUE;
}
BOOL CResultDetails::UpdateWBCForm(sample_info* psampledata)
{

	m_Details_WBCList.SetItemText(0, 1, ChartsToCString((psampledata->wbcdata.wbc), sizeof(psampledata->wbcdata.wbc) / sizeof(char)));
	m_Details_WBCList.SetItemText(1, 1, ChartsToCString((psampledata->wbcdata.lymp), sizeof(psampledata->wbcdata.lymp) / sizeof(char)));
	m_Details_WBCList.SetItemText(2, 1, ChartsToCString((psampledata->wbcdata.neup), sizeof(psampledata->wbcdata.neup) / sizeof(char)));
	m_Details_WBCList.SetItemText(3, 1, ChartsToCString((psampledata->wbcdata.monop), sizeof(psampledata->wbcdata.monop) / sizeof(char)));
	m_Details_WBCList.SetItemText(4, 1, ChartsToCString((psampledata->wbcdata.eosp), sizeof(psampledata->wbcdata.eosp) / sizeof(char)));
	m_Details_WBCList.SetItemText(5, 1, ChartsToCString((psampledata->wbcdata.basp), sizeof(psampledata->wbcdata.basp) / sizeof(char)));
	m_Details_WBCList.SetItemText(6, 1, ChartsToCString((psampledata->wbcdata.alyp), sizeof(psampledata->wbcdata.alyp) / sizeof(char)));
	m_Details_WBCList.SetItemText(7, 1, ChartsToCString((psampledata->wbcdata.licp), sizeof(psampledata->wbcdata.licp) / sizeof(char)));
	m_Details_WBCList.SetItemText(8, 1, ChartsToCString((psampledata->wbcdata.lym), sizeof(psampledata->wbcdata.lym) / sizeof(char)));
	m_Details_WBCList.SetItemText(9, 1, ChartsToCString((psampledata->wbcdata.neu), sizeof(psampledata->wbcdata.neu) / sizeof(char)));
	m_Details_WBCList.SetItemText(10, 1, ChartsToCString((psampledata->wbcdata.mono), sizeof(psampledata->wbcdata.mono) / sizeof(char)));
	m_Details_WBCList.SetItemText(11, 1, ChartsToCString((psampledata->wbcdata.eos), sizeof(psampledata->wbcdata.eos) / sizeof(char)));
	m_Details_WBCList.SetItemText(12, 1, ChartsToCString((psampledata->wbcdata.bas), sizeof(psampledata->wbcdata.bas) / sizeof(char)));
	m_Details_WBCList.SetItemText(13, 1, ChartsToCString((psampledata->wbcdata.aly), sizeof(psampledata->wbcdata.aly) / sizeof(char)));
	m_Details_WBCList.SetItemText(14, 1, ChartsToCString((psampledata->wbcdata.lic), sizeof(psampledata->wbcdata.lic) / sizeof(char)));

	int itemCount = 15;
	CString showbuffer;
	uchar type = systemcfg.range.type;
	CString asterisk = "*";
	CString temp[15];
	float tmp[15];
	for (int i = 0; i < itemCount; i++)
	{
		showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][i]);
		m_Details_WBCList.SetItemText(i, 3, showbuffer);
		showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][i + 28]);
		m_Details_WBCList.SetItemText(i, 4, showbuffer);

		if (i == 0){
			temp[i] = (CString)psampledata->wbcdata.wbc;
			tmp[i] = atof(psampledata->wbcdata.wbc);
		}
		if (i == 1){
			temp[i] = (CString)psampledata->wbcdata.lymp;
			tmp[i] = atof(psampledata->wbcdata.lymp);
		}
		if (i == 2){
			temp[i] = (CString)psampledata->wbcdata.neup;
			tmp[i] = atof(psampledata->wbcdata.neup);
		}
		if (i == 3){
			temp[i] = (CString)psampledata->wbcdata.monop;
			tmp[i] = atof(psampledata->wbcdata.monop);
		}
		if (i == 4){
			temp[i] = (CString)psampledata->wbcdata.eosp;
			tmp[i] = atof(psampledata->wbcdata.eosp);
		}
		if (i == 5){
			temp[i] = (CString)psampledata->wbcdata.basp;
			tmp[i] = atof(psampledata->wbcdata.basp);
		}
		if (i == 6){
			temp[i] = (CString)psampledata->wbcdata.alyp;
			tmp[i] = atof(psampledata->wbcdata.alyp);
		}
		if (i == 7)
		{
			temp[i] = (CString)psampledata->wbcdata.licp;
			tmp[i] = atof(psampledata->wbcdata.licp);
		}
		if (i == 8){
			temp[i] = (CString)psampledata->wbcdata.lym;
			tmp[i] = atof(psampledata->wbcdata.lym);
		}
		if (i == 9){
			temp[i] = (CString)psampledata->wbcdata.neu;
			tmp[i] = atof(psampledata->wbcdata.neu);
		}
		if (i == 10){
			temp[i] = (CString)psampledata->wbcdata.mono;
			tmp[i] = atof(psampledata->wbcdata.mono);
		}
		if (i == 11){
			temp[i] = (CString)psampledata->wbcdata.eos;
			tmp[i] = atof(psampledata->wbcdata.eos);
		}
		if (i == 12){
			temp[i] = (CString)psampledata->wbcdata.bas;
			tmp[i] = atof(psampledata->wbcdata.bas);
		}
		if (i == 13){
			temp[i] = (CString)psampledata->wbcdata.aly;
			tmp[i] = atof(psampledata->wbcdata.aly);
		}
		if (i == 14){
			temp[i] = (CString)psampledata->wbcdata.lic;
			tmp[i] = atof(psampledata->wbcdata.lic);
		}
		if (temp[i].Find(asterisk, 0) >= 0)
			m_Details_WBCList.SetItemText(i, 5, _T("*"));
		else if (tmp[i] < systemcfg.range.normal[type][i])
			m_Details_WBCList.SetItemText(i, 5, _T("L"));
		else if (tmp[i] > systemcfg.range.normal[type][i + 28])
			m_Details_WBCList.SetItemText(i, 5, _T("H"));
		else
			m_Details_WBCList.SetItemText(i, 5, _T("N"));
	}


	return TRUE;
}

BOOL CResultDetails::InitRBCForm(sample_info* psampledata)
{
	CRect rect;

	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_Details_RBClist.GetClientRect(&rect);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_Details_RBClist.SetExtendedStyle(m_Details_RBClist.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_Details_RBClist.SetRowHeigt(20);
	// ΪRBC�б���ͼ�ؼ��������  
	m_Details_RBClist.InsertColumn(0, _T("RBC��Ŀ"), LVCFMT_CENTER, rect.Width() / 6, 0);
	m_Details_RBClist.InsertColumn(1, _T("����"), LVCFMT_CENTER, rect.Width() / 6, 1);
	m_Details_RBClist.InsertColumn(2, _T("��λ"), LVCFMT_CENTER, rect.Width() / 6, 2);
	m_Details_RBClist.InsertColumn(3, _T("LL"), LVCFMT_CENTER, rect.Width() / 6, 3);
	m_Details_RBClist.InsertColumn(4, _T("UL"), LVCFMT_CENTER, rect.Width() / 6, 4);
	m_Details_RBClist.InsertColumn(5, _T("Flag"), LVCFMT_CENTER, rect.Width() / 6, 5);

	// ��RBC�б���ͼ�ؼ��в����б���������б������ı�
	m_Details_RBClist.InsertItem(0, _T("RBC"));
	m_Details_RBClist.SetItemText(0, 2, _T("10^12/L"));
	m_Details_RBClist.InsertItem(1, _T("HGB"));
	m_Details_RBClist.SetItemText(1, 2, _T("g/L"));
	m_Details_RBClist.InsertItem(2, _T("HCT"));
	m_Details_RBClist.SetItemText(2, 2, _T("%"));
	m_Details_RBClist.InsertItem(3, _T("MCV"));
	m_Details_RBClist.SetItemText(3, 2, _T("fL"));
	m_Details_RBClist.InsertItem(4, _T("MCH"));
	m_Details_RBClist.SetItemText(4, 2, _T("pg"));
	m_Details_RBClist.InsertItem(5, _T("MCHC"));
	m_Details_RBClist.SetItemText(5, 2, _T("g/L"));
	m_Details_RBClist.InsertItem(6, _T("RDW-CV"));
	m_Details_RBClist.SetItemText(6, 2, _T("%"));
	m_Details_RBClist.InsertItem(7, _T("RDW-SD"));
	m_Details_RBClist.SetItemText(7, 2, _T("fL"));

	m_Details_RBClist.SetItemText(0, 1, (CString)psampledata->rbcdata.rbc);
	m_Details_RBClist.SetItemText(1, 1, (CString)psampledata->rbcdata.hgb);
	m_Details_RBClist.SetItemText(2, 1, (CString)psampledata->rbcdata.hct);
	m_Details_RBClist.SetItemText(3, 1, (CString)psampledata->rbcdata.mcv);
	m_Details_RBClist.SetItemText(4, 1, (CString)psampledata->rbcdata.mch);
	m_Details_RBClist.SetItemText(5, 1, (CString)psampledata->rbcdata.mchc);
	m_Details_RBClist.SetItemText(6, 1, (CString)psampledata->rbcdata.rdwcv);
	m_Details_RBClist.SetItemText(7, 1, (CString)psampledata->rbcdata.rdwsd);


	uchar type = systemcfg.range.type;
	CString showbuffer;
	int preCount = 15;
	int rbcNum = 8;
	CString asterisk = "*";
	CString temp[8];
	float tmp[8];
	for (int i = 0; i < rbcNum; i++){
		showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][i + preCount]);
		m_Details_RBClist.SetItemText(i, 3, showbuffer);
		showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][i + preCount + 28]);
		m_Details_RBClist.SetItemText(i, 4, showbuffer);

		if (i == 0){
			temp[i] = (CString)psampledata->rbcdata.rbc;
			tmp[i] = atof(psampledata->rbcdata.rbc);
		}

		if (i == 1){
			temp[i] = (CString)psampledata->rbcdata.hgb;
			tmp[i] = atof(psampledata->rbcdata.hgb);
		}
		if (i == 2){
			temp[i] = (CString)psampledata->rbcdata.hct;
			tmp[i] = atof(psampledata->rbcdata.hct);
		}
		if (i == 3){
			temp[i] = (CString)psampledata->rbcdata.mcv;
			tmp[i] = atof(psampledata->rbcdata.mcv);
		}
		if (i == 4){
			temp[i] = (CString)psampledata->rbcdata.mch;
			tmp[i] = atof(psampledata->rbcdata.mch);
		}
		if (i == 5){
			temp[i] = (CString)psampledata->rbcdata.mchc;
			tmp[i] = atof(psampledata->rbcdata.mchc);
		}
		if (i == 6){
			temp[i] = (CString)psampledata->rbcdata.rdwcv;
			tmp[i] = atof(psampledata->rbcdata.rdwcv);
		}
		if (i == 7){
			temp[i] = (CString)psampledata->rbcdata.rdwsd;
			tmp[i] = atof(psampledata->rbcdata.rdwsd);
		}
		if (temp[i].Find(asterisk, 0) >= 0)
			m_Details_RBClist.SetItemText(i, 5, _T("*"));
		else if (tmp[i] < systemcfg.range.normal[type][i + preCount])
			m_Details_RBClist.SetItemText(i, 5, _T("L"));
		else if (tmp[i] >  systemcfg.range.normal[type][i + preCount + 28])
			m_Details_RBClist.SetItemText(i, 5, _T("H"));
		else
			m_Details_RBClist.SetItemText(i, 5, _T("N"));
	}

	return TRUE;
}
BOOL CResultDetails::UpdateRBCForm(sample_info* psampledata)
{

	m_Details_RBClist.SetItemText(0, 1, ChartsToCString((psampledata->rbcdata.rbc), sizeof(psampledata->rbcdata.rbc) / sizeof(char)));
	m_Details_RBClist.SetItemText(1, 1, ChartsToCString((psampledata->rbcdata.hgb), sizeof(psampledata->rbcdata.hgb) / sizeof(char)));
	m_Details_RBClist.SetItemText(2, 1, ChartsToCString((psampledata->rbcdata.hct), sizeof(psampledata->rbcdata.hct) / sizeof(char)));
	m_Details_RBClist.SetItemText(3, 1, ChartsToCString((psampledata->rbcdata.mcv), sizeof(psampledata->rbcdata.mcv) / sizeof(char)));
	m_Details_RBClist.SetItemText(4, 1, ChartsToCString((psampledata->rbcdata.mch), sizeof(psampledata->rbcdata.mch) / sizeof(char)));
	m_Details_RBClist.SetItemText(5, 1, ChartsToCString((psampledata->rbcdata.mchc), sizeof(psampledata->rbcdata.mchc) / sizeof(char)));
	m_Details_RBClist.SetItemText(6, 1, ChartsToCString((psampledata->rbcdata.rdwcv), sizeof(psampledata->rbcdata.rdwcv) / sizeof(char)));
	//MessageBox((CString)psampledata->rbcdata.rdwcv);
	m_Details_RBClist.SetItemText(7, 1, ChartsToCString((psampledata->rbcdata.rdwsd), sizeof(psampledata->rbcdata.rdwsd) / sizeof(char)));

	uchar type = systemcfg.range.type;
	CString showbuffer;
	int preCount = 15;
	int rbcNum = 8;
	CString asterisk = "*";
	CString temp[8];
	float tmp[8];
	for (int i = 0; i < rbcNum; i++){
		showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][i + preCount]);
		m_Details_RBClist.SetItemText(i, 3, showbuffer);
		showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][i + preCount + 28]);
		m_Details_RBClist.SetItemText(i, 4, showbuffer);

		if (i == 0){
			temp[i] = (CString)psampledata->rbcdata.rbc;
			tmp[i] = atof(psampledata->rbcdata.rbc);
		}

		if (i == 1){
			temp[i] = (CString)psampledata->rbcdata.hgb;
			tmp[i] = atof(psampledata->rbcdata.hgb);
		}
		if (i == 2){
			temp[i] = (CString)psampledata->rbcdata.hct;
			tmp[i] = atof(psampledata->rbcdata.hct);
		}
		if (i == 3){
			temp[i] = (CString)psampledata->rbcdata.mcv;
			tmp[i] = atof(psampledata->rbcdata.mcv);
		}
		if (i == 4){
			temp[i] = (CString)psampledata->rbcdata.mch;
			tmp[i] = atof(psampledata->rbcdata.mch);
		}
		if (i == 5){
			temp[i] = (CString)psampledata->rbcdata.mchc;
			tmp[i] = atof(psampledata->rbcdata.mchc);
		}
		if (i == 6){
			temp[i] = (CString)psampledata->rbcdata.rdwcv;
			tmp[i] = atof(psampledata->rbcdata.rdwcv);
		}
		if (i == 7){
			temp[i] = (CString)psampledata->rbcdata.rdwsd;
			tmp[i] = atof(psampledata->rbcdata.rdwsd);
		}
		if (temp[i].Find(asterisk, 0) >= 0)
			m_Details_RBClist.SetItemText(i, 5, _T("*"));
		else if (tmp[i] < systemcfg.range.normal[type][i + preCount])
			m_Details_RBClist.SetItemText(i, 5, _T("L"));
		else if (tmp[i] >  systemcfg.range.normal[type][i + preCount + 28])
			m_Details_RBClist.SetItemText(i, 5, _T("H"));
		else
			m_Details_RBClist.SetItemText(i, 5, _T("N"));
	}

	return TRUE;
}

BOOL CResultDetails::InitPLTForm(sample_info* psampledata)
{
	CRect rect;

	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_Details_PLTlist.GetClientRect(&rect);
	m_Details_PLTlist.SetRowHeigt(20);
	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_Details_PLTlist.SetExtendedStyle(m_Details_PLTlist.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	// ΪPLT�б���ͼ�ؼ��������
	m_Details_PLTlist.InsertColumn(0, _T("PLT��Ŀ"), LVCFMT_CENTER, rect.Width() / 6, 0);
	m_Details_PLTlist.InsertColumn(1, _T("����"), LVCFMT_CENTER, rect.Width() / 6, 1);
	m_Details_PLTlist.InsertColumn(2, _T("��λ"), LVCFMT_CENTER, rect.Width() / 6, 2);
	m_Details_PLTlist.InsertColumn(3, _T("LL"), LVCFMT_CENTER, rect.Width() / 6, 3);
	m_Details_PLTlist.InsertColumn(4, _T("UL"), LVCFMT_CENTER, rect.Width() / 6, 4);
	m_Details_PLTlist.InsertColumn(5, _T("Flag"), LVCFMT_CENTER, rect.Width() / 6, 5);

	// ��PLT�б���ͼ�ؼ��в����б���������б������ı�
	m_Details_PLTlist.InsertItem(0, _T("PLT"));
	m_Details_PLTlist.SetItemText(0, 2, _T("10^9/L"));
	m_Details_PLTlist.InsertItem(1, _T("MPV"));
	m_Details_PLTlist.SetItemText(1, 2, _T("fL"));
	m_Details_PLTlist.InsertItem(2, _T("PDW"));
	m_Details_PLTlist.SetItemText(2, 2, _T("fL"));
	m_Details_PLTlist.InsertItem(3, _T("PCT"));
	m_Details_PLTlist.SetItemText(3, 2, _T("%"));
	m_Details_PLTlist.InsertItem(4, _T("P-LCR"));
	m_Details_PLTlist.SetItemText(4, 2, _T("%"));

	m_Details_PLTlist.SetItemText(0, 1, (CString)psampledata->pltdata.plt);
	m_Details_PLTlist.SetItemText(1, 1, (CString)psampledata->pltdata.mpv);
	m_Details_PLTlist.SetItemText(2, 1, (CString)psampledata->pltdata.pdw);
	m_Details_PLTlist.SetItemText(3, 1, (CString)psampledata->pltdata.pct);
	m_Details_PLTlist.SetItemText(4, 1, (CString)psampledata->pltdata.plcr);


	uchar type = systemcfg.range.type;
	CString showbuffer;
	int pltNum = 5;
	CString asterisk = "*";
	CString temp[5];
	float tmp[5];
	for (int i = 0; i < pltNum; i++){
		showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][i + 23]);
		m_Details_PLTlist.SetItemText(i, 3, showbuffer);
		showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][i + 23 + 28]);
		m_Details_PLTlist.SetItemText(i, 4, showbuffer);

		if (i == 0){
			temp[i] = (CString)psampledata->pltdata.plt;
			tmp[i] = atof(psampledata->pltdata.plt);
		}
		if (i == 1){
			temp[i] = (CString)psampledata->pltdata.mpv;
			tmp[i] = atof(psampledata->pltdata.mpv);
		}
		if (i == 2){
			temp[i] = (CString)psampledata->pltdata.pdw;
			tmp[i] = atof(psampledata->pltdata.pdw);
		}
		if (i == 3){
			temp[i] = (CString)psampledata->pltdata.pct;
			tmp[i] = atof(psampledata->pltdata.pct);
		}
		if (i == 4){
			temp[i] = (CString)psampledata->pltdata.plcr;
			tmp[i] = atof(psampledata->pltdata.plcr);
		}

		if (temp[i].Find(asterisk, 0) >= 0)
			m_Details_PLTlist.SetItemText(i, 5, _T("*"));
		else if (tmp[i] < systemcfg.range.normal[type][i + 23])
			m_Details_PLTlist.SetItemText(i, 5, _T("L"));
		else if (tmp[i] >  systemcfg.range.normal[type][i + 23 + 28])
			m_Details_PLTlist.SetItemText(i, 5, _T("H"));
		else
			m_Details_PLTlist.SetItemText(i, 5, _T("N"));
	}



	return TRUE;
}
BOOL CResultDetails::UpdatePLTForm(sample_info* psampledata)
{

	m_Details_PLTlist.SetItemText(0, 1, ChartsToCString((psampledata->pltdata.plt), sizeof(psampledata->pltdata.plt) / sizeof(char)));
	m_Details_PLTlist.SetItemText(1, 1, ChartsToCString((psampledata->pltdata.mpv), sizeof(psampledata->pltdata.mpv) / sizeof(char)));
	m_Details_PLTlist.SetItemText(2, 1, ChartsToCString((psampledata->pltdata.pdw), sizeof(psampledata->pltdata.pdw) / sizeof(char)));
	m_Details_PLTlist.SetItemText(3, 1, ChartsToCString((psampledata->pltdata.pct), sizeof(psampledata->pltdata.pct) / sizeof(char)));
	m_Details_PLTlist.SetItemText(4, 1, ChartsToCString((psampledata->pltdata.plcr), sizeof(psampledata->pltdata.plcr) / sizeof(char)));

	uchar type = systemcfg.range.type;
	CString showbuffer;
	int pltNum = 5;
	CString asterisk = "*";
	CString temp[5];
	float tmp[5];
	for (int i = 0; i < pltNum; i++){
		showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][i + 23]);
		m_Details_PLTlist.SetItemText(i, 3, showbuffer);
		showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][i + 23 + 28]);
		m_Details_PLTlist.SetItemText(i, 4, showbuffer);

		if (i == 0){
			temp[i] = (CString)psampledata->pltdata.plt;
			tmp[i] = atof(psampledata->pltdata.plt);
		}
		if (i == 1){
			temp[i] = (CString)psampledata->pltdata.mpv;
			tmp[i] = atof(psampledata->pltdata.mpv);
		}
		if (i == 2){
			temp[i] = (CString)psampledata->pltdata.pdw;
			tmp[i] = atof(psampledata->pltdata.pdw);
		}
		if (i == 3){
			temp[i] = (CString)psampledata->pltdata.pct;
			tmp[i] = atof(psampledata->pltdata.pct);
		}
		if (i == 4){
			temp[i] = (CString)psampledata->pltdata.plcr;
			tmp[i] = atof(psampledata->pltdata.plcr);
		}

		if (temp[i].Find(asterisk, 0) >= 0)
			m_Details_PLTlist.SetItemText(i, 5, _T("*"));
		else if (tmp[i] < systemcfg.range.normal[type][i + 23])
			m_Details_PLTlist.SetItemText(i, 5, _T("L"));
		else if (tmp[i] >  systemcfg.range.normal[type][i + 23 + 28])
			m_Details_PLTlist.SetItemText(i, 5, _T("H"));
		else
			m_Details_PLTlist.SetItemText(i, 5, _T("N"));
	}

	return TRUE;
}

BOOL CResultDetails::InitRETForm()
{
	CRect rect;
	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_Details_RETlist.GetClientRect(&rect);
	m_Details_RETlist.SetRowHeigt(20);
	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_Details_RETlist.SetExtendedStyle(m_Details_RETlist.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	// ΪRET�б���ͼ�ؼ��������
	m_Details_RETlist.InsertColumn(0, _T("RET��Ŀ"), LVCFMT_CENTER, rect.Width() / 6, 0);
	m_Details_RETlist.InsertColumn(1, _T("����"), LVCFMT_CENTER, rect.Width() / 6, 1);
	m_Details_RETlist.InsertColumn(2, _T("��λ"), LVCFMT_CENTER, rect.Width() / 6, 2);
	m_Details_RETlist.InsertColumn(3, _T("LL"), LVCFMT_CENTER, rect.Width() / 6, 3);
	m_Details_RETlist.InsertColumn(4, _T("UL"), LVCFMT_CENTER, rect.Width() / 6, 4);
	m_Details_RETlist.InsertColumn(5, _T("Flag"), LVCFMT_CENTER, rect.Width() / 6, 5);

	// ��RET�б���ͼ�ؼ��в����б���������б������ı�
	m_Details_RETlist.InsertItem(0, _T("RET%"));
	m_Details_RETlist.SetItemText(0, 2, _T("10^9/L"));
	m_Details_RETlist.InsertItem(1, _T("RET#"));
	m_Details_RETlist.SetItemText(1, 2, _T("fL"));
	m_Details_RETlist.InsertItem(2, _T("RETL"));
	m_Details_RETlist.SetItemText(2, 2, _T("fL"));
	m_Details_RETlist.InsertItem(3, _T("RETM"));
	m_Details_RETlist.SetItemText(3, 2, _T("%"));
	m_Details_RETlist.InsertItem(4, _T("RETH"));
	m_Details_RETlist.SetItemText(4, 2, _T("%"));
	m_Details_RETlist.InsertItem(5, _T("MFI"));
	m_Details_RETlist.SetItemText(5, 2, _T("%"));
	m_Details_RETlist.InsertItem(6, _T("IMM"));
	m_Details_RETlist.SetItemText(6, 2, _T("%"));
	m_Details_RETlist.InsertItem(7, _T("MRV"));
	m_Details_RETlist.SetItemText(7, 2, _T("fL"));
	m_Details_RETlist.InsertItem(8, _T("IRF"));
	m_Details_RETlist.SetItemText(8, 2, _T("%"));
	m_Details_RETlist.InsertItem(9, _T("CRC"));
	m_Details_RETlist.SetItemText(9, 2, _T("%"));

	return TRUE;
}
BOOL CResultDetails::UpdateRETForm()
{
	return TRUE;
}

BOOL CResultDetails::InitCRPForm()
{
	CRect rect;

	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_Details_CRPlist.GetClientRect(&rect);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_Details_CRPlist.SetExtendedStyle(m_Details_CRPlist.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_Details_CRPlist.SetItemColor(0, RGB(100, 125, 100), RGB(15, 235, 150));//�����ض�Item ���� ������ɫ
	m_Details_CRPlist.SetRowHeigt(20);


	// ΪCRP�б���ͼ�ؼ��������
	m_Details_CRPlist.InsertColumn(0, _T("CRP��Ŀ"), LVCFMT_CENTER, rect.Width() / 6, 0);
	m_Details_CRPlist.InsertColumn(1, _T("����"), LVCFMT_CENTER, rect.Width() / 6, 1);
	m_Details_CRPlist.InsertColumn(2, _T("��λ"), LVCFMT_CENTER, rect.Width() / 6, 2);
	m_Details_CRPlist.InsertColumn(3, _T("LL"), LVCFMT_CENTER, rect.Width() / 6, 3);
	m_Details_CRPlist.InsertColumn(4, _T("UL"), LVCFMT_CENTER, rect.Width() / 6, 4);
	m_Details_CRPlist.InsertColumn(5, _T("Flag"), LVCFMT_CENTER, rect.Width() / 6, 5);

	// ��CRP�б���ͼ�ؼ��в����б���������б������ı�
	m_Details_CRPlist.InsertItem(0, _T("CRP"));
	m_Details_CRPlist.SetItemText(0, 2, _T("10^9/L"));


	return TRUE;
}
BOOL CResultDetails::UpdateCRPForm()
{
	return TRUE;
}

BOOL CResultDetails::InitForm(sample_info* psampledata)
{
	InitWBCForm(psampledata);
	InitRBCForm(psampledata);
	InitPLTForm(psampledata);
	InitRETForm();
	InitCRPForm();
	CString			zStatement;
	CString			filename;
	_ConnectionPtr  m_pDB;
	_RecordsetPtr	m_pRs;

	filename.Format(_T("appdata.accdb"));
	//�����ݿ�
	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
	{
		return -1;
	}
	//���ݱ�Ż�ȡ������Ϣ���Ӧ��¼
	CString numofrs;
	//numofrs = pThisResult->numofrs[pThisResult->nownum];
	CString select_doctordata = _T("select * from doctordata");// where number = '") + numofrs + "';";
	//CString select_sampledata = _T("select * from sampledata'");// where number = '") + numofrs + "';";
	_variant_t var;
	ExeSql(m_pDB, m_pRs, select_doctordata);
	try
	{
		if (!m_pRs->BOF){
			m_pRs->MoveFirst();
		}
		else
		{
			TRACE("��������Ϊ��");
			return FALSE;
		}
		while (!m_pRs->adoEOF)
		{


			/*******************************************/
			//��ʾ��Ϣ����һ������Ϊ�У��ڶ�������Ϊ�У�����������Ϊ����

			var = m_pRs->GetCollect("doct_name");
			CString strName;
			if (var.vt != VT_NULL)
				strName = (LPCSTR)_bstr_t(var);
			//	m_PatientResultList.SetItemText(i, 4, strName);
			m_doctor_combo.AddString(strName);
			m_pRs->MoveNext();
		}
		//	ThisResult2.totalnums = m_PatientResultList.GetItemCount();
	}
	catch (_com_error &e)
	{
		TRACE("UpdateResultList�쳣");
	}



	//loaddoctor(m_pDB, m_pRs, *doctordata);
	//���ݱ�Ż�ȡ�������ݱ�Ķ�Ӧ��¼
	CloseDataBase(m_pDB, m_pRs);

	return TRUE;
}
BOOL CResultDetails::UpdateForm(sample_info* psampledata)
{
	UpdateWBCForm(psampledata);
	UpdateRBCForm(psampledata);
	UpdatePLTForm(psampledata);
	UpdateRETForm();
	UpdateCRPForm();
	return TRUE;
}
/***********************�������************************/

void CResultDetails::PrintChart(sample_info *psampledata)
{
	//PrintLMNEChart();
	PrintBASOChart(psampledata);
	PrintRBCChart(psampledata);
	PrintPLTChart(psampledata);
	PrintPieChart();

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

void CResultDetails::Init_B_LMNE(float	coefficient, B_LMNE* p_blmne)
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
void CResultDetails::LmneGraphPaint(sample_info *psampledata, const unsigned char rangetype, CDC &MemDC)
{
	unsigned int i;
	unsigned char res = 0, scatter = 0;	//���迹�źţ���ɢ���ź�
	unsigned char rangeFlag = ' ', doubtFlag = ' ';
	char showbuff[9] = { 0 };
	unsigned char graphbuff[MATRIX_DATA_MAX] = { 0 };

	B_LMNE		m_blmne;
	CRect rect;
	CWnd* pWnd = GetDlgItem(IDC_RESULT_CHART);
	pWnd->GetClientRect(&rect); // ��ȡ�ؼ���Ļ����
	CDC* pDC = pWnd->GetDC();

	//for (int j = 0; j < 1000; j++){
	//	MemDC.SetPixel(j * LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - j * LMNE_HEIGHT / 255, RGB(0, 255, 0));
	//	//		TRACE("***///%d\n",j);
	//}


	if ((*psampledata).coeoflmne > 1.3)
		psampledata->coeoflmne = 1.3;
	else if ((*psampledata).coeoflmne < 0.7)
		psampledata->coeoflmne = 0.7;

	Init_B_LMNE((*psampledata).coeoflmne, &m_blmne);

	//SetTextColor(hdc, COLOR_black);
	if ((*psampledata).wbcdata.wbc[0] == '*')//δ������
	{
		sprintf(showbuff, "%s%s", "   ", (*psampledata).wbcdata.lymp);
		//TextOut(hdc, 85, 35 + 18, showbuff);
		sprintf(showbuff, "%s%s", "   ", (*psampledata).wbcdata.neup);
		//TextOut(hdc, 85, 35 + 36, showbuff);
		sprintf(showbuff, "%s%s", "   ", (*psampledata).wbcdata.monop);
		//TextOut(hdc, 85, 35 + 54, showbuff);
		sprintf(showbuff, "%s%s", "   ", (*psampledata).wbcdata.eosp);
		//TextOut(hdc, 85, 35 + 72, showbuff);
		sprintf(showbuff, "%s%s", "   ", (*psampledata).wbcdata.alyp);
		//TextOut(hdc, 85, 35 + 108, showbuff);
		sprintf(showbuff, "%s%s", "   ", (*psampledata).wbcdata.licp);
		//TextOut(hdc, 85, 35 + 126, showbuff);

		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%s%.1f", "   ", 10 * atof((*psampledata).wbcdata.lym));
		else
			sprintf(showbuff, "%s%s", "   ", (*psampledata).wbcdata.lym);
		//TextOut(hdc, 85, 35 + 144, showbuff);

		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%s%.1f", "   ", 10 * atof((*psampledata).wbcdata.neu));
		else
			sprintf(showbuff, "%s%s", "   ", (*psampledata).wbcdata.neu);
		//TextOut(hdc, 85, 35 + 162, showbuff);

		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%s%.1f", "   ", 10 * atof((*psampledata).wbcdata.mono));
		else
			sprintf(showbuff, "%s%s", "   ", (*psampledata).wbcdata.mono);
		//TextOut(hdc, 85, 35 + 180, showbuff);

		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%s%.1f", "   ", 10 * atof((*psampledata).wbcdata.eos));
		else
			sprintf(showbuff, "%s%s", "   ", (*psampledata).wbcdata.eos);
		//TextOut(hdc, 85, 35 + 198, showbuff);

		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%s%.1f", "   ", 10 * atof((*psampledata).wbcdata.aly));
		else
			sprintf(showbuff, "%s%s", "   ", (*psampledata).wbcdata.aly);
		//TextOut(hdc, 85, 35 + 234, showbuff);

		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%s%.1f", "   ", 10 * atof((*psampledata).wbcdata.lic));
		else
			sprintf(showbuff, "%s%s", "   ", (*psampledata).wbcdata.lic);
		//TextOut(hdc, 85, 35 + 252, showbuff);
	}
	else//���˲���
	{
		if (1 == (*psampledata).flag_wrp[0])
			doubtFlag = ' ';
		else if (2 == (*psampledata).flag_wrp[0])
			doubtFlag = '?';
		else
			doubtFlag = '*';

		//LYMP
		if (atof((*psampledata).wbcdata.lymp) < systemcfg.range.normal[rangetype][LYMP])
			rangeFlag = 'L';
		else if (atof((*psampledata).wbcdata.lymp) > systemcfg.range.normal[rangetype][LYMP + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).wbcdata.lymp);
		//TextOut(hdc, 85, 35 + 18, showbuff);
		//NEUP
		if (atof((*psampledata).wbcdata.neup) < systemcfg.range.normal[rangetype][NEUP])
			rangeFlag = 'L';
		else if (atof((*psampledata).wbcdata.neup) > systemcfg.range.normal[rangetype][NEUP + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).wbcdata.neup);
		//TextOut(hdc, 85, 35 + 36, showbuff);
		//MONOP
		if (atof((*psampledata).wbcdata.monop) < systemcfg.range.normal[rangetype][MONOP])
			rangeFlag = 'L';
		else if (atof((*psampledata).wbcdata.monop) > systemcfg.range.normal[rangetype][MONOP + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).wbcdata.monop);
		//TextOut(hdc, 85, 35 + 54, showbuff);
		//EOSP
		if (atof((*psampledata).wbcdata.eosp) < systemcfg.range.normal[rangetype][EOSP])
			rangeFlag = 'L';
		else if (atof((*psampledata).wbcdata.eosp) > systemcfg.range.normal[rangetype][EOSP + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).wbcdata.eosp);
		//TextOut(hdc, 85, 35 + 72, showbuff);
		//ALYP
		if (atof((*psampledata).wbcdata.alyp) < systemcfg.range.normal[rangetype][ALYP])
			rangeFlag = 'L';
		else if (atof((*psampledata).wbcdata.alyp) > systemcfg.range.normal[rangetype][ALYP + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).wbcdata.alyp);
		//TextOut(hdc, 85, 35 + 108, showbuff);
		//LICP
		if (atof((*psampledata).wbcdata.licp) < systemcfg.range.normal[rangetype][LICP])
			rangeFlag = 'L';
		else if (atof((*psampledata).wbcdata.licp) > systemcfg.range.normal[rangetype][LICP + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).wbcdata.licp);
		//TextOut(hdc, 85, 35 + 126, showbuff);

		//LYM
		if (atof((*psampledata).wbcdata.lym) < systemcfg.range.normal[rangetype][LYMS])
			rangeFlag = 'L';
		else if (atof((*psampledata).wbcdata.lym) > systemcfg.range.normal[rangetype][LYMS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%c%c %.1f", rangeFlag, doubtFlag, 10 * atof((*psampledata).wbcdata.lym));
		else
			sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).wbcdata.lym);
		//TextOut(hdc, 85, 35 + 144, showbuff);
		//NEU
		if (atof((*psampledata).wbcdata.neu) < systemcfg.range.normal[rangetype][NEUS])
			rangeFlag = 'L';
		else if (atof((*psampledata).wbcdata.neu) > systemcfg.range.normal[rangetype][NEUS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%c%c %.1f", rangeFlag, doubtFlag, 10 * atof((*psampledata).wbcdata.neu));
		else
			sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).wbcdata.neu);
		//TextOut(hdc, 85, 35 + 162, showbuff);
		//MONO
		if (atof((*psampledata).wbcdata.mono) < systemcfg.range.normal[rangetype][MONOS])
			rangeFlag = 'L';
		else if (atof((*psampledata).wbcdata.mono) > systemcfg.range.normal[rangetype][MONOS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%c%c %.1f", rangeFlag, doubtFlag, 10 * atof((*psampledata).wbcdata.mono));
		else
			sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).wbcdata.mono);
		//TextOut(hdc, 85, 35 + 180, showbuff);
		//EOS
		if (atof((*psampledata).wbcdata.eos) < systemcfg.range.normal[rangetype][EOSS])
			rangeFlag = 'L';
		else if (atof((*psampledata).wbcdata.eos) > systemcfg.range.normal[rangetype][EOSS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%c%c %.1f", rangeFlag, doubtFlag, 10 * atof((*psampledata).wbcdata.eos));
		else
			sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).wbcdata.eos);
		//TextOut(hdc, 85, 35 + 198, showbuff);
		//ALY
		if (atof((*psampledata).wbcdata.aly) < systemcfg.range.normal[rangetype][ALYS])
			rangeFlag = 'L';
		else if (atof((*psampledata).wbcdata.aly) > systemcfg.range.normal[rangetype][ALYS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%c%c %.1f", rangeFlag, doubtFlag, 10 * atof((*psampledata).wbcdata.aly));
		else
			sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).wbcdata.aly);
		//TextOut(hdc, 85, 35 + 234, showbuff);
		//LIC
		if (atof((*psampledata).wbcdata.lic) < systemcfg.range.normal[rangetype][LICS])
			rangeFlag = 'L';
		else if (atof((*psampledata).wbcdata.lic) > systemcfg.range.normal[rangetype][LICS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%c%c %.1f", rangeFlag, doubtFlag, 10 * atof((*psampledata).wbcdata.lic));
		else
			sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).wbcdata.lic);
		//TextOut(hdc, 85, 35 + 252, showbuff);
	}

	//SetTextColor(hdc, COLOR_red);
	//WBC������Ϣ
	/*	if (2 == (*psampledata).lmneflg[0])
	//TextOut(hdc, 265, 65, "NO");
	if (2 == (*psampledata).lmneflg[1])
	//TextOut(hdc, 265, 83, "LL");
	if (2 == (*psampledata).lmneflg[2])
	//TextOut(hdc, 265, 101, "LL1");
	if (2 == (*psampledata).lmneflg[3])
	//TextOut(hdc, 265, 119, "NL");
	if (2 == (*psampledata).lmneflg[4])
	//TextOut(hdc, 265, 137, "MN");
	if (2 == (*psampledata).lmneflg[5])
	//TextOut(hdc, 265, 155, "RM");
	if (2 == (*psampledata).lmneflg[6])
	//TextOut(hdc, 265, 173, "LN");
	if (2 == (*psampledata).lmneflg[7])
	//TextOut(hdc, 265, 191, "RN");
	if (2 == (*psampledata).lmneflg[8])
	//TextOut(hdc, 265, 209, "NE");*/

	//------------------------------------------------
	//LMNEɢ��ͼ		
	//����0x00�����⴦��ȥ��,�ָ�ԭʼ����
	for (i = 0; i < MATRIX_DATA_MAX - 1; i++){
		graphbuff[i] = (*psampledata).lmnegraph[i] - 1;
		//	TRACE("***///%d\n", graphbuff[i]);
	}

	for (i = 0; i < MATRIX_POINT_MAX - 1; i++)
	{
		res = graphbuff[(i << 1)];
		scatter = graphbuff[(i << 1) + 1];
		//		TRACE("***///%d\n", res);
		//		TRACE("///***%d\n", scatter);
		if (scatter >= m_blmne.Y_NE)
		{
			if (res < m_blmne.X_NOE)
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 0, 0));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_lightwhite);
			else
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(255, 0, 0));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_red);
		}
		else if (scatter >= m_blmne.Y_RMN)
		{
			if (res < m_blmne.X_NON)
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 0, 0));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_lightwhite);
			else if (res < m_blmne.X_LN)
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 250, 0));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_green);
			else if (m_blmne.X_RN)
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 250, 0));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_green);
			else
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 250, 0));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_green);
		}
		else if (scatter >= m_blmne.Y_NL)
		{
			if (res < m_blmne.X_NON)
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 0, 0));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_lightwhite);
			else if (res < m_blmne.X_LN)
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 250, 0));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_green);
			else if (res < m_blmne.X_LMN)
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 250, 0));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_green);
			else if (res < m_blmne.X_MN)
			{
				if ((res - m_blmne.X_LMN)*(m_blmne.Y_RMN - m_blmne.Y_NL) < (m_blmne.X_MN - m_blmne.X_LMN)*(scatter - m_blmne.Y_NL))
					MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 250, 0));
				//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_green);
				else
					MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(230, 30, 70));
				//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_magenta);
			}
			else if (res < m_blmne.X_RM)
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(230, 30, 70));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_magenta);
			else
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(230, 30, 70));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_magenta);
		}
		else
		{
			if (res < m_blmne.X_NOL)
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 0, 0));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_lightwhite);
			else if (res < m_blmne.X_LL)
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 0, 255));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_blue);
			else if (res< m_blmne.X_AL)
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 0, 255));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_blue);
			else if (res < m_blmne.X_LMU)
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 0, 255));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_blue);
			else if (res < m_blmne.X_LMD)
			{
				if ((m_blmne.X_LMD - res*m_blmne.Y_NL) >(m_blmne.X_LMD - m_blmne.X_LMU)*scatter)
					MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter * LMNE_HEIGHT / 255, RGB(0, 0, 255));
				//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter * LMNE_HEIGHT / 255, COLOR_blue);
				else
					MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter* LMNE_HEIGHT / 255, RGB(230, 30, 70));
				//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter* LMNE_HEIGHT / 255, COLOR_magenta);
			}
			else if (res < m_blmne.X_RM)
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(230, 30, 70));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_magenta);
			else
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(230, 30, 70));
			//SetPixel(hdc, res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, COLOR_magenta);
		}
	}
}
//�����ڿ���
void CResultDetails::PrintLMNEChart(sample_info *psampledata)
{
	CRect rect;
	CWnd* pWnd = GetDlgItem(IDC_RESULT_CHART);
	pWnd->GetClientRect(&rect); // ��ȡ�ؼ���Ļ����
	CDC* pDC = pWnd->GetDC();

	CDC MemDC;
	CBitmap bmp;
	MemDC.CreateCompatibleDC(pDC);
	bmp.CreateCompatibleBitmap(pDC, 267, 282);
	MemDC.SelectObject(&bmp);

	MemDC.FillSolidRect(rect.left, rect.top, 267, 282, RGB(255, 255, 255));
	//	MemDC.MoveTo(0, 0);
	//	MemDC.LineTo(100, 100);
	MemDC.SetViewportOrg(0, 280 - rect.Height());



	MemDC.SetViewportOrg(0, 0);
	MemDC.SelectStockObject(WHITE_BRUSH);
	MemDC.Rectangle(rect);
	CPen cpen, pen;
	pen.CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	MemDC.SelectObject(&pen);
	MemDC.SetViewportOrg(0, 0);
	MemDC.LineTo(0, rect.Height());
	MemDC.LineTo(rect.Width(), rect.Height());
	MemDC.LineTo(rect.Width(), 0);
	MemDC.LineTo(0, 0);
	pen.~CPen();

	pen.CreatePen(PS_SOLID, 1, RGB(96, 96, 96));
	MemDC.SelectObject(&pen);
	MemDC.SetViewportOrg(0, 280);
	MemDC.LineTo(255, 0);
	MemDC.LineTo(255, -255);
	MemDC.LineTo(0, -255);
	MemDC.LineTo(0, 0);
	MemDC.TextOut(0, -280, "LMNE:");
	MemDC.MoveTo(255, 0);
	MemDC.LineTo(265, 0);
	MemDC.LineTo(265, -255);
	MemDC.LineTo(255, -255);

	unsigned char i;

	int 		x1, x2, y1, y2;
	B_LMNE		m_blmne;
	double		coe_w = LMNE_WIDTH / 255.0;
	double		coe_h = LMNE_HEIGHT / 255.0;

	if ((*psampledata).coeoflmne > 1.3)
		psampledata->coeoflmne = 1.3;
	else if ((*psampledata).coeoflmne < 0.7)
		psampledata->coeoflmne = 0.7;
	Init_B_LMNE((*psampledata).coeoflmne, &m_blmne);
	//------------------------------------------------
	//LMNE
	//line 1 (NOL,0)->(NOL,NL)
	x1 = m_blmne.X_NOL * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM;
	x2 = x1;
	y2 = LMNE_BOTTOM - m_blmne.Y_NL * coe_h;
	MemDC.MoveTo(x1, y1);
	MemDC.LineTo(x2, y2);

	//line 2 (NON,NL)->(NON,NE)
	x1 = m_blmne.X_NON * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_NL * coe_h;
	x2 = x1;
	y2 = LMNE_BOTTOM - m_blmne.Y_NE * coe_h;
	MemDC.MoveTo(x1, y1);
	MemDC.LineTo(x2, y2);
	//line 3 (LL,0)->(LL,NL)
	x1 = m_blmne.X_LL * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM;
	x2 = x1;
	y2 = LMNE_BOTTOM - m_blmne.Y_NL * coe_h;
	for (i = 0; i * 3 < y1 - y2;)
	{
		MemDC.MoveTo(x1, y2 + i * 3);
		MemDC.LineTo(x1, y2 + i * 3 + 3);
		i += 2;	// ....  ....  ....
	}
	//line 4 (LN,NL)->(LN,NE)
	x1 = m_blmne.X_LN * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_NL * coe_h;
	x2 = x1;
	y2 = LMNE_BOTTOM - m_blmne.Y_NE * coe_h;
	for (i = 0; i * 3 < y1 - y2;)
	{
		MemDC.MoveTo(x1, y2 + i * 3);
		MemDC.LineTo(x1, y2 + i * 3 + 3);
		i += 2;
	}

	//line 5 (NOE,NE)->(NOE,256)
	x1 = m_blmne.X_NOE*coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_NE*coe_h;
	x2 = x1;
	y2 = LMNE_BOTTOM - LMNE_HEIGHT;
	MemDC.MoveTo(x1, y1);
	MemDC.LineTo(x2, y2);

	//line 6/10 (LMN,NL)->(MN,RMN)
	x1 = m_blmne.X_LMN * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_NL * coe_h;
	x2 = m_blmne.X_MN * coe_w + LMNE_LEFT;
	y2 = LMNE_BOTTOM - m_blmne.Y_RMN * coe_h;
	MemDC.MoveTo(x1, y1);
	MemDC.LineTo(x2, y2);

	//line 7 (AL,0)->(AL,NL)
	x1 = m_blmne.X_AL * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM;
	x2 = x1;
	y2 = LMNE_BOTTOM - m_blmne.Y_NL*coe_h;
	for (i = 0; i * 3 < y1 - y2;)
	{
		MemDC.MoveTo(x1, y2 + i * 3);
		MemDC.LineTo(x1, y2 + i * 3 + 3);
		i += 2;
	}

	//line 8/9 (LMU,NL)->(LMD,0)
	x1 = m_blmne.X_LMU * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_NL * coe_h;
	x2 = m_blmne.X_LMD * coe_w + LMNE_LEFT;
	y2 = LMNE_BOTTOM;
	MemDC.MoveTo(x1, y1);
	MemDC.LineTo(x2, y2);

	//line 11 (RM,0)->(RM,RMN)
	x1 = m_blmne.X_RM * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM;
	x2 = x1;
	y2 = LMNE_BOTTOM - m_blmne.Y_RMN * coe_h;
	MemDC.MoveTo(x1, y1);
	MemDC.LineTo(x2, y2);

	//line 12 (RN,RMN)->(RN,NE)
	x1 = m_blmne.X_RN * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_RMN * coe_h;
	x2 = x1;
	y2 = LMNE_BOTTOM - m_blmne.Y_NE * coe_h;
	MemDC.MoveTo(x1, y1);
	MemDC.LineTo(x2, y2);

	//line 13 (NOL,NL)->(LMU,NL)
	x1 = m_blmne.X_NOL * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_NL * coe_h;
	x2 = m_blmne.X_LMU * coe_w + LMNE_LEFT;
	y2 = y1;
	MemDC.MoveTo(x1, y1);
	MemDC.LineTo(x2, y2);

	//line 14 (MN,RMN)->(256,RMN)
	x1 = m_blmne.X_MN * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_RMN * coe_h;
	x2 = LMNE_WIDTH + LMNE_LEFT;
	y2 = y1;
	MemDC.MoveTo(x1, y1);
	MemDC.LineTo(x2, y2);

	//line 15 (NON,NE)->(256,NE)
	x1 = m_blmne.X_NON * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_NE * coe_h;
	x2 = LMNE_WIDTH + LMNE_LEFT;
	y2 = y1;
	MemDC.MoveTo(x1, y1);
	MemDC.LineTo(x2, y2);


	LmneGraphPaint(sampledata, patientdata->rangetype, MemDC);

	MemDC.SetViewportOrg(0, 0);
	pDC->BitBlt(0, rect.Height() - 280, 267, 282, &MemDC, 0, 0, SRCCOPY);
	MemDC.DeleteDC();
	bmp.DeleteObject();
	GetDlgItem(IDC_RESULT_CHART)->EnableWindow(FALSE);
}

void CResultDetails::UpdatePrintChart(sample_info *psampledata)
{
	UpdateData();
	OnPaint();
	UpdatePrintBASOChart(psampledata);
	UpdatePrintRBCChart(psampledata);
	UpdatePrintPLTChart(psampledata);
	UpdatePrintPieChart();
}

void CResultDetails::PrintLMNEChart()
{


	UpdateData();
	CRect rect;
	CDC *pDC = new CDC;
	pDC = GetDlgItem(IDC_RESULT_CHART)->GetDC();
	GetDlgItem(IDC_RESULT_CHART)->GetWindowRect(&rect);//��ȡ�ؼ�����Ļ����
	ScreenToClient(&rect);//ת��Ϊ�Ի����ϵĿͻ�����
	pDC->SelectStockObject(BLACK_BRUSH);
	pDC->Rectangle(&rect);
	//free(pDC);

	/*CDC *pDC1 = new CDC;
	HDC hdc;
	CView* pActiveView = ((CFrameWnd*)(AfxGetApp()->m_pMainWnd))->GetActiveView();
	HWND testwnd = pActiveView->GetSafeHwnd();
	hdc = ::GetDC(testwnd);
	pDC1->Attach(hdc);
	CPen pen(PS_SOLID, 1, RGB(255, 255, 255));
	pDC1->SelectObject(&pen);
	int orgin = 30;
	//pDC1->MoveTo(orgin,orgin);
	//pDC1->LineTo(orgin, orgin + 200);
	MoveToEx(hdc, orgin, orgin, NULL);
	LineTo(hdc, orgin, orgin + 200);
	LineTo(hdc, orgin + 200, orgin + 200);
	LineTo(hdc, orgin + 200, orgin);
	LineTo(hdc, orgin, orgin);
	MoveToEx(hdc, orgin + 180, orgin, NULL);
	LineTo(hdc, orgin + 180, orgin + 200);
	MoveToEx(hdc, orgin + 30, orgin + 200, NULL);
	LineTo(hdc, orgin + 30, orgin + 150);
	LineTo(hdc, orgin + 120, orgin + 150);
	for (int i = 1; i <= 25; i++){
	LineTo(hdc, orgin + 120 + i, orgin + 150 + 2 * i);
	}
	SetPixel(hdc, 70, 70, RGB(255, 0, 0));
	SetPixel(hdc, 70, 67, RGB(255, 0, 0));
	SetPixel(hdc, 70, 68, RGB(255, 0, 0));
	SetPixel(hdc, 69, 67, RGB(255, 0, 0));
	SetPixel(hdc, 71, 67, RGB(255, 0, 0));
	SetPixel(hdc, 69, 71, RGB(255, 0, 0));
	SetPixel(hdc, 72, 72, RGB(255, 0, 0));
	SetPixel(hdc, 68, 67, RGB(255, 0, 0));
	SetPixel(hdc, 69, 72, RGB(255, 0, 0));
	SetPixel(hdc, 68, 72, RGB(255, 0, 0));
	::ReleaseDC(testwnd, hdc);

	free(pDC1);*/

}
void CResultDetails::UpdatePrintLMNEChart()
{
	UpdateData();
	//CRect rect;
	//CDC *pDC = new CDC;
	//pDC = GetDlgItem(IDC_RESULT_CHART)->GetDC();
	//GetDlgItem(IDC_RESULT_CHART)->GetWindowRect(&rect);//��ȡ�ؼ�����Ļ����
	//ScreenToClient(&rect);//ת��Ϊ�Ի����ϵĿͻ�����
	//pDC->SelectStockObject(BLACK_BRUSH);
	////CRect rect(0, 0, 220, 220);
	//pDC->Rectangle(&rect);

}


void CResultDetails::PrintBASOChart(sample_info *psampledata)
{
	UpdateData();
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
		graphbuff[i] = (psampledata->basograph[i] - 1);

	//������[0,204]��204����ʾ��ȥ��һЩ�㣬ÿ���Ԫ��ȥ���м�һ����
	for (i = 0; i < 204; i++)
	{
		graphbuff[i] = graphbuff[i + (i + 2) / 4];
		pSeries1->AddDataPoint(graphbuff[i]);
	}

	SetDefaultLineWidth();
	SetObjectColors();
	pChart->SetSeriesShadow();
}

void CResultDetails::UpdatePrintBASOChart(sample_info *psampledata)
{
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
		graphbuff[i] = (psampledata->basograph[i] - 1);

	//������[0,204]��204����ʾ��ȥ��һЩ�㣬ÿ���Ԫ��ȥ���м�һ����
	for (i = 0; i < 204; i++)
	{
		graphbuff[i] = graphbuff[i + (i + 2) / 4];
		pSeries1->AddDataPoint(graphbuff[i]);
	}

	SetDefaultLineWidth();
	SetObjectColors();
	pChart->SetSeriesShadow();

	pChart->Redraw();

}

void CResultDetails::PrintRBCChart(sample_info *psampledata)
{
	UpdateData();
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
		graphbuff[i] = ((psampledata->rbcgraph[(i << 1) + 1] - 1) << 8) + psampledata->rbcgraph[i << 1] - 1;

	//������[0,204]��204����ʾ��ȥ��һЩ�㣬ÿ���Ԫ��ȥ���м�һ����
	for (i = 0; i < 204; i++)
	{
		graphbuff[i] = graphbuff[i + (i + 2) / 4];
		pSeries1->AddDataPoint(graphbuff[i]);
	}

}
void CResultDetails::UpdatePrintRBCChart(sample_info *psampledata)
{
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
		graphbuff[i] = ((psampledata->rbcgraph[(i << 1) + 1] - 1) << 8) + psampledata->rbcgraph[i << 1] - 1;

	//������[0,204]��204����ʾ��ȥ��һЩ�㣬ÿ���Ԫ��ȥ���м�һ����
	for (i = 0; i < 204; i++)
	{
		graphbuff[i] = graphbuff[i + (i + 2) / 4];
		pSeries1->AddDataPoint(graphbuff[i]);
	}
	pChart->Redraw();
}

void CResultDetails::PrintPLTChart(sample_info *psampledata)
{
	UpdateData();
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
		graphbuff[i] = psampledata->pltgraph[i] - 1;

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

	SetDefaultLineWidth();
	SetObjectColors();

	pChart->SetSeriesShadow();

}
void CResultDetails::UpdatePrintPLTChart(sample_info *psampledata)
{
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
		graphbuff[i] = psampledata->pltgraph[i] - 1;

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

	SetDefaultLineWidth();
	SetObjectColors();

	pChart->SetSeriesShadow();
	pChart->Redraw();
}

void CResultDetails::PrintPieChart()
{
	UpdateData();
	m_PieChart.EnableTooltip();

	CBCGPChartVisualObject* pChart = m_PieChart.GetChart();
	ASSERT_VALID(pChart);
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


}
void CResultDetails::UpdatePrintPieChart()
{
	UpdateData();
	m_PieChart.EnableTooltip();

	CBCGPChartVisualObject* pChart = m_PieChart.GetChart();
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


}

void CResultDetails::SetObjectColors()
{
	/*m_brFill1 = m_bIsDarkBackground ? CBCGPBrush(CBCGPColor::CadetBlue, .5) : CBCGPBrush(CBCGPColor::RoyalBlue, .2);
	m_brFill2 = m_bIsDarkBackground ? CBCGPBrush(CBCGPColor::ForestGreen, .5) : CBCGPBrush(CBCGPColor::Peru, .2);
	m_brFill3 = CBCGPBrush(CBCGPColor::LightSkyBlue, CBCGPColor::White, CBCGPBrush::BCGP_GRADIENT_DIAGONAL_LEFT, m_bIsDarkBackground ? .9 : .4);
	m_brFill4 = CBCGPBrush(CBCGPColor::LightYellow);
	m_brLine1 = CBCGPBrush(CBCGPColor::DarkRed);
	m_brLine2 = CBCGPBrush(CBCGPColor::DeepSkyBlue);
	m_brText1 = CBCGPBrush(CBCGPColor::SteelBlue);
	m_brText2 = CBCGPBrush(CBCGPColor::Brown);
	OnUpdateChart();*/
}


BOOL CResultDetails::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	OnPaint();
	return CBCGPChartExampleView::OnEraseBkgnd(pDC);
}

void CResultDetails::OnResultUpload()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

int CResultDetails::LoadChoseRecord(pResultToDisplay pThisResult)
{
	CString			zStatement;
	CString			filename;
	_ConnectionPtr  m_pDB;
	_RecordsetPtr	m_pRs;

	filename.Format(_T("appdata.accdb"));
	//�����ݿ�
	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
	{
		return -1;
	}
	//���ݱ�Ż�ȡ������Ϣ���Ӧ��¼
	CString numofrs;
	numofrs = pThisResult->numofrs[pThisResult->nownum];
	CString select_patientdata = _T("select * from patientdata where number = '") + numofrs + "';";
	CString select_sampledata = _T("select * from sampledata where number = '") + numofrs + "';";

	ExeSql(m_pDB, m_pRs, select_patientdata);
	loadpatient(m_pDB, m_pRs, *patientdata);
	//���ݱ�Ż�ȡ�������ݱ�Ķ�Ӧ��¼

	ExeSql(m_pDB, m_pRs, select_sampledata);
	loadresult(m_pDB, m_pRs, *sampledata);
	CloseDataBase(m_pDB, m_pRs);
}

void CResultDetails::OnViewBack()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (pThisResult->nownum > 0);
	{
		pThisResult->nownum--;
		LoadChoseRecord(pThisResult);
		UpdateForm(sampledata);
		UpdatePrintChart(sampledata);
		UpdatePrintChart(sampledata);
		InitPaitientInfo(patientdata);
		if (pThisResult->nownum == 0)
		{
			CButton *pBtn = (CButton *)GetDlgItem(IDC_BUTTON1);
			pBtn->EnableWindow(FALSE);
		}
		CButton *pBtn = (CButton *)GetDlgItem(IDC_BUTTON2);
		pBtn->EnableWindow(TRUE);
		UpdateData(FALSE);
	}

}

void CResultDetails::OnViewForward()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (pThisResult->nownum  < (*pThisResult).totalnums - 1)//record_cur��Χ[0 , ResultsList_nRow-1]
	{
		pThisResult->nownum++;
		LoadChoseRecord(pThisResult);
		UpdateForm(sampledata);
		UpdatePrintChart(sampledata);
		//PrintChart(sampledata);//�˾�֮ǰ��Ҫ����ԭͼ���������������ͼ�񸲸�
		UpdatePrintChart(sampledata);
		InitPaitientInfo(patientdata);
		if (pThisResult->nownum == (*pThisResult).totalnums - 1)
		{
			CButton *pBtn = (CButton *)GetDlgItem(IDC_BUTTON2);
			pBtn->EnableWindow(FALSE);
		}
		CButton *pBtn = (CButton *)GetDlgItem(IDC_BUTTON1);
		pBtn->EnableWindow(TRUE);
		UpdateData(FALSE);
	}
}

BOOL CResultDetails::OnPreparePrinting(CPrintInfo* pInfo)
{

	// TODO:  ���� DoPreparePrinting �Ե��á���ӡ���Ի���

	pInfo->SetMinPage(1);
	pInfo->SetMaxPage(m_reportGenerator.CalculatePages());
	return DoPreparePrinting(pInfo);
}


void CResultDetails::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO:  �ڴ����ר�ô����/����û���

	//CBCGPChartExampleView::OnPrint(pDC, pInfo);
	m_reportGenerator.PrintPage(pDC, pInfo->m_nCurPage);
}

void CResultDetails::GetSample_Data(char uch[28][12], sample_info * sampleinfo)
{
	uchar i = 0;
	strcpy(uch[0], (*sampleinfo).wbcdata.wbc);
	strcpy(uch[1], (*sampleinfo).wbcdata.lymp);
	strcpy(uch[2], (*sampleinfo).wbcdata.neup);
	strcpy(uch[3], (*sampleinfo).wbcdata.monop);
	strcpy(uch[4], (*sampleinfo).wbcdata.eosp);
	strcpy(uch[5], (*sampleinfo).wbcdata.basp);
	strcpy(uch[6], (*sampleinfo).wbcdata.alyp);
	strcpy(uch[7], (*sampleinfo).wbcdata.licp);
	strcpy(uch[8], (*sampleinfo).wbcdata.lym);
	strcpy(uch[9], (*sampleinfo).wbcdata.neu);
	strcpy(uch[10], (*sampleinfo).wbcdata.mono);
	strcpy(uch[11], (*sampleinfo).wbcdata.eos);
	strcpy(uch[12], (*sampleinfo).wbcdata.bas);
	strcpy(uch[13], (*sampleinfo).wbcdata.aly);
	strcpy(uch[14], (*sampleinfo).wbcdata.lic);

	strcpy(uch[15], (*sampleinfo).rbcdata.rbc);
	strcpy(uch[16], (*sampleinfo).rbcdata.hgb);
	strcpy(uch[17], (*sampleinfo).rbcdata.hct);
	strcpy(uch[18], (*sampleinfo).rbcdata.mcv);
	strcpy(uch[19], (*sampleinfo).rbcdata.mch);
	strcpy(uch[20], (*sampleinfo).rbcdata.mchc);
	strcpy(uch[21], (*sampleinfo).rbcdata.rdwcv);
	strcpy(uch[22], (*sampleinfo).rbcdata.rdwsd);

	strcpy(uch[23], (*sampleinfo).pltdata.plt);
	strcpy(uch[24], (*sampleinfo).pltdata.mpv);
	strcpy(uch[25], (*sampleinfo).pltdata.pdw);
	strcpy(uch[26], (*sampleinfo).pltdata.pct);
	strcpy(uch[27], (*sampleinfo).pltdata.plcr);

	//if ((*sampleinfo).pltdata.plt>30 && 2 == (*sampleinfo).pltflg[2])
	//	strcat(uch[23], " PL* ");
	//if ((*sampleinfo).pltdata.plt>30 && 2 == (*sampleinfo).pltflg[3])
	//	strcat(uch[23], "AG");

	for (i = 0; i < 28; i++)
		uch[i][11] = '\0';
}

void CResultDetails::GetSample_Range(char range[28][20])
{
	uchar i;
	uchar type = systemcfg.range.type;

	for (i = 0; i < 28; i++)
		sprintf(range[i], "%.1f--%.1f", systemcfg.range.normal[type][i], systemcfg.range.normal[type][i + 28]);
}

void CResultDetails::GetSample_Warn(char warn[28][2], sample_info*sampleinfo)
{
	uchar i;
	uchar type = systemcfg.range.type;
	char cresult[28][12] = { "" };
	unsigned int iresult[28] = { 0 };
	GetSample_Data(cresult, sampleinfo);
	for (i = 0; i < 28; i++)
	{
		iresult[i] = atoi(cresult[i]);
		if (iresult[i]<systemcfg.range.normal[type][i])
			warn[i][0] = 'L';
		else if (iresult[i]>systemcfg.range.normal[type][i + 28])
			warn[i][0] = 'H';
		else
			warn[i][0] = 0;
		warn[i][1] = '\0';
	}
}

void CResultDetails::Init_graphdata_rbc(void)
{
	int i = 0, j = 0;
	graph_rbc_left[0][0] = 0x02;
	graph_rbc_left[1][1] = 0x04;

	graph_rbc[0][0] = 0x0F;
	graph_rbc[0][1] = 0x04;
	graph_rbc[0][2] = 0x02;
	for (i = 0, j = 3; j < RealCO_Dot_LBRP; j++)
		graph_rbc[i][j] = 0x00;
	for (i = 1; i < 6; i++)
	{
		graph_rbc_left[i][0] = 0x00;
		graph_rbc_left[i][1] = 0x00;

		graph_rbc[i][0] = 0xFF;
		for (j = 1; j < RealCO_Dot_LBRP; j++)
			graph_rbc[i][j] = 0x00;
	}

	graph_rbc_left[6][0] = 0x00;
	graph_rbc_left[6][1] = 0x00;
	graph_rbc[6][0] = 0xFC;
	for (j = 1; j < RealCO_Dot_LBRP - 3; j++)
	{
		if (((j + 1) % 42 == 0) && (j < 250))
			graph_rbc[6][j] = 0x1C;
		else
			graph_rbc[6][j] = 0x04;
	}
	graph_rbc[6][RealCO_Dot_LBRP - 3] = 0x15;
	graph_rbc[6][RealCO_Dot_LBRP - 2] = 0x0A;
	graph_rbc[6][RealCO_Dot_LBRP - 1] = 0x04;

}

void CResultDetails::OnSelectResultPrint()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GernerateLMNEBGP();
	GernerateBASOBGP();
	GernerateRBCBGP();
	GerneratePLTBGP();
	WriteSelectReportData(sampledata, patientdata);

}

void CResultDetails::WriteSelectReportData(sample_info* psampledata, patient_info* ppatientdata)
{

	//if (sampleID.GetLength() == 0) return;
	CString file;
	UpdateData();

	if (systemcfg.printercfg.size == 0)
	{
		m_printStyle = 4;
		if (systemcfg.printercfg.format == 0)
		{
			file.Format(L"./rpt/ChReportA4.rpt");

		}
		else file.Format(L"./rpt/NoPicChReportA4.rpt");
		TRACE(file + "\n");
		FillA4Report(file, psampledata, ppatientdata);
	}
	else if (systemcfg.printercfg.size == 1)
	{
		m_printStyle = 5;
		if (systemcfg.printercfg.format == 0)
		{
			file.Format(L"./rpt/ChReportA5.rpt");
		}
		else file.Format(L"./rpt/NoPicChReportA5.rpt");
		TRACE(file + "\n");
		FillA5Report(file, psampledata, ppatientdata);
	}
	//file.Format(L".\rpt\ChReportA%d.rpt", m_printStyle);
}

void CResultDetails::FillA4Report(CString file, sample_info* psampledata, patient_info* ppatientdata)
{

	CString patientID, patientName, sex, age, hospitalname, reportTitle;
	CString department, area, barcode, remarks;

	CString sextemp[3] = { "(��)", "��", "Ů" };
	COleDateTime testTime;

	hospitalname = systemcfg.hospital;
	hospitalname = "SINNOWA";//

	patientName = ppatientdata->name;
	//patientName = "��ΰС˧��";
	sex = sextemp[_ttoi((CString)ppatientdata->sex)];
	age = ppatientdata->age;
	age = "250";

	m_reportGenerator.New();
	if (m_reportGenerator.SetReportfile(file))
	{
		int max = m_reportGenerator.GetTemplateSize(0);
		for (int t = 0; t < max; t++)
		{
			CString name = m_reportGenerator.GetFieldName(t);
			if (name.GetLength())
			{
				int type = m_reportGenerator.GetFieldType(name);
				if (type == FIELD_TYPE_FIELD)
				{
					CString data;
					if (name.Compare(L"Hospital") == 0)
					{
						data.Empty();

						data += hospitalname;
						m_reportGenerator.Add(name, data);
					}
					else if (name.Compare(L"Title") == 0)
					{
						data.Empty();

						data += reportTitle;
						m_reportGenerator.Add(name, data);
					}

					else if (name.Compare(L"Name") == 0)
					{
						data.Empty();
						//LcwLoadString(IDS_STRPRNAME, data);
						data = "�� ����" + patientName;
						m_reportGenerator.Add(name, data);
					}
					else if (name.Compare(L"PatientID") == 0)
					{
						data.Empty();
						CString tempID;
						tempID.Format(L"%d", sampledata->number);
						tempID = "20" + tempID;
						sampleID = tempID;
						data = "���˺ţ�" + sampleID;
						m_reportGenerator.Add(name, data);
					}
					else if (name.Compare(L"SampleType") == 0)
					{
						data.Empty();
						data = "�������ͣ�ȫѪ+5DIFF";
						m_reportGenerator.Add(name, data);
					}

					else if (name.Compare(L"SampleID") == 0)
					{
						data.Empty();

						data = "��Ʒ�ţ�" + sampleID;
						m_reportGenerator.Add(name, data);
					}

					else if (name.Compare(L"Sex") == 0)
					{
						data.Empty();
						data = "�� ��" + sex;
						m_reportGenerator.Add(name, data);
					}
					else if (name.Compare(L"Department") == 0)
					{
						data.Empty();
						//LcwLoadString(IDS_STRPRDEPART, data);
						data = "��   ��" + department;
						m_reportGenerator.Add(name, data);
					}

					else if (name.Compare(L"Area") == 0)
					{
						data.Empty();
						area = "2222";
						data = "��      ����" + area;
						m_reportGenerator.Add(name, data);
					}

					else 	if (name.Compare(L"Barcode") == 0)
					{
						data.Empty();
						//LcwLoadString(IDS_STRPRTREATAREA, data);
						area = "2222";
						data = "����ţ�" + area;
						m_reportGenerator.Add(name, data);
					}

					else if (name.Compare(L"Age") == 0)
					{
						data.Empty();
						//LcwLoadString(IDS_STRPRAGE, data);
						data = "�� �䣺" + age;
						m_reportGenerator.Add(name, data);
					}

					else if (name.Compare(L"Bed") == 0)
					{
						data.Empty();
						//CString tempbed
						data = "��   ����110";
						m_reportGenerator.Add(name, data);
					}

					else if (name.Compare(L"Doctor") == 0)
					{
						data.Empty();
						//LcwLoadString(IDS_STRPRSILKBED, data);
						data = "�ͼ�ҽʦ��";
						m_reportGenerator.Add(name, data);
					}

					else if (name.Compare(L"Remarks") == 0)
					{
						data.Empty();
						//LcwLoadString(IDS_STRPRDOCTOR, data);
						data = "��    ע��";
						m_reportGenerator.Add(name, data);
					}
					else if (name.Compare(L"TestTime") == 0)
					{
						data.Empty();
						data = "���ʱ�䣺";
						m_reportGenerator.Add(name, data);
					}
					else if (name.Compare(L"ReportTime") == 0)
					{
						data.Empty();
						data += "����ʱ�䣺";
						m_reportGenerator.Add(name, data);
					}
					else if (name.Compare(L"Checker") == 0)
					{
						data.Empty();
						data += "�����ߣ�";
						m_reportGenerator.Add(name, data);
					}
					else if (name.Compare(L"Verifier") == 0)
					{
						data.Empty();
						data += "�����";
						m_reportGenerator.Add(name, data);
					}
					else if (name.Compare(L"TestDate") == 0)
					{
						data.Empty();
						data += "ע��";
						m_reportGenerator.Add(name, data);
					}
				}

				//�������ڵĲ���
				else if (type == FIELD_TYPE_GRID)
				{
					//Get number of columns
					int columns = m_reportGenerator.GetFieldColumns(name);
					if (columns > 0)
					{
						char	result[28][12];
						char	range[28][20];
						char	warn[28][2];


						for (int i = 0; i < 28; i++)
						{
							for (int j = 0; j < 12; j++)
							{
								result[i][j] = 0;
							}
							for (int k = 0; k < 20; k++)
							{
								range[i][k] = 0;
							}
							for (int p = 0; p < 2; p++)
							{
								warn[i][p] = 0;
							}
						}

						GetSample_Data(result, sampledata);
						GetSample_Range(range);
						GetSample_Warn(warn, sampledata);
						//���������ڴ˴�
						if (name.Compare(L"Result") == 0)
						{
							if (m_printStyle == 4)
							{
								CStringArray arr;
								CString line;
								CString col;

								int itemCounter = 28;
								arr.Add(itemhead);

								for (int i = 0; i < itemCounter; i++)
								{
									col.Empty();
									line.Empty();
									
									col.Format(L"%d|%s|%s|%s|%s|%s|%s|",
										(i + 1),
										items_shortname[i],
										items_fullname[i],
										(CString)warn[i],
										(CString)result[i],
										unit_info[i],
										(CString)range[i]
										);
									
									line += col;
									arr.Add(line);
									
								}
								
								m_reportGenerator.Add(name, arr);
								arr.RemoveAll();

							}
							else if (m_printStyle == 5)
							{

								CStringArray arr;
								CString line;
								CString col;
								int itemCounter = 15;
								arr.Add(itemhead);
								for (int i = 0; i < itemCounter; i++)
								{
									col.Empty();
									line.Empty();
									col.Format(L"%d|%s|%s|%s|%s|%s|%s|",
										(i + 1),
										items_shortname[i],
										items_fullname[i],
										(CString)warn[i],
										(CString)result[i],
										unit_info[i],
										(CString)range[i]
										);
									line += col;
									arr.Add(line);
								}
								m_reportGenerator.Add(name, arr);
								arr.RemoveAll();
							}

						}
						if (name.Compare(L"Result2") == 0)
						{
							CStringArray arr;
							CString line;
							CString col;

							int itemCounter = 13;
							arr.Add(itemhead);
							for (int i = 0; i < itemCounter; i++)
							{
								col.Empty();
								line.Empty();
								col.Format(L"%d|%s|%s|%s|%s|%s|%s|",
									(i + 1 + 15),
									items_shortname[i + 15],
									items_fullname[i + 15],
									(CString)warn[i + 15],
									(CString)result[i + 15],
									unit_info[i + 15],
									(CString)range[i + 15]
									);
								line += col;
								arr.Add(line);
							}
							m_reportGenerator.Add(name, arr);
							arr.RemoveAll();
						}
					}
				}
				//�����ǵ���AddObject���������ͼƬ
				//CFile file(L"./res/LMNE.bmp",CFile::modeRead);
				//CDrawObject co;
				//m_reportGenerator.AddObject((CDrawObject)file,1);
				else if (type == FIELD_TYPE_PICTURE){
					if (name.Compare(L"LMNEPIC") == 0){
						CString page2;
						page2.Format(L"./rpt/ChReportA5.rpt");
						//m_reportGenerator.AddTemplate(page2,TEMPLATE_TYPE_SECTION);
						
						//MessageBox(L"find LMNEPIC");
					}						
					else if (name.Compare(L"BASOPIC") == 0){
						//MessageBox(L"find BASOPIC");
					}
					else if (name.Compare(L"RBCPIC") == 0){
						//MessageBox(L"find RBCPIC");
					}
					else if (name.Compare(L"PLTPIC") == 0){
						//MessageBox(L"find PLTPIC");
					}

				}
			}
		}
		m_reportGenerator.Print();
	}
	else
		MessageBox(m_reportGenerator.GetErrorMessage());
}

void CResultDetails::FillA5Report(CString file, sample_info* psampledata, patient_info* ppatientdata)
{
	CString patientID, patientName, sex, age, hospitalname, reportTitle;
	CString department, area, barcode, remarks;

	CString sextemp[3] = { "(��)", "��", "Ů" };
	COleDateTime testTime;

	hospitalname = systemcfg.hospital;
	hospitalname = "SINNOWA";//

	patientName = ppatientdata->name;
	patientName = "��ΰС˧��";
	sex = sextemp[_ttoi((CString)ppatientdata->sex)];
	age = ppatientdata->age;
	age = "250";

	m_reportGenerator.New();
	if (m_reportGenerator.SetReportfile(file))
	{
		int max = m_reportGenerator.GetTemplateSize(0);
		for (int t = 0; t < max; t++)
		{
			CString name = m_reportGenerator.GetFieldName(t);
			if (name.GetLength())
			{
				int type = m_reportGenerator.GetFieldType(name);
				if (type == FIELD_TYPE_FIELD)
				{
					CString data;
					if (name.Compare(L"Hospital") == 0)
					{
						data.Empty();

						data += hospitalname;
						m_reportGenerator.Add(name, data);
					}
					if (name.Compare(L"Title") == 0)
					{
						data.Empty();

						data += reportTitle;
						m_reportGenerator.Add(name, data);
					}

					if (name.Compare(L"Name") == 0)
					{
						data.Empty();
						//LcwLoadString(IDS_STRPRNAME, data);
						data = "�� ����" + patientName;
						m_reportGenerator.Add(name, data);
					}
					if (name.Compare(L"PatientID") == 0)
					{
						data.Empty();
						CString tempID;
						tempID.Format(L"%d", sampledata->number);
						tempID = "20" + tempID;
						sampleID = tempID;
						data = "���˺ţ�" + sampleID;
						m_reportGenerator.Add(name, data);
					}

					if (name.Compare(L"SampleType") == 0)
					{
						data.Empty();
						data = "�������ͣ�ȫѪ+5DIFF";
						m_reportGenerator.Add(name, data);
					}

					if (name.Compare(L"SampleID") == 0)
					{
						data.Empty();

						data = "��Ʒ�ţ�" + sampleID;
						m_reportGenerator.Add(name, data);
					}

					if (name.Compare(L"Sex") == 0)
					{
						data.Empty();
						data = "�� ��" + sex;
						m_reportGenerator.Add(name, data);
					}
					if (name.Compare(L"Department") == 0)
					{
						data.Empty();
						//LcwLoadString(IDS_STRPRDEPART, data);
						data = "��   ��" + department;
						m_reportGenerator.Add(name, data);
					}

					if (name.Compare(L"Area") == 0)
					{
						data.Empty();
						area = "2222";
						data = "��      ����" + area;
						m_reportGenerator.Add(name, data);
					}

					if (name.Compare(L"Barcode") == 0)
					{
						data.Empty();
						//LcwLoadString(IDS_STRPRTREATAREA, data);
						area = "2222";
						data = "����ţ�" + area;
						m_reportGenerator.Add(name, data);
					}

					if (name.Compare(L"Age") == 0)
					{
						data.Empty();
						//LcwLoadString(IDS_STRPRAGE, data);
						data = "�� �䣺" + age;
						m_reportGenerator.Add(name, data);
					}

					if (name.Compare(L"Bed") == 0)
					{
						data.Empty();
						//CString tempbed
						data = "��   ����110";
						m_reportGenerator.Add(name, data);
					}

					if (name.Compare(L"Doctor") == 0)
					{
						data.Empty();
						//LcwLoadString(IDS_STRPRSILKBED, data);
						data = "�ͼ�ҽʦ��";
						m_reportGenerator.Add(name, data);
					}

					if (name.Compare(L"Remarks") == 0)
					{
						data.Empty();
						//LcwLoadString(IDS_STRPRDOCTOR, data);
						data = "��    ע��";
						m_reportGenerator.Add(name, data);
					}
					if (name.Compare(L"TestTime") == 0)
					{
						data.Empty();
						data = "���ʱ�䣺";
						m_reportGenerator.Add(name, data);
					}
					if (name.Compare(L"ReportTime") == 0)
					{
						data.Empty();
						data += "����ʱ�䣺";
						m_reportGenerator.Add(name, data);
					}
					if (name.Compare(L"Checker") == 0)
					{
						data.Empty();
						data += "�����ߣ�";
						m_reportGenerator.Add(name, data);
					}
					if (name.Compare(L"Verifier") == 0)
					{
						data.Empty();
						data += "�����";
						m_reportGenerator.Add(name, data);
					}
					if (name.Compare(L"TestDate") == 0)
					{
						data.Empty();
						data += "ע��";
						m_reportGenerator.Add(name, data);
					}
				}

				else if (type == FIELD_TYPE_GRID)
				{
					//Get number of columns
					int columns = m_reportGenerator.GetFieldColumns(name);
					if (columns > 0)
					{
						char	result[28][12];
						char	range[28][20];
						char	warn[28][2];


						for (int i = 0; i < 28; i++)
						{
							for (int j = 0; j < 12; j++)
							{
								result[i][j] = 0;
							}
							for (int k = 0; k < 12; k++)
							{
								range[i][k] = 0;
							}
							for (int p = 0; p < 2; p++)
							{
								warn[i][p] = 0;
							}
						}

						GetSample_Data(result, sampledata);
						GetSample_Range(range);
						GetSample_Warn(warn, sampledata);
						if (name.Compare(L"Result") == 0)
						{
							if (m_printStyle == 4)
							{
								CStringArray arr;
								CString line;
								CString col;

								int itemCounter = 28;
								arr.Add(itemhead);
								for (int i = 0; i < itemCounter; i++)
								{
									col.Empty();
									line.Empty();
									col.Format(L"%d|%s|%s|%s|%s|%s|%s|",
										(i + 1),
										items_shortname[i],
										items_fullname[i],
										(CString)warn[i],
										(CString)result[i],
										unit_info[i],
										(CString)range[i]
										);
									line += col;
									arr.Add(line);
								}
								m_reportGenerator.Add(name, arr);
								arr.RemoveAll();

							}
							else if (m_printStyle == 5)
							{

								CStringArray arr;
								CString line;
								CString col;
								int itemCounter = 15;
								arr.Add(itemhead);
								for (int i = 0; i < itemCounter; i++)
								{
									col.Empty();
									line.Empty();
									col.Format(L"%d|%s|%s|%s|%s|%s|%s|",
										(i + 1),
										items_shortname[i],
										items_fullname[i],
										(CString)warn[i],
										(CString)result[i],
										unit_info[i],
										(CString)range[i]
										);
									line += col;
									arr.Add(line);
								}
								m_reportGenerator.Add(name, arr);
								arr.RemoveAll();
							}

						}
						if (name.Compare(L"Result2") == 0)
						{
							CStringArray arr;
							CString line;
							CString col;

							int itemCounter = 13;
							arr.Add(itemhead);
							for (int i = 0; i < itemCounter; i++)
							{
								col.Empty();
								line.Empty();
								col.Format(L"%d|%s|%s|%s|%s|%s|%s|",
									(i + 1 + 15),
									items_shortname[i + 15],
									items_fullname[i + 15],
									(CString)warn[i + 15],
									(CString)result[i + 15],
									unit_info[i + 15],
									(CString)range[i + 15]
									);
								line += col;
								arr.Add(line);
							}
							m_reportGenerator.Add(name, arr);
							arr.RemoveAll();
						}
					}
				}
			}
		}
		m_reportGenerator.Print();
	}
	else
		MessageBox(m_reportGenerator.GetErrorMessage());

}


void CResultDetails::GernerateLMNEBGP()
{
	CRect rect;
	CImage imag;
	CWnd* pWnd = GetDlgItem(IDC_RESULT_LMNE_CHART);
	pWnd->GetClientRect(&rect); // ��ȡ�ؼ���Ļ����
	CDC* pDC = pWnd->GetDC();

	CDC MemDC;
	CBitmap bmp;
	MemDC.CreateCompatibleDC(pDC);
	bmp.CreateCompatibleBitmap(pDC, 267, 282);
	MemDC.SelectObject(&bmp);

	MemDC.FillSolidRect(rect.left, rect.top, 267, 282, RGB(255, 255, 255));
	//	MemDC.MoveTo(0, 0);
	//	MemDC.LineTo(100, 100);
	MemDC.SetViewportOrg(0, 280 - rect.Height());



	MemDC.SetViewportOrg(0, 0);
	MemDC.SelectStockObject(WHITE_BRUSH);
	MemDC.Rectangle(rect);
	CPen cpen, pen;
	pen.CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	MemDC.SelectObject(&pen);
	MemDC.SetViewportOrg(0, 0);
	MemDC.LineTo(0, rect.Height());
	MemDC.LineTo(rect.Width(), rect.Height());
	MemDC.LineTo(rect.Width(), 0);
	MemDC.LineTo(0, 0);
	pen.~CPen();

	pen.CreatePen(PS_SOLID, 1, RGB(96, 96, 96));
	MemDC.SelectObject(&pen);
	MemDC.SetViewportOrg(0, 280);
	MemDC.LineTo(255, 0);
	MemDC.LineTo(255, -255);
	MemDC.LineTo(0, -255);
	MemDC.LineTo(0, 0);
	MemDC.TextOut(0, -280, "LMNE:");
	//	MemDC.MoveTo(255, 0);
	//	MemDC.LineTo(265, 0);
	//	MemDC.LineTo(265, -255);
	//	MemDC.LineTo(255, -255);

	unsigned char i;

	int 		x1, x2, y1, y2;
	B_LMNE		m_blmne;
	double		coe_w = LMNE_WIDTH / 255.0;
	double		coe_h = LMNE_HEIGHT / 255.0;

	if ((*sampledata).coeoflmne > 1.3)
		sampledata->coeoflmne = 1.3;
	else if ((*sampledata).coeoflmne < 0.7)
		sampledata->coeoflmne = 0.7;
	Init_B_LMNE((*sampledata).coeoflmne, &m_blmne);
	//------------------------------------------------
	//LMNE
	//line 1 (NOL,0)->(NOL,NL)
	x1 = m_blmne.X_NOL * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM;
	x2 = x1;
	y2 = LMNE_BOTTOM - m_blmne.Y_NL * coe_h;
	MemDC.MoveTo(x1, y1);
	MemDC.LineTo(x2, y2);

	//line 2 (NON,NL)->(NON,NE)
	x1 = m_blmne.X_NON * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_NL * coe_h;
	x2 = x1;
	y2 = LMNE_BOTTOM - m_blmne.Y_NE * coe_h;
	MemDC.MoveTo(x1, y1);
	MemDC.LineTo(x2, y2);
	//line 3 (LL,0)->(LL,NL)
	x1 = m_blmne.X_LL * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM;
	x2 = x1;
	y2 = LMNE_BOTTOM - m_blmne.Y_NL * coe_h;
	for (i = 0; i * 3 < y1 - y2;)
	{
		MemDC.MoveTo(x1, y2 + i * 3);
		MemDC.LineTo(x1, y2 + i * 3 + 3);
		i += 2;	// ....  ....  ....
	}
	//line 4 (LN,NL)->(LN,NE)
	x1 = m_blmne.X_LN * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_NL * coe_h;
	x2 = x1;
	y2 = LMNE_BOTTOM - m_blmne.Y_NE * coe_h;
	for (i = 0; i * 3 < y1 - y2;)
	{
		MemDC.MoveTo(x1, y2 + i * 3);
		MemDC.LineTo(x1, y2 + i * 3 + 3);
		i += 2;
	}

	//line 5 (NOE,NE)->(NOE,256)
	x1 = m_blmne.X_NOE*coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_NE*coe_h;
	x2 = x1;
	y2 = LMNE_BOTTOM - LMNE_HEIGHT;
	MemDC.MoveTo(x1, y1);
	MemDC.LineTo(x2, y2);

	//line 6/10 (LMN,NL)->(MN,RMN)
	x1 = m_blmne.X_LMN * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_NL * coe_h;
	x2 = m_blmne.X_MN * coe_w + LMNE_LEFT;
	y2 = LMNE_BOTTOM - m_blmne.Y_RMN * coe_h;
	MemDC.MoveTo(x1, y1);
	MemDC.LineTo(x2, y2);

	//line 7 (AL,0)->(AL,NL)
	x1 = m_blmne.X_AL * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM;
	x2 = x1;
	y2 = LMNE_BOTTOM - m_blmne.Y_NL*coe_h;
	for (i = 0; i * 3 < y1 - y2;)
	{
		MemDC.MoveTo(x1, y2 + i * 3);
		MemDC.LineTo(x1, y2 + i * 3 + 3);
		i += 2;
	}

	//line 8/9 (LMU,NL)->(LMD,0)
	x1 = m_blmne.X_LMU * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_NL * coe_h;
	x2 = m_blmne.X_LMD * coe_w + LMNE_LEFT;
	y2 = LMNE_BOTTOM;
	MemDC.MoveTo(x1, y1);
	MemDC.LineTo(x2, y2);

	//line 11 (RM,0)->(RM,RMN)
	x1 = m_blmne.X_RM * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM;
	x2 = x1;
	y2 = LMNE_BOTTOM - m_blmne.Y_RMN * coe_h;
	MemDC.MoveTo(x1, y1);
	MemDC.LineTo(x2, y2);

	//line 12 (RN,RMN)->(RN,NE)
	x1 = m_blmne.X_RN * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_RMN * coe_h;
	x2 = x1;
	y2 = LMNE_BOTTOM - m_blmne.Y_NE * coe_h;
	MemDC.MoveTo(x1, y1);
	MemDC.LineTo(x2, y2);

	//line 13 (NOL,NL)->(LMU,NL)
	x1 = m_blmne.X_NOL * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_NL * coe_h;
	x2 = m_blmne.X_LMU * coe_w + LMNE_LEFT;
	y2 = y1;
	MemDC.MoveTo(x1, y1);
	MemDC.LineTo(x2, y2);

	//line 14 (MN,RMN)->(256,RMN)
	x1 = m_blmne.X_MN * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_RMN * coe_h;
	x2 = LMNE_WIDTH + LMNE_LEFT;
	y2 = y1;
	MemDC.MoveTo(x1, y1);
	MemDC.LineTo(x2, y2);

	//line 15 (NON,NE)->(256,NE)
	x1 = m_blmne.X_NON * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_NE * coe_h;
	x2 = LMNE_WIDTH + LMNE_LEFT;
	y2 = y1;
	MemDC.MoveTo(x1, y1);
	MemDC.LineTo(x2, y2);


	LmneGraphPaint(sampledata, patientdata->rangetype, MemDC);

	MemDC.SetViewportOrg(0, 0);
	//pDC->BitBlt(0, rect.Height() - 280, 267, 282, &MemDC, 0, 0, SRCCOPY);

	//	GetDlgItem(IDC_RESULT_CHART)->EnableWindow(FALSE);

	//����ͼ�����λͼͼƬ
	imag.Create(267, 282, 24);
	BitBlt(imag.GetDC(), 0, 0, 267, 282, MemDC.m_hDC, 0, 0, SRCCOPY);
	HRESULT hResult = imag.Save(L"./LMNE.bmp");

	MemDC.DeleteDC();
	bmp.DeleteObject();
	imag.ReleaseDC();
	/*
	CDC memDC;
	CBitmap memBitmap, *pOldBitmap;
	CWindowDC dc(GetDesktopWindow());
	memDC.CreateCompatibleDC(&dc);
	int nWidth, nHeight;

	CRect rect;
	//GetDesktopWindow()->GetWindowRect(rect);
	m_LMNEChart.GetWindowRect(&rect);
	//ClientToScreen(&rect);
	nWidth = rect.Width();
	nHeight = rect.Height();
	memBitmap.CreateCompatibleBitmap(&dc, nWidth, nHeight);
	pOldBitmap = memDC.SelectObject(&memBitmap);
	memDC.BitBlt(0, 0, nWidth, nHeight, &dc, rect.left, rect.top, SRCCOPY);

	BITMAPFILEHEADER BMFhead;
	BITMAPINFOHEADER BMIhead;
	BMFhead.bfReserved1 = 0;
	BMFhead.bfReserved2 = 0;
	BMFhead.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	BMFhead.bfSize = BMFhead.bfOffBits + nWidth*nHeight * 4;
	BMFhead.bfType = 0x4d42;

	BMIhead.biBitCount = 32;
	BMIhead.biClrImportant = 0;
	BMIhead.biClrUsed = 0;
	BMIhead.biSizeImage = 0;
	BMIhead.biXPelsPerMeter = 0;
	BMIhead.biYPelsPerMeter = 0;
	BMIhead.biCompression = BI_RGB;
	BMIhead.biHeight = nHeight;
	BMIhead.biPlanes = 1;
	BMIhead.biSize = sizeof(BITMAPINFOHEADER);
	BMIhead.biWidth = nWidth;

	DWORD dwSize = nWidth*nHeight * 4;
	int size = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwSize;
	DWORD *pData = new DWORD[dwSize / 4];
	GetDIBits(memDC.m_hDC, (HBITMAP)memBitmap.m_hObject, 0, nHeight, (BYTE*)pData, (LPBITMAPINFO)&BMIhead, DIB_RGB_COLORS);


	CFile file;
	file.Open(L"./LMNE.bmp", CFile::modeCreate | CFile::modeWrite);
	file.Write(&BMFhead, sizeof(BITMAPFILEHEADER));
	file.Write(&BMIhead, sizeof(BITMAPINFOHEADER));
	file.Write(pData, dwSize);
	file.Close();

	delete pData;
	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	*/
}
void CResultDetails::GernerateBASOBGP()
{
	unsigned char graphbuff[256] = { 0 };
	CImage imag;
	CBitmap memBitmap;
	CRect rect;

	CDC *pdc = m_BASOChart.GetDC();
	CDC memDC;
	memDC.CreateCompatibleDC(pdc);
	m_BASOChart.GetWindowRect(&rect);
	memBitmap.CreateCompatibleBitmap(pdc, rect.Width(), rect.Height());
	memDC.SelectObject(&memBitmap);
	//���ñ���Ϊ��ɫ
	CRgn rectRgn;
	rectRgn.CreateRectRgn(0, 0, rect.Width(), rect.Height());
	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 255, 255));
	memDC.FillRgn(&rectRgn, &brush);

	CPen pen;
	CPen *pOldPen;
	CFont font;
	CFont *pOldfont;

	//��������
	font.CreateFont(12, 3, 0, 0, 400, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, _T("Arial"));
	pOldfont = memDC.SelectObject(&font);

	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	pOldPen = memDC.SelectObject(&pen);

	//������ϵ
	memDC.MoveTo(10, 120);
	memDC.LineTo(220, 120);
	memDC.MoveTo(10, 120);
	memDC.LineTo(10, 0);
	//������̶�
	for (int i = 60; i < 261; i += 50)
	{
		memDC.MoveTo(i, 120);
		memDC.LineTo(i, 123);
	}
	memDC.TextOutW(56, 124, "50");
	memDC.TextOutW(106, 124, "100");
	memDC.TextOutW(156, 124, "150");
	memDC.TextOutW(206, 124, "200");
	//��������̶�
	for (int i = 80; i >= 0; i -= 40)
	{
		memDC.MoveTo(10, i);
		memDC.LineTo(7, i);
	}
	memDC.TextOutW(0, 81, "100");
	memDC.TextOutW(0, 41, "200");
	memDC.TextOutW(0, 1, "300");
	//�ָ�ԭ���Ļ��ʺ�����
	memDC.SelectObject(pOldPen);
	memDC.SelectObject(pOldfont);
	font.DeleteObject();
	pen.DeleteObject();

	pen.CreatePen(PS_SOLID, 1, RGB(0, 100, 0));//���û��ʻ�ͼ
	pOldPen = memDC.SelectObject(&pen);
	memDC.TextOutW(20, 2, "BASO");
	float ratio;//�������갴������С
	ratio = 120.0 / 300.0;
	for (int i = 0; i < 204; i++)
	{
		graphbuff[i] = ratio*sampledata->basograph[i + (i + 2) / 4];
		memDC.MoveTo(i + 10, 120);
		memDC.LineTo(i + 10, 120 - graphbuff[i]);
	}
	//����ͼ�����λͼͼƬ
	imag.Create(rect.Width(), rect.Height(), 24);
	BitBlt(imag.GetDC(), 0, 0, rect.Width(), rect.Height(), memDC.m_hDC, 0, 0, SRCCOPY);
	HRESULT hResult = imag.Save(L"./BASO.bmp");
	ReleaseDC(pdc);
	imag.ReleaseDC();

/*	//MessageBox(L"aaaa");
	CDC memDC;
	CBitmap memBitmap, *pOldBitmap;
	CWindowDC dc(GetDesktopWindow());
	memDC.CreateCompatibleDC(&dc);
	int nWidth, nHeight;

	CRect rect;
	//GetDesktopWindow()->GetWindowRect(rect);
	
	//m_BASOChart.MoveWindow(0, 0, 223, 137);
	//m_BASOChart.MoveWindow(0, 0, 223, 137);
	m_BASOChart.GetWindowRect(&rect);
	//CRect rect1 = rect;
	
	//m_BASOChart.MoveWindow(0, 0, 223, 137);
	m_BASOChart.GetWindowRect(&rect);

	//TRACE(L"\n======left=%d,top=%d,right=%d,bottom=%d\n",rect.left,rect.top,rect.right,rect.bottom);
	//ClientToScreen(&rect);
	nWidth = rect.Width();
	nHeight = rect.Height();

	//TRACE(L"\n===width=%d,height=%d", nWidth, nHeight);

	memBitmap.CreateCompatibleBitmap(&dc, nWidth, nHeight);
	pOldBitmap = memDC.SelectObject(&memBitmap);
	memDC.BitBlt(0, 0, nWidth, nHeight, &dc, rect.left, rect.top, SRCCOPY);

	BITMAPFILEHEADER BMFhead;
	BITMAPINFOHEADER BMIhead;
	BMFhead.bfReserved1 = 0;
	BMFhead.bfReserved2 = 0;
	BMFhead.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	BMFhead.bfSize = BMFhead.bfOffBits + nWidth*nHeight * 4;
	BMFhead.bfType = 0x4d42;

	BMIhead.biBitCount = 32;
	BMIhead.biClrImportant = 0;
	BMIhead.biClrUsed = 0;
	BMIhead.biSizeImage = 0;
	BMIhead.biXPelsPerMeter = 0;
	BMIhead.biYPelsPerMeter = 0;
	BMIhead.biCompression = BI_RGB;
	BMIhead.biHeight = nHeight;
	BMIhead.biPlanes = 1;
	BMIhead.biSize = sizeof(BITMAPINFOHEADER);
	BMIhead.biWidth = nWidth;

	DWORD dwSize = nWidth*nHeight * 4;
	int size = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwSize;
	DWORD *pData = new DWORD[dwSize / 4];
	GetDIBits(memDC.m_hDC, (HBITMAP)memBitmap.m_hObject, 0, nHeight, (BYTE*)pData, (LPBITMAPINFO)&BMIhead, DIB_RGB_COLORS);


	CFile file;
	file.Open(L"./BASO.bmp", CFile::modeCreate | CFile::modeWrite);//�˴�ԭ��Ϊ./res/BASO.bmp
	file.Write(&BMFhead, sizeof(BITMAPFILEHEADER));
	file.Write(&BMIhead, sizeof(BITMAPINFOHEADER));
	file.Write(pData, dwSize);
	file.Close();

	//m_BASOChart.MoveWindow(rect1);

	delete pData;
	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	*/
}

void CResultDetails::GernerateRBCBGP()
{
	unsigned char graphbuff[256] = { 0 };
	CImage imag;
	CBitmap memBitmap;
	CRect rect;

	CDC *pdc = m_RBCChart.GetDC();
	CDC memDC;
	memDC.CreateCompatibleDC(pdc);
	m_RBCChart.GetWindowRect(&rect);
	memBitmap.CreateCompatibleBitmap(pdc, rect.Width(), rect.Height());
	memDC.SelectObject(&memBitmap);
	//���ñ���Ϊ��ɫ
	CRgn rectRgn;
	rectRgn.CreateRectRgn(0, 0, rect.Width(), rect.Height());
	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 255, 255));
	memDC.FillRgn(&rectRgn, &brush);

	CPen pen;
	CPen *pOldPen;
	CFont font;
	CFont *pOldfont;

	//��������
	font.CreateFont(12, 3, 0, 0, 400, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, _T("Arial"));
	pOldfont = memDC.SelectObject(&font);

	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	pOldPen = memDC.SelectObject(&pen);

	//������ϵ
	memDC.MoveTo(10, 120);
	memDC.LineTo(220, 120);
	memDC.MoveTo(10, 120);
	memDC.LineTo(10, 0);
	//������̶�
	for (int i = 60; i < 261; i += 50)
	{
		memDC.MoveTo(i, 120);
		memDC.LineTo(i, 123);
	}
	memDC.TextOutW(56, 124, "50");
	memDC.TextOutW(106, 124, "100");
	memDC.TextOutW(156, 124, "150");
	memDC.TextOutW(206, 124, "200");
	//��������̶�
	for (int i = 80; i >= 0; i -= 40)
	{
		memDC.MoveTo(10, i);
		memDC.LineTo(7, i);
	}
	memDC.TextOutW(0, 81, "100");
	memDC.TextOutW(0, 41, "200");
	memDC.TextOutW(0, 1, "300");
	//�ָ�ԭ���Ļ��ʺ�����
	memDC.SelectObject(pOldPen);
	memDC.SelectObject(pOldfont);
	font.DeleteObject();
	pen.DeleteObject();

	pen.CreatePen(PS_SOLID, 1, RGB(139, 0, 0));//���û��ʻ�ͼ
	pOldPen = memDC.SelectObject(&pen);
	memDC.TextOutW(20, 2, "RBC");
	float ratio;//�������갴������С
	ratio = 120.0 / 300.0;
	for (int i = 0; i < 255; i++)
		graphbuff[i] = ((sampledata->rbcgraph[(i << 1) + 1] - 1) << 8) + sampledata->rbcgraph[i << 1] - 1;

	for (int i = 0; i < 204; i++)
	{
		graphbuff[i] = ratio*graphbuff[i + (i + 2) / 4];
		memDC.MoveTo(i + 10, 120);
		memDC.LineTo(i + 10, 120 - graphbuff[i]);
	}
	//����ͼ�����λͼͼƬ
	imag.Create(rect.Width(), rect.Height(), 24);
	BitBlt(imag.GetDC(), 0, 0, rect.Width(), rect.Height(), memDC.m_hDC, 0, 0, SRCCOPY);
	HRESULT hResult = imag.Save(L"./RBC.bmp");
	ReleaseDC(pdc);
	imag.ReleaseDC();
/*	CDC memDC;
	CBitmap memBitmap, *pOldBitmap;
	CWindowDC dc(GetDesktopWindow());
	memDC.CreateCompatibleDC(&dc);
	int nWidth, nHeight;

	CRect rect;
	//GetDesktopWindow()->GetWindowRect(rect);
	m_RBCChart.GetWindowRect(&rect);
	//ClientToScreen(&rect);
	nWidth = rect.Width();
	nHeight = rect.Height();
	memBitmap.CreateCompatibleBitmap(&dc, nWidth, nHeight);
	pOldBitmap = memDC.SelectObject(&memBitmap);
	memDC.BitBlt(0, 0, nWidth, nHeight, &dc, rect.left, rect.top, SRCCOPY);

	BITMAPFILEHEADER BMFhead;
	BITMAPINFOHEADER BMIhead;
	BMFhead.bfReserved1 = 0;
	BMFhead.bfReserved2 = 0;
	BMFhead.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	BMFhead.bfSize = BMFhead.bfOffBits + nWidth*nHeight * 4;
	BMFhead.bfType = 0x4d42;

	BMIhead.biBitCount = 32;
	BMIhead.biClrImportant = 0;
	BMIhead.biClrUsed = 0;
	BMIhead.biSizeImage = 0;
	BMIhead.biXPelsPerMeter = 0;
	BMIhead.biYPelsPerMeter = 0;
	BMIhead.biCompression = BI_RGB;
	BMIhead.biHeight = nHeight;
	BMIhead.biPlanes = 1;
	BMIhead.biSize = sizeof(BITMAPINFOHEADER);
	BMIhead.biWidth = nWidth;

	DWORD dwSize = nWidth*nHeight * 4;
	int size = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwSize;
	DWORD *pData = new DWORD[dwSize / 4];
	GetDIBits(memDC.m_hDC, (HBITMAP)memBitmap.m_hObject, 0, nHeight, (BYTE*)pData, (LPBITMAPINFO)&BMIhead, DIB_RGB_COLORS);


	CFile file;
	file.Open(L"./RBC.bmp", CFile::modeCreate | CFile::modeWrite);
	file.Write(&BMFhead, sizeof(BITMAPFILEHEADER));
	file.Write(&BMIhead, sizeof(BITMAPINFOHEADER));
	file.Write(pData, dwSize);
	file.Close();

	delete pData;
	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	*/
}
void CResultDetails::GerneratePLTBGP()
{
	unsigned char graphbuff[256] = { 0 };
	CImage imag;
	CBitmap memBitmap;
	CRect rect;

	CDC *pdc = m_PLTChart.GetDC();
	CDC memDC;
	memDC.CreateCompatibleDC(pdc);
	m_PLTChart.GetWindowRect(&rect);
	memBitmap.CreateCompatibleBitmap(pdc, rect.Width(), rect.Height());
	memDC.SelectObject(&memBitmap);
	//���ñ���Ϊ��ɫ
	CRgn rectRgn;
	rectRgn.CreateRectRgn(0, 0, rect.Width(), rect.Height());
	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 255, 255));
	memDC.FillRgn(&rectRgn, &brush);

	CPen pen;
	CPen *pOldPen;
	CFont font;
	CFont *pOldfont;

	//��������
	font.CreateFont(12, 3, 0, 0, 400, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, _T("Arial"));
	pOldfont = memDC.SelectObject(&font);

	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	pOldPen = memDC.SelectObject(&pen);

	//������ϵ
	memDC.MoveTo(10, 120);
	memDC.LineTo(220, 120);
	memDC.MoveTo(10, 120);
	memDC.LineTo(10, 0);
	//������̶�
	for (int i = 60; i < 261; i += 50)
	{
		memDC.MoveTo(i, 120);
		memDC.LineTo(i, 123);
	}
	memDC.TextOutW(56, 124, "50");
	memDC.TextOutW(106, 124, "100");
	memDC.TextOutW(156, 124, "150");
	memDC.TextOutW(206, 124, "200");
	//��������̶�
	for (int i = 80; i >= 0; i -= 40)
	{
		memDC.MoveTo(10, i);
		memDC.LineTo(7, i);
	}
	memDC.TextOutW(0, 81, "100");
	memDC.TextOutW(0, 41, "200");
	memDC.TextOutW(0, 1, "300");
	//�ָ�ԭ���Ļ��ʺ�����
	memDC.SelectObject(pOldPen);
	memDC.SelectObject(pOldfont);
	font.DeleteObject();
	pen.DeleteObject();

	pen.CreatePen(PS_SOLID, 1, RGB(255, 165, 0));//���û��ʻ�ͼ
	pOldPen = memDC.SelectObject(&pen);
	memDC.TextOutW(20, 2, "PLT");
	float ratio;//�������갴������С
	ratio = 120.0 / 300.0;
	for (int i = 0; i < 204; i++)
	{
		graphbuff[i] = ratio*sampledata->pltgraph[i + (i + 2) / 4];
		memDC.MoveTo(i + 10, 120);
		memDC.LineTo(i + 10, 120 - graphbuff[i]);
	}
	//����ͼ�����λͼͼƬ
	imag.Create(rect.Width(), rect.Height(), 24);
	BitBlt(imag.GetDC(), 0, 0, rect.Width(), rect.Height(), memDC.m_hDC, 0, 0, SRCCOPY);
	HRESULT hResult = imag.Save(L"./PLT.bmp");
	ReleaseDC(pdc);
	imag.ReleaseDC();
	/*
	CDC memDC;
	CBitmap memBitmap, *pOldBitmap;
	CWindowDC dc(GetDesktopWindow());
	memDC.CreateCompatibleDC(&dc);
	int nWidth, nHeight;

	CRect rect;
	//GetDesktopWindow()->GetWindowRect(rect);
	m_PLTChart.GetWindowRect(&rect);
	//ClientToScreen(&rect);
	nWidth = rect.Width();
	nHeight = rect.Height();
	memBitmap.CreateCompatibleBitmap(&dc, nWidth, nHeight);
	pOldBitmap = memDC.SelectObject(&memBitmap);
	memDC.BitBlt(0, 0, nWidth, nHeight, &dc, rect.left, rect.top, SRCCOPY);

	BITMAPFILEHEADER BMFhead;
	BITMAPINFOHEADER BMIhead;
	BMFhead.bfReserved1 = 0;
	BMFhead.bfReserved2 = 0;
	BMFhead.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	BMFhead.bfSize = BMFhead.bfOffBits + nWidth*nHeight * 4;
	BMFhead.bfType = 0x4d42;

	BMIhead.biBitCount = 32;
	BMIhead.biClrImportant = 0;
	BMIhead.biClrUsed = 0;
	BMIhead.biSizeImage = 0;
	BMIhead.biXPelsPerMeter = 0;
	BMIhead.biYPelsPerMeter = 0;
	BMIhead.biCompression = BI_RGB;
	BMIhead.biHeight = nHeight;
	BMIhead.biPlanes = 1;
	BMIhead.biSize = sizeof(BITMAPINFOHEADER);
	BMIhead.biWidth = nWidth;

	DWORD dwSize = nWidth*nHeight * 4;
	int size = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwSize;
	DWORD *pData = new DWORD[dwSize / 4];
	GetDIBits(memDC.m_hDC, (HBITMAP)memBitmap.m_hObject, 0, nHeight, (BYTE*)pData, (LPBITMAPINFO)&BMIhead, DIB_RGB_COLORS);


	CFile file;
	file.Open(L"./PLT.bmp", CFile::modeCreate | CFile::modeWrite);
	file.Write(&BMFhead, sizeof(BITMAPFILEHEADER));
	file.Write(&BMIhead, sizeof(BITMAPINFOHEADER));
	file.Write(pData, dwSize);
	file.Close();

	delete pData;
	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	*/
}

void CResultDetails::OnDeleteRecord()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString filename;
	CString number;
	number = pThisResult->numofrs[pThisResult->nownum];
	CString delete_patientdata = "delete from patientdata where number= '" + number + "'";
	CString delete_sampledata = "delete from sampledata where number= '" + number + "'";
	if (IDOK == MessageBox(L"ȷ��ɾ����", L"��ʾ", MB_YESNO | MB_ICONINFORMATION));
	{
		filename.Format(_T("appdata.accdb"));
		_ConnectionPtr m_pDB;
		_RecordsetPtr m_pRs;
		if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
			return;
		ExeSql(m_pDB, m_pRs, delete_patientdata);
		ExeSql(m_pDB, m_pRs, delete_sampledata);
		CloseDataBase(m_pDB, m_pRs);
		pThisResult->totalnums--;
		for (int i = pThisResult->nownum; i < pThisResult->totalnums - 1; i++)
		{
			pThisResult->numofrs[i] = pThisResult->numofrs[i + 1];
		}
		MessageBox(L"ɾ���ɹ���");
		OnViewBack();
	}
}


void CResultDetails::OnBnClickedResultReturn()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CMainFrame* pMf = (CMainFrame*)AfxGetMainWnd();
	CRect rect;
	CRect rect1;
	pMf->GetClentRectEx(rect);

	CRuntimeClass *pClass = RUNTIME_CLASS(CPatientResultView);
	CView* pView = DYNAMIC_DOWNCAST(CView, pClass->CreateObject());

	ASSERT_VALID(pView);
	CDocument* pCurrentDoc = ((CMainFrame*)::AfxGetMainWnd())->GetActiveDocument();

	CCreateContext newContext;
	newContext.m_pNewViewClass = NULL;
	newContext.m_pNewDocTemplate = NULL;
	newContext.m_pLastView = NULL;
	newContext.m_pCurrentFrame = NULL;
	newContext.m_pCurrentDoc = pCurrentDoc;


	if (!pView->Create(NULL, _T(""), (AFX_WS_DEFAULT_VIEW & ~WS_VISIBLE),
		rect, pMf, AFX_IDW_PANE_FIRST + 11, &newContext))
	{
		delete pView;
		return;
	}
	pView->OnInitialUpdate();

	CView* pActiveView = ((CMainFrame*)::AfxGetMainWnd())->GetActiveView();

	UINT temp = ::GetWindowLong(pActiveView->m_hWnd, GWL_ID);
	::SetWindowLong(pActiveView->m_hWnd, GWL_ID,
	::GetWindowLong(pView->m_hWnd, GWL_ID));
	::SetWindowLong(pView->m_hWnd, GWL_ID, temp);
	
	pActiveView->ShowWindow(SW_HIDE);
	pView->ShowWindow(SW_SHOW);
	((CMainFrame*)::AfxGetMainWnd())->SetActiveView(pView);
}


void CResultDetails::OnEnSetfocusResultEdit3()
{
		CString nametemp;
		GetDlgItem(IDC_RESULT_EDIT3)->GetWindowText(nametemp);
		if (nametemp == "(��)")
			nametemp = "";
		// TODO:  �ڴ���ӿؼ�֪ͨ����������
		GetDlgItem(IDC_RESULT_EDIT3)->SetWindowText(nametemp);
}


void CResultDetails::OnEnKillfocusResultEdit3()
{
	CString nametemp;
	GetDlgItem(IDC_RESULT_EDIT3)->GetWindowText(nametemp);
	if (nametemp == "")
		nametemp = "(��)";
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_RESULT_EDIT3)->SetWindowText(nametemp);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CResultDetails::OnEnSetfocusResultEdit4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString agetemp;
	GetDlgItem(IDC_RESULT_EDIT4)->GetWindowText(agetemp);
	if (agetemp == "(��)")
		agetemp = "";
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_RESULT_EDIT4)->SetWindowText(agetemp);
}


void CResultDetails::OnEnKillfocusResultEdit4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString agetemp;
	GetDlgItem(IDC_RESULT_EDIT4)->GetWindowText(agetemp);
	if (agetemp == "")
		agetemp = "(��)";
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_RESULT_EDIT4)->SetWindowText(agetemp);// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CResultDetails::OnEnSetfocusResultEdit5()
{
	CString barcode;
	GetDlgItem(IDC_RESULT_EDIT5)->GetWindowText(barcode);
	if (barcode == "(��)")
		barcode = "";
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_RESULT_EDIT5)->SetWindowText(barcode);// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CResultDetails::OnEnKillfocusResultEdit5()
{
	CString barcode;
	GetDlgItem(IDC_RESULT_EDIT5)->GetWindowText(barcode);
	if (barcode == "")
		barcode = "(��)";
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_RESULT_EDIT5)->SetWindowText(barcode);// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CResultDetails::OnEnSetfocusResultEdit2()
{
	CString rangetype;
	GetDlgItem(IDC_RESULT_EDIT2)->GetWindowText(rangetype);
	if (rangetype == "(��)")
		rangetype = "";
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_RESULT_EDIT2)->SetWindowText(rangetype);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CResultDetails::OnEnKillfocusResultEdit2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString rangetype;
	GetDlgItem(IDC_RESULT_EDIT2)->GetWindowText(rangetype);
	if (rangetype == "")
		rangetype = "(��)";
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_RESULT_EDIT2)->SetWindowText(rangetype);// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CResultDetails::OnBnClickedButton3()
{
	USES_CONVERSION;
	CString m_number, m_sex, m_name, m_age, m_doctor, m_barcode;
	/******����*********/
	GetDlgItem(IDC_RESULT_EDIT1)->GetWindowText(m_number);

	GetDlgItem(IDC_RESULT_EDIT3)->GetWindowText(m_name);

	GetDlgItem(IDC_RESULT_EDIT4)->GetWindowText(m_age);
	GetDlgItem(IDC_RESULT_EDIT5)->GetWindowText(m_barcode);


	char* temp = W2A(m_age);
	strcpy(patientdata->age, temp);
	temp = W2A(m_barcode);
	sprintf(patientdata->code, "%s", temp);
	m_number.Delete(0, 2);
	patientdata->number = _ttoi(m_number);

	patientdata->sex = m_sex_combo.GetCurSel();


	((CComboBox*)GetDlgItem(IDC_RESULT_COMBO_DOCTOR))->GetWindowText(m_doctor);

	temp = W2A(m_doctor);
	sprintf(patientdata->doctor, "%s", temp);


	wchar_t *ptr;
	ptr = m_name.GetBuffer(m_name.GetLength()*sizeof(wchar_t));
	WideCharToMultiByte(CP_ACP, 0, (LPCTSTR)ptr, -1, patientdata->name, sizeof(patientdata->name), NULL, NULL);
	m_name.ReleaseBuffer();


	AddPatientRecord(patientdata);
}
