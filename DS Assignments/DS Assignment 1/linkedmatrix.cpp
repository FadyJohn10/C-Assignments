#include "linkedmatrix.h"
#include <fstream>

Node::Node() : value(0), next(NULL), down(NULL){} // node default constructor
Node::Node(int row, int column, int value) : row(row), column(column), value(value), next(NULL), down(NULL){} // node non-default constructor

int LinkedMatrix::MatsNum = 0;
// linked matrix default consructor
LinkedMatrix::LinkedMatrix() : numRows(0), numCols(0), rowArray(NULL), colArray(NULL)
{
    ID = 'A' + MatsNum-1;
    MatsNum++;
} 


void LinkedMatrix::create(int numRows, int numCols)
{
    this->numRows = numRows;
    this->numCols = numCols;
    // creating array of heads for rows and columns
    rowArray = new Node[numRows];
    colArray = new Node[numCols];
}

//getter functions
char LinkedMatrix::getID() const
{
    return ID;
}

int LinkedMatrix::getNumRows() const
{
    return numRows;
}

int LinkedMatrix::getNumCols() const
{
    return numCols;
}

int LinkedMatrix::getElement(int Row_Indx, int Col_Indx) const {
    if (Row_Indx < 0 || Row_Indx >= numRows || Col_Indx < 0 || Col_Indx >= numCols) {
        // check if the indices are out of range
        cout << "Error: Indices are out of range\n";
        return 0;
    }
    Node* current = rowArray[Row_Indx].next;
    while (current != nullptr && current->column < Col_Indx) {
        current = current->next;
    }
    if (current != nullptr && current->column == Col_Indx) {
        return current->value;
    } else {
        return 0;
    }
}

void LinkedMatrix::display_mat() const
{
    int nonZeroCount = 0;

    //this loop iterates in every row and check if the node has a value, it will be counted
    for (int i = 0; i < numRows; i++)
    {
        Node *currnode = rowArray[i].next;
        while(currnode != NULL)
        {
            nonZeroCount++;
            currnode = currnode->next;
        }
    }
    cout << "Number of Rows: " << numRows << "\t Number of Columns: " << numCols << "\t Number of non-zero elements: " << nonZeroCount << endl;

    //this loop iterates in every column and check if the node has a value, it will be printed
    for (int i = 0; i < numCols; i++)
    {
        Node *currnode = colArray[i].down;
        while(currnode != NULL)
        {
            cout << "(" << currnode->row << ", " << currnode->column << ") = " << currnode->value << endl;
            currnode = currnode->down;
        }
    }
}

void LinkedMatrix::insertElement(int Row_Indx, int Col_Indx, int value)
{
    // check if row and column indices are in the range of the matrix dimensions
    if (Row_Indx >= numRows || Col_Indx >= numCols) {
        cout << "Error: row or column index out of range" << endl;
        return;
    }
    // loop through the row and find the correct position 
    Node* prevInRow = &rowArray[Row_Indx];
    Node* currentInRow = prevInRow->next;
    while (currentInRow != NULL && currentInRow->column < Col_Indx) {
        prevInRow = currentInRow;
        currentInRow = currentInRow->next;
    }
    // check the node already exists and has a value, update it. If not, create a new node for it and make also the column linkedlist points to it
    if(currentInRow != NULL) {
        currentInRow->value = value;
    }else{
        // create a new node for the element
        Node* newNode = new Node(Row_Indx, Col_Indx, value);
        //updating the pointers in the row
        newNode->next = currentInRow;
        prevInRow->next = newNode;

        // insert the new node into the column list
        Node *prevInCol = &colArray[Col_Indx];
        Node *currentInCol = prevInCol->down;
        while (currentInCol != NULL && currentInCol->row < Row_Indx) {
            prevInCol = currentInCol;
            currentInCol = currentInCol->down;
        }
        //updating the pointers in the column
        newNode->down = currentInCol;
        prevInCol->down = newNode;
    }
}

void LinkedMatrix::removeElement(int Row_Indx, int Col_Indx) 
{
    // search for the element to remove it from the row list
    Node* prevInRow = &rowArray[Row_Indx];
    Node* currentInRow = prevInRow->next;
    while (currentInRow != NULL && currentInRow->column < Col_Indx) {
        prevInRow = currentInRow;
        currentInRow = currentInRow->next;
    }
    // check if the node is not found, terminate. If not, delete the node from the row and column lists
    if (currentInRow == NULL || currentInRow->column != Col_Indx) {
        return;
    }else{
        prevInRow->next = currentInRow->next;
        delete currentInRow;
        // search for the element to remove it from the column list
        Node *prevInCol = &colArray[Col_Indx];
        Node *currentInCol = prevInCol->down;
        while (currentInCol != NULL && currentInCol->row < Row_Indx) {
            prevInCol = currentInCol;
            currentInCol = currentInCol->down;
        }
        prevInCol->down = currentInCol->down;
        delete currentInCol;
    }
}

LinkedMatrix::~LinkedMatrix() 
{
    //this function iterates in every row and check if the node has a value, it will be removed
    for (int i = 0; i < numRows; i++)
    {
        Node *currnode = rowArray[i].next;
        while(currnode != NULL)
        {
            removeElement(i, currnode->column);
            currnode = currnode->next;
        }
    }
    //deallocating the two dynamic arrays of heads
    delete[] rowArray;
    delete[] colArray;
}