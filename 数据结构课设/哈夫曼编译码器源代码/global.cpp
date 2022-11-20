#include "global.h" 
HufTree huf;
void Init() {							  //��ʼ��
	system("mode con cols=96 lines=35");  //�ı���
	system("color F0");					  //�ı����̨������ɫ
	system("cls");						//����
}
void MainInterface() {
	while (1) {
		menus.Menu1();
		switch (_getch()) {							
			case '1': CreateHfmTree(); break;		// 1.������������������������ļ�HfmTree��
			case '2': O.Encoding(); break;	// 2. ���������� ���ļ�ToBeTran�е����Ľ��б���
			case '3': O.Decoding(); break;	// 3. ���������� ���ļ�CodeFile��������������ı���ʽ��ʾ���ն��ϣ����Ĵ����ļ�TextFile
			case '4': O.PrintCompreRatio(); break;	// 4. ��ʾ�����ѹ������ƽ��ѹ������
			case '5': O.Search(); break;	// 5. ��ѯĳ�ַ���Ӧ���빦��
			case '6': O.PrintHfmTree(); break;	// 6. չʾ��������
			case '7': O.ExportHfmCode(); break;	// 7. �������������뵽CorresponCode�ļ���
			case '8': exit(0); break;  // 8. �˳�
			case 27: exit(0); break;			// ESC.�˳�
			default: break;
		}
	}
}
//������������
void CreateHfmTree() {
	while (1) {
		menus.Menu2();
		switch (_getch()) {
			case '1': O.CreateHfmTreeByInput(); break;	
			// 1.���ն˶����ַ�����Ȩֱֵ�ӽ�����������
			case '2': O.CreateHfmTreeByFile(); break;		  
			// 2. ��ȡ�ַ��ļ��������Ź�������
			case 27: return;  // ESC.������һ��
			default: break;
		}
	}
}