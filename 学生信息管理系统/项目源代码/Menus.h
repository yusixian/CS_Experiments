#pragma once
#ifndef _MENUS_
#define _MENUS_
#include <iostream>
#include <string>
using namespace std;
class Menus {
public:
	void Hint1();//����Աע����ʾ
	void Menu1();//��¼orע��˵���ʾ
	void Menu2(int i = 0);//��ʾ�û������˵������˵���0Ϊ�û�Ȩ����ʾ�Ĳ˵���1Ϊ����ԱȨ����ʾ�Ĳ˵�
	void Menu3();//ѧ����Ϣ�޸�һ���˵�
	void Menu4();//ѧ����Ϣ�޸Ķ����˵�
	void Menu5();	//ѧ����Ϣ��ѯһ���˵�
	void Menu6();	//ѧ����Ϣ��ѯ�����˵�
	void Menu7(int i = 0);	//�����ӡ 0Ϊ�û�Ȩ����ʾ�Ĳ˵���1Ϊ����ԱȨ����ʾ�Ĳ˵�
};
#endif

