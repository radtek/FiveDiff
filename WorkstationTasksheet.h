#pragma once
#include "Includes_app.h"
#include "BCGPButton.h"
#include <vector>
using namespace std;
// CWorkstationTasksheet �Ի���

class CWorkstationTasksheet : public CDialogEx
{
	DECLARE_DYNAMIC(CWorkstationTasksheet)

public:
	CWorkstationTasksheet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWorkstationTasksheet();

// �Ի�������
	enum { IDD = IDD_WORKSTATION_TASKSHEET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CMyBCGPListCtrl m_WorkstationTasklist;
	bool InitTaskList();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void	ChangeSize(CWnd *pWnd, int cx, int cy);
	CRect	m_rect;
	afx_msg void	OnPaint();
	CBCGPButton		m_addtask;
	afx_msg void	OnBnClickedAddtask();
	afx_msg void	OnBnClickedDeletetask();
	CBCGPButton		m_deletetask;
	task_info		m_tasksheettask;
	void			AddSingleTask(task_info*  taskdata);
	int				TaskNum;
	int				CurrentTask;
	vector<task_info> m_alltask;
	static int		autogeneratetimes;
	bool			autogenerate;
	static int		startnum;
	afx_msg void	OnClose();
	virtual void	OnOK();
	virtual void	OnCancel();
	CBCGPButton		m_startexecute;
	afx_msg void	OnBnClickedStartexecution();
	void			UpdateTaskStatus(int number,int process);//����״̬ 0��δ���У� 1�����ڽ��У� 2�� ���Խ����� 3�� ����ʧ��
	void			UpdateTaskList(vector<task_info> taskdata);
	bool			CheckDifferent();
	void			LockTheButton();
	void			FreeTheButton();
protected:
	afx_msg LRESULT OnStartNextTask(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedClearsheet();
	CBCGPButton m_clearsheet;
protected:
	afx_msg LRESULT OnRestart(WPARAM wParam, LPARAM lParam);
};
