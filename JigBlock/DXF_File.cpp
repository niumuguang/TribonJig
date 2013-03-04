#include "StdAfx.h"
#include "DXF_File.h"


CDXF_File::CDXF_File(void)
{
}

CDXF_File::CDXF_File( vector<CString> InputContext )
{
	SetFileContext(InputContext);  // 设置内容到 CDXF_File 类
	SetSEC(); // 分割每一个 Section， 这步有点多余
	GetBlocksSEC();
	AnsysDxfData();// 计算量大
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
	// 将每个BlockSEC 分割成小的Block
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
				// 如果发现Block终止标识，加入最后一个Block内容，设置跳跃值plusNum
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
	// 优化Section区分， 只提取Block Section数据 
	bool roo = true;
	int idx = 0;
	for (int i = 0; i<FileContext.size(); i++)
	{
		if (FileContext[i] == "SECTION")
		{
			// Blocks Section
			// Blocks Section 还要拷贝到容器中 浪费时间
			// 将Blocks Section下的所有Blocks分离并加入之BLOCS_SEC容器
			if (FileContext[i+2] == "BLOCKS")
			{
				idx = i;
				roo = true;
				while(roo)
				{
					if (FileContext[idx] == "ENDSEC"|| FileContext[idx] == "EOF")
					{
						// 发现结束标识 则将最后一个Block加入
						roo = false;
						BLOCKS_SEC.push_back(FileContext[idx]);
					}
					// 不是结束标识 正常处理数据
					BLOCKS_SEC.push_back(FileContext[idx]);
					idx = idx + 1;
				}
			}
		}
	}
}

void CDXF_File::AnsysDxfData()//  计算量大
{
	// 解析Blocks Section数据 到对象
	vector<CString> tempContext;
	CModel tempModel;
	// 遍历所有Block数据
	for (int i=0; i<BLK_Context.size(); i++)
	{
		tempContext = BLK_Context.at(i);
		//tempModel.SetModelData(tempContext);
		//ModelList.push_back(tempModel);
		CString tempName = GetBlockName(tempContext);
		// 如果 为其他模型 则跳过
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
						// 如果模型为曲面板
						CCruveModel temp_CruveModel(tempContext,tempName);
						temp_CruveModel.DivisionData(i+6);// 计算量大
						m_ModelList.push_back(temp_CruveModel);
						break;
					}
					else if (tempContext.at(i+6) == "3DFACE")
					{
						// 如果模型为平面板架
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

