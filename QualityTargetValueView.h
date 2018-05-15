#pragma once
#include "CMyBCGPListCtrl.h"


// CQualityTargetValueView �Ի���
extern qc_edit_data_info qcLjEditData;
class CQualityTargetValueView : public CDialogEx
{
	DECLARE_DYNAMIC(CQualityTargetValueView)

public:
	CQualityTargetValueView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CQualityTargetValueView();

// �Ի�������
	enum { IDD = IDD_QUALITY_TARGETVALUE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CMyBCGPListCtrl m_TargetValueList;
	void			InitTargetValueList();
	afx_msg void	OnPaint();
	virtual BOOL	OnInitDialog();
	afx_msg HBRUSH  OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	void	createEdit(NM_LISTVIEW  *pEditCtrl, CEdit *createdit, int &Item, int &SubItem, bool &havecreat);
	void	distroyEdit(CListCtrl *list, CEdit* distroyedit, int &Item, int &SubItem);

	afx_msg void	OnNMClickQualityTargetvalueList(NMHDR *pNMHDR, LRESULT *pResult);
	int				e_Item;    //�ձ༭����  
	int				e_SubItem; //�ձ༭����  
	CEdit			m_QualityTargetEdit;
	bool			haveeditcreate;//��־�༭���Ѿ�������
	static	int		item_focused;
	int nRow;

	CString			tempLjNumber;
	CString			tempLjDeadline;
	CString			Qctarget[26];
	CString			TargetLimit[26];	//ƫ����
	unsigned char	QcLjFileExist;		//0:�ļ�δʹ�ã�1:�ļ���ʹ��
	

	//char			Qctype;
	void			GetQcLimitData();
	afx_msg void	OnQualitytargetConfirm();
	afx_msg void	OnRangeConfirm();
	bool			JudgmentValid(CString Content);
	bool			GetQcFile();
	void			UpdateView();//���½����е�����
//	int			GetEditFileCount(int controlType,int fileNum);

	CFont			textfont;

};
