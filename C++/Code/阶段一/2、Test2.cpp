#include<iostream>
using namespace std;
/*
2.8 ���ݵ�����
���ã����ڴӼ��̻�ȡ����
�ؼ��֣�cin

�﷨��cin >> ����
*/


int main2() {

	//��������
	int a = 0;
	cout << "���������ͱ�����" << endl;
	cin >> a;
	cout << a << endl;

	//����������
	double d = 0;
	cout << "�����븡���ͱ�����" << endl;
	cin >> d;
	cout << d << endl;

	//�ַ�������
	char ch = 0;
	cout << "�������ַ��ͱ�����" << endl;
	cin >> ch;
	cout << ch << endl;

	//�ַ���������
	string str;
	cout << "�������ַ����ͱ�����" << endl;
	cin >> str;
	cout << str << endl;

	//������������
	bool flag = true;
	cout << "�����벼���ͱ�����" << endl;
	cin >> flag;
	cout << flag << endl;
	return 0;
}

