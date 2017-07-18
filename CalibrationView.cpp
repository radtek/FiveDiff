// CalibrationView.cpp : ʵ���ļ�
//

#include "stdafx.h"

#include "CalibrationView.h"
//#include "Includes_app.h"
#include "ManualCalibrationView.h"
#include "FilesOperation.h"
// CCalibrationView

IMPLEMENT_DYNCREATE(CCalibrationView, CBCGPChartExampleView)

CCalibrationView::CCalibrationView()
: CBCGPChartExampleView(CCalibrationView::IDD)
, m_modeRadio(0)
, m_testmodeRadio(0)
{

}

CCalibrationView::~CCalibrationView()
{

}

void CCalibrationView::DoDataExchange(CDataExchange* pDX)
{
	CBCGPChartExampleView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_CalibrationList);
	DDX_Control(pDX, IDC_LIST2, m_CoefficientList);
	DDX_Radio(pDX, IDC_AUTO_MODE_RADIO, m_modeRadio);
	DDX_Radio(pDX, IDC_AUTO_TESTMODE_RADIO, m_testmodeRadio);
}

BEGIN_MESSAGE_MAP(CCalibrationView, CBCGPChartExampleView)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_AUTO_CALIBRATE, &CCalibrationView::OnAutoCalibrateStart)
	ON_WM_TIMER()
	ON_MESSAGE(WM_ACKSPI, &CCalibrationView::OnAckspi)
	ON_BN_CLICKED(IDC_CONFIRM_TARGETVALUE, &CCalibrationView::OnTargetvalue)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &CCalibrationView::OnNMClickCoefficientList)
	ON_BN_CLICKED(IDC_AUTO_MODE_RADIO, &CCalibrationView::OnBnClickedAutoModeRadio)
	ON_BN_CLICKED(IDC_AUTO_MODE_RADIO2, &CCalibrationView::OnBnClickedAutoModeRadio2)
	ON_BN_CLICKED(IDC_AUTO_TESTMODE_RADIO, &CCalibrationView::OnBnClickedAutoTestmodeRadio)
	ON_BN_CLICKED(IDC_AUTO_TESTMODE_RADIO2, &CCalibrationView::OnBnClickedAutoTestmodeRadio2)
	ON_BN_CLICKED(IDC_CALIBRATION_TEST, &CCalibrationView::OnCalibrationTest)
END_MESSAGE_MAP()


// CCalibrationView ���

#ifdef _DEBUG
void CCalibrationView::AssertValid() const
{
	CBCGPChartExampleView::AssertValid();
}

#ifndef _WIN32_WCE
void CCalibrationView::Dump(CDumpContext& dc) const
{
	CBCGPChartExampleView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCalibrationView ��Ϣ�������
unsigned char CCalibrationView::oldSysmode=0;			//��¼�������ǰ��ϵͳ����ģʽ���˳������ʱ��Ҫ�ָ�ԭ���Ĳ���ģʽ
unsigned char CCalibrationView::ac_index=0;              //��Ҫ��β��ԣ���¼�ڼ��β���
unsigned char CCalibrationView::ref_flag=0;				//��ʾ�ο�ֵ������״̬��1��ʾ�����룬0��ʾδ����
status CCalibrationView::CurStatusMess=Free;

void CCalibrationView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CBCGPChartExampleView::OnPaint()
}


BOOL CCalibrationView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return CBCGPChartExampleView::OnEraseBkgnd(pDC);
}

void CCalibrationView::OnInitialUpdate()
{
	CBCGPChartExampleView::OnInitialUpdate();
	// TODO:  �ڴ����ר�ô����/����û���
	oldSysmode = systemcfg.mode;    //����������֮ǰ��ģʽ
	haveeditcreate = false;
	Showtarget();
	InitCalibrationForm();
	InitCoeffcientForm();
}

