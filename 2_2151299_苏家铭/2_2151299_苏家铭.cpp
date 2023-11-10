#include<iostream>
using namespace std;
#include"2_2151299_苏家铭.h"
template<class T>
DblList<T> intersection(const DblList<T>& L1, const DblList<T>& L2);
 
int main() {
	DblList<int> L1, L2, L3;
	//输入L1和L2
	cout << "请输入L1集合的元素（以-1结尾，-1不计入其中）：";
	L1.input_endTag(-1);
	cout << "请输入L2集合的元素（以-1结尾，-1不计入其中）：";
	L2.input_endTag(-1);

	//求交集
	cout << "L1和L2和交集为：";
	L3 = intersection(L1, L2);
	//输出结果
	if (L3.IsEmpty()) {
		cout << "NULL" << endl;
	}
	else {
		DblNode<int>* head = L3.getHead(), * p;
		p = head->rLink;
		while (p != head) {
			if (p->rLink == head) //p是最后一个元素,不输出空格
				cout << p->data;
			else
				cout << p->data << " ";
			p = p->rLink;
		}
	}
	//L3.output(1);
	cin.clear();
	cin.ignore(65535, '\n');
	cout << endl << "PRESS ANY KEY TO CONTINUE...";
	cin.get();

}
template<class T>
DblList<T> intersection(const DblList<T>& L1, const DblList<T>& L2) {
	DblNode<T>* p1, * p2;
	DblList<T> ans;
	p1 = L1.getHead();
	p2 = L2.getHead();//分别指向头指针
	while (p1->rLink != L1.getHead() && p2->rLink != L2.getHead()) {
		if (p1->rLink->data < p2->rLink->data) {
			p1 = p1->rLink;
		}
		else if (p1->rLink->data > p2->rLink->data) {
			p2 = p2->rLink;
		}
		else {
			ans.push_back(p1->rLink->data);
			p1 = p1->rLink;
			p2 = p2->rLink;
		}
	}//end of while
	return ans;
}

