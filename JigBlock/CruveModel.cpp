#include "StdAfx.h"
#include "CruveModel.h"


CCruveModel::CCruveModel(void)
{
	// ����������ʾ�б� �����ʾ�б� �������ʾ�б�
	m_Model_PlateList = glGenLists(2);
	m_Model_PolyList = m_Model_PlateList + 1;
	m_ModelType = _T("CRUVEMODEL");
}

// ������CModelת��Ϊ�����ģ����
CCruveModel::CCruveModel( CModel transModel )
{
	//m_Model_PlateList = glGenLists(2);
	//m_Model_PolyList = m_Model_PlateList + 1;
	m_Model_PlateList = transModel.m_Model_PlateList;
	m_Model_PolyList = transModel.m_Model_PolyList;
	
	m_ModelName = transModel.m_ModelName;
	m_ModelData = transModel.m_ModelData;
	m_ModelType = _T("CRUVEMODEL");
	DivisionData();
	Plate_Poly_ShowList(); // ��������
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

// �ָ�Data���� �������� �� ���������
void CCruveModel::DivisionData()
{
	// ������ƫ��
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

// �ָ�Data���� �ָ�� ������ �Ͷ��������
// ���� idx ����6��������
void CCruveModel::DivisionData(int idx)
{
	// ������ƫ��
	// ���ֿ�����ͺ���
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
	Plate_Poly_ShowList();
}

// �����ݷ�Ϊ �������б�ͺ��������б�
void CCruveModel::Plate_Poly_ShowList()
{
	vector<CString> tempData;
	int ColorIndex;
	CString tempStr;
	float tempFloat_X = 0, tempFloat_Y = 0, tempFloat_Z = 0;
	// ��������ݵõ� �����ʾ�б�
	glNewList(m_Model_PlateList, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	for (int i=0; i<m_PlateList.size(); i++)
	{
		tempData = m_PlateList.at(i);
		if (tempData.size() == 38)
		{
			tempStr = tempData.at(10);
			ColorIndex = _ttoi(tempStr);
			// ��һ����
			tempStr = tempData.at(14);
			_stscanf(tempStr,_T("%f"),&tempFloat_X);
			tempStr = tempData.at(16);
			_stscanf(tempStr,_T("%f"),&tempFloat_Y);
			tempStr = tempData.at(18);
			_stscanf(tempStr,_T("%f"),&tempFloat_Z);
			//
			glVertex3f(tempFloat_X, tempFloat_Y, tempFloat_Z);
			// �ڶ�����
			tempStr = tempData.at(20);
			_stscanf(tempStr,_T("%f"),&tempFloat_X);
			tempStr = tempData.at(22);
			_stscanf(tempStr,_T("%f"),&tempFloat_Y);
			tempStr = tempData.at(24);
			_stscanf(tempStr,_T("%f"),&tempFloat_Z);
			//
			glVertex3f(tempFloat_X, tempFloat_Y, tempFloat_Z);
			// ��������
			tempStr = tempData.at(26);
			_stscanf(tempStr,_T("%f"),&tempFloat_X);
			tempStr = tempData.at(28);
			_stscanf(tempStr,_T("%f"),&tempFloat_Y);
			tempStr = tempData.at(30);
			_stscanf(tempStr,_T("%f"),&tempFloat_Z);
			//
			glVertex3f(tempFloat_X, tempFloat_Y, tempFloat_Z);
			// ���ĸ���
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
			// ��һ����
			tempStr = tempData.at(16);
			_stscanf(tempStr,_T("%f"),&tempFloat_X);
			tempStr = tempData.at(18);
			_stscanf(tempStr,_T("%f"),&tempFloat_Y);
			tempStr = tempData.at(20);
			_stscanf(tempStr,_T("%f"),&tempFloat_Z);
			//
			glVertex3f(tempFloat_X, tempFloat_Y, tempFloat_Z);
			// �ڶ�����
			tempStr = tempData.at(22);
			_stscanf(tempStr,_T("%f"),&tempFloat_X);
			tempStr = tempData.at(24);
			_stscanf(tempStr,_T("%f"),&tempFloat_Y);
			tempStr = tempData.at(26);
			_stscanf(tempStr,_T("%f"),&tempFloat_Z);
			//
			glVertex3f(tempFloat_X, tempFloat_Y, tempFloat_Z);
			// ��������
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
			// ���ĸ���
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
	// ��������
	glNewList(m_Model_PolyList,GL_COMPILE);
	glBegin(GL_LINE);
	for (int i=0; i<m_PolylineList.size();i++)
	{

	}
	glEnd();
	glEndList();

}

GLuint CCruveModel::GetShowPlateList()
{
	return m_Model_PlateList;
}
