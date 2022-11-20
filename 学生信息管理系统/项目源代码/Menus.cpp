#include "Menus.h"
void Menus::Hint1() {
	system("cls");
	cout << "\n\t\t\t ╭═══════════════════════════════════○●○●═══╮" << endl;
	cout << "\t\t\t│\t   欢迎进入学生综合测评管理系统!         │" << endl;
	cout << "\t\t\t╰ ═══○●○●═══════════════════════════════════ ╯\n\n" << endl;
	cout << "\t\t\t      检测到还未有管理员注册，请注册管理员账号\n" << endl;
}
void Menus::Menu1() {
	system("cls");
	cout << "\n\t\t\t ╭═══════════════════════════════════○●○●═══╮" << endl;
	cout << "\t\t\t│\t   欢迎进入学生综合测评管理系统!         │" << endl;
	cout << "\t\t\t╰ ═══○●○●═══════════════════════════════════ ╯\n\n" << endl;

	cout << "\t\t\t┌───────────────────────────────────────────────┐" << endl;
	cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
	cout << "\t\t\t│\t\t    1. 登录\t\t\t│" << endl;
	cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
	cout << "\t\t\t│\t\t    2. 注册\t\t\t│" << endl;
	cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
	cout << "\t\t\t└───────────────────────────────────────────────┘" << endl;
	cout << "\t\t\t\t      输入数字执行对应操作：" << endl;
}
void Menus::Menu2(int i) {
	system("cls");
	cout << "\n\t\t\t ╭═══════════════════════════════════○●○●═══╮" << endl;
	cout << "\t\t\t│\t   欢迎进入学生综合测评管理系统!         │" << endl;
	cout << "\t\t\t╰ ═══○●○●═══════════════════════════════════ ╯\n" << endl;
	if (i == 1) {
		cout << "\t\t\t┌───────────────────────────────────────────────┐"
			 << endl;
		cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
		cout << "\t\t\t│\t  您拥有管理员权限, 可执行以下操作\t│" << endl;
		cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
		cout << "\t\t\t│\t\t1. 添加学生信息\t\t\t│" << endl;
		cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
		cout << "\t\t\t│\t\t2. 删除学生信息\t\t\t│" << endl;
		cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
		cout << "\t\t\t│\t\t3. 修改学生信息\t\t\t│" << endl;
		cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
		cout << "\t\t\t│\t\t4. 查询学生信息\t\t\t│" << endl;
		cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
		cout << "\t\t\t│\t\t5. 显示全部学生信息\t\t│" << endl;
		cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
		cout << "\t\t\t│\t\t6. 显示全部用户信息\t\t│" << endl;
		cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
		cout << "\t\t\t│\t\t7. 导出全部信息\t\t\t│" << endl;
		cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
		cout << "\t\t\t│\t\t8. 修改用户密码\t\t\t│" << endl;
		cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
		cout << "\t\t\t│\t\t9. 提升普通用户权限\t\t│" << endl;
		cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
		cout << "\t\t\t└───────────────────────────────────────────────┘"
			 << endl;
		cout << "\t\t\t\t      输入数字执行对应操作：" << endl;
	}
	else {
		cout << "\t\t\t┌───────────────────────────────────────────────┐"
			 << endl;
		cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
		cout << "\t\t\t│\t   您为普通用户, 可执行以下操作\t\t│" << endl;
		cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
		cout << "\t\t\t│\t\t1. 修改密码\t\t\t│" << endl;
		cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
		cout << "\t\t\t│\t\t2. 查询学生信息\t\t\t│" << endl;
		cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
		cout << "\t\t\t│\t\t3. 显示全部学生信息\t\t│" << endl;
		cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
		cout << "\t\t\t│\t\t4. 导出全部信息\t\t\t│" << endl;
		cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
		cout << "\t\t\t└───────────────────────────────────────────────┘"
			 << endl;
		cout << "\t\t\t\t      输入数字执行对应操作：" << endl;
	}
}

void Menus::Menu3() {
	system("cls");
	cout << "\n\t\t\t ╭═══════════════════════════════════○●○●═══╮" << endl;
	cout << "\t\t\t│     学生综合测评管理系统——学生信息修改界面   │" << endl;
	cout << "\t\t\t╰ ═══○●○●═══════════════════════════════════ ╯\n" << endl;
	cout << "\t\t\t┌───────────────────────────────────────────────┐" << endl;
	cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
	cout << "\t\t\t│      您拥有管理员权限,可修改该学生以下信息\t│" << endl;
	cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
	cout << "\t\t\t│\t\t1. 修改学生姓名\t\t\t│" << endl;
	cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
	cout << "\t\t\t│\t\t2. 修改学生班级\t\t\t│" << endl;
	cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
	cout << "\t\t\t│\t\t3. 修改学生成绩\t\t\t│" << endl;
	cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
	cout << "\t\t\t└───────────────────────────────────────────────┘" << endl;
	cout << "\t\t\t\t      输入数字执行对应操作：" << endl;
}

