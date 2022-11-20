#pragma once
#ifndef _OPERATE_
#define _OPERATE_
#include "Menus.h"
#include "User.h"
#include "global.h"
#include "Student.h"
class Operate {
public:
	void Read(char* s);//输入字符串s，防止长度过长
	void StoreStudentFile(vector<Student> ss);//存储学生文件
	void StoreUserFile(vector<User> uu);//存储用户文件
	void AddInfor(User& U);		 //添加学生信息
	void DeleteInfor(User& U);	 //删除学生信息
	void ModifyInfor(User& U);	 //修改学生信息
	void QueryInfor(User& U);	 //查询学生信息
	void QueryViaDifferWay(int i); //按不同形式查找 1为学号 2为姓名 3为班级 4为模糊
	void FuzzySearch(int i);//模糊查找 1为按姓名 2为按学号 3. 完全模糊查找
	void DisplayStuInfor(User& U);	 //显示全部学生信息
	void DisplayUserInfor(User& U);	//显示全部用户信息
	void ReportPrint(User& U);		 //报表打印
	void Export_File(int i);//导出所有信息文件 1/2 学生/用户
	void ChangePassWord(User& U);//修改密码
	void ImproveVIP(User& U);//管理员提升普通用户权限
	void Rank_Update();//更新班上成绩排名（综测、考试等排名）
	vector<Student> ReadStudentFile();//读取所有学生文件到动态数组中
	vector<User> ReadUserFile();//读取所有用户文件到动态数组中
};
#endif