#include "mystack.h"
#include "vfs_tree.h"

template <class T> MyStack<T>::MyStack()
{
	capacity = 20;
	arr = new T[20];
	num = 0;
}

template <class T> MyStack<T>::MyStack(int n)
{
	capacity = n;
	arr = new T[n];
	num = 0;
}

template <class T> MyStack<T>::~MyStack()
{
	delete[] arr;
}


template <class T> void MyStack<T>::push(T val)
{
	if(num == capacity)
		throw runtime_error("the stack is full");
	arr[num] = val;
	num++;
}

template <class T> void MyStack<T>::pop()
{
	if(empty())
		throw runtime_error("the stack is empty");
	num--;
}

template <class T> T MyStack<T>::top()
{
	if(empty())
		throw runtime_error("the stack is empty");
	return arr[num-1];
}

template <class T> int MyStack<T>::size(){return num;}

template <class T> bool MyStack<T>::empty(){return num == 0;}

template class MyStack<Position*>;
template class MyStack<Inode*>;