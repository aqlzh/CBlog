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
///  ��д���ݹ�������  ��   �Զ���º���
/// </summary>

class comparePerson {
public :
		bool operator()(const Person& p1, const Person& p2) {
			return p1.m_Age > p2.m_Age;
	}
};

void test22() {

	set<Person, comparePerson> s;

	Person p1("����", 23);
	Person p2("����", 27);
	Person p3("�ŷ�", 25);
	Person p4("����", 21);

	s.insert(p1);
	s.insert(p2);
	s.insert(p3);
	s.insert(p4);


	// ������ؼ�����
	for (set<Person, comparePerson>::iterator it = s.begin(); it != s.end(); it++) {
		cout << "���� " << (*it).m_Name << "���� " << (*it).m_Age << endl;
	}
}


int main18() {

	test22();
	system("pause");
	return 0;
}