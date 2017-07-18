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
	virtual void OnInitialUpdate();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


