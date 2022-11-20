#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
typedef int Datatype;
const int maxn = 100005;
const int inf = 0x3f3f3f3f;
int N;
Datatype a[maxn], b[maxn], c[maxn];
void swap(Datatype& a, Datatype& b) {  //交换a,b的值
	Datatype tmp = a;
	a = b;
	b = tmp;
}
void PrintArr(Datatype a[], int N) {
	for (int i = 0; i < N; ++i) {
		printf(" %d" + !i, a[i]);
	}
}
// 1.堆排序
void PercDown(Datatype a[], int N, int rt) {
	//将N个元素的数组中以a[rt]为根的子堆调整为最大堆
	int father, son;
	Datatype tmp = a[rt];
	for (father = rt; (father * 2 + 1) < N; father = son) {	 //从上往下
		son = father * 2 + 1;								 //左儿子
		if (son != N - 1 && a[son] < a[son + 1])  //右儿子存在且比左儿子大
			son++;
		if (tmp >= a[son])
			break;	//找到该放的地方
		else
			a[father] = a[son];	 //下滤
	}
	a[father] = tmp;
}
inline void BuildHeap(Datatype a[], int N) {
	//将已有N个元素的数组调整为最大堆 a[0]为最大元素
	for (int i = N / 2 - 1; i >= 0; --i) {
		PercDown(a, N, i);
	}
}
void Heap_Sort(Datatype a[], int N) {
	printf("1.调整为最大堆结果\n");
	BuildHeap(a, N);
	PrintArr(a, N);
	cout << endl;
	printf("2.交换调整过程\n");
	for (int i = N - 1; i > 0; --i) {
		cout << "最大堆顶" << a[0] << "与" << a[i] << "交换:";
		swap(a[0], a[i]);  //最大堆顶a[0]与a[i]交换
		PrintArr(a, N);
		cout << endl;
		PercDown(a, i, 0);	//删除后进行调整
		cout << " 调整为-> ";
		PrintArr(a, N);
		cout << endl;
	}
}
// 2.快速排序
void QuickSort(Datatype a[], int s, int e) {  //将a[s,e]快排
	if (s >= e)
		return;
	printf("将%d放到合适位置使左边元素都比它小，右边元素都比他大\n",a[s]);
	Datatype k = a[s];
	int i = s, j = e;
	while (i != j) {
		while (j > i && a[j] >= k)
			--j;
		if (i == j) break;
		swap(a[i], a[j]);
		PrintArr(a, N);
		cout << endl;
		while (i < j && a[i] <= k)
			++i;
		if (i == j) break;
		swap(a[i], a[j]);
		PrintArr(a, N);
		cout << endl;
	}						 //处理完后a[i] = k;
	QuickSort(a, s, i - 1);	 //快排左边部分
	QuickSort(a, i + 1, e);	 //快排右边部分
}
void Quick_Sort(Datatype a[], int N) {
	QuickSort(a, 0, N-1);
}
// 3.原始希尔排序
void Shell_Sort(Datatype a[], int N) {
	for (int D = N / 2; D > 0; D /= 2) {  //希尔增量序列
		cout << "增量为" << D << endl;
		for (int P = D; P < N; ++P) {	  //插入排序
			Datatype t = a[P];
			int i;
			for (i = P; i >= D && a[i - D] > t; i -= D)
				a[i] = a[i - D];
			a[i] = t;
		}
		PrintArr(a, N);
		cout << endl;
	}
}
int main() {
	printf("请输入待排序数数量N：");
	cin >> N;
	printf("请输入N个数：");
	for (int i = 0; i < N; ++i) {
		cin >> a[i];
		b[i] = a[i];
		c[i] = a[i];
	}
	printf("堆排序如下：");
	Heap_Sort(a, N);
	cout << endl;

	printf("快速排序如下：\n");
	Quick_Sort(b, N);
	cout << endl;

	printf("希尔排序如下：\n");
	Shell_Sort(c, N);
	cout << endl;
	getchar();
	getchar();
	return 0;
}