#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <string>

// 包含知识点   三种遍历方式的使用    Vector自定义数据类型（Person）  Vector 存放指针


void myPrintln(int val) {
	cout << val << endl;
}



// 自定义数据类型
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


	// 第一种遍历方式
	vector<int>::iterator Begin = v.begin();
	vector<int>::iterator End = v.end();

	while (Begin != End) {
		cout << *Begin << endl;
		Begin++;
	}
	// 第二种遍历方式   简写

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << *it << endl;
	}

	// 第三种方式  STL  内置
	for_each(v.begin(), v.end(), myPrintln);

}

void test13() {
	vector<Person> v1;
	Person p1("花丸",16);
	Person p2("善子", 17);
	Person p3("露比", 15);


	v1.push_back(p1);
    v1.push_back(p2);
	v1.push_back(p3);

	for (vector<Person>::iterator it = v1.begin(); it != v1.end(); it++) {    // *it  就是 Vector<>  内的
		cout << (*it).m_Name << " " << (*it).m_Age << endl;

	}

}
// 存放指针 
void test14() {
	vector<Person*> v2;

	Person p1("小花丸", 16);
	Person p2("中善子", 17);
	Person p3("大露比", 15);


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