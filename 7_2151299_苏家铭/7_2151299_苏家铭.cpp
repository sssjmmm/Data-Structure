#include<iostream>
using namespace std;
#include"7_2151299_苏家铭.h"
/*
8 
4 5 1 2 1 3 1 1
*/
int main() {
	int N, i = 1, val, sum = 0;

	cout << "请输入正整数N（N《104），表示要将木头锯成N块。" << endl;
	cout << "第二行请给出N个正整数，表示每块木头的长度。" << endl;
	while (1) {//健壮性
		cin >> N;
		if (cin.fail() || N <= 0) {
			cout << "输入非法，请再次输入块数:" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}
	minPQueue<int> q(N);//建立一个大小为N的堆
	while (i <= N) {
		while (1) {
			cin >> val;
			if (cin.fail() || val <= 0) {//健壮性
				cout << "输入木块长度非法" << endl;
				cin.clear();
				cin.ignore(65535, '\n');
				cout << endl << "PRESS ANY KEY TO CONTINUE...";
				cin.get();
				return 0;
			}
			else
				break;
		}
		q.push(val);//所有元素入队
		i++;
	}//建立了一个最小优先队列
	if (q.size() == 1)//只有一个元素
		sum = q.front();
	while (q.size() > 1) {//还有元素
		int length1 = q.front();//取最小元素
		q.pop();
		int length2 = q.front();//取次小元素
		q.pop();
		sum += length1 + length2;//花费累计
		q.push(length1 + length2);//权值相加后再入队
	}
	cout << "cost:" << sum << endl;

	cin.clear();
	cin.ignore(65535, '\n');
	cout << endl << "PRESS ANY KEY TO CONTINUE...";
	cin.get();
	return 0;
}
