#include <iostream>
using namespace std;
#include <string>
#include <deque>
#include <algorithm>

void printDeque(deque<int> &d) {
	for (deque<int>::iterator it = d.begin(); it != d.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}

void test18() {
	deque<int> d;
	d.push_back(10);
	d.push_back(20);
	d.push_back(30);
	d.push_front(40);
	d.push_front(50);


	printDeque(d);
	// ≈≈–Ú∫Û
	sort(d.begin(), d.end());
	printDeque(d);
}



int main14() {
	test18();
	system("pause");
	return 0;
}
