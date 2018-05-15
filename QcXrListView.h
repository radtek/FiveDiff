#pragma once


// CQcXrListView �Ի���

class CQcXrListView : public CDialogEx
{
	DECLARE_DYNAMIC(CQcXrListView)

public:
	CQcXrListView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CQcXrListView();

// �Ի�������
	enum { IDD = IDD_QC_XR_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CFont			textfont;
	CMyBCGPListCtrl	m_ListList;				//�б�ؼ��İ󶨶���

	int				curpage;					//��ǰҳ�룬���ڷ�ҳ
	int				maxPage;					//���ҳ��
	int				startIndex;				//��ǰҳ��ʼ�±�
	int				endIndex;					//��ǰҳ��ĩ�±�
	CString			pageNum;					//������ʾҳ���е�ǰҳ��
	int				itemCount;				//��¼����

	unsigned char	QcXrFileExist;				//0:�ļ�δʹ�ã�1:�ļ���ʹ��
	int 				qcXrListDataNum;			//��Ӧ�ʿط�ʽ���ļ��ļ�¼����
	CString			number;					//����
	CString			deadline;					//��Ч��
	double			qcAve[26];				//��ƽ��ֵ
	double			qcRan[26];				//��ƽ������

	double			data[26][62];				//�ʿؽ��,����ƽ��ֵ�ͼ���
	CString			qcResDate[31];			//�ʿ�����
	CString			qcResTime[31];			//�ʿ�ʱ��

	void			setQcAveRan();
	void			InitListList();
	void			UpdateListResultList();
	void			UpdateView();
	bool			GetQcXrEditData();
	int			GetQcXrResultData(int controltype, int controlfile);



	afx_msg void OnBnClickedQcXrListUpButton();
	afx_msg void OnBnClickedQcXrListDownButton();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnRedraw(WPARAM, LPARAM);

};
