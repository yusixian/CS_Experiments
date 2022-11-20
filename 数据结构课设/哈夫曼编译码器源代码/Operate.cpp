#include "Operate.h"
Operate O;
//从终端读入字符及其权值直接建立哈夫曼树
void Operate::CreateHfmTreeByInput() {
	system("cls");
	menus.Hint1();
	int n,fre;
	char ch;
	map<char, int> m;
	cout << "\t\t  请输入字符数n:";
	cin >> n;
	cout << "\n\t\t  请输入字符及其出现频率（如A 4，换行继续输入下个字符）:";
	for (int i = 0; i < n; ++i) {
		cin >> ch >> fre;
		m[ch] = fre;
		getchar();
		cout << "\t\t\t";
	}
	huf.Huffman(m);	 //根据字符及频率建立哈夫曼树
	cout << "\t\t哈夫曼树建立完毕！如下" << endl;
	huf.DrawHuffmanTree(huf.root);
	PrintHfmByTree();
	StoreHfmTree();	//存储哈夫曼树
	menus.Hint2();
}
//读取字符文件建立最优哈夫曼树
void Operate::CreateHfmTreeByFile() {
	system("cls");
	menus.Hint1();
	map<char, int> m = ReadCHfile();
	cout << "\t\t文件" << ToBeTranFile << "中字符种类及其出现频率如下：\n"
		 << endl;
	PrintFrequence(m);
	huf.Huffman(m);	 //根据字符及频率建立哈夫曼树
	cout << "\t\t哈夫曼树建立完毕！如下\n" << endl;
	huf.DrawHuffmanTree(huf.root);
	PrintHfmByTree();
	StoreHfmTree();	//存储哈夫曼树
	cout << endl;
	menus.Hint2();
}
//哈夫曼编码 对文件ToBeTran中的正文进行编码
void Operate::Encoding() {
	system("cls");
	menus.Hint1();
	if (huf.size == 0) ReadHufTreeFile();//如不在内存，则从文件读入
	fstream f1, of1, of2, of3;
	f1.open(ToBeTranFile, ios::in | ios::binary);		//打开待编码文件ToBeTran
	of1.open(CodePrintFile, ios::out);	//编码后以文本形式存入文件CodePrint
	of2.open(CodeFile, ios::out | ios::binary);//编码后以二进制形式存入文件CodeFile
	of3.open(ConfigFile, ios::out);	 //配置文件 存储字符出现的次数
	if (!f1) {
		cout << "\t\t" << ToBeTranFile << "文件打开失败!" << endl;
		Sleep(500);
		return;
	}
	if (!of1) {
		cout << "\t\t" << CodePrintFile << "文件打开失败!" << endl;
		Sleep(500);
		return;
	}
	if (!of2) {
		cout << "\t\t" << CodeFile << "文件打开失败!" << endl;
		Sleep(500);
		return;
	}
	if (!of3) {
		cout << "\t\t" << ConfigFile << "文件打开失败!" << endl;
		Sleep(500);
		return;
	}
	cout << "\t\t\t原文件(ToBeTran文件)内容如下：\n" << endl;
	PrintToBeTranFile();
	huf.ComputingHuffmanCode(huf.root);	//计算哈夫曼编码
	cout << "\t\t\t编码后文本(CodePrintFile文件)内容如下：\n" << endl;
	char Text[MaxSize];
	string str;
	f1.read(Text, MaxSize);
	int len = f1.gcount();	//实际读取了多少个字节
	int cnt = 0;	//一行已显示代码数量
	unsigned char value = 0;
	int pos = 0;	//当前几位
	int CHnum = 0;
	int Codelen = 0;
	cout << "\t\t\t";
	for (int i = 0; i < len; ++i) {//遍历待编码字符串的每个字符
		if (Text[i] == '\r')
			continue;
		if (Text[i] == '\n') {
			of1 << '\n';
			cout << '\n'; 
			continue;
		}
		string Code = huf.SearchCode(Text[i]);
		if (Code == "") {	//提示未找到对应编码 返回
			menus.Hint2();
			return;
		}
		CHnum++;
		Codelen += Code.length();
		of1 << Code << ' ';	  //文本形式存入存的时候加个空格方便阅读
		cout << Code << ' ';  //显示出来
		++cnt;
		if (cnt >= MaxCodeNum) {	 //一行显示最多编码数量
			cnt = 0;
			cout << endl;
			cout << "\t\t\t";
		}
		for (int j = 0; j < Code.size(); ++j) {
			//将字符转为二进制位，满8位就写入
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
	if (pos) { // pos==0，说明刚好存完8位；pos!=0，说明还有多余的位
		value <<= (8 - pos);
		of2.write((char*)&value, sizeof(value));
	}
	//配置文件---存储待翻译字符数以及代码实际占多少bits
	of3 << CHnum << ' ' << Codelen;
	cout << '\n' <<  endl;
	f1.close();
	of1.close();
	of2.close();
	menus.Hint2();
}

//哈夫曼译码 将文件CodeFile的内容译码后以文本形式显示在终端上，译文存入文件TextFile
void Operate::Decoding() {
	system("cls");
	menus.Hint1();
	if (huf.size == 0)
		ReadHufTreeFile();	//如不在内存，则从文件读入
	huf.ComputingHuffmanCode(huf.root);	 //计算哈夫曼编码

	fstream f1, f2, of1;
	f1.open(CodeFile, ios::in | ios::binary);	   //打开待译码文件CodeFile
	f2.open(ConfigFile, ios::in);		//打开配置文件Configfile
	of1.open(TextFile, ios::out);  //译码后以文本形式存入文件TextFile
	if (!f1) {
		cout << "\t\t" << CodePrintFile << "文件打开失败!" << endl;
		Sleep(500);
		return;
	}
	if (!f2) {
		cout << "\t\t" << ConfigFile << "文件打开失败!" << endl;
		Sleep(500);
		return;
	}
	if (!of1) {
		cout << "\t\t" << TextFile << "文件打开失败!" << endl;
		Sleep(500);
		return;
	}
	int CHnum;	
	int cnt = 0;	//已显示字符数目
	f2 >> CHnum;	 //读入待译码的字符个数
	//由压缩文件还原原文件
	cout << "\t\t\t译码后文件(TextFile文件)内容如下：\n" << endl;
	int pos = 7;
	unsigned char value;
	f1.read((char*)&value, sizeof(value));
	Position cur = huf.root;
	cout << "\t\t\t";
	while (CHnum && value != EOF) {
		//到叶子节点说明找到字符，放入解压文件
		if (huf.IsLeaps(cur)) {
			of1 << huf.GetData(cur);
			cout << huf.GetData(cur);//输出该字符到屏幕
			CHnum--;
			cur = huf.root;
			++cnt;
			if (cnt >= MaxTextNum) {	 //一行显示最多编码数量
				cnt = 0;
				cout << "\n\t\t\t";
			}
		}  
		//如果不是叶子结点，0向左走，1向右走
		if (value & (1 << pos)) {
			cur = huf.GetRightSon(cur);
			if (cur == Null) {
				cout << "...\n没有对应字符的编码，请重新建立哈夫曼树！"
						<< endl;
				menus.Hint2();
				return;
			}
		}
		else {
			cur = huf.GetLeftSon(cur);
			if (cur == Null) {
				cout << "...\n没有对应字符的编码，请重新建立哈夫曼树！"
						<< endl;
				menus.Hint2();
				return;
			}
		}
		--pos;
		//当pos < 0时，说明此时已经解压完一个字节，开始解压下一个字节
		if (pos < 0) {
			pos = 7;
			f1.read((char*)&value, sizeof(value));
		}//当CHnum <= 0时，字符已经全部解压完
		if (CHnum <= 0)
			break;
		
	}
	cout << '\n' << endl;
	f1.close();
	of1.close();
	menus.Hint2();
}

//显示译码后压缩率与平均压缩长度
void Operate::PrintCompreRatio() {
	system("cls");
	menus.Hint1();
	if (huf.size == 0)
		ReadHufTreeFile();	//如不在内存，则从文件读入
	fstream f1,f2;
	f1.open(ToBeTranFile, ios::in);	//打开译码前文件ToBeTran
	f2.open(ConfigFile, ios::in);  //打开译码后配置文件ConfigFile
	if (!f1) {
		cout << "\t\t" << ToBeTranFile << "文件打开失败!" << endl;
		Sleep(500);
		return;
	}
	if (!f2) {
		cout << "\t\t" << ConfigFile << "文件打开失败!" << endl;
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
	f2 >> CHnum >> Codelen;	 //译码后字符数(多少个字符)和代码长度（多少bits）
	TrueSize = Codelen + (8-Codelen % 8);
	int t = Codelen % 8;
	if (t == 0)
		TrueSize = Codelen;
	else
		TrueSize = Codelen + 8 - t;
	TrueSize /= 8;
	double ratio = TrueSize * 1.0 / CHsize;
	cout << "\t\t\t译码前占用字节大小：" << CHsize << endl;
	cout << "\n\t\t\t译码后占用字节大小：" << TrueSize << endl;
	cout << "\n\t\t\t压缩率为：" << ratio << "\n" << endl;
	map<char, int> m = ReadCHfile();
	CHnum = huf.CountSize(m);
	cout << "\t\t\t译码前平均长度（字符对应编码长度之和/字符数）：" << 8 << endl;
	double sum = 0;
	for (auto& i : m) {  //前size个节点 存数据和权值
		char ch = i.first;
		sum += HuffmanCode[ch].length();
	}
	ratio = sum / CHnum*1.0;
	cout << "\n\t\t\t译码后平均长度（字符对应编码长度之和/字符数）：" << ratio << '\n' << endl;
	f1.close();
	f2.close();
	menus.Hint2();
}

//查询某字符对应编码功能
void Operate::Search() {
	system("cls");
	menus.Hint1();
	if (huf.size == 0)
		ReadHufTreeFile();	//如不在内存，则从文件读入
	char data;
	cout << "\t\t\t请输入要查询编码的字符:";
	cin >> data;
	string Code = huf.SearchCode(data);
	if (Code == "") {
		cout << "\n\n\t\t\t该字符在哈夫曼树中不存在对应编码！\n\n" << endl;
	}
	else
		cout << "\n\n\t\t\t该字符对应编码为：" << Code << "\n\n" << endl;
	menus.Hint2();
}

//展示哈夫曼树
void Operate::PrintHfmTree() {
	system("cls");
	menus.Hint1();
	if (huf.size == 0)
		ReadHufTreeFile();	//如不在内存，则从文件读入
	cout << "\t\t哈夫曼树如下" << endl;
	huf.DrawHuffmanTree(huf.root);
	PrintHfmByTree();
	cout << endl;
	menus.Hint2();
}

//导出哈夫曼编码到CorresponCode文件中
void Operate::ExportHfmCode() {
	system("cls");
	menus.Hint1();
	if (huf.size == 0)
		ReadHufTreeFile();	//如不在内存，则从文件读入
	huf.ComputingHuffmanCode(huf.root);
	PrintCorresponCodeFile();
	StoreCorreCodeFile();
	menus.Hint2();
}

void Operate::PrintCode() {
	fstream fp;
	fp.open(CodePrintFile, ios::in);
	if (!fp) {
		cout << "\t\t" << CodePrintFile << "文件打开失败！" << endl;
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
		cout << "\t\t" << TreePrintFile << "文件打开失败！" << endl;
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
		cout << "\t\t" << ToBeTranFile << "文件打开失败！" << endl;
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
	cout << "\t\t字符\t出现次数\t哈夫曼编码\t编码长度" << endl;
	int cnt = 0, sum = 0;
	for (const auto& i : HuffmanCode) {
		printf_s("\t\t%3c \t%6d  \t%10s\t%6d  \n", i.first, m[i.first],
				 i.second.c_str(), i.second.length());
	}
	cout << endl;
}

void Operate::PrintFrequence(map<char, int> m) {
	cout << "\t\t字符\t出现次数\n" << endl;
	int cnt = 0, sum = 0;
	for (const auto& i : m) {
		cout << "\t\t" << i.first << '\t' << i.second << "\n" << endl;
		++cnt;
		sum += i.second;
	}
	cout << "\t\t共有" << cnt << "种字符。\n" << endl;
	cout << "\t\t共有" << sum << "个字符。\n" << endl;
}

void Operate::StoreCorreCodeFile() {
	fstream of;
	of.open(CorresponCodeFile, ios::out);
	if (!of) {
		cout << "\t\t" << CorresponCodeFile << "文件打开失败！" << endl;
		Sleep(500);
		return;
	}
	map<char, int> m = huf.CountCH();
	of << "字符,出现次数,哈夫曼编码,编码长度" << endl;
	for (const auto& i : HuffmanCode) {
		of << i.first << ',' << m[i.first] << ','<< i.second
			 << ',' << i.second.length() << endl;
	}
	of.close();
}

void Operate::StoreHfmTree() {
	fstream of;
	of.open(HfmTreeFile, ios::out | ios::binary);  //以二进制只写形式打开文件HfmTree
	if (!of) {
		cout << "\t\t" << HfmTreeFile << "文件打开失败！" << endl;
		Sleep(500);
		return;
	}
	of.write((char*)&huf.size, sizeof(huf.size));  //首先将哈夫曼树大小存入文件
	of.write((char*)&huf.root,
			 sizeof(huf.root));	 //其次将哈夫曼树根结点下标存入文件
	for (int i = 0; i < huf.size; ++i) {  //将结构数组存入
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
		cout << "\t\t" << ToBeTranFile << "文件打开失败!" << endl;
		Sleep(500);
		return m;
	}
	while (getline(f1, str)) {
		int len = str.length();
		for (int i = 0; i < len; ++i) {
			if (m.end() == m.find(str[i]))
				// ch中未找到这个字符对应频率，第一次出现
				m[str[i]] = 1;
			else
				++m[str[i]];  //找到了，对应字符出现频率++
		}
	}
	f1.close();
	return m;
}

void Operate::ReadHufTreeFile() {
	fstream fp;
	fp.open(HfmTreeFile, ios::in | ios::binary);
	if (!fp) {
		cout << "\t\t" << HfmTreeFile << "文件打开失败!" << endl;
		Sleep(500);
	}
	fp.read((char*)&huf.size, sizeof(huf.size)); 
	if (huf.H) {	 //释放原有的哈夫曼结点
		delete huf.H;
	}
	huf.H = new HTNode[huf.size];
	fp.read((char*)&huf.root, sizeof(huf.root));  //其次将哈夫曼树根结点下标读入
	for (int i = 0; i < huf.size; ++i) {  //将结构数组读入
		fp.read((char*)&huf.H[i], sizeof(huf.H[i]));
	}
	huf.ComputingHuffmanCode(huf.root);
	fp.close();
}

