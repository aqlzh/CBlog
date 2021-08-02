> - 我希望你没有刻意为追求一个数字而生活，我希望你找到了真正的价值所在
>- 你一定要坚持做自己，静下心来做自己喜欢的事，然后把自己交给命运

![在这里插入图片描述](https://img-blog.csdnimg.cn/d60cf89f793b46139ce87ca0fdeb8d28.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

@[toc]
# C++对象模型和this指针
## 成员变量和成员函数分开存储
- 在C++中，类内的==成员变量==和==成员函数==分开存储

只有非静态成员变量才属于类的对象上

```c
class Person {
public:
	Person() {
		mA = 0;
	}
	//非静态成员变量占对象空间
	int mA;
	//静态成员变量不占对象空间
	static int mB; 
	//函数也不占对象空间，所有函数共享一个函数实例
	void func() {
		cout << "mA:" << this->mA << endl;
	}
	//静态成员函数也不占对象空间
	static void sfunc() {
	}
};

  
int main() {

	cout << sizeof(Person) << endl;

	system("pause");

	return 0;
}
```

==注意==： 
- `空对象占用内存空间为：1`  ： 原因在于 C++编译器会给每个空对象也分配一个字节空间，是为了区分空对象占内存的位置，每个空对象也应该有一个独一无二的内存地址
- 非静态成员变量，属于类的对象上。静态成员变量、非静态成员函数、静态成员函数、不属于类的对象上

## this指针概念
- C++中成员变量和成员函数是分开存储的

- 每一个非静态成员函数只会诞生一份函数实例，也就是说多个同类型的对象会共用一块代码

那么问题是：这一块代码是如何区分那个对象调用自己的呢？


c++通过提供特殊的对象指针，this指针，解决上述问题。**this指针指向被调用的成员函数所属的对象**


> this指针是隐含每一个非静态成员函数内的一种指针
> 
> this指针不需要定义，直接使用即可

==this指针的用途==：

*  当形参和成员变量同名(`m_Age` 其中m代表member成员变量)时，可用this指针来区分
*  在类的非静态成员函数中返回对象本身，可使用`return *this`

```c
class Person
{
public:

	Person(int age)
	{
		//1、当形参和成员变量同名时，可用this指针来区分
		this->age = age;
	}

	Person& PersonAddPerson(Person p)
	{
		this->age += p.age;
		//返回对象本身
		return *this;
	}

	int age;
};

void test01()
{
	Person p1(10);
	cout << "p1.age = " << p1.age << endl;

	Person p2(10);
	p2.PersonAddPerson(p1).PersonAddPerson(p1).PersonAddPerson(p1);
	cout << "p2.age = " << p2.age << endl;
}

int main() {

	test01();

	system("pause");

	return 0;
}
```

==注意==：

```c
Person& PersonAddPerson(Person p)
{
	this->age += p.age;
	//返回对象本身
	return *this;
}
```
这里使用引用的方式（`Person &`）返回，如果用值的方式(`Person`)返回，则会构造一个新的对象，根据拷贝函数
## 空指针访问成员函数
<font color=skyblue >C++中空指针也是可以调用成员函数的</font>，但是也要注意有没有用到this指针

- 如果用到this指针，需要加以判断保证代码的健壮性 `if (this == NULL) {	return;  }`  

- 再者深究原因，其实`cout << mAge << endl;`  的mAge 为`this->mAge` ,空指针调用肯定报错
**示例：**
```c
//空指针访问成员函数
class Person {
public:

	void ShowClassName() {
		cout << "我是Person类!" << endl;
	}

	void ShowPerson() {
		if (this == NULL) {
			return;
		}
		cout << mAge << endl;
	}

public:
	int mAge;
};

void test01()
{
	Person * p = NULL;
	p->ShowClassName(); //空指针，可以调用成员函数
	p->ShowPerson();  //但是如果成员函数中用到了this指针，就不可以了
}

int main() {

	test01();

	system("pause");

	return 0;
}
```

##  const修饰成员函数

**常函数：**

* 成员函数后加const后我们称为这个函数为**常函数**
* 常函数内不可以修改成员属性
* 成员属性声明时加关键字mutable后，在常函数中依然可以修改

**常对象：**

* 声明对象前加const称该对象为常对象
* 常对象只能调用常函数

**示例：**
```c
class Person {
public:
	Person() {
		m_A = 0;
		m_B = 0;
	}

	//this指针的本质是一个指针常量，指针的指向不可修改
	//如果想让指针指向的值也不可以修改，需要声明常函数
	void ShowPerson() const {
		//const Type* const pointer;
		//this = NULL; //不能修改指针的指向 Person* const this;
		//this->mA = 100; //但是this指针指向的对象的数据是可以修改的

		//const修饰成员函数，表示指针指向的内存空间的数据不能修改，除了mutable修饰的变量
		this->m_B = 100;
	}

	void MyFunc() const {
		//mA = 10000;
	}

public:
	int m_A;
	mutable int m_B; //可修改 可变的
};


//const修饰对象  常对象
void test01() {

	const Person person; //常量对象  
	cout << person.m_A << endl;
	//person.mA = 100; //常对象不能修改成员变量的值,但是可以访问
	person.m_B = 100; //但是常对象可以修改mutable修饰成员变量

	//常对象访问成员函数
	person.MyFunc(); //常对象不能调用const的函数

}

int main() {

	test01();

	system("pause");

	return 0;
}
```

<font color=red>**注意**</font>：
- this指针的本质是==指针常量==，指针的指向不可以更改  `Person  * const this` 

- 在成员函数后面加 const,修饰的是this指向如 `void showPerson() const {}` ，让指针指向的值也不可以修改 其本质为  `const Person * const this` 
- 特殊变量，即使在常函数中，也可以修改这个值，加上关键字 `mutable`


# 友元
- 在程序里，有些私有属性 也想让类外特殊的一些函数或者类进行访问，就需要用到友元的技术

- 友元的目的就是让一个函数或者类 访问另一个类中私有成员

友元的关键字为  ==friend==

<font color=red>**友元的三种实现**</font>

* 全局函数做友元
* 类做友元
* 成员函数做友元


## 全局函数做友元

```c
class Building
{
	//告诉编译器 goodGay全局函数 是 Building类的好朋友，可以访问类中的私有内容
	friend void goodGay(Building * building);

public:

	Building()
	{
		this->m_SittingRoom = "客厅";
		this->m_BedRoom = "卧室";
	}


public:
	string m_SittingRoom; //客厅

private:
	string m_BedRoom; //卧室
};


void goodGay(Building * building)
{
	cout << "好基友正在访问： " << building->m_SittingRoom << endl;
	cout << "好基友正在访问： " << building->m_BedRoom << endl;
}


void test01()
{
	Building b;
	goodGay(&b);
}

int main(){

	test01();

	system("pause");
	return 0;
}
```

## 类做友元

```c
class Building;
class goodGay
{
public:

	goodGay();
	void visit();

private:
	Building *building;
};


class Building
{
	//告诉编译器 goodGay类是Building类的好朋友，可以访问到Building类中私有内容
	friend class goodGay;

public:
	Building();

public:
	string m_SittingRoom; //客厅
private:
	string m_BedRoom;//卧室
};

Building::Building()
{
	this->m_SittingRoom = "客厅";
	this->m_BedRoom = "卧室";
}

goodGay::goodGay()
{
	building = new Building;
}

void goodGay::visit()
{
	cout << "好基友正在访问" << building->m_SittingRoom << endl;
	cout << "好基友正在访问" << building->m_BedRoom << endl;
}

void test01()
{
	goodGay gg;
	gg.visit();

}

int main(){

	test01();

	system("pause");
	return 0;
}
```

## 成员函数做友元
```c
class Building;
class goodGay
{
public:

	goodGay();
	void visit(); //只让visit函数作为Building的好朋友，可以发访问Building中私有内容
	void visit2(); 

private:
	Building *building;
};


class Building
{
	//告诉编译器  goodGay类中的visit成员函数 是Building好朋友，可以访问私有内容
	friend void goodGay::visit();

public:
	Building();

public:
	string m_SittingRoom; //客厅
private:
	string m_BedRoom;//卧室
};

Building::Building()
{
	this->m_SittingRoom = "客厅";
	this->m_BedRoom = "卧室";
}

goodGay::goodGay()
{
	building = new Building;
}

void goodGay::visit()
{
	cout << "好基友正在访问" << building->m_SittingRoom << endl;
	cout << "好基友正在访问" << building->m_BedRoom << endl;
}

void goodGay::visit2()
{
	cout << "好基友正在访问" << building->m_SittingRoom << endl;
	//cout << "好基友正在访问" << building->m_BedRoom << endl;
}

void test01()
{
	goodGay  gg;
	gg.visit();

}

int main(){
    
	test01();

	system("pause");
	return 0;
}
```






