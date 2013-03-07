// BarClass.cpp : 实现文件
//

#include "stdafx.h"
#include "JigBlock.h"
#include "BarClass.h"


// CBarClass

IMPLEMENT_DYNAMIC(CBarClass, CToolBar)

CBarClass::CBarClass()
{

}

CBarClass::~CBarClass()
{
}


BEGIN_MESSAGE_MAP(CBarClass, CToolBar)
	ON_UPDATE_COMMAND_UI(ID_USUALLY_TOOLBAR, &CBarClass::OnUpdateUsuallyToolbar)
END_MESSAGE_MAP()



// CBarClass 消息处理程序




void CBarClass::OnUpdateUsuallyToolbar(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}
