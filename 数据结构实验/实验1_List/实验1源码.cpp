#include <Windows.h>
#include <iostream>
#include <string>
using namespace std;
class Student {
public:
	string id;	  //学号
	string name;  //学生姓名
	int age;	  //年龄
	bool operator==(const Student& s) { return id == s.id; }
	bool operator!=(const Student& s) { return id != s.id; }
	bool operator<(const Student& s) { return id < s.id; }
	Student() : name("小明"), age(18) {}
	friend istream& operator>>(istream& is, Student& s) {
		is >> s.id >> s.name >> s.age;
		getchar();
		return is;
	}
	friend ostream& operator<<(ostream& os, const Student& s) {
		os << "学号:" << s.id << "  姓名:" << s.name << "  年龄:" << s.age
		   << endl;
		return os;
	}
};
template <class T> class List;
//结点定义
template <class T> class LNode {
private:
	LNode* next;  //指针
	T Data;		  //数据
public:
	friend class List<T>;
	LNode() { next = nullptr; }
	void showdata() { cout << Data << endl; }
};

//链表操作类定义
template <class T> class List {
private:
	LNode<T>* head;	 //头结点 不存储元素但分配空间
public:
	friend class LNode<T>;
	List();
	~List();
	LNode<T>* FindKth(int K);  //按序号查找查找 查找链表中第K个元素
							   //若找到返回指向该结点的指针，找不到返回空指针
	LNode<T>* Find(T data);	 //按值查找: 查找元素data
							 //若找到返回指向该结点的指针，找不到返回空指针
	void
	Delete(int pos =
			   1);	//删除操作(删除链表第pos个位置上的结点) 默认为删第一个元素
	void Insert(T data, int pos = 1);  //默认为头插法 将data插入在第pos个元素
	void PrintList();				   //展示该链表
	int getLength();				   //获取该链表长度
	void ReverseList();				   //逆转该链表
};

//链表操作类实现
//构造函数 为head分配空间，不放数据
template <class T> List<T>::List() {
	head = new LNode<T>;
	head->next = nullptr;
}
//析构函数 释放空间
template <class T> List<T>::~List() {
	while (head->next) {
		Delete(1);
	}
	delete head;
}
//(1) 按序号查找::查找链表中第K个元素
// 若找到返回指向该结点的指针，找不到返回空指针
template <class T> LNode<T>* List<T>::FindKth(int K) {
	LNode<T>* p = head->next;  //第一个元素
	if (!p) {
		cout << "Element not found,This List is empty!" << endl;
		return nullptr;
	}
	int pos = 1;
	while (p->next && pos < K) {
		p = p->next;
		pos++;
	}
	if (pos == K)
		return p;  //找到第K个则返回指针
	else {		   //否则位置不合法，返回空指针
		cout << "The location is illegal." << endl;
		return nullptr;
	}
}

//(2) 按值查找: 查找元素data
//若找到返回指向该结点的指针，找不到返回空指针
template <class T> LNode<T>* List<T>::Find(T data) {
	LNode<T>* p = head->next;
	if (!p) {
		cout << "Element not found,This List is empty!" << endl;
		return nullptr;
	}
	while (p->next && p->Data != data)
		p = p->next;
	if (p->Data != data) {  //到最后了但元素仍不是data
		cout << "Element not found!" << endl;
		return nullptr;
	}
	else
		return p;
}

//(3) 删除操作:删除链表第pos个位置上的结点,默认为删第一个元素
template <class T>
void List<T>::Delete(int pos) {	 //删除操作(删除链表第i个位置上的结点)
	LNode<T>* p = head->next;
	if (!p) {
		cout << "Deleted failed,This List is empty!" << endl;
		return;
	}
	if (pos == 1) {	 //若要删除的是表的第一个结点
		head->next = p->next;
		if (p)
			delete p;
		return;
	}
	LNode<T>* s = FindKth(pos - 1);	 //找到第pos-1个元素
	if (!s) {
		cout << "The " << pos-1 << " node does not exist!" << endl;
		return;
	}
	p = s->next;
	if (!p) {
		cout << "The " << pos << " node does not exist!" << endl;
		return;
	} else {
		s->next = p->next;	// s指向第pos+1个结点
		delete p;			//将p从链表中删除
		cout << "Successfully deleted!" << endl;
	}
}

