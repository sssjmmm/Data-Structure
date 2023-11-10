#ifndef _07_
#define _07_
 

#include<iostream>


#define Default_size 20
template <class T>
class minHeap {
private:
	T* pheap;//存放小根堆中元素的数组
	int current_size;//小根堆中当前元素个数
	int minHeap_size;//小根堆最多允许元素个数
	void down_sift(int start, int m);//自上向下调整
	void up_sift(int start);//自下向上调整
public:
	minHeap(int size = Default_size);//构造函数：建立空堆
	minHeap(T arr[], int size);//构造函数：通过一个数组建堆
	~minHeap() {
		delete[]pheap;
	}
	bool insert(const T& x);//将x插入到小根堆中
	bool remove_min(T& x);//删除小根堆上的最小元素
	bool empty()const {//判断堆是否为空
		return (current_size == 0) ? true : false;
	}
	bool full()const {
		return(current_size == minHeap_size) ? true : false;
	}
	void make_empty() {//置空堆
		current_size = 0;
	}
	void rank_heap(T rank[]);//堆排序

	//有元类
	template <class E>
	friend class minPQueue;
};

template<class T>
minHeap<T>::minHeap(int size) {//构造函数
	minHeap_size = (Default_size < size) ? size : Default_size;
	pheap = new T[minHeap_size];//创建存储空间
	if (pheap == NULL) {
		cerr << "小根堆存储分配失败！" << endl;
		return;
	}
	current_size = 0;
}

template<class T>
minHeap<T>::minHeap(T arr[], int size) {//构造函数
	minHeap_size = (Default_size < size) ? size : Default_size;
	pheap = new T[minHeap_size];
	if (pheap == NULL) {
		cerr << "小根堆存储分配失败！" << endl;
		return;
	}
	for (int i = 0; i < size; i++)
		pheap[i] = arr[i];
	current_size = size;//建立当前大小
	int currentPos = (current_size - 2) / 2;//找到最初调整位置：末结点的父结点
	while (currentPos >= 0) {//自底向上
		down_sift(currentPos, current_size - 1);
		currentPos--;
	}
}

template<class T>
void minHeap<T>::down_sift(int start, int m) {
	//从结点strat开始到m位置，自上向下比较
	int i = start, j = 2 * i + 1;//j是i的左子女
	T temp = pheap[i];
	while (j <= m) {
		if (j < m && pheap[j] >pheap[j + 1])//让j指向两子女中的小者
			j++;
		if (temp <= pheap[j])//temp小则不调整
			break;
		else {//小则上移。i、j下降
			pheap[i] = pheap[j];
			i = j;
			j = 2 * j + 1;
		}
	}//end of while
	pheap[i] = temp;
}

template<class T>
void minHeap<T>::up_sift(int start) {
	//从结点start开始到结点0，自下而上比较
	int j = start, i = (j - 1) / 2;
	T temp = pheap[j];
	while (j > 0) {//沿父结点路径向上直达根节点
		if (pheap[i] <= temp)//父结点值小，不调整
			break;
		else {//父结点小，调整
			pheap[j] = pheap[i];
			j = i;
			i = (i - 1) / 2;
		}
	}
	pheap[j] = temp;
}

template<class T>
bool minHeap<T>::insert(const T& x) {
	//将x插入到小根堆中
	if (current_size == minHeap_size) {//堆满
		cerr << "Heap Full!" << endl;
		return false;
	}
	pheap[current_size] = x;//插入
	up_sift(current_size);//向上调整
	current_size++;//堆计数++
	return true;
}

template<class T>
bool minHeap<T>::remove_min(T& x) {
	if (current_size == 0) {
		cout << "Heap Full!" << endl;
		return false;
	}//堆空，最后返回false
	x = pheap[0];
	pheap[0] = pheap[current_size - 1];//最后元素填补到根结点
	current_size--;
	down_sift(0, current_size - 1);//自上向下调整堆
	return true;//返回最小元素
}

template<class T>
void minHeap<T>::rank_heap(T rank[]) {
	//因为堆排序要删除结点，所以再用一个堆复制原本的堆
	minHeap<T> temp_heap(pheap, current_size);
	T x;
	//cout <<"pt:"<< pt[0] << " " << pt[1] << " " << pt[2] << endl;
	int i = 0;
	while (i < current_size) {//current个元素

		rank[i] = temp_heap.pheap[0];//根结点总是最小值
		//删掉根结点
		x = temp_heap.pheap[0];
		temp_heap.pheap[0] = temp_heap.pheap[temp_heap.current_size - 1];//最后元素填补到根结点
		temp_heap.current_size--;
		//调整
		int start = 0, j = 2 * start + 1, m = temp_heap.current_size - 1;//j是i的左子女
		T temp = temp_heap.pheap[start];
		while (j <= m) {
			if (j < m && temp_heap.pheap[j] > temp_heap.pheap[j + 1])//让j指向两子女中的小者
				j++;
			if (temp <= temp_heap.pheap[j])//temp小则不调整
				break;
			else {//小则上移。i、j下降
				temp_heap.pheap[start] = temp_heap.pheap[j];
				start = j;
				j = 2 * j + 1;
			}
		}//end of while
		temp_heap.pheap[start] = temp;

		i++;
	}
}

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
