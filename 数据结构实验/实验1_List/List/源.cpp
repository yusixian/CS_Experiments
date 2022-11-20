#include <Windows.h>
#include <iostream>
#include <string>
using namespace std;
class Student {
public:
	string id;	  //ѧ��
	string name;  //ѧ������
	int age;	  //����
	bool operator==(const Student& s) { return id == s.id; }
	bool operator!=(const Student& s) { return id != s.id; }
	bool operator<(const Student& s) { return id < s.id; }
	Student() : name("С��"), age(18) {}
	friend istream& operator>>(istream& is, Student& s) {
		is >> s.id >> s.name >> s.age;
		getchar();
		return is;
	}
	friend ostream& operator<<(ostream& os, const Student& s) {
		os << "ѧ��:" << s.id << "  ����:" << s.name << "  ����:" << s.age
		   << endl;
		return os;
	}
};
template <class T> class List;
//��㶨��
template <class T> class LNode {
private:
	LNode* next;  //ָ��
	T Data;		  //����
public:
	friend class List<T>;
	LNode() { next = nullptr; }
	void showdata() { cout << Data << endl; }
};

//��������ඨ��
template <class T> class List {
private:
	LNode<T>* head;	 //ͷ��� ���洢Ԫ�ص�����ռ�
public:
	friend class LNode<T>;
	List();
	~List();
	LNode<T>* FindKth(int K);  //����Ų��Ҳ��� ���������е�K��Ԫ��
							   //���ҵ�����ָ��ý���ָ�룬�Ҳ������ؿ�ָ��
	LNode<T>* Find(T data);	 //��ֵ����: ����Ԫ��data
							 //���ҵ�����ָ��ý���ָ�룬�Ҳ������ؿ�ָ��
	void
	Delete(int pos =
			   1);	//ɾ������(ɾ�������pos��λ���ϵĽ��) Ĭ��Ϊɾ��һ��Ԫ��
	void Insert(T data, int pos = 1);  //Ĭ��Ϊͷ�巨 ��data�����ڵ�pos��Ԫ��
	void PrintList();				   //չʾ������
	int getLength();				   //��ȡ��������
	void ReverseList();				   //��ת������
};

//���������ʵ��
//���캯�� Ϊhead����ռ䣬��������
template <class T> List<T>::List() {
	head = new LNode<T>;
	head->next = nullptr;
}
//�������� �ͷſռ�
template <class T> List<T>::~List() {
	while (head->next) {
		Delete(1);
	}
	delete head;
}
//(1) ����Ų���::���������е�K��Ԫ��
// ���ҵ�����ָ��ý���ָ�룬�Ҳ������ؿ�ָ��
template <class T> LNode<T>* List<T>::FindKth(int K) {
	LNode<T>* p = head->next;  //��һ��Ԫ��
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
		return p;  //�ҵ���K���򷵻�ָ��
	else {		   //����λ�ò��Ϸ������ؿ�ָ��
		cout << "The location is illegal." << endl;
		return nullptr;
	}
}

//(2) ��ֵ����: ����Ԫ��data
//���ҵ�����ָ��ý���ָ�룬�Ҳ������ؿ�ָ��
template <class T> LNode<T>* List<T>::Find(T data) {
	LNode<T>* p = head->next;
	if (!p) {
		cout << "Element not found,This List is empty!" << endl;
		return nullptr;
	}
	while (p->next && p->Data != data)
		p = p->next;
	if (p->Data != data) {  //������˵�Ԫ���Բ���data
		cout << "Element not found!" << endl;
		return nullptr;
	}
	else
		return p;
}

//(3) ɾ������:ɾ�������pos��λ���ϵĽ��,Ĭ��Ϊɾ��һ��Ԫ��
template <class T>
void List<T>::Delete(int pos) {	 //ɾ������(ɾ�������i��λ���ϵĽ��)
	LNode<T>* p = head->next;
	if (!p) {
		cout << "Deleted failed,This List is empty!" << endl;
		return;
	}
	if (pos == 1) {	 //��Ҫɾ�����Ǳ�ĵ�һ�����
		head->next = p->next;
		if (p)
			delete p;
		return;
	}
	LNode<T>* s = FindKth(pos - 1);	 //�ҵ���pos-1��Ԫ��
	if (!s) {
		cout << "The " << pos-1 << " node does not exist!" << endl;
		return;
	}
	p = s->next;
	if (!p) {
		cout << "The " << pos << " node does not exist!" << endl;
		return;
	} else {
		s->next = p->next;	// sָ���pos+1�����
		delete p;			//��p��������ɾ��
		cout << "Successfully deleted!" << endl;
	}
}

