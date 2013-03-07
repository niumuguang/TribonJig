// ProTest.cpp : 实现文件
//

#include "stdafx.h"
#include "JigBlock.h"
#include "ProDlg.h"
#include "afxdialogex.h"

// ProTest 对话框

IMPLEMENT_DYNAMIC(ProgressDlg, CDialogEx)

ProgressDlg::ProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ProgressDlg::IDD, pParent)
{

}

ProgressDlg::~ProgressDlg()
{
}

void ProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_Pro);
	//  DDX_Control(pDX, IDC_BUTTON1, m_TestButton);
}


BEGIN_MESSAGE_MAP(ProgressDlg, CDialogEx)
//	ON_BN_CLICKED(IDC_BUTTON1, &ProgressDlg::OnBnClickedButton1)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// ProTest 消息处理程序


//void ProgressDlg::OnBnClickedButton1()
//{
//	// TODO: 在此添加控件通知处理程序代码
//}


void ProgressDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()

}
