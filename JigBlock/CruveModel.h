/*
�̳���CModel��
���������ܵ�ʵ�廯
���������ܵ�������ݺͷ���
*/

#pragma once

#include "stdafx.h"
#include <vector>
#include <string.h>
#include <cstring>
#include <tuple>

using namespace std;
typedef tuple<float, float, float> COORDINATE;

#include "model.h"
//#include "Model.h"
//#include <tuple>
#include "C3DFACE.h"
#include "math3d.h"

class CCruveModel:public CModel
{
public:
	CCruveModel(void);
	//
	CCruveModel(vector<CString> TotalData, CString name);
	// ������CModelת��Ϊ�����ģ����
	CCruveModel(CModel transModel);
	~CCruveModel(void);

public:
	// �ָ�Data����
	void DivisionData();
	// �ָ�Data����
	void DivisionData(int idx);
	// �����ݷ�Ϊ �������б�ͺ��������б�
	void Plate_Poly_ShowList();
// 	// ������������б�
// 	vector<C3DFACE> Get3DFaceList();
	// ֱ����ʾ��
	void ShowPlate();
	// ���ض��������б�
//	void DisposePointList();
	// �������ж�������
	vector<COORDINATE> GetCoorList();
	// ������ʾ�б�����
	GLuint GetShowPlateList();
	vector<GLuint> GetShowPolyList();

public:
	// ��ʱ�������ݽṹ ���Ż���
	vector<CString> m_Polyline;
	// ���������б�
	vector<vector<CString>> m_PolylineList;// ���������ܱ߽�����
	// ��ʱ�����ݽṹ ���Ż���
	vector<CString> m_3DFaceData;
	// ��ʱ�ָ��������ݴ���
	vector<vector<CString>> m_PlateList;
	

private:
	// �����ݴ����б�
	vector<C3DFACE> m_C3DFace_List;
	// ���ж�������
	//vector<COORDINATE> m_DataCoorList;
	// �����ʾ�б�
	//vector<float> m_PlateShowList;
	//// ��ʾ�б�������
	//GLuint m_Model_PlateList;
	//GLuint m_Model_PolyList;

	// ��ʾ�б� ����
	//vector<GLuint> ShowListVec;

	//void push(vector &, float*)
	//{
	//	for (3)
	//	{
	//		m_PlateShowList.push_back(*(p + i))
	//	}
	//}
	

	// �������
	inline void JigCrossProduct(M3DVector3f result, M3DVector3d u, M3DVector3d v)
	{
		result[0] = u[1]*v[2] - v[1]*u[2];
		result[1] = -u[0]*v[2] + v[0]*u[2];
		result[2] = u[0]*v[1] - v[0]*u[1];
	}
};
