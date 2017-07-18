// WorkstationTasksheet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "WorkstationTasksheet.h"
#include "afxdialogex.h"
#include "AddTaskView.h"
#include "FilesOperation.h"
#include <map>

// CWorkstationTasksheet �Ի���

IMPLEMENT_DYNAMIC(CWorkstationTasksheet, CDialogEx)

CWorkstationTasksheet::CWorkstationTasksheet(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWorkstationTasksheet::IDD, pParent)
{
	TaskNum = 0;
	autogenerate = false;
}

CWorkstationTasksheet::~CWorkstationTasksheet()
{

}

void CWorkstationTasksheet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WORKSTATION_TASKLIST, m_WorkstationTasklist);
	DDX_Control(pDX, IDC_ADDTASK, m_addtask);
	DDX_Control(pDX, IDC_DELETETASK, m_deletetask);
	DDX_Control(pDX, IDC_STARTEXECUTION, m_startexecute);
	DDX_Control(pDX, IDC_CLEARSHEET, m_clearsheet);
}


BEGIN_MESSAGE_MAP(CWorkstationTasksheet, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_ADDTASK, &CWorkstationTasksheet::OnBnClickedAddtask)
	ON_BN_CLICKED(IDC_DELETETASK, &CWorkstationTasksheet::OnBnClickedDeletetask)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_STARTEXECUTION, &CWorkstationTasksheet::OnBnClickedStartexecution)
	ON_MESSAGE(WM_STARTNEXTTASK, &CWorkstationTasksheet::OnStartNextTask)
	ON_BN_CLICKED(IDC_CLEARSHEET, &CWorkstationTasksheet::OnBnClickedClearsheet)
	ON_MESSAGE(WM_RESTART, &CWorkstationTasksheet::OnRestart)
END_MESSAGE_MAP()


// CWorkstationTasksheet ��Ϣ�������


void CWorkstationTasksheet::InitTaskList()
{
	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	CRect m_rect;
	GetClientRect(&m_rect);

	m_rect.top += 20;
	m_rect.bottom -= 35;
	m_rect.left += 0;
	m_rect.right -= 0;
	m_WorkstationTasklist.MoveWindow(m_rect);


	CRect rect;
	m_WorkstationTasklist.GetClientRect(&rect);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_WorkstationTasklist.SetExtendedStyle(m_WorkstationTasklist.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_WorkstationTasklist.SetItemColor(0, RGB(100, 125, 100), RGB(15, 235, 150));//�����ض�Item ���� ������ɫ
	m_WorkstationTasklist.SetRowHeigt(20);
	
	m_WorkstationTasklist.DeleteAllItems();//����б�ˢ��

	m_WorkstationTasklist.InsertColumn(0, _T("���к�"), LVCFMT_CENTER, rect.Width() / 14, 0);
	m_WorkstationTasklist.InsertColumn(1, _T("��Ʒ���"), LVCFMT_CENTER, rect.Width() / 7, 1);
	m_WorkstationTasklist.InsertColumn(2, _T("��������"), LVCFMT_CENTER, rect.Width() / 7, 2);
	m_WorkstationTasklist.InsertColumn(3, _T("�Ա�"), LVCFMT_CENTER, rect.Width() / 14, 3);
	m_WorkstationTasklist.InsertColumn(4, _T("����"), LVCFMT_CENTER, rect.Width() / 14, 4);
	m_WorkstationTasklist.InsertColumn(5, _T("�걾����"), LVCFMT_CENTER, rect.Width() / 7, 5);
	m_WorkstationTasklist.InsertColumn(6, _T("��������"), LVCFMT_CENTER, rect.Width() / 14, 6);
	m_WorkstationTasklist.InsertColumn(7, _T("���ģʽ"), LVCFMT_CENTER, rect.Width() / 7, 7);
	m_WorkstationTasklist.InsertColumn(8, _T("����"), LVCFMT_CENTER, rect.Width() / 14, 8);
	m_WorkstationTasklist.InsertColumn(9, _T("״̬"), LVCFMT_CENTER, rect.Width() / 14, 9);
}


HBRUSH CWorkstationTasksheet::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


int CWorkstationTasksheet::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}


