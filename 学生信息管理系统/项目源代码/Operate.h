#pragma once
#ifndef _OPERATE_
#define _OPERATE_
#include "Menus.h"
#include "User.h"
#include "global.h"
#include "Student.h"
class Operate {
public:
	void Read(char* s);//�����ַ���s����ֹ���ȹ���
	void StoreStudentFile(vector<Student> ss);//�洢ѧ���ļ�
	void StoreUserFile(vector<User> uu);//�洢�û��ļ�
	void AddInfor(User& U);		 //���ѧ����Ϣ
	void DeleteInfor(User& U);	 //ɾ��ѧ����Ϣ
	void ModifyInfor(User& U);	 //�޸�ѧ����Ϣ
	void QueryInfor(User& U);	 //��ѯѧ����Ϣ
	void QueryViaDifferWay(int i); //����ͬ��ʽ���� 1Ϊѧ�� 2Ϊ���� 3Ϊ�༶ 4Ϊģ��
	void FuzzySearch(int i);//ģ������ 1Ϊ������ 2Ϊ��ѧ�� 3. ��ȫģ������
	void DisplayStuInfor(User& U);	 //��ʾȫ��ѧ����Ϣ
	void DisplayUserInfor(User& U);	//��ʾȫ���û���Ϣ
	void ReportPrint(User& U);		 //�����ӡ
	void Export_File(int i);//����������Ϣ�ļ� 1/2 ѧ��/�û�
	void ChangePassWord(User& U);//�޸�����
	void ImproveVIP(User& U);//����Ա������ͨ�û�Ȩ��
	void Rank_Update();//���°��ϳɼ��������۲⡢���Ե�������
	vector<Student> ReadStudentFile();//��ȡ����ѧ���ļ�����̬������
	vector<User> ReadUserFile();//��ȡ�����û��ļ�����̬������
};
#endif