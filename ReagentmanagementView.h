#pragma once
#include "Includes_app.h"

// CReagentmanagementView �Ի���

class CReagentmanagementView : public CDialogEx
{
	DECLARE_DYNAMIC(CReagentmanagementView)

public:
	CReagentmanagementView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CReagentmanagementView();

// �Ի�������
	enum { IDD = IDD_REAGENT_MANAGEMENT };
	CFont m_Font;
	CSpi m_spidev;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedMaintenanceWeeklyOk1();
	afx_msg void OnBnClickedMaintenanceWeeklyOk2();
	afx_msg void OnBnClickedMaintenanceYearly();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	afx_msg LRESULT OnAckspi(WPARAM wParam, LPARAM lParam);
};
