#include <iostream>
using namespace std;
#include <string>

class Myprint {
public:
	Myprint() {
		this->count = 0;
	}

	// ���������ʹ��
	void operator()(string str) {
		cout << str << endl;
		count++;
	}

	int count;
};


void test24() {
	Myprint my;
	my("hello");
	my("hello");
	my("hello");

	cout << "my�ĵ��ô���" << my.count << endl;
}


// ������������Ϊ��������
void doPrint(Myprint& my, string str) {
	my(str);
}


void test25() {
	Myprint my;
	doPrint(my, "Hello Jay");
}

int main20() {
	//test24();
	test25();
	system("pause");
	return 0;
}