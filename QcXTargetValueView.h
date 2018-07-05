#pragma once

#include "ReportGenerator\ReportGenerator.h"
// CQcXTargetValueView �Ի���

class CQcXTargetValueView : public CDialogEx
{
	DECLARE_DYNAMIC(CQcXTargetValueView)

public:
	CQcXTargetValueView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CQcXTargetValueView();

	// �Ի�������
	enum { IDD = IDD_QC_X_TARGETVALUE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CMyBCGPListCtrl m_QcXTargetValueList;
	void			InitTargetValueList();
	afx_msg void	OnPaint();
	virtual BOOL	OnInitDialog();
	afx_msg HBRUSH  OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	void	createEdit(NM_LISTVIEW  *pEditCtrl, CEdit *createdit, int &Item, int &SubItem, bool &havecreat);
	void	distroyEdit(CListCtrl *list, CEdit* distroyedit, int &Item, int &SubItem);

	afx_msg void	OnNMClickQcXTargetvalueList(NMHDR *pNMHDR, LRESULT *pResult);
	int				e_QcXItem;    //�ձ༭����  
	int				e_QcXSubItem; //�ձ༭����  
	CEdit			m_QcXTargetEdit;
	bool			isQcXEditcreated;//��־�༭���Ѿ�������
	static	int		item_focused;
	int nRow;

	CString			tempXNumber;
	CString			tempXDeadline;
	CString			Qctarget[26];
	CString			TargetLimit[26];	//ƫ����
	unsigned char	QcXFileExist;		//0:�ļ�δʹ�ã�1:�ļ���ʹ��


	//char			Qctype;
	void			GetQcLimitData();
	afx_msg void	OnQcXTargetConfirm();
	afx_msg void	OnQcXRangeConfirm();
	bool			JudgmentValid(CString Content);
	bool			GetQcFile();
	void			UpdateView();//���½����е�����
	//	int			GetEditFileCount(int controlType,int fileNum);

	CFont			textfont;
	CReportGenerator m_XreportGenerator;
	afx_msg void OnBnClickedPrintTarget();
};
