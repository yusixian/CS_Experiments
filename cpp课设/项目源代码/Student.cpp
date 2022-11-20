#include "Student.h"
Menus m;


void Student::InputInfor() {
	cout << "\t\t\t   �������ѧ��������Ϣ,�Կո���\n" << endl;
	cout << "\t\t\t   ѧ�š��������༶:";
	scanf_s("%s %s %s", stuNum, 14, name, 14, Class, 14);
	getchar();
	cout << endl;
	cout << "\t\t\t   ���ſγ̣��ߵ���ѧ����ѧӢ���C���ԣ��ĳɼ�:";
	double sum = 0;
	for (int i = 0; i < 3; i++) {
		cin >> examGrade[i];
		sum += examGrade[i];
	}
	cout << endl;
	avrGrade = sum / 3.0;
	sum = 0;
	cout << "\t\t\t   ͬѧ�����֡�����Ա���֡���������ʦ���֣�";
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
	printf_s("\t\t\tѧ��:%-15s ����:%-10s �༶:%-10s\n\n", stuNum, name, Class);
	printf_s("\t\t\t�ߵ���ѧ:%-8.2f ��ѧӢ��:%-8.2f c����:%-8.2f\n\n", examGrade[0],
			 examGrade[1], examGrade[2]);
	printf_s("\t\t\t����ƽ���ɼ�:%-8.2f �������Σ��༶��:%-4d\n\n", avrGrade, examRank);
	printf_s("\t\t\tͬѧ������:%-8.2f ����Ա����:%-8.2f ��������ʦ����:%-8.2f\n\n",
			 givenMark[0], givenMark[1], givenMark[2]);
	printf_s("\t\t\t�ۺϲ����ܷ�:%-8.2f �ۺϲ������Σ��༶��:%-4d\n\n", multiGrade,
			 multiGradeRank);
}

void Student::Change() {
	bool flag = true;
	while (flag) {
		m.Menu3();
		switch (_getch()) {
			case '1': Change_Name(); break;	  // 1. �޸�ѧ������
			case '2': Change_Class(); break;  // 2. �޸�ѧ���༶
			case '3': Change_Grade(); break;  // 3. �޸�ѧ���ɼ�
			case 27: flag = false; break;	  // ESC���ص��ϸ�����
			default: break;
		}
	}
}

void Student::Change_Name() {
	system("cls");
	cout << "\n\t\t\t �q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�����T�T�T�r" << endl;
	cout << "\t\t\t��     ѧ���ۺϲ�������ϵͳ����ѧ����Ϣ�޸Ľ���   ��" << endl;
	cout << "\t\t\t�t �T�T�T�����T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T �s\n" << endl;
	cout << "\t\t\t   ������������:";
	scanf_s("%s", name, 14);
	cout << "\n\t\t\t\t�޸���ɣ�\n" << endl;
	Sleep(500);
}

void Student::Change_Class() {
	system("cls");
	cout << "\n\t\t\t �q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�����T�T�T�r" << endl;
	cout << "\t\t\t��     ѧ���ۺϲ�������ϵͳ����ѧ����Ϣ�޸Ľ���   ��" << endl;
	cout << "\t\t\t�t �T�T�T�����T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T �s\n" << endl;
	cout << "\t\t\t   �������°༶:";
	scanf_s("%s", Class, 14);
	cout << "\n\t\t\t\t�޸���ɣ�\n" << endl;
	Sleep(500);
}

void Student::Change_Grade() {
	bool flag = true;

	while (flag) {
		int num = 0;
		m.Menu4();
		switch (_getch()) {
			case '1': num = 1; break;	   // 1. �޸ĸߵ���ѧ�ɼ�
			case '2': num = 2; break;	   // 2. �޸Ĵ�ѧӢ��ɼ�
			case '3': num = 3; break;	   // 3. �޸�c���Գɼ�
			case '4': num = 4; break;	   // 4. �޸�ͬѧ������
			case '5': num = 5; break;	   // 5. �޸ĸ���Ա����
			case '6': num = 6; break;	   // 6. �޸İ���������
			case 27: flag = false; break;  // ESC���ص��ϸ�����
			default: break;
		}
		if (num != 0) {
			system("cls");
			cout << "\n\t\t\t �q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�����T�T�T�r"
				 << endl;
			cout << "\t\t\t��     ѧ���ۺϲ�������ϵͳ����ѧ����Ϣ�޸Ľ���   ��"
				 << endl;
			cout << "\t\t\t�t �T�T�T�����T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T �s\n"
				 << endl;
			cout << "\t\t\t   �������µķ���:";
			switch (num) {
				case 1: cin >> examGrade[0]; break;	 // 1. �޸ĸߵ���ѧ�ɼ�
				case 2: cin >> examGrade[1]; break;	 // 2. �޸Ĵ�ѧӢ��ɼ�
				case 3: cin >> examGrade[2]; break;	 // 3. �޸�c���Գɼ�
				case 4: cin >> givenMark[0]; break;	 // 4. �޸�ͬѧ������
				case 5: cin >> givenMark[1]; break;	 // 5. �޸ĸ���Ա����
				case 6: cin >> givenMark[2]; break;	 // 6. �޸İ���������
			}
			double sum = 0;
			for (int i = 0; i < 3; i++)
				sum += examGrade[i];
			avrGrade = sum / 3.0;
			sum = 0;
			for (int i = 0; i < 3; i++)
				sum += givenMark[i];
			multiGrade = avrGrade * 0.7 + sum * 0.1;
			cout << "\n\t\t\t\t�޸���ɣ�\n" << endl;
			Sleep(500);
		}
	}
}

bool Student::operator<(Student& s) {
	return strcmp(stuNum, s.stuNum) < 0;
}
