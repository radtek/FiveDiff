#pragma once


#include "BCGPChartExample.h"
#include "BCGPChartExampleDoc.h"
#include "BCGPChartExampleView.h"
//#include "afxcmn.h"
#include "BCGPChartCtrl.h"
#include "BCGPListBox.h"
#include "BCGPListCtrl.h"
#include "CMyBCGPListCtrl.h"
#include "Includes_app.h"


// CCalibrationView ������ͼ


static uchar ref_ac[5][6];				//5��ο�ֵ����
static CString wbc_buff[5], rbc_buff[5], hgb_buff[5], mcv_buff[5], plt_buff[5];	//��β��Խ��
static uchar wbc_cvbuff[6], rbc_cvbuff[6], hgb_cvbuff[6], mcv_cvbuff[6], plt_cvbuff[6];			//����ϵ��CV
static uchar wbc_coebuff[5], rbc_coebuff[5], hgb_coebuff[5], mcv_coebuff[5], plt_coebuff[5];	//����У��ϵ��


class CCalibrationView : public CBCGPChartExampleView
{
	DECLARE_DYNCREATE(CCalibrationView)

protected:
	CCalibrationView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CCalibrationView();

public:
	enum { IDD = IDD_CALIBRATION };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnAutoCalibrateStart();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	CMyBCGPListCtrl m_CalibrationList;
	CMyBCGPListCtrl m_CoefficientList;

	CString Mean[5];//ƽ��ֵ
	//CString TestTime[5];//����ʱ��
	int e_Item;    //�ձ༭����  
	int e_SubItem; //�ձ༭����  
	CEdit m_WBCEdit;
	bool haveeditcreate;//��־�༭���Ѿ�������


	void	createEdit(NM_LISTVIEW  *pEditCtrl, CEdit *createdit, int &Item, int &SubItem, bool &havecreat);
	void	distroyEdit(CListCtrl *list, CEdit* distroyedit, int &Item, int &SubItem);
	BOOL	InitCalibrationForm();
	BOOL	InitCoeffcientForm();
	virtual void OnInitialUpdate();
	void	AutoCalibrationRun();
	void	DealWithWBC(uchar CurCalMode);
	void	DealWithRBC(uchar CurCalMode);
	void	DealWithHGB(uchar CurCalMode);
	void	DealWithMCV(uchar CurCalMode);
	void	DealWithPLT(uchar CurCalMode);
	void	DealWithData(uchar CurCalMode, CString ResultBuff[5],CString MeanBuff[5], uchar CVBuff[5], uchar CoeBuff[5], int ItemType,int meanIndex);
	//void	DealWithData(uchar CurCalMode, CString ResultBuff[5], uchar CVBuff[5], uchar CoeBuff[5], int ItemType);
	void	ShowCalibrationInfo();
	void	UpdateCalibrate();
	void	Showtarget();
	BOOL	GetRefValue();

public :

	static unsigned char oldSysmode;			//��¼�������ǰ��ϵͳ����ģʽ���˳������ʱ��Ҫ�ָ�ԭ���Ĳ���ģʽ
	static unsigned char ac_index;              //��Ҫ��β��ԣ���¼�ڼ��β���
	static unsigned char ref_flag;				//��ʾ�ο�ֵ������״̬��1��ʾ�����룬0��ʾδ����
	static status CurStatusMess;



private:
	sample_info		 sampledata;
	CSpi			 m_spidev;
	DataTransmission m_datatrans;
	DataProcess		 m_dataprocess;
	uchar			 TestMode;

protected:
	afx_msg LRESULT OnAckspi(WPARAM wParam, LPARAM lParam);
public:
	//afx_msg void OnTargetvalue();
	afx_msg void OnNMClickCoefficientList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedTestmodeRadio();
	int m_modeRadio;
	int m_testmodeRadio;
	afx_msg void OnBnClickedAutoModeRadio();

	afx_msg void OnBnClickedAutoModeRadio2();
	afx_msg void OnBnClickedAutoTestmodeRadio();
	afx_msg void OnBnClickedAutoTestmodeRadio2();
	afx_msg void OnCalibrationTest();
	void		 UpdateTargetvalue();

	void		initData();


	afx_msg void OnBnClickedManualCalibrationSave();
};


