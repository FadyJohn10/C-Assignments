//============================================================================
// Name         : DS Assignment#2
// Author       : Mai Oudah
// Version      : 2.0
// Date Created : 07-04-2023
// Date Modified: 
// Description  : Virtual Filesystem - Tree class
//============================================================================

#ifndef VFS_TREE_H
#define VFS_TREE_H

#include<iostream>
#include<string>
#include <ctime>
#include "inode.h"
#include "myvector.h" //create this header file where you define the vector class
#include "mystack.h" //create this header file where you define the stack class
#include "myqueue.h" //create this header file where you define the queue class

using namespace std;

class Position
{
	private:
		Inode* inode;
		Position(Inode* inode);
		
	public:
		~Position();
		Position();
		Position parent() const;
		bool isRoot() const;
    	bool isExternal() const;
		MyVector<Position*> childrenPositions () const;

		//add any other necessary code here
		friend class VFS_Tree;
		Inode* getNode(){return inode;}
};

//=============================================================================
class VFS_Tree
{
	private:
		Position* _root;  //the root inode
		Position* currentNode;  //the current inode
		int n; //number of inodes in the tree
		MyQueue<Position*> bin; // the bin queue to store removed inodes
        Position* prevPos;

	public:
		VFS_Tree(); 
		~VFS_Tree(); 
		
        bool empty() const; // check if the tree is empty
        Position* root() const; // returns the position to the root inode
        Position* current() const; // returns the position to the current inode

        Position* find(string name) const; 
        void touch(string filename, int size); 
        void mkdir(string foldername); 
        void ls(); 
		void lsSort(); 
		void cd(string arg); 
        void realpath(string name) const; 
        string pwd(Position* current) const; 
        void mv(string filename, string foldername); 
        void rm(string name); 
        void emptyBin(); 
        void showBin(); 
        void recover(); 
        
		//add any other necessary code and additional supporting methods here to achieve the capabilities of the system
        int getSize(string name);
        void exportVFS();
        void importVFS();
        void mvPath(string filepath, string folderpath);
        void rmPath(string name);

};

#endif