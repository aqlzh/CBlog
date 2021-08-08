#include <iostream>
using namespace std ;

/*
ѡ������
*/
template<class T>
void mySwap(T &a, T &b) {
	T temp = a;
	a = b;
	b = temp;
}


template <class T>
void mySort(T arr[], int len) {
	for (int i = 0; i < len; i++) {
		int max = i;  // �϶����ֵΪ��һ����  ע�����ֵ����±�
		for (int j = i + 1; j < len; j++) {
			if (arr[max] < arr[j]) {
				max = j;   // �����±�
			}
		}
		if (max != i) {    // ����Max �� i ���±�Ԫ�� 
			mySwap(arr[max], arr[i]);
		}
	}
}

template<class T>
void myPrint(T arr[],int  len) {
	for (int i = 0; i < len; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}


void test06() {
	char charArr[] = "badcfe";
	int len = sizeof(charArr) / sizeof(char);
	mySort(charArr, len);
	myPrint(charArr, len);

}


void test07() {
	int  Arr[] = {3,4,7,1,5};
	int len = sizeof(Arr) / sizeof(Arr[0]);
	mySort(Arr, len);
	myPrint(Arr, len);
}
int main() {
	test06();
	test07();
	system("pause");
	return 0;
}
