// WorkstationAnalysis.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "WorkstationAnalysis.h"
#include "afxdialogex.h"


// CWorkstationAnalysis �Ի���

IMPLEMENT_DYNAMIC(CWorkstationAnalysis, CDialogEx)

CWorkstationAnalysis::CWorkstationAnalysis(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWorkstationAnalysis::IDD, pParent)
{

}

CWorkstationAnalysis::~CWorkstationAnalysis()
{

}

void CWorkstationAnalysis::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ANALYSIS_LIST, m_analysisList);

}


BEGIN_MESSAGE_MAP(CWorkstationAnalysis, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_MESSAGE(WM_GETALLTASKINFO, &CWorkstationAnalysis::OnGetallTaskInfo)
	ON_MESSAGE(WM_GETRESULT, &CWorkstationAnalysis::OnGetresult)
END_MESSAGE_MAP()


// CWorkstationAnalysis ��Ϣ�������


HBRUSH CWorkstationAnalysis::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CWorkstationAnalysis::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������

	CWnd *pWnd;

}

void CWorkstationAnalysis::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	dc.FillPath();
}

BOOL CWorkstationAnalysis::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitAnaliysisList();


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void CWorkstationAnalysis::ChangeSize(CWnd *pWnd, int cx, int cy)
{
	if (pWnd)  //�ж��Ƿ�Ϊ�գ���Ϊ�Ի��򴴽�ʱ����ô˺���������ʱ�ؼ���δ����	
	{
		CRect rect;   //��ȡ�ؼ��仯ǰ�Ĵ�С  
		pWnd->GetWindowRect(&rect);
		ScreenToClient(&rect);//���ؼ���Сת��Ϊ�ڶԻ����е���������

		//    cx/m_rect.Width()Ϊ�Ի����ں���ı仯����
		rect.left = rect.left*cx / m_rect.Width();//�����ؼ���С
		rect.right = rect.right*cx / m_rect.Width();
		rect.top = rect.top*cy / m_rect.Height();
		rect.bottom = rect.bottom*cy / m_rect.Height();
		pWnd->MoveWindow(rect);//���ÿؼ���С
	}
}

afx_msg LRESULT CWorkstationAnalysis::OnGetallTaskInfo(WPARAM wParam, LPARAM lParam)
{
	m_alltask = (vector<task_info>*)wParam;
	return 0;
}


afx_msg LRESULT CWorkstationAnalysis::OnGetresult(WPARAM wParam, LPARAM lParam)
{
	sampledata = (sample_info*)wParam;
	int num = GetthetaskSerialNum(sampledata);
	FillResultInfo(sampledata, &((*m_alltask)[num]));
	UpdateAnaliysisList(num+1);
	return 0;
}

int CWorkstationAnalysis::GetthetaskSerialNum(sample_info* sampledata)
{
	int  sum;
	int  Serialnum = 0;
	bool numexit = false;
	CString numberofresult;
	numberofresult.Format(L"%d",sampledata->number);
	sum = m_alltask->size();
	for (auto it = m_alltask->begin(); it != m_alltask->end(); it++, Serialnum++)
	{
		CString number_temp;
		number_temp.Format(L"%d", it->number);
		if (numberofresult == number_temp)
		{
			numexit = true;
			break;
		}
	}
	return Serialnum;
}

