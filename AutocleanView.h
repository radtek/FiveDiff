#pragma once
#include "Includes_app.h"

// CAutocleanView �Ի���

class CAutocleanView : public CDialogEx
{
	DECLARE_DYNAMIC(CAutocleanView)

public:
	CAutocleanView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAutocleanView();
	CFont m_Font;
	CSpi m_spidev;
// �Ի�������
	enum { IDD = IDD_AUTOCLEAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedMianHydrAutoclean();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	afx_msg LRESULT OnAckspi(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnStnClickedAutoclean();
};
