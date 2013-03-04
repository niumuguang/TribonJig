
// JigBlockView.h : CJigBlockView 类的接口
//
// 
//

#pragma once
#include <vector>
#include "math3d.h"
using namespace std;

//    用户定义常量
#define PI 3.1415926535897932384626433832795f


class CJigBlockView : public CView
{
protected: // 仅从序列化创建
	CJigBlockView();
	DECLARE_DYNCREATE(CJigBlockView)

// 特性
public:
	CJigBlockDoc* GetDocument() const;
// 测试数据


// 重写
public:
	virtual void OnDraw(CDC* pDC);  //窗口大小回调函数
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CJigBlockView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
//private:
//	float eye[3];
//	float at[3];

public:
	CClientDC* m_pDC;
	// 初始化
	void InitOpengl(void);
	// 初始化细类
	void SetupRC(void);
	// 绘制场景
	void DrawScene(void);
	// 绘制板架
	void DrawPlate();
	// 绘制坐标轴
	void DrawCoor();
	// 绘制地面
	void DrawGround();
	// 平面鼠标坐标映射
	int hemishere(int x, int y, int d, float v[3]);
	//////////////////////////////////////////////////////////////////////////
	// 绘制立方体（测试）
	void DrawCube();
	// 绘制平面（测试）
	void drawPanel(int *index);
	
	//////////////////////////////////////////////////////////////////////////
	BOOL SetupPixelFormat(void);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

private:
	GLfloat nRange; // 图形显示比例
	int w,h; // 窗口的长宽值
	CPoint StartPt, EndPt; // 记录鼠标中键按下和释放的点
	GLfloat xRotSum, yRotSum; // 记录总共旋转的角度
	float keyRoate; // 单位旋转的角度
	int mouseScale;

public:
	// 按下鼠标中键
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	// 鼠标滚轮向下
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	// 鼠标滚轮向上
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	// 按下鼠标左键
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	// 释放鼠标左键
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	// 叉乘内联函数
	inline void JigCrossProduct(M3DVector3f result, M3DVector3d u, M3DVector3d v)
	{
		result[0] = u[1]*v[2] - v[1]*u[2];
		result[1] = -u[0]*v[2] + v[0]*u[2];
		result[2] = u[0]*v[1] - v[0]*u[1];
	}
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // JigBlockView.cpp 中的调试版本
inline CJigBlockDoc* CJigBlockView::GetDocument() const
   { return reinterpret_cast<CJigBlockDoc*>(m_pDocument); }
#endif

