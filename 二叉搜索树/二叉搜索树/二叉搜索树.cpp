#include<iostream>
using namespace std;
//二叉搜索树的结点
template<class T>
struct BSTNode{
	BSTNode(const T& val = T())
	:_left(nullptr)
	, _right(nullptr)
	, _data(val)
	{
	}
	BSTNode<T>* _left;
	BSTNode<T>* _right;
	T _data;
};
//二叉搜索树
template<class T>
class BSTree{
public:
	typedef BSTNode<T> Node;
	typedef Node* pNode;
	BSTree(const pNode root = nullptr)
		:_root(root)
	{}
	//插入新节点
	bool Insert(const T& x){
		if (_root == nullptr){
			_root = new Node(x);
			return true;
		}
		pNode cur = _root;
		pNode parent = nullptr;
		while (cur != nullptr){
			if (cur->_data > x){
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_data < x){
				parent = cur;
				cur = cur->_right;
			}
			else
				return false;
		}
		cur = new Node(x);
		if (parent->_data>x)
			parent->_left = cur;
		if (parent->_data < x)
			parent->_right = cur;
		return true;
	}
	void Print(){
		if (_root == nullptr)
			return;
		_Print(_root);
		cout << endl;
	}
	void _Print(const pNode root){
		if (root == nullptr)
			return;
		_Print(root->_left);
		cout << root->_data << " ";
		_Print(root->_right);
	}
	//删除节点
	bool Esare(const T& x){
		//判断树是否为空
		if (_root == nullptr)
			return false;
		//寻找结点在树中的位置
		pNode parent = nullptr;
		pNode cur = _root;
		while (cur){
			if (cur->_data = x)
				break;
			else if (x < cur->_data){
				parent = cur;
				cur = cur->_left;
			}
			else {
				parent = cur;
				cur = cur->_right;
			}
			//没有找到要删除的结点
			if (cur == nullptr)
				return false;
		}
		//1.删除的是叶子节点
		if (cur->_left == nullptr && cur->_right == nullptr){
			if (cur != _root){
				if (parent->_left == cur)
					parent->_left = nullptr;
				else
					parent->_right = nullptr;
			}
			else
				_root = nullptr;
			delete cur;
			cur = nullptr;
		}
		//2.孩子节点不完整的
		else if (cur->_left == nullptr){
			if (cur != _root){
				if (parent->_left == cur)
					parent->_left = cur->_right;
				else
					parent->_right = cur->_right;
			}
			else
				_root = cur->_right;
			delete cur;
			cur = nullptr;
		}
		else if (cur->_right == nullptr){
			if (cur != _root){
				if (parent->_left == cur)
					parent->_left = cur->_left;
				else
					parent->_right = cur->_left;
			}
			else
				_root = cur->_left;
			delete cur;
			cur = nullptr;
		}
		//3.孩子节点完整的
		//寻找左子树中最大的节点或者右子树中最小的结点
		else {
			pNode LeftMost = cur->_left;
			parent = cur;
			while (LeftMost->_right){
				parent = LeftMost;
				LeftMost = LeftMost->_right;
			}
			//交换
			cur->_data = LeftMost->_data;
			if (parent->_right == LeftMost)
				parent->_right = LeftMost->_left;
			else
				//???????
				parent->_left = LeftMost->_left;
			delete LeftMost;
			LeftMost = nullptr;
		}
		return true;
	}
	//结点的查找
	pNode Find(const T& x){
		if (_root==nullptr)
			return nullptr;
		pNode cur = _root;
		while (cur){
			if (cur->_data == x)
				break;
			else if (x < cur->_data)
				cur = cur->_left;
			else
				cur = cur->_right;
		}
		return cur;
	}
	pNode Copy(pNode root){
		if (root){
			pNode newNode = new Node(root->_data);
			newNode->_left = Copy(root->_left);
			newNode->_right = Copy(root->_right);
			return newNode;
		}
		else
			return nullptr;
	}
	BSTree(BSTree<T>& bst){
		_root = Copy(bst._root);
	}
	BSTNode<T>& operator=(const BSTree<T>& bst){
		if (this != &bst){
			//先对树进行清空
			if (_root){
				_Delete(_root);
			}
			//再将要拷贝的树拷贝过来
			_root = Copy(bst._root)
		}
		return *this;
	}
	~BSTree(){
		_Delete(_root);
	}
private:
	pNode _root;
	 void _Delete(pNode root){
		if (root){
			_Delete(root->_left);
			_Delete(root->_right);
			delete root;
			root = nullptr;
		}
	}
};
void Test(){
	BSTree<int> bt;
	bt.Insert(5);
	bt.Insert(3);
	bt.Insert(7);
	bt.Insert(1);
	bt.Insert(4);
	bt.Insert(6);
	bt.Insert(8);
	bt.Insert(0);
	bt.Insert(2);
	bt.Insert(9);
	bt.Insert(10);
	bt.Print();
	BSTree<int> bt1 = bt;
	bt1.Print();
}
int main(){
	Test();
	system("pause");
	return 0;
}