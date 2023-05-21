#ifndef MYVECTOR_H
#define MYVECTOR_H
#include <iostream>

using namespace std;

template<typename T>
class MyVector {
	private:
		T* arr;
		int size;
		int capacity;
		void resize();

	public:
	    MyVector();
	    MyVector(int initialSize);
	    ~MyVector();
	    void pushBack(T item);
	    void popBack();
	    void erase(int index);
	    T& operator[](int index);
	    int getSize() const;
	    bool isEmpty();
	    friend class Inode;
};

#endif