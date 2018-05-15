#pragma once
#include "Includes_app.h"

// CPerfusionView �Ի���

class CPerfusionView : public CDialogEx
{
	DECLARE_DYNAMIC(CPerfusionView)

public:
	CPerfusionView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPerfusionView();

// �Ի�������
	enum { IDD = IDD_PERFUSION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPrimeDiluent();
	afx_msg void OnPrimeRinse();
	afx_msg void OnPrimeLmnefix();
	afx_msg void OnPrimeWbclyse();
	afx_msg void OnPrimeHgblyse();
	afx_msg void OnPrimeAll();
	afx_msg void OnPrimeReversedprime();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void PrimeReagent(char* Mess, uchar CMD);
	void SetWindowEnable();
	void SetWindowDisable();
	CSpi m_spidev;
	
protected:
	afx_msg LRESULT OnAckspi(WPARAM wParam, LPARAM lParam);
	int RinseMode;
};
