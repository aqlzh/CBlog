#include <iostream>
using namespace std;
#include <stack>


void test19() {
	stack<int> s;

	s.push(10);
	s.push(20);
	s.push(30);

	cout << "ջ�Ĵ�СΪ  " << s.size() << endl;

	while (!s.empty()) {
		cout << "ջ��Ԫ��Ϊ " << s.top() << endl;
		s.pop();
	}

	cout << "ջ�Ĵ�СΪ  " << s.size() << endl;
}

int main15() {

	test19();
	system("pause");
	return 0;
}
