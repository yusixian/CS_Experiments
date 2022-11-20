#include "Student.h"
Menus m;


void Student::InputInfor() {
	cout << "\t\t\t   请输入该学生基本信息,以空格间隔\n" << endl;
	cout << "\t\t\t   学号、姓名、班级:";
	scanf_s("%s %s %s", stuNum, 14, name, 14, Class, 14);
	getchar();
	cout << endl;
	cout << "\t\t\t   三门课程（高等数学、大学英语和C语言）的成绩:";
	double sum = 0;
	for (int i = 0; i < 3; i++) {
		cin >> examGrade[i];
		sum += examGrade[i];
	}
	cout << endl;
	avrGrade = sum / 3.0;
	sum = 0;
	cout << "\t\t\t   同学互评分、辅导员评分、班主任老师评分：";
	for (int i = 0; i < 3; i++) {
		cin >> givenMark[i];
		sum += givenMark[i];
	}
	cout << endl;
	multiGrade = avrGrade * 0.7 + sum * 0.1;
}

void Student::display() {
	printf_s(" %-14s%-10s%-10s", stuNum, name, Class);
	for (int i = 0; i < 3; i++) {
		printf_s("%-8.2f", examGrade[i]);
	}
	printf_s("%-10.2f%-12.2f%-11d%-3d", avrGrade, multiGrade, examRank,
			 multiGradeRank);
	cout << endl;
}

void Student::PrintDetail() {
	printf_s("\t\t\t学号:%-15s 姓名:%-10s 班级:%-10s\n\n", stuNum, name, Class);
	printf_s("\t\t\t高等数学:%-8.2f 大学英语:%-8.2f c语言:%-8.2f\n\n", examGrade[0],
			 examGrade[1], examGrade[2]);
	printf_s("\t\t\t考试平均成绩:%-8.2f 考试名次（班级）:%-4d\n\n", avrGrade, examRank);
	printf_s("\t\t\t同学互评分:%-8.2f 辅导员评分:%-8.2f 班主任老师评分:%-8.2f\n\n",
			 givenMark[0], givenMark[1], givenMark[2]);
	printf_s("\t\t\t综合测评总分:%-8.2f 综合测评名次（班级）:%-4d\n\n", multiGrade,
			 multiGradeRank);
}

void Student::Change() {
	bool flag = true;
	while (flag) {
		m.Menu3();
		switch (_getch()) {
			case '1': Change_Name(); break;	  // 1. 修改学生姓名
			case '2': Change_Class(); break;  // 2. 修改学生班级
			case '3': Change_Grade(); break;  // 3. 修改学生成绩
			case 27: flag = false; break;	  // ESC，回到上个界面
			default: break;
		}
	}
}

void Student::Change_Name() {
	system("cls");
	cout << "\n\t\t\t ╭═══════════════════════════════════○●○●═══╮" << endl;
	cout << "\t\t\t│     学生综合测评管理系统——学生信息修改界面   │" << endl;
	cout << "\t\t\t╰ ═══○●○●═══════════════════════════════════ ╯\n" << endl;
	cout << "\t\t\t   请输入新名字:";
	scanf_s("%s", name, 14);
	cout << "\n\t\t\t\t修改完成！\n" << endl;
	Sleep(500);
}

void Student::Change_Class() {
	system("cls");
	cout << "\n\t\t\t ╭═══════════════════════════════════○●○●═══╮" << endl;
	cout << "\t\t\t│     学生综合测评管理系统——学生信息修改界面   │" << endl;
	cout << "\t\t\t╰ ═══○●○●═══════════════════════════════════ ╯\n" << endl;
	cout << "\t\t\t   请输入新班级:";
	scanf_s("%s", Class, 14);
	cout << "\n\t\t\t\t修改完成！\n" << endl;
	Sleep(500);
}

void Student::Change_Grade() {
	bool flag = true;

	while (flag) {
		int num = 0;
		m.Menu4();
		switch (_getch()) {
			case '1': num = 1; break;	   // 1. 修改高等数学成绩
			case '2': num = 2; break;	   // 2. 修改大学英语成绩
			case '3': num = 3; break;	   // 3. 修改c语言成绩
			case '4': num = 4; break;	   // 4. 修改同学互评分
			case '5': num = 5; break;	   // 5. 修改辅导员评分
			case '6': num = 6; break;	   // 6. 修改班主任评分
			case 27: flag = false; break;  // ESC，回到上个界面
			default: break;
		}
		if (num != 0) {
			system("cls");
			cout << "\n\t\t\t ╭═══════════════════════════════════○●○●═══╮"
				 << endl;
			cout << "\t\t\t│     学生综合测评管理系统——学生信息修改界面   │"
				 << endl;
			cout << "\t\t\t╰ ═══○●○●═══════════════════════════════════ ╯\n"
				 << endl;
			cout << "\t\t\t   请输入新的分数:";
			switch (num) {
				case 1: cin >> examGrade[0]; break;	 // 1. 修改高等数学成绩
				case 2: cin >> examGrade[1]; break;	 // 2. 修改大学英语成绩
				case 3: cin >> examGrade[2]; break;	 // 3. 修改c语言成绩
				case 4: cin >> givenMark[0]; break;	 // 4. 修改同学互评分
				case 5: cin >> givenMark[1]; break;	 // 5. 修改辅导员评分
				case 6: cin >> givenMark[2]; break;	 // 6. 修改班主任评分
			}
			double sum = 0;
			for (int i = 0; i < 3; i++)
				sum += examGrade[i];
			avrGrade = sum / 3.0;
			sum = 0;
			for (int i = 0; i < 3; i++)
				sum += givenMark[i];
			multiGrade = avrGrade * 0.7 + sum * 0.1;
			cout << "\n\t\t\t\t修改完成！\n" << endl;
			Sleep(500);
		}
	}
}

bool Student::operator<(Student& s) {
	return strcmp(stuNum, s.stuNum) < 0;
}
