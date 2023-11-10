#ifndef _SJM_QUEUE_
#define _SJM_QUEUE_

#include"sjm_list.h"
template<class T>
class Queue {
private:
	DblList<T> list;
public:
	//���캯��
	Queue() {
		list.makeEmpty();
	};
	//��������
	~Queue() { list.makeEmpty(); };
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
