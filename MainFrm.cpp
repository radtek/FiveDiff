//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a sample for BCGControlBar Library Professional Edition
// Copyright (C) 1998-2014 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "BCGPChartExample.h"
//
#include "MainFrm.h"
//
#include "BCGPChartExampleDoc.h"
#include "BCGPChartExampleView.h"
//#include "Includes_app.h"

// TODO: 添加界面
#include "LoginDlg.h"
#include "TestmainView.h"
#include "WorkSheetView.h"
#include "PatientInfoView.h"
#include "ResultManageView.h"
#include "DoctorInfoView.h"
#include "LogView.h"
#include "ResultListView.h"
#include "PatientResultView.h"
#include "ResultDetails.h"
#include "CalibrationView.h"
#include "Reagentmanagement2View.h"

//TODO:添加菜单界面
#include "ConfigSetView.h"
#include "SelfTestView.h"
#include "MotorTestView.h"
#include "ValveTestView.h"
#include "PerfusionView.h"
#include "CleanView.h"
#include "EmptyView.h"
#include "ConcentratecleanView.h"
#include "RecoilView.h"
#include "MicroperfusionView.h"
#include "AutocleanView.h"
#include "ReagentmanagementView.h"
//#include "QcFileSelectView.h"
//#include "ControlChooese.h"
#include "QualityControlView.h"
//#include "ThreadAS.h"
#include "ConstantCurrentView.h"
#include "HgbtestView.h"
#include "LmnetestView.h"
#include "SetMarkModeLMNEView.h"
#include "ReagentalarmView.h"
#include "BASOLandmarkView.h"
#include "LocationquantitativeView.h"
#include "TemperaturecontrolView.h"
#include "FaultstatisticsView.h"
#include "FilesOperation.h"
#include "WorkstationView.h"
#include "Hook.h"
#include "BackupView.h"
#include "LanguageChoose.h"
#include "MultiLangTest.h"

//#include "EnumSerial.h"
#include <array>
TransferWindow TW;
static LPCTSTR viewTypes[] =
{	
	_T("主测试"),
	_T("试剂容量"),
	_T("质量控制"),
	_T("数据管理"),
	_T("定标"),
	_T("工作表"),
	_T("医生信息管理"),
	_T("病人信息管理"), 
	_T("日志"),
	_T("联系我们"),
	_T("工作站模式"),
	_T("文件管理"),
	_T("病理分析"),
};

static CDemoFeature features[] =
{
	CDemoFeature(0, CDemoFeature::TestmainView, _T("TestmainView"), RUNTIME_CLASS(CTestmainView)),
	CDemoFeature(1, CDemoFeature::ReagentmanagementView, _T("ReagentmanagementView"), RUNTIME_CLASS(CReagentmanagement2View)),
	//CDemoFeature(2, CDemoFeature::QcFileSelectView, _T("CQcFileSelectView"), RUNTIME_CLASS(CQcFileSelectView)),
	CDemoFeature(2, CDemoFeature::QualityControlView, _T("QualityControlView"), RUNTIME_CLASS(CQualityControlView)),
	//CDemoFeature(3, CDemoFeature::ResultListView, _T("ResultListView"), RUNTIME_CLASS(CResultListView)),
	CDemoFeature(3, CDemoFeature::ResultManageView, _T("ResultManage"), RUNTIME_CLASS(CResultManageView)),
	CDemoFeature(4, CDemoFeature::CalibtationView, _T("CalibrationView"), RUNTIME_CLASS(CCalibrationView)),
	CDemoFeature(5, CDemoFeature::WorkSheetView, _T("WorkSheetView"), RUNTIME_CLASS(CWorkSheetView)),
	CDemoFeature(6, CDemoFeature::DoctorInfoView, _T("DoctorInfoView"), RUNTIME_CLASS(CDoctorInfoView)),
	CDemoFeature(7, CDemoFeature::PatientInfoView, _T("PatientInfoView"), RUNTIME_CLASS(CPatientInfoView)),
	CDemoFeature(8, CDemoFeature::LogView, _T("LogView"), RUNTIME_CLASS(CLogView)),
	//CDemoFeature(9, CDemoFeature::PatientResultView, _T("PatientResultView"), RUNTIME_CLASS(CPatientResultView)),
	CDemoFeature()
};

CRect m_progressrect;
HWND mainhwnd;
CConfigSetView* SetPTR;
void CALLBACK USBIO_Status_Nofiy(BYTE iDevIndex, DWORD	iStatus)
{
	TRACE(L"\n###usb监听回调2\n");
	PostMessage(mainhwnd, WM_USB_STATUS, iDevIndex, iStatus);
}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CQualityTestView m_QualityTestPage;
CQcXTestView m_QcXTestPage;
CQcXrTestView m_QcXrTestPage;
class CToolbarLabel : public CBCGPToolbarButton  
{
	DECLARE_SERIAL(CToolbarLabel)

public:
	CToolbarLabel (UINT nID = 0, LPCTSTR lpszText = NULL);

	virtual void OnDraw (CDC* pDC, const CRect& rect, CBCGPToolBarImages* pImages, 
						 BOOL bHorz = TRUE, BOOL bCustomizeMode = FALSE,						
						 BOOL bHighlight = FALSE,						
						 BOOL bDrawBorder = TRUE, 
						 BOOL bGrayDisabledButtons = TRUE);
};

IMPLEMENT_SERIAL(CToolbarLabel, CBCGPToolbarButton, 1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CToolbarLabel::CToolbarLabel (UINT nID, LPCTSTR lpszText)
{
	if (lpszText != NULL)	
	{		
		m_strText = lpszText;	
	}	

	m_bText = TRUE;
	m_nID = nID;
	m_iImage = -1;
}

void CToolbarLabel::OnDraw (CDC* pDC, const CRect& rect, CBCGPToolBarImages* pImages, 
							  BOOL bHorz, BOOL /*bCustomizeMode*/, BOOL /*bHighlight*/,	
							  BOOL /*bDrawBorder*/,	BOOL /*bGrayDisabledButtons*/)
{
	UINT nStyle = m_nStyle;	
	m_nStyle &= ~TBBS_DISABLED;

	CBCGPToolbarButton::OnDraw (pDC, rect, pImages, bHorz, FALSE,
								FALSE, FALSE, FALSE);

	m_nStyle = nStyle;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)


BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_BACK, OnViewBack)
	ON_UPDATE_COMMAND_UI(ID_VIEW_BACK, OnUpdateViewBack)
	ON_COMMAND(ID_VIEW_FORWARD, OnViewForward)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FORWARD, OnUpdateViewForward)
	ON_MESSAGE(WM_USB_STATUS, USB_StatusChange)
	ON_MESSAGE(MSG_ACKSPI, OnMSG_ACKSPI)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_TEST_MODE_COMBO, OnTestModeCombo)
	ON_CBN_SELENDOK(ID_TEST_MODE_COMBO, OnTestModeCombo)
	ON_COMMAND_RANGE(ID_SHORTCUT_FIRST, ID_SHORTCUT_LAST, OnOutlookBarShortcut)
	ON_MESSAGE(UM_REDRAW, OnRedraw)
	ON_MESSAGE(WM_TESTSWITCHON, &CMainFrame::OnTestSwitchOn)
	ON_COMMAND(ID_32911, &CMainFrame::OnStartup)
	ON_WM_TIMER()
	ON_COMMAND(ID_32912, &CMainFrame::OnBlanktest)
	ON_COMMAND(ID_32913, &CMainFrame::OnMainTest)
	ON_COMMAND(ID_32914, &CMainFrame::OnConfigSet)
	ON_COMMAND(ID_SELFTEST, &CMainFrame::OnSelftest)
	ON_COMMAND(ID_MOTORCHECK, &CMainFrame::OnMotorcheck)
	ON_COMMAND(ID_VALVECHECK, &CMainFrame::OnValvecheck)
	ON_COMMAND(ID_PERFUSION, &CMainFrame::OnPerfusion)
	ON_COMMAND(ID_CLEAN, &CMainFrame::OnClean)
	ON_COMMAND(ID_EMPTY, &CMainFrame::OnEmpty)
	ON_COMMAND(ID_CONCENTRATEDCLEAN, &CMainFrame::OnConcentratedclean)
	ON_COMMAND(ID_RECOIL, &CMainFrame::OnRecoil)
	ON_COMMAND(ID_MICRO_PERFUSION, &CMainFrame::OnMicroPerfusion)
	ON_COMMAND(ID_AUTOCLEAN, &CMainFrame::OnAutoclean)
	ON_COMMAND(ID_REAGENT_MANAGEMENT, &CMainFrame::OnReagentManagement)
	ON_COMMAND(ID_MAINTENANCE, &CMainFrame::OnMaintenance)
	ON_COMMAND(ID_SOURCE_MANAGEMENT, &CMainFrame::OnSourceManagement)
	ON_COMMAND(ID_HGB_TEST, &CMainFrame::OnHgbTest)
	ON_COMMAND(ID_LMNE_TEST, &CMainFrame::OnLmneTest)
	ON_COMMAND(ID_CLEAN_TANK, &CMainFrame::OnCleanTank)
	ON_COMMAND(ID_LOCATION_QUANTITATIVE, &CMainFrame::OnLocationQuantitative)
	ON_COMMAND(ID_GRAPHIC_DEBUG, &CMainFrame::OnGraphicDebug)
	ON_COMMAND(ID_FAULT_STATISTICS, &CMainFrame::OnFaultStatistics)
	ON_COMMAND(ID_REAGENT_ALARM_SET, &CMainFrame::OnReagentAlarmSet)
	ON_COMMAND(ID_TEMPERATURE_CONTROL, &CMainFrame::OnTemperatureControl)
	ON_COMMAND(ID_BASO_LANDMARK_SET, &CMainFrame::OnBasoLandmarkSet)
	ON_COMMAND(ID_LMNE_LANDMARK_PATTERN, &CMainFrame::OnLmneLandmarkPattern)
	ON_COMMAND(ID_32978, &CMainFrame::OnQualityTest)
	ON_COMMAND(ID_CONNECTDSP, &CMainFrame::OnConnectDSP)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SHORTCUT_FIRST, ID_SHORTCUT_LAST, OnUpdateOutlookBarShortcut)
	ON_WM_CLOSE()

	ON_COMMAND(ID_DATABASE_IMPORT, &CMainFrame::OnDatabaseImport)
	ON_COMMAND(ID_DATABASE_BACKUP, &CMainFrame::OnDatabaseBackup)
	ON_COMMAND(ID_DATABASE_CLEARUP, &CMainFrame::OnDatabaseClearup)
	ON_COMMAND(ID_WORKSHEET, &CMainFrame::OnWorksheet)
	ON_COMMAND(ID_LOCK_KEYBOARD, &CMainFrame::OnLockKeyboard)
	ON_COMMAND(ID_UNLOCK_KEYBOARD, &CMainFrame::OnUnlockKeyboard)
	ON_COMMAND(ID_BACKUPSYSTEM, &CMainFrame::OnBackupsystem)
	
	
	ON_MESSAGE(WM_REAGENT_ALARM, &CMainFrame::OnReagentAlarm)
	ON_COMMAND(ID_LANGUAGE_CHOOSE, &CMainFrame::OnLanguageChoose)
	ON_COMMAND(ID_MULTILANG_TEST, &CMainFrame::OnMultilangTest)
