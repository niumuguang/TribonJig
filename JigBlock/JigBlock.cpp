
// JigBlock.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "JigBlock.h"
#include "MainFrm.h"

#include "JigBlockDoc.h"
#include "JigBlockView.h"

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
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms �������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("JigBlock.AppID.NoVersion"));

	// TODO: �ڴ˴����ӹ�����룬
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
	//TODO: �������������ӵĸ�����Դ
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// CJigBlockApp ��Ϣ��������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

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
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CJigBlockApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CJigBlockApp ��Ϣ��������

//void CAboutDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
//	MessageBox(_T("ON KEY DOWN"));
//
//	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
//}


CDocument* CJigBlockApp::OpenDocumentFile(LPCTSTR lpszFileName)
{
	// TODO: �ڴ�����ר�ô����/����û���
	//MessageBox( _T("OPEN OK"));
	vector<CString> FileContext;
	//HWND s;
	////MessageBox(s, _T("aa"), _T("bb"), 0);
	//this->DoMessageBox(_T("abc"), 0, 1);
	//Application->MessageBox("������Ϣ��","������Ϣ��",MB_ICONWARNING)
	//MessageBox("����һ��ȷ�� ȡ������Ϣ��","����", MB_OKCANCEL );
	CToolBox tl_Box;
	bool tempRes = tl_Box.ReadDxf(lpszFileName, FileContext);
	if(tempRes == false)
	{
		theApp.DoMessageBox(_T("���ļ�ʧ�ܣ�"),0,1);
	}
	m_DxfData = tl_Box.ProgressDxf(FileContext, PlateData, CruveData, PolyData);
	m_ModelList = m_DxfData.GetModelList();
	//tl_Box.ergodic(FileContext, PlateData, CruveData, PolyData);

	return CWinApp::OpenDocumentFile(lpszFileName);
}

vector<COORDINATE> CJigBlockApp::getPlateData( void )
{
	return PlateData;
}

vector<COORDINATE> CJigBlockApp::getCruveData( void )
{
	return CruveData;
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
