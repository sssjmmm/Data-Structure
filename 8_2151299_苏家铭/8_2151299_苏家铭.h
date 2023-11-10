/*小根堆，根结点编号为0*/
#ifndef _08_
#define _08_
#include<iostream>
#include<climits>
 

using namespace std;
#define Default_size 20
#define DEFAULT_VERTICES 30
#define DEFAULT_SIZE 30

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




template<class T, class E>
struct MST_edge_node {//最小生成树边结点的类声明
	int tail, head;//两顶点的位置
	E key;//边上的权值，为关键码
	MST_edge_node() :tail(-1), head(-1), key(0) {}//构造函数
	friend bool operator<(const MST_edge_node& a, const MST_edge_node& b) {
		return a.key < b.key;
	}

	friend bool operator>(const MST_edge_node& a, const MST_edge_node& b) {
		return a.key > b.key;
	}

	bool operator==(const MST_edge_node& b) {
		return key == b.key;
	}

	bool operator>=(const MST_edge_node& b) {
		return key >= b.key;
	}

	bool operator<=(const MST_edge_node& b) {
		return key <= b.key;
	}
};

template<class T, class E>
class MST {
protected:
	MST_edge_node<T, E>* edge_value;//用边值数组表示树
	int max_size, n;//数组的最大元素个数和当前个数
public:
	MST(int size = DEFAULT_SIZE - 1) :max_size(size), n(0) {//构造函数
		edge_value = new MST_edge_node<T, E>[size];
	}
	~MST() {//析构函数
		delete[]edge_value;
	}
	int insert(MST_edge_node<T, E>& item);
	void enlarge(int size);
	bool empty();
	int get_max_size() {
		return max_size;
	}
	int get_n() {
		return n;
	}
	MST_edge_node<T, E>* get_edge_value() {
		return edge_value;
	}

	int get_edge_node_tail(int i) {
		return edge_value[i].tail;
	}
	int get_edge_node_head(int i) {
		return edge_value[i].head;
	}

	int get_edge_node_key(int i) {
		return this->edge_value[i].key;
	}
};

template<class T, class E>
int MST<T, E>::insert(MST_edge_node<T, E>& item) {
	if (n == max_size)
		return false;//树满，不能插入
	edge_value[n].key = item.key;
	edge_value[n].tail = item.tail;
	edge_value[n].head = item.head;
	n++;
	return true;
}

template<class T, class E>
void MST<T, E>::enlarge(int size) {
	MST_edge_node<T, E>* e;
	if (!(size > max_size))
		return;
	e = new MST_edge_node<T, E>[size];
	for (int i = 0; i < n; i++) {
		e[i] = edge_value[i];//每个边赋值过去
	}
	max_size = size;
	delete[]edge_value;
	edge_value = e;
}

template<class T, class E>
bool MST<T, E>::empty() {
	return (edge_value == NULL) ? true : false;
}
#endif


