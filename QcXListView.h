#pragma once


// CQcXListView �Ի���

class CQcXListView : public CDialogEx
{
	DECLARE_DYNAMIC(CQcXListView)

public:
	CQcXListView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CQcXListView();

	// �Ի�������
	enum { IDD = IDD_QC_X_LIST };

	CFont			textfont;
	CMyBCGPListCtrl	m_ListList;				//�б�ؼ��İ󶨶���

	int				curpage;					//��ǰҳ�룬���ڷ�ҳ
	int				maxPage;					//���ҳ��
	int				startIndex;				//��ǰҳ��ʼ�±�
	int				endIndex;					//��ǰҳ��ĩ�±�
	CString			pageNum;					//������ʾҳ���е�ǰҳ��
	int				itemCount;				//��¼����

	unsigned char	QcXFileExist;				//0:�ļ�δʹ�ã�1:�ļ���ʹ��
	CString			number;					//����
	CString			deadline;					//��Ч��
	CString			Qctarget[26];				//��ֵ
	CString			TargetLimit[26];			//ƫ����

	double			data[26][31];				//�ʿؽ��
	CString			qcResDate[31];			//�ʿ�����
	CString			qcResTime[31];			//�ʿ�ʱ��

	void			InitListList();
	void			UpdateListResultList();
	void			UpdateView();
	bool			GetQcXEditData();
	int			GetQcXResultData(int controltype, int controlfile);



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedQcXListUpButton();
	afx_msg void OnBnClickedQcXListDownButton();
	afx_msg LRESULT OnRedraw(WPARAM, LPARAM);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedPrintX();
};
