
// MFCApplication4View.cpp: CMFCApplication4View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCApplication4.h"
#endif

#include "MFCApplication4Doc.h"
#include "MFCApplication4View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication4View

IMPLEMENT_DYNCREATE(CMFCApplication4View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication4View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCApplication4View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_32771, &CMFCApplication4View::OnLine)
	ON_COMMAND(ID_32772, &CMFCApplication4View::OnTriangle)
END_MESSAGE_MAP()

// CMFCApplication4View 构造/析构

CMFCApplication4View::CMFCApplication4View() noexcept
{
	// TODO: 在此处添加构造代码

}

CMFCApplication4View::~CMFCApplication4View()
{
}

BOOL CMFCApplication4View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCApplication4View 绘图

void CMFCApplication4View::OnDraw(CDC* /*pDC*/)
{
	CMFCApplication4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMFCApplication4View 打印


void CMFCApplication4View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCApplication4View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCApplication4View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCApplication4View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMFCApplication4View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCApplication4View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCApplication4View 诊断

#ifdef _DEBUG
void CMFCApplication4View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication4View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication4Doc* CMFCApplication4View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication4Doc)));
	return (CMFCApplication4Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication4View 消息处理程序


void CMFCApplication4View::OnLine() {
	CDC* pDC = GetDC();
	//画裁剪区域
	displayRec(XL, YT, XR, YB, RGB(0, 0, 0));
	//XL += 50, XR -= 150, YB -= 150, YT += 50;
	//裁剪直线
	int BLUE = RGB(0, 0, 255);
	int YELLO = RGB(0, 255, 0);
	int RED = RGB(255, 0, 0);

	//裁剪直线
	displayLine(200, 100, 300, 145, BLUE);
	lineCLip(200, 100, 300, 145, RED);	// 全部区域外

	lineCLip(150, 233, 300, 120, RGB(255, 0, 255));// 区域内

	displayLine(50, 180, 400, 180, BLUE);
	lineCLip(50, 180, 400, 180, RED);	// 部分区域内
	InputDlg inputDlg;
	int nResponse = inputDlg.DoModal();
	if (nResponse == IDOK) {
		//这里获取输入并在客户区输出
		CP2 s, e;
		s.x = _wtoi(inputDlg.SX.GetBuffer(0));
		s.y = _wtoi(inputDlg.SY.GetBuffer(0));
		e.x = _wtoi(inputDlg.EX.GetBuffer(0));
		e.y = _wtoi(inputDlg.EY.GetBuffer(0));
		displayLine(s.x, s.y, e.x, e.y, BLUE);
		lineCLip(s.x, s.y, e.x, e.y, RED);
	}
}


void CMFCApplication4View::OnTriangle() {
	CDC* pDC = GetDC();
	CPoint pt[3] = { CPoint(200,200),CPoint(100,100), CPoint(200,100) };
	pDC->Polygon(pt, 3);
	CP2 pol[3] = { CP2(200,200),CP2(100,100), CP2(200,100) };
	CTransform c1(3, pol);
	c1.rotate(90);		
	c1.translate(300, 0);
	c1.scale(2, 2);
	CPoint pt2[3] = { CPoint(pol[0].x, pol[0].y),CPoint(pol[1].x, pol[1].y), CPoint(pol[2].x, pol[2].y) };
	pDC->Polygon(pt2, 3);
}


int CMFCApplication4View::CODE(CPoint p) {
	int wxl = 100, wxr = 800, wyb = 100, wyt = 400;
	int code = 0;
	if (p.x < wxl)
		code |= 1;
	if (p.x > wxr)
		code |= 2;
	if (p.y < wyb)
		code |= 4;
	if (p.y > wyt)
		code |= 8;
	return code;
}

// 直线裁剪 将区域内的直线上色
void CMFCApplication4View::lineCLip(int x1, int y1, int x2, int y2, int col) {
	int code1, code2, code;
	int x, y;
	code1 = encode(x1, y1);//对端点P1进行编码
	code2 = encode(x2, y2);//对端点P2进行编码
	while (code1 != 0 || code2 != 0)
	{
		//相交不为0,第二种情况，全舍去
		if ((code1 & code2) != 0) return;//整条直线段都在窗口外侧，故简弃
		code = code1;
		if (code == 0) code = code2;//如果P1点在窗口内,则将code2赋给code，然后判断P2点的位置
		if ((LEFT & code) != 0)//线段与左边界相交
		{  //根据三角形相似的知识求出P1P2直线段与左边界的交点
			x = XL;
			y = y1 + (y2 - y1) * (XL - x1) / (x2 - x1);
		}
		else if ((RIGHT & code) != 0)//线段与右边界相交
		{  //根据三角形相似的知识求出P1P2直线段与右边界的交点
			x = XR;
			y = y1 + (y2 - y1) * (XR - x1) / (x2 - x1);
		}
		else if ((BOTTOM & code) != 0)//线段与下边界相交
		{  //根据三角形相似的知识求出P1P2直线段与下边界的交点
			y = YB;
			x = x1 + (x2 - x1) * (YB - y1) / (y2 - y1);
		}
		else if ((TOP & code) != 0)//线段与上边界相交
		{  //根据三角形相似的知识求出P1P2直线段与上边界的交点
			y = YT;
			x = x1 + (x2 - x1) * (YT - y1) / (y2 - y1);
		}
		if (code == code1) {
			x1 = x;
			y1 = y;
			code1 = encode(x, y);
		}
		else {
			x2 = x;
			y2 = y;
			code2 = encode(x, y);
		}
	}
	displayLine(x1, y1, x2, y2, col);
	return;

}


int CMFCApplication4View::encode(int x, int y) {
	int c = 0;
	if (x < XL) c = c | LEFT;
	else if (x > XR) c = c | RIGHT;
	if (y > YB) c = c | BOTTOM;
	else if (y < YT) c = c | TOP;
	return c;

}

// 画裁剪区域
void CMFCApplication4View::displayRec(int x1, int y1, int x2, int y2, int color) {
	displayLine(x1 - 50, y1, x2 + 50, y1, color);
	displayLine(x2, y1 - 50, x2, y2 + 50, color);
	displayLine(x2 + 50, y2, x1 - 50, y2, color);
	displayLine(x1, y2 + 50, x1, y1 - 50, color);
}

// 用中点画线法画直线
void CMFCApplication4View::displayLine(int x1, int y1, int x2, int y2, int color) {
	int x = x1, y = y1;
	int a = y1 - y2, b = x2 - x1;//a,b分别为x和y的增量
	//考虑四种情况，分别计算增量
	int cx = (b >= 0 ? 1 : (b = -b, -1));
	int cy = (a <= 0 ? 1 : (a = -a, -1));

	CDC* pDC = GetDC();
	pDC->SetPixel(x, y, color);

	int d, d1, d2;
	if (-a <= b) {		// 斜率绝对值 <= 1
		d = 2 * a + b;
		d1 = 2 * a;
		d2 = 2 * (a + b);
		while (x != x2)
		{
			if (d < 0)
				y += cy, d += d2;
			else
				d += d1;
			x += cx;
			pDC->SetPixel(x, y, color);
		}
	} else {			// 斜率绝对值 > 1
		d = 2 * b + a;
		d1 = 2 * b;
		d2 = 2 * (a + b);
		while (y != y2)
		{
			if (d < 0)
				d += d1;
			else
				x += cx, d += d2;
			y += cy;
			pDC->SetPixel(x, y, color);
		}
	}
}

