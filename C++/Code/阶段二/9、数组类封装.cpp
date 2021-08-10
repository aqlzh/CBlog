#include <iostream>
using namespace std;
#include "myArray.hpp"
#include <string>


void printArray(MyArray<int> arr) {
	for (int i = 0; i < arr.getSize(); i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}


//  �����Զ�����������
class Person {
public:
	Person() {};    // �޲�������
	Person(string name, int age) {
		this->m_Age = age;
		this->m_Name = name;
	};
public:
	string m_Name;
	int m_Age;
};
//  ���
void printPersonArray(MyArray<Person> PA ) {
	for (int i = 0; i < PA.getSize(); i++) {
		cout << "���� ��" << PA[i].m_Age << "����" << PA[i].m_Name << endl;
 	}
}


// ����������������
void test10() {
	MyArray<int> array1(10);
	for (int i = 0; i < 10; i++) {
		array1.Push_back(i);
	}
	printArray(array1);
	cout << "array1 �Ĵ�С" << array1.getSize() << endl;
	cout << "array1������" << array1.getCapacity() << endl;
		 
	cout << "-------------" << endl;
	MyArray<int> array2(array1);    // ��������  array1 
	array2.Pop_back();
	printArray(array2);
	cout << "array2 �Ĵ�С" << array2.getSize() << endl;
	cout << "array2������" << array2.getCapacity() << endl;
}

// �����Զ�����������    ��Ҫ�ø�����   -->   �������ô���
void test11() {
	MyArray<Person> pArray(10);
	Person p1("�ܽ���",12);
	Person p2("�Ž�", 11);
	Person p3("�ܽ�", 13);
	Person p4("�ӽ�", 21);

	pArray.Push_back(p1);
	pArray.Push_back(p2);
	pArray.Push_back(p3);
	pArray.Push_back(p4);

	cout << endl;
	cout << "-----�Զ������Ͳ���-----" << endl;

	printPersonArray(pArray);
	cout << "pArray �Ĵ�С" << pArray.getSize() << endl;
	cout << "pArray������" << pArray.getCapacity() << endl;
}

int main() {

	test10();
	test11();

	system("pause");
	return 0;
}
