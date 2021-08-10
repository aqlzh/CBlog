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


//  测试自定义数据类型
class Person {
public:
	Person() {};    // 无参数构造
	Person(string name, int age) {
		this->m_Age = age;
		this->m_Name = name;
	};
public:
	string m_Name;
	int m_Age;
};
//  输出
void printPersonArray(MyArray<Person> PA ) {
	for (int i = 0; i < PA.getSize(); i++) {
		cout << "年龄 ：" << PA[i].m_Age << "姓名" << PA[i].m_Name << endl;
 	}
}


// 测试内置数据类型
void test10() {
	MyArray<int> array1(10);
	for (int i = 0; i < 10; i++) {
		array1.Push_back(i);
	}
	printArray(array1);
	cout << "array1 的大小" << array1.getSize() << endl;
	cout << "array1的容量" << array1.getCapacity() << endl;
		 
	cout << "-------------" << endl;
	MyArray<int> array2(array1);    // 拷贝数组  array1 
	array2.Pop_back();
	printArray(array2);
	cout << "array2 的大小" << array2.getSize() << endl;
	cout << "array2的容量" << array2.getCapacity() << endl;
}

// 测试自定义数据类型    不要好高鹜云   -->   不动手敲代码
void test11() {
	MyArray<Person> pArray(10);
	Person p1("周杰伦",12);
	Person p2("张杰", 11);
	Person p3("周杰", 13);
	Person p4("钟杰", 21);

	pArray.Push_back(p1);
	pArray.Push_back(p2);
	pArray.Push_back(p3);
	pArray.Push_back(p4);

	cout << endl;
	cout << "-----自定义类型测试-----" << endl;

	printPersonArray(pArray);
	cout << "pArray 的大小" << pArray.getSize() << endl;
	cout << "pArray的容量" << pArray.getCapacity() << endl;
}

int main() {

	test10();
	test11();

	system("pause");
	return 0;
}
