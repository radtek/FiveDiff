// ResultListView2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "ResultListView2.h"
#include "afxdialogex.h"


// CResultListView2 �Ի���

IMPLEMENT_DYNAMIC(CResultListView2, CDialogEx)
static int reserve_index = 0;
CResultListView2::CResultListView2(CWnd* pParent /*=NULL*/)
	: CDialogEx(CResultListView2::IDD, pParent)
{
	m_nFirstDayOfWeek = 1;

	ThisResult.numofrs.reserve(20);
	ThisResult.numofrs.clear();

	ThisResult.page_num = 20; //һҳ��ʾ��id����
	ThisResult.data_count = 0;  //���ݿ���id��

	int	i = 0;
	static unsigned int date;
	static unsigned int today_start_num;
	static unsigned int today_end_num;
	m_Date = m_ResultDate.GetDate();
	int day = m_Date.GetDay();
	int month = m_Date.GetMonth();
	int year = m_Date.GetYear();
	TRACE("DAY:%d\n", day);
	TRACE("month:%d\n", month);
	TRACE("YEAR:%d\n", year);
	/******************************/

	ThisResult.page_num = 20; //һҳ��ʾ��id����
	ThisResult.data_count = 0;
	date = year * 10000 + month * 100 + day;
	//����λ��ԭ�򣬱���ڴ������ݿ�����ڵĸ���λ��ȡ��
	today_start_num = (date % 1000000) * 10000;
	today_end_num = today_start_num + 9999;
	//����һ����
	CString today_start_num_1;
	CString today_end_num_1;

	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;

	_variant_t var;

	today_start_num_1.Format(_T("%d"), today_start_num);
	today_end_num_1.Format(_T("%d"), today_end_num);

	CString select_condition_1 = _T(" where number >='") + today_start_num_1 + _T("' and number <='") + today_end_num_1 + _T("' ");



	CString select_number_sample;//�ų���һҳ�����
	select_number_sample = _T("select  * from sampledata " + select_condition_1);

	CString select_number_patient;//�ų���һҳ�����
	select_number_patient = _T("select  * from patientdata " + select_condition_1);



	CString filename;
	filename.Format(_T("appdata.accdb"));

	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return;
	ExeSql(m_pDB, m_pRs, select_number_sample);//���ض���ŵ�����ѡȡ����

	try
	{
		if (!m_pRs->BOF){
			m_pRs->MoveFirst();
		}
		else
		{
			TRACE("��������Ϊ��");
			//return;
		}
		while (!m_pRs->adoEOF)
		{
			ThisResult.data_count++;
			m_pRs->MoveNext();
		}

	}
	catch (_com_error &e)
	{
		TRACE("UpdateResultList�쳣");
	}
	CloseDataBase(m_pDB, m_pRs);
	/******************************/

	if (ThisResult.data_count != 0)
		ThisResult.page_count = (ThisResult.data_count % ThisResult.page_num == 0 ? ThisResult.data_count / ThisResult.page_num : ThisResult.data_count / ThisResult.page_num + 1);
	else
		ThisResult.page_count = 1;
	if (reserve_index <= ThisResult.page_count)//����Ƿ񳬳�ҳ�淶Χ
		ThisResult.page_index = reserve_index;
	else
		reserve_index = ThisResult.page_index = ThisResult.page_count;

	/********************/
	//UpdateResultList(m_Date);

	
}

CResultListView2::~CResultListView2()
{
}

void CResultListView2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ResultList);
	DDX_Control(pDX, IDC_RESULT_TIMEPICKER, m_ResultDate);
	//DDX_Control(pDX, IDC_PAITIENT_RESULT, m_paitient_result);
}


BEGIN_MESSAGE_MAP(CResultListView2, CDialogEx)

	ON_BN_CLICKED(IDC_RESULT_TIMEPICKER, &CResultListView2::OnCloseupResultTimepicker)
	ON_WM_PAINT()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CResultListView2::OnNMDblclkList)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_RESULT_PAGE_UP, &CResultListView2::OnBnClickedResultPageUp)
	ON_BN_CLICKED(IDC_RESULT_PAGE_DOWN, &CResultListView2::OnBnClickedResultPageDown)
	ON_BN_CLICKED(IDC_RESULT_PAGE_TRAILER, &CResultListView2::OnBnClickedResultPageTrailer)
	ON_BN_CLICKED(IDC_RESULT_PAGE_JUMP, &CResultListView2::OnBnClickedResultPageJump)
	ON_BN_CLICKED(IDC_RESULT_PAGE_HOME, &CResultListView2::OnBnClickedResultPageHome)
