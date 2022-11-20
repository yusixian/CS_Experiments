#pragma once
#ifndef _GLOBAL_
#define _GLOBAL_
#include <string>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <set>
#include <vector>
#include <algorithm>
#include "User.h"
#include "Student.h"
#include "Menus.h"
#include "Operate.h"
#include <algorithm>
using namespace std;
const string UserFileName = "Users.txt";
const string StudentFile = "Student.txt";
const string ExportUserFile = "AllUsers.csv";
const string ExportStuFile = "AllStudent.csv";
extern Menus menus;
extern User U;
extern Operate O;
bool cmp_exam(const Student& a, const Student& b);
bool cmp_multi(const Student& a, const Student& b);
bool Login();			   //登陆操作
void Register(int i = 0);//注册操作，// 0为普通用户注册，1为管理员注册
void LandR();//登录注册主菜单
void Init();			//初始化 显示登录or注册菜单
void MainInterface();	//用户操作 显示主菜单
#endif	
