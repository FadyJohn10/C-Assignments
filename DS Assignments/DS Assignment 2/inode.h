//============================================================================
// Name         : DS Assignment#2
// Author       : Mai Oudah
// Version      : 2.0
// Date Created : 01-04-2023
// Date Modified: 
// Description  : Virtual Filesystem - iNode class
//============================================================================

#ifndef INODE_H
#define INODE_H

#include <iostream>
#include <string>
#include <ctime>
#include "myvector.h" //create this header file where you define the vector class

using namespace std;


class Inode
{
	private:
		string fname; //inode name (filename or folder name)
		int size; //file/folder size
		string date; //creation date
		bool isFile; //capture the type; true if this is a file, false if this is a folder/directory
		Inode* parent; //the parent directory
		MyVector<Inode*> children; //the container of children, if this inode is a folder

	public:
		Inode(string name, int fSize, bool isFile, string date);
		string getName(){return fname;}
		bool isFolder(){return !isFile;}
		void setDate(string newDate);

		//add any other necessary code and methods here
		friend class Position;
		friend class VFS_Tree;

		MyVector<Inode*> getchi(){return children;}
};

#endif