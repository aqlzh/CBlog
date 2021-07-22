#include <iostream>
using namespace std;
#include <string>

struct student {
	string name;
	int age;
	int score;
} stu1;



int main8() {

	stu1.age = 18;
	stu1.name = "张三";
	stu1.score = 100;

	cout << "name=" << stu1.name << "age=" << stu1.age << "score=" << stu1.score << endl;

	student stu2;
	stu2.age = 20;
	stu2.name = "李四";
	stu2.score = 150;
	cout << "name=" << stu2.name << "age=" << stu2.age << "score=" << stu2.score << endl;

	system("pause");
	return 0;
}