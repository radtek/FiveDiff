// CalibrationView.cpp : 实现文件
//

#include "stdafx.h"

#include "CalibrationView.h"
//#include "Includes_app.h"
#include "ManualCalibrationView.h"
#include "FilesOperation.h"
// CCalibrationView

IMPLEMENT_DYNCREATE(CCalibrationView, CBCGPChartExampleView)

/*****************定标***************/


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
	//ON_BN_CLICKED(IDC_MANUAL_CALIBRATION_SAVE, &CCalibrationView::OnTargetvalue)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &CCalibrationView::OnNMClickCoefficientList)
	ON_BN_CLICKED(IDC_AUTO_MODE_RADIO, &CCalibrationView::OnBnClickedAutoModeRadio)
	ON_BN_CLICKED(IDC_AUTO_MODE_RADIO2, &CCalibrationView::OnBnClickedAutoModeRadio2)
	ON_BN_CLICKED(IDC_AUTO_TESTMODE_RADIO, &CCalibrationView::OnBnClickedAutoTestmodeRadio)
	ON_BN_CLICKED(IDC_AUTO_TESTMODE_RADIO2, &CCalibrationView::OnBnClickedAutoTestmodeRadio2)
	ON_BN_CLICKED(IDC_CALIBRATION_TEST, &CCalibrationView::OnCalibrationTest)
	ON_BN_CLICKED(IDC_MANUAL_CALIBRATION_SAVE, &CCalibrationView::OnBnClickedManualCalibrationSave)
	ON_BN_CLICKED(IDC_PRINT_CALI, &CCalibrationView::OnBnClickedPrintCali)
END_MESSAGE_MAP()


// CCalibrationView 诊断

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


// CCalibrationView 消息处理程序
unsigned char CCalibrationView::oldSysmode=0;			//记录进入界面前的系统测试模式，退出界面的时候要恢复原来的测试模式
unsigned char CCalibrationView::ac_index=0;              //需要五次测试，记录第几次测试
unsigned char CCalibrationView::ref_flag=0;				//表示参考值的输入状态，1表示已输入，0表示未输入
status CCalibrationView::CurStatusMess=Free;

void CCalibrationView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CBCGPChartExampleView::OnPaint()
	//SetBkMode(dc, BM_TRANSPARENT);
	

	//ShowStatusInfo();
	//ShowCalibrationInfo();
	//ShowOriCoefficient(hDlg, &hdc);



}


BOOL CCalibrationView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	return CBCGPChartExampleView::OnEraseBkgnd(pDC);
}

void CCalibrationView::OnInitialUpdate()
{
	CBCGPChartExampleView::OnInitialUpdate();
	// TODO:  在此添加专用代码和/或调用基类
	oldSysmode = systemcfg.mode;    //保存进入界面之前的模式
	haveeditcreate = false;
	Showtarget();
	InitCalibrationForm();
	InitCoeffcientForm();
	OnPaint();
}

