// ResetView.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "ResetView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"
#include "FilesOperation.h"
// CResetView �Ի���

IMPLEMENT_DYNAMIC(CResetView, CDialogEx)

CResetView::CResetView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CResetView::IDD, pParent)
{
	VERIFY(textfont.CreateFont(
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

CResetView::~CResetView()
{
}

void CResetView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RESET_STATIC, m_statictext);
}


BEGIN_MESSAGE_MAP(CResetView, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_DEFAULT_SET, &CResetView::OnSetDefault)
END_MESSAGE_MAP()


// CResetView ��Ϣ�������


void CResetView::OnPaint()
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


BOOL CResetView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CWnd *cWnd = GetDlgItem(IDC_RESET_STATIC);
	cWnd->SetFont(&textfont);
	//cWnd->SetWindowTextW(L"������Ҫ������");
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

HBRUSH CResetView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_RESET_STATIC:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	default:
		break;
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CResetView::OnSetDefault()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	uchar 		lan_temp;		//����ָ�ϵͳĬ�ϲ���ǰ������ѡ��
	lan_temp = systemcfg.language;
	::CopyFile(L".//Config//DefaultSet//systemcfg.dat",L".//Config//systemcfg.dat",false);//false��ʾ���ļ������򸲸�
	ReadSystemcfgFile();
	systemcfg.language = lan_temp;
	
	if (systemcfg.language == CHINESE)
	{
		m_statictext.ShowWindow(SW_HIDE);
		m_statictext.SetWindowText(L"�ɹ��ָ�ϵͳĬ������!");
		m_statictext.ShowWindow(SW_SHOW);
	}
	else if (systemcfg.language == ENGLISH)
	{
		m_statictext.ShowWindow(SW_HIDE);
		m_statictext.SetWindowText(L"Recover Default Settings Success !");
		m_statictext.ShowWindow(SW_SHOW);
	}
}

