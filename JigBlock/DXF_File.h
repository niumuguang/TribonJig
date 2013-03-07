// This Class is a object for Dxf File
/*
Dxf_File��
DXF�ļ���ʵ������
���ڴ���Dxf�ļ���һЩ���ܺ���
*/
#pragma once
#include "stdafx.h"
#include <vector>
#include <tuple>

#include <string.h>
#include <cstring>
#include "Block.h"
#include "Model.h"
#include "OtherModel.h"
#include "CruveModel.h"
#include "PlanarModel.h"
#include "ProDlg.h"

using namespace std;
typedef tuple<float, float, float> COORDINATE;
typedef vector<COORDINATE> POLYLINETYPE;

class CDXF_File
{
public:
	CDXF_File(void);
	CDXF_File(vector<CString> InputContext);
	~CDXF_File(void);

public:
	// ���� FileContext ����dxf������
	bool SetFileContext(vector<CString> InputContext);
	// ��section �ָ�dxf�ļ�����
	void SetSEC();
	// ��block section �з���block���ݣ�������BLK_Context
	void GetBlocksSEC();
	// ����BLK_Context��ÿ��ģ��
	void AnsysDxfData();
	// ��������ģ�ͺ��� ��ʼ������ģ��
	//void TransferModel();
	// �õ�BLK����
	CString	GetBlockName(vector<CString> InputContext);
	// ����dxf�ļ���ģ���б�
	vector<CModel> GetModelList();

private:
	vector<CString> FileContext;
	vector<CString> HEADER_SEC;
	vector<CString> CLASSES_SEC;
	vector<CString> TABLES_SEC;
	vector<CString> BLOCKS_SEC;
	vector<CString> ENTITIES_SEC;
	vector<CString> OBJECTS_SEC;

private:
	vector<vector<CString>> BLK_Context;
	//vector<vector<CString>> Planar_BLK, Cruve_BLK,Other_BLK;
	vector<CModel> m_ModelList;// ����DXF�ļ��е�����ģ��
	ProgressDlg* MainPro;
};

