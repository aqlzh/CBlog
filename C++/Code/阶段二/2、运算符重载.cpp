#include <iostream>
using namespace std;


class MyInteger {
	friend ostream& operator<<(ostream& out, MyInteger myint);
public :
	MyInteger() {
		m_Num = 0;
	}

	// 重载前置运算符
	MyInteger& operator++() {
		m_Num++;
		return *this;   // 链式编程  返回myint 对象
	}
	// 重载后置运算符
	MyInteger operator++(int) {
		// 先返回
		MyInteger temp = *this;
		m_Num++;
		return temp;
	}
private :
	int m_Num;
};



// 全局函数重载 输出
ostream& operator<<(ostream& out, MyInteger myint) {
	out << myint.m_Num;
	return out;

}

void test02() {
	MyInteger myInt;
	cout << ++myInt << endl;
	cout << myInt << endl;
}

void test03() {
	MyInteger myInt;
	cout << ++myInt << endl;
	cout << myInt << endl;
}


int main02() {

	//test02();
	test03();

	system("pause");
	return 0;
}