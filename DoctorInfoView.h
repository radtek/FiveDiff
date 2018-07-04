#pragma once

//#include "BCGPChartExampleDoc.h"
//#include "BCGPChartExampleView.h"
//#include "afxcmn.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPChartCtrl.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPListBox.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPListCtrl.h"
//#include "CMyBCGPListCtrl.h"
#include "Includes_app.h"
// CDoctorInfoView ������ͼ

typedef struct{
	vector<CString>	numofrs;    //�洢id
	int				totalnums;  //��ǰ��ʾid����
	int				nownum;     //��ǰѡ�е�id���

	int				page_count;  //���ݿ���ҳ��
	int				page_index;  //��ǰҳ��
	long			data_count;	//���ݿ�id����
	int				page_num; //һҳ��ʾ��id����
}DoctorInfoToDisplay;

class CDoctorInfoView : public CBCGPChartExampleView
{
	DECLARE_DYNCREATE(CDoctorInfoView)

protected:
	CDoctorInfoView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CDoctorInfoView();

public:
	enum { IDD = IDD_DOCTORINFO };
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
	CMyBCGPListCtrl m_DoctorInfoList;

	BOOL InitDoctorInfoForm();
	BOOL UpdataDoctorInfoForm();
	virtual void OnInitialUpdate();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnManualAdd();
	afx_msg void OnDelete();
	afx_msg void OnDblclkDoctorList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedSave();
	DoctorInfoToDisplay ThisResult;
	afx_msg void OnBnClickedDoctPageHome();
	afx_msg void OnBnClickedDoctPageFront();
	afx_msg void OnBnClickedDoctPageNext();
	afx_msg void OnBnClickedDoctPageTrailer();
	afx_msg void OnBnClickedDoctPageJump();
};


