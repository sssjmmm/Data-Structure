#ifndef _SJM_TREE_
#define _SJM_TREE_
#include "sjm_queue.h"
template <class T>
struct TreeNode {
	T data;//�������
	TreeNode<T>* firstChild, * nextSibling;//��Ů���ֵ�ָ��
	TreeNode(T value = 0, TreeNode<T>* fc = NULL, TreeNode<T>* ns = NULL)
		:data(value), firstChild(fc), nextSibling(ns) {}//���캯��
};

template<class T>
class Tree {
private:
	TreeNode<T>* root, * current;//��ָ�뼰��ǰָ��
public:
	Tree() {//���캯��,����һ������
		root = current = NULL;
	};
	~Tree() {//��������
		makeEmpty();
		delete root;
	};
	void set_root(T r);//���ø����
	bool Root();//currentΪ���ڵ�
	bool IsEmpty() {//�жϸ����Ƿ�Ϊ��
		return (root == NULL) ? true : false;
	};
	TreeNode<T>* get_root();//���ظ��ڵ�ĵ�ַ
	TreeNode<T>* get_current();//����current����ַ
	bool FirstChild();//current��Ϊ��ǰ���ĵ�һ������
	bool NextSibling();//Ѱ�ҵ�ǰ������һ���ֵܣ�ʹ֮��Ϊ��ǰ���
	bool Parent();//Ѱ�ҵ�ǰ���ĸ��ף�ʹ֮��Ϊ��ǰ���
	bool Find(T target);//��������������target�Ľ�㣬ʹ֮��Ϊ��ǰ���
	bool Find(TreeNode<T>* p, T value);//����pΪ������������value
	void change_data(T old_data, T new_data);//����old_data��ֵ
	void makeEmpty();//�����ÿ�
	void insert(T father_data, T son_data);//����fatherΪ�������ӽڵ����һ��son���
	void output_children(T father_data);//��������ǵ�data��currentָ����
	void remove_subtree(TreeNode<T>* q);//ɾ����qΪ��������
	bool FindParent(TreeNode<T>* t, TreeNode<T>* p);//�ҵ�p���ĸ��׽��
	TreeNode<T>* find_value(T val);//����ֵΪval���ĵ�ַ
};

template<class T>
void Tree<T>::set_root(T r) {
	root = new TreeNode<T>(r, NULL, NULL);
	if (root == NULL) {
		cerr << "���ڵ�洢�������" << endl;
		return;
	}
}
template<class T>
bool Tree<T>::Root() {//�Ѹ��ڵ㸳����ǰ���
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
TreeNode<T>* Tree<T>::get_root() {//�Ѹ��ڵ㸳����ǰ���
	return this->root;
};

template<class T>
TreeNode<T>* Tree<T>::get_current() {//�Ѹ��ڵ㸳����ǰ���
	return this->current;
};
template<class T>
bool Tree<T>::Parent() {
	TreeNode<T>* p = current;
	if (current == NULL || current == root) {
		current = NULL;
		return false;//�������Ϊ��ǰ��㣬����false
	}
	return FindParent(root, p);//�Ӹ���ʼ��*p�ĸ��׽��
};

template<class T>
bool Tree<T>::FindParent(TreeNode<T>* t, TreeNode<T>* p) {
	//�ڸ�Ϊ*t��������*p�ĸ���㣬��ʹ֮��Ϊ��ǰ��㡣
	TreeNode<T>* q = t->firstChild;
	bool succ;
	while (q != NULL && q != p) {//�ڸ��ĳ��ӵ��ֵ���������
		if ((succ = Findparent(q, p)) == true)
			return succ;//�ҵ����׽��
		q = q->nextSibling;
	}
	if (q != NULL && q == p) {
		current = t;
		return true;
	}
	else {
		current = NULL;
		return false;//û�ҵ����׽��
	}
};

template<class T>
bool Tree<T>::FirstChild() {
	//�������ҵ�ǰ���ĳ��ӣ���ʹ֮��Ϊ��ǰ���
	if (current != NULL && current->firstChild != NULL) {
		current = current->firstChild;
		return true;
	}
	current = NULL;
	return false;
};

template<class T>
bool Tree<T>::NextSibling() {
	//�������ҵ�ǰ������һ���ֵܣ���ʹ֮��Ϊ��ǰ���
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
	//����δ�������������ĸ������*p���ҵ���ý���Ϊ��ǰ��㣬����ǰ��㲻��
	bool result = false;
	Queue<TreeNode<T>*>Q;
	if (p != NULL) {//������Ϊ��
		Q.push(p);//��ָ�������
		while (!Q.empty()) {
			p = Q.front();//������ȡһ���ڵ�
			Q.pop();
			if (p->data == value) {
				result = true;
				current = p;
				return result;
			}//�����ɹ�
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
	if (p != NULL) {//������Ϊ��
		Q.push(p);//��ָ�������
		while (!Q.empty()) {//���в���
			t = Q.front();//������ȡһ���ڵ�
			Q.pop();
			for (p = t->firstChild; p != NULL; p = p->nextSibling)
				Q.push(p);
			if (t != q) {//ͷ��㲻delete
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
		cerr << "�洢�������" << endl;
		return;
	}
	//�ҵ�father���һ����Ů�������ֵ�ָ��ָ��son
	if (current->firstChild == NULL) {//û�ж���
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
TreeNode<T>* Tree<T>::find_value(T val) {//����ֵΪval���ĵ�ַ
	Find(root, val);
	return get_current();
}
template<class T>
void Tree<T>::change_data(T old_data, T new_data) {
	Find(root, old_data);
	current->data = new_data;
}

#endif