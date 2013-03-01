#include "StdAfx.h"
#include "CruveModel.h"


CCruveModel::CCruveModel(void)
{
	// 生成两个显示列表 板的显示列表 焊缝的显示列表
	m_Model_PlateList = glGenLists(2);
	m_Model_PolyList = m_Model_PlateList + 1;
	m_ModelType = _T("CRUVEMODEL");
}

// 将基类CModel转换为曲面板模型类
CCruveModel::CCruveModel( CModel transModel )
{
	m_Model_PlateList = glGenLists(2);
	m_Model_PolyList = m_Model_PlateList + 1;
	
	m_ModelName = transModel.m_ModelName;
	m_ModelData = transModel.m_ModelData;
	m_ModelType = _T("CRUVEMODEL");
	DivisionData();
	Plate_Poly_Data(); // 计算量大
	//DisposePointList();
}

CCruveModel::CCruveModel( vector<CString> TotalData, CString name )
{
	m_ModelData = TotalData;
	m_ModelName = name;
	m_ModelType = _T("CRUVEMODEL");
	m_Model_PlateList = glGenLists(2);
	m_Model_PolyList = m_Model_PlateList + 1;
}


CCruveModel::~CCruveModel(void)
{
}

// 分割Data数据 成面数据 和 多段线数据
void CCruveModel::DivisionData()
{
	// 计算量偏大
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
	//Plate_Poly_Data();
}

// 分割Data数据 分割成 面数据 和多段线数据
// 引入 idx 减少6个搜索量
void CCruveModel::DivisionData(int idx)
{
	// 计算量偏大
	//m_ModelData
	// 区分开曲面和焊缝
	vector<CString> tempData;
	for (int i=idx;i<m_ModelData.size();i++)
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
	Plate_Poly_Data();
}

