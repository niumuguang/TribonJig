/*
C3DFACE类
为每个显示最小面单元的实例化
*/
#pragma once

#include "stdafx.h"
#include <vector>
#include <string.h>
#include <cstring>
#include <tuple>

using namespace std;
typedef tuple<double, double, double> COORDINATE;

class C3DFACE
{
public:
	C3DFACE(void);
	~C3DFACE(void);

public:
	// 储存总体的数据
	vector<CString> m_3DFACE_Data;
	// 分别储存面的四个点
	// 曲板的四个点实际为三个用于三角形数据
	// 平板的四个点为四个用于矩形数据
	COORDINATE m_coord0,m_coord1,m_coord2,m_coord3;
	// 颜色索引值
	int m_ColorIndex;

public:
	// 设置颜色索引值
	void SetColorIDX(int ColorIndex);
	// 设置坐标数据
	void SetCoord(COORDINATE coord0,COORDINATE coord1,COORDINATE coord2,COORDINATE coord3);
	// 设置总体数据
	void SetData(vector<CString> Data);
	// 获得第一个坐标值
	COORDINATE GetCoord0();
	COORDINATE GetCoord1();
	COORDINATE GetCoord2();
	COORDINATE GetCoord3();
};

