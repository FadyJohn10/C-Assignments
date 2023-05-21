#ifndef MYQUEUE_H
#define MYQUEUE_H
#include <iostream>
using namespace std;

template <typename T>
class MyQueue
{
	private:
		T *array;
		int capacity;
		int size;
		int front;
		int rear;
	public:
		MyQueue();
		~MyQueue();
		void enqueue(T); 
		void dequeue();
		int getSize();
		T getFront();
		bool isEmpty();
		bool isFull();
};

#endif