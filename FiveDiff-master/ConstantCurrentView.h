#pragma once

#include "Includes_app.h"

// CConstantCurrentView �Ի���

class CConstantCurrentView : public CDialogEx
{
	DECLARE_DYNAMIC(CConstantCurrentView)

public:
	CConstantCurrentView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CConstantCurrentView();
	CFont m_Font;
	CSpi m_spidev;
// �Ի�������
	enum { IDD = IDD_CONSTANTCURRENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedConstantcurrentRbc();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedConstantcurrentBaso();
	afx_msg void OnBnClickedConstantcurrentLmne();
	afx_msg void OnBnClickedCancel();
};
