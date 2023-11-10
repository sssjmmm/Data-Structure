#ifndef _SJM_AVL_
#define _SJM_AVL_

#include"sjm_stack.h"
#include"exam_re_sys.h"
template<class E, class K>//E�ǽ�㣬K�ǽ��Ĺؼ���
struct AVLNode {
	E data;//�������
	AVLNode<E, K>* left, * right;//����ָ��
	int bf;//ƽ������balance factor
	AVLNode() :left(NULL), right(NULL), bf(0) {};
	AVLNode(E d, AVLNode<E, K>* l = NULL, AVLNode<E, K>* r = NULL) :data(d), left(l), right(r), bf(0) {};
	~AVLNode() {};//��������
	void setData(E d) {
		data = d;
	}
	E getData() {
		return data;
	}
};
template<class E, class K>
class AVLTree {
protected:
	AVLNode<E, K>* root;//��ָ��
	int tree_num;//������
	bool Insert(AVLNode<E, K>*& ptr, E& el);//���룬�ڲ�����
	bool Remove(AVLNode<E, K>*& ptr, K x);//ɾ�����ڲ�����
	void RotateL(AVLNode<E, K>*& ptr);//����
	void RotateR(AVLNode<E, K>*& ptr);//�ҵ���
	void RotateLR(AVLNode<E, K>*& ptr);//���������ҵ���
	void RotateRL(AVLNode<E, K>*& ptr);//���ҵ�����������
public:
	AVLTree() :root(NULL), tree_num(0) {}//���캯���������AVL��
	AVLNode<E, K>* Search1(K x, AVLNode<E, K>*& ptr);//�������ⲿ�ӿ�
	AVLNode<E, K>* find(K x) {//���ң�����ָ�����ָ�룬�ⲿ�ӿ�
		return Search1(x, root);
	}
	bool Insert(E& el) {//���룬�ⲿ�ӿ�
		return Insert(root, el);
	}
	bool Remove(K x) {//ɾ�����ⲿ�ӿ�
		return Remove(root, x);
	}
	AVLNode<E, K>* get_root() {//���ظ����
		return root;
	}
	int get_Tnum() {//�������Ľ����������ͳ��
		return tree_num;
	}
	void input(int i);//����i��Ԫ��
	void ouput();//���
	int count() {//��������ƽ�������ͳ�Ƶķ���2
		int count = 0;
		Traverse(root, count);
		return count;
	}
	friend ostream& operator<<(ostream& out, const AVLTree<E, K>& Tree) {
		Tree.Traverse(Tree.root, out);//����������������������
		out << endl;
		return out;//�������Ԫ��

	}
	void Traverse(const AVLNode<E, K>* ptr, ostream& out)const;//����������
	void Traverse(const AVLNode<E, K>* ptr, int& count)const;//�����������
};

template<class E, class K>
AVLNode<E, K>* AVLTree<E, K>::Search1(K x, AVLNode<E, K>*& ptr) {
	//������x�Ľ�㣬�ɹ����ظýڵ�ĵ�ַ��ʧ�ܷ���NULL
	if (ptr == NULL)
		return NULL;
	else if (x < ptr->data)
		return Search1(x, ptr->left);//���������м�������
	else if (x > ptr->data)
		return Search1(x, ptr->right);//���������м�������
	else
		return ptr;//�����ɹ�
}

template<class E, class K>
void AVLTree<E, K>::RotateL(AVLNode<E, K>*& ptr) {
	//���������������ߣ�����ptrΪ����AVL��������ת����ת���¸���ptr
	AVLNode<E, K>* subL = ptr;//Ҫ����ת�Ľ��
	ptr = subL->right;//ԭ��������Ů
	subL->right = ptr->left;//ptr��Ϊ�¸�ǰж����߸���
	ptr->left = subL;//����ת��ptrΪ�¸�
	ptr->bf = subL->bf = 0;
}

template<class E, class K>
void AVLTree<E, K>::RotateR(AVLNode<E, K>*& ptr) {
	//���������������ߣ�����ptrΪ����AVL�����ҵ���ת����ת���¸���ptr
	AVLNode<E, K>* subR = ptr;//Ҫ����ת�Ľ��
	ptr = subR->left;//ԭ��������Ů
	subR->left = ptr->right;//ptr��Ϊ�¸�ǰж���ұ߸���
	ptr->right = subR;//�ҵ���ת��ptrΪ�¸�
	ptr->bf = subR->bf = 0;
}

