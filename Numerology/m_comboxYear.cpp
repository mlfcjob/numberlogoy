// m_comboxYear.cpp: 实现文件
//

#include "pch.h"
#include "Numerology.h"
#include "m_comboxYear.h"
#include "afxdialogex.h"


// m_comboxYear 对话框

IMPLEMENT_DYNAMIC(m_comboxYear, CDialogEx)

m_comboxYear::m_comboxYear(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NUMEROLOGY_DIALOG, pParent)
{

}

m_comboxYear::~m_comboxYear()
{
}

void m_comboxYear::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(m_comboxYear, CDialogEx)
END_MESSAGE_MAP()


// m_comboxYear 消息处理程序
