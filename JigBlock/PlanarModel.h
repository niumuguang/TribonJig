#pragma once
#include "model.h"

class CPlanarModel :
	public CModel
{
public:
	CPlanarModel(void);
	~CPlanarModel(void);

public:
	vector<CString> m_3DFaceData;
	vector<vector<CString>> m_PlateList;

public:
	void DivisionData();

};

