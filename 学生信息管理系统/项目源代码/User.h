#pragma once
#ifndef _USER_
#define _USER_
#pragma warning(disable : 4996)
#include <cstring>
#include <iostream>
#include <cstdio>
using namespace std;
class Operate;
class User {  //�û�
	friend bool Login();
	friend void Register(int i);
	friend void MainInterface();
	friend class Operate;
	char userName[15];	//�˺�
	char passWord[15];	//����
	short isAdmin;		//Ȩ�� 0Ϊ��ͨ�û� 1Ϊ����Ա
public:
	User() : isAdmin(0) {}//Ĭ��Ϊ��ͨ�û�
	User(short i) : isAdmin(i) {}//0Ϊ��ͨ�û� 1Ϊ����Ա
	void changeUserName(char* s);//�����û���
	void changePassWord(char* s);//��������
	void PrintNandP();//��ʾ�û���������
};
#endif