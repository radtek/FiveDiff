#pragma once
#include "Includes_app.h"
#include "CMyBCGPListCtrl.h"
#include "BCGPChartCtrl.h"


// CQualityTestView �Ի���

static qcresult_info qcresultdata;

class CQualityTestView : public CDialogEx
{
	DECLARE_DYNAMIC(CQualityTestView)

public:
	CQualityTestView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CQualityTestView();

// �Ի�������
	enum { IDD = IDD_QUALITY_TESTVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	CMyBCGPListCtrl m_WBCList;
	CMyBCGPListCtrl m_RBCList;
	CMyBCGPListCtrl m_PLTList;
	CMyBCGPListCtrl m_RETList;
	CMyBCGPListCtrl m_CRPList;

	CBCGPChartCtrl m_LmneChart;
	CBCGPChartCtrl m_BASOChart;
	CBCGPChartCtrl m_RBCChart;
	CBCGPChartCtrl m_PLTChart;
	CBCGPChartCtrl m_PieChart;
	CSpi		   m_spidev;
	static unsigned char QcLjFileExistEdit;	//0:�ļ�û�б༭��Ϣ��1:�ļ��б༭��?

	BOOL InitForm(sample_info* psampledata);
	BOOL UpdateForm(sample_info* psampledata);
	BOOL InitWBCForm(sample_info* psampledata);
	BOOL UpdateWBCForm(sample_info* psampledata);
	BOOL InitRBCForm(sample_info* psampledata);
	BOOL UpdateRBCForm(sample_info* psampledata);
	BOOL InitPLTForm(sample_info* psampledata);
	BOOL UpdatePLTForm(sample_info* psampledata);
	BOOL InitRETForm();
	BOOL UpdateRETForm();
	BOOL InitCRPForm();
	BOOL UpdateCRPForm();

	void PrintChart(sample_info *psampledata);
	void Init_B_LMNE(float	coefficient, B_LMNE* p_blmne);
	void LmneGraphPaint(sample_info *psampledata, const unsigned char rangetype);
	void PrintLMNEChart(sample_info *psampledata);
	void UpdatePrintChart(sample_info *psampledata);
	void PrintBASOChart(sample_info *psampledata);
	void UpdatePrintBASOChart(sample_info *psampledata);
	void PrintRBCChart(sample_info *psampledata);
	void UpdatePrintRBCChart(sample_info *psampledata);
	void PrintPLTChart(sample_info *psampledata);
	void UpdatePrintPLTChart(sample_info *psampledata);
	void PrintPieChart();
	void UpdatePrintPieChart();

	void initQcLjData();//�ʿز��Բ�������26����û�б�Ҫ28���������������̲�һ��

	CFont	textfont;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

protected:
	afx_msg LRESULT OnQualitytest(WPARAM wParam, LPARAM lParam);

};