//(4)������� Ĭ��Ϊͷ�巨 ��data�����ڵ�pos��Ԫ��
template <class T> void List<T>::Insert(T data, int pos) {
	LNode<T>* p = new LNode<T>();//�����½ڵ�p�Ŀռ�
	p->Data = data;
	if (pos == 1) {	 //���ڵ�һ��
		p->next = head->next;
		head->next = p;
		cout << "Successfully Inserted!" << endl;
		return;
	}
	LNode<T>* s = FindKth(pos - 1);	 //�ҵ���pos-1��Ԫ��
	if (!s) {
		cout << "The location is illegal,Insertion failed!" << endl;
		return;
	}
	p->next = s->next;
	s->next = p;
	cout << "Successfully Inserted!" << endl;
}

//(5)��ȡ��������
template <class T> int List<T>::getLength() {
	LNode<T>* p = head;	 // pָ����ͷ�ڵ�
	int cnt = 0;
	while (p->next) {
		p = p->next;
		cnt++;
	}
	return cnt;
}
//(6)չʾ������
template <class T> void List<T>::PrintList() {
	LNode<T>* p = head;	 // pָ����ͷ�ڵ�
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
//(7)��ת������
template <class T> void List<T>::ReverseList() {
	LNode<T>* now = head->next;	 // nowָ���ĵ�һ���ڵ�
	if (!now) {
		cout << "This List is empty!" << endl;
		return;
	}
	LNode<T>* tmp = now->next;	// ָ��now֮���һ���ڵ�
	while (tmp) {				//��tmp�ŵ�ͷ�����
		now->next = tmp->next;
		tmp->next = head->next;
		head->next = tmp;
		tmp = now->next;
	}
}
//�������е��õĺ���
template <class T> void input(List<T>& Head) {
	T data;
	cout << "����������Ԫ��(�Կո������س�����):";
	cin >> data;
	Head.Insert(data);
}
template <class T> void remove(List<T>& Head) {
	int i;
	cout << "������i(ɾ�������i��Ԫ��):";
	cin >> i;
	getchar();

	Head.Delete(i);
}
template <class T> void findKth(List<T>& Head) {
	int K;
	LNode<T>* s = nullptr;
	cout << "(����Ų���)������K�����������е�K��Ԫ��:";
	cin >> K;
	getchar();
	s = Head.FindKth(K);
	if (!s)
		cout << "δ�ҵ�!" << endl;
	else {
		cout << "���ҳɹ�!��Ԫ��Ϊ:";
		s->showdata();
	}
}
template <class T> void findData(List<T>& Head) {
	string data;
	cout << "�����������ѧ����ѧ��:";
	cin >> data;
	Student t;
	t.id = data;
	getchar();
	LNode<T>* s = nullptr;
	s = Head.Find(t);
	if (!s)
		cout << "δ�ҵ���Ԫ�أ�" << endl;
	else {
		cout << "���ҳɹ�!��Ԫ���������С�";
	}
}
template <class T> void insert(List<T>& Head) {
	int i;
	T data;
	cout << "�������i��λ���ϲ���һ��ѧ����Ϣ,����i:";
	cin >> i;
	cout << "�����ѧ����Ϣ��ѧ�� ���� �����Կո������س�����:";
	cin >> data;
	Head.Insert(data, i);
}
template <class T> inline void getlength(List<T>& Head) {
	cout << "��������Ϊ:" << Head.getLength() << endl;
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
	cout << "1 ���һ��ѧ����Ϣ" << endl;
	cout << "2 ɾ�������i��Ԫ��" << endl;
	cout << "3 ����Ų��������е�K��Ԫ��" << endl;
	cout << "4 ��ֵ����Ԫ��data" << endl;
	cout << "5 �������i��λ���ϲ���Ԫ��data" << endl;
	cout << "6 ��ȡ��������" << endl;
	cout << "7 ��ӡ����ѧ����Ϣ" << endl;
	cout << "8 ��ת������" << endl;
	cout << "9 ����" << endl;
	while (1) {
		cout << "�˵�ѡ��(1-6):";
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
			default: cout << "�����������������";
		}
		if (choice == 9)
			exit(0);
		cout << "���س���������" << endl;
		getchar();
	};
	return 0;
}