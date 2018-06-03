// ReabentalarmView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "ReagentalarmView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"
#include "FilesOperation.h"

// CReabentalarmView �Ի���
    bool warn_diluent;
	 bool warn_rinse;
	 bool warn_hgblyse;
	 bool warn_fixlyse;
	 bool warn_basolyse;
	 bool warn_wasteliquid;

IMPLEMENT_DYNAMIC(CReabentalarmView, CDialogEx)

CReabentalarmView::CReabentalarmView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CReabentalarmView::IDD, pParent)
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
	

			warn_diluent = systemcfg2.warn_diluent;
			warn_rinse = systemcfg2.warn_rinse;
			warn_hgblyse = systemcfg2.warn_hgb;
			warn_fixlyse = systemcfg2.warn_fix ;
			warn_basolyse = systemcfg2.warn_baso;
			warn_wasteliquid = systemcfg2.warn_waste;

}

CReabentalarmView::~CReabentalarmView()
{
}

void CReabentalarmView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CReabentalarmView, CDialogEx)
	ON_BN_CLICKED(IDC_REGENTSET_OK, &CReabentalarmView::OnBnClickedRegentsetOk)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CReabentalarmView ��Ϣ�������


void CReabentalarmView::OnBnClickedRegentsetOk()
{
	if(BST_CHECKED==((CButton*)GetDlgItem(IDC_REGENTSET_DILUENT))->GetCheck())
		warn_diluent = TRUE;
	else
		warn_diluent = FALSE;
	if(IsDlgButtonChecked(IDC_REGENTSET_RINSE) == BST_CHECKED)
		warn_rinse = TRUE;
	else
		warn_rinse = FALSE;
	if(IsDlgButtonChecked(IDC_REGENTSET_HGBLYSE) == BST_CHECKED)
		warn_hgblyse = TRUE;
	else
		warn_hgblyse = FALSE;
	if(IsDlgButtonChecked(IDC_REGENTSET_FIXLYSE) == BST_CHECKED)
		warn_fixlyse = TRUE;
	else
		warn_fixlyse = FALSE;
	if(IsDlgButtonChecked(IDC_REGENTSET_BASOLYSE) == BST_CHECKED)
		warn_basolyse = TRUE;
	else
		warn_basolyse = FALSE;
	if(IsDlgButtonChecked(IDC_REGENTSET_WASTELIQUID) == BST_CHECKED)
		warn_wasteliquid = TRUE;
	else
		warn_wasteliquid = FALSE;
	systemcfg2.warn_diluent = warn_diluent;
	systemcfg2.warn_rinse = warn_rinse;
	systemcfg2.warn_hgb = warn_hgblyse;
	systemcfg2.warn_fix = warn_fixlyse;
	systemcfg2.warn_baso = warn_basolyse;
	systemcfg2.warn_waste = warn_wasteliquid;
	WriteSystemcfg2File(); 
	MessageBox(L"���óɹ����뷵�أ�", L"OK", MB_OK);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CReabentalarmView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	/*@TG
#3073*/
	CRect   rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));   //����Ϊ��ɫ����
	dc.Rectangle(20, 20, rect.right -20, rect.bottom - 30);
	GetDlgItem(IDC_REGENTSET_DILUENT)->SetFont(&m_Font);
	GetDlgItem(IDC_REGENTSET_RINSE)->SetFont(&m_Font);
	GetDlgItem(IDC_REGENTSET_HGBLYSE)->SetFont(&m_Font);
	GetDlgItem(IDC_REGENTSET_FIXLYSE)->SetFont(&m_Font);
	GetDlgItem(IDC_REGENTSET_BASOLYSE)->SetFont(&m_Font);
	GetDlgItem(IDC_REGENTSET_WASTELIQUID)->SetFont(&m_Font);
	
	        if(systemcfg2.warn_diluent)
			((CButton*)GetDlgItem(IDC_REGENTSET_DILUENT))->SetCheck(true);
			if(systemcfg2.warn_rinse)
				((CButton*)GetDlgItem(IDC_REGENTSET_RINSE))->SetCheck(true);
				//SendMessage(GetDlgItem(IDC_REGENTSET_RINSE),BM_SETCHECK, BST_CHECKED);	
			if(systemcfg2.warn_hgb)
				((CButton*)GetDlgItem(IDC_REGENTSET_HGBLYSE))->SetCheck(true);
				//SendMessage(GetDlgItem(IDC_REGENTSET_HGBLYSE),BM_SETCHECK, BST_CHECKED );	
			if(systemcfg2.warn_fix)
				((CButton*)GetDlgItem(IDC_REGENTSET_FIXLYSE))->SetCheck(true);
				//SendMessage(GetDlgItem(IDC_REGENTSET_FIXLYSE),BM_SETCHECK, BST_CHECKED);	
			if(systemcfg2.warn_baso)
				((CButton*)GetDlgItem(IDC_REGENTSET_BASOLYSE))->SetCheck(true);
				//SendMessage(GetDlgItem(IDC_REGENTSET_BASOLYSE),BM_SETCHECK, BST_CHECKED);	
			if(systemcfg2.warn_waste)
				((CButton*)GetDlgItem(IDC_REGENTSET_WASTELIQUID))->SetCheck(true);
				//SendMessage(GetDlgItem(IDC_REGENTSET_WASTELIQUID),BM_SETCHECK, BST_CHECKED);
		// TODO: �ڴ˴������Ϣ����������
		// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


HBRUSH CReabentalarmView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_REGENTSET_DILUENT:case IDC_REGENTSET_RINSE:case IDC_REGENTSET_HGBLYSE :case IDC_REGENTSET_FIXLYSE:case IDC_REGENTSET_BASOLYSE:case IDC_REGENTSET_WASTELIQUID:

		{
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SelectObject(&m_Font);
		pDC->SetBkColor(RGB(255, 255, 255));//���ֱ���ɫ
		HBRUSH b = CreateSolidBrush(RGB(255, 255, 255));//�ؼ�����ɫ   
		return b;
		}break;
	default :break;
	
	
	}

	//if (pWnd->GetDlgCtrlID()==IDC_REGENTSET_DILUENT)
	//{
	//	pDC->SetTextColor(RGB(0, 0, 0));
	//	pDC->SelectObject(&m_Font);
	//	pDC->SetBkColor(RGB(255, 255, 255));//���ֱ���ɫ
	//	HBRUSH b = CreateSolidBrush(RGB(255, 255, 255));//�ؼ�����ɫ   
	//	return b;
	//}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
