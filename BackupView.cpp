// BackupView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "BackupView.h"
#include "afxdialogex.h"

// CBackupView �Ի���

IMPLEMENT_DYNAMIC(CBackupView, CDialogEx)

CBackupView::CBackupView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBackupView::IDD, pParent)
{

}

CBackupView::~CBackupView()
{
}

void CBackupView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_BACKUP_TAB, m_backuptab);
	DDX_Control(pDX, IDC_BACKUP_INSTALL, m_backupinstall);
	DDX_Control(pDX, IDC_SHUTDOWN, m_shutup);
	DDX_Control(pDX, IDC_RESOURCE_MANAGER, m_resourceManage);
	DDX_Control(pDX, IDC_MANUAL_BACKUP, m_manualbackup);
	DDX_Control(pDX, IDC_SAVESET, m_saveset);
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
}


BEGIN_MESSAGE_MAP(CBackupView, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CBackupView ��Ϣ�������


BOOL CBackupView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	updatetabview();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


HBRUSH CBackupView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CBackupView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	//updatetabview();
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	dc.FillPath();
}

void CBackupView::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���
	CDialogEx::OnOK();
}

void CBackupView::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������

}

void CBackupView::updatetabview()
{
	CRect rectTab;
	GetDlgItem(IDC_BACKUP_TAB)->GetWindowRect(&rectTab);
	ScreenToClient(&rectTab);

	m_backuptab.Create(CBCGPTabWnd::STYLE_3D, rectTab, this, 1, CBCGPTabWnd::LOCATION_TOP);

	// m_Tasksheetpage=new CWorkstationTasksheet();
	//m_Analysispage=new CWorkstationAnalysis();
	//m_Resultpage=new CWorkstationResult();

	CSetPage.Create(IDD_BACKUP_SET, &m_backuptab);
	CRestorePage.Create(IDD_BACKUP_RESTORE, &m_backuptab);

	m_backuptab.AddTab(&CSetPage, L"�����������", 0);
	m_backuptab.AddTab(&CRestorePage, L"����ָ�", 1);

	CRect rc;
	m_backuptab.GetClientRect(rc);
	m_backuptab.SetResizeMode(CBCGPTabWnd::RESIZE_VERT);
	rc.top += 27;
	rc.bottom -= 5;
	rc.left += 5;
	rc.right -= 10;
	CSetPage.MoveWindow(&rc);
	CRestorePage.MoveWindow(&rc);
}