// 将数据分为 板数据列表和焊缝数据列表
void CCruveModel::Plate_Poly_Data()
{
	vector<CString> tempData;
	int ColorIndex;
	CString tempStr;
	float tempFloat_X = 0, tempFloat_Y = 0, tempFloat_Z = 0;
	//COORDINATE Coord_0, Coord_1, Coord_2, Coord_3;
	//C3DFACE temp3DFace;
	//int *const num = 0;// = m_PlateList.size();
	//int ss = m_PlateList.size();
	//num = &ss;
	 //float* tempM3DVector3f = new M3DVector3f;
	//M3DVector3f 
	// 处理板数据得到 板的显示列表
	glNewList(m_Model_PlateList, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	for (int i=0; i<m_PlateList.size(); i++)
	{
		tempData = m_PlateList.at(i);
		if (tempData.size() == 38)
		{
			tempStr = tempData.at(10);
			ColorIndex = _ttoi(tempStr);
			//temp3DFace.SetColorIDX(ColorIndex);
			// 第一个点
			tempStr = tempData.at(14);
			_stscanf(tempStr,_T("%f"),&tempFloat_X);
			//get<0>(Coord_0) = tempFloat_X;
			//tempM3DVector3f[0] = tempDou;
			tempStr = tempData.at(16);
			_stscanf(tempStr,_T("%f"),&tempFloat_Y);
			//get<1>(Coord_0) = tempFloat_Y;
			//tempM3DVector3f[1] = tempDou;
			tempStr = tempData.at(18);
			_stscanf(tempStr,_T("%f"),&tempFloat_Z);
			//get<2>(Coord_0) = tempFloat_Z;
			//
			glVertex3f(tempFloat_X, tempFloat_Y, tempFloat_Z);
			//tempM3DVector3f[2] = tempDou;
			//m_PlateShowList.push_back(tempM3DVector3f);
			// 第二个点
			tempStr = tempData.at(20);
			_stscanf(tempStr,_T("%f"),&tempFloat_X);
			//get<0>(Coord_1) = tempFloat_X;
			//tempM3DVector3f[0] = tempDou;
			tempStr = tempData.at(22);
			_stscanf(tempStr,_T("%f"),&tempFloat_Y);
			//get<1>(Coord_1) = tempFloat_Y;
			//tempM3DVector3f[1] = tempDou;
			tempStr = tempData.at(24);
			_stscanf(tempStr,_T("%f"),&tempFloat_Z);
			//get<2>(Coord_1) = tempFloat_Z;
			//
			glVertex3f(tempFloat_X, tempFloat_Y, tempFloat_Z);
			//tempM3DVector3f[2] = tempDou;
			//m_PlateShowList.push_back(tempM3DVector3f);
			// 第三个点
			tempStr = tempData.at(26);
			_stscanf(tempStr,_T("%f"),&tempFloat_X);
			//get<0>(Coord_2) = tempFloat_X;
			//tempM3DVector3f[0] = tempDou;
			tempStr = tempData.at(28);
			_stscanf(tempStr,_T("%f"),&tempFloat_Y);
			//get<1>(Coord_2) = tempFloat_Y;
			//tempM3DVector3f[1] = tempDou;
			tempStr = tempData.at(30);
			_stscanf(tempStr,_T("%f"),&tempFloat_Z);
			//get<2>(Coord_2) = tempFloat_Z;
			//
			glVertex3f(tempFloat_X, tempFloat_Y, tempFloat_Z);
			//tempM3DVector3f[2] = tempDou;
			//m_PlateShowList.push_back(tempM3DVector3f);
			// 第四个点
			tempStr = tempData.at(32);
			_stscanf(tempStr,_T("%f"),&tempFloat_X);
			//get<0>(Coord_3) = tempFloat_X;
			tempStr = tempData.at(34);
			_stscanf(tempStr,_T("%f"),&tempFloat_Y);
			//get<1>(Coord_3) = tempFloat_Y;
			tempStr = tempData.at(36);
			_stscanf(tempStr,_T("%f"),&tempFloat_Z);
			//get<2>(Coord_3) = tempFloat_Z;
		}
		else if (tempData.size() == 40)
		{
			tempStr = tempData.at(10);
			ColorIndex = _ttoi(tempStr);
			//temp3DFace.SetColorIDX(ColorIndex);
			// 第一个点
			tempStr = tempData.at(16);
			_stscanf(tempStr,_T("%f"),&tempFloat_X);
			//get<0>(Coord_0) = tempFloat_X;
			//tempM3DVector3f[0] = tempDou;
			tempStr = tempData.at(18);
			_stscanf(tempStr,_T("%f"),&tempFloat_Y);
			//get<1>(Coord_0) = tempFloat_Y;
			//tempM3DVector3f[1] = tempDou;
			tempStr = tempData.at(20);
			_stscanf(tempStr,_T("%f"),&tempFloat_Z);
			//get<2>(Coord_0) = tempFloat_Z;
			//
			glVertex3f(tempFloat_X, tempFloat_Y, tempFloat_Z);
			//tempM3DVector3f[2] = tempDou;
			//m_PlateShowList.push_back(tempM3DVector3f);
			// 第二个点
			tempStr = tempData.at(22);
			_stscanf(tempStr,_T("%f"),&tempFloat_X);
			//get<0>(Coord_1) = tempFloat_X;
			//tempM3DVector3f[0] = tempDou;
			tempStr = tempData.at(24);
			_stscanf(tempStr,_T("%f"),&tempFloat_Y);
			//get<1>(Coord_1) = tempFloat_Y;
			//tempM3DVector3f[1] = tempDou;
			tempStr = tempData.at(26);
			_stscanf(tempStr,_T("%f"),&tempFloat_Z);
			//get<2>(Coord_1) = tempFloat_Z;
			//
			glVertex3f(tempFloat_X, tempFloat_Y, tempFloat_Z);
			//tempM3DVector3f[2] = tempDou;
			//m_PlateShowList.push_back(tempM3DVector3f);
			// 第三个点
			tempStr = tempData.at(28);
			_stscanf(tempStr,_T("%f"),&tempFloat_X);
			//get<0>(Coord_2) = tempFloat_X;
			//tempM3DVector3f[0] = tempDou;
			tempStr = tempData.at(30);
			_stscanf(tempStr,_T("%f"),&tempFloat_Y);
			//get<1>(Coord_2) = tempFloat_Y;
			//tempM3DVector3f[1] = tempDou;
			tempStr = tempData.at(32);
			_stscanf(tempStr,_T("%f"),&tempFloat_Z);
			//get<2>(Coord_2) = tempFloat_Z;
			//
			glVertex3f(tempFloat_X, tempFloat_Y, tempFloat_Z);
			//tempM3DVector3f[2] = tempDou;
			//m_PlateShowList.push_back(tempM3DVector3f);
			// 第四个点
			tempStr = tempData.at(34);
			_stscanf(tempStr,_T("%f"),&tempFloat_X);
			//get<0>(Coord_3) = tempFloat_X;
			tempStr = tempData.at(36);
			_stscanf(tempStr,_T("%f"),&tempFloat_Y);
			//get<1>(Coord_3) = tempFloat_Y;
			tempStr = tempData.at(38);
			_stscanf(tempStr,_T("%f"),&tempFloat_Z);
			//get<2>(Coord_3) = tempFloat_Z;
		}
		//temp3DFace.SetCoord(Coord_0,Coord_1,Coord_2,Coord_3);
		//m_C3DFace_List.push_back(temp3DFace);
	}
	glEnd();
	glEndList();
}

// 返回面板数据列表
// vector<C3DFACE> CCruveModel::Get3DFaceList()
// {
// 	return m_C3DFace_List;
// }

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

//void CCruveModel::DisposePointList()
//{
//	vector<C3DFACE> temp3DFaceList = Get3DFaceList();
//	C3DFACE temp3dFace;
//	vector<COORDINATE> tempList;
//	vector<COORDINATE> resList;
//	for (int i=0;i<temp3DFaceList.size();i++)
//	{
//		temp3dFace = temp3DFaceList.at(i);
//		tempList = temp3dFace.CoordList();
//		for (int j=0;j<tempList.size();j++)
//		{
//			resList.push_back(tempList.at(j));
//		}
//	}
//	m_DataCoorList = resList;
//	//return resList;
//}

vector<COORDINATE> CCruveModel::GetCoorList()
{
	return m_DataCoorList;
}

GLuint CCruveModel::GetShowPlateList()
{
	return m_Model_PlateList;
}
