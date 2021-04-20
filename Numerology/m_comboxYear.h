#pragma once


// m_comboxYear 对话框

class m_comboxYear : public CDialogEx
{
	DECLARE_DYNAMIC(m_comboxYear)

public:
	m_comboxYear(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~m_comboxYear();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NUMEROLOGY_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
