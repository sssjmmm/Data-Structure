#include<iostream> 
using namespace std;
#include"1_2151299_苏家铭.h"
int main() {
	int choice = -1;
	bool Loop = true;
	student one;
	examination_register_system ers;
	ers.initialization();//初始化系统
	ers.show();//输出
	while (Loop) {
		cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）";
		cin >> choice;
		while (!(choice >= 0 && choice <= 5) || cin.fail()) {
			cout << "输入的操作非法，请再次输入您要进行的操作：";
			cin.clear();
			cin.ignore(65536, '\n');
			cin >> choice;
		}
		switch (choice) {
		case 1:
			ers.insert();
			ers.show();
			break;
		case 2:
			ers.erase();
			ers.show();
			break;
		case 3:
			ers.find();
			break;
		case 4:
			ers.modify();
			ers.show();
			break;
		case 5:
			ers.stat();
			break;
		case 0:
			Loop = false;
			break;
		}//end of switch
	}//end of while
	cin.clear();
	cin.ignore(65535, '\n');
	cout << endl << "PRESS ANY KEY TO CONTINUE...";
	cin.get();
}


