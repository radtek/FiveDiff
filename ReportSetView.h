#pragma once
#include "Includes_app.h"

// CReportSetView �Ի���

class CReportSetView : public CDialogEx
{
	DECLARE_DYNAMIC(CReportSetView)

public:
	CReportSetView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CReportSetView();

// �Ի�������
	enum { IDD = IDD_REPORTSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
