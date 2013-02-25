
// JigBlock.h : JigBlock 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CJigBlockApp:
// 有关此类的实现，请参阅 JigBlock.cpp
//
#include <vector>
#include "ToolBox.h"

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
	vector<COORDINATE> PlateData;
	vector<COORDINATE> CruveData;
	//vector<COORDINATE> PolyLineType;
	vector<POLYLINETYPE> PolyData;

	CDXF_File m_DxfData;
	vector<CModel> m_ModelList;

public:
	vector<COORDINATE> getPlateData(void);
	vector<COORDINATE> getCruveData(void);
	vector<POLYLINETYPE> getPolyData(void);

	CDXF_File getDxfFile();
	vector<CModel> GetModelList();
};

extern CJigBlockApp theApp;
