#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>


class MyCompare {
public:
	// 重载 （）
	bool operator()(int num1, int num2) {
		return num1 > num2;
	}
};

void test26() {
	vector<int> v;
	v.push_back(10);
	v.push_back(30);
	v.push_back(20);
	v.push_back(5);

	// 默认从小到大 排序
	sort(v.begin(), v.end());
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;

	cout << "使用对象函数改变排序策略" << endl;
	sort(v.begin(), v.end(),MyCompare());
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}


int main21() {
	test26();
	system("pause");
	return 0;
}

