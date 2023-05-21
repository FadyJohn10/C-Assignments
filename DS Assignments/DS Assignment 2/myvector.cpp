#include "myvector.h"
#include "vfs_tree.h"
#include <fstream>

template<typename T>
MyVector<T>::MyVector() {
arr = new T[1];
size = 0;
capacity = 1;
}

template<typename T>
MyVector<T>::MyVector(int initialSize) {
arr = new T[initialSize];
size = 0;
capacity = initialSize;
}

template<typename T>
MyVector<T>::~MyVector() {
// delete[] arr;
}

template<typename T>
void MyVector<T>::pushBack(T item) {
if (size == capacity) {
resize();
}
arr[size] = item;
size++;
}

template<typename T>
void MyVector<T>::popBack() {
size--;
}

template <typename T>
void MyVector<T>::erase(int index)
{
	for (int i = index; i < size-1; i++){
		arr[i] = arr[i+1];
	}
	size--;
}

template<typename T>
T& MyVector<T>::operator[](int index){
return arr[index];
}

template<typename T>
int MyVector<T>::getSize() const {
return size;
}

template<typename T>
bool MyVector<T>::isEmpty(){
return size == 0;
}

template<typename T>
void MyVector<T>::resize() {
    T* newArr = new T[capacity * 2];
    for (int i = 0; i < size; i++) {
        newArr[i] = arr[i];
    }
    capacity *= 2; // update capacity before deleting the old array
    delete[] arr;
    arr = newArr;
}
template class MyVector<string>;
template class MyVector<Inode*>;
template class MyVector<Position*>;

