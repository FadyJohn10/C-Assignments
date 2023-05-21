#ifndef MAXHEAP_H
#define MAXHEAP_H
#include <iostream>

template <typename T>
class MaxHeap
{
private:
    T* array;
    int capacity;
    int size;

public:
    MaxHeap(int capacity  = 1);
    ~MaxHeap();
    void insert(const T& key);
    T removeMax();
    T getMax();
    int parent(int k);
    int left(int k);
    int right(int k);
    void siftUp(int k);
    void siftDown(int k);
    int getSize();

private:
    void adjustSize();
};

#endif