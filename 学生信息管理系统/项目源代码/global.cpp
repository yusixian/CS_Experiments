#include "global.h"
fstream fS;
Menus menus;
User U;
Operate O;
bool cmp_exam(const Student& a, const Student& b) {
	return a.avrGrade > b.avrGrade;
}
bool cmp_multi(const Student& a, const Student& b) {
	return a.multiGrade > b.multiGrade;
}
bool Login() {
	system("cls");
	vector<User> uu = O.ReadUserFile();
	vector<User>::iterator it;
	char un[15], pw[15];
	cout << "\n\t\t\t ╭═══════════════════════════════════○●○●═══╮" << endl;
	cout << "\t\t\t│    学生综合测评管理系统————登录界面        │" << endl;
	cout << "\t\t\t╰ ═══○●○●═══════════════════════════════════ ╯\n\n" << endl;
	cout << "\t\t\t\t 请输入账号（最长14位）:";
	O.Read(un);
	cout << "\t\t\t\t 请输入密码（最长14位）:";
	O.Read(pw);
	getchar();
	cout << endl;
	for (it = uu.begin(); it != uu.end(); it++) {
		U = *it;
		if (strcmp(un, U.userName) == 0 && strcmp(pw, U.passWord) == 0) {
			return true;
		}
	}
	return false;
}
void Register(int i) {	// 0为普通用户注册，1为管理员注册
	char un[15], pw[15];
	vector<User> uu = O.ReadUserFile();
	vector<User>::iterator it;
	if (i == 0) {  //普通用户注册
		system("cls");
		cout << "\n\t\t\t ╭═══════════════════════════════════○●○●═══╮" << endl;
		cout << "\t\t\t│    学生综合测评管理系统————注册界面        │" << endl;
		cout << "\t\t\t╰ ═══○●○●═══════════════════════════════════ ╯\n"
			 << endl;
		User U1(0);
		cout << "\t\t\t\t 请输入账号（最长14位）:";
		O.Read(un);
		bool flag = true;//账号是否重复
		while (flag) {
			bool k = false;
			for (it = uu.begin(); it != uu.end(); it++) {
				U = *it;
				if (strcmp(un, U.userName) == 0) {
					flag = true;
					cout << "\t\t\t 账号已存在,请重新输入账号（最长14位）:";
					O.Read(un);
					k = true;
					break;
				}
			}
			if (!k)//如果是结束循环出来的，说明账号不再重复了
				flag = false;
		}
		U1.changeUserName(un);
		cout << "\t\t\t\t 请输入密码（最长14位）:";
		O.Read(pw);
		U1.changePassWord(pw);
		printf("\t\t\t\t 您的账号为:%s\n\n", un);
		printf("\t\t\t\t 您的密码为:%s\n\n", pw);
		uu.push_back(U1);
	}  else {	//管理员注册
		User M(1);
		cout << "\t\t\t\t 输入管理员账号（最长14位）:";
		O.Read(un);
		M.changeUserName(un);
		cout << "\t\t\t\t 输入管理员密码（最长14位）:";
		O.Read(pw);
		M.changePassWord(pw);
		printf("\t\t\t\t 管理员账号为:%s\n\n", un);
		printf("\t\t\t\t 管理员密码为:%s\n\n", pw);
		uu.push_back(M);
	}
	O.StoreUserFile(uu);
	cout << "\t\t\t\t注册完毕！按任意键返回上一步" << endl;
	_getch();
}
void LandR() {
	while (1) {
		menus.Menu1();	//显示登录or注册菜单
		bool flag = false;	//登录成功与否
		int c = _getch();
		if (c == 49) {	 //为1 则执行登录操作
			flag = Login();
			if (flag) {
				cout << "\t\t\t\t\t登录成功！" << endl;
				Sleep(500);
				system("cls");
				return;
			} else {//登陆失败
				cout << "\t\t\t\t登录失败,用户名或密码有误！" << endl;
				Sleep(500);
				menus.Menu1();	//显示登录or注册菜单
			}
		} else if(c == 50){ //为2 则执行注册操作
			Register();	 //普通用户注册
			menus.Menu1();
		} else if (c == 27) {//ESC退出
			exit(0);
		}
	}
}
void Init() {							  //初始化 显示登录or注册菜单
	system("mode con cols=96 lines=35");  //改变宽高
	system("color F0");			//改变控制台窗口颜色
	vector<User> uu = O.ReadUserFile();
	if (uu.empty()) {
		menus.Hint1();	//管理员注册提示
		Register(1);
	}
	LandR();
}
void MainInterface() {
	while (1) {
		menus.Menu2(U.isAdmin);
		if (U.isAdmin) {//管理员
			switch (_getch()) {
				case '1': O.AddInfor(U); break;	// 1. 添加学生信息
				case '2': O.DeleteInfor(U); break;  // 2. 删除学生信息
				case '3': O.ModifyInfor(U); break;  // 3. 修改学生信息
				case '4': O.QueryInfor(U); break;	  // 4. 查询学生信息
				case '5': O.DisplayStuInfor(U); break;	// 5. 显示全部学生信息
				case '6': O.DisplayUserInfor(U); break;	 // 6. 显示全部用户信息
				case '7': O.ReportPrint(U); break;	 // 7. 导出全部信息
				case '8': O.ChangePassWord(U); break;	 // 8. 修改用户密码
				case '9': O.ImproveVIP(U); break;  // 9. 提升普通用户权限
				case 27: Init(); break;	 // ESC，回到上个界面
				default: break;
			}
		} else {//普通用户
			switch (_getch()) {
				case '1': O.ChangePassWord(U); break;	 // 1. 修改用户密码
				case '2': O.QueryInfor(U); break;		 // 2. 查询学生信息
				case '3': O.DisplayStuInfor(U); break;	// 3. 显示全部学生信息
				case '4': O.ReportPrint(U); break;	 // 4. 导出全部信息
				case 27: Init(); break; // ESC，回到上个界面
				default: break;
			}
		}
	}
}