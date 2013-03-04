#include "StdAfx.h"
#include "ToolBox.h"
#include "JigBlock.h"


CToolBox::CToolBox(void)
{
}


CToolBox::~CToolBox(void)
{
}

// ��ȡDxf�ļ�����
bool CToolBox::ReadDxf(LPCTSTR FileDir, vector<CString> &ReadContext)
{
	CStdioFile FileHandle;
	bool RunState;
	RunState = FileHandle.Open(FileDir, CFile::modeRead|CFile::typeText);
	if (RunState == true)
	{
		CString TextContent;
		while(FileHandle.ReadString(TextContent))
		{
			ReadContext.push_back(TextContent);// ���������������ÿ���ı�
		}
		return true;
	}
	return false;
}
// ����Dxf�ļ����ݵ���ں���
CDXF_File CToolBox::ProgressDxf(vector<CString> FileContext)
{
	CDXF_File DXF_File(FileContext);
	return DXF_File;
}

// ��CStringת��ΪDouble����
double CToolBox::CString2Double( CString str )
{
	double res;
	res = _ttof(str);
	//res = _ttoi(str);
	return res;
}
// ��Intת��ΪCString����
CString CToolBox::Int2CString( int Num )
{
	CString SS;
	SS.Format(_T("%d"), Num);
	return SS;
}
