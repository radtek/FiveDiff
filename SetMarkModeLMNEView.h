#pragma once


// CSetMarkModeLMNEView �Ի���

class CSetMarkModeLMNEView : public CDialogEx
{
	DECLARE_DYNAMIC(CSetMarkModeLMNEView)

public:
	CSetMarkModeLMNEView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetMarkModeLMNEView();
	CFont m_Font;
// �Ի�������
	enum { IDD = IDD_SetMarkModeLMNE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedSetlmnemodelOk();
	
	BOOL RAD_LMNE_Manual;
};