BOOL CCalibrationView::InitCalibrationForm()
{
	CRect rect;

	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_CalibrationList.GetClientRect(&rect);
	m_CalibrationList.SetRowHeigt(20);
	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_CalibrationList.SetExtendedStyle(m_CalibrationList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);


	// ΪPLT�б���ͼ�ؼ��������
	m_CalibrationList.InsertColumn(0, _T("ѡ��"), LVCFMT_CENTER, rect.Width() *1/ 16, 0);
	m_CalibrationList.InsertColumn(1, _T("������"), LVCFMT_CENTER, rect.Width()*2 /16, 1);
	m_CalibrationList.InsertColumn(2, _T("��������"), LVCFMT_CENTER, rect.Width()* 3/ 16, 2);
	m_CalibrationList.InsertColumn(3, _T("WBC"), LVCFMT_CENTER, rect.Width() *2/ 16, 3);
	m_CalibrationList.InsertColumn(4, _T("RBC"), LVCFMT_CENTER, rect.Width() *2/ 16, 4);
	m_CalibrationList.InsertColumn(5, _T("HGB"), LVCFMT_CENTER, rect.Width() *2/ 16, 5);
	m_CalibrationList.InsertColumn(5, _T("MCV"), LVCFMT_CENTER, rect.Width() *2/ 16, 6);
	m_CalibrationList.InsertColumn(5, _T("PLT"), LVCFMT_CENTER, rect.Width() *2/ 16, 7);

	// ��PLT�б���ͼ�ؼ��в����б���������б������ı�
	m_CalibrationList.InsertItem(0, _T(""));
	m_CalibrationList.SetItemText(0, 1, _T("Technician"));
	//m_CalibrationList.SetItemText(0, 2, _T("10^9/L"));
	m_CalibrationList.InsertItem(1, _T(""));
	m_CalibrationList.SetItemText(1, 1, _T("Technician"));
	//m_CalibrationList.SetItemText(1, 2, _T("fL"));
	m_CalibrationList.InsertItem(2, _T(""));
	m_CalibrationList.SetItemText(2, 1, _T("Technician"));
	//m_CalibrationList.SetItemText(2, 2, _T("fL"));
	m_CalibrationList.InsertItem(3, _T(""));
	m_CalibrationList.SetItemText(3, 1, _T("Technician"));
	//m_CalibrationList.SetItemText(3, 2, _T("%"));
	m_CalibrationList.InsertItem(4, _T(""));
	m_CalibrationList.SetItemText(4, 1, _T("Technician"));
	//m_CalibrationList.SetItemText(4, 2, _T("%"));

	return TRUE;
}


BOOL CCalibrationView::InitCoeffcientForm()
{

	CRect rect;
	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_CoefficientList.GetClientRect(&rect);
	m_CoefficientList.SetRowHeigt(20);
	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_CoefficientList.SetExtendedStyle(m_CoefficientList.GetExtendedStyle() |LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);


	// ΪPLT�б���ͼ�ؼ��������
	m_CoefficientList.InsertColumn(0, _T(""), LVCFMT_CENTER, rect.Width() * 3 / 8, 0);
	m_CoefficientList.InsertColumn(1, _T("WBC"), LVCFMT_CENTER, rect.Width() * 1 / 8, 1);
	m_CoefficientList.InsertColumn(2, _T("RBC"), LVCFMT_CENTER, rect.Width() * 1 / 8, 2);
	m_CoefficientList.InsertColumn(3, _T("HGB"), LVCFMT_CENTER, rect.Width() * 1 / 8, 3);
	m_CoefficientList.InsertColumn(4, _T("MCV"), LVCFMT_CENTER, rect.Width() * 1 / 8, 4);
	m_CoefficientList.InsertColumn(5, _T("PLT"), LVCFMT_CENTER, rect.Width() * 1 / 8, 5);

	// ��PLT�б���ͼ�ؼ��в����б���������б������ı�
	m_CoefficientList.InsertItem(0, _T("��ֵ"));
	//m_CoefficientList.InsertItem(0, _T(""));
	m_CoefficientList.InsertItem(1, _T("ƽ��ֵ"));
	m_CoefficientList.InsertItem(2, _T("CVֵ"));
	m_CoefficientList.InsertItem(3, _T("��ǰϵ��"));
	m_CoefficientList.InsertItem(4, _T("��ϵ��"));

	CString cs[5];
	for (int i = 0; i < 5; i++)
	{
		cs[i].Format(L"%f", systemcfg.calibration[systemcfg.mode][i]);
		m_CoefficientList.SetItemText(3, i + 1, cs[i]);
	}
	return TRUE;
}

