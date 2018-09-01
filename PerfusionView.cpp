// PerfusionView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "PerfusionView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"
#include "FilesOperation.h"
// CPerfusionView �Ի���

IMPLEMENT_DYNAMIC(CPerfusionView, CDialogEx)

CPerfusionView::CPerfusionView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPerfusionView::IDD, pParent)
{
	RinseMode = 0;
}

CPerfusionView::~CPerfusionView()
{
}

void CPerfusionView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPerfusionView, CDialogEx)
	ON_BN_CLICKED(IDC_PRIME_DILUENT, &CPerfusionView::OnPrimeDiluent)
	ON_BN_CLICKED(IDC_PRIME_RINSE, &CPerfusionView::OnPrimeRinse)
	ON_BN_CLICKED(IDC_PRIME_LMNEFIX, &CPerfusionView::OnPrimeLmnefix)
	ON_BN_CLICKED(IDC_PRIME_WBCLYSE, &CPerfusionView::OnPrimeWbclyse)
	ON_BN_CLICKED(IDC_PRIME_HGBLYSE, &CPerfusionView::OnPrimeHgblyse)
	ON_BN_CLICKED(IDC_PRIME_ALL, &CPerfusionView::OnPrimeAll)
	ON_BN_CLICKED(IDC_PRIME_REVERSEDPRIME, &CPerfusionView::OnPrimeReversedprime)
	ON_WM_TIMER()
	ON_MESSAGE(WM_ACKSPI, &CPerfusionView::OnAckspi)
	ON_BN_CLICKED(ID_PERFUSION_RETURN, &CPerfusionView::OnBnClickedPerfusionReturn)
END_MESSAGE_MAP()


// CPerfusionView ��Ϣ�������

BOOL CPerfusionView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if (DSP_status == Busy){
		SetWindowDisable();
	}
	else if (DSP_status == Free){
		SetWindowEnable();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CPerfusionView::OnPrimeDiluent()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	RinseMode = 0;
	PrimeReagent("PRIME  DILUENT---------#\n", SPI_CMD_PRIME_DILUENT);
}

void CPerfusionView::OnPrimeRinse()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	RinseMode = 1;
	PrimeReagent("PRIME  RINSE---------#\n", SPI_CMD_PRIME_WBCRINSE);
}

void CPerfusionView::OnPrimeLmnefix()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	RinseMode = 2;
	PrimeReagent("PRIME  LMNEFIX---------#\n", SPI_CMD_PRIME_LMNEFIX);
}

void CPerfusionView::OnPrimeWbclyse()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	RinseMode = 3;
	PrimeReagent("PRIME  WBCLYSE---------#\n", SPI_CMD_PRIME_WBCLYSE);
}


void CPerfusionView::OnPrimeHgblyse()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	RinseMode = 4;
	PrimeReagent("PRIME  HGBLYSE---------#\n", SPI_CMD_PRIME_HGBLYSE);
}

void CPerfusionView::OnPrimeAll()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	RinseMode = 5;
	PrimeReagent("PRIME  ALL---------#\n", SPI_CMD_PRIMEALL);
}

void CPerfusionView::OnPrimeReversedprime()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	RinseMode = 6;
	PrimeReagent("PRIME  REVERSEDPRIME---------#\n", SPI_CMD_REVERSEDPRIME);
}

void CPerfusionView::PrimeReagent(char* Mess, uchar CMD)
{
	TRACE(Mess);
	key_status = FALSE;
	
	sdata_cmd[0] = CMD;
	if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
	{
		MessageBox(L"����Ͳ��ɹ���", L"ERROR", MB_OK);
	}
	else
	{
		SetTimer(POLLTIME, 1000, 0);
		DSP_status = Busy;
		SetWindowDisable();
		
	}

}

void CPerfusionView::SetWindowEnable(){
	GetDlgItem(IDC_PRIME_DILUENT)->EnableWindow(TRUE);
	GetDlgItem(IDC_PRIME_RINSE)->EnableWindow(TRUE);
	GetDlgItem(IDC_PRIME_LMNEFIX)->EnableWindow(TRUE);
	GetDlgItem(IDC_PRIME_WBCLYSE)->EnableWindow(TRUE);
	GetDlgItem(IDC_PRIME_HGBLYSE)->EnableWindow(TRUE);
	GetDlgItem(IDC_PRIME_ALL)->EnableWindow(TRUE);
	GetDlgItem(IDC_PRIME_REVERSEDPRIME)->EnableWindow(TRUE);
	GetDlgItem(ID_PERFUSION_RETURN)->EnableWindow(TRUE);

}

