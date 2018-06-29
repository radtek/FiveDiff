// PatientResultView2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "PatientResultView2.h"
#include "afxdialogex.h"


// CPatientResultView2 �Ի���

IMPLEMENT_DYNAMIC(CPatientResultView2, CDialogEx)
static int reserve_index = 0;
CPatientResultView2::CPatientResultView2(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPatientResultView2::IDD, pParent)
{

	is_search = false;


	ThisResult2.numofrs.reserve(20);
	ThisResult2.numofrs.clear();

	ThisResult2.page_num = 20; //һҳ��ʾ��id����
	ThisResult2.data_count = 0;  //���ݿ���id��

	CString filename;
	filename.Format(_T("appdata.accdb"));
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return ;

	CString data_check = _T("select * from patientdata ");
	ExeSql(m_pDB, m_pRs, data_check);
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

			ThisResult2.data_count++;
			m_pRs->MoveNext();
		}

	}
	catch (_com_error &e)
	{
		TRACE("UpdateResultList�쳣");
	}
	CloseDataBase(m_pDB, m_pRs);
	/******************************/

	ThisResult2.page_count = (ThisResult2.data_count % ThisResult2.page_num == 0 ? ThisResult2.data_count / ThisResult2.page_num : ThisResult2.data_count / ThisResult2.page_num + 1);
	if (reserve_index <= ThisResult2.page_count)
		ThisResult2.page_index = reserve_index;
	else
		reserve_index = ThisResult2.page_index = ThisResult2.page_count;
	
	//SetDlgItemText(IDC_PAGE_COUNT,_T(""));
	//SetDlgItemText(IDC_PAGE_COUNT, text_page);
	//UpdateData(false);

}

CPatientResultView2::~CPatientResultView2()
{
}

void CPatientResultView2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_PatientResultList);
	//DDX_Control(pDX, IDC_DAILY_RESULT2, m_daily_result);
	DDX_Text(pDX, IDC_EDIT_NAME, m_patientname);
	//DDX_Text(pDX, IDC_EDIT_GENDER, m_patientGender);
	DDX_Control(pDX, IDC_COMBOX_SEX, patient_gender);
	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_SearchButton);
	DDX_Control(pDX, IDC_PAGE_COUNT, text_page_count);
}


BEGIN_MESSAGE_MAP(CPatientResultView2, CDialogEx)
	
	ON_WM_ERASEBKGND()
	//ON_BN_CLICKED(IDC_DAILY_RESULT2, &CPatientResultView2::OnDailyResult2)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CPatientResultView2::OnNMDblclkList1)
	//	ON_BN_CLICKED(IDC_PATIENT_RESULT2, &CPatientResultView::OnBnClickedPatientResult2)
	ON_BN_CLICKED(IDC_PAGE_FRONT, &CPatientResultView2::OnBnClickedPageFront)
	ON_BN_CLICKED(IDC_PAGE_NEXT, &CPatientResultView2::OnBnClickedPageNext)
	ON_BN_CLICKED(IDC_PAGE_HOME, &CPatientResultView2::OnBnClickedPageHome)
	ON_BN_CLICKED(IDC_PAGE_TRAILER, &CPatientResultView2::OnBnClickedPageTrailer)
	ON_BN_CLICKED(IDC_PAGE_JUMP, &CPatientResultView2::OnBnClickedPageJump)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CPatientResultView2::OnBnClickedButtonSearch)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()



// CPatientResultView2 ��Ϣ�������






