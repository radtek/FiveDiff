// ConcentratecleanView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "ConcentratecleanView.h"
#include "FilesOperation.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CConcentratecleanView �Ի���
static unsigned char ConCleanStep;
uchar Concentratedmode;
extern sMaintain m_sMaintain;



IMPLEMENT_DYNAMIC(CConcentratecleanView, CDialogEx)

CConcentratecleanView::CConcentratecleanView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConcentratecleanView::IDD, pParent)
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
	ConCleanStep = 0;
	Concentratedmode = 0;
}

CConcentratecleanView::~CConcentratecleanView()
{
}

void CConcentratecleanView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CConcentratecleanView, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_ConcentratedClean_OK1, &CConcentratecleanView::OnBnClickedConcentratedcleanOk1)
	ON_BN_CLICKED(IDC_ConcentratedClean_OK2, &CConcentratecleanView::OnBnClickedConcentratedcleanOk2)
	ON_BN_CLICKED(IDC_ConcentratedClean_ESC, &CConcentratecleanView::OnBnClickedConcentratedcleanEsc)
	ON_WM_TIMER()
	ON_MESSAGE(WM_ACKSPI, &CConcentratecleanView::OnAckspi)
END_MESSAGE_MAP()


// CConcentratecleanView ��Ϣ�������





HBRUSH CConcentratecleanView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SelectObject(&m_Font);
		pDC->SetBkColor(RGB(255, 255, 255));//���ֱ���ɫ
		HBRUSH b = CreateSolidBrush(RGB(255,255, 255));//�ؼ�����ɫ   
		return b;
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CConcentratecleanView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect   rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));   //����Ϊ��ɫ����
	dc.Rectangle(20, 20, rect.right - 20, rect.bottom - 20);

}


void CConcentratecleanView::OnBnClickedConcentratedcleanOk1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	if (0 == ConCleanStep)
	{
		//ConcentratedCleaning_1(hDlg, " ");
		//fprintf(stderr, "................CONCENTRATEDCLEAN STEP 1........................ \n");
		//PC_GPIOCMD(EN_RED);
		char * Mess = "";
		TRACE(Mess);
		key_status = FALSE;
		DSP_status = Busy;
		sdata_cmd[0] = SPI_CMD_CONCENTRATE_CLEAN1;
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			MessageBox(L"����Ͳ��ɹ���", L"ERROR", MB_OKCANCEL);
		else{
			CString str = "����ִ�е�һ��";
			GetDlgItem(IDC_ConcentratedClean_Mess)->SetWindowText(str);
			SetTimer(POLLTIME, SPI_POLL_TIME1000, 0);
			GetDlgItem(IDC_ConcentratedClean_OK1)->EnableWindow(FALSE);
			GetDlgItem(IDC_ConcentratedClean_OK2)->EnableWindow(FALSE);
			GetDlgItem(IDC_ConcentratedClean_ESC)->EnableWindow(FALSE);
		}
  }

}
void CConcentratecleanView::OnBnClickedConcentratedcleanOk2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CString str = "����ִ�еڶ���";
	
	//CString str = "����ִ�е�����";
	if (0 == ConCleanStep)
		GetDlgItem(IDC_ConcentratedClean_Mess)->SetWindowText(L"���Ƚ��е�һ��");
	if (1 == ConCleanStep)
	{
		
		//int	* testflag = (int*)GetWindowAdditionalData(hDlg);
		//*testflag = 0;
		//fprintf(stderr, "................CONCENTRATEDCLEAN STEP 2..........................\n");

		//ConcentratedCleaning_2(hDlg, " ");
		//fprintf(stderr, "................CONCENTRATEDCLEAN STEP 3.......................... \n");
		char * Mess = "";
		TRACE(Mess);
		key_status = FALSE;
		DSP_status = Busy;
		sdata_cmd[0] = SPI_CMD_CONCENTRATE_CLEAN2;
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			MessageBox(L"����Ͳ��ɹ���", L"ERROR", MB_OKCANCEL);
		else{
			GetDlgItem(IDC_ConcentratedClean_Mess)->SetWindowText(L"����ִ�еڶ���");
			GetDlgItem(IDC_ConcentratedClean_Mess)->SetWindowText(L"����ִ�е�����");
			SetTimer(POLLTIME, SPI_POLL_TIME1000, 0);
			GetDlgItem(IDC_ConcentratedClean_OK1)->EnableWindow(FALSE);
			GetDlgItem(IDC_ConcentratedClean_OK2)->EnableWindow(FALSE);
			GetDlgItem(IDC_ConcentratedClean_ESC)->EnableWindow(FALSE);
		}

	}
	
}


