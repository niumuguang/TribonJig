#include "StdAfx.h"
#include "Model.h"


CModel::CModel(void)
{
}


CModel::~CModel(void)
{
}

// 设置模型的种类
CString CModel::GetModelType()
{
	return m_ModelType;
}
// 设置模型的数据
void CModel::SetModelData( vector<CString> ModelData )
{
	m_ModelData = ModelData;
}
// 设置模型的名称
void CModel::SetModelName( CString ModelName )
{
	m_ModelName = ModelName;
}




