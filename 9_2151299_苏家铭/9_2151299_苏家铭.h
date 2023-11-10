#ifndef __09_
#define _09_
#include<iostream>
#include<climits>
using namespace std;

#define DEFAULT_VERTICES 30
 

template<class T, class E>//T是顶点数数据的类型，E是边上所附数据的类型
class GRAPH {
protected:
	int max_vertices_num;//图中最大顶点数
	int edges_num;//当前边数
	int vertices_num;//当前顶点数
public:
	//GRAPH(int size = DEFAULT_VERTICES);//构造
	//~GRAPH();//析构
	bool empty()const {
		if (edges_num == 0)
			return true;
		else
			return false;
	}
	bool full()const {
		if (vertices_num == max_vertices_num ||
			vertices_num == max_vertices_num * (max_vertices_num - 1) / 2)
			return true;
		else return false;
	}
	int vertices_number() {//返回当前结点数
		return vertices_num;
	}
	int edges_number() {//返回当前边数
		return edges_num;
	}
};

template<class T, class E>
struct edge {//边结点结构体
	int dest;//边结点的定义
	E cost;//边上的权值
	edge<T, E>* link;//下一条边链指针
	edge() :dest(-1), cost(-1), link(NULL) {};//构造函数
	edge(int num, E data) :dest(num), cost(data), link(NULL) {};//构造函数
	bool operator!=(edge<T, E>& R)const {
		return (dest != R.dest) ? true : false;
	}
};

template<class T, class E>
struct vertex {//顶点结构体
	T data;//顶点的名字
	edge<T, E>* adj;//边链表的头指针
};



template<class T, class E>//T是顶点数据的类型，E是边上所附数据的类型
class graph :public GRAPH<T, E> {//公有继承
private:
	vertex<T, E>* node_table;//顶点表（各边链表的头结点）
public:
	graph(int size = DEFAULT_VERTICES);//构造函数:建立一个空的邻接表
	~graph();//析构函数:删除一个邻接表
	T get_value(int i);//取位置为i的顶点中的值
	E get_weight(int v1, int v2);//返回边（v1,v2）上的权值
	bool insert_vertex(const T& vertex);//在图中插入一个顶点vertex
	bool remove_vertex(int v);//在图中删除一个顶点vertex
	bool insert_edge(int v1, int v2, E cost);//在图中插入一条新无向边(v1,v2)
	bool insert_directed_edge(int v1, int v2, E cost);//在图中插入一条新有向边(v1,v2)
	bool remove_edge(int v1, int v2);//在图中删除一条边(v1,v2)
	int get_vertex_pos(const T vertex);//返回顶点vertex在图中的位置
	int get_first_neighbor(int v);//取顶点v的第一个邻接顶点
	int get_next_neighbor(int v, int w);//取v的邻接顶点w的下一邻接顶点

	int get_neighbor_num(int v);//返回该点的邻接边数量
	friend istream& operator>>(istream& in, const graph& G)
	{
		//通过从输入流对象in输入n个顶点和e条无向边的信息建立图
		int i, j, k, n, m;
		T e1, e2;
		E weight;
		in >> n >> m;//输入顶点数和边数
		for (i = 0; i < n; i++) {//建立顶点表数据
			in >> e1;
			G.insert_vertex(e1);
		}
		i = 0;
		while (i < m) {
			in >> e1 >> e2 >> weight;//输入端点信息
			j = G.get_vertex_pos(e1);
			k = G.get_vertex_pos(e2);//查顶点号
			if (j == -1 || k == -1)
				cout << "边两端点信息有误，请重新输入！" << endl;
			else {
				G.insert_edge(j, k, weight);
				++i;
			}
		}
		return in;
	}

