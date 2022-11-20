#pragma once
#ifndef _STUDENT_
#	define _STUDENT_
#	include "Menus.h"
#	include <Windows.h>
#	include <conio.h>
#	include <cstdio>
#	include <cstring>
#	include <iostream>
using namespace std;
extern Menus m;
class Operate;
class Student {
	friend class Operate;
	char name[15];		  //姓名
	char Class[15];		  //班级
	char stuNum[15];	  //学号
	double examGrade[3];  //高数、大英、c语言成绩
	double givenMark[3];  //同学互评分、辅导员评分、班主任老师评分
	double avrGrade, multiGrade;   //考试平均成绩、综测总分
	int examRank, multiGradeRank;  //考试总分排名、综测总分排名
public:
	friend bool cmp_exam(const Student& a, const Student& b);
	friend bool cmp_multi(const Student& a, const Student& b);
	void InputInfor();	  //输入学生信息
	void display();		  //展示信息 仅展示关键信息
	void PrintDetail();	  //展示详细信息
	void Change();		  //修改信息，学号不可修改
	void Change_Name();	  //修改名字
	void Change_Class();  //修改班级
	void Change_Grade();  //修改成绩
	double get_avrGrade() { return avrGrade; }
	double get_multiGrade() { return multiGrade; }
	bool operator<(Student& s);	 //重载小于号，按学号排序
};
#endif
