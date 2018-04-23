// QualityTargetValueView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "QualityTargetValueView.h"
#include "afxdialogex.h"
#include "QualityFileExit.h"

// CQualityTargetValueView �Ի���

IMPLEMENT_DYNAMIC(CQualityTargetValueView, CDialogEx)

extern int rc;
qc_edit_data_info qcLjEditData;

CQualityTargetValueView::CQualityTargetValueView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQualityTargetValueView::IDD, pParent)
{
	for (int i = 0; i < 26; i++)
	{
		Qctarget[i] = "";
		TargetLimit[i] = "";
	}

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

CQualityTargetValueView::~CQualityTargetValueView()
{
}

void CQualityTargetValueView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_QUALITY_TARGETVALUE_LIST, m_TargetValueList);
}


BEGIN_MESSAGE_MAP(CQualityTargetValueView, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_CLICK, IDC_QUALITY_TARGETVALUE_LIST, &CQualityTargetValueView::OnNMClickQualityTargetvalueList)
	ON_BN_CLICKED(IDC_QUALITYTARGET_CONFIRM, &CQualityTargetValueView::OnQualitytargetConfirm)
	ON_BN_CLICKED(IDC_RANGE_CONFIRM, &CQualityTargetValueView::OnRangeConfirm)
END_MESSAGE_MAP()


// CQualityTargetValueView ��Ϣ�������
int	 CQualityTargetValueView::item_focused = 0;


void CQualityTargetValueView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
}


BOOL CQualityTargetValueView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CString item_temp;
	switch (Controltype)
	{
	case 0:
		item_temp.Format(L"L-J��ֵ�༭���ļ� %02u��", Controlfile + 1);
		break;
	case 1:
		item_temp.Format(L"X��ֵ�༭���ļ� %02u��", Controlfile + 1);
		break;
	case 2:
		item_temp.Format(L"X-R��ֵ�༭���ļ� %02u��", Controlfile + 1);
		break;
	default:
		break;
	}
	SetDlgItemText(IDC_STATIC0, item_temp);
	GetDlgItem(IDC_STATIC0)->SetFont(&textfont);
	
	haveeditcreate = false;
	QcLjFileExist = 0;
	InitTargetValueList();
	GetQcFile();
	
	
	//if (nRow == 0)
	//	QcLjFileExist = 0;
	//else{
	//	QcLjFileExist = 1;
	//	MessageBox(L"FillForm");
	//	FillForm();
	//}
	

	GetDlgItem(IDC_PROJECT_EDIT)->EnableWindow(false);//��Ŀ��
	GetDlgItem(IDC_PROJECTTARGET_EDIT)->EnableWindow(false);//��ֵ
	GetDlgItem(IDC_PROJECT_EDIT)->SetWindowText(m_TargetValueList.GetItemText(item_focused, 0));
	GetDlgItem(IDC_PROJECTTARGET_EDIT)->SetWindowText(m_TargetValueList.GetItemText(item_focused, 2));

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


HBRUSH CQualityTargetValueView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC0:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	default:
		break;
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