END_MESSAGE_MAP()


// CResultListView2 ��Ϣ�������


BOOL CResultListView2::OnInitDialog()
{
	CDialogEx::OnInitDialog();



	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ResultDate.SizeToContent();

	m_ResultDate.SetState(
		CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
		CBCGPDateTimeCtrl::DTM_DATE,
		CBCGPDateTimeCtrl::DTM_SPIN |
		CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
		CBCGPDateTimeCtrl::DTM_DATE |
		CBCGPDateTimeCtrl::DTM_TIME24H |
		CBCGPDateTimeCtrl::DTM_CHECKBOX |
		CBCGPDateTimeCtrl::DTM_TIME |
		CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE);

	m_ResultDate.SetFirstDayOfWeek(m_nFirstDayOfWeek);
	m_Date = COleDateTime::GetCurrentTime();
	m_ResultDate.SetDate(m_Date);
	InitResultForm();
	UpdateResultList(m_Date);

	ThisResult.numofrs.reserve(20);
	ThisResult.numofrs.clear();

	ThisResult.page_num = 20; //һҳ��ʾ��id����
	ThisResult.data_count = 0;  //���ݿ���id��

	int	i = 0;
	static unsigned int date;
	static unsigned int today_start_num;
	static unsigned int today_end_num;
	m_Date = m_ResultDate.GetDate();
	int day = m_Date.GetDay();
	int month = m_Date.GetMonth();
	int year = m_Date.GetYear();
	TRACE("DAY:%d\n", day);
	TRACE("month:%d\n", month);
	TRACE("YEAR:%d\n", year);
	/******************************/

	ThisResult.page_num = 20; //һҳ��ʾ��id����
	ThisResult.data_count = 0;
	date = year * 10000 + month * 100 + day;
	//����λ��ԭ�򣬱���ڴ������ݿ�����ڵĸ���λ��ȡ��
	today_start_num = (date % 1000000) * 10000;
	today_end_num = today_start_num + 9999;
	//����һ����
	CString today_start_num_1;
	CString today_end_num_1;

	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;

	_variant_t var;

	today_start_num_1.Format(_T("%d"), today_start_num);
	today_end_num_1.Format(_T("%d"), today_end_num);

	CString select_condition_1 = _T(" where number >='") + today_start_num_1 + _T("' and number <='") + today_end_num_1 + _T("' ");



	CString select_number_sample;//�ų���һҳ�����
	select_number_sample = _T("select  * from sampledata " + select_condition_1);

	CString select_number_patient;//�ų���һҳ�����
	select_number_patient = _T("select  * from patientdata " + select_condition_1);



	CString filename;
	filename.Format(_T("appdata.accdb"));

	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return 0;
	ExeSql(m_pDB, m_pRs, select_number_sample);//���ض���ŵ�����ѡȡ����

	try
	{
		if (!m_pRs->BOF){
			m_pRs->MoveFirst();
		}
		else
		{
			TRACE("��������Ϊ��");
		//	return 0;
		}
		while (!m_pRs->adoEOF)
		{
			ThisResult.data_count++;
			m_pRs->MoveNext();
		}

	}
	catch (_com_error &e)
	{
		TRACE("UpdateResultList�쳣");
	}
	CloseDataBase(m_pDB, m_pRs);
	/******************************/
	if (ThisResult.data_count != 0)
		ThisResult.page_count = (ThisResult.data_count % ThisResult.page_num == 0 ? ThisResult.data_count / ThisResult.page_num : ThisResult.data_count / ThisResult.page_num + 1);
	else
		ThisResult.page_count = 1;
	if (reserve_index <= ThisResult.page_count)//����Ƿ񳬳�ҳ�淶Χ
		ThisResult.page_index = reserve_index;
	else
		reserve_index = ThisResult.page_index = ThisResult.page_count;

	/********************/
	UpdateResultList(m_Date);

	CString count;
	count.Format(_T("%d"), ThisResult.page_count);
	count = "/" + count;
	SetDlgItemText(IDC_PAGE_COUNT, count);

	CString select;
	select.Format(_T("%d"), ThisResult.page_index + 1);
	SetDlgItemText(IDC_PAGE_SELECT, select);

	int row;
	//�����в�ѯ����ı�Ž��б��棬������ϸ��Ϣ��ҳ��
	row = m_ResultList.GetItemCount();
	//if ((ThisResult.numofrs = (int *)malloc(row*sizeof(int))) == NULL)
	//{
	//	printf("Memory allocation for ResultsList failed--------!\n");
	//	exit(1);
	//}
	//GetDlgItem(IDC_DAILY_RESULT)->EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


BOOL CResultListView2::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return CDialogEx::OnEraseBkgnd(pDC);
}

