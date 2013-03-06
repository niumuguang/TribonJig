#pragma once
#include "afxcmn.h"

#define  PROGRESS_INCREASE 1
// CProgressDlg 对话框

class CProgressDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProgressDlg)

public:
	CProgressDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CProgressDlg();
	HICON m_hIcon;
// 对话框数据
	enum { IDD = IDD_PROGREDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CProgressCtrl m_pro;
	CString m_percent;
	CWinThread* m_pMyThread;

public:
	void OnInitial();
	CProgressCtrl* returnProCtrl();
	void setPosGo();
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
