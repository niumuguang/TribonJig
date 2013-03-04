#pragma once
#include "model.h"

class CPlanarModel :
	public CModel
{
public:
	CPlanarModel(void);
	CPlanarModel(vector<CString> Context, CString name);
	CPlanarModel(CModel transModel);
	~CPlanarModel(void);

public:
	vector<CString> m_3DFaceData;
	vector<vector<CString>> m_PlateList;

public:
	// ��ƽ���ָܷ�� С��3Dface
	void DivisionData();
	// �õ�ƽ���ܵ� ��ʾ�б�
	void Planar_ShowList();
	// ����ƽ���ܵ���ʾ�б�
	GLuint GetShowPlateist();
};