void CQualityTargetValueView::InitTargetValueList()
{
	CRect rect;
	CString table[26] = { "WBC", "LYM%", "NEU%", "MONO%", "EOS%", "BASO", "ALY%", "LIC%", "LYM#", "NEU#", "MONO#", "EOS#", "BASO#", "ALY#",
							"LIC#", "RBC", "HGB", "HCT", "MCV", "MCH", "MCHC", "RDW", "PLT", "MPV", "PDW", "PCT" };
	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_TargetValueList.GetClientRect(&rect);
	m_TargetValueList.SetRowHeigt(20);
	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_TargetValueList.SetExtendedStyle(m_TargetValueList.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);


	// Ϊ�б���ͼ�ؼ��������
	m_TargetValueList.InsertColumn(0, _T("��Ŀ"), LVCFMT_CENTER, rect.Width() * 1 /8, 0);
	m_TargetValueList.InsertColumn(1, _T("����"), LVCFMT_CENTER, rect.Width() * 1 / 4, 1);
	m_TargetValueList.InsertColumn(2, _T("��ֵ"), LVCFMT_CENTER, rect.Width() * 1 / 4, 2);
	m_TargetValueList.InsertColumn(3, _T("����"), LVCFMT_CENTER, rect.Width() * 1 / 4, 3);
	m_TargetValueList.InsertColumn(4, _T("��λ"), LVCFMT_CENTER, rect.Width() * 1 / 8, 4);


	// ���б���ͼ�ؼ��в����б���������б������ı�
	//m_TargetValueList.InsertItem(0, _T("WBC"));
	////m_CoefficientList.InsertItem(0, _T(""));
	//m_TargetValueList.InsertItem(1, _T("ƽ��ֵ"));
	//m_TargetValueList.InsertItem(2, _T("CVֵ"));
	//m_TargetValueList.InsertItem(3, _T("��ǰϵ��"));
	//m_TargetValueList.InsertItem(4, _T("��ϵ��"));
	for (int i = 0; i < 26; i++)
	{
		m_TargetValueList.InsertItem(i,table[i]);
	}

	m_TargetValueList.SetItemText(0, 4, L"10^9/L");
	m_TargetValueList.SetItemText(1, 4, L"%");
	m_TargetValueList.SetItemText(2, 4, L"%");
	m_TargetValueList.SetItemText(3, 4, L"%");
	m_TargetValueList.SetItemText(4, 4, L"%");
	m_TargetValueList.SetItemText(5, 4, L"%");
	m_TargetValueList.SetItemText(6, 4, L"%");
	m_TargetValueList.SetItemText(7, 4, L"%");
	m_TargetValueList.SetItemText(8, 4, L"10^9/L");
	m_TargetValueList.SetItemText(9, 4, L"10^9/L");
	m_TargetValueList.SetItemText(10, 4, L"10^9/L");
	m_TargetValueList.SetItemText(11, 4, L"10^9/L");
	m_TargetValueList.SetItemText(12, 4, L"10^9/L");
	m_TargetValueList.SetItemText(13, 4, L"10^9/L");
	m_TargetValueList.SetItemText(14, 4, L"10^9/L");
	m_TargetValueList.SetItemText(15, 4, L"10^12/L");
	m_TargetValueList.SetItemText(16, 4, L"g/L");
	m_TargetValueList.SetItemText(17, 4, L"%");
	m_TargetValueList.SetItemText(18, 4, L"fL");
	m_TargetValueList.SetItemText(19, 4, L"pg");
	m_TargetValueList.SetItemText(20, 4, L"g/L");
	m_TargetValueList.SetItemText(21, 4, L"%");
	m_TargetValueList.SetItemText(22, 4, L"10^9/L");
	m_TargetValueList.SetItemText(23, 4, L"fL");
	m_TargetValueList.SetItemText(24, 4, L"fL");
	m_TargetValueList.SetItemText(25, 4, L"%");
}

void CQualityTargetValueView::createEdit(NM_LISTVIEW  *pEditCtrl, CEdit *createdit, int &Item, int &SubItem, bool &havecreat)
{
	Item = pEditCtrl->iItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
	SubItem = pEditCtrl->iSubItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
	createdit->Create(ES_AUTOHSCROLL | WS_CHILD | ES_LEFT | ES_WANTRETURN,
		CRect(0, 0, 0, 0), this, IDC_EDIT_CREATEID);//�����༭�����,IDC_EDIT_CREATEIDΪ�ؼ�ID��3000�������¿�ͷ����
	havecreat = true;
	createdit->SetFont(this->GetFont(), FALSE);//��������,����������Ļ�������ֻ��ͻأ�ĸо�
	createdit->SetParent(&m_TargetValueList);//��list control����Ϊ������,���ɵ�Edit������ȷ��λ,���Ҳ����Ҫ
	CRect  EditRect;
	m_TargetValueList.GetSubItemRect(e_Item, e_SubItem, LVIR_LABEL, EditRect);//��ȡ��Ԫ��Ŀռ�λ����Ϣ
	EditRect.SetRect(EditRect.left + 1, EditRect.top + 1, EditRect.left + m_TargetValueList.GetColumnWidth(e_SubItem) - 1, EditRect.bottom - 1);//+1��-1�����ñ༭�����ڵ�ס�б���е�������
	CString strItem = m_TargetValueList.GetItemText(e_Item, e_SubItem);//�����Ӧ��Ԫ���ַ�
	createdit->SetWindowText(strItem);//����Ԫ���ַ���ʾ�ڱ༭����
	createdit->MoveWindow(&EditRect);//���༭��λ�÷�����Ӧ��Ԫ����
	createdit->ShowWindow(SW_SHOW);//��ʾ�༭���ڵ�Ԫ������
	createdit->SetFocus();//����Ϊ���� 
	createdit->SetSel(-1);//���ù�����ı������ֵ����
}

