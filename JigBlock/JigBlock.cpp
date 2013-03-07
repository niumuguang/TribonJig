
// JigBlock.cpp : ����Ӧ�ó��������Ϊ��
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
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
	ON_COMMAND(ID_FILE_OPEN, &CJigBlockApp::OnFileOpen)
END_MESSAGE_MAP()


// CJigBlockApp ����

CJigBlockApp::CJigBlockApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���:
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("TribonModel.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CJigBlockApp ����

CJigBlockApp theApp; //������������


// CJigBlockApp ��ʼ��

BOOL CJigBlockApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	first_X = -1; first_Y = -1; first_Z = -1;
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CJigBlockDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CJigBlockView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand ֮����
	return TRUE;
}

int CJigBlockApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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

// �������жԻ����Ӧ�ó�������
void CJigBlockApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CJigBlockApp ��Ϣ�������

//void CAboutDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	MessageBox(_T("ON KEY DOWN"));
//
//	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
//}


CDocument* CJigBlockApp::OpenDocumentFile(LPCTSTR lpszFileName)
{
	// TODO: �ڴ����ר�ô����/����û���
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
	//Application->MessageBox("������Ϣ��","������Ϣ��",MB_ICONWARNING)
	//MessageBox("����һ��ȷ�� ȡ������Ϣ��","����", MB_OKCANCEL );
	CToolBox tl_Box;
	//testDlg->setPosGo();
	bool tempRes = tl_Box.ReadDxf(lpszFileName, FileContext);//��ȡ�ļ����� FileContext 
	//m_prodlg.m_Pro.SetPos(10);
	if(tempRes == false)
	{
		theApp.DoMessageBox(_T("���ļ�ʧ�ܣ�"),0,1);
	}
	//m_prodlg.m_Pro.SetPos(30);
	m_DxfData = tl_Box.ProgressDxf(FileContext);// ��������
	m_ModelList = m_DxfData.GetModelList();
	// �����ĵ���ʾ�б�
	// ��ʱ��ʾ�б�
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
			CCruveModel tempCruveModel(tempModel);// ��������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//m_Progress.SetPos(100);
}