BOOL CResultListView2::InitResultForm()
{
	CRect rect;

	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_ResultList.GetClientRect(&rect);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_ResultList.SetExtendedStyle(m_ResultList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//m_worksheetList.SetItemColor(0, RGB(100, 125, 100), RGB(15, 235, 150));//�����ض�Item ���� ������ɫ
	m_ResultList.SetRowHeigt(20);


	//// ΪCRP�б���ͼ�ؼ��������

	m_ResultList.InsertColumn(0, _T("ѡ��"), LVCFMT_CENTER, rect.Width() / 10, 0);
	m_ResultList.InsertColumn(1, _T("������"), LVCFMT_CENTER, rect.Width() / 8, 1);
	m_ResultList.InsertColumn(2, _T("ʱ��"), LVCFMT_CENTER, rect.Width() / 8, 2);
	m_ResultList.InsertColumn(3, _T("���˱��"), LVCFMT_CENTER, rect.Width() / 8, 3);
	m_ResultList.InsertColumn(4, _T("��������"), LVCFMT_CENTER, rect.Width() / 8, 4);
	m_ResultList.InsertColumn(5, _T("�Ա�"), LVCFMT_CENTER, rect.Width() / 8, 5);
	m_ResultList.InsertColumn(6, _T("��������"), LVCFMT_CENTER, rect.Width() / 8, 6);
	m_ResultList.InsertColumn(7, _T("����"), LVCFMT_CENTER, rect.Width() / 8, 6);


	// ��CRP�б���ͼ�ؼ��в����б���������б������ı�
	m_ResultList.InsertItem(0, _T(""));
	m_ResultList.SetItemText(0, 1, _T("12345"));
	m_ResultList.SetItemText(0, 2, _T("2016/04/11 16:44:00"));
	m_ResultList.SetItemText(0, 3, _T("1111"));
	m_ResultList.SetItemText(0, 4, _T("����"));
	m_ResultList.SetItemText(0, 5, _T("��"));
	m_ResultList.SetItemText(0, 6, _T("CBC+RET"));
	m_ResultList.SetItemText(0, 7, _T("��"));

	m_ResultList.InsertItem(1, _T(""));
	m_ResultList.SetItemText(1, 1, _T("12345"));
	m_ResultList.SetItemText(1, 2, _T("2016/04/11 16:44:00"));
	m_ResultList.SetItemText(1, 3, _T("1111"));
	m_ResultList.SetItemText(1, 4, _T("����"));
	m_ResultList.SetItemText(1, 5, _T("��"));
	m_ResultList.SetItemText(1, 6, _T("CBC+RET"));
	m_ResultList.SetItemText(1, 7, _T("��"));

	m_ResultList.InsertItem(2, _T(""));
	m_ResultList.SetItemText(2, 1, _T("12345"));
	m_ResultList.SetItemText(2, 2, _T("2016/04/11 16:44:00"));
	m_ResultList.SetItemText(2, 3, _T("1111"));
	m_ResultList.SetItemText(2, 4, _T("����"));
	m_ResultList.SetItemText(2, 5, _T("��"));
	m_ResultList.SetItemText(2, 6, _T("CBC+RET"));
	m_ResultList.SetItemText(2, 7, _T("��"));

	return TRUE;
}


void CResultListView2::UpdateResultList(COleDateTime Date)
{

	int	i = 0;
	static unsigned int date;
	static unsigned int today_start_num;
	static unsigned int today_end_num;
	CString today_start_num_1;
	CString today_end_num_1;

	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;

	_variant_t var;
	CString strNum = "";
	CString strTime = "";
	CString strName = "";
	CString strtemp;
	strtemp = "20";
	CString strSex[3] = { "��", "Ů", "" };

	int day = Date.GetDay();
	int month = Date.GetMonth();
	int year = Date.GetYear();

	date = year * 10000 + month * 100 + day;
	//����λ��ԭ�򣬱���ڴ������ݿ�����ڵĸ���λ��ȡ��
	today_start_num = (date % 1000000) * 10000;
	today_end_num = today_start_num + 9999;
	//����һ����

	today_start_num_1.Format(_T("%d"), today_start_num);
	today_end_num_1.Format(_T("%d"), today_end_num);

	CString select_condition_1 = _T(" where number >='") + today_start_num_1 + _T("' and number <='") + today_end_num_1 + _T("' ");
	CString select_condition_2 = _T(" and number >='") + today_start_num_1 + _T("' and number <='") + today_end_num_1 + _T("' ");

	CString pagenum;
	pagenum.Format(_T("%d"), ThisResult.page_num);
	CString pageindex;
	pageindex.Format(_T("%d"), ThisResult.page_num*(ThisResult.page_index));



	CString select_number_sample;//�ų���һҳ�����
	select_number_sample = (ThisResult.page_index > 0) ? (_T("select top ") + pagenum + " * from sampledata where number not in(select top " + pageindex + " number from patientdata " + select_condition_1 + " order by number ) " + select_condition_2 + " order by number ") :
		(_T("select top ") + pagenum + " * from sampledata " + select_condition_1);

	CString select_number_patient;//�ų���һҳ�����
	select_number_patient = (ThisResult.page_index > 0) ? (_T("select top ") + pagenum + " * from patientdata where number not in(select top " + pageindex + " number from patientdata " + select_condition_1 + " order by number ) " + select_condition_2 + " order by number ") :
		(_T("select top ") + pagenum + " * from patientdata " + select_condition_1);



	CString filename;
	filename.Format(_T("appdata.accdb"));

	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return;
	ExeSql(m_pDB, m_pRs, select_number_sample);//���ض���ŵ�����ѡȡ����
	m_ResultList.DeleteAllItems();
	try
	{
		if (!m_pRs->BOF){
			m_pRs->MoveFirst();
		}
		else
		{
			TRACE("��������Ϊ��");
			return;
		}
		while (!m_pRs->adoEOF)
		{
			var = m_pRs->GetCollect("number");
			if (var.vt != VT_NULL)
				strNum = (LPCSTR)_bstr_t(var);
			ThisResult.numofrs.push_back(strNum);
			strNum = strtemp + strNum;
			m_ResultList.InsertItem(i, _T(""));
			m_ResultList.SetItemText(i, 1, strNum);


			/*****************************/
			var = m_pRs->GetCollect("ID");
			CString strID;
			if (var.vt != VT_NULL)
				strID = (LPCSTR)_bstr_t(var);
			m_ResultList.SetItemText(i, 3, strID);

			var = m_pRs->GetCollect("mode");
			CString strMode;
			if (var.vt != VT_NULL)
				strMode = (LPCSTR)_bstr_t(var);
			m_ResultList.SetItemText(i, 6, strMode);

			/*****************************/

			var = m_pRs->GetCollect("time");
			if (var.vt != VT_NULL)
				strTime = (LPCSTR)_bstr_t(var);
			CString a = ":";
			strTime.Insert(2, a);
			strTime.Insert(5, a);
			m_ResultList.SetItemText(i, 2, strTime);
			i++;
			m_pRs->MoveNext();
		}
		ThisResult.totalnums = m_ResultList.GetItemCount();

	}
	catch (_com_error &e)
	{
		TRACE("UpdateResultList�쳣");
	}

	i = 0;
	ExeSql(m_pDB, m_pRs, select_number_patient);
	try
	{
		if (!m_pRs->BOF){
			m_pRs->MoveFirst();
		}
		else
		{
			TRACE("��������Ϊ��");
			return;
		}
		while (!m_pRs->adoEOF)
		{


			var = m_pRs->GetCollect("name");
			if (var.vt != VT_NULL)
				strName = (LPCSTR)_bstr_t(var);
			m_ResultList.SetItemText(i, 4, strName);

			var = m_pRs->GetCollect("sex");
			CString sextemp;
			if (var.vt != VT_NULL)
			{
				sextemp = (LPCSTR)_bstr_t(var);
				sextemp = strSex[_ttoi(sextemp)];
			}
			m_ResultList.SetItemText(i, 5, sextemp);

			i++;
			m_pRs->MoveNext();
		}
	}
	catch (_com_error &e)
	{
		TRACE("UpdateResultList�쳣");
	}
	CloseDataBase(m_pDB, m_pRs);

}


void CResultListView2::OnCloseupResultTimepicker()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int	i = 0;
	static unsigned int date;
	static unsigned int today_start_num;
	static unsigned int today_end_num;
	m_Date = m_ResultDate.GetDate();
	int day = m_Date.GetDay();
	int month = m_Date.GetMonth();
	int year = m_Date.GetYear();
	TRACE("DAY:%d\n", day);
	TRACE("month:%d\n", month);
	TRACE("YEAR:%d\n", year);
	/******************************/

	ThisResult.page_num = 20; //һҳ��ʾ��id����
	ThisResult.data_count = 0;
	date = year * 10000 + month * 100 + day;
	//����λ��ԭ�򣬱���ڴ������ݿ�����ڵĸ���λ��ȡ��
	today_start_num = (date % 1000000) * 10000;
	today_end_num = today_start_num + 9999;
	//����һ����
	CString today_start_num_1;
	CString today_end_num_1;

	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;

	_variant_t var;

	today_start_num_1.Format(_T("%d"), today_start_num);
	today_end_num_1.Format(_T("%d"), today_end_num);

	CString select_condition_1 = _T(" where number >='") + today_start_num_1 + _T("' and number <='") + today_end_num_1 + _T("' ");
	


	CString select_number_sample;//�ų���һҳ�����
	select_number_sample = _T("select  * from sampledata " + select_condition_1);

	CString select_number_patient;//�ų���һҳ�����
	select_number_patient = _T("select  * from patientdata " + select_condition_1);



	CString filename;
	filename.Format(_T("appdata.accdb"));

	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return;
	ExeSql(m_pDB, m_pRs, select_number_sample);//���ض���ŵ�����ѡȡ����
	m_ResultList.DeleteAllItems();
	try
	{
		if (!m_pRs->BOF){
			m_pRs->MoveFirst();
		}
		else
		{
			TRACE("��������Ϊ��");
			return;
		}
		while (!m_pRs->adoEOF)
		{
			ThisResult.data_count++;
			m_pRs->MoveNext();
		}

	}
	catch (_com_error &e)
	{
		TRACE("UpdateResultList�쳣");
	}
	CloseDataBase(m_pDB, m_pRs);
	/******************************/


	if (ThisResult.data_count != 0)
		ThisResult.page_count = (ThisResult.data_count % ThisResult.page_num == 0 ? ThisResult.data_count / ThisResult.page_num : ThisResult.data_count / ThisResult.page_num + 1);
	else
		ThisResult.page_count = 1;
	if (reserve_index <= ThisResult.page_count)//����Ƿ񳬳�ҳ�淶Χ
		ThisResult.page_index = reserve_index;
	else
		reserve_index = ThisResult.page_index = ThisResult.page_count;

	/********************/
	UpdateResultList(m_Date);

	/********************/
	CString count;
	count.Format(_T("%d"), ThisResult.page_count);
	count = "/" + count;
	SetDlgItemText(IDC_PAGE_COUNT, count);
}


