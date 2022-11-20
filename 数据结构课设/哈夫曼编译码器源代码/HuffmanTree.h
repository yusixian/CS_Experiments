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
const string TreePrintFile = "TreePrint.txt";//�ı���ʽ-��������������ʾ�ļ�
typedef int Position;
//���������ĵ����ڵ�
class HufTree;
class HTNode {
private:
	int weight;	 //�ý���Ȩֵ ����Ƶ��Խ�� ȨֵԽ��
	char data;	//�ý��ʵ�ʴ�����ַ���'#' ��ʾ�ý��ֻ��Ȩֵ������Ҫ������ַ�
	int pos;	//�ýڵ�����ȫ�������б�� 1��ʾ����� 
	Position left;	  //ָ������ -1��ʾ��
	Position right;	  //ָ���Һ��� -1��ʾ��
	Position parent;  //�������±� -1��ʾ��
public:
	friend class HufTree;
	
	HTNode(): weight(MaxFrequence + 1),data('#'),left(Null),right(Null),parent(Null),pos(1) {}	//���캯�� ȨֵΪNull��-1��˵��������ڵ�
	
};
class HufTree {
private:
	HTNode* H;		//�洢�����������Ľṹ����
	Position root;	//������±�
	int size;	//�洢���������������С
public:
	friend class HTNode;
	friend class Operate;
	HufTree() : H(nullptr), root(Null), size(0) {}	//�޲ι��캯��
	HufTree(map<char, int> ch){ //�вι��캯�� ����Ϊ�ַ�����Ƶ��
	
		H = nullptr;
		root = Huffman(ch);
	}  
	~HufTree() { if (H) {delete H;} }  //��������
	bool IsLeaps(Position rt);	//�жϵ�ǰ�ڵ��Ƿ�ΪҶ�ӽڵ�
	int CountSize(map<char, int> ch);	//�����ַ��������
	char GetData(Position rt);	//��ȡ��ǰ����ַ�
	string SearchCode(char Data);	//��ѯĳ�ַ���Ӧ����
	Position GetLeftSon(Position rt);	//����������±�
	Position GetRightSon(Position rt);  //�����Ҷ����±�
	Position Huffman(map<char, int> ch);	//����������� ���ظ�����±�
	void PrintChar(char ch, int num, fstream& fp);	//���ָ��num�������ַ�ch���ļ�TreePrint��
	void PrintSide(int num, fstream& fp);  //���ָ��num�����߳�ΪSideLen���ַ����ļ�TreePrint��
	map<char, int> CountCH();	//�Ҹù��������е������ַ�����Ȩֵ
	void DrawHuffmanTree(Position rt);//������չʾ�������� �浽�ļ�TreePrint��ȥ
	void ComputingHuffmanCode(Position root, string path = "");	 //������������� �ݹ鵽Ҷ�ӽ�㣬����pathΪ����㵽�������·������0��1��
};
extern map<char, string> HuffmanCode;	 //���ַ� ��Ӧ�Ĺ���������
extern map<string, char> DeHuffmanCode;	 //������������ ��Ӧ���ַ�
#endif	// !_HUFFMANTREE_
