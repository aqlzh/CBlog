#include <iostream>
using namespace std;

int main4() {


	// 单重 for 循环
	for (int i = 0; i < 10; i++) {
		if (i == 5) break;
		cout << i << endl;
	}

	// 双重for 循环
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (j == 5) break;
			cout << i << " ";
		}

		// 以下单纯就是换行
		cout << endl;
	}

	system("pause");
	return 0;
}
