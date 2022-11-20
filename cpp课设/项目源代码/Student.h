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
	char name[15];		  //����
	char Class[15];		  //�༶
	char stuNum[15];	  //ѧ��
	double examGrade[3];  //��������Ӣ��c���Գɼ�
	double givenMark[3];  //ͬѧ�����֡�����Ա���֡���������ʦ����
	double avrGrade, multiGrade;   //����ƽ���ɼ����۲��ܷ�
	int examRank, multiGradeRank;  //�����ܷ��������۲��ܷ�����
public:
	friend bool cmp_exam(const Student& a, const Student& b);
	friend bool cmp_multi(const Student& a, const Student& b);
	void InputInfor();	  //����ѧ����Ϣ
	void display();		  //չʾ��Ϣ ��չʾ�ؼ���Ϣ
	void PrintDetail();	  //չʾ��ϸ��Ϣ
	void Change();		  //�޸���Ϣ��ѧ�Ų����޸�
	void Change_Name();	  //�޸�����
	void Change_Class();  //�޸İ༶
	void Change_Grade();  //�޸ĳɼ�
	double get_avrGrade() { return avrGrade; }
	double get_multiGrade() { return multiGrade; }
	bool operator<(Student& s);	 //����С�ںţ���ѧ������
};
#endif
