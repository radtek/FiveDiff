#pragma once
#include "Includes_app.h"

// CEmptyView �Ի���

class CEmptyView : public CDialogEx
{
	DECLARE_DYNAMIC(CEmptyView)

public:
	CEmptyView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEmptyView();
	CSpi m_spidev;
// �Ի�������
	enum { IDD = IDD_EMPTY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedDrainWaste();
	void DrainReagent(char * Mess, uchar CMD, unsigned int m_ntime);
	afx_msg void OnBnClickedDrainRinse();
	afx_msg void OnBnClickedDrainHgb();
	afx_msg void OnBnClickedDrainRbc();
	afx_msg void OnBnClickedDrainBaso();
	afx_msg void OnBnClickedDrainLmne();
	afx_msg void OnBnClickedDrainAll();
	afx_msg void OnBnClickedDrainDiluentPot();
	afx_msg void OnBnClickedDrainCtm();
	afx_msg void OnBnClickedDrainPipe();
	afx_msg void OnBnClickedDrainEscape();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	afx_msg LRESULT OnAckspi(WPARAM wParam, LPARAM lParam);
public:
	void SetWindowDisable();
	void SetWindowEnable();
};
