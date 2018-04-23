#pragma once


// CQcXrChartView �Ի���

class CQcXrChartView : public CDialogEx
{
	DECLARE_DYNAMIC(CQcXrChartView)

public:
	CQcXrChartView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CQcXrChartView();

// �Ի�������
	enum { IDD = IDD_QC_XR_CHART };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CBCGPChartVisualObject* pChart1;
	CBCGPChartVisualObject* pChart2;

	CBCGPChartCtrl  m_QcXrChartLineChart1;
	CBCGPChartCtrl  m_QcXrChartLineChart2;

	CMyBCGPListCtrl   m_QcXrChartMaterialInfolist;

	int				curpage;
	int				qcXrChartFileExistEdit;//0:�ļ�û�б༭��Ϣ��1:�ļ��б༭��Ϣ
	int 				qcXrChartGraphNum;		//��Ӧ�ʿط�ʽ���ļ��ļ�¼����


	double			qcAve[26];//ƽ��ֵ
	double			qcRan[26];//����

	double			data[26][62];//�ʿؽ��
	CString			quality_table[28];

	CFont			textfont;
	CString			number;
	CString			deadline;

	void			InitLineChart1();
	void			InitLineChart2();
	void			OnUpdateChart(int num);
	void			setQcAveRan();
	

	bool			InitmaterialInfoList();
	bool			UpdateMaterialInfoList();
	int			GetQcXrResult(int controltype, int controlfile);
	int			GetQcXrEdit(int controltype, int controlfile);


	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg LRESULT OnRedraw(WPARAM, LPARAM);

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedQcXrChartGraphUp();
	afx_msg void OnBnClickedQcXrChartGraphDown();
};
