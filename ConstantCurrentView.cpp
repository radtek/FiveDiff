// ConstantCurrentView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "ConstantCurrentView.h"
#include "afxdialogex.h"


// CConstantCurrentView �Ի���
	static unsigned char rbc_on_off = 0;		//0��ʾ�رգ�1��ʾ��
	static unsigned char baso_on_off = 0;
	static unsigned char lmne_on_off = 0;
	
IMPLEMENT_DYNAMIC(CConstantCurrentView, CDialogEx)

CConstantCurrentView::CConstantCurrentView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConstantCurrentView::IDD, pParent)
{

}

CConstantCurrentView::~CConstantCurrentView()
{
}

void CConstantCurrentView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CConstantCurrentView, CDialogEx)
	ON_BN_CLICKED(IDC_CONSTANTCURRENT_RBC, &CConstantCurrentView::OnBnClickedConstantcurrentRbc)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CONSTANTCURRENT_BASO, &CConstantCurrentView::OnBnClickedConstantcurrentBaso)
	ON_BN_CLICKED(IDC_CONSTANTCURRENT_LMNE, &CConstantCurrentView::OnBnClickedConstantcurrentLmne)
	ON_BN_CLICKED(IDCANCEL, &CConstantCurrentView::OnBnClickedCancel)
END_MESSAGE_MAP()


// CConstantCurrentView ��Ϣ�������


void CConstantCurrentView::OnBnClickedConstantcurrentRbc()
{
	if(0 == rbc_on_off)
					{
						//RBC ����Դ��
						TRACE("Engineer Maintain:RBC Constant-current Source ON--------------!#\n");
						sdata_cmd[0] = SPI_CMD_RBCCURON;
						PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
						if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			                   MessageBox(L"����Ͳ��ɹ���", L"ERROR", MB_OKCANCEL);
						else
						{
							rbc_on_off = !rbc_on_off;
						  GetDlgItem(IDC_CONSTANTCURRENT_RBC)->SetWindowText(L"RBC����Դ  ��");
						}
					//	if(systemcfg.language == CHINESE)
					//	{
					//		SetDlgItemText(hDlg,IDC_CONSTANTCURRENT_RBC,	"RBC  ����Դ    ��");
					//	}
					//	else if(systemcfg.language == ENGLISH)
					//	{
					//		SetDlgItemText(hDlg,IDC_CONSTANTCURRENT_RBC,"RBC   Constant Current    Close");
					//	}	
					}
					else if(1 == rbc_on_off)
					{
						//RBC ����Դ��
						TRACE("Engineer Maintain:RBC Constant-current Source OFF---------------!#\n");
						sdata_cmd[0] = SPI_CMD_RBCCUROFF;
						PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
						if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			                   MessageBox(L"����Ͳ��ɹ���", L"ERROR", MB_OKCANCEL);
						else
						{
						rbc_on_off = !rbc_on_off;
						 GetDlgItem(IDC_CONSTANTCURRENT_RBC)->SetWindowText(L"RBC����Դ  ��");
						}
						//if(systemcfg.language == CHINESE)
					//	{
					//		SetDlgItemText(hDlg,IDC_CONSTANTCURRENT_RBC,	"RBC  ����Դ   ��");
					//	}
					//	else if(systemcfg.language == ENGLISH)
					//	{
				//			SetDlgItemText(hDlg,IDC_CONSTANTCURRENT_RBC,"RBC   Constant Current    Open");
					//	}	
					}
		
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


HBRUSH CConstantCurrentView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);


	// TODO:  �ڴ˸��� DC ���κ�����
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


void CConstantCurrentView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
			CRect   rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));   //����Ϊ��ɫ����
	dc.Rectangle(30, 20, rect.right-30 , rect.bottom - 30);
	//dc.Rectangle(rect.right/2+10, 20, rect.right-30 , rect.bottom - 70);
		// TODO: �ڴ˴������Ϣ����������
		// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


