#pragma once


// CBackupSetView �Ի���

class CBackupSetView : public CDialogEx
{
	DECLARE_DYNAMIC(CBackupSetView)

public:
	CBackupSetView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBackupSetView();

// �Ի�������
	enum { IDD = IDD_BACKUP_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	void	ChangeSize(CWnd *pWnd, int cx, int cy);

	CRect  m_rect;
};