void CCalibrationView::UpdateTargetvalue()
{
	CString cs[5];
	for (int i = 0; i < 5; i++)
	{
		cs[i].Format(L"%f", systemcfg.calibration[systemcfg.mode][i]);
		m_CoefficientList.SetItemText(3, i + 1, cs[i]);
	}

}

void CCalibrationView::OnTargetvalue()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//unsigned int		i;
	//CString			buffer[6] = {"0"};
	//uchar			num = 0;
	//USES_CONVERSION;
	//for (i = IDC_WBC_TARGET; i <= IDC_PLT_TARGET; i++)
	//{
	//	GetDlgItem(i)->GetWindowText(buffer[i-IDC_WBC_TARGET]);
	//	buffer[5] = '\0';

	//	//ori: num = i - IDC_AUTOCALIB_BASE
	//	//֮ǰ�������Ӻ�Ϊ0.7������������ڴ˴�
	//	num = i - IDC_WBC_TARGET;
	//	strcpy((char*)ref_ac[num],W2A( buffer[i - IDC_WBC_TARGET]));

	//	if (atof((const char*)ref_ac[num]) <= 0 || atof((const char*)ref_ac[num]) > 1000)
	//	{
	//		if (systemcfg.language == CHINESE)
	//			MessageBox(L"��ֵ�������!\n����������!", L"����!");
	//		return ;
	//	}
	//}
	//ref_flag = 1;
	CManualCalibrationView m_manualcalibrationdlg;
	if (m_manualcalibrationdlg.DoModal()==IDOK)
	{
		Showtarget();
		UpdateTargetvalue();
	}
}

void CCalibrationView::DealWithData(uchar CurCalMode, CString ResultBuff[5], uchar CVBuff[5], uchar CoeBuff[5], int ItemType)
{
	unsigned int 	i;
	uchar 		cal_fail = 0;
	uchar 		modeTemp = CurCalMode;
	double 		SUM = 0.0, CV = 0.0, SD = 0.0, MEAN = 0.0, ftmp = 0.0, COE = 0.0;

	double 		MAX, MIN;

	MAX = MIN =_wtof(ResultBuff[0]);

	for (i = 0; i < ac_index; i++)
	{
		if (ResultBuff[i][0] == '*')	//�ôβ������������⣬������DataProcess��ʱ����ʾΪ*��
		{
			cal_fail = 1;
			break;
		}
		else
		{
			ftmp = _wtof(ResultBuff[i]);
			if (ftmp < MIN)
				MIN = ftmp;
			else if (ftmp > MAX)
				MAX = ftmp;
			SUM += ftmp;
		}
	}
	if (cal_fail == 0)
	{
		MEAN = SUM / 5;	//X-bar
		for (i = 0; i < ac_index; i++)
		{
			ftmp = _wtof(ResultBuff[i]);
			SD += (ftmp - MEAN)*(ftmp - MEAN);
		}
		SD /= 4;
		SD = sqrt(SD);
		if (MEAN < 0.00001)	//��֤�����ĳ�����Ϊ0
		{
			sprintf((char*)CVBuff, "*.**");
			sprintf((char*)CoeBuff, "***");
		}
		else
		{
			CV = SD * 100 / MEAN;
			if (CV < 100.0)	//����100wbc_cvbuff�ʹ治�����ˣ��ַ�����ֻ�ܴ�100.00���µ�
			{
				sprintf((char*)CVBuff, "%.2f", CV);
			}
			else
			{
				sprintf((char*)CVBuff, "*.**");
			}
			if (CV < 4.0)		//��ʲô����û��4 xx22
			{
				COE = atof((const char*)ref_ac[ItemType])*systemcfg.calibration[modeTemp][ItemType] / MEAN;	//ԭ��ϵ���Ļ������ٳ���һ����ϵ��

				if (COE > 1.30)		//������ʲô
					COE = 1.30;
				else if (COE < 0.70)	//������ʲô
					COE = 0.70;
				systemcfg.calibration[modeTemp][ItemType] = COE;
				sprintf((char*)CoeBuff, "%.2f", COE);
			}
			else
				sprintf((char*)CoeBuff, "***");
		}
	}
	else
	{
		sprintf((char*)CVBuff, "*.**");
		sprintf((char*)CoeBuff, "***");
	}
}

