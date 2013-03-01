
// JigBlockView.cpp : CJigBlockView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "JigBlock.h"
#endif

#include "JigBlockDoc.h"
#include "JigBlockView.h"
//#include "gl\glew.h"
#include "gl\glut.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CJigBlockView
IMPLEMENT_DYNCREATE(CJigBlockView, CView)

BEGIN_MESSAGE_MAP(CJigBlockView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_MBUTTONDOWN()
ON_WM_MBUTTONUP()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// �û����峣��
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
float lastMatrix[16] ={
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0};
// �����嶥����ɫ����
float color[][3] = {
	{0.0, 0.0, 1.0},{ 1.0, 1.0, 1.0},{0.0,1.0,0.0},{1.0, 0.0, 0.0},
	{0.0, 0.0, 1.0},{ 1.0, 1.0, 1.0},{0.0,1.0,0.0},{1.0, 0.0, 0.0}
};
// �����嶥������
float vertex[][3] =	{
	{-100.0, -100.0, -100.0},{100.0, -100.0, -100.0},{100.0, -100.0, 100.0},{-100.0, -100.0, 100.0},
	{-100.0, 100.0, -100.0}, {100.0, 100.0, -100.0}, {100.0, 100.0, 100.0}, {-100.0, 100.0, 100.0}
};
int vertexOfPanel[][4] ={
	{0, 1, 2, 3}, {0, 1, 5, 4}, {4, 5, 6, 7},
	{7, 6, 2, 3}, {0, 4, 7, 3}, {1, 2, 6, 5}
};

float eye[3] = {0.0, 0.0, 4000.0};		// �۲�������
float at[3] = {0.0, 0.0, 0.0};		// �۲������
float up[3] = {0.0, 1000.0, 0.0};		// �۲��ߵ���������

// CJigBlockView ����/����
CJigBlockView::CJigBlockView()
{
	// TODO: �ڴ˴���ӹ������
	m_pDC = NULL;
	nRange = 59300.0f;
	
	//nRange = 5930.f;
	xRotSum = 0;
	yRotSum = 0;
	keyRoate = 1.0f;// ���̵�λ�ƶ���
	eye[0]=0.0;eye[1] = 0.0;eye[2]=4.0;
	at[0]=0.0;at[1]=0.0;at[2]=0.0;
	mouseScale = 1000;
}

CJigBlockView::~CJigBlockView()
{
}

BOOL CJigBlockView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.style |= WS_CLIPSIBLINGS|WS_CLIPCHILDREN;
	return CView::PreCreateWindow(cs);
}

// CJigBlockView ����
void CJigBlockView::OnDraw(CDC* /*pDC*/)
{
	CJigBlockDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	DrawScene();
}

// CJigBlockView ���
#ifdef _DEBUG
void CJigBlockView::AssertValid() const
{
	CView::AssertValid();
}

void CJigBlockView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CJigBlockDoc* CJigBlockView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CJigBlockDoc)));
	
	return (CJigBlockDoc*)m_pDocument;
}
#endif //_DEBUG

// Respond to arrow keys

// CJigBlockView ��Ϣ�������

void CJigBlockView::InitOpengl(void)
{
	PIXELFORMATDESCRIPTOR pfd;
	int n;
	HGLRC hrc;
	m_pDC = new CClientDC(this);
	ASSERT(m_pDC != NULL);
	if (!SetupPixelFormat())
	{
		return;
	}
	n = ::GetPixelFormat(m_pDC->GetSafeHdc());
	::DescribePixelFormat(m_pDC->GetSafeHdc(), n, sizeof(pfd), &pfd);
	hrc = wglCreateContext(m_pDC->GetSafeHdc());
	wglMakeCurrent(m_pDC->GetSafeHdc(), hrc);
	//
	glEnable(GL_DEPTH_TEST);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	SetupRC();
}


BOOL CJigBlockView::SetupPixelFormat(void)
{
	static PIXELFORMATDESCRIPTOR pfd = 
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW|
		PFD_SUPPORT_OPENGL|
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24,
		0,0,0,0,0,0,
		0,
		0,
		0,
		0,0,0,0,
		32,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0,0,0
	};
	int pixelformat;
	if ((pixelformat = ChoosePixelFormat(m_pDC->GetSafeHdc(),&pfd)) == 0 )
	{
		MessageBox(_T("ChoosePixelFormat Failed"));
		return FALSE;
	}
	if (SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
	{
		MessageBox(_T("SetPixelFormat failed"));
		return FALSE;
	}
	return TRUE;
}

