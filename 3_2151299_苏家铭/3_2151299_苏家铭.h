#ifndef _03_
#define _03_
#include<iostream>
#include<assert.h>
using namespace std;
#define Default_size 20

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
	void Push(const T& x);//进栈
	bool Pop(T& x);//退栈
	bool getTop(T& x)const;//读取栈顶元素
	bool IsEmpty()const { return(top == NULL) ? true : false; }
	int getSize()const;//求栈的元素个数
	void makeEmpty();//清空栈的内容
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


template <class T>
class minHeap {
private:
	T* pheap;//存放小根堆中元素的数组
	int current_size;//小根堆中当前元素个数
	int minHeap_size;//小根堆最多允许元素个数
	void down_sift(int start, int m);//自上向下调整
	void up_sift(int start);//自下向上调整
public:
	minHeap(int size = Default_size);//构造函数：建立空堆
	minHeap(T arr[], int size);//构造函数：通过一个数组建堆
	~minHeap() {
		delete[]pheap;
	}
	bool insert(const T& x);//将x插入到小根堆中
	bool remove_min(T& x);//删除小根堆上的最小元素
	bool empty()const {//判断堆是否为空
		return (current_size == 0) ? true : false;
	}
	bool full()const {
		return(current_size == minHeap_size) ? true : false;
	}
	void make_empty() {//置空堆
		current_size = 0;
	}
	void rank_heap(T rank[]);//堆排序

	//有元类
	template <class E>
	friend class minPQueue;
};

template<class T>
minHeap<T>::minHeap(int size) {//构造函数
	minHeap_size = (Default_size < size) ? size : Default_size;
	pheap = new T[minHeap_size];//创建存储空间
	if (pheap == NULL) {
		cerr << "小根堆存储分配失败！" << endl;
		return;
	}
	current_size = 0;
}

template<class T>
minHeap<T>::minHeap(T arr[], int size) {//构造函数
	minHeap_size = (Default_size < size) ? size : Default_size;
	pheap = new T[minHeap_size];
	if (pheap == NULL) {
		cerr << "小根堆存储分配失败！" << endl;
		return;
	}
	for (int i = 0; i < size; i++)
		pheap[i] = arr[i];
	current_size = size;//建立当前大小
	int currentPos = (current_size - 2) / 2;//找到最初调整位置：末结点的父结点
	while (currentPos >= 0) {//自底向上
		down_sift(currentPos, current_size - 1);
		currentPos--;
	}
}

template<class T>
void minHeap<T>::down_sift(int start, int m) {
	//从结点strat开始到m位置，自上向下比较
	int i = start, j = 2 * i + 1;//j是i的左子女
	T temp = pheap[i];
	while (j <= m) {
		if (j < m && pheap[j] >pheap[j + 1])//让j指向两子女中的小者
			j++;
		if (temp <= pheap[j])//temp小则不调整
			break;
		else {//小则上移。i、j下降
			pheap[i] = pheap[j];
			i = j;
			j = 2 * j + 1;
		}
	}//end of while
	pheap[i] = temp;
}

template<class T>
void minHeap<T>::up_sift(int start) {
	//从结点start开始到结点0，自下而上比较
	int j = start, i = (j - 1) / 2;
	T temp = pheap[j];
	while (j > 0) {//沿父结点路径向上直达根节点
		if (pheap[i] <= temp)//父结点值小，不调整
			break;
		else {//父结点小，调整
			pheap[j] = pheap[i];
			j = i;
			i = (i - 1) / 2;
		}
	}
	pheap[j] = temp;
}

template<class T>
bool minHeap<T>::insert(const T& x) {
	//将x插入到小根堆中
	if (current_size == minHeap_size) {//堆满
		cerr << "Heap Full!" << endl;
		return false;
	}
	pheap[current_size] = x;//插入
	up_sift(current_size);//向上调整
	current_size++;//堆计数++
	return true;
}

template<class T>
bool minHeap<T>::remove_min(T& x) {
	if (current_size == 0) {
		cout << "Heap Full!" << endl;
		return false;
	}//堆空，最后返回false
	x = pheap[0];
	pheap[0] = pheap[current_size - 1];//最后元素填补到根结点
	current_size--;
	down_sift(0, current_size - 1);//自上向下调整堆
	return true;//返回最小元素
}

template<class T>
void minHeap<T>::rank_heap(T rank[]) {
	//因为堆排序要删除结点，所以再用一个堆复制原本的堆
	minHeap<T> temp_heap(pheap, current_size);
	T x;
	//cout <<"pt:"<< pt[0] << " " << pt[1] << " " << pt[2] << endl;
	int i = 0;
	while (i < current_size) {//current个元素

		rank[i] = temp_heap.pheap[0];//根结点总是最小值
		//删掉根结点
		x = temp_heap.pheap[0];
		temp_heap.pheap[0] = temp_heap.pheap[temp_heap.current_size - 1];//最后元素填补到根结点
		temp_heap.current_size--;
		//调整
		int start = 0, j = 2 * start + 1, m = temp_heap.current_size - 1;//j是i的左子女
		T temp = temp_heap.pheap[start];
		while (j <= m) {
			if (j < m && temp_heap.pheap[j] > temp_heap.pheap[j + 1])//让j指向两子女中的小者
				j++;
			if (temp <= temp_heap.pheap[j])//temp小则不调整
				break;
			else {//小则上移。i、j下降
				temp_heap.pheap[start] = temp_heap.pheap[j];
				start = j;
				j = 2 * j + 1;
			}
		}//end of while
		temp_heap.pheap[start] = temp;

		i++;
	}
}

template<class T>
class minPQueue {
private:
	minHeap<T> heap;
public:
	//构造函数
	minPQueue(int size = Default_size);
	minPQueue(T arr[], int size);
	//析构函数
	//~minPQueue() 
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
void minPQueue<T>::push(const T& val) {
	heap.insert(val);
}

template<class T>
void minPQueue<T>::pop() {
	T x;
	heap.remove_min(x);
}

template<class T>
void minPQueue<T>::makeEmpty() {
	heap.make_empty();
}

template<class T>
bool minPQueue<T>::empty()const {
	return heap.empty();
}

template<class T>
int minPQueue<T>::size()const {
	return heap.current_size;
}

template<class T>
const T& minPQueue<T>::front() {
	return heap.pheap[0];
}
template<class T>

minPQueue<T>::minPQueue(int size) {
	heap.minHeap_size = (Default_size < size) ? size : Default_size;
	heap.pheap = new T[heap.minHeap_size];//创建存储空间
	if (heap.pheap == NULL) {
		cerr << "小根堆存储分配失败！" << endl;
		return;
	}
	heap.current_size = 0;
};

template<class T>
minPQueue<T>::minPQueue(T arr[], int size) {
	heap.minHeap_size = (Default_size < size) ? size : Default_size;
	heap.pheap = new T[heap.minHeap_size];
	if (heap.pheap == NULL) {
		cerr << "小根堆存储分配失败！" << endl;
		return;
	}
	for (int i = 0; i < size; i++)
		heap.pheap[i] = arr[i];
	heap.current_size = size;//建立当前大小
	int currentPos = (heap.current_size - 2) / 2;//找到最初调整位置：末结点的父结点
	while (currentPos >= 0) {//自底向上
		heap.down_sift(currentPos, heap.current_size - 1);
		currentPos--;
	}
}
#endif
