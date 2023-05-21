//============================================================================
// Name         : DS Assignment#1
// Author       : Mai Oudah
// Version      : 1.0
// Date Created : 14-02-2023
// Date Modified: 
// Description  : Linked List-based Matrix class for an optimized structure
//============================================================================

#ifndef LINKEDMATRIX_H
#define LINKEDMATRIX_H
#include <iostream>
using namespace std;

class Node
{
	private:
		int row; //the row index
		int column; //the column index
		int value; //the value of the element
		Node* next; //pointer to the next node within the same row
		Node* down; //pointer to the next node within the same column
		friend class LinkedMatrix;
		
	public:
		Node();
		Node(int row, int column, int value);

	//add any other necessary code here
};
//=============================================================================
class LinkedMatrix
{
	private:
		int numRows; //the number of rows
		int numCols; //the number of columns
		Node* rowArray;
		Node* colArray;
		static int MatsNum;
		char ID;

	public:
		LinkedMatrix (); // empty matrix constructor
		void create(int numRows, int numCols); // creates an empty matrix given the provided dimensions
		int getNumRows() const; // returns the total number of rows
		int getNumCols() const; // returns the total number of columns
		void display_mat() const; // display the matrix dimensions, number of non-zero members, and the non-zero members' cardinalities+values
		void insertElement(int Row_Indx, int Col_Indx, int value);
		void removeElement(int Row_Indx, int Col_Indx);
		~LinkedMatrix(); // destructor to properly delete the matrix and deallocate all nodes
	
		//add any other necessary code here
		int getElement(int Row_Indx, int Col_Indx) const;
		char getID() const;

};

#endif