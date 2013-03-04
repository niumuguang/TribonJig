/*
ToolBox类
用于储存程序所需的零散函数集合
*/

#pragma once
#include "stdafx.h"
#include <vector>
#include <tuple>
#include "DXF_File.h"

#include <cstdlib>
#include <sstream>
#include <iostream>
#include <string.h>
#include <cstring>
using namespace std;
//typedef vector<CString> DXFMODE;
typedef tuple<float, float, float> COORDINATE;
typedef vector<COORDINATE> POLYLINETYPE;

class CToolBox
{
public:
	CToolBox(void);
	~CToolBox(void);

public:
	// 处理Dxf文件数据的入口函数
	CDXF_File ProgressDxf(vector<CString> FileContext);

public:
	// 读取Dxf文件数据
	bool ReadDxf(LPCTSTR FileDir, vector<CString> &ReadContext);
	// 将CString转换为Double类型
	double CString2Double(CString str);
	// 将Int转换为CString类型
	CString Int2CString(int Num);

	// 新的DXF解析函数
	//void GetPlanerHull(vector<CString> FileContext, int &Planer_IDX, vector<COORDINATE> &PlateRes);
}; 