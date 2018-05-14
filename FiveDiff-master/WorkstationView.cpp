// WorkstationView.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "BCGPChartExample.h"
#include "WorkstationView.h"
#include "afxdialogex.h"


// CWorkstationView �Ի���
//�����հײ�������
bool			StartupBlankTestsflag2 = FALSE;				//Ϊ1ʱ��ʾĿǰ���ڽ��п����հײ��ԣ���������
char			StartupBlankTestsTimes2;						//�������Խ��пհײ��ԵĴ���<=2
float			StartupBlankTestswbc2;
float			StartupBlankTestsrbc2;
float			StartupBlankTestsplt2;
bool			IsBlankTest2 = FALSE;

char studyPara2[8][6];//�о�����:Blasts(%),Blasts(#),LEFT(%),LEFT(#),NRBC(%),NRBC(#),P-LCC(%),P-LCC(#)	//xx22  P-LCC(%),P-LCC(#)��ʱû��

static unsigned char 	AlertMotorShow;	//���������ʾΪ1������Ϊ0
static unsigned char 	NumOverwashfrequency;	//������washfrequency��Ҫ�Զ���ϴ  ��Ϊ1������Ϊ0
static unsigned char 	DataBaseFull;	//���ݿ���(955-999)  955-999Ϊ1������Ϊ0
static unsigned char 	ReagentEmpty;	//�Լ�����Ϊ1������Ϊ0


IMPLEMENT_DYNAMIC(CWorkstationView, CDialogEx)

CWorkstationView::CWorkstationView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWorkstationView::IDD, pParent)
{

}

CWorkstationView::~CWorkstationView()
{

}

void CWorkstationView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, IDCANCEL, m_cancel);
}


BEGIN_MESSAGE_MAP(CWorkstationView, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_WORKSHEET_TEST, &CWorkstationView::OnWorkstationtest)
	ON_WM_TIMER()
	ON_MESSAGE(WM_WORKSHEET_ACKSPI, &CWorkstationView::OnAckspi)
	ON_MESSAGE(WM_GETALLTASKINFO, &CWorkstationView::OnGetallTaskInfo)
	ON_MESSAGE(WM_WORKSHEET_CLEAN, &CWorkstationView::OnWorksheetClean)
END_MESSAGE_MAP()


// CWorkstationView ��Ϣ�������


HBRUSH CWorkstationView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CWorkstationView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	dc.FillPath();
}


BOOL CWorkstationView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	updatetabview();


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CWorkstationView::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	

}


int CWorkstationView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}


void CWorkstationView::updatetabview()
{
	CRect rectTab;
	GetDlgItem(IDC_WORKSTATION_TAB)->GetWindowRect(&rectTab);
	ScreenToClient(&rectTab);

	m_workstationtab.Create(CBCGPTabWnd::STYLE_3D, rectTab, this, 1, CBCGPTabWnd::LOCATION_TOP);

	// m_Tasksheetpage=new CWorkstationTasksheet();
	 //m_Analysispage=new CWorkstationAnalysis();
	 //m_Resultpage=new CWorkstationResult();

	 m_Tasksheetpage.Create(IDD_WORKSTATION_TASKSHEET, &m_workstationtab);
	 m_Analysispage.Create(IDD_WORKSHEET_ANALYSIS,&m_workstationtab);
	 m_Resultpage.Create(IDD_WORKSTATION_RESULT, &m_workstationtab);

	 m_workstationtab.AddTab(&m_Tasksheetpage,L"�����б�",0);
	 m_workstationtab.AddTab(&m_Analysispage, L"����", 1);
	 m_workstationtab.AddTab(&m_Resultpage, L"���", 2);

	 CRect rc;
	 m_workstationtab.GetClientRect(rc);
	 m_workstationtab.SetResizeMode(CBCGPTabWnd::RESIZE_VERT);
	 rc.top += 27;
	 rc.bottom -= 5;
	 rc.left += 5;
	 rc.right -= 10;
	 m_Tasksheetpage.MoveWindow(&rc);
	 m_Analysispage.MoveWindow(&rc);
	 m_Resultpage.MoveWindow(&rc);

}

void CWorkstationView::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CWorkstationTasksheet::autogeneratetimes = 0;
	CDialogEx::OnClose();
}


void CWorkstationView::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���
	CWorkstationTasksheet::autogeneratetimes = 0;
	CDialogEx::OnOK();
}


void CWorkstationView::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���
	CWorkstationTasksheet::autogeneratetimes = 0;
	CDialogEx::OnCancel();

}

bool  CWorkstationView::ErrorTimer_Flag = FALSE;


