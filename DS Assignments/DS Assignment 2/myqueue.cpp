#include "myqueue.h"
#include "vfs_tree.h"

template<typename T> MyQueue<T>::MyQueue()
{
	capacity = 20;
	front = rear = size = 0;
	array = new T[capacity];
}
template<typename T> MyQueue<T>::~MyQueue()
{
	delete[] array;
}
template<typename T> void MyQueue<T>::enqueue(T element)
{
	if(isFull()){
		throw runtime_error("the queue is full");
	}else{
		array[rear] = element;
		size++;
		rear = (rear+1) % capacity;
	}
	
}
template<typename T> void MyQueue<T>::dequeue()
{
	if(isEmpty()){
		throw runtime_error("the queue is empty");
	}else{
		size--;
		front = (front+1) % capacity;
	}
}

template<typename T> int MyQueue<T>::getSize(){ return size;}

template<typename T> T MyQueue<T>::getFront(){ return array[front];}

template<typename T> bool MyQueue<T>::isEmpty()
{
	return size == 0;
}
template<typename T> bool MyQueue<T>::isFull()
{
	return size == capacity;
}

template class MyQueue<Inode*>;
template class MyQueue<Position*>;