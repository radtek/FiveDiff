#pragma once
#include "Includes_app.h"

// CCleantankView �Ի���

class CCleantankView : public CDialogEx
{
	DECLARE_DYNAMIC(CCleantankView)

public:
	CCleantankView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCleantankView();

// �Ի�������
	enum { IDD = IDD_CLEAN_TANK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