void Menus::Menu4() {
	system("cls");
	cout << "\n\t\t\t ╭═══════════════════════════════════○●○●═══╮" << endl;
	cout << "\t\t\t│     学生综合测评管理系统——学生信息修改界面   │" << endl;
	cout << "\t\t\t╰ ═══○●○●═══════════════════════════════════ ╯\n" << endl;
	cout << "\t\t\t┌───────────────────────────────────────────────┐" << endl;
	cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
	cout << "\t\t\t│      您拥有管理员权限,可修改该学生以下成绩\t│" << endl;
	cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
	cout << "\t\t\t│\t\t1. 修改高等数学成绩\t\t│" << endl;
	cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
	cout << "\t\t\t│\t\t2. 修改大学英语成绩\t\t│" << endl;
	cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
	cout << "\t\t\t│\t\t3. 修改c语言成绩\t\t│" << endl;
	cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
	cout << "\t\t\t│\t\t4. 修改同学互评分\t\t│" << endl;
	cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
	cout << "\t\t\t│\t\t5. 修改辅导员评分\t\t│" << endl;
	cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
	cout << "\t\t\t│\t\t6. 修改班主任评分\t\t│" << endl;
	cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
	cout << "\t\t\t└───────────────────────────────────────────────┘" << endl;
	cout << "\t\t\t\t      输入数字执行对应操作：" << endl;
}

void Menus::Menu5() {
	system("cls");
	cout << "\n\t\t\t ╭═══════════════════════════════════○●○●═══╮" << endl;
	cout << "\t\t\t│     学生综合测评管理系统——学生信息查询界面   │" << endl;
	cout << "\t\t\t╰ ═══○●○●═══════════════════════════════════ ╯\n" << endl;
	cout << "\t\t\t┌───────────────────────────────────────────────┐" << endl;
	cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
	cout << "\t\t\t│\t      可按以下方式查找信息\t\t│" << endl;
	cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
	cout << "\t\t\t│\t      1. 按学号查询单个学生信息\t\t│" << endl;
	cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
	cout << "\t\t\t│\t      2. 按姓名查询学生信息\t\t│" << endl;
	cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
	cout << "\t\t\t│\t      3. 按班级查询学生信息\t\t│" << endl;
	cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
	cout << "\t\t\t│\t      4. 模糊查找\t\t\t│" << endl;
	cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
	cout << "\t\t\t└───────────────────────────────────────────────┘" << endl;
	cout << "\t\t\t\t      输入数字执行对应操作：" << endl;
}

void Menus::Menu6() {
	system("cls");
	cout << "\n\t\t\t ╭═══════════════════════════════════○●○●═══╮" << endl;
	cout << "\t\t\t│     学生综合测评管理系统——学生信息查询界面   │" << endl;
	cout << "\t\t\t╰ ═══○●○●═══════════════════════════════════ ╯\n" << endl;
	cout << "\t\t\t┌───────────────────────────────────────────────┐" << endl;
	cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
	cout << "\t\t\t│\t      模糊查找(输入几个字符即可)\t│" << endl;
	cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
	cout << "\t\t\t│\t      1. 按姓名模糊查找\t\t\t│" << endl;
	cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
	cout << "\t\t\t│\t      2. 按学号模糊查找\t\t\t│" << endl;
	cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
	cout << "\t\t\t│\t      3. 完全模糊查找\t\t\t│" << endl;
	cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
	cout << "\t\t\t└───────────────────────────────────────────────┘" << endl;
	cout << "\t\t\t\t      输入数字执行对应操作：" << endl;
}

void Menus::Menu7(int i) {
	system("cls");
	

	cout << "\n\t\t\t ╭═══════════════════════════════════○●○●═══╮" << endl;
	cout << "\t\t\t│      学生综合测评管理系统——报表打印界面\t │" << endl;
	cout << "\t\t\t╰ ═══○●○●═══════════════════════════════════ ╯\n" << endl;
	if (i == 1) {
		cout << "\t\t\t┌───────────────────────────────────────────────┐" << endl;
		cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
		cout << "\t\t\t│      您拥有管理员权限,可导出以下信息\t\t│" << endl;
		cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
		cout << "\t\t\t│\t      1. 导出全部学生信息\t\t│" << endl;
		cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
		cout << "\t\t\t│\t      2. 导出全部用户信息\t\t│" << endl;
		cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
		cout << "\t\t\t└───────────────────────────────────────────────┘" << endl;
		cout << "\t\t\t\t      输入数字执行对应操作：" << endl;
	}
	else {
		cout << "\t\t\t┌───────────────────────────────────────────────┐"
			 << endl;
		cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
		cout << "\t\t\t│\t      您为普通用户,可导出以下信息\t│" << endl;
		cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
		cout << "\t\t\t│\t      1. 导出全部学生信息\t\t│" << endl;
		cout << "\t\t\t│\t\t\t\t\t\t│" << endl;
		cout << "\t\t\t└───────────────────────────────────────────────┘"
			 << endl;
		cout << "\t\t\t\t      输入数字执行对应操作：" << endl;
	}
	
}