END_MESSAGE_MAP()

//状态栏添加状态信息需要在此处添加内容，并正确初始化
static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_REAGENT_ALARM,		//试剂报警
	ID_DEVICESTATUS,		//设备状态
	IDS_PROGRESS,			//进度条
	ID_INDICATOR_OPERATOR,	//Show the operator
	ID_INDICATOR_DATE,		//Show the date
	ID_INDICATOR_CLOCK,     //show the time
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
	
};


/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction
int			connectionState;//连接状态，0，就绪；1，usb已连接，下位机心跳中；2，USB已连接，未检测到下位机；3，USB已断开
CMainFrame::CMainFrame()
{
	m_nCurrType = theApp.GetInt(_T("ViewType"), ID_SHORTCUT_FIRST);
	//m_nTestMode = theApp.GetInt(_T("TestMode"),0);//初始测试模式默认为WHOLEDIFF
	m_nTestMode = 0;
	//TRACE(L"#####m_nTestMode=%d#########\n", m_nTestMode);
	m_bAutoMenuEnable = TRUE;       //关键部分
}

CMainFrame::~CMainFrame()
{
	//KillTimer(SYSPARAM_TIMER);
	//KillTimer(POLL_TIMER);
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//SetMenu (NULL);//隐藏菜单栏

	//开启导航窗口中的前进后退键
	//m_wndToolBar.EnableNavigationButtons (ID_VIEW_BACK, ID_VIEW_FORWARD, 0, 0);

	// Detect color depth. 256 color toolbars can be used in the
	// high or true color modes only (bits per pixel is > 8):
	CClientDC dc (this);
	BOOL bIsHighColor = dc.GetDeviceCaps (BITSPIXEL) > 8;

	CBCGPToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES,
		bIsHighColor ? IDB_MENUIMAGES24 : 0);

	UINT uiToolbarHotID = bIsHighColor ? IDB_TOOLBAR_HC : 0;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME, uiToolbarHotID))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	//-----------------------
	// Setup toolbar buttons:
	//-----------------------
	CMenu menuView;
	menuView.LoadMenu (IDR_MENU_VIEW);

	m_wndToolBar.ReplaceButton (ID_TOOLBAR_VIEW, 
		CBCGPToolbarMenuButton ((UINT)-1, menuView.Detach (), -1, _T("视图")));

	m_wndToolBar.ReplaceButton (ID_COLOR_LABEL, 
		CToolbarLabel (ID_COLOR_LABEL, _T("测量模式: ")));

	CBCGPToolbarComboBoxButton comboButton(ID_TEST_MODE_COMBO,
		CImageHash::GetImageOfCommand(ID_TEST_MODE_COMBO, FALSE), CBS_DROPDOWNLIST);

	comboButton.AddItem(_T("WHOLEDIFF"));
	comboButton.AddItem(_T("WHOLECBC"));
	
	comboButton.AddItem(_T("DILUENTDIFF"));
	comboButton.AddItem(_T("DILUENTCBC"));

	comboButton.SelectItem(m_nTestMode < 0 ? (int)comboButton.GetCount() + m_nTestMode : m_nTestMode);//为何此处有这一句？+4有什么用？?
	//comboButton.SelectItem(_T("DILUENTCBC"));
	
	//int selectItem = comboButton.GetCurSel();

	//CString str1;
	//char* str;
	////GetDlgItemText(ID_TEST_MODE_COMBO,str);
	////str = comboButton.SelectItem.text;
	//itoa(selectItem, str, 10);
	//str1 = str;
	//MessageBox(str1);

	m_wndToolBar.ReplaceButton(ID_TEST_MODE_COMBO, comboButton);

	//m_wndToolBar.SetToolBarBtnText (m_wndToolBar.CommandToIndex (ID_CHART_EXPORT), NULL, TRUE, TRUE);
	//m_wndToolBar.SetToolBarBtnText (m_wndToolBar.CommandToIndex (ID_CHART_COPY), NULL, TRUE, TRUE);
	m_wndToolBar.SetToolBarBtnText (m_wndToolBar.CommandToIndex (ID_CONNECTDSP), NULL, TRUE, TRUE);

	m_wndToolBar.EnableCustomizeButton (TRUE, (UINT)-1, _T("More Items"));

	//-------------------
	// Create status bar:
	//-------------------
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
	
		return -1;      // fail to create
	}
	
	if (!CreateShortcutsBar())
	{

		TRACE0("Failed to create shortcuts bar\n");
		return -1;      // fail to create
	}


	if (!m_wndCaptionBar.Create(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, this,
		ID_VIEW_CAPTIONBAR, -1))
	{
		TRACE0("Failed to create caption bar\n");
		return -1;      // fail to create
	}

	m_wndCaptionBar.SetFlatBorder();	
	//m_wndCaptionBar.SetText(viewTypes[m_nCurrType - ID_SHORTCUT_FIRST]);
	m_wndCaptionBar.SetText(viewTypes[0]);
	///////////////////////////////////////////
	mainhwnd = GetSafeHwnd();

	DWORD dwScreenX, dwScreenY;
	dwScreenX = GetSystemMetrics(SM_CXSCREEN);
	dwScreenY = GetSystemMetrics(SM_CYSCREEN);

	if (m_spidev.open_spi() == 0)
	{
		connectionState = 1;
		m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_DEVICESTATUS), _T("USB设备已就绪"));
		::PostMessage(mainhwnd, WM_USB_STATUS, 0, 0x80);
		//m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_DEVICESTATUS), _T("设备已连接"));
		//m_wndStatusBar.SetPaneText(1, _T("设备已连接"),TRUE);//**##此处标记下位机连接状态，index应为1，待修改
		m_spidev.close_spi(0);
	}
	else
	{
		connectionState = 3;
		m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_DEVICESTATUS), _T("USB设备已断开"));
		::PostMessage(mainhwnd, WM_USB_STATUS, 0, 0 );
		//m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_DEVICESTATUS), _T("设备连接失败"));
		//m_wndStatusBar.SetPaneText(1, _T("设备连接失败"), TRUE);
	}
	m_wndStatusBar.SetPaneInfo(1, ID_REAGENT_ALARM, SBPS_NORMAL, dwScreenX * 1 / 7);

	m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_REAGENT_ALARM), _T("正常"));
	

	//SetTimer(POLL_TIMER, 1000,NULL);
	USBIO_SetUSBNotify(false, USBIO_Status_Nofiy);//监听USB插拔事件

	//hThread = CreateThread(NULL, 0, CreateSwitchDetechThread, LPVOID(this), 0, &dwThreadId);
	//if (hThread == NULL)
	//{
	//	MessageBox(L"CreateThread   failed.", L"main", MB_OK);
	//}
	//else
	//{
	//	OutputDebugString(L"prepare   post   message\r\n");
	//	Sleep(1000);//等待线程创建好了   
	//	PostThreadMessage(dwThreadId, WM_THREAD, 0, 0);//给线程发消息   
	//	OutputDebugString(L"Post   message   ok\r\n");
	//	CloseHandle(hThread);
	//}

	//m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_INDICATOR_OPERATOR), name); //Show the operator 

	m_wndStatusBar.SetPaneInfo(1, m_wndStatusBar.GetDlgCtrlID(), SBPS_NORMAL, dwScreenX * 1 / 7);//**##   1/2
	m_wndStatusBar.GetItemRect(1, &m_progressrect);

	CTime time;
	time = CTime::GetCurrentTime();
	CString s = time.Format("%H:%M:%S");
	CString s2 = time.Format("%Y-%m-%d");
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
	m_wndStatusBar.SetPaneInfo(2, m_wndStatusBar.GetDlgCtrlID(), SBPS_STRETCH, dwScreenX * 1 / 7);//**##   1/13
	m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_INDICATOR_OPERATOR), name); //Show the operator 
	
	m_wndStatusBar.SetPaneInfo(3, m_wndStatusBar.GetDlgCtrlID(), SBPS_STRETCH, dwScreenX * 1 / 10);//**##   1/30
	m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_INDICATOR_CLOCK), s); //Show the time 
	
	m_wndStatusBar.SetPaneInfo(4, m_wndStatusBar.GetDlgCtrlID(), SBPS_STRETCH, dwScreenX * 1 / 10);//**##   1/30
	m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_INDICATOR_DATE), s2); //Show the date
	

	SetTimer(CLOCK_TIMER, 1000, NULL);// Show the time in real time

	//创建时添加各视图窗口
	//AddFeatureGroup(_T("Overview"), 0);
	//AddFeatureGroup(_T("Overview"), 1);
	//AddFeatureGroup(_T("Overview"), 2);
	//AddFeatureGroup(_T("Overview"), 3);
	//AddFeatureGroup(_T("Overview"), 4);
	//AddFeatureGroup(_T("Overview"), 5);
	//AddFeatureGroup(_T("Overview"), 6);
	//AddFeatureGroup(_T("Overview"), 7);
	//AddFeatureGroup(_T("Overview"), 8);
	//AddFeatureGroup(_T("Overview"), 9);
	//系统参数初始化
	Syscfginit();
	Init();
	HANDLE   hThread = NULL;
	SendMutex = CreateMutex(NULL, FALSE, NULL);

	SetTimer(SYSPARAM_TIMER, 3000, 0);//3s
	//Sleep(9000);

	DWORD	 dwThreadId;
	hThread = CreateThread(NULL, 0, CreateHeartbeatThread, LPVOID(this), 0, &dwThreadId);//**!!此处在连接下位机需要释放
	
	
	//int				m_nSerialPortNum(0);// 串口计数 
	//CString           strSerialList[256];  // 临时定义 256 个字符串组 
	//CArray<SSerInfo, SSerInfo&>		asi;
	//EnumSerialPorts(asi, TRUE);// 参数为 TRUE 时枚举当前可以打开的串口， 
	//// 否则枚举所有串口 
	//m_nSerialPortNum = asi.GetSize();
	//for (int i = 0; i<m_nSerialPortNum;i++)
	//{
	//	CString str = asi[i].strFriendlyName;
	//	TRACE("---serialinfo:%s-------\n", str);
	//}

	//CMenu* mmenu = GetMenu();
	//CMenu* submenu = mmenu->GetSubMenu(1);
	//submenu->EnableMenuItem(ID_32911, MF_DISABLED);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style &= ~FWS_ADDTOTITLE;
	
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	WNDCLASS wndcls;

	if (GetClassInfo (AfxGetInstanceHandle (), cs.lpszClass, &wndcls))
	{
		HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE(IDR_MAINFRAME), RT_GROUP_ICON);
		HICON hIcon = ::LoadIcon(hInst, MAKEINTRESOURCE(IDR_MAINFRAME));
		cs.lpszClass = AfxRegisterWndClass (CS_DBLCLKS, wndcls.hCursor, wndcls.hbrBackground, hIcon);
	}
	cs.style &= ~FWS_ADDTOTITLE;
	return TRUE;
}

