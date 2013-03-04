#include "StdAfx.h"
#include "DXF_File.h"


CDXF_File::CDXF_File(void)
{
}

CDXF_File::CDXF_File( vector<CString> InputContext )
{
	SetFileContext(InputContext);  // �������ݵ� CDXF_File ��
	SetSEC(); // �ָ�ÿһ�� Section�� �ⲽ�е����
	GetBlocksSEC();
	AnsysDxfData();// ��������
}


CDXF_File::~CDXF_File(void)
{
}

bool CDXF_File::SetFileContext( vector<CString> InputContext )
{
	if (InputContext.size() == 0)
	{
		return false;
	}
	FileContext = InputContext;
	return true;
}

void CDXF_File::GetBlocksSEC()
{
	// ��ÿ��BlockSEC �ָ��С��Block
	vector<CString> tempStr;
	tempStr = BLOCKS_SEC;
	vector<CString> BLKtemp;
	int plusNum = 0;
	for (int i=0; i<tempStr.size(); i++)
	{
		if (tempStr[i] == "BLOCK")
		{
			for(int num=0; tempStr[i+num] != "ENDBLK";num++)
			{
				// �������Block��ֹ��ʶ���������һ��Block���ݣ�������ԾֵplusNum
				BLKtemp.push_back(tempStr[i+num]);
				plusNum = num;
			}
			BLKtemp.push_back(_T("ENDBLK"));
			BLK_Context.push_back(BLKtemp);
			BLKtemp.clear();
			i = i + plusNum;
		}
	}
	return;
}

void CDXF_File::SetSEC()
{
	// �Ż�Section���֣� ֻ��ȡBlock Section���� 
	bool roo = true;
	int idx = 0;
	for (int i = 0; i<FileContext.size(); i++)
	{
		if (FileContext[i] == "SECTION")
		{
			// Blocks Section
			// Blocks Section ��Ҫ������������ �˷�ʱ��
			// ��Blocks Section�µ�����Blocks���벢����֮BLOCS_SEC����
			if (FileContext[i+2] == "BLOCKS")
			{
				idx = i;
				roo = true;
				while(roo)
				{
					if (FileContext[idx] == "ENDSEC"|| FileContext[idx] == "EOF")
					{
						// ���ֽ�����ʶ �����һ��Block����
						roo = false;
						BLOCKS_SEC.push_back(FileContext[idx]);
					}
					// ���ǽ�����ʶ ������������
					BLOCKS_SEC.push_back(FileContext[idx]);
					idx = idx + 1;
				}
			}
		}
	}
}

void CDXF_File::AnsysDxfData()//  ��������
{
	// ����Blocks Section���� ������
	vector<CString> tempContext;
	CModel tempModel;
	// ��������Block����
	for (int i=0; i<BLK_Context.size(); i++)
	{
		tempContext = BLK_Context.at(i);
		//tempModel.SetModelData(tempContext);
		//ModelList.push_back(tempModel);
		CString tempName = GetBlockName(tempContext);
		// ��� Ϊ����ģ�� ������
		//if (tempName == "None"||tempName == "*PAPER_SPACE" || tempName == "*MODEL_SPACE")
		//{
		//	
		//}
		//else
		if(tempName != "None"&&tempName != "*PAPER_SPACE"&&tempName != "*MODEL_SPACE")
		{
			for (int i=0;i<tempContext.size();i++)
			{
				if (tempContext.at(i) == "Object name")
				{
					if (tempContext.at(i+6) == "POLYLINE")
					{
						// ���ģ��Ϊ�����
						CCruveModel temp_CruveModel(tempContext,tempName);
						temp_CruveModel.DivisionData(i+6);// ��������
						m_ModelList.push_back(temp_CruveModel);
						break;
					}
					else if (tempContext.at(i+6) == "3DFACE")
					{
						// ���ģ��Ϊƽ����
						CPlanarModel temp_PlanarModel(tempContext,tempName);
						//temp_PlanarModel.SetModelData(tempContext);
						//temp_PlanarModel.SetModelName(tempName);
						temp_PlanarModel.DivisionData();
						m_ModelList.push_back(temp_PlanarModel);
						break;
					}
				}
				//
			}
		}
	}

 }

//void CDXF_File::TransferModel()
//{
//	CModel tempModel;
//	CString ModelType = _T("None");
//	for (int i = 0; i<m_ModelList.size(); i++)
//	{
//		tempModel = m_ModelList.at(i);
//		ModelType = tempModel.GetModelType();
//		if (ModelType == "OTHERMODEL")
//		{
//			
//		}
//		else if(ModelType == "CRUVEMODEL")
//		{
//
//		}
//		else if(ModelType == "PLANARMODEL")
//		{
//
//		}
//	}
//}


CString CDXF_File::GetBlockName(vector<CString> InputContext)
{
	CString BLK_name = _T("None");
	for (int i=0; i<InputContext.size(); i++)
	{
		if (InputContext.at(i) == "   2")
		{
			BLK_name = InputContext.at(i+1);
			break;
		}
		if(InputContext.at(i) == "   3")
		{
			BLK_name = InputContext.at(i+1);
			break;
		}
	}
	return BLK_name;
}

vector<CModel> CDXF_File::GetModelList()
{
	return m_ModelList;
}