void CWorkstationAnalysis::InitAnaliysisList()
{
	CRect rect;
	m_analysisList.GetClientRect(&rect);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_analysisList.SetExtendedStyle(m_analysisList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_analysisList.SetItemColor(0, RGB(100, 125, 100), RGB(15, 235, 150));//�����ض�Item ���� ������ɫ
	m_analysisList.SetRowHeigt(20);

	m_analysisList.DeleteAllItems();//����б�ˢ��

	m_analysisList.InsertColumn(0, _T("���к�"), LVCFMT_CENTER, rect.Width() / 7, 0);
	m_analysisList.InsertColumn(1, _T("��Ʒ���"), LVCFMT_CENTER, rect.Width() *2/ 7, 1);
	m_analysisList.InsertColumn(2, _T("��������"), LVCFMT_CENTER, rect.Width() *2/ 7, 2);
	m_analysisList.InsertColumn(3, _T("���ģʽ"), LVCFMT_CENTER, rect.Width() *2/ 7, 3);
	
}

void CWorkstationAnalysis::UpdateAnaliysisList(int num)
{
	m_analysisList.DeleteAllItems();
	USES_CONVERSION;
	if (m_alltask->size() >= 2)
	{
		if (num <= (m_alltask->size() - 2))
		{
			CString num1, samplenum1, patientname1, testmode1;
			CString num2, samplenum2, patientname2, testmode2;

			num1.Format(L"%d", num);
			samplenum1.Format(L"%d", (*m_alltask)[num].number);
			patientname1 = A2W((*m_alltask)[num].name);
			switch ((*m_alltask)[num].mode)//����ģʽ 0:ȫѪ+CBC5DIFF,1:ȫѪ+CBC,2:Ԥϡ��+CBC5DIFF,3:Ԥϡ��+CBC
			{
			case 0:
				testmode1 = "ȫѪ+CBC5DIFF";
				break;
			case 1:
				testmode1 = "ȫѪ+CBC";
				break;
			case 2:
				break;
				testmode1 = "Ԥϡ��+CBC5DIFF";
			case 3:
				testmode1 = "Ԥϡ��+CBC";
				break;
			default:
				break;
			}
			m_analysisList.InsertItem(0, L"���");
			m_analysisList.SetItemText(0, 0, num1);
			m_analysisList.SetItemText(0, 1, samplenum1);
			m_analysisList.SetItemText(0, 2, patientname1);
			m_analysisList.SetItemText(0, 3, testmode1);

			num2.Format(L"%d", num + 1);
			samplenum2.Format(L"%d", (*m_alltask)[num + 1].number);
			patientname2 = A2W((*m_alltask)[num + 1].name);
			switch ((*m_alltask)[num + 1].mode)//����ģʽ 0:ȫѪ+CBC5DIFF,1:ȫѪ+CBC,2:Ԥϡ��+CBC5DIFF,3:Ԥϡ��+CBC
			{
			case 0:
				testmode1 = "ȫѪ+CBC5DIFF";
				break;
			case 1:
				testmode1 = "ȫѪ+CBC";
				break;
			case 2:
				break;
				testmode1 = "Ԥϡ��+CBC5DIFF";
			case 3:
				testmode1 = "Ԥϡ��+CBC";
				break;
			default:
				break;
			}
			m_analysisList.InsertItem(1, L"���");
			m_analysisList.SetItemText(1, 0, num2);
			m_analysisList.SetItemText(1, 1, samplenum2);
			m_analysisList.SetItemText(1, 2, patientname2);
			m_analysisList.SetItemText(1, 3, testmode2);
		}
	}
	
	if (num == (m_alltask->size() - 1))
	{
		CString num1, samplenum1, patientname1, testmode1;
		CString num2;

		num1.Format(L"%d", num);
		num2.Format(L"%d",num+1);
		samplenum1.Format(L"%d", (*m_alltask)[num].number);
		patientname1 = A2W((*m_alltask)[num].name);

		switch ((*m_alltask)[num].mode)//����ģʽ 0:ȫѪ+CBC5DIFF,1:ȫѪ+CBC,2:Ԥϡ��+CBC5DIFF,3:Ԥϡ��+CBC
		{
		case 0:
			testmode1 = "ȫѪ+CBC5DIFF";
			break;
		case 1:
			testmode1 = "ȫѪ+CBC";
			break;
		case 2:
			break;
			testmode1 = "Ԥϡ��+CBC5DIFF";
		case 3:
			testmode1 = "Ԥϡ��+CBC";
			break;
		default:
			break;
		}
		m_analysisList.InsertItem(0, L"���");
		m_analysisList.SetItemText(0, 0, num1);
		m_analysisList.SetItemText(0, 1, samplenum1);
		m_analysisList.SetItemText(0, 2, patientname1);
		m_analysisList.SetItemText(0, 3, testmode1);

		m_analysisList.InsertItem(1, L"���");
		m_analysisList.SetItemText(1, 0, num2);
	}
	if (num > (m_alltask->size() - 1))
	{
		CString num1, num2;
		num1.Format(L"%d", num);
		num2.Format(L"%d", num + 1);

		m_analysisList.InsertItem(0, L"���");
		m_analysisList.SetItemText(0, 0, num1);

		m_analysisList.InsertItem(1, L"���");
		m_analysisList.SetItemText(1, 0, num2);
	}
}

void CWorkstationAnalysis::FillResultInfo(sample_info* sampledata, task_info* taskdata)
{

	USES_CONVERSION;
	CString serialnum, samplenum, paitientname, sex, age, testmode, testtime, barcode, department;
	int serialnum_temp = GetthetaskSerialNum(sampledata);
	serialnum.Format(L"%d",serialnum_temp);
	samplenum.Format(L"%d",sampledata->number);
	//paitientname.Format(L"%s", taskdata->name);
	paitientname = A2W(taskdata->name);
	switch (taskdata->sex)
	{
	case 0:
		sex = "��";
		break;
	case 1:
		sex = "��";
		break;
	case 2:
		sex = "Ů";
		break;
	default:
		sex = "��";
		break;
	}
	//age.Format(L"%d",taskdata->age);
	age = A2W(taskdata->age);
	switch (sampledata->mode)//����ģʽ 0:ȫѪ+CBC5DIFF,1:ȫѪ+CBC,2:Ԥϡ��+CBC5DIFF,3:Ԥϡ��+CBC
	{
	case 0:
		testmode = "ȫѪ+CBC5DIFF";
		break;
	case 1:
		testmode = "ȫѪ+CBC";
		break;
	case 2:
		break;
		testmode = "Ԥϡ��+CBC5DIFF";
	case 3:
		testmode = "Ԥϡ��+CBC";
		break;
	default:
		break;
	}


	if (taskdata->taskmode == 1)
	{
		testmode = "��ϴ";
	}
	testtime.Format(L"%d", sampledata->time);
	barcode = A2W(taskdata->barcode);
	department = A2W(taskdata->department);

	GetDlgItem(IDC_SERIALNUM_EDIT)->SetWindowText(serialnum);
	GetDlgItem(IDC_SAMPLENUM_EDIT)->SetWindowText(samplenum);
	GetDlgItem(IDC_PAITIENTINFO_EDIT)->SetWindowText(paitientname);
	GetDlgItem(IDC_SEX_EDIT)->SetWindowText(sex);
	GetDlgItem(IDC_AGE_EDIT)->SetWindowText(age);
	GetDlgItem(IDC_TESTMODE_EDIT)->SetWindowText(testmode);
	GetDlgItem(IDC_TESTTIME_EDIT)->SetWindowText(testtime);
	GetDlgItem(IDC_BARCODE_EDIT)->SetWindowText(barcode);
	GetDlgItem(IDC_DEPARTMENT_EDIT)->SetWindowText(department);

	GetDlgItem(IDC_ANALYSIS_WBC)->SetWindowText(A2W(sampledata->wbcdata.wbc));
	GetDlgItem(IDC_ANALYSIS_LYMP)->SetWindowText(A2W(sampledata->wbcdata.lymp));
	GetDlgItem(IDC_ANALYSIS_NEUP)->SetWindowText(A2W(sampledata->wbcdata.neup));
	GetDlgItem(IDC_ANALYSIS_MONOP)->SetWindowText(A2W(sampledata->wbcdata.monop));
	GetDlgItem(IDC_ANALYSIS_EOSP)->SetWindowText(A2W(sampledata->wbcdata.eosp));
	GetDlgItem(IDC_ANALYSIS_BASOP)->SetWindowText(A2W(sampledata->wbcdata.basp));
	GetDlgItem(IDC_ANALYSIS_ALYP)->SetWindowText(A2W(sampledata->wbcdata.alyp));
	GetDlgItem(IDC_ANALYSIS_LICP)->SetWindowText(A2W(sampledata->wbcdata.licp));
	GetDlgItem(IDC_ANALYSIS_LYMA)->SetWindowText(A2W(sampledata->wbcdata.lym));
	GetDlgItem(IDC_ANALYSIS_NEUA)->SetWindowText(A2W(sampledata->wbcdata.neu));
	GetDlgItem(IDC_ANALYSIS_MONOA)->SetWindowText(A2W(sampledata->wbcdata.mono));
	GetDlgItem(IDC_ANALYSIS_EOSA)->SetWindowText(A2W(sampledata->wbcdata.eos));
	GetDlgItem(IDC_ANALYSIS_BASOA)->SetWindowText(A2W(sampledata->wbcdata.bas));
	GetDlgItem(IDC_ANALYSIS_ALYA)->SetWindowText(A2W(sampledata->wbcdata.aly));
	GetDlgItem(IDC_ANALYSIS_LICA)->SetWindowText(A2W(sampledata->wbcdata.lic));


	GetDlgItem(IDC_ANALYSIS_RBC)->SetWindowText(A2W(sampledata->rbcdata.rbc));
	GetDlgItem(IDC_ANALYSIS_HGB)->SetWindowText(A2W(sampledata->rbcdata.hgb));
	GetDlgItem(IDC_ANALYSIS_HCT)->SetWindowText(A2W(sampledata->rbcdata.hct));
	GetDlgItem(IDC_ANALYSIS_MCV)->SetWindowText(A2W(sampledata->rbcdata.mcv));
	GetDlgItem(IDC_ANALYSIS_MCH)->SetWindowText(A2W(sampledata->rbcdata.mch));
	GetDlgItem(IDC_ANALYSIS_MCHC)->SetWindowText(A2W(sampledata->rbcdata.mchc));
	GetDlgItem(IDC_ANALYSIS_RDW_CV)->SetWindowText(A2W(sampledata->rbcdata.rdwcv));
	GetDlgItem(IDC_ANALYSIS_RDW_SD)->SetWindowText(A2W(sampledata->rbcdata.rdwsd));

	GetDlgItem(IDC_ANALYSIS_PLT)->SetWindowText(A2W(sampledata->pltdata.plt));
	GetDlgItem(IDC_ANALYSIS_MPV)->SetWindowText(A2W(sampledata->pltdata.mpv));
	GetDlgItem(IDC_ANALYSIS_PDW)->SetWindowText(A2W(sampledata->pltdata.pdw));
	GetDlgItem(IDC_ANALYSIS_PCT)->SetWindowText(A2W(sampledata->pltdata.pct));
	GetDlgItem(IDC_ANALYSIS_PLCR)->SetWindowText(A2W(sampledata->pltdata.plcr));
}


