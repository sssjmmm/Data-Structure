#include<iostream> 
#include <stdlib.h>
#include <cstring>
#include <chrono>
using namespace std;
#include"10_2151299_苏家铭.h"
void swap(int array[], int i, int j);
void out(int array[], int num);
void to_end();
void msd_radixsort(int array[], int left, int right, int d,int num);
void bubble_sort(int array[], int num);
void bubble_sort_plus(int array[], int num);
void selection_sort(int array[], int num);
void selection_sort_plus(int array[], int num);
void insert_sort(int array[], int num);
void shell_sort(int array[], int num);
void quick_sort(int array[], int num);
void heap_sort(int array[], int num);
void merge_sort(int array[], int num);
void MSDradix_sort(int array[], int num);
void LSDradix_sort(int array[], int num);

long long merge_count = 0;
long long count_cmp=0,count_exc=0;
int main() {
	cout << "**          排序算法比较                   **" << endl;
	cout << "=============================================" << endl;
	cout << "**          1 --- 冒泡排序                 **" << endl;
	cout << "**          2 --- 冒泡排序(优化版)         **" << endl;
	cout << "**          3 --- 选择排序                 **" << endl;
	cout << "**          4 --- 选择排序(优化版)         **" << endl;
	cout << "**          5 --- 直接插入排序             **" << endl;
	cout << "**          6 --- 希尔排序                 **" << endl;
	cout << "**          7 --- 快速排序                 **" << endl;
	cout << "**          8 --- 堆排序                   **" << endl;
	cout << "**          9 --- 归并排序                 **" << endl;
	cout << "**         10 --- MSD基数排序              **" << endl;
	cout << "**         11 --- LSD基数排序              **" << endl;
	cout << "**         12 --- 退出程序                 **" << endl;
	cout << "=============================================" << endl;
	int num,choice;
	int *rank,*rank2;
	cout << "请输入要产生的随机数个数：" ;
	while (1) {
		cin >> num;
		if (cin.fail()) {
			cout << "输入有误，请再次输入要产生的随机数个数：";
			cin.ignore(65535, '\n');
			cin.clear();
		}
		else
			break;
	}
	rank = new int[num];
	rank2 = new int[num];
	srand((unsigned)time(NULL));
	for (int i = 0; i < num; i++) 
		rank[i] = rand() % num + 1;//1-num,num个数字
	
	//out(rank, num);//输出rank
	bool loop = true;
	while (loop) {//从小到大
		cout << "请选择排序算法：";
		while (1) {
			cin >> choice;
			if (cin.fail() || choice < 0 || choice>12) {
				cout << "输入有误，请再次选择排序算法：";
				cin.ignore(65535, '\n');
				cin.clear();
			}
			else
				break;
		}
		//复制rank到rank2进行排序
		for (int i = 0; i < num; i++) 
			rank2[i] = rank[i];
		switch (choice) {
		case 1:
			bubble_sort(rank2, num);
			break;
		case 2:
			bubble_sort_plus(rank2, num);
			break;
		case 3:
			selection_sort(rank2, num);
			break;
		case 4:
			selection_sort_plus(rank2, num);
			break;
		case 5:
			insert_sort(rank2, num);
			break;
		case 6:
			shell_sort(rank2, num);
			break;
		case 7:
			quick_sort(rank2, num);
			break;
		case 8:
			heap_sort(rank2, num);
			break;
		case 9:
			merge_sort(rank2, num);
			break;
		case 10:
			MSDradix_sort(rank2, num);
			break;
		case 11:
			LSDradix_sort(rank2, num);
			break;
		case 12:
			to_end();
			loop = false;
			break;
		}//end of switch

	}//end of while
	delete[]rank;
	delete[]rank2;
	return 0;
}

void out(int array[], int num) {
	for (int i = 0; i < num; i++) {
		cout << array[i] << " ";
	}
	cout << endl;
}
void swap(int array[], int i, int j) {//交换两个元素在数组中的位置
	int temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}
