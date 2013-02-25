#include "StdAfx.h"
#include "CruveModel.h"


CCruveModel::CCruveModel(void)
{
	m_ModelType = _T("CRUVEMODEL");
}

// 将基类CModel转换为曲面板模型类
CCruveModel::CCruveModel( CModel transModel )
{
	m_ModelName = transModel.m_ModelName;
	m_ModelData = transModel.m_ModelData;
	m_ModelType = transModel.m_ModelType;
	DivisionData();
	DisposePlate();
}


CCruveModel::~CCruveModel(void)
{
}

// 分割Data数据
void CCruveModel::DivisionData()
{
	//m_ModelData
	vector<CString> tempData;
	for (int i=0;i<m_ModelData.size();i++)
	{
		tempData.clear();
		if (m_ModelData.at(i) == "POLYLINE")
		{
			int j = i;
			for (j; j<m_ModelData.size(); j++)
			{
				tempData.push_back(m_ModelData.at(j));
				if (m_ModelData.at(j) == "SEQEND")
				{
					i = j;
					break;
				}
			}
			m_PolylineList.push_back(tempData);
		}
		else if (m_ModelData.at(i) == "3DFACE")
		{
			tempData.clear();
			int j = i;
			for (j; j<m_ModelData.size(); j++)
			{
				tempData.push_back(m_ModelData.at(j));
				if (m_ModelData.at(j) == "   0")
				{
					i = j;
					break;
				}
			}
			m_PlateList.push_back(tempData);
		}
	}
	DisposePlate();
}

// 将数据分为 板数据列表和焊缝数据列表
void CCruveModel::DisposePlate()
{
	vector<CString> tempData;
	int ColorIndex;
	CString tempStr;
	double tempDou = 0;
	COORDINATE Coord_0, Coord_1, Coord_2, Coord_3;
	C3DFACE temp3DFace;
	for (int i=0; i<m_PlateList.size(); i++)
	{
		tempData = m_PlateList.at(i);
		temp3DFace.SetData(tempData);
		for (int j=0; j<tempData.size(); j++)
		{
			// color
			if (tempData.at(j) == "   62")
			{
				tempStr = tempData.at(j+1);
				//int a = _ttoi(tempStr);
				ColorIndex = _ttoi(tempStr);
				temp3DFace.SetColorIDX(ColorIndex);
			}
			else if (tempData.at(j) == "   10")
			{
				tempStr = tempData.at(j+1);
				_stscanf(tempStr,_T("%lf"),&tempDou);
				get<0>(Coord_0) = tempDou;
			}
			else if (tempData.at(j) == "   20")
			{
				tempStr = tempData.at(j+1);
				_stscanf(tempStr,_T("%lf"),&tempDou);
				get<1>(Coord_0) = tempDou;
			}
			else if (tempData.at(j) == "   30")
			{
				tempStr = tempData.at(j+1);
				_stscanf(tempStr,_T("%lf"),&tempDou);
				get<2>(Coord_0) = tempDou;
			}
			//////////////////////////////////////////////////////////////////////////
			else if (tempData.at(j) == "   11")
			{
				tempStr = tempData.at(j+1);
				_stscanf(tempStr,_T("%lf"),&tempDou);
				get<0>(Coord_1) = tempDou;
			}
			else if (tempData.at(j) == "   21")
			{
				tempStr = tempData.at(j+1);
				_stscanf(tempStr,_T("%lf"),&tempDou);
				get<1>(Coord_1) = tempDou;
			}
			else if (tempData.at(j) == "   31")
			{
				tempStr = tempData.at(j+1);
				_stscanf(tempStr,_T("%lf"),&tempDou);
				get<2>(Coord_1) = tempDou;
			}
			//////////////////////////////////////////////////////////////////////////
			else if (tempData.at(j) == "   12")
			{
				tempStr = tempData.at(j+1);
				_stscanf(tempStr,_T("%lf"),&tempDou);
				get<0>(Coord_2) = tempDou;
			}
			else if (tempData.at(j) == "   22")
			{
				tempStr = tempData.at(j+1);
				_stscanf(tempStr,_T("%lf"),&tempDou);
				get<1>(Coord_2) = tempDou;
			}
			else if (tempData.at(j) == "   32")
			{
				tempStr = tempData.at(j+1);
				_stscanf(tempStr,_T("%lf"),&tempDou);
				get<2>(Coord_2) = tempDou;
			}
			//////////////////////////////////////////////////////////////////////////
			else if (tempData.at(j) == "   13")
			{
				tempStr = tempData.at(j+1);
				_stscanf(tempStr,_T("%lf"),&tempDou);
				get<0>(Coord_3) = tempDou;
			}
			else if (tempData.at(j) == "   23")
			{
				tempStr = tempData.at(j+1);
				_stscanf(tempStr,_T("%lf"),&tempDou);
				get<1>(Coord_3) = tempDou;
			}
			else if (tempData.at(j) == "   33")
			{
				tempStr = tempData.at(j+1);
				_stscanf(tempStr,_T("%lf"),&tempDou);
				get<2>(Coord_3) = tempDou;
			}
			//////////////////////////////////////////////////////////////////////////
		}
		temp3DFace.SetCoord(Coord_0,Coord_1,Coord_2,Coord_3);
		m_C3DFace_List.push_back(temp3DFace);
	}
	
}

