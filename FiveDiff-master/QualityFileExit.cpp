// QualityFileExit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "QualityFileExit.h"
#include "afxdialogex.h"
#include "QualityTargetValueView.h"

// CQualityFileExit �Ի���

IMPLEMENT_DYNAMIC(CQualityFileExit, CDialogEx)


int rc;

CQualityFileExit::CQualityFileExit(CWnd* pParent /*=NULL*/ )
	: CDialogEx(CQualityFileExit::IDD, pParent)
{
	//setLjXXrEditData(qcLjXXrEditData);
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
	ON_BN_CLICKED(IDCANCEL, &CQualityFileExit::OnBnClickedCancel)
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
	//setLjXXrEditData(qcEditData);
	QcLjXXrEditFileExistReset(&qcLjXXrEditData);
	rc = 0;
	CDialogEx::OnOK();
}

void CQualityFileExit::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	rc = -5;
	CDialogEx::OnClose();
}


void CQualityFileExit::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	rc = -5;
	
	CDialogEx::OnCancel();
}

void CQualityFileExit::setLjXXrEditData(qc_edit_data_info qcEditData)
{
	qcLjXXrEditData.qctype = Controltype + 48;
	qcLjXXrEditData.filenum = Controlfile + 48;


	//USES_CONVERSION;

	strcpy(qcLjXXrEditData.Number, qcEditData.Number);
	strcpy(qcLjXXrEditData.Deadline, qcEditData.Deadline);

	strcpy(qcLjXXrEditData.wbctarget.wbc, qcEditData.wbctarget.wbc);

	strcpy(qcLjXXrEditData.wbctarget.lymp, qcEditData.wbctarget.lymp);
	strcpy(qcLjXXrEditData.wbctarget.neup, qcEditData.wbctarget.neup);
	strcpy(qcLjXXrEditData.wbctarget.monop, qcEditData.wbctarget.monop);
	strcpy(qcLjXXrEditData.wbctarget.eosp, qcEditData.wbctarget.eosp);
	strcpy(qcLjXXrEditData.wbctarget.basp, qcEditData.wbctarget.basp);
	strcpy(qcLjXXrEditData.wbctarget.alyp, qcEditData.wbctarget.alyp);
	strcpy(qcLjXXrEditData.wbctarget.licp, qcEditData.wbctarget.licp);
	strcpy(qcLjXXrEditData.wbctarget.lym, qcEditData.wbctarget.lym);
	strcpy(qcLjXXrEditData.wbctarget.neu, qcEditData.wbctarget.neu);
	strcpy(qcLjXXrEditData.wbctarget.mono, qcEditData.wbctarget.mono);
	strcpy(qcLjXXrEditData.wbctarget.eos, qcEditData.wbctarget.eos);
	strcpy(qcLjXXrEditData.wbctarget.bas, qcEditData.wbctarget.bas);
	strcpy(qcLjXXrEditData.wbctarget.aly, qcEditData.wbctarget.aly);
	strcpy(qcLjXXrEditData.wbctarget.lic, qcEditData.wbctarget.lic);

	strcpy(qcLjXXrEditData.rbctarget.rbc, qcEditData.rbctarget.rbc);
	strcpy(qcLjXXrEditData.rbctarget.hgb, qcEditData.rbctarget.hgb);
	strcpy(qcLjXXrEditData.rbctarget.hct, qcEditData.rbctarget.hct);
	strcpy(qcLjXXrEditData.rbctarget.mcv, qcEditData.rbctarget.mcv);
	strcpy(qcLjXXrEditData.rbctarget.mch, qcEditData.rbctarget.mch);
	strcpy(qcLjXXrEditData.rbctarget.mchc, qcEditData.rbctarget.mchc);
	strcpy(qcLjXXrEditData.rbctarget.rdw, qcEditData.rbctarget.rdw);
	strcpy(qcLjXXrEditData.plttarget.plt, qcEditData.plttarget.plt);
	strcpy(qcLjXXrEditData.plttarget.mpv, qcEditData.plttarget.mpv);
	strcpy(qcLjXXrEditData.plttarget.pdw, qcEditData.plttarget.pdw);
	strcpy(qcLjXXrEditData.plttarget.pct, qcEditData.plttarget.pct);

	strcpy(qcLjXXrEditData.wbcsd.wbc, qcEditData.wbcsd.wbc);
	strcpy(qcLjXXrEditData.wbcsd.lymp, qcEditData.wbcsd.lymp);
	strcpy(qcLjXXrEditData.wbcsd.neup, qcEditData.wbcsd.neup);
	strcpy(qcLjXXrEditData.wbcsd.monop, qcEditData.wbctarget.neu);
	strcpy(qcLjXXrEditData.wbcsd.eosp, qcEditData.wbctarget.neu);
	strcpy(qcLjXXrEditData.wbcsd.basp, qcEditData.wbctarget.neu);
	strcpy(qcLjXXrEditData.wbcsd.alyp, qcEditData.wbctarget.neu);
	strcpy(qcLjXXrEditData.wbcsd.licp, qcEditData.wbctarget.neu);
	strcpy(qcLjXXrEditData.wbcsd.lym, qcEditData.wbctarget.neu);
	strcpy(qcLjXXrEditData.wbcsd.neu, qcEditData.wbctarget.neu);
	strcpy(qcLjXXrEditData.wbcsd.mono, qcEditData.wbctarget.neu);
	strcpy(qcLjXXrEditData.wbcsd.eos, qcEditData.wbctarget.neu);
	strcpy(qcLjXXrEditData.wbcsd.bas, qcEditData.wbctarget.neu);
	strcpy(qcLjXXrEditData.wbcsd.aly, qcEditData.wbctarget.neu);
	strcpy(qcLjXXrEditData.wbcsd.lic, qcEditData.wbctarget.neu);

	strcpy(qcLjXXrEditData.rbcsd.rbc, qcEditData.rbcsd.rbc);
	strcpy(qcLjXXrEditData.rbcsd.hgb, qcEditData.rbcsd.hgb);
	strcpy(qcLjXXrEditData.rbcsd.hct, qcEditData.rbcsd.hct);
	strcpy(qcLjXXrEditData.rbcsd.mcv, qcEditData.rbcsd.mcv);
	strcpy(qcLjXXrEditData.rbcsd.mch, qcEditData.rbcsd.mch);
	strcpy(qcLjXXrEditData.rbcsd.mchc, qcEditData.rbcsd.mchc);
	strcpy(qcLjXXrEditData.rbcsd.rdw, qcEditData.rbcsd.rdw);
	strcpy(qcLjXXrEditData.pltsd.plt, qcEditData.pltsd.plt);
	strcpy(qcLjXXrEditData.pltsd.mpv, qcEditData.pltsd.mpv);
	strcpy(qcLjXXrEditData.pltsd.pdw, qcEditData.pltsd.pdw);
	strcpy(qcLjXXrEditData.pltsd.pct, qcEditData.pltsd.pct);

}