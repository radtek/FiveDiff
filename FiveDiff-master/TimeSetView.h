#pragma once
#include "Includes_app.h"

// CTimeSetView �Ի���

class CTimeSetView : public CDialogEx
{
	DECLARE_DYNAMIC(CTimeSetView)

public:
	CTimeSetView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTimeSetView();

// �Ի�������
	enum { IDD = IDD_TIMESET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
