#include "User.h"

void User::changeUserName(char* s) {
	strncpy(userName, s, 15);
}
void User::changePassWord(char *s) {
	strncpy(passWord, s, 15);
}

void User::PrintNandP() {
	printf_s("\t\t\t%-20s%-20s", userName, passWord);
	if (isAdmin) {
		cout << "    管理员" << endl;
	}
	else
		cout << "    普通用户" << endl;
}
