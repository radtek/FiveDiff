#pragma once


// CBackupRestoreView �Ի���

class CBackupRestoreView : public CDialogEx
{
	DECLARE_DYNAMIC(CBackupRestoreView)

public:
	CBackupRestoreView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBackupRestoreView();

// �Ի�������
	enum { IDD = IDD_BACKUP_RESTORE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
};
