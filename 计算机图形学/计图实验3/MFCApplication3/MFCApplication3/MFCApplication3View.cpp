
// MFCApplication3View.cpp: CMFCApplication3View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCApplication3.h"
#endif

#include "BoundaryFillDlg.h"
#include "MFCApplication3Doc.h"
#include "MFCApplication3View.h"
#include "PolyStruct.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication3View

IMPLEMENT_DYNCREATE(CMFCApplication3View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication3View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCApplication3View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_32771, &CMFCApplication3View::OnPolyScan)
    ON_COMMAND(ID_32772, &CMFCApplication3View::OnBoundaryFill)
END_MESSAGE_MAP()

// CMFCApplication3View 构造/析构

CMFCApplication3View::CMFCApplication3View() noexcept
{
	// TODO: 在此处添加构造代码

}

CMFCApplication3View::~CMFCApplication3View()
{
}

BOOL CMFCApplication3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCApplication3View 绘图

void CMFCApplication3View::OnDraw(CDC* /*pDC*/)
{
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMFCApplication3View 打印


void CMFCApplication3View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCApplication3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCApplication3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCApplication3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMFCApplication3View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCApplication3View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCApplication3View 诊断

#ifdef _DEBUG
void CMFCApplication3View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication3Doc* CMFCApplication3View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication3Doc)));
	return (CMFCApplication3Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication3View 消息处理程序


void CMFCApplication3View::OnPolyScan() {
    CDC* pDC = GetDC(); 
    point polypoint[POINTNUM] = { 370,10,560,100,560,200,430,130,340,170,340,80 };//多边形顶点  
	int MaxY = 0;
	int MinY = 2000;
	int i;
	for (i = 0; i < POINTNUM; i++) {
		if (polypoint[i].y > MaxY) 
			MaxY = polypoint[i].y;
		if (polypoint[i].y < MinY) 
			MinY = polypoint[i].y;
	}

    /*******初始化AET表，即初始化活跃边表**********/
    AET* pAET = new AET;
    pAET->next = NULL;

    /******初始化NET表，即初始化边表***************/
    NET* pNET[1024];
    for (i = MinY; i <= MaxY; ++i) {
        pNET[i] = new NET;
        pNET[i]->next = NULL;
    }

    /******扫描并建立NET表，即建立边表***************/
    for (i = MinY; i <= MaxY; ++i) {
        for (int j = 0; j < POINTNUM; ++j) {
            if (polypoint[j].y == i) {
                if (polypoint[(j - 1 + POINTNUM) % POINTNUM].y > polypoint[j].y) {
                    NET* p = new NET;
                    p->x = polypoint[j].x;
                    p->ymax = polypoint[(j - 1 + POINTNUM) % POINTNUM].y;
                    p->dx = (polypoint[(j - 1 + POINTNUM) % POINTNUM].x - polypoint[j].x) / (polypoint[(j - 1 + POINTNUM) % POINTNUM].y - polypoint[j].y);
                    p->next = pNET[i]->next;
                    pNET[i]->next = p;
                }

                if (polypoint[(j + 1 + POINTNUM) % POINTNUM].y > polypoint[j].y) {
                    NET* p = new NET;
                    p->x = polypoint[j].x;
                    p->ymax = polypoint[(j + 1 + POINTNUM) % POINTNUM].y;
                    p->dx = (polypoint[(j + 1 + POINTNUM) % POINTNUM].x - polypoint[j].x) / (polypoint[(j + 1 + POINTNUM) % POINTNUM].y - polypoint[j].y);
                    p->next = pNET[i]->next;
                    pNET[i]->next = p;
                }
            }
        }
    }

    /******建立并更新活性边表AET***********************/
    for (i = MinY; i <= MaxY; ++i) {
        //计算新的交点x,更新AET***************************/  
        NET* p = pAET->next;
        while (p != NULL) {
            p->x = p->x + p->dx;
            p = p->next;
        }

        //更新后新AET先排序***************************/  
        //断表排序,不再开辟空间  
        AET* tq = pAET;
        p = pAET->next;
        tq->next = NULL;

        while (p != NULL) {
            while (tq->next != NULL && p->x >= tq->next->x)
                tq = tq->next;
            NET* s = p->next;
            p->next = tq->next;
            tq->next = p;
            p = s;
            tq = pAET;
        }

        //(改进算法)先从AET表中删除ymax==i的结点**************/  
        AET* q = pAET;
        p = q->next;
        while (p != NULL) {
            if (p->ymax == i) {
                q->next = p->next;
                delete p;
                p = q->next;
            } else {
                q = q->next;
                p = q->next;
            }
        }

        //将NET中的新点加入AET,并用插入法按X值递增排序************/  
        p = pNET[i]->next;
        q = pAET;
        while (p != NULL) {
            while (q->next != NULL && p->x >= q->next->x)
                q = q->next; 
            NET* s = p->next;
            p->next = q->next;
            q->next = p;
            p = s;
            q = pAET;
        }

        /******配对填充颜色************************/
        p = pAET->next;
        while (p != NULL && p->next != NULL)
        {
            for (float j = p->x; j <= p->next->x; j++)
            {
                pDC->SetPixel(static_cast<int>(j), i, RGB(255, 0, 0));
            }  // pDC.MoveTo( static_cast<int>(p->x), i ); 用画直线来替换上面的设置像素点颜色，速度更快  
                              //  pDC.LineTo( static_cast<int>(p->next->x), i );  

            p = p->next->next;//考虑端点情况  
        }
    }

    NET* phead = NULL;
    NET* pnext = NULL;
    //释放边表  
    /*
    for( i = MinY;i <= MaxY;i++ )
    {
        phead = pNET[i];

        while( phead != NULL )
        {
            pnext = phead->next;
            delete phead;
            phead = pnext;
        }

        pNET[i] = NULL;
    }
    */
    //释放活跃边表  
    phead = pAET;
    while (phead != NULL)
    {
        pnext = phead->next;
        delete phead;
        phead = pnext;
    }
}


void CMFCApplication3View::OnBoundaryFill() {
    CDC* pDC = GetDC();
    BoundaryFillDlg inputDlg;
    int nResponse = inputDlg.DoModal();
    if (nResponse == IDOK) {
        //这里获取输入并在客户区输出
        point LU, RD, S; 
        LU.x = _wtoi(inputDlg.LUX.GetBuffer(0));
        LU.y = _wtoi(inputDlg.LUY.GetBuffer(0));
        RD.x = _wtoi(inputDlg.RDX.GetBuffer(0));
        RD.y = _wtoi(inputDlg.RDY.GetBuffer(0));
        S.x = _wtoi(inputDlg.SX.GetBuffer(0));
        S.y = _wtoi(inputDlg.SY.GetBuffer(0));

        pDC->Rectangle(LU.x, LU.y, RD.x, RD.y);
        Bfs(S.x, S.y, RGB(255, 105, 180), RGB(0, 0, 0), pDC);
    }
}


void CMFCApplication3View::Bfs(int x, int y, int col, int edgeCol, CDC* pDC) {
    // TODO: 在此处添加实现代码.
    long c;
    c = pDC->GetPixel(x, y);
    if (c != col && c != edgeCol) {
        pDC->SetPixel(x, y, col);
        //Sleep(2);
        Bfs(x + 1, y, col, edgeCol, pDC);
        Bfs(x - 1, y, col, edgeCol, pDC);
        Bfs(x, y + 1, col, edgeCol, pDC);
        Bfs(x, y - 1, col, edgeCol, pDC);
    }
}