BOOL CWorkstationTasksheet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitTaskList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CWorkstationTasksheet::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	// TODO:  �ڴ˴������Ϣ����������
	if (nType == 1) return;//��С����ʲô������  
	// TODO: Add your message handler code here  
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_WORKSTATION_TASKLIST);
	ChangeSize(pWnd, cx, cy);
	pWnd = GetDlgItem(IDC_BUTTON1);
	ChangeSize(pWnd, cx, cy);
	GetClientRect(&m_rect);// ���仯��ĶԻ����С��Ϊ�ɴ�С   
}


void CWorkstationTasksheet::ChangeSize(CWnd *pWnd, int cx, int cy)
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

void CWorkstationTasksheet::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	dc.FillPath();
}


void CWorkstationTasksheet::OnBnClickedAddtask()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CAddTaskView  m_addtaskview;


	if (m_addtaskview.DoModal()==IDOK)
	{
		m_tasksheettask = m_addtaskview.m_task;
		autogenerate = m_addtaskview.GenerateNumAuto;
		if (autogenerate == true)
		{
			autogeneratetimes++;
		}
		AddSingleTask(&m_tasksheettask);
		m_alltask.push_back(m_tasksheettask);

	}
}


int	CWorkstationTasksheet::autogeneratetimes=0;

void CWorkstationTasksheet::AddSingleTask(task_info* taskdata)
{
	CString name, barcode, doctor, age, department, testtime, number, status,NO;
	CString sex,testmode;
	USES_CONVERSION;

	NO.Format(L"%d",TaskNum+1);
	name = A2W(taskdata->name);
	doctor = A2W(taskdata->doctor);
	age = A2W(taskdata->age);
	barcode = A2W(taskdata->barcode);
	department = A2W(taskdata->department);
	testtime = A2W(taskdata->time);
	taskdata->row += TaskNum;
	if (autogenerate == true)
	{
		taskdata->number = taskdata->number + autogeneratetimes - 1;
	}
	number.Format(L"%d", taskdata->number);
	status = A2W(taskdata->status);
	if (taskdata->sex == 0)
		sex = "��";
	else if (taskdata->sex == 1)
		sex = "��";
	else
		sex = "Ů";
	ReadSystemcfgFile();
	if (systemcfg.mode == 0)//����ģʽ 0:ȫѪ+CBC5DIFF,1:ȫѪ+CBC,2:Ԥϡ��+CBC5DIFF,3:Ԥϡ��+CBC
		testmode = "ȫѪ+CBC5DIFF";
	else if (systemcfg.mode == 1)
		testmode = "ȫѪ+CBC";
	else if (systemcfg.mode == 2)
		testmode = "Ԥϡ��+CBC5DIFF";
	else testmode = "Ԥϡ��+CBC";


	if (taskdata->taskmode == 1)
	{
		NO.Format(L"%d", TaskNum + 1);
		name = "";
		testmode = "��ϴ";
	}

	m_WorkstationTasklist.InsertItem(TaskNum, L"����");
	m_WorkstationTasklist.SetItemText(TaskNum, 0, NO);
	m_WorkstationTasklist.SetItemText(TaskNum, 1, number);
	m_WorkstationTasklist.SetItemText(TaskNum, 2, name);
	m_WorkstationTasklist.SetItemText(TaskNum, 3, sex);
	m_WorkstationTasklist.SetItemText(TaskNum, 4, age);
	m_WorkstationTasklist.SetItemText(TaskNum, 5, barcode);
	m_WorkstationTasklist.SetItemText(TaskNum, 6, testtime);
	m_WorkstationTasklist.SetItemText(TaskNum, 7, testmode);
	m_WorkstationTasklist.SetItemText(TaskNum, 8, department);
	m_WorkstationTasklist.SetItemText(TaskNum, 9, status);
	TaskNum++;
}



void CWorkstationTasksheet::OnBnClickedDeletetask()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	POSITION pos = m_WorkstationTasklist.GetFirstSelectedItemPosition();
	if (pos == NULL&&m_WorkstationTasklist.GetNextSelectedItem(pos) < m_WorkstationTasklist.GetItemCount())
	{
		MessageBox(L"û������ѡ��!", L"��ʾ!", MB_OK | MB_ICONINFORMATION);
		return;
	}
	else
	{
		int nItem = m_WorkstationTasklist.GetNextSelectedItem(pos);
		TRACE1("Item %d was selected!\n", nItem);
		if (nItem < m_WorkstationTasklist.GetItemCount())
		{
			int sum = m_alltask.size();
			auto it = m_alltask.begin() + nItem;
			it=m_alltask.erase(it);
			TaskNum--;
			autogeneratetimes--;
			for (it; it != m_alltask.end(); it++)
			{
				it->number = it->number - 1;
				TRACE(L"%d\n",it->number);
			}
			UpdateTaskList(m_alltask);
		}
	}
}

