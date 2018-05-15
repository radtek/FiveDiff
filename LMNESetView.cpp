// LMNESetView.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "LMNESetView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"
#include "FilesOperation.h"
// CLMNESetView �Ի���

IMPLEMENT_DYNAMIC(CLMNESetView, CDialogEx)

CLMNESetView::CLMNESetView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLMNESetView::IDD, pParent)
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

CLMNESetView::~CLMNESetView()
{

}

void CLMNESetView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLMNESetView, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_APPLICATE, &CLMNESetView::OnApplicate)
END_MESSAGE_MAP()


// CLMNESetView ��Ϣ�������


void CLMNESetView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	dc.FillPath();

	CDialogEx::OnPaint();
}


HBRUSH CLMNESetView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	// TODO:  �ڴ˸��� DC ���κ�����
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC2:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	case IDC_STATIC1:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	default:
		break;
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


BOOL CLMNESetView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetDlgItem(IDC_STATIC)->SetFont(&font);
	GetDlgItem(IDC_STATIC1)->SetFont(&font1);
	GetDlgItem(IDC_STATIC2)->SetFont(&font1);

	CString peaktemp[2];
	peaktemp[0].Format(L"%d", systemcfg.lmnepeak1);
	peaktemp[1].Format(L"%d", systemcfg.lmnepeak2);
	GetDlgItem(IDC_PEAK1_EDIT)->SetWindowText(peaktemp[0]);
	GetDlgItem(IDC_PEAK2_EDIT)->SetWindowText(peaktemp[1]);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void CLMNESetView::OnApplicate()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString peaktemp[2];
	GetDlgItem(IDC_PEAK1_EDIT)->GetWindowText(peaktemp[0]);
	GetDlgItem(IDC_PEAK2_EDIT)->GetWindowText(peaktemp[1]);
	if (_wtoi(peaktemp[0]) < PEAK1_L || _wtoi(peaktemp[0]) > PEAK1_H || _wtoi(peaktemp[1]) < PEAK2_L || _wtoi(peaktemp[1]) > PEAK2_H)
	{
		if (systemcfg.language == CHINESE)
			MessageBox(L"��������ȷ������!",L"����!", MB_OK | MB_ICONINFORMATION);
		//else if (systemcfg.language == ENGLISH)
		//	CreateWarningBoxNonCHDlg(hDlg, "Please input current number!", "Warning!");
	}
	else
	{
		systemcfg.lmnepeak1 = _wtoi(peaktemp[0]);
		systemcfg.lmnepeak2 = _wtoi(peaktemp[1]);
		WriteSystemcfgFile();
		MessageBox(L"�ɹ�Ӧ��");
	}
}
