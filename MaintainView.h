#pragma once
#include "Includes_app.h"

// CMaintainView �Ի���

class CMaintainView : public CDialogEx
{
	DECLARE_DYNAMIC(CMaintainView)

public:
	CMaintainView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMaintainView();

// �Ի�������
	enum { IDD = IDD_MAINTAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