void CCalibrationView::DealWithWBC(uchar CurCalMode)
{
	DealWithData(CurCalMode, wbc_buff, wbc_cvbuff, wbc_coebuff, CAL_WBCF);
}

void CCalibrationView::DealWithRBC(uchar CurCalMode)
{
	DealWithData(CurCalMode, rbc_buff, rbc_cvbuff, rbc_coebuff, CAL_RBCF);
}

void CCalibrationView::DealWithHGB(uchar CurCalMode)
{
	DealWithData(CurCalMode, hgb_buff, hgb_cvbuff, hgb_coebuff, CAL_HGBF);
}

void CCalibrationView::DealWithMCV(uchar CurCalMode)
{
	DealWithData(CurCalMode, mcv_buff, mcv_cvbuff, mcv_coebuff, CAL_MCVF);
}

void CCalibrationView::DealWithPLT(uchar CurCalMode)
{
	DealWithData(CurCalMode, plt_buff, plt_cvbuff, plt_coebuff, CAL_PLTF);
}

void CCalibrationView::OnAutoCalibrateStart()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
}
BOOL  CCalibrationView::GetRefValue()
{
	CString temp[5];
	CString nametemp[5] = { "WBC", "RBC", "HGB", "MCV","PLT"};
	USES_CONVERSION;
	for (int i = 0; i < 5; i++)
	{
		temp[i] = m_CoefficientList.GetItemText(0, i+1);
		if (temp[i].Compare(L"")==0)
		{
			nametemp[i] += "��ֵΪ��";
			MessageBox(nametemp[i]);
		}
		strcpy((char*)ref_ac[i], W2A(temp[i]));
		if ((_wtof(temp[i]) <= 0) && (_wtof(temp[i]) > 1000))
		{
			if (systemcfg.language == CHINESE)
				MessageBox(L"��ֵ�������!\n����������!",L"����!", MB_OK | MB_ICONINFORMATION);
			return FALSE;
		}
	}
	ref_flag = 1;
	return TRUE;
}

void CCalibrationView::ShowCalibrationInfo()
{
	if (ac_index > 0)
	{
		TRACE("ac_index=%d---------#\n", ac_index);
		//5���������	                     
		//strcpy((char*)wbc_buff[ac_index - 1], sampledata.wbcdata.wbc);
		//strcpy((char*)rbc_buff[ac_index - 1], sampledata.rbcdata.rbc);
		//strcpy((char*)hgb_buff[ac_index - 1], sampledata.rbcdata.hgb);
		//strcpy((char*)mcv_buff[ac_index - 1], sampledata.rbcdata.mcv);
		//strcpy((char*)plt_buff[ac_index - 1], sampledata.pltdata.plt);
		wbc_buff[ac_index - 1].Format(L"%d",sampledata.wbcdata.wbc);
		rbc_buff[ac_index - 1].Format(L"%d",sampledata.rbcdata.rbc);
		hgb_buff[ac_index - 1].Format(L"%d",sampledata.rbcdata.hgb);
		mcv_buff[ac_index - 1].Format(L"%d",sampledata.rbcdata.mcv);
		plt_buff[ac_index - 1].Format(L"%d",sampledata.pltdata.plt);

		for (int i = 0; i < ac_index; i++)
		{
			m_CalibrationList.SetItemText(i,3, wbc_buff[i]);
			m_CalibrationList.SetItemText(i, 4, rbc_buff[i]);
			m_CalibrationList.SetItemText(i, 5, hgb_buff[i]);
			m_CalibrationList.SetItemText(i, 6, mcv_buff[i]);
			m_CalibrationList.SetItemText(i, 7, plt_buff[i]);
		}
	}
}


