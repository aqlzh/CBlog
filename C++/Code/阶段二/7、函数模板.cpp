#include <iostream>
using namespace std ;
#include <string>

class Person {
public :
	Person(string name, int age) {
		this->m_Name = name;
		this->m_Age = age;


	}

	string m_Name;
	int m_Age;
};

// 普通函数模板 
template <class T>
bool myCompare(T& a, T& b) {
	if (a == b) return true;
	else return false;

}

// 具体化
template<> bool myCompare(Person& p1, Person& p2) {
	if (p1.m_Age == p2.m_Age && p1.m_Name == p2.m_Name)return true;
	else return false;

}


void test08() {
	Person p1("Tom", 10);
	Person p2("Tom", 10);

	bool res = myCompare(p1, p2);

	if (res) {
		cout << "两者相等" << endl;
	}
	else {
		cout << "两种不相等" << endl;
	}
}


int main() {

	test08();
	system("pause");
	return 0;
}