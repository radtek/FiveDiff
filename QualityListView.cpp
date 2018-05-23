// QualityListView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "afxwin.h"
#include "BCGPChartExample.h"
#include "QualityListView.h"
#include "afxdialogex.h"



// CQualityListView �Ի���

IMPLEMENT_DYNAMIC(CQualityListView, CDialogEx)

CQualityListView::CQualityListView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQualityListView::IDD, pParent)
	, pageNum(_T(""))
	, m_nDrawType(0)
{
	for (int i = 0; i < 26; i++)
	{
		Qctarget[i] = "";
		TargetLimit[i] = "";
	}
	curpage = 0;
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

CQualityListView::~CQualityListView()
{
}

void CQualityListView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_QUALITY_LIST_LIST, m_ListList);
	DDX_Text(pDX, IDC_QUALITY_LIST_PAGE_NUM, pageNum);
}


BEGIN_MESSAGE_MAP(CQualityListView, CDialogEx)
	ON_MESSAGE(UM_REDRAW, OnRedraw)
	ON_BN_CLICKED(IDC_QUALITY_LIST_UP_BUTTON, &CQualityListView::OnBnClickedQualityListUpButton)
	ON_BN_CLICKED(IDC_QUALITY_LIST_DOWN_BUTTON, &CQualityListView::OnBnClickedQualityListDownButton)
	ON_WM_PAINT()
//	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CQualityListView ��Ϣ�������



