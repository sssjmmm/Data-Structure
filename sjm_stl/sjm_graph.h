#ifndef __SJM_GRAPH_
#define _SJM_GRAPH_
#include<iostream>
#include<climits>
using namespace std;

#define DEFAULT_VERTICES 30
#define MAX_WEIGHT 8177919//��������

template<class T, class E>//T�Ƕ��������ݵ����ͣ�E�Ǳ����������ݵ�����
class GRAPH {
protected:
	int max_vertices_num;//ͼ����󶥵���
	int edges_num;//��ǰ����
	int vertices_num;//��ǰ������
public:
	//GRAPH(int size = DEFAULT_VERTICES);//����
	//~GRAPH();//����
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
	int vertices_number() {//���ص�ǰ�����
		return vertices_num;
	}
	int edges_number() {//���ص�ǰ����
		return edges_num;
	}
};

template<class T, class E>
struct edge {//�߽��ṹ��
	int dest;//�߽��Ķ���
	E cost;//���ϵ�Ȩֵ
	edge<T, E>* link;//��һ������ָ��
	edge() :dest(-1), cost(-1), link(NULL) {};//���캯��
	edge(int num, E data) :dest(num), cost(data), link(NULL) {};//���캯��
	bool operator!=(edge<T, E>& R)const {
		return (dest != R.dest) ? true : false;
	}
};

template<class T, class E>
struct vertex {//����ṹ��
	T data;//���������
	edge<T, E>* adj;//�������ͷָ��
};



template<class T, class E>//T�Ƕ������ݵ����ͣ�E�Ǳ����������ݵ�����
class graph :public GRAPH<T, E> {//���м̳�
private:
	vertex<T, E>* node_table;//��������������ͷ��㣩
public:
	graph(int size = DEFAULT_VERTICES);//���캯��:����һ���յ��ڽӱ�
	~graph();//��������:ɾ��һ���ڽӱ�
	T get_value(int i);//ȡλ��Ϊi�Ķ����е�ֵ
	E get_weight(int v1, int v2);//���رߣ�v1,v2���ϵ�Ȩֵ
	bool insert_vertex(const T& vertex);//��ͼ�в���һ������vertex
	bool remove_vertex(int v);//��ͼ��ɾ��һ������vertex
	bool insert_edge(int v1, int v2, E cost);//��ͼ�в���һ���������(v1,v2)
	bool insert_directed_edge(int v1, int v2, E cost);//��ͼ�в���һ���������(v1,v2)
	bool remove_edge(int v1, int v2);//��ͼ��ɾ��һ����(v1,v2)
	int get_vertex_pos(const T vertex);//���ض���vertex��ͼ�е�λ��
	int get_first_neighbor(int v);//ȡ����v�ĵ�һ���ڽӶ���
	int get_next_neighbor(int v, int w);//ȡv���ڽӶ���w����һ�ڽӶ���

	int get_neighbor_num(int v);//���ظõ���ڽӱ�����
	friend istream& operator>>(istream& in, const graph& G)
	{
		//ͨ��������������in����n�������e������ߵ���Ϣ����ͼ
		int i, j, k, n, m;
		T e1, e2;
		E weight;
		in >> n >> m;//���붥�����ͱ���
		for (i = 0; i < n; i++) {//�������������
			in >> e1;
			G.insert_vertex(e1);
		}
		i = 0;
		while (i < m) {
			in >> e1 >> e2 >> weight;//����˵���Ϣ
			j = G.get_vertex_pos(e1);
			k = G.get_vertex_pos(e2);//�鶥���
			if (j == -1 || k == -1)
				cout << "�����˵���Ϣ�������������룡" << endl;
			else {
				G.insert_edge(j, k, weight);
				++i;
			}
		}
		return in;
	}