void CQualityTargetValueView::distroyEdit(CListCtrl *list, CEdit* distroyedit, int &Item, int &SubItem)
{
	CString meditdata;
	try{
		
		distroyedit->GetWindowTextW(meditdata);
		
	}
	catch (_com_error &e)
	{
		TRACE("distroyedit->GetWindowTextW�쳣");
	}
	list->SetItemText(Item, SubItem, meditdata);//�����Ӧ��Ԫ���ַ�
	distroyedit->DestroyWindow();//���ٶ����д�����Ҫ�����٣���Ȼ�ᱨ��

}

void CQualityTargetValueView::OnNMClickQualityTargetvalueList(NMHDR *pNMHDR, LRESULT *pResult)//�����ֵ�༭ĳһ��Ŀ����Ӧ����
{
	//UpdateData(true);
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW  *pEditCtrl = (NM_LISTVIEW *)pNMHDR;
	printf("�У�%d���У�%d\n", pEditCtrl->iItem, pEditCtrl->iSubItem);
	item_focused = pEditCtrl->iItem;
	GetDlgItem(IDC_PROJECT_EDIT)->SetWindowText(m_TargetValueList.GetItemText(item_focused, 0));
	GetDlgItem(IDC_PROJECTTARGET_EDIT)->SetWindowText(m_TargetValueList.GetItemText(item_focused, 2));
	//GetDlgItem(IDC_PROJECTTARGET_EDIT)->SetWindowText(m_TargetValueList.GetItemText(item_focused, 1));
	//GetDlgItem(IDC_PROJECTRANGE_EDIT)->SetWindowText(m_TargetValueList.GetItemText(item_focused, 2));

	if (pEditCtrl->iItem == -1)//������ǹ�����
	{
		if (haveeditcreate == true)//���֮ǰ�����˱༭������ٵ�
		{
			distroyEdit(&m_TargetValueList, &m_QualityTargetEdit, e_Item, e_SubItem);//���ٵ�Ԫ��༭�����
			haveeditcreate = false;
		}
	}
	else if ((pEditCtrl->iItem >= 0 && pEditCtrl->iItem <= 25) && (pEditCtrl->iSubItem == 2))//�������ڰ�ֵ��������༭��
	{
		if (haveeditcreate == true)
		{
			if (!(e_Item == pEditCtrl->iItem && e_SubItem == pEditCtrl->iSubItem))//������еĵ�Ԫ����֮ǰ�����õ�
			{
				distroyEdit(&m_TargetValueList, &m_QualityTargetEdit, e_Item, e_SubItem);
				haveeditcreate = false;
				createEdit(pEditCtrl, &m_QualityTargetEdit, e_Item, e_SubItem, haveeditcreate);//�����༭��
			}
			else//���еĵ�Ԫ����֮ǰ�����õ�
			{
				m_QualityTargetEdit.SetFocus();//����Ϊ���� 
			}
		}
		else
		{
			e_Item = pEditCtrl->iItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
			e_SubItem = pEditCtrl->iSubItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
			createEdit(pEditCtrl, &m_QualityTargetEdit, e_Item, e_SubItem, haveeditcreate);//�����༭��
		}
	}
	else
	{
		if (haveeditcreate == true)//���֮ǰ�����˱༭������ٵ�
		{
			distroyEdit(&m_TargetValueList, &m_QualityTargetEdit, e_Item, e_SubItem);
			haveeditcreate = false;
		}
	}
	//POSITION pos = m_TargetValueList.GetFirstSelectedItemPosition();
	//if (pos == NULL)
	//	TRACE("No items were selected!\n");
	//else
	//{
	//	int nItem = m_TargetValueList.GetNextSelectedItem(pos);
	//	TRACE1("Item %d was selected!\n", nItem);
	//	CString selectnum = m_TargetValueLists.GetItemText(nItem, 1);

	//}
	*pResult = 0;
}