BOOL CMainFrame::CreateShortcutsBar()//创建左侧导航窗口
{
	CBCGPOutlookWnd::EnableAnimation();
	const int nInitialWidth = 150;
	const CString strCaption = _T("导航栏 :");

	if (!m_wndShortcutsBar.Create(strCaption, this,
		CRect(0, 0, nInitialWidth, nInitialWidth),
		ID_VIEW_OUTLOOKBAR, WS_CHILD | WS_VISIBLE | CBRS_LEFT))
	{
		TRACE0("Failed to create outlook bar\n");
		return FALSE;      // fail to create
	}

#ifdef _BCGSUITE_INC_
	CBCGPOutlookWnd* pShortcutsBarContainer = DYNAMIC_DOWNCAST(CBCGPOutlookWnd,
		m_wndShortcutsBar.GetUnderlyingWindow());
#else
	CBCGPOutlookWnd* pShortcutsBarContainer = DYNAMIC_DOWNCAST(CBCGPOutlookWnd,
		m_wndShortcutsBar.GetUnderlinedWindow());
#endif
	if (pShortcutsBarContainer == NULL)
	{
		TRACE0("Cannot get outlook bar container\n");
		return FALSE;
	}
	CBCGPToolBarImages images;
	images.SetImageSize(CSize(32, 32));

#ifdef _BCGSUITE_INC_
	const int dwDefaultToolbarStyle = AFX_DEFAULT_TOOLBAR_STYLE;

#if _MSC_VER < 1600
	BOOL bAlphaBlend = globalData.bIsOSAlphaBlendingSupport;
#else
	BOOL bAlphaBlend = TRUE;
#endif
#else
	const int dwDefaultToolbarStyle = (WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_HIDE_INPLACE);
	BOOL bAlphaBlend = globalData.bIsOSAlphaBlendingSupport;
#endif
	images.Load(bAlphaBlend ? IDB_SHORTCUTS32 : IDB_SHORTCUTS);
		//images.Load(_T("res/shortcuts32"));
			

m_wndShortcutsPane1.Create(&m_wndShortcutsBar, dwDefaultToolbarStyle, ID_SHORTCUTS_PANE_1);
	m_wndShortcutsPane1.SetOwner(this);
	m_wndShortcutsPane1.EnableTextLabels(1);
	m_wndShortcutsPane1.EnableDocking(CBRS_ALIGN_ANY);

	m_wndShortcutsPane1.AddButton(images.ExtractIcon(0), viewTypes[0], ID_SHORTCUT_1, -1, bAlphaBlend);
	m_wndShortcutsPane1.AddButton(images.ExtractIcon(1), viewTypes[1], ID_SHORTCUT_2, -1, bAlphaBlend);
	m_wndShortcutsPane1.AddButton(images.ExtractIcon(2), viewTypes[2], ID_SHORTCUT_3, -1, bAlphaBlend);
	m_wndShortcutsPane1.AddButton(images.ExtractIcon(3), viewTypes[3], ID_SHORTCUT_4, -1, bAlphaBlend);
	m_wndShortcutsPane1.AddButton(images.ExtractIcon(4), viewTypes[4], ID_SHORTCUT_5, -1, bAlphaBlend);
	//m_wndShortcutsPane1.AddButton(images.ExtractIcon(5), viewTypes[5], ID_SHORTCUT_6, -1, bAlphaBlend);
	m_wndShortcutsPane1.AddButton(images.ExtractIcon(6), viewTypes[6], ID_SHORTCUT_7, -1, bAlphaBlend);
//	m_wndShortcutsPane1.AddButton(images.ExtractIcon(7), viewTypes[7], ID_SHORTCUT_8, -1, bAlphaBlend);
//	m_wndShortcutsPane1.AddButton(images.ExtractIcon(8), viewTypes[8], ID_SHORTCUT_9, -1, bAlphaBlend);
//	m_wndShortcutsPane1.AddButton(images.ExtractIcon(9), viewTypes[9], ID_SHORTCUT_10, -1, bAlphaBlend);
//	m_wndShortcutsPane1.AddButton(images.ExtractIcon(10), viewTypes[10], ID_SHORTCUT_11, -1, bAlphaBlend);
//	m_wndShortcutsPane1.AddButton(images.ExtractIcon(11), viewTypes[11], ID_SHORTCUT_12, -1, bAlphaBlend);
//#ifndef _BCGSUITE_INC_
//	m_wndShortcutsPane1.AddButton(images.ExtractIcon(12), viewTypes[12], ID_SHORTCUT_12, -1, bAlphaBlend);
//#endif	
	pShortcutsBarContainer->AddTab(&m_wndShortcutsPane1, strCaption, (UINT)-1, FALSE);

#ifndef _BCGSUITE_INC_
	pShortcutsBarContainer->SetSingleTabStatic();
#endif
	AddFeatureGroup(_T("Overview"), 0);
	AddFeatureGroup(_T("Overview"), 1);
	AddFeatureGroup(_T("Overview"), 2);
	AddFeatureGroup(_T("Overview"), 3);
	AddFeatureGroup(_T("Overview"), 4);
	AddFeatureGroup(_T("Overview"), 5);
	AddFeatureGroup(_T("Overview"), 6);
	//AddFeatureGroup(_T("Overview"), 7);
	//AddFeatureGroup(_T("Overview"), 8);
	//AddFeatureGroup(_T("Overview"), 9);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnOutlookBarShortcut(UINT id)
{
	const int nViewType = id - ID_SHORTCUT_FIRST;
	
	m_wndCaptionBar.SetText(viewTypes[nViewType-1]);
	if (nViewType > 0 && AfxGetMainWnd() != NULL)
	{
		//TW.add_new_window(nViewType);
		((CMainFrame*)AfxGetMainWnd())->SelectView(nViewType);
	}
	m_nCurrType = id;
	theApp.WriteInt(_T("ViewType"), m_nCurrType);
	/***********************************************/
	//const int nViewType = id - ID_SHORTCUT_FIRST;

	//m_wndCaptionBar.SetText(viewTypes[nViewType]);

	//CBCGPChartExampleView* pActiveView =
	//	DYNAMIC_DOWNCAST(CBCGPChartExampleView, GetActiveView());
	//if (pActiveView != NULL)
	//{
	//	pActiveView->SetViewType(nViewType);
	//}

	//m_nCurrType = id;
	//theApp.WriteInt(_T("ViewTppe"), m_nCurrType);

}
CView* pNewView;

void CMainFrame::SelectView(int nID)  // 获取nID对应窗口，与当前窗口比较，不同则切换
{
	CWaitCursor wait;
	CurView = nID;
	pNewView = GetView(nID);
	if (pNewView == NULL)
	{
		//ASSERT(FALSE);
		return;
	}
	
	CView* pActiveView = GetActiveView();

	if (pActiveView == NULL)
	{
		return;
	}
	/*************调整部分代码**************/
	//pActiveView->ShowWindow(SW_SHOW);
	/***************************************/
	m_nCurrType = nID;


	if (pNewView != pActiveView)//原则上这句不能去掉
	{

		UINT temp = ::GetWindowLong(pActiveView->m_hWnd, GWL_ID);

		::SetWindowLong(pActiveView->m_hWnd, GWL_ID,
		::GetWindowLong(pNewView->m_hWnd, GWL_ID));

		::SetWindowLong(pNewView->m_hWnd, GWL_ID, temp);
		
		pActiveView->ShowWindow(SW_HIDE);
		pNewView->ShowWindow(SW_SHOW);
		
		if(nID==4)pNewView->OnInitialUpdate();
		

		SetActiveView(pNewView);
		
	}
	theApp.WriteInt(_T("ViewType"), m_nCurrType);
	PostMessage(UM_REDRAW);
}


CView* CMainFrame::GetView(int nID)
{
	if (m_arViews.GetSize() == 0)
	{
		const int nCount = GetFeatureCount();
		for (int i = 0; i < nCount; i++)
		{
			m_arViews.Add(NULL);
		}
	}
	int nIndex = nID - 1;

	if (nIndex < 0 || nIndex >= m_arViews.GetSize())
	{
		//ASSERT(FALSE);
		return NULL;
	}

	CView* pView = m_arViews[nIndex];
	if (pView != NULL)
	{
		return pView;
	}
	CRuntimeClass* pClass = GetFeatureViewRTI(nID);

	if (pClass == NULL)
	{	
		ASSERT(FALSE);
		return NULL;
	}

	ASSERT(pClass->IsDerivedFrom(RUNTIME_CLASS(CView)));//此处error，ControlChooese不是CView的子类
	pView = DYNAMIC_DOWNCAST(CView, pClass->CreateObject());

	ASSERT_VALID(pView);
	CDocument* pCurrentDoc = GetActiveDocument();

	CCreateContext newContext;
	newContext.m_pNewViewClass = NULL;
	newContext.m_pNewDocTemplate = NULL;
	newContext.m_pLastView = NULL;
	newContext.m_pCurrentFrame = NULL;
	newContext.m_pCurrentDoc = pCurrentDoc;

	if (!pView->Create(NULL, _T(""), (AFX_WS_DEFAULT_VIEW & ~WS_VISIBLE),
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST + nIndex, &newContext))//如果创建失败，则回收该指针，返回NULL
	{
		delete pView;
		return NULL;
	}
	pView->OnInitialUpdate();
	m_arViews.SetAt(nIndex, pView);//将新窗口保存在m_arViews,nIndex相应位置
	return pView;
}


void CMainFrame::UpdateCurrentView (int nViewType)
{
	m_nCurrType = nViewType;
	theApp.WriteInt (_T("ViewType"), m_nCurrType);
}


CRuntimeClass* CMainFrame::GetFeatureViewRTI(int id) const
{
	CDemoFeature* pItem = NULL;

	if (m_mapItems.Lookup(id, pItem))
	{
		return pItem->m_RTI;
	}

	return NULL;
}

void CMainFrame::GetFeatureName(int id, CString& strTitle) const
{
	CDemoFeature* pItem = NULL;

	if (m_mapItems.Lookup(id, pItem))
	{
		strTitle = pItem->m_strName;
	} 
	else
	{
		strTitle.Empty();
	}
}

CDemoFeature::Feature CMainFrame::GetFeature(int id) const
{
	CDemoFeature* pItem = NULL;

	if (m_mapItems.Lookup(id, pItem))
	{
		return pItem->m_Feature;
	}
	else
	{
		return CDemoFeature::BCGP_Unknown;
	}
}

void CMainFrame::AddFeatureGroup(LPCTSTR lpszName, int nGroupID)
{
	for (int i = 0;; i++)
	{
		CDemoFeature& feature = features[i];
		if (feature.m_nGroup == -1)
		{
			break;
		}

		if (feature.m_nGroup == nGroupID)
		{
			int id = GetFeatureCount() + 1;
			feature.m_id = id;
			m_mapItems.SetAt(id, &feature);
		}
	}
}

void CMainFrame::OnViewBack() 
{

	int id;
	id = TW.back();
	if (id <= 10){
		const int nViewType = id;
		m_wndCaptionBar.SetText(viewTypes[nViewType - 1]);
		if (nViewType > 0 && AfxGetMainWnd() != NULL)
		{
			((CMainFrame*)AfxGetMainWnd())->SelectView(nViewType);
		}
		m_nCurrType = id;
		theApp.WriteInt(_T("ViewType"), m_nCurrType);
		PostMessage(UM_REDRAW);
	}
}

void CMainFrame::OnUpdateViewBack(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_nCurrType > 1);
}

