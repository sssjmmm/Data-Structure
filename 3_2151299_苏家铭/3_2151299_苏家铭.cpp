/*BFS(有队列/无队列) DFS 递归 A星*/
#include<iostream>
#include"3_2151299_苏家铭.h"
#include<cstring>
#include<algorithm>
#include<cmath>
 
using namespace std;

#define MAZE_ROW 6
#define MAZE_COL 6
#define ENTRANCE_ROW 1
#define ENTRANCE_COL 0
#define END_ROW 6
#define END_COL 7
struct note {
	int x;
	int y;
	int f;
	int s;
};
struct xynote {
	int x;
	int y;
	int s;
	xynote() { x = y = s = -1; };
	friend bool operator<(const xynote& a, const xynote& b) {
		return (abs(END_ROW - a.x) + abs(END_COL - a.y)) < (abs(END_ROW - b.x) + abs(END_COL - b.y));
	}

	friend bool operator>(const xynote& a, const xynote& b) {
		return (abs(END_ROW - a.x) + abs(END_COL - a.y)) > (abs(END_ROW - b.x) + abs(END_COL - b.y));
	}

	bool operator==(const xynote& b) {
		return (abs(END_ROW - x) + abs(END_COL - y)) == (abs(END_ROW - b.x) + abs(END_COL - b.y));
	}

	bool operator<=(const xynote& b) {
		return (abs(END_ROW - x) + abs(END_COL - y)) <= (abs(END_ROW - b.x) + abs(END_COL - b.y));
	}

	bool operator>=(const xynote& b) {
		return (abs(END_ROW - x) + abs(END_COL - y)) >= (abs(END_ROW - b.x) + abs(END_COL - b.y));
	}
};
struct offsets {
	int a, b;//a,b是x,y方向的偏移
	const char* dir;//dir是方向
}move[8];
struct items {
	int x, y, dir;
};


class find_path {
public:
	int maze[MAZE_ROW + 2][MAZE_COL + 2] = { {1,1,1,1,1,1,1,1},
											 {0,0,1,1,1,1,1,1},
											 {1,0,0,1,0,1,1,1},
											 {1,0,0,0,0,0,0,1},
											 {1,1,0,0,0,1,0,1},
											 {1,0,1,0,0,0,0,1},
											 {1,1,1,1,0,0,0,0},
											 {1,1,1,1,1,1,1,1}
	};//迷宫定义


	int mark[MAZE_ROW + 2][MAZE_COL + 2];

