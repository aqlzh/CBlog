#include <iostream>
using namespace std;

int main4() {


	// ���� for ѭ��
	for (int i = 0; i < 10; i++) {
		if (i == 5) break;
		cout << i << endl;
	}

	// ˫��for ѭ��
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (j == 5) break;
			cout << i << " ";
		}

		// ���µ������ǻ���
		cout << endl;
	}

	system("pause");
	return 0;
}