void CMainFrame::OnViewForward() 
{
	int id;
	id = TW.forward();
	const int nViewType = id;
	m_wndCaptionBar.SetText(viewTypes[nViewType - 1]);
	if (nViewType > 0 && AfxGetMainWnd() != NULL)
	{
		((CMainFrame*)AfxGetMainWnd())->SelectView(nViewType);
	}
	m_nCurrType = id;
	theApp.WriteInt(_T("ViewType"), m_nCurrType);
	PostMessage(UM_REDRAW);
}

void CMainFrame::InitMaintain(void)
{

	ReadMaintainFile();
	if (m_sMaintain.first_use != 1)
	{
		//配置文件初始化
		m_sMaintain.first_use = 1;		//"1"表示已经初始化过
		m_sMaintain.TimesOfFriday = 0;
		m_sMaintain.m_bIs2ndFriday = FALSE;
		m_sMaintain.TestedDay = 1;
		WriteMaintainFile();
	}
}

void  CMainFrame::InitNormalUserParas()
{
	uchar i, j;

	ReadSystemcfgFile();
	if (systemcfg.first_use != 1)
	{
		//配置文件初始化
		systemcfg.first_use = 1;		//"1"表示已经初始化过

		strcpy((char*)systemcfg.hospital, "");	//医院名称
		systemcfg.cleanperiod = 120;
		systemcfg.washfrequency = 30;
		systemcfg.sleeptime = 15;
		systemcfg.miniprimetime = 60;
		systemcfg.datetype = YYYYMMDD;

		systemcfg.mode = WHOLEDIFF; 		//全血5DIFF mode
		systemcfg.language = CHINESE;//汉语	
		systemcfg.unitWBC = 0;
		systemcfg.unitRBC = 0;
		systemcfg.unitHGB = 0;
		systemcfg.unitMCVRDWSD = 0;
		systemcfg.unitMCH = 0;
		systemcfg.unitMCHC = 0;
		systemcfg.unitPLT = 0;
		systemcfg.unitMPV = 0;

		systemcfg.printercfg.mode = 0;
		systemcfg.printercfg.format = 0;
		systemcfg.printercfg.size = 0;
		systemcfg.com.baudrate = 3;
		systemcfg.com.upload = 1;

		systemcfg.range.type = RANGE_UNIVERSAL;
		for (i = 0; i <= 8; i++)
		{
			systemcfg.range.normal[i][WBCS] = 3.5;
			systemcfg.range.normal[i][WBCS + 28] = 9.5;		//WBC
			systemcfg.range.normal[i][LYMP] = 20.0;
			systemcfg.range.normal[i][LYMP + 28] = 50.0;		//LYM%
			systemcfg.range.normal[i][NEUP] = 40.0;
			systemcfg.range.normal[i][NEUP + 28] = 75.0;		//NEU%
			systemcfg.range.normal[i][MONOP] = 3.0;
			systemcfg.range.normal[i][MONOP + 28] = 10.0;	//MONO%
			systemcfg.range.normal[i][EOSP] = 0.4;
			systemcfg.range.normal[i][EOSP + 28] = 8.0;		//EOS%
			systemcfg.range.normal[i][BASOP] = 0;
			systemcfg.range.normal[i][BASOP + 28] = 1.0;		//BASO%
			systemcfg.range.normal[i][ALYP] = 0;
			systemcfg.range.normal[i][ALYP + 28] = 2.0;		//ALY%
			systemcfg.range.normal[i][LICP] = 0;
			systemcfg.range.normal[i][LICP + 28] = 2.0;		//LIC%		
			systemcfg.range.normal[i][LYMS] = 1.0;
			systemcfg.range.normal[i][LYMS + 28] = 4.0;		//LYM#
			systemcfg.range.normal[i][NEUS] = 2.0;
			systemcfg.range.normal[i][NEUS + 28] = 8.0;		//NEU#
			systemcfg.range.normal[i][MONOS] = 0.1;
			systemcfg.range.normal[i][MONOS + 28] = 0.6;		//MONO#
			systemcfg.range.normal[i][EOSS] = 0.02;
			systemcfg.range.normal[i][EOSS + 28] = 0.52;		//EOS#
			systemcfg.range.normal[i][BASOS] = 0;
			systemcfg.range.normal[i][BASOS + 28] = 0.06;		//BASO#
			systemcfg.range.normal[i][ALYS] = 0;
			systemcfg.range.normal[i][ALYS + 28] = 0.2;		//ALY#
			systemcfg.range.normal[i][LICS] = 0;
			systemcfg.range.normal[i][LICS + 28] = 0.2;		//LIC#
			if (i == 1)
			{
				systemcfg.range.normal[i][RBCS] = 4.3;
				systemcfg.range.normal[i][RBCS + 28] = 5.8;		//RBC
				systemcfg.range.normal[i][HGBS] = 130.0;
				systemcfg.range.normal[i][HGBS + 28] = 175.0;	//HGB
				systemcfg.range.normal[i][HCTS] = 40.0;
				systemcfg.range.normal[i][HCTS + 28] = 50.0;		//HCT
			}
			else
			{
				systemcfg.range.normal[i][RBCS] = 3.8;
				systemcfg.range.normal[i][RBCS + 28] = 5.1;		//RBC
				systemcfg.range.normal[i][HGBS] = 115.0;
				systemcfg.range.normal[i][HGBS + 28] = 150.0;	//HGB
				systemcfg.range.normal[i][HCTS] = 35.0;
				systemcfg.range.normal[i][HCTS + 28] = 45.0;		//HCT
			}
			systemcfg.range.normal[i][MCVS] = 82.0;
			systemcfg.range.normal[i][MCVS + 28] = 100.0;	//MCV
			systemcfg.range.normal[i][MCHS] = 27.0;
			systemcfg.range.normal[i][MCHS + 28] = 34.0;		//MCH
			systemcfg.range.normal[i][MCHCS] = 316;
			systemcfg.range.normal[i][MCHCS + 28] = 354;		//MCHC
			systemcfg.range.normal[i][RDWCVS] = 10.0;
			systemcfg.range.normal[i][RDWCVS + 28] = 15.0;	//RDW-CV
			systemcfg.range.normal[i][RDWSDS] = 40.0;
			systemcfg.range.normal[i][RDWSDS + 28] = 53.0;	//RDW-CV	
			systemcfg.range.normal[i][PLTS] = 125;
			systemcfg.range.normal[i][PLTS + 28] = 350;		//PLT
			systemcfg.range.normal[i][MPVS] = 6.5;
			systemcfg.range.normal[i][MPVS + 28] = 12.5;		//MPV
			systemcfg.range.normal[i][PDWS] = 10.0;
			systemcfg.range.normal[i][PDWS + 28] = 15.0;		//PDW
			systemcfg.range.normal[i][PCTS] = 0.10;
			systemcfg.range.normal[i][PCTS + 28] = 0.27;		//PCT
			systemcfg.range.normal[i][PLCRS] = 13.0;
			systemcfg.range.normal[i][PLCRS + 28] = 43.0;		//PLCR

		}
		//LMNE对应于256个通道
		systemcfg.range.thresholds[NoL] = 44;
		systemcfg.range.thresholds[NoN] = 50;
		systemcfg.range.thresholds[LL] = 60;
		systemcfg.range.thresholds[LN] = 70;
		systemcfg.range.thresholds[NoE] = 96;
		systemcfg.range.thresholds[LMN] = 140;
		systemcfg.range.thresholds[AL] = 136;
		systemcfg.range.thresholds[LMU] = 156;
		systemcfg.range.thresholds[LMD] = 180;
		systemcfg.range.thresholds[MN] = 180;
		systemcfg.range.thresholds[RM] = 236;
		systemcfg.range.thresholds[RN] = 236;
		systemcfg.range.thresholds[NL] = 58;
		systemcfg.range.thresholds[RMN] = 102;
		systemcfg.range.thresholds[NE] = 156;
		systemcfg.range.thresholds[FLN] = 4;	//报警区的宽度
		systemcfg.range.thresholds[FNE] = 4;	//报警区的宽度
		systemcfg.range.thresholds[FMN] = 4;	//报警区的宽度
		//BASO
		systemcfg.range.thresholds[BA1] = 35;
		systemcfg.range.thresholds[BA2] = 110;
		systemcfg.range.thresholds[BA3] = 240;
		//RBC
		systemcfg.range.thresholds[RB1] = 30;
		systemcfg.range.thresholds[RB2] = 213;   // 220->213
		//PLT
		systemcfg.range.thresholds[PLT1] = 10;
		systemcfg.range.thresholds[PLT2] = 192;	    //200->192
		//BASO
		systemcfg.range.thresholds_qc[QCBA1] = 35;
		systemcfg.range.thresholds_qc[QCBA2] = 110;
		systemcfg.range.thresholds_qc[QCBA3] = 240;

		systemcfg.tmp.env = 30.0;
		systemcfg.tmp.incub = 35.0;
		systemcfg.regentfull.diluent = 10000;		//FDparam
		systemcfg.regentfull.rinse = 10000;
		systemcfg.regentfull.hgblyse = 10000;
		systemcfg.regentfull.eoslyse = 10000;
		systemcfg.regentfull.baslyse = 10000;
		for (int i = 0; i < 5; i++)
		{
			systemcfg.regentdate.startyear[i] = 2015;
			systemcfg.regentdate.startmonth[i] = 6;
			systemcfg.regentdate.startday[i] = 6;
			systemcfg.regentdate.endyear[i] = 2016;
			systemcfg.regentdate.endmonth[i] = 6;
			systemcfg.regentdate.endday[i] = 6;
		}
		for (i = 0; i < 4; i++)
			for (j = 0; j <11; j++)
			{
				systemcfg.modify[i].a[j] = 0.000;
				systemcfg.modify[i].b[j] = 1.00;
				systemcfg.modify[i].c[j] = 0.00;
			}

		systemcfg.qualitycontrol.XB_on = 0;
		systemcfg.qualitycontrol.XB_group_num = 20;	//默认20
		strcpy((char*)systemcfg.qualitycontrol.mcvtarget, "");
		strcpy((char*)systemcfg.qualitycontrol.mchtarget, "");
		strcpy((char*)systemcfg.qualitycontrol.mchctarget, "");
		strcpy((char*)systemcfg.qualitycontrol.mcvsd, "");
		strcpy((char*)systemcfg.qualitycontrol.mchsd, "");
		strcpy((char*)systemcfg.qualitycontrol.mchcsd, "");

		systemcfg.lmnepeak1 = 50;
		systemcfg.lmnepeak2 = 80;

		systemcfg.PltRightThresholdMode = 1;
		systemcfg.LMNEMarkMode = 1;


		// XM 电机参数，默认不带穿刺的
		systemcfg.mstp[XM_START_RINSE] = 2400;	//与仪器相匹配的参数值
		systemcfg.mstp[XM_START_HGB] = 2995;
		systemcfg.mstp[XM_START_LMNE] = 3678;
		systemcfg.mstp[XM_START_RBC] = 4365;
		systemcfg.mstp[XM_START_WBCBASO] = 5221;
		systemcfg.mstp[XM_CUP_RADIUS] = 150;
		//稀释电机参数
		systemcfg.mstp[DIM_DILUENT] = 180;
		//YM 电机参数，默认不带穿刺的
		systemcfg.mstp[YM_REF] = 465;
		systemcfg.mstp[YM_HIGH_RINSE] = 40;
		systemcfg.mstp[YM_LOW_RINSE] = 240;
		systemcfg.mstp[YM_MID_HGB] = 655;
		systemcfg.mstp[YM_LOW_HGB] = 1200;
		systemcfg.mstp[YM_HIGH_HGB] = 40;
		systemcfg.mstp[YM_WBCLMNE] = 643;
		systemcfg.mstp[YM_RBCPLT] = 661;
		systemcfg.mstp[YM_WBCBASO] = 660;
		systemcfg.mstp[YM_STARTSAMPLE] = 2100;

		systemcfg.Autosamplerpara[PUSH_SHELF] = 689;
		systemcfg.Autosamplerpara[J_MOTOR] = 136;
		systemcfg.Autosamplerpara[HAND_X] = 350;
		systemcfg.Autosamplerpara[HAND_Y] = 238;
		systemcfg.Autosamplerpara[HAND_MIXER] = 68;
		systemcfg.Autosamplerpara[FLAT] = 2360;
		systemcfg.Autosamplerpara[POP_SHELF] = 50;
		systemcfg.Autosamplerpara[HAND_TAKETOROUNG] = 192;
		systemcfg.Autosamplerpara[HAND_ENDTOTEST] = 238;
		systemcfg.Autosamplerpara[HAND_Y_UPTOROUNG] = 164;


		for (i = 0; i < 4; i++)
			for (j = 0; j < 5; j++)
			{
				systemcfg.calibration[i][j] = 1.0;
			}
		WriteSystemcfgFile();
	}
}

