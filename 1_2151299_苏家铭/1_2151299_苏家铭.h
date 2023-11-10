#ifndef _MAIN01_
#define _MAIN01_
#include<iostream>
#include<iomanip>
#include<assert.h>
#define RIGHT 1
#define LEFT 0
#define STRING_DEFAULT_SIZE 50
using namespace std;
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




/*链式栈*/
/*top->an--an-1--an-2--......--a1->NULL*/
template<class T>
struct LinkNode {//链表结点类
	T data;
	LinkNode* rLink;
	LinkNode(T d, LinkNode* L) :data(d), rLink(L) {};
};
template<class T>
class LinkedStack {
private:
	LinkNode<T>* top;
public:
	LinkedStack() :top(NULL) {}//构造函数，置空栈
	~LinkedStack() { makeEmpty(); };//析构函数
	void Push(const T& x);//元素进栈
	bool Pop(T& x);//元素退栈
	bool getTop(T& x)const;//返回栈顶元素
	bool IsEmpty()const { return(top == NULL) ? true : false; }
	int getSize()const;//返回栈的元素个数
	void makeEmpty();//清空栈
	friend ostream& operator << (ostream& os, LinkedStack<T>& s) {
		//输出栈中元素的重载操作<<
		os << "栈中元素个数=" << s.getSize() << endl;//输出栈中元素个数
		LinkNode<T>* p = s.top;
		int i = 0;//逐个输出栈中元素个数
		while (p != NULL) {
			os << ++i << ":" << p->data << endl;
			p = p->rLink;
		}
		return os;

	};//输出栈中元素的重载操作
};

template<class T>
void LinkedStack<T>::makeEmpty() {
	//逐次删去链式栈中的元素直至栈顶指针为空
	LinkNode<T>* p;
	while (top != NULL) {//逐个结点释放
		p = top;
		top = top->rLink;
		delete p;
	}
};

template<class T>
void LinkedStack<T>::Push(const T& x) {
	//将元素值x插入到链式栈的栈顶，即链头
	top = new LinkNode<T>(x, top);//创建新的含x结点
	assert(top != NULL);//创建新结点失败退出
}

template <class T>
bool LinkedStack<T>::Pop(T& x) {
	//删除栈顶结点，返回被删栈顶元素的值
	if (IsEmpty() == true)
		return false;//若栈空则不退栈，返回
	LinkNode <T>* p = top;//否则暂存栈顶元素
	top = top->rLink;
	x = p->data;
	delete p;//释放结点，返回退出元素的值
	return true;
}

template<class T>
bool LinkedStack<T>::getTop(T& x)const {
	//返回栈顶元素的值
	if (IsEmpty() == true)
		return false;//若栈空则返回false
	x = top->data;//栈不空则返回栈顶元素的值
	return true;
}

template<class T>
int LinkedStack<T>::getSize()const {
	LinkNode<T>* p = top;
	int k = 0;
	while (p != NULL) {
		p = top->rLink;
		k++;
	}
	return k;
}


