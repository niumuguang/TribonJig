
// JigBlockView.h : CJigBlockView ��Ľӿ�
//
// 
//

#pragma once
#include <vector>
#include "math3d.h"
using namespace std;

//    �û����峣��
#define PI 3.1415926535897932384626433832795f


class CJigBlockView : public CView
{
protected: // �������л�����
	CJigBlockView();
	DECLARE_DYNCREATE(CJigBlockView)

// ����
public:
	CJigBlockDoc* GetDocument() const;
// ��������


// ��д
public:
	virtual void OnDraw(CDC* pDC);  //���ڴ�С�ص�����
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CJigBlockView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
//private:
//	float eye[3];
//	float at[3];

public:
	CClientDC* m_pDC;
	// ��ʼ��
	void InitOpengl(void);
	// ��ʼ��ϸ��
	void SetupRC(void);
	// ���Ƴ���
	void DrawScene(void);
	// ���ư��
	void DrawPlate();
	// ����������
	void DrawCoor();
	// ���Ƶ���
	void DrawGround();
	// ƽ���������ӳ��
	int hemishere(int x, int y, int d, float v[3]);
	//////////////////////////////////////////////////////////////////////////
	// ���������壨���ԣ�
	void DrawCube();
	// ����ƽ�棨���ԣ�
	void drawPanel(int *index);
	
	//////////////////////////////////////////////////////////////////////////
	BOOL SetupPixelFormat(void);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

private:
	GLfloat nRange; // ͼ����ʾ����
	int w,h; // ���ڵĳ���ֵ
	CPoint StartPt, EndPt; // ��¼����м����º��ͷŵĵ�
	GLfloat xRotSum, yRotSum; // ��¼�ܹ���ת�ĽǶ�
	float keyRoate; // ��λ��ת�ĽǶ�
	int mouseScale;

public:
	// ��������м�
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	// ����������
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	// ����������
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	// ����������
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	// �ͷ�������
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	// �����������
	inline void JigCrossProduct(M3DVector3f result, M3DVector3d u, M3DVector3d v)
	{
		result[0] = u[1]*v[2] - v[1]*u[2];
		result[1] = -u[0]*v[2] + v[0]*u[2];
		result[2] = u[0]*v[1] - v[0]*u[1];
	}
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // JigBlockView.cpp �еĵ��԰汾
inline CJigBlockDoc* CJigBlockView::GetDocument() const
   { return reinterpret_cast<CJigBlockDoc*>(m_pDocument); }
#endif

