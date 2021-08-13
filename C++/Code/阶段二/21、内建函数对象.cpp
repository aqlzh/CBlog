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


	// 将 v 容器搬运到  容器v2  中
	vector<bool> v2;
	// 首先在搬运前 resize   确定v2  容器大小 否则不能搬运

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