void CJigBlockView::DrawScene(void)
{
	//  ����ͼ��
	float fZ,bZ;
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClear(GL_COLOR_BUFFER_BIT);
	fZ = 100.0f;
	bZ = -100.0f;
	//glEnable(GL_SCISSOR_TEST);
	//// test line
	glPushMatrix();
	glRotatef(xRotSum,1,0,0);
	glRotatef(yRotSum,0,1,0);
	//GLfloat y;
	//GLfloat fSize[2];
	//GLfloat fCurrSize;
	//glGetFloatv(GL_LINE_WIDTH_RANGE, fSize);
	//fCurrSize = fSize[0];
	//fCurrSize = fCurrSize + 1000;
	//glColor3f(0,0,0);
	//glLineWidth(fCurrSize);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, -100, 0);
	glVertex3f(0, 100, 0);
	glVertex3f(100,100,0);
	glEnd();

	//glEnable(GL_DEPTH_TEST);
	//glFrontFace(GL_CCW);
	//glEnable(GL_CULL_FACE);
	//for (int num=0;num<1000000;num++)
	//{
	//	
	//	glTranslatef(1000,0,0);
	//	DrawCube();
	//}
	
	glPopMatrix();

	// Set material color, Red
	DrawCoor();
	//glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	//glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	//
	//glColor3f(0,1,0);
	DrawPlate();
	//
	//// Restore the matrix state
	//glPopMatrix();

	SwapBuffers(wglGetCurrentDC());
}


int CJigBlockView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	InitOpengl();
	return 0;
}


void CJigBlockView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	HGLRC hrc;
	hrc = ::wglGetCurrentContext();
	::wglMakeCurrent(NULL, NULL);
	if (hrc)
	{
		::wglDeleteContext(hrc);
	}
	if (m_pDC)
	{
		delete m_pDC;
	}
}


void CJigBlockView::OnSize(UINT nType, int cx, int cy)
{
	//CView::OnSize(nType, cx, cy);
	// TODO: �ڴ˴������Ϣ����������
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(60.0,(float)w/(float)h,0.1,20.0);

	w=cx;
	h=cy;
	if (h == 0)
	{
		h = 1;
	}
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w<h)
	{
		glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange*2.0f, nRange*2.0f);
	}
	else
	{
		glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange*2.0f, nRange*2.0f);
	}
	glMatrixMode(GL_MODELVIEW);
	//gluLookAt(eye[0],eye[1],eye[2],at[0],at[1],at[2],up[0],up[1],up[2]);

	glLoadIdentity();
}


BOOL CJigBlockView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return TRUE;
}

void CJigBlockView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//MessageBox(_T("ON KEY DOWN"));
	switch(nChar)
	{
	case 'w':case 'W':
		{
			xRot = xRot + keyRoate;
			break;
		}
	case 's':case 'S':
		{
			xRot = xRot -keyRoate;
			break;
		}
	case 'a':case 'A':
		{
			yRot = yRot+keyRoate;
			break;
		}
	case 'd':case 'D':
		{
			yRot = yRot -keyRoate;
			break;
		}
	}
	xRot = (GLfloat)((const int)xRot % 360);
	yRot = (GLfloat)((const int)yRot % 360);
	xRotSum = xRotSum + xRot;
	yRotSum = yRotSum + yRot;
	m_pDocument->UpdateAllViews(NULL);
}

void CJigBlockView::SetupRC( void )
{
	GLfloat  whiteLight[] = { 0.45f, 0.45f, 0.45f, 1.0f };
	GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
	GLfloat	 lightPos[] = { -100.f, 100.0f, 100.0f, 0.0f };
	GLfloat gray[] = {0.75f, 0.75f, 0.75f, 1.0f};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);

	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	glEnable(GL_CULL_FACE);		// Do not calculate inside of jet
	// Enable lighting
	glEnable(GL_LIGHTING);
	// Setup and enable light 0
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	glEnable(GL_LIGHT0);

	// Enable color tracking
	glEnable(GL_COLOR_MATERIAL);
	// Set Material properties to follow glColor values
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	// Black blue background
	glClearColor(0.4f, 0.4f, 0.4f, 0.0f );
}