BOOL CQualityListView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString item_temp;
	switch (Controltype)
	{
	case 0:
		item_temp.Format(L"L-J��ֵ�༭���ļ� %02u��", Controlfile + 1);
		break;
	case 1:
		item_temp.Format(L"X��ֵ�༭���ļ� %02u��", Controlfile + 1);
		break;
	case 2:
		item_temp.Format(L"X-R��ֵ�༭���ļ� %02u��", Controlfile + 1);
		break;
	default:
		break;
	}
	SetDlgItemText(IDC_QUALITY_LIST_STATIC0, item_temp);
	GetDlgItem(IDC_QUALITY_LIST_STATIC0)->SetFont(&textfont);

	GetDlgItem(IDC_QUALITY_LIST_NUMBER)->EnableWindow(false);//�˴��������ź���Ч�ڵ������
	GetDlgItem(IDC_QUALITY_LIST_DEADLINE)->EnableWindow(false);
	
	InitListList();
	GetQcLjEditData();
	itemCount = GetQcLjResultData(Controltype, Controlfile);
	UpdateListResultList();
	maxPage = itemCount % 5 == 0 ? itemCount / 5 -1: itemCount / 5 ;
	
	pageNum.Format(L"�� %d/%d ҳ", curpage+1, maxPage+1);
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void CQualityListView::InitListList()
{
	/***************��ʼ�����**************/
	CRect rect;
	CString table[28] = { "����","ʱ��","WBC", "LYM%", "NEU%", "MONO%", "EOS%", "BASO", "ALY%", "LIC%", "LYM#", "NEU#", "MONO#", "EOS#", "BASO#", "ALY#",
		"LIC#", "RBC", "HGB", "HCT", "MCV", "MCH", "MCHC", "RDW", "PLT", "MPV", "PDW", "PCT" };
	/*	CString unit[] = { _T("10^9/L"), _T("%"), _T("%"), _T("%"), _T("%"),
		_T("%"), _T("%"), _T("%"), _T("10^9/L"), _T("10^9/L"),
		_T("10^9/L"), _T("10^9/L"), _T("10^9/L"), _T("10^9/L"), _T("10^9/L"),_T("10^12/L"), _T("g/L"), _T("%"), _T("fL"),
		_T("pg"), _T("g/L"), _T("%"), _T("fL"), _T("10^9/L"), _T("fL"), _T("fL"), _T("%") };
	*/


	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_ListList.GetClientRect(&rect);
	m_ListList.SetRowHeigt(20);
	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_ListList.SetExtendedStyle(m_ListList.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

		// Ϊ�б���ͼ�ؼ��������;
	m_ListList.InsertColumn(0, _T(""), LVCFMT_CENTER, rect.Width() * 1 / 9, 0);
	m_ListList.InsertColumn(1, _T("��ֵ"), LVCFMT_CENTER, rect.Width() * 1 / 8, 1);
	m_ListList.InsertColumn(2, _T("ƫ����"), LVCFMT_CENTER, rect.Width() * 1 / 8, 2);
	m_ListList.InsertColumn(3, _T("1"), LVCFMT_CENTER, rect.Width() * 1 / 8, 3);
	m_ListList.InsertColumn(4, _T("2"), LVCFMT_CENTER, rect.Width() * 1 / 8, 4);
	m_ListList.InsertColumn(5, _T("3"), LVCFMT_CENTER, rect.Width() * 1 / 8, 5);
	m_ListList.InsertColumn(6, _T("4"), LVCFMT_CENTER, rect.Width() * 1 / 8, 6);
	m_ListList.InsertColumn(7, _T("5"), LVCFMT_CENTER, rect.Width() * 1 / 8, 7);


	// ���б���ͼ�ؼ��в����б���������б������ı�
	//m_ListList.InsertItem(0, _T("WBC"));
	////m_CoefficientList.InsertItem(0, _T(""));
	//m_ListList.InsertItem(1, _T("ƽ��ֵ"));
	//m_ListList.InsertItem(2, _T("CVֵ"));
	//m_ListList.InsertItem(3, _T("��ǰϵ��"));
	//m_ListList.InsertItem(4, _T("��ϵ��"));
	for (int i = 0; i < 28; i++)
	{
		m_ListList.InsertItem(i, table[i]);
	}
	
	/***************����ʼ������**************/
	//m_ListList.SetItemText(0, 4, L"10^9/L");
	//m_ListList.SetItemText(1, 4, L"%");
	//m_ListList.SetItemText(2, 4, L"%");
	//m_ListList.SetItemText(3, 4, L"%");
	//m_ListList.SetItemText(4, 4, L"%");
	//m_ListList.SetItemText(5, 4, L"%");
	//m_ListList.SetItemText(6, 4, L"%");
	//m_ListList.SetItemText(7, 4, L"%");
	//m_ListList.SetItemText(8, 4, L"10^9/L");
	//m_ListList.SetItemText(9, 4, L"10^9/L");
	//m_ListList.SetItemText(10, 4, L"10^9/L");
	//m_ListList.SetItemText(11, 4, L"10^9/L");
	//m_ListList.SetItemText(12, 4, L"10^9/L");
	//m_ListList.SetItemText(13, 4, L"10^9/L");
	//m_ListList.SetItemText(14, 4, L"10^9/L");
	//m_ListList.SetItemText(15, 4, L"10^12/L");
	//m_ListList.SetItemText(16, 4, L"g/L");
	//m_ListList.SetItemText(17, 4, L"%");
	//m_ListList.SetItemText(18, 4, L"fL");
	//m_ListList.SetItemText(19, 4, L"pg");
	//m_ListList.SetItemText(20, 4, L"g/L");
	//m_ListList.SetItemText(21, 4, L"%");
	//m_ListList.SetItemText(22, 4, L"10^9/L");
	//m_ListList.SetItemText(23, 4, L"fL");
	//m_ListList.SetItemText(24, 4, L"fL");
	//m_ListList.SetItemText(25, 4, L"%");

}

//��ȡ��ֵ��ƫ����,�������б���
bool CQualityListView::GetQcLjEditData(){
	CString filename;
	CString	qctypetemp;
	CString qcFileNumtemp;
	filename.Format(_T("appdata.accdb"));
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;

	_variant_t var;
	CString strTemp;
	int temprow;

	qctypetemp.Format(L"%d", Controltype);
	qcFileNumtemp.Format(L"%d", Controlfile);
	CString inital_target = _T("select * from qceditdata where qctype ='") + qctypetemp + "'and filenum ='" + qcFileNumtemp + "';";

	if (-1 == OpenDataBase(filename, m_pDB, m_pRs)){
		//MessageBox(L"Open Failure!");
		return false;
	}
	ExeSql(m_pDB, m_pRs, inital_target);
	try
	{
		if (!m_pRs->BOF){
			m_pRs->MoveFirst();

		}
		else
		{
			TRACE("\n��������Ϊ��!\n");
			//return FALSE;//���ڴ˴���Ҫ������е�������Ϊ�գ����Բ���ֱ�ӷ���
		}
		temprow = int(m_pRs->GetRecordCount());

		//TRACE("\n###temprow=%d\n",temprow);
		//TRACE("\n###nRow=%d", nRow);
		//nRow = temprow;
		if (temprow == 0)//��Ч����Ϊ0���������ֵ
		{
			QcLjFileExist = 0;
			number = "";
			deadline = "";
			GetDlgItem(IDC_QUALITY_LIST_NUMBER)->SetWindowText(number);
			GetDlgItem(IDC_QUALITY_LIST_DEADLINE)->SetWindowText(deadline);
			for (int i = 0; i < 26; i++)
			{
				Qctarget[i] = "";
				TargetLimit[i] = "";
				m_ListList.SetItemText(i, 2, Qctarget[i]);
				m_ListList.SetItemText(i, 1, TargetLimit[i]);
				m_ListList.SetItemText(i, 3, TargetLimit[i]);
			}
		}
		else
		{
			QcLjFileExist = 1;

			var = m_pRs->GetCollect("number");
			if (var.vt != VT_NULL)
			{
				strTemp = m_pRs->GetCollect("number");
				number = (LPCSTR)_bstr_t(var);
				GetDlgItem(IDC_QUALITY_LIST_NUMBER)->SetWindowText(number);
				//��������
			}
			var = m_pRs->GetCollect("deadline");
			if (var.vt != VT_NULL)
			{
				int qctype = m_pRs->GetCollect("deadline");
				deadline.Format(L"%d", qctype);
				GetDlgItem(IDC_QUALITY_LIST_DEADLINE)->SetWindowText(deadline);
				//�����ֹ����
			}

			//�����ֵ
			for (int j = 0; j < 26; j++)
			{
				var = m_pRs->GetFields()->GetItem((long)j + 5)->Value;//��ȡ��ǰ��¼�ʿ�26����Ŀ�İ�ֵ
				Qctarget[j] = var;
				m_ListList.SetItemText(j+2, 1, Qctarget[j]);
			}
			//�������޺�����
			for (int j = 0; j < 26; j++)
			{
				var = m_pRs->GetFields()->GetItem((long)j + 26 + 5)->Value;//��ȡ��ǰ��¼�ʿ�26����Ŀ��ƫ��ֵ
				TargetLimit[j] = var;
				m_ListList.SetItemText(j+2, 2, TargetLimit[j]);

				//double lowLimit = _wtof(Qctarget[j]) - _wtof(TargetLimit[j]);
				//double highimit = _wtof(Qctarget[j]) + _wtof(TargetLimit[j]);
				//CString str;
				//str.Format(L"%.2lf", lowLimit);
				//m_ListList.SetItemText(j, 1, str);
				//str.Format(L"%.2lf", highimit);
				//m_ListList.SetItemText(j, 3, str);
			}

		}
		CloseDataBase(m_pDB, m_pRs);
		return TRUE;
	}
	catch (_com_error &e)
	{
		TRACE("GetQCFile�쳣");
	}
	return false;
}

//��ȡ�ʿؽ��
int CQualityListView::GetQcLjResultData(int controltype, int controlfile){

	CString select_detail;
	CString filename;
	int rownum = 0;
	filename.Format(_T("appdata.accdb"));
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	_variant_t var;
	CString strTemp;
	CString hhTemp;
	CString mmTemp;
	CString ssTemp;
	int k = 0;
	for (int i = 0; i < 31; i++){//����������data��ʼ���
		qcResDate[i].Format(L"%s","");
		qcResTime[i].Format(L"%s", "");
		for (int j = 0; j < 26; j++){
			data[j][i] = -5.0;
		}
	}
//
	select_detail.Format(L"select * from qcresultdata where qctype = '%d' and filenum = '%d' order by date,time;", controltype, controlfile);

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
			var = m_pRs->GetCollect("date");
			if (var.vt != VT_NULL)
			{
				qcResDate[k] = m_pRs->GetCollect("date");
			}

			var = m_pRs->GetCollect("time");
			if (var.vt != VT_NULL)
			{
				qcResTime[k] = m_pRs->GetCollect("time");
				hhTemp = qcResTime[k].Left(2);
				mmTemp = qcResTime[k].Mid(2,2);
				ssTemp = qcResTime[k].Right(2);
				qcResTime[k].Format(L"%s:%s:%s", hhTemp, mmTemp, ssTemp);
			}

			for (int i = 0; i < 26; i++)
			{
				var = m_pRs->GetFields()->GetItem((long)2 + i)->Value;
				if (var.vt != VT_NULL){
					strTemp = (LPCSTR)_bstr_t(var);
					data[i][k] = _wtof(strTemp);
					//UpdateListResultList();
				}
			}
			k++;
			m_pRs->MoveNext();
		}
	}
	catch (_com_error &e)
	{
		TRACE("GetDetail���������쳣\n");
	}
	CloseDataBase(m_pDB, m_pRs);
	return rownum;

}

