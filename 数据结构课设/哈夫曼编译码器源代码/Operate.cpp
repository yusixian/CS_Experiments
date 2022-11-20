#include "Operate.h"
Operate O;
//���ն˶����ַ�����Ȩֱֵ�ӽ�����������
void Operate::CreateHfmTreeByInput() {
	system("cls");
	menus.Hint1();
	int n,fre;
	char ch;
	map<char, int> m;
	cout << "\t\t  �������ַ���n:";
	cin >> n;
	cout << "\n\t\t  �������ַ��������Ƶ�ʣ���A 4�����м��������¸��ַ���:";
	for (int i = 0; i < n; ++i) {
		cin >> ch >> fre;
		m[ch] = fre;
		getchar();
		cout << "\t\t\t";
	}
	huf.Huffman(m);	 //�����ַ���Ƶ�ʽ�����������
	cout << "\t\t��������������ϣ�����" << endl;
	huf.DrawHuffmanTree(huf.root);
	PrintHfmByTree();
	StoreHfmTree();	//�洢��������
	menus.Hint2();
}
//��ȡ�ַ��ļ��������Ź�������
void Operate::CreateHfmTreeByFile() {
	system("cls");
	menus.Hint1();
	map<char, int> m = ReadCHfile();
	cout << "\t\t�ļ�" << ToBeTranFile << "���ַ����༰�����Ƶ�����£�\n"
		 << endl;
	PrintFrequence(m);
	huf.Huffman(m);	 //�����ַ���Ƶ�ʽ�����������
	cout << "\t\t��������������ϣ�����\n" << endl;
	huf.DrawHuffmanTree(huf.root);
	PrintHfmByTree();
	StoreHfmTree();	//�洢��������
	cout << endl;
	menus.Hint2();
}
//���������� ���ļ�ToBeTran�е����Ľ��б���
void Operate::Encoding() {
	system("cls");
	menus.Hint1();
	if (huf.size == 0) ReadHufTreeFile();//�粻���ڴ棬����ļ�����
	fstream f1, of1, of2, of3;
	f1.open(ToBeTranFile, ios::in | ios::binary);		//�򿪴������ļ�ToBeTran
	of1.open(CodePrintFile, ios::out);	//��������ı���ʽ�����ļ�CodePrint
	of2.open(CodeFile, ios::out | ios::binary);//������Զ�������ʽ�����ļ�CodeFile
	of3.open(ConfigFile, ios::out);	 //�����ļ� �洢�ַ����ֵĴ���
	if (!f1) {
		cout << "\t\t" << ToBeTranFile << "�ļ���ʧ��!" << endl;
		Sleep(500);
		return;
	}
	if (!of1) {
		cout << "\t\t" << CodePrintFile << "�ļ���ʧ��!" << endl;
		Sleep(500);
		return;
	}
	if (!of2) {
		cout << "\t\t" << CodeFile << "�ļ���ʧ��!" << endl;
		Sleep(500);
		return;
	}
	if (!of3) {
		cout << "\t\t" << ConfigFile << "�ļ���ʧ��!" << endl;
		Sleep(500);
		return;
	}
	cout << "\t\t\tԭ�ļ�(ToBeTran�ļ�)�������£�\n" << endl;
	PrintToBeTranFile();
	huf.ComputingHuffmanCode(huf.root);	//�������������
	cout << "\t\t\t������ı�(CodePrintFile�ļ�)�������£�\n" << endl;
	char Text[MaxSize];
	string str;
	f1.read(Text, MaxSize);
	int len = f1.gcount();	//ʵ�ʶ�ȡ�˶��ٸ��ֽ�
	int cnt = 0;	//һ������ʾ��������
	unsigned char value = 0;
	int pos = 0;	//��ǰ��λ
	int CHnum = 0;
	int Codelen = 0;
	cout << "\t\t\t";
	for (int i = 0; i < len; ++i) {//�����������ַ�����ÿ���ַ�
		if (Text[i] == '\r')
			continue;
		if (Text[i] == '\n') {
			of1 << '\n';
			cout << '\n'; 
			continue;
		}
		string Code = huf.SearchCode(Text[i]);
		if (Code == "") {	//��ʾδ�ҵ���Ӧ���� ����
			menus.Hint2();
			return;
		}
		CHnum++;
		Codelen += Code.length();
		of1 << Code << ' ';	  //�ı���ʽ������ʱ��Ӹ��ո񷽱��Ķ�
		cout << Code << ' ';  //��ʾ����
		++cnt;
		if (cnt >= MaxCodeNum) {	 //һ����ʾ����������
			cnt = 0;
			cout << endl;
			cout << "\t\t\t";
		}
		for (int j = 0; j < Code.size(); ++j) {
			//���ַ�תΪ������λ����8λ��д��
			value <<= 1;	
			if (Code[j] == '1')
				value |= 1;
			else
				value |= 0;
			++pos;
			if (pos == 8) {
				of2.write((char*)&value, sizeof(value));
				pos = 0;
				value = 0;
			}
		}
	}
	if (pos) { // pos==0��˵���պô���8λ��pos!=0��˵�����ж����λ
		value <<= (8 - pos);
		of2.write((char*)&value, sizeof(value));
	}
	//�����ļ�---�洢�������ַ����Լ�����ʵ��ռ����bits
	of3 << CHnum << ' ' << Codelen;
	cout << '\n' <<  endl;
	f1.close();
	of1.close();
	of2.close();
	menus.Hint2();
}

