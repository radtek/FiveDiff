// BASOLandmarkView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "BASOLandmarkView.h"
#include "afxdialogex.h"
#include "FilesOperation.h"

int baso1,baso2,baso3;
// CBASOLandmarkView �Ի���

IMPLEMENT_DYNAMIC(CBASOLandmarkView, CDialogEx)

CBASOLandmarkView::CBASOLandmarkView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBASOLandmarkView::IDD, pParent)
{
	VERIFY(m_Font.CreateFont(
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


}

CBASOLandmarkView::~CBASOLandmarkView()
{
}

void CBASOLandmarkView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBASOLandmarkView, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &CBASOLandmarkView::OnBnClickedOk)
END_MESSAGE_MAP()


// CBASOLandmarkView ��Ϣ�������


HBRUSH CBASOLandmarkView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

//#3018
//
//#3019
//	return hbr;
//
//#3018
//
//#3019
//	return hbr;
//	// TODO:  �ڴ˸��� DC ���κ�����
//
//#3019
//	return hbr;
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SelectObject(&m_Font);
		pDC->SetBkColor(RGB(255, 255, 255));//���ֱ���ɫ
		HBRUSH b = CreateSolidBrush(RGB(255, 255, 255));//�ؼ�����ɫ   
		return b;
	}
	//if (nCtlColor == CTLCOLOR_EDIT)
	//{
	//	pDC->SetTextColor(RGB(0, 0, 0));
	//pDC->SelectObject(&m_Font);
	//pDC->SetBkColor(RGB(255, 255, 255));//���ֱ���ɫ
	//	HBRUSH b = CreateSolidBrush(RGB(255, 255, 255));//�ؼ�����ɫ

	//}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CBASOLandmarkView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	/*@TG
#3073*/
	CString str;
	CRect   rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));   //����Ϊ��ɫ����
	dc.Rectangle(40, 20, rect.right - 40, rect.bottom - 30);
	Edit_BASO1=(CEdit *)GetDlgItem(IDC_THD_QC_BASO1);
	Edit_BASO1->SetFont(&m_Font);
	Edit_BASO2=(CEdit *)GetDlgItem(IDC_THD_QC_BASO2);
	Edit_BASO2->SetFont(&m_Font);
	Edit_BASO3=(CEdit *)GetDlgItem(IDC_THD_QC_BASO3);
	Edit_BASO3->SetFont(&m_Font);

	str.Format(L"%d",systemcfg.range.thresholds_qc[0]);
	GetDlgItem(IDC_THD_QC_BASO1)->SetWindowText((LPCTSTR)str);
	str.Format(L"%d",systemcfg.range.thresholds_qc[1]);
	GetDlgItem(IDC_THD_QC_BASO2)->SetWindowText((LPCTSTR)str);
	str.Format(L"%d",systemcfg.range.thresholds_qc[2]);
	GetDlgItem(IDC_THD_QC_BASO3)->SetWindowText((LPCTSTR)str);
		// TODO: �ڴ˴������Ϣ����������
		// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


void CBASOLandmarkView::OnBnClickedOk()
{
	baso1= GetDlgItemInt(IDC_THD_QC_BASO1);
	baso2= GetDlgItemInt(IDC_THD_QC_BASO2);
	baso3= GetDlgItemInt(IDC_THD_QC_BASO3);
	if(baso1>254||baso2>254||baso3>254)
	{
	if(baso1>254)
		MessageBox(L"BASO1��ֵ������Χ��", L"ERROR", MB_OKCANCEL);
	if(baso2>254)
		MessageBox(L"BASO2��ֵ������Χ��", L"ERROR", MB_OKCANCEL);
	if(baso3>254)
		MessageBox(L"BASO3��ֵ������Χ��", L"ERROR", MB_OKCANCEL);
	}
	else
	{
		systemcfg.range.thresholds_qc[0] = baso1;
		systemcfg.range.thresholds_qc[1] = baso2;
		systemcfg.range.thresholds_qc[2] = baso3;
		WriteSystemcfgFile();
		MessageBox(L"���óɹ����뷵�أ�", L"OK", MB_OK);
	}
		
		
	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}
