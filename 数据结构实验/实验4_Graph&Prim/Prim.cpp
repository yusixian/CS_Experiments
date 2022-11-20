//邻接矩阵存图
#include <iomanip>
#include <iostream>
using namespace std;
const int inf = 32767;	  //无穷大
const int Null = -1;	 
const int MVNum = 500;	  //最大顶点数
typedef char VerTexType;  //假设顶点的数据类型为字符型
typedef int ArcType;	  //表示边的权值，类型为整形
//辅助数组的定义，用来记录从顶点集U到V-U的权值最小的边
bool isvis[MVNum];	  //顶点i是否被收录过
ArcType dist[MVNum];  //到该节点路径最短的路径长度
int fa[MVNum];		  //到该节点路径最短的顶点下标

struct AMGraph {
	VerTexType vexs[MVNum];		 //顶点表
	ArcType arcs[MVNum][MVNum];	 //邻接矩阵
	int vexNum, arcNum;			 //图的当前点数和边数
	void init();				 //将isvis全部置否
	int Find(VerTexType val);  //查找值为val的顶点下标 没有则返回-1
	void CreateNewGraph();	//输入无向图的顶点数、边数及各条边的顶点对
	void InsertEdge(VerTexType s, VerTexType e, ArcType w);	//插入权值为w的边(u,v)
	void PrintAMGraph();								//展示邻接矩阵
	void Prim(VerTexType s);  // Prim算法构造最小生成树, 以s为起始点
	AMGraph() : vexNum(0), arcNum(0) {	//构造函数初始化
		for (int i = 0; i < MVNum; ++i) {
			for (int j = 0; j < MVNum; ++j) {
				arcs[i][j] = inf;
			}
			dist[i] = inf;
			fa[i] = Null;
			isvis[i] = false;
		}
	};
};
void AMGraph::init() {
	for (int i = 0; i < vexNum; ++i) {
		isvis[i] = false;
		fa[i] = Null;
	}
}
//查找值为val的顶点下标 没有则返回-1
int AMGraph::Find(VerTexType val) {
	for (int i = 0; i < vexNum; ++i) {
		if (vexs[i] == val) {
			return i;
		}
	}
	return Null;
}
//输入顶点数、边数与顶点和边创建一个新图
void AMGraph::CreateNewGraph() {
	cout << "请输入总顶点数、总边数,以空格隔开:";
	cin >> vexNum >> arcNum;
	getchar();
	cout << endl;
	cout << "输入点的名称,如A" << endl;
	for (int i = 0; i < vexNum; ++i) {
		cout << "请输入第" << i + 1 << "个结点的名称:";
		cin >> vexs[i];
		getchar();
	}
	cout << endl;

	cout << "输入每个无向边两端的结点名称及权值，空格间隔，如AB 5" << endl;
	for (int i = 0; i < arcNum; ++i) {
		VerTexType s, e;
		ArcType w;
		int u, v;
		u = v = -1;
		cout << "请输入第" << i + 1 << "条边两端的顶点及其权值:";
		cin >> s >> e >> w;
		getchar();
		InsertEdge(s, e, w);
	}
	cout << endl;

	cout << "无向图创建完成！" << endl;
}
//插入权值为w的边(u,v)
void AMGraph::InsertEdge(VerTexType s, VerTexType e, ArcType w) {
	int u, v;
	for (int i = 0; i < vexNum; ++i) {
		if (vexs[i] == s)
			u = i;
		if (vexs[i] == e)
			v = i;
	}
	arcs[u][v] = w;
	arcs[v][u] = w;
}
void AMGraph::PrintAMGraph() {
	cout << "该无向图的邻接矩阵如下:" << endl;
	for (int i = 0; i < vexNum; ++i) {
		for (int j = 0; j < vexNum; ++j) {
			cout << setw(7) << arcs[i][j];
		}
		cout << endl;
	}
	cout << endl;
}
void AMGraph::Prim(VerTexType s) {
	int ans = 0;
	int si = Find(s);
	init();
	isvis[si] = true;
	for (int i = 0; i < vexNum; ++i) {
		dist[i] = arcs[si][i];  //初始每个顶点到根结点s的距离为他们边，若无边则为最大值
		fa[i] = si;	  //每个结点最短边的另一个端点
	}
	for (int i = 1; i <= vexNum - 1; ++i) {	 // n个顶点的最小生成树需要找n-1条边
		int minw = inf;
		int v = Null;
		//找最小且未找过的顶点
		for (int j = 0; j < vexNum; ++j) {
			if (!isvis[j] && dist[j] < minw) {
				minw = dist[j];
				v = j;
			}
		}
		if (v != Null) {  //找到了最小的，收入
			isvis[v] = true;
			ans += dist[v];
			cout << "边   " << vexs[fa[v]] << "  ->   " << vexs[v] << "\t"
				 << dist[v] << endl;
			//更新距离dist,
			for (int j = 0; j < vexNum; ++j) {
				if (!isvis[j] && arcs[v][j] < dist[j]) {
					dist[j] = arcs[v][j];
					fa[j] = v;
				}
			}
		}
		else {
			cout << "未能找到最小生成树，该图不为连通图！" << endl;
			return;
		}
	}
	cout << "最小生成树的权值之和:" << ans << endl;
}
int main() {
	AMGraph G;
	G.CreateNewGraph();
	G.PrintAMGraph();
	VerTexType s;
	cout << "请输入起点：";
	cin >> s;
	getchar();
	G.Prim(s);
	getchar();
	return 0;
}
