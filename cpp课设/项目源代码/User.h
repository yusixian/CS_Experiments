#pragma once
#ifndef _USER_
#define _USER_
#pragma warning(disable : 4996)
#include <cstring>
#include <iostream>
#include <cstdio>
using namespace std;
class Operate;
class User {  //用户
	friend bool Login();
	friend void Register(int i);
	friend void MainInterface();
	friend class Operate;
	char userName[15];	//账号
	char passWord[15];	//密码
	short isAdmin;		//权限 0为普通用户 1为管理员
public:
	User() : isAdmin(0) {}//默认为普通用户
	User(short i) : isAdmin(i) {}//0为普通用户 1为管理员
	void changeUserName(char* s);//更改用户名
	void changePassWord(char* s);//更改密码
	void PrintNandP();//显示用户名和密码
};
#endif