	friend ostream& operator<< (ostream& out, const graph& G)
	{
		//输入图的所有顶点和边的信息
		int i, j, n, m;
		T e1, e2;
		E w;
		n = G.vertices_number();
		m = G.edges_number();
		out << "顶点数：" << n << "," << "边数：" << m << endl;
		for (i = 0; i < n; i++) {
			for (j = i + 1; j < n; j++) {
				w = G.get_weight(i, j);//取边上权值
				if (w > 0 && w < INT_MAX) {//权值有效
					e1 = G.get_value(i);
					e2 = G.get_value(j);
					out << e1 << "-(" << w << ")->" << e2 << " " << endl;
				}
			}
		}
		return out;
	}


};
template<class T, class E>
T graph<T, E>::get_value(int i) {
	return (i >= 0 && i < this->vertices_num) ? node_table[i].data : 0;
}

template<class T, class E>
int graph<T, E>::get_vertex_pos(const T vertex) {//返回顶点vertex在图中的位置
	for (int i = 0; i < this->vertices_num; i++)
		if (node_table[i].data == vertex)
			return i;
	return -1;
}

template<class T, class E>
graph<T, E>::graph(int size) {
	this->max_vertices_num = size;
	this->vertices_num = 0;
	this->edges_num = 0;
	node_table = new vertex<T, E>[this->max_vertices_num];//创建顶点表数组
	if (node_table == NULL) {
		cerr << "存储分配错误！" << endl;
		return;
	}

	for (int i = 0; i < this->max_vertices_num; i++)
		node_table[i].adj = NULL;
}

template<class T, class E>
graph<T, E>::~graph() {//删除一个邻接表
	for (int i = 0; i < this->vertices_num; i++) {//删除各链表中的结点
		edge<T, E>* p = node_table[i].adj;//找到其对应边链表的首结点
		while (p != NULL) {//不断地删除第一个结点
			node_table[i].adj = p->link;
			delete p;
			p = node_table[i].adj;
		}
	}
	delete[]node_table;//删除顶点表数组
}

template<class T, class E>
int graph<T, E>::get_first_neighbor(int v) {
	//给出顶点位置为v的第一个邻接顶点的位置，如果找不到，则函数返回-1
	if (v != -1) {//顶点v存在
		edge<T, E>* p = node_table[v].adj;//对应边链表第一个边结点
		if (p != NULL)
			return p->dest;//存在，返回第一个邻接结点
	}
	return -1;//第一个邻接顶点不存在
}

template<class T, class E>
int graph<T, E>::get_next_neighbor(int v, int w) {
	//给出顶点v的邻接顶点w的下一个邻接顶点的位置，若没有则返回-1
	if (v != -1) {//顶点v存在
		edge<T, E>* p = node_table[v].adj;//对应边链表第一个边结点
		while (p != NULL && p->dest != w)//寻找邻接顶点w
			p = p->link;
		if (p != NULL && p->link != NULL)
			return p->link->dest;//存在，下一个邻接结点
	}
	return -1;//下一个邻接顶点不存在
}

template<class T, class E>
E graph<T, E>::get_weight(int v1, int v2) {
	//函数返回边（v1，v2）上的权值，若该边不在图中，则函数返回权值INT_MAX
	if (v1 != -1 && v2 != -1) {
		edge<T, E>* p = node_table[v1].adj;//v1的第一条关联的边
		while (p != NULL && p->dest != v2)//寻找邻接顶点v2
			p = p->link;
		if (p != NULL)
			return p->cost;//找到此边，返回权值
	}
	return INT_MAX;
}

template<class T, class E>
bool graph<T, E>::insert_vertex(const T& vertex) {
	//在图的顶点表中插入一个新的顶点vertex
	if (this->vertices_num == this->max_vertices_num)
		return false;//顶点表满，不能插入
	node_table[this->vertices_num].data = vertex;//插在表的最后
	this->vertices_num++;
	return true;
}

