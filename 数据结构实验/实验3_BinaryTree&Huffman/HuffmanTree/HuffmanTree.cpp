#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>
#include <queue>
#define f1_Name "f1.txt"
#define f2_Name "f2.txt"
#define f3_Name "f3.txt"
#define Error -1
#define Null -1
#define MaxSize 1000
#define MaxFrequence 200
using namespace std;
typedef int Position;
struct HTNode {
	int weight;		//该结点的权值 出现频率越高 权值越大 
	char data;	//该结点实际代表的字符，'#' 表示该结点只有权值，无需要编码的字符
	Position left;	//指向左孩子 -1表示无
	Position right;	//指向右孩子 -1表示无
	Position parent; //父结点的下标 -1表示无
	HTNode() :weight(MaxFrequence + 1), data('#'), left(Null), right(Null), parent(Null) {}	
	//构造函数 权值为Null（-1）说明无这个节点
} *H;
map<char, string> HuffmanCode;	//各字符对应的哈弗曼编码
map<string, char> DeHuffmanCode;	//各哈弗曼编码 对应的字符
//读取f1文件 返回f1中字符出现频率
map<char, int> Readfile1() {
	map<char, int> ch;
	string str;
	fstream f1;
	f1.open(f1_Name, ios::in);
	if (!f1) {
		cout << "f1.txt文件打开失败!" << endl;
		return ch;
	}
	while (getline(f1, str)) {
		int len = str.length();
		for (int i = 0; i < len; ++i) {
			if (ch.end() == ch.find(str[i]))
				ch.insert(make_pair(str[i], 1));
			else
				++ch[str[i]];
		}
	}
	f1.close();
	return ch;
}

//计算有多少种字符
int CountSize(map<char, int> ch) {
	int cnt = 0;
	for (auto& i : ch) {	//前size个节点 存数据和权值
		++cnt;
	}
	return cnt;
}

//展示各字符出现次数
void PrintFrequence(const map<char, int> m) {
	cout << "字符\t出现次数" << endl;
	int cnt = 0, sum = 0;
	for (const auto& i : m) {
		cout << i.first << '\t' << i.second << endl;
		++cnt;
		sum += i.second;
	}
	cout << "共有" << cnt << "种字符。" << endl;
	cout << "共有" << sum << "个字符。" << endl;
}

//将字符及其频率作为参数传入 构造出哈夫曼树 返回根节点下标 无则返回Null(-1)
Position Huffman(map<char, int> ch) {
	int size = CountSize(ch);	//ch中共统计了多少种字符 
	if (size == 0) return Null;
	if (H) delete[] H;
	H = new HTNode[2 * size - 1];
	int cnt = 0;
	for (auto& i : ch) {	//前size个节点 存数据和权值
		H[cnt].data = i.first;
		H[cnt].weight = i.second;
		++cnt;
	}
	if (size == 1) return 0;	//只有一个元素
	Position EmptyNode = cnt;	 //最前边的空结点下标
	for (int k = 1; k <= size - 1; ++k) {	//size-1次合并 每次合并选两个在所有无父节点中权值最小的结点
		int min1 = Null, min2 = Null;	//最小权值结点下标、次小权值结点下标
		int minw1 = MaxFrequence + 1, minw2 = MaxFrequence + 1;	//最小权值1、次小权值2
		for (int i = 0; i < 2 * size - 1; ++i) {	//找两个最小无父结点的结点
			if (H[i].parent != Null) continue;	//有父节点了不用看
			if (H[i].weight < minw1) {	//当前节点权值比最小值小
				minw2 = minw1;
				min2 = min1;
				minw1 = H[i].weight;
				min1 = i;
			}
			else if (H[i].weight < minw2) {	//比次小值小
				minw2 = H[i].weight;
				min2 = i;
			}

		}
		//合并
		H[min1].parent = EmptyNode;
		H[min2].parent = EmptyNode;
		H[EmptyNode].left = min1;
		H[EmptyNode].right = min2;
		H[EmptyNode].weight = H[min1].weight + H[min2].weight;
		H[EmptyNode].parent = Null;
		EmptyNode++;
	}
	Position root = 0;
	while (H[root].parent != -1) {	//有父节点的时候循环继续，找到根节点即当前结点没有父节点的时候循环退出
		root = H[root].parent;
	}
	return root;
}

