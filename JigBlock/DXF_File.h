// This Class is a object for Dxf File
/*
Dxf_File类
DXF文件的实例化类
用于处理Dxf文件的一些功能函数
*/
#pragma once
#include "stdafx.h"
#include <vector>
#include <tuple>

#include <string.h>
#include <cstring>
#include "Block.h"
#include "Model.h"
#include "OtherModel.h"
#include "CruveModel.h"
#include "PlanarModel.h"
#include "ProDlg.h"

using namespace std;
typedef tuple<float, float, float> COORDINATE;
typedef vector<COORDINATE> POLYLINETYPE;

class CDXF_File
{
public:
	CDXF_File(void);
	CDXF_File(vector<CString> InputContext);
	~CDXF_File(void);

public:
	// 设置 FileContext 整个dxf的内容
	bool SetFileContext(vector<CString> InputContext);
	// 按section 分割dxf文件内容
	void SetSEC();
	// 从block section 中分离block内容，并加入BLK_Context
	void GetBlocksSEC();
	// 分析BLK_Context中每个模型
	void AnsysDxfData();
	// 调用种类模型函数 初始化各种模型
	//void TransferModel();
	// 得到BLK名称
	CString	GetBlockName(vector<CString> InputContext);
	// 返回dxf文件的模型列表
	vector<CModel> GetModelList();

private:
	vector<CString> FileContext;
	vector<CString> HEADER_SEC;
	vector<CString> CLASSES_SEC;
	vector<CString> TABLES_SEC;
	vector<CString> BLOCKS_SEC;
	vector<CString> ENTITIES_SEC;
	vector<CString> OBJECTS_SEC;

private:
	vector<vector<CString>> BLK_Context;
	//vector<vector<CString>> Planar_BLK, Cruve_BLK,Other_BLK;
	vector<CModel> m_ModelList;// 储存DXF文件中的所有模型
	ProgressDlg* MainPro;
};