//���������� ���ļ�CodeFile��������������ı���ʽ��ʾ���ն��ϣ����Ĵ����ļ�TextFile
void Operate::Decoding() {
	system("cls");
	menus.Hint1();
	if (huf.size == 0)
		ReadHufTreeFile();	//�粻���ڴ棬����ļ�����
	huf.ComputingHuffmanCode(huf.root);	 //�������������

	fstream f1, f2, of1;
	f1.open(CodeFile, ios::in | ios::binary);	   //�򿪴������ļ�CodeFile
	f2.open(ConfigFile, ios::in);		//�������ļ�Configfile
	of1.open(TextFile, ios::out);  //��������ı���ʽ�����ļ�TextFile
	if (!f1) {
		cout << "\t\t" << CodePrintFile << "�ļ���ʧ��!" << endl;
		Sleep(500);
		return;
	}
	if (!f2) {
		cout << "\t\t" << ConfigFile << "�ļ���ʧ��!" << endl;
		Sleep(500);
		return;
	}
	if (!of1) {
		cout << "\t\t" << TextFile << "�ļ���ʧ��!" << endl;
		Sleep(500);
		return;
	}
	int CHnum;	
	int cnt = 0;	//����ʾ�ַ���Ŀ
	f2 >> CHnum;	 //�����������ַ�����
	//��ѹ���ļ���ԭԭ�ļ�
	cout << "\t\t\t������ļ�(TextFile�ļ�)�������£�\n" << endl;
	int pos = 7;
	unsigned char value;
	f1.read((char*)&value, sizeof(value));
	Position cur = huf.root;
	cout << "\t\t\t";
	while (CHnum && value != EOF) {
		//��Ҷ�ӽڵ�˵���ҵ��ַ��������ѹ�ļ�
		if (huf.IsLeaps(cur)) {
			of1 << huf.GetData(cur);
			cout << huf.GetData(cur);//������ַ�����Ļ
			CHnum--;
			cur = huf.root;
			++cnt;
			if (cnt >= MaxTextNum) {	 //һ����ʾ����������
				cnt = 0;
				cout << "\n\t\t\t";
			}
		}  
		//�������Ҷ�ӽ�㣬0�����ߣ�1������
		if (value & (1 << pos)) {
			cur = huf.GetRightSon(cur);
			if (cur == Null) {
				cout << "...\nû�ж�Ӧ�ַ��ı��룬�����½�������������"
						<< endl;
				menus.Hint2();
				return;
			}
		}
		else {
			cur = huf.GetLeftSon(cur);
			if (cur == Null) {
				cout << "...\nû�ж�Ӧ�ַ��ı��룬�����½�������������"
						<< endl;
				menus.Hint2();
				return;
			}
		}
		--pos;
		//��pos < 0ʱ��˵����ʱ�Ѿ���ѹ��һ���ֽڣ���ʼ��ѹ��һ���ֽ�
		if (pos < 0) {
			pos = 7;
			f1.read((char*)&value, sizeof(value));
		}//��CHnum <= 0ʱ���ַ��Ѿ�ȫ����ѹ��
		if (CHnum <= 0)
			break;
		
	}
	cout << '\n' << endl;
	f1.close();
	of1.close();
	menus.Hint2();
}

