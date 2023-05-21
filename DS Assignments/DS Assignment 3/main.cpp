
//=================================================================================
// Name         : DS Assignment#3
// Author       : Mai Oudah
// Version      : 1.0
// Date Created : 25-April-2023
// Date Modified: 
// Description  : Starter Code for Word Count Wizard using HASH TABLE in C++
//=================================================================================
#include<iostream>
#include<cstdlib>
#include<sstream>

#include "dochashtable.h"
#include "mylist.h"
//==========================================================
void listCommands()
{
	cout<<"\n ==================================================================="<<endl
        <<" Welcome to the Word Count Wizard!"<<endl
        <<" List of available Commands:"<<endl
        <<" import <path>           :Import a TXT file"<<endl
        <<" select_hashFun          :Choose a hash function"<<endl
		<<" count_collisions        :Print the number of collisions"<<endl
		<<" count_unique_words      :Print the number of unique words"<<endl
		<<" count_words             :Print the the total number of words"<<endl
		<<" find_freq <word>        :Search for a word and return its frequency"<<endl
		<<" find_max                :Print the word with the highest frequency"<<endl
		<<" exit                    :Exit the program"<<endl
		<<" ===================================================================\n"<<endl;
}
//==========================================================

// to be completed with any necessary method definitions

string lastImpFile = "";


void count_collisions(DocHASHTABLE& myTable)
{
	myTable.count_collisions();
}

void count_unique_words(DocHASHTABLE& myTable)
{
	cout << "The number of unique words is: " << myTable.count_unique_words() << endl;
}

void count_words(DocHASHTABLE& myTable)
{
	myTable.count_words();
}

void import(DocHASHTABLE& myTable, string path)
{
	ifstream myfile(path);
    // check the file openning 
    if (!myfile.is_open()) {
        cout << "Unable to open file. \n";
        return;
    }else{
    	lastImpFile = path;
		myTable.import(path);
		cout << "Done! \n";
		myTable.count_collisions();
		count_unique_words(myTable);
		myTable.count_words();
		myfile.close();
    }

	
}

void select_hashFun(DocHASHTABLE& myTable)
{
	cout << "Enter the Hash Function ID: [1, 2, 3, 4, 5, 6] \n";
	string choice;
	cout << ">";
	getline(cin, choice);
	if (choice.empty()){
		myTable.select_hashFun(5);
	}else if(stoi(choice) < 1 || stoi(choice) > 6){
		cout << "Invalid Input\n";
	}else{
		myTable.select_hashFun(stoi(choice));
	}
	
	import(myTable, lastImpFile);
}

void find_freq(DocHASHTABLE& myTable, string word)
{
	cout << "The frequency of the word \"" << word << "\" is: " << myTable.find_freq(word) << endl;
}

void find_max(DocHASHTABLE& myTable)
{
	cout << "The word with the highest frequency is: " << myTable.find_max() << endl;
}

//==========================================================
// main function
int main()
{
	DocHASHTABLE myDocHASHTABLE;

	cout << "Greetings! Welcome to the Word Count Wizard! \n" << "Please provide a path to the file you want to analyze: \n>";
	string path;
	cin >> path;
	import(myDocHASHTABLE, path);
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	string user_input;
    string command;
	string params[2];
	while(true)
	{
		listCommands();
		//to be completed 

		params[0] = "";
	    params[1] = "";
		cout<<">";
		getline(cin,user_input);

		istringstream ss(user_input);
		int i = 0;
		while (ss >> command) {
			params[i] = command;
			i++;
		}

		try
		{
			if (params[0]=="import") 				import(myDocHASHTABLE, params[1]);
			else if(params[0]=="select_hashFun")    select_hashFun(myDocHASHTABLE);
			else if(params[0]=="count_collisions")	count_collisions(myDocHASHTABLE);	
			else if(params[0]=="count_unique_words")count_unique_words(myDocHASHTABLE);	
			else if(params[0]=="count_words")		count_words(myDocHASHTABLE);	
			else if(params[0]=="find_freq")			find_freq(myDocHASHTABLE, params[1]);
			else if(params[0]=="find_max")			find_max(myDocHASHTABLE);	
			else if(command == "exit")          	break;
			else if(user_input=="")             	continue;
			else                                	cout<<"Invalid Command!"<<endl;
		}
		catch(exception &e)
		{
			cout<<"Exception: "<<e.what()<<endl;
		}

	}

	return EXIT_SUCCESS;
}
