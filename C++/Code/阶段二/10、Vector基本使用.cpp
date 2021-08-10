#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <string>

// ����֪ʶ��   ���ֱ�����ʽ��ʹ��    Vector�Զ����������ͣ�Person��  Vector ���ָ��


void myPrintln(int val) {
	cout << val << endl;
}



// �Զ�����������
class  Person {
public:
	Person(string name, int age) {
		this->m_Name = name;
		this->m_Age = age;

	}

public:
	string m_Name;
	int m_Age;

};

void test12() {
	vector<int> v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);


	// ��һ�ֱ�����ʽ
	vector<int>::iterator Begin = v.begin();
	vector<int>::iterator End = v.end();

	while (Begin != End) {
		cout << *Begin << endl;
		Begin++;
	}
	// �ڶ��ֱ�����ʽ   ��д

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << *it << endl;
	}

	// �����ַ�ʽ  STL  ����
	for_each(v.begin(), v.end(), myPrintln);

}

void test13() {
	vector<Person> v1;
	Person p1("����",16);
	Person p2("����", 17);
	Person p3("¶��", 15);


	v1.push_back(p1);
    v1.push_back(p2);
	v1.push_back(p3);

	for (vector<Person>::iterator it = v1.begin(); it != v1.end(); it++) {    // *it  ���� Vector<>  �ڵ�
		cout << (*it).m_Name << " " << (*it).m_Age << endl;

	}

}
// ���ָ�� 
void test14() {
	vector<Person*> v2;

	Person p1("С����", 16);
	Person p2("������", 17);
	Person p3("��¶��", 15);


	v2.push_back(&p1);
	v2.push_back(&p2);
	v2.push_back(&p3);

	for (vector<Person*>::iterator it = v2.begin(); it != v2.end(); it++) {
		cout << (*it)->m_Name << " " << (*it)->m_Age << endl;

	}

}


int main() {

	test12();
	test13();
	test14();
	system("pause");
	return 0;
}