//顺序栈
#include <bits/stdc++.h>
#define error -1
using namespace std;
//顺序栈定义
template <class T> class myStack1 {
private:
	int MaxSize;  //堆栈容量
	T* Data;	  //数据
	int top;  //记录栈顶元素 为栈顶元素下标后一个下标，为空时top为0
public:
	myStack1(int maxsize = 100);  //构造函数 分配空间
	~myStack1();				   //析构函数 回收空间
	void PrintStack();		   //展示顺序栈中所有元素
	void Push(T data);	//入栈操作,top值加一,存储元素item在栈顶
	T Pop();			//出栈操作,将元素弹出返回,Top值减一
	T Top();			//取栈顶元素,不弹出
	int Size();			//获取堆栈元素数量
	bool IsEmpty();		//判断栈空与否
	bool IsFull();		//判断栈满与否
};

//顺序栈操作类实现
//构造函数 分配空间
template <class T>
myStack1<T>::myStack1(int maxsize) : MaxSize(maxsize), top(0) {
	Data = new T[maxsize];
};
//析构函数 释放空间
template <class T> myStack1<T>::~myStack1() {
	if (Data)
		delete[] Data;
}
//(1) 判断栈空与否
template <class T> bool myStack1<T>::IsEmpty() {
	return top == 0;
}
//(2) 判断栈满与否
template <class T> bool myStack1<T>::IsFull() {
	return top == MaxSize;
}
//(3) 入栈操作
// 存储元素data在栈顶,Top值加一
template <class T> void myStack1<T>::Push(T data) {
	if (IsFull()) {
		cout << "error:Failed to Push,The Stack is Full!" << endl;
	}
	else {
		Data[top++] = data;
	}
}
//(4) 取栈顶元素,不弹出
template <class T> T myStack1<T>::Top() {
	if (IsEmpty()) {
		cout << "error:The Top isn't existed, The Stack is Empty!" << endl;
		return error;  // ERROR为T类型中的特殊值
	}
	else {
		return Data[top - 1];
	}
}
//(5) 获取堆栈元素数量
template <class T> int myStack1<T>::Size() {
	return top;
}
//(6) 出栈操作
// 弹出栈顶元素,Top值减一
template <class T> T myStack1<T>::Pop() {
	if (IsEmpty()) {
		cout << "error:Failed to Pop, The Stack is Empty!" << endl;
		return error;  // ERROR为T类型中的特殊值
	}
	else {
		T temp = Data[--top];
		return temp;
	}
}
//(7) 展示顺序栈中所有元素
template <class T> void myStack1<T>::PrintStack() {
	if (IsEmpty())
		cout << "This Stack is empty!" << endl;
	for (int i = 0; i < top; ++i) {
		cout << "The " << i + 1 << "th Data is:";
		cout << Data[i] << endl;
	}
	cout << "The Stack has " << top << " elements in total." << endl;
}
//主函数中调用的函数 (测试用)
template <class T> void Stack_Push(myStack1<T>& S) {
	T data;
	cout << "请输入要入栈的元素:";
	cin >> data;
	S.Push(data);
	cout << "------------- After Push, Stack S ---------------" << endl;
	S.PrintStack();
}
template <class T> void Stack_Pop(myStack1<T>& S) {
	T data = S.Pop();
	if (data != error) {
		cout << "出栈元素为:";
		cout << data << endl;
	}
	cout << "------------- After Pop, Stack S ---------------" << endl;
	S.PrintStack();
}
template <class T> void Stack_Top(myStack1<T>& S) {
	T data = S.Top();
	if (data != error) {
		cout << "栈顶元素为:";
		cout << data << endl;
	}
}
template <class T> void Stack_Size(myStack1<T>& S) {
	cout << "该堆栈中元素个数为:" << S.Size() << endl;
}
template <class T> void Stack_PrintStack(myStack1<T>& S) {
	cout << "---------------------- Stack S --------------------" << endl;
	S.PrintStack();
}
int main() {
	int n;
	cout << "输入n,建立长度为n的顺序栈:";
	cin >> n;
	myStack1<int> S(n);
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
	cout << "5 输出顺序栈中所有元素" << endl;
	cout << "6 结束" << endl;
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
			case 6: break;
			default: cout << "输入错误，请重新输入";
		}
		if (choice == 6)
			exit(0);
		cout << "按回车键继续…" << endl;
		getchar();
	};
	return 0;
}