#include <iostream>
using namespace std;

class Father {

public :
	int m_A;
protected :
	int m_B;
private :
	int m_C;
};

class Son :public Father {
public :
	int m_D;
};

int main03() {
	cout << "Size of Son = " << sizeof(Son) << endl;
	system("pause");
	return 0 ;
}