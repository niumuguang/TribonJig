/*
����ģ�͵Ļ���
���ڴ���͹����Dxf�ж�ȡ����ģ��
*/

#pragma once
#include "stdafx.h"
#include <vector>
#include <string.h>
#include <cstring>

using namespace std;

//#include "CruveModel.h"


class CModel
{
public:
	CModel(void); 
	~CModel(void);

public:
	// ����ģ�͵�����
	void SetModelData(vector<CString> ModelData);
	// ����ģ�͵�����
	void SetModelName(CString ModelName);
	// ����ģ�͵�����
	CString GetModelType();
	

public:
	// ģ�͵����� ����ģ��������ܵ�����
	CString m_ModelName;
	// ģ�͵���������
	vector<CString> m_ModelData;
	// ģ�͵�����
	CString m_ModelType; // OTHERMODEL,CRUVEMODEL,PLANARMODEL ��������
	// ����������
	// ���������б�

	// ��ʾ�б����� ����
	//vector<GLuint> ShowListVec;
	// ��ʾ�б� ����֧��
	GLuint m_Model_PlateList;
	GLuint m_Model_PolyList;
};