template<class T, class E>
bool graph<T, E>::remove_vertex(int v) {
	//在图中删除一个顶点v,v是顶点号
	if (this->vertices_num == 0 || v < 0 || v >= this->vertices_num)//表空或顶点后超出范围
		return false;
	edge<T, E>* p, * s, * t;
	int i, k;
	while (node_table[v].adj != NULL) {//删除第v个边链表中所有结点
		p = node_table[v].adj;
		k = p->dest;//取邻接顶点k
		s = node_table[k].adj;//找对称存放的边结点
		t = NULL;
		while (s != NULL && s->dest != v) {
			t = s;
			s = s->link;
		}
		if (s != NULL) {//删除对称存放结点
			if (t == NULL)
				node_table[k].adj = s->link;
			else
				t->link = s->link;
			delete s;
		}
		node_table[v].adj = p->link;//清除顶点v的边链表结点
		delete p;
		this->edges_num--;//与顶点v相关联的边数-1
	}
	this->vertices_num--;//图的顶点个数减1
	node_table[v].data = node_table[this->vertices_num].data;//填补
	p = node_table[v].adj = node_table[this->vertices_num].adj;
	while (p != NULL) {
		s = node_table[p->dest].adj;
		while (s != NULL) {
			if (s->dest == this->vertices_num) {
				s->dest = v;
				break;
			}
			else
				s = s->link;
		}
	}
	return true;
}

template<class T, class E>
bool graph<T, E>::insert_edge(int v1, int v2, E weight) {
	//在带权图中插入一条新无向边（v1,v2）,若此边存在或参数不合理返回false，否则true
	if (!(v1 >= 0 && v1 < this->vertices_num && v2 >= 0 && v2 < this->vertices_num))
		return false;
	edge<T, E>* q, * p = node_table[v1].adj;//v1对应的边链表头指针
	while (p != NULL && p->dest != v2)//寻找邻接顶点v2
		p = p->link;
	if (p != NULL)//找到此边，不插入
		return false;
	p = new edge<T, E>;
	q = new edge<T, E>;//创建新结点
	p->dest = v2;
	p->cost = weight;
	p->link = node_table[v1].adj;//头结点插入
	node_table[v1].adj = p;
	q->dest = v1;
	q->cost = weight;
	q->link = node_table[v2].adj;//头结点插入
	node_table[v2].adj = q;
	this->edges_num++;
	return true;
}

template<class T, class E>
bool graph<T, E>::insert_directed_edge(int v1, int v2, E weight) {
	//在带权图中插入一条新有向边（v1,v2）,若此边存在或参数不合理返回false，否则true
	if (!(v1 >= 0 && v1 < this->vertices_num && v2 >= 0 && v2 < this->vertices_num))
		return false;
	edge<T, E>* p = node_table[v1].adj;//v1对应的边链表头指针
	while (p != NULL && p->dest != v2)//寻找邻接顶点v2
		p = p->link;
	if (p != NULL)//找到此边，不插入
		return false;
	p = new edge<T, E>;//创建新结点
	p->dest = v2;
	p->cost = weight;
	p->link = node_table[v1].adj;//头结点插入
	node_table[v1].adj = p;
	this->edges_num++;
	return true;
}

template<class T, class E>
bool graph<T, E>::remove_edge(int v1, int v2) {
	//删除一条边（v1，v2）
	if (v1 != -1 && v2 != -1) {
		edge<T, E>* p = node_table[v1].adj, * q = NULL, * s = p;
		while (p != NULL && p->dest != v2) {//v1对应边链表找被删边
			q = p;
			p = p->link;
		}
		if (q != NULL) {//找到被删边结点
			if (p == s)//该结点是边链表首结点
				node_table[v1].adj = p->link;
			else//不是首结点
				q->link = p->link;
			delete p;
		}
		else//没有找到被删结点
			return false;
		p = node_table[v2].adj;
		q = NULL, s = p;//v2对应边链表删除
		while (p->dest != v1) {
			q = p;
			p = p->link;
		}
		if (p == s)
			node_table[v2].adj = p->link;
		else
			q->link = p->link;
		delete p;
		return true;
	}
	return false;
}


template<class T, class E>
int  graph<T, E>::get_neighbor_num(int v) {
	int count = 0;
	edge<T, E>* p = node_table[v].adj;//对应边链表第一个边结点
	if (v != -1) {//顶点v存在
		while (p != NULL) {
			count++;
			p = p->link;
		}
		return count;
	}
	return -1;//顶点不存在
}



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
