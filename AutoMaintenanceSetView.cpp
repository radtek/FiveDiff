// AutoMaintenanceSetView.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "AutoMaintenanceSetView.h"
//
//#include"Includes_app.h"
#include "FilesOperation.h"

// CAutoMaintenanceSetView �Ի���

IMPLEMENT_DYNAMIC(CAutoMaintenanceSetView, CDialogEx)

CAutoMaintenanceSetView::CAutoMaintenanceSetView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAutoMaintenanceSetView::IDD, pParent)
	, m_microperfusiontimeRadio(0)
{
	VERIFY(font.CreateFont(
		20,                        // nHeight
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

	VERIFY(font1.CreateFont(
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

CAutoMaintenanceSetView::~CAutoMaintenanceSetView()
{
}

void CAutoMaintenanceSetView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_TIME_RADIO1, m_microperfusiontimeRadio);
}


BEGIN_MESSAGE_MAP(CAutoMaintenanceSetView, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_APPLICATE_MANTAINSET, &CAutoMaintenanceSetView::OnApplicateMantainset)
END_MESSAGE_MAP()


// CAutoMaintenanceSetView ��Ϣ�������


void CAutoMaintenanceSetView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CFont* pOldFont = dc.SelectObject(&globalData.fontCaption);

	dc.SetTextColor(globalData.clrWindowText);
	dc.SetBkMode(TRANSPARENT);


	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect,RGB(255,255,255));
	dc.FillPath();
	
	CDialogEx::OnPaint();
}




HBRUSH CAutoMaintenanceSetView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	case IDC_STATIC2:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	case IDC_STATIC3:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	case IDC_STATIC4:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	case IDC_STATIC5:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	case IDC_STATIC6:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	case IDC_TIME_RADIO1:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	case IDC_TIME_RADIO2:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	case IDC_TIME_RADIO3:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	case IDC_TIME_RADIO4:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	default:
		break;
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


BOOL CAutoMaintenanceSetView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetDlgItem(IDC_STATIC)->SetFont(&font);
	GetDlgItem(IDC_STATIC2)->SetFont(&font);
	GetDlgItem(IDC_STATIC3)->SetFont(&font1);
	GetDlgItem(IDC_STATIC4)->SetFont(&font1);
	GetDlgItem(IDC_STATIC5)->SetFont(&font1);
	GetDlgItem(IDC_STATIC6)->SetFont(&font1);
	GetDlgItem(IDC_TIME_RADIO1)->SetFont(&font1);
	GetDlgItem(IDC_TIME_RADIO2)->SetFont(&font1);
	GetDlgItem(IDC_TIME_RADIO3)->SetFont(&font1);
	GetDlgItem(IDC_TIME_RADIO4)->SetFont(&font1);

	switch (systemcfg.miniprimetime)
	{
	case 30:
		m_microperfusiontimeRadio = 0;
		break;
	case 40:
		m_microperfusiontimeRadio = 1;
		break;
	case 50:
		m_microperfusiontimeRadio = 2;
		break;
	case 60:
		m_microperfusiontimeRadio = 3;
		break;
	default:
		break;
	}
	CString strtemp, strtemp1;
	strtemp.Format(L"%d",systemcfg.cleanperiod);
	strtemp1.Format(L"%d", systemcfg.washfrequency);
	GetDlgItem(IDC_CLEAN_INTERVAL)->SetWindowText(strtemp);
	GetDlgItem(IDC_CLEAN_TIMES)->SetWindowText(strtemp1);
	UpdateData(false);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

BOOL CAutoMaintenanceSetView::SaveIntervalFrequency()
{
	CString buffer, buffer1;
	char *   intervaltemp;
	char * timestemp;
	int buf_len1, buf_len2,temp;
	GetDlgItem(IDC_CLEAN_INTERVAL)->GetWindowText(buffer);
	GetDlgItem(IDC_CLEAN_TIMES)->GetWindowText(buffer1);
	USES_CONVERSION;
	intervaltemp = W2A(buffer);
	timestemp = W2A(buffer1);
	buf_len1 = strlen(intervaltemp);
	buf_len2 = strlen(timestemp);
	for (int i = 0; i < buf_len1; i++)
	{
		if (!(intervaltemp[i] >= '0'&&intervaltemp[i] <= '9'))
		{
			if (systemcfg.language == CHINESE)
				MessageBox(L"������Ϸ��ַ�!",L"����!", MB_OK | MB_ICONINFORMATION);
			//else if (systemcfg.language == ENGLISH)
			//	CreateWarningBoxNonCHDlg(HWND_DESKTOP, "Please input legal char!", "Warning!");
			return FALSE;
		}
	}
	temp = atoi(intervaltemp);
	if (temp >= 1 && temp <= 200)
		systemcfg.cleanperiod = temp;
	else
	{
		if (systemcfg.language == CHINESE)
			MessageBox(L"��������ȷ��Χʱ��!",L"����!", MB_OK | MB_ICONINFORMATION);
		return FALSE;
	}
	for (int i = 0; i < buf_len2; i++)
	{
		if (!(timestemp[i] >= '0'&&timestemp[i] <= '9'))
		{
			if (systemcfg.language == CHINESE)
				MessageBox(L"������Ϸ��ַ�!", L"����!", MB_OK | MB_ICONINFORMATION);
			//else if (systemcfg.language == ENGLISH)
			//	CreateWarningBoxNonCHDlg(HWND_DESKTOP, "Please input legal char!", "Warning!");
			return FALSE;
		}

	}
	temp = atoi(timestemp);
	if (temp >= 1 && temp <= 100)
		systemcfg.washfrequency = temp;
	else
	{
		if (systemcfg.language == CHINESE)
			MessageBox(L"��������ȷ����!",L"����!", MB_OK | MB_ICONINFORMATION);
	/*	else if (systemcfg.language == ENGLISH)
			CreateWarningBoxNonCHDlg(HWND_DESKTOP, "Please input Correct times!", "Warning!");*/
		return FALSE;
	}
	return TRUE;
}
void CAutoMaintenanceSetView::OnApplicateMantainset()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	switch (m_microperfusiontimeRadio)
	{
	case 0:
		systemcfg.miniprimetime = 30;
		break;
	case 1:
		systemcfg.miniprimetime = 40;
		break;
	case 2:
		systemcfg.miniprimetime = 50;
		break;
	case 3:
		systemcfg.miniprimetime = 60;
		break;
	default:
		systemcfg.miniprimetime = 60;
		break;
	}
	if (SaveIntervalFrequency())
	{
		MessageBox(L"�޸ĳɹ�");
	}
	WriteSystemcfgFile();
}

