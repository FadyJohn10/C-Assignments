#ifndef MYLIST_H
#define MYLIST_H
#include <iostream>

template <typename T>
class MyList {
    private:
        
        class Node {
        public:
            T data;
            Node* next;
            Node(T value) : data(value), next(NULL) {}
        };

        Node* head;
        int size;

    public:
        MyList();
        bool empty() const;
        void addFront(T value); 
        void removeFront();
        unsigned int countElem(T value) const; 
        int getSize();
        ~MyList();
        T* getSimilar(T value);
    };

#endif
