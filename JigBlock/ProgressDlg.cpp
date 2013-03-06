// ProgressDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "JigBlock.h"
#include "ProgressDlg.h"
#include "afxdialogex.h"



int pos=0;
// CProgressDlg �Ի���

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


// CProgressDlg ��Ϣ�������


//void CProgressDlg::OnTimer(UINT_PTR nIDEvent)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
//	////�������ý�����λ�õķ���������ע�͵���Ҳ��
//	///*pro->GetRange( nPos, nMaxRange );
//	//nPos = pro->GetPos()+PROGRESS_INCREASE;
//	//if( nPos>nMaxRange ) nPos = 0;
//	//pro->SetPos( nPos );*/
//	//pro->OffsetPos( PROGRESS_INCREASE );//PROGRESS_INCREASE�궨������ÿ�ε�����
//	//pro->GetRange( nPos, nMaxRange );
//	//nPos = pro->GetPos();
//	//if( nPos>=nMaxRange ) pro->SetPos( 0 );
//	CDialogEx::OnTimer(nIDEvent);
//}


void CProgressDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//m_pro.SetPos(100);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CProgressDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
