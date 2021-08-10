#include <iostream>
using namespace std;

#include "person.hpp"

void test09() {
	Person<string, int> p("Tom", 10);
	p.showPerson();
}

int main09() {
	test09();
	system("pause");
	return 0;
}