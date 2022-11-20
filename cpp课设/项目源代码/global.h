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
bool Login();			   //��½����
void Register(int i = 0);//ע�������// 0Ϊ��ͨ�û�ע�ᣬ1Ϊ����Աע��
void LandR();//��¼ע�����˵�
void Init();			//��ʼ�� ��ʾ��¼orע��˵�
void MainInterface();	//�û����� ��ʾ���˵�
#endif	
