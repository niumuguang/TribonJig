#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "resource.h"

// ProTest �Ի���

class ProgressDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ProgressDlg)

public:
	ProgressDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ProgressDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl m_Pro;
//	CButton m_TestButton;
//	afx_msg void OnBnClickedButton1();
	afx_msg void OnPaint();
};
