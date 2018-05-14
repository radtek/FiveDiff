#pragma once
#include "Includes_app.h"

// CAutoMaintenanceSetView �Ի���

class CAutoMaintenanceSetView : public CDialogEx
{
	DECLARE_DYNAMIC(CAutoMaintenanceSetView)

public:
	CAutoMaintenanceSetView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAutoMaintenanceSetView();

// �Ի�������
	enum { IDD = IDD_AUTOMAINTENANCESET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	int m_microperfusiontimeRadio;
	CFont font,font1;
	virtual BOOL OnInitDialog();
	afx_msg void OnApplicateMantainset();

	BOOL SaveIntervalFrequency();
	afx_msg void OnRecoil();
};