//初始化超级用户参数
void  CMainFrame::InitSuperUserParas(void)
{
	ReadSystemcfg2File();
	if (systemcfg2.first_use != 1)
	{
		//配置文件初始化
		systemcfg2.first_use = 1;		//"1"表示已经初始化过

		strcpy(systemcfg2.company, "SINNOWA");	//公司名
		strcpy(systemcfg2.model, "HB 7510");	//型号
		systemcfg2.warn_baso = FALSE;
		systemcfg2.warn_diluent = FALSE;
		systemcfg2.warn_fix = FALSE;
		systemcfg2.warn_hgb = FALSE;
		systemcfg2.warn_rinse = FALSE;
		systemcfg2.warn_waste = FALSE;
		systemcfg2.PcConMode = 2;			//网口，初始化默认是网口，不然易与自动进样冲突
		systemcfg2.rsspeed = 500000;
		systemcfg2.netport = 2000;    
		strcpy(systemcfg2.ipaddr, "192.168.2.2");
		WriteSystemcfg2File();
	}
}

//初始化特权用户参数
void CMainFrame::InitPrerogativeUserParas(void)
{
	ReadSystemcfg3File();
	if (systemcfg3.first_use != 1)
	{
		//配置文件初始化
		systemcfg3.first_use = 1;		//"1"表示已经初始化过

		systemcfg3.structure = 1;		//不穿刺
		systemcfg3.screen = 1;		//非触摸屏
		systemcfg3.diluent = 2;            //默认50ul;

		WriteSystemcfg3File();
	}
}
//日志文件初始化
void CMainFrame::InitLogFiles(void)
{
	uchar i;

	ReadLogFile();
	if (logfile.first_use != 1)
	{
		//日志文件初始化
		logfile.first_use = 1;		//"1"表示已经初始化过

		logfile.totaltimesoftest = 0;

		logfile.regent.rinse = 10000;	//与systemcfg.regentfull.rinse保持一致
		logfile.regent.hgblyse = 10000;
		logfile.regent.eoslyse = 10000;
		logfile.regent.baslyse = 10000;
		for (int i = 0; i < 5; i++)
		{
			logfile.regentdate.startyear[i] = 2015;
			logfile.regentdate.startmonth[i] = 6;
			logfile.regentdate.startday[i] = 6;
			logfile.regentdate.endyear[i] = 2016;
			logfile.regentdate.endmonth[i] = 6;
			logfile.regentdate.endday[i] = 6;
		}
		for (i = 0; i < ERRNUM + 1; i++)
			logfile.alertnum[i] = 0;
		WriteLogFile();
	}
}

//初始化系统配置全局变量,读入保存的系统配置，第一次使用则为默认配置
void CMainFrame::Syscfginit(void)
{
	InitPrerogativeUserParas();
	InitSuperUserParas();
	InitNormalUserParas();

	InitLogFiles();
	InitMaintain();
}

//*Description:	初始化非系统配置全局变量
void CMainFrame::Init(void)
{
	//帧长度定义
	framelen[SPI_TYPE_CMD] = 1;
	framelen[SPI_TYPE_STATE] = 1;
	framelen[SPI_TYPE_SETTINGS] = 50;

	framelen[SPI_TYPE_HGBRES] = 4;
	framelen[SPI_TYPE_BASORES] = 256;
	framelen[SPI_TYPE_RBCRES] = 512;
	framelen[SPI_TYPE_PLTRES] = 256;
	framelen[SPI_TYPE_LMNERES] = MATRIX_DATA_MAX;

	framelen[SPI_TYPE_TEMRES] = 8;
	framelen[SPI_TYPE_DIFFADJUSTRES] = 4 + 2 + 1 + 1;
	framelen[SPI_TYPE_HGBTESTRES] = 8;
	framelen[SPI_TYPE_DSPVERSIONRES] = 4;
	framelen[SPI_TYPE_ERRORRES] = ERRNUM + 1;

	//其它非系统参数
}

void CMainFrame::OnUpdateOutlookBarShortcut(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(m_nCurrType == pCmdUI->m_nID);
}

void CMainFrame::OnUpdateViewForward(CCmdUI* pCmdUI) 
{
	//pCmdUI->Enable(m_nCurrType < m_wndWorkSpace.GetFeatureCount());
}

void CMainFrame::OnTestModeCombo() //响应测试模式comboBox的函数
{
	CWaitCursor wait;

	CBCGPToolbarComboBoxButton* pCombobox = DYNAMIC_DOWNCAST(CBCGPToolbarComboBoxButton,
		m_wndToolBar.GetButton(m_wndToolBar.CommandToIndex(ID_TEST_MODE_COMBO)));
	ASSERT_VALID(pCombobox);

	m_nTestMode = pCombobox->GetCurSel();
	switch (m_nTestMode)
	{
	case 0:
		systemcfg.mode = WHOLEDIFF ;
		break;
	case 1:
		systemcfg.mode = WHOLECBC;
		break;
	case 2:
		systemcfg.mode = DILUENTDIFF;
		break;
	case 3:
		systemcfg.mode = DILUENTCBC;
		break;
	default:
		break;
	}
	for (int i = 0; i < m_arViews.GetSize(); i++)
	{
		CBCGPChartExampleView* pView = DYNAMIC_DOWNCAST(CBCGPChartExampleView, m_arViews[i]);
		if (pView != NULL)
		{
			pView->UpdateChartColorTheme(m_nTestMode);

			if (pView->IsWindowVisible())
			{
				pView->RedrawWindow();
			}
		}
	}
	
	TRACE1(".................m_nTestMode=%d........\n", m_nTestMode);
	theApp.WriteInt(_T("TestMode"), m_nTestMode);
}

LRESULT CMainFrame::OnRedraw(WPARAM, LPARAM)
{
	RecalcLayout(TRUE);
	GetActiveView()->UpdateWindow();
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_ALLCHILDREN | RDW_FRAME);

	return 0;
}

