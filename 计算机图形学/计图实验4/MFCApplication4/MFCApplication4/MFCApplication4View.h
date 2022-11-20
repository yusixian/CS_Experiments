
// MFCApplication4View.h: CMFCApplication4View 类的接口
//

#pragma once
#include "CTransform.h"
#include "InputDlg.h"
class CMFCApplication4View : public CView
{
protected: // 仅从序列化创建
	CMFCApplication4View() noexcept;
	DECLARE_DYNCREATE(CMFCApplication4View)

// 特性
public:
	CMFCApplication4Doc* GetDocument() const;

// 操作
public:
	int LEFT = 1;//0001
	int RIGHT = 2;//0010
	int BOTTOM = 4;//0100
	int TOP = 8;//1000
	int XL = 100;	// 左
	int XR = 500;	// 右
	int YB = 500;	// 下
	int YT = 100;	// 上
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFCApplication4View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLine();
	afx_msg void OnTriangle();
	void DDAdrawLine(int x1, int y1, int x2, int y2, int Col);
	int CODE(CPoint p);
	void lineCLip(int x1, int y1, int x2, int y2, int col);
	int encode(int x, int y);
	void displayRec(int x1, int y1, int x2, int y2, int color);
	void displayLine(int x1, int y1, int x2, int y2, int color);
};

#ifndef _DEBUG  // MFCApplication4View.cpp 中的调试版本
inline CMFCApplication4Doc* CMFCApplication4View::GetDocument() const
   { return reinterpret_cast<CMFCApplication4Doc*>(m_pDocument); }
#endif