void CWorkstationTasksheet::UpdateTaskList(vector<task_info> taskdata)
{

	CString name, barcode, doctor, age, department, testtime, number, status, NO;
	CString sex, testmode;
	USES_CONVERSION;
	m_WorkstationTasklist.DeleteAllItems();
	int sum = taskdata.size();
	for (int i = 0; i < sum; i++)
	{
		NO.Format(L"%d", i + 1);
		name = A2W(taskdata[i].name);
		doctor = A2W(taskdata[i].doctor);
		age = A2W(taskdata[i].age);
		barcode = A2W(taskdata[i].barcode);
		department = A2W(taskdata[i].department);
		testtime = A2W(taskdata[i].time);

		number.Format(L"%d", taskdata[i].number);
		status = A2W(taskdata[i].status);
		if (taskdata[i].sex == 0)
			sex = "��";
		else if (taskdata[i].sex == 1)
			sex = "��";
		else
			sex = "Ů";
		switch (taskdata[i].mode)//����ģʽ 0:ȫѪ+CBC5DIFF,1:ȫѪ+CBC,2:Ԥϡ��+CBC5DIFF,3:Ԥϡ��+CBC
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
		m_WorkstationTasklist.InsertItem(i, L"����");
		m_WorkstationTasklist.SetItemText(i, 0, NO);
		m_WorkstationTasklist.SetItemText(i, 1, number);
		m_WorkstationTasklist.SetItemText(i, 2, name);
		m_WorkstationTasklist.SetItemText(i, 3, sex);
		m_WorkstationTasklist.SetItemText(i, 4, age);
		m_WorkstationTasklist.SetItemText(i, 5, barcode);
		m_WorkstationTasklist.SetItemText(i, 6, testtime);
		m_WorkstationTasklist.SetItemText(i, 7, testmode);
		m_WorkstationTasklist.SetItemText(i, 8, department);
		m_WorkstationTasklist.SetItemText(i, 9, status);
	}
}

void CWorkstationTasksheet::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnClose();
}

void CWorkstationTasksheet::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���

	CDialogEx::OnOK();
}


void CWorkstationTasksheet::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���

	CDialogEx::OnCancel();
}

void CWorkstationTasksheet::UpdateTaskStatus(int number,int process)
{
	// TODO:  �ڴ����ר�ô����/����û���
	switch (process)
	{
	case 0:
		m_WorkstationTasklist.SetItemText(number,9,L"δ����");
		memset(m_alltask[number].status, 0, sizeof(m_alltask[number].status));
		sprintf(m_alltask[number].status, "δ����");
		break;
	case 1:
		m_WorkstationTasklist.SetItemText(number, 9, L"���Խ�����");
		memset(m_alltask[number].status, 0, sizeof(m_alltask[number].status));
		sprintf(m_alltask[number].status, "���Խ�����");
		break;
	case 2:
		m_WorkstationTasklist.SetItemText(number, 9, L"���Խ���");
		memset(m_alltask[number].status, 0, sizeof(m_alltask[number].status));
		sprintf(m_alltask[number].status, "���Խ���");
		break;
	case 3:
		m_WorkstationTasklist.SetItemText(number, 9, L"����ʧ��");
		memset(m_alltask[number].status, 0, sizeof(m_alltask[number].status));
		sprintf(m_alltask[number].status, "����ʧ��");
		break;
	default:
		break;
	}
}