void CMainFrame::RecalcLayout(BOOL bNotify) 
{
	CFrameWnd::RecalcLayout(bNotify);

	if (IsPrintPreview())
	{
		return;
	}

	for (int i = 0; i < m_arViews.GetSize(); i++)
	{
		CView* pView = m_arViews[i];

		if (pView->GetSafeHwnd() != NULL)
		{
			//pView->ShowWindow(i != m_nCurrType - 1 ? SW_HIDE : SW_SHOWNOACTIVATE);//这句有一定问题
		}
	}
}


void  CMainFrame::SendSysPara(void)
{
	int i = 0;
	uchar sdata[50] = { 0 };

	//向DSP发送步进电机运动参数
	for (i = XM_START_RINSE; i <= YM_STARTSAMPLE; i++)
	{
		sdata[2 * i] = systemcfg.mstp[i] & 0x00FF; 	//低8位
		sdata[2 * i + 1] = systemcfg.mstp[i] >> 8;   	//高8位
	}
	//温度参数
	sdata[34] = (int)(systemcfg.tmp.env * 100) / 1000;
	sdata[35] = ((int)(systemcfg.tmp.env * 100) / 100) % 10;
	sdata[36] = ((int)(systemcfg.tmp.env * 100) / 10) % 10;
	sdata[37] = (int)(systemcfg.tmp.env * 100) % 10;
	//试剂温度
	sdata[38] = (int)(systemcfg.tmp.incub * 100) / 1000;
	sdata[39] = ((int)(systemcfg.tmp.incub * 100) / 100) % 10;
	sdata[40] = ((int)(systemcfg.tmp.incub * 100) / 10) % 10;
	sdata[41] = (int)(systemcfg.tmp.incub * 100) % 10;

	sdata[42] = (systemcfg3.diluent == 1) ? 0 : 1;
	sdata[43] = (systemcfg.mode > 1) ? 0 : 1;

	//防止数据异常设定的随机值
	for (i = 44; i < 50; i++)
		sdata[i] = 0x01;

	if (WAIT_OBJECT_0 == WaitForSingleObject(SendMutex, INFINITE))// 收到激发态的消息  
	{
		PC_SEND_FRAME(sdata, SPI_TYPE_SETTINGS);
	}
	else
	{
		MessageBox(L"仪器运行中无法进行操作!", L"提醒!", MB_OK | MB_ICONINFORMATION);
	}
	//MessageBox(L"发送电机参数");
}

void CMainFrame::SendSysPara_MainTop()
{	
	SendSysPara();
	PC_RECEIVE_FRAME(rdata_state, SPI_TYPE_STATE);
	ReleaseMutex(SendMutex);
	CBCGPToolbarComboBoxButton* pCombobox = DYNAMIC_DOWNCAST(CBCGPToolbarComboBoxButton,
		m_wndToolBar.GetButton(m_wndToolBar.CommandToIndex(ID_TEST_MODE_COMBO)));
	ASSERT_VALID(pCombobox);

	m_nTestMode = pCombobox->GetCurSel();
	switch (m_nTestMode)
	{
	case 0:
		systemcfg.mode = WHOLEDIFF;
		break;
	case 1:
		systemcfg.mode = WHOLECBC;
		break;
	case 2:
		systemcfg.mode = DILUENTDIFF;
		break;
	case 3:
		systemcfg.mode = DILUENTCBC;
		break;
	default:
		break;
	}

	SendMessage(MSG_ACKSPI, rdata_state[0], 0);
}

//TODO: 清洗
void CMainFrame::OnStartup()
{
	// TODO:  在此添加命令处理程序代码
	//SetTimer(STARTUP_TIMER, 5000, 0);
	if (connectionState != 1){
		MessageBox(L"下位机未连接！");
		return;
	}
	DSP_status = Busy;
	sdata_cmd[0] = SPI_CMD_STARTUP;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	SetTimer( POLLTIME, 3000,0);

	StartProgress(3000);

	CView* pActiveView = GetActiveView();
	HWND testwnd = pActiveView->GetSafeHwnd();
	//::PostMessage(testwnd,WM_DISABLEVIEW,0,0);
}

//TODO：空白测试
void CMainFrame::OnBlanktest()
{
	// TODO:  在此添加命令处理程序代码
	CView* pActiveView = GetActiveView();
	HWND testwnd = pActiveView->GetSafeHwnd();
	::PostMessage(testwnd, WM_MAINBLANKTEST, 0, 0);
}

//TODO：测试
void CMainFrame::OnMainTest()
{
	// TODO:  在此添加命令处理程序代码
	//MessageBox(L"sceshi",L"ERROE",0);
	//CView* pActiveView = GetActiveView();
	//HWND testwnd = pActiveView->GetSafeHwnd();
	//::PostMessage(testwnd, WM_MAINTEST, 0, 0);
	CView* pActiveView = GetActiveView();
	HWND testwnd = pActiveView->GetSafeHwnd();
	//printf("***********************AAAAAAAAAAAAAAAAA%d\n", CurView);
	if (CurView != 1)
	{

		MessageBox(L"请切换到主测试界面");
	}
	else
	{
		//MessageBox(L"执行主测试");
		::PostMessage(testwnd, WM_MAINTEST, 0, 0);
	}
	//return 0;
}

void CMainFrame::GetClentRectEx(CRect& lpRect)
{
	CRect rect, rect0, rect1, rect2, rect3, rect4, rect5;
	GetClientRect(rect0);
	m_wndToolBar.GetClientRect(&rect1);
	m_wndShortcutsPane1.GetClientRect(&rect2);
	m_wndCaptionBar.GetClientRect(&rect3);
	m_wndShortcutsBar.GetClientRect(&rect4);
	m_wndStatusBar.GetClientRect(&rect5);
	rect.top = rect1.bottom + rect3.bottom + rect5.bottom + 13;
	rect.left = rect4.right + 4;
	rect.bottom = rect0.bottom - rect1.bottom + 6;
	rect.right = rect0.right;
	lpRect = rect;
}

int CMainFrame::TimeClick = 0;

void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case SYSPARAM_TIMER:
	{		
			SendSysPara_MainTop();
			TimeClick++;
			if (TimeClick == 4)//90
			{
				KillTimer(SYSPARAM_TIMER);
				//MessageBox( _T("DSP 连接异常"),_T("警告!"));//**!!
			}
		break;
	}
	case CLOCK_TIMER:
	{
		CTime time;
		time = CTime::GetCurrentTime();
		CString s = time.Format("%H:%M:%S");
		CString s2 = time.Format("%Y-%m-%d");
		m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_INDICATOR_CLOCK), s); //Show the time 
		m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_INDICATOR_DATE), s2); //Show the date
		break;
	}
	case POLL_TIMER:
	{
		//MessageBox(_T("定时器2!"));
		sdata_cmd[0] = SPI_CMD_REQDSP_STATUS;
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		PC_RECEIVE_FRAME(rdata_state, SPI_TYPE_STATE);
		SendMessage(MSG_ACKSPI, rdata_state[0], 0);
		break;
	}
	case PROGRESS_TIMER:
	{
		if (progresstimes > 100)
		{
			m_progress.DestroyWindow();
			
			KillTimer(PROGRESS_TIMER);
			progresstimes = 0;
			break;
		}
		m_progress.StepIt();
		//m_progress.StepIt();
		progresstimes ++;
		break;
	}
	default:
		break;
	}
	CFrameWnd::OnTimer(nIDEvent);
}



LRESULT CMainFrame::USB_StatusChange(WPARAM wParam, LPARAM lParam)
{

	if (lParam & 0x80)                    //usb dev plugged
	{
		/*	if(byDevIndex != 0xFF)
		{
		return 0;
		}
		OnConnect();*/
		//int fd=m_spidev.open_spi();
		//m_spidev.close_spi(fd);
		if (connectionState == 1){

			TRACE(L"###\nUSB设备已连接2\n");
			m_wndStatusBar.SetPaneText(2, _T("USB设备已连接,下位机心跳中"));
		} else {
			TRACE(L"###\nUSB设备已连接2\n");
			m_wndStatusBar.SetPaneText(2, _T("USB设备已连接，未检测到下位机"));
		}
	}
	else
	{
		
		//if (m_spidev.byDevIndex == wParam)//此处if从未进入,wParam一直为0
		if (m_spidev.byDevIndex == 255)//
		{
			m_spidev.SPI_dev->bRunning = false;
			TRACE(L"###\nUSB设备变化，请检查USB插拔状态\n");
			m_wndStatusBar.SetPaneText(2, _T("USB设备变化，请检查USB插拔状态"));
			USBIO_CloseDevice(m_spidev.byDevIndex);
			m_spidev.byDevIndex = 0xFF;

		}
		else{
			m_wndStatusBar.SetPaneText(2, _T("USB设备已断开"));
		}
	}
	return 0;
}

LRESULT CMainFrame::OnMSG_ACKSPI(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
		//DSP没接收到系统参数，一直循环发送参数
	case SPI_STATE_SYSPARAM_UNRECEIVED:
		break;
		//DSP接收到系统参数
	case SPI_STATE_SYSPARAM_RECEIVED:
		KillTimer(SYSPARAM_TIMER);
		break;
	case SPI_STATE_INFO_END:
		KillTimer(POLL_TIMER);
		break;
	default:
		break;
	}
	return 0;
}

void CMainFrame::OnConfigSet()
{
	// TODO:  在此添加命令处理程序代码
	CConfigSetView setdlg;
	SetPTR = &setdlg;
	if (!setdlg.DoModal())
	{
		MessageBox(_T("生成设置窗口失败"));
		return;
	}

	return;
}

void CMainFrame::OnSelftest()
{
	// TODO:  在此添加命令处理程序代码
	CSelftestView	selftestDlg;
	if (!selftestDlg.DoModal())
	{
		MessageBox(_T("生成自检窗口失败"));
		return;
	}
	return;
}

void CMainFrame::OnMotorcheck()
{
	// TODO:  在此添加命令处理程序代码
	CMotortestView	motortestDlg;
	if (!motortestDlg.DoModal())
	{
		MessageBox(L"生成检测电机窗口失败");
		return;
	}
	return;
}

void CMainFrame::OnValvecheck()
{
	// TODO:  在此添加命令处理程序代码
	CValvetestView valvetestDlg;
	if (!valvetestDlg.DoModal())
	{
		MessageBox(L"生成检测阀窗口失败");
		return;
	}
	return;
}

void CMainFrame::OnPerfusion()
{
	// TODO:  在此添加命令处理程序代码
	CPerfusionView perfusionDlg;
	if (!perfusionDlg.DoModal())
	{
		MessageBox(L"生成检测阀窗口失败");
		return;
	}
	return;
}

