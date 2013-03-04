#include "StdAfx.h"
#include "ToolBox.h"
#include "JigBlock.h"


CToolBox::CToolBox(void)
{
}


CToolBox::~CToolBox(void)
{
}

// 读取Dxf文件数据
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
			ReadContext.push_back(TextContent);// 建立容器依次添加每行文本
		}
		return true;
	}
	return false;
}
// 处理Dxf文件数据的入口函数
CDXF_File CToolBox::ProgressDxf(vector<CString> FileContext)
{
	CDXF_File DXF_File(FileContext);
	return DXF_File;
}

// 将CString转换为Double类型
double CToolBox::CString2Double( CString str )
{
	double res;
	res = _ttof(str);
	//res = _ttoi(str);
	return res;
}
// 将Int转换为CString类型
CString CToolBox::Int2CString( int Num )
{
	CString SS;
	SS.Format(_T("%d"), Num);
	return SS;
}
