#pragma once
#include "Includes_app.h"

// CThresholdSetView �Ի���

class CThresholdSetView : public CDialogEx
{
	DECLARE_DYNAMIC(CThresholdSetView)

public:
	CThresholdSetView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CThresholdSetView();

// �Ի�������
	enum { IDD = IDD_THRESHOLDSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnThresholdApplicate();
};
