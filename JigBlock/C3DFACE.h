/*
C3DFACE��
Ϊÿ����ʾ��С�浥Ԫ��ʵ����
*/
#pragma once

#include "stdafx.h"
#include <vector>
#include <string.h>
#include <cstring>
#include <tuple>

using namespace std;
typedef tuple<double, double, double> COORDINATE;

class C3DFACE
{
public:
	C3DFACE(void);
	~C3DFACE(void);

public:
	// �������������
	vector<CString> m_3DFACE_Data;
	// �ֱ𴢴�����ĸ���
	// ������ĸ���ʵ��Ϊ������������������
	// ƽ����ĸ���Ϊ�ĸ����ھ�������
	COORDINATE m_coord0,m_coord1,m_coord2,m_coord3;
	// ��ɫ����ֵ
	int m_ColorIndex;

public:
	// ������ɫ����ֵ
	void SetColorIDX(int ColorIndex);
	// ������������
	void SetCoord(COORDINATE coord0,COORDINATE coord1,COORDINATE coord2,COORDINATE coord3);
	// ������������
	void SetData(vector<CString> Data);
	// ��õ�һ������ֵ
	COORDINATE GetCoord0();
	COORDINATE GetCoord1();
	COORDINATE GetCoord2();
	COORDINATE GetCoord3();
};

