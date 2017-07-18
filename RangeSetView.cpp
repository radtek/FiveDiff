// RangeSetView.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "RangeSetView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"
#include "FilesOperation.h"
#include "TypeRangeCopy.h"
// CRangeSetView �Ի���

IMPLEMENT_DYNAMIC(CRangeSetView, CDialogEx)

CRangeSetView::CRangeSetView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRangeSetView::IDD, pParent)
{

}

CRangeSetView::~CRangeSetView()
{
}

void CRangeSetView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TYPE_LIST, m_typeList);
}


BEGIN_MESSAGE_MAP(CRangeSetView, CDialogEx)
	ON_WM_PAINT()

	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_CLICK, IDC_TYPE_LIST, &CRangeSetView::OnNMClickTypeList)
	ON_BN_CLICKED(IDC_SET_DEFAULT, &CRangeSetView::OnSetDefault)
	ON_BN_CLICKED(IDC_SAVE, &CRangeSetView::OnSave)
	ON_BN_CLICKED(IDC_SAMPLE_COPY, &CRangeSetView::OnSampleCopy)
END_MESSAGE_MAP()


// CRangeSetView ��Ϣ�������


void CRangeSetView::OnPaint()
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




BOOL CRangeSetView::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitTypeList();

	switch (systemcfg.range.type)
	{
	case RANGE_UNIVERSAL:
		m_typeList.SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED);
		ShowRange(systemcfg.range.type);
		break;
	case RANGE_MAN:
		m_typeList.SetItemState(1, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED);
		ShowRange(systemcfg.range.type);
		break;
	case RANGE_WOMAN:
		m_typeList.SetItemState(2, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED);
		ShowRange(systemcfg.range.type);
		break;
	case RANGE_CHILD:
		m_typeList.SetItemState(3, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED);
		ShowRange(systemcfg.range.type);
		break;
	case RANGE_BABY:
		m_typeList.SetItemState(4, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED);
		ShowRange(systemcfg.range.type);
		break;
	case RANGE_OLD:
		m_typeList.SetItemState(5, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED);
		ShowRange(systemcfg.range.type);
		break;
	default:
		break;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


HBRUSH CRangeSetView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

