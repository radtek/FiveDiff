#pragma once


// CManualCalibrationView �Ի���

class CManualCalibrationView : public CDialogEx
{
	DECLARE_DYNAMIC(CManualCalibrationView)

public:
	CManualCalibrationView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CManualCalibrationView();

// �Ի�������
	enum { IDD = IDC_MANUAL_CALIBRATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int			m_moderadio;
	int			m_testmoderadio;
	uchar		TestMode;
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnModeRadio();
	afx_msg void OnModeRadio2();
	afx_msg void OnTestmodeRadio();
	afx_msg void OnTestmodeRadio2();

	void ShowCalibration();
};
