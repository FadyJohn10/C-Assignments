//============================================================================
// Name         : DS Assignment#1
// Author       : Mai Oudah
// Version      : 1.0
// Date Created : 09-02-2023
// Date Modified: 
// Description  : Matrix Computation - Main Program
//============================================================================
#include<iostream>
#include<string>
#include<fstream>
#include<exception>
#include<sstream>
#include<iomanip>

#include "linkedmatrix.h"
#include "matcomp.h"
using namespace std;

//=====================================
void listCommands()
{
	cout<<" ===================================================================================="<<endl
        <<" Welcome to the Matrix Computation system!\n"<<endl
        <<" List of available Commands:"<<endl
		<<" import <file_name>    : Read a matrix from <filename>"<<endl
		<<" export <file_name>    : Write a matrix into <filename>"<<endl
		<<" add                   : Add 2 matrices A and B and store the result in matrix A"<<endl
		<<" multi-by-const <const> : Multiply a matrix by a constant and update the matrix"<<endl
		<<" multi-by-matrix        : Multiply a matrix by another matrix and return the resultant"<<endl     
		<<" display               : Display a matrix in the optimized structure"<<endl
		<<" help                  : Display the list of available commands"<<endl
		<<" exit                  : Exit the Program"<<endl
		<<" ====================================================================================\n"<<endl;
		

}

// define the needed methods to execute the operations in the system (import, export, add, ...)

// function to convert the ID given by user to an integer (index) for accessing the matrix list
int idToIndex(char id)
{
	return id-65;
}