BOOL CPatientResultView2::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	ThisResult2.page_num = 20; //һҳ��ʾ��id����
	ThisResult2.data_count = 0;
	CString filename;
	filename.Format(_T("appdata.accdb"));
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return 0;
	CString ID, name, age, sex;
	char sex_1;
	CString data_check = _T("select * from patientdata where ");
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(name);
	GetDlgItem(IDC_EDIT6)->GetWindowText(age);
	GetDlgItem(IDC_EDIT_ID)->GetWindowText(ID);
	ID.Delete(0, 2);
	sex_1 = patient_gender.GetCurSel();
	if (sex_1 < 3 && sex_1 >= 0)
	{
		sex_1 = sex_1 + 48;
		sex = sex_1;
	}
	//�жϼ�������
	if (name.GetLength() != 0)
		data_check += " name like '%" + name + "%' and ";
	if (age.GetLength() != 0)
		data_check += " age = '" + age + "' and ";
	if (ID.GetLength() != 0)
		data_check += " number like '%" + ID + "%' and ";
	if (sex.GetLength() != 0)
		data_check += " sex = '" + sex + "'";
	else
		data_check.Delete(data_check.GetLength() - 5, 4);

	ExeSql(m_pDB, m_pRs, data_check);
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

			ThisResult2.data_count++;
			m_pRs->MoveNext();
		}

	}
	catch (_com_error &e)
	{
		TRACE("UpdateResultList�쳣");
	}
	CloseDataBase(m_pDB, m_pRs);
	/******************************/

	ThisResult2.page_count = (ThisResult2.data_count % ThisResult2.page_num == 0 ? ThisResult2.data_count / ThisResult2.page_num : ThisResult2.data_count / ThisResult2.page_num + 1);
	if (reserve_index <= ThisResult2.page_count)
		ThisResult2.page_index = reserve_index;
	else
		reserve_index = ThisResult2.page_index = ThisResult2.page_count;


	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitPatientResultForm();




	CString count;
	count.Format(_T("%d"), ThisResult2.page_count);
	count = "/" + count;
	SetDlgItemText(IDC_PAGE_COUNT, count);
	CString select;
	select.Format(_T("%d"), ThisResult2.page_index+1);
	SetDlgItemText(IDC_PAGE_SELECT, select);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


