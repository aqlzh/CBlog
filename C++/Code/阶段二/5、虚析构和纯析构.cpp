#include <iostream> 
using namespace std;


class Animal {
public :
	Animal() {
		cout << "Animal ���캯���ĵ���" << endl;
	}
	// ���麯��   --> ���������䣬�����Ϊ������
	virtual void Speak() = 0;
	 
	//��������
	//virtual ~Animal() = 0;

	~Animal() {
		cout << "Animal �鹹�����ĵ���" << endl;
	}
};


//Animal::~Animal() {
//	cout << "Animal �еĴ��������������ã�" << endl;
//}

class Cat : public Animal {
public :
	Cat(string name) {
		cout << "Cat �Ĺ��캯����ʹ��" << endl;
		m_Name = new string(name); // ʹָ��ά����ջ��
	}
	virtual void Speak() {
		cout << *m_Name << "Сè��˵��" << endl;  // ������
	}
	~Cat() {
		cout << "Cat �����������ĵ���" << endl;
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