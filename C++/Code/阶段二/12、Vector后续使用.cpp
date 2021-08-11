#include <iostream>
using namespace std;
#include <vector>
#include <string>

void printVector(vector<int>& v) {
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << *it << endl;
	}
}

void test16() {
	vector<int> v;

	// Ô¤Áô¿Õ¼ä
	//v.reserve(100000);
	
	int num = 0;
	int* p = NULL; //vector  À©ÈÝÊ±µÄÍ·Ö¸Õë
	for (int i = 0; i < 100000; i++) {
		v.push_back(i);
		if (p != &v[0]) {
			p = &v[0];
			num++;
		}
	}
	cout << "num = " << num << endl;

}

void test17() {
	vector<int> v2;

	v2.push_back(19);
	v2.push_back(29);
	v2.push_back(39);

	printVector(v2);

	// Î²É¾
	cout << "== Î²É¾===" << endl;
	v2.pop_back();
	printVector(v2);
	

	//²åÈë
	cout << "==²åÈë===" << endl;
	v2.insert(v2.begin(), 2, 1111);
	printVector(v2);
	

	// É¾³ý
	cout << "==É¾³ý===" << endl;
	v2.erase(v2.begin(), v2.end());
	printVector(v2);
	
}

int main() {
	test16();
	cout << "======" << endl;
	test17();
	system("pause");
	return 0;

}
