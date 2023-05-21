#include "mylist.h"
#include "dochashtable.h"

template <typename T>
MyList<T>::MyList() : head(NULL), size(0) {}

template <typename T>
bool MyList<T>::empty() const 
{
    return head == NULL;
}

template <typename T>
void MyList<T>::addFront(T value)
{  
    //create a node with the value and adjust pointers
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
    size++;
}

template <typename T>
void MyList<T>::removeFront()
{
    //captrue the node, adjust pointers, and delete it
    Node* oldHead = head;
    head = oldHead->next;
    delete oldHead;
    size--;
}

// a function to count the number of instances of an element in the list
template <typename T>
unsigned int MyList<T>::countElem(T value) const
{
    unsigned int counter = 0;
    Node* testptr = head;
    //loop through the list and compare data of current to value. if equal, increment counter. if not, continue.
    while(testptr != NULL){
        if(testptr->data == value){
            counter++;
        }
        testptr = testptr->next;
    }
    return counter;
}

// a function to get a node that has the same value
template <typename T>
T* MyList<T>::getSimilar(T value)
{
    Node* testptr = head;
    //loop through the list and compare data of current to value. if equal, return this node. 
    while(testptr != NULL){
        if(testptr->data == value){
            return &(testptr->data);
        }
        testptr = testptr->next;
    }
    return &(testptr->data);
}

template <typename T>
MyList<T>::~MyList(){
    // remove the front element until the list is empty
    while(!empty()){
        removeFront();
    }
}

template <typename T>
int MyList<T>::getSize(){return size;}

template class MyList<HashNode>;