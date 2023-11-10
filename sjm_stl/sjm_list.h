#ifndef _SJM_LIST_
#define _SJM_LIST_

/*������ͷ����˫��ѭ��������ඨ��*/

template<class T>
struct DblNode {//����ڵ���
	T data;//����������
	DblNode<T>* lLink, * rLink;//��ָ����,ǰ��������������̣�������
	DblNode(DblNode<T>* left = NULL, DblNode<T>* right = NULL) {
		lLink = left;
		rLink = right;
	}//����ʼ��ָ���Ա�Ĺ��캯��
	DblNode(const T& item, DblNode<T>* left = NULL, DblNode<T>* right = NULL) {
		data = item;
		lLink = left;
		rLink = right;
	}//��ʼ��ģ��������ָ���Ա�Ĺ��캯��
	DblNode(const T& item, DblNode<T>* right ) {
		data = item;
		rLink = right;
	}//��ʼ��ģ����������ָ���Ա�Ĺ��캯��
};

template<class T>
class DblList {
protected:
	DblNode<T>* first;
public:
	DblList() {
		first = new DblNode<T>;
		if (first == NULL) {
			cerr << "�洢�������" << endl;
			return;
		}
		first->rLink = first->lLink = first;
	}//���캯��
	DblList(T uniqueVal) {
		first = new DblNode<T>(uniqueVal);
		if (first == NULL) {
			cerr << "�洢�������" << endl;
			return;
		}
		first->rLink = first->lLink = first;
	}//���캯��:����˫��ѭ������ĸ���ͷ��㣬��������һ������ĳЩ�ض������ֵ
	DblList(const DblList<T>& L);//���ƹ��캯��
	~DblList() {
		makeEmpty();
		delete first;
	}//��������

	void makeEmpty();//��������Ϊ�ձ�
	int Length()const;//����˫����ĳ���
	DblNode<T>* getHead()const {
		return first;
	}//���ظ���ͷ����ַ
	void setHead(DblNode<T>* ptr) {
		first = ptr;
	}//���ø���ͷ����ַ
	DblNode<T>* Search(const T& x);//���������غ��Ѱ�ҵ�������x��Ԫ��
	DblNode<T>* Locate(int i, int d);//�������ж�λ���Ϊi��>=0���Ľ�㣬d=0��ǰ������d!=0����̷���
	bool getDate(int i, T& x, int d);//ȡ����d�����i��Ԫ�صĵ�ַ
	void setData(int i, T& x, int d);//��x�޸İ�d�����i��Ԫ�ص�ֵ
	bool Inset(int i, const T& x, int d);//�ڵ�i��Ԫ�غ����x,d=0��ǰ������d!=0����̷���
	bool Remove(int i, T& x, int d);//ɾ����i��Ԫ��,x���ظ�Ԫ�ص�ֵ,d=0��ǰ������d!=0����̷���
	bool IsEmpty()const {
		return first->rLink == first ? true : false;
	}//�б�շ�?���򷵻�true
	bool IsFull()const { return false; }//�б����񣿲����򷵻�false
	void push_back(T data);//��β������һ������
	void push_front(T data);//��ǰ������һ������

	//void Sort() {};//����  ��ʵ��
	void input_num(int i);//����i��Ԫ��
	void input_endTag(T endTag);//��������Ԫ�أ�ֱ������endTag
	void output(int d);//���
	DblList<T>& operator= (const DblList<T>& L);//���غ�������ֵ

	template<class E>
	friend class Queue;
};

//DblList��ĳ�Ա������ʵ��
template<class T>
DblList<T>::DblList(const DblList<T>& L) {
	//���ƹ��캯��
	T value;
	DblNode<T>* srcptr = L.getHead();//�����Ʊ�ĸ���ͷ����ַ
	DblNode<T>* destptr = first = new DblNode<T>;
	while (srcptr->rLink != L.first) {//����ڵ㸴��
		value = srcptr->rLink->data;
		destptr->rLink = new DblNode<T>(value);
		destptr->rLink->lLink = destptr;
		destptr = destptr->rLink;
		srcptr = srcptr->rLink;
	}
	destptr->rLink = first;
	destptr->rLink->lLink = destptr;
};

