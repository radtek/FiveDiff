#pragma once
#include "Includes_app.h"

// CUnitSetView �Ի���

class CUnitSetView : public CDialogEx
{
	DECLARE_DYNAMIC(CUnitSetView)

public:
	CUnitSetView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUnitSetView();

// �Ի�������
	enum { IDD = IDD_UNITSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	int m_WBCunitRadio;
	int m_RBCunitRadio;
	int m_HGBunitRadio;
	int m_MCVunitRadio;
	int m_MCHunitRadio;
	int m_MCHCunitRadio;
	int m_PLTunitRadio;
	int m_MPVunitRadio;
	int m_PDWunitRadio;
	int m_OtherunitRadio;
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnUnitApplicate();
};