	LinkedStack<items>ans;
	offsets move[4] = { {-1,0,"N"},{0,1,"E"},
						{1,0,"S"},
						{0,-1,"W"}
	};
	find_path();
	void path_DFS(int start_r, int statr_c, int m, int p);//深度优先搜索
	void path_BFS(int start_r, int start_c, int end_r, int end_c);//广度优先搜索
	void path_recursion(int start_r, int start_c, int end_r, int end_c);//递归求深度
	void path_BFS_queue(int start_r, int start_c, int end_r, int end_c);//队列求广度
	void path_Astar(int start_r, int start_c, int end_r, int end_c);//A*算法
	int recursion(int start_r, int start_c, int end_r, int end_c);
};
void find_path::path_BFS(int start_r, int start_c, int end_r, int end_c) {
	struct note que[MAZE_ROW * MAZE_COL + 1];//结构体数组记录寻路过程

	int flag = 0;//标记符，是否找到出口

	int next[4][2] = { {0,1} ,{1,0} , {0, -1},{-1,0}//二维数组表示四个方向上下左右
	};
	int head = 1, tail = 2, tx, ty;
	int i;

	que[head].x = start_r;//初始化起点
	que[head].y = start_c;
	que[head].f = 0;
	que[head].s = 0;
	memset(mark, 0, sizeof(mark));//标记数组mark置0
	mark[start_r][start_c] = 1;//起点已经走过，为1

	while (head < tail)
	{
		for (int k = 0; k < 4; k++) {
			tx = que[head].x + next[k][0];
			ty = que[head].y + next[k][1];
			if (tx<1 || tx >(MAZE_ROW + 1) || ty < 1 || ty >(MAZE_COL + 1)) {//在迷宫中
				continue;
			}
			if (maze[tx][ty] == 0 && mark[tx][ty] == 0)//还未走过可探索
			{
				que[tail].x = tx;
				que[tail].y = ty;
				que[tail].f = head;
				que[tail].s = que[head].s + 1;
				tail++;//延申
				mark[tx][ty] = 1;
			}
			if (tx == end_r && ty == end_c) {//找到出口
				flag = 1;
				break;
			}
		}
		if (flag == 1)
			break;
		head++;//重点
	}
	int str[MAZE_ROW * MAZE_COL + 1][2] = { 0 };
	if (flag == 1) {//找到一条可行路径
		i = 1;
		tail--;
		while (que[tail].s != 0) {
			str[i][0] = que[tail].x;
			str[i][1] = que[tail].y;
			tail = que[tail].f;
			i++;
		}
		i--;
		cout << "BFS route are as follows:" << endl;//输出路径
		cout << "(" << start_r << " " << start_c << ")" << "-->" << "(" << str[i][0] << " " << str[i][1] << ")";

		while (i > 0) {//逆序输出路径
			if (i - 1 > 0)
				cout << "-->" << "(" << str[i - 1][0] << " " << str[i - 1][1] << ")";

			i--;
		}
	}
	else if (start_r == END_ROW && start_c == END_COL) {//起点就是终点
		cout << "BFS route are as follows:" << endl;
		cout << "(" << start_r << " " << start_c << ")";
	}
	else//没有可以到达的路径
		cout << "no path in maze" << endl;
	memset(mark, 0, sizeof(mark));//mark数组重置
	return;
}
void find_path::path_DFS(int start_r, int start_c, int m, int p) {
	int i, j, d, g, h;
	mark[start_r][start_c] = 1;//设置入口坐标，mark置为1
	//LinkedStack<items>st(MAZE_ROW * MAZE_COL);
	LinkedStack<items>st;
	LinkedStack<items> end;
	items temp;//设置工作栈和工作单元
	temp.x = start_r;
	temp.y = start_c;
	temp.dir = 0;
	st.Push(temp);//初始化坐标方向三元组进栈
	while (st.IsEmpty() == false) {//栈不空，继续搜索
		st.Pop(temp);//出栈
		i = temp.x;
		j = temp.y;
		d = temp.dir;//d为前进方向表move[]的下标
		while (d < 4) {//还有方向能继续搜索
			g = i + move[d].a;//找下一个位置(g,h)
			h = j + move[d].b;
			if (g == m && h == p) {//找到出口
				temp.x = i;
				temp.y = j;
				temp.dir = d;
				st.Push(temp);//(i.j)进栈
				cout << "DFS route are as follows:" << endl;//输出路径
				if (start_r == END_ROW && start_c == END_COL) {
					cout << "(" << start_r << " " << start_c << ")" << endl;
					memset(mark, 0, sizeof(mark));
					return;
				}
				while (st.IsEmpty() == 0) {
					st.Pop(temp);
					end.Push(temp);
				}
				while (end.IsEmpty() == 0) {
					end.Pop(temp);
					cout << "(" << temp.x << " " << temp.y << ")" << "-->";
				}
				cout << "(" << m << " " << p << ")" << endl;
				memset(mark, 0, sizeof(mark));
				return;
			}
			if (maze[g][h] == 0 && mark[g][h] == 0) {//新的位置可通
				mark[g][h] = 1;//标记为已访问过
				temp.x = i;//记忆已经通过的位置和前进位置
				temp.y = j;
				temp.dir = d;
				st.Push(temp);//进栈
				i = g;//移动到(g,h)，在各个方向试探
				j = h;
				d = 0;
			}
			else
				d++;
		}
	}
	cout << "no path in maze" << endl;
	memset(mark, 0, sizeof(mark));
}
int find_path::recursion(int start_r, int start_c, int  end_r, int end_c) {
	int i, g, h;
	items temp;
	mark[start_r][start_c] = 1;//设置入口坐标，mark置为1
	if (start_r == end_r && start_c == end_c)
		return 1;
	for (i = 0; i < 4; i++) {
		g = start_r + move[i].a;
		h = start_c + move[i].b;
		if (maze[g][h] == 0 && mark[g][h] == 0) {
			mark[g][h] = 1;
			if (recursion(g, h, end_r, end_c)) {//搜索成功，把逆序压入栈
				temp.x = g;
				temp.y = h;
				temp.dir = i;
				ans.Push(temp);
				return 1;
			}
		}
		//换一个方向再次搜索
	}
	return 0;
}
void find_path::path_recursion(int start_r, int start_c, int  end_r, int end_c) {
	items temp;
	recursion(ENTRANCE_ROW, ENTRANCE_COL, END_ROW, END_COL);//递归寻路
	if (ans.IsEmpty() == true) {//栈空，没有可行路径或起点就是终点
		if (start_r == END_ROW && start_c == END_COL) {
			cout << "Recursion route are as follows:" << endl;//输出路径
			cout << "(" << ENTRANCE_ROW << " " << ENTRANCE_COL << ")";
			memset(mark, 0, sizeof(mark));
			ans.makeEmpty();
			return;
		}
		cout << "recursion no path in maze" << endl;
	}
	else {
		cout << "Recursion route are as follows:" << endl;//输出路径
		cout << "(" << ENTRANCE_ROW << " " << ENTRANCE_COL << ")" << "-->";
		while (ans.IsEmpty() == 0) {
			ans.Pop(temp);
			cout << "(" << temp.x << " " << temp.y << ")";
			if (!(temp.x == end_r && temp.y == end_c))
				cout << "-->";
		}
	}
	memset(mark, 0, sizeof(mark));
	ans.makeEmpty();
	return;
}
void find_path::path_BFS_queue(int start_r, int start_c, int end_r, int end_c) {
	int next[4][2] = { {0,1} ,{1,0} , {0, -1},{-1,0}
	};
	memset(mark, 0, sizeof(mark));
	Queue<xynote> q;
	xynote N[MAZE_COL + 2][MAZE_COL + 2], n;
	int S = 0;
	bool flag = false;
	mark[start_r][start_c] = 1;//入口置1
	N[start_r][start_c].x = start_r;//标记起点
	N[start_r][start_c].y = start_c;
	N[start_r][start_c].s = S;
	q.push(N[start_r][start_c]);//起点进队列
	while (!q.empty()) {//当队列不为空
		n = q.front();//取队首
		q.pop();//出队

		if (n.x == end_r && n.y == end_c) {//找到终点
			flag = true;
			break;
		}

		for (int i = 0; i < 4; ++i) {//朝四个方向逐层遍历
			int curX = n.x + next[i][0];
			int curY = n.y + next[i][1];
			if (curX < 0 || curX >= MAZE_ROW + 2 || curY < 0 || curY >= MAZE_COL + 2)//已经超过迷宫范围
				continue;
			if (maze[curX][curY] == 0 && mark[curX][curY] == 0) {//可以到达
				N[curX][curY].x = curX;
				N[curX][curY].y = curY;
				N[curX][curY].s = n.s + 1;
				q.push(N[curX][curY]);
				mark[curX][curY] = 1;
			}
		}//end of for
	}//end of while

	/*逆序输出，用栈反转*/
	LinkedStack<xynote> stack;
	int curX = n.x, curY = n.y;
	if (flag == true) {
		stack.Push(n);//最后一个结点进栈
		while (!(curX == start_r && curY == start_c)) {
			for (int i = 0; i < 4; ++i) {
				stack.getTop(n);
				curX = n.x + next[i][0];
				curY = n.y + next[i][1];
				if (curX < 0 || curX >= MAZE_ROW + 2 || curY < 0 || curY >= MAZE_COL + 2)
					continue;
				if (N[curX][curY].s == n.s - 1) {//找比前一个结点路程小1的结点
					stack.Push(N[curX][curY]);//下一个结点进栈
					break;
				}
			}//end of for

		}//end of while
	}
	cout << "BFS(using queue) route are as follows:" << endl;//输出路径
	while (stack.IsEmpty() == 0) {
		stack.Pop(n);
		cout << "(" << n.x << " " << n.y << ")";
		if (!(n.x == end_r && n.y == end_c))
			cout << "-->";
	}
}

