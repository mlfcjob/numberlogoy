#pragma once


// m_comboMon 对话框

class m_comboMon : public CDialogEx
{
	DECLARE_DYNAMIC(m_comboMon)

public:
	m_comboMon(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~m_comboMon();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NUMEROLOGY_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
