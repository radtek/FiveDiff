#pragma once
#include "Includes_app.h"

// CSourcemanagementView �Ի���

class CSourcemanagementView : public CDialogEx
{
	DECLARE_DYNAMIC(CSourcemanagementView)

public:
	CSourcemanagementView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSourcemanagementView();

// �Ի�������
	enum { IDD = IDD_SOURCE_MANAGEMENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
