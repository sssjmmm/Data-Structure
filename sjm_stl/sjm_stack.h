#ifndef _SJM_STACK_
#define _SJM_STACK_
#include<iostream>
#include<assert.h>
using namespace std;
/*链式栈*/
/*top->an--an-1--an-2--......--a1->NULL*/
template<class T>
struct LinkNode {//链表结点类
	T data;
	LinkNode* rLink;
	LinkNode(T d, LinkNode* L) :data(d), rLink(L) {};
};
template<class T>
class LinkedStack {
private:
	LinkNode<T>* top;
public:
	LinkedStack() :top(NULL) {}//构造函数，置空栈
	~LinkedStack() { makeEmpty(); };//析构函数
	void Push(const T& x);//元素进栈
	bool Pop(T& x);//元素退栈
	bool getTop(T& x)const;//返回栈顶元素
	bool IsEmpty()const { return(top == NULL) ? true : false; }
	int getSize()const;//返回栈的元素个数
	void makeEmpty();//清空栈
	friend ostream& operator << (ostream& os, LinkedStack<T>& s) {
		//输出栈中元素的重载操作<<
		os << "栈中元素个数=" << s.getSize() << endl;//输出栈中元素个数
		LinkNode<T>* p = s.top;
		int i = 0;//逐个输出栈中元素个数
		while (p != NULL) {
			os << ++i << ":" << p->data << endl;
			p = p->rLink;
		}
		return os;

	};//输出栈中元素的重载操作
};

template<class T>
void LinkedStack<T>::makeEmpty() {
	//逐次删去链式栈中的元素直至栈顶指针为空
	LinkNode<T>* p;
	while (top != NULL) {//逐个结点释放
		p = top;
		top = top->rLink;
		delete p;
	}
};

template<class T>
void LinkedStack<T>::Push(const T& x) {
	//将元素值x插入到链式栈的栈顶，即链头
	top = new LinkNode<T>(x, top);//创建新的含x结点
	assert(top != NULL);//创建新结点失败退出
}

template <class T>
bool LinkedStack<T>::Pop(T& x) {
	//删除栈顶结点，返回被删栈顶元素的值
	if (IsEmpty() == true)
		return false;//若栈空则不退栈，返回
	LinkNode <T>* p = top;//否则暂存栈顶元素
	top = top->rLink;
	x = p->data;
	delete p;//释放结点，返回退出元素的值
	return true;
}

template<class T>
bool LinkedStack<T>::getTop(T& x)const {
	//返回栈顶元素的值
	if (IsEmpty() == true)
		return false;//若栈空则返回false
	x = top->data;//栈不空则返回栈顶元素的值
	return true;
}

template<class T>
int LinkedStack<T>::getSize()const {
	LinkNode<T>* p = top;
	int k = 0;
	while (p != NULL) {
		p = top->rLink;
		k++;
	}
	return k;
}

#endif