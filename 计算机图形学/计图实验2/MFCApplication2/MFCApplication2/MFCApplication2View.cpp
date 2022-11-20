
// MFCApplication2View.cpp: CMFCApplication2View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCApplication2.h"
#endif

#include "MFCApplication2Doc.h"
#include "MFCApplication2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication2View

IMPLEMENT_DYNCREATE(CMFCApplication2View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication2View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCApplication2View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_32771, &CMFCApplication2View::OnDDA)
//	ON_MESSAGE(WM_LBUTTONDOWN, &CMFCApplication2View::OnLButtonDown)
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
//ON_WM_MOUSEMOVE()
ON_COMMAND(ID_32773, &CMFCApplication2View::OnLineMid)
ON_COMMAND(ID_32774, &CMFCApplication2View::OnBresenham)
END_MESSAGE_MAP()

// CMFCApplication2View 构造/析构
CMFCApplication2View::CMFCApplication2View() noexcept {
	// TODO: 在此处添加构造代码
	m_Draw = false;
}

CMFCApplication2View::~CMFCApplication2View()
{
}

BOOL CMFCApplication2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCApplication2View 绘图

void CMFCApplication2View::OnDraw(CDC* /*pDC*/)
{
	CMFCApplication2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMFCApplication2View 打印


void CMFCApplication2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCApplication2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCApplication2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCApplication2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMFCApplication2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCApplication2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCApplication2View 诊断

#ifdef _DEBUG
void CMFCApplication2View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication2Doc* CMFCApplication2View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication2Doc)));
	return (CMFCApplication2Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication2View 消息处理程序
void CMFCApplication2View::OnDDA() {
	int x1, y1, x2, y2;
	x1 = y1 = 100;
	x2 = 300, y2 = 200;
	double delta_x, delta_y, x, y;
	int dx, dy, steps;
	dx = x2 - x1;
	dy = y2 - y1;
	if (abs(dx) > abs(dy)) steps = abs(dx);
	else steps = abs(dy);
	delta_x = dx * 1.0 / steps;
	delta_y = dy * 1.0 / steps;
	x = x1, y = y1;
	CDC* pDC = GetDC();
	pDC->SetPixel(x, y, RGB(255, 0, 0));
	for (int i = 1; i <= steps; i++) {
		x += delta_x;
		y += delta_y;
		pDC->SetPixel(x, y, RGB(255, 0, 0));
	}
}


void CMFCApplication2View::OnLButtonDown(UINT nFlags, CPoint point) {
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	m_Draw = true;							//将鼠标按下标志置为true
	vstart = point;								//将鼠标按下的位置用p1记录
	CView::OnLButtonDown(nFlags, point);	//函数自调用，循环检测。nFlags 表示控制键状态
}


void CMFCApplication2View::OnLButtonUp(UINT nFlags, CPoint point) {
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_Draw = false;//标记鼠标左键弹起
    vend = point;
	OnLineMid();
	CView::OnLButtonUp(nFlags, point);
}


//void CMFCApplication2View::OnMouseMove(UINT nFlags, CPoint point) {
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//    
//	CDC* pDC = GetDC();
//	vend = point;
//	if (m_Draw == true)		
//		OnLineMid();		//调用OnLineMid函数绘制直线
//	CView::OnMouseMove(nFlags, point);
//}


void CMFCApplication2View::OnLineMid() {
	// TODO: 在此添加命令处理程序代码
	// 中点画线法绘制直线
    CDC* pDC = GetDC();
    CPoint p, t; 
    COLORREF clr = RGB(0, 0, 0);
    if (fabs(vstart.x - vend.x) < 1e-6) {
        if (vstart.y > vend.y) {
            t = vstart;
            vstart = vend;
            vend = t;
        }
        for (p = vstart; p.y < vend.y; p.y++) {
            pDC->SetPixelV(Round(p.x), Round(p.y), clr);
        }

    } else {
        double k, d;
        k = (vend.y - vstart.y) / (vend.x - vstart.x);

        if (k > 1.0)
        {
            if (vstart.y > vend.y)
            {
                t = vstart;
                vstart = vend;
                vend = t;
            }
            d = 1 - 0.5 * k;
            for (p = vstart; p.y < vend.y; p.y++)
            {
                pDC->SetPixelV(Round(p.x), Round(p.y), clr);
                if (d >= 0)
                {
                    p.x++;
                    d += 1 - k;
                }
                else
                    d += 1;
            }
        }
        if (0.0 <= k && k <= 1.0)
        {
            if (vstart.x > vend.x) {
                t = vstart;
                vstart = vend;
                vend = t;
            }
            d = 0.5 - k;
            for (p = vstart; p.x < vend.x; p.x++)
            {
                pDC->SetPixelV(Round(p.x), Round(p.y), clr);

                if (d < 0)
                {
                    p.y++;
                    d += 1 - k;
                }
                else
                    d -= k;
            }
        }

        if (k >= -1.0 && k < 0.0)
        {
            if (vstart.x > vend.x)
            {
                t = vstart;
                vstart = vend;
                vend = t;
            }
            d = -0.5 - k;

            for (p = vstart; p.x < vend.x; p.x++)
            {
                pDC->SetPixelV(Round(p.x), Round(p.y), clr);
                if (d > 0)
                {
                    p.y--;
                    d -= 1 + k;
                }
                else
                    d -= k;

            }
        }

        if (k < -1.0)
        {
            if (vstart.y < vend.y)
            {
                t = vstart;
                vstart = vend;
                vend = t;
            }
            d = -1 - 0.5 * k;
            for (p = vstart; p.y < vend.y; p.y--)
            {
                pDC->SetPixelV(Round(p.x), Round(p.y), clr);
                if (d < 0)
                {
                    p.x++;
                    d -= 1 + k;
                }
                else
                    d -= 1;
            }
        }
    }
    vstart = vend;
}

void CMFCApplication2View::OnBresenham() {
    // TODO: 在此添加命令处理程序代码
    CDC* pDC = GetDC();
    int r = 200; 
    int x0 = 200, y0 = 200, x, y;
    int c = RGB(0, 0, 0);
    float d;
    d = 3 - 2 * r;
    x = 0;
    y = r;
    while (x <= y) {
        if (d < 0) {
            d = d + 4 * x + 6;
            x = x + 1;
        }
        else if (d >= 0) {
            d = d + 4 * (x - y) + 10;
            x = x + 1;
            y = y - 1;
        }
        pDC->SetPixel(x + x0, y + y0, c);
        pDC->SetPixel(-x + x0, y + y0, c);
        pDC->SetPixel(x + x0, -y + y0, c);
        pDC->SetPixel(-x + x0, -y + y0, c);
        pDC->SetPixel(y + x0, x + y0, c);
        pDC->SetPixel(-y + x0, x + y0, c);
        pDC->SetPixel(y + x0, -x + y0, c);
        pDC->SetPixel(-y + x0, -x + y0, c);
    }
}