//��ҳ���е���Ϣװ����ṹ�壬׼������
//�˺��������Ӷ���Ŀո�ע���޲�
void CQualityTargetValueView::GetQcLimitData()
{
	qcLjEditData.qctype = Controltype + 48;
	qcLjEditData.filenum =Controlfile + 48;
	

	USES_CONVERSION;
	
	strcpy(qcLjEditData.Number, W2A(tempLjNumber));
	strcpy(qcLjEditData.Deadline, W2A(tempLjDeadline));

	strcpy(qcLjEditData.wbctarget.wbc, W2A(m_TargetValueList.GetItemText(0, 2).Trim()));//�ڶ���Ϊ��ֵ

	strcpy(qcLjEditData.wbctarget.lymp, W2A(m_TargetValueList.GetItemText(1, 2).Trim()));
	strcpy(qcLjEditData.wbctarget.neup, W2A(m_TargetValueList.GetItemText(2, 2).Trim()));
	strcpy(qcLjEditData.wbctarget.monop, W2A(m_TargetValueList.GetItemText(3, 2).Trim()));
	strcpy(qcLjEditData.wbctarget.eosp, W2A(m_TargetValueList.GetItemText(4, 2).Trim()));
	strcpy(qcLjEditData.wbctarget.basp, W2A(m_TargetValueList.GetItemText(5, 2).Trim()));
	strcpy(qcLjEditData.wbctarget.alyp, W2A(m_TargetValueList.GetItemText(6, 2).Trim()));
	strcpy(qcLjEditData.wbctarget.licp, W2A(m_TargetValueList.GetItemText(7, 2).Trim()));
	strcpy(qcLjEditData.wbctarget.lym, W2A(m_TargetValueList.GetItemText(8, 2).Trim()));
	strcpy(qcLjEditData.wbctarget.neu, W2A(m_TargetValueList.GetItemText(9, 2).Trim()));
	strcpy(qcLjEditData.wbctarget.mono, W2A(m_TargetValueList.GetItemText(10, 2).Trim()));
	strcpy(qcLjEditData.wbctarget.eos, W2A(m_TargetValueList.GetItemText(11, 2).Trim()));
	strcpy(qcLjEditData.wbctarget.bas, W2A(m_TargetValueList.GetItemText(12, 2).Trim()));
	strcpy(qcLjEditData.wbctarget.aly, W2A(m_TargetValueList.GetItemText(13, 2).Trim()));
	strcpy(qcLjEditData.wbctarget.lic, W2A(m_TargetValueList.GetItemText(14, 2).Trim()));
	strcpy(qcLjEditData.rbctarget.rbc, W2A(m_TargetValueList.GetItemText(15, 2).Trim()));
	strcpy(qcLjEditData.rbctarget.hgb, W2A(m_TargetValueList.GetItemText(16, 2).Trim()));
	strcpy(qcLjEditData.rbctarget.hct, W2A(m_TargetValueList.GetItemText(17, 2).Trim()));
	strcpy(qcLjEditData.rbctarget.mcv, W2A(m_TargetValueList.GetItemText(18, 2).Trim()));
	strcpy(qcLjEditData.rbctarget.mch, W2A(m_TargetValueList.GetItemText(19, 2).Trim()));
	strcpy(qcLjEditData.rbctarget.mchc,W2A(m_TargetValueList.GetItemText(20, 2).Trim()));
	strcpy(qcLjEditData.rbctarget.rdw, W2A(m_TargetValueList.GetItemText(21, 2).Trim()));
	strcpy(qcLjEditData.plttarget.plt, W2A(m_TargetValueList.GetItemText(22, 2).Trim()));
	strcpy(qcLjEditData.plttarget.mpv, W2A(m_TargetValueList.GetItemText(23, 2).Trim()));
	strcpy(qcLjEditData.plttarget.pdw, W2A(m_TargetValueList.GetItemText(24, 2).Trim()));
	strcpy(qcLjEditData.plttarget.pct, W2A(m_TargetValueList.GetItemText(25, 2).Trim()));

	strcpy(qcLjEditData.wbcsd.wbc, W2A(TargetLimit[0].Trim()));
	strcpy(qcLjEditData.wbcsd.lymp, W2A(TargetLimit[1].Trim()));
	strcpy(qcLjEditData.wbcsd.neup, W2A(TargetLimit[2].Trim()));
	strcpy(qcLjEditData.wbcsd.monop, W2A(TargetLimit[3].Trim()));
	strcpy(qcLjEditData.wbcsd.eosp, W2A(TargetLimit[4].Trim()));
	strcpy(qcLjEditData.wbcsd.basp, W2A(TargetLimit[5].Trim()));
	strcpy(qcLjEditData.wbcsd.alyp, W2A(TargetLimit[6].Trim()));
	strcpy(qcLjEditData.wbcsd.licp, W2A(TargetLimit[7].Trim()));
	strcpy(qcLjEditData.wbcsd.lym, W2A(TargetLimit[8].Trim()));
	strcpy(qcLjEditData.wbcsd.neu, W2A(TargetLimit[9].Trim()));
	strcpy(qcLjEditData.wbcsd.mono, W2A(TargetLimit[10].Trim()));
	strcpy(qcLjEditData.wbcsd.eos, W2A(TargetLimit[11].Trim()));
	strcpy(qcLjEditData.wbcsd.bas, W2A(TargetLimit[12].Trim()));
	strcpy(qcLjEditData.wbcsd.aly, W2A(TargetLimit[13].Trim()));
	strcpy(qcLjEditData.wbcsd.lic, W2A(TargetLimit[14].Trim()));
	strcpy(qcLjEditData.rbcsd.rbc, W2A(TargetLimit[15].Trim()));
	strcpy(qcLjEditData.rbcsd.hgb, W2A(TargetLimit[16].Trim()));
	strcpy(qcLjEditData.rbcsd.hct, W2A(TargetLimit[17].Trim()));
	strcpy(qcLjEditData.rbcsd.mcv, W2A(TargetLimit[18].Trim()));
	strcpy(qcLjEditData.rbcsd.mch, W2A(TargetLimit[19].Trim()));
	strcpy(qcLjEditData.rbcsd.mchc, W2A(TargetLimit[20].Trim()));
	strcpy(qcLjEditData.rbcsd.rdw, W2A(TargetLimit[21].Trim()));
	strcpy(qcLjEditData.pltsd.plt, W2A(TargetLimit[22].Trim()));
	strcpy(qcLjEditData.pltsd.mpv, W2A(TargetLimit[23].Trim()));
	strcpy(qcLjEditData.pltsd.pdw, W2A(TargetLimit[24].Trim()));
	strcpy(qcLjEditData.pltsd.pct, W2A(TargetLimit[25].Trim()));
}

