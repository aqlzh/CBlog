#include <iostream>
using namespace std;
#include <iostream>

/// <summary>
///  �ṹ��ָ��  �ṹ������
/// </summary>

struct student {
	string name;
	int age;
	int score;

};

int main() {

	student arr[2] = {
		{"�ɱ���",18,100},
		{"����",16,99}
	};

	arr[1].name = "СȪ����";
	int  len = sizeof(arr) / sizeof(arr[0]);
 
	student * p = &arr[1];
	for (int i = 0; i < len; i++) {
		cout << arr[i].name << " " << arr[i].age<<" " << arr[i].score << endl;
		cout << p->name << endl;
	}

}