template<class E, class K>
struct AVLNode {
	E data;//数据
	AVLNode<E, K>* left, * right;//左子女和右子女
	int bf;//平衡因子
	AVLNode() :left(NULL), right(NULL), bf(0) {};
	AVLNode(E d, AVLNode<E, K>* l = NULL, AVLNode<E, K>* r = NULL) :data(d), left(l), right(r), bf(0) {};
	~AVLNode() {};//析构函数
	void setData(E d) {
		data = d;
	}
	E getData() {
		return data;
	}
};
template<class E, class K>
class AVLTree {
protected:
	AVLNode<E, K>* root;//根指针
	int tree_num;
	bool Insert(AVLNode<E, K>*& ptr, E& el);
	bool Remove(AVLNode<E, K>*& ptr, K x);
	void RotateL(AVLNode<E, K>*& ptr);//左单旋
	void RotateR(AVLNode<E, K>*& ptr);//右单旋
	void RotateLR(AVLNode<E, K>*& ptr);//先左单旋后右单旋
	void RotateRL(AVLNode<E, K>*& ptr);//先右单旋后做单旋
public:
	AVLTree() :root(NULL), tree_num(0) {}//构造函数，构造空AVL树
	AVLNode<E, K>* Search1(K x, AVLNode<E, K>*& ptr);
	AVLNode<E, K>* find(K x) {
		return Search1(x, root);
	}
	bool Insert(E& el) {
		return Insert(root, el);
	}
	bool Remove(K x) {
		return Remove(root, x);
	}
	//friend istream& operator>>(istream& in, AVLTree<E,K>& Tree);
	AVLNode<E, K>* get_root() {
		return root;
	}
	int get_Tnum() {
		return tree_num;
	}
	void input(int i);//插入i个元素
	void ouput();//输出
	int count() {
		int count = 0;
		Traverse(root, count);
		return count;
	}
	friend ostream& operator<<(ostream& out, const AVLTree<E, K>& Tree) {
		Tree.Traverse(Tree.root, out);//以中序次序输出各结点的数据
		out << endl;
		return out;//返回输出元素

	}
	void Traverse(const AVLNode<E, K>* ptr, ostream& out)const;
	void Traverse(const AVLNode<E, K>* ptr, int& count)const;
	//int Height()const;
};

template<class E, class K>
AVLNode<E, K>* AVLTree<E, K>::Search1(K x, AVLNode<E, K>*& ptr) {
	//搜索含x的结点，成功返回该节点的地址，失败返回NULL
	if (ptr == NULL)
		return NULL;
	else if (x < ptr->data)
		return Search1(x, ptr->left);//到左子树中继续搜索
	else if (x > ptr->data)
		return Search1(x, ptr->right);//到右子树中继续搜索
	else
		return ptr;//搜索成功
}

template<class E, class K>
void AVLTree<E, K>::RotateL(AVLNode<E, K>*& ptr) {
	//右子树比左子树高：对以ptr为根的AVL树做左单旋转，旋转后新根在ptr
	AVLNode<E, K>* subL = ptr;//要左旋转的结点
	ptr = subL->right;//原根的右子女
	subL->right = ptr->left;//ptr成为新根前卸掉左边负载
	ptr->left = subL;//左单旋转，ptr为新根
	ptr->bf = subL->bf = 0;
}

template<class E, class K>
void AVLTree<E, K>::RotateR(AVLNode<E, K>*& ptr) {
	//右子树比左子树高：对以ptr为根的AVL树做右单旋转，旋转后新根在ptr
	AVLNode<E, K>* subR = ptr;//要右旋转的结点
	ptr = subR->left;//原根的左子女
	subR->left = ptr->right;//ptr成为新根前卸掉右边负载
	ptr->right = subR;//右单旋转，ptr为新根
	ptr->bf = subR->bf = 0;
}

template<class E, class K>
void AVLTree<E, K>::RotateLR(AVLNode<E, K>*& ptr) {
	AVLNode<E, K>* subR = ptr, * subL = subR->left;
	ptr = subL->right;
	subL->right = ptr->left;//ptr成为新根前甩掉它左边的负载
	ptr->left = subL;//左单旋转，ptr成为新根
	if (ptr->bf <= 0)
		subL->bf = 0;//插入结新点后ptr左子树变高
	else
		subL->bf = -1;
	subR->left = ptr->right;//ptr成为新根前甩掉它右边
	ptr->right = subR;//右单旋转，ptr成为新根
	if (ptr->bf == -1)
		subR->bf = 1;
	else
		subR->bf = 0;
	ptr->bf = 0;
}

template<class E, class K>
void AVLTree<E, K>::RotateRL(AVLNode<E, K>*& ptr) {
	AVLNode<E, K>* subL = ptr, * subR = subL->right;
	ptr = subR->left;
	subR->left = ptr->right;//ptr成为新根前甩掉它右边的负载
	ptr->right = subR;//右单旋转，ptr成为新根
	if (ptr->bf >= 0)
		subR->bf = 0;
	else
		subR->bf = 1;
	subL->right = ptr->left;//ptr成为新根前甩掉它左边的负载
	ptr->left = subL;//左单旋转，ptr成为新根
	if (ptr->bf == 1)
		subL->bf = -1;
	else
		subL->bf = 0;
	ptr->bf = 0;
}

