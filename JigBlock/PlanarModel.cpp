#include "StdAfx.h"
#include "PlanarModel.h"
#include "ProDlg.h"
#include "JigBlock.h"


CPlanarModel::CPlanarModel(void)
{
	m_ModelType = _T("PLANARMODEL");
	m_Model_PlanarList = glGenLists(1);
}

CPlanarModel::CPlanarModel( vector<CString> Context, CString name )
{
	m_Model_PlanarList = glGenLists(1);
	m_ModelData = Context;
	m_ModelName = name;
	m_ModelType = "PLANARMODEL";
}

CPlanarModel::CPlanarModel( CModel transModel )
{
	m_Model_PlanarList = transModel.m_Model_PlanarList;
	m_ModelName = transModel.m_ModelName;
	m_ModelData = transModel.m_ModelData;
	m_ModelType = _T("PLANARMODEL");
	DivisionData();
	Planar_ShowList();
}


CPlanarModel::~CPlanarModel(void)
{
}

void CPlanarModel::DivisionData()
{
	// 将平面板架分割成 小块面板
	ProgressDlg* prodlg;
	prodlg = theApp.getProDlgHandle();

	vector<CString> tempData;
	for (int i=0; i<m_ModelData.size(); i++)
	{
		prodlg->m_Pro.StepIt();
		if (m_ModelData.at(i) == "3DFACE")
		{
			tempData.clear();
			int j=i;
			for (j; j<m_ModelData.size();j++)
			{
				prodlg->m_Pro.StepIt();
				tempData.push_back(m_ModelData.at(j));
				if (m_ModelData.at(j) == "   0")
				{
					i=j;
					break;
				}
			}
			m_PlateList.push_back(tempData);
		}
	}
	Planar_ShowList();
}

void CPlanarModel::Planar_ShowList()
{
	ProgressDlg* prodlg;
	prodlg = theApp.getProDlgHandle();

	vector<CString> tempData;
	int ColorIndex;
	CString tempStr;
	bool firstPoint = false;
	if (theApp.getFirstX() == -1)
	{
		firstPoint = true;
	}
	float tempFloat_X = 0, tempFloat_Y = 0, tempFloat_Z = 0;
	glNewList(m_Model_PlanarList, GL_COMPILE);
	glBegin(GL_QUADS);
	for (int i=0; i<m_PlateList.size(); i++)
	{
		prodlg->m_Pro.StepIt();
		tempData = m_PlateList.at(i);
		if (tempData.size() == 38)
		{
			tempStr = tempData.at(10);
			ColorIndex = _ttoi(tempStr);
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
			tempStr = tempData.at(32);
			_stscanf(tempStr,_T("%f"),&tempFloat_X);
			tempStr = tempData.at(34);
			_stscanf(tempStr,_T("%f"),&tempFloat_Y);
			tempStr = tempData.at(36);
			_stscanf(tempStr,_T("%f"),&tempFloat_Z);
			glVertex3f(tempFloat_X, tempFloat_Y, tempFloat_Z);
		}
		else if (tempData.size() == 40)
		{
			tempStr = tempData.at(10);
			ColorIndex = _ttoi(tempStr);
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
			tempStr = tempData.at(34);
			_stscanf(tempStr,_T("%f"),&tempFloat_X);
			//get<0>(Coord_3) = tempFloat_X;
			tempStr = tempData.at(36);
			_stscanf(tempStr,_T("%f"),&tempFloat_Y);
			//get<1>(Coord_3) = tempFloat_Y;
			tempStr = tempData.at(38);
			_stscanf(tempStr,_T("%f"),&tempFloat_Z);
			//get<2>(Coord_3) = tempFloat_Z;
			glVertex3f(tempFloat_X, tempFloat_Y, tempFloat_Z);
		}
	}
	glEnd();
	glEndList();
}

GLuint CPlanarModel::GetShowPlateist()
{
	return m_Model_PlanarList;
}
