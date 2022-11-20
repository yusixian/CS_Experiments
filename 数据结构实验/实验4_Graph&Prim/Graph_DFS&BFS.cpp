//邻接矩阵存图 DFS&BFS
#include <iostream>
#include <iomanip>
#include <queue>
using namespace std;
const int Null = -1;	//顶点类型
const int MVNum = 1000;	//最大顶点数
typedef char VertexType;	
struct VNode;
struct ArcNode {	//边结点定义
	int vexindex;	//该边所指向的顶点位置下标
	ArcNode* nextArc;	//指向下一条边的指针
	ArcNode():vexindex(Null),nextArc(nullptr) {}	//用构造函数进行初始化
};
typedef ArcNode* ArcPtr;

struct VNode {
	VertexType data;//顶点数据类型
	ArcPtr firstArc;	//指向第一条依附该顶点的边的指针 
	VNode():firstArc(nullptr) {}
	~VNode();
};
VNode::~VNode() {
	if (firstArc) {
		while (firstArc->nextArc) {
			ArcPtr p = firstArc->nextArc;
			while (p->nextArc)
				p = p->nextArc;
			delete p;
		}
		delete firstArc;
	}
}
typedef VNode* AdjList;
struct ALGraph {
	int vexNum;		//该图顶点数
	int arcNum;		//该图边数
	bool isvis[MVNum];		// DFS/BFS中是否被访问过
	AdjList vertices;	//邻接表
	ALGraph() :vexNum(0), arcNum(0), vertices(nullptr) { init();  }	//构造函数初始化
	~ALGraph();	//构造函数初始化
	int Find(VertexType val);	//查找值为val的顶点下标 没有则返回-1
	void CreateNewGraph();	//输入有向图的顶点数、边数及各条边的顶点对
	void InsertEdge(VNode& u, int vindex);	//插入边<u,v>
	void PrintAdjList();	//展示邻接表
	void init();		//遍历前的初始化操作，将isvis全部置否
	void DFS(int v);	//以顶点v为起点进行dfs遍历
	void BFS(int v);	//以顶点v为起点进行bfs遍历
};

ALGraph::~ALGraph() {
	if (vertices)
		delete[] vertices;
}
//查找值为val的顶点下标 没有则返回-1
int ALGraph::Find(VertexType val) {
	for (int i = 0; i < vexNum; ++i) {
		if (vertices[i].data == val) return i;
	}
	return -1;
}
//输入顶点数、边数与顶点和边创建一个新图
void ALGraph::CreateNewGraph() {
	cout << "请输入总顶点数、总边数,以空格隔开:";
	cin >> vexNum >> arcNum;
	getchar(); 
	cout << endl;
	if (vertices) delete[] vertices;
	vertices = new VNode[vexNum];
	cout << "输入点的名称,如A" << endl;
	for (int i = 0; i < vexNum; ++i) {
		cout << "请输入第" << i+1 << "个结点的名称:";
		cin >> vertices[i].data;
		getchar();
	}
	cout << endl;
	
	cout << "输入每个有向边两端的结点，空格间隔，如AB" << endl;
	for (int i = 0; i < arcNum; ++i) {
		VertexType s, e;
		int u, v;
		u = v = -1;
		cout << "请输入第" << i + 1 << "条边两端的顶点:";
		cin >> s >> e;
		getchar();
		for (int j = 0; j < vexNum; ++j) {
			if (vertices[j].data == s) 
				u = j;
			else if (vertices[j].data == e)
				v = j;
		}
		InsertEdge(vertices[u], v);
	}
	cout << endl;
	
	cout << "有向图创建完成！" << endl;
}
//插入边<u,v>
void ALGraph::InsertEdge(VNode& u, int vindex) {
	//将v加入u的邻接链表中
	if (!u.firstArc) {	//结点u暂时没有邻接边
		u.firstArc = new ArcNode;
		u.firstArc->vexindex = vindex;
		u.firstArc->nextArc = nullptr;
	} else {		
		ArcPtr temp = new ArcNode;
		temp->vexindex = vindex;
		temp->nextArc = u.firstArc;
		u.firstArc = temp;
	}
}
void ALGraph::PrintAdjList() {
	cout << "有向图的邻接表如下:" << endl;
	for (int i = 0; i < vexNum; ++i) {
		cout << setw(7) << vertices[i].data << "顶点  ->  ";
		ArcPtr p = vertices[i].firstArc;
		if (p) {
			cout << vertices[p->vexindex].data;
			while (p->nextArc) {
				p = p->nextArc;
				cout << setw(7) << vertices[p->vexindex].data;
			}
		}
		cout << endl;
	}
	cout << endl;
}
void ALGraph::init() {
	for (int i = 0; i < vexNum; ++i) 
		isvis[i] = false;
}
void ALGraph::DFS(int v) {
	VNode& vex = vertices[v];
	cout << setw(7) << vex.data;
	isvis[v] = true;
	ArcPtr p = vex.firstArc;
	while (p) {
		int w = p->vexindex;
		if (!isvis[w])	//若这个邻接点未访问过
			DFS(w);
		p = p->nextArc;
	}
}
void ALGraph::BFS(int v) {
	queue<int> q;	//存每次访问的下标
	isvis[v] = true;
	q.push(v);
	while (!q.empty()) {
		int t = q.front();
		q.pop();
		VNode& vex = vertices[t];
		cout << setw(7) << vex.data;
		ArcPtr p = vex.firstArc;
		while (p) {
			int w = p->vexindex;
			if (!isvis[w]) {	//若这个邻接点未访问过 加入队列
				isvis[w] = true;
				q.push(w);
			}
			p = p->nextArc;
		}
	}
	
}
int main() {
	ALGraph G;
	G.CreateNewGraph();
	G.PrintAdjList();
	VertexType v;
	cout << "请输入遍历有向图的起始点:";
	while (cin >> v) {
		G.init();//标记数组清空
		int s = G.Find(v);
		cout << "\n深度优先搜索遍历有向图结果:" << endl;
		G.DFS(s);

		G.init();//标记数组清空
		cout << "\n广度优先搜索遍历有向图结果:" << endl;
		G.BFS(s);

		cout << "\n\n请输入遍历有向图的起始点:";
	}
	return 0;
}



