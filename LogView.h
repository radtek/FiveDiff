#pragma once
//#include "BCGPChartExampleDoc.h"
//#include "BCGPChartExampleView.h"
//#include "afxcmn.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPChartCtrl.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPListBox.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPListCtrl.h"
//#include "CMyBCGPListCtrl.h"
#include "Includes_app.h"

// CLogView ������ͼ

class CLogView : public CBCGPChartExampleView
{
	DECLARE_DYNCREATE(CLogView)

protected:
	CLogView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CLogView();

public:
	enum { IDD = IDD_LOG };
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
	virtual void OnInitialUpdate();
	BOOL InitLogForm();


	CMyBCGPListCtrl m_LogList;
	int m_Logtype;
	afx_msg void OnBnClickedLogtypeRadio1();
};


