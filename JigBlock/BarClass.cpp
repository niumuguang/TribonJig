// BarClass.cpp : ʵ���ļ�
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



// CBarClass ��Ϣ�������




void CBarClass::OnUpdateUsuallyToolbar(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
}
