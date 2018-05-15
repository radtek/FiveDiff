#pragma once
#include "Includes_app.h"

// CConcentratecleanView �Ի���

class CConcentratecleanView : public CDialogEx
{
	DECLARE_DYNAMIC(CConcentratecleanView)

public:
	CConcentratecleanView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CConcentratecleanView();
	CFont m_Font;
	CSpi m_spidev;
// �Ի�������
	enum { IDD = IDD_CONCENTRATECLEAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedConcentratedcleanOk1();
	afx_msg void OnBnClickedConcentratedcleanOk2();
	afx_msg void OnBnClickedConcentratedcleanEsc();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	afx_msg LRESULT OnAckspi(WPARAM wParam, LPARAM lParam);
public:
	void ShowCloseMess();
	
};
