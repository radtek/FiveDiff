#pragma once


// CQualityFileExit �Ի���
extern int rc;
class CQualityFileExit : public CDialogEx
{
	DECLARE_DYNAMIC(CQualityFileExit)

public:
	CQualityFileExit(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CQualityFileExit();

// �Ի�������
	enum { IDD = IDD_QUALITY_FILEEXIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnPaint();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	CFont		 textfont;

};
