#pragma once


// CMultiLangTest �Ի���

class CMultiLangTest : public CDialogEx
{
	DECLARE_DYNAMIC(CMultiLangTest)

public:
	CMultiLangTest(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMultiLangTest();

// �Ի�������
	enum { IDD = IDD_MULTILANG_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
