#include <iostream>
using namespace std;
#include <map>
#include <string>;

void printMap(map<int, int> &m) {
	for (map<int, int>::iterator it = m.begin(); it != m.end(); it++) {
		cout << "key=  " << (*it).first << "value= " << (*it).second << " ";
	}
	cout << endl;
}


void test23() {
	map<int, int> m;
	m.insert(pair<int, int>(1, 10));
	m.insert(pair<int, int>(2, 20));
	m.insert(pair<int, int>(3, 30));


	printMap(m);
}

int main() {
	test23();
	system("pause");
	return 0;
}