BOOL CJigBlockView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//MessageBox(_T("ON Mouse Whell"));
	if (zDelta > 0)
	{
		nRange = nRange + mouseScale;
	}
	else
	{
		nRange = nRange - mouseScale;
	}
	if (h == 0)
	{
		h = 1;
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w<h)
	{
		glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange*2.0f, nRange*2.0f);
	}
	else
	{
		glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange*2.0f, nRange*2.0f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	m_pDocument->UpdateAllViews(NULL);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CJigBlockView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	StartPt = point;
	CView::OnMButtonDown(nFlags, point);
}

void CJigBlockView::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	EndPt = point;
	int del_X = EndPt.x - StartPt.x;
	int del_Y = EndPt.y - StartPt.y;
	glTranslatef(-del_X, 0, 0);
	glTranslatef(0, -del_Y, 0);
	m_pDocument->UpdateAllViews(NULL);
	CView::OnMButtonUp(nFlags, point);
}

void CJigBlockView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CView::OnLButtonDown(nFlags, point);
}

void CJigBlockView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CView::OnLButtonUp(nFlags, point);
}


double getDist(COORDINATE pt1, COORDINATE pt2)
{
	double Dis_X = (get<0>(pt1)-get<0>(pt2))*(get<0>(pt1)-get<0>(pt2));
	double Dis_Y = (get<1>(pt1)-get<1>(pt2))*(get<1>(pt1)-get<1>(pt2));
	double Dis_Z = (get<2>(pt1)-get<2>(pt2))*(get<2>(pt1)-get<2>(pt2));
	double Dist = sqrt(Dis_X+Dis_Y+Dis_Z);
	return Dist;
}

