
// NumerologyDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Numerology.h"
#include "NumerologyDlg.h"
#include "afxdialogex.h"
#include "locale.h"
#include "common.h"
#include <iostream>
#include <map>
#include <ctime>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CNumerologyDlg 对话框

BEGIN_DHTML_EVENT_MAP(CNumerologyDlg)
	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
END_DHTML_EVENT_MAP()


CNumerologyDlg::CNumerologyDlg(CWnd* pParent /*=nullptr*/)
	: CDHtmlDialog(IDD_NUMEROLOGY_DIALOG, IDR_HTML_NUMEROLOGY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	setlocale(LC_ALL, "chs");
	m_nSex = SEX_UNKOWN;

	time_t now = time(0);
	tm ltm;
	localtime_s(&ltm, &now);
	m_nCurYear = 1900 + ltm.tm_year;
	//cout << "年: " << 1900 + ltm->tm_year << endl;
	//cout << "月: " << 1 + ltm->tm_mon << endl;
	//cout << "日: " << ltm->tm_mday << endl;
	//cout << "时间: " << ltm->tm_hour << ":";
	
}

void CNumerologyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNumerologyDlg, CDHtmlDialog)
	ON_WM_SYSCOMMAND()
	ON_CBN_SELCHANGE(IDC_COMBO_YEAR, &CNumerologyDlg::OnCbnSelchangeComboYear)
	ON_BN_CLICKED(IDC_BUTTON_TIAN, &CNumerologyDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO_MALE, &CNumerologyDlg::OnBnClickedRadioMale)
	ON_BN_CLICKED(IDC_RADIO_FEMALE, &CNumerologyDlg::OnBnClickedRadioFemale)
	ON_BN_CLICKED(IDC_BUTTON_PERSON, &CNumerologyDlg::OnBnClickedButtonPerson)
END_MESSAGE_MAP()


// CNumerologyDlg 消息处理程序


CString CharToCString(char *str) {
	CString m_str;
	int  charLen = strlen(str);
	int len = MultiByteToWideChar(CP_ACP, 0, str, charLen, NULL, 0);
	TCHAR* buf = new TCHAR[len + 1];
	MultiByteToWideChar(CP_ACP, 0, str, charLen, buf, len);
	buf[len] = '\0';

	m_str.Append(buf);
	delete[]buf;
	return m_str;
}


BOOL CNumerologyDlg::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MAXIMIZE);

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码

	CComboBox *year = (CComboBox*)GetDlgItem(IDC_COMBO_YEAR);
	CString str;
	for (int y = 1900; y <= m_nCurYear; y++)
	{
		str.Format(_T("%d"), y);
		year->AddString(str);
	}

	CComboBox* mon = (CComboBox*)GetDlgItem(IDC_COMBO_MON);
	int len, charLen;
	for (int i = 0; i < 12; i++)
	{
		mon->InsertString(i, CharToCString(mon_str[i]));
	}

	CComboBox* day = (CComboBox*)GetDlgItem(IDC_COMBO_DAY);
	for (int i = 0; i < 30; i++)
	{
		day->InsertString(i, CharToCString(day_str[i]));
	}

	CComboBox* hour = (CComboBox*)GetDlgItem(IDC_COMBO_HOUR);
	for (int i = 0; i < 12; i++)
	{
		hour->InsertString(i, CharToCString(hour_str[i]));
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CNumerologyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDHtmlDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CNumerologyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDHtmlDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CNumerologyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HRESULT CNumerologyDlg::OnButtonOK(IHTMLElement* /*pElement*/)
{
	OnOK();
	return S_OK;
}

HRESULT CNumerologyDlg::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;
}


void CNumerologyDlg::OnCbnSelchangeComboYear()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CNumerologyDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (0 == m_nSex)
	{
		MessageBox(TEXT("请选择您的性别"),TEXT("性别"),MB_OKCANCEL);
		return;
	}

	CString y;
	CComboBox *year =  (CComboBox*)GetDlgItem(IDC_COMBO_YEAR);
	int index = year->GetCurSel();
	year->GetLBText(index, y);
	if (y.IsEmpty())
	{
		MessageBox(TEXT("请输入您的出身年份"), TEXT("请输入您的出身年份"), MB_OKCANCEL);
		//MessageBeep(0);

	}
	else
	{
		CString age_info;
		char buf[256];
		memset(buf, 0, 256);
		int age = 2021 - atoi(CT2A(y.GetBuffer())) + 1;

		if (m_nSex == MALE)
		{
			sprintf_s(buf, "%s:%d,%s%s%s\n", "您的年龄(虚岁)是,", age, "您今年的照命为", male_star[age % 9], "星照命");
		}
		else if (m_nSex == FEMALE)
		{
			sprintf_s(buf, "%s:%d,%s%s%s\n", "您的年龄(虚岁)是,", age,"您今年的照命为", female_star[age%9],"星照命");
		}

		
		age_info = CharToCString(buf);

		MessageBox(age_info, TEXT("天时"), MB_OK);
	}


}

void CNumerologyDlg::OnBnClickedButtonPerson()
{
	if (0 == m_nSex)
	{
		MessageBox(TEXT("请选择您的性别"), TEXT("性别"), MB_OKCANCEL);
		return;
	}

	CString y;
	CComboBox* year = (CComboBox*)GetDlgItem(IDC_COMBO_YEAR);
	int index = year->GetCurSel();
	year->GetLBText(index, y);
	if (y.IsEmpty())
	{
		MessageBox(TEXT("请输入您的出身年份"), TEXT("请输入您的出身年份"), MB_OKCANCEL);
		//MessageBeep(0);

	}
	else
	{
		CString person_info;
		char buf[256];
		memset(buf, 0, 256);

		int huajiaYear = (atoi(CT2A(y.GetBuffer())) + 2697 - 1) % 60; // -(-2697) 公元前837年为甲子年  公元前2697年为第一个甲子年


		sprintf_s(buf, "%s%s%s%s%s%s\n", "您为", huajiaStr[huajiaYear] , "年生人,属", zodiacStr[huajiaYear%12] ,",出生命运为:", huajiaFateStr[huajiaYear]);

		person_info = CharToCString(buf);

		MessageBox(person_info, TEXT("天时"), MB_OK);
	}

}


void CNumerologyDlg::OnBnClickedRadioMale()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nSex = MALE;
}


void CNumerologyDlg::OnBnClickedRadioFemale()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nSex = FEMALE;
}
