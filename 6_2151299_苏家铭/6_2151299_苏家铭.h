#ifndef _06_
#define _06_
#include <iostream>
using namespace std;
#define STRING_DEFAULT_SIZE 50

/*带附加头结点的双向循环链表的类定义*/
 
template<class T>
struct DblNode {//链表节点类
	T data;//链表结点数据
	DblNode<T>* lLink, * rLink;//链指针域,前驱（左链）、后继（右链）
	DblNode(DblNode<T>* left = NULL, DblNode<T>* right = NULL) {
		lLink = left;
		rLink = right;
	}//仅初始化指针成员的构造函数
	DblNode(const T& item, DblNode<T>* left = NULL, DblNode<T>* right = NULL) {
		data = item;
		lLink = left;
		rLink = right;
	}//初始化模板数据与指针成员的构造函数
	DblNode(const T& item, DblNode<T>* right) {
		data = item;
		rLink = right;
	}//初始化模板数据与右指针成员的构造函数
};

template<class T>
class DblList {
protected:
	DblNode<T>* first;
public:
	DblList() {
		first = new DblNode<T>;
		if (first == NULL) {
			cerr << "存储分配出错！" << endl;
			return;
		}
		first->rLink = first->lLink = first;
	}//构造函数
	DblList(T uniqueVal) {
		first = new DblNode<T>(uniqueVal);
		if (first == NULL) {
			cerr << "存储分配出错！" << endl;
			return;
		}
		first->rLink = first->lLink = first;
	}//构造函数:建立双向循环链表的附加头结点，它包含了一个用于某些特定情况的值
	DblList(const DblList<T>& L);//复制构造函数
	~DblList() {
		makeEmpty();
		delete first;
	}//析构函数

	void makeEmpty();//将链表置为空表
	int Length()const;//计算双链表的长度
	DblNode<T>* getHead()const {
		return first;
	}//返回附加头结点地址
	void setHead(DblNode<T>* ptr) {
		first = ptr;
	}//设置附加头结点地址
	DblNode<T>* Search(const T& x);//在链表中沿后继寻找等于数据x的元素
	DblNode<T>* Locate(int i, int d);//在链表中定位序号为i（>=0）的结点，d=0按前驱方向，d!=0按后继方向
	bool getDate(int i, T& x, int d);//取出按d方向第i个元素的地址
	void setData(int i, T& x, int d);//用x修改按d方向第i个元素的值
	bool Inset(int i, const T& x, int d);//在第i个元素后插入x,d=0按前驱方向，d!=0按后继方向
	bool Remove(int i, T& x, int d);//删除第i个元素,x返回该元素的值,d=0按前驱方向，d!=0按后继方向
	bool IsEmpty()const {
		return first->rLink == first ? true : false;
	}//判表空否?空则返回true
	bool IsFull()const { return false; }//判表满否？不满则返回false
	void push_back(T data);//在尾部插入一个数据
	void push_front(T data);//在前部插入一个数据

	//void Sort() {};//排序  待实现
	void input_num(int i);//输入i个元素
	void input_endTag(T endTag);//输入若干元素，直到遇到endTag
	void output(int d);//输出
	DblList<T>& operator= (const DblList<T>& L);//重载函数：赋值

	template<class E>
	friend class Queue;
};

//DblList类的成员函数的实现
template<class T>
DblList<T>::DblList(const DblList<T>& L) {
	//复制构造函数
	T value;
	DblNode<T>* srcptr = L.getHead();//被复制表的附加头结点地址
	DblNode<T>* destptr = first = new DblNode<T>;
	while (srcptr->rLink != L.first) {//逐个节点复制
		value = srcptr->rLink->data;
		destptr->rLink = new DblNode<T>(value);
		destptr->rLink->lLink = destptr;
		destptr = destptr->rLink;
		srcptr = srcptr->rLink;
	}
	destptr->rLink = first;
	destptr->rLink->lLink = destptr;
};

template <class T>
void DblList <T>::makeEmpty() {
	//将链表置为空表
	DblNode<T>* q;
	while (first->rLink != first) {//当链不空时，删去链中所有节点
		q = first->rLink;
		first->rLink = q->rLink;//保存被删结点，从链上摘下该结点
		delete q;//删除（仅保留一个表头结点）
	}
};