//先序遍历展示哈夫曼树
void PreOrderPrintHuffman(Position root) {
if (root != Null) {
	cout << H[root].data << ": " << H[root].weight << endl;
	if (H[root].left != Null) PreOrderPrintHuffman(H[root].left);
	if (H[root].right != Null) PreOrderPrintHuffman(H[root].right);
}
else cout << "The HuffmanTree is Empty" << endl;
}

//中序遍历展示哈夫曼树
void InOrderPrintHuffman(Position root) {
	if (root != -1) {
		if (H[root].left != -1) InOrderPrintHuffman(H[root].left);
		cout << H[root].data << ": " << H[root].weight << endl;
		if (H[root].right != -1) InOrderPrintHuffman(H[root].right);
	}
	else cout << "The HuffmanTree is Empty" << endl;
}

//计算哈夫曼编码 递归到叶子结点 参数path为根结点到这个结点的路径（左0右1） 
void ComputingHuffmanCode(Position root, string path) {
if (root == Null)
	cout << "Fail to computing！The HuffmanTree is Empty" << endl;
if (H[root].left == Null && H[root].right == Null) {//为叶子结点
	HuffmanCode[H[root].data] = path;
	DeHuffmanCode[path] = H[root].data;		//这里将哈夫曼编码对应的字符也存下方便译码
	return;
}
string lcode = path + '0';
string rcode = path + '1';
if (H[root].left != Null) ComputingHuffmanCode(H[root].left, lcode);
if (H[root].right != Null) ComputingHuffmanCode(H[root].right, rcode);
}

//展示各字符哈夫曼编码
void PrintHuffmanCode() {
	cout << "字符\t哈夫曼编码" << endl;
	int cnt = 0, sum = 0;
	for (const auto& i : HuffmanCode) {
		cout << i.first << '\t' << i.second << endl;
	}
}

//读入f1文件，全部编码后存入另一个文件f2；
void StoreAfterCoding() {
	fstream f1, f2;
	f1.open(f1_Name, ios::in);
	f2.open(f2_Name, ios::out);
	if (!f1) {
		cout << "f1.txt文件打开失败!" << endl;
		return;
	}
	if (!f2) {
		cout << "f2.txt文件打开失败!" << endl;
		return;
	}
	string str;
	while (getline(f1, str)) {
		int len = str.length();
		for (int i = 0; i < len; ++i) {
			f2 << HuffmanCode[str[i]] << ' ';//存的时候加个空格方便译码
		}
	}
	f1.close();
	f2.close();
}

//读入f2文件，全部解码后存入另一个文件f3；
void GeneratedAfterDecoding() {
	fstream f2, f3;
	f2.open(f2_Name, ios::in);
	f3.open(f3_Name, ios::out);
	if (!f2) {
		cout << "f2.txt文件打开失败!" << endl;
		return;
	}
	if (!f3) {
		cout << "f3.txt文件打开失败!" << endl;
		return;
	}
	string str;
	while (f2 >> str) {
		f3 << DeHuffmanCode[str];
	}
	f2.close();
	f3.close();
}
int main() {
	map<char, int> ch;
	//(1)建立由英文字符组成的文件f1（字符种类≥10，长度≥100），并统计不同字符出现的次数；
	ch = Readfile1();
	PrintFrequence(ch);

	//(2)按字符出现的次数对其建立哈夫曼树，并求出各个字符的哈夫曼编码
	Position root = Huffman(ch);
	cout << "先序遍历展示哈夫曼树" << endl;
	PreOrderPrintHuffman(root);
	cout << "\n中序遍历展示哈夫曼树" << endl;
	InOrderPrintHuffman(root);
	string str;
	ComputingHuffmanCode(root, str);
	PrintHuffmanCode();

	//(3)读入要编码的文件f1，编码后存入另一个文件f2
	StoreAfterCoding();

	//(4)读入要解码的文件f2，解码后存入另一个文件f3
	GeneratedAfterDecoding();
	return 0;
}
