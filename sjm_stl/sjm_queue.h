#ifndef _SJM_QUEUE_
#define _SJM_QUEUE_

#include"sjm_list.h"
template<class T>
class Queue {
private:
	DblList<T> list;
public:
	//构造函数
	Queue() {
		list.makeEmpty();
	};
	//析构函数
	~Queue() { list.makeEmpty(); };
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
template<class T>
void Queue<T>::push(const T& val) {
	this->list.push_back(val);
};
template<class T>
void Queue<T>::pop() {
	T temp;
	this->list.Remove(1, temp, 1);

};
template<class T>
void Queue<T>::makeEmpty() {
	this->list.makeEmpty();
};
template<class T>
bool Queue<T>::empty()const {
	return this->list.IsEmpty();
};
template<class T>
int Queue<T>::size()const {
	return this->list.size();
};
template<class T>
const T& Queue<T>::front() {
	return list.first->rLink->data;
}
#endif