BOOL CCalibrationView::InitCalibrationForm()
{
	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	m_CalibrationList.GetClientRect(&rect);
	m_CalibrationList.SetRowHeigt(20);
	// 为列表视图控件添加全行选中和栅格风格   
	m_CalibrationList.SetExtendedStyle(m_CalibrationList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	
	// 为PLT列表视图控件添加四列
	m_CalibrationList.InsertColumn(0, _T("选择"), LVCFMT_CENTER, rect.Width() *1/ 16, 0);
	m_CalibrationList.InsertColumn(1, _T("操作者"), LVCFMT_CENTER, rect.Width()*2 /16, 1);
	m_CalibrationList.InsertColumn(2, _T("测试日期"), LVCFMT_CENTER, rect.Width()* 3/ 16, 2);
	m_CalibrationList.InsertColumn(3, _T("WBC"), LVCFMT_CENTER, rect.Width() *2/ 16, 3);
	m_CalibrationList.InsertColumn(4, _T("RBC"), LVCFMT_CENTER, rect.Width() *2/ 16, 4);
	m_CalibrationList.InsertColumn(5, _T("HGB"), LVCFMT_CENTER, rect.Width() *2/ 16, 5);
	m_CalibrationList.InsertColumn(5, _T("MCV"), LVCFMT_CENTER, rect.Width() *2/ 16, 6);
	m_CalibrationList.InsertColumn(5, _T("PLT"), LVCFMT_CENTER, rect.Width() *2/ 16, 7);

	// 在PLT列表视图控件中插入列表项，并设置列表子项文本
	m_CalibrationList.InsertItem(0, _T(""));
	m_CalibrationList.SetItemText(0, 0, _T("1"));
	//m_CalibrationList.SetItemText(0, 2, _T("10^9/L"));
	m_CalibrationList.InsertItem(1, _T(""));
	m_CalibrationList.SetItemText(1, 0, _T("2"));
	//m_CalibrationList.SetItemText(1, 2, _T("fL"));
	m_CalibrationList.InsertItem(2, _T(""));
	m_CalibrationList.SetItemText(2, 0, _T("3"));
	//m_CalibrationList.SetItemText(2, 2, _T("fL"));
	m_CalibrationList.InsertItem(3, _T(""));
	m_CalibrationList.SetItemText(3, 0, _T("4"));
	//m_CalibrationList.SetItemText(3, 2, _T("%"));
	m_CalibrationList.InsertItem(4, _T(""));
	m_CalibrationList.SetItemText(4, 0, _T("5"));
	//m_CalibrationList.SetItemText(4, 2, _T("%"));

	return TRUE;
}


BOOL CCalibrationView::InitCoeffcientForm()
{

	CRect rect;
	// 获取编程语言列表视图控件的位置和大小   
	m_CoefficientList.GetClientRect(&rect);
	m_CoefficientList.SetRowHeigt(20);
	// 为列表视图控件添加全行选中和栅格风格   
	m_CoefficientList.SetExtendedStyle(m_CoefficientList.GetExtendedStyle() |LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);


	// 为PLT列表视图控件添加四列
	m_CoefficientList.InsertColumn(0, _T(""), LVCFMT_CENTER, rect.Width() * 3 / 8, 0);
	m_CoefficientList.InsertColumn(1, _T("WBC"), LVCFMT_CENTER, rect.Width() * 1 / 8, 1);
	m_CoefficientList.InsertColumn(2, _T("RBC"), LVCFMT_CENTER, rect.Width() * 1 / 8, 2);
	m_CoefficientList.InsertColumn(3, _T("HGB"), LVCFMT_CENTER, rect.Width() * 1 / 8, 3);
	m_CoefficientList.InsertColumn(4, _T("MCV"), LVCFMT_CENTER, rect.Width() * 1 / 8, 4);
	m_CoefficientList.InsertColumn(5, _T("PLT"), LVCFMT_CENTER, rect.Width() * 1 / 8, 5);

	// 在PLT列表视图控件中插入列表项，并设置列表子项文本
	m_CoefficientList.InsertItem(0, _T("靶值  (请在表格中输入靶值)"));
	//m_CoefficientList.InsertItem(0, _T(""));
	m_CoefficientList.InsertItem(1, _T("平均值"));
	m_CoefficientList.InsertItem(2, _T("CV值"));
	m_CoefficientList.InsertItem(3, _T("当前系数"));
	m_CoefficientList.InsertItem(4, _T("新系数"));

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

void CCalibrationView::OnBnClickedManualCalibrationSave()
{

	CString calibrationtemp[4][5];
	GetDlgItem(IDC_WBC_TARGET)->GetWindowText(calibrationtemp[TestMode][0]);
	GetDlgItem(IDC_RBC_TARGET)->GetWindowText(calibrationtemp[TestMode][1]);
	GetDlgItem(IDC_HGB_TARGET)->GetWindowText(calibrationtemp[TestMode][2]);
	GetDlgItem(IDC_MCV_TARGET)->GetWindowText(calibrationtemp[TestMode][3]);
	GetDlgItem(IDC_PLT_TARGET)->GetWindowText(calibrationtemp[TestMode][4]);
	for (int i = 0; i < 5; i++)
	{
		systemcfg.calibration[TestMode][i] = _wtof(calibrationtemp[TestMode][i]);
	}
	WriteSystemcfgFile();
	// TODO:  在此添加控件通知处理程序代码
	/*unsigned int		i;
	CString			buffer[6] = {"0"};
	uchar			num = 0;
	USES_CONVERSION;
	for (i = IDC_WBC_TARGET; i <= IDC_PLT_TARGET; i++)
	{
		GetDlgItem(i)->GetWindowText(buffer[i-IDC_WBC_TARGET]);
		buffer[5] = '\0';
		//ori: num = i - IDC_AUTOCALIB_BASE
		//之前定标因子恒为0.7，估计问题出于此处
		num = i - IDC_WBC_TARGET;
		strcpy((char*)ref_ac[num],W2A( buffer[i - IDC_WBC_TARGET]));

		if (atof((const char*)ref_ac[num]) <= 0 || atof((const char*)ref_ac[num]) > 1000)
		{
			if (systemcfg.language == CHINESE)
				MessageBox(L"靶值输入错误!\n请重新输入!", L"警告!");
			return ;
		}
	}
	ref_flag = 1;*/


	//CManualCalibrationView m_manualcalibrationdlg;
	//if (m_manualcalibrationdlg.DoModal()==IDOK)
	//{
	//	Showtarget();
	//	UpdateTargetvalue();
	//}
}

/*************************处理数据*********************************
CurCalMode  测试模式 0:全血+CBC5DIFF,1:全血+CBC,2:预稀释+CBC5DIFF,3:预稀释+CBC；
ResultBuff  五次测试结果
CVBuff	变异系数CV
CoeBuff	最后的校正系数；
ItemType 五项数据的编号

**************************************************/
void CCalibrationView::DealWithData(uchar CurCalMode, CString ResultBuff[5], CString MeanBuff[5], uchar CVBuff[5], uchar CoeBuff[5], int ItemType,int meanIndex)
//void CCalibrationView::DealWithData(uchar CurCalMode, CString ResultBuff[5],  uchar CVBuff[5], uchar CoeBuff[5], int ItemType)

{
	unsigned int 	i;
	uchar 		cal_fail = 0;
	uchar 		modeTemp = CurCalMode;
	double 		SUM = 0.0, CV = 0.0, SD = 0.0, MEAN = 0.0, ftmp = 0.0, COE = 0.0;

	double 		MAX, MIN;

	MAX = MIN =_wtof(ResultBuff[0]);

	for (i = 0; i < ac_index; i++)
	{
		if (ResultBuff[i][0] == '*')	//该次测试数据有问题，所以在DataProcess的时候显示为*号
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
		Mean[meanIndex].Format(L"%.2lf", MEAN);
		for (i = 0; i < ac_index; i++)
		{
			ftmp = _wtof(ResultBuff[i]);
			SD += (ftmp - MEAN)*(ftmp - MEAN);
		}
		SD /= 4;
		SD = sqrt(SD);
		if (MEAN < 0.00001)	//保证除法的除数不为0
		{
			sprintf((char*)CVBuff, "*.**");
			sprintf((char*)CoeBuff, "***");
		}
		else
		{
			CV = SD * 100 / MEAN;
			if (CV < 100.0)	//超过100wbc_cvbuff就存不起来了，字符数组只能存100.00以下的
			{
				sprintf((char*)CVBuff, "%.2f", CV);
			}
			else
			{
				sprintf((char*)CVBuff, "*.**");
			}
			if (CV < 4.0)		//有什么依据没有4 xx22
			//if (CV<40)
			{
				COE = atof((const char*)ref_ac[ItemType])*systemcfg.calibration[modeTemp][ItemType] / MEAN;	//原有系数的基础上再乘以一个新系数

				if (COE > 1.30)		//依据是什么
					COE = 1.30;
				else if (COE < 0.70)	//依据是什么
					COE = 0.70;
				systemcfg.calibration[modeTemp][ItemType] = COE;
				//_tcscpy();
				sprintf((char*)CoeBuff, "%.2lf", COE);
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
	DealWithData(CurCalMode, wbc_buff,Mean, wbc_cvbuff, wbc_coebuff, CAL_WBCF,0);
	//DealWithData(CurCalMode, wbc_buff, wbc_cvbuff, wbc_coebuff, CAL_WBCF);
}

void CCalibrationView::DealWithRBC(uchar CurCalMode)
{
	DealWithData(CurCalMode, rbc_buff, Mean, rbc_cvbuff, rbc_coebuff, CAL_RBCF, 1);
	//DealWithData(CurCalMode, rbc_buff,  rbc_cvbuff, rbc_coebuff, CAL_RBCF);
}

void CCalibrationView::DealWithHGB(uchar CurCalMode)
{
	DealWithData(CurCalMode, hgb_buff, Mean, hgb_cvbuff, hgb_coebuff, CAL_HGBF, 2);
	//DealWithData(CurCalMode, hgb_buff, hgb_cvbuff, hgb_coebuff, CAL_HGBF);
}

void CCalibrationView::DealWithMCV(uchar CurCalMode)
{
	DealWithData(CurCalMode, mcv_buff, Mean, mcv_cvbuff, mcv_coebuff, CAL_MCVF, 3);
	//DealWithData(CurCalMode, mcv_buff,  mcv_cvbuff, mcv_coebuff, CAL_MCVF);
}

void CCalibrationView::DealWithPLT(uchar CurCalMode)
{
	DealWithData(CurCalMode, plt_buff, Mean, plt_cvbuff, plt_coebuff, CAL_PLTF, 4);
	//DealWithData(CurCalMode, plt_buff, plt_cvbuff, plt_coebuff, CAL_PLTF);
}

void CCalibrationView::OnAutoCalibrateStart()
{
	// TODO:  在此添加控件通知处理程序代码
	
}

//获取定标靶值
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
			nametemp[i] += "靶值为空";
			MessageBox(nametemp[i]);
			return FALSE;
		}
		strcpy((char*)ref_ac[i], W2A(temp[i]));
		if ((_wtof(temp[i]) <= 0) && (_wtof(temp[i]) > 1000))
		{
			if (systemcfg.language == CHINESE)
				MessageBox(L"靶值输入错误!\n请重新输入!",L"警告!", MB_OK | MB_ICONINFORMATION);
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
		//5个定标参数	                     
		//strcpy((char*)wbc_buff[ac_index - 1], sampledata.wbcdata.wbc);
		//strcpy((char*)rbc_buff[ac_index - 1], sampledata.rbcdata.rbc);
		//strcpy((char*)hgb_buff[ac_index - 1], sampledata.rbcdata.hgb);
		//strcpy((char*)mcv_buff[ac_index - 1], sampledata.rbcdata.mcv);
		//strcpy((char*)plt_buff[ac_index - 1], sampledata.pltdata.plt);

		//wbc_buff[ac_index - 1].Format(L"%.2f",sampledata.wbcdata.wbc);
		//rbc_buff[ac_index - 1].Format(L"%.2f",sampledata.rbcdata.rbc);
		//hgb_buff[ac_index - 1].Format(L"%.2f",sampledata.rbcdata.hgb);
		//mcv_buff[ac_index - 1].Format(L"%.2f",sampledata.rbcdata.mcv);
		//plt_buff[ac_index - 1].Format(L"%.2f",sampledata.pltdata.plt);
		CString timeTemp;		
		time(&systime);
		caltime = localtime(&systime);		
		timeTemp.Format(L"%04d-%02d-%02d %02d : %02d", caltime->tm_year + 1900, caltime->tm_mon + 1, caltime->tm_mday, caltime->tm_hour, caltime->tm_min);
		
		CString name;
		switch (operator_right)
		{
		case  0:
			name = "Administrator";
			break;
		case 1:
			name = "Engineer";
			break;
		case 2:
			name = "Doctor";
			break;
		case 3:
			name = "Operator";
			break;
		default:
			name = "Sinnowa";
			break;
		}

		wbc_buff[ac_index - 1]=sampledata.wbcdata.wbc;
		rbc_buff[ac_index - 1]=sampledata.rbcdata.rbc;
		hgb_buff[ac_index - 1]=sampledata.rbcdata.hgb;
		mcv_buff[ac_index - 1]=sampledata.rbcdata.mcv;
		plt_buff[ac_index - 1]=sampledata.pltdata.plt;

		for (int i = 0; i < ac_index; i++)
		{
			m_CalibrationList.SetItemText(i, 1, name);
			m_CalibrationList.SetItemText(i, 2, timeTemp);
			m_CalibrationList.SetItemText(i,3, wbc_buff[i]);
			m_CalibrationList.SetItemText(i, 4, rbc_buff[i]);
			m_CalibrationList.SetItemText(i, 5, hgb_buff[i]);
			m_CalibrationList.SetItemText(i, 6, mcv_buff[i]);
			m_CalibrationList.SetItemText(i, 7, plt_buff[i]);
		}
	}
}

//更新并显示定标因子coe
void CCalibrationView::UpdateCalibrate()
{
	uchar CurCalMode;

	CurCalMode = systemcfg.mode;

	DealWithWBC(CurCalMode);
	DealWithRBC(CurCalMode);
	DealWithHGB(CurCalMode);
	DealWithMCV(CurCalMode);
	DealWithPLT(CurCalMode);

	CString str;
	
	str = wbc_cvbuff;
	m_CoefficientList.SetItemText(2, 1,str);
	str = rbc_cvbuff;
	m_CoefficientList.SetItemText(2, 2, str);
	str = hgb_cvbuff;
	m_CoefficientList.SetItemText(2, 3, str);
	str = mcv_cvbuff;
	m_CoefficientList.SetItemText(2, 4, str);
	str = plt_cvbuff;
	m_CoefficientList.SetItemText(2, 5, str);

	str = wbc_coebuff;
	m_CoefficientList.SetItemText(4, 1,str);
	str = rbc_coebuff;
	m_CoefficientList.SetItemText(4, 2, str);
	str = hgb_coebuff;
	m_CoefficientList.SetItemText(4, 3, str);
	str = mcv_coebuff;
	m_CoefficientList.SetItemText(4, 4, str);
	str = plt_coebuff;
	m_CoefficientList.SetItemText(4, 5, str);

	for (int i = 0; i < 5; i++){
		m_CoefficientList.SetItemText(1, i+1, Mean[i]);
	}



}

void CCalibrationView::AutoCalibrationRun()
{
	uchar CurCalMode;

	DSP_status = Busy;
	CurStatusMess = Busy;

	systemcfg.mode = TestMode;//因为WbcBasoAnalysis等函数需要用到测试模式(systemcfg.mode)		

	if (TestMode == WHOLEDIFF || TestMode == DILUENTDIFF)//预稀释5Diff的DSP流程和全血5Diff的DSP流程一样，只不过最后传到ARM的数据乘的因子不一样
		sdata_cmd[0] = SPI_CMD_CBC5DIFF_MODE;
	else if (TestMode == WHOLECBC || TestMode == DILUENTCBC)//预稀释CBC的DSP流程和全血CBC的DSP流程一样，只不过最后传到ARM的数据乘的因子不一样
		sdata_cmd[0] = SPI_CMD_CBC_MODE;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	rdata_state[0] = SPI_STATE_INFO_START;
	SetTimer(SLEEP_TIMER2, 50000, 0);
}


void CCalibrationView::OnCalibrationTest()
{
	// TODO:  在此添加控件通知处理程序代码

	if (!GetRefValue())
	{
		MessageBox(L"请输入靶值!", L"警告!");
		return;
	}
	if (1 == ref_flag && ac_index < 5)
		AutoCalibrationRun();


	///************************以下为测试部分代码************************/
	//initData();
	//ac_index = 5;
	//
	//
	//UpdateCalibrate();



}


void CCalibrationView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

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
		SendMessage(WM_ACKSPI, rdata_state[0], 0);//将查询的状态发送到SPI消息响应处理
		//SendMessage(MSG_ACKSPI, rdata_state[0], 0);//将查询的状态发送到SPI消息响应处理
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
		//DSP测试数据准备好
	case SPI_STATE_DATAISOK:
		if (WAITING_DATA == PC_status)//逻辑上保证只接收数据一次，而不是重复接收
		{
			KillTimer(POLLTIME);

			m_datatrans.GetNormalData_BASO(&sampledata);
			m_datatrans.GetNormalData_RBC(&sampledata);
			m_datatrans.GetNormalData_PLT(&sampledata);
			m_datatrans.GetNormalData_HGB();
			//数据分析
			{
				uchar IsSuper = 1;
				m_dataprocess.WbcBasoAnalysis(&sampledata, &IsSuper);
				m_dataprocess.HgbAnalysis(&sampledata);		//必须放在BASO分析前面
				m_dataprocess.RbcAnalysis(&sampledata, &IsSuper);
				m_dataprocess.PltAnalysis(&sampledata);
			}
			ac_index += 1;

			CurStatusMess = Free;
			//此处要更新数据

			ShowCalibrationInfo();
			if (ac_index == 5)
				UpdateCalibrate();


			//刷新图形等待流程结束
			PC_status = WAITING_TEST_OVER;
			SetTimer(POLLTIME, SPI_POLL_TIME3000,0);
		}
		break;
		//测试过程结束
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
	Item = pEditCtrl->iItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
	SubItem = pEditCtrl->iSubItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
	createdit->Create(ES_AUTOHSCROLL | WS_CHILD | ES_LEFT | ES_WANTRETURN,
		CRect(0, 0, 0, 0), this, IDC_EDIT_CREATEID);//创建编辑框对象,IDC_EDIT_CREATEID为控件ID号3000，在文章开头定义
	havecreat = true;
	createdit->SetFont(this->GetFont(), FALSE);//设置字体,不设置这里的话上面的字会很突兀的感觉
	createdit->SetParent(&m_CoefficientList);//将list control设置为父窗口,生成的Edit才能正确定位,这个也很重要
	CRect  EditRect;
	m_CoefficientList.GetSubItemRect(e_Item, e_SubItem, LVIR_LABEL, EditRect);//获取单元格的空间位置信息
	EditRect.SetRect(EditRect.left + 1, EditRect.top + 1, EditRect.left + m_CoefficientList.GetColumnWidth(e_SubItem) - 1, EditRect.bottom - 1);//+1和-1可以让编辑框不至于挡住列表框中的网格线
	CString strItem = m_CoefficientList.GetItemText(e_Item, e_SubItem);//获得相应单元格字符
	createdit->SetWindowText(strItem);//将单元格字符显示在编辑框上
	createdit->MoveWindow(&EditRect);//将编辑框位置放在相应单元格上
	createdit->ShowWindow(SW_SHOW);//显示编辑框在单元格上面
	createdit->SetFocus();//设置为焦点 
	createdit->SetSel(-1);//设置光标在文本框文字的最后
}

void CCalibrationView::distroyEdit(CListCtrl *list, CEdit* distroyedit, int &Item, int &SubItem)
{
	CString meditdata;
	distroyedit->GetWindowTextW(meditdata);
	list->SetItemText(Item, SubItem, meditdata);//获得相应单元格字符
	distroyedit->DestroyWindow();//销毁对象，有创建就要有销毁，不然会报错
}

void CCalibrationView::OnNMClickCoefficientList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	NM_LISTVIEW  *pEditCtrl = (NM_LISTVIEW *)pNMHDR;
	printf("行：%d，列：%d\n", pEditCtrl->iItem, pEditCtrl->iSubItem);
	if (pEditCtrl->iItem == -1)//点击到非工作区
	{
		if (haveeditcreate == true)//如果之前创建了编辑框就销毁掉
		{
			distroyEdit(&m_CoefficientList, &m_WBCEdit, e_Item, e_SubItem);//销毁单元格编辑框对象
			haveeditcreate = false;
		}
	}
	else if( (pEditCtrl->iItem==0)&&(pEditCtrl->iSubItem != 0))
	{
		if (haveeditcreate == true)
		{
			if (!(e_Item == pEditCtrl->iItem && e_SubItem == pEditCtrl->iSubItem))//如果点中的单元格不是之前创建好的
			{
				distroyEdit(&m_CoefficientList, &m_WBCEdit, e_Item, e_SubItem);
				haveeditcreate = false;
				createEdit(pEditCtrl, &m_WBCEdit, e_Item, e_SubItem, haveeditcreate);//创建编辑框
			}
			else//点中的单元格是之前创建好的
			{
				m_WBCEdit.SetFocus();//设置为焦点 
			}
		}
		else
		{
			e_Item = pEditCtrl->iItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
			e_SubItem = pEditCtrl->iSubItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
			createEdit(pEditCtrl, &m_WBCEdit, e_Item, e_SubItem, haveeditcreate);//创建编辑框
		}
	}
	else
	{
		if (haveeditcreate == true)//如果之前创建了编辑框就销毁掉
		{
			distroyEdit(&m_CoefficientList, &m_WBCEdit, e_Item, e_SubItem);
			haveeditcreate = false;
		}
	}
	*pResult = 0;
}

//将选择的模式保存到变量
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
	// TODO:  在此添加控件通知处理程序代码
	Showtarget();
}


