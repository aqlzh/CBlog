#pragma once 
#include <iostream>
using namespace std;
#include <string>

template <class T>
class MyArray {
public :

	// 构造函数
	MyArray(int capacity) {
		this->m_Capacity = capacity;
		this->m_Size = 0;
		pAddress = new T[this->m_Capacity];
	}

	// 拷贝构造
	//  const  的作用在于 防止误操作
	MyArray(const MyArray &arr) {
		this->m_Capacity = arr.m_Capacity;
		this->m_Size = arr.m_Size;
		// this->pAddress = arr.pAddress;   这里不能直接这样操作(这是指针，普通则可以)   浅拷贝
		this->pAddress = new T[this->m_Capacity];

		for (int i = 0; i < this->m_Size; i++) {
			this->pAddress[i] = arr.pAddress[i];
		}
	}


	// 重载  =     防止浅拷贝的问题
	MyArray& operator=(const MyArray& myarray) {
		//  判断原来堆区是否有数据，有则释放数据
		if (this->pAddress != NULL) {
			delete[] this->pAddress;
			this->m_Size = 0;
			this->m_Capacity = 0;
		}

		this->m_Capacity = myarray.m_Capacity;
		this->m_Size = myarray.m_Size;
		this->pAddress = new T[this->m_Capacity];

		for (int i = 0; i < this->m_Size; i++) {
			this->pAddress[i] = myarray.pAddress[i];
		}
		return *this;
	}

// 重载 []  
	T& operator[](int index) {
		return this->pAddress[index];
}

// 尾插法
	void Push_back(const T& val) {
		if (this->m_Capacity == this->m_Size) {
			return;
		}
		this->pAddress[this->m_Size] = val;
		this->m_Size++ ;
}

// 尾删法
	void Pop_back() {
		if (this->m_Size == 0) return;
		this->m_Size--;
	}

	int getCapacity() {
		return this->m_Capacity;
	}
	int getSize() {
		return this->m_Size;
	}


	~MyArray() {
		if (this->pAddress != NULL) {
			delete[] this->pAddress;
			this->pAddress = NULL;
			this->m_Capacity = 0;
			this->m_Size = 0;
		}
	}
private :
	T* pAddress;  // 指向一个堆空间 ，存储真正的数据
	int m_Capacity ; 
	int m_Size;
};