//����ҳ���е���Ϣ����ֵȷ������Ӧ������
void CQualityTargetValueView::OnQualitytargetConfirm()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_QUALITY_NUMBER)->GetWindowText(tempLjNumber);
	GetDlgItem(IDC_QUALITY_DEADLINE)->GetWindowText(tempLjDeadline);

	//����У��
	if (tempLjNumber.Trim() == "" || tempLjDeadline.Trim() == "")
	{
		MessageBox(L"��Ϣ����Ϊ��!",L"����!");
		return;
	}
	for (int i = 0; i < 1; i++)//i<26
	{
		if (_wtof(m_TargetValueList.GetItemText(i, 2))<0.00001)
		{
			MessageBox(L"��ֵ����Ϊ0!", L"����!");
			return;
		}
		if (_wtof(TargetLimit[i]) < 0.00001)
		{
			MessageBox(L"ƫ��ֵ����Ϊ0!", L"����!");
			return;
		}
	}
	
	////�������
	//for (int i = 0; i < 1; i++){
	//	_wtof(m_TargetValueList.GetItemText(i, 2));
	//	_wtof(TargetLimit[i]);
	//}
	
	GetQcLimitData();

	//qcLjEditData.qctype=Controltype+48;
	//TRACE("\n@@@@@@@Controltype=%d\n",Controltype);
	//
	//qcLjEditData.filenum = Controlfile + 48;
	//TRACE("\n@@@@@@@Controlfile=%d\n", Controlfile);

	if (QcLjFileExist == 1)
		//CreateQcLjEditFileExistDlg(hDlg, &qcLjEditData, &rc);
	{
		//CDialog  m_QualityFileExitDlg;
		CQualityFileExit m_QualityFileExitDlg;
		m_QualityFileExitDlg.DoModal();
	}
	else//�ļ�δʹ��
		rc = QcLjXXrEditFileAdd(&qcLjEditData);

	if (rc == 0)
	{
		if (systemcfg.language == CHINESE)
			MessageBox(L"����ɹ�",L"��ʾ", MB_OK | MB_ICONINFORMATION);
		//else if (systemcfg.language == ENGLISH)
		//	CreateWarningBoxNonCHDlg(hDlg, "Successfully", "Presentation");
	}
	else if (rc == -5)
	{
		if (systemcfg.language == CHINESE)
			MessageBox(L"����ʧ��",L"��ʾ", MB_OK | MB_ICONINFORMATION);
	/*	else if (systemcfg.language == ENGLISH)
			CreateWarningBoxNonCHDlg(hDlg, "Failed", "Presentation");*/
	}
}