void CCalibrationView::UpdateCalibrate()
{
	uchar CurCalMode;

	CurCalMode = systemcfg.mode;

	DealWithWBC(CurCalMode);
	DealWithRBC(CurCalMode);
	DealWithHGB(CurCalMode);
	DealWithMCV(CurCalMode);
	DealWithPLT(CurCalMode);
	m_CoefficientList.SetItemText(2, 1,(LPCTSTR)wbc_cvbuff);
	m_CoefficientList.SetItemText(2, 2, (LPCTSTR)rbc_cvbuff);
	m_CoefficientList.SetItemText(2, 3, (LPCTSTR)hgb_cvbuff);
	m_CoefficientList.SetItemText(2, 4, (LPCTSTR)mcv_cvbuff);
	m_CoefficientList.SetItemText(2, 5, (LPCTSTR)plt_cvbuff);

	m_CoefficientList.SetItemText(4, 1,(LPCTSTR)wbc_coebuff);
	m_CoefficientList.SetItemText(4, 2, (LPCTSTR)rbc_coebuff);
	m_CoefficientList.SetItemText(4, 3, (LPCTSTR)hgb_coebuff);
	m_CoefficientList.SetItemText(4, 4, (LPCTSTR)mcv_coebuff);
	m_CoefficientList.SetItemText(4, 5, (LPCTSTR)plt_coebuff);

}

void CCalibrationView::AutoCalibrationRun()
{
	uchar CurCalMode;

	DSP_status = Busy;
	CurStatusMess = Busy;

	systemcfg.mode = TestMode;//��ΪWbcBasoAnalysis�Ⱥ�����Ҫ�õ�����ģʽ(systemcfg.mode)		

	if (TestMode == WHOLEDIFF || TestMode == DILUENTDIFF)//Ԥϡ��5Diff��DSP���̺�ȫѪ5Diff��DSP����һ����ֻ������󴫵�ARM�����ݳ˵����Ӳ�һ��
		sdata_cmd[0] = SPI_CMD_CBC5DIFF_MODE;
	else if (TestMode == WHOLECBC || TestMode == DILUENTCBC)//Ԥϡ��CBC��DSP���̺�ȫѪCBC��DSP����һ����ֻ������󴫵�ARM�����ݳ˵����Ӳ�һ��
		sdata_cmd[0] = SPI_CMD_CBC_MODE;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	rdata_state[0] = SPI_STATE_INFO_START;
	SetTimer(SLEEP_TIMER2, 50000, 0);
}


void CCalibrationView::OnCalibrationTest()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!GetRefValue())
	{
		MessageBox(L"�������ֵ!", L"����!");
		return;
	}
	if (1 == ref_flag && ac_index < 5)
		AutoCalibrationRun();
}


void CCalibrationView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CBCGPChartExampleView::OnTimer(nIDEvent);
	switch (nIDEvent)
	{
	case SLEEP_TIMER2:
		KillTimer(SLEEP_TIMER2);
		PC_status = WAITING_DATA;
		SetTimer(POLLTIME,3000,0);
	case POLLTIME:
		sdata_cmd[0] = SPI_CMD_REQDSP_STATUS;
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		PC_RECEIVE_FRAME(rdata_state, SPI_TYPE_STATE);
		SendMessage(MSG_ACKSPI, rdata_state[0], 0);//����ѯ��״̬���͵�SPI��Ϣ��Ӧ����
		TRACE("MSG_TIMER:POLLTIME is due -------------#\n");
	default:
			break;
	}
}

