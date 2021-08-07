#include <iostream>
using namespace std ;
#include <string>


double PI = 3.14;

class Circle {
public :

	int r ;
	double fun() {
		return 2 * PI * r;
	}
};

class Student {
public :
	int age;
	string name;


	void setName(string name) {
		name = name;
	}

	void setAge(int age) {
		age = age;
	}

	void Print() {
		cout << "姓名= " << name << "年龄=" << age<<endl;
	}

	
};

int main10() {

	Circle c1;
	c1.r = 10;

	cout << "圆的周长= " << c1.fun() << endl;

	cout << "我是分节符" << endl;

	Student stu1;
	stu1.age = 18;
	stu1.name = "花阳";
	stu1.Print();

	system("pause");
	return 0;
}
