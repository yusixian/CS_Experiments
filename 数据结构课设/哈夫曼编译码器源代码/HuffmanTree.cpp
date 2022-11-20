#include "HuffmanTree.h"
map<char, string> HuffmanCode;			 //各字符 对应的哈弗曼编码
map<string, char> DeHuffmanCode;
bool HufTree::IsLeaps(Position rt) {
	if (rt == Null)
		return false;
	if (H[rt].left == Null && H[rt].right == Null)
		return true;
	else return false;
}
//各哈弗曼编码 对应的字符
int HufTree::CountSize(map<char, int> ch) {
	int cnt = 0;
	for (auto& i : ch) {  //前size个节点 存数据和权值
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
		// HuffmanCode中未找到这个字符对应编码
		cout << "\n\t\t\t没有对应编码的字符，请重新建立哈夫曼树！" << endl;
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
	int kind = CountSize(ch);  // ch中共统计了多少种字符
	if (kind == 0)
		return Null;
	size = 2 * kind - 1;	//一共需要kind + kind-1个结点
	if (H) {	//释放原有的哈夫曼结点
		delete H;
	}
	H = new HTNode[size];	
	int cnt = 0;
	for (auto& i : ch) {  //前kind个节点 存字符及其和权值
		H[cnt].data = i.first;
		H[cnt].weight = i.second;
		++cnt;
	}
	if (size == 1) {
		root = 0;
		return 0;
	}						   //只有一个元素 不用合并 就一个编码
	Position EmptyNode = cnt;  //最前边的空结点下标 0 1 2…
	for (int k = 1; k <= kind - 1; ++k) {	 
	//kind个叶子结点需要kind-1次合并 
	//每次合并选两个在所有无父结点的节点中中权值最小的结点
	//合并后权值放到新的空结点内
		int min1 = Null, min2 = Null;  //最小权值结点下标、次小权值结点下标
		int minw1 = MaxFrequence + 1,
			minw2 = MaxFrequence + 1;  //最小权值1、次小权值2
		for (int i = 0; i < size; ++i) {  //找两个最小无父结点的结点
			if (H[i].parent != Null)	//有父节点了不用看
				continue;				
			if (H[i].weight < minw1) {	//当前节点权值比最小值小
				minw2 = minw1;
				min2 = min1;//将最小值赋给次小值
				minw1 = H[i].weight;
				min1 = i;//将当前结点权值赋给最小值
			}
			else if (H[i].weight < minw2) {	 //当前节点权值比次小值小
				minw2 = H[i].weight;
				min2 = i;
			}
		}
		//合并
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
		//有父节点的时候循环继续，找到根节点
		//即当前结点没有父节点的时候循环退出
		rt = H[rt].parent;
	}
	root = rt;
	ComputingHuffmanCode(root);	//计算哈夫曼编码
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
		while (cur != Null) {//一直向左并将沿途结点压入堆栈
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
		cout << TreePrintFile << "文件打开失败!" << endl;
		return;
	}
	int height = 0;				//层数
	int index = 0;						//层序遍历序列下标
	Position* LevelOrder = new Position[size];//层序遍历序列
	vector<int> NodesNum;
	queue<Position> q;
	if (rt == Null) {
		f1 << "该哈夫曼树为空！" << endl;
		return;	 //当前树为空,直接返回
	}
	H[rt].pos = 1;
	q.push(rt);
	while (!q.empty()) {  //层序遍历，记录每个结点pos值与每层节点数以及高度
		int len = q.size();
		NodesNum.push_back(len);
		++height;
		for (int i = 1; i <= len; ++i) {  //每一层的所有节点
			Position p = q.front();
			q.pop();
			LevelOrder[index++] = p;
			if (H[p].left != Null) {  //有左孩子
				int lr = H[p].left;
				q.push(lr);
				H[lr].pos = H[p].pos * 2;  //左孩子编号=父节点编号*2
			}
			if (H[p].right != Null) {  //有右孩子
				int rr = H[p].right;
				q.push(rr);
				H[rr].pos = H[p].pos * 2 + 1;//右孩子编号=父节点编号*2+1
			}
		}
	}
	int cnt = 1;						//当前待输出结点编号
	index = 0;
	for (int h = 0; h < height; ++h) {	//第0层~最后一层
		int tab = 0;	//开头的缩进
		int Unit = SideLen / 2;
		for (int i = 0; i < height - 1 - h; ++i) {
			tab += Unit;
			Unit *= 2;
		}
		PrintChar(' ', tab, f1);						  //开头缩进
		for (int i = 0; i < NodesNum[h]; ++i, ++index) {  //遍历每一层的所有结点
			Position p = LevelOrder[index];	//按层序遍历中的顺序来 自上而下 自左而右
			int interval = pow(2, height - 1 - h) - 1;	 //各层各结点间隔由层数决定
			if (cnt == H[p].pos) {	//当前节点恰为待输出节点 直接输出
				f1 << ' ' << H[p].data << ":" << H[p].weight << ' ';
				PrintSide(interval, f1);
				++cnt;
				if (i == NodesNum[h] - 1) {//若当前节点该层最后一个有内容的结点，则看其后是否有空结点
					int p2 = pow(2,h+1)-1;
					for (; cnt <= p2; ++cnt) {
						f1 << " ---- ";
						PrintSide(interval, f1);
					}
				}
			}
			else {	//否则要输出空隙再输出结点
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
		cout << "编码失败!哈夫曼树为空！" << endl;
		Sleep(500);
		return;
	}
	if (rt == root && H[rt].left == Null && H[rt].right == Null) {
		//特判只有一种字符的情况
		HuffmanCode[H[rt].data] = "0";
		DeHuffmanCode["0"] =
			H[rt].data;	 //这里将哈夫曼编码对应的字符也存下方便译码
		return;
	}
	if (H[rt].left == Null && H[rt].right == Null) {  //为叶子结点
		HuffmanCode[H[rt].data] = path;
		DeHuffmanCode[path] = H[rt].data;  //这里将哈夫曼编码对应的字符也存下方便译码
		return;
	}
	string lcode = path + '0';
	string rcode = path + '1';
	if (H[rt].left != Null)
		ComputingHuffmanCode(H[rt].left, lcode);
	if (H[rt].right != Null)
		ComputingHuffmanCode(H[rt].right, rcode);
}