//��ʾ�����ѹ������ƽ��ѹ������
void Operate::PrintCompreRatio() {
	system("cls");
	menus.Hint1();
	if (huf.size == 0)
		ReadHufTreeFile();	//�粻���ڴ棬����ļ�����
	fstream f1,f2;
	f1.open(ToBeTranFile, ios::in);	//������ǰ�ļ�ToBeTran
	f2.open(ConfigFile, ios::in);  //������������ļ�ConfigFile
	if (!f1) {
		cout << "\t\t" << ToBeTranFile << "�ļ���ʧ��!" << endl;
		Sleep(500);
		return;
	}
	if (!f2) {
		cout << "\t\t" << ConfigFile << "�ļ���ʧ��!" << endl;
		Sleep(500);
		return;
	}
	string Text;
	string str;
	while (getline(f1, str)) { 
		Text.append(str); 
	}
	int CHsize = Text.length();
	int CHnum, Codelen;
	int TrueSize;
	f2 >> CHnum >> Codelen;	 //������ַ���(���ٸ��ַ�)�ʹ��볤�ȣ�����bits��
	TrueSize = Codelen + (8-Codelen % 8);
	int t = Codelen % 8;
	if (t == 0)
		TrueSize = Codelen;
	else
		TrueSize = Codelen + 8 - t;
	TrueSize /= 8;
	double ratio = TrueSize * 1.0 / CHsize;
	cout << "\t\t\t����ǰռ���ֽڴ�С��" << CHsize << endl;
	cout << "\n\t\t\t�����ռ���ֽڴ�С��" << TrueSize << endl;
	cout << "\n\t\t\tѹ����Ϊ��" << ratio << "\n" << endl;
	map<char, int> m = ReadCHfile();
	CHnum = huf.CountSize(m);
	cout << "\t\t\t����ǰƽ�����ȣ��ַ���Ӧ���볤��֮��/�ַ�������" << 8 << endl;
	double sum = 0;
	for (auto& i : m) {  //ǰsize���ڵ� �����ݺ�Ȩֵ
		char ch = i.first;
		sum += HuffmanCode[ch].length();
	}
	ratio = sum / CHnum*1.0;
	cout << "\n\t\t\t�����ƽ�����ȣ��ַ���Ӧ���볤��֮��/�ַ�������" << ratio << '\n' << endl;
	f1.close();
	f2.close();
	menus.Hint2();
}

//��ѯĳ�ַ���Ӧ���빦��
void Operate::Search() {
	system("cls");
	menus.Hint1();
	if (huf.size == 0)
		ReadHufTreeFile();	//�粻���ڴ棬����ļ�����
	char data;
	cout << "\t\t\t������Ҫ��ѯ������ַ�:";
	cin >> data;
	string Code = huf.SearchCode(data);
	if (Code == "") {
		cout << "\n\n\t\t\t���ַ��ڹ��������в����ڶ�Ӧ���룡\n\n" << endl;
	}
	else
		cout << "\n\n\t\t\t���ַ���Ӧ����Ϊ��" << Code << "\n\n" << endl;
	menus.Hint2();
}

//չʾ��������
void Operate::PrintHfmTree() {
	system("cls");
	menus.Hint1();
	if (huf.size == 0)
		ReadHufTreeFile();	//�粻���ڴ棬����ļ�����
	cout << "\t\t������������" << endl;
	huf.DrawHuffmanTree(huf.root);
	PrintHfmByTree();
	cout << endl;
	menus.Hint2();
}

//�������������뵽CorresponCode�ļ���
void Operate::ExportHfmCode() {
	system("cls");
	menus.Hint1();
	if (huf.size == 0)
		ReadHufTreeFile();	//�粻���ڴ棬����ļ�����
	huf.ComputingHuffmanCode(huf.root);
	PrintCorresponCodeFile();
	StoreCorreCodeFile();
	menus.Hint2();
}

void Operate::PrintCode() {
	fstream fp;
	fp.open(CodePrintFile, ios::in);
	if (!fp) {
		cout << "\t\t" << CodePrintFile << "�ļ���ʧ�ܣ�" << endl;
		Sleep(500);
		return;
	}
	string str;
	while (getline(fp, str)) {
		cout << str << endl;
	}
	fp.close();
}

void Operate::PrintHfmByTree() {
	fstream fp;
	fp.open(TreePrintFile, ios::in);
	if (!fp) {
		cout << "\t\t" << TreePrintFile << "�ļ���ʧ�ܣ�" << endl;
		Sleep(500);
		return;
	}
	string str;
	while (getline(fp, str)) {
		cout << "\t\t" << str << endl;
	}
	fp.close();
}

