#pragma once
#include "afxcmn.h"
#include "Includes_app.h"


// CQcXrTestView �Ի���

class CQcXrTestView : public CDialogEx
{
	DECLARE_DYNAMIC(CQcXrTestView)

public:
	CQcXrTestView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CQcXrTestView();

// �Ի�������
	enum { IDD = IDD_QC_XR_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int					testNum;			//���Դ���
	unsigned int			QcXrFileExistEdit ;	//0:�ļ�û�б༭��Ϣ��1:�ļ��б༭��
	CString				tempXrNumber ;
	CString				tempXrDeadline ;

	CMyBCGPListCtrl		m_QcXrTestList;
	QcDataProcess	 m_qcDataProcess;
	CSpi		   m_spidev;
	qcresult_info qcresultdata;			//���Խ��
	qcresult_info qcresultdata1;		//���Խ��
	qcresult_info qcresultdataAve;		//ƽ�����Խ����ֻ�в�����ͼ��û������
	qcresult_info qcresultdataRan;		//���ֻ�в�����ͼ��û������


	void					InitQcXrTestList();
	void					UpdateQcXrTestList1();
	void					UpdateQcXrTestList2();
	void					UpdateQcXrTestHeadInfo();

	void					initQcXrData();
	void					initQcXrData1();
	void					initQcXrAveData();
	void					initQcXrRanData();
	void					copyqcresultToResult1();

	void					getAveRan();
	bool					getQcXrEditFile();//��ȡ���ݿ����ʿر༭����
	int					getqcresultRow();
	afx_msg LRESULT		OnQualitytest(WPARAM wParam, LPARAM lParam);//�����ʿز�������
	afx_msg LRESULT		OnAckspi(WPARAM wParam, LPARAM lParam);//onackspi������λ����ȡ����
	void					OnTimer(UINT_PTR nIDEvent);//��ʱ����ontimer
	//���±��

	//

	

	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	CFont			textfont;

	
};
