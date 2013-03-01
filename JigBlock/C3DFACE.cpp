#include "StdAfx.h"
#include "C3DFACE.h"


C3DFACE::C3DFACE(void)
{
}


C3DFACE::~C3DFACE(void)
{
}

// 设置总体数据
void C3DFACE::SetData( vector<CString> Data )
{
	m_3DFACE_Data = Data;
}

// 设置坐标数据
void C3DFACE::SetCoord( COORDINATE coord0,COORDINATE coord1,COORDINATE coord2,COORDINATE coord3 )
{
	m_coord0 = coord0;
	m_coord1 = coord1;
	m_coord2 = coord2;
	m_coord3 = coord3;
}

// 设置颜色索引值
void C3DFACE::SetColorIDX( int ColorIndex )
{
	m_ColorIndex = ColorIndex;
}

COORDINATE C3DFACE::GetCoord0()
{
	return m_coord0;
}

COORDINATE C3DFACE::GetCoord1()
{
	return m_coord1;
}

COORDINATE C3DFACE::GetCoord2()
{
	return m_coord2;
}

COORDINATE C3DFACE::GetCoord3()
{
	return m_coord3;
}

vector<COORDINATE> C3DFACE::CoordList()
{
	vector<COORDINATE> resList;
	resList.push_back(m_coord0);
	resList.push_back(m_coord1);
	resList.push_back(m_coord2);
	resList.push_back(m_coord3);
	return resList;
}
