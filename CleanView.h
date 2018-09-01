#pragma once
#include "Includes_app.h"

// CCleanView �Ի���

class CCleanView : public CDialogEx
{
	DECLARE_DYNAMIC(CCleanView)

public:
	CCleanView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCleanView();

// �Ի�������
	enum { IDD = IDD_WASH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	void CleanChannel(char* Mess, uchar CMD);
	void SetWindowEnabled();
	void SetWindowDisabled();

	CSpi m_spidev;
	afx_msg void OnCleanCyto();
	afx_msg void OnCleanChambers();
	afx_msg void OnCleanDiluentintine();
	afx_msg void OnCleanDiluentextine();
	afx_msg void OnCleanGem();
	afx_msg void OnCleanSheatflowpipe();
	afx_msg void OnCleanRinsebaso();
	afx_msg void OnCleanRinseintine();
	afx_msg void OnCleanRinseextine();
	afx_msg void OnCleanExternneedle();

	static unsigned char ExterCleanFlag;	//�ⲿ����ϴ��־��1-�ⲿ����ϴ
	static unsigned char ExterCleanStep;	//�ⲿ��ϴ���裬0-��ʼ״̬��1-��һ����ɣ�2-�ڶ�����ɣ�3-��������ɣ�4-���Ĳ����
protected:
	afx_msg LRESULT OnAckspi(WPARAM wParam, LPARAM lParam);
};
