// m_comboMon.cpp: 实现文件
//

#include "pch.h"
#include "Numerology.h"
#include "m_comboMon.h"
#include "afxdialogex.h"


// m_comboMon 对话框

IMPLEMENT_DYNAMIC(m_comboMon, CDialogEx)

m_comboMon::m_comboMon(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NUMEROLOGY_DIALOG, pParent)
{

}

m_comboMon::~m_comboMon()
{
}

void m_comboMon::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(m_comboMon, CDialogEx)
END_MESSAGE_MAP()


// m_comboMon 消息处理程序