void CQualityTargetValueView::OnRangeConfirm()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString Content;
	
	
	
	USES_CONVERSION;
	GetDlgItem(IDC_PROJECTRANGE_EDIT)->GetWindowText(Content);//��ȡ�ؼ��е����Ʒ�Χ
	if (Content == "")
	{
		MessageBox(L"���Ʒ�Χ����Ϊ��");
		return;
	}
	if (!JudgmentValid(Content))
	{
		return;
	}
	TargetLimit[item_focused] = Content;
	CString targettemp;
	float   TargetLimit1, TargetLimit2;
	CString CTargetLimit1, CTargetLimit2;
	targettemp=m_TargetValueList.GetItemText(item_focused, 2);//��ȡ�ؼ��еİ�ֵ
	TargetLimit1=_wtof(targettemp) - _wtof(Content);//����
	TargetLimit2=_wtof(targettemp) + _wtof(Content);//����
	CTargetLimit1.Format(L"%.2f",TargetLimit1);
	CTargetLimit2.Format(L"%.2f",TargetLimit2);

	//�˴���Ҫ��ƫ��ֵд���Ӧ��
	m_TargetValueList.SetItemText(item_focused, 1, CTargetLimit1);
	m_TargetValueList.SetItemText(item_focused, 3, CTargetLimit2);
}

bool CQualityTargetValueView::JudgmentValid(CString Content)
{
	char temp[10];
	int  temp_len;
	int	 dot_count;
	USES_CONVERSION;
	sprintf(temp, "%s", W2A(Content));
	temp_len = strlen(temp);
	dot_count = 0;
	for (int j = 0; j < temp_len; j++)
	{
		if ((temp[j] >= '0' && temp[j] <= '9') || temp[j] == '.')
		{
			if (temp[j] == '.')
				dot_count++;
			if (dot_count > 1)
			{
				if (systemcfg.language == CHINESE)
					MessageBox(L"С�����������!", L"����!", MB_OK | MB_ICONINFORMATION);
				//else if (systemcfg.language == ENGLISH)
				//	CreateWarningBoxNonCHDlg(HWND_DESKTOP, "Only one dot is permitted!", "Warning!");
				return false;
			}
		}
		else
		{
			if (systemcfg.language == CHINESE)
				MessageBox(L"������Ϸ��ַ�!", L"����!", MB_OK | MB_ICONINFORMATION);
			/*else if (systemcfg.language == ENGLISH)
			CreateWarningBoxNonCHDlg(HWND_DESKTOP, "Please input legal number!", "Warning!");*/
			return false;
		}
	}
	return true;
}

