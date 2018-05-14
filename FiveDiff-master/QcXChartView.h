#pragma once
#include "BCGPChartCtrl.h"
#include "BCGPListCtrl.h"

// CQcXChartView �Ի���

class CQcXChartView : public CDialogEx
{
	DECLARE_DYNAMIC(CQcXChartView)

public:
	CQcXChartView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CQcXChartView();

// �Ի�������
	enum { IDD = IDD_QC_X_CHART };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void	OnPaint();
	virtual BOOL	OnInitDialog();
	afx_msg HBRUSH  OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CBCGPChartVisualObject* pChart;
	CBCGPChartVisualObject* pChart2;
	CBCGPChartVisualObject* pChart3;
	CBCGPChartVisualObject* pChart4;

	void			InitLineChart();
	void			InitLineChart2();
	void			InitLineChart3();
	void			InitLineChart4();

	void			UpdateLineChart();
	void			UpdateLineChart2();
	void			UpdateLineChart3();
	void			UpdateLineChart4();

	void			OnUpdateChart(int num);
	CBCGPChartCtrl  m_QcXLineChart;
	CBCGPChartCtrl  m_QcXLineChart2;
	CBCGPChartCtrl  m_QcXLineChart3;
	CBCGPChartCtrl  m_QcXLineChart4;
	CMyBCGPListCtrl   m_QcXmaterialInfolist;
	bool			InitQcXMaterialInfoList();
	bool			UpdateQcXMaterialInfoList();
	CString			quality_table[28];

	int				curpage;
	afx_msg void	OnQcXGraphUp();
	afx_msg void	OnQcXGraphDown();

	void UpdateView();


	CFont			textfont;
	int				isQcXEditExist;//0:�ļ�û�б༭��Ϣ��1:�ļ��б༭��Ϣ
	int 			qcXGraphNum;		//��Ӧ�ʿط�ʽ���ļ��ļ�¼����
	int				GetNumDea(int controltype, int controlfile);
	int				GetDetail(int controltype, int controlfile);
	void			UpdateMSC();
	void			UpdateLUlimit();
	double			upperlimit[26];//����
	double			lowerlimit[26];//����
	double			data[26][31];//�ʿؽ��
	CString number;
	CString deadline;
};
