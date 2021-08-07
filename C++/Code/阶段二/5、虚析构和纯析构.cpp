#include <iostream> 
using namespace std;


class Animal {
public :
	Animal() {
		cout << "Animal 构造函数的调用" << endl;
	}
	// 纯虚函数   --> 当类中有其，则该类为抽象类
	virtual void Speak() = 0;
	 
	//纯虚析构
	//virtual ~Animal() = 0;

	~Animal() {
		cout << "Animal 虚构函数的调用" << endl;
	}
};


//Animal::~Animal() {
//	cout << "Animal 中的纯虚析构函数调用！" << endl;
//}

class Cat : public Animal {
public :
	Cat(string name) {
		cout << "Cat 的构造函数的使用" << endl;
		m_Name = new string(name); // 使指针维护堆栈区
	}
	virtual void Speak() {
		cout << *m_Name << "小猫在说话" << endl;  // 解析用
	}
	~Cat() {
		cout << "Cat 的析构函数的调用" << endl;
		if (this->m_Name != NULL) {
			delete m_Name;
			m_Name = NULL;
		}
	}
public :
	string* m_Name;
};

void test05() {
	Animal * animal = new Cat("Tom");
	animal->Speak();
	delete animal;
}
int main05() {
	// cout << "Hello" << endl;
	test05();
	system("pause");
	return 0;
}