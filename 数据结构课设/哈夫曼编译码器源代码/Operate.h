#pragma once
#ifndef _OPERATE_
#define _OPERATE_
#include "Menus.h"
#include "global.h"
#include <map>
#include "HuffmanTree.h"
class Operate {
public:
	//主菜单功能
	void CreateHfmTreeByInput();	 //从终端读入字符及其权值直接建立哈夫曼树
	void CreateHfmTreeByFile();	//读取字符文件建立最优哈夫曼树
	void Encoding();		//哈夫曼编码 对文件ToBeTran中的正文进行编码
	void Decoding();		//哈夫曼译码 将文件CodeFile的内容译码后以文本形式显示在终端上，译文存入文件TextFile
	void PrintCompreRatio();//显示译码后压缩率与平均压缩长度
	void Search();		//查询某字符对应编码
	void PrintHfmTree();	//展示哈夫曼树
	void ExportHfmCode();	//导出哈夫曼编码到CorresponCode文件中
	//辅助功能
	void PrintCode();  //展示文件CodePrintFile，并输出经哈夫曼编码后的文本到终端上	
	void PrintHfmByTree();	//展示文件TreePrintFile，即以树形展示哈夫曼树
	void PrintToBeTranFile();	//展示ToBeTran文件内容
	void PrintCorresponCodeFile();	//展示已建好的哈夫曼树中各字符对应编码
	void PrintFrequence(map<char, int> m);	//展示各字符出现次数
	void StoreCorreCodeFile();//将已建好的哈夫曼树中各字符对应编码存入文件CorresponCodeFile中
	void StoreHfmTree();  //二进制形式存储哈夫曼树到文件HfmTree中
	map<char, int> ReadCHfile();  //读入字符文件ToBeTranFile返回其中所有字符和出现频率
	void ReadHufTreeFile();	 //从文件HufTree中读入哈夫曼树
};
extern Operate O;
#endif