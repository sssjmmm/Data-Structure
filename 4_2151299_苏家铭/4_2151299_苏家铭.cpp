#include<iostream>
#include<math.h>
#include"4_2151299_苏家铭.h"
 

/*
		判断负号还是减号方法:
		 "-"前面是")"或者数字作为减
		 "-'后面是"(" 作为单目取反
		 否则都是负号
		 正号同理
*/
using namespace std;

double str_to_num(String& str);
int isp(char& c) {
	if (c == '#') {
		return 0;
	}
	else if (c == '(') {
		return 1;
	}
	else if (c == '*' || c == '/' || c == '%') {
		return 5;
	}
	else if (c == '+' || c == '-') {
		return 3;
	}
	else if (c == ')') {
		return 6;
	}
	return 999;

}
int icp(char& c) {
	if (c == '#') {
		return 0;
	}
	else if (c == '(') {
		return 6;
	}
	else if (c == '*' || c == '/' || c == '%') {
		return 4;
	}
	else if (c == '+' || c == '-') {
		return 2;
	}
	else if (c == ')') {
		return 1;
	}
	return 999;
}
void postfix(String& str, String& ans) {//中缀表达式转换为后缀表达式函数，此时中缀最后一个字符为#
	LinkedStack<char>s;
	String shuzi;
	char ch = '#', ch1, op;
	int i = 0;
	s.Push(ch);
	//cin.get(ch);
	ch = str[i++];
	while (s.IsEmpty() == false) {

		if (ch == '#') {
			while (s.IsEmpty() == false) {
				s.Pop(op);
				if (op != '#')
					ans = ans + op + " ";
				//cout << op;
			}
			//去掉尾空格
			ans.pop_back();
			cout << ans;
			return;
		}
		if (!(((ch == '-' || ch == '+') && i - 2 >= 0 && str[i - 2] == ')') ||//不是加减
			((ch == '-' || ch == '+') && i - 2 >= 0 && isdigit(str[i - 2])) ||
			((ch == '-' || ch == '+') && i  < int(str.length()) && str[i] == '('))) {//不是单目 
			//不是加减不是单目那就负号
			if (ch == '-') {
				shuzi += ch;
				ch = str[i++];
			}
			else if (ch == '+') {
				ch = str[i++];
			}
		}
		if (isdigit(ch) || ch == '.') {//数字或者小数点或者负号就放入shuzi字符串
			//cout << ch;
			shuzi += ch;//存入数字字符串
			if (!(isdigit(str[i]) || str[i] == '.')) {//下一位不为数字
				ans = ans + shuzi + " ";//装进ans
				shuzi = "";//重新置为空
			}
			//cin.get(ch);
			ch = str[i++];
		}
		else {
			s.getTop(ch1);
			if (isp(ch1) < icp(ch)) {
				s.Push(ch);
				ch = str[i++];
				//cin.get(ch);
			}
			else if (isp(ch1) > icp(ch)) {
				s.Pop(op);
				ans = ans + op + " ";//存入ans
				//cout<<op;
			}
			else {
				s.Pop(op);
				if (op == '(')
					ch = str[i++];
				//cin.get(ch);
			}
		}
	}//end of while


};

void run(String& str) {
	int i = 0, len = str.length();
	str += '#';
	String temp = "";
	LinkedStack<double> st;
	while (i < len) {
		if (isdigit(str[i]) || (str[i] == '-' && isdigit(str[i + 1]))) {//是数字
			while (str[i] != ' ' && i < len) {
				temp += str[i];
				i++;
			}
			i++;//指向下一个数字或字符
			double d;
			d = str_to_num(temp);
			st.Push(d);
			temp = "";
		}
		else if (str[i] == '-' || str[i] == '+' || str[i] == '*' || str[i] == '/') {//单个符号 从栈取两个数进行操作
			if (!st.IsEmpty()) {
				double d1, d2;
				st.Pop(d1);
				if (!st.Pop(d2))
					d2 = 0;
				if (str[i] == '+')
					d2 += d1;
				else if (str[i] == '-')
					d2 -= d1;
				else if (str[i] == '*')
					d2 *= d1;
				else if (str[i] == '/')
					d2 /= d1;
				st.Push(d2);
			}
			i += 2;

		}
	}//end of while
	double ans;
	st.getTop(ans);
	cout << ans << endl;
}
/*将字符串数字换成double*/
double str_to_num(String& str)
{
	double ans = 0;
	bool minus = false;
	int indexOfPoint = 0;
	if (str[0] == '-')
		minus = true;
	while (indexOfPoint < str.length() && str[indexOfPoint] != '.')
		indexOfPoint++;
	for (int i = 0 + minus; i < indexOfPoint; ++i)
		ans = ans * 10 + str[i] - '0';

	if (indexOfPoint == str.length())
		return (minus ? -ans : ans);

	const int sjm = 15;
	double temp = 0;
	double exp = 0.1;
	for (int i = indexOfPoint + 1; i < str.length() && i < indexOfPoint + sjm; ++i) {
		temp += (double(str[i]) - '0') * exp;
		exp /= 10;
	}
	return (minus ? -(ans + temp) : (ans + temp));

}
int main() {
	String s0,s, ans;
	//s = "12+(34*(56-789)-32/23)";
	cout << "please input infix expression:" << endl;
	char* ch=new char[80];
	fgets(ch,80,stdin);
	s0 = ch;
	//s = "((2+3)*4-(8+2))/5";
	//s="2+3*(7-4)+8/4";
	//s = "-1-(-3)";
	//s = "+(2*(+3))";
	//s = "3+4";
	//s = "1314+25.5*12";
	//s = "-0";
	//去掉空格
	int len = s0.length();
	for (int i = 0; i <len-1 ; ++i) {
		//if (s[len - 1] == ' ')
		if (s0[i] != ' ') {
			if (s0[i]!='.'&&s0[i] != '+' && s0[i] != '-' && s0[i] != '*' && s0[i] != '/' &&
				s0[i] != '(' && s0[i] != ')' && s0[i] != '%' && !(s0[i] >= '0' && s0[i] <= '9')) {
				cout << "含有非法字符！" << endl;
				cin.clear();
				cin.ignore(65535, '\n');
				cout << endl << "PRESS ANY KEY TO CONTINUE...";
				cin.get();
				delete[] ch;
				return 0;
			}
			s += s0[i];
		}
	}
	//非法字符

	s += "#";
	cout << "中缀表达式转后缀表达式为：" << endl;
	postfix(s, ans);
	//此时ans为后缀表达式结果，已达到项目要求
	cout << endl << "后缀表达式的运算结果为：";
	run(ans);
	cin.clear();
	cin.ignore(65535, '\n');
	cout << endl << "PRESS ANY KEY TO CONTINUE...";
	cin.get();
	delete[] ch;
}
