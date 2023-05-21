#include "maxheap.h"
#include "dochashtable.h"

template <typename T>
void MaxHeap<T>::adjustSize()
{
    if(this->size == this->capacity) //check if the heap is full
    {
        // create a new array of double the size and copy the old array elements into it
        T *newArray = new T[capacity*2];
        for(int i=0; i<capacity; i++)
            newArray[i] = array[i];
        delete[] array;
        array = newArray;
        capacity = capacity*2;  
    }
}

template <typename T>
MaxHeap<T>::MaxHeap(int capacity)
{
    this->capacity = capacity;
    size = 1;
    array = new T[capacity];
}

template <typename T>
MaxHeap<T>::~MaxHeap()
{
    delete[] array;
}

template <typename T>
void MaxHeap<T>::insert(const T& key)
{
    if (size == capacity) //check if the heap is full
    {
        adjustSize();
    }
    array[size++] = key;
    siftUp(size - 1);
}

template <typename T>
T MaxHeap<T>::removeMax()
{
    if (size == 1) //check if the heap is empty
    {
        throw std::out_of_range("The heap is empty");
    }
    else
    {
        T root = array[1];
        array[1] = array[--size];
        siftDown(1);
        return root;
    }
}

template <typename T>
T MaxHeap<T>::getMax()
{
    if (size == 1) //check if the heap is empty
    {
        throw std::out_of_range("The heap is empty");
    }
    return array[1];
}

template <typename T>
int MaxHeap<T>::parent(int k)
{
    return k / 2;
}

template <typename T>
int MaxHeap<T>::left(int k)
{
    return (2 * k);
}

template <typename T>
int MaxHeap<T>::right(int k)
{
    return (2 * k + 1);
}

template <typename T>
void MaxHeap<T>::siftUp(int k)
{
    int id = k;
    // while parent is less than child and root is not reached, swap them
    while (id > 1 && array[parent(id)] < array[id])
    {
        T temp = array[id];
        array[id] = array[parent(id)];
        array[parent(id)] = temp;
        id = parent(id);
    }
}

template <typename T>
void MaxHeap<T>::siftDown(int k)
{
    int largest = k;

    // Check if the left child is larger than the current element
    if (left(k) < size && array[left(k)] > array[largest])
    {
        largest = left(k);
    }
    // Check if the right child is larger than the current element
    if (right(k) < size && array[right(k)] > array[largest])
    {
        largest = right(k);
    }
    // If the largest element is not the current element, swap them and recursively sift down the swapped child
    if (largest != k)
    {
        T temp = array[k];
        array[k] = array[largest];
        array[largest] = temp;
        siftDown(largest);
    }
}

template <typename T>
int MaxHeap<T>::getSize()
{
    return size;
}

template class MaxHeap<HashNode>;