template <class T>
void DblList <T>::makeEmpty() {
	//��������Ϊ�ձ�
	DblNode<T>* q;
	while (first->rLink != first) {//��������ʱ��ɾȥ�������нڵ�
		q = first->rLink;
		first->rLink = q->rLink;//���汻ɾ��㣬������ժ�¸ý��
		delete q;//ɾ����������һ����ͷ��㣩
	}
};

template <class T>
int DblList<T>::Length()const {
	//���������ͷ���ĵ�������
	DblNode<T>* p = first->rLink;
	int count = 0;
	while (p != first) {//ѭ��ɨ�裬Ѱ����β
		p = p->rLink;
		count++;
	}
	return count;
};

template <class T>
DblNode<T>* DblList<T>::Search(const T& x) {
	//�ڱ�������������x�Ľ�㣬�����ɹ�ʱ�������ظý���ַ�����򷵻�NULLֵ
	DblNode<T>* current = first->rLink;
	while (current != first && current->data != x) {//ѭ���Һ�x�Ľ��
		current = current->rLink;
	}
	if (current != first)//�����ɹ�
		return current;
	else//����ʧ��
		return NULL;
};

template<class T>
DblNode<T>* DblList<T>::Locate(int i, int d) {
	//��λ���������ر��е�i��Ԫ�صĵ�ַ����i<0��i�������н��������򷵻�NULL��
	//�ڴ�����ͷ����˫��ѭ���б��а�d��ָ����Ѱ�ҵ�i�����ĵ�ַ����d=0����ǰ������
	//Ѱ�ҵ�i����㣬��d!=0���ں�̷���Ѱ�ҵ�i����㡣
	if (i < 0)
		return NULL;
	DblNode <T>* current;
	if (d == 0)
		current = first->lLink;
	else
		current = first->rLink;

	for (int j = 1; j < i; j++) {//��������
		if (current == first)//��̫���˳�����
			break;
		else if (d == 0)
			current = current->lLink;
		else
			current = current->rLink;
	}
	if (current != first)
		return current;//�����ɹ�
	else
		return NULL;//����ʧ��

};

template <class T>
bool DblList <T>::getDate(int i, T& x, int d) {
	//ȡ�����а�d��ָʾ����ĵ�i��Ԫ�ص�ֵ
	if (i < 0)//i̫С
		return NULL;
	DblNode<T>* current = Locate(i, d);
	if (current == NULL)//i̫��
		return false;
	else {
		x = current->data;
		return true;
	}
};

template<class T>
void DblList <T>::setData(int i, T& x, int d) {
	//�������е�i��Ԫ�ظ�ֵx��
	if (i <= 0)
		return;
	DblNode<T>* current = Locate(i, d);
	if (current == NULL)//i̫��
		return;
	else {
		current->data = x;
	}
};

template <class T>
bool DblList<T>::Inset(int i, const T& x, int d) {
	//����Ԫ��x��dָ���ķ�������������е�i�����֮��
	DblNode<T>* current = Locate(i, d);//���ҵ�i�����
	if (current == NULL)
		return false;//���벻�ɹ�
	DblNode<T>* newNode = new DblNode<T>(x);
	if (newNode == NULL) {
		cerr << "�洢�������" << endl;
		return false;
	}
	if (d == 0) {//ǰ���������
		newNode->lLink = current->lLink;//������current֮��
		current->lLink = newNode;
		newNode->lLink->rLink = newNode;
		newNode->rLink = current;
	}
	else {//��̷������
		newNode->rLink = current->rLink;//������current֮��
		current->rLink = newNode;
		newNode->rLink->lLink = newNode;
		newNode->lLink = current;
	}
	return true;//����ɹ�
};