void CRangeSetView::InitTypeList()
{
	CRect rect;

	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_typeList.GetClientRect(&rect);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_typeList.SetExtendedStyle(m_typeList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_typeList.SetRowHeigt(20);

	m_typeList.DeleteAllItems();//����б�ˢ��

	m_typeList.DeleteColumn(0);

	// ΪWBC�б���ͼ�ؼ��������   
	m_typeList.InsertColumn(0, _T("��������"), LVCFMT_CENTER, rect.Width(), 0);

	// ��WBC�б���ͼ�ؼ��в����б���������б������ı�   
	m_typeList.InsertItem(0, _T("ͨ��"));
	m_typeList.InsertItem(1, _T("����"));
	m_typeList.InsertItem(2, _T("��Ů"));
	m_typeList.InsertItem(3, _T("��ͯ"));
	m_typeList.InsertItem(4, _T("Ӥ��"));
	m_typeList.InsertItem(5, _T("����"));

	return ;

}

void CRangeSetView::ShowRange(int types)
{
	CString buff[56];
	char    temp[6] = {0};
	int type;
	type = types;
	for (int i = 0; i < 56; i++)
	{
		if (i == PLTS || i == PLTS + 28)
			sprintf(temp, "%.0f", systemcfg.range.normal[type][i]);
		else if (i == WBCS || i == MPVS || i == PCTS || i == WBCS + 28 || i == MPVS + 28 || i == PCTS + 28)
			sprintf(temp, "%.2f", systemcfg.range.normal[type][i]);
		else if ((i >= LYMS && i <= RBCS) || (i >= LYMS + 28 && i <= RBCS + 28))
			sprintf(temp, "%.2f", systemcfg.range.normal[type][i]);
		else
			sprintf(temp, "%.1f", systemcfg.range.normal[type][i]);
		buff[i] = temp;
	}
	GetDlgItem(IDC_LRANGE_WBC)->SetWindowTextW(buff[0]);
	GetDlgItem(IDC_LRANGE_LYMP)->SetWindowTextW(buff[1]);
	GetDlgItem(IDC_LRANGE_NEUP)->SetWindowTextW(buff[2]);
	GetDlgItem(IDC_LRANGE_MONOP)->SetWindowTextW(buff[3]);
	GetDlgItem(IDC_LRANGE_EOSP)->SetWindowTextW(buff[4]);
	GetDlgItem(IDC_LRANGE_BASOP)->SetWindowTextW(buff[5]);
	GetDlgItem(IDC_LRANGE_ALYP)->SetWindowTextW(buff[6]);
	GetDlgItem(IDC_LRANGE_LICP)->SetWindowTextW(buff[7]);
	GetDlgItem(IDC_LRANGE_LYM)->SetWindowTextW(buff[8]);
	GetDlgItem(IDC_LRANGE_NEU)->SetWindowTextW(buff[9]);
	GetDlgItem(IDC_LRANGE_MONO)->SetWindowTextW(buff[10]);
	GetDlgItem(IDC_LRANGE_EOS)->SetWindowTextW(buff[11]);
	GetDlgItem(IDC_LRANGE_BASO)->SetWindowTextW(buff[12]);
	GetDlgItem(IDC_LRANGE_ALY)->SetWindowTextW(buff[13]);
	GetDlgItem(IDC_LRANGE_LIC)->SetWindowTextW(buff[14]);
	GetDlgItem(IDC_LRANGE_RBC)->SetWindowTextW(buff[15]);
	GetDlgItem(IDC_LRANGE_HGB)->SetWindowTextW(buff[16]);
	GetDlgItem(IDC_LRANGE_HCT)->SetWindowTextW(buff[17]);
	GetDlgItem(IDC_LRANGE_MCV)->SetWindowTextW(buff[18]);
	GetDlgItem(IDC_LRANGE_MCH)->SetWindowTextW(buff[19]);
	GetDlgItem(IDC_LRANGE_MCHC)->SetWindowTextW(buff[20]);
	GetDlgItem(IDC_LRANGE_RDWCV)->SetWindowTextW(buff[21]);
	GetDlgItem(IDC_LRANGE_RDWSD)->SetWindowTextW(buff[22]);
	GetDlgItem(IDC_LRANGE_PLT)->SetWindowTextW(buff[23]);
	GetDlgItem(IDC_LRANGE_MPV)->SetWindowTextW(buff[24]);
	GetDlgItem(IDC_LRANGE_PDW)->SetWindowTextW(buff[25]);
	GetDlgItem(IDC_LRANGE_PCT)->SetWindowTextW(buff[26]);
	GetDlgItem(IDC_LRANGE_PLCR)->SetWindowTextW(buff[27]);

	GetDlgItem(IDC_HRANGE_WBC)->SetWindowTextW(buff[28]);
	GetDlgItem(IDC_HRANGE_LYMP)->SetWindowTextW(buff[29]);
	GetDlgItem(IDC_HRANGE_NEUP)->SetWindowTextW(buff[30]);
	GetDlgItem(IDC_HRANGE_MONOP)->SetWindowTextW(buff[31]);
	GetDlgItem(IDC_HRANGE_EOSP)->SetWindowTextW(buff[32]);
	GetDlgItem(IDC_HRANGE_BASOP)->SetWindowTextW(buff[33]);
	GetDlgItem(IDC_HRANGE_ALYP)->SetWindowTextW(buff[34]);
	GetDlgItem(IDC_HRANGE_LICP)->SetWindowTextW(buff[35]);
	GetDlgItem(IDC_HRANGE_LYM)->SetWindowTextW(buff[36]);
	GetDlgItem(IDC_HRANGE_NEU)->SetWindowTextW(buff[37]);
	GetDlgItem(IDC_HRANGE_MONO)->SetWindowTextW(buff[38]);
	GetDlgItem(IDC_HRANGE_EOS)->SetWindowTextW(buff[39]);
	GetDlgItem(IDC_HRANGE_BASO)->SetWindowTextW(buff[40]);
	GetDlgItem(IDC_HRANGE_ALY)->SetWindowTextW(buff[41]);
	GetDlgItem(IDC_HRANGE_LIC)->SetWindowTextW(buff[42]);
	GetDlgItem(IDC_HRANGE_RBC)->SetWindowTextW(buff[43]);
	GetDlgItem(IDC_HRANGE_HGB)->SetWindowTextW(buff[44]);
	GetDlgItem(IDC_HRANGE_HCT)->SetWindowTextW(buff[45]);
	GetDlgItem(IDC_HRANGE_MCV)->SetWindowTextW(buff[46]);
	GetDlgItem(IDC_HRANGE_MCH)->SetWindowTextW(buff[47]);
	GetDlgItem(IDC_HRANGE_MCHC)->SetWindowTextW(buff[48]);
	GetDlgItem(IDC_HRANGE_RDWCV)->SetWindowTextW(buff[49]);
	GetDlgItem(IDC_HRANGE_RDWSD)->SetWindowTextW(buff[50]);
	GetDlgItem(IDC_HRANGE_PLT)->SetWindowTextW(buff[51]);
	GetDlgItem(IDC_HRANGE_MPV)->SetWindowTextW(buff[52]);
	GetDlgItem(IDC_HRANGE_PDW)->SetWindowTextW(buff[53]);
	GetDlgItem(IDC_HRANGE_PCT)->SetWindowTextW(buff[54]);
	GetDlgItem(IDC_HRANGE_PLCR)->SetWindowTextW(buff[55]);
}

void CRangeSetView::SaveRange(int types)
{
	unsigned int i, j;
	//char buff[6] = { 0 };
	CString buff[56];
	char temp[6] = {0};
	char temp_high[6] = { 0 };
	char temp_low[6] = { 0 };
	unsigned char temp_len = 0;
	unsigned char dot_count = 0;

	GetDlgItem(IDC_LRANGE_WBC)->GetWindowText(buff[0]);
	GetDlgItem(IDC_LRANGE_LYMP)->GetWindowText(buff[1]);
	GetDlgItem(IDC_LRANGE_NEUP)->GetWindowText(buff[2]);
	GetDlgItem(IDC_LRANGE_MONOP)->GetWindowText(buff[3]);
	GetDlgItem(IDC_LRANGE_EOSP)->GetWindowText(buff[4]);
	GetDlgItem(IDC_LRANGE_BASOP)->GetWindowText(buff[5]);
	GetDlgItem(IDC_LRANGE_ALYP)->GetWindowText(buff[6]);
	GetDlgItem(IDC_LRANGE_LICP)->GetWindowText(buff[7]);
	GetDlgItem(IDC_LRANGE_LYM)->GetWindowText(buff[8]);
	GetDlgItem(IDC_LRANGE_NEU)->GetWindowText(buff[9]);
	GetDlgItem(IDC_LRANGE_MONO)->GetWindowText(buff[10]);
	GetDlgItem(IDC_LRANGE_EOS)->GetWindowText(buff[11]);
	GetDlgItem(IDC_LRANGE_BASO)->GetWindowText(buff[12]);
	GetDlgItem(IDC_LRANGE_ALY)->GetWindowText(buff[13]);
	GetDlgItem(IDC_LRANGE_LIC)->GetWindowText(buff[14]);
	GetDlgItem(IDC_LRANGE_RBC)->GetWindowText(buff[15]);
	GetDlgItem(IDC_LRANGE_HGB)->GetWindowText(buff[16]);
	GetDlgItem(IDC_LRANGE_HCT)->GetWindowText(buff[17]);
	GetDlgItem(IDC_LRANGE_MCV)->GetWindowText(buff[18]);
	GetDlgItem(IDC_LRANGE_MCH)->GetWindowText(buff[19]);
	GetDlgItem(IDC_LRANGE_MCHC)->GetWindowText(buff[20]);
	GetDlgItem(IDC_LRANGE_RDWCV)->GetWindowText(buff[21]);
	GetDlgItem(IDC_LRANGE_RDWSD)->GetWindowText(buff[22]);
	GetDlgItem(IDC_LRANGE_PLT)->GetWindowText(buff[23]);
	GetDlgItem(IDC_LRANGE_MPV)->GetWindowText(buff[24]);
	GetDlgItem(IDC_LRANGE_PDW)->GetWindowText(buff[25]);
	GetDlgItem(IDC_LRANGE_PCT)->GetWindowText(buff[26]);
	GetDlgItem(IDC_LRANGE_PLCR)->GetWindowText(buff[27]);

	GetDlgItem(IDC_HRANGE_WBC)->GetWindowText(buff[28]);
	GetDlgItem(IDC_HRANGE_LYMP)->GetWindowText(buff[29]);
	GetDlgItem(IDC_HRANGE_NEUP)->GetWindowText(buff[30]);
	GetDlgItem(IDC_HRANGE_MONOP)->GetWindowText(buff[31]);
	GetDlgItem(IDC_HRANGE_EOSP)->GetWindowText(buff[32]);
	GetDlgItem(IDC_HRANGE_BASOP)->GetWindowText(buff[33]);
	GetDlgItem(IDC_HRANGE_ALYP)->GetWindowText(buff[34]);
	GetDlgItem(IDC_HRANGE_LICP)->GetWindowText(buff[35]);
	GetDlgItem(IDC_HRANGE_LYM)->GetWindowText(buff[36]);
	GetDlgItem(IDC_HRANGE_NEU)->GetWindowText(buff[37]);
	GetDlgItem(IDC_HRANGE_MONO)->GetWindowText(buff[38]);
	GetDlgItem(IDC_HRANGE_EOS)->GetWindowText(buff[39]);
	GetDlgItem(IDC_HRANGE_BASO)->GetWindowText(buff[40]);
	GetDlgItem(IDC_HRANGE_ALY)->GetWindowText(buff[41]);
	GetDlgItem(IDC_HRANGE_LIC)->GetWindowText(buff[42]);
	GetDlgItem(IDC_HRANGE_RBC)->GetWindowText(buff[43]);
	GetDlgItem(IDC_HRANGE_HGB)->GetWindowText(buff[44]);
	GetDlgItem(IDC_HRANGE_HCT)->GetWindowText(buff[45]);
	GetDlgItem(IDC_HRANGE_MCV)->GetWindowText(buff[46]);
	GetDlgItem(IDC_HRANGE_MCH)->GetWindowText(buff[47]);
	GetDlgItem(IDC_HRANGE_MCHC)->GetWindowText(buff[48]);
	GetDlgItem(IDC_HRANGE_RDWCV)->GetWindowText(buff[49]);
	GetDlgItem(IDC_HRANGE_RDWSD)->GetWindowText(buff[50]);
	GetDlgItem(IDC_HRANGE_PLT)->GetWindowText(buff[51]);
	GetDlgItem(IDC_HRANGE_MPV)->GetWindowText(buff[52]);
	GetDlgItem(IDC_HRANGE_PDW)->GetWindowText(buff[53]);
	GetDlgItem(IDC_HRANGE_PCT)->GetWindowText(buff[54]);
	GetDlgItem(IDC_HRANGE_PLCR)->GetWindowText(buff[55]);
	USES_CONVERSION;
	for (i = 0; i < 56; i++)
	{
		sprintf(temp,"%s", W2A(buff[i]));
		temp_len = strlen(temp);
		dot_count = 0;
		for (j = 0; j < temp_len; j++)
		{
			if ((temp[j] >= '0' && temp[j] <= '9') || temp[j] == '.')
			{
				if (temp[j] == '.')
					dot_count++;
				if (dot_count > 1)
				{
					if (systemcfg.language == CHINESE)
						MessageBox(L"С�����������!",L"����!", MB_OK | MB_ICONINFORMATION);
					//else if (systemcfg.language == ENGLISH)
					//	CreateWarningBoxNonCHDlg(HWND_DESKTOP, "Only one dot is permitted!", "Warning!");
					return;
				}
			}
			else
			{
				if (systemcfg.language == CHINESE)
					MessageBox(L"������Ϸ��ַ�!",L"����!", MB_OK | MB_ICONINFORMATION);
				/*else if (systemcfg.language == ENGLISH)
					CreateWarningBoxNonCHDlg(HWND_DESKTOP, "Please input legal number!", "Warning!");*/
				return;
			}
		}
	}

	for (i = 0; i < 28; i++)
	{

		if (_tstof(buff[i]) >= _tstof(buff[i + 28]))
		{
			if (systemcfg.language == CHINESE)
				MessageBox(L"���뷶ΧҪ����:����<����!",L"����!", MB_OK | MB_ICONINFORMATION);
			/*else if (systemcfg.language == ENGLISH)
				CreateWarningBoxNonCHDlg(HWND_DESKTOP, "Lower limit must be lower than Higher limit!", "Warning!");*/
			return;
		}
	}
	for (i = 0; i < 56; i++)
	{
		systemcfg.range.normal[types][i] = _tstof(buff[i]);
	}
	WriteSystemcfgFile();
	MessageBox(L"�޸ĳɹ�");
}

void CRangeSetView::OnNMClickTypeList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	POSITION pos = m_typeList.GetFirstSelectedItemPosition();

	if (pos == NULL)
	{
		TRACE("No items were selected!\n");
		GetDlgItem(IDC_SAMPLE_COPY)->EnableWindow(FALSE);
	}
	
	else
	{
		int nItem = m_typeList.GetNextSelectedItem(pos);
		TRACE1("Item %d was selected!\n", nItem);
		ShowRange(nItem);
		GetDlgItem(IDC_SAMPLE_COPY)->EnableWindow(TRUE);
	}
}


