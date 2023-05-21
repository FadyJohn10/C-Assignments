#include "matcomp.h"

MatComp::MatComp(){
	matrix_list = new LinkedMatrix[26];
	addedMats = 0;
};

void MatComp::importMatrix(LinkedMatrix& newMat, string filename)
{	
	// getting the number of rows and columns from the file
	ifstream fin(filename);
	string dump;
	fin >> dump;
	int row;
	sscanf(dump.c_str(), "Rows=%d", &row);
	fin >> dump;
	int col;
	sscanf(dump.c_str(), "Columns=%d", &col);
	fin >> dump;
	// setting the dimensions of the new matrix
	newMat.create(row, col);
    while(fin >> dump){
    	int x, y, z;
	    //extract integers from the input string
	    sscanf(dump.c_str(), "(%d, %d)=%d", &x, &y, &z);
	    newMat.insertElement(x, y, z);
    }
	matrix_list[addedMats] = newMat; // adding the new matrix to the matrices list
	addedMats++;
	cout << "Done! This is matrix " << matrix_list[addedMats].getID() << endl;
	
	fin.close();
}

void MatComp::exportMat(LinkedMatrix& Mat, string filename)
{
	ofstream fout(filename);
	// check opening the file
	if(fout.fail()){
        cout << "Error opening the file\n";
        return;
    }
    // loop through the matrix to count non zero elements
    int nonZeroCount = 0;
    for (int i = 0; i < Mat.getNumCols(); i++) {
        for (int j = 0; j < Mat.getNumRows(); j++) {
            // insert the values if they are not both zero
            if (Mat.getElement(j, i) != 0) {
                nonZeroCount++;
            }
        }
    }
    fout << "Rows=" << Mat.getNumRows() << endl << "Columns=" << Mat.getNumCols() << endl << "Non-ZeroElements=" << nonZeroCount << endl;
    // loop through the matrix to print the non-zero elements
    for (int i = 0; i < Mat.getNumCols(); i++) {
        for (int j = 0; j < Mat.getNumRows(); j++) {
            // insert the values if they are not both zero
            if (Mat.getElement(j, i) != 0) {
                fout << "(" << j << ", " << i << ") = " << Mat.getElement(j, i) << endl;
            }
        }
    }
    fout.close();
    cout << "Done!\n";
}

void MatComp::add(LinkedMatrix &Mat1, LinkedMatrix &Mat2)
{
    for (int i = 0; i < Mat1.getNumRows(); i++) {
        for (int j = 0; j < Mat1.getNumCols(); j++) {
            // get the values of the two matrices at the current row and column and add them
            int sum = Mat1.getElement(i, j) + Mat2.getElement(i, j);
            // insert the values if they are not both zero
            if (sum != 0) {
                // set the value of the result matrix at the current row and column
                Mat1.insertElement(i, j, sum);
            }
        }
    }
    cout << "Done! \n";
}

void MatComp::multi(LinkedMatrix &Mat, int a)
{
    for (int i = 0; i < Mat.getNumRows(); i++) {
        for (int j = 0; j < Mat.getNumCols(); j++) {
            // get the value of the two matrix at every index and multiply by the constant a
            int result = Mat.getElement(i, j) * a;

            // insert the values if the product is not zero
            if (result != 0) {
                // set the value of the result matrix at the current row and column
                Mat.insertElement(i, j, result);
            }
        }
    }
    cout << "Done!\n";
}

void MatComp::multi(LinkedMatrix &Mat1, LinkedMatrix &Mat2, LinkedMatrix &Mat3)
{
    Mat3.create(Mat1.getNumRows(), Mat2.getNumCols()); // create a new martix for the product matrix

    for (int i = 0; i < Mat1.getNumRows(); i++) {
        for (int j = 0; j < Mat2.getNumCols(); j++) {
            int result = 0;
            for(int m = 0; m<Mat1.getNumCols(); m++) {

                result += Mat1.getElement(i, m) * Mat2.getElement(m, j);

            }
            // insert the values if the entry(i,j) productis not zero
            if (result != 0) {
                Mat3.insertElement(i, j, result);
            }
        }
    }
    matrix_list[addedMats] = Mat3; // add the craeted matrix to the matrices list
	addedMats++;
    Mat3.display_mat();
    cout << "Done!\n";
}

void MatComp::display(LinkedMatrix &Mat)
{
	Mat.display_mat();
}

// getter function to retuen matrices list
LinkedMatrix* MatComp::getMatrixList()
{
	return matrix_list;
}

int MatComp::getMatsNum()
{
	return addedMats;
}

MatComp::~MatComp()
{
    for(int i=0; i<addedMats; i++){
        matrix_list[i].~LinkedMatrix();
    }
    delete[] matrix_list;
}