void CCalibrationView::OnBnClickedAutoModeRadio2()
{
	// TODO:  在此添加控件通知处理程序代码
	Showtarget();
}


void CCalibrationView::OnBnClickedAutoTestmodeRadio()
{
	// TODO:  在此添加控件通知处理程序代码
	Showtarget();
}

void CCalibrationView::OnBnClickedAutoTestmodeRadio2()
{
	// TODO:  在此添加控件通知处理程序代码
	Showtarget();
}


void CCalibrationView::initData(){
	//_tcscpy(items_shortname[i].GetBuffer(items_shortname_temp[i].GetLength()+1), items_shortname_temp[i]);

	//CString wbc_buff_temp[5] = { "15.43", "3.22", "97.6", "90.8", "112" };
	//CString rbc_buff_temp[5] = { "15.56", "3.22", "98.3", "111.7", "159" };
	//CString hgb_buff_temp[5] = { "15.73", "3.22", "102.3", "82.6", "105" };
	//CString mcv_buff_temp[5] = { "13.97", "3.53", "108.00", "100.1", "160" };
	//CString plt_buff_temp[5] = { "0.00", "2.54", "117.8", "87.3", "153" };

	USES_CONVERSION;
	CString ref_ac_temp[5] = {"12.5","3.14","104.8","94.5","137.8"};
	CString wbc_buff_temp[5] = { "15.43", "15.56", "15.73", "13.97", "0.00" };
	CString rbc_buff_temp[5] = { "3.22", "3.22","3.22", "3.53",  "2.54"   };
	CString hgb_buff_temp[5] = { "97.6", "98.3", "102.3","108.00" , "117.8"};
	CString mcv_buff_temp[5] = { "90.8", "111.7", "82.6", "100.1" , "87.3"};
	CString plt_buff_temp[5] = { "112", "159",  "105", "160", "153" };

	for (int i = 0; i < 5; i++){
		strcpy((char*)ref_ac[i], W2A(ref_ac_temp[i]));
		_tcscpy(wbc_buff[i].GetBuffer(wbc_buff[i].GetLength() + 1), wbc_buff_temp[i]);
		_tcscpy(rbc_buff[i].GetBuffer(rbc_buff[i].GetLength() + 1), rbc_buff_temp[i]);
		_tcscpy(hgb_buff[i].GetBuffer(hgb_buff[i].GetLength() + 1), hgb_buff_temp[i]);
		_tcscpy(mcv_buff[i].GetBuffer(mcv_buff[i].GetLength() + 1), mcv_buff_temp[i]);
		_tcscpy(plt_buff[i].GetBuffer(plt_buff[i].GetLength() + 1), plt_buff_temp[i]);
	}	
}




