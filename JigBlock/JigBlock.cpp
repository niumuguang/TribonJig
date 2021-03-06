
// JigBlock.cpp : 定义应用程序的类行为。
//
#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "JigBlock.h"
#include "MainFrm.h"

#include "JigBlockDoc.h"
#include "JigBlockView.h"
#include "afxcmn.h"
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CJigBlockApp

BEGIN_MESSAGE_MAP(CJigBlockApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CJigBlockApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
	ON_COMMAND(ID_FILE_OPEN, &CJigBlockApp::OnFileOpen)
END_MESSAGE_MAP()


// CJigBlockApp 构造

CJigBlockApp::CJigBlockApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则:
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("TribonModel.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CJigBlockApp 对象

CJigBlockApp theApp; //整个程序的入口


// CJigBlockApp 初始化

BOOL CJigBlockApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// 标准初始化
	first_X = -1; first_Y = -1; first_Z = -1;
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)

	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CJigBlockDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CJigBlockView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// 仅当具有后缀时才调用 DragAcceptFiles
	//  在 SDI 应用程序中，这应在 ProcessShellCommand 之后发生
	return TRUE;
}

int CJigBlockApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
//	CClientDC* m_pDC;
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	CProgressCtrl m_Progress;
	CButton m_testButton;
	afx_msg void OnBnClickedButton1();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
	//m_Progress.SetPos(100);
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	DDX_Control(pDX, IDC_BUTTON1, m_testButton);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_BUTTON1, &CAboutDlg::OnBnClickedButton1)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CJigBlockApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CJigBlockApp 消息处理程序

//void CAboutDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	MessageBox(_T("ON KEY DOWN"));
//
//	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
//}


CDocument* CJigBlockApp::OpenDocumentFile(LPCTSTR lpszFileName)
{
	// TODO: 在此添加专用代码和/或调用基类
	//MessageBox( _T("OPEN OK"));
	vector<CString> FileContext;
	//CAboutDlg aboutDlg;
	//aboutDlg.DoModal();
	//ProTest dd;
	//dd.DoModal();

	//CProgressDlg testDlg;
	//testDlg.ModifyStyle(WS_EX_APPWINDOW,0);
	////testDlg->ModifyStyle(WS_EX_APPWINDOW,0);
	//testDlg.DoModal();
	////CWnd *pWnd = AfxGetMainWnd();
	//CProgressDlg* testDlg = new CProgressDlg();
	//ProTest* testDlg = new ProTest;
	
	//testDlg->OnInitDialog();
	//testDlg->OnInitial();
	m_prodlg.Create(IDD_DIALOG1);
	//testDlg->ModifyStyle(WS_EX_APPWINDOW,0);
	m_prodlg.CenterWindow();
	m_prodlg.ShowWindow(SW_SHOW);
	m_prodlg.m_Pro.SetRange32(0,1000000);
	m_prodlg.m_Pro.SetStep(1);
	//m_prodlg.m_Pro.SetPos(10);
	//CProgressCtrl* ss = testDlg->returnProCtrl();
	//ss.SetPos(400);
	/*CProgressDlg* dlg = new CProgressDlg();
	dlg->Create(CProgressDlg::IDD,GetDesktopWindow());
	dlg->ShowWindow(SW_SHOW);*/

	//testDlg->ShowWindow(0);
	//testDlg->GetParent()->EnableWindow(FALSE);
	//testDlg.Create(_T("s"),pWnd);
	//testDlg.DoModal();
	//ProDlg.DoModal();
	////MessageBox(s, _T("aa"), _T("bb"), 0);
	//this->DoMessageBox(_T("abc"), 0, 1);
	//Application->MessageBox("警告信息框","警告信息框",MB_ICONWARNING)
	//MessageBox("这是一个确定 取消的消息框！","标题", MB_OKCANCEL );
	CToolBox tl_Box;
	//testDlg->setPosGo();
	bool tempRes = tl_Box.ReadDxf(lpszFileName, FileContext);//读取文件返回 FileContext 
	//m_prodlg.m_Pro.SetPos(10);
	if(tempRes == false)
	{
		theApp.DoMessageBox(_T("打开文件失败！"),0,1);
	}
	//m_prodlg.m_Pro.SetPos(30);
	m_DxfData = tl_Box.ProgressDxf(FileContext);// 计算量大
	m_ModelList = m_DxfData.GetModelList();
	// 分析的到显示列表
	// 临时显示列表
	GLuint tempShowList;
	vector<GLuint> tempPolyList;
	//testDlg->setPosGo();
	//m_prodlg.m_Pro.SetPos(20);
	for (int idx=0;idx<m_ModelList.size();idx++)
	{
		m_prodlg.m_Pro.OffsetPos(1);
		//testDlg.m_Pro.SetStep(5);
		//m_prodlg.m_Pro.OffsetPos(0.1);
		m_prodlg.OnPaint();
		CModel tempModel;
		tempModel = m_ModelList.at(idx);
		if (tempModel.GetModelType() == "CRUVEMODEL")
		{
			//testDlg->setPosGo();
			CCruveModel tempCruveModel(tempModel);// 计算量大
			//m_CruveDataList = tempCruveModel.GetCoorList();
			tempShowList = tempCruveModel.GetShowPlateList();
			resShowListVec.push_back(tempShowList);
			tempPolyList = tempCruveModel.GetShowPolyList();
			for (int i=0; i<tempPolyList.size(); i++)
			{
				resPolyListVec.push_back(tempPolyList.at(i));
			}
		}
		else if (tempModel.GetModelType() == "PLANARMODEL")
		{
			CPlanarModel tempPlanarModel(tempModel);
			tempShowList = tempPlanarModel.GetShowPlateist();
			resShowListVec.push_back(tempShowList);
		}
		//else if (tempModel.GetModelType() == "PLANARMODEL")
		//{
		//	//CPlanarModel tempPlanarModel(tempModel);

		//}
	}
	//m_prodlg.m_Pro.SetPos(10000000);
	m_prodlg.DestroyWindow();
	return CWinApp::OpenDocumentFile(lpszFileName);
}

vector<COORDINATE> CJigBlockApp::getPlateData( void )
{
	return PlateDataList;
}

vector<COORDINATE> CJigBlockApp::getCruveData( void )
{
	return m_CruveDataList;
}

vector<POLYLINETYPE> CJigBlockApp::getPolyData( void )
{
	return PolyData;
}

CDXF_File CJigBlockApp::getDxfFile()
{
	return m_DxfData;
}

vector<CModel> CJigBlockApp::GetModelList()
{
	return m_ModelList;
}

vector<GLuint> CJigBlockApp::getShowListVec()
{
	return resShowListVec;
}

vector<GLuint> CJigBlockApp::getPolyListVec()
{
	return resPolyListVec;
}

 ProgressDlg* CJigBlockApp::getProDlgHandle()
 {
 	return &m_prodlg;
 }

 GLfloat CJigBlockApp::getFirstX()
 {
	 return first_X;
 }

 void CJigBlockApp::setFirstX(GLfloat firstX)
 {
	 first_X = firstX;
 }

 GLfloat CJigBlockApp::getFirstY()
 {
	 return first_Y;
 }

 void CJigBlockApp::setFirstY( GLfloat firstY )
 {
	 first_Y = firstY;
 }

 GLfloat CJigBlockApp::getFirstZ()
 {
	 return first_Z;
 }

 void CJigBlockApp::setFirstZ( GLfloat firstZ )
 {
	 first_Z = firstZ;
 }

void CAboutDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//m_Progress.SetPos(100);
}