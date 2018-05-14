#pragma once
#include "Includes_app.h"
#include "CMyBCGPListCtrl.h"
#include "BCGPChartCtrl.h"

// CQcXTestView �Ի���

class CQcXTestView : public CDialogEx
{
	DECLARE_DYNAMIC(CQcXTestView)

public:
	CQcXTestView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CQcXTestView();

// �Ի�������
	enum { IDD = IDD_QC_X_TESTVIEW };

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

	qcresult_info	 qcresultdata;			//���Խ��
	qcresult_info	 qcresultdataAve;			//ƽ�����Խ����ֻ�в�����ͼ��û������
	QcDataProcess	 m_qcDataProcess;
	CSpi		   m_spidev;
	static unsigned int QcXFileExistEdit;	//0:�ļ�û�б༭��Ϣ��1:�ļ��б༭��?
	unsigned char 	testNum;			//���Դ���

	BOOL InitForm(qcresult_info *qcresultdata);
	BOOL UpdateForm(qcresult_info *qcresultdata);
	BOOL InitWBCForm(qcresult_info *qcresultdata);
	BOOL UpdateWBCForm(qcresult_info *qcresultdata);
	BOOL InitRBCForm(qcresult_info *qcresultdata);
	BOOL UpdateRBCForm(qcresult_info *qcresultdata);
	BOOL InitPLTForm(qcresult_info *qcresultdata);
	BOOL UpdatePLTForm(qcresult_info *qcresultdata);
	BOOL InitRETForm();
	BOOL UpdateRETForm();
	BOOL InitCRPForm();
	BOOL UpdateCRPForm();


	void PrintChart(qcresult_info *qcresultdata);
	void Init_B_LMNE(float	coefficient, B_LMNE* p_blmne);

	void LmneGraphPaint(qcresult_info *qcresultdata, const unsigned char rangetype, CDC &MemDC);
	void LmneGraphPaint(qcresult_info *qcresultdata, const unsigned char rangetype);

	void PrintLMNEChart(qcresult_info *qcresultdata);
	void UpdatePrintChart(qcresult_info *qcresultdata);
	void PrintBASOChart(qcresult_info *qcresultdata);
	void UpdatePrintBASOChart(qcresult_info *qcresultdata);
	void PrintRBCChart(qcresult_info *qcresultdata);
	void UpdatePrintRBCChart(qcresult_info *qcresultdata);
	void PrintPLTChart(qcresult_info *qcresultdata);
	void UpdatePrintPLTChart(qcresult_info *qcresultdata);
	void PrintPieChart();
	void UpdatePrintPieChart();
	void UpdateView();

	//void initQcLjData();//�ʿز��Բ�������26����û�б�Ҫ28���������������̲�һ��
	int getqcresultRow();

	CFont	textfont;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	void initQcXData();
	void initQcXAveData();
	void Addqcresult1ToAve();
	void Addqcresult2ToAve();



protected:
	afx_msg LRESULT OnQualitytest(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnAckspi(WPARAM wParam, LPARAM lParam);
};
