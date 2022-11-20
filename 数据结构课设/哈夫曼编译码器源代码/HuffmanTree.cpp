#include "HuffmanTree.h"
map<char, string> HuffmanCode;			 //���ַ� ��Ӧ�Ĺ���������
map<string, char> DeHuffmanCode;
bool HufTree::IsLeaps(Position rt) {
	if (rt == Null)
		return false;
	if (H[rt].left == Null && H[rt].right == Null)
		return true;
	else return false;
}
//������������ ��Ӧ���ַ�
int HufTree::CountSize(map<char, int> ch) {
	int cnt = 0;
	for (auto& i : ch) {  //ǰsize���ڵ� �����ݺ�Ȩֵ
		++cnt;
	}
	return cnt;
}

char HufTree::GetData(Position rt) {
	return H[rt].data;
}

string HufTree::SearchCode(char Data) {
	string Code;
	ComputingHuffmanCode(root);
	if (HuffmanCode.end() == HuffmanCode.find(Data)) {
		// HuffmanCode��δ�ҵ�����ַ���Ӧ����
		cout << "\n\t\t\tû�ж�Ӧ������ַ��������½�������������" << endl;
		return Code;
	}
	Code = HuffmanCode[Data];
	return Code;
}

Position HufTree::GetLeftSon(Position rt) {
	return H[rt].left;
}

Position HufTree::GetRightSon(Position rt) {
	return H[rt].right;
}

Position HufTree::Huffman(map<char, int> ch) {
	int kind = CountSize(ch);  // ch�й�ͳ���˶������ַ�
	if (kind == 0)
		return Null;
	size = 2 * kind - 1;	//һ����Ҫkind + kind-1�����
	if (H) {	//�ͷ�ԭ�еĹ��������
		delete H;
	}
	H = new HTNode[size];	
	int cnt = 0;
	for (auto& i : ch) {  //ǰkind���ڵ� ���ַ������Ȩֵ
		H[cnt].data = i.first;
		H[cnt].weight = i.second;
		++cnt;
	}
	if (size == 1) {
		root = 0;
		return 0;
	}						   //ֻ��һ��Ԫ�� ���úϲ� ��һ������
	Position EmptyNode = cnt;  //��ǰ�ߵĿս���±� 0 1 2��
	for (int k = 1; k <= kind - 1; ++k) {	 
	//kind��Ҷ�ӽ����Ҫkind-1�κϲ� 
	//ÿ�κϲ�ѡ�����������޸����Ľڵ�����Ȩֵ��С�Ľ��
	//�ϲ���Ȩֵ�ŵ��µĿս����
		int min1 = Null, min2 = Null;  //��СȨֵ����±ꡢ��СȨֵ����±�
		int minw1 = MaxFrequence + 1,
			minw2 = MaxFrequence + 1;  //��СȨֵ1����СȨֵ2
		for (int i = 0; i < size; ++i) {  //��������С�޸����Ľ��
			if (H[i].parent != Null)	//�и��ڵ��˲��ÿ�
				continue;				
			if (H[i].weight < minw1) {	//��ǰ�ڵ�Ȩֵ����СֵС
				minw2 = minw1;
				min2 = min1;//����Сֵ������Сֵ
				minw1 = H[i].weight;
				min1 = i;//����ǰ���Ȩֵ������Сֵ
			}
			else if (H[i].weight < minw2) {	 //��ǰ�ڵ�Ȩֵ�ȴ�СֵС
				minw2 = H[i].weight;
				min2 = i;
			}
		}
		//�ϲ�
		H[min1].parent = EmptyNode;
		H[min2].parent = EmptyNode;
		H[EmptyNode].left = min1;
		H[EmptyNode].right = min2;
		H[EmptyNode].weight = H[min1].weight + H[min2].weight;
		H[EmptyNode].parent = Null;
		EmptyNode++;
	}
	Position rt = 0;
	while (H[rt].parent != -1) {  
		//�и��ڵ��ʱ��ѭ���������ҵ����ڵ�
		//����ǰ���û�и��ڵ��ʱ��ѭ���˳�
		rt = H[rt].parent;
	}
	root = rt;
	ComputingHuffmanCode(root);	//�������������
	return rt;
}

void HufTree::PrintChar(char ch, int num, fstream& fp) {
	for (int i = 0; i < num; ++i)
		fp << ch;
}
void HufTree::PrintSide(int num, fstream& fp) {
	for (int i = 0; i < num; ++i)
		PrintChar(' ', SideLen, fp);
}