afx_msg LRESULT CWorkstationView::OnWorkstationtest(WPARAM wParam, LPARAM lParam)
{
	TRACE("===============Workstation Test==========\n");
	task_info* m_taskdata = (task_info*)wParam;
	TRACE("----%d------", m_taskdata->number);
	//hw_add:20150104
	errorShowMess = 0;
	//if(errorNumber > 0)
	if (ErrorTimer_Flag)
	{
		ErrorTimer_Flag = FALSE;
		KillTimer(ERROR_TIMER);
	}
	if (BlockErr_Flag)
	{
		BlockErr_Flag = FALSE;
		KillTimer(CHECKERR_TIMER);
	}
	TimesofTest++;
	logfile.totaltimesoftest++;
	InitData(m_taskdata);
	NumFromBoot++;
	//����ƻ����Ͳ�������
	DSP_status = Busy;
	if (m_taskdata->mode == WHOLEDIFF || m_taskdata->mode == DILUENTDIFF)
		sdata_cmd[0] = SPI_CMD_CBC5DIFF_MODE;
	else if (m_taskdata->mode == WHOLECBC || m_taskdata->mode == DILUENTCBC)
		sdata_cmd[0] = SPI_CMD_CBC_MODE;
	if (WAIT_OBJECT_0 == WaitForSingleObject(SendMutex, INFINITE))// �յ�����̬����Ϣ  
	{
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	}
	else
	{
		MessageBox(L"�����������޷����в���!", L"����!", MB_OK | MB_ICONINFORMATION);
		::SendMessage(m_Tasksheetpage, WM_RESTART, 0, 0);
		return 0;
	}
	statusShowMess = 1;
	if (3 == systemcfg3.structure)//�Զ�����
	{
		PC_status = WAITING_PUNCTURE_OVER;
		//�趨��ѯ���ƻ�״̬�Ķ�ʱ��		
		SetTimer(POLLTIME, SPI_POLL_TIME3000, 0);    //��ѯʱ�䶨ʱ��		
	}
	else
	{
		PC_status = WAITING_DATA;
		SetTimer(SLEEP_TIMER1, 3000, 0);	//FDparam ��SPI_STATE_DATAISOK��һ��
	}
	return 0;
}


afx_msg LRESULT CWorkstationView::OnWorksheetClean(WPARAM wParam, LPARAM lParam)
{
	sdata_cmd[0] = SPI_CMD_STARTUP;
	if (WAIT_OBJECT_0 == WaitForSingleObject(SendMutex, INFINITE))// �յ�����̬����Ϣ  
	{
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	}
	else
	{
		MessageBox(L"�����������޷����в���!", L"����!", MB_OK | MB_ICONINFORMATION);
		::SendMessage(m_Tasksheetpage, WM_RESTART, 0, 0);
		return 0;
	}
	SetTimer(POLLTIME, 3000, 0);
	return 0;
}


void CWorkstationView::InitData(task_info* taskdata)
{
	unsigned int i;
	//Ĭ���ַ�Ϊ""
	patientdata2.number = taskdata->number;
	strcpy(patientdata2.name, taskdata->name);
	patientdata2.sex = taskdata->sex;
	patientdata2.rangetype = systemcfg.range.type;
	strcpy(patientdata2.age, taskdata->age);
	strcpy(patientdata2.code, taskdata->barcode);
	strcpy(patientdata2.technician, "");
	strcpy(patientdata2.doctor, taskdata->doctor);
	patientdata2.row = sampledata2.row;
	patientdata2.number = sampledata2.number;

	sampledata2.row = taskdata->row;
	sampledata2.number = taskdata->number;
	//WBC
	strcpy(sampledata2.wbcdata.wbc, "**.**");
	strcpy(sampledata2.wbcdata.lymp, "**.*");
	strcpy(sampledata2.wbcdata.neup, "**.*");
	strcpy(sampledata2.wbcdata.monop, "*.*");
	strcpy(sampledata2.wbcdata.eosp, "*.*");
	strcpy(sampledata2.wbcdata.basp, "*.*");
	strcpy(sampledata2.wbcdata.alyp, "*.*");
	strcpy(sampledata2.wbcdata.licp, "*.*");

	strcpy(sampledata2.wbcdata.lym, "*.**");
	strcpy(sampledata2.wbcdata.neu, "*.**");
	strcpy(sampledata2.wbcdata.mono, "*.**");
	strcpy(sampledata2.wbcdata.eos, "*.**");
	strcpy(sampledata2.wbcdata.bas, "*.**");
	strcpy(sampledata2.wbcdata.aly, "*.**");
	strcpy(sampledata2.wbcdata.lic, "*.**");
	//RBC
	strcpy(sampledata2.rbcdata.rbc, "*.**");
	strcpy(sampledata2.rbcdata.hgb, "***.*");
	strcpy(sampledata2.rbcdata.hct, "**.*");
	strcpy(sampledata2.rbcdata.mcv, "***.*");
	strcpy(sampledata2.rbcdata.mch, "**.*");
	strcpy(sampledata2.rbcdata.mchc, "***.*");
	strcpy(sampledata2.rbcdata.rdwcv, "**.*");
	strcpy(sampledata2.rbcdata.rdwsd, "**.*");
	//PLT
	strcpy(sampledata2.pltdata.plt, "***");
	strcpy(sampledata2.pltdata.mpv, "**.**");
	strcpy(sampledata2.pltdata.pct, "**.**");
	strcpy(sampledata2.pltdata.pdw, "**.*");
	strcpy(sampledata2.pltdata.plcr, "**.*");

	//ɢ��ͼ
	for (i = 0; i < MATRIX_DATA_MAX; i++)
		sampledata2.lmnegraph[i] = 1;
	//BASOֱ��ͼ
	for (i = 0; i < 256; i++)
		sampledata2.basograph[i] = 1;
	//RBCֱ��ͼ
	for (i = 0; i < 512; i++)
		sampledata2.rbcgraph[i] = 1;
	//PLTֱ��ͼ
	for (i = 0; i < 256; i++)
		sampledata2.pltgraph[i] = 1;
	//���
	for (i = 0; i < 9; i++)
		sampledata2.lmneflg[i] = 1;
	sampledata2.basoflg[0] = 1;
	for (i = 0; i < 2; i++)
		sampledata2.rbcflg[i] = 1;
	for (i = 0; i < 4; i++)
		sampledata2.pltflg[i] = 1;
	sampledata2.mode = systemcfg.mode;
	for (i = 0; i < 4; i++)
		sampledata2.flag_wrp[i] = 1;
	sampledata2.coeoflmne = 1.0;

	for (i = 0; i < 8; i++)
		strcpy(studyPara2[i], "**.*");
	//AfxMessageBox(_T("2829"));
}

