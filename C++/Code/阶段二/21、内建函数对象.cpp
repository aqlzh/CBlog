#include <iostream>
using namespace std;
#include <functional>
#include <vector>
#include <algorithm>

void test27() {
	vector<bool> v;
	v.push_back(true);
	v.push_back(false);
	v.push_back(true);
	v.push_back(false);

	for (vector<bool>::iterator it = v.begin(); it != v.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;


	// �� v �������˵�  ����v2  ��
	vector<bool> v2;
	// �����ڰ���ǰ resize   ȷ��v2  ������С �����ܰ���

	v2.resize(v.size());
	transform(v.begin(), v.end(), v2.begin(), logical_not<bool>());
	for (vector<bool>::iterator it = v2.begin(); it != v2.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;

}

int main() {
	test27();
	system("pause");
	return 0;
}
