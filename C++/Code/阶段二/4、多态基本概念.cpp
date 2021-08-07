#include <iostream>
using namespace std ;

class Animal {
public :
	Animal() {
		cout << "Animal 的构造函数" << endl;
	}

	virtual void speak() {
		cout << "动物在叫" << endl;
	}

};

class Cat: public Animal {
public :
	void speak() {
		cout << "猫在叫" << endl;
	}
};

// 多态
void doSpeak(Animal & animal) {
	animal.speak();
}

void test04(){
	Cat cat;
	cat.speak();    // 注意: 两者区别
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