#pragma once

//#include "Includes_app.h"
// CBCGPHeaderCtrl

class CMyBCGPHeaderCtrl : public CBCGPHeaderCtrl
{
	DECLARE_DYNAMIC(CMyBCGPHeaderCtrl)

public:
	CMyBCGPHeaderCtrl();
	virtual ~CMyBCGPHeaderCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();

public:
	CStringArray m_HChar;
	CString m_Format; //��ʾ�������͵���������,0��ʾ����룬1��ʾ�м���룬2��ʾ�Ҷ���
public:
	int m_R;
	int m_G;
	int m_B;
	int m_Gradient;	// �����屳��������ϵ��
	float m_Height;  //��ͷ�߶ȣ����Ǳ���,
	int m_fontHeight; //����߶�
	int m_fontWith;   //������
	COLORREF m_color;
	LRESULT OnLayout(WPARAM wParam, LPARAM lParam);
};

