// ProTest.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "JigBlock.h"
#include "ProDlg.h"
#include "afxdialogex.h"

// ProTest �Ի���

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


// ProTest ��Ϣ�������


//void ProgressDlg::OnBnClickedButton1()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//}


void ProgressDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()

}