//��ȡ�ʿ��ļ�����־λQcLjFileExist���������Ի��ֵ
//�˴����ݿ������ҳ���߼�/ҵ���߼�������һ���ˣ��������Ӧ�ý����Ƿֿ�
bool CQualityTargetValueView::GetQcFile()
{
	CString filename;
	CString	qctypetemp;
	CString qcFileNumtemp;
	filename.Format(_T("appdata.accdb"));
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	
	_variant_t var;
	CString strTemp;
	int temprow;

	qctypetemp.Format( L"%d",Controltype);
	qcFileNumtemp.Format(L"%d",Controlfile);
	CString inital_target = _T("select * from qceditdata where qctype ='") + qctypetemp +"'and filenum ='" + qcFileNumtemp + "';";

	if (-1 == OpenDataBase(filename, m_pDB, m_pRs)){
		//MessageBox(L"Open Failure!");
		return false;
	}
	ExeSql(m_pDB, m_pRs, inital_target);
	try
	{
		if (!m_pRs->BOF){
			m_pRs->MoveFirst();
			
		}
		else
		{
			TRACE("\n��������Ϊ��!\n");			
			//return FALSE;//���ڴ˴���Ҫ������е�������Ϊ�գ����Բ���ֱ�ӷ���
		}		
		temprow = int(m_pRs->GetRecordCount());
		
		//TRACE("\n###temprow=%d\n",temprow);
		//TRACE("\n###nRow=%d", nRow);
		nRow = temprow;
		if (temprow == 0)//��Ч����Ϊ0���������ֵ
		{
			QcLjFileExist = 0;
			tempLjNumber = "";
			tempLjDeadline = "";
			GetDlgItem(IDC_QUALITY_NUMBER)->SetWindowText(tempLjNumber);
			GetDlgItem(IDC_QUALITY_DEADLINE)->SetWindowText(tempLjDeadline);
			for (int i = 0; i < 26; i++)
			{
				Qctarget[i] = "";
				TargetLimit[i] = "";
				m_TargetValueList.SetItemText(i, 2, Qctarget[i]);
				m_TargetValueList.SetItemText(i, 1, TargetLimit[i]);
				m_TargetValueList.SetItemText(i, 3, TargetLimit[i]);
			}
		}
		else
		{
			QcLjFileExist = 1;
			
			var = m_pRs->GetCollect("number");
			if (var.vt != VT_NULL)
			{
				strTemp = m_pRs->GetCollect("number");
				tempLjNumber = (LPCSTR)_bstr_t(var);
				GetDlgItem(IDC_QUALITY_NUMBER)->SetWindowText(tempLjNumber);
				//��������
			}
			var = m_pRs->GetCollect("deadline");
			if (var.vt != VT_NULL)
			{
				int qctype = m_pRs->GetCollect("deadline");
				tempLjDeadline.Format(L"%d", qctype);
				GetDlgItem(IDC_QUALITY_DEADLINE)->SetWindowText(tempLjDeadline);
				//�����ֹ����
			}
			
			//�����ֵ
			for (int j = 0; j < 26; j++)
			{
				var = m_pRs->GetFields()->GetItem((long)j + 5)->Value;//��ȡ��ǰ��¼�ʿ�26����Ŀ�İ�ֵ
				Qctarget[j] = var;
				m_TargetValueList.SetItemText(j, 2, Qctarget[j]);
			}
			//�������޺�����
			for (int j = 0; j < 26; j++)
			{
				var = m_pRs->GetFields()->GetItem((long)j + 26 + 5)->Value;//��ȡ��ǰ��¼�ʿ�26����Ŀ��ƫ��ֵ
				TargetLimit[j] = var;

				double lowLimit = _wtof(Qctarget[j]) - _wtof(TargetLimit[j]);
				double highimit = _wtof(Qctarget[j]) + _wtof(TargetLimit[j]);
				CString str;
				str.Format(L"%.2lf", lowLimit);
				m_TargetValueList.SetItemText(j, 1, str);
				str.Format(L"%.2lf", highimit);
				m_TargetValueList.SetItemText(j, 3, str);
			}

		}
		CloseDataBase(m_pDB, m_pRs);
		return TRUE;
	}
	catch (_com_error &e)
	{
		TRACE("GetQCFile�쳣");
	}
	return false;

	//if (OpenDataBase(filename, m_pDB, m_pRs) != -1)
	//{
	//	temprow = int(m_pRs->GetRecordCount());
	//	if (temprow == 0)
	//	{
	//		QcLjFileExist = 0;
	//		tempLjNumber="";
	//		tempLjDeadline="";
	//		for (int i = 0; i < 26; i++)
	//		{
	//			Qctarget[26]="";
	//			TargetLimit[26]="";
	//		}
	//	}
	//	else
	//	{
	//		QcLjFileExist = 1;
	//		var = m_pRs->GetCollect("number");
	//		if (var.vt != VT_NULL)
	//		{
	//			int qctype = m_pRs->GetCollect("number");
	//			tempLjNumber.Format(L"%d",qctype);
	//		}
	//		var = m_pRs->GetCollect("deadline");
	//		if (var.vt != VT_NULL)
	//		{
	//			int qctype = m_pRs->GetCollect("deadline");
	//			tempLjDeadline.Format(L"%d", qctype);
	//		}
	//		for (int j = 0; j < 26;j++)
	//		{
	//			var = m_pRs->GetFields()->GetItem((long)j+5)->Value;//��ȡ��ǰ��¼�ʿ�26����Ŀ�İ�ֵ
	//			Qctarget[j] = var;
	//		}
	//		for (int j = 0; j < 26; j++)
	//		{
	//			var = m_pRs->GetFields()->GetItem((long)j +26+ 5)->Value;//��ȡ��ǰ��¼�ʿ�26����Ŀ��ƫ��ֵ
	//			TargetLimit[j]=var;
	//		}
	//	}
	//	CloseDataBase(m_pDB, m_pRs);
	//	return true;
	//}
	//else return false;
	/***************************************************/
	//int rc;
	//unsigned int i;
	//unsigned nRow = 0, nColumn = 0;
	//unsigned int tempRow = 0;
	//static char **dbResult;
	//static char *zErrMsg = NULL;
	//char *zStatement = NULL;
	//char inital_target[] = "select * from qceditdata where qctype = %d and filenum = %d;";
	//if (OpenDataBase(DATABASE_PATH, &db) == -1)
	//	return -1;
	//zStatement = sqlite3_mprintf(inital_target, 1, QcLjFileNum);
	//rc = sqlite3_get_table(db, zStatement, &dbResult, &nRow, &nColumn, &zErrMsg);
	//sqlite3_free(zStatement);
	//zStatement = NULL;
	//CloseDataBase(db);
	//if (SQLITE_OK != rc)
	//{
	//	printf("SQL error: %s---------!\n", zErrMsg);
	//	sqlite3_free_table(dbResult);
	//	return -1;
	//}
	//else
	//{
	//	tempRow = nRow;
	//}
	//if (tempRow == 0)
	//{
	//	QcLjFileExist = 0;
	//	strcpy(tempLjNumber, "");
	//	strcpy(tempLjDeadline, "");
	//	for (i = 0; i < 52; i++)
	//		strcpy(qcLjParam[i], "");
	//}
	//else//����Ӧ�ʿط�ʽ��Ӧ�ļ������ݶ�����
	//{
	//	QcLjFileExist = 1;
	//	strcpy(tempLjNumber, dbResult[nColumn + 2]);
	//	strcpy(tempLjDeadline, dbResult[nColumn + 3]);
	//	for (i = 4; i < 56; i++)
	//		strcpy(qcLjParam[i - 4], dbResult[nColumn + i]);    //nColumn*tempRow+i	
	//}
}

