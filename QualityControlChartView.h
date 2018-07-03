#pragma once
#include "BCGPChartCtrl.h"
#include "BCGPListCtrl.h"
//#include <CString>


// CQualityControlChartView �Ի���


class CQualityControlChartView : public CDialogEx
{
	DECLARE_DYNAMIC(CQualityControlChartView)

public:
	CQualityControlChartView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CQualityControlChartView();

	// �Ի�������
	enum { IDD = IDD_QUALITY_CONTROL_CHART };

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
	CBCGPChartCtrl  m_QualityLineChart;
	CBCGPChartCtrl  m_QualityLineChart2;
	CBCGPChartCtrl  m_QualityLineChart3;
	CBCGPChartCtrl  m_QualityLineChart4;
	CMyBCGPListCtrl   m_materialInfolist;
	bool			InitmaterialInfoList();
	bool			UpdateMaterialInfoList();
	CString			quality_table[28];

	int				curpage;
	afx_msg void	OnGraphUp();
	afx_msg void	OnGraphDown();
	afx_msg LRESULT OnRedraw(WPARAM, LPARAM);

	void UpdateView();


	CFont			textfont;
	int				QcLjFileExistEdit;//0:�ļ�û�б༭��Ϣ��1:�ļ��б༭��Ϣ
	int 			qcLjGraphNum;		//��Ӧ�ʿط�ʽ���ļ��ļ�¼����
	int				GetNumDea(int controltype, int controlfile);
	int				GetDetail(int controltype, int controlfile);
	void			UpdateMSC();
	void			UpdateLUlimit();
	double			upperlimit[26];//����
	double			lowerlimit[26];//����
	double			data[26][31];//�ʿؽ��
	float Mean[26];
	float SD[26];
	float CV[26];
	CString number;
	CString deadline;

	//void Draw_LJ(int Orgx, int Orgy, HDC hdc);
	afx_msg void OnBnClickedGraphPrint();
	//void Draw_LJ(int Orgx, int Orgy, int y_max, int num, HDC hdc);
	void Draw_LJ(CString type, CDC &pDC, int Xorg, int Yorg, float y_max, int num);
	void Compute_MSC();//����ÿ����Ŀ��Mean,SD,CV��ֵ
};