void CConstantCurrentView::OnBnClickedConstantcurrentBaso()
{
	if(0 == baso_on_off)
					{
						//BASO ����Դ��
						TRACE("Engineer Maintain:BASO Constant-current Source ON--------------!#\n");
						sdata_cmd[0] = SPI_CMD_BASOCURON;
						PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
						if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			                   MessageBox(L"����Ͳ��ɹ���", L"ERROR", MB_OKCANCEL);
						else
						{
						baso_on_off = !baso_on_off;
						 GetDlgItem(IDC_CONSTANTCURRENT_BASO)->SetWindowText(L"BASO����Դ  ��");
						}
						//if(systemcfg.language == CHINESE)
					//	{
					//		SetDlgItemText(hDlg,IDC_CONSTANTCURRENT_BASO,"BASO����Դ   ��");
					//	}
					//	else if(systemcfg.language == ENGLISH)
					//	{
					//		SetDlgItemText(hDlg,IDC_CONSTANTCURRENT_BASO,"BASO Constant Current    Close");
					//	}
					}
					else if(1 == baso_on_off)
					{
						//BASO ����Դ��
						TRACE("Engineer Maintain:BASO Constant-current Source OFF--------------!#\n");
						sdata_cmd[0] = SPI_CMD_BASOCUROFF;
						PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
							if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			                   MessageBox(L"����Ͳ��ɹ���", L"ERROR", MB_OKCANCEL);
							else
							{
								baso_on_off = !baso_on_off;
						 GetDlgItem(IDC_CONSTANTCURRENT_BASO)->SetWindowText(L"BASO����Դ  ��");
							}
						//if(systemcfg.language == CHINESE)
						//{
							//SetDlgItemText(hDlg,IDC_CONSTANTCURRENT_BASO,"BASO����Դ  ��");
						//}
						//else if(systemcfg.language == ENGLISH)
						//{
							//SetDlgItemText(hDlg,IDC_CONSTANTCURRENT_BASO,"BASO Constant Current    Open");
						//}
					}
					
					
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CConstantCurrentView::OnBnClickedConstantcurrentLmne()
{
	if(0 == lmne_on_off)
					{
						//LMNE ����Դ��
						TRACE("Engineer Maintain:LMNE Constant-current Source ON--------------!#\n");
						sdata_cmd[0] = SPI_CMD_LMNECURON;
						PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
						if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			                   MessageBox(L"����Ͳ��ɹ���", L"ERROR", MB_OKCANCEL);
						else
						{
							lmne_on_off = !lmne_on_off;
							 GetDlgItem(IDC_CONSTANTCURRENT_LMNE)->SetWindowText(L"LMNE����Դ  ��");
						}
						/*if(systemcfg.language == CHINESE)
						{
							SetDlgItemText(hDlg,IDC_CONSTANTCURRENT_LMNE,"LMNE����Դ  ��");
						}
						else if(systemcfg.language == ENGLISH)
						{
							SetDlgItemText(hDlg,IDC_CONSTANTCURRENT_LMNE,"LMNE Constant Current    Close");
						}*/
					}
					else if(1 == lmne_on_off)
					{
						//LMNE ����Դ��
						TRACE("Engineer Maintain:LMNE Constant-current Source OFF---------------!#\n");
						sdata_cmd[0] = SPI_CMD_LMNECUROFF;
						PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
						if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			                   MessageBox(L"����Ͳ��ɹ���", L"ERROR", MB_OKCANCEL);
						else
						{
							lmne_on_off = !lmne_on_off;
							 GetDlgItem(IDC_CONSTANTCURRENT_LMNE)->SetWindowText(L"LMNE����Դ  ��");
						}
						/*if(systemcfg.language == CHINESE)
						{
							SetDlgItemText(hDlg,IDC_CONSTANTCURRENT_LMNE,"LMNE����Դ  ��");
						}
						else if(systemcfg.language == ENGLISH)
						{
							SetDlgItemText(hDlg,IDC_CONSTANTCURRENT_LMNE,"LMNE Constant Current    Open");
						}*/
					}
					
					
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CConstantCurrentView::OnBnClickedCancel()
{
	
	if(rbc_on_off != 0 || baso_on_off != 0 || lmne_on_off != 0)
		{
			 MessageBox(L"��رպ���Դ��", L"����", MB_OKCANCEL);
						/*if(systemcfg.language == CHINESE)
							MessageBox(HWND_DESKTOP,"��رպ���Դ!","����!",MB_OK | MB_ICONINFORMATION);	
						else if(systemcfg.language == ENGLISH)
							CreateWarningBoxNonCHDlg(HWND_DESKTOP, "Please Close The Constant Current!", "Warning!");*/
		}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	else
	CDialogEx::OnCancel();
}
