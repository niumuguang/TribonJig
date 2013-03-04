/*
ToolBox��
���ڴ�������������ɢ��������
*/

#pragma once
#include "stdafx.h"
#include <vector>
#include <tuple>
#include "DXF_File.h"

#include <cstdlib>
#include <sstream>
#include <iostream>
#include <string.h>
#include <cstring>
using namespace std;
//typedef vector<CString> DXFMODE;
typedef tuple<float, float, float> COORDINATE;
typedef vector<COORDINATE> POLYLINETYPE;

class CToolBox
{
public:
	CToolBox(void);
	~CToolBox(void);

public:
	// ����Dxf�ļ����ݵ���ں���
	CDXF_File ProgressDxf(vector<CString> FileContext);

public:
	// ��ȡDxf�ļ�����
	bool ReadDxf(LPCTSTR FileDir, vector<CString> &ReadContext);
	// ��CStringת��ΪDouble����
	double CString2Double(CString str);
	// ��Intת��ΪCString����
	CString Int2CString(int Num);

	// �µ�DXF��������
	//void GetPlanerHull(vector<CString> FileContext, int &Planer_IDX, vector<COORDINATE> &PlateRes);
}; 