#pragma once
#ifndef _OPERATE_
#define _OPERATE_
#include "Menus.h"
#include "global.h"
#include <map>
#include "HuffmanTree.h"
class Operate {
public:
	//���˵�����
	void CreateHfmTreeByInput();	 //���ն˶����ַ�����Ȩֱֵ�ӽ�����������
	void CreateHfmTreeByFile();	//��ȡ�ַ��ļ��������Ź�������
	void Encoding();		//���������� ���ļ�ToBeTran�е����Ľ��б���
	void Decoding();		//���������� ���ļ�CodeFile��������������ı���ʽ��ʾ���ն��ϣ����Ĵ����ļ�TextFile
	void PrintCompreRatio();//��ʾ�����ѹ������ƽ��ѹ������
	void Search();		//��ѯĳ�ַ���Ӧ����
	void PrintHfmTree();	//չʾ��������
	void ExportHfmCode();	//�������������뵽CorresponCode�ļ���
	//��������
	void PrintCode();  //չʾ�ļ�CodePrintFile����������������������ı����ն���	
	void PrintHfmByTree();	//չʾ�ļ�TreePrintFile����������չʾ��������
	void PrintToBeTranFile();	//չʾToBeTran�ļ�����
	void PrintCorresponCodeFile();	//չʾ�ѽ��õĹ��������и��ַ���Ӧ����
	void PrintFrequence(map<char, int> m);	//չʾ���ַ����ִ���
	void StoreCorreCodeFile();//���ѽ��õĹ��������и��ַ���Ӧ��������ļ�CorresponCodeFile��
	void StoreHfmTree();  //��������ʽ�洢�����������ļ�HfmTree��
	map<char, int> ReadCHfile();  //�����ַ��ļ�ToBeTranFile�������������ַ��ͳ���Ƶ��
	void ReadHufTreeFile();	 //���ļ�HufTree�ж����������
};
extern Operate O;
#endif