template<class E, class K>
void AVLTree<E, K>::RotateLR(AVLNode<E, K>*& ptr) {
	AVLNode<E, K>* subR = ptr, * subL = subR->left;
	ptr = subL->right;
	subL->right = ptr->left;//ptr��Ϊ�¸�ǰ˦������ߵĸ���
	ptr->left = subL;//����ת��ptr��Ϊ�¸�
	if (ptr->bf <= 0)
		subL->bf = 0;//������µ��ptr���������
	else
		subL->bf = -1;
	subR->left = ptr->right;//ptr��Ϊ�¸�ǰ˦�����ұ�
	ptr->right = subR;//�ҵ���ת��ptr��Ϊ�¸�
	if (ptr->bf == -1)
		subR->bf = 1;
	else
		subR->bf = 0;
	ptr->bf = 0;
}

template<class E, class K>
void AVLTree<E, K>::RotateRL(AVLNode<E, K>*& ptr) {
	AVLNode<E, K>* subL = ptr, * subR = subL->right;
	ptr = subR->left;
	subR->left = ptr->right;//ptr��Ϊ�¸�ǰ˦�����ұߵĸ���
	ptr->right = subR;//�ҵ���ת��ptr��Ϊ�¸�
	if (ptr->bf >= 0)
		subR->bf = 0;
	else
		subR->bf = 1;
	subL->right = ptr->left;//ptr��Ϊ�¸�ǰ˦������ߵĸ���
	ptr->left = subL;//����ת��ptr��Ϊ�¸�
	if (ptr->bf == 1)
		subL->bf = -1;
	else
		subL->bf = 0;
	ptr->bf = 0;
}

template<class E, class K>
bool AVLTree<E, K>::Insert(AVLNode<E, K>*& ptr, E& el) {
	//����ptrΪ����AVL���в�����Ԫ��el���������ɹ�����������true�����򷵻�false��
	AVLNode<E, K>* pr = NULL, * p = ptr, * q;
	int d;
	LinkedStack<AVLNode<E, K>*>st;
	while (p != NULL) {//Ѱ�Ҳ���λ��
		if (el == p->data)//�ҵ�����el�Ľ�㣬������
			return false;
		pr = p;
		st.Push(pr);//������ջ�������·��
		if (el < p->data)
			p = p->left;
		else
			p = p->right;
	}
	p = new AVLNode<E, K>(el);//�����½�㣬data=el��bf=0
	if (p == NULL) {
		cerr << "�洢�ռ䲻�㣡" << endl;
		return false;
	}
	if (pr == NULL) {//�������½���Ϊ�����
		ptr = p;
		tree_num++;
		return true;
	}
	if (el < pr->data)
		pr->left = p;
	else
		pr->right = p;
	while (st.IsEmpty() == false) {//����ƽ�⻯
		st.Pop(pr);//��ջ���˳������
		if (p == pr->left)//����������ƽ������
			pr->bf--;
		else
			pr->bf++;
		if (pr->bf == 0)//���ƽ������=0��ƽ���˳�
			break;
		if (pr->bf == 1 || pr->bf == -1)//���ƽ�����Ӿ���ֵ=1
			p = pr;
		else {//���ƽ�����Ӿ���ֵ=2
			d = (pr->bf < 0) ? -1 : 1;//����˫����־
			if (p->bf == d) {//�����ƽ������ͬ�ţ�����ת
				if (d == -1)//�ҵ���ת
					RotateR(pr);
				else//����ת
					RotateL(pr);
			}
			else {//�����ƽ�����ӷ��ţ�˫��ת
				if (d == -1)//�������˫��ת����<����
					RotateLR(pr);
				else//���Һ���˫��ת����>����
					RotateRL(pr);
			}
			break;//�������ϵ���
		}//end of |bf|==2
	}//end of while(st.IsIsEmpty()==false)
	if (st.IsEmpty() == true)
		ptr = pr;//���������ĸ����
	else {//�м���������
		st.getTop(q);
		if (q->data > pr->data)
			q->left = pr;
		else
			q->right = pr;
	}
	tree_num++;
	return true;
}