template <class T>
int DblList<T>::Length()const {
	//计算带附加头结点的单链表长度
	DblNode<T>* p = first->rLink;
	int count = 0;
	while (p != first) {//循链扫描，寻找链尾
		p = p->rLink;
		count++;
	}
	return count;
};

template <class T>
DblNode<T>* DblList<T>::Search(const T& x) {
	//在表中搜索含数据x的结点，搜索成功时函数返回该结点地址；否则返回NULL值
	DblNode<T>* current = first->rLink;
	while (current != first && current->data != x) {//循链找含x的结点
		current = current->rLink;
	}
	if (current != first)//搜索成功
		return current;
	else//搜索失败
		return NULL;
};

template<class T>
DblNode<T>* DblList<T>::Locate(int i, int d) {
	//定位函数。返回表中第i个元素的地址。若i<0或i超出表中结点个数，则返回NULL。
	//在带附加头结点的双向循环列表中按d所指方向寻找第i个结点的地址。若d=0，在前驱方向
	//寻找第i个结点，若d!=0，在后继方向寻找第i个结点。
	if (i < 0)
		return NULL;
	DblNode <T>* current;
	if (d == 0)
		current = first->lLink;
	else
		current = first->rLink;

	for (int j = 1; j < i; j++) {//逐个结点检测
		if (current == first)//链太短退出搜索
			break;
		else if (d == 0)
			current = current->lLink;
		else
			current = current->rLink;
	}
	if (current != first)
		return current;//搜索成功
	else
		return NULL;//搜索失败

};

template <class T>
bool DblList <T>::getDate(int i, T& x, int d) {
	//取出表中按d所指示方向的第i个元素的值
	if (i < 0)//i太小
		return NULL;
	DblNode<T>* current = Locate(i, d);
	if (current == NULL)//i太大
		return false;
	else {
		x = current->data;
		return true;
	}
};

template<class T>
void DblList <T>::setData(int i, T& x, int d) {
	//给链表中第i个元素赋值x。
	if (i <= 0)
		return;
	DblNode<T>* current = Locate(i, d);
	if (current == NULL)//i太大
		return;
	else {
		current->data = x;
	}
};

template <class T>
bool DblList<T>::Inset(int i, const T& x, int d) {
	//将新元素x按d指定的方向插入在链表中第i个结点之后。
	DblNode<T>* current = Locate(i, d);//查找第i个结点
	if (current == NULL)
		return false;//插入不成功
	DblNode<T>* newNode = new DblNode<T>(x);
	if (newNode == NULL) {
		cerr << "存储分配错误！" << endl;
		return false;
	}
	if (d == 0) {//前驱方向插入
		newNode->lLink = current->lLink;//链接在current之后
		current->lLink = newNode;
		newNode->lLink->rLink = newNode;
		newNode->rLink = current;
	}
	else {//后继方向插入
		newNode->rLink = current->rLink;//链接在current之后
		current->rLink = newNode;
		newNode->rLink->lLink = newNode;
		newNode->lLink = current;
	}
	return true;//插入成功
};

template <class T>
bool DblList <T>::Remove(int i, T& x, int d) {
	//将链表中的第i个元素按照d所指方向删去，通过引用型参数x返回该元素的值。
	DblNode<T>* current = Locate(i, d);
	if (current == NULL)
		return false;//删除不成功
	current->rLink->lLink = current->lLink;//从lLink链中摘下
	current->lLink->rLink = current->rLink;//从lLink链中摘下
	x = current->data;//取出被删结点中的数据值
	delete current;
	return true;//删除成功
};

template <class T>
void DblList<T>::output(int d) {
	//双循环链表的输出函数：将链表中所有数据按d所指方向输出到屏幕上。d=0,向前驱，d!=0按后继
	DblNode<T>* current;
	if (d == 0)
		current = first->lLink;
	else
		current = first->rLink;
	while (current != first) {
		cout << current->data << " ";
		if (d == 0)
			current = current->lLink;
		else
			current = current->rLink;
	}
};