BOOL CPatientResultView2::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return CDialogEx::OnEraseBkgnd(pDC);
}
BOOL CPatientResultView2::InitPatientResultForm()
{
	CRect rect;
	int i = 0;


	CString strNum = "";
	CString strtemp = "20";
	CString strSex[3] = { "��", "��", "Ů" };
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	patient_gender.AddString(_T("��"));
	patient_gender.AddString(_T("��"));
	patient_gender.AddString(_T("Ů"));


	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_PatientResultList.GetClientRect(&rect);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_PatientResultList.SetExtendedStyle(m_PatientResultList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//m_worksheetList.SetItemColor(0, RGB(100, 125, 100), RGB(15, 235, 150));//�����ض�Item ���� ������ɫ
	m_PatientResultList.SetRowHeigt(20);


	// ΪCRP�б���ͼ�ؼ��������
	m_PatientResultList.InsertColumn(0, _T("ѡ��"), LVCFMT_CENTER, rect.Width() / 10, 0);
	m_PatientResultList.InsertColumn(1, _T("������"), LVCFMT_CENTER, rect.Width() / 8, 1);
	m_PatientResultList.InsertColumn(2, _T("ʱ��"), LVCFMT_CENTER, rect.Width() / 8, 2);
	m_PatientResultList.InsertColumn(3, _T("���˱��"), LVCFMT_CENTER, rect.Width() / 8, 3);
	m_PatientResultList.InsertColumn(4, _T("��������"), LVCFMT_CENTER, rect.Width() / 8, 4);
	m_PatientResultList.InsertColumn(5, _T("�Ա�"), LVCFMT_CENTER, rect.Width() / 8, 5);
	m_PatientResultList.InsertColumn(6, _T("��������"), LVCFMT_CENTER, rect.Width() / 8, 6);
	m_PatientResultList.InsertColumn(7, _T("����"), LVCFMT_CENTER, rect.Width() / 8, 6);
	
	// ��CRP�б���ͼ�ؼ��в����б���������б������ı�
	_variant_t var;

	CString filename;
	filename.Format(L"appdata.accdb");

	//select top 20 * from �� where Id not in(select top 9*20 Id from �� order by id desc) order by Id desc
	CString pagenum;
	pagenum.Format(_T("%d"), ThisResult2.page_num);
	CString pageindex;
	pageindex.Format(_T("%d"), ThisResult2.page_num*(ThisResult2.page_index));


	CString select_name_sample;//�ų���һҳ�����
	select_name_sample = (ThisResult2.page_index > 0) ? (_T("select top ") + pagenum + " * from patientdata where ID not in(select top " + pageindex + " ID from patientdata order by ID ) order by ID ") :
		(_T("select top ") + pagenum + " * from patientdata");
	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)//����Ϊ�����ݿ�
		return FALSE;
	ExeSql(m_pDB, m_pRs, select_name_sample);     //ִ�����ݿ�
	m_PatientResultList.DeleteAllItems();
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
			var = m_pRs->GetCollect("number");
			if (var.vt != VT_NULL)
				strNum = (LPCSTR)_bstr_t(var);
			ThisResult2.numofrs.push_back(strNum);
			strNum = strtemp + strNum;								//�����Ŷ�ȡ��ȷ������ǰ�����20
			m_PatientResultList.InsertItem(i, _T(""));              //��ʾ��Ϣ����һ������Ϊ�У��ڶ�������Ϊ�У�����������Ϊ����
			m_PatientResultList.SetItemText(i, 1, strNum);


			var = m_pRs->GetCollect("sex");
			CString sextemp;
			if (var.vt != VT_NULL)
			{
				sextemp = (LPCSTR)_bstr_t(var);

				sextemp = strSex[_ttoi(sextemp)];
			}
			m_PatientResultList.SetItemText(i, 5, sextemp);



			/*******************************************/



			var = m_pRs->GetCollect("ID");
			CString strID;
			if (var.vt != VT_NULL)
				strID = (LPCSTR)_bstr_t(var);
			m_PatientResultList.SetItemText(i, 3, strID);
			//m_PatientResultList.InsertItem(i, _T(""));              //��ʾ��Ϣ����һ������Ϊ�У��ڶ�������Ϊ�У�����������Ϊ����

			var = m_pRs->GetCollect("name");
			CString strName;
			if (var.vt != VT_NULL)
				strName = (LPCSTR)_bstr_t(var);
			m_PatientResultList.SetItemText(i, 4, strName);


			/*******************************************/


			/*var = m_pRs->GetCollect("time");
			if (var.vt != VT_NULL)
			strTime = (LPCSTR)_bstr_t(var);
			CString a = ":";
			strTime.Insert(2, a);
			strTime.Insert(5, a);
			m_PatientResultList.SetItemText(i, 2, strTime);*/

			i++;
			m_pRs->MoveNext();
		}
		ThisResult2.totalnums = i;
		/*for (int sup_1 = ThisResult2.totalnums; sup_1 < ThisResult2.page_num; sup_1++){
			m_PatientResultList.InsertItem(sup_1, _T(""));
			for (int sup_2 = 0; sup_2 <= 5; sup_2++){
				m_PatientResultList.SetItemText(sup_1, sup_2, _T(""));
			}
		}*/
	}
	catch (_com_error &e)
	{
		TRACE("UpdateResultList�쳣");
	}


	return TRUE;
}
BOOL CPatientResultView2::UpdatePatientResultForm()
{
	CRect rect;
	int i = 0;
	CString ID, name, age, sex;
	char sex_1;

	CString strNum = "";
	CString strtemp = "20";
	CString strSex[3] = { "��", "��", "Ů" };
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(name);
	GetDlgItem(IDC_EDIT6)->GetWindowText(age);
	GetDlgItem(IDC_EDIT_ID)->GetWindowText(ID);
	ID.Delete(0, 2);
	sex_1 = patient_gender.GetCurSel();
	if (sex_1 < 3 && sex_1 >= 0)
	{
		sex_1 = sex_1 + 48;
		sex = sex_1;
	}
	//�жϼ�������
	CString inquire_1 = L" where ";
	CString inquire_2 = L" and ";
	//inquire_1��inquire_2Ϊģ����ѯ���������
	if (is_search == TRUE &&
		name.GetLength() == 0 && age.GetLength() == 0
		&& ID.GetLength() == 0 && sex.GetLength() == 0)
	{
		inquire_1 = inquire_2 = "";
		is_search = FALSE;
	}
	else if (is_search == TRUE)
	{
		if (name.GetLength() != 0)
		{
			inquire_1 += " name like '%" + name + "%' and ";
			inquire_2 += " name like '%" + name + "%' and ";

		}

		if (age.GetLength() != 0)
		{
			inquire_1 += " age = '" + age + "' and ";
			inquire_2 += " age = '" + age + "' and ";
		}

		if (ID.GetLength() != 0)
		{
			inquire_1 += " number like '%" + ID + "%' and ";
			inquire_2 += " number like '%" + ID + "%' and ";
		}

		if (sex.GetLength() != 0)
		{
			inquire_1 += " sex = '" + sex + "'";
			inquire_2 += " sex = '" + sex + "'";
		}
		else
		{
			inquire_1.Delete(inquire_1.GetLength() - 5, 4);
			inquire_2.Delete(inquire_2.GetLength() - 5, 4);
		}

	}
	else
		inquire_1 = inquire_2 = "";
	



	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_PatientResultList.GetClientRect(&rect);

	



	// ��CRP�б���ͼ�ؼ��в����б���������б������ı�
	_variant_t var;

	CString filename;
	filename.Format(L"appdata.accdb");

	//select top 20 * from �� where Id not in(select top 9*20 Id from �� order by id desc) order by Id desc
	CString pagenum;
	pagenum.Format(_T("%d"), ThisResult2.page_num);
	CString pageindex;
	pageindex.Format(_T("%d"), ThisResult2.page_num*(ThisResult2.page_index));


	CString select_name_sample;//�ų���һҳ�����
	select_name_sample = (ThisResult2.page_index > 0) ? (_T("select top ") + pagenum + " * from patientdata where ID not in(select top " + pageindex + " ID from patientdata "+inquire_1+" order by ID ) "+inquire_2+" order by ID ") :
		(_T("select top ") + pagenum + " * from patientdata "+inquire_1);


	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)//����Ϊ�����ݿ�
		return FALSE;
	ExeSql(m_pDB, m_pRs, select_name_sample);     //ִ�����ݿ�

	m_PatientResultList.DeleteAllItems();

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
			var = m_pRs->GetCollect("number");
			if (var.vt != VT_NULL)
				strNum = (LPCSTR)_bstr_t(var);
			ThisResult2.numofrs.push_back(strNum);
			strNum = strtemp + strNum;								//�����Ŷ�ȡ��ȷ������ǰ�����20
			m_PatientResultList.InsertItem(i, _T(""));              //��ʾ��Ϣ����һ������Ϊ�У��ڶ�������Ϊ�У�����������Ϊ����
			m_PatientResultList.SetItemText(i, 1, strNum);


			var = m_pRs->GetCollect("sex");
			CString sextemp;
			if (var.vt != VT_NULL)
			{
				sextemp = (LPCSTR)_bstr_t(var);

				sextemp = strSex[_ttoi(sextemp)];
			}
			m_PatientResultList.SetItemText(i, 5, sextemp);



			/*******************************************/



			var = m_pRs->GetCollect("ID");
			CString strID;
			if (var.vt != VT_NULL)
				strID = (LPCSTR)_bstr_t(var);
			m_PatientResultList.SetItemText(i, 3, strID);
			//m_PatientResultList.InsertItem(i, _T(""));              //��ʾ��Ϣ����һ������Ϊ�У��ڶ�������Ϊ�У�����������Ϊ����

			var = m_pRs->GetCollect("name");
			CString strName;
			if (var.vt != VT_NULL)
				strName = (LPCSTR)_bstr_t(var);
			m_PatientResultList.SetItemText(i, 4, strName);


			/*******************************************/


			/*var = m_pRs->GetCollect("time");
			if (var.vt != VT_NULL)
			strTime = (LPCSTR)_bstr_t(var);
			CString a = ":";
			strTime.Insert(2, a);
			strTime.Insert(5, a);
			m_PatientResultList.SetItemText(i, 2, strTime);*/

			i++;
			m_pRs->MoveNext();
		}
		ThisResult2.totalnums = i;
		/*for (int sup_1 = ThisResult2.totalnums; sup_1 < ThisResult2.page_num; sup_1++){
		m_PatientResultList.InsertItem(sup_1, _T(""));
		for (int sup_2 = 0; sup_2 <= 5; sup_2++){
		m_PatientResultList.SetItemText(sup_1, sup_2, _T(""));
		}
		}*/
	}
	catch (_com_error &e)
	{
		TRACE("UpdateResultList�쳣");
	}


		return TRUE;
	
}

