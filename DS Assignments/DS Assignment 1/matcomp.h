//============================================================================
// Name         : DS Assignment#1
// Author       : Mai Oudah
// Version      : 1.0
// Date Created : 11-02-2023
// Date Modified:  
// Description  : Matrix Computation in C++ 
//============================================================================

#include<fstream>
#include<string>
#include "linkedmatrix.h"
using namespace std;
//=======================================
class MatComp
{
	private:
		LinkedMatrix* matrix_list; //the imported and generated matrices will be stored in this array
		int addedMats;
	public:
		MatComp();
		void importMatrix(LinkedMatrix& newMat, string filename); 
		void multi(LinkedMatrix& Mat, int a);
		void add(LinkedMatrix& Mat1, LinkedMatrix& Mat2);
		void multi(LinkedMatrix& Mat1, LinkedMatrix& Mat2, LinkedMatrix& Mat3);
		void exportMat(LinkedMatrix& Mat, string filename);
		void display(LinkedMatrix& Mat);

		//add any other necessary code here
		LinkedMatrix* getMatrixList();
		int getMatsNum();
		~MatComp();
};