void CWorkstationView::DisplayErrMess()
{
	errorShowMess = errorMessage[errorShowNum];

	if (errorShowMess == 8)       //WBC�¿�
	{
		SendMessage(WM_BLOCKER, (WPARAM)1, 0L);
	}
	else if (errorShowMess == 13)		  //�����¿�
	{
		SendMessage(WM_BLOCKER, (WPARAM)2, 0L);
	}
	else if (errorShowMess == 9)		  //RBC�¿�
	{
		SendMessage(WM_BLOCKER, (WPARAM)3, 0L);
	}
	else
	{

	}
	//AfxMessageBox(_T("3435"));
}

void CWorkstationView::GetErrInfo()
{
	int		i;

	for (i = 0; i < ERRNUM + 1; i++)
	{
		errorReceive[i] = 0;
	}
	sdata_cmd[0] = SPI_CMD_REQERROR;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	PC_RECEIVE_FRAME(errorReceive, SPI_TYPE_ERRORRES);
	errorNumber = 0;

	for (i = 1; i < ERRNUM + 1; i++)
		if (1 == errorReceive[i])
		{
			logfile.alertnum[i]++;
			errorMessage[errorNumber] = i;
			errorNumber++;
		}
	//AfxMessageBox(_T("3334"));
}


extern bool Allow_ASOnLine;
extern bool AS_OnLine;				//�Զ�����ϵͳ��������������-1(START)��δ��������-0(OVER)
extern bool ASCur_EN;				//��ǰ����ʹ�ܡ�1��Ч���ܹ���������Ѫ������������Ѫ��(ִ���Զ�ά������ʾ���ݿ���������ʱ��ͣ)


int		CWorkstationView::addtime = 0;
bool	CWorkstationView::TempReq_EN = FALSE;
int		CWorkstationView::cuptemp = 0;
int		CWorkstationView::oritemp_rea = 0;
int		CWorkstationView::oritemp_cup = 0;
int		CWorkstationView::reagenttemp = 0;
unsigned char	CWorkstationView::ErrFlag = 0;
unsigned char	CWorkstationView::IsBlocking = 0;
unsigned char	CWorkstationView::EN_Repeat = 0;
int				CWorkstationView::TimesofTest = 0;

