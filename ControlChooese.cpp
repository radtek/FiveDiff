// ControlChooese.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "ControlChooese.h"
#include "afxdialogex.h"


// CControlChooese �Ի���

IMPLEMENT_DYNAMIC(CControlChooese, CDialogEx)

CControlChooese::CControlChooese(CWnd* pParent /*=NULL*/): CDialogEx(CControlChooese::IDD, pParent)	, m_ControltypeRadio(0)
{
	VERIFY(textfont.CreateFont(
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

	Controltype = m_ControltypeRadio;
}

CControlChooese::~CControlChooese()
{
}

void CControlChooese::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FILEBUTTON1, m_File1);
	DDX_Control(pDX, IDC_FILEBUTTON2, m_file2);
	DDX_Control(pDX, IDC_FILEBUTTON3, m_file3);
	DDX_Control(pDX, IDC_FILEBUTTON4, m_file4);
	DDX_Control(pDX, IDC_FILEBUTTON5, m_file5);
	DDX_Control(pDX, IDC_FILEBUTTON6, m_file6);
	DDX_Control(pDX, IDC_FILEBUTTON7, m_file7);
	DDX_Control(pDX, IDC_FILEBUTTON8, m_file8);
	DDX_Control(pDX, IDC_FILEBUTTON9, m_file9);
	DDX_Radio(pDX, IDC_LJCONTROLRADIO, m_ControltypeRadio);
}


BEGIN_MESSAGE_MAP(CControlChooese, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_LJCONTROLRADIO, &CControlChooese::OnLjcontrolradio)
	ON_BN_CLICKED(IDC_FILEBUTTON1, &CControlChooese::OnFilebutton1)
	ON_BN_CLICKED(IDC_FILEBUTTON2, &CControlChooese::OnFilebutton2)
	ON_BN_CLICKED(IDC_FILEBUTTON3, &CControlChooese::OnFilebutton3)
	ON_BN_CLICKED(IDC_FILEBUTTON4, &CControlChooese::OnFilebutton4)
	ON_BN_CLICKED(IDC_FILEBUTTON5, &CControlChooese::OnFilebutton5)
	ON_BN_CLICKED(IDC_FILEBUTTON6, &CControlChooese::OnFilebutton6)
	ON_BN_CLICKED(IDC_FILEBUTTON7, &CControlChooese::OnFilebutton7)
	ON_BN_CLICKED(IDC_FILEBUTTON8, &CControlChooese::OnFilebutton8)
	ON_BN_CLICKED(IDC_FILEBUTTON9, &CControlChooese::OnFilebutton9)
END_MESSAGE_MAP()


// CControlChooese ��Ϣ�������


void CControlChooese::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//MessageBox(L"close here!");
	CDialogEx::OnClose();
}


HBRUSH CControlChooese::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_LJCONTROLRADIO:
	case IDC_XCONTROLRADIO:
	case IDC_XRCONTROLRADIO:
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


int CControlChooese::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}


void CControlChooese::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	dc.FillPath();
}

BOOL CControlChooese::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetDlgItem(IDC_LJCONTROLRADIO)->SetFont(&textfont);
	GetDlgItem(IDC_XCONTROLRADIO)->SetFont(&textfont);
	GetDlgItem(IDC_XRCONTROLRADIO)->SetFont(&textfont);
	GetDlgItem(IDC_STATIC1)->SetFont(&textfont);

	Initbutton();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CControlChooese::Initbutton()
{

	m_File1.SetImage(IDB_CONTROLTYPE);
	m_File1.SetWindowText(L"�ļ�1");
	m_File1.m_bRighImage = FALSE;
	m_File1.m_bTopImage = TRUE;
	m_File1.SizeToContent();
	m_File1.Invalidate();

	m_file2.SetImage(IDB_CONTROLTYPE);
	m_file2.SetWindowText(L"�ļ�2");
	m_file2.m_bRighImage = FALSE;
	m_file2.m_bTopImage = TRUE;
	m_file2.SizeToContent();
	m_file2.Invalidate();


	m_file3.SetImage(IDB_CONTROLTYPE);
	m_file3.SetWindowText(L"�ļ�3");
	m_file3.m_bRighImage = FALSE;
	m_file3.m_bTopImage = TRUE;
	m_file3.SizeToContent();
	m_file3.Invalidate();

	m_file4.SetImage(IDB_CONTROLTYPE);
	m_file4.SetWindowText(L"�ļ�4");
	m_file4.m_bRighImage = FALSE;
	m_file4.m_bTopImage = TRUE;
	m_file4.SizeToContent();
	m_file4.Invalidate();

	m_file5.SetImage(IDB_CONTROLTYPE);
	m_file5.SetWindowText(L"�ļ�5");
	m_file5.m_bRighImage = FALSE;
	m_file5.m_bTopImage = TRUE;
	m_file5.SizeToContent();
	m_file5.Invalidate();

	m_file6.SetImage(IDB_CONTROLTYPE);
	m_file6.SetWindowText(L"�ļ�6");
	m_file6.m_bRighImage = FALSE;
	m_file6.m_bTopImage = TRUE;
	m_file6.SizeToContent();
	m_file6.Invalidate();

	m_file7.SetImage(IDB_CONTROLTYPE);
	m_file7.SetWindowText(L"�ļ�7");
	m_file7.m_bRighImage = FALSE;
	m_file7.m_bTopImage = TRUE;
	m_file7.SizeToContent();
	m_file7.Invalidate();

	m_file8.SetImage(IDB_CONTROLTYPE);
	m_file8.SetWindowText(L"�ļ�8");
	m_file8.m_bRighImage = FALSE;
	m_file8.m_bTopImage = TRUE;
	m_file8.SizeToContent();
	m_file8.Invalidate();

	m_file9.SetImage(IDB_CONTROLTYPE);
	m_file9.SetWindowText(L"�ļ�9");
	m_file9.m_bRighImage = FALSE;
	m_file9.m_bTopImage = TRUE;
	m_file9.SizeToContent();
	m_file9.Invalidate();
}

void CControlChooese::OnLjcontrolradio()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	Controltype = m_ControltypeRadio;
}



void CControlChooese::OnFilebutton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	Controlfile = 0;
	CDialog::OnOK();
}


void CControlChooese::OnFilebutton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Controlfile = 1;
	CDialog::OnOK();
}


void CControlChooese::OnFilebutton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Controlfile = 2;
	CDialog::OnOK();
}



void CControlChooese::OnFilebutton4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Controlfile = 3;
	CDialog::OnOK();
}


void CControlChooese::OnFilebutton5()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Controlfile = 4;
	CDialog::OnOK();
}


void CControlChooese::OnFilebutton6()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Controlfile = 5;
	CDialog::OnOK();
}


void CControlChooese::OnFilebutton7()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Controlfile = 6;
	CDialogEx::OnOK();
}


void CControlChooese::OnFilebutton8()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Controlfile = 7;
	CDialog::OnOK();
}


void CControlChooese::OnFilebutton9()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	Controlfile = 8;
	CDialog::OnOK();
}
