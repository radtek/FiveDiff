// QualityFileExit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "QualityFileExit.h"
#include "afxdialogex.h"
#include "QualityTargetValueView.h"

// CQualityFileExit �Ի���
extern qc_edit_data_info qcLjEditData;
IMPLEMENT_DYNAMIC(CQualityFileExit, CDialogEx)

int rc;

CQualityFileExit::CQualityFileExit(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQualityFileExit::IDD, pParent)
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
}

CQualityFileExit::~CQualityFileExit()
{
}

void CQualityFileExit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CQualityFileExit, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CQualityFileExit ��Ϣ�������

void CQualityFileExit::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


BOOL CQualityFileExit::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CWnd *cWnd = GetDlgItem(IDC_STATIC);
	cWnd->SetFont(&textfont);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void CQualityFileExit::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���
	QcLjXXrEditFileExistReset(&qcLjEditData);
	rc = 0;
	CDialogEx::OnOK();
}

void CQualityFileExit::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	rc = -5;
	CDialogEx::OnClose();
}
