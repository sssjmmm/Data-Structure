#include<iostream>
#include<climits>
using namespace std;
#include"9_2151299_苏家铭.h"
/*
*/
/*
7 8
1 2 4
1 3 3
2 4 5
3 4 3
4 5 2
4 6 6
5 7 5
6 7 2
 
9 11
1 2 6
1 3 4
1 4 5
2 5 1
3 5 1
4 6 2
5 7 9
5 8 7
6 8 4
7 9 2
8 9 4
*/
template<class T, class E>
void AOE(graph<T, E>& Gin, graph<T, E>& Gout, int* in, int* out);
int main() {
	int N, M;
	graph<int, int> Gin, Gout;
	cout << "第一行请输入两个正整数——任务交接点数N与任务数M：" << endl;
	cout<<"随后M行，每行给出3个正整数"<<endl;
	cout << "分别是该任务开始和完成设计的交接点编号以及完成该任务所需要的时间" << endl;
	cout << "整数间用空格分隔。" << endl;
	while (1) {
		cin >> N >> M;//结点和边
		if (cin.fail() || N < 0 || M < 0) {
			cout << "输入不合法，请再次输入结点和边:" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
		

	}
	int i = 1, front, end, weight;

	while (i <= N) {
		Gin.insert_vertex(i);
		Gout.insert_vertex(i);
		i++;
	}
	//建立一个入度图和一个出度图

	i = 0;
	int j, k;
	while (i < M) {
		cin >> front >> end >> weight;
		j = Gin.get_vertex_pos(front);
		k = Gin.get_vertex_pos(end);//查顶点号
		if (j == -1 || k == -1)
			cout << "边两端点信息有误，请重新输入！" << endl;
		Gout.insert_directed_edge(j, k, weight);//出度图
		Gin.insert_directed_edge(k, j, weight);//入度图
		i++;
	}
	//入度、出度数组
	int* in, * out;
	in = new int[N];
	out = new int[N];
	for (int i = 0; i < N; i++) {
		in[i] = Gin.get_neighbor_num(i);//i是节点数组的位置
		out[i] = Gout.get_neighbor_num(i);
	}
	cout << "所需时长以及关键路径为:" << endl;
	AOE(Gin, Gout, in, out);
	delete[] in;
	delete[] out;
	cin.clear();
	cin.ignore(65535, '\n');
	cout << endl << "PRESS ANY KEY TO CONTINUE...";
	cin.get();
	return 0;

}


template<class T, class E>
void AOE(graph<T, E>& Gin, graph<T, E>& Gout, int* in, int* out) {
	Queue<int>q;
	int n = Gin.vertices_number();
	E* Ve = new E[n];
	E* Vl = new E[n];
	for (int i = 0; i < n; i++)//Ve[]置0
		Ve[i] = 0;
	for (int i = 0; i < n; i++)  //n  节点的总数
		if (in[i] == 0)
			q.push(i);  //将入度为0的点入队列,队列中是顶点序号

	int next;
	while (!q.empty()) {//顺序拓扑排序，在这个过程中计算Ve
		int p = q.front();
		q.pop(); // 选一个入度为0的点，出队列
		next = Gout.get_first_neighbor(p);
		for (int i = 0; i < Gout.get_neighbor_num(p); i++) {
			//把这个点周围一圈箭头都消掉，再判断有没有入度为0的点
			//更新Ve
			int w = Gout.get_weight(p, next);
			if (Ve[p] + w > Ve[next])
				Ve[next] = Ve[p] + w;
			in[next]--;
			if (in[next] == 0)
				q.push(next);
			next = Gout.get_next_neighbor(p, next);
		}
	}

	for (int i = 0; i < n; i++)//Vl[]置无穷
		Vl[i] = INT_MAX;
	Vl[n - 1] = Ve[n - 1];
	while (!q.empty())
		q.pop();//置空;
	for (int i = 0; i < n; i++)  //n  节点的总数
		if (out[i] == 0) q.push(i);  //将出度为0的点入队列,队列中是顶点序号

	while (!q.empty()) {//逆拓扑排序，在这个过程中计算Vl
		int p = q.front(); q.pop(); // 选一个入度为0的点，出队列
		next = Gin.get_first_neighbor(p);
		for (int i = 0; i < Gin.get_neighbor_num(p); i++) {
			//把这个点周围一圈箭头都消掉，再判断有没有入度为0的点
			//更新Ve
			int w = Gin.get_weight(p, next);
			if (Vl[p] - w < Vl[next])
				Vl[next] = Vl[p] - w;

			out[next]--;
			if (out[next] == 0)
				q.push(next);
			next = Gin.get_next_neighbor(p, next);
		}
	}
	
	cout << Ve[n - 1] << endl;
	E Ae, Al;
	for (int i = 0; i < n; i++) {//若Ae==Al则该活动是关键活动
		int j = Gout.get_first_neighbor(i);
		while (j != -1) {
			Ae = Ve[i];
			Al = Vl[j] - Gout.get_weight(i, j);
			if (Al == Ae)
				cout << Gout.get_value(i) << "->"
				<< Gout.get_value(j) << endl;
			j = Gout.get_next_neighbor(i, j);
		}
	}

	delete[]Ve;
	delete[]Vl;
}