template <class T>
DblList<T>& DblList<T>::operator= (const DblList<T>& L) {
	//重载函数：赋值操作，形如A=B，其中A是调用此操作的DblList对象，B是与参数表中的引用型参数L结合的实参
	T value;
	DblNode<T>* srcptr = L.getHead();//被复制表的附加头结点地址
	DblNode<T>* destptr = first = new DblNode<T>;
	while (srcptr->rLink != L.first) {//逐个节点复制
		value = srcptr->rLink->data;
		destptr->rLink = new DblNode<T>(value);
		destptr->rLink->lLink = destptr;
		destptr = destptr->rLink;
		srcptr = srcptr->rLink;
	}
	destptr->rLink = first;
	destptr->rLink->lLink = destptr;
	return*this;//返回操作对象地址

}

template<class T>
void DblList<T>::input_num(int i) {//后插法，一个个向后插入i个元素
	DblNode<T>* newNode, * last;
	int end = 1;
	T val;
	if (i < 1)
		return;
	makeEmpty();
	last = first;
	while (end++ <= i) {
		cin >> val;
		newNode = new DblNode<T>(val);
		if (newNode == NULL) {
			cerr << "存储分配错误！" << endl;
			return;
		}
		last->rLink = newNode;
		last->rLink->lLink = last;
		last = newNode;
	}
	last->rLink = first;//表收尾，这2句实际可省略
	last->rLink->lLink = last;
}