afx_msg LRESULT CCalibrationView::OnAckspi(WPARAM wParam, LPARAM lParam)
{

	switch (wParam)
	{
		//------------------------------------------------
		//DSP��������׼����
	case SPI_STATE_DATAISOK:
		if (WAITING_DATA == PC_status)//�߼��ϱ�ֻ֤��������һ�Σ��������ظ�����
		{
			KillTimer(POLLTIME);

			m_datatrans.GetNormalData_BASO(&sampledata);
			m_datatrans.GetNormalData_RBC(&sampledata);
			m_datatrans.GetNormalData_PLT(&sampledata);
			m_datatrans.GetNormalData_HGB();
			//���ݷ���
			{
				uchar IsSuper = 1;
				m_dataprocess.WbcBasoAnalysis(&sampledata, &IsSuper);
				m_dataprocess.HgbAnalysis(&sampledata);		//�������BASO����ǰ��
				m_dataprocess.RbcAnalysis(&sampledata, &IsSuper);
				m_dataprocess.PltAnalysis(&sampledata);
			}
			ac_index += 1;

			CurStatusMess = Free;
			//ˢ��ͼ�εȴ����̽���
			PC_status = WAITING_TEST_OVER;
			SetTimer(POLLTIME, SPI_POLL_TIME3000,0);
		}
		break;
		//���Թ��̽���
	case SPI_STATE_TESTISOVER:
		KillTimer( POLLTIME);
		DSP_status = Free;
		TRACE("MSG_ACKSPI: Test Proc is over -------------#\n");
		break;
	default:
		break;
	}
	return 0;
}

void CCalibrationView::createEdit(NM_LISTVIEW  *pEditCtrl, CEdit *createdit, int &Item, int &SubItem, bool &havecreat)
{
	Item = pEditCtrl->iItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
	SubItem = pEditCtrl->iSubItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
	createdit->Create(ES_AUTOHSCROLL | WS_CHILD | ES_LEFT | ES_WANTRETURN,
		CRect(0, 0, 0, 0), this, IDC_EDIT_CREATEID);//�����༭�����,IDC_EDIT_CREATEIDΪ�ؼ�ID��3000�������¿�ͷ����
	havecreat = true;
	createdit->SetFont(this->GetFont(), FALSE);//��������,����������Ļ�������ֻ��ͻأ�ĸо�
	createdit->SetParent(&m_CoefficientList);//��list control����Ϊ������,���ɵ�Edit������ȷ��λ,���Ҳ����Ҫ
	CRect  EditRect;
	m_CoefficientList.GetSubItemRect(e_Item, e_SubItem, LVIR_LABEL, EditRect);//��ȡ��Ԫ��Ŀռ�λ����Ϣ
	EditRect.SetRect(EditRect.left + 1, EditRect.top + 1, EditRect.left + m_CoefficientList.GetColumnWidth(e_SubItem) - 1, EditRect.bottom - 1);//+1��-1�����ñ༭�����ڵ�ס�б���е�������
	CString strItem = m_CoefficientList.GetItemText(e_Item, e_SubItem);//�����Ӧ��Ԫ���ַ�
	createdit->SetWindowText(strItem);//����Ԫ���ַ���ʾ�ڱ༭����
	createdit->MoveWindow(&EditRect);//���༭��λ�÷�����Ӧ��Ԫ����
	createdit->ShowWindow(SW_SHOW);//��ʾ�༭���ڵ�Ԫ������
	createdit->SetFocus();//����Ϊ���� 
	createdit->SetSel(-1);//���ù�����ı������ֵ����
}

