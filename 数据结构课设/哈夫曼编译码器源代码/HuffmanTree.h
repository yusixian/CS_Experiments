#pragma once
#ifndef _HUFFMANTREE_
#define _HUFFMANTREE_
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <vector>
#include <conio.h>
#include <fstream>
#include <windows.h>
using namespace std;
const int Null = -1;
const int MaxSize = 1000;
const int MaxFrequence = 200;
const int SideLen = 6;
const string TreePrintFile = "TreePrint.txt";//文本形式-哈夫曼树树形显示文件
typedef int Position;
//哈夫曼树的单个节点
class HufTree;
class HTNode {
private:
	int weight;	 //该结点的权值 出现频率越高 权值越大
	char data;	//该结点实际代表的字符，'#' 表示该结点只有权值，无需要编码的字符
	int pos;	//该节点在完全二叉树中编号 1表示根结点 
	Position left;	  //指向左孩子 -1表示无
	Position right;	  //指向右孩子 -1表示无
	Position parent;  //父结点的下标 -1表示无
public:
	friend class HufTree;
	
	HTNode(): weight(MaxFrequence + 1),data('#'),left(Null),right(Null),parent(Null),pos(1) {}	//构造函数 权值为Null（-1）说明无这个节点
	
};
class HufTree {
private:
	HTNode* H;		//存储哈夫曼树结点的结构数组
	Position root;	//根结点下标
	int size;	//存储哈夫曼树的数组大小
public:
	friend class HTNode;
	friend class Operate;
	HufTree() : H(nullptr), root(Null), size(0) {}	//无参构造函数
	HufTree(map<char, int> ch){ //有参构造函数 参数为字符及其频率
	
		H = nullptr;
		root = Huffman(ch);
	}  
	~HufTree() { if (H) {delete H;} }  //析构函数
	bool IsLeaps(Position rt);	//判断当前节点是否为叶子节点
	int CountSize(map<char, int> ch);	//计算字符种类个数
	char GetData(Position rt);	//获取当前结点字符
	string SearchCode(char Data);	//查询某字符对应编码
	Position GetLeftSon(Position rt);	//返回左儿子下标
	Position GetRightSon(Position rt);  //返回右儿子下标
	Position Huffman(map<char, int> ch);	//构造哈夫曼树 返回根结点下标
	void PrintChar(char ch, int num, fstream& fp);	//输出指定num个数的字符ch到文件TreePrint中
	void PrintSide(int num, fstream& fp);  //输出指定num个数边长为SideLen的字符到文件TreePrint中
	map<char, int> CountCH();	//找该哈夫曼树中的所有字符及其权值
	void DrawHuffmanTree(Position rt);//以树形展示哈夫曼树 存到文件TreePrint中去
	void ComputingHuffmanCode(Position root, string path = "");	 //计算哈夫曼编码 递归到叶子结点，参数path为根结点到这个结点的路径（左0右1）
};
extern map<char, string> HuffmanCode;	 //各字符 对应的哈弗曼编码
extern map<string, char> DeHuffmanCode;	 //各哈弗曼编码 对应的字符
#endif	// !_HUFFMANTREE_
