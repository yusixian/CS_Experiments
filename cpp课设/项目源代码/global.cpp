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
	cout << "\n\t\t\t �q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�����T�T�T�r" << endl;
	cout << "\t\t\t��    ѧ���ۺϲ�������ϵͳ����������¼����        ��" << endl;
	cout << "\t\t\t�t �T�T�T�����T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T �s\n\n" << endl;
	cout << "\t\t\t\t �������˺ţ��14λ��:";
	O.Read(un);
	cout << "\t\t\t\t ���������루�14λ��:";
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
void Register(int i) {	// 0Ϊ��ͨ�û�ע�ᣬ1Ϊ����Աע��
	char un[15], pw[15];
	vector<User> uu = O.ReadUserFile();
	vector<User>::iterator it;
	if (i == 0) {  //��ͨ�û�ע��
		system("cls");
		cout << "\n\t\t\t �q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�����T�T�T�r" << endl;
		cout << "\t\t\t��    ѧ���ۺϲ�������ϵͳ��������ע�����        ��" << endl;
		cout << "\t\t\t�t �T�T�T�����T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T �s\n"
			 << endl;
		User U1(0);
		cout << "\t\t\t\t �������˺ţ��14λ��:";
		O.Read(un);
		bool flag = true;//�˺��Ƿ��ظ�
		while (flag) {
			bool k = false;
			for (it = uu.begin(); it != uu.end(); it++) {
				U = *it;
				if (strcmp(un, U.userName) == 0) {
					flag = true;
					cout << "\t\t\t �˺��Ѵ���,�����������˺ţ��14λ��:";
					O.Read(un);
					k = true;
					break;
				}
			}
			if (!k)//����ǽ���ѭ�������ģ�˵���˺Ų����ظ���
				flag = false;
		}
		U1.changeUserName(un);
		cout << "\t\t\t\t ���������루�14λ��:";
		O.Read(pw);
		U1.changePassWord(pw);
		printf("\t\t\t\t �����˺�Ϊ:%s\n\n", un);
		printf("\t\t\t\t ��������Ϊ:%s\n\n", pw);
		uu.push_back(U1);
	}  else {	//����Աע��
		User M(1);
		cout << "\t\t\t\t �������Ա�˺ţ��14λ��:";
		O.Read(un);
		M.changeUserName(un);
		cout << "\t\t\t\t �������Ա���루�14λ��:";
		O.Read(pw);
		M.changePassWord(pw);
		printf("\t\t\t\t ����Ա�˺�Ϊ:%s\n\n", un);
		printf("\t\t\t\t ����Ա����Ϊ:%s\n\n", pw);
		uu.push_back(M);
	}
	O.StoreUserFile(uu);
	cout << "\t\t\t\tע����ϣ��������������һ��" << endl;
	_getch();
}
void LandR() {
	while (1) {
		menus.Menu1();	//��ʾ��¼orע��˵�
		bool flag = false;	//��¼�ɹ����
		int c = _getch();
		if (c == 49) {	 //Ϊ1 ��ִ�е�¼����
			flag = Login();
			if (flag) {
				cout << "\t\t\t\t\t��¼�ɹ���" << endl;
				Sleep(500);
				system("cls");
				return;
			} else {//��½ʧ��
				cout << "\t\t\t\t��¼ʧ��,�û�������������" << endl;
				Sleep(500);
				menus.Menu1();	//��ʾ��¼orע��˵�
			}
		} else if(c == 50){ //Ϊ2 ��ִ��ע�����
			Register();	 //��ͨ�û�ע��
			menus.Menu1();
		} else if (c == 27) {//ESC�˳�
			exit(0);
		}
	}
}
void Init() {							  //��ʼ�� ��ʾ��¼orע��˵�
	system("mode con cols=96 lines=35");  //�ı���
	system("color F0");			//�ı����̨������ɫ
	vector<User> uu = O.ReadUserFile();
	if (uu.empty()) {
		menus.Hint1();	//����Աע����ʾ
		Register(1);
	}
	LandR();
}
void MainInterface() {
	while (1) {
		menus.Menu2(U.isAdmin);
		if (U.isAdmin) {//����Ա
			switch (_getch()) {
				case '1': O.AddInfor(U); break;	// 1. ���ѧ����Ϣ
				case '2': O.DeleteInfor(U); break;  // 2. ɾ��ѧ����Ϣ
				case '3': O.ModifyInfor(U); break;  // 3. �޸�ѧ����Ϣ
				case '4': O.QueryInfor(U); break;	  // 4. ��ѯѧ����Ϣ
				case '5': O.DisplayStuInfor(U); break;	// 5. ��ʾȫ��ѧ����Ϣ
				case '6': O.DisplayUserInfor(U); break;	 // 6. ��ʾȫ���û���Ϣ
				case '7': O.ReportPrint(U); break;	 // 7. ����ȫ����Ϣ
				case '8': O.ChangePassWord(U); break;	 // 8. �޸��û�����
				case '9': O.ImproveVIP(U); break;  // 9. ������ͨ�û�Ȩ��
				case 27: Init(); break;	 // ESC���ص��ϸ�����
				default: break;
			}
		} else {//��ͨ�û�
			switch (_getch()) {
				case '1': O.ChangePassWord(U); break;	 // 1. �޸��û�����
				case '2': O.QueryInfor(U); break;		 // 2. ��ѯѧ����Ϣ
				case '3': O.DisplayStuInfor(U); break;	// 3. ��ʾȫ��ѧ����Ϣ
				case '4': O.ReportPrint(U); break;	 // 4. ����ȫ����Ϣ
				case 27: Init(); break; // ESC���ص��ϸ�����
				default: break;
			}
		}
	}
}