template<class E, class K>
bool AVLTree<E, K>::Insert(AVLNode<E, K>*& ptr, E& el) {
	//在以ptr为根的AVL树中插入新元素el，如果插入成功，函数返回true，否则返回false。
	AVLNode<E, K>* pr = NULL, * p = ptr, * q;
	int d;
	LinkedStack<AVLNode<E, K>*>st;
	while (p != NULL) {//寻找插入位置
		if (el == p->data)//找到等于el的结点，不插入
			return false;
		pr = p;
		st.Push(pr);//否则用栈记忆查找路径
		if (el < p->data)
			p = p->left;
		else
			p = p->right;
	}
	p = new AVLNode<E, K>(el);//创建新结点，data=el，bf=0
	if (p == NULL) {
		cerr << "存储空间不足！" << endl;
		return false;
	}
	if (pr == NULL) {//空树，新结点成为根结点
		ptr = p;
		tree_num++;
		return true;
	}
	if (el < pr->data)
		pr->left = p;
	else
		pr->right = p;
	while (st.IsEmpty() == false) {//重新平衡化
		st.Pop(pr);//从栈中退出父结点
		if (p == pr->left)//调整父结点的平衡因子
			pr->bf--;
		else
			pr->bf++;
		if (pr->bf == 0)//结点平衡因子=0，平衡退出
			break;
		if (pr->bf == 1 || pr->bf == -1)//结点平衡因子绝对值=1
			p = pr;
		else {//结点平衡因子绝对值=2
			d = (pr->bf < 0) ? -1 : 1;//区别单双旋标志
			if (p->bf == d) {//两结点平衡因子同号，单旋转
				if (d == -1)//右单旋转
					RotateR(pr);
				else//左单旋转
					RotateL(pr);
			}
			else {//两结点平衡因子番号，双旋转
				if (d == -1)//先左后右双旋转，“<”型
					RotateLR(pr);
				else//先右后左双旋转，“>”型
					RotateRL(pr);
			}
			break;//不再向上调整
		}//end of |bf|==2
	}//end of while(st.IsIsEmpty()==false)
	if (st.IsEmpty() == true)
		ptr = pr;//调整到数的根结点
	else {//中间重新连接
		st.getTop(q);
		if (q->data > pr->data)
			q->left = pr;
		else
			q->right = pr;
	}
	tree_num++;
	return true;
}

template<class E, class K>
void AVLTree<E, K>::input(int i) {
	int count = 1;
	E item;
	while (count <= i) {
		cin >> item;
		Insert(item);
		count++;
	}
}

template<class E, class K>
void AVLTree<E, K>::ouput() {
	cout << "中根遍历AVL树" << endl;
	Traverse(root);//以中序次序输出各结点的数据
	cout << endl;
}

template<class E, class K>
void AVLTree<E, K>::Traverse(const AVLNode<E, K>* ptr, ostream& out)const {
	if (ptr != NULL) {//树非空
		Traverse(ptr->left, out);//中序遍历左子树
		out << ptr->data << endl;//输出根的数据
		Traverse(ptr->right, out);//中序遍历右子树
	}
}

