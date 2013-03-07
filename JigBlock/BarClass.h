#pragma once


// CBarClass

class CBarClass : public CToolBar
{
	DECLARE_DYNAMIC(CBarClass)

public:
	CBarClass();
	virtual ~CBarClass();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnUpdateUsuallyToolbar(CCmdUI *pCmdUI);
};


