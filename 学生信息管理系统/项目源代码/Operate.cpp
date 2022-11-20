#include "Operate.h"
void Operate::Read(char* s) {
	string str;
	cin >> str;
	cout << endl;
	while (str.size() >= 15) {
		str.erase();
		cout << "\t\t\t\t 长度过长，请重新输入:";
		cin >> str;
		cout << endl;
	}
	strcpy(s, str.c_str());
}
void Operate::StoreStudentFile(vector<Student> ss) {
	Student s;
	fstream of;
	of.open(StudentFile, ios::out | ios::binary);  //以二进制形式
	vector<Student>::iterator it;
	for (it = ss.begin(); it != ss.end(); it++) {
		s = *it;
		of.write((char*)&s, sizeof(s));	 //存入文件
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
		of.write((char*)&u, sizeof(u));	 //存入文件
	}
	of.close();
}
void Operate::AddInfor(User& U) {
	Student s1, s;
	system("cls");
	cout << "\n\t\t\t ╭═══════════════════════════════════○●○●═══╮" << endl;
	cout << "\t\t\t│     学生综合测评管理系统——学生信息添加界面   │" << endl;
	cout << "\t\t\t╰ ═══○●○●═══════════════════════════════════ ╯\n" << endl;
	char stunum[15];
	cout << "\t\t\t   请输入要添加的学生的学号：";
	Read(stunum);
	vector<Student> ss = ReadStudentFile();
	vector<Student>::iterator it;
	//确保文件中之前没有这个学生的信息（学号唯一）
	bool flag = true;  //是否需要再检测一轮
	while (flag) {
		bool k = false;	 //是否有重复
		for (it = ss.begin(); it != ss.end(); it++) {
			s = *it;
			if (strcmp(stunum, s.stuNum) == 0) {  //学号有重复的
				flag = true;
				cout << "\t\t\t该学生信息已存在,请重新输入要添加的学生的学号:";
				Read(stunum);
				k = true;
				break;
			}
		}
		if (!k)	 //如果是结束循环出来的，说明学号不再重复了
			flag = false;
	}
	s1.InputInfor();  //输入信息
	ss.push_back(s1);
	StoreStudentFile(ss);
	Rank_Update();  //更新排名
	cout << "\t\t\t\t---添加完毕！按任意键返回上一步---" << endl;
	_getch();
}
void Operate::DeleteInfor(User& U) {
	Student s;
	vector<Student> ss = ReadStudentFile();
	vector<Student>::iterator it;
	char stunum[15];
	system("cls");
	cout << "\n\t\t\t ╭═══════════════════════════════════○●○●═══╮" << endl;
	cout << "\t\t\t│     学生综合测评管理系统——学生信息删除界面   │" << endl;
	cout << "\t\t\t╰ ═══○●○●═══════════════════════════════════ ╯\n" << endl;
	cout << "\t\t\t   请输入要删除的学生的学号：";
	bool flag = true;
	while (flag) {
		Read(stunum);
		for (it = ss.begin(); it != ss.end(); it++) {
			s = (*it);
			if (strcmp(stunum, s.stuNum) == 0) {
				flag = false;  //找到了要删除的学生
				cout << "\t\t\t\t要删除的学生的信息如下\n" << endl;
				cout << "-----学号------姓名------班级------高数----大英----"
						"c语言--平均成绩--综测总分--成绩排名--综测排名\n"
					 << endl;
				s.display();
				cout << "\n\t\t\t---确认要删除吗？按ESC取消删除,按回车确定删除-"
						"--"
					 << endl;
				int c = _getch();
				if (c == 27) {	// ESC
					break;
				}
				else {
					it = ss.erase(it);
					cout << "\n\t\t\t\t删除完成！\n" << endl;
					Sleep(500);
					break;
				}
			}
		}
		if (flag) {	 //未找到
			cout << "\t\t\t\t未找到该学生,请重新输入学号：";
		}
	}
	//删除完毕，重新存入文件
	StoreStudentFile(ss);
	Rank_Update();
}
void Operate::ModifyInfor(User& U) {
	system("cls");
	cout << "\n\t\t\t ╭═══════════════════════════════════○●○●═══╮" << endl;
	cout << "\t\t\t│     学生综合测评管理系统——学生信息修改界面   │" << endl;
	cout << "\t\t\t╰ ═══○●○●═══════════════════════════════════ ╯\n" << endl;
	cout << "\t\t\t   请输入要修改学生的学号:";
	vector<Student> ss = ReadStudentFile();
	vector<Student>::iterator it;
	char stunum[15];
	bool flag = true;
	while (flag) {
		Read(stunum);
		for (it = ss.begin(); it != ss.end(); it++) {
			if (strcmp(stunum, (*it).stuNum) == 0) {
				flag = false;  //找到了要修改的学生
				cout << "\t\t\t   要修改的学生的信息如下\n" << endl;
				cout << "-----学号------姓名------班级------高数----大英----"
						"c语言--平均成绩--综测总分--成绩排名--综测排名\n"
					 << endl;
				(*it).display();
				cout << endl;
				cout << "\t\t\t---"
						"确认要修改吗？按ESC可退出，按其他任意键可进入下一步---"
					 << endl;
				int c = _getch();
				if (c == 27) {	// ESC
					break;
				}
				else {	//回车
					(*it).Change();
					Sleep(500);
					break;
				}
			}
		}
		if (flag) {	 //未找到
			cout << "\t\t\t\t未找到该学生,请重新输入学号：";
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
			case '1': QueryViaDifferWay(1); break;	// 1. 按学号查询单个学生信息
			case '2': QueryViaDifferWay(2); break;	// 2. 按姓名查询学生信息
			case '3': QueryViaDifferWay(3); break;	// 3. 按班级查询学生信息
			case '4': QueryViaDifferWay(4); break;	// 4. 模糊查找
			case 27: flag = false; break;			// ESC，回到上个界面
			default: break;
		}
	}
}
void Operate::QueryViaDifferWay(int i) {
	Student s;
	vector<Student> ss = ReadStudentFile();
	vector<Student>::iterator it;
	system("cls");
	cout << "\n\t\t\t ╭═══════════════════════════════════○●○●═══╮" << endl;
	cout << "\t\t\t│     学生综合测评管理系统——学生信息查询界面   │" << endl;
	cout << "\t\t\t╰ ═══○●○●═══════════════════════════════════ ╯\n" << endl;
	if (i == 1) {  //学号查找
		cout << "\t\t\t   请输入学号：";
		char stunum[15];
		bool flag = true;
		while (flag) {
			Read(stunum);
			for (it = ss.begin(); it != ss.end(); it++) {
				if (strcmp(stunum, (*it).stuNum) == 0) {
					flag = false;  //找到了
					cout << "\t\t\t该学生的详细信息如下\n" << endl;
					(*it).PrintDetail();
					cout << "\t\t\t\t\t---按ESC可退出---" << endl;
					while (1) {
						int c = _getch();
						if (c == 27)  // ESC
							break;
					}
					break;
				}
			}
			if (flag) {	 //未找到
				cout << "\t\t\t\t未找到该学生,请重新输入学号：";
			}
		}
	}
	else if (i == 2) {
		cout << "\t\t\t   请输入姓名：";
		char name[15];
		bool flag = true;
		while (flag) {
			Read(name);
			for (it = ss.begin(); it != ss.end(); it++) {
				if (strcmp(name, (*it).name) == 0) {
					flag = false;  //找到了该学生
					cout << "\t\t\t该学生的详细信息如下\n" << endl;
					(*it).PrintDetail();
				}
			}
			if (flag) {	 //未找到
				cout << "\t\t\t\t未找到该学生,请重新输入姓名：";
			}
			else {
				cout << "\t\t\t\t\t---按ESC可退出---" << endl;
				while (1) {
					int c = _getch();
					if (c == 27)  // ESC
						break;
				}
			}
		}
	}
	else if (i == 3) {
		cout << "\t\t\t   请输入要查询的班级：";
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
					flag = false;  //找到了该班级学生
				}
			}
			if (flag) {	 //未找到
				cout << "\t\t\t\t未找到该班级学生,请重新输入班级：";
			}
			else {
				cout << "--------------------------------------该班级共有";
				printf_s("  %-3d", s1.size());
				cout << "名学生-------------------------------------\n" << endl;
				cout << "----学号------姓名------班级------高数----大英----"
						"c语言--平均成绩--综测总分--成绩排名---综测排名\n"
					 << endl;
				for (it = s1.begin(); it != s1.end(); it++) {
					(*it).display();
					cout << endl;
				}
				cout << "\t\t\t\t\t---按ESC可退出---" << endl;
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
				case '1': FuzzySearch(1); break;  // 1. 按姓名模糊查找
				case '2': FuzzySearch(2); break;  // 2. 按学号模糊查找
				case '3': FuzzySearch(3); break;  // 3. 完全模糊查找
				case 27: flag = false; break;	  // ESC，回到上个界面
				default: break;
			}
		}
	}
}
void Operate::FuzzySearch(int i) {
	system("cls");
	cout << "\n\t\t\t ╭═══════════════════════════════════○●○●═══╮" << endl;
	cout << "\t\t\t│     学生综合测评管理系统——学生信息查询界面   │" << endl;
	cout << "\t\t\t╰ ═══○●○●═══════════════════════════════════ ╯\n" << endl;
	char str[15];
	Student s;
	vector<Student> ss = ReadStudentFile();
	vector<Student> s1, s2;
	vector<Student>::iterator it;
	cout << "\t\t\t   请输入一串字符:";
	bool flag = true;
	while (flag) {
		s1.clear();
		s2.clear();
		Read(str);
		for (it = ss.begin(); it != ss.end(); it++) {
			if (strstr((*it).name, str) && i != 2) {
				s = *it;
				flag = false;  //按姓名模糊查找到了学生
				s1.push_back(s);
			}
			if (strstr((*it).stuNum, str) && i != 1) {
				s = *it;
				flag = false;  //按学号模糊查找到了学生
				s1.push_back(s);
			}
			if ((strstr((*it).Class, str) || strstr((*it).name, str) ||
				 strstr((*it).stuNum, str)) &&
				i == 3) {
				s = *it;
				s2.push_back(s);
			}
		}
		if (flag) {	 //未找到
			cout << "\t\t模糊查找未找到匹配的学生,请重新输入一串字符：";
		}
		else {
			if (i == 3)
				s1 = s2;
			cout << "--------------------------------此次模糊查找共找到";
			printf_s("  %-3d", s1.size());
			cout << "名学生-----------------------------------\n" << endl;
			cout << "----学号------姓名------班级------高数----大英----"
					"c语言--平均成绩--综测总分--成绩排名---综测排名\n"
				 << endl;
			for (it = s1.begin(); it != s1.end(); it++) {
				(*it).display();
				cout << endl;
			}
			cout << "\t\t\t\t\t---按ESC可退出---" << endl;
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
	cout << "\n\t\t\t ╭═══════════════════════════════════○●○●═══╮" << endl;
	cout << "\t\t\t│     学生综合测评管理系统——全部学生信息展示   │" << endl;
	cout << "\t\t\t╰ ═══○●○●═══════════════════════════════════ ╯\n\n" << endl;
	Student s;
	vector<Student> ss = ReadStudentFile();
	sort(ss.begin(), ss.end());
	if (ss.empty())
		cout << "--------------------------------------当前暂未有任"
				"何学生!-----------------------------------\n"
			 << endl;
	else {
		cout << "----------------------------------------当前共有";
		printf_s("  %-3d", ss.size());
		cout << "名学生-------------------------------------\n" << endl;
		cout << "-----学号------姓名------班级------高数----大英----c语言--"
				"平均成绩--综测总分--成绩排名--综测排名\n"
			 << endl;
	}
	vector<Student>::iterator it;
	for (it = ss.begin(); it != ss.end(); it++) {
		s = *it;
		s.display();
		cout << endl;
	}
	cout << "\t\t\t\t\t---按ESC可退出---" << endl;
	bool flag = true;
	while (flag) {
		switch (_getch()) {
			case 27: flag = false; break;  // ESC，回到上个界面
			default: break;
		}
	}
}
void Operate::DisplayUserInfor(User& U) {
	system("cls");
	cout << "\n\t\t\t ╭═══════════════════════════════════○●○●═══╮" << endl;
	cout << "\t\t\t│     学生综合测评管理系统——全部用户信息展示   │" << endl;
	cout << "\t\t\t╰ ═══○●○●═══════════════════════════════════ ╯\n\n" << endl;
	User u;
	vector<User> uu = ReadUserFile();
	if (uu.empty())
		cout << "--------------------------------------当前暂未有任"
				"何用户!-----------------------------------\n"
			 << endl;
	else {
		cout << "----------------------------------------当前共有";
		printf_s("  %-3d", uu.size());
		cout << "名用户-------------------------------------\n" << endl;
		cout << "------------------------用户名--------------密码--------------"
				"------权限--"
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
	cout << "\t\t\t\t\t---按ESC可退出---" << endl;
	bool flag = true;
	while (flag) {
		switch (_getch()) {
			case 27: flag = false; break;  // ESC，回到上个界面
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
				case '1': Export_File(1); break;  // 1. 导出全部学生信息
				case '2': Export_File(2); break;  // 2. 导出全部用户信息
				case 27: flag = false; break;	  // ESC，回到上个界面
				default: break;
			}
		}
		else {
			switch (_getch()) {
				case '1': Export_File(1); break;  // 1. 导出全部学生信息
				case 27: flag = false; break;	  // ESC，回到上个界面
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
			fp << "学号,姓名,班级,高等数学成绩,大学英语成绩,C语言成绩,"
				  "考试平均成绩,考试名次(班级),同学互评分,辅导员评分,"
				  "班主任老师评分,"
				  "综合测评总分,综合测评名次(班级)"
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
			cout << "\n\t\t\t\t导出完毕！";
			Sleep(500);
		}
		else {
			cout << "文件打开失败！" << endl;
		}
	}
	else if (i == 2) {
		fp.open(ExportUserFile, ios::out);
		vector<User> uu = ReadUserFile();
		vector<User>::iterator it;
		if (fp) {
			fp << "用户名,密码,权限" << endl;
			for (it = uu.begin(); it != uu.end(); it++) {
				User u = *it;
				fp << u.userName << "," << u.passWord << ",";
				if (u.isAdmin)
					fp << "管理员" << endl;
				else
					fp << "用户" << endl;
			}
			cout << "\n\t\t\t\t导出完毕！";
			Sleep(500);
		}
		else {
			cout << "文件打开失败！" << endl;
		}
	}
	fp.close();
}
void Operate::ChangePassWord(User& U) {
	vector<User> u = ReadUserFile();
	vector<User>::iterator it;
	system("cls");
	cout << "\n\t\t\t ╭═══════════════════════════════════○●○●═══╮" << endl;
	cout << "\t\t\t│       学生综合测评管理系统——用户密码修改\t │" << endl;
	cout << "\t\t\t╰ ═══○●○●═══════════════════════════════════ ╯\n\n" << endl;
	if (U.isAdmin) {  //管理员可以更改所有用户的账号密码
		User temp;
		cout << "\t\t\t管理员可更改任意用户的密码,输入用户名即可更改其密码:";
		char un[15], pw[15];
		bool flag = true;
		while (flag) {
			Read(un);
			for (it = u.begin(); it != u.end(); it++) {
				if (strcmp(un, (*it).userName) == 0) {
					flag = false;
					cout << "\t\t\t\t 请输入新密码：";
					char pw[15];
					Read(pw);
					(*it).changePassWord(pw);
					cout << "\t\t\t\t  修改成功！" << endl;
					Sleep(500);
				}
			}
			if (flag) {
				cout << "\t\t\t\t未找到该用户,请重新输入用户名：";
			}
		}
	}
	else {
		cout << "\t\t\t\t 请输入新密码：";
		char pw[15];
		Read(pw);
		U.changePassWord(pw);
		for (it = u.begin(); it != u.end(); it++) {
			if (strcmp(U.userName, (*it).userName) == 0) {
				(*it).changePassWord(pw);
				cout << "\t\t\t\t  修改成功！" << endl;
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

	cout << "\n\t\t\t ╭═══════════════════════════════════○●○●═══╮" << endl;
	cout << "\t\t\t│       学生综合测评管理系统——用户权限提升     │" << endl;
	cout << "\t\t\t╰ ═══○●○●═══════════════════════════════════ ╯\n\n" << endl;
	if (U.isAdmin) {  //管理员可以更改所有用户的账号密码
		User temp;
		cout << "\t\t\t管理员可提升任意用户的权限,输入用户名即可提升其权限:";
		char un[15];
		bool flag = true;
		while (flag) {
			Read(un);
			for (it = u.begin(); it != u.end(); it++) {
				if (strcmp(un, (*it).userName) == 0) {
					flag = false;
					(*it).isAdmin = 1;
					cout << "\t\t\t\t  提升成功！" << endl;
					Sleep(500);
					break;
				}
			}
			if (flag) {
				cout << "\t\t\t\t未找到该用户,请重新输入用户名：";
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
	for (st = classes.begin(); st != classes.end(); st++) {//每个班级
		int averank = 1;
		int mulrank = 1;
		vv.clear();
		for (it = ss.begin(); it != ss.end(); it++) {//将该班级所有同学放入vv中
			if (strcmp((*st).c_str(), (*it).Class) == 0 ) {  //同班同学
				vv.push_back(*it);
			}
		}
		sort(vv.begin(), vv.end(), cmp_exam);//按考试成绩排序
		for (it = vv.begin(); it != vv.end(); it++) {
			(*it).examRank = averank;
			averank++;
		}
		sort(vv.begin(), vv.end(), cmp_multi);	//按综测排序
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
	while (fp.read((char*)&s, sizeof(s))) {	 //读出之前所有学生信息
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
	while (fp.read((char*)&u, sizeof(u))) {	 //读出之前所有学生信息
		uu.push_back(u);
	}
	fp.close();
	return uu;
}
