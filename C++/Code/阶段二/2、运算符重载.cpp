#include <iostream>
using namespace std;


class MyInteger {
	friend ostream& operator<<(ostream& out, MyInteger myint);
public :
	MyInteger() {
		m_Num = 0;
	}

	// ����ǰ�������
	MyInteger& operator++() {
		m_Num++;
		return *this;   // ��ʽ���  ����myint ����
	}
	// ���غ��������
	MyInteger operator++(int) {
		// �ȷ���
		MyInteger temp = *this;
		m_Num++;
		return temp;
	}
private :
	int m_Num;
};



// ȫ�ֺ������� ���
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