//=======================================
// main function
int main()
{
	int ATTEMPS;
	MatComp matCompSys;
	LinkedMatrix tempMat;
	LinkedMatrix *listOfMats = matCompSys.getMatrixList();

	listCommands();
	string user_input;
	string command;
	string parameter;

	do
	{
		cout<<"> ";
		getline(cin,user_input);
		
		// parse userinput into command and parameter(s)
		stringstream sstr(user_input);
		getline(sstr,command,' ');
		getline(sstr,parameter);
		
		//add code as necessary
		if(command == "import")
		{
			ifstream fin;
			fin.open(parameter);
			if(fin){
				matCompSys.importMatrix(tempMat, parameter);
		    }else{
		    	ATTEMPS = 2;
			    while(ATTEMPS--){
			    	string filename;
			    	cout << "Error opening the file. Enter the filename again: ";
			    	cin >> filename;
			    	fin.open(filename);
			    	if(fin){
			    		matCompSys.importMatrix(tempMat, filename);
			    		break;
			    	}
			    }
			    if(ATTEMPS<0){cout<<"You have no more attemps!! \n";}
		    }
		}else if(command == "export")
		{
			if (matCompSys.getMatsNum() == 0) //check if the system does not contain matrices
			{
				cout << "There is no matrix in the system.\n";
			}else
			{
				ATTEMPS = 3;
				while(ATTEMPS--)
				{
					char id;
					cout << "please provide the 1st matrix ID [A, B, C, ...] \n";
					cin >> id;
					if(id > 'A' + matCompSys.getMatsNum()-1 || id<'A') // check if the matrix exist (the given ID is out of range)
					{
						cout << "No matrix with this ID exists in the system!\n";
					}else
					{
						matCompSys.exportMat(listOfMats[idToIndex(id)], parameter);
						break;
					}	
				}
				if(ATTEMPS<0){cout<<"You have no more attemps!! \n";}
			}
		}else if(command == "add")
		{

			if (matCompSys.getMatsNum() == 0) //check if the system does not contain matrices
			{
				cout << "There is no matrix in the system.\n";
			}else
			{
				ATTEMPS = 3;
				while(ATTEMPS--)
				{
					char id1, id2;
					cout << "please provide the 1st matrix ID [A, B, C, ...] \n";
					cin >> id1;
					cout << "please provide the 2nd matrix ID [A, B, C, ...] \n";
					cin >> id2;
					if(listOfMats[idToIndex(id1)].getNumRows() != listOfMats[idToIndex(id2)].getNumRows() || listOfMats[idToIndex(id1)].getNumCols() != listOfMats[idToIndex(id2)].getNumCols()) //check the condition for the addition process
					{
						cout << "The dimensions of the matrices are not the same. try again \n";
					}else if(id1 > 'A'+matCompSys.getMatsNum()-1 || id1<'A' || id2 > 'A'+matCompSys.getMatsNum()-1 || id2<'A') //check if the two matrix exist (one of the two given IDs is out of range)
					{
						cout << "No matrix with this ID exists in the system!\n";
					}
					else
					{
						matCompSys.add(listOfMats[idToIndex(id1)], listOfMats[idToIndex(id2)]);
						break;
					}	
				}
				if(ATTEMPS<0){cout<<"You have no more attemps!! \n";}
			}
		}
		else if(command == "multi-by-const")
		{
			if (matCompSys.getMatsNum() == 0) //check if the system does not contain matrices
			{
				cout << "There is no matrix in the system.\n";
			}else
			{
				ATTEMPS = 3;
				while(ATTEMPS--)
				{
					char id;
					cout << "please provide the 1st matrix ID [A, B, C, ...] \n";
					cin >> id;
					if(id > 'A'+matCompSys.getMatsNum()-1 || id<'A') // check if the matrix exist (the given ID is out of range)
					{
						cout << "No matrix with this ID exists in the system!\n";
					}else
					{
						matCompSys.multi(listOfMats[idToIndex(id)], stoi(parameter));
						break;
					}	
				}
				if(ATTEMPS<0){cout<<"You have no more attemps!! \n";}
			}
		}
		else if(command == "multi-by-matrix")
		{
			if (matCompSys.getMatsNum() == 0) //check if the system does not contain matrices
			{
				cout << "There is no matrix in the system.\n";
			}else
			{
				ATTEMPS = 3;
				while(ATTEMPS--)
				{
					char id1, id2;
					cout << "please provide the 1st matrix ID [A, B, C, ...] \n";
					cin >> id1;
					cout << "please provide the 2nd matrix ID [A, B, C, ...] \n";
					cin >> id2;
					if(listOfMats[idToIndex(id1)].getNumCols() != listOfMats[idToIndex(id2)].getNumRows()) //check the condition for the multiplication process
					{
						cout << "Number of cols of 1st matrix is not equal to Number of rows of 2nd matrix. try again \n";
					}else if(id1 > 'A'+matCompSys.getMatsNum()-1 || id1<'A' || id2 > 'A'+matCompSys.getMatsNum()-1 || id2<'A') //check if the two matrix exist and also check if one of the two given IDs is out of range
					{
						cout << "No matrix with this ID exists in the system!\n";
					}
					else
					{
						matCompSys.multi(listOfMats[idToIndex(id1)], listOfMats[idToIndex(id2)], tempMat);
						break;
					}	
				}
				if(ATTEMPS<0){cout<<"You have no more attemps!! \n";}
			}
		}
		else if(command == "display")
		{
			if (matCompSys.getMatsNum() == 0) //check if the system does not contain matrices
			{
				cout << "There is no matrix in the system.\n";
			}else
			{
				ATTEMPS = 3;
				while(ATTEMPS--)
				{
					char id;
					cout << "please provide the 1st matrix ID [A, B, C, ...] \n";
					cin >> id;
					if(id > 'A'+matCompSys.getMatsNum()-1 || id<'A') // check if the matrix exist and also check if the given ID is out of range
					{
						cout << "No matrix with this ID exists in the system!\n";
					}else
					{
						matCompSys.display(listOfMats[idToIndex(id)]);
						break;
					}	
				}
				if(ATTEMPS<0){cout<<"You have no more attemps!! \n";}
			}
		}
		else if(command == "help")			listCommands();
		else if(command == "exit"){break;}
		else 							cout<<"Invalid Command!"<<endl;
		fflush(stdin);
	}while(true);

	return EXIT_SUCCESS;
}