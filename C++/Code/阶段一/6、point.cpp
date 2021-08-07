#include <iostream>
using namespace std;

int main6() {
	int a = 10;
	int* p = &a;
	cout << *p << endl;    // ½âÒıÓÃ
	cout << "sizeof(int *) = " << sizeof(int*) << endl;
	system("pause");
	return 0;
}