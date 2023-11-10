#ifndef _SJM_PQueue_
#define _SJM_PQueue_
/*��С���ȶ���*/
#include<iostream>
template<class T>
class minPQueue {
private:
	DblList<T> list;
public:
	//���캯��
	minPQueue() {
		list.makeEmpty();
	};
	//��������
	~minPQueue() { list.makeEmpty(); };
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


#endif