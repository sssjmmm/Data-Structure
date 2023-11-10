#ifndef _SJM_STACK_
#define _SJM_STACK_
#include<iostream>
#include<assert.h>
using namespace std;
/*��ʽջ*/
/*top->an--an-1--an-2--......--a1->NULL*/
template<class T>
struct LinkNode {//��������
	T data;
	LinkNode* rLink;
	LinkNode(T d, LinkNode* L) :data(d), rLink(L) {};
};
template<class T>
class LinkedStack {
private:
	LinkNode<T>* top;
public:
	LinkedStack() :top(NULL) {}//���캯�����ÿ�ջ
	~LinkedStack() { makeEmpty(); };//��������
	void Push(const T& x);//Ԫ�ؽ�ջ
	bool Pop(T& x);//Ԫ����ջ
	bool getTop(T& x)const;//����ջ��Ԫ��
	bool IsEmpty()const { return(top == NULL) ? true : false; }
	int getSize()const;//����ջ��Ԫ�ظ���
	void makeEmpty();//���ջ
	friend ostream& operator << (ostream& os, LinkedStack<T>& s) {
		//���ջ��Ԫ�ص����ز���<<
		os << "ջ��Ԫ�ظ���=" << s.getSize() << endl;//���ջ��Ԫ�ظ���
		LinkNode<T>* p = s.top;
		int i = 0;//������ջ��Ԫ�ظ���
		while (p != NULL) {
			os << ++i << ":" << p->data << endl;
			p = p->rLink;
		}
		return os;

	};//���ջ��Ԫ�ص����ز���
};

template<class T>
void LinkedStack<T>::makeEmpty() {
	//���ɾȥ��ʽջ�е�Ԫ��ֱ��ջ��ָ��Ϊ��
	LinkNode<T>* p;
	while (top != NULL) {//�������ͷ�
		p = top;
		top = top->rLink;
		delete p;
	}
};

template<class T>
void LinkedStack<T>::Push(const T& x) {
	//��Ԫ��ֵx���뵽��ʽջ��ջ��������ͷ
	top = new LinkNode<T>(x, top);//�����µĺ�x���
	assert(top != NULL);//�����½��ʧ���˳�
}

template <class T>
bool LinkedStack<T>::Pop(T& x) {
	//ɾ��ջ����㣬���ر�ɾջ��Ԫ�ص�ֵ
	if (IsEmpty() == true)
		return false;//��ջ������ջ������
	LinkNode <T>* p = top;//�����ݴ�ջ��Ԫ��
	top = top->rLink;
	x = p->data;
	delete p;//�ͷŽ�㣬�����˳�Ԫ�ص�ֵ
	return true;
}

template<class T>
bool LinkedStack<T>::getTop(T& x)const {
	//����ջ��Ԫ�ص�ֵ
	if (IsEmpty() == true)
		return false;//��ջ���򷵻�false
	x = top->data;//ջ�����򷵻�ջ��Ԫ�ص�ֵ
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