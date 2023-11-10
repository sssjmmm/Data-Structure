#ifndef _SJM_AVL_
#define _SJM_AVL_

#include"sjm_stack.h"
#include"exam_re_sys.h"
template<class E, class K>//E是结点，K是结点的关键码
struct AVLNode {
	E data;//结点数据
	AVLNode<E, K>* left, * right;//左右指针
	int bf;//平衡因子balance factor
	AVLNode() :left(NULL), right(NULL), bf(0) {};
	AVLNode(E d, AVLNode<E, K>* l = NULL, AVLNode<E, K>* r = NULL) :data(d), left(l), right(r), bf(0) {};
	~AVLNode() {};//析构函数
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
	AVLNode<E, K>* root;//根指针
	int tree_num;//结点个数
	bool Insert(AVLNode<E, K>*& ptr, E& el);//插入，内部函数
	bool Remove(AVLNode<E, K>*& ptr, K x);//删除，内部函数
	void RotateL(AVLNode<E, K>*& ptr);//左单旋
	void RotateR(AVLNode<E, K>*& ptr);//右单旋
	void RotateLR(AVLNode<E, K>*& ptr);//先左单旋后右单旋
	void RotateRL(AVLNode<E, K>*& ptr);//先右单旋后做单旋
public:
	AVLTree() :root(NULL), tree_num(0) {}//构造函数，构造空AVL树
	AVLNode<E, K>* Search1(K x, AVLNode<E, K>*& ptr);//搜索，外部接口
	AVLNode<E, K>* find(K x) {//查找，返回指向结点的指针，外部接口
		return Search1(x, root);
	}
	bool Insert(E& el) {//插入，外部接口
		return Insert(root, el);
	}
	bool Remove(K x) {//删除，外部接口
		return Remove(root, x);
	}
	AVLNode<E, K>* get_root() {//返回根结点
		return root;
	}
	int get_Tnum() {//返回树的结点数，用于统计
		return tree_num;
	}
	void input(int i);//插入i个元素
	void ouput();//输出
	int count() {//中序遍历计结点个数，统计的方法2
		int count = 0;
		Traverse(root, count);
		return count;
	}
	friend ostream& operator<<(ostream& out, const AVLTree<E, K>& Tree) {
		Tree.Traverse(Tree.root, out);//以中序次序输出各结点的数据
		out << endl;
		return out;//返回输出元素

	}
	void Traverse(const AVLNode<E, K>* ptr, ostream& out)const;//中序遍历输出
	void Traverse(const AVLNode<E, K>* ptr, int& count)const;//中序遍历计数
};

template<class E, class K>
AVLNode<E, K>* AVLTree<E, K>::Search1(K x, AVLNode<E, K>*& ptr) {
	//搜索含x的结点，成功返回该节点的地址，失败返回NULL
	if (ptr == NULL)
		return NULL;
	else if (x < ptr->data)
		return Search1(x, ptr->left);//到左子树中继续搜索
	else if (x > ptr->data)
		return Search1(x, ptr->right);//到右子树中继续搜索
	else
		return ptr;//搜索成功
}

template<class E, class K>
void AVLTree<E, K>::RotateL(AVLNode<E, K>*& ptr) {
	//右子树比左子树高：对以ptr为根的AVL树做左单旋转，旋转后新根在ptr
	AVLNode<E, K>* subL = ptr;//要左旋转的结点
	ptr = subL->right;//原根的右子女
	subL->right = ptr->left;//ptr成为新根前卸掉左边负载
	ptr->left = subL;//左单旋转，ptr为新根
	ptr->bf = subL->bf = 0;
}

template<class E, class K>
void AVLTree<E, K>::RotateR(AVLNode<E, K>*& ptr) {
	//右子树比左子树高：对以ptr为根的AVL树做右单旋转，旋转后新根在ptr
	AVLNode<E, K>* subR = ptr;//要右旋转的结点
	ptr = subR->left;//原根的左子女
	subR->left = ptr->right;//ptr成为新根前卸掉右边负载
	ptr->right = subR;//右单旋转，ptr为新根
	ptr->bf = subR->bf = 0;
}

template<class E, class K>
void AVLTree<E, K>::RotateLR(AVLNode<E, K>*& ptr) {
	AVLNode<E, K>* subR = ptr, * subL = subR->left;
	ptr = subL->right;
	subL->right = ptr->left;//ptr成为新根前甩掉它左边的负载
	ptr->left = subL;//左单旋转，ptr成为新根
	if (ptr->bf <= 0)
		subL->bf = 0;//插入结新点后ptr左子树变高
	else
		subL->bf = -1;
	subR->left = ptr->right;//ptr成为新根前甩掉它右边
	ptr->right = subR;//右单旋转，ptr成为新根
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
	subR->left = ptr->right;//ptr成为新根前甩掉它右边的负载
	ptr->right = subR;//右单旋转，ptr成为新根
	if (ptr->bf >= 0)
		subR->bf = 0;
	else
		subR->bf = 1;
	subL->right = ptr->left;//ptr成为新根前甩掉它左边的负载
	ptr->left = subL;//左单旋转，ptr成为新根
	if (ptr->bf == 1)
		subL->bf = -1;
	else
		subL->bf = 0;
	ptr->bf = 0;
}

