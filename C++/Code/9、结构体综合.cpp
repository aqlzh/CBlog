#include <iostream>
using namespace std;
#include <iostream>

/// <summary>
///  结构体指针  结构体数组
/// </summary>

struct student {
	string name;
	int age;
	int score;

};

int main() {

	student arr[2] = {
		{"渡边曜",18,100},
		{"花阳",16,99}
	};

	arr[1].name = "小泉花阳";
	int  len = sizeof(arr) / sizeof(arr[0]);
 
	student * p = &arr[1];
	for (int i = 0; i < len; i++) {
		cout << arr[i].name << " " << arr[i].age<<" " << arr[i].score << endl;
		cout << p->name << endl;
	}

}