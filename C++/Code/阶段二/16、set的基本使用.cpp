#include <iostream>
using namespace std;
#include <set> 


void test21() {

	cout << "set 测试" << endl;
	set<int> s;
	pair<set<int>::iterator, bool> ret = s.insert(10);
	s.insert(20);
	s.insert(30);

	if (ret.second) {
		cout << "第一次插入成功" << endl;
	}
	else {
		cout << "第一次插入失败" << endl;
	}

	ret = s.insert(10);
	if (ret.second) {
		cout << "第二次插入成功" << endl;
	}
	else {
		cout << "第二次插入失败" << endl;
	}

	cout << endl;
	cout << "set find 查找" << endl;
    // find  返回迭代器
	set<int>::iterator pos = s.find(20);
	
	if (pos != s.end()) {
		cout << "找到了元素 " << *pos << endl;
	}
	else {
		cout << "没找到元素" << endl;
	}

	cout << "multiset 测试" << endl;
	multiset<int> ms;
	ms.insert(10);
	ms.insert(10);

	for (multiset<int>::iterator it = ms.begin(); it != ms.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;


}

int main() {
	test21();
	system("pause");
	return 0;

}