#include <iostream>
#include <string>
using namespace std;

int main3() {
	string str = "LZH";
	int a = 10;
	int b = 15;
	const int week = 7;
	bool flag = true;
	int score = 0;
	cout << "请输入一个分数" << endl;
//	cin >> score >> endl;
	cin >> score;


	// if else  语句的运用
	if (score > 600) {
		cout << "我考上了好大学" << endl;
	}
	else {
		cout << "我考上了井冈山大学" << endl;
	}

	cout << str << endl;
	cout << a+b << week<<endl;
	cout << str+"\t"<< a << endl;
	cout << str+str+ + "\t" << a << endl;
	cout << flag << endl;  // 输出为 1


    // while  循环语句的运用
	int num = 0;

	while (num < 5) {
		cout << "num =" << num << endl;
		num++;
	}


	system("pause"); 
	return 0;
}