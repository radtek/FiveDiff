#pragma once

//#include "BCGPChartExampleDoc.h"
//#include "BCGPChartExampleView.h"
//#include "afxcmn.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPChartCtrl.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPListBox.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPListCtrl.h"
//#include "CMyBCGPListCtrl.h"
#include "Includes_app.h"
// CPatientInfoView ������ͼ

class CPatientInfoView : public CBCGPChartExampleView
{
	DECLARE_DYNCREATE(CPatientInfoView)

protected:
	CPatientInfoView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CPatientInfoView();

public:
	enum { IDD = IDD_PAITIENTINFO };
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
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	BOOL InitPaitientInfoForm();

	CMyBCGPListCtrl m_PatientInfoList;
	virtual void OnInitialUpdate();
};


