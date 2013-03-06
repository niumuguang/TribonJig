// ProgressDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "JigBlock.h"
#include "ProgressDlg.h"
#include "afxdialogex.h"



int pos=0;
// CProgressDlg 对话框

IMPLEMENT_DYNAMIC(CProgressDlg, CDialogEx)

CProgressDlg::CProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProgressDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//m_pro.SetPos(100);
// 	CProgressCtrl *pPadProgressCtrl;
// 	pPadProgressCtrl = new CProgressCtrl;
// 	CRect m_rect;
// 
// 	pPadProgressCtrl->SetRange(0, 100);
// 	pPadProgressCtrl->SetPos(0);
} 

CProgressDlg::~CProgressDlg()
{
}

void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_pro);
}


BEGIN_MESSAGE_MAP(CProgressDlg, CDialogEx)
//	ON_WM_TIMER()
	ON_WM_TIMER()
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CProgressDlg::OnInitial()
{
	m_pro.SetRange32(0,100);
	m_pro.SetPos(100);
	
}

CProgressCtrl* CProgressDlg::returnProCtrl()
{
	return &m_pro;
}


// CProgressDlg 消息处理程序


//void CProgressDlg::OnTimer(UINT_PTR nIDEvent)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	pos = pos + 50;
//	if (pos > 500)
//	{
//		pos = 0;
//	}
//	m_pro.SetPos(pos);
//	
//	//int nPos, nMaxRange;
//	//CProgressCtrl  *pro;
//	//switch( nIDEvent )
//	//{
//	//case IDC_PROGRESS1:
//	//	pro = ( CProgressCtrl *)GetDlgItem( IDC_PROGRESS1 );
//	//	break;
//	//default:
//	//	return ;
//	//}
//	////两种设置进度条位置的方法，其中注释掉的也行
//	///*pro->GetRange( nPos, nMaxRange );
//	//nPos = pro->GetPos()+PROGRESS_INCREASE;
//	//if( nPos>nMaxRange ) nPos = 0;
//	//pro->SetPos( nPos );*/
//	//pro->OffsetPos( PROGRESS_INCREASE );//PROGRESS_INCREASE宏定义设置每次递增量
//	//pro->GetRange( nPos, nMaxRange );
//	//nPos = pro->GetPos();
//	//if( nPos>=nMaxRange ) pro->SetPos( 0 );
//	CDialogEx::OnTimer(nIDEvent);
//}


void CProgressDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	pos = pos + 50;
	if (pos > 500)
	{
		pos = 0;
	}
	m_pro.SetPos(pos);
	CDialogEx::OnTimer(nIDEvent);
}

void CProgressDlg::setPosGo()
{
	//m_pro->SetRange32(0,100);
	m_pro.SetRange32(0,100);
	m_pro.OffsetPos(100);
	m_pro.SetPos(100);
	m_pro.ShowWindow(SW_SHOW);
	//m_pro->OffsetPos( PROGRESS_INCREASE );
}


BOOL CProgressDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//m_pro.SetPos(100);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CProgressDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}
