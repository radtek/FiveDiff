#pragma once
#include "Includes_app.h"

// CPLTSetView �Ի���

class CPLTSetView : public CDialogEx
{
	DECLARE_DYNAMIC(CPLTSetView)

public:
	CPLTSetView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPLTSetView();

// �Ի�������
	enum { IDD = IDD_PLTSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnApplicate();

public:
	int m_pltmodeRadio;
	CFont font, font1;
};
