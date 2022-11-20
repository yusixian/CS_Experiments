//二叉树链表存储
#include <iostream>
#define error -1
using namespace std;
template <class T> class BTree;
//二叉树结点定义
template <class T> class BTNode {
private:
	T data;		  //数据
	BTNode* left;  //左孩子
	BTNode* right;  //右孩子
public:
	friend class BTree<T>;
	BTNode() :left(nullptr), right(nullptr) {}	 //空结点
	BTNode(T d) :data(d), left(nullptr), right(nullptr) {} //有数据的结点
};
//二叉树操作类定义 一个类
template <class T> class BTree {
public:
	BTNode<T>* root;		//该二叉树的根结点
	BTree() :root(nullptr) {}		//构造函数
	~BTree() { Clear(root); }		//析构函数 回收空间
	bool IsEmpty();				//判断二叉树是否为空（root是否存在）
	void Clear(BTNode<T>* R);			//清空该二叉树
	void PreorderTraversal(BTNode<T>* R);		//先序遍历
	void InorderTraversal(BTNode<T>* R);		//中序遍历
	void PostorderTraversal(BTNode<T>* R);		//后序遍历
	//根据完整先序遍历序列（子树空用’#’表示），重建二叉树
	void Rebuild(BTNode<T>** R);	//返回当前树用了多少结点
};
//二叉树操作类实现
//判断二叉树是否为空（root是否存在）
template <class T> bool BTree<T>::IsEmpty() {
	if (!root) return true;
	else return false;
}
//清空该二叉树
template <class T> void BTree<T>::Clear(BTNode<T>* R) {
	if (R) {
		if (R->left) Clear(R->left);
		if (R->right) Clear(R->right);
		delete R;
	}
}
//先序遍历
template <class T> void BTree<T>::PreorderTraversal(BTNode<T>* R) {
	if (R) {	//根左右
		cout << R->data;	//先访问根节点 进行访问或其他操作
		PreorderTraversal(R->left);
		PreorderTraversal(R->right);
	}
}
//中序遍历
template <class T> void BTree<T>::InorderTraversal(BTNode<T>* R) {
	if (R) {	//左根右
		InorderTraversal(R->left);
		cout << R->data;	//访问根节点 进行访问或其他操作
		InorderTraversal(R->right);
	}
}
//后序遍历
template <class T> void BTree<T>::PostorderTraversal(BTNode<T>* R) {
	if (R) {	//左右根
		PostorderTraversal(R->left);
		PostorderTraversal(R->right);
		cout << R->data;	//最后访问根节点 进行访问或其他操作
	}
}

//根据完整先序遍历序列（子树空用’#’表示），重建二叉树 
template <class T> void BTree<T>::Rebuild(BTNode<T>** R) {
	char ch;
	//scanf("%c", &ch);
	ch = getchar();
	if (ch == '#') *R = nullptr;
	else {
		(*R) = new BTNode<T>;
		(*R)->data = ch;
		Rebuild(&((*R)->left));
		Rebuild(&((*R)->right));
	}
}
//主函数中调用的函数 (测试用)
template <class T> void BinTree_Rebuild(BTree<T>& R) {
	R.Clear(R.root);
	cout << "Please input complete preorder traversal sequence:" << endl;
	R.Rebuild(&R.root);
	getchar();
	cout << "Successfully Rebuild!" << endl;
}
template <class T> void BinTree_Preorder(BTree<T>& R) {
	cout << "The preorder traversal sequence is:";
	if (R.root) R.PreorderTraversal(R.root);
	else cout << "The BinaryTree is Empty!" << endl;
	cout << endl;
}
template <class T> void BinTree_Inorder(BTree<T>& R) {
	cout << "The inorder traversal sequence is:";
	if (R.root) R.InorderTraversal(R.root);
	else cout << "The BinaryTree is Empty!" << endl;
	cout << endl;
}
template <class T> void BinTree_Postorder(BTree<T>& R) {
	cout << "The postorder traversal sequence is:";
	if (R.root) R.PostorderTraversal(R.root);
	else cout << "The BinaryTree is Empty!" << endl;
	cout << endl;
}
int main() {
	BTree<char> R;//字符型
	BinTree_Rebuild(R);
	cout << "You can do the following operation" << endl;
	cout << "1 Rebuild By PreorderTraversal" << endl;
	cout << "2 PreorderTraversal" << endl;
	cout << "3 InorderTraversal" << endl;
	cout << "4 PostOrderTraversal" << endl;
	cout << "5 Exit" << endl;
	while (1) {
		int choice;
		cout << "Please chose:";
		cin >> choice;
		getchar();
		switch (choice) {
		case 1: BinTree_Rebuild(R); break;
		case 2: BinTree_Preorder(R); break;
		case 3: BinTree_Inorder(R); break;
		case 4: BinTree_Postorder(R); break;
		case 5: break;
		default: cout << "Input errors,please reenter!" << endl;
		}
		if (choice == 5)
			exit(0);
		cout << "Press Enter to continue..." << endl;
		getchar();
	};
	return 0;
}