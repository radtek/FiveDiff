#pragma once
#include "afxwin.h"


// CBASOLandmarkView �Ի���

class CBASOLandmarkView : public CDialogEx
{
	DECLARE_DYNAMIC(CBASOLandmarkView)

public:
	CBASOLandmarkView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBASOLandmarkView();
	CFont m_Font;
// �Ի�������
	enum { IDD = IDD_BASO_LANDMARK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	CEdit* Edit_BASO1;
	CEdit* Edit_BASO2;
	CEdit* Edit_BASO3;
	afx_msg void OnBnClickedOk();
};
