#ifndef _SJM_MINPQueue_
#define _SJM_MINPQueue_
#include"sjm_shortHeap.h"
/*最小优先队列*/
#include<iostream>
template<class T>
class minPQueue {
private:
	minHeap<T> heap;
public:
	//构造函数
	minPQueue(int size = Default_size);
	minPQueue(T arr[], int size);
	//析构函数
	//~minPQueue() 
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
void minPQueue<T>::push(const T& val) {
	heap.insert(val);
}

template<class T>
void minPQueue<T>::pop() {
	T x;
	heap.remove_min(x);
}

template<class T>
void minPQueue<T>::makeEmpty() {
	heap.make_empty();
}

template<class T>
bool minPQueue<T>::empty()const {
	return heap.empty();
}

template<class T>
int minPQueue<T>::size()const {
	return heap.current_size;
}

template<class T>
const T& minPQueue<T>::front() {
	return heap.pheap[0];
}
template<class T>

minPQueue<T>::minPQueue(int size) {
	heap.minHeap_size = (Default_size < size) ? size : Default_size;
	heap.pheap = new T[heap.minHeap_size];//创建存储空间
	if (heap.pheap == NULL) {
		cerr << "小根堆存储分配失败！" << endl;
		return;
	}
	heap.current_size = 0;
};

template<class T>
minPQueue<T>::minPQueue(T arr[], int size) {
	heap.minHeap_size = (Default_size < size) ? size : Default_size;
	heap.pheap = new T[heap.minHeap_size];
	if (heap.pheap == NULL) {
		cerr << "小根堆存储分配失败！" << endl;
		return;
	}
	for (int i = 0; i < size; i++)
		heap.pheap[i] = arr[i];
	heap.current_size = size;//建立当前大小
	int currentPos = (heap.current_size - 2) / 2;//找到最初调整位置：末结点的父结点
	while (currentPos >= 0) {//自底向上
		heap.down_sift(currentPos, heap.current_size - 1);
		currentPos--;
	}
}
#endif
