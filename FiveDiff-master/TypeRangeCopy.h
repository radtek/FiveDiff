#pragma once
#include "afxwin.h"


// CTypeRangeCopy �Ի���

class CTypeRangeCopy : public CDialogEx
{
	DECLARE_DYNAMIC(CTypeRangeCopy)

public:
	CTypeRangeCopy(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTypeRangeCopy();

// �Ի�������
	enum { IDD = IDD_TYPERANGE_COPY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnOK();
	virtual void OnCancel();

	CString pasteName[10];
	CComboBox m_copyCombo;
};
