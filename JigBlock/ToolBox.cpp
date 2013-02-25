#include "StdAfx.h"
#include "ToolBox.h"
#include "JigBlock.h"


CToolBox::CToolBox(void)
{
}


CToolBox::~CToolBox(void)
{
}

// 读取Dxf文件数据
bool CToolBox::ReadDxf(LPCTSTR FileDir, vector<CString> &ReadContext)
{
	CStdioFile FileHandle;
	bool RunState;
	RunState = FileHandle.Open(FileDir, CFile::modeRead|CFile::typeText);

	if (RunState == true)
	{
		CString TextContent;
		while(FileHandle.ReadString(TextContent))
		{
			ReadContext.push_back(TextContent);
		}
		return true;
	}
	return false;
}
// 处理Dxf文件数据的入口函数
CDXF_File CToolBox::ProgressDxf(vector<CString> FileContext, vector<COORDINATE> &PlateRes, vector<COORDINATE> &CruveRes, vector<POLYLINETYPE> &PolyRes)
{
	CDXF_File DXF_File(FileContext);
	//DXF_File.init(FileContext);
	//DXF_File.SetFileContext(FileContext);
	return DXF_File;
}

//
//
//void CToolBox::ProgressDxf( vector<CString> FileContext, vector<COORDINATE> &PlateRes,  vector<COORDINATE> &CruveRes, vector<POLYLINETYPE> &PolyRes)
//{
//	COORDINATE tempCoor;
//	int Counter = 0;
//	int testNum = 0;
//	int Idx;
//	for (int i =0; i<FileContext.size(); i++)
//	{
//		if(FileContext[i] == "Object name")
//		{
//			if (FileContext[i] == "POLYLINE")
//			{
//				while(FileContext[i+6] == "POLYLINE")
//				{
//					//////////////////////////////////////////////////////////////////////////
//					testNum = 0;
//					Idx = 0;
//					POLYLINETYPE tempPoly;
//					Idx = i+6;
//					bool roo = true;
//					//CString temp = Int2CString(Idx);
//					//theApp.DoMessageBox(temp,0,1);
//					while(roo)  // 提取Polyline数据
//					{
//						if (FileContext[Idx] == "AcDb3dPolylineVertex")
//						{
//							//CString temp = Int2CString(Idx);
//							//theApp.DoMessageBox(temp,0,1);
//							Counter = 0;
//							while(Counter<13) // 第一个坐标
//							{
//								if (FileContext[Idx+Counter] == "   10")
//								{
//									//CString temp = Int2CString(Counter);
//									//theApp.DoMessageBox(temp,0,1);
//									get<0>(tempCoor) = CString2Double(FileContext[Idx+Counter+1]);
//								}
//								if (FileContext[Idx+Counter] == "   20")
//								{
//									get<1>(tempCoor) = CString2Double(FileContext[Idx+Counter+1]);
//								}
//								if (FileContext[Idx+Counter] == "   30")
//								{
//									get<2>(tempCoor) = CString2Double(FileContext[Idx+Counter+1]);
//								}
//								Counter = Counter + 1;
//							}
//							tempPoly.push_back(tempCoor);
//						}
//						if (FileContext[Idx] == "SEQEND")
//						{
//							PolyRes.push_back(tempPoly);
//							tempPoly.clear();
//							//break;
//						}
//						// 跳出条件 循环增量
//						if (FileContext[Idx] == "Object name" || FileContext[Idx] == "ENDSEC"|| FileContext[Idx] == "3DFACE")
//						{
//							break;
//						}
//						Idx = Idx + 1;
//					}
//					//////////////////////////////////////////////
//					//CString temp = Int2CString(Idx);
//					//theApp.DoMessageBox(temp,0,1);
//					roo = true;
//					//Idx = i+6;
//					while(roo)
//					{
//						if (FileContext[Idx] == "AcDbFace")
//						{
//							Counter = 0;
//							while (Counter < 28)
//							{
//								if (FileContext[Idx+Counter] == "   10")
//								{
//									//CString temp = Int2CString(Counter);
//									//theApp.DoMessageBox(temp,0,1);
//									get<0>(tempCoor) = CString2Double(FileContext[Idx+Counter+1]);
//								}
//								if (FileContext[Idx+Counter] == "   20")
//								{
//									get<1>(tempCoor) = CString2Double(FileContext[Idx+Counter+1]);
//								}
//								if (FileContext[Idx+Counter] == "   30")
//								{
//									get<2>(tempCoor) = CString2Double(FileContext[Idx+Counter+1]);
//								}
//								Counter = Counter + 1;
//							}
//							CruveRes.push_back(tempCoor);// first
//
//							//////////////////////////////////////////////////////////////////////////
//							Counter = 0;
//							while(Counter<29) // 第二个坐标
//							{
//								if (FileContext[Idx+Counter] == "   11")
//								{
//									get<0>(tempCoor) = CString2Double(FileContext[Idx+Counter+1]);
//								}
//								if (FileContext[Idx+Counter] == "   21")
//								{
//									get<1>(tempCoor) = CString2Double(FileContext[Idx+Counter+1]);
//								}
//								if (FileContext[Idx+Counter] == "   31")
//								{
//									get<2>(tempCoor) = CString2Double(FileContext[Idx+Counter+1]);
//								}
//								Counter = Counter + 1;
//							}
//							CruveRes.push_back(tempCoor);//second
//							//////////////////////////////////////////////////////////////////////////
//							Counter = 0;
//							while(Counter<29) // 第三个坐标
//							{
//								if (FileContext[Idx+Counter] == "   12")
//								{
//									get<0>(tempCoor) = CString2Double(FileContext[Idx+Counter+1]);
//								}
//								if (FileContext[Idx+Counter] == "   22")
//								{
//									get<1>(tempCoor) = CString2Double(FileContext[Idx+Counter+1]);
//								}
//								if (FileContext[Idx+Counter] == "   32")
//								{
//									get<2>(tempCoor) = CString2Double(FileContext[Idx+Counter+1]);
//								}
//								Counter = Counter + 1;
//							}
//							CruveRes.push_back(tempCoor);//third
//							//////////////////////////////////////////////////////////////////////////
//							Counter = 0;
//							while(Counter<29) // 第四个坐标
//							{
//								if (FileContext[Idx + Counter] == "   13")
//								{
//									get<0>(tempCoor) = CString2Double(FileContext[ Idx +Counter+1]);
//								}
//								if (FileContext[Idx +Counter] == "   23")
//								{
//									get<1>(tempCoor) = CString2Double(FileContext[ Idx +Counter+1]);
//								}
//								if (FileContext[Idx + Counter] == "   33")
//								{
//									get<2>(tempCoor) = CString2Double(FileContext[ Idx +Counter+1]);
//								}
//								Counter = Counter + 1;
//							}
//							CruveRes.push_back(tempCoor);//fourth
//						}
//						if (FileContext[Idx] == "Object name" || FileContext[Idx] == "ENDSEC"|| FileContext[Idx] == "POLYLINE")
//						{
//							CString temp = Int2CString(Idx);
//							theApp.DoMessageBox(temp,0,1);
//							i = Idx-2;
//							break;
//						}
//						Idx = Idx + 1;
//					}
//					if (FileContext[i] == "Object name" || FileContext[i] == "ENDSEC")
//					{
//						//CString temp = Int2CString(Idx);
//						//theApp.DoMessageBox(temp,0,1);
//						break;
//					}
//					i = i + 1;
//				}
//
//			}
//			
//			///////////////////////////////////////////////////////////////////////////////////////
//			if (FileContext[i] == "3DFACE")
//			{
//				// 平面模型
//				int Index = i;
//				bool roo = true;
//				while(roo)
//				{
//					if (FileContext[Index] == "AcDbFace")
//					{
//						//Counter = 0;
//						//while(Counter<29) // 第一个坐标
//						//{
//						//	if (FileContext[Index+Counter] == "   10")
//						//	{
//						//		get<0>(tempCoor) = CString2Double(FileContext[Index+Counter+1]);
//						//	}
//						//	if (FileContext[Index+Counter] == "   20")
//						//	{
//						//		get<1>(tempCoor) = CString2Double(FileContext[Index+Counter+1]);
//						//	}
//						//	if (FileContext[Index+Counter] == "   30")
//						//	{
//						//		get<2>(tempCoor) = CString2Double(FileContext[Index+Counter+1]);
//						//	}
//						//	Counter = Counter + 1;
//						//}
//						tempCoor = GetPlanerDataF(FileContext, Index);
//						PlateRes.push_back(tempCoor);
//
//						Counter = 0;
//						while(Counter<29) // 第二个坐标
//						{
//							if (FileContext[Index+Counter] == "   11")
//							{
//								get<0>(tempCoor) = CString2Double(FileContext[Index+Counter+1]);
//							}
//							if (FileContext[Index+Counter] == "   21")
//							{
//								get<1>(tempCoor) = CString2Double(FileContext[Index+Counter+1]);
//							}
//							if (FileContext[Index+Counter] == "   31")
//							{
//								get<2>(tempCoor) = CString2Double(FileContext[Index+Counter+1]);
//							}
//							Counter = Counter + 1;
//						}
//						PlateRes.push_back(tempCoor);
//
//						Counter = 0;
//						while(Counter<29) // 第三个坐标
//						{
//							if (FileContext[Index+Counter] == "   12")
//							{
//								get<0>(tempCoor) = CString2Double(FileContext[Index+Counter+1]);
//							}
//							if (FileContext[Index+Counter] == "   22")
//							{
//								get<1>(tempCoor) = CString2Double(FileContext[Index+Counter+1]);
//							}
//							if (FileContext[Index+Counter] == "   32")
//							{
//								get<2>(tempCoor) = CString2Double(FileContext[Index+Counter+1]);
//							}
//							Counter = Counter + 1;
//						}
//						PlateRes.push_back(tempCoor);
//
//						Counter = 0;
//						while(Counter<29) // 第四个坐标
//						{
//							if (FileContext[Index + Counter] == "   13")
//							{
//								get<0>(tempCoor) = CString2Double(FileContext[ Index +Counter+1]);
//							}
//							if (FileContext[Index +Counter] == "   23")
//							{
//								get<1>(tempCoor) = CString2Double(FileContext[ Index +Counter+1]);
//							}
//							if (FileContext[Index + Counter] == "   33")
//							{
//								get<2>(tempCoor) = CString2Double(FileContext[ Index +Counter+1]);
//							}
//							Counter = Counter + 1;
//						}
//						PlateRes.push_back(tempCoor);
//					}
//					// 跳出条件 循环增量
//					if (FileContext[Index] == "Object name" || FileContext[Index] == "ENDSEC")
//					{
//						break;
//					}
//					Index = Index + 1;
//				}
//			}
//			i = i + 1;
//		}
//		//
//	}
//}



