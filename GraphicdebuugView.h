#pragma once
#include "Includes_app.h"

// CGraphicdebuugView �Ի���

class CGraphicdebuugView : public CDialogEx
{
	DECLARE_DYNAMIC(CGraphicdebuugView)

public:
	CGraphicdebuugView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGraphicdebuugView();

// �Ի�������
	enum { IDD = IDD_GRAPHIC_DEBUG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
