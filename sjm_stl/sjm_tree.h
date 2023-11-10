#ifndef _SJM_TREE_
#define _SJM_TREE_
#include "sjm_queue.h"
template <class T>
struct TreeNode {
	T data;//结点数据
	TreeNode<T>* firstChild, * nextSibling;//子女及兄弟指针
	TreeNode(T value = 0, TreeNode<T>* fc = NULL, TreeNode<T>* ns = NULL)
		:data(value), firstChild(fc), nextSibling(ns) {}//构造函数
};

template<class T>
class Tree {
private:
	TreeNode<T>* root, * current;//根指针及当前指针
public:
	Tree() {//构造函数,建立一个空树
		root = current = NULL;
	};
	~Tree() {//析构函数
		makeEmpty();
		delete root;
	};
	void set_root(T r);//设置根结点
	bool Root();//current为根节点
	bool IsEmpty() {//判断该树是否为空
		return (root == NULL) ? true : false;
	};
	TreeNode<T>* get_root();//返回根节点的地址
	TreeNode<T>* get_current();//返回current结点地址
	bool FirstChild();//current变为当前结点的第一个儿子
	bool NextSibling();//寻找当前结点的下一个兄弟，使之成为当前结点
	bool Parent();//寻找当前结点的父亲，使之成为当前结点
	bool Find(T target);//在树中搜索含有target的结点，使之成为当前结点
	bool Find(TreeNode<T>* p, T value);//在以p为根的树中搜索value
	void change_data(T old_data, T new_data);//更改old_data的值
	void makeEmpty();//把树置空
	void insert(T father_data, T son_data);//在以father为父结点的子节点插入一个son结点
	void output_children(T father_data);//输出孩子们的data，current指向父亲
	void remove_subtree(TreeNode<T>* q);//删除以q为根的子树
	bool FindParent(TreeNode<T>* t, TreeNode<T>* p);//找到p结点的父亲结点
	TreeNode<T>* find_value(T val);//返回值为val结点的地址
};

template<class T>
void Tree<T>::set_root(T r) {
	root = new TreeNode<T>(r, NULL, NULL);
	if (root == NULL) {
		cerr << "根节点存储分配出错！" << endl;
		return;
	}
}
template<class T>
bool Tree<T>::Root() {//把根节点赋给当前结点
	if (root == NULL) {
		current = NULL;
		return false;
	}
	else {
		current = root;
		return true;
	}
};

template<class T>
TreeNode<T>* Tree<T>::get_root() {//把根节点赋给当前结点
	return this->root;
};

template<class T>
TreeNode<T>* Tree<T>::get_current() {//把根节点赋给当前结点
	return this->current;
};
template<class T>
bool Tree<T>::Parent() {
	TreeNode<T>* p = current;
	if (current == NULL || current == root) {
		current = NULL;
		return false;//空树或根为当前结点，返回false
	}
	return FindParent(root, p);//从根开始找*p的父亲结点
};

template<class T>
bool Tree<T>::FindParent(TreeNode<T>* t, TreeNode<T>* p) {
	//在根为*t的树种找*p的父结点，并使之成为当前结点。
	TreeNode<T>* q = t->firstChild;
	bool succ;
	while (q != NULL && q != p) {//在根的长子的兄弟链中搜索
		if ((succ = Findparent(q, p)) == true)
			return succ;//找到父亲结点
		q = q->nextSibling;
	}
	if (q != NULL && q == p) {
		current = t;
		return true;
	}
	else {
		current = NULL;
		return false;//没找到父亲结点
	}
};

template<class T>
bool Tree<T>::FirstChild() {
	//在树中找当前结点的长子，并使之成为当前结点
	if (current != NULL && current->firstChild != NULL) {
		current = current->firstChild;
		return true;
	}
	current = NULL;
	return false;
};

template<class T>
bool Tree<T>::NextSibling() {
	//在树中找当前结点的下一个兄弟，并使之成为当前结点
	if (current != NULL && current->nextSibling != NULL) {
		current = current->nextSibling;
		return true;
	}
	current = NULL;
	return false;
};

template<class T>
bool Tree<T>::Find(T value) {
	if (IsEmpty() == true)
		return false;
	return Find(root, value);
};



template<class T>
bool Tree<T>::Find(TreeNode<T>* p, T value) {
	//按层次次序遍历树，树的根结点是*p。找到后该结点成为当前结点，否则当前结点不变
	bool result = false;
	Queue<TreeNode<T>*>Q;
	if (p != NULL) {//当树不为空
		Q.push(p);//根指针进队列
		while (!Q.empty()) {
			p = Q.front();//队伍中取一个节点
			Q.pop();
			if (p->data == value) {
				result = true;
				current = p;
				return result;
			}//搜索成功
			for (p = p->firstChild; p != NULL; p = p->nextSibling)
				Q.push(p);
		}
	}
	return result;
};

template<class T>
void Tree<T>::makeEmpty() {
	remove_subtree(root);
};

template<class T>
void Tree<T>::remove_subtree(TreeNode<T>* q) {
	Queue<TreeNode<T>*>Q;
	TreeNode<T>* p = q, * t;
	if (p != NULL) {//当树不为空
		Q.push(p);//根指针进队列
		while (!Q.empty()) {//队列不空
			t = Q.front();//队伍中取一个节点
			Q.pop();
			for (p = t->firstChild; p != NULL; p = p->nextSibling)
				Q.push(p);
			if (t != q) {//头结点不delete
				delete t;
			}
			else {
				q->firstChild = NULL;
			}
		}
	}
}

template<class T>
void Tree<T>::insert(T father_data, T son_data) {
	Find(root, father_data);
	TreeNode<T>* pt = new TreeNode<T>(son_data, NULL, NULL);
	if (pt == NULL) {
		cerr << "存储分配出错！" << endl;
		return;
	}
	//找到father最后一个儿女，他的兄弟指针指向son
	if (current->firstChild == NULL) {//没有儿子
		current->firstChild = pt;
	}
	else {
		current = current->firstChild;
		while (current->nextSibling != NULL)
			current = current->nextSibling;
		current->nextSibling = pt;
	}
}

template<class T>
void Tree<T>::output_children(T father_data) {
	Find(root, father_data);
	TreeNode<T>* p = current->firstChild;
	while (p != NULL) {
		cout << p->data << " ";
		p = p->nextSibling;
	}
}

template<class T>
TreeNode<T>* Tree<T>::find_value(T val) {//返回值为val结点的地址
	Find(root, val);
	return get_current();
}
template<class T>
void Tree<T>::change_data(T old_data, T new_data) {
	Find(root, old_data);
	current->data = new_data;
}

#endif