#ifndef __SJM_GRAPH_
#define _SJM_GRAPH_
#include<iostream>
#include<climits>
using namespace std;

#define DEFAULT_VERTICES 30
#define MAX_WEIGHT 8177919//代表无穷

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
				if (w > 0 && w < MAX_WEIGHT) {//权值有效
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
#endif