template <class T>
bool DblList <T>::Remove(int i, T& x, int d) {
	//�������еĵ�i��Ԫ�ذ���d��ָ����ɾȥ��ͨ�������Ͳ���x���ظ�Ԫ�ص�ֵ��
	DblNode<T>* current = Locate(i, d);
	if (current == NULL)
		return false;//ɾ�����ɹ�
	current->rLink->lLink = current->lLink;//��lLink����ժ��
	current->lLink->rLink = current->rLink;//��lLink����ժ��
	x = current->data;//ȡ����ɾ����е�����ֵ
	delete current;
	return true;//ɾ���ɹ�
};

template <class T>
void DblList<T>::output(int d) {
	//˫ѭ�������������������������������ݰ�d��ָ�����������Ļ�ϡ�d=0,��ǰ����d!=0�����
	DblNode<T>* current;
	if (d == 0)
		current = first->lLink;
	else
		current = first->rLink;
	while (current != first) {
		cout << current->data << " ";
		if (d == 0)
			current = current->lLink;
		else
			current = current->rLink;
	}
};

template <class T>
DblList<T>& DblList<T>::operator= (const DblList<T>& L) {
	//���غ�������ֵ����������A=B������A�ǵ��ô˲�����DblList����B����������е������Ͳ���L��ϵ�ʵ��
	T value;
	DblNode<T>* srcptr = L.getHead();//�����Ʊ�ĸ���ͷ����ַ
	DblNode<T>* destptr = first = new DblNode<T>;
	while (srcptr->rLink != L.first) {//����ڵ㸴��
		value = srcptr->rLink->data;
		destptr->rLink = new DblNode<T>(value);
		destptr->rLink->lLink = destptr;
		destptr = destptr->rLink;
		srcptr = srcptr->rLink;
	}
	destptr->rLink = first;
	destptr->rLink->lLink = destptr;
	return*this;//���ز��������ַ

}

template<class T>
void DblList<T>::input_num(int i) {//��巨��һ����������i��Ԫ��
	DblNode<T>* newNode, * last;
	int end = 1;
	T val;
	if (i < 1)
		return;
	makeEmpty();
	last = first;
	while (end++ <= i) {
		cin >> val;
		newNode = new DblNode<T>(val);
		if (newNode == NULL) {
			cerr << "�洢�������" << endl;
			return;
		}
		last->rLink = newNode;
		last->rLink->lLink = last;
		last = newNode;
	}
	last->rLink = first;//����β����2��ʵ�ʿ�ʡ��
	last->rLink->lLink = last;
}

template<class T>
void DblList<T>::input_endTag(T endTag) {//��巨��һ����������Ԫ�أ�ֱ������endTag
	//endTag��Լ�����������н����ı�־�����������������������endTag������0���߸�����
	//��������������ַ���endTag�������ַ����в�����ֵ��ַ�����"\0"
	DblNode<T>* newNode, * last;
	T val = 0;
	makeEmpty();
	last = first;
	while (1) {
		cin >> val;
		if (cin.fail()) {
			cout << "���������Ӵ��������ַ���ʼ��������" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else {
			if (val == endTag)
				break;
			newNode = new DblNode<T>(val);
			if (newNode == NULL) {
				cerr << "�洢�������" << endl;
				return;
			}
			last->rLink = newNode;
			last->rLink->lLink = last;
			last = newNode;
		}
	}
	last->rLink = first;//����β����2��ʵ�ʿ�ʡ��
	last->rLink->lLink = last;
};
template <class T>
void DblList<T>::push_back(T data)//������ĩβ����һ��Ԫ��
{
	DblNode<T>* newNode, * last;
	newNode = new DblNode<T>(data, NULL, NULL);
	if (newNode == NULL) {
		cerr << "�洢�������" << endl;
		return;
	}
	last = first->lLink;
	last->rLink = newNode;
	last->rLink->lLink = last;
	last = newNode;
	last->rLink = first;
	first->lLink = last;
};
template <class T>
void DblList<T>::push_front(T data)//������ǰ�˲���һ��Ԫ��
{
	DblNode<T>* newNode;
	newNode = new DblNode<T>(data);
	if (newNode == NULL) {
		cerr << "�洢�������" << endl;
		return;
	}

	newNode->rLink = first->rLink;
	first->rLink->lLink = newNode;
	first->rLink = newNode;
	newNode->lLink = first;
}
#endif
