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
typedef tuple<float, float, float> COORDINATE;

#include "model.h"
//#include "Model.h"
//#include <tuple>
#include "C3DFACE.h"
#include "math3d.h"

class CCruveModel:public CModel
{
public:
	CCruveModel(void);
	//
	CCruveModel(vector<CString> TotalData, CString name);
	// 将基类CModel转换为曲面板模型类
	CCruveModel(CModel transModel);
	~CCruveModel(void);

public:
	// 分割Data数据
	void DivisionData();
	// 分割Data数据
	void DivisionData(int idx);
	// 将数据分为 板数据列表和焊缝数据列表
	void Plate_Poly_ShowList();
// 	// 返回面板数据列表
// 	vector<C3DFACE> Get3DFaceList();
	// 直接显示面
	void ShowPlate();
	// 返回顶点数据列表
//	void DisposePointList();
	// 返回所有顶点数据
	vector<COORDINATE> GetCoorList();
	// 返回显示列表名称
	GLuint GetShowPlateList();
	vector<GLuint> GetShowPolyList();

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
	// 所有顶点数据
	//vector<COORDINATE> m_DataCoorList;
	// 面的显示列表
	//vector<float> m_PlateShowList;
	//// 显示列表储存名称
	//GLuint m_Model_PlateList;
	//GLuint m_Model_PolyList;

	// 显示列表 容器
	//vector<GLuint> ShowListVec;

	//void push(vector &, float*)
	//{
	//	for (3)
	//	{
	//		m_PlateShowList.push_back(*(p + i))
	//	}
	//}
	

	// 向量叉乘
	inline void JigCrossProduct(M3DVector3f result, M3DVector3d u, M3DVector3d v)
	{
		result[0] = u[1]*v[2] - v[1]*u[2];
		result[1] = -u[0]*v[2] + v[0]*u[2];
		result[2] = u[0]*v[1] - v[0]*u[1];
	}
};