void CRangeSetView::OnSetDefault()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	POSITION pos = m_typeList.GetFirstSelectedItemPosition();

	if (pos == NULL)
		TRACE("No items were selected!\n");
	else
	{
		int nItem = m_typeList.GetNextSelectedItem(pos);
		TRACE1("Item %d was selected!\n", nItem);
		systemcfg.range.type = nItem;
		MessageBox(L"����Ĭ���������óɹ�");
	}
}


void CRangeSetView::OnSave()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int nItem = 0;

	POSITION pos = m_typeList.GetFirstSelectedItemPosition();

	if (pos == NULL)
		TRACE("No items were selected!\n");
	else
	{
		nItem = m_typeList.GetNextSelectedItem(pos);
		TRACE1("Item %d was selected!\n", nItem);
	}
	SaveRange(nItem);

}


void CRangeSetView::OnSampleCopy()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	POSITION pos = m_typeList.GetFirstSelectedItemPosition();

	if (pos == NULL)
		TRACE("No items were selected!\n");
	else
	{
		ListFocusItem = m_typeList.GetNextSelectedItem(pos);
		TRACE1("Item %d was selected!\n", ListFocusItem);
	}
	CTypeRangeCopy m_rangeCopy;
	if (!m_rangeCopy.DoModal())
	{
		MessageBox(L"���ƴ�������ʧ��");
	}
}
