#include "StdAfx.h"
#include "CruveModel.h"
#include "ProDlg.h"
#include "JigBlock.h"


CCruveModel::CCruveModel(void)
{
	// 生成两个显示列表 板的显示列表 焊缝的显示列表
	m_Model_PlateList = glGenLists(1);
	m_ModelType = _T("CRUVEMODEL");
}

// 将基类CModel转换为曲面板模型类
CCruveModel::CCruveModel( CModel transModel )
{
	m_Model_PlateList = transModel.m_Model_PlateList;
	m_PolyVec = transModel.m_PolyVec;
	
	m_ModelName = transModel.m_ModelName;
	m_ModelData = transModel.m_ModelData;
	m_ModelType = _T("CRUVEMODEL");
	//DivisionData();
	//Plate_Poly_ShowList(); // 计算量大
	//DisposePointList();
}

CCruveModel::CCruveModel( vector<CString> TotalData, CString name )
{
	m_ModelData = TotalData;
	m_ModelName = name;
	m_ModelType = _T("CRUVEMODEL");
	m_Model_PlateList = glGenLists(1);
	
}


CCruveModel::~CCruveModel(void)
{
}

// 分割Data数据 成面数据 和 多段线数据
void CCruveModel::DivisionData()
{
	// 计算量偏大
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
	// 区分开曲面和焊缝
	ProgressDlg* prodlg;
	prodlg = theApp.getProDlgHandle();

	vector<CString> tempData;
	for (int i=idx;i<m_ModelData.size();i++)
	{
		prodlg->m_Pro.StepIt();
		tempData.clear();
		if (m_ModelData.at(i) == "POLYLINE")
		{
			int j = i;
			for (j; j<m_ModelData.size(); j++)
			{
				prodlg->m_Pro.StepIt();
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
				prodlg->m_Pro.StepIt();
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
	Plate_Poly_ShowList();
}

// 将数据分为 板数据列表和焊缝数据列表
void CCruveModel::Plate_Poly_ShowList()
{
	vector<CString> tempData;
	int ColorIndex;
	CString tempStr;
	vector<CString> tempCString;
	float tempFloat_X = 0, tempFloat_Y = 0, tempFloat_Z = 0;
	// 处理板数据得到 板的显示列表
	bool ColorCounter = false;
	bool firstPoint = false;
	if (theApp.getFirstX() == -1)
	{
		firstPoint = true;
	}
	glNewList(m_Model_PlateList, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	ProgressDlg* prodlg;
	prodlg = theApp.getProDlgHandle();
	for (int i=0; i<m_PlateList.size(); i++)
	{
		prodlg->m_Pro.StepIt();
		tempData = m_PlateList.at(i);
		if (tempData.size() == 38)
		{
			tempStr = tempData.at(10);
			ColorIndex = _ttoi(tempStr);
			if (i == 0)
			{
				if (ColorIndex == 3)
				{
					glColor3f(1,0,0);
				}
				else
				{
					glColor3f(0,1,0);
				}
			}
			// 第一个点
			tempStr = tempData.at(14);
			_stscanf(tempStr,_T("%f"),&tempFloat_X);
			tempStr = tempData.at(16);
			_stscanf(tempStr,_T("%f"),&tempFloat_Y);
			tempStr = tempData.at(18);
			_stscanf(tempStr,_T("%f"),&tempFloat_Z);
			if (firstPoint == true)
			{
				theApp.setFirstX(tempFloat_X);theApp.setFirstY(tempFloat_Y);theApp.setFirstZ(tempFloat_Z);
				firstPoint == false;
			}
			//
			glVertex3f(tempFloat_X, tempFloat_Y, tempFloat_Z);
			// 第二个点
			tempStr = tempData.at(20);
			_stscanf(tempStr,_T("%f"),&tempFloat_X);
			tempStr = tempData.at(22);
			_stscanf(tempStr,_T("%f"),&tempFloat_Y);
			tempStr = tempData.at(24);
			_stscanf(tempStr,_T("%f"),&tempFloat_Z);
			//
			glVertex3f(tempFloat_X, tempFloat_Y, tempFloat_Z);
			// 第三个点
			tempStr = tempData.at(26);
			_stscanf(tempStr,_T("%f"),&tempFloat_X);
			tempStr = tempData.at(28);
			_stscanf(tempStr,_T("%f"),&tempFloat_Y);
			tempStr = tempData.at(30);
			_stscanf(tempStr,_T("%f"),&tempFloat_Z);
			//
			glVertex3f(tempFloat_X, tempFloat_Y, tempFloat_Z);
			// 第四个点
			//tempStr = tempData.at(32);
			//_stscanf(tempStr,_T("%f"),&tempFloat_X);
			//tempStr = tempData.at(34);
			//_stscanf(tempStr,_T("%f"),&tempFloat_Y);
			//tempStr = tempData.at(36);
			//_stscanf(tempStr,_T("%f"),&tempFloat_Z);
		}
		else if (tempData.size() == 40)
		{
			tempStr = tempData.at(10);
			ColorIndex = _ttoi(tempStr);
			if (i == 0)
			{
				if (ColorIndex == 3)
				{
					//theApp.DoMessageBox("ss",0,0);
					glColor3f(1,0,0);
				}
				else
				{
					glColor3f(0,1,0);
				}
			}
			// 第一个点
			tempStr = tempData.at(16);
			_stscanf(tempStr,_T("%f"),&tempFloat_X);
			tempStr = tempData.at(18);
			_stscanf(tempStr,_T("%f"),&tempFloat_Y);
			tempStr = tempData.at(20);
			_stscanf(tempStr,_T("%f"),&tempFloat_Z);
			if (firstPoint == true)
			{
				theApp.setFirstX(tempFloat_X);theApp.setFirstY(tempFloat_Y);theApp.setFirstZ(tempFloat_Z);
				firstPoint == false;
			}
			//
			glVertex3f(tempFloat_X, tempFloat_Y, tempFloat_Z);
			// 第二个点
			tempStr = tempData.at(22);
			_stscanf(tempStr,_T("%f"),&tempFloat_X);
			tempStr = tempData.at(24);
			_stscanf(tempStr,_T("%f"),&tempFloat_Y);
			tempStr = tempData.at(26);
			_stscanf(tempStr,_T("%f"),&tempFloat_Z);
			//
			glVertex3f(tempFloat_X, tempFloat_Y, tempFloat_Z);
			// 第三个点
			tempStr = tempData.at(28);
			_stscanf(tempStr,_T("%f"),&tempFloat_X);
			tempStr = tempData.at(30);
			_stscanf(tempStr,_T("%f"),&tempFloat_Y);
			tempStr = tempData.at(32);
			_stscanf(tempStr,_T("%f"),&tempFloat_Z);
			//
			glVertex3f(tempFloat_X, tempFloat_Y, tempFloat_Z);
			//tempM3DVector3f[2] = tempDou;
			//m_PlateShowList.push_back(tempM3DVector3f);
			// 第四个点
			//tempStr = tempData.at(34);
			//_stscanf(tempStr,_T("%f"),&tempFloat_X);
			////get<0>(Coord_3) = tempFloat_X;
			//tempStr = tempData.at(36);
			//_stscanf(tempStr,_T("%f"),&tempFloat_Y);
			////get<1>(Coord_3) = tempFloat_Y;
			//tempStr = tempData.at(38);
			//_stscanf(tempStr,_T("%f"),&tempFloat_Z);
			////get<2>(Coord_3) = tempFloat_Z;
		}
	}
	glEnd();
	glEndList();
	//
	// 处理多短线
	GLuint tempList;
	for (int i=0; i<m_PolylineList.size();i++)
	{
		prodlg->m_Pro.StepIt();
		tempList = glGenLists(1);
		glNewList(tempList, GL_COMPILE);
		glBegin(GL_LINE);
		glColor3f(1,0,0);
		tempCString = m_PolylineList.at(i);
		for (int j=0; j<tempCString.size(); j++)
		{
			prodlg->m_Pro.StepIt();
			if (tempCString.at(j) == "AcDb3dPolylineVertex")
			{
				j = j+2;
				tempStr = tempCString.at(j);
				_stscanf(tempStr,_T("%f"),&tempFloat_X);
				j = j+2;
				tempStr = tempCString.at(j);
				_stscanf(tempStr,_T("%f"),&tempFloat_Y);
				j = j+2;
				tempStr = tempCString.at(j);
				_stscanf(tempStr,_T("%f"),&tempFloat_Z);
				glVertex3f(tempFloat_X,tempFloat_Y,tempFloat_Z);
			}
		}
		glEnd();
		glEndList();
		m_PolyVec.push_back(tempList);
	}
}

GLuint CCruveModel::GetShowPlateList()
{
	return m_Model_PlateList;
}

vector<GLuint> CCruveModel::GetShowPolyList()
{
	return m_PolyVec;
}
