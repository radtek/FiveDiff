// SetMarkModeLMNEView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "SetMarkModeLMNEView.h"
#include "afxdialogex.h"
#include "FilesOperation.h"

// CSetMarkModeLMNEView �Ի���

IMPLEMENT_DYNAMIC(CSetMarkModeLMNEView, CDialogEx)

CSetMarkModeLMNEView::CSetMarkModeLMNEView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetMarkModeLMNEView::IDD, pParent)
	
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
	if(systemcfg.LMNEMarkMode== 0)
	RAD_LMNE_Manual = FALSE;
	else if(systemcfg.LMNEMarkMode== 1)
		RAD_LMNE_Manual = TRUE;
	
}

CSetMarkModeLMNEView::~CSetMarkModeLMNEView()
{
}

void CSetMarkModeLMNEView::DoDataExchange(CDataExchange* pDX)
{

	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_SETMARKMODE_LMNE_MANUAL,RAD_LMNE_Manual);
	
}


BEGIN_MESSAGE_MAP(CSetMarkModeLMNEView, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_SetLMNEModel_OK, &CSetMarkModeLMNEView::OnBnClickedSetlmnemodelOk)
END_MESSAGE_MAP()


// CSetMarkModeLMNEView ��Ϣ�������


HBRUSH CSetMarkModeLMNEView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CSetMarkModeLMNEView::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	/*@TG
#3073*/
	CPaintDC dc(this); // device context for painting
	CRect   rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));   //����Ϊ��ɫ����
	dc.Rectangle(40, 20, rect.right - 40, rect.bottom - 30);
		// TODO: �ڴ˴������Ϣ����������
		// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


void CSetMarkModeLMNEView::OnBnClickedSetlmnemodelOk()
{
	if(IsDlgButtonChecked(IDC_SETMARKMODE_LMNE_MANUAL) == BST_CHECKED)
		// GetDlgItem(IDC_SetLMNEModel_OK)->SetWindowText(L"����ִ��HGB���ԣ�");
						systemcfg.LMNEMarkMode= 0;
					else if(IsDlgButtonChecked(IDC_SETMARKMODE_LMNE_AUTO) == BST_CHECKED)
						systemcfg.LMNEMarkMode= 1;
						// GetDlgItem(IDC_SetLMNEModel_OK)->SetWindowText(L"ȷ��");
					WriteSystemcfgFile();
					MessageBox(L"���óɹ����뷵�أ�", L"OK", MB_OKCANCEL);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