void CWorkstationView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case SLEEP_TIMER1:
	{
		if (!TempReq_EN)
		{
			TRACE(_T("SLEEP_TIMER1"));
			KillTimer(SLEEP_TIMER1);
			TRACE("MSG_TIMER:SLEEP_TIMER1 is due -------------#\n");
			//�趨��ѯ���ƻ�״̬�Ķ�ʱ��		
			SetTimer(POLLTIME2, SPI_POLL_TIME1000, 0);    //��ѯʱ�䶨ʱ��	
		}
		else
		{
			TRACE(_T("SLEEP_TIMER2"));
			addtime++;
			if (addtime <= 30)      //10����
			{
				for (int i = 0; i < 3; i++)	//ѭ�����Σ���ֹ���ݴ����쳣
				{
					sdata_cmd[0] = SPI_CMD_REQTEM;
					PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
					memset(temperature, 0, 8);
					if (0 == PC_RECEIVE_FRAME(temperature, SPI_TYPE_TEMRES))
					{
						break;
					}
				}
				if (addtime == 1)
				{
					oritemp_rea = temperature[0] * 1000 + temperature[1] * 100 + temperature[2] * 10 + temperature[3];
					oritemp_cup = temperature[4] * 1000 + temperature[5] * 100 + temperature[6] * 10 + temperature[7];
				}
				reagenttemp = temperature[0] * 1000 + temperature[1] * 100 + temperature[2] * 10 + temperature[3];
				cuptemp = temperature[4] * 1000 + temperature[5] * 100 + temperature[6] * 10 + temperature[7];
				tempcup_base = (unsigned int)systemcfg.tmp.env * 100;
				tempreagent_base = (unsigned int)systemcfg.tmp.incub * 100;

				//if(reagenttemp > tempreagent_base && cuptemp > tempcup_base && reagenttemp < 4000 && cuptemp < 4000 )     //�����ı�
				if (reagenttemp > tempreagent_base - 200 && reagenttemp < 4000)
				{
					KillTimer(SLEEP_TIMER1);

					//���¶�����֮����ܽ�����������
					DSP_status = Free;
					Allow_ASOnLine = TRUE;
					ASCur_EN = TRUE;
					statusShowMess = 0;
					addtime = 0;
					TempReq_EN = FALSE;
				}
			}
			else
			{
				TRACE(_T("SLEEP_TIMER3"));
				char str_show[100] = "";
				char str_cat[20] = "";

				if (reagenttemp - oritemp_rea < 100)
				{
					if (systemcfg.language == CHINESE)
						MessageBox(_T("�¿�ϵͳ1: �Լ�������"), _T("����!"));
					else if (systemcfg.language == ENGLISH)
						MessageBox(_T("Temerature control system 1 : reagent doesn't heat"), _T("Warning!"));
				}
				if (reagenttemp < 200)
				{
					if (systemcfg.language == CHINESE)
						MessageBox(_T("�¿�ϵͳ1: �Լ��¶�Ϊ0"), _T("����!"));
					else if (systemcfg.language == ENGLISH)
						MessageBox(_T("Temerature control system 1 : reagent temperature is 0"), _T("Warning!"));
				}
				if (reagenttemp > tempreagent_base - 400)
				{
					if (systemcfg.language == CHINESE)
						strcpy(str_show, "�����¶�̫��");
					else if (systemcfg.language == ENGLISH)
						strcpy(str_show, "Environment temerature is too low");
					sprintf(str_cat, "\n %d", reagenttemp);
					strcat(str_show, str_cat);

					if (systemcfg.language == CHINESE)
						MessageBox((LPCTSTR)str_show, _T("����!"));
					else if (systemcfg.language == ENGLISH)
						MessageBox((LPCTSTR)str_show, _T("Warning!"));
				}
				if (reagenttemp < tempreagent_base - 400 && reagenttemp > 200)
				{
					if (systemcfg.language == CHINESE)
						strcpy(str_show, "�¿�ϵͳ1: �Լ��¶�̫��");
					else if (systemcfg.language == ENGLISH)
						strcpy(str_show, "Temerature control system 1 : reagent temperature is too low");
					sprintf(str_cat, "\n %d", reagenttemp);
					strcat(str_show, str_cat);

					if (systemcfg.language == CHINESE)
						MessageBox((LPCTSTR)str_show, _T("����!"));
					else if (systemcfg.language == ENGLISH)
						MessageBox((LPCTSTR)str_show, _T("Warning!"));
				}
				KillTimer(SLEEP_TIMER1);
				DSP_status = Free;
				Allow_ASOnLine = TRUE;
				ASCur_EN = TRUE;
				statusShowMess = 0;
				addtime = 0;
				TempReq_EN = FALSE;
			}
		}
		break;
	}
	case ERROR_TIMER:
	{
		errorShowNum++;
		if (errorShowNum >= errorNumber)
		{
			errorShowNum = 0;
			ErrFlag = 0;
			ErrorTimer_Flag = FALSE;
			KillTimer(ERROR_TIMER);
		}
		else
			DisplayErrMess();
		break;
	}
	case CHECKERR_TIMER:
	{
		if (ErrorTimer_Flag == FALSE)    //��ErrorTimer�ر�    
		{
			BlockErr_Flag = FALSE;
			KillTimer(CHECKERR_TIMER);
			errorShowMess = BlockErrStore;

			if (errorShowMess > 0)
			{

			}
		}
		break;
	}
	case POLLTIME2:
	{
		TRACE(_T("POLLTIME2\n"));
		sdata_cmd[0] = SPI_CMD_REQDSP_STATUS;
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		PC_RECEIVE_FRAME(rdata_state, SPI_TYPE_STATE);

		TRACE(_T("rdata_sate[0]=%X\n"), rdata_state[0]);
		PostMessage(WM_WORKSHEET_ACKSPI, rdata_state[0], 0);
		break;
	}
	default:
		break;
		
	}
	CDialogEx::OnTimer(nIDEvent);
}

