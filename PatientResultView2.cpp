// PatientResultView2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "PatientResultView2.h"
#include "afxdialogex.h"


// CPatientResultView2 �Ի���

IMPLEMENT_DYNAMIC(CPatientResultView2, CDialogEx)

CPatientResultView2::CPatientResultView2(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPatientResultView2::IDD, pParent)
{
	is_search = false;

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
}


BEGIN_MESSAGE_MAP(CPatientResultView2, CDialogEx)
	
	ON_WM_ERASEBKGND()
	//ON_BN_CLICKED(IDC_DAILY_RESULT2, &CPatientResultView2::OnDailyResult2)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CPatientResultView2::OnNMDblclkList1)
	//	ON_BN_CLICKED(IDC_PATIENT_RESULT2, &CPatientResultView::OnBnClickedPatientResult2)
	//ON_BN_CLICKED(IDC_BUTTON3, &CPatientResultView::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CPatientResultView2::OnBnClickedButtonSearch)
END_MESSAGE_MAP()



// CPatientResultView2 ��Ϣ�������






BOOL CPatientResultView2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitPatientResultForm();

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
	CString select_name_sample = L"select * from patientdata ";// where name = '" + m_patientname + "'";
	CString strNum = "";
	CString strtemp = "20";
	CString strSex[3] = { "��", "��", "Ů" };

	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	patient_gender.AddString(_T("��"));
	patient_gender.AddString(_T("��"));
	patient_gender.AddString(_T("Ů"));

	_variant_t var;
	is_search = false;
	CString filename;
	filename.Format(L"appdata.accdb");

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

	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)//����Ϊ�����ݿ�
		return FALSE;
	ExeSql(m_pDB, m_pRs, select_name_sample);     //ִ�����ݿ�
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
			ThisResult2.numofrs[i] = strNum;
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
		ThisResult2.totalnums = m_PatientResultList.GetItemCount();
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
		if (is_search == true)
			ThisResult2.nownum = ThisRelation.ado_pos[nItem];
		else
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString ID, name, age, sex;
	char sex_1;
	CRect rect;
	int i = 0;
	CString select_name_sample = L"select * from patientdata where";
	CString strNum = "";
	CString strtemp = "20";
	CString strSex[3] = { "��", "��", "Ů" };
	//��ȡ����
	m_PatientResultList.DeleteAllItems();
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
		select_name_sample += " name like '%" + name + "%' and ";
	if (age.GetLength() != 0)
		select_name_sample += " age = '" + age + "' and ";
	if (ID.GetLength() != 0)
		select_name_sample += " number like '%" + ID + "%' and ";
	if (sex.GetLength() != 0)
		select_name_sample += " sex = '" + sex + "'";
	else
		select_name_sample.Delete(select_name_sample.GetLength() - 5, 4);

	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;

	_variant_t var;

	CString filename;
	filename.Format(L"appdata.accdb");

	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return;
	ExeSql(m_pDB, m_pRs, select_name_sample);
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

		bool bo = false;
		int pos;
		is_search = false;
		while (!m_pRs->adoEOF)
		{
			if (i == 0)
			{
				m_PatientResultList.DeleteAllItems();
				is_search = true;
			}

			var = m_pRs->GetCollect("number");
			if (var.vt != VT_NULL)
				strNum = (LPCSTR)_bstr_t(var);
			ThisResult2.numofrs[i] = strNum;
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
			m_PatientResultList.SetItemText(i, 3, strID);            //��ʾ��Ϣ����һ������Ϊ�У��ڶ�������Ϊ�У�����������Ϊ����

			var = m_pRs->GetCollect("name");
			CString strName;
			if (var.vt != VT_NULL)
				strName = (LPCSTR)_bstr_t(var);
			m_PatientResultList.SetItemText(i, 4, strName);


			i++;
			m_pRs->MoveNext();

		}
		if (m_pRs->adoEOF && is_search == false)
			MessageBox(L"can not find!");
	}
	catch (_com_error &e)
	{
		TRACE("UpdateResultList�쳣");
	}
}