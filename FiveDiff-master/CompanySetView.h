#pragma once
#include "Includes_app.h"

// CCompanySetView �Ի���

class CCompanySetView : public CDialogEx
{
	DECLARE_DYNAMIC(CCompanySetView)

public:
	CCompanySetView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCompanySetView();

// �Ի�������
	enum { IDD = IDD_COMPANYSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
