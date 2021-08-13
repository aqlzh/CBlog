#include <iostream>
using namespace std;
#include <set>
#include <string>



class Person {
public:
	Person(string name, int age) {
		this->m_Name = name;
		this->m_Age = age;
	}

	string m_Name;
	int m_Age;
};

/// <summary>
///  重写根据规则排序  类   自定义仿函数
/// </summary>

class comparePerson {
public :
		bool operator()(const Person& p1, const Person& p2) {
			return p1.m_Age > p2.m_Age;
	}
};

void test22() {

	set<Person, comparePerson> s;

	Person p1("刘备", 23);
	Person p2("关羽", 27);
	Person p3("张飞", 25);
	Person p4("赵云", 21);

	s.insert(p1);
	s.insert(p2);
	s.insert(p3);
	s.insert(p4);


	// 本程序关键如下
	for (set<Person, comparePerson>::iterator it = s.begin(); it != s.end(); it++) {
		cout << "姓名 " << (*it).m_Name << "年龄 " << (*it).m_Age << endl;
	}
}


int main18() {

	test22();
	system("pause");
	return 0;
}