void CResultListView2::OnPaint()
{
	CPaintDC dc(this); 
	//OnCloseupResultTimepicker();
	//InitResultForm();

	// device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CBCGPChartExampleView::OnPaint()
	//UpdateResultList();
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
}

void CResultListView2::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	//MessageBox(L"Assert Here!");
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	POSITION pos = m_ResultList.GetFirstSelectedItemPosition();


	if (pos == NULL)
		TRACE("No items were selected!\n");
	else
	{
		int nItem = m_ResultList.GetNextSelectedItem(pos);
		TRACE1("Item %d was selected!\n", nItem);
		CString selectnum = m_ResultList.GetItemText(nItem, 1);
		ThisResult.nownum = nItem;

		if (m_ResultList.GetNextSelectedItem(pos)<m_ResultList.GetItemCount())
		{
			CMainFrame* pMf = (CMainFrame*)AfxGetMainWnd();
			CRect rect;
			CRect rect1;
			pMf->GetClentRectEx(rect);

			CRuntimeClass* pClass = RUNTIME_CLASS(CResultDetails);
			CView* pView = DYNAMIC_DOWNCAST(CView, pClass->CreateObject());

			this->m_pResultDetails = (CResultDetails*)pView;
			m_pResultDetails->pThisResult = &ThisResult;


			ASSERT_VALID(pView);
			CDocument* pCurrentDoc = ((CMainFrame*)::AfxGetMainWnd())->GetActiveDocument();

			CCreateContext newContext;
			newContext.m_pNewViewClass = NULL;
			newContext.m_pNewDocTemplate = NULL;
			newContext.m_pLastView = NULL;
			newContext.m_pCurrentFrame = NULL;
			newContext.m_pCurrentDoc = pCurrentDoc;


			if (!pView->Create(NULL, _T(""), (AFX_WS_DEFAULT_VIEW & ~WS_VISIBLE),
				rect, pMf, AFX_IDW_PANE_FIRST + 10, &newContext))
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
			//::PostMessage(AfxGetApp()->GetMainWnd()->GetSafeHwnd(), WM_WINDOWCHANGE, 17, 0);

		}
	}

}
void CResultListView2::OnBnClickedResultPageHome()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	ThisResult.page_index = reserve_index = 0;
	ThisResult.numofrs.reserve(20);
	ThisResult.numofrs.clear();
	OnCloseupResultTimepicker();
	CString select;
	select.Format(_T("%d"), ThisResult.page_index + 1);
	SetDlgItemText(IDC_PAGE_SELECT, select);
}
void CResultListView2::OnBnClickedResultPageUp()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (reserve_index > 0)
		reserve_index--;
	ThisResult.page_index = reserve_index;
	ThisResult.numofrs.reserve(20);
	ThisResult.numofrs.clear();
	OnCloseupResultTimepicker();
	CString select;
	select.Format(_T("%d"), ThisResult.page_index + 1);
	SetDlgItemText(IDC_PAGE_SELECT, select);
}


