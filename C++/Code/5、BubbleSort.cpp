#include <iostream>
using namespace std;

int main5() {
	int arr1[9] = { 4,2,8,0,5,7,1,3,9 };

	for (int i = 0; i < 9 - 1; i++) {
		for (int j = 0; j < 9 - 1; j++) {
			if (arr1[j] > arr1[j + 1]) {
				int temp = arr1[j];
				arr1[j] = arr1[j + 1];
				arr1[j + 1] = temp;
			}
		}
	}
	for (int i = 0; i < 9; i++) {
		cout << arr1[i] <<" ";
	}

   // �鿴��ά����֪ʶ��
	cout << "��ά�������" << endl;

	int arr[2][3] =
	{
		{1,2,3},
		{4,5,6}
	};

	cout << "��ά�����С�� " << sizeof(arr) << endl;
	cout << "��ά����һ�д�С�� " << sizeof(arr[0]) << endl;
	cout << "��ά����Ԫ�ش�С�� " << sizeof(arr[0][0]) << endl;

	cout << "��ά���������� " << sizeof(arr) / sizeof(arr[0]) << endl;
	cout << "��ά���������� " << sizeof(arr[0]) / sizeof(arr[0][0]) << endl;

	//��ַ
	cout << "��ά�����׵�ַ��" << arr << endl;
	cout << "��ά�����һ�е�ַ��" << arr[0] << endl;
	cout << "��ά����ڶ��е�ַ��" << arr[1] << endl;

	cout << "��ά�����һ��Ԫ�ص�ַ��" << &arr[0][0] << endl;
	cout << "��ά����ڶ���Ԫ�ص�ַ��" << &arr[0][1] << endl;

	system("pause");
	return 0;

}