// Create Model: Planar Plate, Cruve Plate, PolyLine;
void CJigBlockView::DrawPlate()
{
 	//vector<COORDINATE> tempShowList = theApp.getCruveData();
	//M3DVector3f tempCruveList[1000] = {0};
	//vector<M3DVector3f> tempTest;
	//float tempCruveList[1000][3];
	//
	//COORDINATE tempUnit;
	//vector<COORDINATE> tempCruveList;
	vector<GLuint> test = theApp.getShowListVec();
 	for(int i=0; i<test.size(); i++)
	{
		glPushMatrix();
		glRotatef(xRotSum,1,0,0);
		glRotatef(yRotSum,0,1,0);
		glCallList(test.at(i));
		glPopMatrix();
	}
	

	//testing[0][0] = 0.00;
	//int num = 0;
	//if (tempShowList.size() != 0)
	//{ 
	//	for (int i=0; i<1000;i++)
	//	{
	//		//M3DVector3f testM3D;
	//		get<0>(tempUnit) = get<0>(tempShowList[i]);
	//		get<1>(tempUnit) = get<1>(tempShowList[i]);
	//		get<2>(tempUnit) = get<2>(tempShowList[i]);
	//		tempCruveList.push_back(tempUnit);
	//		//tempTest.push_back();
	//		//
	//		//tempCruveList[i][0] = get<0>(tempShowList[i]);
	//		//tempCruveList[i][1] = get<1>(tempShowList[i]);
	//		//tempCruveList[i][2] = get<2>(tempShowList[i]);
	//	}
	//	//
	//	
	//	glPushMatrix();
	//	glRotatef(xRotSum,1,0,0);
	//	glRotatef(yRotSum,0,1,0);
	//	//GLfloat y;
	//	//GLfloat fSize[2];
	//	//GLfloat fCurrSize;
	//	//glGetFloatv(GL_LINE_WIDTH_RANGE, fSize);
	//	//fCurrSize = fSize[0];
	//	//fCurrSize = fCurrSize + 1000;
	//	glColor3f(0,0,0);
	//	//glLineWidth(fCurrSize);
	//	//glBegin(GL_LINE_STRIP);
	//	//for (int i=0;i<1000;i++)
	//	//{
	//	//	glVertex3f(get<0>(tempCruveList.at(i)),get<0>(tempCruveList.at(i)),get<0>(tempCruveList.at(i)));
	//	//	//glArrayElement(i);
	//	//}
	//	//glEnd();
	//	glEnableClientState(GL_VERTEX_ARRAY);
	//	glVertexPointer(1000,GL_FLOAT,0,&tempCruveList);
	//	glDrawArrays(GL_POINT_SPRITE,0,3);
	//	//glDisableClientState(GL_VERTEX_ARRAY);
	//	glPopMatrix();
	//}
	

	// ��Dxf�ļ����ȡģ�����б�
	//vector<CModel> tempModelList = theApp.GetModelList();

	//for (int i=0; i<tempModelList.size(); i++)
	//{
	//	CModel tempModel;
	//	tempModel = tempModelList.at(i);
	//	if (tempModel.GetModelType() == "CRUVEMODEL")
	//	{
	//		CCruveModel tempCruveModel(tempModel);
	//		// �õ����б�
	//		vector<C3DFACE> temp3DFaceList = tempCruveModel.Get3DFaceList();
	//		// ����ÿ����
	//		for (int i=0;i<temp3DFaceList.size();i++)
	//		{
	//			C3DFACE temp3DFace = temp3DFaceList.at(i);

	//			COORDINATE tempCoor0 = temp3DFace.GetCoord0();
	//			COORDINATE tempCoor1 = temp3DFace.GetCoord1();
	//			COORDINATE tempCoor2 = temp3DFace.GetCoord2();
	//			COORDINATE tempCoor3 = temp3DFace.GetCoord3();
	//			COORDINATE AxieCoor = temp3DFaceList.at (0).GetCoord0();
	//			//glTranslatef(-get<0>(AxieCoor),-get<1>(AxieCoor),-get<2>(AxieCoor));
	//			glPushMatrix();
	//			glTranslatef(-get<0>(AxieCoor),-get<1>(AxieCoor),-get<2>(AxieCoor));
	//			//glTranslatef(-10000,-700,-2225);
	//			glBegin(GL_POLYGON);
	//			glVertex3f(get<0>(tempCoor0),get<1>(tempCoor0),get<2>(tempCoor0));
	//			glVertex3f(get<0>(tempCoor1),get<1>(tempCoor1),get<2>(tempCoor1));
	//			glVertex3f(get<0>(tempCoor2),get<1>(tempCoor2),get<2>(tempCoor2));
	//			glEnd();
	//			glPopMatrix();
	//		}
	//		//tempCruveModel.ShowPlate();
	//	}
	//}

	//if (PlateData.size() == 0 && CruveData.size() == 0 && PolyData.size() == 0)
	//{
	//	return;
	//}
	//
	//for (int i=0; i<PlateData.size(); i=i+4)
	//{
	//	COORDINATE tempCoor1, tempCoor2, tempCoor3, tempCoor4;
	//	tempCoor1 = PlateData[i];
	//	tempCoor2 = PlateData[i+1];
	//	tempCoor3 = PlateData[i+2];
	//	tempCoor4 = PlateData[i+3];
	//	if (getDist(tempCoor4, tempCoor2) < 0.00001)
	//	{
	//		get<0>(tempCoor4) = get<0>(tempCoor1);
	//		get<1>(tempCoor4) = get<1>(tempCoor3);
	//		get<2>(tempCoor4) = get<2>(tempCoor1);
	//	}
	//	glPushMatrix();
	//	//glTranslatef(-10000,-700,-2225);
	//	//glEnable(GL_NORMALIZE);
	//	glTranslatef(-get<0>(PlateData[0]),-get<1>(PlateData[0]),-get<2>(PlateData[0]));
	//	glBegin(GL_QUADS);
	//	//glNormal3f(0.0f, 0.0f, 1.0f);
	//	M3DVector3f vPoints[3] = {
	//		(get<0>(tempCoor1), get<1>(tempCoor1), get<2>(tempCoor1)),
	//		(get<0>(tempCoor2), get<1>(tempCoor2), get<2>(tempCoor2)),
	//		(get<0>(tempCoor3), get<1>(tempCoor3), get<2>(tempCoor3))
	//	};
	//	M3DVector3f vNormal;
	//	M3DVector3d v1,v2;
	//	v1[0] = get<0>(tempCoor2) - get<0>(tempCoor1);
	//	v1[1] = get<1>(tempCoor2) - get<1>(tempCoor1);
	//	v1[2] = get<2>(tempCoor2) - get<2>(tempCoor1);

	//	v2[0] = get<0>(tempCoor2) - get<0>(tempCoor3);
	//	v2[1] = get<1>(tempCoor2) - get<1>(tempCoor3);
	//	v2[2] = get<2>(tempCoor2) - get<2>(tempCoor3);

	//	JigCrossProduct(vNormal, v1, v2);
	//	//m3dFindNormal();
	//	//m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
	//	glNormal3fv(vNormal);
	//	glVertex3f(get<0>(tempCoor1), get<1>(tempCoor1), get<2>(tempCoor1));
	//	glVertex3f(get<0>(tempCoor2), get<1>(tempCoor2), get<2>(tempCoor2));
	//	glVertex3f(get<0>(tempCoor3), get<1>(tempCoor3), get<2>(tempCoor3));
	//	glVertex3f(get<0>(tempCoor4), get<1>(tempCoor4), get<2>(tempCoor4));

	//	glEnd();
	//	glPopMatrix();
	//}
	////TimeFirst = 1;
}