// 返回面板数据列表
vector<C3DFACE> CCruveModel::Get3DFaceList()
{
	return m_C3DFace_List;
}

// 直接显示面
void CCruveModel::ShowPlate()
{
	for (int i=0; i<m_C3DFace_List.size(); i++)
	{
		C3DFACE temp3DFace = m_C3DFace_List.at(i);
		//glPushMatrix();
		//glTranslatef(-10000,-700,-2225);
		//glBegin(GL_QUADS);
		//M3DVector3f vPoints[3] = {
		//	(get<0>(temp3DFace.m_coord0),get<1>(temp3DFace.m_coord0),get<2>(temp3DFace.m_coord0)),
		//	(get<0>(temp3DFace.m_coord1),get<1>(temp3DFace.m_coord1),get<2>(temp3DFace.m_coord1)),
		//	(get<0>(temp3DFace.m_coord2),get<1>(temp3DFace.m_coord2),get<2>(temp3DFace.m_coord2))
		//};
		//M3DVector3f vNormal;
		//M3DVector3d v1,v2;
		//v1[0] = get<0>(temp3DFace.m_coord1) - get<0>(temp3DFace.m_coord0);
		//v1[1] = get<1>(temp3DFace.m_coord1) - get<1>(temp3DFace.m_coord0);
		//v1[2] = get<2>(temp3DFace.m_coord1) - get<2>(temp3DFace.m_coord0);

		//v2[0] = get<0>(temp3DFace.m_coord1) - get<0>(temp3DFace.m_coord0);
		//v2[1] = get<1>(temp3DFace.m_coord1) - get<1>(temp3DFace.m_coord0);
		//v2[2] = get<2>(temp3DFace.m_coord1) - get<2>(temp3DFace.m_coord0);

		//JigCrossProduct(vNormal, v1, v2);
		////m3dFindNormal();
		////m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
		//glNormal3fv(vNormal);
		//glVertex3f(get<0>(temp3DFace.m_coord0), get<1>(temp3DFace.m_coord0), get<2>(temp3DFace.m_coord0));
		//glVertex3f(get<0>(temp3DFace.m_coord1), get<1>(temp3DFace.m_coord1), get<2>(temp3DFace.m_coord1));
		//glVertex3f(get<0>(temp3DFace.m_coord2), get<1>(temp3DFace.m_coord2), get<2>(temp3DFace.m_coord2));
		//glVertex3f(get<0>(temp3DFace.m_coord3), get<1>(temp3DFace.m_coord3), get<2>(temp3DFace.m_coord3));
		//glEnd();
		//glPopMatrix();
	}
	
}