afx_msg LRESULT CWorkstationView::OnAckspi(WPARAM wParam, LPARAM lParam)
{

	switch (wParam)
	{
		//"���̽���"
	case SPI_STATE_PUNCTURE_OVER:	//�Զ�����ģʽ�²��õ�
		TRACE(_T("SPI_STATE_PUNCTURE_OVER"));
		printf("Puncture is over----------#\n");
		if (PC_status != WAITING_PUNCTURE_OVER)
			break;
		PC_status = WAITING_DATA;
		break;
		//------------------------------------------------
		//���ղ������ݴ���		
		//DSP״̬���SPI_STATE_DATAISOK����һ��״̬ʱҪȷ�������ѽ�����
	case SPI_STATE_ERROR_DRM:
		TRACE(_T("SPI_STATE_ERROR_DRM"));
		if (systemcfg.language == CHINESE)
			MessageBox(_T("��Һ��ʱ,��ػ����"), _T("����!"), MB_OK | MB_ICONINFORMATION);
		else if (systemcfg.language == ENGLISH)
			//CreateWarningBoxNonCHDlg(hDlg, "Drain over time,please shutdown and have a check", "Warning!");
			MessageBox(_T("��Һ��ʱ,��ػ����"), _T("����!"), MB_OK | MB_ICONINFORMATION);
		while (1)
			Sleep(10);
		break;
	case SPI_STATE_ERROR_YM:
		MessageBox(_T("SPI_STATE_ERROR_YM"));
		if (systemcfg.language == CHINESE)
			MessageBox(_T("YM�����λ����,��ػ����"), _T("����!"), MB_OK | MB_ICONINFORMATION);
		else if (systemcfg.language == ENGLISH)
			//CreateWarningBoxNonCHDlg(HWND_DESKTOP, "Reseting YM motor fault,please shutdown and have a check", "Warning!");
			MessageBox(_T("��Һ��ʱ,��ػ����"), _T("����!"), MB_OK | MB_ICONINFORMATION);
		while (1)
			Sleep(10);
		break;
	case SPI_STATE_DATAISOK:
		printf("Data is over----------#\n");
		TRACE(_T("SPI_STATE_DATAISOK"));
		if (PC_status != WAITING_DATA)
			break;
		PC_status = WAITING_TEST_OVER;
		KillTimer(POLLTIME2);
		//------------------------------------------------------------------------------------------------
		m_datatrans.GetNormalTestData(systemcfg.mode, &sampledata2);

		//------------------------------------------------------------------------------------------------
		//��־�ļ����޸�
		//�Լ�ʣ����
		if (systemcfg2.warn_diluent || systemcfg2.warn_baso || systemcfg2.warn_fix || systemcfg2.warn_hgb
			|| systemcfg2.warn_rinse || systemcfg2.warn_waste)
		{
			if (WHOLEDIFF == systemcfg.mode || DILUENTDIFF == systemcfg.mode)
			{
				if (systemcfg2.warn_rinse)
				{
					if (logfile.regent.rinse > 11)
						logfile.regent.rinse = logfile.regent.rinse - 11;
					else
						logfile.regent.rinse = 0;
				}
				if (systemcfg2.warn_hgb)
				{
					if (logfile.regent.hgblyse > 4)
						logfile.regent.hgblyse = logfile.regent.hgblyse - 4;
					else
						logfile.regent.hgblyse = 0;
				}
				if (systemcfg2.warn_fix)
				{
					if (logfile.regent.eoslyse > 10)
						logfile.regent.eoslyse = logfile.regent.eoslyse - 10;
					else
						logfile.regent.eoslyse = 0;
				}
				if (systemcfg2.warn_baso)
				{
					if (logfile.regent.baslyse > 21)
						logfile.regent.baslyse = logfile.regent.baslyse - 21;
					else
						logfile.regent.baslyse = 0;
				}
			}
			else
			{
				if (systemcfg2.warn_rinse)
				{
					if (logfile.regent.rinse > 11)
						logfile.regent.rinse = logfile.regent.rinse - 11;
					else
						logfile.regent.rinse = 0;
				}
				if (systemcfg2.warn_hgb)
				{
					if (logfile.regent.hgblyse > 4)
						logfile.regent.hgblyse = logfile.regent.hgblyse - 4;
					else
						logfile.regent.hgblyse = 0;
				}
				if (systemcfg2.warn_baso)
				{
					if (logfile.regent.baslyse > 20)
						logfile.regent.baslyse = logfile.regent.baslyse - 20;
					else
						logfile.regent.baslyse = 0;
				}
				//logfile.regent.fix = logfile.regent.eoslyse - 10;		//CBCģʽ������
			}
		}
		//���մ���״̬
		GetErrInfo();
		//��־�ļ�����		
		if (errorNumber > 0 || systemcfg2.warn_baso || systemcfg2.warn_diluent || systemcfg2.warn_fix
			|| systemcfg2.warn_hgb || systemcfg2.warn_rinse || systemcfg2.warn_waste)
		{
			if (errorNumber > 0)
			{
				ErrFlag = 1;
				errorShowNum = 0;
				ErrorTimer_Flag = TRUE;

				DisplayErrMess();//��ʾ������Ϣ��������
				SetTimer(ERROR_TIMER, 200, 0);
			}
		}
		SetTimer(UPDATE_STATUS, 200, 0);
		//------------------------------------------------------------------------------------------------
		//���ݽ��ճɹ������д���Ĺ���
		//��������
		{
			//uchar* 	pIsSuper = (uchar*)GetWindowAdditionalData(hDlg);
			int		recv = 0;

			m_dataprocess.BasoLmneRbcPlt_2Analyse(&sampledata2);//û����

			m_dataprocess.WbcBasoAnalysis(&sampledata2, pIsSuper);
			if (WHOLEDIFF == systemcfg.mode || DILUENTDIFF == systemcfg.mode)
			{
				recv = m_dataprocess.LmneAnalysis(&sampledata2, pIsSuper);	//�������BASO��������
				//����������ȫ��Ϊ0�������½���
				if (recv == -1)
				{
					for (int i = 0; i < 3; i++)
					{
						sdata_cmd[0] = SPI_CMD_REQLMNE;
						PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
						if (0 == PC_RECEIVE_FRAME((unsigned char*)sampledata2.lmnegraph, SPI_TYPE_LMNERES))
						{
							printf("LMNE transfer times=%d---------#\n", i + 1);
							break;
						}
					}
					recv = m_dataprocess.LmneAnalysis(&sampledata2, pIsSuper);
				}
			}
			m_dataprocess.HgbAnalysis(&sampledata2);		//�������RBC����ǰ��
			m_dataprocess.RbcAnalysis(&sampledata2, pIsSuper);
			m_dataprocess.PltAnalysis(&sampledata2);
		}
		//------------------------------------------------------------------------------------------------	
		if (!StartupBlankTestsflag2)	//���ǿ����հײ���
		{
			//���������ݱ�����¼
			AddSampleRecord(&sampledata2);
			//������Ϣ����벡�˱�ţ�ע���ԺͲ������ݱ��¼ͬ��
			AddPatientRecord(&patientdata2);
			//----------------------------------------
			//�Ƿ�����ͣ�Զ�����ϵͳ��������ά������
			DataBaseFull = 0;
			if (sampledata2.row >= 995 && sampledata2.row <= 999)//���ݿ�995,996,997,998,999��ʾ���ݿⱸ�ݣ�������ʾ5��
			{
				DataBaseFull = 1;
			}//else δ��995������������������ڶ���   ��1000��ʱ��Ͳ���ʾ���ݿ�����ˣ�ֱ�Ӷ���һ��row��С�ļ�¼�����������ڶ���	

			ReagentEmpty = 0;
			if (logfile.regent.rinse == 0 || logfile.regent.hgblyse == 0 || logfile.regent.eoslyse == 0 || logfile.regent.baslyse == 0)//�Լ�����
			{
				ReagentEmpty = 1;
			}//else �Լ�����
			AlertMotorShow = 0;
			if (errorNumber > 0)//�д���
			{
				for (int i = 0; i < errorNumber; i++)//�������
				{
					if (errorMessage[i] >= 1 && errorMessage[i] <= 7)
					{
						AlertMotorShow = 1;     //�˴�ֻ�ܱ�ʾ�е�����󣬲�����ȷ�����ļ���
						break;
					}
				}
			}//else û�е������
			NumOverwashfrequency = 0;
			if (NumFromBoot >= systemcfg.washfrequency)
			{
				printf("NumFromBoot >= washfrequency----------#\n");
				NumOverwashfrequency = 1;
			}

			if (DataBaseFull || ReagentEmpty || AlertMotorShow || NumOverwashfrequency)//���ݿ��������Զ���ϴ  �Զ�����ϵͳ��ͣ����
			{
				ASCur_EN = FALSE;
			}
			else
			{
				if (1 != IsBlocking && 3 != IsBlocking)
					DSP_status = Clean;	//׼������ϴ�����н�����һ�μ������
			}
			//----------------------------------------
		}
		if (1 == IsBlocking || 3 == IsBlocking)
		{
			key_status = FALSE;
			statusShowMess = 5;
		}
		else
		{
			statusShowMess = 0;
		}
		SetTimer(POLLTIME2, SPI_POLL_TIME3000, 0);
		break;
		//------------------------------------------------
		//���Թ���״̬
	case SPI_STATE_INFO_END:
		//ARM_GPIOCMD(EN_GREEN);
		TRACE(_T("SPI_STATE_INFO_END"));
		KillTimer(POLLTIME2);
		IsBlocking = 0;
		DSP_status = Free;
		statusShowMess = 0;
		//InvalidateRect(hDlg, &STATUS, TRUE);
		key_status = TRUE;
		//Standby_EN = TRUE;
		ASCur_EN = TRUE;
		break;
	case SPI_STATE_TESTISOVER:
		TRACE("MSG_TIMER:POLLTIME is killed -------------#\n");
		TRACE("MSG_ACKSPI: Test Proc is over -------------#\n");
		TRACE(_T("SPI_TEST_IS OVER"));
		if (PC_status != WAITING_TEST_OVER)
			return -1;
		EN_Repeat = 0;
		//----------
		ErrFlag = 0;
		KillTimer(POLLTIME2);
		//----------
		PC_status = TEST_OVER;		//������SendMessage֮ǰ���ں�ᵼ�µڶ��ο����հײ��Բ���������
		if (IsBlankTest2)
			IsBlankTest2 = FALSE;
		//------------------------------------------------
		if (StartupBlankTestsflag2)//��������  �ָ�������״̬
		{
			StartupBlankTestsTimes2++;
			if (1 == StartupBlankTestsTimes2)
			{
				if (StartupBlankTestswbc2 < 0.3 && StartupBlankTestsrbc2 < 0.05 && StartupBlankTestsplt2 < 10)//�Լ���������жϣ���һ�οհײ��Ժϸ�					
				{
					TRACE("Startup BlankTest first time Qualified----------\n");
					StartupBlankTestsflag2 = FALSE;

					TempReq_EN = TRUE;
				}
				else//��һ�οհײ��Բ��ϸ�
				{
					TRACE("Startup BlankTest first time not Qualified----------\n");
					TempReq_EN = FALSE;
					SendMessage(WM_MAINBLANKTEST, 0);	//����հײ���
				}
			}
			else if (2 == StartupBlankTestsTimes2)
			{
				if (StartupBlankTestswbc2 < 0.3 && StartupBlankTestsrbc2 < 0.05 && StartupBlankTestsplt2 < 10)//�Լ���������жϣ��ڶ��οհײ��Ժϸ�			
				{
					TempReq_EN = TRUE;
					printf("Startup BlankTest second time Qualified----------\n");
				}
				else//�ڶ��οհײ��Բ��ϸ�					
				{
					TempReq_EN = FALSE;
					printf("Startup BlankTest second time not Qualified----------\n");
					if (systemcfg.language == CHINESE)
						MessageBox(_T("�հײ��Բ��ϸ�\n  ��������!"), _T("����!"), MB_OK | MB_ICONINFORMATION);
					else if (systemcfg.language == ENGLISH)
						//CreateWarningBoxNonCHDlg(hDlg, "Blank test wrong!\nPlease check device!", "Warning!");
						MessageBox(_T("�հײ��Բ��ϸ�\n  ��������!"), _T("����!"), MB_OK | MB_ICONINFORMATION);
				}
				TempReq_EN = TRUE;      //�ڶ��οհײ��Խ����������������¶�
				StartupBlankTestsflag2 = FALSE;
			}
			if (TempReq_EN)
			{
				addtime = 0;
				statusShowMess = 3;
				//InvalidateRect(hDlg, &STATUS, TRUE);
				UpdateData(FALSE);
				SetTimer(SLEEP_TIMER1, 2000, 0);     //6000
			}
		}
		else//���ǿ�������
		{
			if (1 == IsBlocking)
			{
				DealwithBlockErr(SPI_CMD_BACKSWING_WBCPH, 8);
			}
			else if (3 == IsBlocking)
			{
				DealwithBlockErr(SPI_CMD_BACKSWING_RBCPH, 9);
			}
			else
			{
				DSP_status = Free;
				key_status = TRUE;
			}
		}
		//------------------------------------------------Ӱ���Զ�������	
		if (1 == DataBaseFull || 1 == ReagentEmpty || 1 == AlertMotorShow || 1 == NumOverwashfrequency)
		{
			if (1 == DataBaseFull)	//�����˵��Ŀհײ��ԣ������Ĳ��Զ��ᴥ�����
			{
				if (systemcfg.language == CHINESE)
					MessageBox(_T("���ݿ��������뱸�ݡ�������ǰ���ݶ�ʧ!"), _T("��ʾ"), MB_OK | MB_ICONINFORMATION);
				else if (systemcfg.language == ENGLISH)
					//CreateWarningBoxNonCHDlg(hDlg, "Database is full,Please backup database.Otherwise,Previous database will be lost!", "Presentation");
					MessageBox(_T("���ݿ��������뱸�ݡ�������ǰ���ݶ�ʧ!"), _T("��ʾ"), MB_OK | MB_ICONINFORMATION);
				//CreateEmptyDatabaseDlg(hDlg);
			}
			if (1 == ReagentEmpty)	//����Լ�
			{
				if (systemcfg.language == CHINESE)
					MessageBox(_T("�����Լ�!"), _T("��ʾ"), MB_OK | MB_ICONINFORMATION);
				else if (systemcfg.language == ENGLISH)
					//CreateWarningBoxNonCHDlg(hDlg, "Check the Reagent Please!", "Presentation");
					MessageBox(_T("�����Լ�!"), _T("��ʾ"), MB_OK | MB_ICONINFORMATION);
				//CreateRegentAmountDlg(hDlg);
			}
			if (1 == AlertMotorShow)//�����
			{
				if (systemcfg.language == CHINESE)
					MessageBox(_T("������!"), _T("��ʾ"), MB_OK | MB_ICONINFORMATION);
				else if (systemcfg.language == ENGLISH)
					//CreateWarningBoxNonCHDlg(hDlg, "Check the Motor Please!", "Presentation");
					MessageBox(_T("Check the Motor Please!"), _T("Presentation"), MB_OK | MB_ICONINFORMATION);
				//CreateAlertShowDlg(hDlg);
				break;//����꣬��ʹ���Զ�����ϵͳ����ִ���Զ���ϴ
			}
			if (1 == NumOverwashfrequency)
			{
				SendMessage(WM_AUTOCLEAN, 0);
				//�Զ���ϴִ����ִ��ASCur_EN = 1
			}
			else
			{
				ASCur_EN = TRUE;	//����Ҫ���Զ���ϴ��ʱ�򣬿���ʹ���Զ�����ϵͳ(ֻ���Զ�����ϵͳ�õ�)
			}
		}
		if (TimesofTest >= 500)   //Add:20150430
		{
			int 		response;
			MesBox	Message;

			if (systemcfg.language == CHINESE)
			{
				response = MessageBox(_T("���������Ѵ�500,��ִ��Ũ����ϴ"), _T("Ũ����ϴ��ʾ"), MB_YESNO);
			}
			else if (systemcfg.language == ENGLISH)
			{
				Message.caption = "Tip of Concentrated Clean";
				Message.message = "You have tested 500 samples,\na Concentrated Clean is necessary";
				Message.type = MBOX_YESNO;
				//CreateYesNoDlg(hDlg, &response, &Message);
			}
			if (response == IDYES)
				SendMessage(WM_CONCENCLEAN, 0L);
		}
		::SendMessage(m_Analysispage, WM_GETRESULT, (WPARAM)&sampledata2, 0);
		ReleaseMutex(SendMutex);
		InformWindowTheTask((sampledata2.number+1));
		//------------------------------------------------	
		break;
		//----------------------------------------
	default:
		break;
	}
	return 0;
}

void CWorkstationView::DealwithBlockErr(uchar CMD_Name, uchar ErrNum)
{
	if (!BlockErr_Flag)
	{
		BlockErr_Flag = TRUE;

		BlockErrStore = ErrNum;
		SetTimer(CHECKERR_TIMER, 200, 0);
	}
	else
		puts("CHECKERR_TIMER is open!");

	SendCmdToDSP(CMD_Name);
	//AfxMessageBox(_T("3637"));
}


void CWorkstationView::SendCmdToDSP(uchar CMD_Name)
{
	char Mess[50];

	sdata_cmd[0] = CMD_Name;

	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	SetTimer(POLLTIME2, SPI_POLL_TIME3000, 0);
}

void CWorkstationView::InformWindowTheTask(int num)
{
	::SendMessage(m_Tasksheetpage, WM_STARTNEXTTASK, (WPARAM)num, 0);
}


afx_msg LRESULT CWorkstationView::OnGetallTaskInfo(WPARAM wParam, LPARAM lParam)
{
	m_alltask = (vector<task_info>*)wParam;
	::SendMessage(m_Analysispage, WM_GETALLTASKINFO, (WPARAM)m_alltask,0);
	return 0;
}