void CCalibrationView::OnBnClickedPrintCali()
{
	PRINTDLG pd;
	// Initialize PRINTDLG
	ZeroMemory(&pd, sizeof(PRINTDLG));
	pd.lStructSize = sizeof(PRINTDLG);
	pd.hwndOwner = NULL;
	pd.hDevMode = NULL;     // Don't forget to free or store hDevMode
	pd.hDevNames = NULL;     // Don't forget to free or store hDevNames
	pd.Flags = PD_USEDEVMODECOPIESANDCOLLATE | PD_RETURNDC;
	pd.nCopies = 1;
	pd.nFromPage = 0xFFFF;
	pd.nToPage = 0xFFFF;
	pd.nMinPage = 1;
	pd.nMaxPage = 0xFFFF;

	//PrintDlg(&pd);
	if (PrintDlg(&pd) == TRUE)
	{
		// GDI calls to render output. 
		DOCINFO di;
		ZeroMemory(&di, sizeof(DOCINFO));
		di.cbSize = sizeof(DOCINFO);
		di.lpszDocName = _T("NewDoc");

		StartDoc(pd.hDC, &di);
		CTime time;
		CDC pDC;
		CPen penBlack;
		CString str;
		CFont font;
		CString cs[5];
		//CFont *poldfont;
		pDC.Attach(pd.hDC);
		font.CreateFont(150, 60, 0, 0, 400, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, _T("Arial"));
		penBlack.CreatePen(PS_SOLID, 15, RGB(0, 0, 0));
		StartPage(pd.hDC);
		CFont *poldfont = pDC.SelectObject(&font);
		pDC.TextOutW(1900, 250, L"定 标 因 子 参 数");
		pDC.SelectObject(poldfont);
		CPen *poldPen = pDC.SelectObject(&penBlack);
		pDC.MoveTo(500, 500);
		pDC.LineTo(4500, 500);
		pDC.SelectObject(poldPen);

		pDC.TextOutW(2000, 1500, L"模式");
		pDC.TextOutW(2500, 1500, L"参数");
		pDC.TextOutW(2000, 1750, L"WBC:");
		pDC.TextOutW(2000, 2250, L"RBC:");
		pDC.TextOutW(2000, 2750, L"HGB:");
		pDC.TextOutW(2000, 3250, L"MCV:");
		pDC.TextOutW(2000, 3750, L"PLT:");
		for (int i = 0; i < 5; i++)
		{
			cs[i].Format(L"%.2f", systemcfg.calibration[systemcfg.mode][i]);
			pDC.TextOutW(2500, 1750 + 500 * i, cs[i]);
		}
		if (systemcfg.mode == 0)
		{
			pDC.TextOutW(500, 750, L"模式:");
			pDC.TextOutW(1000, 750, L"全血");
			pDC.TextOutW(500, 1000, L"观测模式:");
			pDC.TextOutW(1000, 1000, L"CBC+5DIFF");
		}
		else if (systemcfg.mode == 1)
		{
			pDC.TextOutW(1000, 750, L"模式:");
			pDC.TextOutW(1250, 750, L"全血");
			pDC.TextOutW(1000, 1000, L"观测模式:");
			pDC.TextOutW(1250, 1000, L"CBC");
		}
		else if (systemcfg.mode == 2)
		{
			pDC.TextOutW(1000, 750, L"模式:");
			pDC.TextOutW(1250, 750, L"预稀释");
			pDC.TextOutW(1000, 1000, L"观测模式:");
			pDC.TextOutW(1250, 1000, L"CBC+5DIFF");
		}
		else
		{
			pDC.TextOutW(1000, 750, L"模式:");
			pDC.TextOutW(1250, 750, L"预稀释");
			pDC.TextOutW(1000, 1000, L"观测模式:");
			pDC.TextOutW(1250, 1000, L"CBC");
		}
		str.Empty();
		time = CTime::GetCurrentTime();
		str = time.Format("%Y-%m-%d");
		pDC.TextOutW(3500, 6000, str);
		EndPage(pd.hDC);
		EndDoc(pd.hDC);

		// Delete DC when done.
		DeleteDC(pd.hDC);
	}
}