template<class T>
void DblList<T>::input_endTag(T endTag) {//后插法，一个个向后插入元素，直到遇到endTag
	//endTag是约定的输入序列结束的标志。如果输入序列是正整数，endTag可以是0或者负数；
	//如果输入序列是字符，endTag可以是字符集中不会出现的字符，如"\0"
	DblNode<T>* newNode, * last;
	T val = 0;
	makeEmpty();
	last = first;
	while (1) {
		cin >> val;
		if (cin.fail()) {
			cout << "输入错误！请从错误输入字符开始继续输入" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else {
			if (val == endTag)
				break;
			newNode = new DblNode<T>(val);
			if (newNode == NULL) {
				cerr << "存储分配错误！" << endl;
				return;
			}
			last->rLink = newNode;
			last->rLink->lLink = last;
			last = newNode;
		}
	}
	last->rLink = first;//表收尾，这2句实际可省略
	last->rLink->lLink = last;
};
template <class T>
void DblList<T>::push_back(T data)//在链表末尾插入一个元素
{
	DblNode<T>* newNode, * last;
	newNode = new DblNode<T>(data, NULL, NULL);
	if (newNode == NULL) {
		cerr << "存储分配错误！" << endl;
		return;
	}
	last = first->lLink;
	last->rLink = newNode;
	last->rLink->lLink = last;
	last = newNode;
	last->rLink = first;
	first->lLink = last;
};
template <class T>
void DblList<T>::push_front(T data)//在链表前端插入一个元素
{
	DblNode<T>* newNode;
	newNode = new DblNode<T>(data);
	if (newNode == NULL) {
		cerr << "存储分配错误！" << endl;
		return;
	}

	newNode->rLink = first->rLink;
	first->rLink->lLink = newNode;
	first->rLink = newNode;
	newNode->lLink = first;
}

template<class T>
class Queue {
private:
	DblList<T> list;
public:
	//构造函数
	Queue() {
		list.makeEmpty();
	};
	//析构函数
	~Queue() { list.makeEmpty(); };
	//入队
	void push(const T& val);
	//出队
	void pop();
	//置空
	void makeEmpty();
	//判断空否
	bool empty()const;
	//返回队列大小
	int size()const;
	//返回队首元素
	const T& front();
};
template<class T>
void Queue<T>::push(const T& val) {
	this->list.push_back(val);
};
template<class T>
void Queue<T>::pop() {
	T temp;
	this->list.Remove(1, temp, 1);

};
template<class T>
void Queue<T>::makeEmpty() {
	this->list.makeEmpty();
};
template<class T>
bool Queue<T>::empty()const {
	return this->list.IsEmpty();
};
template<class T>
int Queue<T>::size()const {
	return this->list.size();
};
template<class T>
const T& Queue<T>::front() {
	return list.first->rLink->data;
}

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



class String
{
private:
	char* elements;
	int size;
	int capacity;

	//扩容
	void expand();
public:
	//求指定字符串常量的长度
	static int length_of_str(const char* ptr);
	//判断是否为数字
	static inline bool isdigit(char word)
	{
		return word >= '0' && word <= '9';
	}
	//判断是否为大写字母
	static inline bool isupper(char word)
	{
		return word >= 'A' && word <= 'Z';
	}
	//判断是否为小写字母
	static inline bool islower(char word)
	{
		return word >= 'a' && word <= 'z';
	}
	//判断是否为字母
	static inline bool isalpha(char word)
	{
		return isupper(word) || islower(word);
	}
	//判断是否为空
	static inline bool isblank(char word)
	{
		return word == '\0';
	}
public:
	//默认构造函数
	String();
	//复制构造函数
	String(const String&);
	//字符串常量方式的构造
	String(const char*);
	//指定长度的构造方式
	String(const char*, int);
	//字符成倍的构造
	String(int, char);

	//析构函数
	~String();

	//重载取下标运算符
	inline char& operator[](int index);
	//重载等号运算符
	String& operator=(const String& s);
	//重载字符串常量的等号运算符
	String& operator=(const char*);
	//重载输入输出
	friend std::istream& operator>>(std::istream& in, String& s);
	friend std::ostream& operator<<(std::ostream& out, const String& s);
	//重载==运算符
	bool operator==(const String& s);
	//重载+运算符
	String operator+(const String& s);
	//重载+=运算符
	String& operator+=(const String& s);

	//重载+运算符 对于char
	String operator+(const char& ch);
	//重载+=运算符 对于char
	String& operator+=(const char& ch);

	//清空字符串
	void clear();

	//返回字符串常量
	const char* c_str()const;

	//返回字符串长度
	int length()const;

	//退出最后一个元素
	void pop_back();

	//友元类
	friend class BigInterger;
};

//默认构造函数
String::String()
{
	this->capacity = STRING_DEFAULT_SIZE;
	this->size = 0;
	//根据默认容量大小分配空间
	this->elements = new char[capacity];
	this->elements[0] = '\0';
}

//复制构造函数
String::String(const String& s)
{
	this->capacity = s.capacity;
	this->size = s.size;
	//分配空间
	this->elements = new char[capacity];


	//复制
	for (int i = 0; i <= size && i < capacity; ++i)
		this->elements[i] = s.elements[i];
}

//字符串常量方式的构造
String::String(const char* s)
{
	//获取字符串常量长度
	int size = 0;
	while (s[size] != '\0')
		size++;

	this->size = size;
	this->capacity = (size / STRING_DEFAULT_SIZE + 1) * STRING_DEFAULT_SIZE;
	this->elements = new char[capacity];

	//一一复制
	for (int i = 0; i <= size; ++i)
		this->elements[i] = s[i];
}

//指定长度的构造方式
String::String(const char* s, int length)
{
	int strLength = this->length_of_str(s);
	this->capacity = (length / STRING_DEFAULT_SIZE + 1) * STRING_DEFAULT_SIZE;
	//计算有效长度
	if (strLength >= length)
		this->size = length;
	else
		this->size = strLength;
	//申请空间
	this->elements = new char[capacity];
	for (int i = 0; i < size; ++i)
		this->elements[i] = s[i];
	this->elements[size] = '\0';
}

//字符成倍的构造
String::String(int num, char word)
{
	this->size = num;
	this->capacity = (size / STRING_DEFAULT_SIZE + 1) * STRING_DEFAULT_SIZE;
	this->elements = new char[capacity];
	for (int i = 0; i < size; ++i)
		this->elements[i] = word;
	this->elements[size] = '\0';

}

//析构函数
String::~String()
{
	delete[]elements;
}

//重载取下标运算符
inline char& String::operator[](int index)
{
	if (index < 0 || index >= size)
		cout << "存取位置过大！";

	return elements[index];
}

//重载等号运算符
String& String::operator=(const String& s)
{
	if (this->elements == s.elements)
		return *this;

	//清空所有元素
	delete[] elements;

	//一一对应
	this->capacity = s.capacity;
	this->size = s.size;
	//分配空间
	this->elements = new char[capacity];


	//复制
	for (int i = 0; i <= size && i < capacity; ++i)
		this->elements[i] = s.elements[i];

	return *this;
}

//重载字符串常量的等号运算符
String& String::operator=(const char* s)
{
	//清空所有元素
	delete[] elements;

	//获取字符串常量长度
	int size = 0;
	while (s[size] != '\0')
		size++;

	this->size = size;
	this->capacity = (size / STRING_DEFAULT_SIZE + 1) * STRING_DEFAULT_SIZE;
	this->elements = new char[capacity];

	//一一复制
	for (int i = 0; i <= size; ++i)
		this->elements[i] = s[i];

	return *this;
}


//清空字符串
void String::clear()
{
	//清空所有元素
	delete[] elements;

	//调用默认构造函数
	this->capacity = STRING_DEFAULT_SIZE;
	this->size = 0;
	//根据默认容量大小分配空间
	this->elements = new char[capacity];

}
//减去最后一个元素
void String::pop_back() {

	elements[--size] = '\0';

}
//扩大容量
void String::expand()
{
	this->capacity = this->capacity + STRING_DEFAULT_SIZE;

	char* oldElements = this->elements;

	//复制
	this->elements = new char[capacity];
	for (int i = 0; i <= size && i < capacity; ++i)
		elements[i] = oldElements[i];

	delete[] oldElements;
}

std::istream& operator>>(std::istream& in, String& s)
{
	in >> s.elements;
	//注意需要更改size
	s.size = s.length_of_str(s.elements);
	return in;
}

std::ostream& operator<<(std::ostream& out, const String& s)
{
	out << s.elements;
	return out;
}

//重载==运算符
bool String::operator==(const String& s)
{
	//判断长度
	if (this->size != s.size)
		return false;
	//逐一对比
	for (int i = 0; i < this->size; ++i)
		if (this->elements[i] != s.elements[i])
			return false;

	return true;
}

//重载+运算符
String String::operator+(const String& s)
{
	String str(this->elements, this->size + s.size);
	str.size = this->size + s.size;
	for (int i = this->size; i < str.size; ++i)
		str.elements[i] = s.elements[i - this->size];
	str.elements[str.size] = '\0';
	return str;
}

String String::operator+(const char& ch)
{
	String str(this->elements, this->size + 1);
	str.size = this->size + 1;
	str.elements[str.size - 1] = ch;
	str.elements[str.size] = '\0';
	return str;
}

//重载+=运算符
String& String::operator+=(const String& s)
{
	this->capacity = ((this->size + s.size) / STRING_DEFAULT_SIZE + 1) * STRING_DEFAULT_SIZE;
	char* newStr = new char[capacity];
	for (int i = 0; i < this->size; ++i)
		newStr[i] = this->elements[i];
	this->size += s.size;
	for (int i = this->size - s.size; i < this->size; ++i)
		newStr[i] = s.elements[i - this->size + s.size];
	newStr[this->size] = '\0';
	delete this->elements;
	this->elements = newStr;
	return *this;
}

String& String::operator+=(const char& ch)
{
	this->capacity = ((this->size + 1) / STRING_DEFAULT_SIZE + 1) * STRING_DEFAULT_SIZE;
	char* newStr = new char[capacity];
	for (int i = 0; i < this->size; ++i)
		newStr[i] = this->elements[i];
	this->size += 1;
	newStr[this->size - 1] = ch;
	newStr[this->size] = '\0';
	delete this->elements;
	this->elements = newStr;
	return *this;
}

//求指定字符串常量的长度
int String::length_of_str(const char* ptr)
{
	int size = 0;
	while (ptr[size] != '\0')
		++size;
	return size;
}

//返回字符串常量
const char* String::c_str()const
{
	return elements;
}

int String::length()const
{
	return this->length_of_str(this->c_str());
}
#endif
