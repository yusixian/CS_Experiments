#pragma once
#ifndef _GLOBAL_
#define _GLOBAL_
#include "Menus.h"
#include "Operate.h"
#include "HuffmanTree.h"
#include <algorithm>
#include <conio.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <windows.h>
using namespace std;
const string HfmTreeFile = "HfmTree.hufman";  //二进制形式-存储哈夫曼树
const string ToBeTranFile = "ToBeTran.txt";	 //文本形式-待编码的原文件
const string CodeFile = "CodeFile.hufman";	  //二进制形式-编码后的压缩文件
const string ConfigFile = "Configfile.hufman";//二进制形式-配置文件,存储待翻译字符数以及译码实际占多少比特
const string TextFile = "TextFile.txt";		//文本形式-由压缩文件解压缩而来的文本文件
const string CodePrintFile = "CodePrint.txt";  //文本形式-编码后压缩文件的直观展示(01串)
const string CorresponCodeFile = "CorresponCode.csv";	//文本形式-存储哈夫曼树中字符及其对应编码，可用excel打开
const int MaxCodeNum = 10;//编码后一行最多显示对应编码数量
const int MaxTextNum = 50;//译码后一行最多显示对应字符数量
extern HufTree huf;
void Init();		   //初始化
void MainInterface();  //用户操作 显示主菜单
void CreateHfmTree();	//建立哈夫曼树
#endif
