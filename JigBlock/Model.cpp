#include "StdAfx.h"
#include "Model.h"


CModel::CModel(void)
{
}


CModel::~CModel(void)
{
}

// ����ģ�͵�����
CString CModel::GetModelType()
{
	return m_ModelType;
}
// ����ģ�͵�����
void CModel::SetModelData( vector<CString> ModelData )
{
	m_ModelData = ModelData;
}
// ����ģ�͵�����
void CModel::SetModelName( CString ModelName )
{
	m_ModelName = ModelName;
}