void find_path::path_Astar(int start_r, int start_c, int end_r, int end_c) {
	int next[4][2] = { {0,1} ,{1,0} , {0, -1},{-1,0}
	};
	memset(mark, 0, sizeof(mark));
	minPQueue<xynote> q;//用小根堆实现的优先级队列
	xynote N[MAZE_COL + 2][MAZE_COL + 2], n;
	int S = 0;
	bool flag = false;
	mark[start_r][start_c] = 1;//入口置1
	N[start_r][start_c].x = start_r;
	N[start_r][start_c].y = start_c;
	N[start_r][start_c].s = S;
	q.push(N[start_r][start_c]);
	while (!q.empty()) {
		n = q.front();
		q.pop();

		if (n.x == end_r && n.y == end_c) {
			flag = true;
			break;//找到终点
		}

		for (int i = 0; i < 4; ++i) {
			int curX = n.x + next[i][0];
			int curY = n.y + next[i][1];
			if (curX < 0 || curX >= MAZE_ROW + 2 || curY < 0 || curY >= MAZE_COL + 2)
				continue;
			if (maze[curX][curY] == 0 && mark[curX][curY] == 0) {
				N[curX][curY].x = curX;
				N[curX][curY].y = curY;
				N[curX][curY].s = n.s + 1;
				q.push(N[curX][curY]);
				mark[curX][curY] = 1;
			}
		}//end of for
	}//end of while


	LinkedStack<xynote> stack;
	int curX = n.x, curY = n.y;
	if (flag == true) {
		stack.Push(n);//最后一个结点进栈
		while (!(curX == start_r && curY == start_c)) {
			for (int i = 0; i < 4; ++i) {
				stack.getTop(n);
				curX = n.x + next[i][0];
				curY = n.y + next[i][1];
				if (curX < 0 || curX >= MAZE_ROW + 2 || curY < 0 || curY >= MAZE_COL + 2)
					continue;
				if (N[curX][curY].s == n.s - 1) {//找比前一个结点路程小1的结点
					stack.Push(N[curX][curY]);//下一个结点进栈
					break;
				}
			}//end of for

		}//end of while
	}
	cout << "Astar route are as follows:" << endl;//输出路径
	while (stack.IsEmpty() == 0) {
		stack.Pop(n);
		cout << "(" << n.x << " " << n.y << ")";
		if (!(n.x == end_r && n.y == end_c))
			cout << "-->";
	}
}