void Operate::PrintToBeTranFile() {
	fstream fp;
	fp.open(ToBeTranFile, ios::in);
	if (!fp) {
		cout << "\t\t" << ToBeTranFile << "�ļ���ʧ�ܣ�" << endl;
		Sleep(500);
		return;
	}
	string str;
	while (getline(fp, str)) {
		cout << "\t\t\t" << str << endl;
	}
	cout << endl;
	fp.close();
}


void Operate::PrintCorresponCodeFile() {
	map<char, int> m = huf.CountCH();
	cout << "\t\t�ַ�\t���ִ���\t����������\t���볤��" << endl;
	int cnt = 0, sum = 0;
	for (const auto& i : HuffmanCode) {
		printf_s("\t\t%3c \t%6d  \t%10s\t%6d  \n", i.first, m[i.first],
				 i.second.c_str(), i.second.length());
	}
	cout << endl;
}

void Operate::PrintFrequence(map<char, int> m) {
	cout << "\t\t�ַ�\t���ִ���\n" << endl;
	int cnt = 0, sum = 0;
	for (const auto& i : m) {
		cout << "\t\t" << i.first << '\t' << i.second << "\n" << endl;
		++cnt;
		sum += i.second;
	}
	cout << "\t\t����" << cnt << "���ַ���\n" << endl;
	cout << "\t\t����" << sum << "���ַ���\n" << endl;
}

void Operate::StoreCorreCodeFile() {
	fstream of;
	of.open(CorresponCodeFile, ios::out);
	if (!of) {
		cout << "\t\t" << CorresponCodeFile << "�ļ���ʧ�ܣ�" << endl;
		Sleep(500);
		return;
	}
	map<char, int> m = huf.CountCH();
	of << "�ַ�,���ִ���,����������,���볤��" << endl;
	for (const auto& i : HuffmanCode) {
		of << i.first << ',' << m[i.first] << ','<< i.second
			 << ',' << i.second.length() << endl;
	}
	of.close();
}

void Operate::StoreHfmTree() {
	fstream of;
	of.open(HfmTreeFile, ios::out | ios::binary);  //�Զ�����ֻд��ʽ���ļ�HfmTree
	if (!of) {
		cout << "\t\t" << HfmTreeFile << "�ļ���ʧ�ܣ�" << endl;
		Sleep(500);
		return;
	}
	of.write((char*)&huf.size, sizeof(huf.size));  //���Ƚ�����������С�����ļ�
	of.write((char*)&huf.root,
			 sizeof(huf.root));	 //��ν���������������±�����ļ�
	for (int i = 0; i < huf.size; ++i) {  //���ṹ�������
		of.write((char*)&huf.H[i], sizeof(huf.H[i]));
	}
	of.close();
}

map<char, int> Operate::ReadCHfile() {
	map<char, int> m;
	string str;
	fstream f1;
	f1.open(ToBeTranFile, ios::in);
	if (!f1) {
		cout << "\t\t" << ToBeTranFile << "�ļ���ʧ��!" << endl;
		Sleep(500);
		return m;
	}
	while (getline(f1, str)) {
		int len = str.length();
		for (int i = 0; i < len; ++i) {
			if (m.end() == m.find(str[i]))
				// ch��δ�ҵ�����ַ���ӦƵ�ʣ���һ�γ���
				m[str[i]] = 1;
			else
				++m[str[i]];  //�ҵ��ˣ���Ӧ�ַ�����Ƶ��++
		}
	}
	f1.close();
	return m;
}

void Operate::ReadHufTreeFile() {
	fstream fp;
	fp.open(HfmTreeFile, ios::in | ios::binary);
	if (!fp) {
		cout << "\t\t" << HfmTreeFile << "�ļ���ʧ��!" << endl;
		Sleep(500);
	}
	fp.read((char*)&huf.size, sizeof(huf.size)); 
	if (huf.H) {	 //�ͷ�ԭ�еĹ��������
		delete huf.H;
	}
	huf.H = new HTNode[huf.size];
	fp.read((char*)&huf.root, sizeof(huf.root));  //��ν���������������±����
	for (int i = 0; i < huf.size; ++i) {  //���ṹ�������
		fp.read((char*)&huf.H[i], sizeof(huf.H[i]));
	}
	huf.ComputingHuffmanCode(huf.root);
	fp.close();
}