void CPerfusionView::SetWindowDisable(){
	GetDlgItem(IDC_PRIME_DILUENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_PRIME_RINSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_PRIME_LMNEFIX)->EnableWindow(FALSE);
	GetDlgItem(IDC_PRIME_WBCLYSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_PRIME_HGBLYSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_PRIME_ALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_PRIME_REVERSEDPRIME)->EnableWindow(FALSE);
	GetDlgItem(ID_PERFUSION_RETURN)->EnableWindow(FALSE);
	
}


void CPerfusionView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case POLLTIME:
	{
		TRACE("MSG_TIMER:POLLTIME is due -------------#\n");
		sdata_cmd[0] = SPI_CMD_REQDSP_STATUS;
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		PC_RECEIVE_FRAME(rdata_state, SPI_TYPE_STATE);
		SendMessage(WM_ACKSPI, rdata_state[0], 0);
		//SetWindowEnable();
		break;
	}
	default:
		return;
	}
	//CDialogEx::OnTimer(nIDEvent);
}



afx_msg LRESULT CPerfusionView::OnAckspi(WPARAM wParam, LPARAM lParam)
{
	if (DSP_status == Busy){
		SetWindowEnable();
	}
	switch (wParam)
	{
		//��ע���
	case SPI_STATE_INFO_END:
		KillTimer(POLLTIME);
		//�Լ�ʣ����
		switch (RinseMode)
		{
		case 0:
			
			break;
		case 1:

			/*if (systemcfg2.warn_rinse)
			{

				if (systemcfg2.warn_rinse)
				{*/
					if (logfile.regent.rinse > 25.8)
						logfile.regent.rinse = logfile.regent.rinse - 25.8;
					else
						logfile.regent.rinse = 0;
				//}
			//}
			break;
		case 2:

		/*	if (systemcfg2.warn_fix)
			{
				if (systemcfg2.warn_fix)
				{*/
					if (logfile.regent.eoslyse> 25.8)
						logfile.regent.eoslyse = logfile.regent.eoslyse - 25.8;
					else
						logfile.regent.eoslyse = 0;
				//}
			//}
			break;
		case 3:

		/*	if (systemcfg2.warn_baso)
			{
				if (systemcfg2.warn_baso)
				{*/
					if (logfile.regent.baslyse > 25.8)
						logfile.regent.baslyse = logfile.regent.baslyse - 25.8;
					else
						logfile.regent.baslyse = 0;
				//}

			//}
			break;
		case 4:

			/*if (systemcfg2.warn_hgb)
			{
				if (systemcfg2.warn_hgb)
				{*/
					if (logfile.regent.hgblyse > 4.2)
						logfile.regent.hgblyse = logfile.regent.hgblyse - 4.2;
					else
						logfile.regent.hgblyse = 0;
				//}

			//}
			break;
		case 5:

			/*if (systemcfg2.warn_diluent || systemcfg2.warn_baso || systemcfg2.warn_fix || systemcfg2.warn_hgb
				|| systemcfg2.warn_rinse || systemcfg2.warn_waste)
			{

				if (systemcfg2.warn_rinse)
				{*/
					if (logfile.regent.rinse > 25.8)
						logfile.regent.rinse = logfile.regent.rinse - 25.8;
					else
						logfile.regent.rinse = 0;
				/*}
				if (systemcfg2.warn_hgb)
				{*/
					if (logfile.regent.hgblyse > 4.2)
						logfile.regent.hgblyse = logfile.regent.hgblyse - 4.2;
					else
						logfile.regent.hgblyse = 0;
				/*}
				if (systemcfg2.warn_fix)
				{*/
					if (logfile.regent.eoslyse > 25.8)
						logfile.regent.eoslyse = logfile.regent.eoslyse - 25.8;
					else
						logfile.regent.eoslyse = 0;
				/*}
				if (systemcfg2.warn_baso)
				{*/
					if (logfile.regent.baslyse > 25.8)
						logfile.regent.baslyse = logfile.regent.baslyse - 25.8;
					else
						logfile.regent.baslyse = 0;
				//}

			//}
			break;
		case 6:

			break;

		}
		//��־�ļ�����		
		if (systemcfg2.warn_baso || systemcfg2.warn_diluent || systemcfg2.warn_fix
			|| systemcfg2.warn_hgb || systemcfg2.warn_rinse || systemcfg2.warn_waste)
		{
			WriteLogFile();
		}
		DSP_status = Free;
		SetWindowEnable();
		key_status = TRUE;
		break;
	default:
		break;
	}
	return 0;
}


void CPerfusionView::OnBnClickedPerfusionReturn()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}