int	CWorkstationTasksheet::startnum=0;
void CWorkstationTasksheet::OnBnClickedStartexecution()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int tasknum;
	tasknum=m_WorkstationTasklist.GetItemCount();
	if (tasknum == 0)
	{
		MessageBox(L"������!", L"��ʾ!", MB_OK | MB_ICONINFORMATION);
		return;
	}
	if (!CheckDifferent())
	{
		if (MessageBox(L"���ظ���Ʒ����ȷ���Ƿ����!", L"��ʾ!", MB_OKCANCEL | MB_ICONINFORMATION) != IDOK)
		{
			return;
		}
	}
	startnum = m_alltask[0].number;
	LockTheButton();
	SendMessage(WM_STARTNEXTTASK,(WPARAM)startnum,0);
	//
}

bool CWorkstationTasksheet::CheckDifferent()
{
	int sum = m_WorkstationTasklist.GetItemCount();
	//vector<CString> barcode;
	map<CString,bool> barcode;
	for (int i = 0; i < sum; i++)
	{
		if (barcode.find(m_WorkstationTasklist.GetItemText(i, 5)) == barcode.end() )
		{
			barcode[m_WorkstationTasklist.GetItemText(i, 5)]=true;
		}
		else
		{
			if(m_WorkstationTasklist.GetItemText(i, 5) != "")
				return false;
			else continue;
		}
	}
	return true;
}

void CWorkstationTasksheet::LockTheButton()
{
	GetDlgItem(IDC_ADDTASK)->EnableWindow(false);
	GetDlgItem(IDC_DELETETASK)->EnableWindow(false);
	GetDlgItem(IDC_STARTEXECUTION)->EnableWindow(false);
	GetDlgItem(IDC_CLEARSHEET)->EnableWindow(false);
}

void CWorkstationTasksheet::FreeTheButton()
{
	GetDlgItem(IDC_ADDTASK)->EnableWindow(true);
	GetDlgItem(IDC_DELETETASK)->EnableWindow(true);
	GetDlgItem(IDC_STARTEXECUTION)->EnableWindow(true);
	GetDlgItem(IDC_CLEARSHEET)->EnableWindow(true);
}

afx_msg LRESULT CWorkstationTasksheet::OnStartNextTask(WPARAM wParam, LPARAM lParam)
{
	int sum;
	int tasknum = (int)wParam;
	int Serialnum=0;
	bool numexit = false;
	TRACE(L"------%d-------\n",tasknum);
	sum = m_WorkstationTasklist.GetItemCount();
	for (int i = 0; i < sum; i++)
	{
		CString number;
		CString number_str;
		number_str.Format(L"%d",tasknum);
		number=m_WorkstationTasklist.GetItemText(i,1);
		if (number_str == number)
		{
			Serialnum = i;
			numexit = true;
			break;
		}
	}
	if (numexit == false)
	{
		Serialnum = sum;
	}

	if (Serialnum > 0)
	{
		UpdateTaskStatus(Serialnum - 1, 2);
	}
	TRACE("---------%d-------------\n",numexit);
	if (numexit == false)
	{
		MessageBox(L"�޴�������������!", L"��ʾ!", MB_OKCANCEL | MB_ICONINFORMATION);
		GetDlgItem(IDC_CLEARSHEET)->EnableWindow(true);
		return 0;
	}
	if (m_alltask[Serialnum].taskmode == 0)
	{
		MessageBox(L"��׼������Ʒ!", L"��ʾ", MB_OK | MB_ICONINFORMATION);
	}

	UpdateTaskStatus(Serialnum, 1);
	CWnd* pWnd = GetParent()->GetParent();
	if (m_alltask[Serialnum].taskmode == 0)
	{
		::SendMessage(pWnd->m_hWnd, WM_WORKSHEET_TEST, (WPARAM)&m_alltask[Serialnum], 0);
	}
	else if (m_alltask[Serialnum].taskmode == 1)
	{
		::SendMessage(pWnd->m_hWnd, WM_WORKSHEET_CLEAN, (WPARAM)&m_alltask[Serialnum], 0);
	}
	::SendMessage(pWnd->m_hWnd, WM_GETALLTASKINFO, (WPARAM)&m_alltask, 0);
	return 0;
}


void CWorkstationTasksheet::OnBnClickedClearsheet()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_WorkstationTasklist.DeleteAllItems();
	m_alltask.erase(m_alltask.begin(), m_alltask.end());
	FreeTheButton();
	TaskNum = 0;
}


afx_msg LRESULT CWorkstationTasksheet::OnRestart(WPARAM wParam, LPARAM lParam)
{
	FreeTheButton();
	return 0;
}
