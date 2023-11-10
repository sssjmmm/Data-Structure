#include<iostream>
using namespace std;
#include"5_2151299_苏家铭.h"
int ans[1000]; 
int main() {
	Queue<int> qA, qB;//奇数去A队，偶数去B队
	int sum, num, i = 1;
	cout << "请输入为一行正整数，" << endl;
	cout << "其中第一个数字N（N <= 1000）为顾客总数，" << endl;
	cout << "后面跟着N位顾客的编号。数字间以空格分隔。" << endl;
	while (1) {//健壮性
		cin >> sum;
		if (cin.fail() || sum < 1) {//输入非法
			cout << "输入个数非法，请再次输入！" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else {//输入正确
			break;
		}
	}
	while (i++ <= sum) {
		while (1) {//健壮性
			cin >> num;
			if (cin.fail() || num < 1) {//输入非法
				cout <<endl<< "此编号序列存在非法字符！"<<endl;
				cin.clear();
				cin.ignore(65535, '\n');
				cout << endl << "PRESS ANY KEY TO CONTINUE...";
				cin.get();
				return 0;
			}
			else {//输入正确
				break;
			}
		}
		if (num % 2 == 1)//奇数
			qA.push(num);
		else//偶数
			qB.push(num);
	}//入队完毕
	i = 1;
	//出队
	while (!qA.empty() && !qB.empty()) {
		ans[i++] = qA.front();
		qA.pop();
		if (qA.empty())
			break;
		ans[i++] = qA.front();
		qA.pop();
		ans[i++] = qB.front();
		qB.pop();
	}
	if (qA.empty() && !qB.empty()) {//A空B不空
		while (!qB.empty()) {//让B空
			ans[i++] = qB.front();
			qB.pop();
		}
	}
	else if (!qA.empty() && qB.empty()) {//B空A不空
		while (!qA.empty()) {//让A空
			ans[i++] = qA.front();
			qA.pop();
		}
	}
	i = 1;
	//此时答案已经在ans[1]--ans[sum]
	while (i < sum) {
		cout << ans[i++] << " ";
	}
	cout << ans[i];


	cin.clear();
	cin.ignore(65535, '\n');
	cout << endl << "PRESS ANY KEY TO CONTINUE...";
	cin.get();
}
