#pragma once
#ifndef _MENUS_
#define _MENUS_
#include <iostream>
#include <string>
using namespace std;
class Menus {
public:
	void Hint1();	//��ʾ��ӭʹ�ù�������/������
	void Hint2();	//��ʾ�����������
	void Menu1();   //��ʼ�˵���ʾ
	void Menu2();	//�������������˵���ʾ
};
extern Menus menus;
#endif