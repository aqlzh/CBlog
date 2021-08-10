#pragma once 
#include <iostream>
using namespace std;
#include <string>

template <class T>
class MyArray {
public :

	// ���캯��
	MyArray(int capacity) {
		this->m_Capacity = capacity;
		this->m_Size = 0;
		pAddress = new T[this->m_Capacity];
	}

	// ��������
	//  const  ���������� ��ֹ�����
	MyArray(const MyArray &arr) {
		this->m_Capacity = arr.m_Capacity;
		this->m_Size = arr.m_Size;
		// this->pAddress = arr.pAddress;   ���ﲻ��ֱ����������(����ָ�룬��ͨ�����)   ǳ����
		this->pAddress = new T[this->m_Capacity];

		for (int i = 0; i < this->m_Size; i++) {
			this->pAddress[i] = arr.pAddress[i];
		}
	}


	// ����  =     ��ֹǳ����������
	MyArray& operator=(const MyArray& myarray) {
		//  �ж�ԭ�������Ƿ������ݣ������ͷ�����
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

// ���� []  
	T& operator[](int index) {
		return this->pAddress[index];
}

// β�巨
	void Push_back(const T& val) {
		if (this->m_Capacity == this->m_Size) {
			return;
		}
		this->pAddress[this->m_Size] = val;
		this->m_Size++ ;
}

// βɾ��
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
	T* pAddress;  // ָ��һ���ѿռ� ���洢����������
	int m_Capacity ; 
	int m_Size;
};