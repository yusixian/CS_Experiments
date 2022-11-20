#include "Menus.h"
#include <conio.h>
Menus menus;
//提示欢迎使用哈夫曼编/译码器
void Menus::Hint1() {
	cout << "\n\n\t\t\t╭═══════════════════════════════════○●○●════╮ " << endl;
	cout << "\t\t\t│\t   欢迎使用哈夫曼编/译码器!      \t│" << endl;
	cout << "\t\t\t╰ ═══○●○●══════════════════════════════════ ╯\t作者：余弦" << endl;
	cout << "________________________________________________";
	cout << "________________________________________________\n\n\n ";
}
void Menus::Hint2() {
	cout << "\t\t\t ...按任意键返回..." << endl;
	_getch();
}
//初始菜单显示
void Menus::Menu1() {
	system("cls");
	Hint1();
	cout << "\t\t┌───────────────────────────────────────────────────────────────┐" << endl;
	cout << "\t\t│\t\t\t\t\t\t\t\t│" << endl;
	cout << "\t\t│\t\t\t  1. 建立哈夫曼树\t\t\t│" << endl;
	cout << "\t\t│\t\t\t\t\t\t\t\t│" << endl;
	cout << "\t\t│\t\t\t  2. 哈夫曼编码\t\t\t\t│" << endl;
	cout << "\t\t│\t\t\t\t\t\t\t\t│" << endl;
	cout << "\t\t│\t\t\t  3. 哈夫曼译码\t\t\t\t│" << endl;
	cout << "\t\t│\t\t\t\t\t\t\t\t│" << endl;
	cout << "\t\t│\t\t\t  4. 显示译码后压缩率\t\t\t│" << endl;
	cout << "\t\t│\t\t\t\t\t\t\t\t│" << endl;
	cout << "\t\t│\t\t\t  5. 查询某字符对应编码功能\t\t│" << endl;
	cout << "\t\t│\t\t\t\t\t\t\t\t│" << endl;
	cout << "\t\t│\t\t\t  6. 展示哈夫曼树\t\t\t│" << endl;
	cout << "\t\t│\t\t\t\t\t\t\t\t│" << endl;
	cout << "\t\t│\t\t\t  7. 导出哈夫曼编码\t\t\t│" << endl;
	cout << "\t\t│\t\t\t\t\t\t\t\t│" << endl;
	cout << "\t\t│\t\t\t  8. 退出\t\t\t\t│" << endl;
	cout << "\t\t│\t\t\t\t\t\t\t\t│" << endl;
	cout << "\t\t└───────────────────────────────────────────────────────────────┘\n" << endl;
	cout << "\t\t\t\t   输入数字执行对应操作..." << endl;
}

//建立哈夫曼树二级菜单显示
void Menus::Menu2() {
	system("cls");
	Hint1();
	cout << "\t\t┌───────────────────────────────────────────────────────────────┐" << endl;
	cout << "\t\t│\t\t\t\t\t\t\t\t│" << endl;
	cout << "\t\t│\t\t1. 从终端读入字符及其权值直接建立哈夫曼树\t│" << endl;
	cout << "\t\t│\t\t\t\t\t\t\t\t│" << endl;
	cout << "\t\t│\t\t2. 读取字符文件建立最优哈夫曼树\t\t\t│" << endl;
	cout << "\t\t│\t\t\t\t\t\t\t\t│" << endl;
	cout << "\t\t└───────────────────────────────────────────────────────────────┘\n" << endl;
	cout << "\t\t\t\t   输入数字执行对应操作..." << endl;
}