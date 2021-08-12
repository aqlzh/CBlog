#include <iostream>
using namespace std;
#include <list>

void printFun(list<int>& L) {
	for (list<int>::iterator it = L.begin(); it != L.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;

}

bool myCompare(int val1, int val2) {
	return val1 > val2;   // ½µÐò  
}

void test20() {
	list<int> L;

	L.push_back(10);
	L.push_back(20);
	L.push_back(30);


	// 10 20 30
	printFun(L);
	L.push_front(5);
	// 5 10 20 30
	printFun(L);

	list<int>::iterator pos = L.begin();
	L.insert(++pos,100);
	// 5 100 10 20 30
	printFun(L);


	cout << "·´×ª" << endl;
	L.reverse();
	// 30 20 10 100 5
	printFun(L);

	cout << "½µÐò" << endl;
	L.sort(myCompare);
	printFun(L);

}

int main16() {
	
	test20();
	system("pause");
	return 0;
 
}