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
	cout << "������һ������" << endl;
//	cin >> score >> endl;
	cin >> score;


	// if else  ��������
	if (score > 600) {
		cout << "�ҿ����˺ô�ѧ" << endl;
	}
	else {
		cout << "�ҿ����˾���ɽ��ѧ" << endl;
	}

	cout << str << endl;
	cout << a+b << week<<endl;
	cout << str+"\t"<< a << endl;
	cout << str+str+ + "\t" << a << endl;
	cout << flag << endl;  // ���Ϊ 1


    // while  ѭ����������
	int num = 0;

	while (num < 5) {
		cout << "num =" << num << endl;
		num++;
	}


	system("pause"); 
	return 0;
}