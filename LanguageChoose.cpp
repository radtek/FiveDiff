// LanguageChoose.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "LanguageChoose.h"
#include "afxdialogex.h"
#include "MainFrm.h"


// CLanguageChoose �Ի���

IMPLEMENT_DYNAMIC(CLanguageChoose, CDialogEx)

BOOL m_bRestartFlag;
extern HWND mainhwnd;
CLanguageChoose::CLanguageChoose(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLanguageChoose::IDD, pParent)
	//, m_languageChoose(0)
{

}

CLanguageChoose::~CLanguageChoose()
{
}

void CLanguageChoose::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_CHINESE, m_languageChoose);
}


BEGIN_MESSAGE_MAP(CLanguageChoose, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLanguageChoose::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CLanguageChoose::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_RADIO_CHINESE, &CLanguageChoose::OnBnClickedRadioChinese)
	ON_BN_CLICKED(IDC_RADIO_ENGLISH, &CLanguageChoose::OnBnClickedRadioEnglish)
	ON_BN_CLICKED(IDC_RADIO_FRENCH, &CLanguageChoose::OnBnClickedRadioFrench)
	ON_BN_CLICKED(IDC_RADIO_RUSSIAN, &CLanguageChoose::OnBnClickedRadioRussian)
	ON_BN_CLICKED(IDC_RADIO_SPANISH, &CLanguageChoose::OnBnClickedRadioSpanish)
END_MESSAGE_MAP()


// CLanguageChoose ��Ϣ�������


BOOL CLanguageChoose::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	LCID lcidNew = GetThreadUILanguage();
	int curLang = PRIMARYLANGID(LANGIDFROMLCID(lcidNew));
	switch (curLang){
	case LANG_CHINESE:
		((CButton*)GetDlgItem(IDC_RADIO_CHINESE))->SetCheck(1);
		break;
	case LANG_ENGLISH:
		((CButton*)GetDlgItem(IDC_RADIO_ENGLISH))->SetCheck(1);
		break;
	case LANG_FRENCH:
		((CButton*)GetDlgItem(IDC_RADIO_FRENCH))->SetCheck(1);
		break;
	case LANG_RUSSIAN:
		((CButton*)GetDlgItem(IDC_RADIO_RUSSIAN))->SetCheck(1);
		break;
	case LANG_SPANISH:
		((CButton*)GetDlgItem(IDC_RADIO_SPANISH))->SetCheck(1);
		break;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CLanguageChoose::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//����ѡ�д�������ļ���
	LCID lcidNew = GetThreadUILanguage();
	int curLang = PRIMARYLANGID(LANGIDFROMLCID(lcidNew));
	switch (m_languageChoose){
	case 0://chinese
		if (curLang == LANG_CHINESE){//��ǰ����Ϊ���ģ����л�
			return;
		}
		else{						//����,�л���ǰ����Ϊ����
			lcidNew = MAKELCID(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED),
				SORT_DEFAULT);
		}

		break;
	case 1://english
		if (curLang == LANG_ENGLISH){//��ǰ����ΪӢ�ģ����л�
			return;
		}
		else{						//����,�л���ǰ����ΪӢ��
			lcidNew = MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
				SORT_DEFAULT);
		}

		break;
	case 2://french
		if (curLang == LANG_FRENCH){//��ǰ����Ϊ���ģ����л�
			return;
		}
		else{						//����,�л���ǰ����Ϊ����
			lcidNew = MAKELCID(MAKELANGID(LANG_FRENCH, SUBLANG_FRENCH),
				SORT_DEFAULT);
		}

		break;
	case 3://russian
		if (curLang == LANG_RUSSIAN){//��ǰ����Ϊ���ģ����л�
			return;
		}
		else{						//����,�л���ǰ����Ϊ����
			lcidNew = MAKELCID(MAKELANGID(LANG_RUSSIAN, SUBLANG_RUSSIAN_RUSSIA),
				SORT_DEFAULT);
		}

		break;
	case 4:// spanish
		if (curLang == LANG_SPANISH){//��ǰ����Ϊ�������ģ����л�
			return;
		}
		else{						//����,�л���ǰ����Ϊ��������
			lcidNew = MAKELCID(MAKELANGID(LANG_SPANISH, SUBLANG_SPANISH),
				SORT_DEFAULT);
		}

		break;

	}



	////�л�����
	//// ��ȡ��ǰ�̵߳����ԣ������ݵ�ǰ�߳����Խ��������л�
	//LCID lcidNew = GetThreadUILanguage();
	//if (LANG_ENGLISH == PRIMARYLANGID(LANGIDFROMLCID(lcidNew)))//��ǰ����ΪӢ��
	//{
	//	lcidNew = MAKELCID(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED),
	//		SORT_DEFAULT);
	//}
	//else
	//{
	//	lcidNew = MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
	//		SORT_DEFAULT);
	//}

	// ����������д�������ļ�
	CFile file;
	file.Open(_T("Language.ini"), CFile::modeWrite | CFile::modeCreate | CFile::typeBinary);
	file.Write(&lcidNew, sizeof(lcidNew));
	file.Close();

	// �رմ���
	m_bRestartFlag = TRUE;
	//CWnd* mainwnd = AfxGetMainWnd();
	::PostMessageW(mainhwnd, WM_CLOSE, 0, 0);
	//PostMessage( WM_CLOSE, 0, 0);
	CDialogEx::OnOK();
}


void CLanguageChoose::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CLanguageChoose::OnBnClickedRadioChinese()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_languageChoose = 0;
}


void CLanguageChoose::OnBnClickedRadioEnglish()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_languageChoose = 1;
}


void CLanguageChoose::OnBnClickedRadioFrench()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_languageChoose = 2;
}


void CLanguageChoose::OnBnClickedRadioRussian()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_languageChoose = 3;
}


void CLanguageChoose::OnBnClickedRadioSpanish()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_languageChoose = 4;
}

