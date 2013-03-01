
// JigBlock.h : JigBlock Ӧ�ó������ͷ�ļ�
//
#pragma once
#include "stdafx.h"
#include <vector>
#include <string.h>
#include <cstring>
#include <tuple>

using namespace std;

//typedef tuple<double, double, double> COORDINATE;
typedef tuple<float, float, float> COORDINATE;

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CJigBlockApp:
// �йش����ʵ�֣������ JigBlock.cpp
//
//#include <vector>
#include "ToolBox.h"
//#include <vector>

class CJigBlockApp : public CWinApp
{
public:
	CJigBlockApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
	//bool ReadFileL(CString Dir_ConfigFile, vector<CString>);
	//afx_msg void OnFileOpen();

private:
	vector<COORDINATE> PlateDataList;
	vector<COORDINATE> m_CruveDataList;
	vector<POLYLINETYPE> PolyData;

	CDXF_File m_DxfData;
	vector<CModel> m_ModelList;
	//vector<COORDINATE> CoorList_Cruve;
	// testing
	GLuint testing;
	vector<GLuint> resShowListVec;

public:
	vector<COORDINATE> getPlateData(void);
	vector<COORDINATE> getCruveData(void);
	vector<POLYLINETYPE> getPolyData(void);

	CDXF_File getDxfFile();
	vector<CModel> GetModelList();
	vector<GLuint> getShowListVec();
};

extern CJigBlockApp theApp;