void CResultListView2::OnBnClickedResultPageDown()
{
	if (reserve_index < ThisResult.page_count - 1)
		reserve_index++;
	ThisResult.page_index = reserve_index;
	ThisResult.numofrs.reserve(20);
	ThisResult.numofrs.clear();
	OnCloseupResultTimepicker();
	CString select;
	select.Format(_T("%d"), ThisResult.page_index + 1);
	SetDlgItemText(IDC_PAGE_SELECT, select);

}


void CResultListView2::OnBnClickedResultPageTrailer()
{

	reserve_index = ThisResult.page_count - 1;

	ThisResult.page_index = reserve_index;
	ThisResult.numofrs.reserve(20);
	ThisResult.numofrs.clear();
	OnCloseupResultTimepicker();
	CString select;
	select.Format(_T("%d"), ThisResult.page_index + 1);
	SetDlgItemText(IDC_PAGE_SELECT, select);
}


void CResultListView2::OnBnClickedResultPageJump()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int page = GetDlgItemInt(IDC_PAGE_SELECT);
	if (page > 0 && page <= ThisResult.page_count)
		reserve_index = page - 1;
	ThisResult.page_index = reserve_index;
	ThisResult.numofrs.reserve(20);
	ThisResult.numofrs.clear();
	OnCloseupResultTimepicker();
	CString select;
	select.Format(_T("%d"), ThisResult.page_index + 1);
	SetDlgItemText(IDC_PAGE_SELECT, select);
}