template<class E, class K>
void AVLTree<E, K>::input(int i) {
	int count = 1;
	E item;
	while (count <= i) {
		cin >> item;
		Insert(item);
		count++;
	}
}

template<class E, class K>
void AVLTree<E, K>::ouput() {
	cout << "�и�����AVL��" << endl;
	Traverse(root);//����������������������
	cout << endl;
}

template<class E, class K>
void AVLTree<E, K>::Traverse(const AVLNode<E, K>* ptr, ostream& out)const {
	if (ptr != NULL) {//���ǿ�
		Traverse(ptr->left, out);//�������������
		out << ptr->data << endl;//�����������
		Traverse(ptr->right, out);//�������������
	}
}

template<class E, class K>
void AVLTree<E, K>::Traverse(const AVLNode<E, K>* ptr, int& count)const {
	if (ptr != NULL) {//���ǿ�
		Traverse(ptr->left, count);//�������������
		count++;
		Traverse(ptr->right, count);//�������������
	}
}
template<class E, class K>
bool AVLTree<E, K>::Remove(AVLNode<E, K>*& cur, K val) {
	LinkedStack<AVLNode<E, K>*> stk;
	//p:Ҫɾ���Ľ�㣬son:Ҫɾ�������ӽ��
	AVLNode<E, K>* parent = NULL, * p = cur, * pparent = NULL, * son;
	int d = 0, dd = 0;
	while (p)//Ѱ��ɾ��λ��
	{
		if (val == p->data.num)//�ҵ���Ҫɾ���Ľ��
			break;
		parent = p;
		stk.Push(parent);//��¼�߹���·��
		if (val < p->data.num)
			p = p->left;
		else
			p = p->right;
	}
	//�Ҳ���Ҫɾ���Ľ��
	if (p == NULL)
		return false;
	if (p->left && p->right)//��ɾ������������ӽ�㣬�任Ϊ�����
	{
		parent = p;
		stk.Push(parent);
		//��������ֱ��ǰ���������һ���������ߵ����ұ�
		son = p->left;
		while (son->right)
		{
			parent = son;
			stk.Push(parent);
			son = son->right;
		}
		p->data = son->data;//ֱ��ǰ����ֵ����Ҫɾ���Ľ��
		p = son;//ת��ΪҪɾȥֱ��ǰ��
	}
	//����֮��������������һ���ӽ�㣬��¼Ϊson
	if (p->left)
		son = p->left;
	else
		son = p->right;
	//Ϊ����㣬ֱ������Ҫɾ�������ӽ��son
	if (parent == NULL)
		cur = son;
	else//���Ǹ����
	{
		//����Ҫɾ�������ӽ��son
		if (parent->left == p)
			parent->left = son;
		else
			parent->right = son;

		//��ʼ���ݣ�����ƽ�⻯
		while (!stk.IsEmpty())
		{

			stk.Pop(parent);
			//����parent��bf
			if (parent->left == son)//ɾ����ԭ����parent��ߵĽ��
				parent->bf++;
			else
				parent->bf--;

			//�õ�ү���
			if (!stk.IsEmpty())
			{
				stk.Pop(pparent);
				dd = (pparent->left == parent) ? -1 : 1;
			}
			else//û��ү���
				dd = 0;
			//���parentƽ�����Ӿ���ֵΪ1�����õ�����ֱ���˳�
			if (parent->bf == 1 || parent->bf == -1)
				break;
			if (parent->bf)//bf����ֵΪ2
			{
				if (parent->bf < 0)
				{
					d = -1;
					son = parent->left;
				}
				else
				{
					d = 1;
					son = parent->right;
				}

				if (son->bf == 0)
				{
					if (d == -1)
					{
						RotateR(parent);
						parent->bf = 1;
						parent->left->bf = -1;
					}
					else
					{
						RotateL(parent);
						parent->bf = -1;
						parent->right->bf = 1;
					}
					break;
				}
				if (son->bf == d)
				{
					if (d == -1)
						RotateR(parent);
					else
						RotateL(parent);
				}
				else
				{
					if (d == -1)
						RotateLR(parent);
					else
						RotateRL(parent);
				}

				if (dd == -1)
					pparent->left = parent;
				else if (dd == 1)
					pparent->right = parent;
			}
			son = parent;
		}
		if (stk.IsEmpty())
			cur = parent;
	}//end if else

	tree_num--;
	return true;
}
#endif
