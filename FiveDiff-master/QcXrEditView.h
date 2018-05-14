#pragma once


// CQcXrEditView �Ի���

class CQcXrEditView : public CDialogEx
{
	DECLARE_DYNAMIC(CQcXrEditView)

public:
	CQcXrEditView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CQcXrEditView();



// �Ի�������
	enum { IDD = IDD_QC_XR_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	unsigned int QcXrFileExist;
	CString tempXrNumber;
	CString tempXrDeadline;
	

	afx_msg void OnBnClickedQcXrEditEnter();
	bool getQcXrFile(bool loadData);
	//bool GetQcXEditData();
	void setQcXrEditData();
	CFont			textfont;
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
};
