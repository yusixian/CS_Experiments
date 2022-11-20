//链栈
#include <bits/stdc++.h>
#define error -1
using namespace std;
template <class T> class Stack;
//链栈结点定义
template <class T> class SNode {
private:
	SNode* next;  //指针
	T Data;		  //数据
public:
	friend class Stack<T>;
	SNode() { next = nullptr; }	 //空结点
	SNode(T data) {				 //有数据的结点
		Data = data;
		next = nullptr;
	}
	void showdata() { cout << Data << endl; }  //展示该结点数据
};
//链栈操作类定义
template <class T> class Stack {
private:
	int maxsize;  //堆栈容量
	SNode<T>* head;	 //头指针 带空头结点，所以栈顶元素一直为head->next
public:
	Stack(int size = 100);	//构造函数 分配空间,空头结点
	~Stack();				//析构函数 回收空间
	void PrintStack();		//展示栈中所有元素
	void Clear();			//清空栈中所有元素
	void Push(T data);		//入栈操作 存储元素data在栈顶
	T Pop();		 //出栈操作 弹出栈顶元素并将其在栈中删除
	T Top();		 //取栈顶元素,不弹出
	int Size();		 //获取堆栈元素数量
	bool IsEmpty();	 //判断栈空与否
	bool IsFull();	 //判断栈满与否
};

//链栈操作类实现
//构造函数 分配空间,空头结点
template <class T> Stack<T>::Stack(int size) : maxsize(size) {
	head = new SNode<T>;
	head->next = nullptr;
};

//析构函数 释放空间
template <class T> Stack<T>::~Stack() {
	while (head->next) {
		Pop();
	}
	if (head)
		delete head;
}
//(1) 判断栈空与否
template <class T> bool Stack<T>::IsEmpty() {
	if (head->next)
		return false;
	else
		return true;
}
//(2) 判断栈满与否
template <class T> bool Stack<T>::IsFull() {
	if (Size() < maxsize)
		return false;
	else
		return true;
}
//(3) 入栈操作
// 存储元素data在栈顶
template <class T> void Stack<T>::Push(T data) {
	if (IsFull()) {
		cout << "error:Failed to Push,The Stack is Full!" << endl;
	}
	else {
		SNode<T>* p = new SNode<T>;
		p->Data = data;
		p->next = head->next;
		head->next = p;
	}
}
//(4) 取栈顶元素,不弹出
template <class T> T Stack<T>::Top() {
	if (IsEmpty()) {
		cout << "error:The Top isn't existed, The Stack is Empty!" << endl;
		return error;
	}
	else {
		T temp = head->next->Data;
		return temp;
	}
}
//(5) 获取堆栈元素数量
template <class T> int Stack<T>::Size() {
	int cnt = 0;
	SNode<T>* p = head;
	while (p->next) {
		cnt++;
		p = p->next;
	}
	return cnt;
}
//(6) 出栈操作
// 弹出栈顶元素并将其在栈中删除
template <class T> T Stack<T>::Pop() {
	if (IsEmpty()) {
		cout << "error:Failed to Pop, The Stack is Empty!" << endl;
		return error;
	}
	else {
		SNode<T>* temp = head->next;
		T TopData = temp->Data;
		head->next = temp->next;
		delete temp;
		return TopData;
	}
}
//(7) 展示栈中所有元素
template <class T> void Stack<T>::PrintStack() {
	if (IsEmpty())
		cout << "This Stack is empty!" << endl;
	SNode<T>* p = head;
	int cnt = 0;
	while (p->next) {
		++cnt;
		p = p->next;
		cout << "The " << cnt << "th Data is:";
		cout << p->Data << endl;
	}
	cout << "The Stack has " << Size() << " elements in total." << endl;
}
//(8) 清空栈中所有元素
template <class T> void Stack<T>::Clear() {
	while (head->next) {
		Pop();
	}
}
//主函数中调用的函数 (测试用)
template <class T> void Stack_Push(Stack<T>& S) {
	T data;
	cout << "请输入要入栈的元素:";
	cin >> data;
	getchar();
	S.Push(data);
	cout << "------------- After Push, Stack S ---------------" << endl;
	S.PrintStack();
}
template <class T> void Stack_Pop(Stack<T>& S) {
	T data = S.Pop();
	if (data != error) {
		cout << "出栈元素为:";
		cout << data << endl;
	}
	cout << "------------- After Pop, Stack S ---------------" << endl;
	S.PrintStack();
}
template <class T> void Stack_Top(Stack<T>& S) {
	T data = S.Top();
	if (data != error) {
		cout << "栈顶元素为:";
		cout << data << endl;
	}
}
template <class T> void Stack_Size(Stack<T>& S) {
	cout << "该堆栈中元素个数为:" << S.Size() << endl;
}
template <class T> void Stack_PrintStack(Stack<T>& S) {
	cout << "---------------------- Stack S --------------------" << endl;
	S.PrintStack();
}
template <class T> void Stack_ClearStack(Stack<T>& S) {
	S.Clear();
	cout << "成功清空！" << endl;
}
int main() {
	int n;
	cout << "输入n,建立长度为n的链栈:";
	cin >> n;
	Stack<int> S(n);
	cout << "输入n个元素:" << endl;
	for (int i = 0; i < n; ++i) {
		int data;
		cin >> data;
		S.Push(data);
	}
	cout << "1 入栈操作" << endl;
	cout << "2 出栈操作" << endl;
	cout << "3 取栈顶元素" << endl;
	cout << "4 取堆栈元素个数" << endl;
	cout << "5 输出栈中所有元素" << endl;
	cout << "6 清空栈中所有元素" << endl;
	cout << "7 结束" << endl;
	while (1) {
		int choice;
		cout << "菜单选择:";
		cin >> choice;
		getchar();
		switch (choice) {
			case 1: Stack_Push(S); break;
			case 2: Stack_Pop(S); break;
			case 3: Stack_Top(S); break;
			case 4: Stack_Size(S); break;
			case 5: Stack_PrintStack(S); break;
			case 6: Stack_ClearStack(S); break;
			case 7: break;
			default: cout << "输入错误，请重新输入";
		}
		if (choice == 7)
			exit(0);
		cout << "按回车键继续…" << endl;
		getchar();
	};
	return 0;
}