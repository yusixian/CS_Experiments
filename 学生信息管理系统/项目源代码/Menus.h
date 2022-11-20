#pragma once
#ifndef _MENUS_
#define _MENUS_
#include <iostream>
#include <string>
using namespace std;
class Menus {
public:
	void Hint1();//管理员注册提示
	void Menu1();//登录or注册菜单显示
	void Menu2(int i = 0);//显示用户操作菜单（主菜单）0为用户权限显示的菜单，1为管理员权限显示的菜单
	void Menu3();//学生信息修改一级菜单
	void Menu4();//学生信息修改二级菜单
	void Menu5();	//学生信息查询一级菜单
	void Menu6();	//学生信息查询二级菜单
	void Menu7(int i = 0);	//报表打印 0为用户权限显示的菜单，1为管理员权限显示的菜单
};
#endif