//����list�ؼ��е����ݣ��ڳ�ʼ������ҳʱ����
void CQualityListView::UpdateListResultList(){
	startIndex = curpage * 5;
	endIndex = curpage * 5 + 4;
	CString strData;
	
	for (int i = startIndex; i <= endIndex; i++){	//��ѭ��������ÿһҳ�еļ�¼����0~4
		if (i > 30){								//�ܹ���ʾ31�����ݣ����������ʾ�հ�
			m_ListList.SetItemText(0, i + 3 - curpage * 5, L"");
			m_ListList.SetItemText(1, i + 3 - curpage * 5, L"");
			for (int j = 0; j < 26; j++){				//��ѭ��������ÿ����¼�Ĳ���
				m_ListList.SetItemText(j + 2, i + 3 - curpage * 5, L"");
			}
		}
		else{
			m_ListList.SetItemText(0, i + 3 - curpage * 5, qcResDate[i]);
			m_ListList.SetItemText(1, i + 3 - curpage * 5, qcResTime[i]);
			for (int j = 0; j < 26; j++){				//��ѭ��������ÿ����¼�Ĳ���
				strData.Format(L"%.2lf", data[j][i]);
				m_ListList.SetItemText(j + 2, i + 3 - curpage * 5, strData);
				if (data[j][i] == -5.0){
					m_ListList.SetItemText(j + 2, i + 3 - curpage * 5, L"");
				}
			}
		}
	}
	pageNum.Format(L"�� %d/%d ҳ", curpage + 1, maxPage + 1);
	UpdateData(false);
}


void CQualityListView::OnBnClickedQualityListUpButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//��ȡҳ�룬�������жϣ��ı�ҳ�룬����resultList
	if (curpage > 0)
	{
		curpage--;
	}
	if (curpage == 0)
	{
		GetDlgItem(IDC_QUALITY_LIST_UP_BUTTON)->EnableWindow(false);
	}
	if (curpage != maxPage)
		GetDlgItem(IDC_QUALITY_LIST_DOWN_BUTTON)->EnableWindow(true);
	//UpdateData();
	UpdateListResultList();

}


void CQualityListView::OnBnClickedQualityListDownButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (curpage <maxPage)
	{
		curpage++;
	}
	if (curpage == maxPage)
	{
		GetDlgItem(IDC_QUALITY_LIST_DOWN_BUTTON)->EnableWindow(false);
	}
	if (curpage != 0)
		GetDlgItem(IDC_QUALITY_LIST_UP_BUTTON)->EnableWindow(true);
	//UpdateData();
	UpdateListResultList();
}

void CQualityListView::UpdateView(){
	CString item_temp;
	switch (Controltype)
	{
	case 0:
		item_temp.Format(L"L-J��ֵ�༭���ļ� %02u��", Controlfile + 1);
		break;
	case 1:
		item_temp.Format(L"X��ֵ�༭���ļ� %02u��", Controlfile + 1);
		break;
	case 2:
		item_temp.Format(L"X-R��ֵ�༭���ļ� %02u��", Controlfile + 1);
		break;
	default:
		break;
	}
	SetDlgItemText(IDC_QUALITY_LIST_STATIC0, item_temp);
	GetDlgItem(IDC_QUALITY_LIST_STATIC0)->SetFont(&textfont);

	GetDlgItem(IDC_QUALITY_LIST_NUMBER)->EnableWindow(false);//�˴��������ź���Ч�ڵ������
	GetDlgItem(IDC_QUALITY_LIST_DEADLINE)->EnableWindow(false);

	//InitListList();
	GetQcLjEditData();
	itemCount = GetQcLjResultData(Controltype, Controlfile);
	UpdateListResultList();
	maxPage = itemCount % 5 == 0 ? itemCount / 5 - 1 : itemCount / 5;

	pageNum.Format(L"�� %d/%d ҳ", curpage + 1, maxPage + 1);
	UpdateData(false);

}