template<class E, class K>
void AVLTree<E, K>::Traverse(const AVLNode<E, K>* ptr, int& count)const {
	if (ptr != NULL) {//树非空
		Traverse(ptr->left, count);//中序遍历左子树
		count++;
		Traverse(ptr->right, count);//中序遍历右子树
	}
}
template<class E, class K>
bool AVLTree<E, K>::Remove(AVLNode<E, K>*& cur, K val) {
	LinkedStack<AVLNode<E, K>*> stk;
	//p:要删除的结点，son:要删除结点的子结点
	AVLNode<E, K>* parent = NULL, * p = cur, * pparent = NULL, * son;
	int d = 0, dd = 0;
	while (p)//寻找删除位置
	{
		if (val == p->data.num)//找到了要删除的结点
			break;
		parent = p;
		stk.Push(parent);//记录走过的路径
		if (val < p->data.num)
			p = p->left;
		else
			p = p->right;
	}
	//找不到要删除的结点
	if (p == NULL)
		return false;
	if (p->left && p->right)//被删除结点有两个子结点，变换为简单情况
	{
		parent = p;
		stk.Push(parent);
		//左子树的直接前驱，左边走一步，接着走到最右边
		son = p->left;
		while (son->right)
		{
			parent = son;
			stk.Push(parent);
			son = son->right;
		}
		p->data = son->data;//直接前驱的值赋给要删除的结点
		p = son;//转换为要删去直接前驱
	}
	//换完之后的情况：至多有一个子结点，记录为son
	if (p->left)
		son = p->left;
	else
		son = p->right;
	//为根结点，直接连上要删除结点的子结点son
	if (parent == NULL)
		cur = son;
	else//不是根结点
	{
		//连上要删除结点的子结点son
		if (parent->left == p)
			parent->left = son;
		else
			parent->right = son;

		//开始回溯，重新平衡化
		while (!stk.IsEmpty())
		{

			stk.Pop(parent);
			//调整parent的bf
			if (parent->left == son)//删掉了原来在parent左边的结点
				parent->bf++;
			else
				parent->bf--;

			//得到爷结点
			if (!stk.IsEmpty())
			{
				stk.Pop(pparent);
				dd = (pparent->left == parent) ? -1 : 1;
			}
			else//没有爷结点
				dd = 0;
			//如果parent平衡因子绝对值为1，则不用调整，直接退出
			if (parent->bf == 1 || parent->bf == -1)
				break;
			if (parent->bf)//bf绝对值为2
			{
				if (parent->bf < 0)
				{
					d = -1;
					son = parent->left;
				}
				else
				{
					d = 1;
					son = parent->right;
				}

				if (son->bf == 0)
				{
					if (d == -1)
					{
						RotateR(parent);
						parent->bf = 1;
						parent->left->bf = -1;
					}
					else
					{
						RotateL(parent);
						parent->bf = -1;
						parent->right->bf = 1;
					}
					break;
				}
				if (son->bf == d)
				{
					if (d == -1)
						RotateR(parent);
					else
						RotateL(parent);
				}
				else
				{
					if (d == -1)
						RotateLR(parent);
					else
						RotateRL(parent);
				}

				if (dd == -1)
					pparent->left = parent;
				else if (dd == 1)
					pparent->right = parent;
			}
			son = parent;
		}
		if (stk.IsEmpty())
			cur = parent;
	}//end if else

	tree_num--;
	return true;
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







struct student {
	//int pos;
	int num;//考号
	String name;//姓名
	String sex;//性别
	int age;//年龄
	String major;//报考类别
	student(const int num = -1, const String& name = "None",
		const String& sex = "None", const int age = 0,
		const String& major = "None")
		:num(num), name(name), sex(sex), age(age), major(major) {}
	friend istream& operator>>(istream& in, student& S)
	{
		while (1)
		{
			in >> S.num >> S.name >> S.sex >> S.age >> S.major;
			if (cin.fail() || S.num < 0 || S.age < 0)
			{
				cout << "输入错误！" << endl;
				cin.clear();
				cin.ignore(65536, '\n');
			}
			else
				break;
		}
		return in;
	}
	friend ostream& operator<<(ostream& out, const student& S)
	{
		cout << setiosflags(ios::left);
		cout << setw(8) << S.num << setw(8) << S.name << setw(8) << S.sex << setw(8) << S.age << S.major;
		return out;
	}
	friend bool operator<(const student& s1, const student& s2)
	{
		return s1.num < s2.num;
	}
	friend bool operator<(const int& i1, const student& s2)
	{
		return i1 < s2.num;
	}
	friend bool operator>(const student& s1, const student& s2)
	{
		return s1.num > s2.num;
	}
	friend bool operator>(const int& i1, const student& s2)
	{
		return i1 > s2.num;
	}
	friend bool operator==(const student& s1, const student& s2)
	{
		return s1.num == s2.num;
	}

};
class examination_register_system {
private:
	DblList<student> ers;
	AVLTree<student, int> avl;
public:
	void initialization();//初始化考生信息
	void show();//打印学生信息
	void insert();//插入一条学生数据
	void erase();//删除数据系统中指定的学生数据
	void find();//查找

	void modify();
	//void count();//打印数据系统中考生总数
	//void update();//更新考生信息
	void stat();//统计考生系统信息
	//void save_to_file();//将数据保存到本地文件
};

void examination_register_system::initialization() {//初始化考生信息系统
	int num = 0;
	cout << "首先建立考生信息系统!" << endl;
	cout << "请输入考生人数：";
	cin >> num;
	while (num < 1) {
		cout << "考生人数错误！" << endl;
		cout << "请输入考生人数：";
		cin >> num;
	}
	cout << "请依次输入考生的考号、姓名、性别、年龄及报考类别!" << endl;
	avl.input(num);
	//ers.input_num(num);
}

void examination_register_system::show() {
	cout << setiosflags(ios::left) << setw(8) << "考号" << setw(8) << "姓名" << setw(8)
		<< "性别" << setw(8) << "年龄" << setw(8) << "报考类别" << endl;
	cout << avl;
	//ers.output(RIGHT);
}

void examination_register_system::insert() {
	//int i;
	student one;
	//while (i < 0||i>ers.Length()) {//i太小或太大
	//	cout << "插入的考生位置非法，请重新输入：";
	//	cin >> i;
	//}
	cout << "请依次输入要插入的考生的考号、姓名、性别、年龄及报考类别!" << endl;
	cin >> one;
	//ers.Inset(i, one,1);
	avl.Insert(one);
}

void examination_register_system::erase() {
	int denum;
	AVLNode<student, int>* s;
	cout << "请输入您要删除考生的考号：";
	cin >> denum;
	s = avl.find(denum);
	if (s != NULL) {
		if (!avl.Remove(denum)) {
			cout << "删除失败，未找到该考生信息！" << endl;
			return;
		}
		cout << "您删除的考生信息是：" << endl;
		cout << s->data << endl << endl;
	}
	else {
		cout << "未找到该考生信息！" << endl;
	}
	//if (ers.Remove(find(denum,one), one,RIGHT))
		//cout << one<<endl<<endl;
}

void examination_register_system::find() {
	int denum;
	AVLNode<student, int>* s;
	cout << "请输入您要查找考生的考号：";
	cin >> denum;
	s = avl.find(denum);
	if (s != NULL) {
		cout << "您查找的考生信息是：" << endl;
		cout << s->data << endl << endl;
	}
	else {
		cout << "未找到该考生信息！" << endl;
	}
}
/*
int examination_register_system::find(int kaohao,student&S) {
	//在表中搜索含数据x的结点，搜索成功时函数返回该结点是第几个；否则返回-1
	DblNode<student>* current = ers.getHead()->rLink;
	//avl.Search(kaohao);
	int count = 0;
	while (current != ers.getHead()) {//循链找含kaohao的结点
		count++;
		if (current->data.num == kaohao) {
			S = current->data;
			break;
		}
		else
			current = current->rLink;
	}
	if (current != ers.getHead())
		return count;
	else {
		cout << "该考号无对应考生" << endl<<endl;
		return -1;
	}
}
*/
void examination_register_system::modify() {
	int denum;
	AVLNode<student, int>* s;
	cout << "请输入您要修改考生的考号：";
	cin >> denum;
	s = avl.find(denum);
	if (s != NULL) {
		if (!avl.Remove(denum)) {
			cout << "删除失败，未找到该考生信息！" << endl;
			return;
		}
		cout << "您修改的考生信息是：" << endl;
		cout << s->data << endl << endl;
		student one;
		cout << "请输入修改后的考生考号、姓名、性别、年龄、报考类别！" << endl;
		cin >> one;
		avl.Insert(one);
	}
	else {
		cout << "未找到该考生信息！" << endl;
	}
}

void examination_register_system::stat() {

	cout << "*********************************" << endl;
	cout << "考生总数：" << avl.get_Tnum() << endl;
	show();
	cout << "*********************************" << endl;
}

#endif
