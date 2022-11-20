#include <cmath>
#include <iostream>
#include <utility>
using namespace std;
const int HashSize = 13;  //哈希函数取模用
const int MaxSize = 16;	  //表长
typedef int Index;		  //散列后的下标
//散列单元状态类型，分别对应：有合法元素、空单元、有已删除元素
typedef enum { Legitimate, Empty, Deleted } EntryType;
typedef int DataType;  //数据的类型
struct HashNode {	   //散列表单元类型
	DataType data;	   //存放元素
	EntryType flag;	   //单元状态
};
struct HashTable {	  //散列表类型
	int TableSize;	  //表长
	HashNode* Units;  //存放散列单元的数组
};
typedef HashTable* ptrHash;
//创建一个长度为TableSize的空表
ptrHash CreateTable(int TableSize) {
	ptrHash H;
	int i;
	H = new HashTable;
	H->TableSize = TableSize;
	H->Units = new HashNode[H->TableSize];
	for (int i = 0; i < H->TableSize; ++i) {
		H->Units[i].flag = Empty;
	}

	return H;
}
//返回经散列函数计算后的下标
inline Index Hash(DataType Key) {
	return Key % HashSize;
}
//查找Key元素,这里采用线性探测再散列处理冲突
Index Find(ptrHash H, DataType Key) {
	Index nowp, newp;
	int Cnum = 0;  //记录冲突次数
	newp = nowp = Hash(Key);
	//若该位置的单元非空且不是要找的元素时发生冲突
	while (H->Units[newp].flag != Empty && H->Units[newp].data != Key) {
		++Cnum;	 //冲突增加一次
		newp = (nowp + Cnum) % H->TableSize;
	}
	return newp;  //返回位置，该位置若为一个空单元的位置则表示找不到
}
//采用线性探测再散列处理冲突, 返回冲突次数
Index FindCnum(ptrHash H, DataType Key) {
	Index nowp, newp;
	int Cnum = 0;  //记录冲突次数
	newp = nowp = Hash(Key);
	//若该位置的单元非空且不是要找的元素时发生冲突
	while (H->Units[newp].flag != Empty && H->Units[newp].data != Key) {
		++Cnum;	 //冲突增加一次
		newp = (nowp + Cnum) % H->TableSize;
	}
	return Cnum;  //返回冲突次数
}
//插入Key到表中 返回插入成功与否
bool Insert(ptrHash H, DataType Key) {
	Index p = Find(H, Key);
	if (H->Units[p].flag !=
		Legitimate) {  //只要这个单位能放入新元素（有已删除元素或空单元）
		H->Units[p].flag = Legitimate;
		H->Units[p].data = Key;
		return true;
	}
	else {	//该键值已存在
		return false;
	}
}
int a[12] = {19, 14, 23, 1, 68, 20, 84, 27, 55, 11, 10, 79};
int cnum[12];  //冲突次数，+1即为查找成功比较次数
int cnt, sum;  //比较次数、比较总数（算ASL）
int t;		   //待查找元素
void CountASL(ptrHash H) {
	//冲突次数
	for (int i = 0; i < MaxSize; ++i) {
		if (H->Units[i].flag == Empty)
			printf("Null\t");
		else {
			cnum[cnt] = FindCnum(H, H->Units[i].data);
			printf("%d\t", cnum[cnt]);
			++cnt;
		}
	}
	cout << endl << "ASL = (";
	for (int i = 0; i < 12; ++i) {
		if (i == 11)
			cout << cnum[i] + 1 << ")";
		else {
			cout << cnum[i] + 1 << " + ";
		}
		sum += cnum[i] + 1;
	}
	cout << " / 12 = " << sum / 12.0 << endl;
}
int main() {
	ptrHash H = CreateTable(MaxSize);
	for (int i = 0; i < 12; ++i) {
		Insert(H, a[i]);
	}
	//下标
	for (int i = 0; i < MaxSize; ++i)
		printf("%d\t", i);
	cout << endl;
	//数据
	for (int i = 0; i < MaxSize; ++i) {
		if (H->Units[i].flag == Empty)
			printf("Null\t");
		else
			printf("%d\t", H->Units[i].data);
	}
	cout << endl;
	CountASL(H);
	cout << "Please input the element to be found:";
	while (cin >> t) {
		int i = Find(H, t);
		if (H->Units[i].flag == Empty)
			cout << "The element was not found!" << endl;
		else {
			cout << "Find successful! The element is located under the hash table as:" << i << endl;
		}
	}
	return 0;
}