void CMainFrame::OnClean()
{
	// TODO:  在此添加命令处理程序代码
	CCleanView cleanviewDlg;
	if (!cleanviewDlg.DoModal())
	{
		MessageBox(L"生成清洗窗口失败");
		return;
	}
	return;
}

void CMainFrame::OnEmpty()
{
	// TODO:  在此添加命令处理程序代码
	CEmptyView	emptyDlg;
	if (!emptyDlg.DoModal())
	{
		MessageBox(L"生成排空窗口失败");
		return;
	}
	return;
}

void CMainFrame::OnConcentratedclean()
{
	// TODO:  在此添加命令处理程序代码
	CConcentratecleanView	concentratedcleanDlg;
	if (!concentratedcleanDlg.DoModal())
	{
		MessageBox(L"生成浓缩清洗窗口失败");
		return;
	}
	return;
}

void CMainFrame::OnRecoil()
{
	// TODO:  在此添加命令处理程序代码
	CRecoilView	recoilDlg;
	if (!recoilDlg.DoModal())
	{
		MessageBox(L"生成反冲窗口失败");
		return;
	}
	return;
}

void CMainFrame::OnMicroPerfusion()
{
	// TODO:  在此添加命令处理程序代码
	CMicroperfusionView		microperfusionDlg;
	if (!microperfusionDlg.DoModal())
	{
		MessageBox(L"生成微灌注窗口失败");
		return;
	}
	return;
}

void CMainFrame::OnAutoclean()
{
	// TODO:  在此添加命令处理程序代码
	CAutocleanView	autocleanDlg;
	if (!autocleanDlg.DoModal())
	{
		MessageBox(L"生成自动清洗窗口失败");
		return;
	}
	return;

}

void CMainFrame::OnReagentManagement()
{
	// TODO:  在此添加命令处理程序代码
	/*CReagentmanagementView	reagentmanagementDlg;
	if (!reagentmanagementDlg.DoModal())
	{
		MessageBox(L"生成窗口失败");
		return;
	}
	return;*/
}

void CMainFrame::OnMaintenance()
{
	// TODO:  在此添加命令处理程序代码
	CReagentmanagementView	reagentmanagementDlg;
	if (!reagentmanagementDlg.DoModal())
	{
		MessageBox(L"生成微灌注窗口失败");
		return;
	}
	return;
}

void CMainFrame::OnSourceManagement()
{
	CConstantCurrentView constantcurrentDlg;
	if (!constantcurrentDlg.DoModal())
	{
		MessageBox(L"生成恒流源管理窗口失败!");
		return;
	}
	return;
	// TODO:  在此添加命令处理程序代码

}

void CMainFrame::OnHgbTest()
{
	CHgbtestView hgbtestDlg;
	if (!hgbtestDlg.DoModal())
	{
		MessageBox(L"生成HGB测试窗口失败!");
		return;
	}
	return;
	// TODO:  在此添加命令处理程序代码
}

void CMainFrame::OnLmneTest()
{
	CLmnetestView lmnetestDlg;
	if (!lmnetestDlg.DoModal())
	{
		MessageBox(L"生成LMNE测试窗口失败!");
		return;
	}
	return;
	// TODO:  在此添加命令处理程序代码
}

void CMainFrame::OnCleanTank()
{
	TRACE("IDC_EM_RINSEBATHS---------#\n");
	key_status = FALSE;		
	DSP_status = Busy;
	sdata_cmd[0] = SPI_CMD_RINSEBATHS;	
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	
	if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			MessageBox(L"命令发送不成功！", L"ERROR", MB_OKCANCEL);
	else
	       {
			   SetTimer( POLLTIME,SPI_POLL_TIME3000,0);
			 //  GetDlgItem(IDC_STATIC_WEEKLY)->SetWindowText(L"正在执行年保养！");
			  // DayConCleanStep=0;
			  
	        }
	// TODO:  在此添加命令处理程序代码
}

void CMainFrame::OnLocationQuantitative()
{
	CLocationquantitativeView locationquantitativeDlg;
	if (!locationquantitativeDlg.DoModal())
	{
		MessageBox(L"生成定位定量窗口失败!");
		return;
	}
	return;
	// TODO:  在此添加命令处理程序代码
}

void CMainFrame::OnGraphicDebug()
{
	// TODO:  在此添加命令处理程序代码
}

void CMainFrame::OnFaultStatistics()
{
	CFaultstatisticsView faultstatisticsDlg;
	if (!faultstatisticsDlg.DoModal())
	{
		MessageBox(L"生成故障统计窗口失败!");
		return;
	}
	return;
	// TODO:  在此添加命令处理程序代码
}

void CMainFrame::OnReagentAlarmSet()
{
	CReabentalarmView reabentalarmDlg;
	if (!reabentalarmDlg.DoModal())
	{
		MessageBox(L"生成LMNE界标设置窗口失败!");
		return;
	}
	return;
	// TODO:  在此添加命令处理程序代码
}

void CMainFrame::OnTemperatureControl()
{
	CTemperaturecontrolView temperaturecontrolDlg;
	if (!temperaturecontrolDlg.DoModal())
	{
		MessageBox(L"生成温度控制设置窗口失败!");
		return;
	}
	return;

	// TODO:  在此添加命令处理程序代码
}

void CMainFrame::OnBasoLandmarkSet()
{
	CBASOLandmarkView basolandmarkDlg;
	if (!basolandmarkDlg.DoModal())
	{
		MessageBox(L"生成LMNE界标设置窗口失败!");
		return;
	}
	return;
	// TODO:  在此添加命令处理程序代码
}

void CMainFrame::OnLmneLandmarkPattern()
{
	
	CSetMarkModeLMNEView setmarkModelmneDlg;
	if (!setmarkModelmneDlg.DoModal())
	{
		MessageBox(L"生成LMNE界标模式窗口失败!");
		return;
	}
	return;
	
	// TODO:  在此添加命令处理程序代码
}

//状态栏中进度条的动态处理程序
int CMainFrame::progresstimes = 0;
void CMainFrame::StartProgress(int ntime)
{
	if (progresstimes != 0){
		MessageBox(L"正在执行清洗");
		return;
	}
	m_progress.Create(WS_CHILD | WS_VISIBLE | PBS_SMOOTH, m_progressrect, &m_wndStatusBar, 123);
	m_progress.SetPos(0);
	m_progress.SetRange(0, 100);
	m_progress.SetStep(1);

	SetTimer(PROGRESS_TIMER,ntime,0);
	//m_progress.UpdateWindow();
	//
}

void CMainFrame::OnQualityTest()
{
	// TODO:  在此添加命令处理程序代码
	if (3 != CurView){
		MessageBox(L"请先切换到质控界面！");
	}
	else{
		switch (Controltype)//根据质控类型，向对应的页面发消息
		{
		case 0:
			::PostMessage(m_QualityTestPage, WM_QUALITYTEST, 0, 0);
			break; 
		case 1:
			::PostMessage(m_QcXTestPage, WM_QUALITYTEST, 0, 0);
			break;
		case 2:
			::PostMessage(m_QcXrTestPage, WM_QUALITYTEST, 0, 0);
			break;
		default:
			MessageBox(L"No such ControlType!");
			break;
		}
		
		//MessageBox(L"QC test in mf");
	}
}

void CMainFrame::OnDatabaseImport()
{
	// TODO: 在此添加控件通知处理程序代码  
	CString strPath = "数据库(*.accdb)|*.accdb||";//过滤文件列表  
	CString path;
	CFileDialog file(true, NULL, NULL, OFN_HIDEREADONLY, strPath, NULL);//创建文件对象并打开  
	if (file.DoModal() == IDOK)//显示文件打开对话框  
	{
		// MessageBox(L"OK");
		path = file.GetPathName();
		CopyFile(path, L"appdata.accdb ", FALSE);
		MessageBox(L"成功导入数据库!", L"提示", MB_OK | MB_ICONINFORMATION);
		m_bRestartFlag = TRUE;
		::PostMessage(mainhwnd, WM_CLOSE, 0, 0);
	}
}

void CMainFrame::OnDatabaseBackup()
{
	// TODO:  在此添加命令处理程序代码
	CTime tm = CTime::GetCurrentTime();
	CString str2;
	CString csPath = "BACKUP";

	if (!PathIsDirectory(csPath))
	{
		CreateDirectory(csPath, 0);//不存在则创建
		//MessageBox(L"CReate");
	}

	str2.Format(_T("BACKUP\\appdata__%04d%02d%02d_%02d%02d.accdb"), tm.GetYear(), tm.GetMonth(), tm.GetDay(), tm.GetHour(), tm.GetMinute());
	//AfxMessageBox(str2);
	//CFile file;
	//file.Open(str2, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);
	CopyFile(L"appdata.accdb ", str2, FALSE);
	MessageBox(L"成功备份数据库!", L"提示", MB_OK | MB_ICONINFORMATION);
}


void CMainFrame::OnDatabaseClearup()
{
	// TODO:  在此添加命令处理程序代码
	if (MessageBox(L"删除数据将不可恢复，请确认！", L"警告", MB_YESNO | MB_ICONINFORMATION) == IDYES)
	{
		if (CopyFile(L"BACKUP\\EmptyDatabase\\appdata.accdb", L"appdata.accdb ", FALSE) != 0)
		{
			MessageBox(L"成功清空数据库!", L"提示", MB_OK | MB_ICONINFORMATION);
			m_bRestartFlag = TRUE;
			::PostMessage(mainhwnd, WM_CLOSE, 0, 0);
		}
		else
		{
			MessageBox(L"清空数据库失败!", L"提示", MB_OK | MB_ICONINFORMATION);
		}
	}
}

void CMainFrame::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	// 判断是否需要重新启动窗口
	if (m_bRestartFlag)
	{
		CString strFileName = _T("");
		GetModuleFileName(NULL, strFileName.GetBuffer(MAX_PATH), MAX_PATH);
		ShellExecute(NULL, _T(""), strFileName, NULL, NULL, SW_SHOWNORMAL);
		strFileName.ReleaseBuffer();
	}

	KillTimer(CLOCK_TIMER);

	CFrameWnd::OnClose();
	exit(0);
}

