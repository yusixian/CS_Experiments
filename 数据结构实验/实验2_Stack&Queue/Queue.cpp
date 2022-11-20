//循环队列
#include <bits/stdc++.h>
#define error -1
using namespace std;
//循环队列定义
template <class T> class myQueue {
private:
	int MaxSize;  //队列最大容量
	T* Data;	  //存放数据的指针，申请MaxSize+1的空间只利用MaxSize的空间
	int front;  //记录队首元素下标
	int rear;	//记录队尾元素下标 为实际队尾元素的后一个下标，初始时为0
public:
	myQueue(int maxsize = 100);  //构造函数 分配空间
	~myQueue();				   //析构函数 回收空间
	void PrintQueue();		   //展示循环队列中所有元素
	void Push(T data);	//入队操作,rear值加一,存储元素data在队尾rear
	void Clear();			//清空队中所有元素
	T Pop();			//出队操作,返回队首元素
	T Front();			//取队首元素,不出队
	int Size();			//获取队元素数量
	bool IsEmpty();		//判断队空与否 front = rear时队空
	bool IsFull();		//判断队满与否 front = (rear+1) % MaxSize时队满
};

//循环队列操作类实现
//构造函数 分配空间
template <class T>
myQueue<T>::myQueue(int maxsize) : MaxSize(maxsize), front(0), rear(0) {
	Data = new T[MaxSize+1];//这里申请MaxSize+1的空间便于判断循环队列的空与满
};
//析构函数 释放空间
template <class T> myQueue<T>::~myQueue() {
	if (Data)
		delete[] Data;
}
//(1) 判断队空与否
template <class T> bool myQueue<T>::IsEmpty() {
	return front == rear;
}
//(2) 判断队满与否
template <class T> bool myQueue<T>::IsFull() {
	return front == (rear + 1) % (MaxSize+1);
}
//(3) 入队操作
// 存储元素data在队尾rear,rear值加一
template <class T> void myQueue<T>::Push(T data) {
	if (IsFull()) {
		cout << "error:Failed to Push,The Queue is Full!" << endl;
	} else {
		Data[rear] = data;
		rear++;
		rear %= MaxSize + 1; //保证不会数组越界
	}
}
//(4) 取队首元素,不出队
template <class T> T myQueue<T>::Front() {
	if (IsEmpty()) {
		cout << "error:The Front isn't existed, The Queue is Empty!" << endl;
		return error;  // error为T类型中的特殊值
	} else {
		return Data[front];
	}
}
//(5) 获取队元素数量
template <class T> int myQueue<T>::Size() {
	if (IsFull())
		return MaxSize;
	if (IsEmpty())
		return 0;
	if (front < rear) //正常情况 front在前 
		return rear - front;
	else {				//front在rear后，先到数组尾部，再从头开始到rear
		int size = MaxSize + 1 - front; 
		size += rear;
	}
}
//(6) 出队操作
// 弹出队首元素
template <class T> T myQueue<T>::Pop() {
	if (IsEmpty()) {
		cout << "error:Failed to Pop, The Queue is Empty!" << endl;
		return error;  // error为T类型中的特殊值
	}
	else {
		T temp = Data[front];
		front++;
		front %= MaxSize + 1; //保证不会数组越界
		return temp;
	}
}
//(7) 清空操作
// 清空该循环队列
template <class T> void myQueue<T>::Clear() {
	while (!IsEmpty()) {
		Pop();
	}
}
//(8) 展示循环队列中所有元素
template <class T> void myQueue<T>::PrintQueue() {
	if (IsEmpty()) {
		cout << "This Queue is empty!" << endl;
		return;
	}
	int cnt = 0;
	if (front < rear) {//正常情况 front在前
		for(int i = front; i < rear; ++i) {
			++cnt;
			cout << "The " << cnt << "th Data is:";
			cout << Data[i] << endl;
		}
	} else {				//front在rear后，先到数组尾部，再从头开始到rear
		for(int i = front; i < MaxSize+1; ++i) {
			++cnt;
			cout << "The " << cnt << "th Data is:";
			cout << Data[i] << endl;
		}
		for(int i = 0; i < rear; ++i) {
			++cnt;
			cout << "The " << cnt << "th Data is:";
			cout << Data[i] << endl;
		}
	}
	cout << "The Queue has " << cnt << " elements in total." << endl;
}
//主函数中调用的函数 (测试用)
template <class T> void Queue_Push(myQueue<T>& Q) {
	T data;
	cout << "Queue_Push:";
	cin >> data;
	Q.Push(data);
	cout << "------------- After Push, Queue Q ---------------" << endl;
	Q.PrintQueue();
}
template <class T> void Queue_Pop(myQueue<T>& Q) {
	T data = Q.Pop();
	if (data != error) {
		cout << "Queue_Pop:";
		cout << data << endl;
	}
	cout << "------------- After Pop, Queue Q ---------------" << endl;
	Q.PrintQueue();
}
template <class T> void Queue_Front(myQueue<T>& Q) {
	T data = Q.Front();
	if (data != error) {
		cout << "Queue_Front:";
		cout << data << endl;
	}
}
template <class T> void Queue_Clear(myQueue<T>& Q) {
	Q.Clear();
	cout << "Cleared successfully!" << endl;
	cout << "------------- After Clear, Queue Q ---------------" << endl;
	Q.PrintQueue();
}
template <class T> void Queue_Size(myQueue<T>& Q) {
	cout << "Queue_Size:" << Q.Size() << endl;
}
template <class T> void Queue_PrintQueue(myQueue<T>& Q) {
	cout << "---------------------- Queue Q --------------------" << endl;
	Q.PrintQueue();
}
int main() {
	int n;
	cout << "Please input n:";
	cin >> n;
	myQueue<int> Q(n);
	cout << "Please input n element:" << endl;
	for (int i = 0; i < n; ++i) {
		int data;
		cin >> data;
		Q.Push(data);
	}
	cout << "1 Queue_Push" << endl;
	cout << "2 Queue_Pop" << endl;
	cout << "3 Queue_Front" << endl;
	cout << "4 Queue_Clear" << endl;
	cout << "5 Queue_Size" << endl;
	cout << "6 Queue_PrintQueue" << endl;
	cout << "7 Exit" << endl;
	while (1) {
		int choice;
		cout << "Please chose:";
		cin >> choice;
		getchar();
		switch (choice) {
			case 1: Queue_Push(Q); break;
			case 2: Queue_Pop(Q); break;
			case 3: Queue_Front(Q); break;
			case 4: Queue_Clear(Q); break;
			case 5: Queue_Size(Q); break;
			case 6: Queue_PrintQueue(Q); break;
			case 7: break;
			default: cout << "Input errors,please reenter";
		}
		if (choice == 7)
			exit(0);
		cout << "Press Enter to continue..." << endl;
		getchar();
	};
	return 0;
}