	friend ostream& operator<< (ostream& out, const graph& G)
	{
		//����ͼ�����ж���ͱߵ���Ϣ
		int i, j, n, m;
		T e1, e2;
		E w;
		n = G.vertices_number();
		m = G.edges_number();
		out << "��������" << n << "," << "������" << m << endl;
		for (i = 0; i < n; i++) {
			for (j = i + 1; j < n; j++) {
				w = G.get_weight(i, j);//ȡ����Ȩֵ
				if (w > 0 && w < MAX_WEIGHT) {//Ȩֵ��Ч
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
int graph<T, E>::get_vertex_pos(const T vertex) {//���ض���vertex��ͼ�е�λ��
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
	node_table = new vertex<T, E>[this->max_vertices_num];//�������������
	if (node_table == NULL) {
		cerr << "�洢�������" << endl;
		return;
	}

	for (int i = 0; i < this->max_vertices_num; i++)
		node_table[i].adj = NULL;
}

template<class T, class E>
graph<T, E>::~graph() {//ɾ��һ���ڽӱ�
	for (int i = 0; i < this->vertices_num; i++) {//ɾ���������еĽ��
		edge<T, E>* p = node_table[i].adj;//�ҵ����Ӧ��������׽��
		while (p != NULL) {//���ϵ�ɾ����һ�����
			node_table[i].adj = p->link;
			delete p;
			p = node_table[i].adj;
		}
	}
	delete[]node_table;//ɾ�����������
}

template<class T, class E>
int graph<T, E>::get_first_neighbor(int v) {
	//��������λ��Ϊv�ĵ�һ���ڽӶ����λ�ã�����Ҳ�������������-1
	if (v != -1) {//����v����
		edge<T, E>* p = node_table[v].adj;//��Ӧ�������һ���߽��
		if (p != NULL)
			return p->dest;//���ڣ����ص�һ���ڽӽ��
	}
	return -1;//��һ���ڽӶ��㲻����
}

template<class T, class E>
int graph<T, E>::get_next_neighbor(int v, int w) {
	//��������v���ڽӶ���w����һ���ڽӶ����λ�ã���û���򷵻�-1
	if (v != -1) {//����v����
		edge<T, E>* p = node_table[v].adj;//��Ӧ�������һ���߽��
		while (p != NULL && p->dest != w)//Ѱ���ڽӶ���w
			p = p->link;
		if (p != NULL && p->link != NULL)
			return p->link->dest;//���ڣ���һ���ڽӽ��
	}
	return -1;//��һ���ڽӶ��㲻����
}

template<class T, class E>
E graph<T, E>::get_weight(int v1, int v2) {
	//�������رߣ�v1��v2���ϵ�Ȩֵ�����ñ߲���ͼ�У���������ȨֵINT_MAX
	if (v1 != -1 && v2 != -1) {
		edge<T, E>* p = node_table[v1].adj;//v1�ĵ�һ�������ı�
		while (p != NULL && p->dest != v2)//Ѱ���ڽӶ���v2
			p = p->link;
		if (p != NULL)
			return p->cost;//�ҵ��˱ߣ�����Ȩֵ
	}
	return INT_MAX;
}

template<class T, class E>
bool graph<T, E>::insert_vertex(const T& vertex) {
	//��ͼ�Ķ�����в���һ���µĶ���vertex
	if (this->vertices_num == this->max_vertices_num)
		return false;//������������ܲ���
	node_table[this->vertices_num].data = vertex;//���ڱ�����
	this->vertices_num++;
	return true;
}

template<class T, class E>
bool graph<T, E>::remove_vertex(int v) {
	//��ͼ��ɾ��һ������v,v�Ƕ����
	if (this->vertices_num == 0 || v < 0 || v >= this->vertices_num)//��ջ򶥵�󳬳���Χ
		return false;
	edge<T, E>* p, * s, * t;
	int i, k;
	while (node_table[v].adj != NULL) {//ɾ����v�������������н��
		p = node_table[v].adj;
		k = p->dest;//ȡ�ڽӶ���k
		s = node_table[k].adj;//�ҶԳƴ�ŵı߽��
		t = NULL;
		while (s != NULL && s->dest != v) {
			t = s;
			s = s->link;
		}
		if (s != NULL) {//ɾ���Գƴ�Ž��
			if (t == NULL)
				node_table[k].adj = s->link;
			else
				t->link = s->link;
			delete s;
		}
		node_table[v].adj = p->link;//�������v�ı�������
		delete p;
		this->edges_num--;//�붥��v������ı���-1
	}
	this->vertices_num--;//ͼ�Ķ��������1
	node_table[v].data = node_table[this->vertices_num].data;//�
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
	//�ڴ�Ȩͼ�в���һ��������ߣ�v1,v2��,���˱ߴ��ڻ������������false������true
	if (!(v1 >= 0 && v1 < this->vertices_num && v2 >= 0 && v2 < this->vertices_num))
		return false;
	edge<T, E>* q, * p = node_table[v1].adj;//v1��Ӧ�ı�����ͷָ��
	while (p != NULL && p->dest != v2)//Ѱ���ڽӶ���v2
		p = p->link;
	if (p != NULL)//�ҵ��˱ߣ�������
		return false;
	p = new edge<T, E>;
	q = new edge<T, E>;//�����½��
	p->dest = v2;
	p->cost = weight;
	p->link = node_table[v1].adj;//ͷ������
	node_table[v1].adj = p;
	q->dest = v1;
	q->cost = weight;
	q->link = node_table[v2].adj;//ͷ������
	node_table[v2].adj = q;
	this->edges_num++;
	return true;
}

template<class T, class E>
bool graph<T, E>::insert_directed_edge(int v1, int v2, E weight) {
	//�ڴ�Ȩͼ�в���һ��������ߣ�v1,v2��,���˱ߴ��ڻ������������false������true
	if (!(v1 >= 0 && v1 < this->vertices_num && v2 >= 0 && v2 < this->vertices_num))
		return false;
	edge<T, E>* p = node_table[v1].adj;//v1��Ӧ�ı�����ͷָ��
	while (p != NULL && p->dest != v2)//Ѱ���ڽӶ���v2
		p = p->link;
	if (p != NULL)//�ҵ��˱ߣ�������
		return false;
	p = new edge<T, E>;//�����½��
	p->dest = v2;
	p->cost = weight;
	p->link = node_table[v1].adj;//ͷ������
	node_table[v1].adj = p;
	this->edges_num++;
	return true;
}

template<class T, class E>
bool graph<T, E>::remove_edge(int v1, int v2) {
	//ɾ��һ���ߣ�v1��v2��
	if (v1 != -1 && v2 != -1) {
		edge<T, E>* p = node_table[v1].adj, * q = NULL, * s = p;
		while (p != NULL && p->dest != v2) {//v1��Ӧ�������ұ�ɾ��
			q = p;
			p = p->link;
		}
		if (q != NULL) {//�ҵ���ɾ�߽��
			if (p == s)//�ý���Ǳ������׽��
				node_table[v1].adj = p->link;
			else//�����׽��
				q->link = p->link;
			delete p;
		}
		else//û���ҵ���ɾ���
			return false;
		p = node_table[v2].adj;
		q = NULL, s = p;//v2��Ӧ������ɾ��
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
	edge<T, E>* p = node_table[v].adj;//��Ӧ�������һ���߽��
	if (v != -1) {//����v����
		while (p != NULL) {
			count++;
			p = p->link;
		}
		return count;
	}
	return -1;//���㲻����
}
#endif