//此线程没有用
DWORD WINAPI CMainFrame::CreateSwitchDetechThread(LPVOID lpParam)
{
	// 定义结构对象  
	PROCESS_INFORMATION pi;
	STARTUPINFO         si;
	BOOL                bRet;

	// 申请空间  
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	ZeroMemory(&si, sizeof(STARTUPINFO));

	// 设置进程启动属性  
	si.cb = sizeof(STARTUPINFO);
	si.lpReserved = NULL;
	si.lpDesktop = NULL;
	si.lpTitle = NULL;
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOWNORMAL;
	si.cbReserved2 = NULL;
	si.lpReserved2 = NULL;

	CSpi m_spidev;
	//int index = 0;

	/*while (1)
	{
		WaitForSingleObject(SendMutex, INFINITE);

		sdata_cmd[0] = SPI_CMD_REQERROR;

		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		AfxMessageBox(L"检测DSP状态");
		ReleaseMutex(SendMutex);

	}*/

	//CMainFrame *pt = (CMainFrame*)CWnd::FromHandle(((CMainFrame*)lpParam)->m_hWnd);//get the handle to post message
	//pt->PostMessage(WM_TESTSWITCHON, 0, 0);

	//CMainFrame *pt = (CMainFrame*)CWnd::FromHandle(((CMainFrame*)lpParam)->m_hWnd);//get the handle to post message
	//while (1)
	//{
	//	sdata_cmd[0] = SPI_CMD_REQERROR;
	//	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	//	int index = 0;
	//	while (index++ < 5)
	//	{
	//		PC_RECEIVE_FRAME(rdata_state, SPI_TYPE_STATE);
	//		switch (rdata_state[0])
	//		{
	//			case SPI_STATE_SWITCHON:
	//				pt->PostMessage(WM_TESTSWITCHON, 0, 0);
	//				break;
	//			default:
	//				break;
	//		}
	//	}
	//}
	//	
	//	//TRACE("HAHAHAA\n");
	//	Sleep(100);
	//}
	return   0;
}

DWORD WINAPI CMainFrame::CreateHeartbeatThread(LPVOID lpParam)
{
	// 定义结构对象  
	PROCESS_INFORMATION pi;
	STARTUPINFO         si;
	BOOL                bRet;

	// 申请空间  
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	ZeroMemory(&si, sizeof(STARTUPINFO));

	// 设置进程启动属性  
	si.cb = sizeof(STARTUPINFO);
	si.lpReserved = NULL;
	si.lpDesktop = NULL;
	si.lpTitle = NULL;
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOWNORMAL;
	si.cbReserved2 = NULL;
	si.lpReserved2 = NULL;

	//CBCGPStatusBar			m_wndStatusBar;

	CSpi m_spidev;
	int unReachtimes=0;
	while (1)
	{
		WaitForSingleObject(SendMutex, INFINITE );
		int i = 0;
		uchar sdata[50] = { 0 };
		//向DSP发送步进电机运动参数
		for (i = XM_START_RINSE; i <= YM_STARTSAMPLE; i++)
		{
			sdata[2 * i] = systemcfg.mstp[i] & 0x00FF; 	//低8位
			sdata[2 * i + 1] = systemcfg.mstp[i] >> 8;   	//高8位
		}
		//温度参数
		sdata[34] = (int)(systemcfg.tmp.env * 100) / 1000;
		sdata[35] = ((int)(systemcfg.tmp.env * 100) / 100) % 10;
		sdata[36] = ((int)(systemcfg.tmp.env * 100) / 10) % 10;
		sdata[37] = (int)(systemcfg.tmp.env * 100) % 10;
		//试剂温度
		sdata[38] = (int)(systemcfg.tmp.incub * 100) / 1000;
		sdata[39] = ((int)(systemcfg.tmp.incub * 100) / 100) % 10;
		sdata[40] = ((int)(systemcfg.tmp.incub * 100) / 10) % 10;
		sdata[41] = (int)(systemcfg.tmp.incub * 100) % 10;
		sdata[42] = (systemcfg3.diluent == 1) ? 0 : 1;
		sdata[43] = (systemcfg.mode > 1) ? 0 : 1;

		//防止数据异常设定的随机值
		for (i = 44; i < 50; i++)
			sdata[i] = 0x01;



		//连上后拔下连接线，再插上后点击重连，心跳包线程收不到数据(SPI固有问题)
		//其余情况可正常连接，如初始时连上；初始时不连，心跳包线程结束后连上点击重连
		PC_SEND_FRAME(sdata, SPI_TYPE_SETTINGS);
		PC_RECEIVE_FRAME(rdata_state, SPI_TYPE_STATE);

		switch (rdata_state[0])
		{
				//DSP没接收到系统参数，一直循环发送参数
			case SPI_STATE_SYSPARAM_UNRECEIVED://0x36
				TRACE("DSP没接受到系统参数\n");
				unReachtimes++;
				rdata_state[0] = 0;

				break;
				//DSP接收到系统参数
			case SPI_STATE_SYSPARAM_RECEIVED://0x37
				TRACE("DSP接受到系统参数\n");
				unReachtimes = 0;
				rdata_state[0] = 0;
				if (Reconnection == true)
				{
					AfxMessageBox(L"重连成功", MB_OK | MB_ICONINFORMATION);
					Reconnection = false;
				}
				connectionState = 1;
				::PostMessage(mainhwnd, WM_USB_STATUS, 0, 0x80);
				break;
			case SPI_STATE_INFO_END://0x39
				TRACE("SPI_STATE_INFO_END\n");
				unReachtimes++;
				rdata_state[0] = 0;
				break;
			default:
				unReachtimes++;
				rdata_state[0] = 0;
				break;
		}
 		if (Reconnection == true && unReachtimes >= 3)
		{
			AfxMessageBox(L"重连失败", MB_OK | MB_ICONINFORMATION);			
			unReachtimes = 0;
			Reconnection = false;
			connectionState = 3;
			//m_wndStatusBar.SetPaneText(1, _T("设备连接失败1"), TRUE);
			//m_wndStatusBar.SetPaneInfo(1, m_wndStatusBar.GetDlgCtrlID(), SBPS_NORMAL, dwScreenX * 1 / 10);
			::PostMessage(mainhwnd, WM_USB_STATUS, 0, 0);
			ReleaseMutex(SendMutex);
			return 0;
		}
		if (unReachtimes >=3)
		{
			AfxMessageBox(L"DSP连接异常，请检查仪器状态\n以及通信接口,稍后请重连", MB_OK | MB_ICONINFORMATION);
			connectionState = 3;
			::PostMessage(mainhwnd,WM_USB_STATUS, 0, 0);
			unReachtimes = 0;
			Reconnection = true;
			ReleaseMutex(SendMutex); 
			return 0;
		}
		ReleaseMutex(SendMutex);		//控制线程结束
		Sleep(5000);
	}
	return 0;
}
afx_msg LRESULT CMainFrame::OnTestSwitchOn(WPARAM wParam, LPARAM lParam)
{
	CView* pActiveView = GetActiveView();
	HWND testwnd = pActiveView->GetSafeHwnd();
	//printf("***********************AAAAAAAAAAAAAAAAA%d\n", CurView);
	if (CurView!=1)
	{

		MessageBox(L"请切换到主测试界面");
	}
	else
	{
		::PostMessage(testwnd, WM_MAINTEST, 0, 0);
	}
	return 0;
}

void CMainFrame::OnWorksheet()
{
	// TODO:  在此添加命令处理程序代码
	CWorkstationView m_workstation;
	if (!m_workstation.DoModal())
	{
		MessageBox(L"工作站窗口创建失败");
	}
}

void CMainFrame::OnConnectDSP()
{
	// TODO:  在此添加命令处理程序代码
	MessageBox(L"connect");
	DWORD	 dwThreadId;
	HANDLE   hThread = NULL;
	hThread = CreateThread(NULL, 0, CreateHeartbeatThread, LPVOID(this), 0, &dwThreadId);
}


void CMainFrame::OnLockKeyboard()
{
	// TODO:  在此添加命令处理程序代码
	SetHook(m_hWnd);
}


void CMainFrame::OnUnlockKeyboard()
{
	// TODO:  在此添加命令处理程序代码
	StopHook(m_hWnd);
}


void CMainFrame::OnBackupsystem()
{
	// TODO:  在此添加命令处理程序代码
	CBackupView m_backupsystem;
	if (!m_backupsystem.DoModal())
	{
		MessageBox(L"备份系统窗口创建失败");
	}

}


//afx_msg LRESULT CMainFrame::OnUpdateErrStatus(WPARAM wParam, LPARAM lParam)
//{
//	return 0;
//}


afx_msg LRESULT CMainFrame::OnReagentAlarm(WPARAM wParam, LPARAM lParam)
{
	CString		MotorErrInfo_CN[] = { "正常",
	"X电机故障! 请检查",                		 //  1
	"Y电机故障!  请检查",               		//  2
	"采样电机(SM)故障! 请检查",		//  3
	"稀释电机(DIM)故障! 请检查",	//  4
	"排空电机(DRM)故障! 请检查",	//  5
	"计数电机(CTM)故障! 请检查",	//  6
	"鞘流电机(CYM)故障! 请检查",	//  7
	"WBC堵孔",							//  8
	"RBC堵孔",								//  9
	"排废液时间过长",				//  10
	"稀释液不足",						//  11
	"废液已满",							//  12
	"鞘流堵孔",                          //  13
	"缺清洗剂",                          //14 add by jxq 20170309
	"缺HB5D-HGB溶血剂",                   //15 add by jxq 20170309
	"缺HB5D-EOS嗜酸",                     //16 add by jxq 20170309
	"缺HB5D-BAS嗜碱" };	                     //17 add by jxq 20170309

	if (lParam == 0){		
		//MessageBox(L"0");
		m_wndStatusBar.SetPaneText(1, MotorErrInfo_CN[0]);
		if (wParam > 0 && wParam < 11 || wParam==13){
			m_wndStatusBar.SetPaneText(1, MotorErrInfo_CN[wParam]);
		}		
		
	}
	else{
		//MessageBox(L"1");
		MessageBox(MotorErrInfo_CN[wParam]);
		m_wndStatusBar.SetPaneText(1, MotorErrInfo_CN[wParam]);

	}

	return 0;
}


void CMainFrame::OnLanguageChoose()
{
	// TODO:  在此添加命令处理程序代码
	CLanguageChoose	languageChooseDlg;
	if (!languageChooseDlg.DoModal())
	{
		MessageBox(L"生成语言选择窗口失败");
		return;
	}
	return;
}


void CMainFrame::OnMultilangTest()
{
	// TODO:  在此添加命令处理程序代码

	CMultiLangTest	multiLangTestDlg;
	if (!multiLangTestDlg.DoModal())
	{
		MessageBox(L"生成多语言测试窗口失败");
		return;
	}
	return;
}



