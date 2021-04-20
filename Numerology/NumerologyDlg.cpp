
// NumerologyDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Numerology.h"
#include "NumerologyDlg.h"
#include "afxdialogex.h"
#include "locale.h"
#include <iostream>
#include <map>

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
END_MESSAGE_MAP()


// CNumerologyDlg 消息处理程序

static char *mon_str[12] = {"正月", "二月", "三月", "四月", "五月", "六月", "七月", "八月", "九月", "十月", "冬月", "腊月"};
static char* day_str[30] = {"初一","初二","初三","初四","初五","初六","初七","初八","初九","初十","十一","十二","十三","十四","十五","十六","十七","十八","十九","廿十","廿一","廿二","廿三","廿四","廿五","廿六","廿七","廿八","廿九","三十" };
static char* hour_str[12] = { "子时(23:00-01:00)","丑时(01:00-03:00)","寅时(03:00-05:00)","卯时(05:00-07:00)","辰时(07:00-09:00)","巳时(09:00-11:00)","午时(11:00-13:00)","未时(13:00-15:00)","申时(15:00-17:00)","酉时(17:00-19:00)","戌时(19:00-21:00)","亥时(21:00-23:00)" };


// 九星照命算法，虚岁模9取余，余数与照命之星如下对应关系
// 男九星照命
//    0     1     2     3     4      5    6    7    8  
//   木星  罗睺  土星  水星  金星  太阳  火星 计都 太阴 


// 女九星照命
//   0     1     2     3     4     5     6      7    8  
//  水星  计都  火星  木星  太阴  土星  罗睺  太阳  金星

static char* male_star[9] = {"木星","罗睺","土星","水星","金星","太阳","火星","计都","太阴"};
static char* female_star[9] = {"水星","计都","火星","木星","太阴" ,"土星", "罗睺","太阳", "金星" };


//
//⑴太阳星照命（吉星，盛运。万事吉，防冬季有失或不顺）
//行年值太阳，男人呈吉祥。添人又进口，终岁保安康。
//克命则不吉，凡事细商量。女命遇太阳，克命有灾殃。
//⑵太阴星照命（吉星，进运。知其进退，定会成功）
//行年值太阴，诸事皆遂心。男女均相宜，凡事有贵人。
//克命不为喜，女命尤需慎。生身运气旺，名利两相衬。
//⑶罗睺星照命（凶星，潜运。凡事谨慎，待机而动，防是非病难）
//行年值罗睺，事事多忧愁。男逢遭灾祸，女遇也担忧。
//口舌是非起，灾厄不时有。平素多晦气，克命祸临头。
//⑷计都星照命（凶星，死运。静守勿动，防受损有病）
//行年值计都，凡事皆忧愁。男逢也可怕，小心摔跟头。
//是非口舌多，独木难行舟。女逢更可畏，克命祸临头。
//⑸木星照命（吉星，吉运。凡事勿急，好事自成）
//行年值木星，全年保安宁。家宅多吉祥，和顺又昌明。
//克命则不吉，刀光掠血影。女命也犯忌，受克事难成。
//⑹水星照命（吉星，喜运。防色情口舌，乐极生悲）
//行年值水星，财源多丰盛。男人更可喜，福寿均增生。
//命若不受克，凡事皆顺景。男女均怕克，受克祸不轻。
//⑺金星照命（凶星，生运。明月被遮蔽，谋事皆难成）
//行年值金星，灾祸易生成。男逢忧虑大，女逢苦伶仃。
//生身还算好，受克灾不轻。血光孝服事，也难脱干净。
//⑻土星照命（中性星，开运）
//行年值土星，小心起官灾。出入多不吉，须防小人害。
//小心上半年，到秋灾不来。受克烦恼多，生身则悠哉。
//⑼火星照命（凶星，休运。进退两难，不可强行）
//行年值火星，噩运心生惊。女人多灾难，男人不离刑。
//疾病绕身转，闺房闻哭声。生身灾可免，受克灾不轻。
//
//三 九星解释
//⑴太阳星：名云太阳星
//光辉天下，无处不明朗。主远行有财，大人见喜，添人进口，万事和合。女人不喜此星，禳解方吉。
//⑵太阴星：名云注阳星
//见官有理。男人出入，凡事遂心。女人有疾厄、产患之难。
//⑶罗睺星：名云口舌星
//主有官非口舌，眼目之疾。女人见血光产厄之灾。
//⑷计都星：名云凶星
//大人不利，六畜不旺，阴人有口舌是非。出入远行有财，在家有暗昧不明之事。
//⑸木星：名云朝元星
//其人男人宜有眼目之疾。阴人有血光之灾，不妨。婚姻相合，人口平安。
//⑹水星：名云福禄星
//大人见喜，远行有财，添人进口。女人不得凶灾，男人不宜渡河。
//⑺金星：名云朝阳星
//贵人见喜，添人进口。婚姻嫁娶，恐有肚腹之灾。出入提防小人。
//⑻土星：名云厄星
//此年见灾不安，家宅啾唧、怪梦。六畜不旺，不利远行。
//⑼火星：名云灾星
//主疮疾。女人产难血光，男人官灾不利。人口不安，六畜不旺，自宜谨慎。

static char* starinfo[9] = {};

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
	for (int y = 1900; y <= 2021; y++)
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
