#pragma once
#include "Includes_app.h"

// CDevelopmentSetView �Ի���

class CDevelopmentSetView : public CDialogEx
{
	DECLARE_DYNAMIC(CDevelopmentSetView)

public:
	CDevelopmentSetView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDevelopmentSetView();

// �Ի�������
	enum { IDD = IDD_DEVELOPMENTSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();

	afx_msg void OnBnClickedApply();
	int m_structureRadio;
	int m_diluentRadio;
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
