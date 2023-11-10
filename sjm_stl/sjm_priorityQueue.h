#ifndef _SJM_PQueue_
#define _SJM_PQueue_
/*最小优先队列*/
#include<iostream>
template<class T>
class minPQueue {
private:
	DblList<T> list;
public:
	//构造函数
	minPQueue() {
		list.makeEmpty();
	};
	//析构函数
	~minPQueue() { list.makeEmpty(); };
	//入队
	void push(const T& val);
	//出队
	void pop();
	//置空
	void makeEmpty();
	//判断空否
	bool empty()const;
	//返回队列大小
	int size()const;
	//返回队首元素
	const T& front();
};


#endif