/*
所有模型的基类
用于储存和管理从Dxf中读取出的模型
*/

#pragma once
#include "stdafx.h"
#include <vector>
#include <string.h>
#include <cstring>

using namespace std;

//#include "CruveModel.h"


class CModel
{
public:
	CModel(void); 
	~CModel(void);

public:
	// 设置模型的数据
	void SetModelData(vector<CString> ModelData);
	// 设置模型的名称
	void SetModelName(CString ModelName);
	// 设置模型的种类
	CString GetModelType();
	

public:
	// 模型的名称 储存模型所属板架的名称
	CString m_ModelName;
	// 模型的所有数据
	vector<CString> m_ModelData;
	// 模型的类型
	CString m_ModelType; // OTHERMODEL,CRUVEMODEL,PLANARMODEL 三个种类
	// 兼容曲面板架
	// 焊缝数据列表

	// 显示列表名称 容器
	//vector<GLuint> ShowListVec;
	// 显示列表 曲面支持
	GLuint m_Model_PlateList;
	GLuint m_Model_PolyList;
};

