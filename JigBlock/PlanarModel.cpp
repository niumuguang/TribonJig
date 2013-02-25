#include "StdAfx.h"
#include "PlanarModel.h"


CPlanarModel::CPlanarModel(void)
{
	m_ModelType = _T("PLANARMODEL");
}


CPlanarModel::~CPlanarModel(void)
{
}

void CPlanarModel::DivisionData()
{
	vector<CString> tempData;
	for (int i=0; i<m_ModelData.size(); i++)
	{
		if (m_ModelData.at(i) == "3DFACE")
		{
			tempData.clear();
			int j=i;
			for (j; j<m_ModelData.size();j++)
			{
				tempData.push_back(m_ModelData.at(j));
				if (m_ModelData.at(j) == "0")
				{
					i=j;
					break;
				}
			}
			m_PlateList.push_back(tempData);
		}
	}
}