void mergearray(int a[], int first, int mid, int last){	//将两个有序数组合并排序 
	int *temp=new int[last - first + 1];
	
	int i = first, j = mid + 1;
	int m = mid, n = last;
	int k = 0;
	count_cmp++;
	while (i <= m && j <= n){
		count_cmp++;
		if (a[i] < a[j])
			temp[k++] = a[i++];
		else
			temp[k++] = a[j++];
	}
	while (i <= m) {
		temp[k++] = a[i++];

	}
	while (j <= n) {
		temp[k++] = a[j++];
	}


	for (i = 0; i < last - first + 1; i++) {
		a[first + i] = temp[i];
	}
	delete[]temp;
}
void mergesort(int a[], int first, int last){	//将两个任意数组合并排序 
	int mid;
	if (first < last){
		mid = (first + last) / 2;
		mergesort(a, first, mid);	//左边有序 
		mergesort(a, mid + 1, last);	//右边有序 
		mergearray(a, first, mid, last);	//再将两个有序数组合并 
	}
}
void QuickSort(int array[], int begin, int end) {
	if (begin > end)
		return;
	int tmp = array[begin];
	int i = begin;
	int j = end;
	while (i != j) {
		count_cmp++;
		while (array[j] >= tmp && j > i) {
			j--;
			count_cmp++;
		}
		count_cmp++;
		while (array[i] <= tmp && j > i) {
			count_cmp++;
			i++;
		}
		if (j > i) {
			int t = array[i];
			array[i] = array[j];
			array[j] = t;
			count_exc++;
		}
	}
	array[begin] = array[i];
	array[i] = tmp;
	count_exc++;
	QuickSort(array, begin, i - 1);
	QuickSort(array, i + 1, end);
}
int get_digit(int array[], int num) {//返回最array最大的位数
	int max = array[0], digit = 0;
	for (int i = 1; i < num; i++) {
		if (array[i] > max)
			max = array[i];
	}
	while (max) {
		max /= 10;
		digit++;
	}
	return digit;
}
int get_num(int num, int d) {//返回num中的第d位
	int k = 1;
	while (d > 1) {
		k *= 10;
		d--;
	}
	return num / k % 10;
}
void to_end() {
	cin.clear();
	cin.ignore(65535, '\n');
	cout << endl << "PRESS ANY KEY TO CONTINUE...";
	cin.get();
}
void bubble_sort(int array[],int num) {//冒泡排序（初始版）
	count_cmp = 0;//比较次数
	count_exc = 0;//交换次数
	auto begin = chrono::steady_clock::now();
	if (num < 2) //num==1||num==0无需排序
		return;

	for (int i = 0; i < num - 1; i++) {//一共比较 num-1 次
		for (int j = 0; j < num - 1 - i; j++) {//两个紧挨的元素进行比较
			if (array[j] > array[j + 1]) {//前面一个数大于后面，则交换
				swap(array, j, j + 1);
				count_exc++;
			}
			count_cmp++;
		}
	}

	auto end = chrono::steady_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	bool is_ms = false;
	if (duration)
		is_ms = true;
	else
	duration = chrono::duration_cast<chrono::microseconds>(end - begin).count();
	cout << "冒泡排序所用时间：" << duration;
	if (is_ms)
		cout << "毫秒" << endl;
	else
		cout << "微秒" << endl;
	cout << "冒泡排序比较次数：" << count_cmp << endl;
	cout << "冒泡排序交换次数：" << count_exc << endl;
	//out(array, num);
}
void bubble_sort_plus(int array[], int num) {//冒泡排序（优化版）
	//若数组本身后面部分有序，则第二层循环的比较次数可少一些
	//若比较到后期数组已经有序，则最后几步可以不用比较，即需要确定每一层的无序边界
	count_cmp = 0;//比较次数
	count_exc = 0;//交换次数
	auto begin = chrono::steady_clock::now();
	if (num < 2) //num==1||num==0无需排序
		return;
	int no_order_border=0,sort_border=num-1;
	for (int i = 0; i < num - 1; i++) {//一共比较 num-1 次
		bool is_order = true;//若这一趟比较没有元素交换，则说明数组已经有序
		for (int j = 0; j <sort_border; j++) {//两个紧挨的元素进行比较
			if (array[j] > array[j + 1]) {//前面一个数大于后面，则交换
				is_order = false;//有元素交换，说明还没有达到全部有序
				swap(array, j, j + 1);
				count_exc++;
				no_order_border = j;
			}
			count_cmp++;
		}
		sort_border = no_order_border;
		if (is_order==true)//若已经全部有序，则不用再比较，退出
			break;
	}
	auto end = chrono::steady_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	bool is_ms = false;
	duration = chrono::duration_cast<chrono::microseconds>(end - begin).count();
	cout << "冒泡排序plus所用时间：" << duration;
	if (is_ms)
		cout << "毫秒" << endl;
	else
		cout << "微秒" << endl;
	
	cout << "冒泡排序plus比较次数：" << count_cmp << endl;
	cout << "冒泡排序plus交换次数：" << count_exc << endl;
	//out(array, num);
}
void selection_sort(int array[], int num) {
	//每次选出最小的放在第一个，然后选出第二小放第二个...以此类推
	count_cmp = 0;//比较次数
	count_exc = 0;//交换次数
	auto begin = chrono::steady_clock::now();
	if (num < 2)//num==0||num==1无需排序
		return;
	for (int i = 0; i < num-1; i++) {//一共num-1趟
		int target = i;//要放在最前端的数字
		for (int j = i+1; j < num ; j++) {//每一趟都要找到剩下元素中最小的
			if (array[j] < array[target]) {
				target=j;
			}
			count_cmp++;
		}
		swap(array, target, i);
		count_exc++;
	}
	auto end = chrono::steady_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	bool is_ms = false;
	duration = chrono::duration_cast<chrono::microseconds>(end - begin).count();
	cout << "选择排序所用时间：" << duration;
	if (is_ms)
		cout << "毫秒" << endl;
	else
		cout << "微秒" << endl;

	cout << "选择排序比较次数：" << count_cmp << endl;
	cout << "选择排序交换次数：" << count_exc << endl;
	//out(array, num);
}
void selection_sort_plus(int array[], int num) {
	//一次就选出最大值和最小值，放在数组的开头和结尾
	count_cmp = 0;//比较次数
	count_exc = 0;//交换次数
	auto begin = chrono::steady_clock::now();
	if (num < 2)//num==0||num==1无需排序
		return;
	int front = 0,tail=num-1;//起始时候数组头尾
	while (front < tail) {//头尾还没相接
		int max = front;
		int min = front;
		for (int i = front; i <= tail; i++) {//从还没排好的数组中找最大最小
			count_cmp++;
			bool flags = true;
			if (array[i] < array[min]) {
				min = i;
				flags = false;
			}
			else if (array[i] > array[max]) {
				max = i;
			}
			count_cmp += flags;
		}
		bool flag = false;
		if (min != front) {
			swap(array, min, front);
			count_exc++;
			flag = true;
		}
		if (max == front&&flag==true)//如果max在front，并且被换掉了
			max = min;
		if (max != tail) {
			swap(array, max, tail);
			count_exc++;
		}

		++front;
		--tail;
	}
	auto end = chrono::steady_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	bool is_ms = false;
	duration = chrono::duration_cast<chrono::microseconds>(end - begin).count();
	cout << "选择排序plus所用时间：" << duration;
	if (is_ms)
		cout << "毫秒" << endl;
	else
		cout << "微秒" << endl;

	cout << "选择排序plus比较次数：" << count_cmp << endl;
	cout << "选择排序plus交换次数：" << count_exc << endl;
	//out(array, num);
}
void insert_sort(int array[], int num) {
	count_cmp = 0;//比较次数
	count_exc = 0;//交换次数
	
	auto begin = chrono::steady_clock::now();
	for (int i = 0; i < num-1; i++) {
		int end = i;//前面的有序序列的最后一个元素的位置
		int temp = array[end + 1];//取后一个元素
		while(end >= 0) {
			count_cmp++;
			if (temp < array[end]) {
				array[end + 1] = array[end];//往后移一格
				end--;
			}
			else
				break;
		}
		array[end + 1] = temp;
		count_exc++;
	}
	auto end = chrono::steady_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	bool is_ms = false;
	duration = chrono::duration_cast<chrono::microseconds>(end - begin).count();
	cout << "直接插入排序所用时间：" << duration;
	if (is_ms)
		cout << "毫秒" << endl;
	else
		cout << "微秒" << endl;

	cout << "直接插入排序比较次数：" << count_cmp << endl;
	cout << "直接插入排序交换次数：" << count_exc << endl;
	//out(array, num);
}
void shell_sort(int array[], int num) {
	count_cmp = 0;//比较次数
	count_exc = 0;//交换次数

	auto begin = chrono::steady_clock::now();
	int gap = num;//分块
	while (gap > 1){	
		gap = gap / 2;//每次gap/2
		for (int i = 0; i < num - gap; ++i){
			int end = i;
			int temp = array[end + gap];
			while (end >= 0){
				count_cmp++;
				if (temp < array[end]){
					array[end + gap] = array[end];
					end -= gap;
					count_exc++;
				}
				else
					break;
			}
			array[end + gap] = temp;
			count_exc++;
		}
	}
	auto end = chrono::steady_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	bool is_ms = false;
	duration = chrono::duration_cast<chrono::microseconds>(end - begin).count();
	cout << "希尔排序所用时间：" << duration;
	if (is_ms)
		cout << "毫秒" << endl;
	else
		cout << "微秒" << endl;

	cout << "希尔排序比较次数：" << count_cmp << endl;
	cout << "希尔排序交换次数：" << count_exc << endl;
	//out(array, num);
}
void quick_sort(int array[], int num) {
	count_cmp = 0;//比较次数
	count_exc = 0;//交换次数
	
	auto begin = chrono::steady_clock::now();
	QuickSort(array, 0, num - 1);
	auto end = chrono::steady_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	bool is_ms = false;
	duration = chrono::duration_cast<chrono::microseconds>(end - begin).count();
	cout << "快速排序所用时间：" << duration;
	if (is_ms)
		cout << "毫秒" << endl;
	else
		cout << "微秒" << endl;

	cout << "快速排序比较次数：" << count_cmp << endl;
	cout << "快速排序交换次数：" << count_exc << endl;
	//out(array, num);
}
void heap_sort(int array[], int num) {
	//使用一个大根堆，每次把堆顶元素和最后一个元素置换，并在除了被换过后的堆底元素
	//中的其他元素中调整大根堆，依次循环
	count_heapcmp = 0;//比较次数
	count_heapexc = 0;//交换次数
	
	auto begin = chrono::steady_clock::now();
	maxHeap<int> heap(array,num);

	heap.rank_heap();
	auto end = chrono::steady_clock::now();
	//int* p = heap.get_pheap();
	auto duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	bool is_ms = false;
	duration = chrono::duration_cast<chrono::microseconds>(end - begin).count();
	cout << "堆排序所用时间：" << duration;
	if (is_ms)
		cout << "毫秒" << endl;
	else
		cout << "微秒" << endl;

	cout << "堆排序比较次数：" << count_heapcmp << endl;
	cout << "堆排序交换次数：" << count_heapexc << endl;
	//out(p, num);
}
void merge_sort(int array[], int num) {
	count_cmp = 0;//比较次数
	count_exc = 0;//交换次数
	
	auto begin = chrono::steady_clock::now();
	mergesort(array, 0, num - 1);
	auto end = chrono::steady_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	bool is_ms = false;
	duration = chrono::duration_cast<chrono::microseconds>(end - begin).count();
	cout << "归并排序所用时间：" << duration;
	if (is_ms)
		cout << "毫秒" << endl;
	else
		cout << "微秒" << endl;

	cout << "归并排序比较次数：" << count_cmp << endl;
	//cout << "归并排序交换次数：" << count_exc << endl;
	//out(array, num);
}
void MSDradix_sort(int array[], int num) {
	int d = get_digit(array, num);
	count_cmp = 0;//比较次数
	count_exc = 0;//交换次数

	auto begin = chrono::steady_clock::now();
	msd_radixsort(array, 0, num - 1, d,num);
	auto end = chrono::steady_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	bool is_ms = false;
	duration = chrono::duration_cast<chrono::microseconds>(end - begin).count();
	cout << "MSD基数排序所用时间：" << duration;
	if (is_ms)
		cout << "毫秒" << endl;
	else
		cout << "微秒" << endl;

	cout << "MSD基数排序交换次数：" << count_exc << endl;
	//out(array, num);
}
void msd_radixsort(int array[], int left, int right, int d,int num) {
	//从高位到底为对序列进行划分，d是第几位，d=1是个位
	//left和right是待排序元素子序列的始端和尾端
	int i,j,count[10], p1, p2;
	int* temp = new int[right-left+1];
	if (d <= 0)
		return;
	
	memset(count, 0, sizeof(count));
	for (i = left; i <= right; i++)//统计各个桶元素个数
		count[get_num(array[i],d)]++;//取第i个元素的第d位的值
	for (i = 1; i < 10; i++)//每个桶中元素的末位置
		count[i] = count[i] + count[i - 1];
	for (i = left; i <= right; i++) {
		j = get_num(array[i], d);//取第i个元素的第d位的值
		temp[count[j] - 1] = array[i];//存放
		count[j]--;
	}
	for (i = left, j = 0; i <= right; i++, j++) {
		array[i] = temp[j];
		count_exc++;
	}//把temp中的元素写入原来的数组
	delete[]temp;
	for (j = 0; j < 10; j++) {//按桶递归对d-1位排序
		p1 = left+count[j];//取该桶开始的位置
		if (j < 9)
			p2 = left+count[j + 1] - 1;//取该桶结束的位置
		else
			p2 = right;
		if(p1<p2)
		msd_radixsort(array, p1, p2, d - 1,num);//对该桶内的元素进行排序
	}

}
void LSDradix_sort(int array[], int num) {
	count_cmp = 0;//比较次数
	count_exc = 0;//交换次数

	auto begin = chrono::steady_clock::now();
	int digit = get_digit(array, num);  // digit表示数组array的最大位数
	int radix = 1;                // radix表示当前比较的是什么位，个位、十位...

	for (int i = 0; i < digit; i++) {
		int* temp = new int[num];
		int buckets[10] ;
		memset(buckets, 0, sizeof(buckets));
		for (int i = 0; i < num; i++) {
			buckets[(array[i] / radix) % 10]++;
		}//每个篮子里有几个
		for (int i = 1; i < 10; i++) {
			buckets[i] += buckets[i - 1];
		}//每位在数组中的末位置
		for (int i = num - 1; i >= 0; i--) {
			temp[buckets[(array[i] / radix) % 10] - 1] = array[i];
			buckets[(array[i] / radix) % 10]--;
		}//从后往前放入temp
		for (int i = 0; i < num; i++)
			array[i] = temp[i];
		radix *= 10;
	}
	auto end = chrono::steady_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	bool is_ms = false;
	duration = chrono::duration_cast<chrono::microseconds>(end - begin).count();
	cout << "MSD基数排序所用时间：" << duration;
	if (is_ms)
		cout << "毫秒" << endl;
	else
		cout << "微秒" << endl;
	//cout << "LSD基数排序比较次数：" << count_cmp << endl;
	//cout << "LSD基数排序交换次数：" << count_exc << endl;
	//out(array, num);
}
