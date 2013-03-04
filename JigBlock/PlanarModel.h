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
	// 将平面板架分割成 小的3Dface
	void DivisionData();
	// 得到平面板架的 显示列表
	void Planar_ShowList();
	// 返回平面板架的显示列表
	GLuint GetShowPlateist();
};

