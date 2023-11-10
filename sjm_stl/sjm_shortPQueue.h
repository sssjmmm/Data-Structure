#ifndef _SJM_MINPQueue_
#define _SJM_MINPQueue_
#include"sjm_shortHeap.h"
/*��С���ȶ���*/
#include<iostream>
template<class T>
class minPQueue {
private:
	minHeap<T> heap;
public:
	//���캯��
	minPQueue(int size = Default_size);
	minPQueue(T arr[], int size);
	//��������
	//~minPQueue() 
	//���
	void push(const T& val);
	//����
	void pop();
	//�ÿ�
	void makeEmpty();
	//�жϿշ�
	bool empty()const;
	//���ض��д�С
	int size()const;
	//���ض���Ԫ��
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
	heap.pheap = new T[heap.minHeap_size];//�����洢�ռ�
	if (heap.pheap == NULL) {
		cerr << "С���Ѵ洢����ʧ�ܣ�" << endl;
		return;
	}
	heap.current_size = 0;
};

template<class T>
minPQueue<T>::minPQueue(T arr[], int size) {
	heap.minHeap_size = (Default_size < size) ? size : Default_size;
	heap.pheap = new T[heap.minHeap_size];
	if (heap.pheap == NULL) {
		cerr << "С���Ѵ洢����ʧ�ܣ�" << endl;
		return;
	}
	for (int i = 0; i < size; i++)
		heap.pheap[i] = arr[i];
	heap.current_size = size;//������ǰ��С
	int currentPos = (heap.current_size - 2) / 2;//�ҵ��������λ�ã�ĩ���ĸ����
	while (currentPos >= 0) {//�Ե�����
		heap.down_sift(currentPos, heap.current_size - 1);
		currentPos--;
	}
}
#endif
