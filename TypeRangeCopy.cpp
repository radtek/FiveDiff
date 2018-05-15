// TypeRangeCopy.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "TypeRangeCopy.h"
#include "afxdialogex.h"
#include "RangeSetView.h"
#include "FilesOperation.h"
// CTypeRangeCopy �Ի���

IMPLEMENT_DYNAMIC(CTypeRangeCopy, CDialogEx)

CTypeRangeCopy::CTypeRangeCopy(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTypeRangeCopy::IDD, pParent)
{
	pasteName[0] = "ͨ��";
	pasteName[1] = "����";
	pasteName[2] = "��Ů";
	pasteName[3] = "��ͯ";
	pasteName[4] = "Ӥ��";
	pasteName[5] = "����";
}

CTypeRangeCopy::~CTypeRangeCopy()
{
}

void CTypeRangeCopy::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COPY_COMBO, m_copyCombo);
}


BEGIN_MESSAGE_MAP(CTypeRangeCopy, CDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CTypeRangeCopy ��Ϣ�������


BOOL CTypeRangeCopy::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetDlgItem(IDC_PASTE_EDIT)->SetWindowTextW(pasteName[ListFocusItem]);
	m_copyCombo.AddString(L"ͨ��");
	m_copyCombo.AddString(L"����");
	m_copyCombo.AddString(L"��Ů");
	m_copyCombo.AddString(L"��ͯ");
	m_copyCombo.AddString(L"Ӥ��");
	m_copyCombo.AddString(L"����");
	m_copyCombo.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


HBRUSH CTypeRangeCopy::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CTypeRangeCopy::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���
	int nItem;
	nItem = m_copyCombo.GetCurSel();
	for (int i = 0; i < 56; i++)
	{
		systemcfg.range.normal[nItem][i] = systemcfg.range.normal[ListFocusItem][i];
	}
	WriteSystemcfgFile();
	CDialogEx::OnOK();
}

void CTypeRangeCopy::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���

	CDialogEx::OnCancel();
}
