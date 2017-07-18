#pragma once
#include "Includes_app.h"
#include "afxwin.h"

// CCorrectParaSetView �Ի���

class CCorrectParaSetView : public CDialogEx
{
	DECLARE_DYNAMIC(CCorrectParaSetView)

public:
	CCorrectParaSetView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCorrectParaSetView();

// �Ի�������
	enum { IDD = IDD_CORRECTEPARASET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	int m_modeRadio;
	int m_testmodeRadio;
	uchar		TestMode;
	afx_msg void OnBnClickedModifysetWholeblood();
	afx_msg void OnBnClickedModifysetDiluent();
	afx_msg void OnBnClickedModifysetCbc5diff();
	afx_msg void OnBnClickedModifysetCbc();
	virtual BOOL OnInitDialog();
	void ShowModifyPara();
	afx_msg void OnParaSetSave();
};
