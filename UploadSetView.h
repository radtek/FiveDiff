#pragma once
#include "Includes_app.h"

// CUploadSetView �Ի���

class CUploadSetView : public CDialogEx
{
	DECLARE_DYNAMIC(CUploadSetView)

public:
	CUploadSetView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUploadSetView();

// �Ի�������
	enum { IDD = IDD_UPLOADSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
