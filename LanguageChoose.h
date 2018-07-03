#pragma once


// CLanguageChoose �Ի���

class CLanguageChoose : public CDialogEx
{
	DECLARE_DYNAMIC(CLanguageChoose)

public:
	CLanguageChoose(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLanguageChoose();

	// �Ի�������
	enum { IDD = IDD_LANGUAGE_CHOOSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	int m_languageChoose;
	afx_msg void OnBnClickedRadioChinese();
	afx_msg void OnBnClickedRadioEnglish();
	afx_msg void OnBnClickedRadioFrench();
	afx_msg void OnBnClickedRadioRussian();
	afx_msg void OnBnClickedRadioSpanish();
	virtual BOOL OnInitDialog();
};
