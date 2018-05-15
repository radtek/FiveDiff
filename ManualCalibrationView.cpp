// ManualCalibrationView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "ManualCalibrationView.h"
#include "afxdialogex.h"
#include "FilesOperation.h"

// CManualCalibrationView �Ի���

IMPLEMENT_DYNAMIC(CManualCalibrationView, CDialogEx)

CManualCalibrationView::CManualCalibrationView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManualCalibrationView::IDD, pParent)
	, m_moderadio(0)
	, m_testmoderadio(0)
{
	TestMode = WHOLEDIFF;
}

CManualCalibrationView::~CManualCalibrationView()
{
}

void CManualCalibrationView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_MODE_RADIO, m_moderadio);
	DDX_Radio(pDX, IDC_TESTMODE_RADIO, m_testmoderadio);
}


BEGIN_MESSAGE_MAP(CManualCalibrationView, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_MODE_RADIO, &CManualCalibrationView::OnModeRadio)
	ON_BN_CLICKED(IDC_MODE_RADIO2, &CManualCalibrationView::OnModeRadio2)
	ON_BN_CLICKED(IDC_TESTMODE_RADIO, &CManualCalibrationView::OnTestmodeRadio)
	ON_BN_CLICKED(IDC_TESTMODE_RADIO2, &CManualCalibrationView::OnTestmodeRadio2)
END_MESSAGE_MAP()
// CManualCalibrationView ��Ϣ�������


void CManualCalibrationView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	CRect   rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));   //����Ϊ��ɫ����
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


BOOL CManualCalibrationView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	ShowCalibration();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}



void CManualCalibrationView::OnModeRadio()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	ShowCalibration();

}


void CManualCalibrationView::OnModeRadio2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	ShowCalibration();
}


void CManualCalibrationView::OnTestmodeRadio()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	ShowCalibration();
}


void CManualCalibrationView::OnTestmodeRadio2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	ShowCalibration();
}


void CManualCalibrationView::ShowCalibration()
{
	CString calibrationtemp[4][5];

	if (m_moderadio == 0)
	{
		if (m_testmoderadio == 0)
		{
			TestMode = WHOLEDIFF;
		}
		else if (m_testmoderadio == 1)
		{
			TestMode = WHOLECBC;
		}
	}
	else if (m_moderadio == 1)
	{
		if (m_testmoderadio == 0)
		{
			TestMode = DILUENTDIFF;
		}
		else if (m_testmoderadio == 1)
		{
			TestMode = DILUENTCBC;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		calibrationtemp[TestMode][i].Format(L"%0.2f", systemcfg.calibration[TestMode][i]);
	}
	GetDlgItem(IDC_MANCALIB_WBCF)->SetWindowText(calibrationtemp[TestMode][0]);
	GetDlgItem(IDC_MANCALIB_RBCF)->SetWindowText(calibrationtemp[TestMode][1]);
	GetDlgItem(IDC_MANCALIB_HGBF)->SetWindowText(calibrationtemp[TestMode][2]);
	GetDlgItem(IDC_MANCALIB_MCVF)->SetWindowText(calibrationtemp[TestMode][3]);
	GetDlgItem(IDC_MANCALIB_PLTF)->SetWindowText(calibrationtemp[TestMode][4]);
}


void CManualCalibrationView::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���
	CString calibrationtemp[4][5];
	GetDlgItem(IDC_MANCALIB_WBCF)->GetWindowText(calibrationtemp[TestMode][0]);
	GetDlgItem(IDC_MANCALIB_RBCF)->GetWindowText(calibrationtemp[TestMode][1]);
	GetDlgItem(IDC_MANCALIB_HGBF)->GetWindowText(calibrationtemp[TestMode][2]);
	GetDlgItem(IDC_MANCALIB_MCVF)->GetWindowText(calibrationtemp[TestMode][3]);
	GetDlgItem(IDC_MANCALIB_PLTF)->GetWindowText(calibrationtemp[TestMode][4]);
	for (int i = 0; i < 5; i++)
	{
		systemcfg.calibration[TestMode][i] = _wtoi(calibrationtemp[TestMode][i]);
	}
	WriteSystemcfgFile();
	CDialogEx::OnOK();
}


void CManualCalibrationView::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���

	CDialogEx::OnCancel();
}
