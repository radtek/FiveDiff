#pragma once

//#include "BCGPChartExampleDoc.h"
//#include "BCGPChartExampleView.h"
//#include "afxcmn.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPChartCtrl.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPListBox.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPListCtrl.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPComboBox.h"
//#include "CMyBCGPListCtrl.h"
//#include "ListCtrl.h"
#include "ReportGenerator\ReportGenerator.h"
#include "ReportGenerator\DrawPicture.h"
#include "Includes_app.h"
#include "afxwin.h"

typedef struct{
	vector<CString>	numofrs;    //存储id
	int				totalnums;  //当前显示id个数
	int				nownum;     //当前选中的id序号
	
	int				page_count;  //数据库总页数
	int				page_index;  //当前页数
	long				data_count;	//数据库id总数
	int				page_num; //一页显示的id个数
}ResultToDisplay;
typedef	ResultToDisplay*	pResultToDisplay;
extern int reserve_index;

///***** 用于医生id与姓名的匹配*******/
//struct doct_match
//{
//	int doct_id=-1;
//	CString doct_name="";
//};
//doct_match doctor_match[30];
///*****************/



typedef struct{
	int list_pos[1000];
	int ado_pos[1000];
}Relation;
// CResultDetails 窗体视图

class CResultDetails : public CBCGPChartExampleView
{
	DECLARE_DYNCREATE(CResultDetails)

public:
	CResultDetails();           // 动态创建所使用的受保护的构造函数
	virtual ~CResultDetails();

public:
	enum { IDD = IDD_RESULTDETAILS };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMyBCGPListCtrl		m_Details_WBCList;
	CMyBCGPListCtrl		m_Details_RBClist;
	CMyBCGPListCtrl		m_Details_PLTlist;
	CMyBCGPListCtrl		m_Details_RETlist;
	CMyBCGPListCtrl		m_Details_CRPlist;
	CBCGPChartCtrl		m_LMNEChart;
	CBCGPChartCtrl		m_BASOChart;
	CBCGPChartCtrl		m_RBCChart;
	CBCGPChartCtrl		m_PLTChart;
	CBCGPChartCtrl		m_PieChart;
	CBCGPListBox		m_WBCFlag;
	CBCGPListBox		m_RBCFlag;
	CBCGPListBox		m_PLTFlag;
	CBCGPListBox		m_RETFlag;
	CBCGPComboBox		m_sex_combo;

	CReportGenerator	m_reportGenerator;

	static ResultToDisplay*  pThisResult;
	int					m_printStyle;
	BOOL				m_print_tip;

private:
	static sample_info	*	sampledata;			//与界面交互和数据库交互的变量
	static patient_info*	patientdata;

	BOOL			InitPaitientInfo(patient_info* ppatientdata);
	BOOL			InitForm(sample_info* psampledata);
	BOOL			InitWBCForm(sample_info* psampledata);
	BOOL			InitRBCForm(sample_info* psampledata);
	BOOL			InitPLTForm(sample_info* psampledata);
	BOOL			InitRETForm();
	BOOL			InitCRPForm();

	BOOL			UpdatePatientResultForm();
	BOOL			UpdateForm(sample_info* psampledata);
	BOOL			UpdateWBCForm(sample_info* psampledata);
	BOOL			UpdateRBCForm(sample_info* psampledata);
	BOOL			UpdatePLTForm(sample_info* psampledata);
	BOOL			UpdateRETForm();
	BOOL			UpdateCRPForm();



	void			PrintChart(sample_info *psampledata);
	void			PrintLMNEChart();
	void			PrintBASOChart(sample_info *psampledata);
	void			PrintRBCChart(sample_info *psampledata);
	void			PrintPLTChart(sample_info *psampledata);
	void			PrintPieChart();

	void			UpdatePrintChart(sample_info *psampledata);
	void			UpdatePrintLMNEChart();
	void			UpdatePrintBASOChart(sample_info *psampledata);
	void			UpdatePrintRBCChart(sample_info *psampledata);
	void			UpdatePrintPLTChart(sample_info *psampledata);
	void			UpdatePrintPieChart();


	void			SetObjectColors();
	int				LoadChoseRecord(pResultToDisplay pThisResult);

	void			GetSample_Data(char uch[28][12], sample_info * sampleinfo);
	void			GetSample_Warn(char uch[28][2], sample_info * sampleinfo);
	void			GetSample_Range(char uch[28][20]);

	void			Init_graphdata_rbc(void);

public:
	void			Init_B_LMNE(float	coefficient, B_LMNE* p_blmne);
	void			LmneGraphPaint(sample_info *psampledata, const unsigned char rangetype, CDC &MemDC);
	void			PrintLMNEChart(sample_info *psampledata);
	virtual void	OnInitialUpdate();
	virtual void	OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL	OnPreparePrinting(CPrintInfo* pInfo);
	afx_msg BOOL	OnEraseBkgnd(CDC* pDC);
	afx_msg void	OnPaint();
	afx_msg void	OnResultUpload();
	afx_msg void	OnViewBack();
	afx_msg void	OnViewForward();
	afx_msg void	OnSelectResultPrint();

	void			WriteSelectReportData(sample_info* psampledata, patient_info* ppatientdata);
	void			FillA4Report(CString file, sample_info* psampledata, patient_info* ppatientdata);
	void			FillA5Report(CString file, sample_info* psampledata, patient_info* ppatientdata);



	void			GernerateLMNEBGP();
	void			GernerateBASOBGP();
	void			GernerateRBCBGP();
	void			GerneratePLTBGP();

public:
	CString			sampleID;
	uchar	graph_lmne[16][256];
	uchar	graph_baso_left[7][103];
	uchar	graph_baso[7][256];
	uchar	graph_rbc_left[7][2];
	uchar	graph_rbc[7][256];
	uchar	graph_plt_left[7][101];
	uchar	graph_plt[7][256];



	CString	itemhead;

	CString items_fullname[28];
	CString items_shortname[28];
	CString unit_info[28];



	afx_msg void OnDeleteRecord();

	afx_msg void OnBnClickedResultReturn();

	CComboBox m_doctor_combo;
	//	 afx_msg void OnEnSetfocusResultEdit3();
	//afx_msg void OnEnSetfocusResultEdit3();
	//afx_msg void OnEnKillfocusResultEdit3();
	//afx_msg void OnEnSetfocusResultEdit4();
	//afx_msg void OnEnKillfocusResultEdit4();
	//afx_msg void OnEnSetfocusResultEdit5();
	//afx_msg void OnEnKillfocusResultEdit5();
	//afx_msg void OnEnSetfocusResultEdit2();
	//afx_msg void OnEnKillfocusResultEdit2();
	//afx_msg void OnBnClickedButton3();
	afx_msg void OnEnSetfocusResultEdit3();
	afx_msg void OnEnKillfocusResultEdit3();
	afx_msg void OnEnSetfocusResultEdit4();
	afx_msg void OnEnKillfocusResultEdit4();
	afx_msg void OnEnSetfocusResultEdit5();
	afx_msg void OnEnKillfocusResultEdit5();
	afx_msg void OnEnSetfocusResultEdit2();
	afx_msg void OnEnKillfocusResultEdit2();
	afx_msg void OnBnClickedButton3();
};


