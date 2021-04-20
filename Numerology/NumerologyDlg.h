
// NumerologyDlg.h: 头文件
//

#pragma once

#define SEX_UNKOWN 0
#define MALE   1
#define FEMALE 2

// CNumerologyDlg 对话框
class CNumerologyDlg : public CDHtmlDialog
{
// 构造
public:
	CNumerologyDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NUMEROLOGY_DIALOG, IDH = IDR_HTML_NUMEROLOGY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
public:
	afx_msg void OnLbnSelchangeList3();
	afx_msg void OnCbnSelchangeComboYear();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedRadioMale();
private:
	int m_nSex; // 1: male 2:femal
public:
	afx_msg void OnBnClickedRadioFemale();
};
