#pragma once
#include "Includes_app.h"

// CReabentalarmView �Ի���

class CReabentalarmView : public CDialogEx
{
	DECLARE_DYNAMIC(CReabentalarmView)

public:
	CReabentalarmView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CReabentalarmView();
	CFont m_Font;
// �Ի�������
	enum { IDD = IDD_REAGENT_ALARM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRegentsetOk();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
