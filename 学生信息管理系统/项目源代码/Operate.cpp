#include "Operate.h"
void Operate::Read(char* s) {
	string str;
	cin >> str;
	cout << endl;
	while (str.size() >= 15) {
		str.erase();
		cout << "\t\t\t\t ���ȹ���������������:";
		cin >> str;
		cout << endl;
	}
	strcpy(s, str.c_str());
}
void Operate::StoreStudentFile(vector<Student> ss) {
	Student s;
	fstream of;
	of.open(StudentFile, ios::out | ios::binary);  //�Զ�������ʽ
	vector<Student>::iterator it;
	for (it = ss.begin(); it != ss.end(); it++) {
		s = *it;
		of.write((char*)&s, sizeof(s));	 //�����ļ�
	}
	of.close();
}
void Operate::StoreUserFile(vector<User> uu) {
	User u;
	fstream of;
	of.open(UserFileName, ios::out | ios::binary);
	vector<User>::iterator it;
	for (it = uu.begin(); it != uu.end(); it++) {
		u = *it;
		of.write((char*)&u, sizeof(u));	 //�����ļ�
	}
	of.close();
}
void Operate::AddInfor(User& U) {
	Student s1, s;
	system("cls");
	cout << "\n\t\t\t �q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�����T�T�T�r" << endl;
	cout << "\t\t\t��     ѧ���ۺϲ�������ϵͳ����ѧ����Ϣ��ӽ���   ��" << endl;
	cout << "\t\t\t�t �T�T�T�����T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T �s\n" << endl;
	char stunum[15];
	cout << "\t\t\t   ������Ҫ��ӵ�ѧ����ѧ�ţ�";
	Read(stunum);
	vector<Student> ss = ReadStudentFile();
	vector<Student>::iterator it;
	//ȷ���ļ���֮ǰû�����ѧ������Ϣ��ѧ��Ψһ��
	bool flag = true;  //�Ƿ���Ҫ�ټ��һ��
	while (flag) {
		bool k = false;	 //�Ƿ����ظ�
		for (it = ss.begin(); it != ss.end(); it++) {
			s = *it;
			if (strcmp(stunum, s.stuNum) == 0) {  //ѧ�����ظ���
				flag = true;
				cout << "\t\t\t��ѧ����Ϣ�Ѵ���,����������Ҫ��ӵ�ѧ����ѧ��:";
				Read(stunum);
				k = true;
				break;
			}
		}
		if (!k)	 //����ǽ���ѭ�������ģ�˵��ѧ�Ų����ظ���
			flag = false;
	}
	s1.InputInfor();  //������Ϣ
	ss.push_back(s1);
	StoreStudentFile(ss);
	Rank_Update();  //��������
	cout << "\t\t\t\t---�����ϣ��������������һ��---" << endl;
	_getch();
}
void Operate::DeleteInfor(User& U) {
	Student s;
	vector<Student> ss = ReadStudentFile();
	vector<Student>::iterator it;
	char stunum[15];
	system("cls");
	cout << "\n\t\t\t �q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�����T�T�T�r" << endl;
	cout << "\t\t\t��     ѧ���ۺϲ�������ϵͳ����ѧ����Ϣɾ������   ��" << endl;
	cout << "\t\t\t�t �T�T�T�����T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T �s\n" << endl;
	cout << "\t\t\t   ������Ҫɾ����ѧ����ѧ�ţ�";
	bool flag = true;
	while (flag) {
		Read(stunum);
		for (it = ss.begin(); it != ss.end(); it++) {
			s = (*it);
			if (strcmp(stunum, s.stuNum) == 0) {
				flag = false;  //�ҵ���Ҫɾ����ѧ��
				cout << "\t\t\t\tҪɾ����ѧ������Ϣ����\n" << endl;
				cout << "-----ѧ��------����------�༶------����----��Ӣ----"
						"c����--ƽ���ɼ�--�۲��ܷ�--�ɼ�����--�۲�����\n"
					 << endl;
				s.display();
				cout << "\n\t\t\t---ȷ��Ҫɾ���𣿰�ESCȡ��ɾ��,���س�ȷ��ɾ��-"
						"--"
					 << endl;
				int c = _getch();
				if (c == 27) {	// ESC
					break;
				}
				else {
					it = ss.erase(it);
					cout << "\n\t\t\t\tɾ����ɣ�\n" << endl;
					Sleep(500);
					break;
				}
			}
		}
		if (flag) {	 //δ�ҵ�
			cout << "\t\t\t\tδ�ҵ���ѧ��,����������ѧ�ţ�";
		}
	}
	//ɾ����ϣ����´����ļ�
	StoreStudentFile(ss);
	Rank_Update();
}
void Operate::ModifyInfor(User& U) {
	system("cls");
	cout << "\n\t\t\t �q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�����T�T�T�r" << endl;
	cout << "\t\t\t��     ѧ���ۺϲ�������ϵͳ����ѧ����Ϣ�޸Ľ���   ��" << endl;
	cout << "\t\t\t�t �T�T�T�����T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T �s\n" << endl;
	cout << "\t\t\t   ������Ҫ�޸�ѧ����ѧ��:";
	vector<Student> ss = ReadStudentFile();
	vector<Student>::iterator it;
	char stunum[15];
	bool flag = true;
	while (flag) {
		Read(stunum);
		for (it = ss.begin(); it != ss.end(); it++) {
			if (strcmp(stunum, (*it).stuNum) == 0) {
				flag = false;  //�ҵ���Ҫ�޸ĵ�ѧ��
				cout << "\t\t\t   Ҫ�޸ĵ�ѧ������Ϣ����\n" << endl;
				cout << "-----ѧ��------����------�༶------����----��Ӣ----"
						"c����--ƽ���ɼ�--�۲��ܷ�--�ɼ�����--�۲�����\n"
					 << endl;
				(*it).display();
				cout << endl;
				cout << "\t\t\t---"
						"ȷ��Ҫ�޸��𣿰�ESC���˳���������������ɽ�����һ��---"
					 << endl;
				int c = _getch();
				if (c == 27) {	// ESC
					break;
				}
				else {	//�س�
					(*it).Change();
					Sleep(500);
					break;
				}
			}
		}
		if (flag) {	 //δ�ҵ�
			cout << "\t\t\t\tδ�ҵ���ѧ��,����������ѧ�ţ�";
		}
	}
	StoreStudentFile(ss);
	Rank_Update();
}
void Operate::QueryInfor(User& U) {
	system("cls");
	bool flag = true;
	while (flag) {
		menus.Menu5();
		switch (_getch()) {
			case '1': QueryViaDifferWay(1); break;	// 1. ��ѧ�Ų�ѯ����ѧ����Ϣ
			case '2': QueryViaDifferWay(2); break;	// 2. ��������ѯѧ����Ϣ
			case '3': QueryViaDifferWay(3); break;	// 3. ���༶��ѯѧ����Ϣ
			case '4': QueryViaDifferWay(4); break;	// 4. ģ������
			case 27: flag = false; break;			// ESC���ص��ϸ�����
			default: break;
		}
	}
}
void Operate::QueryViaDifferWay(int i) {
	Student s;
	vector<Student> ss = ReadStudentFile();
	vector<Student>::iterator it;
	system("cls");
	cout << "\n\t\t\t �q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�����T�T�T�r" << endl;
	cout << "\t\t\t��     ѧ���ۺϲ�������ϵͳ����ѧ����Ϣ��ѯ����   ��" << endl;
	cout << "\t\t\t�t �T�T�T�����T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T �s\n" << endl;
	if (i == 1) {  //ѧ�Ų���
		cout << "\t\t\t   ������ѧ�ţ�";
		char stunum[15];
		bool flag = true;
		while (flag) {
			Read(stunum);
			for (it = ss.begin(); it != ss.end(); it++) {
				if (strcmp(stunum, (*it).stuNum) == 0) {
					flag = false;  //�ҵ���
					cout << "\t\t\t��ѧ������ϸ��Ϣ����\n" << endl;
					(*it).PrintDetail();
					cout << "\t\t\t\t\t---��ESC���˳�---" << endl;
					while (1) {
						int c = _getch();
						if (c == 27)  // ESC
							break;
					}
					break;
				}
			}
			if (flag) {	 //δ�ҵ�
				cout << "\t\t\t\tδ�ҵ���ѧ��,����������ѧ�ţ�";
			}
		}
	}
	else if (i == 2) {
		cout << "\t\t\t   ������������";
		char name[15];
		bool flag = true;
		while (flag) {
			Read(name);
			for (it = ss.begin(); it != ss.end(); it++) {
				if (strcmp(name, (*it).name) == 0) {
					flag = false;  //�ҵ��˸�ѧ��
					cout << "\t\t\t��ѧ������ϸ��Ϣ����\n" << endl;
					(*it).PrintDetail();
				}
			}
			if (flag) {	 //δ�ҵ�
				cout << "\t\t\t\tδ�ҵ���ѧ��,����������������";
			}
			else {
				cout << "\t\t\t\t\t---��ESC���˳�---" << endl;
				while (1) {
					int c = _getch();
					if (c == 27)  // ESC
						break;
				}
			}
		}
	}
	else if (i == 3) {
		cout << "\t\t\t   ������Ҫ��ѯ�İ༶��";
		char cl[15];
		bool flag = true;
		vector<Student> s1;
		Student s;
		while (flag) {
			Read(cl);
			for (it = ss.begin(); it != ss.end(); it++) {
				if (strcmp(cl, (*it).Class) == 0) {
					s = *it;
					s1.push_back(s);
					flag = false;  //�ҵ��˸ð༶ѧ��
				}
			}
			if (flag) {	 //δ�ҵ�
				cout << "\t\t\t\tδ�ҵ��ð༶ѧ��,����������༶��";
			}
			else {
				cout << "--------------------------------------�ð༶����";
				printf_s("  %-3d", s1.size());
				cout << "��ѧ��-------------------------------------\n" << endl;
				cout << "----ѧ��------����------�༶------����----��Ӣ----"
						"c����--ƽ���ɼ�--�۲��ܷ�--�ɼ�����---�۲�����\n"
					 << endl;
				for (it = s1.begin(); it != s1.end(); it++) {
					(*it).display();
					cout << endl;
				}
				cout << "\t\t\t\t\t---��ESC���˳�---" << endl;
				while (1) {
					int c = _getch();
					if (c == 27)  // ESC
						break;
				}
			}
		}
	}
	else if (i == 4) {
		bool flag = true;
		while (flag) {
			m.Menu6();
			switch (_getch()) {
				case '1': FuzzySearch(1); break;  // 1. ������ģ������
				case '2': FuzzySearch(2); break;  // 2. ��ѧ��ģ������
				case '3': FuzzySearch(3); break;  // 3. ��ȫģ������
				case 27: flag = false; break;	  // ESC���ص��ϸ�����
				default: break;
			}
		}
	}
}
void Operate::FuzzySearch(int i) {
	system("cls");
	cout << "\n\t\t\t �q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�����T�T�T�r" << endl;
	cout << "\t\t\t��     ѧ���ۺϲ�������ϵͳ����ѧ����Ϣ��ѯ����   ��" << endl;
	cout << "\t\t\t�t �T�T�T�����T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T �s\n" << endl;
	char str[15];
	Student s;
	vector<Student> ss = ReadStudentFile();
	vector<Student> s1, s2;
	vector<Student>::iterator it;
	cout << "\t\t\t   ������һ���ַ�:";
	bool flag = true;
	while (flag) {
		s1.clear();
		s2.clear();
		Read(str);
		for (it = ss.begin(); it != ss.end(); it++) {
			if (strstr((*it).name, str) && i != 2) {
				s = *it;
				flag = false;  //������ģ�����ҵ���ѧ��
				s1.push_back(s);
			}
			if (strstr((*it).stuNum, str) && i != 1) {
				s = *it;
				flag = false;  //��ѧ��ģ�����ҵ���ѧ��
				s1.push_back(s);
			}
			if ((strstr((*it).Class, str) || strstr((*it).name, str) ||
				 strstr((*it).stuNum, str)) &&
				i == 3) {
				s = *it;
				s2.push_back(s);
			}
		}
		if (flag) {	 //δ�ҵ�
			cout << "\t\tģ������δ�ҵ�ƥ���ѧ��,����������һ���ַ���";
		}
		else {
			if (i == 3)
				s1 = s2;
			cout << "--------------------------------�˴�ģ�����ҹ��ҵ�";
			printf_s("  %-3d", s1.size());
			cout << "��ѧ��-----------------------------------\n" << endl;
			cout << "----ѧ��------����------�༶------����----��Ӣ----"
					"c����--ƽ���ɼ�--�۲��ܷ�--�ɼ�����---�۲�����\n"
				 << endl;
			for (it = s1.begin(); it != s1.end(); it++) {
				(*it).display();
				cout << endl;
			}
			cout << "\t\t\t\t\t---��ESC���˳�---" << endl;
			while (1) {
				int c = _getch();
				if (c == 27)  // ESC
					break;
			}
		}
	}
}
void Operate::DisplayStuInfor(User& U) {
	system("cls");
	cout << "\n\t\t\t �q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�����T�T�T�r" << endl;
	cout << "\t\t\t��     ѧ���ۺϲ�������ϵͳ����ȫ��ѧ����Ϣչʾ   ��" << endl;
	cout << "\t\t\t�t �T�T�T�����T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T �s\n\n" << endl;
	Student s;
	vector<Student> ss = ReadStudentFile();
	sort(ss.begin(), ss.end());
	if (ss.empty())
		cout << "--------------------------------------��ǰ��δ����"
				"��ѧ��!-----------------------------------\n"
			 << endl;
	else {
		cout << "----------------------------------------��ǰ����";
		printf_s("  %-3d", ss.size());
		cout << "��ѧ��-------------------------------------\n" << endl;
		cout << "-----ѧ��------����------�༶------����----��Ӣ----c����--"
				"ƽ���ɼ�--�۲��ܷ�--�ɼ�����--�۲�����\n"
			 << endl;
	}
	vector<Student>::iterator it;
	for (it = ss.begin(); it != ss.end(); it++) {
		s = *it;
		s.display();
		cout << endl;
	}
	cout << "\t\t\t\t\t---��ESC���˳�---" << endl;
	bool flag = true;
	while (flag) {
		switch (_getch()) {
			case 27: flag = false; break;  // ESC���ص��ϸ�����
			default: break;
		}
	}
}
void Operate::DisplayUserInfor(User& U) {
	system("cls");
	cout << "\n\t\t\t �q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�����T�T�T�r" << endl;
	cout << "\t\t\t��     ѧ���ۺϲ�������ϵͳ����ȫ���û���Ϣչʾ   ��" << endl;
	cout << "\t\t\t�t �T�T�T�����T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T �s\n\n" << endl;
	User u;
	vector<User> uu = ReadUserFile();
	if (uu.empty())
		cout << "--------------------------------------��ǰ��δ����"
				"���û�!-----------------------------------\n"
			 << endl;
	else {
		cout << "----------------------------------------��ǰ����";
		printf_s("  %-3d", uu.size());
		cout << "���û�-------------------------------------\n" << endl;
		cout << "------------------------�û���--------------����--------------"
				"------Ȩ��--"
				""
				"----------------------\n"
			 << endl;
	}
	vector<User>::iterator it;
	for (it = uu.begin(); it != uu.end(); it++) {
		u = *it;
		u.PrintNandP();
		cout << endl;
	}
	cout << "\t\t\t\t\t---��ESC���˳�---" << endl;
	bool flag = true;
	while (flag) {
		switch (_getch()) {
			case 27: flag = false; break;  // ESC���ص��ϸ�����
			default: break;
		}
	}
}
void Operate::ReportPrint(User& U) {
	bool flag = true;
	while (flag) {
		m.Menu7(U.isAdmin);
		if (U.isAdmin) {
			switch (_getch()) {
				case '1': Export_File(1); break;  // 1. ����ȫ��ѧ����Ϣ
				case '2': Export_File(2); break;  // 2. ����ȫ���û���Ϣ
				case 27: flag = false; break;	  // ESC���ص��ϸ�����
				default: break;
			}
		}
		else {
			switch (_getch()) {
				case '1': Export_File(1); break;  // 1. ����ȫ��ѧ����Ϣ
				case 27: flag = false; break;	  // ESC���ص��ϸ�����
				default: break;
			}
		}
	}
}
void Operate::Export_File(int i) {
	fstream fp;
	if (i == 1) {
		fp.open(ExportStuFile, ios::out);
		vector<Student> ss = ReadStudentFile();
		vector<Student>::iterator it;
		if (fp) {
			fp << "ѧ��,����,�༶,�ߵ���ѧ�ɼ�,��ѧӢ��ɼ�,C���Գɼ�,"
				  "����ƽ���ɼ�,��������(�༶),ͬѧ������,����Ա����,"
				  "��������ʦ����,"
				  "�ۺϲ����ܷ�,�ۺϲ�������(�༶)"
			   << endl;
			for (it = ss.begin(); it != ss.end(); it++) {
				Student s = *it;
				fp << s.stuNum << "," << s.name << "," << s.Class << ",";
				for (int i = 0; i < 3; i++)
					fp << s.examGrade[i] << ",";
				fp << s.avrGrade << "," << s.examRank << ",";
				for (int i = 0; i < 3; i++)
					fp << s.givenMark[i] << ",";
				fp << s.multiGrade << "," << s.multiGradeRank << endl;
			}
			cout << "\n\t\t\t\t������ϣ�";
			Sleep(500);
		}
		else {
			cout << "�ļ���ʧ�ܣ�" << endl;
		}
	}
	else if (i == 2) {
		fp.open(ExportUserFile, ios::out);
		vector<User> uu = ReadUserFile();
		vector<User>::iterator it;
		if (fp) {
			fp << "�û���,����,Ȩ��" << endl;
			for (it = uu.begin(); it != uu.end(); it++) {
				User u = *it;
				fp << u.userName << "," << u.passWord << ",";
				if (u.isAdmin)
					fp << "����Ա" << endl;
				else
					fp << "�û�" << endl;
			}
			cout << "\n\t\t\t\t������ϣ�";
			Sleep(500);
		}
		else {
			cout << "�ļ���ʧ�ܣ�" << endl;
		}
	}
	fp.close();
}
void Operate::ChangePassWord(User& U) {
	vector<User> u = ReadUserFile();
	vector<User>::iterator it;
	system("cls");
	cout << "\n\t\t\t �q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�����T�T�T�r" << endl;
	cout << "\t\t\t��       ѧ���ۺϲ�������ϵͳ�����û������޸�\t ��" << endl;
	cout << "\t\t\t�t �T�T�T�����T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T �s\n\n" << endl;
	if (U.isAdmin) {  //����Ա���Ը��������û����˺�����
		User temp;
		cout << "\t\t\t����Ա�ɸ��������û�������,�����û������ɸ���������:";
		char un[15], pw[15];
		bool flag = true;
		while (flag) {
			Read(un);
			for (it = u.begin(); it != u.end(); it++) {
				if (strcmp(un, (*it).userName) == 0) {
					flag = false;
					cout << "\t\t\t\t �����������룺";
					char pw[15];
					Read(pw);
					(*it).changePassWord(pw);
					cout << "\t\t\t\t  �޸ĳɹ���" << endl;
					Sleep(500);
				}
			}
			if (flag) {
				cout << "\t\t\t\tδ�ҵ����û�,�����������û�����";
			}
		}
	}
	else {
		cout << "\t\t\t\t �����������룺";
		char pw[15];
		Read(pw);
		U.changePassWord(pw);
		for (it = u.begin(); it != u.end(); it++) {
			if (strcmp(U.userName, (*it).userName) == 0) {
				(*it).changePassWord(pw);
				cout << "\t\t\t\t  �޸ĳɹ���" << endl;
				Sleep(500);
			}
		}
	}
	StoreUserFile(u);
}
void Operate::ImproveVIP(User& U) {
	vector<User> u = ReadUserFile();
	vector<User>::iterator it;
	system("cls");

	cout << "\n\t\t\t �q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�����T�T�T�r" << endl;
	cout << "\t\t\t��       ѧ���ۺϲ�������ϵͳ�����û�Ȩ������     ��" << endl;
	cout << "\t\t\t�t �T�T�T�����T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T �s\n\n" << endl;
	if (U.isAdmin) {  //����Ա���Ը��������û����˺�����
		User temp;
		cout << "\t\t\t����Ա�����������û���Ȩ��,�����û�������������Ȩ��:";
		char un[15];
		bool flag = true;
		while (flag) {
			Read(un);
			for (it = u.begin(); it != u.end(); it++) {
				if (strcmp(un, (*it).userName) == 0) {
					flag = false;
					(*it).isAdmin = 1;
					cout << "\t\t\t\t  �����ɹ���" << endl;
					Sleep(500);
					break;
				}
			}
			if (flag) {
				cout << "\t\t\t\tδ�ҵ����û�,�����������û�����";
			}
		}
	}
	StoreUserFile(u);
}
void Operate::Rank_Update() {
	vector<Student> ss = ReadStudentFile();
	vector<Student> news;
	set<string> classes;
	vector<Student> vv;
	vector<Student>::iterator it;
	set<string>::iterator st;
	for (it = ss.begin(); it != ss.end(); it++) {
		string str = (*it).Class;
		classes.insert(str);
	}
	for (st = classes.begin(); st != classes.end(); st++) {//ÿ���༶
		int averank = 1;
		int mulrank = 1;
		vv.clear();
		for (it = ss.begin(); it != ss.end(); it++) {//���ð༶����ͬѧ����vv��
			if (strcmp((*st).c_str(), (*it).Class) == 0 ) {  //ͬ��ͬѧ
				vv.push_back(*it);
			}
		}
		sort(vv.begin(), vv.end(), cmp_exam);//�����Գɼ�����
		for (it = vv.begin(); it != vv.end(); it++) {
			(*it).examRank = averank;
			averank++;
		}
		sort(vv.begin(), vv.end(), cmp_multi);	//���۲�����
		for (it = vv.begin(); it != vv.end(); it++) {
			(*it).multiGradeRank = mulrank;
			news.push_back(*it);
			mulrank++;
		}

	}
	sort(news.begin(), news.end());
	StoreStudentFile(news);
}
vector<Student> Operate::ReadStudentFile() {
	Student s;
	fstream fp;
	vector<Student> ss;
	fp.open(StudentFile, ios::in | ios::binary);
	while (fp.read((char*)&s, sizeof(s))) {	 //����֮ǰ����ѧ����Ϣ
		ss.push_back(s);
	}
	fp.close();
	return ss;
}
vector<User> Operate::ReadUserFile() {
	User u;
	fstream fp;
	vector<User> uu;
	fp.open(UserFileName, ios::in | ios::binary);
	while (fp.read((char*)&u, sizeof(u))) {	 //����֮ǰ����ѧ����Ϣ
		uu.push_back(u);
	}
	fp.close();
	return uu;
}