//(4)插入操作 默认为头插法 将data插入在第pos个元素
template <class T> void List<T>::Insert(T data, int pos) {
	LNode<T>* p = new LNode<T>();//申请新节点p的空间
	p->Data = data;
	if (pos == 1) {	 //插在第一个
		p->next = head->next;
		head->next = p;
		cout << "Successfully Inserted!" << endl;
		return;
	}
	LNode<T>* s = FindKth(pos - 1);	 //找到第pos-1个元素
	if (!s) {
		cout << "The location is illegal,Insertion failed!" << endl;
		return;
	}
	p->next = s->next;
	s->next = p;
	cout << "Successfully Inserted!" << endl;
}

//(5)获取该链表长度
template <class T> int List<T>::getLength() {
	LNode<T>* p = head;	 // p指向表的头节点
	int cnt = 0;
	while (p->next) {
		p = p->next;
		cnt++;
	}
	return cnt;
}
//(6)展示该链表
template <class T> void List<T>::PrintList() {
	LNode<T>* p = head;	 // p指向表的头节点
	if (!head->next)
		cout << "This List is empty!" << endl;
	int cnt = 0;
	while (p->next) {
		p = p->next;
		cnt++;
		cout << "The " << cnt << "th Data is:";
		p->showdata();
	}
	cout << "The list has " << cnt << " elements in total." << endl;
}
//(7)逆转该链表
template <class T> void List<T>::ReverseList() {
	LNode<T>* now = head->next;	 // now指向表的第一个节点
	if (!now) {
		cout << "This List is empty!" << endl;
		return;
	}
	LNode<T>* tmp = now->next;	// 指向now之后的一个节点
	while (tmp) {				//把tmp放到头结点后边
		now->next = tmp->next;
		tmp->next = head->next;
		head->next = tmp;
		tmp = now->next;
	}
}
//主函数中调用的函数
template <class T> void input(List<T>& Head) {
	T data;
	cout << "请输入链表元素(以空格间隔，回车结束):";
	cin >> data;
	Head.Insert(data);
}
template <class T> void remove(List<T>& Head) {
	int i;
	cout << "请输入i(删除链表第i个元素):";
	cin >> i;
	getchar();

	Head.Delete(i);
}
template <class T> void findKth(List<T>& Head) {
	int K;
	LNode<T>* s = nullptr;
	cout << "(按序号查找)请输入K，查找链表中第K个元素:";
	cin >> K;
	getchar();
	s = Head.FindKth(K);
	if (!s)
		cout << "未找到!" << endl;
	else {
		cout << "查找成功!该元素为:";
		s->showdata();
	}
}
template <class T> void findData(List<T>& Head) {
	string data;
	cout << "请输入待查找学生的学号:";
	cin >> data;
	Student t;
	t.id = data;
	getchar();
	LNode<T>* s = nullptr;
	s = Head.Find(t);
	if (!s)
		cout << "未找到该元素！" << endl;
	else {
		cout << "查找成功!该元素在链表中。";
	}
}
template <class T> void insert(List<T>& Head) {
	int i;
	T data;
	cout << "在链表第i个位置上插入一名学生信息,输入i:";
	cin >> i;
	cout << "输入该学生信息，学号 姓名 年龄以空格间隔，回车结束:";
	cin >> data;
	Head.Insert(data, i);
}
template <class T> inline void getlength(List<T>& Head) {
	cout << "该链表长度为:" << Head.getLength() << endl;
}
template <class T> void printList(List<T>& Head) {
	cout << "---------------------- List P --------------------" << endl;
	Head.PrintList();
}
template <class T> void reverseList(List<T>& Head) {
	T data;
	cout << "---------------------- List P --------------------" << endl;
	Head.PrintList();
	cout << endl;

	Head.ReverseList();
	cout << "------------- After reverse, List P ---------------" << endl;
	Head.PrintList();
}
int main() {
	List<Student> P;
	int choice;
	cout << "1 添加一名学生信息" << endl;
	cout << "2 删除链表第i个元素" << endl;
	cout << "3 按序号查找链表中第K个元素" << endl;
	cout << "4 按值查找元素data" << endl;
	cout << "5 在链表第i个位置上插入元素data" << endl;
	cout << "6 获取该链表长度" << endl;
	cout << "7 打印所有学生信息" << endl;
	cout << "8 逆转该链表" << endl;
	cout << "9 结束" << endl;
	while (1) {
		cout << "菜单选择(1-6):";
		cin >> choice;
		getchar();
		switch (choice) {
			case 1: input(P); break;
			case 2: remove(P); break;
			case 3: findKth(P); break;
			case 4: findData(P); break;
			case 5: insert(P); break;
			case 6: getlength(P); break;
			case 7: printList(P); break;
			case 8: reverseList(P); break;
			case 9: break;
			default: cout << "输入错误，请重新输入";
		}
		if (choice == 9)
			exit(0);
		cout << "按回车键继续…" << endl;
		getchar();
	};
	return 0;
}