void CJigBlockView::DrawCoor()
{
	glDisable(GL_CULL_FACE);
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidSphere(0.02*abs(nRange),20,10);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-45, 1.0f, 0.0f, 0.0f);
	glRotatef(-45, 0.0f, 1.0f, 0.0f);

	GLUquadric *pObj; 
	pObj = gluNewQuadric();
	glColor3f(1.0f, 0.0f, 0.0f);

	gluCylinder(pObj, 0.01*abs(nRange), 0.01*abs(nRange), 0.2*abs(nRange), 0.2*abs(nRange), 10);
	glRotatef(-90, 1,0,0);
	glColor3f(0.0f, 1.0f, 0.0f);
	gluCylinder(pObj, 0.01*abs(nRange), 0.01*abs(nRange), 0.2*abs(nRange), 0.2*abs(nRange), 10);
	glRotatef(90, 0,1,0);
	glColor3f(0.0f, 0.0f, 1.0f);
	gluCylinder(pObj, 0.01*abs(nRange), 0.01*abs(nRange), 0.2*abs(nRange), 0.2*abs(nRange), 10);
	gluDeleteQuadric(pObj);
	glPopMatrix();
	//
	glPushMatrix();
	glRotatef(-45, 1.0f, 0.0f, 0.0f);
	glRotatef(-45, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.2*abs(nRange),0,0);
	glRotatef(90, 0,1,0);
	glutSolidCone(0.02*abs(nRange), 0.05*abs(nRange), 10, 30);
	glPopMatrix();
	//
	glPushMatrix();
	glRotatef(-45, 1.0f, 0.0f, 0.0f);
	glRotatef(-45, 0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glTranslatef(0,0.2*abs(nRange),0);
	glRotatef(-90, 1,0,0);
	glutSolidCone(0.02*abs(nRange), 0.05*abs(nRange), 10, 30);
	glPopMatrix();
	//
	glPushMatrix();
	glRotatef(-45, 1.0f, 0.0f, 0.0f);
	glRotatef(-45, 0.0f, 1.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(0,0,0.2*abs(nRange));
	glRotatef(90, 0,0,1);
	glutSolidCone(0.02*abs(nRange), 0.05*abs(nRange), 10, 30);
	glPopMatrix();

	glColor3f(1.0f, 1.0f, 0.0f);
	glPushMatrix();
}
// ���Ժ���
void CJigBlockView::DrawCube()
{
	// ��������
	// ������������ֱ���Ҫ�õ��Ķ�������
	int i;
	for(i =0;i<6;i++)
	{
		drawPanel(vertexOfPanel[i]);
	}
}
// ���Ժ���
void CJigBlockView::drawPanel(int *index)
{
	/*
	��������
	*/
	//////////////////////////////////////////////////////////////////////////
	int i;
	glBegin(GL_POLYGON);
	for (i = 0; i < 4; i++)
	{
		glColor3fv(color[index[i]]);
		glVertex3fv(vertex[index[i]]);
	}
	glEnd();
	glBegin(GL_LINE_LOOP);
	for (i = 0; i < 4; i++)
	{
		glColor3f(0.0, 0.0, 0.0);
		glVertex3fv(vertex[index[i]]);
	}
	glEnd();
}


