#include <iostream>
using namespace std;
#include <set> 


void test21() {

	cout << "set ����" << endl;
	set<int> s;
	pair<set<int>::iterator, bool> ret = s.insert(10);
	s.insert(20);
	s.insert(30);

	if (ret.second) {
		cout << "��һ�β���ɹ�" << endl;
	}
	else {
		cout << "��һ�β���ʧ��" << endl;
	}

	ret = s.insert(10);
	if (ret.second) {
		cout << "�ڶ��β���ɹ�" << endl;
	}
	else {
		cout << "�ڶ��β���ʧ��" << endl;
	}

	cout << endl;
	cout << "set find ����" << endl;
    // find  ���ص�����
	set<int>::iterator pos = s.find(20);
	
	if (pos != s.end()) {
		cout << "�ҵ���Ԫ�� " << *pos << endl;
	}
	else {
		cout << "û�ҵ�Ԫ��" << endl;
	}

	cout << "multiset ����" << endl;
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