void CPatientResultView2::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//MessageBox(L"Assert Here!");
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	POSITION pos = m_PatientResultList.GetFirstSelectedItemPosition();

	if (pos == NULL)
		TRACE("No items were selected!\n");
	else
	{
		int nItem = m_PatientResultList.GetNextSelectedItem(pos);//��ò�����Ϣ���
		TRACE1("Item %d was selected!\n", nItem);
		CString selectnum = m_PatientResultList.GetItemText(nItem, 1);
		/*if (is_search == true)
			ThisResult2.nownum = ThisRelation.ado_pos[nItem];
		else*/
			ThisResult2.nownum = nItem;
		if (m_PatientResultList.GetNextSelectedItem(pos) < m_PatientResultList.GetItemCount())
		{
			CMainFrame* pMf = (CMainFrame*)AfxGetMainWnd();
			CRect rect;
			pMf->GetClentRectEx(rect);

			/**********���¹��̽��н����л�**************/
			CRuntimeClass* pClass = RUNTIME_CLASS(CResultDetails);
			CView* pView = DYNAMIC_DOWNCAST(CView, pClass->CreateObject());

			//�������俴��̫�������������ڴ˴�
			this->m_pResultDetails2 = (CResultDetails*)pView;
			m_pResultDetails2->pThisResult = &ThisResult2;

			//��Ȼ�ڴ˴���������ʧ�ܣ�
			//MessageBox(L"Before failure");
			ASSERT_VALID(pView);
			//MessageBox(L"After  failure");

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
		}
	}

}
void CPatientResultView2::OnBnClickedButtonSearch()
{
	ThisResult2.page_num = 20; //һҳ��ʾ��id����
	ThisResult2.data_count = 0;
	CString filename;
	filename.Format(_T("appdata.accdb"));
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return ;
	CString ID, name, age, sex;
	char sex_1;
	CString data_check = _T("select * from patientdata where ");
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(name);
	GetDlgItem(IDC_EDIT6)->GetWindowText(age);
	GetDlgItem(IDC_EDIT_ID)->GetWindowText(ID);
	ID.Delete(0, 2);
	sex_1 = patient_gender.GetCurSel();
	if (sex_1 < 3 && sex_1 >= 0)
	{
		sex_1 = sex_1 + 48;
		sex = sex_1;
	}
	//�жϼ�������
	if (name.GetLength() != 0)
		data_check += " name like '%" + name + "%' and ";
	if (age.GetLength() != 0)
		data_check += " age = '" + age + "' and ";
	if (ID.GetLength() != 0)
		data_check += " number like '%" + ID + "%' and ";
	if (sex.GetLength() != 0)
		data_check += " sex = '" + sex + "'";
	else
		data_check.Delete(data_check.GetLength() - 5, 4);

	if (name.GetLength() == 0 && age.GetLength() == 0
		&& ID.GetLength() == 0 && sex.GetLength() == 0)
		is_search = FALSE;
	else
		is_search = TRUE;
	ExeSql(m_pDB, m_pRs, data_check);
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

			ThisResult2.data_count++;
			m_pRs->MoveNext();
		}

	}
	catch (_com_error &e)
	{
		TRACE("UpdateResultList�쳣");
	}
	CloseDataBase(m_pDB, m_pRs);
	/******************************/

	ThisResult2.page_count = (ThisResult2.data_count % ThisResult2.page_num == 0 ? ThisResult2.data_count / ThisResult2.page_num : ThisResult2.data_count / ThisResult2.page_num + 1);
	if (reserve_index <= ThisResult2.page_count)
		ThisResult2.page_index = reserve_index;
	else
		reserve_index = ThisResult2.page_index = ThisResult2.page_count;

	CString count;
	count.Format(_T("%d"), ThisResult2.page_count);
	count = "/" + count;
	SetDlgItemText(IDC_PAGE_COUNT, count);
	
	CString select;
	select.Format(_T("%d"), ThisResult2.page_index + 1);
	SetDlgItemText(IDC_PAGE_SELECT, select);
	OnBnClickedPageHome();
}