afx_msg LRESULT CQualityListView::OnRedraw(WPARAM, LPARAM){
	UpdateView();
	return 0;
}
void CQualityListView::Update_InitListList()
{
	/***************��ʼ�����**************/
	CRect rect;
	CString table[28] = { "����", "ʱ��", "WBC", "LYM%", "NEU%", "MONO%", "EOS%", "BASO", "ALY%", "LIC%", "LYM#", "NEU#", "MONO#", "EOS#", "BASO#", "ALY#",
		"LIC#", "RBC", "HGB", "HCT", "MCV", "MCH", "MCHC", "RDW", "PLT", "MPV", "PDW", "PCT" };	
	


	LVCOLUMN m_vcolumn;
	CString strText[8] = { "", "��ֵ", "ƫ����", "1" ,"2","3","4","5"};

	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_ListList.GetClientRect(&rect);
	m_ListList.SetRowHeigt(20);
	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_ListList.SetExtendedStyle(m_ListList.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	for (int i = 0; i < 8; i++)
	{
		m_vcolumn.mask = LVCF_TEXT;
		m_vcolumn.pszText = strText[i].GetBuffer(0);
		m_vcolumn.cchTextMax = strText[i].GetLength();
		m_ListList.SetColumn(i, &m_vcolumn);
	}

	for (int i = 0; i < 28; i++)
	{
		m_ListList.SetItemText(i,0, table[i]);
	}
	m_ListList.SetItemText(0, 1, _T(""));
	m_ListList.SetItemText(0, 2, _T(""));
	m_ListList.SetItemText(1, 1, _T(""));
	m_ListList.SetItemText(1, 2, _T(""));

}

void CQualityListView::OnPaint()
{

	CPaintDC dc(this);	
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	/*Update_InitListList();
	UpdateListResultList();
	UpdateView();*/
	// device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}





//BOOL CQualityListView::OnEraseBkgnd(CDC* pDC)
//{
//	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
//
//	return CDialogEx::OnEraseBkgnd(pDC);
//}
