#include<iostream>
using namespace std;
 
#include"6_2151299_苏家铭.h"
void choice_A(Tree<String>& tree);
void choice_B(Tree<String>& tree);
void choice_C(Tree<String>& tree);
void choice_D(Tree<String>& tree);
void choice_E(Tree<String>& tree);
int main() {
	Tree<String> tree;
	String name;
	cout << "**          家谱管理系统                   **" << endl;
	cout << "=============================================" << endl;
	cout << "**       请选择要执行的操作 :              **" << endl;
	cout << "**          A --- 完善家谱                 **" << endl;
	cout << "**          B --- 添加家庭成员             **" << endl;
	cout << "**          C --- 解散局部家庭             **" << endl;
	cout << "**          D --- 更改家庭成员姓名         **" << endl;
	cout << "**          E --- 查看家庭成员的第一代子孙 **" << endl;
	cout << "**          F --- 退出    程序             **" << endl;
	cout << "=============================================" << endl;
	cout << "首先建立一个家谱!" << endl;
	cout << "请输入祖先的名字:" << endl;
	cin >> name;
	cout << "此家谱的祖先是:" << name << endl;
	tree.set_root(name);
	bool Loop = true;
	char choice;
	while (Loop) {
		cout << endl << "请选择要执行的操作：" << endl;
		while (1) {
			cin >> choice;
			if (choice >= 'a' && choice <= 'z')//小写转大写
				choice = choice + 'A' - 'a';

			if (choice >= 'A' && choice <= 'Z') {
				break;
			}
			else {
				cout << "输入操作有误，请再次输入" << endl;
				cin.clear();
				cin.ignore(65535, '\n');
			}
		}
		switch (choice) {
		case 'A':
			choice_A(tree);
			break;
		case 'B':
			choice_B(tree);
			break;
		case 'C':
			choice_C(tree);
			break;
		case 'D':
			choice_D(tree);
			break;
		case 'E':
			choice_E(tree);
			break;
		case 'F':
			Loop = false;
			break;
		default:
			break;
		}
	}
	cin.clear();
	cin.ignore(65535, '\n');
	cout << endl << "PRESS ANY KEY TO CONTINUE...";
	cin.get();
	return 0;
}

void choice_A(Tree<String>& tree) {
	String name[50];
	int num;
	cout << "请输入要建立家庭的人的姓名：";
	cin >> name[0];
	//健壮性
	while (!tree.Find(name[0])) {//没找到该成员
		cout << "未在家谱中找到该成员！" << endl;
		cout << "请重新输入要建立家庭的人的姓名：";
		cin >> name[0];
	}

	while (1) {
		cout << "请输入" << name[0] << "的儿女的个数：";
		cin >> num;
		if (cin.fail() || num <= 0) {
			cout << "儿女个数输入错误！" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
		}
		else
			break;
	}
	cout << "请依次输入" << name[0] << "儿女的姓名:";
	for (int i = 1; i <= num; i++) {
		cin >> name[i];
	}
	int i = 1;
	while (i <= num) {
		tree.insert(name[0], name[i]);
		i++;
	}
	cout << name[0] << "的第一代儿女是:";
	tree.output_children(name[0]);
	cout << endl;

}

void choice_B(Tree<String>& tree) {
	String name[2];
	cout << "请输入要添加儿子（女儿）的人的姓名:";
	cin >> name[0];
	cout << "请输入" << name[0] << "新添加的儿子（女儿）的姓名:";
	cin >> name[1];
	while (!tree.Find(tree.get_root(), name[0])) {//找到
		cout << "未找到要添加儿子（女儿）的人的姓名:" << endl;
		cout << "请再次输入要添加儿子（女儿）的人的姓名:";
		cin >> name[0];
		cout << "请输入" << name[0] << "新添加的儿子（女儿）的姓名:";
		cin >> name[1];
	}
	tree.insert(name[0], name[1]);
	cout << name[0] << "的第一代子孙是:";
	tree.output_children(name[0]);
	cout << endl;
}

void choice_C(Tree<String>& tree) {
	String name;
	cout << "请输入要解散家庭的人的姓名:";
	cin >> name;
	while (!tree.Find(tree.get_root(), name)) {//找到
		cout << "未找到要解散家庭的人的姓名:" << endl;
		cout << "请再次输入要解散家庭的人的姓名:";
		cin >> name;
	}
	cout << name << "的第一代子孙是:";
	tree.output_children(name);
	cout << endl;
	tree.remove_subtree(tree.get_current());
}

void choice_D(Tree<String>& tree) {
	String name[2];
	cout << "请输入要更改姓名的人的目前姓名:";
	cin >> name[0];
	while (!tree.Find(tree.get_root(), name[0])) {//找到
		cout << "未找到要更改姓名的人名:" << endl;
		cout << "请再次输入要更改姓名的人名:";
		cin >> name[0];
	}
	cout << "请输入更改后的姓名:";
	cin >> name[1];
	tree.change_data(name[0], name[1]);
	cout << name[0] << "已更名为" << name[1] << endl;
}

void choice_E(Tree<String>& tree) {
	String name;
	cout << "请输入要查看儿女的人的姓名:";
	cin >> name;
	while (!tree.Find(tree.get_root(), name)) {//找到
		cout << "未找到要查看儿女的人的姓名:" << endl;
		cout << "请再次输入要查看儿女的人的姓名:";
		cin >> name;
	}
	cout << name << "的第一代子孙是:";
	tree.output_children(name);
	cout << endl;
}

