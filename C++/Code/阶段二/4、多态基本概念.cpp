#include <iostream>
using namespace std ;

class Animal {
public :
	Animal() {
		cout << "Animal �Ĺ��캯��" << endl;
	}

	virtual void speak() {
		cout << "�����ڽ�" << endl;
	}

};

class Cat: public Animal {
public :
	void speak() {
		cout << "è�ڽ�" << endl;
	}
};

// ��̬
void doSpeak(Animal & animal) {
	animal.speak();
}

void test04(){
	Cat cat;
	cat.speak();    // ע��: ��������
	doSpeak(cat);

	cout << "=======" << endl;

	Animal* aniaml = new Cat();
	aniaml->speak();
}

int main() {

	test04();
	system("pause");
	return 0;
}