template<class E, class K>
bool AVLTree<E, K>::Insert(AVLNode<E, K>*& ptr, E& el) {
	//在以ptr为根的AVL树中插入新元素el，如果插入成功，函数返回true，否则返回false。
	AVLNode<E, K>* pr = NULL, * p = ptr, * q;
	int d;
	LinkedStack<AVLNode<E, K>*>st;
	while (p != NULL) {//寻找插入位置
		if (el == p->data)//找到等于el的结点，不插入
			return false;
		pr = p;
		st.Push(pr);//否则用栈记忆查找路径
		if (el < p->data)
			p = p->left;
		else
			p = p->right;
	}
	p = new AVLNode<E, K>(el);//创建新结点，data=el，bf=0
	if (p == NULL) {
		cerr << "存储空间不足！" << endl;
		return false;
	}
	if (pr == NULL) {//空树，新结点成为根结点
		ptr = p;
		tree_num++;
		return true;
	}
	if (el < pr->data)
		pr->left = p;
	else
		pr->right = p;
	while (st.IsEmpty() == false) {//重新平衡化
		st.Pop(pr);//从栈中退出父结点
		if (p == pr->left)//调整父结点的平衡因子
			pr->bf--;
		else
			pr->bf++;
		if (pr->bf == 0)//结点平衡因子=0，平衡退出
			break;
		if (pr->bf == 1 || pr->bf == -1)//结点平衡因子绝对值=1
			p = pr;
		else {//结点平衡因子绝对值=2
			d = (pr->bf < 0) ? -1 : 1;//区别单双旋标志
			if (p->bf == d) {//两结点平衡因子同号，单旋转
				if (d == -1)//右单旋转
					RotateR(pr);
				else//左单旋转
					RotateL(pr);
			}
			else {//两结点平衡因子番号，双旋转
				if (d == -1)//先左后右双旋转，“<”型
					RotateLR(pr);
				else//先右后左双旋转，“>”型
					RotateRL(pr);
			}
			break;//不再向上调整
		}//end of |bf|==2
	}//end of while(st.IsIsEmpty()==false)
	if (st.IsEmpty() == true)
		ptr = pr;//调整到数的根结点
	else {//中间重新连接
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
	cout << "中根遍历AVL树" << endl;
	Traverse(root);//以中序次序输出各结点的数据
	cout << endl;
}

template<class E, class K>
void AVLTree<E, K>::Traverse(const AVLNode<E, K>* ptr, ostream& out)const {
	if (ptr != NULL) {//树非空
		Traverse(ptr->left, out);//中序遍历左子树
		out << ptr->data << endl;//输出根的数据
		Traverse(ptr->right, out);//中序遍历右子树
	}
}

template<class E, class K>
void AVLTree<E, K>::Traverse(const AVLNode<E, K>* ptr, int& count)const {
	if (ptr != NULL) {//树非空
		Traverse(ptr->left, count);//中序遍历左子树
		count++;
		Traverse(ptr->right, count);//中序遍历右子树
	}
}
template<class E, class K>
bool AVLTree<E, K>::Remove(AVLNode<E, K>*& cur, K val) {
	LinkedStack<AVLNode<E, K>*> stk;
	//p:要删除的结点，son:要删除结点的子结点
	AVLNode<E, K>* parent = NULL, * p = cur, * pparent = NULL, * son;
	int d = 0, dd = 0;
	while (p)//寻找删除位置
	{
		if (val == p->data.num)//找到了要删除的结点
			break;
		parent = p;
		stk.Push(parent);//记录走过的路径
		if (val < p->data.num)
			p = p->left;
		else
			p = p->right;
	}
	//找不到要删除的结点
	if (p == NULL)
		return false;
	if (p->left && p->right)//被删除结点有两个子结点，变换为简单情况
	{
		parent = p;
		stk.Push(parent);
		//左子树的直接前驱，左边走一步，接着走到最右边
		son = p->left;
		while (son->right)
		{
			parent = son;
			stk.Push(parent);
			son = son->right;
		}
		p->data = son->data;//直接前驱的值赋给要删除的结点
		p = son;//转换为要删去直接前驱
	}
	//换完之后的情况：至多有一个子结点，记录为son
	if (p->left)
		son = p->left;
	else
		son = p->right;
	//为根结点，直接连上要删除结点的子结点son
	if (parent == NULL)
		cur = son;
	else//不是根结点
	{
		//连上要删除结点的子结点son
		if (parent->left == p)
			parent->left = son;
		else
			parent->right = son;

		//开始回溯，重新平衡化
		while (!stk.IsEmpty())
		{

			stk.Pop(parent);
			//调整parent的bf
			if (parent->left == son)//删掉了原来在parent左边的结点
				parent->bf++;
			else
				parent->bf--;

			//得到爷结点
			if (!stk.IsEmpty())
			{
				stk.Pop(pparent);
				dd = (pparent->left == parent) ? -1 : 1;
			}
			else//没有爷结点
				dd = 0;
			//如果parent平衡因子绝对值为1，则不用调整，直接退出
			if (parent->bf == 1 || parent->bf == -1)
				break;
			if (parent->bf)//bf绝对值为2
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