map<char, int> HufTree::CountCH() {
	map<char, int> m;
	if (root == Null)
		return m;
	if (H[root].right == Null && H[root].left == Null) {
		m[H[root].data] = H[root].weight;
		return m;
	}
	Position cur = root;
	stack<Position> s; 
	while (cur != Null || !s.empty()) {
		while (cur != Null) {//һֱ���󲢽���;���ѹ���ջ
			s.push(cur);
			cur = GetLeftSon(cur);
		}
		if (!s.empty()) {
			cur = s.top();
			s.pop();
			if (IsLeaps(cur)) {
				m[GetData(cur)] = H[cur].weight;
			}
			cur = GetRightSon(cur);
		}
	}
	return m;
}

void HufTree::DrawHuffmanTree(Position rt) {
	fstream f1;
	f1.open(TreePrintFile, ios::out);
	if (!f1) {
		cout << TreePrintFile << "�ļ���ʧ��!" << endl;
		return;
	}
	int height = 0;				//����
	int index = 0;						//������������±�
	Position* LevelOrder = new Position[size];//�����������
	vector<int> NodesNum;
	queue<Position> q;
	if (rt == Null) {
		f1 << "�ù�������Ϊ�գ�" << endl;
		return;	 //��ǰ��Ϊ��,ֱ�ӷ���
	}
	H[rt].pos = 1;
	q.push(rt);
	while (!q.empty()) {  //�����������¼ÿ�����posֵ��ÿ��ڵ����Լ��߶�
		int len = q.size();
		NodesNum.push_back(len);
		++height;
		for (int i = 1; i <= len; ++i) {  //ÿһ������нڵ�
			Position p = q.front();
			q.pop();
			LevelOrder[index++] = p;
			if (H[p].left != Null) {  //������
				int lr = H[p].left;
				q.push(lr);
				H[lr].pos = H[p].pos * 2;  //���ӱ��=���ڵ���*2
			}
			if (H[p].right != Null) {  //���Һ���
				int rr = H[p].right;
				q.push(rr);
				H[rr].pos = H[p].pos * 2 + 1;//�Һ��ӱ��=���ڵ���*2+1
			}
		}
	}
	int cnt = 1;						//��ǰ����������
	index = 0;
	for (int h = 0; h < height; ++h) {	//��0��~���һ��
		int tab = 0;	//��ͷ������
		int Unit = SideLen / 2;
		for (int i = 0; i < height - 1 - h; ++i) {
			tab += Unit;
			Unit *= 2;
		}
		PrintChar(' ', tab, f1);						  //��ͷ����
		for (int i = 0; i < NodesNum[h]; ++i, ++index) {  //����ÿһ������н��
			Position p = LevelOrder[index];	//����������е�˳���� ���϶��� �������
			int interval = pow(2, height - 1 - h) - 1;	 //�����������ɲ�������
			if (cnt == H[p].pos) {	//��ǰ�ڵ�ǡΪ������ڵ� ֱ�����
				f1 << ' ' << H[p].data << ":" << H[p].weight << ' ';
				PrintSide(interval, f1);
				++cnt;
				if (i == NodesNum[h] - 1) {//����ǰ�ڵ�ò����һ�������ݵĽ�㣬������Ƿ��пս��
					int p2 = pow(2,h+1)-1;
					for (; cnt <= p2; ++cnt) {
						f1 << " ---- ";
						PrintSide(interval, f1);
					}
				}
			}
			else {	//����Ҫ�����϶��������
				for (; cnt < H[p].pos; ++cnt) {
					f1 << " ---- ";
					PrintSide(interval, f1);
				}
				f1 << ' ' << H[p].data << ":" << H[p].weight << ' ';
				PrintSide(interval, f1);
				cnt++;
			}
		}
		f1 << endl;
	}
	f1.close();
}

void HufTree::ComputingHuffmanCode(Position rt, string path) {
	if (rt == Null) {
		cout << "����ʧ��!��������Ϊ�գ�" << endl;
		Sleep(500);
		return;
	}
	if (rt == root && H[rt].left == Null && H[rt].right == Null) {
		//����ֻ��һ���ַ������
		HuffmanCode[H[rt].data] = "0";
		DeHuffmanCode["0"] =
			H[rt].data;	 //���ｫ�����������Ӧ���ַ�Ҳ���·�������
		return;
	}
	if (H[rt].left == Null && H[rt].right == Null) {  //ΪҶ�ӽ��
		HuffmanCode[H[rt].data] = path;
		DeHuffmanCode[path] = H[rt].data;  //���ｫ�����������Ӧ���ַ�Ҳ���·�������
		return;
	}
	string lcode = path + '0';
	string rcode = path + '1';
	if (H[rt].left != Null)
		ComputingHuffmanCode(H[rt].left, lcode);
	if (H[rt].right != Null)
		ComputingHuffmanCode(H[rt].right, rcode);
}
