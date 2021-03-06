
// JigBlock.h : JigBlock 应用程序的主头文件
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
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CJigBlockApp:
// 有关此类的实现，请参阅 JigBlock.cpp
//
//#include <vector>
#include "ToolBox.h"
#include "ProDlg.h"
//#include <vector>

class CJigBlockApp : public CWinApp
{
public:
	CJigBlockApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
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
	vector<GLuint> resPolyListVec;
	GLfloat first_X, first_Y, first_Z;

public:
	ProgressDlg m_prodlg;
	GLfloat getFirstX();
	void setFirstX(GLfloat firstX);
	GLfloat getFirstY();
	void setFirstY(GLfloat firstY);
	GLfloat getFirstZ();
	void setFirstZ(GLfloat firstZ);

public:
	vector<COORDINATE> getPlateData(void);
	vector<COORDINATE> getCruveData(void);
	vector<POLYLINETYPE> getPolyData(void);

	CDXF_File getDxfFile();
	vector<CModel> GetModelList();
	vector<GLuint> getShowListVec();
	vector<GLuint> getPolyListVec();
	ProgressDlg* getProDlgHandle();
};

extern CJigBlockApp theApp;
