#include <iostream>
using namespace std;

class Person {

public :
	Person(int age) {
		this->age = age;
	}
	int age;
};


void test01() {
	Person p1(18);
	cout << "p1µÄÄêÁäÎª" << p1.age << endl;
}


int main01() { 
	test01();
	system("pause");
	return 0;
}