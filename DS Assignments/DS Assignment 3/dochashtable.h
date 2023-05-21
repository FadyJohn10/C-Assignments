//=================================================================================
// Name         : DS Assignment#3
// Author       : Mai Oudah
// Version      : 1.0
// Date Created : 25-April-2023
// Date Modified: 
// Description  : Word Count Wizard - Hash Table Class in C++ 
//=================================================================================

#ifndef DocHASHTABLE_H
#define DocHASHTABLE_H

#include<iostream>
#include <cmath>
#include <fstream>
// include additional header files as needed
#include "mylist.h"
#include "maxheap.h"

using namespace std;

class HashNode
{
    private:
        //add the attributes: key and value
        string key;
        int value;

    public:
        //define and implement the constructor
        HashNode(string k, int v);
        bool operator==(const HashNode& n) const;
        bool operator<(const HashNode& n) const;
        bool operator>(const HashNode& n) const;
        HashNode();
        string getKey();
        int getVal();
        friend class DocHASHTABLE;
};

//=============================================================================
class DocHASHTABLE
{
    private:
        MyList<HashNode>* buckets;      //an array of Buckets, include your own Linked List Class called MyList
        int size;                       //Current Size of HashTable
        int capacity;                   // The Capacity of HashTable
        // add more attributes as needed
        MaxHeap<HashNode> MyHeap;

    public:
        DocHASHTABLE();                     //constructor
        ~DocHASHTABLE();                    //destructor
        long hashCode(string key);          //use a hash function to generate a hash code for the provided key
        int import(string path);            //Load a TXT file to the HashTable
        void select_hashFun(int hashFunID); //choose one of the six implemented hash functions to construct the hash table      
        int count_collisions();             //return the number of collisions in the HashTable
        int count_unique_words();           //return the number of unique words in the laoded text
        int count_words();                  //return the total count of words in the laoded text
        int find_freq(string word);         //return the frequency of the provided word, if it exists. Otherwise, return zero.
        string find_max();                  //return the word with the highest frequency

        // add more methods as needed
        void fakeImport(string path);
        void clearTable();
};

#endif
