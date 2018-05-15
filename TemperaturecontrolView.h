#pragma once
#include "Includes_app.h"

// CTemperaturecontrolView �Ի���

class CTemperaturecontrolView : public CDialogEx
{
	DECLARE_DYNAMIC(CTemperaturecontrolView)

public:
	CTemperaturecontrolView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTemperaturecontrolView();
	CFont m_Font;
	CSpi m_spidev;
	CEdit * Tem_Env;
	CEdit * Tem_Inc;
	int Tem_Set_Env;
	int Tem_Set_Inc;
// �Ի�������
	enum { IDD = IDD_TEMPERATURE_CONTROL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	
	afx_msg void OnBnClickedTmctrlTmsetOk();
	void SendSysPara(void);
};