// 将CString转换为Double类型
double CToolBox::CString2Double( CString str )
{
	double res;
	res = _ttof(str);
	//res = _ttoi(str);
	return res;
}
// 将Int转换为CString类型
CString CToolBox::Int2CString( int Num )
{
	CString SS;
	SS.Format(_T("%d"), Num);
	return SS;
}

void CToolBox::GetPlanerHull( vector<CString> FileContext, int &Planer_IDX, vector<COORDINATE> &PlateRes )
{
	int IDX = Planer_IDX; // 这个板从这个索引开始
	int RecordIDX = FileContext.size()-2; // 这个板到这个索引结束

	for (int IDX = Planer_IDX; IDX<FileContext.size(); IDX++)
	{
		if (FileContext[IDX] == "Object name")
		{
			RecordIDX = IDX - 2; // 上移两个单位方便下次查找 跳出函数后会下一一个单位
			break;
		}
		else if (FileContext[IDX] == "ENDSEC")
		{
			RecordIDX = IDX - 2; // 上移两个单位方便下次查找 跳出函数后会下一一个单位
			break;
		}
	}
	Planer_IDX = RecordIDX; // 返回已经遍历到的位置
	// 获得该平板的数据段
	vector<CString> FileSegment;
	for (;IDX<RecordIDX; IDX++)
	{
		FileSegment.push_back(FileContext[IDX]);
	}
	// 解析数据段
	//COORDINATE tempCoor;
	//for (int SegmentIDX = 0; SegmentIDX<FileSegment.size(); SegmentIDX++)
	//{
	//	if (FileSegment[SegmentIDX] == "AcDbFace")
	//	{

	//	}
	//}
}

//void CToolBox::GetAcDbFaceData( vector<CString> FileSegment, vector<COORDINATE> &PlateData )
//{
//	COORDINATE tempCoor;
//	for (int SegmentIDX = 0; SegmentIDX<FileSegment.size();)
//	{
//		if (FileSegment[SegmentIDX] == "AcDbFace")
//		{
//			int Counter = 0;
//			while(Counter<29) // 第一个坐标
//			{
//				if (FileContext[Index+Counter] == "   10")
//				{
//					get<0>(tempCoor) = CString2Double(FileContext[Index+Counter+1]);
//				}
//				if (FileContext[Index+Counter] == "   20")
//				{
//					get<1>(tempCoor) = CString2Double(FileContext[Index+Counter+1]);
//				}
//				if (FileContext[Index+Counter] == "   30")
//				{
//					get<2>(tempCoor) = CString2Double(FileContext[Index+Counter+1]);
//				}
//				Counter = Counter + 1;
//			}
//			PlateData.push_back(tempCoor);
//
//		}
//	}
//}
