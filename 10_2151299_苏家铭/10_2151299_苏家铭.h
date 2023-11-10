/*大根堆，根结点编号为0*/ 
#ifndef _SJM_MAXHEAP_
#define _SJM_MAXHEAP_ 

#define Default_size 20
int count_heapcmp = 0;
int count_heapexc = 0;
template <class T>
class maxHeap {
private:
	T* pheap;//存放大根堆中元素的数组
	int current_size;//大根堆中当前元素个数
	int maxHeap_size;//大根堆最多允许元素个数
	void down_sift(int start, int m);//自上向下调整
	void up_sift(int start);//自下向上调整
public:
	maxHeap(int size = Default_size);//构造函数：建立空堆
	maxHeap(T arr[], int size);//构造函数：通过一个数组建堆
	~maxHeap() {
		delete[]pheap;
	}
	T* get_pheap() {
		return this->pheap;
	}
	bool insert(const T& x);//将x插入到大根堆中
	bool remove_max(T& x);//删除大根堆上的最大元素
	bool empty()const {//判断堆是否为空
		return (current_size == 0) ? true : false;
	}
	bool full()const {
		return(current_size == maxHeap_size) ? true : false;
	}
	void make_empty() {//置空堆
		current_size = 0;
	}
	void rank_heap();//堆排序,升序

};

template<class T>
maxHeap<T>::maxHeap(int size) {//构造函数
	maxHeap_size = (Default_size < size) ? size : Default_size;
	pheap = new T[maxHeap_size];//创建存储空间
	if (pheap == NULL) {
		cerr << "大根堆存储分配失败！" << endl;
		return;
	}
	current_size = 0;
}

template<class T>
maxHeap<T>::maxHeap(T arr[], int size) {//构造函数
	this->current_size = size;//建立当前size
	maxHeap_size = (Default_size < size) ? size : Default_size;
	pheap = new T[maxHeap_size];
	if (pheap == NULL) {
		cerr << "大根堆存储分配失败！" << endl;
		return;
	}
	for (int i = 0; i < size; i++)
		pheap[i] = arr[i];
	int currentPos = (current_size - 2) / 2;//找到最初调整位置：末结点的父结点
	while (currentPos >= 0) {//自底向上
		down_sift(currentPos, current_size - 1);
		currentPos--;
	}
}

template<class T>
void maxHeap<T>::down_sift(int start, int m) {
	//从结点strat开始到m位置，自上向下比较
	int i = start, j = 2 * i + 1;//j是i的左子女
	T temp = pheap[i];
	while (j <= m) {
		count_heapcmp++;
		if (j < m && pheap[j] <pheap[j + 1])//让j指向两子女中的大者
			j++;
		count_heapcmp++;
		if (temp >= pheap[j])//temp大则不调整
			break;
		else {//大则上移。i、j下降
			pheap[i] = pheap[j];
			i = j;
			j = 2 * j + 1;
			count_heapexc++;
		}
	}//end of while
	pheap[i] = temp;
}

template<class T>
void maxHeap<T>::up_sift(int start) {
	//从结点start开始到结点0，自下而上比较
	int j = start, i = (j - 1) / 2;
	T temp = pheap[j];
	while (j > 0) {//沿父结点路径向上直达根节点
		if (pheap[i] >= temp)//父结点值大，不调整
			break;
		else {//父结点大，调整
			pheap[j] = pheap[i];
			j = i;
			i = (i - 1) / 2;
		}
	}
	pheap[j] = temp;
}

template<class T>
bool maxHeap<T>::insert(const T& x) {
	//将x插入到大根堆中
	if (current_size == maxHeap_size) {//堆满
		cerr << "Heap Full!" << endl;
		return false;
	}
	pheap[current_size] = x;//插入
	up_sift(current_size);//向上调整
	current_size++;//堆计数++
	return true;
}

template<class T>
bool maxHeap<T>::remove_max(T& x) {
	if (current_size == 0) {
		cout << "Heap Full!" << endl;
		return false;
	}//堆空，最后返回false
	x = pheap[0];
	pheap[0] = pheap[current_size - 1];//最后元素填补到根结点
	current_size--;
	down_sift(0, current_size - 1);//自上向下调整堆
	return true;//返回最大元素
}


template<class T>
void maxHeap<T>::rank_heap() {
	int i = 0,k=current_size-1;
	while (i < current_size-1) {		
		T temp = pheap[k];
        pheap[k] = pheap[0];
		pheap[0] = temp;//堆顶最大值和最后一个元素交换
		k--;
		down_sift(0, k);//调整
		i++;
	}
}



#endif