find_path::find_path()
{

	for (int i = 0; i < MAZE_ROW; ++i)
		for (int j = 0; j < MAZE_COL; ++j)
		{
			mark[i][j] = 0;
		}
}
int main() {
	find_path a;
	int i = 0;
	cout << "     ";
	while (i < MAZE_COL+2) {
		cout << i++ << "列 ";
	}
	cout << endl;
	for (int i = 0; i < MAZE_ROW + 2; i++) {
		cout << i << "行  ";
		for (int j = 0; j < MAZE_COL + 2; j++) {
			cout << a.maze[i][j] << "   ";
		}
		cout << endl;
	}
	a.path_DFS(ENTRANCE_ROW, ENTRANCE_COL, END_ROW, END_COL);
	cout << endl;
	a.path_BFS(ENTRANCE_ROW, ENTRANCE_COL, END_ROW, END_COL);
	cout << endl << endl;
	a.path_recursion(ENTRANCE_ROW, ENTRANCE_COL, END_ROW, END_COL);
	cout << endl << endl;
	a.path_BFS_queue(ENTRANCE_ROW, ENTRANCE_COL, END_ROW, END_COL);
	cout << endl << endl;
	a.path_Astar(ENTRANCE_ROW, ENTRANCE_COL, END_ROW, END_COL);

	cin.clear();
	cin.ignore(65535, '\n');
	cout << endl << "PRESS ANY KEY TO CONTINUE...";
	cin.get();
}
