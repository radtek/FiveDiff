#pragma once
#include "BCGPDateTimeCtrl.h"
#include "BCGPComboBox.h"
#include "BCGPButton.h"


// CAddTaskView �Ի���

class CAddTaskView : public CDialogEx
{
	DECLARE_DYNAMIC(CAddTaskView)

public:
	CAddTaskView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddTaskView();

// �Ի�������
	enum { IDD = IDD_WORKSTATION_ADDTASK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	CRect		 m_rect;
	void		 ChangeSize(CWnd *pWnd, int cx, int cy); 
	bool		 GetTaskInfo();
	task_info	 m_task;
	CBCGPDateTimeCtrl m_testtime;
	int			 m_nFirstDayOfWeek;
	CString		 m_barcode;

	CBCGPComboBox m_addtasksex;
	bool		GenerateNumAuto;
	afx_msg void OnEnSetfocusAddtaskBarcode();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	static DWORD WINAPI	BarcodeCheck(LPVOID lpParam);
	HANDLE   hThread;

protected:
	afx_msg LRESULT OnGetbarcode(WPARAM wParam, LPARAM lParam);
public:
	int			 m_taskmode;
	afx_msg void OnBnClickedTaskmodeRadio1();
	void		 LocktheControl();
	void		 FreetheControl();
	void		 InitTaskdata(task_info &taskdata);
	CBCGPButton  m_OK;
	CBCGPButton  m_CANCEL;
};