void CPatientResultView2::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
}


HBRUSH CPatientResultView2::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	//switch (pWnd->GetDlgCtrlID())
	//{
	//case IDC_BUTTON_SEARCH:
	//	pDC->SetBkMode(TRANSPARENT);
	//	pDC->SetTextColor(RGB(0, 0, 0));

	//	return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	//default:
	//	break;
	//}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CPatientResultView2::OnBnClickedPageFront()//��һҳ
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (reserve_index > 0)
		reserve_index--;
	ThisResult2.page_index = reserve_index;
	ThisResult2.numofrs.reserve(20);
	ThisResult2.numofrs.clear();
	UpdatePatientResultForm();
	CString select;
	select.Format(_T("%d"), ThisResult2.page_index + 1);
	SetDlgItemText(IDC_PAGE_SELECT, select);
}


void CPatientResultView2::OnBnClickedPageHome()//��ҳ
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	reserve_index=0;
	ThisResult2.page_index = reserve_index;
	ThisResult2.numofrs.reserve(20);
	ThisResult2.numofrs.clear();
	UpdatePatientResultForm();
	CString select;
	select.Format(_T("%d"), ThisResult2.page_index + 1);
	SetDlgItemText(IDC_PAGE_SELECT, select);
}


void CPatientResultView2::OnBnClickedPageNext()//��һҳ
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (reserve_index < ThisResult2.page_count - 1)
		reserve_index++;
	ThisResult2.page_index = reserve_index;
	ThisResult2.numofrs.reserve(20);
	ThisResult2.numofrs.clear();
	UpdatePatientResultForm();
	CString select;
	select.Format(_T("%d"), ThisResult2.page_index + 1);
	SetDlgItemText(IDC_PAGE_SELECT, select);
}


void CPatientResultView2::OnBnClickedPageTrailer()//βҳ
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	reserve_index = ThisResult2.page_count - 1;
	ThisResult2.page_index = reserve_index;
	ThisResult2.numofrs.reserve(20);
	ThisResult2.numofrs.clear();
	UpdatePatientResultForm();
	CString select;
	select.Format(_T("%d"), ThisResult2.page_index + 1);
	SetDlgItemText(IDC_PAGE_SELECT, select);
}

void CPatientResultView2::OnBnClickedPageJump()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int page =	GetDlgItemInt(IDC_PAGE_SELECT) ;
	if (page > 0 && page <= ThisResult2.page_count)
		reserve_index = page - 1;
	ThisResult2.page_index = reserve_index;
	ThisResult2.numofrs.reserve(20);
	ThisResult2.numofrs.clear();
	UpdatePatientResultForm();
	CString select;
	select.Format(_T("%d"), ThisResult2.page_index+1);
	SetDlgItemText(IDC_PAGE_SELECT, select);
}