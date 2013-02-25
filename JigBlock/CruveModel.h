/*
继承于CModel类
用于曲面板架的实体化
储存曲面板架的相关数据和方法
*/

#pragma once

#include "stdafx.h"
#include <vector>
#include <string.h>
#include <cstring>
#include <tuple>

using namespace std;
typedef tuple<double, double, double> COORDINATE;

#include "model.h"
//#include "Model.h"
//#include <tuple>
#include "C3DFACE.h"
#include "math3d.h"

class CCruveModel:public CModel
{
public:
	CCruveModel(void);
	// 将基类CModel转换为曲面板模型类
	CCruveModel(CModel transModel);
	~CCruveModel(void);

public:
	// 分割Data数据
	void DivisionData();
	// 将数据分为 板数据列表和焊缝数据列表
	void DisposePlate();
	// 返回面板数据列表
	vector<C3DFACE> Get3DFaceList();
	// 直接显示面
	void ShowPlate();

public:
	// 临时焊缝数据结构 可优化掉
	vector<CString> m_Polyline;
	// 焊缝数据列表
	vector<vector<CString>> m_PolylineList;// 储存曲面板架边界数据
	// 临时面数据结构 可优化掉
	vector<CString> m_3DFaceData;
	// 临时分割后的面数据储存
	vector<vector<CString>> m_PlateList;

private:
	// 面数据储存列表
	vector<C3DFACE> m_C3DFace_List;

	// 向量叉乘
	inline void JigCrossProduct(M3DVector3f result, M3DVector3d u, M3DVector3d v)
	{
		result[0] = u[1]*v[2] - v[1]*u[2];
		result[1] = -u[0]*v[2] + v[0]*u[2];
		result[2] = u[0]*v[1] - v[0]*u[1];
	}
};