void CConcentratecleanView::OnBnClickedConcentratedcleanEsc()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CConcentratecleanView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case POLLTIME:
		//DEBUG_PRINT1("MSG_TIMER:POLLTIME is due -------------#\n");
		sdata_cmd[0] = SPI_CMD_REQDSP_STATUS;
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		PC_RECEIVE_FRAME(rdata_state, SPI_TYPE_STATE);
		SendMessage(WM_ACKSPI, rdata_state[0], 0);
		break;
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


afx_msg LRESULT CConcentratecleanView::OnAckspi(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case SPI_STATE_INFO_END:
		//ARM_GPIOCMD(EN_GREEN);
		KillTimer(POLLTIME);
		DSP_status = Free;
		ConCleanStep++;
		if (1 == ConCleanStep)
		{
			if (systemcfg.language == CHINESE)
			{
				CString str1 = "����ÿ�����м�3mlȥ����Һ,��ִ�еڶ���";
				SetDlgItemText(IDC_ConcentratedClean_Mess,str1 );
			}
				
			else if (systemcfg.language == ENGLISH)
				SetDlgItemText(IDC_ConcentratedClean_Mess, L"add 3ml protein solution to each cup, and excute the action of concentrated cleaning step 2");
			GetDlgItem(IDC_ConcentratedClean_OK1)->EnableWindow(TRUE);
			GetDlgItem(IDC_ConcentratedClean_OK2)->EnableWindow(TRUE);
			GetDlgItem(IDC_ConcentratedClean_ESC)->EnableWindow(TRUE);
			key_status = true;
		}
		else if (2 == ConCleanStep)
		{
			//fprintf(stderr, "................CONCENTRATEDmode=%d....................... \n", Concentratedmode);
			if (Concentratedmode == 0)
			{
			//	fprintf(stderr, "................CONCENTRATEDCLEAN STEP 5........................ \n");
				if (systemcfg.language == CHINESE)
					SetDlgItemText( IDC_ConcentratedClean_Mess, L"Ũ����ϴ���");
				else if (systemcfg.language == ENGLISH)
					SetDlgItemText(IDC_ConcentratedClean_Mess,L"Concentrated Cleaning Done");
				ConCleanStep = 0;
				GetDlgItem(IDC_ConcentratedClean_OK1)->EnableWindow(TRUE);
				GetDlgItem(IDC_ConcentratedClean_OK2)->EnableWindow(TRUE);
				GetDlgItem(IDC_ConcentratedClean_ESC)->EnableWindow(TRUE);
				key_status = TRUE;
			}
			else if (Concentratedmode == 1)
			{
				//fprintf(stderr, "................CONCENTRATEDCLEAN STEP 6........................ \n");
				ShowCloseMess();
				m_sMaintain.m_bIs2ndFriday = FALSE;
			//	SaveMaintenanceParas(&m_sMaintain);
				WriteMaintainFile();
			}
		}
		break;
	default:
		break;
	}
	return 0;
}


void CConcentratecleanView::ShowCloseMess()
{

		if (systemcfg.language == CHINESE)
			SetDlgItemText( IDC_ConcentratedClean_Mess, L"Ũ����ϴ��ɣ���رյ�Դ��ллʹ��");
		else if (systemcfg.language == ENGLISH)
			SetDlgItemText(IDC_ConcentratedClean_Mess, L"Concentrated Cleaning Done��Please power off, thanks for using");

		if (m_sMaintain.m_bIs2ndFriday)
		{
			//��ťʧ��Ч��
			//SetWindowBkColor(GetDlgItem(hDlg, IDC_ConcentratedClean_OK1), PIXEL_darkgray);
			//SetWindowBkColor(GetDlgItem(hDlg, IDC_ConcentratedClean_OK2), PIXEL_darkgray);
			//SetWindowBkColor(GetDlgItem(hDlg, IDC_ConcentratedClean_ESC), PIXEL_darkgray);
			GetDlgItem(IDC_ConcentratedClean_OK1)->EnableWindow(FALSE);
			GetDlgItem(IDC_ConcentratedClean_OK2)->EnableWindow(FALSE);
			GetDlgItem(IDC_ConcentratedClean_ESC)->EnableWindow(FALSE);

		}
		key_status = FALSE;
}
