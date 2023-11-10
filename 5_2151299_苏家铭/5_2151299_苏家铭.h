#ifndef _SJM_LIST_
#define _SJM_LIST_

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


#endif