void CCalibrationView::distroyEdit(CListCtrl *list, CEdit* distroyedit, int &Item, int &SubItem)
{
	CString meditdata;
	distroyedit->GetWindowTextW(meditdata);
	list->SetItemText(Item, SubItem, meditdata);//�����Ӧ��Ԫ���ַ�
	distroyedit->DestroyWindow();//���ٶ����д�����Ҫ�����٣���Ȼ�ᱨ��
}

void CCalibrationView::OnNMClickCoefficientList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW  *pEditCtrl = (NM_LISTVIEW *)pNMHDR;
	printf("�У�%d���У�%d\n", pEditCtrl->iItem, pEditCtrl->iSubItem);
	if (pEditCtrl->iItem == -1)//������ǹ�����
	{
		if (haveeditcreate == true)//���֮ǰ�����˱༭������ٵ�
		{
			distroyEdit(&m_CoefficientList, &m_WBCEdit, e_Item, e_SubItem);//���ٵ�Ԫ��༭�����
			haveeditcreate = false;
		}
	}
	else if( (pEditCtrl->iItem==0)&&(pEditCtrl->iSubItem != 0))
	{
		if (haveeditcreate == true)
		{
			if (!(e_Item == pEditCtrl->iItem && e_SubItem == pEditCtrl->iSubItem))//������еĵ�Ԫ����֮ǰ�����õ�
			{
				distroyEdit(&m_CoefficientList, &m_WBCEdit, e_Item, e_SubItem);
				haveeditcreate = false;
				createEdit(pEditCtrl, &m_WBCEdit, e_Item, e_SubItem, haveeditcreate);//�����༭��
			}
			else//���еĵ�Ԫ����֮ǰ�����õ�
			{
				m_WBCEdit.SetFocus();//����Ϊ���� 
			}
		}
		else
		{
			e_Item = pEditCtrl->iItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
			e_SubItem = pEditCtrl->iSubItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
			createEdit(pEditCtrl, &m_WBCEdit, e_Item, e_SubItem, haveeditcreate);//�����༭��
		}
	}
	else
	{
		if (haveeditcreate == true)//���֮ǰ�����˱༭������ٵ�
		{
			distroyEdit(&m_CoefficientList, &m_WBCEdit, e_Item, e_SubItem);
			haveeditcreate = false;
		}
	}
	*pResult = 0;
}

void CCalibrationView::Showtarget()
{
	CString calibrationtemp[4][5];
	UpdateData(true);
	if (m_modeRadio == 0)
	{
		if (m_testmodeRadio == 0)
		{
			TestMode = WHOLEDIFF;
		}
		else if (m_testmodeRadio == 1)
		{
			TestMode = WHOLECBC;
		}
	}
	else if (m_modeRadio == 1)
	{
		if (m_testmodeRadio == 0)
		{
			TestMode = DILUENTDIFF;
		}
		else if (m_testmodeRadio == 1)
		{
			TestMode = DILUENTCBC;
		}
	}
	ReadSystemcfgFile();
	for (int i = 0; i < 5; i++)
	{
		calibrationtemp[TestMode][i].Format(L"%0.2f", systemcfg.calibration[TestMode][i]);
	}
	GetDlgItem(IDC_WBC_TARGET)->SetWindowText(calibrationtemp[TestMode][0]);
	GetDlgItem(IDC_RBC_TARGET)->SetWindowText(calibrationtemp[TestMode][1]);
	GetDlgItem(IDC_HGB_TARGET)->SetWindowText(calibrationtemp[TestMode][2]);
	GetDlgItem(IDC_MCV_TARGET)->SetWindowText(calibrationtemp[TestMode][3]);
	GetDlgItem(IDC_PLT_TARGET)->SetWindowText(calibrationtemp[TestMode][4]);
}


void CCalibrationView::OnBnClickedAutoModeRadio()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Showtarget();
}


void CCalibrationView::OnBnClickedAutoModeRadio2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Showtarget();
}


void CCalibrationView::OnBnClickedAutoTestmodeRadio()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Showtarget();
}

void CCalibrationView::OnBnClickedAutoTestmodeRadio2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Showtarget();
}
