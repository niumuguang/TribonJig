#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "resource.h"

// ProTest 对话框

class ProgressDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ProgressDlg)

public:
	ProgressDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ProgressDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl m_Pro;
//	CButton m_TestButton;
//	afx_msg void OnBnClickedButton1();
	afx_msg void OnPaint();
};