void CQualityTargetValueView::UpdateView()
{
		CString item_temp;
	switch (Controltype)
	{
	case 0:
		item_temp.Format(L"L-J��ֵ�༭���ļ� %02u��", Controlfile + 1);
		break;
	case 1:
		item_temp.Format(L"X��ֵ�༭���ļ� %02u��", Controlfile + 1);
		break;
	case 2:
		item_temp.Format(L"X-R��ֵ�༭���ļ� %02u��", Controlfile + 1);
		break;
	default:
		break;
	}
	SetDlgItemText(IDC_STATIC0, item_temp);
	GetDlgItem(IDC_STATIC0)->SetFont(&textfont);
	GetQcFile();
	
}
	
//int CQualityTargetValueView::GetEditFileCount(int controlType, int fileNum)
//{
//	CString getEditFileCount;
//	CString filename;
//	int rownum = 0;
//	filename.Format(_T("appdata.accdb"));
//	_ConnectionPtr m_pDB;
//	_RecordsetPtr m_pRs;
//	_variant_t var;
//
//	getEditFileCount.Format(L"select * from qceditdata where qctype ='%d' and filenum ='%d';", controlType, fileNum);
//
//	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
//		return -1;
//	ExeSql(m_pDB, m_pRs, getEditFileCount);
//	rownum = int(m_pRs->GetRecordCount());
//
//	try
//	{
//		if (!m_pRs->BOF){
//			m_pRs->MoveFirst();
//		}
//		else
//		{
//			TRACE("��������Ϊ��\n");
//			return -1;
//		}
//		//while (!m_pRs->adoEOF)
//		//{
//		//	for (int i = 0; i < 26; i++)
//		//	{
//		//		var = m_pRs->GetFields()->GetItem(4 + i)->Value;//�������Ǹ�������ֵ��
//		//		if (var.vt != VT_NULL){
//		//			lowerlimit[i] = var;
//		//		}
//		//		var = m_pRs->GetFields()->GetItem(4 + 26 + i)->Value;
//		//		if (var.vt != VT_NULL){
//		//			upperlimit[i] = var;
//		//		}
//		//	}
//		//}
//	}
//	catch (_com_error &e)
//	{
//		TRACE("GetNumDea���������쳣\n");
//	}
//	CloseDataBase(m_pDB, m_pRs);
//	return rownum;
//}