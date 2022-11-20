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
const string HfmTreeFile = "HfmTree.hufman";  //��������ʽ-�洢��������
const string ToBeTranFile = "ToBeTran.txt";	 //�ı���ʽ-�������ԭ�ļ�
const string CodeFile = "CodeFile.hufman";	  //��������ʽ-������ѹ���ļ�
const string ConfigFile = "Configfile.hufman";//��������ʽ-�����ļ�,�洢�������ַ����Լ�����ʵ��ռ���ٱ���
const string TextFile = "TextFile.txt";		//�ı���ʽ-��ѹ���ļ���ѹ���������ı��ļ�
const string CodePrintFile = "CodePrint.txt";  //�ı���ʽ-�����ѹ���ļ���ֱ��չʾ(01��)
const string CorresponCodeFile = "CorresponCode.csv";	//�ı���ʽ-�洢�����������ַ������Ӧ���룬����excel��
const int MaxCodeNum = 10;//�����һ�������ʾ��Ӧ��������
const int MaxTextNum = 50;//�����һ�������ʾ��Ӧ�ַ�����
extern HufTree huf;
void Init();		   //��ʼ��
void MainInterface();  //�û����� ��ʾ���˵�
void CreateHfmTree();	//������������
#endif
