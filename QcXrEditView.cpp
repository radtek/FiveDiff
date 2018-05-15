// QcXrEditView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "QcXrEditView.h"
#include "afxdialogex.h"
#include "QualityFileExit.h"


// CQcXrEditView �Ի���

IMPLEMENT_DYNAMIC(CQcXrEditView, CDialogEx)

qc_edit_data_info qcXrEditData;
extern int rc;

CQcXrEditView::CQcXrEditView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQcXrEditView::IDD, pParent)
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

CQcXrEditView::~CQcXrEditView()
{
}

void CQcXrEditView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CQcXrEditView, CDialogEx)
	ON_BN_CLICKED(IDC_QC_XR_EDIT_ENTER, &CQcXrEditView::OnBnClickedQcXrEditEnter)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

BOOL CQcXrEditView::OnInitDialog()
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
	SetDlgItemText(IDC_QC_XR_EDIT_STATIC0, item_temp);
	GetDlgItem(IDC_QC_XR_EDIT_STATIC0)->SetFont(&textfont);
	getQcXrFile(true);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


// CQcXrEditView ��Ϣ�������
void CQcXrEditView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
}

HBRUSH CQcXrEditView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

bool CQcXrEditView::getQcXrFile(bool loadData){
	CString filename;
	CString	qctypetemp;
	CString qcFileNumtemp;
	filename.Format(_T("appdata.accdb"));
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;

	_variant_t var;
	CString strTemp;
	int tempRow;

	qctypetemp.Format(L"%d", Controltype);
	qcFileNumtemp.Format(L"%d", Controlfile);
	CString inital_target = _T("select * from qceditdata where qctype ='") + qctypetemp + "'and filenum ='" + qcFileNumtemp + "';";

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
		tempRow = int(m_pRs->GetRecordCount());

		if (tempRow == 0)
		{
			QcXrFileExist = 0;
			tempXrNumber.Format(L"");
			tempXrDeadline.Format(L"");
		}
		else//����Ӧ�ʿط�ʽ��Ӧ�ļ������ݶ�����
		{
			if (loadData == true){
				QcXrFileExist = 1;
				var = m_pRs->GetCollect("number");
				if (var.vt != VT_NULL)
				{
					strTemp = m_pRs->GetCollect("number");
					tempXrNumber = (LPCSTR)_bstr_t(var);
					GetDlgItem(IDC_QC_XR_EDIT_NUMBER)->SetWindowText(tempXrNumber);
					//��������
				}

				var = m_pRs->GetCollect("deadline");
				if (var.vt != VT_NULL)
				{
					strTemp = m_pRs->GetCollect("deadline");
					tempXrDeadline = (LPCSTR)_bstr_t(var);
					GetDlgItem(IDC_QC_XR_EDIT_DEADLINE)->SetWindowText(tempXrDeadline);
					//��������
				}
			}
			else{
				QcXrFileExist = 1;
			}
		}
		//if (temprow == 0)//��Ч����Ϊ0���������ֵ
		//{
		//	QcLjFileExist = 0;
		//	number = "";
		//	deadline = "";
		//	GetDlgItem(IDC_QC_XR_EDIT_NUMBER)->SetWindowText(number);
		//	GetDlgItem(IDC_QC_XR_EDIT_DEADLINE)->SetWindowText(deadline);
		//	for (int i = 0; i < 26; i++)
		//	{
		//		Qctarget[i] = "";
		//		TargetLimit[i] = "";
		//		m_ListList.SetItemText(i, 2, Qctarget[i]);
		//		m_ListList.SetItemText(i, 1, TargetLimit[i]);
		//		m_ListList.SetItemText(i, 3, TargetLimit[i]);
		//	}
		//}
		//else
		//{
		//	QcLjFileExist = 1;
		//	var = m_pRs->GetCollect("number");
		//	if (var.vt != VT_NULL)
		//	{
		//		strTemp = m_pRs->GetCollect("number");
		//		number = (LPCSTR)_bstr_t(var);
		//		GetDlgItem(IDC_QC_X_LIST_NUMBER)->SetWindowText(number);
		//		//��������
		//	}
		//	var = m_pRs->GetCollect("deadline");
		//	if (var.vt != VT_NULL)
		//	{
		//		int qctype = m_pRs->GetCollect("deadline");
		//		deadline.Format(L"%d", qctype);
		//		GetDlgItem(IDC_QC_X_LIST_DEADLINE)->SetWindowText(deadline);
		//		//�����ֹ����
		//	}
		CloseDataBase(m_pDB, m_pRs);
		return true;
	}
	catch (_com_error &e)
	{
		TRACE("GetQCFile�쳣");
	}
	return false;
}

void CQcXrEditView::setQcXrEditData()
{
	qcXrEditData.qctype = Controltype + 48;
	qcXrEditData.filenum = Controlfile + 48;

	USES_CONVERSION;
	
	strcpy(qcXrEditData.Number, W2A(tempXrNumber.Trim()));
	strcpy(qcXrEditData.Deadline, W2A(tempXrDeadline.Trim()));
	//û�а�ֵ��ƫ���ޣ��������ֻ�����漸������
}

afx_msg void CQcXrEditView::OnBnClickedQcXrEditEnter()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CString tempXrNumber, tempXrDeadline;
	getQcXrFile(false);
	GetDlgItem(IDC_QC_XR_EDIT_NUMBER)->GetWindowText(tempXrNumber);
	GetDlgItem(IDC_QC_XR_EDIT_DEADLINE)->GetWindowText(tempXrDeadline);

	if (tempXrNumber.Trim()=="" || tempXrDeadline.Trim()=="")
	{
		
		MessageBox( L"��Ϣ����Ϊ��!");
		
		return ;
	}
	
	setQcXrEditData();
	if (QcXrFileExist == 1)
	{//CreateQcXEditFileExistDlg(hDlg, &qcXrEditData, &rc);      //�������͵���ʾ��һ��������XEdit�е�
		CQualityFileExit m_QualityFileExitDlg;
		m_QualityFileExitDlg.setLjXXrEditData(qcXrEditData);
		m_QualityFileExitDlg.DoModal();
	}
		
	else//�ļ�δʹ��
	{//rc = QcLjXXrEditFileAdd(&qcXrEditData);
		rc = QcLjXXrEditFileAdd(&qcXrEditData);

	}
		

	if (rc == 0)
	{
		if (systemcfg.language == CHINESE)
			MessageBox(L"����ɹ�", L"��ʾ", MB_OK | MB_ICONINFORMATION);
		
	}
	else if (rc != -5)
	{
		if (systemcfg.language == CHINESE)
			MessageBox(L"����ʧ��", L"��ʾ", MB_OK | MB_ICONINFORMATION);
	}

}







