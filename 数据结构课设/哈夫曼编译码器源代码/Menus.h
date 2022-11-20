#pragma once
#ifndef _MENUS_
#define _MENUS_
#include <iostream>
#include <string>
using namespace std;
class Menus {
public:
	void Hint1();	//提示欢迎使用哈夫曼编/译码器
	void Hint2();	//提示按任意键返回
	void Menu1();   //初始菜单显示
	void Menu2();	//建立哈夫曼树菜单显示
};
extern Menus menus;
#endif