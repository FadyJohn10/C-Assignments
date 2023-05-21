#ifndef MYSTACK_H
#define MYSTACK_H
#include <iostream>
using namespace std;

template <class T>
class MyStack{
private:
	int capacity;
	int num;
	T *arr;

public:
	MyStack();
	MyStack(int n);
	void push(T val);
	void pop();
	T top();
	int size();
	bool empty();
	~MyStack();
};

#endif